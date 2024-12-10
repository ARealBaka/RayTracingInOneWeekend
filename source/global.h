#ifndef GLOBAL_H
#define GLOBAL_H

#include<cmath>
#include<iostream>
#include<limits>
#include<memory>
#include<cstdlib>

// Common Headers

#include"color.h"
#include"vec3.h"
#include"ray.h"


// C++ Std Usings

using std::make_shared;
using std::shared_ptr;

//Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;


// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}



#endif