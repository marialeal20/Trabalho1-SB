#ifndef ERRORANALYSIS_H_INCLUDED
#define ERRORANALYSIS_H_INCLUDED
#define MAX 200
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

class Errors
{
public:
    string Error_name;
    int Error_line;
    string Error_msg;
};

vector<Errors> error_name;

int sameLineLabel(vector<TS> labels)
{
    int sameLine;
    int num = 0;
    for (int i = 0; i < (signed)labels.size(); i++)
    {
        for (int j = 0; j < (signed)labels.size(); j++)
        {
            if (labels[i].line == labels[j].line)
            {
                num++;
            }
            if (num > (signed)labels.size())
            {
                sameLine = 1;
            }
            else
            {
                sameLine = 0;
            }
        }
    }
    return sameLine;
}

int sameNameLabel(vector<TS> labels)
{
    int sameName;
    int num = 0;
    for (int i = 0; i < (signed)labels.size(); i++)
    {
        for (int j = 0; j < (signed)labels.size(); j++)
        {
            if (labels[i].name_symbol == labels[j].name_symbol)
            {
                num++;
            }
        }
        if (num > (signed)labels.size())
        {

            sameName = 1;
        }
        else
        {
            sameName = 0;
        }
    }
    return sameName;
}

bool verifyLabel(vector<TS> ts)
{ //encontrar o endereço das labels
    int found = 0;
    for (int i = 0; i < (signed)ts.size(); i++)
    {
        for (int j = 0; j < (signed)ts.size(); j++)
        {
            if (ts[j].name_symbol == ts[i].name_symbol)
            {
                found++;
            }
        }
    }
    if (found > (signed)ts.size())
    {
        return false;
    }
    return true;
}
#endif // ERRORANALYSIS_H_INCLUDED
