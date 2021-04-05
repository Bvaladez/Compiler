#pragma once
#include <vector>
#include <string>
#include "Symbol.h"

class Node;
class StatementNode;
class StartNode;
class ProgramNode;
class BlockNode;
class StatementGroupNode;
class DeclarationStatementNode;
class AssignmentStateNode;
class IfStatementNode;
class WhileStatementNode;
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
	virtual void Interpret() = 0;
	virtual ~Node();
private:

};

class StartNode: public Node {

public:
	StartNode(ProgramNode *programNode);
	virtual ~StartNode();
	void Interpret();

private:
	ProgramNode *mProgramNode;

};

class ProgramNode : public Node {

public:
	ProgramNode(BlockNode *blockNode);
	virtual ~ProgramNode();
	void Interpret();

private:
	BlockNode *mBlockNode;
};

class StatementNode : public Node {

public:
	StatementNode();
	virtual ~StatementNode();

private:

};

class BlockNode : public StatementNode {

public:
	BlockNode(StatementGroupNode *statementGroupNode);
	virtual ~BlockNode();
	void Interpret();

private:
	StatementGroupNode *mStatementGroupNode;
};

class StatementGroupNode : public Node {

public:
	StatementGroupNode();
	virtual ~StatementGroupNode();
	void addStatement(StatementNode *statementNode);
	void Interpret();
	
private:
	std::vector<StatementNode*> mStatementNodes;

};

class DeclarationStatementNode : public StatementNode {

public:
	DeclarationStatementNode(IdentifierNode* indentifierNode);
	virtual ~DeclarationStatementNode();
	void Interpret();

private:
	IdentifierNode* mIdentifierNode;

};

class AssignmentStatementNode : public StatementNode {

public:
	AssignmentStatementNode(IdentifierNode* indentifierNode, ExpressionNode* expressionNode);
	// might not need a destructor because it inherits from node
	~AssignmentStatementNode();
	void Interpret();


private:
	IdentifierNode* mIdentifierNode;
	ExpressionNode* mExpressionNode;

};

class IfStatementNode : public StatementNode {

public:
	IfStatementNode(ExpressionNode* expressionNode, BlockNode* blockNode);
	~IfStatementNode();
	void Interpret();

private:
	ExpressionNode* mExpressionNode;
	BlockNode* mBlockNode;
};

class WhileStatementNode : public StatementNode {

public:
	WhileStatementNode(ExpressionNode* expressionNode, BlockNode* blockNode);
	~WhileStatementNode();
	void Interpret();

private:
	ExpressionNode* mExpressionNode;
	BlockNode* mBlockNode;
};

class CoutStatementNode : public StatementNode {

public:
	CoutStatementNode(ExpressionNode* expressionNode);
	~CoutStatementNode();
	void Interpret();
	
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
	virtual int Evaluate();

private:
	int mInteger;
};

class IdentifierNode : public ExpressionNode {
public:
	IdentifierNode(std::string label, SymbolTableClass * symbolTable);
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

class AndNode : public BinaryOperatorNode {

public:
	AndNode(ExpressionNode * lhs, ExpressionNode * rhs);
	virtual int Evaluate();

private:
};

class OrNode : public BinaryOperatorNode {

public:
	OrNode(ExpressionNode * lhs, ExpressionNode * rhs);
	virtual int Evaluate();

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





