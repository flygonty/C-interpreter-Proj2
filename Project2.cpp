# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <string>
# include <iostream>
# include <sstream>
# include <vector>
# include <math.h>
# include <ctype.h>

# define NUM_INFINITY 69454559
using namespace std;

static int uTestNum = 0 ;
static float uTolerance = 0.0001; // tolerance number

enum TokenType
{
    // define Token Type
    IDENT,
    CONSTANT, // 1, 3.5, 'a', "Hi, there", true, false
    INT, // int
    FLOAT, // float
    CHAR, // char
    BOOL, // bool
    STRING, // string
    VOID, // void
    IF, // if
    ELSE, // else
    WHILE, // while
    DO, // do
    RETURN, // return 
    LEFT_PAREN, // (
    RIGHT_PAREN, // )
    LB, // [
    RB, // ]
    LCB, // {
    RCB, // }
    ADD, // +
    MINUS, // -
    MULT, // *
    DIV, // /
    MOD, // %
    XOR, // ^
    GREATER, // >
    LESS, // <
    GE, // >=
    LE, // <=
    EQ, // ==
    NEQ, // <>
    AND_OP, // &
    OR_OP, // |
    ASSIGN, //  =
    NOT, // !
    AND, // &&
    OR, // ||
    PE, // +=
    ME, // -=
    TE, // *=
    DE, // /=
    RE, // %=
    PP, // ++
    MM, // --
    RS, // >>
    LS, // << 
    SEMICOLON, // ;
    COMMA, // ,
    CONDITION, // ?
    COLON // :
};

struct Token {
  string tokenValue; // record data
  TokenType type; // to tell parser which type
  int line;
};

struct While {
  vector <string> condition ;
  vector <string> statement ;
};

struct Function {
  vector <string> type ;
  vector <string> type_of_parameter ;
  vector <string> parameter ;
  vector <string> statement ;
};


class Scanner {
private:
  Token mBuf_token; // PeekToken()
  int mLine;
public:
  Scanner() ;
  Token PeekToken() ;
  Token GetToken() ;
}; // Scanner

Scanner::Scanner() {
  // initial constructor
  mLine = 1 ;
} // Scanner::Scanner()

Token Scanner::PeekToken() {
  // check next token type for parser
  if ( mBuf_token.tokenValue == "" ) {
    mBuf_token = GetToken();
  } // if
  
  return mBuf_token;
} // Scanner::PeekToken()

