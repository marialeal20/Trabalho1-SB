#ifndef ERRORANALYSIS_H_INCLUDED
#define ERRORANALYSIS_H_INCLUDED
#define MAX 200
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

class Errors{
    public:
        string Error_name;
        vector <int> Error_line;
        string Error_msg;

};

Errors error_name[MAX];
#endif// ERRORANALYSIS_H_INCLUDED
