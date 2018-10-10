#include "evaluator.h"
#include "ExpressionOperator.h"
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

		if (ExpressionOperator::isOperator(current_char)) //GETTING THE FULL OPERATOR
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

int Evaluator::evaluate(string expression) {
	expression = addSpaces(expression); //formats the expression properly with operators spaced
	istringstream tokens(expression);
	char next_char;
	string op;
	int value;

	while (tokens >> next_char) { //read in values until you cant anymore
		if (isdigit(next_char)) {													//NUMBER
			tokens.putback(next_char);
			tokens >> value;
			operand_stack.push(value);
		}
		else if (next_char == '(' || next_char == '{' || next_char == '[')			//OPEN PARENTHESES
		{
			tokens.putback(next_char);
			tokens >> op;
			operator_stack.push(op);
		}

		else if (next_char == ')' || next_char == '}' || next_char == ']')			//CLOSE PARENTHESES
		{
			if (operator_stack.empty())
			{
				cout << "Error: Close Parentheses without matching open parentheses\n";
				return 0;
			}
			while (operator_stack.top() != "(" && operator_stack.top() != "{" && operator_stack.top() != "[") //does all operations till it reaches an open parentheses
			{
				if (ExpressionOperator::isBinary(op))
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
					operand_stack.push(ExpressionOperator::evaluate(operator_stack.top(), oper1, oper2));
				}
				else
				{
					int oper1;
					oper1 = operand_stack.top();
					operand_stack.pop();
					operand_stack.push(ExpressionOperator::evaluate(operator_stack.top(), oper1));
				}
				operator_stack.pop();
			}
			operator_stack.pop();
		}
		else if (ExpressionOperator::isOperator(next_char))							//OPERATORS
		{
			tokens.putback(next_char);
			tokens >> op;
			while (!operator_stack.empty() && ExpressionOperator::comparePrecedence(operator_stack.top(), op)) //while the top has a higher precedence than op
			{
				if (ExpressionOperator::isBinary(operator_stack.top())) //binary operations
				{
					int oper1;
					int oper2;
					oper2 = operand_stack.top();
					operand_stack.pop();
					oper1 = operand_stack.top();
					operand_stack.pop();
					if (oper2 == 0 && op == "/") //checks for arithmetic errors
					{
						cout << "Error: Cannot divide by zero\n";
						return 0;
					}
					operand_stack.push(ExpressionOperator::evaluate(operator_stack.top(), oper1, oper2));
					operator_stack.pop();
				}
				else //does all unary operations before moving onto the binary one
				{
					int oper1;
					if (ExpressionOperator::isBinary(op)) {
						while (!operator_stack.empty() && ExpressionOperator::comparePrecedence(operator_stack.top(), op))
						{
							oper1 = operand_stack.top();
							operand_stack.pop();
							operand_stack.push(ExpressionOperator::evaluate(operator_stack.top(), oper1));
							operator_stack.pop();
						}
					}
					break;
				}
			}
			operator_stack.push(op);
		}

	}
	while (!operator_stack.empty()) //once all values are read do operations until none left
	{

		if (ExpressionOperator::isBinary(op)) //binary operations
		{
			int oper1;
			int oper2;
			oper2 = operand_stack.top();
			operand_stack.pop();
			if (operand_stack.empty()) //checks if the stack is empty and if it is puts out an error
			{
				cout << "Error: Binary operator without two operands\n";
				return 0;
			}
			oper1 = operand_stack.top();
			operand_stack.pop();
			if (oper2 == 0 && op == "/") //divide by zero error check
			{
				cout << "Error: Cannot divide by zero\n";
				return 0;
			}
			operand_stack.push(ExpressionOperator::evaluate(operator_stack.top(), oper1, oper2));
		}
		else //unary operations
		{
			int oper1;
			oper1 = operand_stack.top();
			operand_stack.pop();
			operand_stack.push(ExpressionOperator::evaluate(operator_stack.top(), oper1));
		}
		operator_stack.pop();
	}
	if (operand_stack.size() != 1) //checks if there are more values in operand_stack than just the final value
	{
		cout << "Error: Two operands in a row\n";
		return 0;
	}
	return operand_stack.top(); //returns the final value

}
