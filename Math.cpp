//
// Created by Wojcik98 on 30.03.18.
//

#include <cmath>
#include "Math.h"

map<string, Math::ScriptFunction> Math::funcs = {
        {"ln", &log},
        {"log", &log10},
        {"exp", &exp}
};

/**
 * @brief Math::isOperator
 * @param a
 * @return true if a is math operator
 */
bool Math::isOperator(char a) {
    return (a=='*' || a=='/' || a=='+' || a=='-' || a=='^' || a=='!');
}

/**
 * @brief Math::isFunction
 * @param a
 * @return true if a is function
 */
bool Math::isFunction(string a) {
    return (a=="ln" || a=="log" || a=="exp");
}

/**
 * @brief Math::factorial
 * @param a
 * @return a factorial defined for integers
 */
double Math::factorial(double a) {
    double result = 1.;
    for(int i=1;i<=a;i++) {
        result *= i;
    }

    return result;
}

/**
 * @brief Math::operation
 * @param x
 * @param y
 * @param op
 * @return value of x op y
 * Computes x op y, e.g. for x=2,y=3,op=^ it returns 2^3.
 */
double Math::operation(double x, double y, string op) {
    if(op=="+"){
        return x+y;
    }
    else if(op=="-"){
        return x-y;
    }
    else if(op=="*"){
        return x*y;
    }
    else if(op=="/"){
        return x/y;
    }
    else if(op=="^"){
        return pow(x, y);
    }
    return 0.;
}

/**
 * @brief Math::function
 * @param fun function to use
 * @param x parameter to use in function
 * @return value of function fun with parameter x
 * Computes fun(x), e.g. for fun=log,x=10 it returns log(10).
 */
double Math::function(string fun, double x) {
    return funcs[fun](x);
}

/**
 * @brief Math::operatorPrio
 * @param a operator or function that we want to know priority of
 * @return priority of a
 * Returns prority of a to compare them, e.g. * has higher priority than +
 */
int Math::operatorPrio(string a) {
    if(Math::isFunction(a) || a=="!"){
        return 4;
    }
    else if(a=="^"){
        return 3;
    }
    else if(a=="*" || a=="/"){
        return 2;
    }
    else if(a=="+" || a=="-"){
        return 1;
    }
    else{
        return -1;
    }
}