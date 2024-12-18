#include "head.hpp"
#include "Utaste.hpp"


int main(int argc, char *argv[])
{
    UTaste utaste(argv[1], argv[2]);
    utaste.printing();
    return 0;
}