Token Scanner::GetToken() {
   // get the token and return to parser
  Token temp_Token;
  int countDot = 0 ; // to determine the token
  char peek_char; // peek_char for check peek char || get_char is actuaaly what you get 
  peek_char = cin.peek();
  if ( mBuf_token.tokenValue != "" ) {
    // if buffer it's not empty then use it and return for parser
    temp_Token.tokenValue = mBuf_token.tokenValue;
    temp_Token.type = mBuf_token.type;
    mBuf_token.tokenValue = ""; // empty the buffer
  } // if
  else {
    if ( peek_char == ' ' || peek_char == '\t' ) {
      cin.get(); // skip whitespace
      temp_Token = GetToken();
    } // if
    else if ( peek_char == '\n' ) {
      cin.get();
      mLine++ ;
      temp_Token = GetToken();
    } // else if
    else if ( peek_char == '(' ) {
      // LP
      char get_char = cin.get();
      temp_Token.type = LEFT_PAREN;
      temp_Token.tokenValue = "(";
    } // else if
    else if ( peek_char == ')' ) {
      // RP
      char get_char = cin.get();
      temp_Token.type = RIGHT_PAREN;
      temp_Token.tokenValue = ")";
    } // else if
    else if ( peek_char == '[' ) {
      // RP
      char get_char = cin.get();
      temp_Token.type = LB;
      temp_Token.tokenValue = "[";
    } // else if
    else if ( peek_char == ']' ) {
      // RP
      char get_char = cin.get();
      temp_Token.type = RB;
      temp_Token.tokenValue = "]";
    } // else if
    else if ( peek_char == '{' ) {
      // RP
      char get_char = cin.get();
      temp_Token.type = LCB;
      temp_Token.tokenValue = "{";
    } // else if
    else if ( peek_char == '}' ) {
      // RP
      char get_char = cin.get();
      temp_Token.type = RCB;
      temp_Token.tokenValue = "}";
    } // else if
    else if ( peek_char == '+' ) {
      char get_char = cin.get() ;
      char temp_peek = cin.peek() ;
      if ( temp_peek == '=' ) {
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        get_char = cin.get();
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        temp_Token.type = PE;
      } // if
      else if ( temp_peek == '+' ) {
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        get_char = cin.get();
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        temp_Token.type = PP;
      } // else if
      else {
        temp_Token.type = ADD;
        temp_Token.tokenValue = "+";
      } // else
    } // else if
    else if ( peek_char == '-' ) {
      char get_char = cin.get() ;
      char temp_peek = cin.peek() ;
      if ( temp_peek == '=' ) {
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        get_char = cin.get();
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        temp_Token.type = ME;
      } // if
      else if ( temp_peek == '-' ) {
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        get_char = cin.get();
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        temp_Token.type = MM;
      } // else if
      else {
        temp_Token.type = MINUS ;
        temp_Token.tokenValue = "-";
      } // else
    } // else if 
    else if ( peek_char == '*' ) {
      char get_char = cin.get() ;
      char temp_peek = cin.peek() ;
      if ( temp_peek == '=' ) {
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        get_char = cin.get();
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        temp_Token.type = TE;
      } // if
      else {
        temp_Token.type = MULT;
        temp_Token.tokenValue = "*";
      } // else 
    } // else if
    else if ( peek_char == '/' ) {
      // check whether it is comment or divide
      char get_char = cin.get();
      char temp_peek = cin.peek();
      if ( temp_peek == '/' ) {
        // it's comment
        cin.get(); // read all comment
        temp_peek = cin.peek();
        while ( temp_peek != '\n' ) {
          // skip the comment
          cin.get();
          temp_peek = cin.peek();
        } // while()

        temp_Token = GetToken() ;
      } // if
      else if ( temp_peek == '=' ) {
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        get_char = cin.get();
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        temp_Token.type = DE;
      } // else if
      else {
        // it's divide
        temp_Token.type = DIV;
        temp_Token.tokenValue = "/";
      } // else
    } // else if 
    else if ( peek_char == '%' ) {
      char get_char = cin.get() ;
      char temp_peek = cin.peek() ;
      if ( temp_peek == '=' ) {
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        get_char = cin.get();
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        temp_Token.type = RE;
      } // if
      else {
        temp_Token.type = MOD;
        temp_Token.tokenValue = "%";
      } // else 

    } // else if
    else if ( peek_char == '^' ) {
      char get_char = cin.get() ;
      temp_Token.type = XOR ;
      temp_Token.tokenValue = "^" ;
    } // else if
    else if ( peek_char == '>' ) {
      char get_char = cin.get();
      char temp_peek = cin.peek();
      if ( temp_peek == '=' ) {
        // >=
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        get_char = cin.get();
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        temp_Token.type = GE;
      } // if
      else if ( temp_peek == '>' ) {
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        get_char = cin.get();
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        temp_Token.type = RS;
      } // else if
      else {
        temp_Token.type = GREATER;
        temp_Token.tokenValue = ">";
      } // else
    } // else if
    else if ( peek_char == '<' ) {
      char get_char = cin.get();
      char temp_peek = cin.peek();
      if ( temp_peek == '=' ) {
        // >=
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        get_char = cin.get();
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        temp_Token.type = LE;
      } // if
      else if ( temp_peek == '<' ) {
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        get_char = cin.get();
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        temp_Token.type = LS;
      } // else if
      else {
        temp_Token.type = LESS;
        temp_Token.tokenValue = "<";
      } // else
    } // else if
    else if ( peek_char == '&' ) {
      char get_char = cin.get() ;
      char temp_peek = cin.peek() ;
      if ( temp_peek == '&' ) {
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        get_char = cin.get();
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        temp_Token.type = AND;
      } // if
      else {
        temp_Token.type = AND_OP;
        temp_Token.tokenValue = "&";
      } // else
    } // else if
    else if ( peek_char == '|' ) {
      char get_char = cin.get() ;
      char temp_peek = cin.peek() ;
      if ( temp_peek == '|' ) {
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        get_char = cin.get();
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        temp_Token.type = OR;
      } // if
      else {
        temp_Token.type = OR_OP;
        temp_Token.tokenValue = "|";
      } // else
    } // else if
    else if ( peek_char == '=' ) {
      char get_char = cin.get();
      char temp_peek = cin.peek();
      if ( temp_peek == '=' ) {
        // >=
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        get_char = cin.get();
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        temp_Token.type = EQ;
      } // if
      else {
        temp_Token.type = ASSIGN;
        temp_Token.tokenValue = "=";
      } // else
    } // else if
    else if ( peek_char == '!' ) {
      char get_char = cin.get() ;
      char temp_peek = cin.peek() ;
      if ( temp_peek == '=' ) {
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        get_char = cin.get();
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        temp_Token.type = NEQ;
      } // if
      else {
        temp_Token.type = NOT;
        temp_Token.tokenValue = "!";
      } // else
    } // else if
    else if ( peek_char == ';' ) {
      char get_char = cin.get();
      temp_Token.type = SEMICOLON;
      temp_Token.tokenValue = ";";
    } // else if
    else if ( peek_char == ',' ) {
      char get_char = cin.get();
      char temp_peek = cin.peek();
      temp_Token.type = COMMA;
      temp_Token.tokenValue = ",";
    } // else if
    else if ( peek_char == '?' ) {
      char get_char = cin.get();
      char temp_peek = cin.peek();
      temp_Token.type = CONDITION;
      temp_Token.tokenValue = "?";
    } // else if
    else if ( peek_char == ':' ) {
      char get_char = cin.get();
      char temp_peek = cin.peek();
      temp_Token.type = COLON;
      temp_Token.tokenValue = ":";
    } // else if
    else if ( peek_char >= '0' && peek_char <= '9' ) {
      // num or float
      char get_char = cin.get() ;
      temp_Token.tokenValue = temp_Token.tokenValue + get_char ;
      char temp_peek = cin.peek() ;
      if ( temp_peek == '.' ) {
        countDot++ ;
      } // if

      while ( countDot != 2 && ( temp_peek == '.' || ( temp_peek >= '0' && temp_peek <= '9' ) ) ) {
        char get_char = cin.get();
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        temp_peek = cin.peek();
        if ( temp_peek == '.' ) {
          countDot++ ;
        } // if
      } // while()

      temp_Token.type = CONSTANT ;
    } // else if
    else if ( peek_char == '.' ) {
      // .3 case  num
      char get_char = cin.get() ;
      temp_Token.tokenValue = temp_Token.tokenValue + get_char ;
      char temp_peek = cin.peek() ;
      while ( temp_peek >= '0' && temp_peek <= '9' ) {
        char get_char = cin.get();
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        temp_peek = cin.peek();
      } // while()

      temp_Token.type = CONSTANT ;
    } // else if
    else if ( peek_char == '\'' ) {
      char get_char = cin.get();
      char temp_peek = cin.peek( );
      if ( temp_peek != '\'' ) {
        char get_char = cin.get();
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
      } // if

      cin.get();
      temp_Token.type = CONSTANT;
    } // else if
    else if ( peek_char == '"' ) {
      char get_char = cin.get();
      char temp_peek = cin.peek( );
      while ( temp_peek != '"' ) {
        char get_char = cin.get();
        temp_Token.tokenValue = temp_Token.tokenValue + get_char;
        temp_peek = cin.peek();
      } // while

      cin.get( );
      temp_Token.type = CONSTANT;
    } // else if
    else {
      // Identifier, Constant, type
      char get_char = cin.get();
      temp_Token.tokenValue = temp_Token.tokenValue + get_char;
      if ( ( ( get_char >= 'a' && get_char <= 'z' ) || 
             ( get_char >= 'A' && get_char <= 'Z' ) ) ) {

        char temp_peek = cin.peek();
        while ( ( ( temp_peek >= 'a' && temp_peek <= 'z' ) || 
                  ( temp_peek >= 'A' && temp_peek <= 'Z' ) || temp_peek == '_' ) ||
                ( temp_peek >= '0' && temp_peek <= '9' )  ) {

          char get_char = cin.get();
          temp_Token.tokenValue = temp_Token.tokenValue + get_char;
          temp_peek = cin.peek() ;
        } // while()
      } // if()

      if ( strcmp( temp_Token.tokenValue.c_str(), "true" ) == 0 ) {
        temp_Token.type = CONSTANT ;
      } // if
      else if ( strcmp( temp_Token.tokenValue.c_str(), "false" ) == 0 ) {
        temp_Token.type = CONSTANT ;
      } // else if
      else if ( strcmp( temp_Token.tokenValue.c_str(), "int" ) == 0 ) {
        temp_Token.type = INT ;
      } // else if
      else if ( strcmp( temp_Token.tokenValue.c_str(), "float" ) == 0 ) {
        temp_Token.type = FLOAT ;
      } // else if
      else if ( strcmp( temp_Token.tokenValue.c_str(), "char" ) == 0 ) {
        temp_Token.type = CHAR ;
      } // else if
      else if ( strcmp( temp_Token.tokenValue.c_str(), "bool" ) == 0 ) {
        temp_Token.type = BOOL ;
      } // else if
      else if ( strcmp( temp_Token.tokenValue.c_str(), "string" ) == 0 ) {
        temp_Token.type = STRING ;
      } // else if
      else if ( strcmp( temp_Token.tokenValue.c_str(), "void" ) == 0 ) {
        temp_Token.type = VOID ;
      } // else if
      else if ( strcmp( temp_Token.tokenValue.c_str(), "if" ) == 0 ) {
        temp_Token.type = IF ;
      } // else if
      else if ( strcmp( temp_Token.tokenValue.c_str(), "else" ) == 0 ) {
        temp_Token.type = ELSE ;
      } // else if
      else if ( strcmp( temp_Token.tokenValue.c_str(), "while" ) == 0 ) {
        temp_Token.type = WHILE ;
      } // else if
      else if ( strcmp( temp_Token.tokenValue.c_str(), "do" ) == 0 ) {
        temp_Token.type = DO ;
      } // else if
      else if ( strcmp( temp_Token.tokenValue.c_str(), "return" ) == 0 ) {
        temp_Token.type = RETURN ;
      } // else if
      else {
        temp_Token.type = IDENT ;
      } // else
    } // else
  } // else

  temp_Token.line = mLine ;
  return temp_Token ;
} // Scanner::GetToken()

