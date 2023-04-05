%{
#include <stdlib.h>
#include <stdio.h>
#include "y.tab.h"

%}

%option noyywrap
%option noinput
%option nounput
%option yylineno
%option header-file="lex.yy.h"

LETRAS [a-zA-Z]
GUION_BAJO [_]
NUMERO [0-9]
ESPACIOS [ \t]+
NUEVA_LINEA [\n]

OPERADOR [.;\(\)\[\],\{\}\/<>*+=-]

ALFANUMERICA ({GUION_BAJO}({NUMERO}|{LETRAS})({NUMERO}|{GUION_BAJO}|{LETRAS})*)|({LETRAS}({NUMERO}|{GUION_BAJO}|{LETRAS})*)
NUMERO_ENTERO {NUMERO}({NUMERO}|_{NUMERO})*
NUMERO_DOUBLE {NUMERO}({NUMERO}|_{NUMERO})*"."({NUMERO}|_{NUMERO})*
CIENTIFICO ({NUMERO_ENTERO}|{NUMERO_DOUBLE})(e|E)(\+|\-){NUMERO_ENTERO}*
BINARIO (0b|0B)[01_]*

MAS_MAS \+\+
IGUAL_IGUAL ==
MAS_IGUAL \+=

%%
{ALFANUMERICA} {yylval.identificador = (char *)malloc(strlen(yytext)+1);
                strncpy(yylval.identificador,yytext,strlen(yytext));
                yylval.identificador[strlen(yytext)] = '\0';
                return (IDENTIFICADOR);}
({NUMERO_ENTERO}|{BINARIO}) {yylval.entero=atoi(yytext); return (ENTERO);}
({OPERADOR}|{NUEVA_LINEA}) {return yytext[0];}
{ESPACIOS}
<<EOF>> {return(EOF);}
. {return(-100);}
%%