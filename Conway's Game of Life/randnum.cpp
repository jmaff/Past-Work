//
//  randnum.cpp
//  Conway's Game of Life
//
//  Created by 21maffetone on 12/10/17.
//  Copyright © 2017 21maffetone. All rights reserved.
//
#include <random>

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);  // static used for efficiency, so we only calculate this value once
    // evenly distribute the random number across our range
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}
