//
// Created by Wojcik98 on 28.03.18.
//

#ifndef INC_2PRJ_CONVERTER_H
#define INC_2PRJ_CONVERTER_H

#include <string>
#include <vector>

using namespace std;

class Converter {
public:
    explicit Converter(string infix);
    vector<string> toRPN();

private:
    string infix;
    vector<string> rpn;
    void rpnStep(int &i);
    void validate();
};


#endif //INC_2PRJ_CONVERTER_H
