#include "Debug.h"
#include "Node.h" 

// BASE NODE
Node::Node() {
}

Node::~Node() {
	MSG("Destructing Node...");
}


// START NODE
StartNode::StartNode(ProgramNode* programNode){
	mProgramNode = programNode;
}

StartNode::~StartNode() {
	MSG("Destructing Start Node...");
	delete mProgramNode;
}

void StartNode::Interpret() {
	mProgramNode->Interpret();
}

// PROGRAM NODE
ProgramNode::ProgramNode(BlockNode* blockNode) {
	mBlockNode = blockNode;
}

ProgramNode::~ProgramNode() {
	delete mBlockNode;
	MSG("Destructing Program Node...");
}

void ProgramNode::Interpret() {
	mBlockNode->Interpret();
}

// BLOCK NODE
BlockNode::BlockNode(StatementGroupNode* statementGroupNode) {
	mStatementGroupNode = statementGroupNode;
}

BlockNode::~BlockNode() {
	delete mStatementGroupNode;
	MSG("Destructing Block Node...");
}

void BlockNode::Interpret() {
	mStatementGroupNode->Interpret();
}


// STATEMENT GROUP NODE
StatementGroupNode::StatementGroupNode() {

}

StatementGroupNode::~StatementGroupNode() {
	for (int i = 0; i < mStatementNodes.size(); i++) {
		delete mStatementNodes[i];
	}
	MSG("Destructing Statement Nodes...");
}

void StatementGroupNode::addStatement(StatementNode* statementNode) {
	mStatementNodes.push_back(statementNode);
}

void StatementGroupNode::Interpret() {
	for (int i = 0; i < mStatementNodes.size(); i++) {
		mStatementNodes[i]->Interpret();
	}
}

// STATEMENT NODE 
StatementNode::StatementNode() {

}

StatementNode::~StatementNode() {

}

// DECLARATION STATEMENT NODE
DeclarationStatementNode::DeclarationStatementNode( IdentifierNode* identifierNode) {
	mIdentifierNode = identifierNode;
}

DeclarationStatementNode::~DeclarationStatementNode() {
	delete mIdentifierNode;
	MSG("Destructing Statement Declaration Statement Node...");
}

void DeclarationStatementNode::Interpret() {
	mIdentifierNode->DeclareVariable();
}

// ASSIGNEMNT STATEMENT NODE
AssignmentStatementNode::AssignmentStatementNode(IdentifierNode* identifierNode, ExpressionNode* expressionNode){
	mIdentifierNode = identifierNode;
	mExpressionNode = expressionNode;
}

AssignmentStatementNode::~AssignmentStatementNode() {
	delete mIdentifierNode;
	delete mExpressionNode;
	MSG("Destructing Statement Assignment Statement Node...");
}

void AssignmentStatementNode::Interpret() {
	int value = mExpressionNode->Evaluate();
	mIdentifierNode->SetValue(value);
}

// IF STATMENT NODE
IfStatementNode::IfStatementNode(ExpressionNode* expressionNode, BlockNode* ifBlockNode, BlockNode* elseBlockNode) {
	mExpressionNode = expressionNode;
	mIfBlockNode = ifBlockNode;
	mElseBlockNode = elseBlockNode;
}

IfStatementNode::~IfStatementNode() {
	delete mExpressionNode;
	MSG("Destructing Statement If Statement Node...");
}

void IfStatementNode::Interpret() {
	if (mExpressionNode->Evaluate() == 1) {
		mIfBlockNode->Interpret();
	}
	else if (mElseBlockNode != NULL) {
		mElseBlockNode->Interpret();
	}
}

// WHILE STATEMENT NODE
WhileStatementNode::WhileStatementNode(ExpressionNode* expressionNode, BlockNode* blockNode) {
	mExpressionNode = expressionNode;
	mBlockNode = blockNode;
}

WhileStatementNode::~WhileStatementNode() {
	delete mExpressionNode;
	MSG("Destructing Statement While Statement Node...");
}

void WhileStatementNode::Interpret() {
	while (mExpressionNode->Evaluate() == 1) {
		mBlockNode->Interpret();
	}
}

// COUT STATEMENT NODE
CoutStatementNode::CoutStatementNode(ExpressionNode* expressionNode) {
	mExpressionNode = expressionNode;
}

CoutStatementNode::~CoutStatementNode() {
	delete mExpressionNode;
	MSG("Destructing Statement Cout Statement Node...");
}

void CoutStatementNode::Interpret() {
	int value = mExpressionNode->Evaluate();
	//std::cout << value << '\r';
	std::cout << value << std::endl;
}


// EXPRESSION NODE
ExpressionNode::~ExpressionNode() {
	MSG("Destructing Statement Expression Node...");
}


// INTEGER NODE
IntegerNode::IntegerNode(int val) {
	mInteger = val;
}

int IntegerNode::Evaluate() {
	return mInteger;
}


