//
// Created by Wojcik98 on 28.03.18.
//

#include "Variable.h"
#include <cmath>
#include <stack>

using namespace std;

Variable::Variable(string name, map <string, Variable*> *vars) {
    this->name = name;
    funcs["ln"] = &log;
    funcs["log"] = &log10;
    funcs["exp"] = &exp;
    this->vars = vars;
}

void Variable::setExp(vector <string> exp) {
    this->expression = exp;
}

double Variable::value() {
    stack <string> stos;

    for(const string &a: expression){

    }

    return 0.0;
}
