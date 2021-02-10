#pragma once
#include <vector>

class Node;
class StartNode;
class ProgramNode;
class BlockNode;
class StatementGroupNode;
class StatementNode;
class IdentifierNode;
class ExpressionNode;

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

class AssignmentStatementNode : public Node {

public:
	AssignmentStatementNode(IdentifierNode* indentifierNode, ExpressionNode* expressionNode);
	// might not need a destructor because it inherits from node
	~AssignmentStatementNode();


private:
	IdentifierNode* mIdentifierNode;
	ExpressionNode* mExpressionNode;

};

