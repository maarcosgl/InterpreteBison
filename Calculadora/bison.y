%{
#include <stdio.h>
#include "lex.yy.h"
#include "tablasimbolos.h"

void yyerror(char* s);

%}
%union{
double real;
int entero; 
char* identificador;
}

%token <entero> ENTERO
%token <identificador> IDENTIFICADOR
%type <real> exp_entera

%start input
%left '+'
%%
input:  /**/ {printf(">");}
        |input line

line:   '\n'
        |exp '\n'{}
        ;

exp:    exp_entera {printf("%lf\n", $1);printf(">");}
        ;

exp_entera:     ENTERO { $$ = $1; }
                |IDENTIFICADOR {
                                if(buscarNodoTabla($1)){
                                        $$ = devolverNodoTabla($1);
                                }
                                else{
                                        yyerror("Identificador no definido");
                                }
                        }
                |exp_entera '+' exp_entera { $$ = $1 + $3; }
                ;
;
%%
void yyerror(char* s)
{
fprintf(stderr,"%s\n",s);
}