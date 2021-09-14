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

int sameLineLabel(vector <TS> labels){
    int sameLine; 
    for(int i=0; i<labels.size();i++){
        for (int j=0; j<labels.size(); j++){
            if (labels[i].line==labels[j].line){
                sameLine=1;
            }
            else{
                sameLine=0;
            }
        }
    }
    return sameLine;
}

int sameNameLabel(vector <TS> labels){
    int sameName; 
    for(int i=0; i<labels.size();i++){
        for (int j=0; j<labels.size(); j++){
            if (labels[i].name_symbol==labels[j].name_symbol){
                sameName=1;
            }
            else{
                sameName=0;
            }
        }
    }
    return sameName;
}
#endif// ERRORANALYSIS_H_INCLUDED