class Parser {
private:
  Scanner mScanner;
  vector <Function> mFunctionList ;
  vector <string> mVariableList ;
  vector <Token> mTokenList ; // store token and give it to eval
public:

  bool User_input() ;
  void Definition( bool &correct ) ;
  bool Type_specifier( Token token ) ;
  void Function_definition_or_declarators( bool &correct ) ;
  void Rest_of_declarators( bool &correct ) ;
  void Function_definition_without_ID( bool &correct ) ;
  void Formal_parameter_list( bool &correct ) ;
  void Compound_statement( bool &correct ) ;
  void Declaration( bool &correct ) ;
  void Statement( bool &correct ) ;
  void Expression( bool &correct ) ;
  void Basic_expression( bool &correct ) ;
  void Rest_of_Identifier_started_basic_exp( bool &correct ) ;
  void Rest_of_PPMM_Identifier_started_basic_exp( bool &correct ) ;
  bool Sign( Token token ) ;
  void Actual_parameter_list( bool &correct ) ;
  bool Assignment_operator( Token token ) ;
  void Romce_and_romloe( bool &correct ) ;
  void Rest_of_maybe_logical_OR_exp( bool &correct ) ;
  void Maybe_logical_AND_exp( bool &correct ) ;
  void Rest_of_maybe_logical_AND_exp( bool &correct ) ;
  void Maybe_bit_OR_exp( bool &correct ) ;
  void Rest_of_maybe_bit_OR_exp( bool &correct ) ;
  void Maybe_bit_ex_OR_exp( bool &correct ) ;
  void Rest_of_maybe_bit_ex_OR_exp( bool &correct ) ;
  void Maybe_bit_AND_exp( bool &correct ) ;
  void Rest_of_maybe_bit_AND_exp( bool &correct ) ;
  void Maybe_equality_exp( bool &correct ) ;
  void Rest_of_maybe_equality_exp( bool &correct ) ;
  void Maybe_relational_exp( bool &correct ) ;
  void Rest_of_maybe_relational_exp( bool &correct ) ;
  void Maybe_shift_exp( bool &correct ) ;
  void Rest_of_maybe_shift_exp( bool &correct ) ;
  void Maybe_additive_exp( bool &correct ) ;
  void Rest_of_maybe_additive_exp( bool &correct ) ;
  void Maybe_mult_exp( bool &correct ) ;
  void Rest_of_maybe_mult_exp( bool &correct ) ;
  void Unary_exp( bool &correct ) ;
  void Signed_unary_exp( bool &correct ) ;
  void Unsigned_unary_exp( bool &correct ) ;

