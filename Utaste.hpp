#ifndef UTASTE_HPP
#define UTASTE_HPP
#include "head.hpp"
#include "put.hpp"
#include "post.hpp"
#include "delete.hpp"
#include "get.hpp"
#include "exception.hpp"

class UTaste
{
public:
    UTaste(string restaurants_path, string districts_path, string discounts_path);
    void checkCommand(const vector<string> &command_words, string &test);
    void setLogin(string username);
    void setLogout(string username);
    void setUserDistrict(string *districti_ptr, string username);
    void setReserve(string *&restaurant_name_ptr, string *&table_id_ptr, string *&start_time_ptr,
                    string *&end_time_ptr,
                    string *&foods_ptr, string &test);
    void setNewUser(pair<USERNAME, USER_DATA> &new_user);
    void deleteReserve(vector<string> &command_wordl);
    void delLastReserve(string &name);
    void increaseBudget(int &amount);
    void printing();

protected:
    Putter putter;
    Poster poster;
    Deleter deleter;
    Getter getter;
};
#endif
