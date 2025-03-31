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
};

class StatementNode : public ASTNode {
	
};

class ProgramNode : public ASTNode {

};

class BinaryOpNode : public ASTNode {
private:
	char op;
public:
	ASTNode* leftNode;
	ASTNode* rightNode;
	BinaryOpNode(char op, ASTNode* leftNode, ASTNode* rightNode) : op(op), leftNode(leftNode), rightNode(rightNode)
	{

	}
};

#endif