  void Print_Definition_Variable( string ID ) ;
  void Print_Definition_Function( string ID ) ;


  bool IsUnrecognized( string& token ) ;
  void ErrorProcess() ;
  
  void Print_Unrecognized( Token token ) ;
  void Print_Unexpected( Token token ) ;
  void Print_Undefined( Token token ) ;

}; // Parser

bool Parser::User_input() {
  // : ( definition | statement ) { definition | statement }
} // Parser::User_input()

void Parser::Definition( bool &correct ) {
  // :           VOID Identifier function_definition_without_ID 
  // | type_specifier Identifier function_definition_or_declarators
  Token token, peek ;
  bool F_d_w_ID = false, F_d_o_d = false ;
  peek = mScanner.PeekToken() ;
  if ( peek.type != VOID && !Type_specifier( peek ) ) {
    // 1. Unrecognized 2. Unexpected
    correct = false ;
    if ( IsUnrecognized( peek.tokenValue ) ) {
      token = mScanner.GetToken() ;
      Print_Unrecognized( token ) ;
    } // if
    else {
      token = mScanner.GetToken() ;
      Print_Unexpected( token ) ;
    } // else

    ErrorProcess() ;
    return ;  	
  } // if

  correct = true ;
  if ( peek.type == VOID ) {
    token = mScanner.GetToken() ; // get the void token
    peek = mScanner.PeekToken() ; // peek IDENT
    if ( peek.type == IDENT ) {
      Function_definition_without_ID( F_d_w_ID ) ;
      if ( !F_d_w_ID ) {
        // error
        ErrorProcess() ;
        correct = false ;
      } // if
    } // if
    else {
      correct = false ;
      // error
      // 1. Unrecognized
      // 2. Unexpected
      if ( IsUnrecognized( peek.tokenValue ) ) {
        token = mScanner.GetToken() ;
        Print_Unrecognized( token ) ;
        ErrorProcess() ;
      } // if
      else {
      	token = mScanner.GetToken() ;
        Print_Unexpected( token ) ;
        ErrorProcess() ;
      } // else
    } // else
  } // if
  else if ( Type_specifier( peek ) ) {
    token = mScanner.GetToken() ; // get the Type token
    peek = mScanner.PeekToken() ; // peek IDENT
    if ( peek.type == IDENT ) {
      Function_definition_or_declarators( F_d_o_d ) ;
      if ( !F_d_o_d ) {
        // error
        correct = false ;
        ErrorProcess() ;
      } // if
    } // if
    else {
      // error
      correct = false ;
      // 1. Unrecognized
      // 2. Unexpected
      if ( IsUnrecognized( peek.tokenValue ) ) {
        token = mScanner.GetToken() ;
        Print_Unrecognized( token ) ;
        ErrorProcess() ;
      } // if
      else {
      	token = mScanner.GetToken() ;
        Print_Unexpected( token ) ;
        ErrorProcess() ;
      } // else
    } // else
  } // else if

  return ;
} // Parser::Definition()

