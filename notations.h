/*
	Sileem Farghaly
	20 April 2012
	Project 5
	notations.h
*/
#ifndef NOTATIONS_H
#define NOTATIONS_H
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <cctype>
#include <cmath>
#include <stdlib.h>
using namespace std;

void processExpr(string expr, queue<string>& infix);
void infixToPostfix(queue<string>& infix, queue<string>& postfix);		// infix is kept as a reference parameter because we don't care what happens to it. Save space
double evaluatePostfix(queue<string>& postfix);							// See above
bool isoperator(char input);
int priority(char ch);

#endif