%{
  #include "scanner.h"
  #define YY_USER_ACTION yylloc->columns( yyleng );
%}

%option nodefault yyclass="OptionsScanner" noyywrap c++

COMMENT #.*
STRING .*
IDENTIFIER [a-zA-Z][a-zA-Z0-9]*
WHITESPACE [ \n\t]+

%%

%{
  yylloc->step();
%}

COMMENT { return visualizer::OptionsParser::token::COMMENT; }
IDENTIFIER { return visualizer::OptionsParser::token::IDENTIFIER; }
STRING  { return visualizer::OptionsParser::token::STRING; }
. { yylloc->step(); }
"\n"+   { yylloc->lines( yyleng ); yylloc->step(); }

