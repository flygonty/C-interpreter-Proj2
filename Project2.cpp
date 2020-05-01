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
static bool uFloat = false ;
static bool uBoolean = false ; // check whether has bool op

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

struct Id {
  string id;
  float float_value;
  int int_value ;
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

  return temp_Token ;
} // Scanner::GetToken()

class Parser {
private:
  Scanner mScanner;
  vector <Id> mIdList; // store id's value

public:
  bool User_input() ;
  void Definition( float &value, bool &correct ) ;
  void Type_specifier() ;
  void Function_definition_ordeclarators() ;
  void Rest_of_declarator() ;
  void Function_definition_without_ID( float &value, bool &correct ) ;
  void Formal_parameter_list() ;
  void Compound_statement() ;
  void Declaration() ;
  void Statement( float &value, bool &correct ) ;
  void Expression() ;
  void Basic_expression() ;
  void Rest_of_Identifier_started_basic_exp() ;
  void Rest_of_PPMM_Identifier_started_basic_exp() ;
  void Sign() ;
  void Actual_parameter_list() ;
  void Assignment_operator() ;
  void Romce_and_romloe() ;
  void Rest_of_maybe_logical_OR_exp() ;
  void Maybe_logical_AND_exp() ;
  void Rest_of_maybe_logical_AND_exp() ;
  void Maybe_bit_OR_exp() ;
  void Rest_of_maybe_bit_OR_exp() ;
  void Maybe_bit_ex_OR_exp() ;
  void Rest_of_maybe_bit_ex_OR_exp() ;
  void Maybe_bit_AND_exp() ;
  void Rest_of_maybe_bit_AND_exp() ;
  void Maybe_equality_exp() ;
  void Rest_of_maybe_equality_exp() ;
  void Maybe_relational_exp() ;
  void Rest_of_maybe_relational_exp() ;
  void Maybe_shift_exp() ;
  void Rest_of_maybe_shift_exp() ;
  void Maybe_additive_exp() ;
  void Rest_of_maybe_additive_exp() ;
  void Maybe_mult_exp() ;
  void Rest_of_maybe_mult_exp() ;
  void Unary_exp() ;
  void Signed_unary_exp() ;
  void Unsigned_unary_exp() ;

  void Print_Definition_Variable( string ID ) ;
  void Print_Definition_Function( string ID ) ;

  bool CheckInside( string& id ) ;
  void ChangeInsideValue( string id, float value ) ; // change vector's id value
  void InitID( Id id ) ;

  bool IsRecognized( string& token ) ;
  bool HasDot( string& token ) ;
  void ErrorProcess() ;
  bool WrongFloat( string& token ) ;
  
  void Print_Unrecognized( string token ) ;
  void Print_Unexpected( string token ) ;
  void Print_Undefined( string token ) ;

  void Print_Float( float value ) ;
  void Print_Int( float value ) ;
}; // Parser

bool Parser::User_input() {
  // : ( definition | statement ) { definition | statement }
  float definition1Value = 0.0, statement1Value = 0.0 ;
  bool definition1Correct = false, statement1Correct = false ;
  Definition( definition1Value, definition1Correct ) ;
  Statement( statement1Value, statement1Correct ) ;
  if ( !definition1Correct && !statement1Correct ) {
    // error
  } // if

  do {
    Definition( definition1Value, definition1Correct ) ;
    Statement( statement1Value, statement1Correct ) ;
    if ( !definition1Correct && !statement1Correct ) {
      // error
    } // if
  } while( 1 ) ;
} // Parser::User_input()

void Parser::Definition( float &value, bool &correct ) {
  // :           VOID Identifier function_definition_without_ID 
  // | type_specifier Identifier function_definition_or_declarators

  float F_d_w_ID1Value = 0.0 ;
  bool F_d_w_ID1Correct = false ;

  Token peek, token ;
  peek = mScanner.PeekToken() ;
  if ( peek.type == VOID ) {
    correct = true ;
  } // if
  else if ( peek.type == INT && peek.type == CHAR && peek.type == FLOAT 
            && peek.type == STRING && peek.type == BOOL ) {
    token = mScanner.GetToken() ; // get the void 
    peek = mScanner.PeekToken() ;
    if ( peek.type == IDENT ) {
      token = mScanner.GetToken() ; // get Identifier
      Function_definition_without_ID( F_d_w_ID1Value, F_d_w_ID1Correct ) ;
      if ( !F_d_w_ID1Correct ) {
        value = 0.0 ;
        correct = false ;
        return ;
      } // if
      else {
        
      } // else
    } // if
    else {
      value = 0.0 ;
      correct = false ;
      return ;
    } // else

    correct = true ;
    return ;
  } // else if
  else {
    // no match token
    value = 0.0 ;
    correct = false ;
    return ;
  } // else
} // Parser::Definition()

