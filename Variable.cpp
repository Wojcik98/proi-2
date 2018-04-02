//
// Created by Wojcik98 on 28.03.18.
//

#include "Variable.h"
#include "Math.h"
#include <stack>

using namespace std;

/**
 * @brief Variable::Variable
 * @param vars available variables
 * Constructor.
 */
Variable::Variable(map<string, Variable *> *vars) {
    this->vars = vars;
    this->isUsed = false;
}

/**
 * @brief Variable::setExpression
 * @param exp expression to be set
 * Sets variable's expression to exp.
 */
void Variable::setExpression(vector<string> exp) {
    this->expression = exp;
}

/**
 * @brief Variable::value
 * @return evaluated value of variable
 * @throws exception if variable is used in its own expression (even if it's used indirectly in other variables)
 * @throws exception if unknown value is used (e.g. uninitialized variable)
 * Constructor
 */
double Variable::value() {
    stack <string> stos;
    if(isUsed){
        isUsed = false;
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
                try {
                    double tmp = (*vars)[a]->value();
                    stos.push(to_string(tmp));
                }
                catch (string &e) {
                    isUsed = false;
                    throw string(e);
                }
            }
            else{
                try{
                    double tmp = stod(a);       //check if it's number
                    stos.push(to_string(tmp));
                }
                catch (const invalid_argument &e){
                    isUsed = false;
                    throw string("Unknown value ") + a;
                }

            }
        }
    }

    isUsed = false;
    return stod(stos.top());
}
