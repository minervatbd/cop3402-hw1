#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "machine_main.h"
#include "utilities.h"
#include "machine.h"

int main(int argc, char** argv){

//check input was provided
if(argc == 1){
    bail_with_error("Must supply command line arguments.\n");
}
//vars for storing inputs
char* filename;
int printModeBool = 0;
//parse mode and store values appropriately 
if(!strcmp(argv[1],"-p")){
    printModeBool = 1;
    
    if(argc > 2){
        filename = (char*) malloc(sizeof(argv[2]));
        strcpy(filename, argv[2]);
    } else bail_with_error("Must supply command line arguments.\n");
} else{
    filename = (char*) malloc(sizeof(argv[1]));
    strcpy(filename, argv[1]);
}


machine(printModeBool, filename);

}
