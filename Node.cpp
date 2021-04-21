#include <cmath>

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

void StartNode::Code(InstructionsClass& machineCode) {
	mProgramNode->Code(machineCode);
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

void ProgramNode::Code(InstructionsClass& machineCode) {
	mBlockNode->Code(machineCode);
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

void BlockNode::Code(InstructionsClass& machineCode) {
	mStatementGroupNode->Code(machineCode);
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

void StatementGroupNode::Code(InstructionsClass& machineCode) {
	for (int i = 0; i < mStatementNodes.size(); i++) {
		mStatementNodes[i]->Code(machineCode);
	}
}
// STATEMENT NODE 
StatementNode::StatementNode() {

}

StatementNode::~StatementNode() {

}


// DECLARATION STATEMENT NODE
DeclarationStatementNode::DeclarationStatementNode( IdentifierNode* identifierNode, ExpressionNode* expressionNode) {
	mIdentifierNode = identifierNode;
	mExpressionNode = expressionNode;
}

DeclarationStatementNode::~DeclarationStatementNode() {
	delete mIdentifierNode;
	delete mExpressionNode;
	MSG("Destructing Statement Declaration Statement Node...");
}

void DeclarationStatementNode::Interpret() {
	mIdentifierNode->DeclareVariable();
	if (mExpressionNode != NULL) {
		mIdentifierNode->SetValue(mExpressionNode->Evaluate());
	}
}

void DeclarationStatementNode::Code(InstructionsClass& machineCode) {
	mIdentifierNode->DeclareVariable();
	if (mExpressionNode != NULL) {
		mExpressionNode->CodeEvaluate(machineCode);
		int index = mIdentifierNode->GetIndex();
		machineCode.PopAndStore(index);
	}
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

void AssignmentStatementNode::Code(InstructionsClass& machineCode) {
	mExpressionNode->CodeEvaluate(machineCode);
	int index = mIdentifierNode->GetIndex();
	machineCode.PopAndStore(index);
}

// PLUS EQUAL STATEMENT NODE
PlusEqualStatementNode::PlusEqualStatementNode(IdentifierNode* identifierNode, ExpressionNode* expressionNode){
	mIdentifierNode = identifierNode;
	mExpressionNode = expressionNode;
}

PlusEqualStatementNode::~PlusEqualStatementNode() {
	delete mIdentifierNode;
	delete mExpressionNode;
	MSG("Destructing Statement Assignment Statement Node...");
}

void PlusEqualStatementNode::Interpret() {
	int addValue = mExpressionNode->Evaluate();
	int currentValue = mIdentifierNode->Evaluate();
	mIdentifierNode->SetValue(currentValue + addValue);
}

void PlusEqualStatementNode::Code(InstructionsClass& machineCode) {
	int index = mIdentifierNode->GetIndex();
	machineCode.PushValue(index);
	mExpressionNode->CodeEvaluate(machineCode);
	machineCode.PopPopAddPush();
	machineCode.PopAndStore(index);
}

// MINUS EQUAL STATEMENT NODE
MinusEqualStatementNode::MinusEqualStatementNode(IdentifierNode* identifierNode, ExpressionNode* expressionNode){
	mIdentifierNode = identifierNode;
	mExpressionNode = expressionNode;
}

MinusEqualStatementNode::~MinusEqualStatementNode() {
	delete mIdentifierNode;
	delete mExpressionNode;
	MSG("Destructing Statement Assignment Statement Node...");
}

void MinusEqualStatementNode::Interpret() {
	int addValue = mExpressionNode->Evaluate();
	int currentValue = mIdentifierNode->Evaluate();
	mIdentifierNode->SetValue(currentValue - addValue);
}

void MinusEqualStatementNode::Code(InstructionsClass& machineCode) {
	int index = mIdentifierNode->GetIndex();
	machineCode.PushValue(index);
	mExpressionNode->CodeEvaluate(machineCode);
	machineCode.PopPopSubPush();
	machineCode.PopAndStore(index);
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

void IfStatementNode::Code(InstructionsClass& machineCode) {
	//else statements will not work with current coding
	mExpressionNode->CodeEvaluate(machineCode);
	unsigned char* InsertAddress = machineCode.SkipIfZeroStack();
	unsigned char* address1 = machineCode.GetAddress();
	mIfBlockNode->Code(machineCode);
	unsigned char* address2 = machineCode.GetAddress();
	machineCode.SetOffset(InsertAddress, (int)(address2 - address1));
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

void WhileStatementNode::Code(InstructionsClass& machineCode) {
	unsigned char* address1 = machineCode.GetAddress();
	mExpressionNode->CodeEvaluate(machineCode);
	unsigned char* InsertAddressToSkip = machineCode.SkipIfZeroStack();
	unsigned char* address2 = machineCode.GetAddress();
	mBlockNode->Code(machineCode);
	unsigned char* InsertAddressToJump = machineCode.Jump();
	unsigned char* address3 = machineCode.GetAddress();
	machineCode.SetOffset(InsertAddressToSkip, (int)(address3 - address2));
	machineCode.SetOffset(InsertAddressToJump, (int)(address1 - address3));

}

// COUT STATEMENT NODE
CoutStatementNode::CoutStatementNode(std::vector<ExpressionNode*> expressionNodes) {
	mExpressionNodes = expressionNodes;
}

CoutStatementNode::~CoutStatementNode() {
	for (int i = 0; i < mExpressionNodes.size(); i++) {
		delete mExpressionNodes[i];
	}
	MSG("Destructing Statement Cout Statement Node...");
}

void CoutStatementNode::Interpret() {
	for (int i = 0; i < mExpressionNodes.size(); i++) {
		if (mExpressionNodes[i] != NULL) {
			int value = mExpressionNodes[i]->Evaluate();
			std::cout << value;
		}
		else {
			std::cout << std::endl;
		}
	}
}

void CoutStatementNode::Code(InstructionsClass& machineCode) {
	for (int i = 0; i < mExpressionNodes.size(); i++) {
		if (mExpressionNodes[i] != NULL) {
			mExpressionNodes[i]->CodeEvaluate(machineCode);
			machineCode.PopAndWrite(); 
		}
		else {
			machineCode.WriteEndl();
		}
	}
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

void IntegerNode::CodeEvaluate(InstructionsClass& machineCode) {
	machineCode.PushValue(mInteger);
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

void IdentifierNode::CodeEvaluate(InstructionsClass& machineCode) {
	machineCode.PushVariable(this->GetIndex());
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

// BITWISE OR STATMENT NODE
BitwiseOrNode::BitwiseOrNode(ExpressionNode * lhs, ExpressionNode * rhs) 
	: BinaryOperatorNode(lhs,rhs){
}

int BitwiseOrNode::Evaluate() {
	int retval = mLhs->Evaluate() | mRhs->Evaluate();
	return retval;
}

void BitwiseOrNode::CodeEvaluate(InstructionsClass& machineCode) {
	void;
}


// BITWISE AND STATMENT NODE
BitwiseAndNode::BitwiseAndNode(ExpressionNode * lhs, ExpressionNode * rhs)
	: BinaryOperatorNode(lhs, rhs){
}

int BitwiseAndNode::Evaluate() {
	int retval = (mLhs->Evaluate() & mRhs->Evaluate());
	return retval;
}

void BitwiseAndNode::CodeEvaluate(InstructionsClass& machineCode) {
	void;
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

void OrNode::CodeEvaluate(InstructionsClass& machineCode) {
	mLhs->CodeEvaluate(machineCode);
	mRhs->CodeEvaluate(machineCode);
	machineCode.PopPopOrPush();
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

void AndNode::CodeEvaluate(InstructionsClass& machineCode) {
	mLhs->CodeEvaluate(machineCode);
	mRhs->CodeEvaluate(machineCode);
	machineCode.PopPopAndPush();
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

void PlusNode::CodeEvaluate(InstructionsClass& machineCode) {
	mLhs->CodeEvaluate(machineCode);
	mRhs->CodeEvaluate(machineCode);
	machineCode.PopPopAddPush();
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

void MinusNode::CodeEvaluate(InstructionsClass& machineCode) {
	mLhs->CodeEvaluate(machineCode);
	mRhs->CodeEvaluate(machineCode);
	machineCode.PopPopSubPush();
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

void TimesNode::CodeEvaluate(InstructionsClass& machineCode) {
	mLhs->CodeEvaluate(machineCode);
	mRhs->CodeEvaluate(machineCode);
	machineCode.PopPopMulPush();
}

// EXPONENT STATMENT NODE
ExpNode::ExpNode(ExpressionNode * lhs, ExpressionNode * rhs) 
	: BinaryOperatorNode(lhs,rhs){
}

int ExpNode::Evaluate() {
	int retval = pow(mLhs->Evaluate(), mRhs->Evaluate());
	return retval;
}

void ExpNode::CodeEvaluate(InstructionsClass& machineCode) {
	void;
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

void DivideNode::CodeEvaluate(InstructionsClass& machineCode) {
	mLhs->CodeEvaluate(machineCode);
	mRhs->CodeEvaluate(machineCode);
	machineCode.PopPopDivPush();
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

void LessNode::CodeEvaluate(InstructionsClass& machineCode) {
	mLhs->CodeEvaluate(machineCode);
	mRhs->CodeEvaluate(machineCode);
	machineCode.PopPopLessPush();
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

void LessEqualNode::CodeEvaluate(InstructionsClass& machineCode) {
	mLhs->CodeEvaluate(machineCode);
	mRhs->CodeEvaluate(machineCode);
	machineCode.PopPopLessEqualPush();
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

void GreaterNode::CodeEvaluate(InstructionsClass& machineCode) {
	mLhs->CodeEvaluate(machineCode);
	mRhs->CodeEvaluate(machineCode);
	machineCode.PopPopGreaterPush();
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

void GreaterEqualNode::CodeEvaluate(InstructionsClass& machineCode) {
	mLhs->CodeEvaluate(machineCode);
	mRhs->CodeEvaluate(machineCode);
	machineCode.PopPopGreaterEqualPush();
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

void EqualNode::CodeEvaluate(InstructionsClass& machineCode) {
	mLhs->CodeEvaluate(machineCode);
	mRhs->CodeEvaluate(machineCode);
	machineCode.PopPopEqualPush();
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

void NotEqualNode::CodeEvaluate(InstructionsClass& machineCode) {
	mLhs->CodeEvaluate(machineCode);
	mRhs->CodeEvaluate(machineCode);
	machineCode.PopPopNotEqualPush();
}

