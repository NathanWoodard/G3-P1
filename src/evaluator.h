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
	int evaluate(string expresion);
private:
	stack <string> operator_stack;
	stack <int> operand_stack;
	string addSpaces(string expresion);
};
#endif
