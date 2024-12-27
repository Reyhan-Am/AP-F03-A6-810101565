#include "Utaste.hpp"

UTaste::UTaste(string districts_path, string restaurants_path)
    : putter(districts_path, restaurants_path, *this),
      poster(districts_path, restaurants_path, *this),
      deleter(districts_path, restaurants_path, *this),
      getter(districts_path, restaurants_path) {}
void UTaste::checkCommand()
{
    string command, word;
    vector<string> command_words;
    bool inside_quotes = false;
    string current_token = "";

    while (getline(cin, command))
    {
        try
        {
            command_words.clear();
            stringstream command_stream(command);
            while (getline(command_stream, word, ' '))
            {
                if (!inside_quotes && word.front() == '"' && word.back() == '"')
                {
                    command_words.push_back(word);
                }
                else if (!inside_quotes && word.front() == '"' && word.back() != '"')
                {
                    inside_quotes = true;
                    current_token = word;
                }
                else if (inside_quotes)
                {
                    current_token += " " + word;
                    if (word.back() == '"')
                    {
                        inside_quotes = false;
                        command_words.push_back(current_token);
                        current_token.clear();
                    }
                }
                else
                {
                    command_words.push_back(word);
                }
            }
            if (command_words[0] == "GET")
            {
                getter.checkCommand(command_words);
            }
            else if (command_words[0] == "PUT")
            {
                putter.checkCommand(command_words);
            }
            else if (command_words[0] == "POST")
            {
                poster.checkCommand(command_words);
            }
            else if (command_words[0] == "DELETE")
            {
                deleter.checkCommand(command_words);
            }
            else
            {
                throw Exception(BAD_REQ);
            }
        }
        catch (Exception &ex)
        {
            ex.handleException();
        }
    }
}
void UTaste::deleteReserve(vector<string> &command_words)
{
    putter.deleteReserve(command_words);
    poster.deleteReserve(command_words);
    deleter.deleteReserve(command_words);
    getter.deleteReserve(command_words);
    throw Exception(OK);
}
void UTaste::setNewUser(pair<USERNAME, USER_DATA> &new_user)
{
    putter.setNewUser(new_user);
    poster.setNewUser(new_user);
    deleter.setNewUser(new_user);
    getter.setNewUser(new_user);
}
void UTaste::setLogin(string username)
{
    putter.setLogin(username);
    poster.setLogin(username);
    deleter.setLogin(username);
    getter.setLogin(username);
}
void UTaste::setLogout(string username)
{
    putter.setLogout(username);
    poster.setLogout(username);
    deleter.setLogout(username);
    getter.setLogout(username);
}
void UTaste::setUserDistrict(string *districti_ptr, string username)
{
    putter.setUserDistrict(districti_ptr, username);
    poster.setUserDistrict(districti_ptr, username);
    deleter.setUserDistrict(districti_ptr, username);
    getter.setUserDistrict(districti_ptr, username);
    throw Exception(OK);
}
void UTaste::setReserve(string *&restaurant_name_ptr, string *&table_id_ptr, string *&start_time_ptr,
                        string *&end_time_ptr,
                        string *&foods_ptr)
{
    putter.setReserve(restaurant_name_ptr, table_id_ptr, start_time_ptr, end_time_ptr, foods_ptr);
    putter.handleReserve(restaurant_name_ptr, table_id_ptr, start_time_ptr, end_time_ptr, foods_ptr);
    getter.handleReserve(restaurant_name_ptr, table_id_ptr, start_time_ptr, end_time_ptr, foods_ptr);
    deleter.handleReserve(restaurant_name_ptr, table_id_ptr, start_time_ptr, end_time_ptr, foods_ptr);
    poster.handleReserve(restaurant_name_ptr, table_id_ptr, start_time_ptr, end_time_ptr, foods_ptr);
    putter.printReserveMessage(restaurant_name_ptr);
}
void UTaste::printing()
{
}