bool Parser::Type_specifier( Token token ) {
  // : INT | CHAR | FLOAT | STRING | BOOL
  if ( token.type != INT && token.type != CHAR && token.type != FLOAT 
       && token.type != STRING && token.type != BOOL  ) {
    return false ;
  } // if
  else {
    return true ;
  } // else
} // Parser::Type_specifier()

void Parser::Function_definition_or_declarators( bool &correct ) {
  // : function_definition_without_ID
  // | rest_of_declarators
  Token token, peek ;
  peek = mScanner.PeekToken() ;
  bool F_d_w_ID = false, R_o_d = false ;
  if ( peek.type != LEFT_PAREN && peek.type != LB && peek.type != COMMA ) {
    correct = false ;
    if ( IsUnrecognized( peek.tokenValue ) ) {
      token = mScanner.GetToken() ;
      Print_Unrecognized( token ) ;
    } // if
    else {
      token = mScanner.GetToken() ;
      Print_Unexpected( token ) ;
    } // else

    ErrorProcess() ;
    return ;
  } // if

  correct = true ;
  if ( peek.type == LEFT_PAREN ) {
    Function_definition_without_ID( F_d_w_ID ) ;
    if ( !F_d_w_ID ) {
      // error
      ErrorProcess() ;
    } // if
  } // if
  else if ( peek.type == LB || peek.type == COMMA ) {
    Rest_of_declarators( R_o_d ) ;
    if ( !R_o_d ) {
      // error
      ErrorProcess() ;
    } // if
  } // else if

  return ;
} // Parser::Function_definition_or_declarators()

void Parser::Rest_of_declarators( bool &correct ) {
  // : [ '[' Constant ']' ] 
  // { ',' Identifier [ '[' Constant ']' ] } ';'
  Token token, peek ;
  peek = mScanner.PeekToken() ;
  if ( peek.type == LB ) {
    token = mScanner.GetToken() ;// get '['
    peek = mScanner.PeekToken() ;
    if ( peek.type == CONSTANT ) {
      token = mScanner.GetToken() ; // get Constant
      peek = mScanner.PeekToken() ;
      if ( peek.type == RB ) {
        token = mScanner.GetToken() ;
      } // if
      else {
        // error 1.Unrecognized 2. Unexpected
        correct = false ;
        if ( IsUnrecognized( peek.tokenValue ) ) {
          token = mScanner.GetToken() ;
          Print_Unrecognized( token ) ;
        } // if
        else {
          token = mScanner.GetToken() ;
          Print_Unexpected( token ) ;
        } // else

        ErrorProcess() ;
        return ;
      } // else
    } // if
    else {
      // error 1.Unrecognized 2. Unexpected
      correct = false ;
      if ( IsUnrecognized( peek.tokenValue ) ) {
        token = mScanner.GetToken() ;
        Print_Unrecognized( token ) ;
      } // if
      else {
        token = mScanner.GetToken() ;
        Print_Unexpected( token ) ;
      } // else

      ErrorProcess() ;
      return ;
    } // else
  } // if

  do {
    peek = mScanner.PeekToken() ;
    if ( peek.type != COMMA ) {
      correct = false ;
      if ( IsUnrecognized( peek.tokenValue ) ) {
        token = mScanner.GetToken() ;
        Print_Unrecognized( token ) ;
      } // if
      else {
        token = mScanner.GetToken() ;
        Print_Unexpected( token ) ;
      } // else

      ErrorProcess() ;
      return ;
    } // if

    correct = true ;
    if ( peek.type == COMMA ) {
      token = mScanner.GetToken() ;
      peek = mScanner.PeekToken() ;
      if ( peek.type == IDENT ) {
        token = mScanner.GetToken() ; // get Identifier
        peek = mScanner.PeekToken() ; // peek '['
        if ( peek.type == LB ) {
          token = mScanner.GetToken() ; // get '['
          peek = mScanner.PeekToken() ; // peek Constant
          if ( peek.type == CONSTANT ) {
            token = mScanner.GetToken() ; // get Constant
            peek = mScanner.PeekToken() ; // peek ']'
            if ( peek.type == RB ) {
              token = mScanner.GetToken() ; // get ']' [Constant] OK
            } // if
            else {
              correct = false ;
              if ( IsUnrecognized( peek.tokenValue ) ) {
                token = mScanner.GetToken() ;
                Print_Unrecognized( token ) ;
			  } // if
              else {
                token = mScanner.GetToken() ;
                Print_Unexpected( token ) ;
              } // else

              ErrorProcess() ;
              return ;
            } // else
          } // if
          else {
            correct = false ;
            if ( IsUnrecognized( peek.tokenValue ) ) {
              token = mScanner.GetToken() ;
              Print_Unrecognized( token ) ;
			} // if
            else {
              token = mScanner.GetToken() ;
              Print_Unexpected( token ) ;
            } // else

            ErrorProcess() ;
            return ;
          } // else
        } // if
        else if ( peek.type == SEMICOLON ) {
          token = mScanner.GetToken() ; // get ';'
          return ;
        } // else if
      } // if
      else {
        correct = false ;
        if ( IsUnrecognized( peek.tokenValue ) ) {
          token = mScanner.GetToken() ;
          Print_Unrecognized( token ) ;
        } // if
        else {
          token = mScanner.GetToken() ;
          Print_Unexpected( token ) ;
        } // else

        ErrorProcess() ;
        return ;
      } // else
    } // if
  } while( 1 ) ; 
} // Parser::Rest_of_declarator()

