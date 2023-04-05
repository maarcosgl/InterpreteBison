#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "y.tab.h"
#include "lex.yy.h"
#include "tablasimbolos.h"

int main(int argc, char *argv[]){
    crearTabla();
    yyparse();
}