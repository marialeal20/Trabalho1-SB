#ifndef SYMBOLSTABLE_H_INCLUDED
#define SYMBOLSTABLE_H_INCLUDED
#define MAX 200
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

//Classe da tabela de símbolos, cada um será um objeto dessa classe
class TS{
    public:
        bool flag_pending;
        string name_symbol;
        int address;
        //vector <int> line;
        //TS(bool, string,int);
};

/*TS::TS(bool arg1, string arg2, int arg3){
    flag_pending=arg1;
    name_symbol=arg2;
    address=arg3;
}*/

//Vetor responsável por guardar essas labels
TS labels[MAX];

//Verifica se a label respeita as regras de nomes de variáveis. Se flag_verify for true, então as labels estão de acordo, senão, não estão de acordo e retornam um erro
bool VerifyLabel(string Label){
    bool flag_verify=true;
    if(Label.size()>50){
        flag_verify=false;
    }
    if(Label.front()== '1'||Label.front()== '2'||Label.front()== '3'||Label.front()== '4'||Label.front()=='5'||Label.front()== '6'||Label.front()=='7'||Label.front()== '8'||Label.front()== '9'|| Label.front()=='_'){
        flag_verify=false;
    }
    for (int i=0; i<Label.length();i++){
        if(Label.at(i)=='.'||Label.at(i)=='-'||Label.at(i)==','||Label.at(i)=='*'||Label.at(i)=='#'||Label.at(i)==';'||Label.at(i)=='@'||Label.at(i)=='+'){
            flag_verify=false;
        }
    }
    return flag_verify;
}



#endif// SYMBOLSTABLE_H_INCLUDED