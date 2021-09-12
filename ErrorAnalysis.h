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
        int Error_line;
        string Error_msg;

};

vector <Errors> error_name;
#endif// ERRORANALYSIS_H_INCLUDED
