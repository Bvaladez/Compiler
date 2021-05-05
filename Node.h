#pragma once
#include <vector>
#include <string>
#include "Symbol.h"
#include "instructions.h"

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
class ExpNode;
class BitwiseAndNode;
class BitwiseOrNode;
class AndNode;
class OrNode;
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
	virtual void Code(InstructionsClass & machineCode) = 0;
	virtual void Interpret() = 0;
	virtual ~Node();
private:

};

class StartNode: public Node {

public:
	StartNode(ProgramNode *programNode);
	virtual ~StartNode();
	void Interpret();
	void Code(InstructionsClass & machineCode);

private:
	ProgramNode *mProgramNode;

};

class ProgramNode : public Node {

public:
	ProgramNode(BlockNode *blockNode);
	virtual ~ProgramNode();
	void Interpret();
	void Code(InstructionsClass & machineCode);

private:
	BlockNode *mBlockNode;
};

class StatementNode : public Node {

public:
	StatementNode();
	virtual ~StatementNode();
	virtual void Code(InstructionsClass & machineCode)=0;

private:

};

class BlockNode : public StatementNode {

public:
	BlockNode(StatementGroupNode *statementGroupNode);
	virtual ~BlockNode();
	void Interpret();
	void Code(InstructionsClass & machineCode);

private:
	StatementGroupNode *mStatementGroupNode;
};

class StatementGroupNode : public Node {

public:
	StatementGroupNode();
	virtual ~StatementGroupNode();
	void addStatement(StatementNode *statementNode);
	void Interpret();
	void Code(InstructionsClass & machineCode);
	
private:
	std::vector<StatementNode*> mStatementNodes;

};

class DeclarationStatementNode : public StatementNode {

public:
	DeclarationStatementNode(IdentifierNode* indentifierNode, ExpressionNode * expressionNode);
	virtual ~DeclarationStatementNode();
	void Interpret();
	void Code(InstructionsClass & machineCode);

private:
	IdentifierNode* mIdentifierNode;
	ExpressionNode* mExpressionNode;

};

class AssignmentStatementNode : public StatementNode {

public:
	AssignmentStatementNode(IdentifierNode* indentifierNode, ExpressionNode* expressionNode);
	// might not need a destructor because it inherits from node
	~AssignmentStatementNode();
	void Interpret();
	void Code(InstructionsClass & machineCode);

private:
	IdentifierNode* mIdentifierNode;
	ExpressionNode* mExpressionNode;

};

class TimesEqualStatementNode : public StatementNode {

public:
	TimesEqualStatementNode(IdentifierNode* indentifierNode, ExpressionNode* expressionNode);
	~TimesEqualStatementNode();
	void Interpret();
	void Code(InstructionsClass & machineCode);

private:
	IdentifierNode* mIdentifierNode;
	ExpressionNode* mExpressionNode;

};



class PlusEqualStatementNode : public StatementNode {

public:
	PlusEqualStatementNode(IdentifierNode* indentifierNode, ExpressionNode* expressionNode);
	~PlusEqualStatementNode();
	void Interpret();
	void Code(InstructionsClass & machineCode);

private:
	IdentifierNode* mIdentifierNode;
	ExpressionNode* mExpressionNode;

};

class MinusEqualStatementNode : public StatementNode {

public:
	MinusEqualStatementNode(IdentifierNode* indentifierNode, ExpressionNode* expressionNode);
	~MinusEqualStatementNode();
	void Interpret();
	void Code(InstructionsClass & machineCode);

private:
	IdentifierNode* mIdentifierNode;
	ExpressionNode* mExpressionNode;

};


class IfStatementNode : public StatementNode {

public:
	IfStatementNode(ExpressionNode* expressionNode, BlockNode* ifBlockNode, BlockNode* elseBlockNode);
	~IfStatementNode();
	void Interpret();
	void Code(InstructionsClass & machineCode);

private:
	ExpressionNode* mExpressionNode;
	BlockNode* mIfBlockNode;
	BlockNode* mElseBlockNode;
};

class WhileStatementNode : public StatementNode {

public:
	WhileStatementNode(ExpressionNode* expressionNode, BlockNode* blockNode);
	~WhileStatementNode();
	void Interpret();
	void Code(InstructionsClass & machineCode);

private:
	ExpressionNode* mExpressionNode;
	BlockNode* mBlockNode;
};

class DoWhileStatementNode : public StatementNode {

public:
	DoWhileStatementNode(ExpressionNode* expressionNode, BlockNode* blockNode);
	~DoWhileStatementNode();
	void Interpret();
	void Code(InstructionsClass & machineCode);

private:
	ExpressionNode* mExpressionNode;
	BlockNode* mBlockNode;
};


class CoutStatementNode : public StatementNode {

public:
	CoutStatementNode(std::vector<ExpressionNode*> expressionNodes);
	~CoutStatementNode();
	void Interpret();
	void Code(InstructionsClass & machineCode);
	
private:
	std::vector<ExpressionNode*> mExpressionNodes;
};

