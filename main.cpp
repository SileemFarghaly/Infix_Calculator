/*
	Sileem Farghaly
	20 April 2012
	Project 5
	farghaly5.cpp
*/
#include <iostream>
#include <string>
#include <queue>
#include "notations.h"
using namespace std;

int main() {
	// User input for the expression
	string expression;
	cout << "Enter an Expression: ";
	getline(cin,expression);

	// Initialize the queue
	queue<string> infix;
	processExpr(expression,infix);

	// Translate to postfix
	queue<string> postfix;
	infixToPostfix(infix,postfix);

	// Evaluate postfix
	cout << "The result is: " << evaluatePostfix(postfix) << '\n';

	return 0;
}
