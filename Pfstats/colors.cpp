#include "colors.h"

Colors::Colors()
{
    hexColors.push_back("#9180ff");
    hexColors.push_back("#7fffa1");
    hexColors.push_back("#fffbbf");
    hexColors.push_back("#ff80b3");
    hexColors.push_back("#bffff2");
    hexColors.push_back("#ffee00");
    hexColors.push_back("#c8bfff");
    hexColors.push_back("#ff2200");
    hexColors.push_back("#4100f2");
    hexColors.push_back("#81f200");
    hexColors.push_back("#ffaa00");
    hexColors.push_back("#ffbfbf");
    hexColors.push_back("#3d9df2");
    hexColors.push_back("#917399");
    hexColors.push_back("#992654");
    hexColors.push_back("#822699");
    hexColors.push_back("#94994d");
    hexColors.push_back("#258c00");
    hexColors.push_back("#8c0000");
    hexColors.push_back("#8c5e00");
}

string Colors::getColor(int x){
    return hexColors[x];
}
