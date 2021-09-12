#ifndef READFILE_H_INCLUDED
#define READFILE_H_INCLUDED
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "SymbolsTable.h"
#include "ErrorAnalysis.h"

using namespace std;

//Faz a verificação e abertura do arquivo

fstream openfile(char *name)
{
    fstream fileasm;
    fileasm.open(name);
    if (fileasm.is_open())
    {
        return fileasm;
    }
    else
    {
        cout << "O arquivo não pode ser aberto, verifique se esse arquivo existe" << endl;
    }
    return fileasm;
}
//fileasm.close()

fstream readfile(char *name)
{
    //Declaração de Variáveis
    fstream file;
    string charaux = "";
    string charaux_ant="";
    bool testeflag;
    bool include_data=false;
    int line=1;
    int label_vector=0, error_vector=0;
    int count_opcode=0,count_address=0;
    char character;
    vector <string> labelsectiondata;
    vector <int> object_counter;
    
    file.open(name, ios::in); //modo de leitura de arquivo
    if (file.is_open())
    {
        while (file.get(character)) //Pega caractere por caractere do arquivo
        {
           cout << character << endl;
         if (character == ' ' || character == '\n'){ //Separação entre tokens
              // cout << "charaux:"<< charaux << endl;
                 if (character =='\n'){
                     line++;
                  }
                 if (charaux.back() == ':' && include_data==false) //Verificação de Labels //se include data nao for true, tem que criar com endereço 0 e flag_pending true
                 {
                     charaux.pop_back();
                     testeflag=VerifyLabel(charaux); //Verifica se o nome das labels é válido, se sim, testeflag=true
                     if (testeflag==true){
                        TS label_token; //Objeto que representa uma label
                        labels.push_back(label_token);//Vetor de objetos Label
                        labels[label_vector].flag_pending=false;
                        labels[label_vector].name_symbol=charaux;
                        labels[label_vector].address=count_address;
                        labels[label_vector].value=0; 

                        label_vector++;
                        //insertobject2vector(labels,false,charaux,count_address,0,label_vector);
                     }
                     else{
                        Errors errordetected;//Objeto do tipo Erro
                        error_name.push_back(errordetected); //Acrescenta um objeto no vetor de labels
                        error_name[error_vector].Error_name="Sintax Error";
                        error_name[error_vector].Error_line= line;
                        error_name[error_vector].Error_msg="Erro de sintaxe, verifique o nome de sua variável"; //Erro para o caso de um nome de label inválido, objeto erro incluído no vetor de erros
                     }

                     charaux_ant=charaux;
                     charaux.clear();
                 }
                 if (charaux.back() == ':' && include_data==true) //Verificação de Labels //se include data nao for true, tem que criar com endereço 0 e flag_pending true
                 {
                     charaux.pop_back();
                     //VERIFICAR O QUE FAZER COM O COUNT_ADRESS
                     testeflag=VerifyLabel(charaux); //Verifica se o nome das labels é válido, se sim, testeflag=true
                     if (testeflag==true){//Vetor de objetos
                     TS label_token;
                     labels.push_back(label_token);
                     labels[label_vector].flag_pending=true;
                     labels[label_vector].name_symbol=charaux;
                     labels[label_vector].address= 0;
                     labels[label_vector].value=0; 

                     label_vector++;  
                     //insertobject2vector(labels,true,charaux,count_address,0,label_vector);   
                     }
                     else{
                        Errors errordetected;
                        error_name.push_back(errordetected);
                        error_name[error_vector].Error_name="Sintax Error";
                        error_name[error_vector].Error_line=line;
                        error_name[error_vector].Error_msg="Erro de sintaxe, verifique o nome de sua variável";
                        //Erro para o caso de um nome de label inválido, objeto erro incluído no vetor de erros
                     }
                     charaux_ant=charaux;
                     charaux.clear();
                 }
                 else //Verifica se está na etapa de texto ou de data para definir se as labels são pendentes ou não
                 {
                     if(charaux_ant=="SECTION"){ //Para a verificação de endereço de labels 
                         if (charaux=="TEXT"){
                            include_data=false;
                        }
                     else {
                        if(charaux =="DATA"){
                           include_data=true;
                         //Criar vetor para guardar as declarações que serão usadas ao final
                        }
                     }
                     }
                     //charaux_ant=charaux;
                    // charaux.clear();
                  }
                 if (charaux == "ADD"){
                    count_address=count_address+2;
                    object_counter.push_back(01);
                 }
                 if(charaux=="SUB"){
                    count_address=count_address+2;
                    object_counter.push_back(02);
                 }
                 if(charaux=="MUL"){
                    count_address=count_address+2;
                    object_counter.push_back(03);
                 }
                 if (charaux=="DIV"){
                    count_address=count_address+2;
                    object_counter.push_back(04);
                 }
                 if(charaux=="JMP"){
                    count_address=count_address+2;
                    object_counter.push_back(05);  
                 }
                 if(charaux=="JMPN"){
                    count_address=count_address+2;
                    object_counter.push_back(06);  
                 }
                 if(charaux=="JMPP"){
                    count_address=count_address+2;
                    object_counter.push_back(07);
                 }
                 if(charaux=="JMPZ"){
                    count_address=count_address+2;
                    object_counter.push_back(8);
                 }
                 if(charaux=="COPY"){
                    count_address=count_address+2;
                    object_counter.push_back(9);  
                 }
                 if(charaux=="LOAD"){
                    count_address=count_address+2;
                    object_counter.push_back(10);
                 }
                 if(charaux=="STORE"){
                    count_address=count_address+2;
                    object_counter.push_back(11);
                 }
                 if(charaux =="INPUT"){
                    count_address=count_address+2;
                    object_counter.push_back(12);
                 }
                 if(charaux=="OUTPUT"){
                    count_address=count_address+2;
                    object_counter.push_back(13);
                 }
                 if(charaux=="STOP"){
                    count_address=count_address+1;
                    object_counter.push_back(14);
                 }
                 //Verificar as labels e colocar os endereços, se nao tiver pendente bota o endereço, se estiver, bota 1000 (teste)
                for (int i=0; i<labels.size(); i++){
                    if (labels[i].name_symbol== charaux){
                        if(labels[i].flag_pending==false){
                          object_counter.push_back(labels[i].address);
                        //  cout <<"name symbol" <<labels[i].name_symbol <<endl;
                       }
                       else{
                          object_counter.push_back(10000);
                        //  cout <<"name symbol" <<labels[i].name_symbol <<endl;
                       }
                    }
                 }
                charaux_ant=charaux;
                charaux.clear();    
                //cout << charaux << "\n";
                //charaux = "";
            }
            
            else
            {
               if (character==','){
                  for (int i=0; i<labels.size(); i++){
                    if (labels[i].name_symbol== charaux){
                        if(labels[i].flag_pending==false){
                          object_counter.push_back(labels[i].address);
                        //  cout <<"name symbol" <<labels[i].name_symbol <<endl;
                       }
                       else{
                     object_counter.push_back(10000);
                     //cout <<"name symbol" <<labels[i].name_symbol <<endl;
                     }
                     charaux_ant=charaux;
                     charaux.clear();
                        /*
                       }*/
                       
                       }}}
               else{
                  if (file.eof()){
                     cout << "the end" << charaux << endl;
                     charaux.push_back(toupper(character));
                  }
                  else{
                     charaux.push_back(toupper(character));
                  }  
                  
               }
               
        // charaux_ant=charaux;
         //charaux.clear();      
         //charaux_ant=charaux;
         //  charaux.clear();
          
      }    
     // charaux.push_back(toupper(character));
        }
    file.close();
    }
    else{ //Para o caso do arquivo nao estar aberto

       cout <<"the file is not open"<<endl;
    }
    
    for (int j=0;j<object_counter.size();j++){ //Imprime os endereços na ordem necessária
        cout<<object_counter[j]<<" ";
    }
    
    return file;
}

#endif // READINGFILE_H_INCLUDED