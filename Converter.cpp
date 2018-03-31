//
// Created by Wojcik98 on 28.03.18.
//

#include "Converter.h"
#include "Math.h"
#include <stack>

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
    stack <string> stos;
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
                throw string("Invalid number format!");
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
            if(Math::isFunction(tmp)){
                stos.push(tmp);
            }
            else {
                rpn.push_back(tmp);
            }
            i--;
            continue;
        }
        if(infix[i]=='!'){
            rpn.push_back("!");
        }
        if(Math::isOperator(infix[i])){
            while(!stos.empty() && Math::operatorPrio(stos.top())>=Math::operatorPrio(infix.substr(i, 1))){
                string tmp = stos.top();
                rpn.push_back(tmp);
                stos.pop();
            }
            stos.push(infix.substr(i, 1));
        }
        if(infix[i]=='('){
            i++;
            rpnStep(i);
        }
        else if(infix[i]==')'){
            while(!stos.empty()){
                string tmp = stos.top();
                rpn.push_back(tmp);
                stos.pop();
            }
            return;
        }
    }
    while(!stos.empty()){
        string tmp = stos.top();
        rpn.push_back(tmp);
        stos.pop();
    }
}

void Converter::validate() {
    int nested = 0;
    char prev = infix[0];

    if(infix[0]=='!')
        throw string("Operators error!");

    for(char a: infix){
        if(a == '(')
            nested++;
        if(a == ')')
            nested--;
        if(nested < 0)
            throw string("Bad brackets nesting!");
        if(Math::isOperator(a) && Math::isOperator(prev))   //todo check order for factorial
            throw string("Operators error!");

        prev = a;
    }

    if(nested != 0)
        throw string("Bad brackets nesting!");
}
