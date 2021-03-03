#pragma once
#include <vector>
#include <string>
#include "Symbol.h"

class Node;
class StartNode;
class ProgramNode;
class BlockNode;
class StatementGroupNode;
class StatementNode;
class DeclarationStatementNode;
class AssignmentStateNode;
class CoutStatementNode;
class ExpressionNode;
class IntegerNode;
class IdentifierNode;
class BinaryOperatorNode;
class PlusNode;
class MinusNode;
class TimesNode;
class DivideNode;
class LessNode;
class LessEqualNode;
class GreaterNode;
class GreaterEqualNode;
class EqualNode;
class NotEqualNode;


class Node {

public:
	Node();
	virtual ~Node();
private:

};

class StartNode: public Node {

public:
	StartNode(ProgramNode *programNode);
	virtual ~StartNode();

private:
	ProgramNode *mProgramNode;

};

class ProgramNode : public Node {

public:
	ProgramNode(BlockNode *blockNode);
	virtual ~ProgramNode();

private:
	BlockNode *mBlockNode;
};

class BlockNode : public Node {

public:
	BlockNode(StatementGroupNode *statementGroupNode);
	virtual ~BlockNode();

private:
	StatementGroupNode *mStatementGroupNode;
};

class StatementGroupNode : public Node {

public:
	StatementGroupNode();
	virtual ~StatementGroupNode();
	void addStatement(StatementNode *statementNode);
	
private:

	std::vector<StatementNode*> mStatementNodes;

};

class StatementNode : public Node {

public:

private:

};

class DeclarationStatementNode : public StatementNode {

public:
	DeclarationStatementNode(IdentifierNode* indentifierNode);
	virtual ~DeclarationStatementNode();

private:
	IdentifierNode* mIdentifierNode;

};

class AssignmentStatementNode : public StatementNode {

public:
	AssignmentStatementNode(IdentifierNode* indentifierNode, ExpressionNode* expressionNode);
	// might not need a destructor because it inherits from node
	~AssignmentStatementNode();


private:
	IdentifierNode* mIdentifierNode;
	ExpressionNode* mExpressionNode;

};

class CoutStatementNode : public StatementNode {

public:
	CoutStatementNode(ExpressionNode* expressionNode);
	~CoutStatementNode();
	
private:
	ExpressionNode* mExpressionNode;
};

class ExpressionNode {
public:
	virtual int Evaluate() = 0;
	virtual ~ExpressionNode();

private:
};

class IntegerNode : public ExpressionNode {
public:
	IntegerNode(int val);
	virtual int Evaluate() = 0;

private:
	int mInteger;
};

class IdentifierNode : public ExpressionNode {
public:
	IdentifierNode(std::string label);
	void DeclareVariable();
	void SetValue(int v);
	int GetIndex();
	virtual int Evaluate();
private:
	std::string mLabel;
	SymbolTableClass* SymbolTable;

};


class BinaryOperatorNode : public ExpressionNode {
public:
	BinaryOperatorNode(ExpressionNode * lhs, ExpressionNode * rhs);
	~BinaryOperatorNode();
protected:
	ExpressionNode * mRhs;
	ExpressionNode * mLhs;
private:
};

class PlusNode : public BinaryOperatorNode {
public:
	PlusNode(ExpressionNode * lhs, ExpressionNode * rhs);
	virtual int Evaluate();

private:

};

class MinusNode : public BinaryOperatorNode {
public:
	MinusNode(ExpressionNode *lhs, ExpressionNode *rhs );
	virtual int Evaluate();
private:
};

class TimesNode : public BinaryOperatorNode {
public:
	TimesNode(ExpressionNode *lhs, ExpressionNode *rhs );
	virtual int Evaluate();
private:
};

class DivideNode : public BinaryOperatorNode {
public:
	DivideNode(ExpressionNode *lhs, ExpressionNode *rhs );
	virtual int Evaluate();
private:
};

class LessNode : public BinaryOperatorNode {
public:
	LessNode(ExpressionNode *lhs, ExpressionNode *rhs );
	virtual int Evaluate();
private:
};

class LessEqualNode : public BinaryOperatorNode {
public:
	LessEqualNode(ExpressionNode *lhs, ExpressionNode *rhs );
	virtual int Evaluate();
private:
};

class GreaterNode : public BinaryOperatorNode {
public:
	GreaterNode(ExpressionNode *lhs, ExpressionNode *rhs );
	virtual int Evaluate();
private:
};

class GreaterEqualNode : public BinaryOperatorNode {
public:
	GreaterEqualNode(ExpressionNode *lhs, ExpressionNode *rhs );
	virtual int Evaluate();
private:
};

class EqualNode : public BinaryOperatorNode {
public:
	EqualNode(ExpressionNode *lhs, ExpressionNode *rhs );
	virtual int Evaluate();
private:
};

class NotEqualNode : public BinaryOperatorNode {
public:
	NotEqualNode(ExpressionNode *lhs, ExpressionNode *rhs );
	virtual int Evaluate();
private:
};





