#ifndef AXION_AST_HPP
#define AXION_AST_HPP

#include <string>
#include <vector>
#include <memory>
#include <any>
#include <iostream>

#include "lexeme.hpp"

using namespace std;

class ASTNode {
public:
	virtual ~ASTNode() = default;
	virtual void accept(class Visitor& visitor) = 0;
	virtual any eval() = 0;
};

class StatementNode : public ASTNode {
	
};

class ProgramNode : public ASTNode {

};

class AdditionNode : public ASTNode {
private:
	char op;
	ASTNode *leftChild;
	ASTNode *rightChild;
public:
	AdditionNode(char o, ASTNode* leftChild, ASTNode* rightChild) : op(o), leftChild(leftChild), rightChild(rightChild) {

	}

};

class MutliplicationNode : public ASTNode {
private:
	char op;
	ASTNode* leftChild;
	ASTNode* rightChild;
public:
	MutliplicationNode(char o, ASTNode* leftChild, ASTNode* rightChild) : op(o), leftChild(leftChild), rightChild(rightChild) {

	}
};

#endif