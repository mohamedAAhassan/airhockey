#include <iostream>
#include "nnetparser.h"

using namespace std;


CNNParser parser("test.txt");

//string str = "1.5 3433435 2 4";
string token;
int pos;
int main()
{
    parser.parse();
    parser.getPatterns().print();

    return 0;
}
