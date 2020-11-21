#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <iterator>
#include <sstream>
#include <utility>
#include <queue>

using namespace std;

vector<int>my_data {3, 0, 0, 0};
//ingridients
//[d0, d1, d2, d3, id, price, type]
vector<vector<int> > casts = {vector<int>( 2,  0,  0,  0, 78,  0,  1),
        vector<int>(-1,  1,  0,  0, 79,  0,  1),
        vector<int>( 0, -1,  1,  0, 80,  0,  1),
        vector<int>( 0,  0, -1,  1, 81,  0,  1)
};

vector<vector<int> > learn = (
vector<int>( 0,  6,  4, -4, 31,  1,  0,  2),
vector<int>( 0,  9,  6, -6, 31,  1,  0,  3),
vector<int>( 0,  3,  2, -2, 31,  1,  0,  1),
vector<int>(-6,  0,  0,  2,  0,  1,  1,  2),
vector<int>(-9,  0,  0,  3,  0,  1,  1,  3),
vector<int>(-3,  0,  0,  1,  0,  1,  1,  1),
vector<int>(-8,  0,  4,  0, 11,  1,  2,  2),
vector<int>(-12,   0,   6,   0,  11,   1,   2,   3),
vector<int>(-4,  0,  2,  0, 11,  1,  2,  1),
vector<int>( 8,  2, -2,  0, 28,  1,  3,  2),
vector<int>(12,  3, -3,  0, 28,  1,  3,  3),
vector<int>( 4,  1, -1,  0, 28,  1,  3,  1),
vector<int>( 0,  0, -4,  4, 39,  1,  4,  2),
vector<int>( 0,  0, -6,  6, 39,  1,  4,  3),
vector<int>( 0,  0, -2,  2, 39,  1,  4,  1),
vector<int>(1, 1, 0, 0, 2, 0, 5, 1)
);