// IDENTIFIER NODE

IdentifierNode::IdentifierNode(std::string label, SymbolTableClass * symbolTable) {
	mLabel = label;
	SymbolTable = symbolTable;
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
BinaryOperatorNode::BinaryOperatorNode(ExpressionNode* lhs, ExpressionNode* rhs) {
	mRhs = rhs;
	mLhs = lhs;
	}

BinaryOperatorNode::~BinaryOperatorNode() {
	delete mRhs;
	delete mLhs;
	MSG("Destructing Statement Binary Operator Node...");
}

// OR STATMENT NODE
OrNode::OrNode(ExpressionNode * lhs, ExpressionNode * rhs) 
	: BinaryOperatorNode(lhs,rhs){
}

int OrNode::Evaluate() {
	int retval = 0;
	if (mLhs->Evaluate() == 1 || mRhs->Evaluate() == 1) {
		retval = 1;
	}
	return retval;
}

// AND STATMENT NODE
AndNode::AndNode(ExpressionNode * lhs, ExpressionNode * rhs)
	: BinaryOperatorNode(lhs, rhs){
}

int AndNode::Evaluate() {
	int retval = 0;
	if (mLhs->Evaluate() == 1 && mRhs->Evaluate() == 1) {
		retval = 1;
	}
	return retval;
}



// PLUS NODE

PlusNode::PlusNode(ExpressionNode* lhs, ExpressionNode* rhs)
	: BinaryOperatorNode(lhs, rhs){
}

int PlusNode::Evaluate() {
	int retval = 0;
	retval += mRhs->Evaluate();
	retval += mLhs->Evaluate();
	return retval;
}

// MINUS NODE

MinusNode::MinusNode(ExpressionNode* lhs, ExpressionNode* rhs)
	: BinaryOperatorNode(lhs, rhs){
}

int MinusNode::Evaluate() {
	int retval = 0;
	retval += mLhs->Evaluate();
	retval -= mRhs->Evaluate();
	return retval;
}

// TIMES NODE

TimesNode::TimesNode(ExpressionNode* lhs, ExpressionNode* rhs)
	: BinaryOperatorNode(lhs, rhs){
}

int TimesNode::Evaluate() {
	int retval = 0;
	retval += mLhs->Evaluate();
	retval *= mRhs->Evaluate();
	return retval;
}

// DIVIDE NODE

DivideNode::DivideNode(ExpressionNode* lhs, ExpressionNode* rhs)
	: BinaryOperatorNode(lhs, rhs){
}

int DivideNode::Evaluate() {
	int retval = 0;
	retval += mLhs->Evaluate();
	retval /= mRhs->Evaluate();
	return retval;
}

// LESS NODE

LessNode::LessNode(ExpressionNode* lhs, ExpressionNode* rhs)
	: BinaryOperatorNode(lhs, rhs){
}

int LessNode::Evaluate() {
	int retval = 0;
	if ( mLhs->Evaluate() < mRhs->Evaluate() ) {
		retval = 1;
	}
	return retval;
}

// LESS EQUAL NODE

LessEqualNode::LessEqualNode(ExpressionNode* lhs, ExpressionNode* rhs)
	: BinaryOperatorNode(lhs, rhs){
}

int LessEqualNode::Evaluate() {
	int retval = 0;
	if ( mLhs->Evaluate() <= mRhs->Evaluate() ) {
		retval = 1;
	}
	return retval;
}

// GREATER NODE

GreaterNode::GreaterNode(ExpressionNode* lhs, ExpressionNode* rhs)
	: BinaryOperatorNode(lhs, rhs){
}

int GreaterNode::Evaluate() {
	int retval = 0;
	if ( mLhs->Evaluate() > mRhs->Evaluate() ) {
		retval = 1;
	}
	return retval;
}

// GREATER EQUAL NODE

GreaterEqualNode::GreaterEqualNode(ExpressionNode* lhs, ExpressionNode* rhs)
	: BinaryOperatorNode(lhs, rhs){
}

int GreaterEqualNode::Evaluate() {
	int retval = 0;
	if ( mLhs->Evaluate() >= mRhs->Evaluate() ) {
		retval = 1;
	}
	return retval;
}

// EQUAL NODE

EqualNode::EqualNode(ExpressionNode* lhs, ExpressionNode* rhs)
	: BinaryOperatorNode(lhs, rhs){
}

int EqualNode::Evaluate() {
	int retval = 0;
	if ( mLhs->Evaluate() == mRhs->Evaluate() ) {
		retval = 1;
	}
	return retval;
}

// NOT EQUAL NODE

NotEqualNode::NotEqualNode(ExpressionNode* lhs, ExpressionNode* rhs)
	: BinaryOperatorNode(lhs, rhs){
}

int NotEqualNode::Evaluate() {
	int retval = 0;
	if ( mLhs->Evaluate() != mRhs->Evaluate() ) {
		retval = 1;
	}
	return retval;
}



