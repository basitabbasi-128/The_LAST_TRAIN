#include "util.h"
#include<iostream>
// Primitive helper utilities, clamping, and screen control
using namespace std;

// it keeps value within minimum and maximum limit 
int clampInt (int val, int minVal, int maxVal){
    if (val < minVal) return minVal;
    else if (val > maxVal) return maxVal;
    else return val;
}

// removes the extra space from start and end of string 
void trimWhitespace(char* str){
    int length = 0;
    for (; str[length] !='\0' ;){
        length++;
    }
    int st = 0;
    int end= length - 1;
    for (; st <=end && str[st] == ' ' ;){
        st++;
    }
    for (; end >=st && str[end] ==' ' ;){
        end--;
    }
    int a = 0;
    for(int i=st ; i<=end ; i++){
        str[a] = str[i];
        a++;
     }
    str[a]= '\0';}

// checks if two strings are equal
bool stringEquals(const char* a, const char* b){
    int i=0;
    for (; a[i] != '\0' && b[i] !='\0' ;){
        if (a[i] != b[i]){
            return false;
        }
        i++;    
    }
    return a[i]=='\0' && b[i] == '\0';
}

// prints title
void printHeader(const char* title){
    cout << "===============================" << endl;
    cout << title << endl;
    cout << "===============================" << endl;
}
//clears screen
void clearScreen(){
    for (int i = 0; i < 30; i++ ){
        cout << "    " << endl;
    }
}