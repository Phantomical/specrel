/* This file was automatically generated.  Do not edit! */
typedef struct ValueNodeImpl ValueNode;
#define Parser_v0_1_TOKENTYPE  ValueNode* 
typedef struct ProgramNodeType ProgramNode;
#define Parser_v0_1_ARG_PDECL , ProgramNode** arg 
void Parser_v0_1_(void *yyp,int yymajor,Parser_v0_1_TOKENTYPE yyminor Parser_v0_1_ARG_PDECL);
#if defined(YYTRACKMAXSTACKDEPTH)
int Parser_v0_1_StackPeak(void *p);
#endif
void Parser_v0_1_Free(void *p,void(*freeProc)(void *));
#define YYMALLOCARGTYPE size_t
void *Parser_v0_1_Alloc(void *(*mallocProc)(YYMALLOCARGTYPE));
#if !defined(NDEBUG)
void Parser_v0_1_Trace(FILE *TraceFILE,char *zTracePrompt);
#endif
#define Parser_v0_1_ARG_STORE yypParser->arg  = arg 
#define Parser_v0_1_ARG_FETCH  ProgramNode** arg  = yypParser->arg 
#define Parser_v0_1_ARG_SDECL  ProgramNode** arg ;
#define TOKEN_HEXVAL                         10
#define TOKEN_COMMA                           9
#define TOKEN_GREATER                         8
#define TOKEN_LESSER                          7
#define TOKEN_COLON                           6
#define TOKEN_SEMICOLON                       5
#define TOKEN_RBRACE                          4
#define TOKEN_LBRACE                          3
#define TOKEN_NUMBER                          2
#define TOKEN_IDENTIFIER                      1
#define TOKEN_STRING 32
#define INTERFACE 0
