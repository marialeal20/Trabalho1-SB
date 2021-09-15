#ifndef SYMBOLSTABLE_H_INCLUDED
#define SYMBOLSTABLE_H_INCLUDED
#define MAX 200
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

//Classe da tabela de símbolos, cada um será um objeto dessa classe
class TS
{
public:
    bool flag_pending;
    string name_symbol; //Nome do token
    int address;        //Endereço do token
    string value;
    string vector_symbols; //Valor que guarda o endereço de declaração (const n, space 0)
    int line;              //Linha do token
};

vector<TS> labels; //Vetor responsável por guardar essas labels

bool VerifyLabel(string Label)
{ //Verifica se a label respeita as regras de nomes de variáveis. Se flag_verify for true, então as labels estão de acordo, senão, não estão de acordo e retornam um erro
    bool flag_verify = true;
    if (Label.size() > 50)
    {
        flag_verify = false;
    }
    if (Label.front() == '1' || Label.front() == '2' || Label.front() == '3' || Label.front() == '4' || Label.front() == '5' || Label.front() == '6' || Label.front() == '7' || Label.front() == '8' || Label.front() == '9' || Label.front() == '_')
    {
        flag_verify = false;
    }
    for (int i = 0; i < (signed)Label.length(); i++)
    {
        if (Label.at(i) == '.' || Label.at(i) == '-' || Label.at(i) == ',' || Label.at(i) == '*' || Label.at(i) == '#' || Label.at(i) == ';' || Label.at(i) == '@' || Label.at(i) == '+')
        {
            flag_verify = false;
        }
    }
    return flag_verify;
}

bool verifyTS(vector<TS> ts, string name)
{ //encontrar o endereço das labels
    for (int i = 0; i < (signed)ts.size(); i++)
    {
        if (ts[i].name_symbol == name)
        {
            return true;
        }
    }
    return false;
}

bool verifyStr(vector<string> ts, string name)
{ //encontrar o endereço das labels
    for (int i = 0; i < (signed)ts.size(); i++)
    {
        if (ts[i] == name)
        {
            return true;
        }
    }
    return false;
}

#endif // SYMBOLSTABLE_H_INCLUDED