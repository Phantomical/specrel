#pragma once

#include "..\..\Defs.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NODE_IMPL(Type) typedef struct Type##Impl Type

	NODE_IMPL(ValueNode);
	NODE_IMPL(AssignNode);
	NODE_IMPL(ExpressionNode);

	struct ProgramNodeImpl;
	struct VectorNodeImpl;
	struct TypeNodeImpl;

	typedef struct TypeNode
	{
		void(*Add)(struct TypeNodeImpl*, AssignNode*);
		void(*SetIden)(struct TypeNodeImpl*, ValueNode*);
		struct TypeNodeImpl* Impl;
	} TypeNode;
	typedef struct VectorNodeType
	{
		void(*Add)(struct VectorNodeImpl*, ExpressionNode*);
		struct VectorNodeImpl* Impl;
	} VectorNode;
	typedef struct ProgramNodeType 
	{ 
		void(*Add)(struct ProgramNodeImpl*, TypeNode*); 
		struct ProgramNodeImpl* Impl; 
	} ProgramNode; 

	AssignNode* CreateAssignNode(ValueNode* iden, ExpressionNode* expr);
	ExpressionNode* CreateColourNode(ValueNode* iden, VectorNode* vec);
	ExpressionNode* CreateUnitValueNode(ValueNode* num, ValueNode* iden);
	ExpressionNode* CreateExpressionNode(ValueNode* iden);
	ExpressionNode* CreateVecExprNode(VectorNode* vec);

	ProgramNode* CreateProgramNode();
	TypeNode* CreateTypeNode();
	VectorNode* CreateVectorNode();

#undef NODE_IMPL

#define Add(A, B) A->Add(A->Impl, B)
#define SetIden(A, B) A->SetIden(A->Impl, B)

#ifdef __cplusplus
}
#endif
