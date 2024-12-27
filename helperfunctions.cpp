#include <string>
#include <iterator>
using namespace std;
bool isStartWithComma(string word)
{
    if ((*word.begin() == '"') && *(word.end() - 1) == '"')
    {
        return true;
    }
    return false;
}
