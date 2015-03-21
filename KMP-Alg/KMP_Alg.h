#ifndef KMP_ALG_H_
#define KMP_ALG_H_
#include "UnaryArray.h"

/*
 * This is the primitive prefix function algorithm of KMP algorithm.
 * KMP_First_Match function call Prefix function to generate pattern string's
 * prefix array and use it to match target string.
*/

//This Prefix function hasn't been optimized.
//We can use recurse to optimize it.
//We can read this code to figure out how to generate a next array of a pattern string.
UnaryArray<int>* Prefix(UnaryArray<char>&);

//This Max_matched_length function is use to assist prefix
//to figure out the prefix array(also called next array).
int Max_matched_length(UnaryArray<char>&, int);

//KMP Algorithm function.
//Read the implement codes to understand it.
int KMP_First_Match(UnaryArray<char>&, UnaryArray<char>&);

//Optimized prefix function.
//It's hard to understand the meaning of codes.
UnaryArray<int>* Optimized_Prefix(UnaryArray<char>&);

#endif // KMP_ALG_H_
