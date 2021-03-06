// zadanie 2: wykonac po kolei Exercise 1,2 i 3 ze str.253
// Przysłać końcową wersję po ulepszeniu kalkulatora poprzez zrobienie wszystkich trzech Exercise.
// This program implements a basic expression calculator based in this input
// grammar:
//
//  Calculation:
//      Statement
//      Print
//      Quit
//      Calculation Statement
//  Statement:
//      Declaration
//      Expression
//  Print:
//      ";"
//  Quit:
//      "exit"
//  Declaration:
//      "let" Name "=" Expression
//      "const" Name "=" Expression
//  Expression:
//      Term
//      Expression "+" Term
//      Expression "-" Term
//  Term:
//      Primary
//      Term "*" Primary
//      Term "/" Primary
//      Term "%" Primary
//  Primary:
//      Number
//      "("Expression")"
//      "-" Primary
//      "+" Primary
//      Name
//          Name = Expression
//
//  Number:
//      [floating-point-literal]
//  Name:
//      [alphabetic-char with '_']
//
#include "std_lib_facilities.hpp"

//------------------------------------------------------------------------------

const char number = '8';    // t.kind==number means that t is a number Token
const char quit   = 'q';    // t.kind==quit means that t is a quit Token
const char print  = ';';    // t.kind==print means that t is a print Token
const char name   = 'a';    // name token
const char let    = 'L';    // declaration token
const char con    = 'C';    // const  token
const string autorize = "let";		// declaration keyword
const string conkey = "const";	// const keyword
const string prompt  = "> ";
const string result  = "= "; // used to indicate that what follows is a result
const string quitkey = "exit"; // keyword to quit

//------------------------------------------------------------------------------

class Token {
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value
    string name;      // for names: name itself
    Token(char ch)             : kind(ch), value(0)   {}
    Token(char ch, double val) : kind(ch), value(val) {}
    Token(char ch, string n)   : kind(ch), name(n)    {} // make a Token from a char and string
};

//------------------------------------------------------------------------------

class Token_stream {
public:
    Token_stream();   // make a Token_stream that reads from cin
    Token get();      // get a Token (get() is defined elsewhere)
    void unget(Token t);
    void ignore(char c);
private:
    bool full;        // is there a Token in the buffer?
    Token buffer;     // here is where we keep a Token put back using unget()
};

//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
:full(false), buffer(0)    // no Token in buffer
{
}

//------------------------------------------------------------------------------

// The unget() member function puts its argument back into the Token_stream's buffer:
void Token_stream::unget(Token t)
{
    if (full) error("unget() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

Token Token_stream::get() // read characters from cin and compose a Token
{
    if (full) {         // check if we already have a Token ready
        full=false;
        return buffer;
    }

    char ch;
    cin >> ch;          // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
    case quit:
    case print:
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '=':
        return Token(ch); // let each character represent itself
    case '.':             // a floating-point literal can start with a dot
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':    // numeric literal
    {
        cin.unget();
        double val;
        cin >> val;
        return Token(number,val);
    }
    default:
        if (isalpha(ch)) {	// start with a letter
            string s;
            s += ch;
            while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch=='_')) s+=ch;	// letters digits and underscores
            cin.unget();
            if (s == autorize) return Token(let); // keyword "let"
            if (s == conkey) return Token(con); // keyword "const"
            if (s == quitkey) return Token(quit); // quit keyword
            return Token(name,s);
        }
        error("Bad token");
    }
}

//------------------------------------------------------------------------------

void Token_stream::ignore(char c)
    // c represents the kind of a Token
{
    // first look in buffer:
    if (full && c==buffer.kind) {
        full = false;
        return;
    }
    full = false;

    // now search input:
    char ch = 0;
    while (cin>>ch)
        if (ch==c) return;
}

//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and unget()

//------------------------------------------------------------------------------

class Variable {
public:
    string name;
    double value;
	bool var;	// variable (true) or constant (false)
    Variable (string n, double v, bool va = true) :name(n), value(v), var(va) { }
};

//------------------------------------------------------------------------------

vector<Variable> names;

//------------------------------------------------------------------------------

double get_value(string s)
    // return the value of the Variable names s
{
    for (int i = 0; i<names.size(); ++i)
        if (names[i].name == s) return names[i].value;
    error("get: undefined variable ", s);
}

