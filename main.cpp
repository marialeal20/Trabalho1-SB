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
#include "ErrorAnalysis.h"
#include "SymbolsTable.h"

using namespace std;


int main(int argc, char *argv[]){
    //Declaração das variáveis
 
    char *filename;
    filename= argv[1];
    fstream fileasm;

    fileasm= openfile(filename);
    readfile(filename);
  
    return 0;

}
