
%token_type { ValueNode* }
%extra_argument { ProgramNode** arg }

%include {
#include "AST.h"
#include <assert.h>
#ifdef _MSC_VER
#pragma warning(disable:4100 4189)
#endif

#if INTERFACE
typedef struct ProgramNodeType ProgramNode;
typedef struct ValueNodeImpl ValueNode;
#define YYMALLOCARGTYPE size_t
#endif
}

%name Parser_v0_1_
%token_prefix TOKEN_

%type types       { ProgramNode* }
%type type        { TypeNode* }
%type values      { TypeNode* }
%type value       { AssignNode* }
%type expression  { ExpressionNode* }
%type vector      { VectorNode* }
%type vector_vals { VectorNode* }
%type number      { ValueNode* }

entry ::= program END.
program ::= IDENTIFIER NUMBER types(B).      { *arg = B; }
types(A) ::= types(B) type(C).               { A = B; Add(A, C); }
types(A) ::= type(B).                        { A = CreateProgramNode(); Add(A, B); }
type(A) ::= IDENTIFIER(B) LBRACE 		     
			values(C) RBRACE SEMICOLON.      { A = C; SetIden(A, B); }
values(A) ::= values(B) value(C).            { A = B; Add(A, C); }
values(A) ::= value(B).                      { A = CreateTypeNode(); Add(A, B); }
value(A) ::= IDENTIFIER(B) COLON 		     
             expression(C) SEMICOLON.        { A = CreateAssignNode(B, C); }
expression(A) ::= number(B).                 { A = CreateExpressionNode(B); }
expression(A) ::= IDENTIFIER(B).             { A = CreateExpressionNode(B); }
expression(A) ::= IDENTIFIER(B) vector(C).   { A = CreateColourNode(B, C); }
expression(A) ::= number(B) IDENTIFIER(C).   { A = CreateUnitValueNode(B, C); }
expression(A) ::= vector(B).                 { A = CreateVecExprNode(B); }
vector(A) ::= LESSER vector_vals(B) GREATER. { A = B; }
vector_vals(A) ::= vector_vals(B) 
				COMMA number(C).             { A = B; Add(A, CreateExpressionNode(C)); }
vector_vals(A) ::= number(B).                { A = CreateVectorNode(); Add(A, CreateExpressionNode(B)); }
number(A) ::= HEXVAL(B).                     { A = B; }
number(A) ::= NUMBER(B).                     { A = B; }
