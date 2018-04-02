//
// Created by Wojcik98 on 01.04.18.
//

#include <iostream>

#include "testMath.h"
#include "testConverter.h"
#include "testVariable.h"

using namespace std;

int main(){
    cout << "Running testMath::testOperators..." << endl;
    testMath::testOperators();
    cout << "Running testMath::testFunctions..." << endl;
    testMath::testFunctions();

    cout << "Running testConverter::testCorrect..." << endl;
    testConverter::testCorrect();
    cout << "Running testConverter::testEmpty..." << endl;
    testConverter::testEmpty();
    cout << "Running testConverter::testInvalidCharacters..." << endl;
    testConverter::testInvalidCharacters();
    cout << "Running testConverter::testInvalidBrackets..." << endl;
    testConverter::testInvalidBrackets();
    cout << "Running testConverter::testInvalidAssignment..." << endl;
    testConverter::testInvalidAssignment();
    cout << "Running testConverter::testOperators..." << endl;
    testConverter::testOperators();

    cout << "Running testVariable::testEvaluation..." << endl;
    testVariable::testEvaluation();
    cout << "Running testVariable::testUnknownVariable..." << endl;
    testVariable::testUnknownVariable();
    cout << "Running testVariable::testSelfreferencing..." << endl;
    testVariable::testSelfreferencing();

    cout << "All tests passed!" << endl;
    return 0;
}
