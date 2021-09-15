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
   fileasm.close();
   return fileasm;
}

ofstream readfile(char *name)
{
   //Declaração de Variáveis
   fstream file;
   ofstream file_obj;

   string charaux = "";
   string charaux_ant = "";
   string char_label_const = "";
   string namefile1 = "";

   bool testeflag;
   bool include_data = false;
   bool exist = false;
   bool data_first = true;
   bool flag_comment = false;

   int line = 1;
   int label_vector = 0, error_vector = 0;
   int count_address = 0;

   char character;

   vector<string> labelsectiondata;
   vector<int> object_counter;
   vector<string> vec_aux;

   file.open(name, ios::in); //modo de leitura de arquivo

   if (file.is_open())
   {
      while (file.get(character)) //Pega caractere por caractere do arquivo
      {
         if (character == '\n')
         { //Somatório das linhas
            line++;
         }

         if (character == ';')
         { //Flag para definir inicio de comentário
            flag_comment = true;
         }

         if (flag_comment == true && character == '\n')
         { //Flag que define o final do comentário
            flag_comment = false;
         }

         if (character == ' ' || character == '\n')
         { //Separação entre tokens

            // cout << "charaux:"<< charaux << endl; //Imprime os tokens

            if (charaux.front() == '1' || charaux.front() == '2' || charaux.front() == '3' || charaux.front() == '4' || charaux.front() == '5' || charaux.front() == '6' || charaux.front() == '7' || charaux.front() == '8' || charaux.front() == '9' || charaux.front() == '0')
            {
               for (int i = 0; i < (signed)labels.size(); i++)
               { //Valor a ser colocado no .obj para casos de const
                  if (labels[i].name_symbol == char_label_const)
                  {
                     labels[i].vector_symbols = charaux;
                  }
               }
            }

            if (charaux.back() == ':' && include_data == false)
            {                                    //Verificação de Labels - Código começa no Section Text
               charaux.pop_back();               //Retira os dois pontos
               testeflag = VerifyLabel(charaux); //Verifica se o nome das labels é válido, se sim, testeflag=true

               if (testeflag == true)
               {
                  if (!verifyTS(labels, charaux))
                  {
                     TS label_token;                //Objeto que representa uma label
                     labels.push_back(label_token); //Vetor de objetos Label
                     labels[label_vector].flag_pending = false;
                     labels[label_vector].name_symbol = charaux;
                     labels[label_vector].address = count_address;
                     labels[label_vector].value = "none";
                     labels[label_vector].vector_symbols = count_address;
                     labels[label_vector].line = line;

                     label_vector++;
                  }
               }

               else
               {                                       //Se o nome for inválido, ele cria um objeto no vetor de erros
                  Errors errordetected;                //Objeto do tipo Erro
                  error_name.push_back(errordetected); //Acrescenta um objeto no vetor de labels
                  error_name[error_vector].Error_name = "Sintax Error";
                  error_name[error_vector].Error_line = line;
                  error_name[error_vector].Error_msg = "Sintax Eror, verify your variable - " + charaux; //Erro para o caso de um nome de label inválido, objeto erro incluído no vetor de erros
               }

               if (charaux != "")
               { //Se o token não for vazio, salva o token atual e limpa a string para receber o próximo token
                  charaux_ant = charaux;
               }
               charaux.clear();
            }

            if (charaux.back() == ':' && include_data == true)
            { //Verificação de Labels - se o SECTION DATA vier primeiro

               charaux.pop_back();               //Tira os :
               testeflag = VerifyLabel(charaux); //Verifica se o nome das labels é válido, se sim, testeflag=true
               if (testeflag == true)
               {
                  if (!verifyTS(labels, charaux))
                  { //Vetor de objetos
                     TS label_token;
                     labels.push_back(label_token);
                     labels[label_vector].flag_pending = true;
                     labels[label_vector].name_symbol = charaux;
                     labels[label_vector].address = 0;
                     labels[label_vector].value = " ";
                     labels[label_vector].vector_symbols = "0";
                     labels[label_vector].line = line;

                     label_vector++;
                  }
               }

               else
               {
                  Errors errordetected; //Se o nome da label for inválido, ele adiciona no vetor de erros
                  error_name.push_back(errordetected);
                  error_name[error_vector].Error_name = "Sintax Error";
                  error_name[error_vector].Error_line = line;
                  error_name[error_vector].Error_msg = "Sintax Eror, verify your variable -" + charaux;
               }

               if (charaux != "")
               { //Se a string nao for vazio, salva o token e depois apaga para receber outro
                  charaux_ant = charaux;
                  charaux.clear();
               }
            }

            /*******Se não acabar em dois pontos, ou seja, se não for uma Label ele: *********/

            else
            { //Verifica se está na etapa de texto ou de data para definir se as labels são pendentes ou não
               if (charaux_ant == "SECTION")
               { //Para a verificação de endereço de labels
                  if (charaux == "TEXT")
                  {
                     include_data = false;
                  }

                  else if (charaux == "DATA")
                  {
                     include_data = true;
                  }
               }
            }

            for (int i = 0; i < (signed)labels.size(); i++)
            { //Verifica se o Token já está cadastrado na tabela de simbolos
               if (charaux == labels[i].name_symbol)
               {
                  exist = true;
               }
            }

            if (charaux == "ADD")
            { //Adiciona no endereço, acrescenta o valor 1 no vetor a ser impresso ao final e acrescenta ao vetor auxiliar
               count_address = count_address + 2;
               object_counter.push_back(1);
               vec_aux.push_back(charaux);
            }
            else if (charaux == "SUB")
            { //Adiciona no endereço, acrescenta o valor 2 no vetor a ser impresso ao final e acrescenta ao vetor auxiliar
               count_address = count_address + 2;
               object_counter.push_back(2);
               vec_aux.push_back(charaux);
            }
            else if (charaux == "MUL")
            { //Adiciona no endereço, acrescenta o valor 3 no vetor a ser impresso ao final e acrescenta ao vetor auxiliar
               count_address = count_address + 2;
               object_counter.push_back(3);
               vec_aux.push_back(charaux);
            }
            else if (charaux == "DIV")
            { //Adiciona no endereço, acrescenta o valor 4 no vetor a ser impresso ao final e acrescenta ao vetor auxiliar
               count_address = count_address + 2;
               object_counter.push_back(4);
               vec_aux.push_back(charaux);
            }
            else if (charaux == "JMP")
            { //Adiciona no endereço, acrescenta o valor 5 no vetor a ser impresso ao final e acrescenta ao vetor auxiliar
               count_address = count_address + 2;
               object_counter.push_back(5);
               vec_aux.push_back(charaux);
               cout << count_address << endl;
               cout << charaux << endl;
            }
            else if (charaux == "JMPN")
            { //Adiciona no endereço, acrescenta o valor 6 no vetor a ser impresso ao final e acrescenta ao vetor auxiliar
               count_address = count_address + 2;
               object_counter.push_back(6);
               vec_aux.push_back(charaux);
            }
            else if (charaux == "JMPP")
            { //Adiciona no endereço, acrescenta o valor 7 no vetor a ser impresso ao final e acrescenta ao vetor auxiliar
               count_address = count_address + 2;
               object_counter.push_back(7);
               vec_aux.push_back(charaux);
            }
            else if (charaux == "JMPZ")
            { //Adiciona no endereço, acrescenta o valor 8 no vetor a ser impresso ao final e acrescenta ao vetor auxiliar
               count_address = count_address + 2;
               object_counter.push_back(8);
               vec_aux.push_back(charaux);
            }
            else if (charaux == "COPY")
            { //Adiciona no endereço, acrescenta o valor 9 no vetor a ser impresso ao final e acrescenta ao vetor auxiliar
               count_address = count_address + 3;
               object_counter.push_back(9);
               vec_aux.push_back(charaux);
            }
            else if (charaux == "LOAD")
            { //Adiciona no endereço, acrescenta o valor 10 no vetor a ser impresso ao final e acrescenta ao vetor auxiliar
               count_address = count_address + 2;
               object_counter.push_back(10);
               vec_aux.push_back(charaux);
            }
            else if (charaux == "STORE")
            { //Adiciona no endereço, acrescenta o valor 11 no vetor a ser impresso ao final e acrescenta ao vetor auxiliar
               count_address = count_address + 2;
               object_counter.push_back(11);
               vec_aux.push_back(charaux);
            }
            else if (charaux == "INPUT")
            { //Adiciona no endereço, acrescenta o valor 12 no vetor a ser impresso ao final e acrescenta ao vetor auxiliar
               count_address = count_address + 2;
               object_counter.push_back(12);
               vec_aux.push_back(charaux);
            }
            else if (charaux == "OUTPUT")
            { //Adiciona no endereço, acrescenta o valor 13 no vetor a ser impresso ao final e acrescenta ao vetor auxiliar
               count_address = count_address + 2;
               object_counter.push_back(13);
               vec_aux.push_back(charaux);
            }
            else if (charaux == "STOP")
            { //Adiciona no endereço, acrescenta o valor 14 no vetor a ser impresso ao final e acrescenta ao vetor auxiliar
               count_address++;
               object_counter.push_back(14);
               vec_aux.push_back(charaux);
            }
            else if (charaux == "CONST")
            { //Se for const ele verifica na tabela de símbolos o token que condiz com ele e guarda o valor anterior (nome da label) para acrescentar ao final no código obj
               for (int y = 0; y < (signed)labels.size(); y++)
               {
                  if (charaux_ant == labels[y].name_symbol)
                  {
                     labels[y].value = charaux;
                     labels[y].vector_symbols = "1000";
                     char_label_const = charaux_ant;
                  }
               }
            }
            else if (charaux == "SPACE")
            { //Se for Space ele coloca no valor a ser impresso do endereço do token no valor específico
               for (int y = 0; y < (signed)labels.size(); y++)
               {
                  if (charaux_ant == labels[y].name_symbol)
                  {
                     labels[y].value = charaux;
                     labels[y].vector_symbols = "0";
                  }
               }
            }
            else if (charaux == "SECTION" || charaux == "TEXT" || charaux == "DATA")
            { //Eliminando todos os tokens conhecidos para restar os tokens que são labels
            }
            else if (charaux.front() == '1' || charaux.front() == '2' || charaux.front() == '3' || charaux.front() == '4' || charaux.front() == '5' || charaux.front() == '6' || charaux.front() == '7' || charaux.front() == '8' || charaux.front() == '9' || charaux.front() == '0')
            { //Eliminando números também
            }
            else if (exist)
            {
               exist = false;
            }
            else if (charaux == "")
            {
            }
            else
            {
               if (!verifyTS(labels, charaux))
               {
                  //object_counter.push_back(0);
                  // vec_aux.push_back(charaux);

                  testeflag = VerifyLabel(charaux); //Verifica se o nome das labels é válido, se sim, testeflag=true
                  if (testeflag == true)
                  { //Vetor de objetos
                     TS label_token;
                     labels.push_back(label_token);
                     labels[label_vector].flag_pending = true;
                     labels[label_vector].name_symbol = charaux;
                     labels[label_vector].address = 0;
                     labels[label_vector].value = " ";
                     labels[label_vector].vector_symbols = "0";
                     labels[label_vector].line = line;

                     label_vector++;
                  }
               }
            }

            //Verificar as labels e colocar os endereços, se nao tiver pendente bota o endereço senão, é colocado um valor hipotético
            for (int i = 0; i < (signed)labels.size(); i++)
            {
               if (labels[i].name_symbol == charaux)
               {
                  if (labels[i].flag_pending == false)
                  {
                     object_counter.push_back(labels[i].address);
                     vec_aux.push_back(charaux);
                  }
                  else
                  {
                     object_counter.push_back(10000);
                     vec_aux.push_back(charaux);
                  }
               }
            }

            if (charaux != "")
            {
               charaux_ant = charaux;
            }
            charaux.clear();
         }

         else
         {
            if (character == ',')
            {
               if (data_first == true)
               {
                  for (int i = 0; i < (signed)labels.size(); i++)
                  {
                     if (labels[i].name_symbol == charaux)
                     {
                        if (labels[i].flag_pending == false)
                        {
                           object_counter.push_back(labels[i].address);
                        }
                        else
                        {
                           object_counter.push_back(10000);
                           vec_aux.push_back(charaux);
                        }
                        if (charaux != "")
                        {
                           charaux_ant = charaux;
                        }
                        charaux.clear();
                     }
                  }
               }
               else if (!verifyTS(labels, charaux))
               {
                  object_counter.push_back(0);
                  vec_aux.push_back(charaux);
                  if (charaux != "")
                  {
                     charaux_ant = charaux;
                     charaux.clear();
                  }
               }
            }
            else
            {
               if (flag_comment == false)
               {
                  charaux.push_back(toupper(character));
               }
            }
         }
      }
      if (sameLineLabel(labels) == 1)
      {
         Errors errordetected;
         error_name.push_back(errordetected);
         error_name[error_vector].Error_name = "Sintatic Error";
         error_name[error_vector].Error_line = line;
         error_name[error_vector].Error_msg = "Erro sintático, não é possível declarar duas labels em uma mesma linha";
      }

      if (sameNameLabel(labels) == 1)
      {
         Errors errordetected;
         error_name.push_back(errordetected);
         error_name[error_vector].Error_name = "Sintatic Error";
         error_name[error_vector].Error_line = line;
         error_name[error_vector].Error_msg = "Erro sintatico, esta label já foi declarada anteriormente";
      }

      if (!verifyLabel)
      {
         Errors errordetected;
         error_name.push_back(errordetected);
         error_name[error_vector].Error_name = "Semantic Error";
         error_name[error_vector].Error_line = line;
         error_name[error_vector].Error_msg = "Erro semantico, algumas labels já foram declarada";
      }

      if (charaux == "ADD")
      {
         count_address = count_address + 2;
         object_counter.push_back(01);
         vec_aux.push_back(charaux);
      }
      if (charaux == "SUB")
      {
         count_address = count_address + 2;
         object_counter.push_back(02);
         vec_aux.push_back(charaux);
      }
      if (charaux == "MUL")
      {
         count_address = count_address + 2;
         object_counter.push_back(03);
         vec_aux.push_back(charaux);
      }
      if (charaux == "DIV")
      {
         count_address = count_address + 2;
         object_counter.push_back(04);
         vec_aux.push_back(charaux);
      }
      if (charaux == "JMP")
      {
         count_address = count_address + 2;
         object_counter.push_back(05);
         vec_aux.push_back(charaux);
      }
      if (charaux == "JMPN")
      {
         count_address = count_address + 2;
         object_counter.push_back(06);
         vec_aux.push_back(charaux);
      }
      if (charaux == "JMPP")
      {
         count_address = count_address + 2;
         object_counter.push_back(07);
         vec_aux.push_back(charaux);
      }
      if (charaux == "JMPZ")
      {
         count_address = count_address + 2;
         object_counter.push_back(8);
         vec_aux.push_back(charaux);
      }
      if (charaux == "COPY")
      {
         count_address = count_address + 3;
         object_counter.push_back(9);
         vec_aux.push_back(charaux);
      }
      if (charaux == "LOAD")
      {
         count_address = count_address + 2;
         object_counter.push_back(10);
         vec_aux.push_back(charaux);
      }
      if (charaux == "STORE")
      {
         count_address = count_address + 2;
         object_counter.push_back(11);
         vec_aux.push_back(charaux);
      }
      if (charaux == "INPUT")
      {
         count_address = count_address + 2;
         object_counter.push_back(12);
         vec_aux.push_back(charaux);
      }
      if (charaux == "OUTPUT")
      {
         count_address = count_address + 2;
         object_counter.push_back(13);
         vec_aux.push_back(charaux);
      }
      if (charaux == "STOP")
      {
         object_counter.push_back(14);
         vec_aux.push_back(charaux);
      }
      if (charaux == "CONST")
      {
         for (int y = 0; y < (signed)labels.size(); y++)
         {
            if (charaux_ant == labels[y].name_symbol)
            {
               labels[y].value = charaux;
               labels[y].vector_symbols = "1000";
               char_label_const = charaux_ant;
            }
         }
      }
      if (charaux == "SPACE")
      {
         for (int y = 0; y < (signed)labels.size(); y++)
         {
            if (charaux_ant == labels[y].name_symbol)
            {
               labels[y].value = charaux;
               labels[y].vector_symbols = "0";
            }
         }
      }
      file.close();
   }
   else
   { //Para o caso do arquivo nao estar aberto

      cout << "the file is not open" << endl;
   }

   char *namefile = strtok(name, ".");
   namefile1.append(namefile);
   namefile1.append(".obj");
   file_obj.open(namefile1, ios::out);

   if (file_obj.is_open())
   {

      if (error_name.empty())
      { //Se o código não tem erros
         for (int i = 0; i < (signed)labels.size(); i++)
         {
            if (labels[i].flag_pending == true)
            {
               count_address++;
               labels[i].address = count_address;
            }
         }

         for (int x = 0; x < (signed)vec_aux.size(); x++)
         {
            for (int j = 0; j < labels.size(); j++)
            {
               if (vec_aux[x] == labels[j].name_symbol)
               {
                  object_counter[x] = labels[j].address;
               }
            }
         }

         for (int j = 0; j < (signed)object_counter.size(); j++)
         { //Imprime os endereços na ordem necessária
            file_obj << object_counter[j] << " ";
         }
         for (int j = 0; j < (signed)labels.size(); j++)
         {
            if (labels[j].flag_pending == true)
            {
               file_obj << labels[j].vector_symbols << " ";
            }
         }
         file_obj.close();
      }

      else
      {
         for (int i = 0; (signed)i < (signed)error_name.size(); i++)
         {
            file_obj << "Error:" << error_name[i].Error_msg << " Line: " << error_name[i].Error_line << endl;
         }
         file_obj.close();
      }
   }
   else
   {
      cout << "can't open file" << endl;
   }
   return file_obj;
}

#endif // READINGFILE_H_INCLUDED