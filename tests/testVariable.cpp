//
// Created by Wojcik98 on 01.04.18.
//

#include <vector>
#include <string>
#include <cassert>
#include <cmath>

#include "testVariable.h"
#include "../Variable.h"
#include "../Converter.h"

#define FEQUAL(a, b) (fabs((a)-(b))<0.0000001)

using namespace std;

void testVariable::testEvaluation() {
    map <string, Variable*> vars;
    vars["ans"] = new Variable(&vars);
    pair<string, vector <string>> tmp = Converter("2+4.5*9.7").toRPN();
    vars[tmp.first]->setExpression(tmp.second);
    assert(FEQUAL(vars[tmp.first]->value(), 45.65));

    vars["a"] = new Variable(&vars);
    pair<string, vector <string>> tmp2 = Converter("a=5^2*ln(1)+exp(0)").toRPN();
    vars[tmp2.first]->setExpression(tmp2.second);
    assert(FEQUAL(vars[tmp2.first]->value(), 1.));

    vars["b"] = new Variable(&vars);
    pair<string, vector <string>> tmp3 = Converter("b=a^3").toRPN();
    vars[tmp3.first]->setExpression(tmp3.second);
    assert(FEQUAL(vars[tmp3.first]->value(), 1.));

    pair<string, vector <string>> tmp4 = Converter("a=3").toRPN();
    vars[tmp4.first]->setExpression(tmp4.second);
    assert(FEQUAL(vars[tmp4.first]->value(), 3.));

    pair<string, vector <string>> tmp5 = Converter("b").toRPN();
    vars[tmp5.first]->setExpression(tmp5.second);
    assert(FEQUAL(vars[tmp5.first]->value(), 27.));
}

void testVariable::testUnknownVariable() {
    map <string, Variable*> vars;
    vars["ans"] = new Variable(&vars);
    pair<string, vector <string>> tmp = Converter("a*2").toRPN();
    vars[tmp.first]->setExpression(tmp.second);

    bool caught = false;
    try {
        vars[tmp.first]->value();
    }
    catch (const string &e) {
        caught = true;
    }
    assert(caught);
}

void testVariable::testSelfreferencing() {
    map <string, Variable*> vars;
    vars["ans"] = new Variable(&vars);
    vars["a"] = new Variable(&vars);
    vars["b"] = new Variable(&vars);
    pair<string, vector <string>> tmp = Converter("a=1").toRPN();
    vars[tmp.first]->setExpression(tmp.second);

    pair<string, vector <string>> tmp2 = Converter("b=a").toRPN();
    vars[tmp2.first]->setExpression(tmp2.second);

    pair<string, vector <string>> tmp3 = Converter("a=b").toRPN();
    vars[tmp3.first]->setExpression(tmp3.second);

    bool caught = false;
    try {
        vars[tmp.first]->value();
    }
    catch (const string &e) {
        caught = true;
    }
    assert(caught);
}
