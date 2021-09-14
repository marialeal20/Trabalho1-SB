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
        string value;
        string vector_symbols;
        int line;
        //vector <int> line;
        //TS(bool, string,int);
};

//Vetor responsável por guardar essas labels
vector <TS> labels;

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

int adress_code(string charaux, string charaux_ant, int code_adress){ //encontrar o endereço das labels
    return 0;
}
/*
void insertobject2vector(vector <TS> labels, bool flagpending, string charaux, int count_address, int valuen, int label_vector){

    labels[label_vector].flag_pending=flagpending;
    labels[label_vector].name_symbol=charaux;
    labels[label_vector].address=count_address;
    labels[label_vector].value=valuen; //Vetor de objetos
    label_vector++;

    cout<< "status: "<< labels[label_vector].flag_pending<<endl;
    cout<< "name:" << labels[label_vector].name_symbol<<endl;
    cout << "address" << labels[label_vector].address << endl;
    cout << "value" << labels[label_vector].value << endl;
}*/
#endif// SYMBOLSTABLE_H_INCLUDED