void Parser::Function_definition_without_ID( bool &correct ) {
  // : '(' [ VOID | formal_parameter_list ] ')' compound_statement
  Token token, peek ;
  bool F_p_l = false, C_s = false ;
  peek = mScanner.PeekToken() ; // peek '('
  if ( peek.type == LEFT_PAREN ) {
    token = mScanner.GetToken() ;
    peek = mScanner.PeekToken() ;
    if ( peek.type == VOID ) {
      token = mScanner.GetToken() ;
	} // if
    else {
      Formal_parameter_list( F_p_l ) ;
    } // else

    peek = mScanner.PeekToken() ;
    if ( peek.type == RIGHT_PAREN ) {
      token = mScanner.GetToken() ;
    } // if

    // compound_statment
    Compound_statement( C_s ) ;
    if ( C_s ) {
      correct = true ;
      return ;
    } // if
    else {
      correct = false ;
      return ;
    } // else
  } // if
  else {
    correct = false ;
    if ( IsUnrecognized( peek.tokenValue ) ) {
      token = mScanner.GetToken() ;
      Print_Unrecognized( token ) ;
    } // if
    else {
      token = mScanner.GetToken() ;
      Print_Unrecognized( token ) ;
    } // else

    ErrorProcess() ;
    return ;
  } // else
} // Parser::Function_definition_without_ID()

void Parser::Formal_parameter_list( bool &correct ) {
  // : type_specifier [ '&' ] Identifier [ '[' Constant ']' ] 
  // { ',' type_specifier [ '&' ] Identifier [ '[' Constant ']' ] }
  Token token, peek ;
  peek = mScanner.PeekToken() ; // peek token
  if ( Type_specifier( peek ) ) {

  } // if
  else {
    correct = false ;
    if ( IsUnrecognized( peek.tokenValue ) ) {
      token = mScanner.GetToken() ;
      Print_Unrecognized( token ) ;
    } // if
    else {
      token = mScanner.GetToken() ;
      Print_Unrecognized( token ) ;
    } // else

    ErrorProcess() ;
    return ;
  } // else
} // Parser::Formal_parameter_list()

void Parser::Compound_statement( bool &correct ) {
  // : '{' { declaration | statement } '}'
  Token token, peek ;
  bool declaration1Correct = false, statement1Correct = false ;
  peek = mScanner.PeekToken() ;
  if ( peek.type == LCB ) {
    token = mScanner.GetToken() ;
  } // if
  else {
    correct = false ;
    if ( IsUnrecognized( peek.tokenValue ) ) {
      token = mScanner.GetToken() ;
      Print_Unrecognized( token ) ;
    } // if
    else {
      token = mScanner.GetToken() ;
      Print_Unrecognized( token ) ;
    } // else

    ErrorProcess() ;
    return ;
  } // else

  correct = true ;
  do {
    peek = mScanner.PeekToken() ;
    if ( peek.type == RCB ) {
      return ; // meet ' }' then break
    } // if

    if ( Type_specifier( peek ) ) {
      Declaration( declaration1Correct ) ;
      if ( !declaration1Correct ) {
        correct = false ;
        return ;
      } // if
    } // if
    else {
      Statement( statement1Correct ) ;
      if ( !statement1Correct ) {
        correct = false ;
        return ;
      } // if
    } // else
  } while ( 1 ) ;
} // Parser::Compound_statement()

void Parser::Declaration( bool &correct ) {
  // : type_specifier Identifier rest_of_declarators
  Token token, peek ;
  bool R_o_d = false ;
  peek = mScanner.PeekToken() ;
  if ( Type_specifier( peek ) ) {
    token = mScanner.GetToken() ; // get type_specfier
    peek = mScanner.PeekToken() ;
    if ( peek.type == IDENT ) {
      token = mScanner.GetToken() ;
      Rest_of_declarators( R_o_d ) ;
      if ( R_o_d ) {
        correct = true ;
        return ;
      } // if
      else {
        correct = false ;
        return ;
      } // else
    } // if
    else {
      correct = false ;
      token = mScanner.GetToken() ;
      if ( IsUnrecognized( token.tokenValue ) ) {
        Print_Unrecognized( token ) ;
      } // if
      else {
        Print_Unexpected( token ) ;
      } // else

      ErrorProcess() ;
      return ;
    } // else
  } // if
  else {
    correct = false ;
    token = mScanner.GetToken() ;
    if ( IsUnrecognized( token.tokenValue ) ) {
      Print_Unrecognized( token ) ;
    } // if
    else {
      Print_Unexpected( token ) ;
    } // else

    ErrorProcess() ;
    return ;
  } // else
} // Parser::Declaration()

