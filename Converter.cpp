//
// Created by Wojcik98 on 28.03.18.
//

#include "Converter.h"
#include "Math.h"
#include <stack>
#include <algorithm>

Converter::Converter(string infix) {
    this->infix = infix;
    clean();
    validate();
}

pair<string, vector<string>> Converter::toRPN() {
    rpn.clear();
    int i=0;
    rpnStep(i);

    return make_pair(varToAssign, rpn);
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
        /*if(infix[i]=='!'){
            rpn.push_back("!");
        }*/
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

void Converter::clean() {
    infix.erase(
            remove(infix.begin(), infix.end(), ' '),
            infix.end()
    );

    size_t eqPos = infix.find('=');
    size_t nonAlphaPos = infix.find_first_not_of("abcdefghijklmnopqrstuvwxyz");
    size_t nextEqPos = infix.find('=', eqPos+1);
    if(eqPos!=string::npos){    //then nonAlphaPos is also not npos
        if(eqPos==nonAlphaPos && nextEqPos==string::npos) {
            varToAssign = infix.substr(0, eqPos);
            infix.erase(0, eqPos+1);
        }
        else{
            throw string("Invalid assignment!");
        }
    }
    else{
        varToAssign = "ans";
    }
}

void Converter::validate() {
    if(infix.empty()){
        throw string("Empty line!");
    }

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
