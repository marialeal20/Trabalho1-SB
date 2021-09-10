#ifndef READFILE_H_INCLUDED
#define READFILE_H_INCLUDED
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <vector>
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
    int line=1;
    int label_vector=0, error_vector=0;
    char character;
    int count_opcode=0,count_address=0;
    vector <int> object_counter;
    bool include_data=false;


    file.open(name, ios::in); //modo de leitura de arquivo
    if (file.is_open())
    {
      //cout<<"fileopen"<<endl;
        while (file.get(character))
        {
            if (character == ' ' || character == '\n') //Separração entre tokens
            {
                 if (character =='\n'){
                     line++;
                  }
                 if (charaux.back() == ':' && include_data==true) //Verificação de Labels //se include data nao for true, tem que criar com endereço 0 e flag_pending true
                 {

                     testeflag=VerifyLabel(charaux); //Verifica se o nome das labels é válido, se sim, testeflag=true

                     if (testeflag==true){
                        labels[label_vector]=TS{false,charaux, count_address}; //Vetor de objetos 
                     }
                     else{
                         error_name[error_vector]= Errors{("Sintax Error", line,"Erro de sintaxe, verifique o nome de sua variável")}; //Erro para o caso de um nome de label inválido, objeto erro incluído no vetor de erros
                     }
                     charaux_ant=charaux;
                     charaux.clear();
                 }
                 else
                 {
                     if(charaux_ant=="SECTION"){
                         if (charaux=="TEXT"){
                            include_data=false;
                                 if (charaux == "ADD"){
                                    count_address=count_address+2;
                                    object_counter.push_back(01);
                                    
                                 }
                                 if(charaux=="SUB"){
                                    count_address=count_address+2;
                                    object_counter.push_back(02);
                                    
                                 }
                                 if(charaux=="MULT"){
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
                              }
                  else {
                     if(charaux =="DATA"){
                        include_data=true;
                         //Criar vetor para guardar as declarações que serão usadas ao final
                     //   cout<< "data aqui" << endl;
                     }
                  }
               }
                     //charaux_ant=charaux;
                    // charaux.clear();
            }
              /*   if (charaux == "ADD"){
                    count_address=count_address+2;
                    object_counter.push_back(01);
                  
                 }
                 if(charaux=="SUB"){
                    count_address=count_address+2;
                    object_counter.push_back(02);
                    
                 }
                 if(charaux=="MULT"){
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
                    
                 }*/
                
                charaux_ant=charaux;
                charaux.clear();
                     
                //cout << charaux << "\n";
                //charaux = "";
            }
            else
            {
                charaux.push_back(toupper(character));
            }
            //charaux_ant=charaux;
          //  charaux.clear();
       // }
          
     // charaux.push_back(toupper(character));
    }

  /* for (int i=0;i<charaux.size();i++){
        cout<<charaux[i]<<endl;
    }
    /*for(int J=0; J<=4; J++){
       cout<< "table : " << J << " label ->" << error_name[J].Error_msg <<endl;
    }*/

    file.close();
    
    }
    else{ //Para o caso do arquivo nao estar aberto

       cout <<"the file is not open"<<endl;
    }
    for (int i=0;i<object_counter.size();i++){
        cout<<object_counter[i]<<endl;
    }
    return file;
}

#endif // READINGFILE_H_INCLUDED