void Parser::Statement( bool &correct ) {
  // : ';'     // the null statement
  // | expression ';'  /* expression here should not be empty */
  // | RETURN [ expression ] ';'
  // | compound_statement
  // | IF '(' expression ')' statement [ ELSE statement ]
  // | WHILE '(' expression ')' statement
  // | DO statement WHILE '(' expression ')' ';'
  Token token, peek ;
  bool C_s1Correct = false, expression1Correct, statement1Correct ;
  peek = mScanner.PeekToken() ;
  if ( peek.type == SEMICOLON ) {
    token = mScanner.GetToken() ;
    correct = true ;
    return ;
  } // if
  else if ( peek.type == RETURN ) {
    token = mScanner.GetToken() ;
    peek = mScanner.PeekToken() ;
    if ( peek.type == SEMICOLON ) {
      token = mScanner.GetToken() ;
      correct = true ;
      return ;
    } // if
    else {
      Expression( expression1Correct ) ;
      if ( expression1Correct ) {
        peek = mScanner.GetToken() ;
        if ( peek.type == SEMICOLON ) {
          token = mScanner.GetToken() ;
          return ;
        } // if
        else {
          token = mScanner.GetToken() ;
          if ( IsUnrecognized( token.tokenValue ) ) {
            Print_Unrecognized( token ) ;
          } // if
          else {
            Print_Unexpected( token ) ;
          } // else

          ErrorProcess() ;
          return ;
        } // else
      } // if
      else {
        correct = false ;
        return ;
      } // else
    } // else
  } // else if
  else if ( peek.type == IF ) {
    token = mScanner.GetToken() ; // get IF
    peek = mScanner.PeekToken() ;
    if ( peek.type == LEFT_PAREN ) {
      token = mScanner.GetToken() ; // get '('
      Expression( expression1Correct ) ;
      if ( expression1Correct ) {
        peek = mScanner.PeekToken() ; // after expression peek ')'
        if ( peek.type == RIGHT_PAREN ) {
          token = mScanner.GetToken() ; // get ')'
          Statement( statement1Correct ) ;
          if ( statement1Correct ) {
            correct = true ;
            peek = mScanner.PeekToken() ;
            if ( peek.type == ELSE ) {
              token = mScanner.GetToken() ;
              Statement( statement1Correct ) ;
              if ( !statement1Correct ) {
                correct = false ;
                return ;
              } // if
              else {
                correct = true ;
                return ;
              } // else
            } // if
          } // if
          else {
            correct = false ;
            return ;
          } // else 
        } // if
        else {
          correct = false ;
          token = mScanner.GetToken() ;
          if ( IsUnrecognized( token.tokenValue ) ) {
            Print_Unrecognized( token ) ;
          } // if
          else {
            Print_Unexpected( token ) ;
          } // else

          ErrorProcess() ;
          return ;
        } // else
      } // if
      else {
        correct = false ;
        return ;
      } // else
    } // if
    else {
      correct = false ;
      token = mScanner.GetToken() ;
      if ( IsUnrecognized( token.tokenValue ) ) {
        Print_Unrecognized( token ) ;
      } // if
      else {
        Print_Unexpected( token ) ;
      } // else

      ErrorProcess() ;
      return ;
    } // else 
  } // else if
  else if ( peek.type == WHILE ) {
    token = mScanner.GetToken() ; // get WHILE
    peek = mScanner.PeekToken() ; // peek '('
    if ( peek.type == LEFT_PAREN ) {
      token = mScanner.GetToken() ; // get '('
      Expression( expression1Correct ) ;
      if ( expression1Correct ) {
        peek = mScanner.PeekToken() ;
        if ( peek.type == RIGHT_PAREN ) {
          token = mScanner.GetToken() ; // get ')'
          Statement( statement1Correct ) ;
          if ( statement1Correct ) {
            correct = true ;
            return ;
          } // if
          else {
            correct = false ;
            return ;
          } // else
        } // if
        else {
          correct = false ;
          token = mScanner.GetToken() ; // get wrong token
          if ( IsUnrecognized( token.tokenValue ) ) {
            Print_Unrecognized( token ) ;
          } // if
          else {
            Print_Unexpected( token ) ;
          } // else

          ErrorProcess() ;
          return ;
        } // else
      } // if
      else {
        correct = false ;
        return ;
      } // else
    } // if
    else {
      correct = false ;
      token = mScanner.GetToken() ; // get wrong token
      if ( IsUnrecognized( token.tokenValue ) ) {
        Print_Unrecognized( token ) ;
      } // if
      else {
        Print_Unexpected( token ) ;
      } // else

      ErrorProcess() ;
      return ;
    } // else
  } // else if
  else if ( peek.type == DO ) {
  } // else if
  else {
    Compound_statement( C_s1Correct ) ;
    if ( !C_s1Correct ) {
      correct = false ;
      return ;
    } // if
  } // else
} // Parser::Statement()