void Parser::Statement( float &value, bool &correct ) {
	
} // Parser::Statement()

void Parser::Function_definition_without_ID( float &value, bool &correct ) {
	
} // Parser::Function_definition_without_ID()

void Parser::Print_Definition_Variable( string ID ) {
  printf( "Definition of %s entered ...\n", ID.c_str() ) ;
} // Parser::Print_Definition_Variable()

void Print_Definition_Function( string ID ) {
  printf( "Definition of %s() entered ...\n", ID.c_str() ) ;
} // Parser::Print_Definition_Function()

bool Parser::CheckInside( string& id ) {
  // check this id has already in the vector
  for ( int i = 0 ; i < mIdList.size() ; i++ ) {
    if ( strcmp( id.c_str(), mIdList[i].id.c_str() ) == 0 ) {
      return true;
    } // if
  } // for
  
  return false;
} // Parser::CheckInside()

void Parser::ChangeInsideValue( string id, float value ) {
  // renew the value in the id
  for ( int i = 0 ; i < mIdList.size() ; i++ ) {
    if ( strcmp( id.c_str(), mIdList[i].id.c_str() ) == 0 ) {
      // change inside value
      if ( uFloat ) { 
        mIdList.at( i ).float_value = value ;
        mIdList.at( i ).int_value = NUM_INFINITY ;
      } // if 
      else {
        mIdList.at( i ).int_value = value ;
        mIdList.at( i ).float_value = NUM_INFINITY ;
      } // else
    } // if
  } // for
} // Parser::ChangeInsideValue() 


void Parser::InitID( Id id ) {
  id.id = "" ;
  id.float_value = NUM_INFINITY ;
  id.int_value = NUM_INFINITY ;
} // Parser::InitID()

bool Parser::IsRecognized( string& token ) {
  // determine the token is recognized
  if ( strcmp( token.c_str(), ":=" ) == 0 ) {
    return true ;
  } // if

  if ( token[0] == '_' ) {
    return false ;
  } // if

  for ( int i = 0 ; i < token.size() ; i++ ) {
    if ( token[i] != '_' && token[i] != '*' && token[i] != '(' && token[i] != ')' && token[i] != '-' && 
         token[i] != '+' && token[i] != ';' &&  ( token[i] < '0' || token[i] > '9'  ) &&
         ( ( token[i] < 'a' || token[i] > 'z' ) && 
           ( token[i] < 'A' || token[i] > 'Z' ) && token[i] != '=' ) && token[i] != '/' &&
         token[i] != '<' && token[i] != '>' && token[i] != '.'  ) {

      return false ;
    } // if
  } // for

  return true ;
} // Parser::IsRecognized()

bool Parser::HasDot( string& token ) {
  // determine the token value is float 
  for ( int i = 0 ; i < token.size() ; i++ ) {
    if ( token[i] == '.' ) {
      return true ;
    } // if
  } // for
  
  return false ;
} // Parser::HasDot()

bool Parser::WrongFloat( string& token ) {
  // try to catch 3.4.5 wrong float case
  int checkDot = 0 ;
  for ( int i = 0 ; i < token.size() ; i++ ) {
    if ( token[i] == '.' ) {
      checkDot++ ;
    } // if

    if ( checkDot >= 2 ) {
      return true ;
    } // if
  } // for
  
  return false ;
} // Parser::WrongFloat()

void Parser::ErrorProcess() {
  // read all garbage char
  char temp_peek = cin.peek() ;
  while ( temp_peek != '\n' ) {
    cin.get() ;
    temp_peek = cin.peek() ;
  } // while()
} // Parser::ErrorProcess()

void Parser::Print_Unrecognized( string token ) {
  string output = "Unrecognized token with first char : '" + token + "'" ;
  printf( "%s\n", output.c_str() ) ; // c++ string to c string
} // Parser::Print_Unrecognized()

void Parser::Print_Unexpected( string token ) {
  string output = "Unexpected token : '" + token + "'" ;
  printf( "%s\n", output.c_str() ) ; // c++ string to c string
} // Parser::Print_Unexpected()

void Parser::Print_Undefined( string token ) {
  string output = "Undefined identifier : '" + token + "'" ;
  printf( "%s\n", output.c_str() ) ; // c++ string to c string
} // Parser::Print_Undefined()

void Parser::Print_Float( float value ) {
  printf( "%1.3f\n", value ) ;
} // Parser::Print_Float()

void Parser::Print_Int( float value ) {
  int num = value ; // float to string
  printf( "%d\n", num ) ;
} // Parser::Print_Int()

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
      cout << token.type << "       " << token.tokenValue << endl << endl ;
  } // while()
} // main()