class ExpressionNode {
public:
	virtual int Evaluate() = 0;
	virtual ~ExpressionNode();
	virtual void CodeEvaluate(InstructionsClass& machineCode) = 0;

private:
};

class IntegerNode : public ExpressionNode {
public:
	IntegerNode(int val);
	virtual int Evaluate();
	virtual void CodeEvaluate(InstructionsClass& machineCode);

private:
	int mInteger;
};

class TrueNode : public ExpressionNode {
public:
	TrueNode();
	virtual int Evaluate();
	virtual void CodeEvaluate(InstructionsClass& machineCode);

private:
};

class FalseNode : public ExpressionNode {
public:
	FalseNode();
	virtual int Evaluate();
	virtual void CodeEvaluate(InstructionsClass& machineCode);

private:
};

class IdentifierNode : public ExpressionNode {
public:
	IdentifierNode(std::string label, SymbolTableClass * symbolTable);
	void DeclareVariable();
	void SetValue(int v);
	int GetIndex();
	virtual int Evaluate();
	virtual void CodeEvaluate(InstructionsClass& machineCode);

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

class BitwiseAndNode : public BinaryOperatorNode {

public:
	BitwiseAndNode(ExpressionNode * lhs, ExpressionNode * rhs);
	virtual int Evaluate();
	virtual void CodeEvaluate(InstructionsClass& machineCode);

private:
};

class BitwiseOrNode : public BinaryOperatorNode {

public:
	BitwiseOrNode(ExpressionNode * lhs, ExpressionNode * rhs);
	virtual int Evaluate();
	virtual void CodeEvaluate(InstructionsClass& machineCode);

private:
};



class AndNode : public BinaryOperatorNode {

public:
	AndNode(ExpressionNode * lhs, ExpressionNode * rhs);
	virtual int Evaluate();
	virtual void CodeEvaluate(InstructionsClass& machineCode);

private:
};

class OrNode : public BinaryOperatorNode {

public:
	OrNode(ExpressionNode * lhs, ExpressionNode * rhs);
	virtual int Evaluate();
	virtual void CodeEvaluate(InstructionsClass& machineCode);

private:
};

class ExpNode : public BinaryOperatorNode {

public:
	ExpNode(ExpressionNode* lhs, ExpressionNode* rhs);
	virtual int Evaluate();
	virtual void CodeEvaluate(InstructionsClass& machineCode);

private:
};

class PlusNode : public BinaryOperatorNode {
public:
	PlusNode(ExpressionNode * lhs, ExpressionNode * rhs);
	virtual int Evaluate();
	virtual void CodeEvaluate(InstructionsClass& machineCode);

private:

};

class MinusNode : public BinaryOperatorNode {
public:
	MinusNode(ExpressionNode *lhs, ExpressionNode *rhs );
	virtual int Evaluate();
	virtual void CodeEvaluate(InstructionsClass& machineCode);

private:
};

class TimesNode : public BinaryOperatorNode {
public:
	TimesNode(ExpressionNode *lhs, ExpressionNode *rhs );
	virtual int Evaluate();
	virtual void CodeEvaluate(InstructionsClass& machineCode);

private:
};

class DivideNode : public BinaryOperatorNode {
public:
	DivideNode(ExpressionNode *lhs, ExpressionNode *rhs );
	virtual int Evaluate();
	virtual void CodeEvaluate(InstructionsClass& machineCode);

private:
};

class LessNode : public BinaryOperatorNode {
public:
	LessNode(ExpressionNode *lhs, ExpressionNode *rhs );
	virtual int Evaluate();
	virtual void CodeEvaluate(InstructionsClass& machineCode);

private:
};

class LessEqualNode : public BinaryOperatorNode {
public:
	LessEqualNode(ExpressionNode *lhs, ExpressionNode *rhs );
	virtual int Evaluate();
	virtual void CodeEvaluate(InstructionsClass& machineCode);

private:
};

class GreaterNode : public BinaryOperatorNode {
public:
	GreaterNode(ExpressionNode *lhs, ExpressionNode *rhs );
	virtual int Evaluate();
	virtual void CodeEvaluate(InstructionsClass& machineCode);

private:
};

class GreaterEqualNode : public BinaryOperatorNode {
public:
	GreaterEqualNode(ExpressionNode *lhs, ExpressionNode *rhs );
	virtual int Evaluate();
	virtual void CodeEvaluate(InstructionsClass& machineCode);

private:
};

class EqualNode : public BinaryOperatorNode {
public:
	EqualNode(ExpressionNode *lhs, ExpressionNode *rhs );
	virtual int Evaluate();
	virtual void CodeEvaluate(InstructionsClass& machineCode);

private:
};

class NotEqualNode : public BinaryOperatorNode {
public:
	NotEqualNode(ExpressionNode *lhs, ExpressionNode *rhs );
	virtual int Evaluate();
	virtual void CodeEvaluate(InstructionsClass& machineCode);

private:
};


