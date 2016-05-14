#include "AST.h"
#include "AstDefs.h"

extern "C" AssignNode* CreateAssignNode(ValueNode* iden, ExpressionNode* expr)
{
	return new AssignNode(iden, expr);
}
extern "C" ExpressionNode* CreateColourNode(ValueNode* iden, VectorNode* vec)
{
	return new ExpressionNode(new ColourNode(iden, vec));
}
extern "C" ExpressionNode* CreateUnitValueNode(ValueNode* num, ValueNode* iden)
{
	return new ExpressionNode(new UnitValueNode(num, iden));
}
extern "C" ExpressionNode* CreateExpressionNode(ValueNode* iden)
{
	return new ExpressionNode(iden);
}
extern "C" ExpressionNode* CreateVecExprNode(VectorNode* vec)
{
	return new ExpressionNode(vec);
}
extern "C" ProgramNode* CreateProgramNode()
{
	ProgramNode* prg = new ProgramNode();
	prg->Add = [](ProgramNodeImpl* impl, TypeNode* type) { impl->Types.push_back(type); };
	prg->Impl = new ProgramNodeImpl();
	return prg;
}
extern "C" TypeNode* CreateTypeNode()
{
	TypeNode* type = new TypeNode();
	type->Add = [](TypeNodeImpl* impl, AssignNode* node) { impl->Nodes.push_back(node); };
	type->SetIden = [](TypeNodeImpl* impl, ValueNode* v) { impl->Identifier = v; };
	type->Impl = new TypeNodeImpl();
	return type;
}
extern "C" VectorNode* CreateVectorNode()
{
	VectorNode* vec = new VectorNode();
	vec->Add = [](VectorNodeImpl* impl, ExpressionNode* val) { impl->Values.push_back(val); };
	vec->Impl = new VectorNodeImpl();
	return vec;
}

void DeleteNode(TypeNode* t)
{
	delete t->Impl;
	delete t;
}
void DeleteNode(ProgramNode* p)
{
	delete p->Impl;
	delete p;
}
void DeleteNode(VectorNode* v)
{
	delete v->Impl;
	delete v;
}
