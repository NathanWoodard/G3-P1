#include "evaluator.h"
#include <string>
#include <sstream>
#include <cctype>
#include <stack>
#include <cmath>
#include <iostream>

using std::istringstream;
using std::isdigit;
using std::string;
using std::stack;
using std::cout;

Evaluator::Evaluator(void) {

}

int Evaluator::evaluate(string op, int op1, int op2) {
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
bool Evaluator::isOperator(char token)
{

	const char operatorTokens[] = "({[]})!+-_^*/%><=&|"; //REMOVED PARENTHESES
	const int OPERATOR_TOKEN_COUNT = strlen(operatorTokens);
	for (int i = 0; i < OPERATOR_TOKEN_COUNT; i++) {
		if (token == operatorTokens[i])
			return true;
	}
	return false;
}
string Evaluator::addSpaces(string expression)
{
	char current_char;
	string spaced_expression = "";
	string previous_type = "None";
	for (unsigned int i = 0; i < expression.length(); ++i) //iterate over entire string
	{
		current_char = expression[i];
		if (isdigit(current_char)) //GETTING THE FULL NUMBER
		{
			while (isdigit(current_char))
			{
				spaced_expression += current_char;
				++i;
				current_char = expression[i];
			}
			previous_type = "Number";
			spaced_expression += " ";
		}
		if (isOperator(current_char)) //GETTING THE FULL OPERATOR
		{
			spaced_expression += current_char;
			if (current_char == expression[i + 1] && (current_char == '&' || current_char == '|'))
			{
				spaced_expression += expression[i + 1];
				++i;
			}
			if (previous_type != "Number") //checks for cases where there are multiple - or +
			{
				if (current_char == expression[i + 1] && (current_char == '+' || current_char == '-')) //creates proper increment and decrement
				{
					spaced_expression += expression[i + 1];
					++i;
				}
				else if (current_char == '-' && isdigit(expression[i + 1])) //replaces the - for a negative with a _
				{
					spaced_expression = spaced_expression.substr(0, spaced_expression.length() - 1);
					spaced_expression += "_";
				}
			}
			if ((current_char == '>' || current_char == '<' || current_char == '=' || current_char == '!') && expression[i + 1] == '=') //comparison operators
			{
				spaced_expression += expression[i + 1];
				++i;

			}
			if (isdigit(spaced_expression[spaced_expression.length() - 1])) //sets the previous type for use in conditional above
				previous_type = "Number";
			else
				previous_type = "Operator";
		}
		spaced_expression += " "; //adds spaces to properly read as tokens
	}
	return spaced_expression;
}
bool Evaluator::precedenceCompare(string op1, string op2) // returns false if the op2 has higher precedence and true otherwise
{
	string operator1 = " " + op1 + " "; //spaces added to differentiate between operators such as ++ and +
	string operator2 = " " + op2 + " ";
	string precedence[9] = { " ! ++ -- _ ", " ^ ", " * / % ", " + - ", " > >= < <= ", " == != ", "&& ", " || " }; //array of precedences
	int op1_prec;
	int op2_prec;
	for (op1_prec = 0; op1_prec < 9; ++op1_prec) //if the string is in the element it breaks with that being the precedence
	{
		if (precedence[op1_prec].find(operator1) != string::npos)
			break;
	}
	for (op2_prec = 0; op2_prec < 9; ++op2_prec)
	{
		if (precedence[op2_prec].find(operator2) != string::npos)
			break;
	}
	if (op2_prec < op1_prec) //the lower the number the higher the precedence
		return false;
	return true;
}
int Evaluator::parser(string expression) {
	expression = addSpaces(expression);
	istringstream tokens(expression);
	string binary_op = " + - / * ^ < <= > >= == != && || ";
	char next_char;
	string op;
	int value;

	while (tokens >> next_char) {
		if (isdigit(next_char)) {
			tokens.putback(next_char);
			tokens >> value;
			operand_stack.push(value);
		}
		else if (next_char == '(' || next_char == '{' || next_char == '[')
		{
			tokens.putback(next_char);
			tokens >> op;
			operator_stack.push(op);
		}

		else if (next_char == ')' || next_char == '}' || next_char == ']')
		{
			if (operator_stack.empty())
			{
				cout << "Error: Close Parentheses without matching open parentheses\n";
				return 0;
			}
			while (operator_stack.top() != "(" && operator_stack.top() != "{" && operator_stack.top() != "[")
			{
				if (binary_op.find(" " + op + " ") != string::npos)
				{
					int oper1;
					int oper2;
					oper2 = operand_stack.top();
					operand_stack.pop();
					oper1 = operand_stack.top();
					operand_stack.pop();
					if (oper2 == 0 && op == "/")
					{
						cout << "Error: Cannot divide by zero\n";
						return 0;
					}
					operand_stack.push(evaluate(operator_stack.top(), oper1, oper2));
				}
				else
				{
					int oper1;
					oper1 = operand_stack.top();
					operand_stack.pop();
					operand_stack.push(evaluate(operator_stack.top(), oper1));
				}
				operator_stack.pop();
			}
			operator_stack.pop();
		}
		else if (isOperator(next_char))
		{
			tokens.putback(next_char);
			tokens >> op;
			while (!operator_stack.empty() && precedenceCompare(operator_stack.top(), op))
			{
				if (binary_op.find(" " + operator_stack.top() + " ") != string::npos)
				{
					int oper1;
					int oper2;
					oper2 = operand_stack.top();
					operand_stack.pop();
					oper1 = operand_stack.top();
					operand_stack.pop();
					if (oper2 == 0 && op == "/")
					{
						cout << "Error: Cannot divide by zero\n";
						return 0;
					}
					operand_stack.push(evaluate(operator_stack.top(), oper1, oper2));
					operator_stack.pop();
				}
				else
				{
					int oper1;
					while (!operator_stack.empty() && precedenceCompare(operator_stack.top(), op) && binary_op.find(" " + op + " ") != string::npos && binary_op.find(" "+operator_stack.top()+" ") == string::npos)
					{
						oper1 = operand_stack.top();
						operand_stack.pop();
						operand_stack.push(evaluate(operator_stack.top(), oper1));
						operator_stack.pop();
					}
					break;
				}
			}
			operator_stack.push(op);
		}
		else
		{
			cout << "Error: Invalid character\n";
			return 0;
		}

	}
	while (!operator_stack.empty())
	{

		if (binary_op.find(" " + operator_stack.top() + " ") != string::npos)
		{
			int oper1;
			int oper2;
			oper2 = operand_stack.top();
			operand_stack.pop();
			if (operand_stack.empty())
			{
				cout << "Error: Binary operator without two operands\n";
				return 0;
			}
			oper1 = operand_stack.top();
			operand_stack.pop();
			if (oper2 == 0 && operator_stack.top() == "/")
			{
				cout << "Error: Cannot divide by zero\n";
				return 0;
			}
			operand_stack.push(evaluate(operator_stack.top(), oper1, oper2));
		}
		else
		{
			int oper1;
			oper1 = operand_stack.top();
			operand_stack.pop();
			operand_stack.push(evaluate(operator_stack.top(), oper1));
		}
		operator_stack.pop();
	}
	if (operand_stack.size() != 1)
	{
		cout << "Error: Two operands in a row\n";
		return 0;
	}
	return operand_stack.top();

}
