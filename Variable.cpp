//
// Created by Wojcik98 on 28.03.18.
//

#include "Variable.h"
#include "Math.h"
#include <stack>
#include <iostream>

using namespace std;

Variable::Variable(map<string, Variable *> *vars) {
    this->vars = vars;
    this->isUsed = false;
}

void Variable::setExpression(vector<string> exp) {
    this->expression = exp;
}

double Variable::value() {
    stack <string> stos;
    if(isUsed){
        throw string("Error: self-referencing equation!");
    }
    else{
        isUsed = true;
    }

    for(const string &a: expression){
        if(Math::isOperator(a[0])) {
            if(a=="!"){
                double tmp = stod(stos.top());
                stos.pop();
                tmp = Math::factorial(tmp);
                stos.push(to_string(tmp));
            }
            else{
                double x, y, tmp;
                y = stod(stos.top());
                stos.pop();
                x = stod(stos.top());
                stos.pop();
                tmp = Math::operation(x, y, a);
                stos.push(to_string(tmp));
            }
        }
        else if(Math::isFunction(a)){
            double tmp = stod(stos.top());
            stos.pop();
            tmp = Math::function(a, tmp);
            stos.push(to_string(tmp));
        }
        else{
            if(vars->find(a)!=vars->end()){
                double tmp = (*vars)[a]->value();
                stos.push(to_string(tmp));
            }
            else{
                try{
                    double tmp = stod(a);       //check if it's number
                    stos.push(to_string(tmp));
                }
                catch (const invalid_argument &e){
                    throw string("Unknown value") + a;
                }

            }
        }
    }

    isUsed = false;
    return stod(stos.top());
}
