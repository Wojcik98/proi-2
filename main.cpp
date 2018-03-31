#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>

#include "Converter.h"
#include "Variable.h"

using namespace std;

int main() {
    string equation;

    map<string, Variable*> vars;
    vars["ans"] = new Variable(&vars);
    vector <string> rpn;

    string varToAssign;

    while(getline(cin, equation)){
        try {
            pair<string, vector<string>> extracted = Converter(equation).toRPN();
            varToAssign = extracted.first;
            rpn = extracted.second;
            if(vars.find(varToAssign)==vars.end()){
                vars[varToAssign] = new Variable(&vars);
            }
            vars[varToAssign]->setExpression(rpn);
            double value = vars[varToAssign]->value();
            cout << varToAssign << " = " << value << endl;
        }
        catch (const string &e) {
            cout << e << endl;
        }
    }

    for(auto it: vars){
        delete it.second;
    }

    return 0;
}
