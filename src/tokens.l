%{
#include <string>
#include "node.h"
#include "parser.hpp"

#define SAVE_TOKEN  yylval.string = new std::string(strdup(yytext), yyleng)
#define TOKEN(t)    (yylval.token = t)

int linenum = 0;
%}

%option noyywrap
%option nodefault

%%
[ \t]
[ \n]					        linenum++;
"extern"                        return TOKEN(TEXTERN);
"return"				        return TOKEN(TRETURN);
[a-zA-Z_][a-zA-Z0-9_]*          SAVE_TOKEN; return TIDENTIFIER;
[0-9]+\.[0-9]* 			        SAVE_TOKEN; return TDOUBLE;
[0-9]+					        SAVE_TOKEN; return TINTEGER;

"="						        return TOKEN(TEQUAL);
"=="				          	return TOKEN(TCEQ);
"!="			          		return TOKEN(TCNE);
"<"				          		return TOKEN(TCLT);
"<="	          				return TOKEN(TCLE);
">"				          		return TOKEN(TCGT);
">="					        return TOKEN(TCGE);

"("	          					return TOKEN(TLPAREN);
")"					          	return TOKEN(TRPAREN);
"{"         					return TOKEN(TLBRACE);
"}"					          	return TOKEN(TRBRACE);
"\""                            return TOKEN(TQUOTE);

"."         					return TOKEN(TDOT);
","				          		return TOKEN(TCOMMA);

"+"				          		return TOKEN(TPLUS);
"-"		          				return TOKEN(TMINUS);
"*"		          				return TOKEN(TMUL);
"/"				          		return TOKEN(TDIV);

.                               return yytext[0];

%%
