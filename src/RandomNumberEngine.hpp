/** ---------------------------------------------------------------------------
 ** rng.hpp
 ** Header file that contains random number generator abstractions.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef MINIMUM_CUT_RNG_HPP
#define MINIMUM_CUT_RNG_HPP

#include <random>

enum Engine {MERSENNE, CLASSIC_C};

class RandomNumberEngine{
public:
    RandomNumberEngine(Engine selection);

    /**
     * @param from Minimum value that can be returned.
     * @param to Maximum value that can be returned.
     * @return Random value in the specified range.
     */
    unsigned int GetRandom(unsigned int from, unsigned int to);

private:
    Engine mEngine;
};

unsigned int getRandom(unsigned int from, unsigned int to);

#endif //MINIMUM_CUT_RNG_HPP
