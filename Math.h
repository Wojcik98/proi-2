//
// Created by Wojcik98 on 30.03.18.
//

#ifndef INC_2PRJ_MATH_H
#define INC_2PRJ_MATH_H

#include <string>
#include <map>

using namespace std;

class Math {
public:
    static bool isOperator(char a);
    static bool isFunction(string a);
    static double factorial(double a);
    static double operation(double x, double y, string op);
    static double function(string fun, double x);
    static int operatorPrio(string a);

private:
    typedef double (*ScriptFunction)(double);
    static map <string, ScriptFunction> funcs;
};


#endif //INC_2PRJ_MATH_H
