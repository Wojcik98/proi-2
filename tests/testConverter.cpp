//
// Created by Wojcik98 on 01.04.18.
//

#include <cassert>
#include "testConverter.h"
#include "../Converter.h"

/**
 * @brief testConverter::testCorrect
 * Tests if correct equations are converted properly.
 */
void testConverter::testCorrect(){
    pair<string, vector<string>> extracted = Converter("2+2*7").toRPN();
    assert(extracted.first == "ans");
    assert(extracted.second[0]=="2");
    assert(extracted.second[1]=="2");
    assert(extracted.second[2]=="7");
    assert(extracted.second[3]=="*");
    assert(extracted.second[4]=="+");

    pair<string, vector<string>> extracted2 = Converter("a=2+2*7").toRPN();
    assert(extracted2.first == "a");
    assert(extracted2.second[0]=="2");
    assert(extracted2.second[1]=="2");
    assert(extracted2.second[2]=="7");
    assert(extracted2.second[3]=="*");
    assert(extracted2.second[4]=="+");

    pair<string, vector<string>> extracted3 = Converter("(2+2)*7").toRPN();
    assert(extracted3.first == "ans");
    assert(extracted3.second[0]=="2");
    assert(extracted3.second[1]=="2");
    assert(extracted3.second[2]=="+");
    assert(extracted3.second[3]=="7");
    assert(extracted3.second[4]=="*");
}

/**
 * @brief testConverter::testEmpty
 * Tests if empty equation causes exception.
 */
void testConverter::testEmpty(){
    bool caught = false;
    try {
        pair<string, vector<string>> extracted = Converter(" ").toRPN();
    }
    catch (const string &e) {
        caught = true;
    }
    assert(caught);

    caught = false;
    try {
        pair<string, vector<string>> extracted = Converter("a=  ").toRPN();
    }
    catch (const string &e) {
        caught = true;
    }
    assert(caught);
}

/**
 * @brief testConverter::testSpaces
 * Tests if invalid characters are removed properly.
 */
void testConverter::testInvalidCharacters(){
    pair<string, vector<string>> extracted = Converter(" < 2 +\t2  ? *7{ ] ").toRPN();
    assert(extracted.first == "ans");
    assert(extracted.second[0]=="2");
    assert(extracted.second[1]=="2");
    assert(extracted.second[2]=="7");
    assert(extracted.second[3]=="*");
    assert(extracted.second[4]=="+");
}

/**
 * @brief testConverter::testInvalidBrackets
 * Tests if invalid brackets cause exception.
 */
void testConverter::testInvalidBrackets(){
    bool caught = false;

    try {
        Converter("(2+2*7").toRPN();
    }
    catch (const string &e) {
        caught = true;
    }
    assert(caught);
    caught = false;

    try {
        Converter("(2+2))*7").toRPN();
    }
    catch (const string &e) {
        caught = true;
    }
    assert(caught);
    caught = false;

    try {
        Converter("((2+2*7)").toRPN();
    }
    catch (const string &e) {
        caught = true;
    }
    assert(caught);
}

/**
 * @brief testConverter::testInvalidAssignment
 * Tests if multiple assignment signs cause exception.
 */
void testConverter::testInvalidAssignment(){
    bool caught = false;

    try {
        Converter("a==2*2").toRPN();
    }
    catch (const string &e) {
        caught = true;
    }
    assert(caught);
    caught = false;

    try {
        Converter("a=b=2*2").toRPN();
    }
    catch (const string &e) {
        caught = true;
    }
    assert(caught);
}

/**
 * @brief testConverter::testOperators
 * Tests operators priority and if invalid placement causes exception.
 */
void testConverter::testOperators(){
    pair<string, vector<string>> extracted = Converter("ln1*2/exp3+log4^5-6!").toRPN();
    assert(extracted.second[0]=="1");
    assert(extracted.second[1]=="ln");
    assert(extracted.second[2]=="2");
    assert(extracted.second[3]=="*");
    assert(extracted.second[4]=="3");
    assert(extracted.second[5]=="exp");
    assert(extracted.second[6]=="/");
    assert(extracted.second[7]=="4");
    assert(extracted.second[8]=="log");
    assert(extracted.second[9]=="5");
    assert(extracted.second[10]=="^");
    assert(extracted.second[11]=="+");
    assert(extracted.second[12]=="6");
    assert(extracted.second[13]=="!");

    bool caught = false;
    try {
        pair<string, vector<string>> extracted2 = Converter("2+").toRPN();
    }
    catch (const string &e) {
        caught = true;
    }
    assert(caught);
}
