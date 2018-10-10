
#include <string>
#include "ExpressionOperator.h"

const char * OPERATOR_TOKENS = "({[]})!+-_^*/%><=&|"; //REMOVED PARENTHESES
const string BINARY_OPERATOR_TOKENS[] = { "+",  "-", "/" , "*", "^", "<", "<=", ">", ">=" "==", "!=" , "&&", "||" };

const size_t BINARY_OPERATOR_COUNT = 12;
const int OPERATOR_TOKEN_COUNT = strlen(OPERATOR_TOKENS);

bool ExpressionOperator::isOperator(char _operator)
{
	
	
	for (int i = 0; i < OPERATOR_TOKEN_COUNT; i++) {
		if (_operator == OPERATOR_TOKENS[i])
			return true;
	}
	return false;
}

bool ExpressionOperator::isBinary(string _operator)
{

	for (size_t i = 0; i < BINARY_OPERATOR_COUNT; i++) {
		if (_operator == BINARY_OPERATOR_TOKENS[i])
			return true;
	}
	return false;
}

int ExpressionOperator::getPrecedence(string & _operator) {
	string operator1 = " " + _operator + " "; //spaces added to differentiate between operators such as ++ and +
	string precedence[9] = { " ! ++ -- _ ", " ^ ", " * / % ", " + - ", " > >= < <= ", " == != ", "&& ", " || " }; //array of precedences
	int operator_precedence;
	for (operator_precedence = 0; operator_precedence < 9; ++operator_precedence) //if the string is in the element it breaks with that being the precedence
	{
		if (precedence[operator_precedence].find(operator1) != string::npos)
			break;
	}
	return operator_precedence;
}

bool ExpressionOperator::comparePrecedence(string & operator1, string & operator2) {
	int operator1_prec = ExpressionOperator::getPrecedence(operator1);
	int operator2_prec = ExpressionOperator::getPrecedence(operator2);
	if (operator1_prec < operator2_prec) //the lower the number the higher the precedence
		return false;
	return true;
}

int ExpressionOperator::evaluate(string op, int op1, int op2) {
	if (op == "+")
		return op1 + op2;
	else if (op == "-")
		return op1 - op2;
	else if (op == "*")
		return op1 * op2;
	else if (op == "/")
		return op1 / op2;
	else if (op == "^")
		return pow(op1, op2);
	else if (op == "<")
		return op1 < op2;
	else if (op == "<=")
		return op1 <= op2;
	else if (op == ">")
		return op1 > op2;
	else if (op == ">=")
		return op1 >= op2;
	else if (op == "==")
		return op1 == op2;
	else if (op == "!=")
		return op1 != op2;
	else if (op == "&&")
		return op1 && op2;
	else if (op == "||")
		return op1 || op2;
	else if (op == "!")
		return !op1;
	else if (op == "++")
		return ++op1;
	else if (op == "--")
		return --op1;
	else if (op == "%")
		return op1 % op2;
	else if (op == "_")
		return -1 * op1;
	return 0;
}