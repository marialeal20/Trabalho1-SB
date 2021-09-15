#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <list>
#include <istream>
#include "ReadFile.h"
#include "Simulador.h"
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    //Declaração das variáveis

    char *file_obj_name;
    file_obj_name = argv[1];
    fstream fileobj;
    readfileobj(file_obj_name);

    return 0;
}
