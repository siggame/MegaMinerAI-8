%require "2.4.1"
/* C++ parser template apparently */
%skeleton "lalr1.cc"
%defines 
%locations
%define namespace "visualizer"
%define parser_class_name "OptionsParser"

%parse-param { visualizer::OptionsScanner& scanner }
%parse-param { visualizer::OptionsMan& options }
%lex-param { visualizer::OptionsScanner& scanner }

%code requires
{
  #include <sstream>
  #include "optionsman.h"
  namespace visualizer
  {
    // Need to forward declare the Scanner Class
    class OptionsScanner;

  } // Visualizer

}

%code
{
  static int yylex( 
    visualizer::OptionsParser::semantic_type* yylval, 
    visualizer::OptionsParser::location_type* yylloc,
    visualizer::OptionsScanner& scanner
    );

}

%union {
  char* string; 
}


%token <string> COMMENT 
%token <string> STRING 
%token <string> IDENTIFIER

%%

OptionsFile
  : OptionsFile Line
  | Line
  ;

Line
  : Comment
  | Assignment
  ;

Comment
  : COMMENT { options.addComment( $1 ); }
  ;

Assignment
  : IDENTIFIER '=' STRING { options[ $1 ] = $3; }
  | IDENTIFIER '(' Options ')' '=' STRING { options[ $1 ] = $6; }
  ;

Options
  : Options ',' Option
  | Option 
  ;

Option
  : STRING { options.addOption( $1 ); }
  ;

%%

void visualizer::OptionsParser::error
  ( 
  const visualizer::OptionsParser::location_type &loc, const std::string& msg
  )
{
  ostringstream ret;
  ret << "Parser Error at " << loc << ": " << msg;
  throw ret.str();


}

#include "scanner.h"
static int yylex
  ( 
  visualizer::OptionsParser::semantic_type* yylval,
  visualizer::OptionsParser::location_type* yylloc,
  visualizer::OptionsScanner& scanner
  )
  {
    return scanner.yylex( yylval, yylloc );

  }

