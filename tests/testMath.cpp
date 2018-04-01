//
// Created by Wojcik98 on 01.04.18.
//

#include <cassert>
#include <cmath>
#include "testMath.h"
#include "../Math.h"

#define FEQUAL(a, b) (fabs((a)-(b))<0.0000001)

/**
 * @brief testMath::testOperators
 * Tests if methods related to operators work properly.
 */
void testMath::testOperators() {
    assert(Math::isOperator('+'));
    assert(Math::isOperator('-'));
    assert(Math::isOperator('*'));
    assert(Math::isOperator('/'));
    assert(Math::isOperator('!'));
    assert(!Math::isOperator('t'));
    assert(FEQUAL(Math::factorial(3), 6));
    assert(FEQUAL(Math::operation(2,5,"+"), 7));
    assert(FEQUAL(Math::operation(5,2,"-"), 3));
    assert(FEQUAL(Math::operation(5,2,"*"), 10));
    assert(FEQUAL(Math::operation(5,2,"/"), 2.5));
    assert(FEQUAL(Math::operation(5,2,"^"), 25));
    assert(Math::operatorPrio("ln") == Math::operatorPrio("!"));
    assert(Math::operatorPrio("!") > Math::operatorPrio("^"));
    assert(Math::operatorPrio("^") > Math::operatorPrio("*"));
    assert(Math::operatorPrio("*") == Math::operatorPrio("/"));
    assert(Math::operatorPrio("/") > Math::operatorPrio("+"));
    assert(Math::operatorPrio("+") == Math::operatorPrio("-"));
}

/**
 * @brief testMath::testFunctions
 * Tests if methods related to functions work properly.
 */
void testMath::testFunctions() {
    assert(Math::isFunction("ln"));
    assert(Math::isFunction("log"));
    assert(Math::isFunction("exp"));
    assert(!Math::isFunction("sth"));
    assert(FEQUAL(Math::factorial(3), 6));
    assert(FEQUAL(Math::function("ln", 5), 1.6094379124341003));
    assert(FEQUAL(Math::function("log", 5), 0.6989700043360188));
    assert(FEQUAL(Math::function("exp", 5), 148.41315910257660342));
}
