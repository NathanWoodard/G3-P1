#ifndef EVALUATOR_H
#define EVALUATOR_H
#include <string>
#include <sstream>
#include <cctype>
#include <stack>
#include <cmath>

using std::istringstream;
using std::isdigit;
using std::string;
using std::stack;
class Evaluator {
public:
	Evaluator();
	int parser(string expresion);
private:
	stack <string> operator_stack;
	stack <int> operand_stack;
	bool isOperator(char c);
	bool precedenceCompare(string op1, string op2);
	string addSpaces(string expresion);
	int evaluate(string op, int op1, int op2 = 0);
};
#endif
