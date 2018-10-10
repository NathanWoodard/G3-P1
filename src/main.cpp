#include <iostream>
#include "./evaluator.h"

using std::cout;
using std::endl;
using std::cin;
int main() {
    Evaluator e;
	string test = "(++----5)^0";
	// cout << e.addSpaces(test) << endl;
	cout << e.parser(test) << endl;
	
    // this stops code execution for
    char c;
    cin >> c;
}