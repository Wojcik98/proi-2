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
    Variable(map<string, Variable *> *vars);

    void setExpression(vector<string> exp);
    double value();
private:
    bool isUsed;
    vector <string> expression;
    map <string, Variable*> *vars;
};


#endif //INC_2PRJ_VARIABLE_H
