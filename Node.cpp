#include "Node.h"

Node::Node() {
}

Node::~Node() {
}

// START NODE
StartNode::StartNode(ProgramNode* programNode){
	mProgramNode = programNode;
}

StartNode::~StartNode() {
	delete mProgramNode;
}

// PROGRAM NODE
ProgramNode::ProgramNode(BlockNode* blockNode) {
	mBlockNode = blockNode;
}

ProgramNode::~ProgramNode() {
	delete mBlockNode;
}

// BLOCK NODE
BlockNode::BlockNode(StatementGroupNode* statementGroupNode) {
	mStatementGroupNode = statementGroupNode;
}

BlockNode::~BlockNode() {
	delete mStatementGroupNode;
}

// STATEMENT GROUP NODE
StatementGroupNode::StatementGroupNode() {

}

StatementGroupNode::~StatementGroupNode() {
	for (int i = 0; i < mStatementNodes.size(); i++) {
		delete mStatementNodes[i];
	}
}

void StatementGroupNode::addStatement(StatementNode* statementNode) {
	mStatementNodes.push_back(statementNode);
}


DeclarationStatementNode::DeclarationStatementNode( IdentifierNode* identifierNode) {
	mIdentifierNode = identifierNode;
}

DeclarationStatementNode::~DeclarationStatementNode() {
	delete mIdentifierNode;
}

// ASSIGNEMNT STATEMENT NODE
AssignmentStatementNode::AssignmentStatementNode(IdentifierNode* identifierNode, ExpressionNode* expressionNode){
	mIdentifierNode = identifierNode;
	mExpressionNode = expressionNode;
}

AssignmentStatementNode::~AssignmentStatementNode() {
	delete mIdentifierNode;
	delete mExpressionNode;
}

// COUT STATEMENT NODE
CoutStatementNode::CoutStatementNode(ExpressionNode* expressionNode) {
	mExpressionNode = expressionNode;
}

CoutStatementNode::~CoutStatementNode() {
	delete mExpressionNode;
}


// EXPRESSION NODE

ExpressionNode::~ExpressionNode() {

}

// INTEGER NODE
IntegerNode::IntegerNode(int val) {
	mInteger = val;
}

int IntegerNode::Evaluate() {
	return mInteger;
}


// IDENTIFIER NODE

IdentifierNode::IdentifierNode(std::string label) {
	mLabel = label;
	}

void IdentifierNode::DeclareVariable() {
	SymbolTable->AddEntry(mLabel);
	}

void IdentifierNode::SetValue(int v) {
	SymbolTable->SetValue(mLabel, v);
	}

int IdentifierNode::GetIndex() {
	return SymbolTable->GetIndex(mLabel);
	}

int IdentifierNode::Evaluate() {
	return SymbolTable->GetValue(mLabel);
}


// BINARY OPERATOR NODE
BinaryOperatorNode::BinaryOperatorNode(ExpressionNode* rhs, ExpressionNode* lhs) {
	mRhs = rhs;
	mLhs = lhs;
	}

BinaryOperatorNode::~BinaryOperatorNode() {
	delete mRhs;
	delete mLhs;
}


// PLUS NODE

PlusNode::PlusNode(ExpressionNode* rhs, ExpressionNode* lhs)
	: BinaryOperatorNode(rhs, lhs){
}

int PlusNode::Evaluate() {
	int retval = 0;
	retval += mRhs->Evaluate();
	retval += mLhs->Evaluate();
	return retval;
}