//------------------------------------------------------------------------------

void set_value(string s, double d)
    // set the Variable named s to d
{
    for (int i = 0; i<names.size(); ++i)
        if (names[i].name == s) {
			if (names[i].var==false) error(s," is a constant");
            names[i].value = d;
            return;
        }
    error("set: undefined variable ", s);
}

//------------------------------------------------------------------------------

bool is_declared(string var)
    // is var already in names?
{
    for (int i = 0; i<names.size(); ++i)
        if (names[i].name == var) return true;
    return false;
}

//------------------------------------------------------------------------------

double define_name(string s, double val, bool var=true)
    // add (s,val,var) to names
{
    if (is_declared(s)) error(s," declared twice");
    names.push_back(Variable(s,val,var));
    return val;
}

//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()

//------------------------------------------------------------------------------

// deal with numbers and parentheses
double primary()
{
    Token t = ts.get();
    switch (t.kind) {
    case '(':           // handle '(' expression ')'
        {
            double d = expression();
            t = ts.get();
            if (t.kind != ')') error("')' expected");
            return d;
        }
    case number:
        return t.value;    // return the number's value
    case name:
		{
			Token next = ts.get();
			if (next.kind == '=') {
				double d = expression();
				set_value(t.name,d);
				return d;
			}
			else {
				ts.unget(next);
				return get_value(t.name);
			}
		}
    case '-':
        return - primary();
    case '+':
        return primary();
    default:
        error("primary expected");
    }
}

//------------------------------------------------------------------------------

// deal with *, /, and %
double term()
{
    double left = primary();
    Token t = ts.get(); // get the next token from token stream

    while(true) {
        switch (t.kind) {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
            {
                double d = primary();
                if (d == 0) error("divide by zero");
                left /= d;
                t = ts.get();
                break;
            }
        case '%':
            {
                int i1 = narrow_cast<int>(left);
                int i2 = narrow_cast<int>(term());
                if (i2 == 0) error("%: divide by zero");
                left = i1%i2;
                t = ts.get();
                break;
            }
        default:
            ts.unget(t);        // put t back into the token stream
            return left;
        }
    }
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
    double left = term();
    Token t = ts.get();

    while(true) {
        switch(t.kind) {
        case '+':
            left += term();
            t = ts.get();
            break;
        case '-':
            left -= term();
            t = ts.get();
            break;
        default:
            ts.unget(t);
            return left;
        }
    }
}

//------------------------------------------------------------------------------

double declaration(Token k)
    // handle: name = expression
    // declare a variable called "name" with the initial value "expression"
	// k will be "let" or "con"(stant)
{
    Token t = ts.get();
    if (t.kind != name) error ("name expected in declaration");
    string names = t.name;

    Token t2 = ts.get();
    if (t2.kind != '=') error("= missing in declaration of ", names);

    double d = expression();
    define_name(names,d,k.kind==let);
    return d;
}

//------------------------------------------------------------------------------

double statement()
{
    Token t = ts.get();
    switch (t.kind) {
    case let:
	case con:
        return declaration(t.kind);
    default:
        ts.unget(t);
        return expression();
    }
}

//------------------------------------------------------------------------------

void clean_up_mess()
{
    ts.ignore(print);
}

//------------------------------------------------------------------------------

void calculate()
{
    while (cin)
      try {
        cout << prompt;
        Token t = ts.get();
        while (t.kind == print) t=ts.get();    // first discard all "prints"
        if (t.kind == quit) return;        // quit
        ts.unget(t);
        cout << result << statement() << endl;
    }
    catch (exception& e) {
        cerr << e.what() << endl;        // write error message
        clean_up_mess();
    }
}

//------------------------------------------------------------------------------

int main()
try {
    // predefine names:
    define_name("pi",3.1415926535,false);	// these pre-defiend names are constants
    define_name("e",2.7182818284,false);

    calculate();

  //  keep_window_open();
    return 0;
}
catch (exception& e) {
    cerr << e.what() << endl;
   char c;
    while (cin >>c&& c!= print);
    return 1;
}
catch (...) {
    cerr << "exception \n";
   char c;
    while (cin>>c && c!= print);
    return 2;
}

//------------------------------------------------------------------------------

