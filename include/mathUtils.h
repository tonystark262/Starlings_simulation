#ifndef MATHUTILS_H
#define MATHUTILS_H
#include "ds.h"
#include <random>

using namespace std;

float getDistance(const position_struct &p1, const position_struct &p2);
float speed(const velocity_struct &v);
float random_number(float a=-1.0, float b=1.0);
position_struct random_position(float x=0.5, float y=0.5, float z=0.5);
velocity_struct random_velocity(float x=0.02, float y=0.02, float z=0.02);
bool isInVision(const velocity_struct &v, const position_struct &p, const position_struct &q);

#endif