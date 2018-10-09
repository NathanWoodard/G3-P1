#include "evaluator.h"
#include <string>
#include <iostream>

using namespace std;

Evaluator::Evaluator(void) {
    
}

int Evaluator::evaluate(string & rawExpression) {
    return 0;
}
bool Evaluator::isOperator(char token)
{
	
	const char operatorTokens[] = "(){}[]!+-^*/%><=&|";
	const int OPERATOR_TOKEN_COUNT = strlen(operatorTokens);
	for(int i = 0; i < OPERATOR_TOKEN_COUNT; i++) {
		if(token == operatorTokens[i])
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
				if (current_char == '-' && isdigit(expression[i + 1])) //checks for negative numbers and adds them to expression as a number that is negative
				{
					++i;
					current_char = expression[i];
					while (isdigit(current_char))
					{
						spaced_expression += current_char;
						++i;
						current_char = expression[i];
					}
					--i;
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
	string precedence[9] = { "( { [ ] } ) ","! ++ -- ", "^ ", "* / % ", "+ - ", "> >= < <= ", "== != ", "&& ", "|| " }; //array of precedences
	op1 += " "; //spaces added to differentiate between operators such as ++ and +
	op2 += " ";
	int op1_prec;
	int op2_prec;
	for (op1_prec = 0; op1_prec < 9; ++op1_prec) //if the string is in the element it breaks with that being the precedence
	{
		if (precedence[op1_prec].find(op1) != string::npos)
			break;
	}
	for (op2_prec = 0; op2_prec < 9; ++op2_prec)
	{
		if (precedence[op2_prec].find(op2) != string::npos)
			break;
	}
	if (op2_prec < op1_prec) //the lower the number the higher the precedence
		return false;
	return true;
}
void Evaluator::parser(string expression) {
	istringstream tokens(expression);
	char next_char;

	while (tokens >> next_char) {					//Token took out char
		if (isdigit(next_char)) {				//Test is the char is digit
			tokens.putback(next_char);			//Token put back char
			//stack funtion
		}
		else if (isOperator(next_char)) {			//Test char if is operator... Need to create "is_operator"funtion
		// code for compare the operator and decided to throw in stuck or not
		}
		else {
			throw std::logic_error("Invalid charator error");   //if char is not digit or operator that allowed. 
		}
	}

}
