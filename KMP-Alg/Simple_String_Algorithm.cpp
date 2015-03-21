#include<iostream>
#include "Simple_String_Algorithm.h"
//#define DEBUG_MODE_POS0


int First_match(char* str, char* pattern){
    int strIndex = 0;
    bool matchFlag = false;
    while(str[strIndex] != '\0'){
#ifdef DEBUG_MODE_POS0
        std::cout << "In First_Match function loop.Current position: "<< strIndex << std::endl;
#endif // DEBUG_MODE
        if(matchFlag)return strIndex - Str_length(pattern) + 1;
        matchFlag = Match(str, pattern, &strIndex);
        if(Str_length(str, strIndex) < Str_length(pattern))return -1;
    }
    return -1;
}

bool Match(char* str, char* pattern, int* startMatchPosition){
    int strIndex = *startMatchPosition, patternIdx = 0;
    if(str[strIndex] != pattern[patternIdx]){
        *startMatchPosition = strIndex + 1;
        return false;
    }
    while(str[strIndex] != '\0' && pattern[patternIdx] != '\0'){
#ifdef DEBUG_MODE_POS0
        std::cout << "In Match function loop." << std::endl;
#endif // DEBUG_MODE
        if(str[strIndex] != pattern[patternIdx])break;
        ++strIndex;
        ++patternIdx;
    }
    if(pattern[patternIdx] == '\0'){
        *startMatchPosition = strIndex - 1;
        return true;
    }else {
        *startMatchPosition = strIndex;
        return false;
    }
}

int Str_length(char* str, int start){
    while(str[start] != '\0')++start;
    return start;
}
