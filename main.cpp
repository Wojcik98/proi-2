#include <iostream>
#include <string>
#include <vector>

#include "Converter.h"

using namespace std;

int main() {
    string equation;

    vector <string> tmp;

    while(getline(cin, equation)){
        try {
            tmp = Converter(equation).toRPN();
        }
        catch (const char *e){
                cout << e;
        }

        for(string a: tmp)
            cout << a << " ";
        cout << endl;
    }

    return 0;
}