//
// Created by Wojcik98 on 28.03.18.
//

#ifndef INC_2PRJ_VARIABLE_H
#define INC_2PRJ_VARIABLE_H

#include <string>
#include <map>
#include <vector>

using namespace std;

class Variable {
public:
    Variable(string name, map <string, Variable*> *vars);

    void setExp(vector <string> exp);
    double value();
private:
    typedef double (*ScriptFunction)(double);

    vector <string> expression;
    map <string, Variable*> *vars;
    map <string, ScriptFunction> funcs;
    string name;
};


#endif //INC_2PRJ_VARIABLE_H
