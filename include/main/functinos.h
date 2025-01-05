#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

int genRand(int min, int max)
{
    int timeX = time(0);
    srand(timeX);
    int modulus = max - min + 1;

    int result = min + rand() % modulus;

    return result;
}