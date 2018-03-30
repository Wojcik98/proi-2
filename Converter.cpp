//
// Created by Wojcik98 on 28.03.18.
//

#include "Converter.h"
#include <stack>
#include <stdexcept>

Converter::Converter(string infix) {
    this->infix = infix;
    validate();
}

vector<string> Converter::toRPN() {
    rpn.clear();
    int i=0;
    rpnStep(i);

    return rpn;
}

void Converter::rpnStep(int &i) {
    stack <char> stos;
    for(;i<infix.size();i++){
        if(isdigit(infix[i])){
            string tmp = "";
            while(isdigit(infix[i]) || infix[i]=='.'){
                tmp += infix[i];
                i++;
            }
            try {   //check if valid double value
                stod(tmp);
            }
            catch (invalid_argument &e) {
                throw "Invalid number format!";
            }

            rpn.push_back(tmp);
            i--;
            continue;
        }
        if(isalpha(infix[i])){
            string tmp = "";
            while(isalpha(infix[i])){
                tmp += infix[i];
                i++;
            }
            rpn.push_back(tmp);
            i--;
            continue;
        }
        if(infix[i]=='!'){
            rpn.push_back("!");
        }
        if(isOperator(infix[i])){
            while(!stos.empty() && operatorPrio(stos.top())>=operatorPrio(infix[i])){
                string tmp = " ";
                tmp[0] = stos.top();
                rpn.push_back(tmp);
                stos.pop();
            }
            stos.push(infix[i]);
        }
        if(infix[i]=='('){
            i++;
            rpnStep(i);
        }
        else if(infix[i]==')'){
            while(!stos.empty()){
                string tmp = " ";
                tmp[0] = stos.top();
                rpn.push_back(tmp);
                stos.pop();
            }
            return;
        }
    }
    while(!stos.empty()){
        string tmp = " ";
        tmp[0] = stos.top();
        rpn.push_back(tmp);
        stos.pop();
    }
}

int Converter::operatorPrio(char a) {
    switch(a){
        case '^':
            return 3;
        case '*':
            return 2;
        case '/':
            return 2;
        case '+':
            return 1;
        case '-':
            return 1;
        case '(':
            return 0;
        default:
            return -1;
    }
}

void Converter::validate() {
    int nested = 0;
    char prev = infix[0];

    if(infix[0]=='!')
        throw "Operators error!";

    for(char a: infix){
        if(a == '(')
            nested++;
        if(a == ')')
            nested--;
        if(nested < 0)
            throw "Bad brackets nesting!";
        if(isOperator(a) && isOperator(prev))
            throw "Operators error!";

        prev = a;
    }

    if(nested != 0)
        throw "Bad brackets nesting!";
}

bool Converter::isOperator(char a) {
    return (a=='*' || a=='/' || a=='+' || a=='-' || a=='^');
}

