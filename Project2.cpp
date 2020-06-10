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

/* 
   function print
   if function error that would also push to functionvariableList
   error line print
*/

static int uTestNum = 0 ;
static float uTolerance = 0.0001; // tolerance number

static bool uIsVariable = false ;
static bool uIsFunction = false ;

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

struct Variable {
  string type ;
  string id ;
  string constant ;
};


struct Function {
  Token type ;
  Token function_id ;  
  vector <Variable> parameter ;
  vector <Token> statement ;
};

struct FunctionVariable {
  string function_id ;
  vector <Variable> functionVariableList ;
};

FunctionVariable gFunctionVariable ; // global function variable

class Scanner {
private:
  Token mBuf_token; // PeekToken()
  int mLine;
public:
  Scanner() ;
  Token PeekToken() ;
  Token GetToken() ;
  void InitializeLine() ;
}; // Scanner

Scanner::Scanner() {
  // initial constructor
  mLine = 1 ;
} // Scanner::Scanner()

void Scanner::InitializeLine() {
  mLine = 0 ;
} // Scanner::InitializeLine()

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

  // cout << temp_Token.tokenValue << "  " << temp_Token.type << endl ;
  temp_Token.line = mLine ;
  return temp_Token ;
} // Scanner::GetToken()

class Parser {
private:
  Scanner mScanner; 
  vector <Function> mFunctionList ;
  vector <FunctionVariable> mFunctionVariableList ;
  vector <Variable> mVariableList ;
  vector <Variable> mTempList ;
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

  bool SameType( string ID, string Type ) ;
  bool SameConstant( string ID, string Constant ) ;
  bool IntheList( string ID ) ;
  bool IntheFunctionList( string ID ) ;
  bool IntheTempList( string ID ) ;
  bool IntheFVariableList( string ID ) ;
  bool HasFunctionVariable( string ID ) ;
  void Save_Definition() ;

  void Print_NewDefinition_Variable( string ID ) ;
  void Print_NewDefinition_Function( string ID ) ;
  void Print_Definition_Variable( string ID ) ;
  void Print_Definition_Function( string ID ) ;
  void Print_NewDefinition( string ID ) ;

  void Sort() ;
  bool Done( Token peek ) ;
  void CleanTokenBuffer() ;
  void ErrorMessage() ;

  bool IsUnrecognized( string& token ) ;
  void ErrorProcess() ;
  void Undefined() ;
  bool IsListFunction( Token peek ) ;
  bool IsCinCout( Token peek ) ;

  void Print_Unrecognized( Token token ) ;
  void Print_Unexpected( Token token ) ;
  void Print_Undefined( Token token ) ;

}; // Parser

bool Parser::User_input() {
  // : ( definition | statement ) { definition | statement }

  uIsVariable = false ; // global variable
  uIsFunction = false ; // global variable
  bool definition1Correct = false, statement1Correct = false ;
  string statementID ;
  Token peek ;
  peek = mScanner.PeekToken() ;

  if ( Done( peek ) ) {
    return false ;
  } // if


  if ( peek.type == VOID || Type_specifier( peek ) ) {
    Definition( definition1Correct ) ;
    if ( !definition1Correct ) {
      if ( uIsFunction ) { // clear mFunctionVariable element when occuring error
        for ( int i = 0 ; i < mFunctionVariableList.size() ; i++ ) {
          if ( strcmp( mFunctionVariableList[i].function_id.c_str(),
                       gFunctionVariable.function_id.c_str() ) == 0 ) {
            mFunctionVariableList.erase( mFunctionVariableList.begin() + i ) ;
          } // if
        } // for
      } // if
    } // if

    if ( definition1Correct ) {
      Save_Definition() ;
      /*
      for ( int i = 0 ; i < mFunctionVariableList.size() ; i++ ) {
       cout << "642 : " << mFunctionVariableList[i].function_id << endl ;
       for ( int j = 0 ; j < mFunctionVariableList[i].functionVariableList.size() ; j++  ) {
         cout << mFunctionVariableList[i].functionVariableList[j].type << 
         mFunctionVariableList[i].functionVariableList[j].id << " " 
         << mFunctionVariableList[i].functionVariableList[j].constant << endl ;
       } // for
      } // for
      */
    } // if
  } // if
  else {
    Statement( statement1Correct ) ;
    if ( strcmp( peek.tokenValue.c_str(), "ListAllVariables" ) == 0 ) {
      statementID = peek.tokenValue ;
    } // if
    else if ( strcmp( peek.tokenValue.c_str(), "ListVariable" ) == 0 ) {
      statementID = peek.tokenValue ;
    } // if

    if ( statement1Correct ) {
      Sort() ;
      if ( strcmp( statementID.c_str(), "ListAllVariables" ) == 0 ) { // need to sort and print
        for ( int i = 0 ; i < mVariableList.size() ; i++ ) {
          printf( "%s\n", mVariableList[i].id.c_str() ) ;
        } // for
      } // if
      else if ( strcmp( statementID.c_str(), "ListVariable" ) == 0 ) {
        for ( int i = 0 ; i < mVariableList.size() ; i++ ) {
          if ( strcmp( mVariableList[i].id.c_str(), mTokenList[2].tokenValue.c_str() ) == 0 ) {
            printf( "%s %s", mVariableList[i].type.c_str(), mVariableList[i].id.c_str() ) ;
            if ( mVariableList[i].constant != "" ) {
              printf( "[ %s ] ;\n", mVariableList[i].constant.c_str() ) ;
            } // if
            else {
              printf( " ;\n" ) ;
            } // else
          } // if
        } // for
      } // if
 
      printf( "Statement executed ...\n" ) ;
    } // if
  } // else




  gFunctionVariable.function_id = "" ; // empty id
  gFunctionVariable.functionVariableList.clear() ; // clear vector
  mScanner.InitializeLine() ; // every one command need to intialize
  CleanTokenBuffer() ;
  return true ;
} // Parser::User_input()

