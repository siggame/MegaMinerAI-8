%require "2.4.1"
/* C++ parser template apparently */
%skeleton "lalr1.cc"
%defines 
%locations
%define namespace "Visualizer"
%define parser_class_name "OptionsParser"
%parse-param { Visualizer::_OptionsMan &options }

%code requires
{
  namespace Visualizer
  {
    // Need to forward declare the Scanner Class
    class OptionsScanner;
  } // Visualizer

}

%token COMMENT STRING IDENTIFIER

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
  : IDENTIFIER '=' STRING { options[ $1 ] = $2; }
  | IDENTIFIER '(' Options ')' '=' STRING { options[ $1 ] = $2; }
  ;

Options
  : Options ',' Option
  | Option 
  ;

Option
  : STRING { options.addOption( $1 ); }
  ;

