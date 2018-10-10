#ifndef EXPRESSION_OPERATOR_H
#define EXPRESSION_OPERATOR_H
#include <string>
using std::string;

class ExpressionOperator {
private:
	int precedence;
	string operatorCharacter;
	
public:
	static bool isOperator(char _operator);
	static bool isBinary(string _other);
	static int getPrecedence(string & _operator);
	static bool comparePrecedence(string & operator1, string & operator2);
	static int evaluate(string op, int op1, int op2 = 0);
};

#endif