#ifndef GLOXCOMMON_HPP_
#define GLOXCOMMON_HPP_

#include <inttypes.h>
#include <cstdio>

/* Include the OpenGL stuff */
#include "GL/gl.h"

/*
 * Author: jrahm
 * created: 2013/10/23
 * GloxCommon.hpp: <description>
 */

namespace glox {
    typedef long long Glox64;
    typedef unsigned long long Glox64u;
    typedef int Glox32;
    typedef unsigned int Glox32u;
    typedef unsigned char Glox8u;
    typedef signed char Glox8;
    typedef unsigned short Glox16u;
    typedef signed short Glox16;
};

#endif /* GLOXCOMMON_HPP_ */