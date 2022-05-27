#ifndef randomness_functions_cpp
#define randomness_functions_cpp

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>


/* 
    Purpose: this module contains various functions for (psuedo-) random number generation.
    
    Prerequisites: set_srand() must be called before random numbers can be generated. 
*/


void set_srand()
{
    srand(time(NULL));
}

/* get random number between two inputs */
int get_rand_btwn (int num1, int num2)
{
    int rand_num = ( rand() % abs(num2-num1) + num1);
    return rand_num;
}

/* get random number between 0 and an input */
int mod_rand(int num)
{
    int rand_num = rand() % num;
    return rand_num;
}

/* either 0 or 1 */
bool coin_flip()
{
    int coin = mod_rand(2);
    return coin;
}

/* get random color */
std::vector<int> get_rand_color()
{
    int rand1 = rand()%255;
    int rand2 = rand()%255;
    int rand3 = rand()%255;

    std::vector<int> new_color = {rand1, rand2, rand3, 255};
    return new_color;
}


#endif /* randomness_functions_cpp */ 