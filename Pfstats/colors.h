#ifndef COLORS_H
#define COLORS_H

#include <vector>
#include <string>

using namespace std;

class Colors
{
private:
    vector<string> hexColors; //ordered

public:
    Colors();
    string getColor(int x);
};

#endif // COLORS_H
