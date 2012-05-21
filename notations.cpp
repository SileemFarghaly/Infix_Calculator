/*
        Sileem Farghaly
        20 April 2012
        Project 5
        notations.cpp
 */
#include "notations.h"

void processExpr(string expr, queue<string>& infix) {
    // Handle an empty expression
    if (expr == "")
        return;

    string token;
    char ch;
    int len = expr.length();
    int i = 0;
    bool matchedParenthesis;

    // Variables used for...variables
    int alphaIdx;
    string val;
    string variables[26];
    for (int k = 0; k < 26; k++)
        variables[k] = '?';

    while (i < len) {
        ch = expr[i];

        if (isalpha(ch)) {
            if (i - 1 >= 0 && token[token.length() - 1] == '.') {
                // Checks the previous character to assure no variable decimals
                cout << "Syntax Error: Decimal before Variable\n";
                exit(-1);
            } else if (i + 1 < len && expr[i + 1] == '.') {
                cout << "Syntax Error: Decinal after variable\n";
                exit(-1);
            }
            ch = toupper(ch);
            alphaIdx = ch - 65;
            if (variables[alphaIdx] == "?") {
                cout << "Enter a value for " << ch << " : ";
                cin >> variables[alphaIdx];
                val = variables[alphaIdx];
                infix.push(val);
            } else {
                val = variables[alphaIdx];
                infix.push(val);
            }
            i++;

        } else if (isoperator(ch)) {
            if (i == 0) {
                cout << "Syntax Error: " << ch << '\n';
                exit(-1);
            } else if (isoperator(infix.back()[0])) {
                // Checks for too many operators
                cout << "Syntax Error: Multiple operators\n";
                exit(-1);
            }
            token = ch;
            infix.push(token);
            i++;
        } else if (ch == '(' || ch == ')') {
            token = ch;
            infix.push(token);
            i++;
            // Check for mismatched parenthesis
            if (ch == '(')
                matchedParenthesis = false;
            else if (ch == ')')
                matchedParenthesis = true;
        } else if (isdigit(ch) || ch == '.') {
            token = "";
            while (i < len && (isdigit(expr[i]) || expr[i] == '.')) {
                if (ch == '.' && token == "")
                    token += '0'; // amend a 0 to decimals
                token += ch;
                i++;
                if (i != len) // Prevent walking off the string
                    ch = expr[i];
            }
            if (ch == '.') {
                cout << "Syntax Error: Unfinished Decimal\n";
                exit(-1);
            }
            infix.push(token);
        } else if (isspace(ch))
            i++;
        else {
            cout << "Syntax Error: " << ch << '\n';
            exit(-1);
        }
        // Implicit Multiplication
	if (i < len && isalpha(expr[i]) && isdigit(expr[i-1]))
            infix.push("*");
    }

    // This needs to be worked out
    //  if (matchedParenthesis == false) {
    //		cout << "Syntax Error: Mismatched Parenthesis\n";
    //		exit(-1);
    //	}
    //	if(isoperator(ch)) {
    //		cout << "Syntax Error: Invalid Expression\n";
    //		exit(-1);
    //	}
}

void infixToPostfix(queue<string>& infix, queue<string>& postfix) {
    // Quit if empty
    if (infix.empty())
        return;

    string token;
    stack<string> operators;
    while (!infix.empty()) {
        token = infix.front();
        infix.pop();

        if (token == "(")
            operators.push(token);
        else if (isdigit(token[0]))
            postfix.push(token);
        else if (token == ")") {
            while (operators.top() != "(") {
                postfix.push(operators.top());
                operators.pop();
            }
            operators.pop();
        } else if (isoperator(token[0])) {
            if (operators.empty())
                operators.push(token);
            else if (priority(token[0]) > priority(operators.top()[0]))
                operators.push(token);
            else {
                do {
                    postfix.push(operators.top());
                    operators.pop();
                } while (!operators.empty() && priority(operators.top()[0]) >= priority(token[0]));
                operators.push(token);
            }
        }
    }
    while (!operators.empty()) {
        if (operators.top() == "(") {
            cout << "Error: Parenthesis\n";
            exit(-1);
        }
        postfix.push(operators.top());
        operators.pop();
    }
}

double evaluatePostfix(queue<string>& postfix) {
    // If no expression was entered, assume the result is 0
    if (postfix.empty())
        return 0;

    stack<double>results;
    double token, result;
    double val1, val2;

    while (!postfix.empty()) {
        if (isdigit(postfix.front()[0])) {
            token = atof(postfix.front().c_str());
            postfix.pop();
            results.push(token);
        } else if (isoperator(postfix.front()[0])) {
            // Switch the results
            val2 = results.top();
            results.pop();
            val1 = results.top();
            results.pop();

            // Determine the operator and evaluate
            if (postfix.front() == "+")
                result = val1 + val2;
            else if (postfix.front() == "-")
                result = val1 - val2;
            else if (postfix.front() == "*")
                result = val1 * val2;
            else if (postfix.front() == "/")
                result = val1 / val2;
            else if (postfix.front() == "^")
                result = pow(val1, val2);

            postfix.pop();
            results.push(result);
        }
    }
    result = results.top();

    return result;
}

bool isoperator(char input) {
    if (input == '+' || input == '-'
            || input == '*' || input == '/'
            || input == '^')
        return true;
    else
        return false;
}

int priority(char ch) {
    switch (ch) {
        case('('): return 0;
            break;
        case('+'):
        case('-'): return 1;
            break;
        case('*'):
        case('/'): return 2;
            break;
        case('^'): return 3;
            break;
        default: return 0;
            break;
    }
}