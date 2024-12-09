#include "Response.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * render_static_file(char *filename){
    FILE * file = fopen(filename, "r");

    if(file == NULL){
        return NULL;
    }
    else{
        print("%s does exist\n", filename);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *temp = malloc(sizeof(char) * (file_size+1));
    char ch;

    int i=0;
    while((ch = fgetc(file)) != EOF){
        temp[i] = ch;
        i++;
    }

    fclose(file);
    return temp;

}