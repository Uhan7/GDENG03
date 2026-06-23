#include "random.h"

float RandomFloat(float min, float max){
    static random_device rd;
    static mt19937 gen(rd());
    uniform_real_distribution<float> distrib(min, max);
    return distrib(gen);
}