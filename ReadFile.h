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
    fstream file_obj;
    string charaux = "";
    string charaux_ant="";
    string char_label_const ="";
    
    bool testeflag;
    bool include_data=false;
    bool exist=false;
    bool data_first=false;
    bool flag_comment=false;
    bool flag_error =false;
   // bool const_true=false;
    int line=1;
    int label_vector=0, error_vector=0;
    int count_opcode=0,count_address=0;

    char character;

    vector <string> labelsectiondata;
    vector <int> object_counter;
    vector <string> vec_aux;
    //char* namefile;
    string namefile1="";
    
    file.open(name, ios::in); //modo de leitura de arquivo
    if (file.is_open())
    {
        while (file.get(character)) //Pega caractere por caractere do arquivo
        {
         //  cout << character << endl;
          if (character =='\n'){
                     line++;
                     
                  }
                  if (character==';'){
                     flag_comment=true;
                    
                  }
                  if(flag_comment==true && character=='\n'){
                     flag_comment=false;
                     
                  }

         if (character == ' ' || character == '\n'){ //Separação entre tokens
              // cout << "charaux:"<< charaux << endl;
                

            if(charaux.front()=='1'||charaux.front()=='2'||charaux.front()=='3'||charaux.front()=='4'||charaux.front()=='5'||charaux.front()=='6'||charaux.front()=='7'|| charaux.front()=='8'||charaux.front()=='9'|| charaux.front()=='0'){
            for (int i=0; i<labels.size(); i++){
               if(labels[i].name_symbol==char_label_const){
              //   // cout<<labels[i].name_symbol<<endl;
                  labels[i].vector_symbols=charaux;
               }
            }
           // const_true=false;
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
                        labels[label_vector].value="none"; 
                        labels[label_vector].vector_symbols=count_address;
                        labels[label_vector].line=line;

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

                     if (charaux != ""){
                        charaux_ant=charaux;}
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
                     labels[label_vector].value=" ";
                     labels[label_vector].vector_symbols="0"; 
                     labels[label_vector].line=line;

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
                     if (charaux != ""){
                     charaux_ant=charaux;}
                     charaux.clear();
                 }
                 else //Verifica se está na etapa de texto ou de data para definir se as labels são pendentes ou não
                 {
                     if(charaux_ant=="SECTION"){ //Para a verificação de endereço de labels 
                         if (charaux=="TEXT"){
                           // cout << "hey there"<<endl;
                            include_data=false;
                            
                        }
                     else {
                        if(charaux =="DATA"){
                           include_data=true;
                           data_first=true;
                         //Criar vetor para guardar as declarações que serão usadas ao final
                        }
                     }
                     }
                     //charaux_ant=charaux;
                    // charaux.clear();
                  }

               for (int i=0;i<labels.size();i++){
                  if (charaux== labels[i].name_symbol){
                     exist=true;
                  }
               }
                 if (charaux == "ADD"){
                    count_address=count_address+2;
                    object_counter.push_back(01);
                    vec_aux.push_back(charaux);
                 }
                 else if(charaux=="SUB"){
                    count_address=count_address+2;
                    object_counter.push_back(02);
                    vec_aux.push_back(charaux);
                 }
                 else if(charaux=="MUL"){
                    count_address=count_address+2;
                    object_counter.push_back(03);
                    vec_aux.push_back(charaux);
                 }
                 else if (charaux=="DIV"){
                    count_address=count_address+2;
                    object_counter.push_back(04);
                    vec_aux.push_back(charaux);
                 }
                 else if(charaux=="JMP"){
                    count_address=count_address+2;
                    object_counter.push_back(05);  
                    vec_aux.push_back(charaux);
                 }
                 else if(charaux=="JMPN"){
                    count_address=count_address+2;
                    object_counter.push_back(06);  
                    vec_aux.push_back(charaux);
                 }
                 else if(charaux=="JMPP"){
                    count_address=count_address+2;
                    object_counter.push_back(07);
                    vec_aux.push_back(charaux);
                 }
                 else if(charaux=="JMPZ"){
                    count_address=count_address+2;
                    object_counter.push_back(8);
                    vec_aux.push_back(charaux);
                 }
                 else if(charaux=="COPY"){
                    count_address=count_address+2;
                    object_counter.push_back(9);  
                    vec_aux.push_back(charaux);
                 }
                 else if(charaux=="LOAD"){
                    count_address=count_address+2;
                    object_counter.push_back(10);
                    vec_aux.push_back(charaux);
                 }
                 else if(charaux=="STORE"){
                    count_address=count_address+2;
                    object_counter.push_back(11);
                    vec_aux.push_back(charaux);
                 }
                 else if(charaux =="INPUT"){
                    count_address=count_address+2;
                    object_counter.push_back(12);
                    vec_aux.push_back(charaux);
                 }
                 else if(charaux=="OUTPUT"){
                    count_address=count_address+2;
                    object_counter.push_back(13);
                    vec_aux.push_back(charaux);
                 }
                 else if(charaux=="STOP"){
                    count_address=count_address+1;
                    object_counter.push_back(14);
                    vec_aux.push_back(charaux);
                 }
                 else if (charaux=="CONST"){
                  //  cout<<"hello"  <<endl;
                    for (int y=0; y< labels.size();y++){
                       //cout <<"charaux_ant **: " << charaux_ant<<endl;
                     //  cout<<"charaux **: " << charaux <<endl;
                       if (charaux_ant==labels[y].name_symbol){
                          labels[y].value=charaux;
                          labels[y].vector_symbols="1000";
                        //  const_true=true;
                          char_label_const= charaux_ant;
                       }
                    }
                 }
                 else if (charaux=="SPACE"){
                    for (int y=0; y< labels.size();y++){
                       if (charaux_ant==labels[y].name_symbol){
                          labels[y].value=charaux;
                          labels[y].vector_symbols="0";
                        //  const_true=true;
                       }
                    }
                 }
                  else if (charaux=="SECTION"||charaux=="TEXT"|| charaux=="DATA"){

                  }
                  else if(charaux.front()=='1'||charaux.front()=='2'||charaux.front()=='3'||charaux.front()=='4'||charaux.front()=='5'||charaux.front()=='6'||charaux.front()=='7'|| charaux.front()=='8'||charaux.front()=='9'|| charaux.front()=='0'){

                  }
                  else if(exist){
                     //cout<<"exist: "<<charaux<<endl;
                     exist=false;
                  }
                  else if(charaux==""){

                  }
                 else{

                    object_counter.push_back(0);
                    vec_aux.push_back(charaux);
                   // cout<<"else: "<<charaux<<endl;

                  /*
                  testeflag=VerifyLabel(charaux); //Verifica se o nome das labels é válido, se sim, testeflag=true
                     if (testeflag==true){//Vetor de objetos
                     TS label_token;
                     labels.push_back(label_token);
                     labels[label_vector].flag_pending=true;
                     labels[label_vector].name_symbol=charaux;
                     labels[label_vector].address= 0;
                     labels[label_vector].value=" ";
                     labels[label_vector].vector_symbols="0"; 
                     labels[label_vector].line=line;

                     label_vector++;  
                     }*/


                 }

                 //Verificar as labels e colocar os endereços, se nao tiver pendente bota o endereço, se estiver, bota 1000 (teste)
                for (int i=0; i<labels.size(); i++){
                    if (labels[i].name_symbol== charaux){
                        if(labels[i].flag_pending==false){
                          object_counter.push_back(labels[i].address);
                          vec_aux.push_back(charaux);
                        //  cout <<"name symbol" <<labels[i].name_symbol <<endl;
                       }
                       else{
                          object_counter.push_back(10000);
                          vec_aux.push_back(charaux);
                        //  cout <<"name symbol" <<labels[i].name_symbol <<endl;
                       }
                    }
                 }
                if (charaux != ""){
                        charaux_ant=charaux;}
                charaux.clear();    
                //cout << charaux << "\n";
                //charaux = "";
            }
            
            else
            {
               if (character==','){
                  //cout <<"virgula:" << charaux<<endl;
                  if (data_first==true){
                  for (int i=0; i<labels.size(); i++){
                    if (labels[i].name_symbol== charaux){
                        if(labels[i].flag_pending==false){
                          object_counter.push_back(labels[i].address);
                        //  cout <<"name symbol" <<labels[i].name_symbol <<endl;
                       }
                       else{
                     object_counter.push_back(10000);
                     vec_aux.push_back(charaux);
                     //cout <<"name symbol" <<labels[i].name_symbol <<endl;
                     }
                     if (charaux != ""){
                        charaux_ant=charaux;}
                     charaux.clear();
                        
                       }
                       
                       }} 
                  else{
                     object_counter.push_back(0);
                     vec_aux.push_back(charaux);
                      if (charaux != ""){
                        charaux_ant=charaux;
                     charaux.clear();
                  }
                       }}
               else{
                 /* if (file.eof()){
                     cout << "the end" << charaux << endl;
                     charaux.push_back(toupper(character));
                  }
                  else{*/
                  if(flag_comment==false){
                     charaux.push_back(toupper(character));
                  }
                 

                     
                //  }  
                  
               }
               
        // charaux_ant=charaux;
         //charaux.clear();      
         //charaux_ant=charaux;
         //  charaux.clear();
         // cout << charaux << endl;
      } }   
     // charaux.push_back(toupper(character));
   //  cout <<"charaux_ant: " << charaux_ant<<endl;
    //                   cout<<"charaux: " << charaux <<endl;
      if (sameLineLabel(labels)==1){
         Errors errordetected;
         error_name.push_back(errordetected);
         error_name[error_vector].Error_name="Sintatic Error";
         error_name[error_vector].Error_line=line;
         error_name[error_vector].Error_msg="Erro sintático, não é possível declarar duas labels em uma mesma linha";
        // cout <<"erro"<<endl;
      }

      if (sameNameLabel(labels)==1){
         Errors errordetected;
         error_name.push_back(errordetected);
         error_name[error_vector].Error_name="Sintatic Error";
         error_name[error_vector].Error_line=line;
         error_name[error_vector].Error_msg="Erro sintatico, esta label já foi declarada anteriormente";
        // cout <<"erro"<<endl;
      }


                 if (charaux == "ADD"){
                    count_address=count_address+2;
                    object_counter.push_back(01);
                    vec_aux.push_back(charaux);
                 }
                 if(charaux=="SUB"){
                    count_address=count_address+2;
                    object_counter.push_back(02);
                    vec_aux.push_back(charaux);
                 }
                 if(charaux=="MUL"){
                    count_address=count_address+2;
                    object_counter.push_back(03);
                    vec_aux.push_back(charaux);
                 }
                 if (charaux=="DIV"){
                    count_address=count_address+2;
                    object_counter.push_back(04);
                    vec_aux.push_back(charaux);
                 }
                 if(charaux=="JMP"){
                    count_address=count_address+2;
                    object_counter.push_back(05);
                    vec_aux.push_back(charaux);  
                 }
                 if(charaux=="JMPN"){
                    count_address=count_address+2;
                    object_counter.push_back(06);
                    vec_aux.push_back(charaux);  
                 }
                 if(charaux=="JMPP"){
                    count_address=count_address+2;
                    object_counter.push_back(07);
                    vec_aux.push_back(charaux);
                 }
                 if(charaux=="JMPZ"){
                    count_address=count_address+2;
                    object_counter.push_back(8);
                    vec_aux.push_back(charaux);
                 }
                 if(charaux=="COPY"){
                    count_address=count_address+2;
                    object_counter.push_back(9);  
                    vec_aux.push_back(charaux);
                 }
                 if(charaux=="LOAD"){
                    count_address=count_address+2;
                    object_counter.push_back(10);
                    vec_aux.push_back(charaux);
                 }
                 if(charaux=="STORE"){
                    count_address=count_address+2;
                    object_counter.push_back(11);
                    vec_aux.push_back(charaux);
                 }
                 if(charaux =="INPUT"){
                    count_address=count_address+2;
                    object_counter.push_back(12);
                    vec_aux.push_back(charaux);
                 }
                 if(charaux=="OUTPUT"){
                    count_address=count_address+2;
                    object_counter.push_back(13);
                    vec_aux.push_back(charaux);
                 }
                 if(charaux=="STOP"){
                    count_address=count_address+1;
                    object_counter.push_back(14);
                    vec_aux.push_back(charaux);
                 }
                  if (charaux=="CONST"){
                    for (int y=0; y< labels.size();y++){
                       cout <<"charaux_ant: " << charaux_ant<<endl;
                       cout<<"charaux: " << charaux <<endl;
                       if (charaux_ant==labels[y].name_symbol){
                          labels[y].value=charaux;
                          labels[y].vector_symbols="1000";
                        //  const_true=true;
                          char_label_const= charaux_ant;
                       }
                    }
                 }
                 if (charaux=="SPACE"){
                    for (int y=0; y< labels.size();y++){
                       if (charaux_ant==labels[y].name_symbol){
                          labels[y].value=charaux;
                          labels[y].vector_symbols="0";
                        //  const_true=true;
                       }
                    }
                 }

  /* for(int x=0;x<labels.size(); x++){
      if (labels[x].flag_pending == true){


      }*/
  // }

    file.close();
    }
    else{ //Para o caso do arquivo nao estar aberto

       cout <<"the file is not open"<<endl;
    }
     for (int i=0; i<labels.size();i++){
      if(labels[i].flag_pending==true){
         count_address++;
      labels[i].address=count_address;
      //object_counter.push_back(labels[i].address);
      //labels[i].flag_pending=false;
      }
      
   }

   //cout << "*"<<vec_aux.size() <<" "<<object_counter.size()<< endl ;

   for (int x=0; x<vec_aux.size();x++){
      for (int j=0;j<labels.size();j++){
         if (vec_aux[x]==labels[j].name_symbol){
            object_counter[x]=labels[j].address;
            

         }
      }
   }
  

    for (int j=0;j<object_counter.size();j++){ //Imprime os endereços na ordem necessária
        cout<<object_counter[j]<<" ";
    }

    for (int j=0; j<labels.size();j++){
       if(labels[j].flag_pending==true){
         // cout << labels[j].name_symbol<<" ";
          cout << labels[j].vector_symbols<<" ";
       }
    }
/*
   char *namefile=strtok(name,".");
 //  cout << namefile <<endl;
   namefile1.append(namefile);
   namefile1.append(".obj");
 //  cout <<namefile1 <<endl;
   file_obj.open(namefile1, ios::out);

   if(file_obj.is_open()){

      for (int i=0; i<labels.size();i++){
      if(labels[i].flag_pending==true){
         count_address++;
      labels[i].address=count_address;
      //object_counter.push_back(labels[i].address);
      //labels[i].flag_pending=false;
      }}
      for (int j=0;j<object_counter.size();j++){ //Imprime os endereços na ordem necessária
        cout<<object_counter[j]<<" ";
    }
    for (int j=0; j<labels.size();j++){
       if(labels[j].flag_pending==true){
         // cout << labels[j].name_symbol<<" ";
          cout << labels[j].vector_symbols<<" ";
       }
    }
    file_obj.close();
   }*/
    return file;
}

#endif // READINGFILE_H_INCLUDED