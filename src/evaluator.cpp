#include "evaluator.h"
#include <string>
#include <sstream>
#include <cctype>
#include <stack>
#include <cmath>

using std::istringstream;
using std::isdigit;
using std::string;
using std::stack;

Evaluator::Evaluator(void) {

}

int Evaluator::evaluate(string op,int op1, int op2) {
	if (op == "+")
		return op1 + op2;
	else if (op == "-")
		return op1 - op2;
	else if (op == "*")
		return op1 * op2;
	else if (op == "/")
		return op1 / op2;
	else if (op == "^")
		return int(pow(op1, op2));
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

	const char operatorTokens[] = "!+-_^*/%><=&|"; //REMOVED PARENTHESES
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
	for (unsigned int i = 0;i < expression.length();++i) //iterate over entire string
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
				if (current_char == '-' && isdigit(expression[i + 1]))
				{
					spaced_expression = spaced_expression.substr(0, spaced_expression.length() - 1);
					spaced_expression += "_";
				}
				//checks for negative numbers and adds them to expression as a number that is negative
				/*{
					++i;
					current_char = expression[i];
					while (isdigit(current_char))
					{
						spaced_expression += current_char;
						++i;
						current_char = expression[i];
					}
					--i;
				}*/
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
/* TWO WAYS TO MAKE POSTFIX:: REVERSE IN PLACE FACTORING IN MINUS, OR REVERSE AFTER SPACED SO MINUS IS IRRELEVANT*/
bool Evaluator::precedenceCompare(string op1, string op2) // returns false if the op2 has higher precedence and true otherwise
{
	string operator1 = " " + op1 + " "; //spaces added to differentiate between operators such as ++ and +
	string operator2 = " " + op2 + " ";
	string precedence[9] = {" ! ++ -- _ ", " ^ ", " * / % ", " + - ", " > >= < <= ", " == != ", "&& ", " || " }; //array of precedences
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
	istringstream tokens(expression);
	string binary_op = " + - / * ^ < <= > >= == != && || ";
	char next_char;
	string op;
	int value;

	while (tokens >> next_char) {
		if (isdigit(next_char)) {
			tokens.putback(next_char); //next_next_char is used to check if there is a minus operator since it is put together with this number
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
					operand_stack.push(evaluate(op, oper1, oper2));
				}
				else
				{
					int oper1;
					oper1 = operand_stack.top();
					operand_stack.pop();
					operand_stack.push(evaluate(op, oper1));
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
					operand_stack.push(evaluate(operator_stack.top(), oper1, oper2));
					operator_stack.pop();
				}
				else
				{
					/*tokens >> next_char;
					while (!isdigit(next_char))
					{
						tokens.putback(next_char);
						tokens >> op;
						operator_stack.push(op);
						tokens >> next_char;
					}
					tokens.putback(next_char);
					int oper1;
					tokens >> oper1;
					operand_stack.push(oper1);*/
					int oper1;
					while (!operator_stack.empty() && precedenceCompare(operator_stack.top(), op) && binary_op.find(" " +op+ " ") != string::npos)
					{
						oper1 = operand_stack.top();
						operand_stack.pop();
						operand_stack.push(evaluate(operator_stack.top(), oper1));
						operator_stack.pop();																//READS IN WRONG CHARACTER
					}
					break;
				}
			}
			operator_stack.push(op);
		}
	
	}
	while (!operator_stack.empty())
	{
		
		if (binary_op.find(" " +operator_stack.top()+ " ") != string::npos)
		{
			int oper1;
			int oper2;
			oper2 = operand_stack.top();
			operand_stack.pop();
			oper1 = operand_stack.top();
			operand_stack.pop();
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
	return operand_stack.top();

}
