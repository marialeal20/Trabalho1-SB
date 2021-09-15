#ifndef SIMULADOR_H_INCLUDED
#define SIMULADOR_H_INCLUDED
#include "ReadFile.h"
#include <string.h>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>

class Sim
{
public:
    int pc;
    int line;
    string op;
    int address;
};

vector<Sim> Simulator;

class label_address_value
{
public:
    int value;
    int address;
};

vector<label_address_value> label_sim(vector<int> code)
{
    int y = 0;
    vector<label_address_value> vec_Label;
    for (int i = (signed)code.size(); i >= 0; i++)
    {
        if (code[i] == 14)
        {
            y = i;
            break;
        }
    }
    for (y; y > (signed)code.size(); y++)
    {
        label_address_value b;
        vec_Label.push_back(b);
        vec_Label[y].value = code[y];
        vec_Label[y].address = 0;
    }
    return vec_Label;
};

int findValue(int label, vector<label_address_value> label_vector)
{
    for (int x = 0; x < (signed)label_vector.size(); x++)
    {
        if (label == label_vector[x].address)
        {
            return label_vector[x].value;
        }
    }
    return 0;
}

int findPos(int label, vector<label_address_value> label_vector)
{
    for (int x = 0; x < (signed)label_vector.size(); x++)
    {
        if (label == label_vector[x].address)
        {
            return x;
        }
    }
    return 0;
}

fstream readfileobj(char *name)
{
    char character;
    string stringaux = "";
    string stringaux_ant = "";
    fstream fileobj;
    int pc = 0;
    int aux = 0, aux2 = 0;
    int acc = 0;
    int mem = 0;
    int code_address = 0;
    string op = "";
    vector<int> vectors;
    vector<label_address_value> vec_label;

    fileobj.open(name, ios::in); //modo de leitura de arquivo

    if (fileobj.is_open())
    {
        while (fileobj.get(character))
        {
            if (character == ' ' || character == '\n')
            {

                vectors.push_back(atoi(stringaux.c_str()));
                stringaux_ant = stringaux;
                stringaux.clear();
            }
            else
            {
                stringaux.push_back(toupper(character));
            }
        }

        int first_label = 0;
        int second_label = 0;
        int i = 0, j = 0;
        bool stop = false;
        while (i < (signed)vectors.size())
        {
            switch (vectors[i])
            {
            case 1:
                code_address = code_address + 2;
                pc = pc + 2;
                first_label = vectors[i + 1];
                second_label = 0;
                acc = acc + mem;
                op = "ADD";
                i = i + 2;
                break;
            case 2:
                code_address = code_address + 2;
                first_label = vectors[i + 1];
                second_label = 0;
                acc = acc + mem;
                op = "SUB";
                i = i + 2;
                break;
            case 3:
                code_address = code_address + 2;
                first_label = vectors[i + 1];
                second_label = 0;
                acc = acc + mem;
                op = "MUL";
                i = i + 2;
                break;
            case 4:
                code_address = code_address + 2;
                first_label = vectors[i + 1];
                second_label = 0;
                acc = acc / mem;
                op = "DIV";
                i = i + 2;
                break;
            case 5:
                code_address = code_address + 2;
                first_label = vectors[i + 1];
                second_label = 0;
                aux = i;
                op = "JMP";
                i = findValue(first_label, vec_label);
                //  i = i + 2;
                break;
            case 6:
                code_address = code_address + 2;
                first_label = vectors[i + 1];
                second_label = 0;
                op = "JMPN";
                if (acc < 0)
                {
                    aux = i;
                    i = findValue(first_label, vec_label);
                }
                // i = i + 2;
                break;
            case 7:
                code_address = code_address + 2;
                first_label = vectors[i + 1];
                second_label = 0;
                op = "JMPP";
                if (acc > 0)
                {
                    aux = i;
                    i = findValue(first_label, vec_label);
                }

                // i = i + 2;
                break;
            case 8:
                code_address = code_address + 2;
                first_label = vectors[i + 1];
                second_label = 0;
                op = "JMPZ";
                if (acc == 0)
                {
                    aux = i;
                    i = findValue(first_label, vec_label);
                }
                // i = i + 2;
                break;
            case 9:
                code_address = code_address + 2;
                first_label = vectors[i + 1];
                second_label = vectors[i + 2];
                aux = findPos(second_label, vec_label);
                aux2 = findPos(first_label, vec_label);
                vec_label[aux].value = vec_label[aux2].value;
                op = "COPY";
                i = i + 3;
                break;
            case 10:
                code_address = code_address + 2;
                first_label = vectors[i + 1];
                second_label = 0;
                acc = mem;
                op = "LOAD";
                i = i + 2;
                break;
            case 11:
                code_address = code_address + 2;
                first_label = vectors[i + 1];
                second_label = 0;
                mem = acc;
                op = "STORE";
                i = i + 2;
                break;
            case 12:
                code_address = code_address + 2;
                first_label = vectors[i + 1];
                second_label = 0;
                op = "INPUT";
                cin >> vec_label[findPos(first_label, vec_label)].value;
                i = i + 2;
                break;
            case 13:
                code_address = code_address + 2;
                first_label = vectors[i + 1];
                second_label = 0;
                //cout << mem << endl;
                op = "OUTPUT";
                i = i + 2;

                char waiting;
                while (true)
                {
                    waiting = getchar();
                    if (waiting == '\n')
                    {
                        cout << mem << endl;

                        break;
                    }
                }
            case 14:
                first_label = 0;
                second_label = 0;
                code_address = code_address + 1;
                stop = true;
                op = "STOP";
                j = i;
                i++;
                break;
            }
            if (stop == true)
            {
                break;
            }

            cout << "******************" << endl;
            cout << "OP: " << op << " ACC: " << acc << " Pc: " << i << endl;
            cout << "*****************" << endl;
        }

        vector<label_address_value> a;
        int p = 0;
        for (j; j < (signed)vectors.size(); j++)
        {

            label_address_value label_values;
            a.push_back(label_values);
            a[p].value = vectors[j];
            a[p].address = code_address;
            code_address++;
            p++;
        }

        fileobj.close();
    }
    else
    {
        cout << "arquivo nao pode ser aberto" << endl;
    }
    return fileobj;
}

#endif // SIMULADOR_H_INCLUDED