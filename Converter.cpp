//
// Created by Wojcik98 on 28.03.18.
//

#include "Converter.h"
#include "Math.h"
#include <stack>
#include <algorithm>

/**
 * @brief Converter::Converter
 * @param infix equation in infix form
 * Constructor.
 */
Converter::Converter(string infix) {
    this->infix = infix;
    clean();
    validate();
}

/**
 * @brief Converter::toRPN
 * @return pair of string with variable name and vector of strings with equation in RPN
 * Starts conversion of infix to reverse polish notation (RPN).
 */
pair<string, vector<string>> Converter::toRPN() {
    rpn.clear();
    unsigned int i=0;
    rpnStep(i);

    return make_pair(varToAssign, rpn);
}

/**
 * @brief Converter::rpnStep
 * @param i position in infix string
 * @throws exception if number can't be converted to double
 * Converts to RPN on current nesting level, if new bracket is found then recursively calls itself.
 */
void Converter::rpnStep(unsigned int &i) {
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

/**
 * @brief Converter::clean
 * @throws exception if variable is used in its own expression (even if it's used indirectly in other variables)
 * @throws exception if unknown value is used (e.g. uninitialized variable)
 * Cleans equation of spaces.
 */
void Converter::clean() {
    infix.erase(
            remove_if(infix.begin(), infix.end(), Converter::isInvalidChar),
            infix.end()
    );
}

/**
 * @brief Converter::validate
 * @throws exception if equation is empty
 * @throws exception if brackets nesting is invalid
 * @throws exception if operators order is invalid
 * @throws exception if assign signs are placed incorrectly (multiple signs or in the middle of equation)
 * Validates that infix equation is valid and checks variable name.
 */
void Converter::validate() {
    if(infix.empty()){
        throw string("Empty line!");
    }

    int nested = 0;
    char prev = infix[0];   //it will also check if first symbol is operator

    if(infix[0]=='!')
        throw string("Operators error!");

    for(char a: infix){
        if(a == '(')
            nested++;
        if(a == ')')
            nested--;
        if(nested < 0)
            throw string("Bad brackets nesting!");
        if(Math::isOperator(a) && Math::isOperator(prev) && prev != '!')
            throw string("Operators error!");

        prev = a;
    }

    if(Math::isOperator(infix[infix.size()-1]) && infix[infix.size()-1] != '!') {
        throw string("Operators error!");
    }

    if(nested != 0) {
        throw string("Bad brackets nesting!");
    }

    size_t eqPos = infix.find('=');
    size_t nonAlphaPos = infix.find_first_not_of("abcdefghijklmnopqrstuvwxyz");
    size_t nextEqPos = infix.find('=', eqPos+1);
    if(eqPos!=string::npos){    //then nonAlphaPos is also not npos
        if(eqPos==nonAlphaPos && nextEqPos==string::npos) {
            varToAssign = infix.substr(0, eqPos);
            infix.erase(0, eqPos+1);

            if(infix.empty()){  //assigned value must not be empty
                throw string("Empty assignment!");
            }
        }
        else{
            throw string("Invalid assignment!");
        }
    }
    else{
        varToAssign = "ans";
    }
}

bool Converter::isInvalidChar(char a) {
    return !(Math::isOperator(a) || isalnum(a) || a=='.' || a=='=' || a=='(' || a==')');
}
