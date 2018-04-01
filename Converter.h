//
// Created by Wojcik98 on 28.03.18.
//

#ifndef INC_2PRJ_CONVERTER_H
#define INC_2PRJ_CONVERTER_H

#include <string>
#include <vector>
#include <utility>

using namespace std;

class Converter {
public:
    explicit Converter(string infix);
    pair<string, vector<string>> toRPN();

private:
    string infix;
    vector<string> rpn;
    string varToAssign;
    void rpnStep(unsigned int &i);
    void validate();
    void clean();
};


#endif //INC_2PRJ_CONVERTER_H
