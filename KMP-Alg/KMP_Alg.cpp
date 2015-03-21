#include "KMP_Alg.h"
//#define DEBUG_MODE_POS1
//#define DEBUG_MODE_POS2
//#define DEBUG_MODE_POS3

/*
 * First, we should known the meaning of prefix array.
 * In prefix array, value of a prefix array element is corresponded with
 * the original string's element that has the same index value.
 * The meaning of a prefix array element is to guide the algorithm to
 * get next start index of matching when mismatch happens.
 *
 * Then, prefix array is generated according to the pattern's self-symmetry.
 * Every prefix array element value is the longest matched counts of prefixes of
 * a string.
 * For example, string "ababc" has four sub prefix "a", "ab", "aba", "abab" and
 * four suffix "c", "bc", "abc", "babc".
 * Except for "a" and "c", every prefixes and suffixes have their own prefixes and suffixes.
 * So the prefix array element value of index0(corresponding index of "a") is 0.
 * When the index value goes to 1, it corresponds to "ab" and "ab" have a prefix "a" and a suffix
 * "b". But "a" is not matched with "b". So the value of prefix array element which has the index
 * 1 is 0.
 * When the index value goes to 2, it corresponds to "aba" (prefixes: "a", "ab"; suffixes: "a","ab").
 * The longest matched counts is 2(prefix "ab" matches suffix "ab").
 * And so we can calculate in this way when then index value goes.
 * This how we calculate the prefix array of a string.
 */
UnaryArray<int>* Prefix(UnaryArray<char>& pattern){
    int patternLength = pattern.getSize();      //Get the bound of calculation.
#ifdef DEBUG_MODE_POS1
    std::cout << "Got string size: " << patternLength << std::endl;
#endif // DEBUG_MODE_POS1
    UnaryArray<int>* prefixValue = new UnaryArray<int>(patternLength);      //Allocate the memory of prefix array.
#ifdef DEBUG_MODE_POS1
std::cout << "Record size: " << prefixValue->getSize() << std::endl;
#endif // DEBUG_MODE_POS1
    prefixValue->operator[](0) = 0;             //Sub prefix of single character can match nothing so its value is 0.
    //(*prefixValue)[0] = 0;
    int prefixCounter = 1;                      //Start with sub prefix which has two characters.
    while(prefixCounter < patternLength){
#ifdef DEBUG_MODE_POS1
        std::cout << "Looping in the prefix while clause. Location Index: " << prefixCounter << std::endl;
#endif // DEBUG_MODE_POS1
        //Max_matched_length function is the core of calculating prefix array.
        //In this loop, we slice the original string to prefix pieces.
        //And pass this prefix pieces to Max_matched_length.
        //The function will return the max matched count of this prefix pieces.
        prefixValue->operator[](prefixCounter) = Max_matched_length(pattern, prefixCounter + 1);
        //(*prefixValue)[prefixCounter] = prefixCounter + 1;
        ++prefixCounter;
    }
    return prefixValue;
}

//Core algorithm of calculating prefix array.
int Max_matched_length(UnaryArray<char>& pattern, int totalCompareLength){
    int compareLength = 1;
    int matched = 0, oldMatched = 0;
    int frontHead, rearHead;
#ifdef DEBUG_MODE_POS2
    std::cout << "Total compare string length:" << totalCompareLength << std::endl;
#endif // DEBUG_MODE_POS2
    while(compareLength < totalCompareLength){          //We use bound to limit the loop.
#ifdef DEBUG_MODE_POS2
        std::cout << "Looping in matching function loop.Location Index:" << compareLength << std::endl;
#endif
        oldMatched = matched;       //The variable is current using, we need a record to recover the value
        //when the mismatch happens.
        matched = 0;
        frontHead = 0;
        rearHead = totalCompareLength - compareLength;  //Get the start index of suffix.
        //Start matching sub prefix and sub suffix.
        while((rearHead < totalCompareLength) && (pattern[frontHead] == pattern[rearHead]))
        {
            ++frontHead, ++rearHead, ++matched;
#ifdef DEBUG_MODE_POS2
            std::cout << "Front: " << frontHead << " Rear: " << rearHead << " matched: " << matched << std::endl;
#endif // DEBUG_MODE_POS2
        }
        if(rearHead < totalCompareLength)matched = oldMatched;
        ++compareLength;        //Remember matching next prefix and suffix.
    }
#ifdef DEBUG_MODE_POS2
    std::cout << "Returning..." << std::endl;
#endif // DEBUG_MODE_POS2
    return matched;
}

//KMP Algorithm implement codes.
int KMP_First_Match(UnaryArray<char>& target, UnaryArray<char>& pattern){
    int targetCounter = 0, totalTargetLength = target.getSize();
    int patternCounter = 0;
    //I have explained how Prefix function works.
    UnaryArray<int>* patternPrefix = Prefix(pattern);
#ifdef DEBUG_MODE_POS3
    patternPrefix->printArray(std::cout);
#endif // DEBUG_MODE_POS3
    for(targetCounter = 0; targetCounter < totalTargetLength; ++targetCounter){     //The target counter will not trace back.
        while(patternCounter > 0 && pattern[patternCounter] != target[targetCounter]){
            //When mismatch happens, this loop will proceed until return a index value
            //makes current position of pattern matched with target.
            //It's a key to figure out why next patternCounter = (*patternPrefix)[patternCounter - 1];
            //Is it we assume the last index before mismatched index is a matched index?
            patternCounter = (*patternPrefix)[patternCounter - 1];
#ifdef DEBUG_MODE_POS3
            std::cout << std::endl << "Mismatched target index:" << targetCounter << " and search next:" << patternCounter << std::endl;
#endif // DEBUG_MODE_POS3
        }
        if(pattern[patternCounter] == target[targetCounter]){
            //Matched and go ahead.
#ifdef DEBUG_MODE_POS3
            std::cout << "Matched: " << target[targetCounter] << " ";
#endif // DEBUG_MODE_POS3
            ++patternCounter;
        }
        if(patternCounter == pattern.getSize()){
            //Full match happened.
            //If we need to show all matched index, this
            //clause can be modified to save the index clause and "patternCounter = (*patternPrefix)[patternCounter - 1]".
            delete patternPrefix;
            return targetCounter - patternCounter + 1;
        }
    }
    delete patternPrefix;
    return -1;
}

//The optimized prefix function is based on this fact:
//Next prefix's longest matched number is current's plus 1 or reset to be 0.
UnaryArray<int>* Optimized_Prefix(UnaryArray<char>& pattern){
    int length = pattern.getSize();
    UnaryArray<int>* prefixValue = new UnaryArray<int>(length);
    (*prefixValue)[0] = -1;
    int i,j;
    for(j = 1; j < length; ++j){
        i = (*prefixValue)[j - 1];
        while(pattern[j] != pattern[i + 1] && i >= 0)
            i = (*prefixValue)[i];
        if(pattern[j] == pattern[i + 1])
            (*prefixValue)[j] = i + 1;
        else (*prefixValue)[j] = -1;
    }
    //Original optimized prefix function's prefix array element value is based on
    //pattern string's index when my define prefix array element value is base on
    //matched count.So we can add 1 to this element to fit my definition.
    for(i = 0; i < length; ++i)++(*prefixValue)[i];
    return prefixValue;
}
