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

bool Math::isOperator(char a) {
    return (a=='*' || a=='/' || a=='+' || a=='-' || a=='^' || a=='!');
}

bool Math::isFunction(string a) {
    return (a=="ln" || a=="log" || a=="exp");
}

double Math::factorial(double a) {
    double result = 1.;
    for(int i=1;i<=a;i++) {
        result *= i;
    }

    return result;
}

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

double Math::function(string fun, double x) {
    return funcs[fun](x);
}


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