void Parser::Definition( bool &correct ) {
  // :           VOID Identifier function_definition_without_ID 
  // | type_specifier Identifier function_definition_or_declarators
  Token token, peek ;
  string id ;
  bool f_d_w_ID = false, f_d_o_d = false ;
  peek = mScanner.PeekToken() ;
  if ( peek.type != VOID && !Type_specifier( peek ) ) {
    // 1. Unrecognized 2. Unexpected
    correct = false ;
    ErrorMessage() ;
    return ;
  } // if

  correct = true ;
  if ( peek.type == VOID ) {
    uIsVariable = false ;
    uIsFunction = true ;

    token = mScanner.GetToken() ; // get the void token
    mTokenList.push_back( token ) ; // push to buffer 
    peek = mScanner.PeekToken() ; // peek IDENT
    if ( peek.type == IDENT ) {
      gFunctionVariable.function_id = peek.tokenValue ; // assign ID give it to gFuncVariable
      if ( IntheFunctionList( gFunctionVariable.function_id ) ) {
        for ( int i = 0 ; i < mFunctionVariableList.size() ; i++ ) {
          if ( strcmp( gFunctionVariable.function_id.c_str(),
                       mFunctionVariableList[i].function_id.c_str() ) == 0 ) {
            mFunctionVariableList[i].functionVariableList.clear() ;
          } // if
        } // for
      } // if


      token = mScanner.GetToken() ; // get ident
      mTokenList.push_back( token ) ; // push to buffer 
      Function_definition_without_ID( f_d_w_ID ) ;
      if ( !f_d_w_ID ) {
        // error
        ErrorProcess() ;
        correct = false ;
      } // if

    } // if
    else {
      correct = false ;
      ErrorMessage() ;
    } // else
  } // if
  else if ( Type_specifier( peek ) ) {
    token = mScanner.GetToken() ; // get the Type token
    mTokenList.push_back( token ) ; // push to buffer 
    peek = mScanner.PeekToken() ; // peek IDENT
    gFunctionVariable.function_id = peek.tokenValue ; // assign ID give it to gFuncVariable
    if ( peek.type == IDENT ) {
      token = mScanner.GetToken() ; // get ident
      mTokenList.push_back( token ) ;
      Function_definition_or_declarators( f_d_o_d ) ;
      if ( !f_d_o_d ) {
        // error
        correct = false ;
        ErrorProcess() ;
      } // if
    } // if
    else {
      // error
      correct = false ;
      ErrorMessage() ;
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
  bool f_d_w_ID = false, r_o_d = false ;
  if ( peek.type != LEFT_PAREN && peek.type != LB && peek.type != COMMA && peek.type != SEMICOLON ) {
    correct = false ;
    ErrorMessage() ;
    return ;
  } // if

  correct = true ;
  if ( peek.type == LEFT_PAREN ) {
    uIsVariable = false ; // global variable
    uIsFunction = true ; // global variable
    Function_definition_without_ID( f_d_w_ID ) ;
    if ( !f_d_w_ID ) {
      // error
      correct = false ;
      ErrorProcess() ;
    } // if
  } // if
  else if ( peek.type == LB || peek.type == COMMA || peek.type == SEMICOLON ) {
    uIsVariable = true ; // global variable
    uIsFunction = false ; // global variable
    gFunctionVariable.function_id = "" ; // empty id
    Rest_of_declarators( r_o_d ) ;
    if ( !r_o_d ) {
      // error
      correct = false ;
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
    token = mScanner.GetToken() ; // get '['
    mTokenList.push_back( token ) ;
    peek = mScanner.PeekToken() ;
    if ( peek.type == CONSTANT ) {
      token = mScanner.GetToken() ; // get Constant
      mTokenList.push_back( token ) ;
      peek = mScanner.PeekToken() ;
      if ( peek.type == RB ) {
        token = mScanner.GetToken() ;
        mTokenList.push_back( token ) ;
      } // if
      else {
        // error 1.Unrecognized 2. Unexpected
        correct = false ;
        ErrorMessage() ;
        return ;
      } // else
    } // if
    else {
      // error 1.Unrecognized 2. Unexpected
      correct = false ;
      ErrorMessage() ;
      return ;
    } // else
  } // if

  correct = true ;
  Variable variable ;

  do {
    peek = mScanner.PeekToken() ;
    if ( peek.type != COMMA ) {
      if ( peek.type == SEMICOLON ) {
        correct = true ;
        token = mScanner.GetToken() ;
        mTokenList.push_back( token ) ; // push to buffer
        for ( int i = 0 ; i < mTokenList.size() ; i++ ) {
          if ( Type_specifier( mTokenList[i] ) ) {
            variable.type = mTokenList[i].tokenValue ;
          } // if
          else if ( mTokenList[i].type == IDENT && 
                    strcmp( mTokenList[i].tokenValue.c_str(),
                            gFunctionVariable.function_id.c_str() ) == 1 ) {
            variable.id = mTokenList[i].tokenValue ;
            if ( i + 2 < mTokenList.size() && mTokenList[i+2].type == CONSTANT ) {
              variable.constant = mTokenList[i+2].tokenValue ;
              gFunctionVariable.functionVariableList.push_back( variable ) ;
              variable.constant = "" ;
            } // if
            else {
              gFunctionVariable.functionVariableList.push_back( variable ) ;
            } // else
          } // if
        } // for

        variable.type = "" ;
        variable.id = "" ;
        variable.constant = "" ;
        if ( uIsFunction ) {
          if ( !IntheFVariableList( gFunctionVariable.function_id ) ) {
            mFunctionVariableList.push_back( gFunctionVariable ) ;
          } // if
        } // if
        else {
          gFunctionVariable.functionVariableList.clear() ;
        } // else

        return ;
      } // if

      correct = false ;
      ErrorMessage() ;
      return ;
    } // if

    correct = true ;
    if ( peek.type == COMMA ) {
      token = mScanner.GetToken() ; // get ','
      mTokenList.push_back( token ) ; // push to buffer 
      peek = mScanner.PeekToken() ;
      if ( peek.type == IDENT ) {
        token = mScanner.GetToken() ; // get Identifier
        mTokenList.push_back( token ) ; // push to token list buffer 
        peek = mScanner.PeekToken() ; // peek '['
        if ( peek.type == LB ) {
          token = mScanner.GetToken() ; // get '['
          mTokenList.push_back( token ) ;
          peek = mScanner.PeekToken() ; // peek Constant
          if ( peek.type == CONSTANT ) {
            token = mScanner.GetToken() ; // get Constant
            mTokenList.push_back( token ) ;
            peek = mScanner.PeekToken() ; // peek ']'
            if ( peek.type == RB ) {
              token = mScanner.GetToken() ; // get ']' [Constant] OK
              mTokenList.push_back( token ) ;
            } // if
            else {
              correct = false ;
              ErrorMessage() ;
              return ;
            } // else
          } // if
          else {
            correct = false ;
            ErrorMessage() ;
            return ;
          } // else
        } // if
        else if ( peek.type == SEMICOLON ) {
          correct = true ;
          token = mScanner.GetToken() ; // get ';'
          mTokenList.push_back( token ) ;
          Variable variable ;
          for ( int i = 0 ; i < mTokenList.size() ; i++ ) {
            // get definition of variable in the function
            if ( uIsFunction && Type_specifier( mTokenList[i] ) ) {
              variable.type = mTokenList[i].tokenValue ;
            } // if
            else if ( uIsFunction && mTokenList[i].type == IDENT ) {
              variable.id = mTokenList[i].tokenValue ;
              if ( uIsFunction && i + 2 < mTokenList.size() && mTokenList[i+2].type == CONSTANT ) {
                variable.constant = mTokenList[i+2].tokenValue ;
                gFunctionVariable.functionVariableList.push_back( variable ) ; 
                // push it to global function variable
                variable.constant = "" ;
              } // if
              else {
                if ( uIsFunction && variable.type != "" ) { // push variable not function id
                  gFunctionVariable.functionVariableList.push_back( variable ) ; 
                  // push it to global function variable
                } // if
              } // else

              if ( !IntheFVariableList( gFunctionVariable.function_id ) ) {
                mFunctionVariableList.push_back( gFunctionVariable ) ;
              } // if
            } // else if
          } // for

          return ;
        } // else if
      } // if
      else {
        correct = false ;
        ErrorMessage() ;
        return ;
      } // else
    } // if
    else {
      correct = false ;
      ErrorMessage() ;
      return ;
    } // else
  } while ( 1 ) ; 
} // Parser::Rest_of_declarators()

void Parser::Function_definition_without_ID( bool &correct ) {
  // : '(' [ VOID | formal_parameter_list ] ')' compound_statement
  Token token, peek ;
  bool f_p_l = false, c_s = false ;
  peek = mScanner.PeekToken() ; // peek '('
  if ( peek.type == LEFT_PAREN ) {
    token = mScanner.GetToken() ;
    mTokenList.push_back( token ) ; // push to buffer 
    peek = mScanner.PeekToken() ;
    if ( peek.type != RIGHT_PAREN ) { // VOID
      Formal_parameter_list( f_p_l ) ;
      if ( !f_p_l ) {
        correct = false ;
        return ;
      } // if
    } // if

    peek = mScanner.PeekToken() ;
    if ( peek.type == RIGHT_PAREN ) {
      token = mScanner.GetToken() ; // get ')'
      mTokenList.push_back( token ) ; // push to buffer 
    } // if
    else {
      correct = false ;
      ErrorMessage() ;
      return ;
    } // else

    // compound_statment
    Compound_statement( c_s ) ;
    if ( c_s ) {
      mTempList.clear() ; // clear temp variable list
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
    ErrorMessage() ;
    return ;
  } // else
} // Parser::Function_definition_without_ID()

void Parser::Formal_parameter_list( bool &correct ) {
  // : type_specifier [ '&' ] Identifier [ '[' Constant ']' ] 
  // { ',' type_specifier [ '&' ] Identifier [ '[' Constant ']' ] }
  Token token, peek ;
  peek = mScanner.PeekToken() ; // peek token
  if ( Type_specifier( peek ) ) {
    token = mScanner.GetToken() ;
    mTokenList.push_back( token ) ; // push to buffer 
    peek = mScanner.PeekToken() ;
    if ( peek.type == AND_OP ) {
      token = mScanner.GetToken() ; // get '&'
      mTokenList.push_back( token ) ; // push to buffer 
      peek = mScanner.PeekToken() ; // peek Ident
      if ( peek.type == IDENT ) {
        token = mScanner.GetToken() ;
        mTokenList.push_back( token ) ; // push to buffer 
      } // if
      else {
        correct = false ;
        ErrorMessage() ;
        return ;
      } // else
    } // if
    else if ( peek.type == IDENT ) {
      token = mScanner.GetToken() ; // get Identifier
      mTokenList.push_back( token ) ; // push to buffer 
    } // else if
    else {
      correct = false ;
      ErrorMessage() ;
      return ;
    } // else

    peek = mScanner.PeekToken() ; // peek '['
    if ( peek.type == LB ) {
      token = mScanner.GetToken() ; // get '['
      mTokenList.push_back( token ) ; // push to buffer 
      peek = mScanner.PeekToken() ;
      if ( peek.type == CONSTANT ) {
        token = mScanner.GetToken() ; // get Constant
        mTokenList.push_back( token ) ; // push to buffer 
        peek = mScanner.PeekToken() ;
        if ( peek.type == RB ) {
          token = mScanner.GetToken() ; // get ']'
          mTokenList.push_back( token ) ; // push to buffer 
        } // if
        else {
          correct = false ;
          ErrorMessage() ;
          return ;
        } // else
      } // if
      else {
        correct = false ;
        ErrorMessage() ;
        return ;
      } // else
    } // if


    do {

      peek = mScanner.PeekToken() ;
      if ( peek.type != COMMA ) {
        correct = true ;
        return ;
      } // if

      token = mScanner.GetToken() ; // get ','
      mTokenList.push_back( token ) ; // push to buffer 
      peek = mScanner.PeekToken() ;
      if ( Type_specifier( peek ) ) {
        token = mScanner.GetToken() ;
        mTokenList.push_back( token ) ; // push to buffer 
        peek = mScanner.PeekToken() ;
        if ( peek.type == AND_OP ) {
          token = mScanner.GetToken() ; // get '&'
          mTokenList.push_back( token ) ; // push to buffer 
          peek = mScanner.PeekToken() ; // peek Ident
          if ( peek.type == IDENT ) {
            token = mScanner.GetToken() ;
            mTokenList.push_back( token ) ; // push to buffer 
          } // if
          else {
            correct = false ;
            ErrorMessage() ;
            return ;
          } // else
        } // if
        else  if ( peek.type == IDENT ) {
          token = mScanner.GetToken() ; // get Identifier
          mTokenList.push_back( token ) ; // push to buffer 
        } // else if
        else {
          correct = false ;
          ErrorMessage() ;
          return ;
        } // else

        peek = mScanner.PeekToken() ; // peek '['
        if ( peek.type == LB ) {
          token = mScanner.GetToken() ; // get '['
          mTokenList.push_back( token ) ; // push to buffer 
          peek = mScanner.PeekToken() ;
          if ( peek.type == CONSTANT ) {
            token = mScanner.GetToken() ; // get Constant
            mTokenList.push_back( token ) ; // push to buffer 
            peek = mScanner.PeekToken() ;
            if ( peek.type == RB ) {
              token = mScanner.GetToken() ; // get ']'
              mTokenList.push_back( token ) ; // push to buffer 
            } // if
            else {
              correct = false ;
              ErrorMessage() ;
              return ;
            } // else
          } // if
          else {
            correct = false ;
            ErrorMessage() ;
            return ;
          } // else
        } // if
      } // if
      else {
        correct = false ;
        ErrorMessage() ;
        return ;
      } // else
    } while ( 1 ) ;

  } // if
  else {
    correct = false ;
    ErrorMessage() ;
    return ;
  } // else
} // Parser::Formal_parameter_list()

void Parser::Compound_statement( bool &correct ) {
  // : '{' { declaration | statement } '}'
  Token token, peek ;
  bool declaration1Correct = false, statement1Correct = false ;
  peek = mScanner.PeekToken() ; // peek '{'
  if ( peek.type == LCB ) {
    token = mScanner.GetToken() ;
    mTokenList.push_back( token ) ; // push to buffer 
  } // if
  else {
    correct = false ;
    ErrorMessage() ;
    return ;
  } // else

  peek = mScanner.PeekToken() ;
  if ( peek.type == RCB ) { // { empty }
    Variable variable ;
 
    for ( int i = 0 ; i < mTokenList.size() ; i++ ) {
      if ( Type_specifier( mTokenList[i] ) ) {
        variable.type = mTokenList[i].tokenValue ;
      } // if
      else if ( mTokenList[i].type == IDENT ) {
        variable.id = mTokenList[i].tokenValue ;
        if ( i + 2 < mTokenList.size() && mTokenList[i+2].type == CONSTANT ) {
          variable.constant = mTokenList[i+2].tokenValue ;
          gFunctionVariable.functionVariableList.push_back( variable ) ;
          variable.constant = "" ;
        } // if
        else {
          gFunctionVariable.functionVariableList.push_back( variable ) ;
        } // else
      } // if
    } // for

    if ( !IntheFVariableList( gFunctionVariable.function_id ) ) {
      mFunctionVariableList.push_back( gFunctionVariable ) ;
    } // if
  } // if

  do {
    peek = mScanner.PeekToken() ;

    if ( peek.type == RCB ) {
      correct = true ;
      token = mScanner.GetToken() ;
      mTokenList.push_back( token ) ; // push to buffer
      return ; // meet ' }' then break
    } // if

    if ( Type_specifier( peek ) ) {
      Declaration( declaration1Correct ) ;
      if ( !declaration1Correct ) {
        mTempList.clear() ; // because error then all drop it
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
  Variable variable ;
  bool r_o_d = false ;
  peek = mScanner.PeekToken() ;
  if ( Type_specifier( peek ) ) {
    token = mScanner.GetToken() ; // get type_specfier
    mTokenList.push_back( token ) ; // push to buffer
    peek = mScanner.PeekToken() ;
    if ( peek.type == IDENT ) {
      token = mScanner.GetToken() ; // get Ident
      mTokenList.push_back( token ) ; // push to buffer
      Rest_of_declarators( r_o_d ) ;
      if ( r_o_d ) {
        for ( int i = 0 ; i < mTokenList.size() ; i++ ) {
          if ( Type_specifier( mTokenList[i] ) ) {
            variable.type = mTokenList[i].tokenValue ;
          } // if
          else if ( mTokenList[i].type == IDENT ) {
            variable.id = mTokenList[i].tokenValue ;
            if ( i + 2 < mTokenList.size() && mTokenList[i+2].type == CONSTANT 
                 && mTokenList[i+1].type == LB ) {
              variable.constant = mTokenList[i+2].tokenValue ;
              mTempList.push_back( variable ) ;
              variable.constant = "" ;
            } // if
            else {
              if ( mTokenList[i+1].type == COMMA || mTokenList[i+1].type == SEMICOLON )
                mTempList.push_back( variable ) ;
            } // else
          } // else if
        } // for


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
      ErrorMessage() ;
      return ;
    } // else
  } // if
  else {
    correct = false ;
    ErrorMessage() ;
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
  bool c_s1Correct = false, expression1Correct, statement1Correct ;
  peek = mScanner.PeekToken() ;
  if ( peek.type == SEMICOLON ) {
    token = mScanner.GetToken() ;
    mTokenList.push_back( token ) ; // push to buffer
    correct = true ;
    return ;
  } // if
  else if ( peek.type == IDENT || peek.type == PP || peek.type == MM || 
            Sign( peek ) || peek.type == CONSTANT || peek.type == LEFT_PAREN ) {
    Expression( expression1Correct ) ;
    if ( expression1Correct ) {
      peek = mScanner.PeekToken() ; // peek ';'
      if ( peek.type == SEMICOLON ) {
        token = mScanner.GetToken() ;
        mTokenList.push_back( token ) ; // push to buffer
        correct = true ;
        return ;
      } // if
      else {
        correct = false ;
        ErrorMessage() ;
        return ;
      } // else
    } // if
    else {
      correct = false ;
      return ;
    } // else
  } // else if
  else if ( peek.type == RETURN ) {
    token = mScanner.GetToken() ; // get 'return'
    mTokenList.push_back( token ) ; // push to buffer
    peek = mScanner.PeekToken() ;
    if ( peek.type == SEMICOLON ) {
      token = mScanner.GetToken() ;
      mTokenList.push_back( token ) ; // push to buffer
      correct = true ;
      return ;
    } // if
    else {
      Expression( expression1Correct ) ;
      if ( expression1Correct ) {
        peek = mScanner.PeekToken() ;
        if ( peek.type == SEMICOLON ) {
          correct = true ;
          token = mScanner.GetToken() ;
          mTokenList.push_back( token ) ; // push to buffer
          return ;
        } // if
        else {
          correct = false ;
          ErrorMessage() ;
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
    mTokenList.push_back( token ) ; // push to buffer
    peek = mScanner.PeekToken() ;
    if ( peek.type == LEFT_PAREN ) {
      token = mScanner.GetToken() ; // get '('
      mTokenList.push_back( token ) ; // push to buffer
      Expression( expression1Correct ) ;
      if ( expression1Correct ) {
        peek = mScanner.PeekToken() ; // after expression peek ')'
        if ( peek.type == RIGHT_PAREN ) {
          token = mScanner.GetToken() ; // get ')'
          mTokenList.push_back( token ) ; // push to buffer
          Statement( statement1Correct ) ;
          if ( statement1Correct ) {
            correct = true ;
            peek = mScanner.PeekToken() ;
            if ( peek.type == ELSE ) { // optional
              token = mScanner.GetToken() ;
              mTokenList.push_back( token ) ; // push to buffer
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
            else {
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
          ErrorMessage() ;
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
      ErrorMessage() ;
      return ;
    } // else 
  } // else if
  else if ( peek.type == WHILE ) {
    token = mScanner.GetToken() ; // get WHILE
    mTokenList.push_back( token ) ; // push to buffer
    peek = mScanner.PeekToken() ; // peek '('
    if ( peek.type == LEFT_PAREN ) {
      token = mScanner.GetToken() ; // get '('
      mTokenList.push_back( token ) ; // push to buffer
      Expression( expression1Correct ) ;
      if ( expression1Correct ) {
        peek = mScanner.PeekToken() ;
        if ( peek.type == RIGHT_PAREN ) {
          token = mScanner.GetToken() ; // get ')'
          mTokenList.push_back( token ) ; // push to buffer
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
          ErrorMessage() ;
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
      ErrorMessage() ;
      return ;
    } // else
  } // else if
  else if ( peek.type == DO ) {
    // DO statement WHILE '(' expression ')' ';'
    token = mScanner.GetToken() ; // get token DO
    mTokenList.push_back( token ) ; // push to buffer
    Statement( statement1Correct ) ;
    if ( statement1Correct ) {
      peek = mScanner.PeekToken() ; // peek WHILE
      if ( peek.type == WHILE ) {
        token = mScanner.GetToken() ; // get WHILE
        mTokenList.push_back( token ) ; // push to buffer
        peek = mScanner.PeekToken() ; // peek '('
        if ( peek.type == LEFT_PAREN ) {
          token = mScanner.GetToken() ; // get '('
          mTokenList.push_back( token ) ; // push to buffer
          Expression( expression1Correct ) ;
          if ( expression1Correct ) {
            peek = mScanner.PeekToken() ; // peek ')'
            if ( peek.type == RIGHT_PAREN ) {
              token = mScanner.GetToken() ; // get ')'
              mTokenList.push_back( token ) ; // push to buffer
              peek = mScanner.PeekToken() ; // peek ';'
              if ( peek.type == SEMICOLON ) {
                token = mScanner.GetToken() ; // get ';'
                mTokenList.push_back( token ) ; // push to buffer
                correct = true ;
                return ;
              } // if
              else {
                correct = false ;
                ErrorMessage() ;
                return ;
              } // else
            } // if
            else {
              correct = false ;
              ErrorMessage() ;
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
          ErrorMessage() ;
          return ;
        } // else
      } // if
      else {
        // error
        correct = false ;
        ErrorMessage() ;
        return ;
      } // else 
    } // if
    else {
      correct = false ;
      return ;
    } // else
  } // else if
  else {
    // compound_statement
    Compound_statement( c_s1Correct ) ;
    if ( c_s1Correct ) {
      mTempList.clear() ; // clear temp variable list
      correct = true ;
      return ;
    } // if
    else {
      correct = false ;
      return ;
    } // else
  } // else
} // Parser::Statement()

void Parser::Expression( bool &correct ) {
  // : basic_expression { ',' basic_expression }
  Token token, peek ;
  bool basic_exp1Correct = false ;
  Basic_expression( basic_exp1Correct ) ;
  if ( basic_exp1Correct ) {
    do {
      peek = mScanner.PeekToken() ;
      if ( peek.type != COMMA ) {
        correct = true ;
        return ;
      } // if

      if ( peek.type == COMMA ) {
        token = mScanner.GetToken() ; // get ','
        mTokenList.push_back( token ) ; // push to token buffer
        Basic_expression( basic_exp1Correct ) ;
        if ( !basic_exp1Correct ) {
          correct = false ;
          return ;
        } // if
      } // if
    } while ( 1 ) ;
  } // if
  else {
    correct = false ;
    return ;
  } // else
} // Parser::Expression()

void Parser::Basic_expression( bool &correct ) {
  Token token, peek ;
  bool r_o_I_s_b_e1Correct = false, r_o_PPMM_I_s_b_e1Correct = false ;
  bool signed_unary_exp1Correct = false, romce_and_romloe1Correct = false ;
  bool expression1Correct = false ;

  peek = mScanner.PeekToken() ; // peek token to determine go which ways
  if ( peek.type == IDENT ) {
    if ( !IsListFunction( peek ) && !IsCinCout( peek ) ) {
      if ( uIsFunction ) {
        if ( !HasFunctionVariable( peek.tokenValue ) ) {
          Undefined() ;
          correct = false ;
          return ;
        } // if

        if ( !IntheTempList( peek.tokenValue ) ) {
          Undefined() ;
          correct = false ;
          return ;
        } // if
      } // if
      else if ( !uIsFunction && !IntheList( peek.tokenValue ) ) { // Undefined
        Undefined() ;
        correct = false ;
        return ;
      } // if
      else if ( !uIsFunction && !IntheTempList( peek.tokenValue ) 
                && !IntheList( peek.tokenValue ) && mTempList.size() > 0 ) { // Undefined
        Undefined() ;
        correct = false ;
        return ;
      } // if
    } // if

    token = mScanner.GetToken() ; // get Identifier
    mTokenList.push_back( token ) ; // push to token buffer
    Rest_of_Identifier_started_basic_exp( r_o_I_s_b_e1Correct ) ;
    if ( r_o_I_s_b_e1Correct ) {
      correct = true ;
      return ;
    } // if
    else {
      correct = false ;
      return ;
    } // else
  } // if
  else if ( peek.type == PP || peek.type == MM ) {
    token = mScanner.GetToken() ; // get PP or MM
    mTokenList.push_back( token ) ; // push to token buffer
    peek = mScanner.PeekToken() ; // peek Identifier
    if ( peek.type == IDENT ) {
      if ( !IsListFunction( peek ) && !IsCinCout( peek ) ) {
        if ( uIsFunction ) {
          if ( !HasFunctionVariable( peek.tokenValue ) ) {
            Undefined() ;
            correct = false ;
            return ;
          } // if

          if ( !IntheTempList( peek.tokenValue ) ) {
            Undefined() ;
            correct = false ;
            return ;
          } // if
        } // if

        if ( !uIsFunction && !IntheList( peek.tokenValue ) ) { // Undefined
          Undefined() ;
          correct = false ;
          return ;
        } // if

        if ( !uIsFunction && !IntheTempList( peek.tokenValue ) && mTempList.size() > 0 ) { // Undefined
          Undefined() ;
          correct = false ;
          return ;
        } // if
      } // if

      token = mScanner.GetToken() ; // get Identifier
      mTokenList.push_back( token ) ; // push to token buffer
      Rest_of_PPMM_Identifier_started_basic_exp( r_o_PPMM_I_s_b_e1Correct ) ;
      if ( r_o_PPMM_I_s_b_e1Correct ) {
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
      ErrorMessage() ;
      return ;
    } // else
  } // else if
  else if ( Sign( peek ) ) {
    token = mScanner.GetToken() ; // get sign
    mTokenList.push_back( token ) ; // push to token buffer
    peek = mScanner.PeekToken() ; // peek sign
    if ( peek.type == CONSTANT ) { // ( Constant | '(' expression ')' ) romce_and_romloe
      token = mScanner.GetToken() ; // get Constanat or '('
      mTokenList.push_back( token ) ;
      if ( token.type == LEFT_PAREN ) {
        Expression( expression1Correct ) ;
        if ( expression1Correct ) {
          peek = mScanner.PeekToken() ; // peek ')'
          if ( peek.type == RIGHT_PAREN ) {
            token = mScanner.GetToken() ; // get ')'
            mTokenList.push_back( token ) ; // push to token buffer
          } // if
          else {
            correct = false ;
            ErrorMessage() ;
            return ;
          } // else
        } // if
        else {
          correct = false ;
          return ;
        } // else
      } // if

      Romce_and_romloe( romce_and_romloe1Correct ) ;
      if ( romce_and_romloe1Correct ) {
        correct = true ;
        return ;
      } // if
      else {
        correct = false ;
        return ;
      } // else
    } // if
    else {
      while ( !Sign( peek ) ) {
        token = mScanner.GetToken() ; // get sign
        mTokenList.push_back( token ) ; // push to token buffer
        peek = mScanner.PeekToken() ;
      } // while()

      Signed_unary_exp( signed_unary_exp1Correct ) ;
      if ( signed_unary_exp1Correct ) {
        Romce_and_romloe( romce_and_romloe1Correct ) ;
        if ( romce_and_romloe1Correct ) {
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
        return ;
      } // else
    } // else
  } // else if
  else if ( peek.type == CONSTANT || peek.type == LEFT_PAREN ) {
    token = mScanner.GetToken() ; // get Constanat or '('
    mTokenList.push_back( token ) ;
    if ( token.type == LEFT_PAREN ) {
      Expression( expression1Correct ) ;
      if ( expression1Correct ) {
        peek = mScanner.PeekToken() ; // peek ')'
        if ( peek.type == RIGHT_PAREN ) {
          token = mScanner.GetToken() ; // get ')'
          mTokenList.push_back( token ) ; // push to token buffer
        } // if
        else {
          correct = false ;
          ErrorMessage() ;
          return ;
        } // else
      } // if
      else {
        correct = false ;
        return ;
      } // else
    } // if

    Romce_and_romloe( romce_and_romloe1Correct ) ;
    if ( romce_and_romloe1Correct ) {
      correct = true ;
      return ;
    } // if
    else {
      correct = false ;
      return ;
    } // else
  } // else if
  else {
    correct = false ;
    ErrorMessage() ;
    return ;
  } // else
} // Parser::Basic_expression()

void Parser::Rest_of_Identifier_started_basic_exp( bool &correct ) {
  Token token, peek ;
  bool b_expression1Correct = false, romce_and_romloe1Correct = false ; 
  bool expression1Correct = false, actual_parameter_list1Correct = false ;
  peek = mScanner.PeekToken() ;

  if ( peek.type == LB ) {
    token = mScanner.GetToken() ;
    mTokenList.push_back( token ) ; // push to token buffer
    Expression( expression1Correct ) ;
    if ( expression1Correct ) {
      peek = mScanner.PeekToken() ;
      if ( peek.type != RB ) {
        correct = false ;
        ErrorMessage() ;
        return ;
      } // if
      else {
        token = mScanner.GetToken() ;
        mTokenList.push_back( token ) ; // push to token buffer
        peek = mScanner.PeekToken() ;
      } // else
    } // if
    else {
      correct = false ;
      return ;
    } // else
  } // if

  if ( Assignment_operator( peek ) ) {
    token = mScanner.GetToken() ; // get Assignment op
    mTokenList.push_back( token ) ; // push to token buffer
    Basic_expression( b_expression1Correct ) ;
    if ( b_expression1Correct ) {
      correct = true ;
      return ;
    } // if
    else {
      correct = false ;
      return ;
    } // else
  } // if
  else if ( peek.type == PP || peek.type == MM ) {
    token = mScanner.GetToken() ; // get PP or MM
    mTokenList.push_back( token ) ; // push to token buffer
    Romce_and_romloe( romce_and_romloe1Correct ) ;
    if ( romce_and_romloe1Correct ) {
      correct = true ;
      return ;
    } // if
    else {
      correct = false ;
      return ;
    } // else
  } // else if
  else if ( peek.type == LEFT_PAREN ) {
    token = mScanner.GetToken() ; // get '('
    mTokenList.push_back( token ) ; // push to token buffer
    peek = mScanner.PeekToken() ; // peek ')'
    if ( peek.type == RIGHT_PAREN ) {
      token = mScanner.GetToken() ; // get ')'
      mTokenList.push_back( token ) ; // push to token buffer
      Romce_and_romloe( romce_and_romloe1Correct ) ;
      if ( romce_and_romloe1Correct ) {
        correct = true ;
        return ;
      } // if
      else {
        correct = false ;
        return ;
      } // else
    } // if
    else {
      Actual_parameter_list( actual_parameter_list1Correct ) ;
      if ( actual_parameter_list1Correct ) {
        peek = mScanner.PeekToken() ; // peek ')'
        if ( peek.type == RIGHT_PAREN ) {
          token = mScanner.GetToken() ; // get ')'
          mTokenList.push_back( token ) ; // push to token buffer
          Romce_and_romloe( romce_and_romloe1Correct ) ;
          if ( romce_and_romloe1Correct ) {
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
          ErrorMessage() ;
          return ;
        } // else
      } // if
      else {
        correct = false ;
        return ;
      } // else
    } // else
  } // else if
  else {
    Romce_and_romloe( romce_and_romloe1Correct ) ;
    if ( romce_and_romloe1Correct ) {
      correct = true ;
      return ;
    } // if
    else {
      correct = false ;
      return ;
    } // else
  } // else
} // Parser::Rest_of_Identifier_started_basic_exp()

void Parser::Rest_of_PPMM_Identifier_started_basic_exp( bool &correct ) {
  Token token, peek ;
  bool expression1Correct = false, romce_and_romloe1Correct = false ;

  peek = mScanner.PeekToken() ; // peek '['
  if ( peek.type == LB ) {
    token = mScanner.GetToken() ; // get '['
    mTokenList.push_back( token ) ; // push to token buffer
    Expression( expression1Correct ) ;
    if ( expression1Correct ) {
      peek = mScanner.PeekToken() ; // peek ']'
      if ( peek.type == RB ) {
        token = mScanner.GetToken() ; // get ']'
        mTokenList.push_back( token ) ; // push to token buffer
        correct = true ;
        return ;
      } // if
      else {
        correct = false ;
        ErrorMessage() ;
        return ;
      } // else
    } // if
    else {
      correct = false ;
      return ;
    } // else
  } // if
  else { // do romce_and_romloe without expression
    Romce_and_romloe( romce_and_romloe1Correct ) ;
    if ( romce_and_romloe1Correct ) {
      correct = true ;
      return ;
    } // if
    else {
      correct = false ;
      return ;
    } // else
  } // else
} // Parser::Rest_of_PPMM_Identifier_started_basic_exp()

bool Parser::Sign( Token token ) {
  if ( token.type == ADD || token.type == MINUS || token.type == NOT ) {
    return true ;
  } // if
  else {
    return false ;
  } // else
} // Parser::Sign()

void Parser::Actual_parameter_list( bool &correct ) {
  Token token, peek ;
  bool b_expression1Correct = false ;

  Basic_expression( b_expression1Correct ) ;
  if ( b_expression1Correct ) {
    correct = true ;
    do {
      peek = mScanner.PeekToken() ; // peek ','
      if ( peek.type != COMMA ) {
        return ;
      } // if

      token = mScanner.GetToken() ; // get ','
      mTokenList.push_back( token ) ; // push to token buffer
      Basic_expression( b_expression1Correct ) ;
      if ( !b_expression1Correct ) {
        correct = false ;
        return ;
      } // if
    } while ( 1 ) ;
  } // if
  else {
    correct = false ;
    return ;
  } // else
} // Parser::Actual_parameter_list()

bool Parser::Assignment_operator( Token token ) {
  if ( token.type == ASSIGN || token.type == TE || token.type == DE ||
       token.type == RE || token.type == PE || token.type == ME ) {
    return true ;
  } // if
  else {
    return false ;
  } // else
} // Parser::Assignment_operator()

void Parser::Romce_and_romloe( bool &correct ) {
  Token token, peek ;
  bool r_o_m_l_OR_exp1Correct = false, b_expression1Correct = false ;
  Rest_of_maybe_logical_OR_exp( r_o_m_l_OR_exp1Correct ) ;
  if ( r_o_m_l_OR_exp1Correct ) {
    correct = true ;
    peek = mScanner.PeekToken() ; // peek '?'
    if ( peek.type == CONDITION ) {
      token = mScanner.GetToken() ; // '?'
      mTokenList.push_back( token ) ; // push to token buffer
      Basic_expression( b_expression1Correct ) ;
      if ( b_expression1Correct ) {
        peek = mScanner.PeekToken() ; // peek ':'
        if ( peek.type == COLON ) {
          token = mScanner.GetToken() ; // get ':'
          mTokenList.push_back( token ) ; // push to token buffer
          Basic_expression( b_expression1Correct ) ;
          if ( b_expression1Correct ) {
            return ; // correct == true
          } // if
          else {
            correct = false ;
            return ;
          } // else
        } // if
        else {
          correct = false ;
          ErrorMessage() ;
          return ;
        } // else
      } // if
      else {
        correct = false ;
        return ;
      } // else
    } // if
    else {
      return ;
    } // else
  } // if
  else {
    correct = false ;
    return ;
  } // else
} // Parser::Romce_and_romloe()

void Parser::Rest_of_maybe_logical_OR_exp( bool &correct ) {
  Token token, peek ;
  bool r_o_m_l_AND_exp1Correct = false, maybe_logical_AND_exp1Correct = false ;

  Rest_of_maybe_logical_AND_exp( r_o_m_l_AND_exp1Correct ) ;
  if ( r_o_m_l_AND_exp1Correct ) {
    do {
      peek = mScanner.PeekToken() ; // peek OR
      if ( peek.type == OR ) {
        token = mScanner.GetToken() ; // get 'OR'
        mTokenList.push_back( token ) ; // push to token buffer
        Maybe_logical_AND_exp( maybe_logical_AND_exp1Correct ) ;
        if ( !maybe_logical_AND_exp1Correct ) {
          correct = false ;
          return ;
        } // if
      } // if
      else {
        correct = true ;
        return ;
      } // else
    } while ( 1 ) ;
  } // if
  else {
    correct = false ;
    return ;
  } // else
} // Parser::Rest_of_maybe_logical_OR_exp()

void Parser::Maybe_logical_AND_exp( bool &correct ) {
  Token token, peek ;
  bool maybe_bit_OR_exp1Correct = false ;

  Maybe_bit_OR_exp( maybe_bit_OR_exp1Correct ) ;
  if ( maybe_bit_OR_exp1Correct ) {
    do {
      peek = mScanner.PeekToken() ; // peek OR
      if ( peek.type == AND ) {
        token = mScanner.GetToken() ; // get 'OR'
        mTokenList.push_back( token ) ; // push to token buffer
        Maybe_bit_OR_exp( maybe_bit_OR_exp1Correct ) ;
        if ( !maybe_bit_OR_exp1Correct ) {
          correct = false ;
          return ;
        } // if
      } // if
      else {
        correct = true ;
        return ;
      } // else
    } while ( 1 ) ;
  } // if
  else {
    correct = false ;
    return ;
  } // else
} // Parser::Maybe_logical_AND_exp()

void Parser::Rest_of_maybe_logical_AND_exp( bool &correct ) {
  Token token, peek ;
  bool r_o_m_l_OR_exp1Correct = false, maybe_bit_OR_exp1Correct = false ;

  Rest_of_maybe_bit_OR_exp( r_o_m_l_OR_exp1Correct ) ;
  if ( r_o_m_l_OR_exp1Correct ) {
    do {
      peek = mScanner.PeekToken() ; // peek AND
      if ( peek.type == AND ) {
        token = mScanner.GetToken() ; // get 'AND'
        mTokenList.push_back( token ) ; // push to token buffer
        Maybe_bit_OR_exp( maybe_bit_OR_exp1Correct ) ;
        if ( !maybe_bit_OR_exp1Correct ) {
          correct = false ;
          return ;
        } // if
      } // if
      else {
        correct = true ;
        return ;
      } // else
    } while ( 1 ) ;
  } // if
  else {
    correct = false ;
    return ;
  } // else
} // Parser::Rest_of_maybe_logical_AND_exp()

void Parser::Maybe_bit_OR_exp( bool &correct ) {
  Token token, peek ;
  bool maybe_bit_ex_OR_exp1Correct = false ;

  Maybe_bit_ex_OR_exp( maybe_bit_ex_OR_exp1Correct ) ;
  if ( maybe_bit_ex_OR_exp1Correct ) {
    do {
      peek = mScanner.PeekToken() ; // peek OR_OP '|'
      if ( peek.type == OR_OP ) {
        token = mScanner.GetToken() ; // get 'OR_OP'
        mTokenList.push_back( token ) ; // push to token buffer
        Maybe_bit_ex_OR_exp( maybe_bit_ex_OR_exp1Correct ) ;
        if ( !maybe_bit_ex_OR_exp1Correct ) {
          correct = false ;
          return ;
        } // if
      } // if
      else {
        correct = true ;
        return ;
      } // else
    } while ( 1 ) ;
  } // if
  else {
    correct = false ;
    return ;
  } // else
} // Parser::Maybe_bit_OR_exp()

void Parser::Rest_of_maybe_bit_OR_exp( bool &correct ) {
  Token token, peek ;
  bool r_o_maybe_bit_ex_OR_exp1Correct = false, maybe_bit_ex_OR_exp1Correct = false ;

  Rest_of_maybe_bit_ex_OR_exp( r_o_maybe_bit_ex_OR_exp1Correct ) ;
  if ( r_o_maybe_bit_ex_OR_exp1Correct ) {
    do {
      peek = mScanner.PeekToken() ; // peek OR
      if ( peek.type == OR_OP ) {
        token = mScanner.GetToken() ; // get 'OR_OP'
        mTokenList.push_back( token ) ; // push to token buffer
        Maybe_bit_ex_OR_exp( maybe_bit_ex_OR_exp1Correct ) ;
        if ( !maybe_bit_ex_OR_exp1Correct ) {
          correct = false ;
          return ;
        } // if
      } // if
      else {
        correct = true ;
        return ;
      } // else
    } while ( 1 ) ;
  } // if
  else {
    correct = false ;
    return ;
  } // else
} // Parser::Rest_of_maybe_bit_OR_exp()

void Parser::Maybe_bit_ex_OR_exp( bool &correct ) {
  Token token, peek ;
  bool maybe_bit_AND_exp1Correct = false ;

  Maybe_bit_AND_exp( maybe_bit_AND_exp1Correct ) ;
  if ( maybe_bit_AND_exp1Correct ) {
    do {
      peek = mScanner.PeekToken() ; // peek '^'
      if ( peek.type == XOR ) {
        token = mScanner.GetToken() ; // get '^'
        mTokenList.push_back( token ) ; // push to token buffer
        Maybe_bit_AND_exp( maybe_bit_AND_exp1Correct ) ;
        if ( !maybe_bit_AND_exp1Correct ) {
          correct = false ;
          return ;
        } // if
      } // if
      else {
        correct = true ;
        return ;
      } // else
    } while ( 1 ) ;
  } // if
  else {
    correct = false ;
    return ;
  } // else
} // Parser::Maybe_bit_ex_OR_exp()

void Parser::Rest_of_maybe_bit_ex_OR_exp( bool &correct ) {
  Token token, peek ;
  bool r_o_maybe_bit_AND_exp1Correct = false, maybe_bit_AND_exp1Correct = false ;

  Rest_of_maybe_bit_AND_exp( r_o_maybe_bit_AND_exp1Correct ) ;
  if ( r_o_maybe_bit_AND_exp1Correct ) {
    do {
      peek = mScanner.PeekToken() ; // peek XOR '^'
      if ( peek.type == XOR ) {
        token = mScanner.GetToken() ; // get 'XOR' ^
        mTokenList.push_back( token ) ; // push to token buffer
        Maybe_bit_AND_exp( maybe_bit_AND_exp1Correct ) ;
        if ( !maybe_bit_AND_exp1Correct ) {
          correct = false ;
          return ;
        } // if
      } // if
      else {
        correct = true ;
        return ;
      } // else
    } while ( 1 ) ;
  } // if
  else {
    correct = false ;
    return ;
  } // else
} // Parser::Rest_of_maybe_bit_ex_OR_exp()

void Parser::Maybe_bit_AND_exp( bool &correct ) {
  Token token, peek ;
  bool maybe_equality_exp1Correct = false ;

  Maybe_equality_exp( maybe_equality_exp1Correct ) ;
  if ( maybe_equality_exp1Correct ) {
    do {
      peek = mScanner.PeekToken() ; // peek '&'
      if ( peek.type == AND_OP ) {
        token = mScanner.GetToken() ; // get '&'
        Maybe_equality_exp( maybe_equality_exp1Correct ) ;
        if ( !maybe_equality_exp1Correct ) {
          correct = false ;
          return ;
        } // if
      } // if
      else {
        correct = true ;
        return ;
      } // else
    } while ( 1 ) ;
  } // if
  else {
    correct = false ;
    return ;
  } // else
} // Parser::Maybe_bit_AND_exp()

void Parser::Rest_of_maybe_bit_AND_exp( bool &correct ) {
  Token token, peek ;
  bool r_o_maybe_equalityexp1Correct = false, maybe_equality_exp1Correct = false ;

  Rest_of_maybe_equality_exp( r_o_maybe_equalityexp1Correct ) ;
  if ( r_o_maybe_equalityexp1Correct ) {
    do {
      peek = mScanner.PeekToken() ; // peek AND
      if ( peek.type == AND_OP ) {
        token = mScanner.GetToken() ; // get '&'
        mTokenList.push_back( token ) ; // push to token buffer
        Maybe_equality_exp( maybe_equality_exp1Correct ) ;
        if ( !maybe_equality_exp1Correct ) {
          correct = false ;
          return ;
        } // if
      } // if
      else {
        correct = true ;
        return ;
      } // else
    } while ( 1 ) ;
  } // if
  else {
    correct = false ;
    return ;
  } // else
} // Parser::Rest_of_maybe_bit_AND_exp()

void Parser::Maybe_equality_exp( bool &correct ) {
  Token token, peek ;
  bool maybe_relational_exp1Correct = false ;

  Maybe_relational_exp( maybe_relational_exp1Correct ) ;
  if ( maybe_relational_exp1Correct ) {
    do {
      peek = mScanner.PeekToken() ; // peek 'EQ' or NEQ
      if ( peek.type == EQ || peek.type == NEQ ) {
        token = mScanner.GetToken() ; // get EQ or NEQ
        mTokenList.push_back( token ) ; // push to token buffer
        Maybe_relational_exp( maybe_relational_exp1Correct ) ;
        if ( !maybe_relational_exp1Correct ) {
          correct = false ;
          return ;
        } // if
      } // if
      else {
        correct = true ;
        return ;
      } // else
    } while ( 1 ) ;
  } // if
  else {
    correct = false ;
    return ;
  } // else
} // Parser::Maybe_equality_exp()

void Parser::Rest_of_maybe_equality_exp( bool &correct ) {
  Token token, peek ;
  bool r_maybe_relational_exp1Correct = false, maybe_relational_exp1Correct = false ;

  Rest_of_maybe_relational_exp( r_maybe_relational_exp1Correct ) ;
  if ( r_maybe_relational_exp1Correct ) {
    do {
      peek = mScanner.PeekToken() ; // peek 'EQ' or NEQ
      if ( peek.type == EQ || peek.type == NEQ ) {
        token = mScanner.GetToken() ; // get EQ or NEQ
        mTokenList.push_back( token ) ; // push to token buffer
        Maybe_relational_exp( maybe_relational_exp1Correct ) ;
        if ( !maybe_relational_exp1Correct ) {
          correct = false ;
          return ;
        } // if
      } // if
      else {
        correct = true ;
        return ;
      } // else
    } while ( 1 ) ;
  } // if
  else {
    correct = false ;
    return ;
  } // else
} // Parser::Rest_of_maybe_equality_exp()

void Parser::Maybe_relational_exp( bool &correct ) {
  Token token, peek ;
  bool maybe_shift_exp1Correct = false ;

  Maybe_shift_exp( maybe_shift_exp1Correct ) ;
  if ( maybe_shift_exp1Correct ) {
    do {
      peek = mScanner.PeekToken() ; // peek '>' or '<'
      if ( peek.type == GREATER || peek.type == LESS || peek.type == LE || peek.type == GE ) {
        token = mScanner.GetToken() ; // get >, <, >=, <= 
        mTokenList.push_back( token ) ; // push to token buffer
        Maybe_shift_exp( maybe_shift_exp1Correct ) ;
        if ( !maybe_shift_exp1Correct ) {
          correct = false ;
          return ;
        } // if
      } // if
      else {
        correct = true ;
        return ;
      } // else
    } while ( 1 ) ;
  } // if
  else {
    correct = false ;
    return ;
  } // else
} // Parser::Maybe_relational_exp()

void Parser::Rest_of_maybe_relational_exp( bool &correct ) {
  Token token, peek ;
  bool r_maybe_shift_exp1Correct = false, maybe_shift_exp1Correct = false ;

  Rest_of_maybe_shift_exp( r_maybe_shift_exp1Correct ) ;
  if ( r_maybe_shift_exp1Correct ) {
    do {
      peek = mScanner.PeekToken() ; // peek '>' or '<'
      if ( peek.type == GREATER || peek.type == LESS || peek.type == LE || peek.type == GE ) {
        token = mScanner.GetToken() ; // >, <, >=, <= 
        mTokenList.push_back( token ) ; // push to token buffer
        Maybe_shift_exp( maybe_shift_exp1Correct ) ;
        if ( !maybe_shift_exp1Correct ) {
          correct = false ;
          return ;
        } // if
      } // if
      else {
        correct = true ;
        return ;
      } // else
    } while ( 1 ) ;
  } // if
  else {
    correct = false ;
    return ;
  } // else
} // Parser::Rest_of_maybe_relational_exp()

void Parser::Maybe_shift_exp( bool &correct ) {
  Token token, peek ;
  bool maybe_additive_exp1Correct = false ;

  Maybe_additive_exp( maybe_additive_exp1Correct ) ;
  if ( maybe_additive_exp1Correct ) {
    do {
      peek = mScanner.PeekToken() ; // peek '>>' or '<<'
      if ( peek.type == LS || peek.type == RS ) {
        token = mScanner.GetToken() ; // get >, <, >=, <= 
        mTokenList.push_back( token ) ; // push to token buffer
        Maybe_additive_exp( maybe_additive_exp1Correct ) ;
        if ( !maybe_additive_exp1Correct ) {
          correct = false ;
          return ;
        } // if
      } // if
      else {
        correct = true ;
        return ;
      } // else
    } while ( 1 ) ;
  } // if
  else {
    correct = false ;
    return ;
  } // else
} // Parser::Maybe_shift_exp()

void Parser::Rest_of_maybe_shift_exp( bool &correct ) {
  Token token, peek ;
  bool r_maybe_additive_exp1Correct, maybe_additive_exp1Correct = false ;

  Rest_of_maybe_additive_exp( r_maybe_additive_exp1Correct ) ;
  if ( r_maybe_additive_exp1Correct ) {
    do {
      peek = mScanner.PeekToken() ; // peek '>>' or '<<'
      if ( peek.type == LS || peek.type == RS ) {
        token = mScanner.GetToken() ; // get >, <, >=, <=
        mTokenList.push_back( token ) ; // push to token buffer
        Maybe_additive_exp( maybe_additive_exp1Correct ) ;
        if ( !maybe_additive_exp1Correct ) {
          correct = false ;
          return ;
        } // if
      } // if
      else {
        correct = true ;
        return ;
      } // else
    } while ( 1 ) ;
  } // if
  else {
    correct = false ;
    return ;
  } // else
} // Parser::Rest_of_maybe_shift_exp()

void Parser::Maybe_additive_exp( bool &correct ) {
  Token token, peek ;
  bool maybe_mult_exp1Correct = false ;

  Maybe_mult_exp( maybe_mult_exp1Correct ) ;
  if ( maybe_mult_exp1Correct ) {
    do {
      peek = mScanner.PeekToken() ; // peek '+' or '-'
      if ( peek.type == ADD || peek.type == MINUS ) {
        token = mScanner.GetToken() ; // get +, -
        mTokenList.push_back( token ) ; // push to token buffer
        Maybe_mult_exp( maybe_mult_exp1Correct ) ;
        if ( !maybe_mult_exp1Correct ) {
          correct = false ;
          return ;
        } // if
      } // if
      else {
        correct = true ;
        return ;
      } // else
    } while ( 1 ) ;
  } // if
  else {
    correct = false ;
    return ;
  } // else
} // Parser::Maybe_additive_exp()

void Parser::Rest_of_maybe_additive_exp( bool &correct ) {
  Token token, peek ;
  bool r_maybe_mult_exp1Correct = false, maybe_mult_exp1Correct = false ;

  Rest_of_maybe_mult_exp( r_maybe_mult_exp1Correct ) ;
  if ( r_maybe_mult_exp1Correct ) {
    do {
      peek = mScanner.PeekToken() ; // peek '+' or '-'
      if ( peek.type == ADD || peek.type == MINUS ) {
        token = mScanner.GetToken() ; // get +, -
        mTokenList.push_back( token ) ; // push to token buffer
        Maybe_mult_exp( maybe_mult_exp1Correct ) ;
        if ( !maybe_mult_exp1Correct ) {
          correct = false ;
          return ;
        } // if
      } // if
      else {
        correct = true ;
        return ;
      } // else
    } while ( 1 ) ;
  } // if
  else {
    correct = false ;
    return ;
  } // else
} // Parser::Rest_of_maybe_additive_exp()

void Parser::Maybe_mult_exp( bool &correct ) {
  bool unary_exp1Correct = false, r_o_maybe_mult_exp1Correct = false ;
  Unary_exp( unary_exp1Correct ) ;
  if ( unary_exp1Correct ) {
    Rest_of_maybe_mult_exp( r_o_maybe_mult_exp1Correct ) ;
    if ( r_o_maybe_mult_exp1Correct ) {
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
    return ;
  } // else
} // Parser::Maybe_mult_exp()

void Parser::Rest_of_maybe_mult_exp( bool &correct ) {
  Token token, peek ;
  bool unary_exp1Correct = false ;
  do {
    peek = mScanner.PeekToken() ;
    if ( peek.type == MULT || peek.type == DIV || peek.type == MOD ) {
      token = mScanner.GetToken() ; // get '*' '/' '%'
      mTokenList.push_back( token ) ; // push to token buffer
      Unary_exp( unary_exp1Correct ) ;
      if ( !unary_exp1Correct ) {
        correct = false ;
        return ;
      } // if
    } // if
    else {
      // could be empty !
      correct = true ;
      return ;
    } // else
  } while ( 1 ) ;
} // Parser::Rest_of_maybe_mult_exp()

void Parser::Unary_exp( bool &correct ) {
  Token token, peek ;
  bool signed_unary_exp1Correct = false, unsigned_unary_exp1Correct = false, expression1Correct = false ;

  peek = mScanner.PeekToken() ;
  if ( Sign( peek ) ) {
    while ( !Sign( peek ) ) {
      token = mScanner.GetToken() ;
      mTokenList.push_back( token ) ; // push to token buffer
      peek = mScanner.PeekToken() ;
    } // while()

    Signed_unary_exp( signed_unary_exp1Correct ) ;
    if ( signed_unary_exp1Correct ) {
      correct = true ;
      return ;
    } // if
    else {
      correct = false ;
      return ;
    } // else
  } // if
  else if ( peek.type == PP || peek.type == MM ) {
    token = mScanner.GetToken() ; // get PP, MM
    mTokenList.push_back( token ) ; // push to token buffer
    peek = mScanner.PeekToken() ;
    if ( peek.type == IDENT ) {
      if ( !IsListFunction( peek ) && !IsCinCout( peek ) ) {
        if ( uIsFunction ) {
          if ( !HasFunctionVariable( peek.tokenValue ) ) {
            Undefined() ;
            correct = false ;
            return ;
          } // if

          if ( !IntheTempList( peek.tokenValue ) ) {
            Undefined() ;
            correct = false ;
            return ;
          } // if
        } // if

        if ( !uIsFunction && !IntheList( peek.tokenValue ) ) { // Undefined
          Undefined() ;
          correct = false ;
          return ;
        } // if

        if ( !uIsFunction && !IntheTempList( peek.tokenValue ) && mTempList.size() > 0 ) { // Undefined
          Undefined() ;
          correct = false ;
          return ;
        } // if
      } // if

      token = mScanner.GetToken() ; // get Identitifier
      mTokenList.push_back( token ) ; // push to token buffer
      peek = mScanner.PeekToken() ; // '['
      if ( peek.type == LB ) {
        token = mScanner.GetToken() ; // get '['
        mTokenList.push_back( token ) ; // push to token buffer
        Expression( expression1Correct ) ;
        if ( expression1Correct ) {
          peek = mScanner.PeekToken() ; // peek ']'
          if ( peek.type == RB ) {
            token = mScanner.GetToken() ; // get ']'
            mTokenList.push_back( token ) ; // push to token buffer
            correct = true ;
            return ;
          } // if
          else {
            correct = false ;
            ErrorMessage() ;
            return ;
          } // else
        } // if
        else {
          correct = false ;
          return ;
        } // else
      } // if
      else {
        correct = true ;
        return ;
      } // else
    } // if
    else {
      correct = false ;
      ErrorMessage() ;
      return ;
    } // else
  } // else if
  else {
    Unsigned_unary_exp( unsigned_unary_exp1Correct ) ;
    if ( unsigned_unary_exp1Correct ) {
      correct = true ;
      return ;
    } // if
    else {
      correct = false ;
      return ;
    } // else
  } // else
} // Parser::Unary_exp()

void Parser::Signed_unary_exp( bool &correct ) {
  Token token, peek ;
  bool actual_parameter_list1Correct = false, expression1Correct = false ;

  peek = mScanner.PeekToken() ; // peek Ident, Constant, '('
  if ( peek.type == IDENT ) {
    if ( !IsListFunction( peek ) && !IsCinCout( peek ) ) {
      if ( uIsFunction ) {
        if ( !HasFunctionVariable( peek.tokenValue ) ) {
          Undefined() ;
          correct = false ;
          return ;
        } // if

        if ( !IntheTempList( peek.tokenValue ) ) {
          Undefined() ;
          correct = false ;
          return ;
        } // if
      } // if

      if ( !uIsFunction && !IntheList( peek.tokenValue ) ) { // Undefined
        Undefined() ;
        correct = false ;
        return ;
      } // if

      if ( !uIsFunction && !IntheTempList( peek.tokenValue ) && mTempList.size() > 0 ) { // Undefined
        Undefined() ;
        correct = false ;
        return ;
      } // if
    } // if

    token = mScanner.GetToken() ; // get Ident
    mTokenList.push_back( token ) ; // push to token buffer
    peek = mScanner.PeekToken() ; // peek '(', '['
    if ( peek.type == LEFT_PAREN ) {
      token = mScanner.GetToken() ; // get '('
      mTokenList.push_back( token ) ; // push to token buffer
      Actual_parameter_list( actual_parameter_list1Correct ) ;
      if ( actual_parameter_list1Correct ) {
        peek = mScanner.PeekToken() ; // peek ')'
        if ( peek.type == RIGHT_PAREN ) {
          token = mScanner.GetToken() ; // get ')'
          mTokenList.push_back( token ) ; // push to token buffer
          correct = true ;
          return ;
        } // if
        else {
          correct = false ;
          ErrorMessage() ;
          return ;
        } // else
      } // if
      else {
        peek = mScanner.PeekToken() ;
        if ( peek.type == RIGHT_PAREN ) {
          token = mScanner.GetToken() ;
          mTokenList.push_back( token ) ; // push to token buffer
          correct = true ;
          return ;
        } // if
        else {
          correct = false ;
          ErrorMessage() ;
          return ;
        } // else
      } // else
    } // if
    else if ( peek.type == LB ) {
      token = mScanner.GetToken() ; // get '['
      mTokenList.push_back( token ) ; // push to token buffer
      Expression( expression1Correct ) ;
      if ( expression1Correct ) {
        peek = mScanner.PeekToken() ; // peek ']'
        if ( peek.type == RB ) {
          token = mScanner.GetToken() ; // get ']'
          mTokenList.push_back( token ) ; // push to token buffer
          correct = true ;
          return ;
        } // if
        else {
          correct = false ;
          ErrorMessage() ;
          return ;
        } // else
      } // if
      else {
        correct = false ;
        return ;
      } // else
    } // else if
    else {
      correct = true ;
      return ;
    } // else
  } // if
  else if ( peek.type == CONSTANT ) {
    token = mScanner.GetToken() ;
    mTokenList.push_back( token ) ; // push to token buffer
    correct = true ;
    return ;
  } // else if
  else if ( peek.type == ADD || peek.type == MINUS ) {
    token = mScanner.GetToken() ;
    mTokenList.push_back( token ) ;
    peek = mScanner.PeekToken() ;
    if ( peek.type == CONSTANT ) {
      token = mScanner.GetToken() ;
      mTokenList.push_back( token ) ;
      correct = true ;
      return ;
    } // if
    else {
      Print_Unexpected( token ) ;
      ErrorProcess() ;
      correct = false ;
      return ;
    } // else
  } // else if
  else if ( peek.type == LEFT_PAREN ) {
    token = mScanner.GetToken() ; // get '('
    mTokenList.push_back( token ) ; // push to token buffer
    Expression( expression1Correct ) ;
    if ( expression1Correct ) {
      peek = mScanner.PeekToken() ; // peek ')'
      if ( peek.type == RIGHT_PAREN ) {
        token = mScanner.GetToken() ; // get ')'
        mTokenList.push_back( token ) ; // push to token buffer
        correct = true ;
        return ;
      } // if
      else {
        correct = false ;
        ErrorMessage() ;
        return ;
      } // else
    } // if
    else {
      correct = false ;
      return ;
    } // else
  } // else if
  else {
    correct = false ;
    ErrorMessage() ;
    return ; 
  } // else
} // Parser::Signed_unary_exp()

void Parser::Unsigned_unary_exp( bool &correct ) {
  Token token, peek ;
  bool actual_parameter_list1Correct = false, expression1Correct = false ;

  peek = mScanner.PeekToken() ; // peek Ident, Constant, '('
  if ( peek.type == IDENT ) {
    if ( !IsListFunction( peek ) && !IsCinCout( peek ) ) {
      if ( uIsFunction ) {
        if ( !HasFunctionVariable( peek.tokenValue ) ) {
          Undefined() ;
          correct = false ;
          return ;
        } // if

        if ( !IntheTempList( peek.tokenValue ) ) {
          Undefined() ;
          correct = false ;
          return ;
        } // if
      } // if

      if ( !uIsFunction && !IntheList( peek.tokenValue ) ) { // Undefined
        Undefined() ;
        correct = false ;
        return ;
      } // if

      if ( !uIsFunction && !IntheTempList( peek.tokenValue ) && mTempList.size() > 0 ) { // Undefined
        Undefined() ;
        correct = false ;
        return ;
      } // if
    } // if

    token = mScanner.GetToken() ; // get Ident
    mTokenList.push_back( token ) ; // push to token buffer
    peek = mScanner.PeekToken() ; // peek '(', '['
    if ( peek.type == LEFT_PAREN ) {
      token = mScanner.GetToken() ; // get '('
      mTokenList.push_back( token ) ; // push to token buffer
      Actual_parameter_list( actual_parameter_list1Correct ) ;
      if ( actual_parameter_list1Correct ) {
        peek = mScanner.PeekToken() ; // peek ')'
        if ( peek.type == RIGHT_PAREN ) {
          token = mScanner.GetToken() ; // get ')'
          mTokenList.push_back( token ) ; // push to token buffer
          correct = true ;
          return ;
        } // if
        else {
          correct = false ;
          ErrorMessage() ;
          return ;
        } // else
      } // if
      else {
        peek = mScanner.PeekToken() ;
        if ( peek.type == RIGHT_PAREN ) {
          token = mScanner.GetToken() ;
          mTokenList.push_back( token ) ; // push to token buffer
          correct = true ;
          return ;
        } // if
        else {
          correct = false ;
          ErrorMessage() ;
          return ;
        } // else
      } // else
    } // if
    else if ( peek.type == LB ) {
      token = mScanner.GetToken() ; // get '['
      mTokenList.push_back( token ) ; // push to token buffer
      Expression( expression1Correct ) ;
      if ( expression1Correct ) {
        peek = mScanner.PeekToken() ; // peek ']'
        if ( peek.type == RB ) {
          token = mScanner.GetToken() ; // get ']'
          mTokenList.push_back( token ) ; // push to token buffer
          peek = mScanner.PeekToken() ; // peek PP or MM
          if ( peek.type == PP || peek.type == MM ) {
            token = mScanner.GetToken() ; // get PP or MM
            mTokenList.push_back( token ) ; // push to token buffer
            correct = true ;
            return ;
          } // if
          else {
            correct = true ;
            return ;
          } // else
        } // if
        else {
          correct = false ;
          ErrorMessage() ;
          return ;
        } // else
      } // if
      else {
        correct = false ;
        return ;
      } // else
    } // else if
    else {
      correct = true ;
      return ;
    } // else
  } // if
  else if ( peek.type == CONSTANT ) {
    token = mScanner.GetToken() ; // get Constant
    mTokenList.push_back( token ) ; // push to token buffer
    correct = true ;
    return ;
  } // else if
  else if ( peek.type == ADD || peek.type == MINUS ) {
    token = mScanner.GetToken() ;
    mTokenList.push_back( token ) ;
    peek = mScanner.PeekToken() ;
    if ( peek.type == CONSTANT ) {
      token = mScanner.GetToken() ;
      mTokenList.push_back( token ) ;
      correct = true ;
      return ;
    } // if
    else {
      Print_Unexpected( token ) ;
      ErrorProcess() ;
      correct = false ;
      return ;
    } // else
  } // else if
  else if ( peek.type == LEFT_PAREN ) {
    token = mScanner.GetToken() ; // get '('
    mTokenList.push_back( token ) ; // push to token buffer
    Expression( expression1Correct ) ;
    if ( expression1Correct ) {
      peek = mScanner.PeekToken() ; // peek ')'
      if ( peek.type == RIGHT_PAREN ) {
        token = mScanner.GetToken() ; // get ')'
        mTokenList.push_back( token ) ; // push to token buffer
        correct = true ;
        return ;
      } // if
      else {
        correct = false ;
        ErrorMessage() ;
        return ;
      } // else
    } // if
    else {
      correct = false ;
      return ;
    } // else
  } // else if
  else {
    correct = false ;
    ErrorMessage() ;
    return ;
  } // else
} // Parser::Unsigned_unary_exp()

bool Parser::SameType( string ID, string Type ) {
  for ( int i = 0 ; i < mVariableList.size() ; i++ ) {
    if ( strcmp( mVariableList[i].id.c_str(), ID.c_str() ) == 0 ) {
      if ( strcmp( mVariableList[i].type.c_str(), Type.c_str() ) == 0 )
        return true ;
    } // if
  } // for

  return false ;
} // Parser::SameType()

bool Parser::SameConstant( string ID, string Constant ) {
  for ( int i = 0 ; i < mVariableList.size() ; i++ ) {
    if ( strcmp( mVariableList[i].id.c_str(), ID.c_str() ) == 0 ) {
      if ( strcmp( mVariableList[i].constant.c_str(), Constant.c_str() ) == 0 )
        return true ;
    } // if
  } // for

  return false ;
} // Parser::SameConstant()

bool Parser::IntheList( string ID ) {
  for ( int i = 0 ; i < mVariableList.size() ; i++ ) {
    if ( strcmp( mVariableList[i].id.c_str(), ID.c_str() ) == 0 ) {
      return true ;
    } // if
  } // for

  return false ;
} // Parser::IntheList()

bool Parser::IntheFunctionList( string ID ) {
  for ( int i = 0 ; i < mFunctionList.size() ; i++ ) {
    if ( strcmp( mFunctionList[i].function_id.tokenValue.c_str(), ID.c_str() ) == 0 ) {
      return true ;
    } // if
  } // for

  return false ;
} // Parser::IntheFunctionList()

bool Parser::IntheTempList( string ID ) {
  for ( int i = 0 ; i < mTempList.size() ; i++ ) {
    if ( strcmp( mTempList[i].id.c_str(), ID.c_str() ) == 0 ) {
      return true ;
    } // if
  } // for

  return false ;
} // Parser::IntheTempList()

bool Parser::IntheFVariableList( string ID ) {
  for ( int i = 0 ; i < mFunctionVariableList.size() ; i++ ) {
    if ( strcmp( mFunctionVariableList[i].function_id.c_str(), ID.c_str() ) == 0 ) {
      return true ;
    } // if
  } // for

  return false ;
} // Parser::IntheFVariableList()

void Parser::Save_Definition() {
  if ( uIsVariable && !uIsFunction ) { // Variable
    for ( int i = 1 ; i < mTokenList.size() ; i++ ) {
      Variable variable ;
      variable.type = mTokenList[0].tokenValue ; // give it type
      if ( mTokenList[i].type == IDENT ) {
        variable.id = mTokenList[i].tokenValue ;
        if ( IntheList( variable.id ) ) {
          Print_NewDefinition_Variable( variable.id ) ;
        } // if

        else {
          Print_Definition_Variable( variable.id ) ;
        } // else
      } // if

      if ( mTokenList[i+1].type == LB ) {
        variable.constant = mTokenList[i+2].tokenValue ;
      } // if

      if ( variable.id != "" && !IntheList( variable.id ) ) {
        mVariableList.push_back( variable ) ;
      } // if
      else if ( variable.id != "" && IntheList( variable.id ) ) {
        if ( SameType( variable.id, variable.type ) ) {
          if ( !SameConstant( variable.id, variable.constant ) ) {
            // change the variable constant
            for ( int j = 0 ; j < mVariableList.size() ; j++ ) {
              if ( strcmp( mVariableList[j].id.c_str(), variable.id.c_str() ) == 0 ) {
                mVariableList[j].constant = variable.constant ;
              } // if
            } // for
          } // if
        } // if

        else { // change type and constant
          if ( !SameConstant( variable.id, variable.constant ) ) {
            for ( int j = 0 ; j < mVariableList.size() ; j++ ) {
              if ( strcmp( mVariableList[j].id.c_str(), variable.id.c_str() ) == 0 ) {
                mVariableList[j].type = variable.type ;
                mVariableList[j].constant = variable.constant ;
              } // if
            } // for
          } // if

          else {
            // change type
            for ( int j = 0 ; j < mVariableList.size() ; j++ ) {
              if ( strcmp( mVariableList[j].id.c_str(), variable.id.c_str() ) == 0 ) {
                mVariableList[j].type = variable.type ;
              } // if
            } // for
          } // else
        } // else
      } // else if
    } // for
  } // if
  else if ( !uIsVariable && uIsFunction ) {
    cout << endl << "Function definition " << endl ;
    Function function ;
    // get function type and id
    int pos_FisrstLCB = 0 ;
    bool hasType = false, hasParameter = false ;

    for ( int i = 0 ; i < mTokenList.size() ; i++ ) { // get parameter list
      Variable parameter ;
      if ( !hasType ) {
        function.type = mTokenList[0] ;
        function.function_id = mTokenList[1] ;
        if ( !IntheFunctionList( function.function_id.tokenValue ) ) {
          Print_Definition_Function( function.function_id.tokenValue ) ;
        } // if
        else {
          Print_NewDefinition_Function( function.function_id.tokenValue ) ;
        } // else

        hasType = true ;
      } // if
      else if ( !hasParameter && Type_specifier( mTokenList[i] ) ) {
        parameter.type = mTokenList[i].tokenValue ;
        parameter.id = mTokenList[i+1].tokenValue ;
        if ( mTokenList[i+2].type == LB ) {
          parameter.constant = mTokenList[i+3].tokenValue ;
        } // if

        function.parameter.push_back( parameter ) ;
      } // if
      else if ( !hasParameter && mTokenList[i].type == LCB ) {
        function.statement.push_back( mTokenList[i] ) ;
        pos_FisrstLCB = i ;
        hasParameter = true ;
      } // else if
      else if ( hasType && hasParameter ) {
        function.statement.push_back( mTokenList[i] ) ;
      } // else if
    } // for

    if ( !IntheFunctionList( function.function_id.tokenValue.c_str() ) ) {
      mFunctionList.push_back( function ) ;
    } // if
    else {
      // change value mFunctionList and mFunctionVariableList
      for ( int i = 0 ; i < mFunctionList.size() ; i++ ) {
        if ( strcmp( function.function_id.tokenValue.c_str(),
                     mFunctionList[i].function_id.tokenValue.c_str() ) == 0 ) {
          mFunctionList[i].type = function.type ;
          mFunctionList[i].parameter = function.parameter ;
          mFunctionList[i].statement = function.statement ;
        } // if
      } // for

      // delete new definition void Fun() { int a ;} void Fun(){int a, b ;} 

      for ( int i = 0 ; i < mFunctionVariableList.size() ; i++ ) {
        if ( strcmp( function.function_id.tokenValue.c_str(), 
                     mFunctionVariableList[i].function_id.c_str() ) == 0 ) {
          mFunctionVariableList[i].functionVariableList = gFunctionVariable.functionVariableList ;
        } // if
      } // for
    } // else

    cout << endl << "Function Type and ID : " << function.type.tokenValue
         << " " << function.function_id.tokenValue << endl ;   
    for ( int j = 0 ; j < function.parameter.size() ; j++ ) {
      cout << "Parameter List : " << function.parameter[j].type 
           << "  " << function.parameter[j].id << "  " << function.parameter[j].constant << endl ;
    } // for

    for ( int i = 0 ; i < function.statement.size() ; i++ ) {
      cout << "Statement : " << function.statement[i].tokenValue << endl ;
    } // for
  } // else if

  /*
  for ( int i = 0 ; i < mTokenList.size() ; i++ ) {
    // cout << "mTokenList Info : " << mTokenList[i].tokenValue << endl ;
  } // for
  */

  CleanTokenBuffer() ;
} // Parser::Save_Definition()

void Parser::Print_NewDefinition_Variable( string ID ) {
  printf( "New definition of %s entered ...\n", ID.c_str() ) ;
} // Parser::Print_NewDefinition_Variable()

void Parser::Print_NewDefinition_Function( string ID ) {
  printf( "New definition of %s() entered ...\n", ID.c_str() ) ;
} // Parser::Print_NewDefinition_Function()

void Parser::Print_Definition_Variable( string ID ) {
  printf( "Definition of %s entered ...\n", ID.c_str() ) ;
} // Parser::Print_Definition_Variable()

void Parser::Print_Definition_Function( string ID ) {
  printf( "Definition of %s() entered ...\n", ID.c_str() ) ;
} // Parser::Print_Definition_Function()


void Parser::Sort() {
  int i, j ;
  int n = mVariableList.size() ;
  Variable temp ;
  for ( i = 0 ; i < n - 1 ; i++ ) {
    for ( j = 0 ; j < n - i - 1 ; j ++ ) {
      if ( mVariableList[j].id > mVariableList[j+1].id ) {
        temp = mVariableList[j+1] ;
        mVariableList[j+1] = mVariableList[j] ;
        mVariableList[j] = temp ;
      } // if
    } // for
  } // for
} // Parser::Sort()

bool Parser::Done( Token peek ) {
  Token token ;
  if ( strcmp( peek.tokenValue.c_str(), "Done" ) == 0 ) {
    token = mScanner.GetToken() ;
    peek = mScanner.PeekToken() ;
    if ( peek.type == LEFT_PAREN ) {
      token = mScanner.GetToken() ;
      peek = mScanner.PeekToken() ;
      if ( peek.type == RIGHT_PAREN ) {
        token = mScanner.GetToken() ;
        peek = mScanner.PeekToken() ;
        if ( peek.type == SEMICOLON ) {
          token = mScanner.GetToken() ;
          return true ;
        } // if
        else {
          ErrorMessage() ;
        } // else
      } // if
      else {
        ErrorMessage() ;
      } // else
    } // if
    else {
      ErrorMessage() ;
    } // else
  } // if

  return false ;
} // Parser::Done()

void Parser::CleanTokenBuffer() {
  mTokenList.clear() ;
  gFunctionVariable.function_id = "" ;
  gFunctionVariable.functionVariableList.clear() ;
} // Parser::CleanTokenBuffer()

void Parser::ErrorMessage() {
  Token token ;
  token = mScanner.GetToken() ;
  if ( IsUnrecognized( token.tokenValue ) ) {
    Print_Unrecognized( token ) ;
  } // if
  else {
    Print_Unexpected( token ) ;
  } // else

  mScanner.InitializeLine() ;
  ErrorProcess() ;
} // Parser::ErrorMessage()

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

bool Parser::HasFunctionVariable( string ID ) {
  for ( int i = 0 ; i < mFunctionVariableList.size() ; i++ ) {
    if ( strcmp( gFunctionVariable.function_id.c_str(),
                 mFunctionVariableList[i].function_id.c_str() ) == 0 ) {
      for ( int j = 0 ; j < mFunctionVariableList[i].functionVariableList.size() ; j++ ) {
        if ( strcmp( ID.c_str(), mFunctionVariableList[i].functionVariableList[j].id.c_str() ) == 0 ) {
          return true ;
        } // if
      } // for
    } // if
  } // for

  return false ;
} // Parser::HasFunctionVariable()

bool Parser::IsListFunction( Token peek ) {
  if ( strcmp( peek.tokenValue.c_str(), "ListAllVariables" ) == 0 ) {
    return true ;
  } // if

  if ( strcmp( peek.tokenValue.c_str(), "ListVariable" ) == 0 ) {
    return true ;
  } // if

  if ( strcmp( peek.tokenValue.c_str(), "ListAllFunctions" ) == 0 ) {
    return true ;
  } // if

  if ( strcmp( peek.tokenValue.c_str(), "ListFunction" ) == 0 ) {
    return true ;
  } // if

  return false ;
} // Parser::IsListFunction()

bool Parser::IsCinCout( Token peek ) {
  if ( strcmp( peek.tokenValue.c_str(), "cin" ) == 0 || strcmp( peek.tokenValue.c_str(), "cout" ) == 0 ) {
    return true ;
  } // if

  return false ;
} // Parser::IsCinCout()

void Parser::ErrorProcess() {
  // read all garbage char
  char temp_peek = cin.peek() ;
  while ( temp_peek != '\n' ) {
    cin.get() ;
    temp_peek = cin.peek() ;
  } // while()
} // Parser::ErrorProcess()

void Parser::Undefined() {
  Token token ;
  token = mScanner.GetToken() ;
  Print_Undefined( token ) ;
  mScanner.InitializeLine() ;
  ErrorProcess() ;
} // Parser::Undefined()

void Parser::Print_Unrecognized( Token token ) {
  string output = "unrecognized token with first char : '" + token.tokenValue + "'" ;
  printf( "Line %d : %s\n", token.line, output.c_str() ) ; // c++ string to c string
} // Parser::Print_Unrecognized()

void Parser::Print_Unexpected( Token token ) {
  string output = "unexpected token : '" + token.tokenValue + "'" ;
  printf( "Line %d : %s\n", token.line, output.c_str() ) ; // c++ string to c string
} // Parser::Print_Unexpected()

void Parser::Print_Undefined( Token token ) {
  string output = "undefined identifier : '" + token.tokenValue + "'" ;
  printf( "Line %d : %s\n", token.line, output.c_str() ) ; // c++ string to c string
} // Parser::Print_Undefined()

int main() {
  char ch = '\0' ; // read '\n'
  Token token ;
  bool jumpOut = false ;
  Parser parser ;
  Scanner scanner;
  // scanf( "%d%c", &uTestNum, &ch ) ;
  printf( "Our-C running ...\n" ) ;
  while ( jumpOut != true ) {
    printf( "> " ) ; 
    if ( !parser.User_input() ) {
        jumpOut = true ;
    } // if
  } // while()

  printf( "Our-C exited ...\n" ) ;
} // main()
