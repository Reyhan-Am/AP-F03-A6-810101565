#include "command.hpp"

Command::Command(string districts_path, string restaurants_path)
{
    readDistricts(districts_path);
    readRestaurants(restaurants_path);
}
void Command::readDistricts(string districs_path)
{
    fstream csv_file;
    csv_file.open(districs_path);
    string line, word;
    vector<string> temp_line, temp_neighbors;
    int first_line_flag = 1;
    while (getline(csv_file, line))
    {
        stringstream line_stream(line);
        if (first_line_flag)
        {
            first_line_flag = 0;
            continue;
        }
        else
        {
            while (getline(line_stream, word, ','))
            {
                temp_line.push_back(word);
            }
            stringstream neighbors_stream(temp_line[1]);
            while (getline(neighbors_stream, word, ';'))
            {
                temp_neighbors.push_back(word);
            }
            districts.push_back({temp_line[0], temp_neighbors});
            temp_neighbors.clear();
            temp_line.clear();
        }
    }
}
void Command::readRestaurants(string restaurants_path)
{
    fstream csv_file;
    csv_file.open(restaurants_path);
    string line, word;
    vector<string> temp_line, temp_food;
    map<string, int> temp_foods;
    int first_line_flag = 1;
    while (getline(csv_file, line))
    {
        stringstream line_stream(line);
        if (first_line_flag)
        {
            first_line_flag = 0;
            continue;
        }
        else
        {
            while (getline(line_stream, word, ','))
            {
                temp_line.push_back(word);
            }
            stringstream foods_stream(temp_line[2]);
            while (getline(foods_stream, word, ';'))
            {
                stringstream food_stream(word);
                while (getline(food_stream, word, ':'))
                {
                    temp_food.push_back(word);
                }
                temp_foods[temp_food[0]] = stoi(temp_food[1]);
                temp_food.clear();
            }
            restaurants.push_back(Restaurant(temp_line[0], temp_line[1], temp_foods, stoi(temp_line[3]), stoi(temp_line[4]), stoi(temp_line[5])));
            temp_foods.clear();
            temp_line.clear();
        }
    }
}
void Command::printing()
{
    for (auto x : restaurants)
    {
        cout<<x.name<<x.district<<x.opening_time<<x.closing_time<<x.table_no<<endl;
        for(auto y:x.foods){
            cout<<y.first<<y.second<<endl;
        }
    }
}