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

using namespace std;

struct USER_DATA
{
    bool is_logged_in;
    string password;
};
typedef string USERNAME;
typedef string DISTRICT;
typedef vector<string> NEIGHBORS;
typedef map<USERNAME, USER_DATA> USERS;
typedef vector<pair<DISTRICT, NEIGHBORS>> DISTRICTS;

#endif
