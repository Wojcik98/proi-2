#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>

#include "Converter.h"
#include "Variable.h"

using namespace std;

int main() {
    string equation;

    map<string, Variable*> vars;
    vars["ans"] = new Variable("ans", &vars);
    vector <string> rpn;

    string varToAssign;

    while(getline(cin, equation)){
        try {
            equation.erase(
                    remove(equation.begin(), equation.end(), ' '),
                    equation.end()
            );

            size_t eqPos = equation.find('=');
            size_t nonAlphaPos = equation.find_first_not_of("abcdefghijklmnopqrstuvwxyz");
            if(eqPos!=string::npos){    //then nonAlphaPos is also not npos
                if(eqPos==nonAlphaPos) {
                    varToAssign = equation.substr(0, eqPos-1);
                    equation.erase(0, eqPos);
                }
                else{
                    throw "Invalid assignment!";
                }
            }
            else{
                varToAssign = "ans";
            }

            rpn = Converter(equation).toRPN();
            if(vars.find(varToAssign)==vars.end()){
                vars[varToAssign] = new Variable(varToAssign, &vars);
            }
            vars[varToAssign]->setExp(rpn);
            double value = vars[varToAssign]->value();
            cout << varToAssign << " = " << value << endl;
        }
        catch (const char *e) {
            cout << e << endl;
        }
    }

    return 0;
}
