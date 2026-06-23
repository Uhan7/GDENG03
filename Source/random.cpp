#include "random.h"

float RandomFloat(float min, float max){
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> distrib(min, max);
    return distrib(gen);
}