void Parser::Expression( bool &correct ) {
} // Parser::Expression()

void Parser::Basic_expression( bool &correct ) {
} // Parser::Basic_expression()

void Parser::Rest_of_Identifier_started_basic_exp( bool &correct ) {
} // Parser::Rest_of_Identifier_started_basic_exp()

void Parser::Rest_of_PPMM_Identifier_started_basic_exp( bool &correct ) {
} // Parser::Rest_of_PPMM_Identifier_started_basic_exp()

bool Parser::Sign( Token token ) {
} // Parser::Sign()

void Parser::Actual_parameter_list( bool &correct ) {
} // Parser::Actual_parameter_list()

bool Parser::Assignment_operator( Token token ) {
} // Parser::Assignment_operator()

void Parser::Romce_and_romloe( bool &correct ) {
} // Parser::Romce_and_romloe()

void Parser::Rest_of_maybe_logical_OR_exp( bool &correct ) {
} // Parser::Rest_of_maybe_logical_OR_exp()

void Parser::Maybe_logical_AND_exp( bool &correct ) {
} // Parser::Maybe_logical_AND_exp()

void Parser::Rest_of_maybe_logical_AND_exp( bool &correct ) {
} // Parser::Rest_of_maybe_logical_AND_exp()

void Parser::Maybe_bit_OR_exp( bool &correct ) {
} // Parser::Maybe_bit_OR_exp()

void Parser::Rest_of_maybe_bit_ex_OR_exp( bool &correct ) {
} // Parser::Rest_of_maybe_bit_ex_OR_exp()

void Parser::Maybe_bit_AND_exp( bool &correct ) {
} // Parser::Maybe_bit_AND_exp()

void Parser::Rest_of_maybe_bit_AND_exp( bool &correct ) {
} // Parser::Rest_of_maybe_bit_AND_exp()

void Parser::Maybe_equality_exp( bool &correct ) {
} // Parser::Maybe_equality_exp()

void Parser::Rest_of_maybe_equality_exp( bool &correct ) {
} // Parser::Rest_of_maybe_equality_exp()

void Parser::Maybe_relational_exp( bool &correct ) {
} // Parser::Maybe_relational_exp()

void Parser::Rest_of_maybe_relational_exp( bool &correct ) {
} // Parser::Rest_of_maybe_relational_exp()

void Parser::Maybe_shift_exp( bool &correct ) {
} // Parser::Maybe_shift_exp()

void Parser::Print_Definition_Variable( string ID ) {
  printf( "Definition of %s entered ...\n", ID.c_str() ) ;
} // Parser::Print_Definition_Variable()

void Print_Definition_Function( string ID ) {
  printf( "Definition of %s() entered ...\n", ID.c_str() ) ;
} // Parser::Print_Definition_Function()


bool Parser::IsUnrecognized( string& token ) {
  // determine the token is recognized

  if ( token[0] == '_' ) {
    return true ;
  } // if

  for ( int i = 0 ; i < token.size() ; i++ ) {
    if ( token[i] == '`' && token[i] == '~' && token[i] == '@' && token[i] == '#' && token[i] == '$' && 
         token[i] == '\\' ) {

      return true ;
    } // if
  } // for

  return false ;
} // Parser::IsUnrecognized()

void Parser::ErrorProcess() {
  // read all garbage char
  char temp_peek = cin.peek() ;
  while ( temp_peek != '\n' ) {
    cin.get() ;
    temp_peek = cin.peek() ;
  } // while()
} // Parser::ErrorProcess()

void Parser::Print_Unrecognized( Token token ) {
  string output = "unrecognized token with first char : '" + token.tokenValue + "'" ;
  printf( "Line %d : %s\n", token.line, token.tokenValue.c_str() ) ; // c++ string to c string
} // Parser::Print_Unrecognized()

void Parser::Print_Unexpected( Token token ) {
  string output = "unexpected token : '" + token.tokenValue + "'" ;
  printf( "Line %d : %s\n", token.line, token.tokenValue.c_str() ) ; // c++ string to c string
} // Parser::Print_Unexpected()

int main() {
  char ch = '\0' ; // read '\n'
  Token token ;
  bool jumpOut = false ;
  Parser parser ;
  Scanner scanner;
  // scanf_s( "%d%c", &uTestNum, &ch ) ;
  printf( "Program starts...\n" ) ;
  while ( 1 ) {
    token = scanner.GetToken();
      cout << token.type << "       " << token.tokenValue << "		" << token.line << endl << endl ;
  } // while()
} // main()

