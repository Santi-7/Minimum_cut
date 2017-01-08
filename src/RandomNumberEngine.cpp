/** ---------------------------------------------------------------------------
 ** rng.cpp
 ** Implementation of random number generators.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include "RandomNumberEngine.hpp"

RandomNumberEngine::RandomNumberEngine(Engine selection)
{
    // Initialize the random number generator
    switch(selection)
    {
    case MERSENNE:
        break;
    case CLASSIC_C:
        srand((unsigned int) time(NULL));
    }
    mEngine = selection;
}

unsigned int RandomNumberEngine::GetRandom(unsigned int from, unsigned int to)
{
    switch(mEngine)
    {
    case MERSENNE:
    {
        static std::random_device rd;     // only used once to initialise (seed) engine
        static std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
        std::uniform_int_distribution<int> uni(from, to); // guaranteed unbiased
        return (unsigned int) uni(rng);
    }
    case CLASSIC_C:
        // This random generator is biased towards lower values: http://www.cplusplus.com/reference/cstdlib/rand/
        return rand() % (to - from + 1) + from;
    }
    throw 1;
}
