#include <iostream>
//#include "Simple_String_Algorithm.h"
#include "KMP_Alg.h"

using namespace std;

//int Test_simple_string_Algorithm();
int Test_prefix();
int Test_UnaryArray();
int Test_KMP_First_Match();
int Test_Optimized_Prefix();

int main()
{
    Test_Optimized_Prefix();
    //Test_KMP_First_Match();
    //Test_prefix();
    //char pattern[] = "abcabcd";
    //int nothing[] = {1, 2, 3};
    //Print_arrary(pattern, sizeof(pattern));
    //Print_arrary(nothing, 3);
    return 0;//Test_simple_string_Algorithm();
}

/*
int Test_simple_string_Algorithm(){
    cout << "Start Match" << endl;
    cout << First_match("abababcagcdddd", "ababc")<< endl;
    //cout << Str_length("avc") << endl;
    cout << "Match Finished" << endl;
}
*/

int Test_UnaryArray(){
    UnaryArray<int> intUnaryArray(3);
    intUnaryArray[0] = 1;
    intUnaryArray[1] = 2;
    intUnaryArray[2] = 3;
    try{
        intUnaryArray[2] = 5;
    }catch(invalid_argument e){
        cout << "Invalid_argument exception caught." << endl;
        e.what();
    }
    intUnaryArray.printArray(cout);
    return 0;
}

int Test_prefix(){
    /*
    UnaryArray<char> pattern(12);
    //pattern[0] = pattern[1] = pattern[2] = pattern[3] = pattern[4] = 'a';
    pattern[0] = 'a', pattern[1] = 'b';
    pattern[2] = 'c', pattern[3] = 'c';
    pattern[4] = 'a', pattern[5] = 'b';
    pattern[6] = 'c', pattern[7] = 'c';
    pattern[8] = 'a', pattern[9] = 'b';
    pattern[10] = 'c', pattern[11] = 'a';
    */
    //UnaryArray<char> pattern("abccabccabca");
    UnaryArray<char> pattern("agctagcagctagctg");
    //pattern.printArray(cout);
    UnaryArray<int>* prefixValue = Prefix(pattern);
    prefixValue->printArray(cout);
    delete prefixValue;
    prefixValue = 0;
    return 0;
}

int Test_KMP_First_Match(){
    UnaryArray<char> target("abababcagcdddd");
    UnaryArray<char> pattern("ababc");
    cout << "First Matched Index: " << KMP_First_Match(target, pattern) << endl;
    return 0;
}

int Test_Optimized_Prefix(){
    UnaryArray<char> pattern("abadabcabcdabc");
    UnaryArray<int>* prefixValue1 = Prefix(pattern);
    UnaryArray<int>* prefixValue2 = Optimized_Prefix(pattern);
    prefixValue1->printArray(cout);
    prefixValue2->printArray(cout);
    delete prefixValue1;
    prefixValue1 = 0;
    delete prefixValue2;
    prefixValue2 = 0;
    return 0;
}
