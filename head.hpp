#ifndef HEAD_HPP
#define HEAD_HPP
#include <string>
#include <vector>
#include <cmath>
#include <iterator>
#include <algorithm>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>
#include "constants.hpp"

using namespace std;

struct USER_DATA
{
    bool is_logged_in;
    string password;
    string user_district;
};
typedef string USERNAME;
typedef string DISTRICT;
typedef vector<string> NEIGHBORS;
typedef map<USERNAME, USER_DATA> USERS;
typedef vector<pair<DISTRICT, NEIGHBORS>> DISTRICTS;

bool isStartWithComma(string word);

#endif
