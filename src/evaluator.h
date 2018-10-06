#ifndef EVALUATOR_H
#define EVALUATOR_H
#include <string>
#include <sstream>
#include <cctype>

using std::istringstream;
using std::isdigit;
using std::string;
class Evaluator {
    private:
        bool isOperator(char c);
        bool precedenceCompare(string op1, string op2);
        string addSpaces(string expresion);
    public:
        Evaluator(void);
        int evaluate(string & rawExpression);
        void parser(string expresion);

};
#endif
