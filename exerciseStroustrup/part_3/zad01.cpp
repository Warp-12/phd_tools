// Zadanie 1: wykonac Drill ze str. 251 (calculator08buggy.cpp)

/*
	calculator08buggy.cpp

	Helpful comments removed.

	We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

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
//      "#" Name "=" Expression
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
//      Function"("Arguments")"
//  Function:
//      "sqrt"
//      "pow"
//  Arguments:
//      Expression
//      Argument","Expression
//  Number:
//      [floating-point-literal]
//  Name:
//      [alphabetic-char]
//      Name[alphabetic-char]


#include "std_lib_facilities.hpp"

//-----------------------------------------------------------------------------
const char let = '#';    // declaration token
const char con = 'C';      // constant token
const char quit = 'q';   // t.kind==quit means that t is a quit Token
const char print = ';';    // t.kind==print means that t is a print Token
const char number = '8';  // t.kind==number means that t is a number Token
const char name = 'a';   // name token
const char sqrt_t = 's';	// square root token
const char pow_t = 'p';		// power token
//-----------------------------------------------------------------------------
const string conkey = "const"; // constant keyword
const string autorize = "# ";
const string prompt = "> ";
const string result = "= ";
const string pow_s = "pow"; // power() keyword
const string sqrt_s = "sqrt"; // square_root() keyword
const string quitkey = "exit"; // keyword to quit
//-----------------------------------------------------------------------------
struct Token {
	char kind;          //what kind of token
	double value;       // for numbers: a value
	string name;        // for names: naming
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch, string n) :kind(ch), name(n) { } // make a Token from a char and string
};

//-----------------------------------------------------------------------------
class Token_stream {

public:
	Token_stream(); // make a Token_stream that reads from cin
	Token get();      // get a Token (get() is defined elsewhere)
	void unget(Token t);
	void ignore(char);

private:
    bool full;   // is there a Token in the buffer?
	Token buffer;  // here is where we keep a Token put back using putback()
};


//-----------------------------------------------------------------------------
// The constructor just sets full to indicate that the buffer is empty:
 Token_stream::Token_stream()
    :full(false), buffer(0) { }   // no Token in buffer
//-----------------------------------------------------------------------------

Token Token_stream::get()  // read characters from cin and compose a Token
{
	if (full) { full=false; return buffer; } // check if we already have a Token ready

	char ch;
    cin >> ch;
	switch (ch) {
    case quit:
    case print:
    case let:
	case '(':
	case ')':
	case '+':
	case '-':
    case ',':
	case '*':
	case '/':
	case '%':
	case '=':
		return Token(ch);// let each character represent itself
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
	case '9': // numeric literal
	{	cin.unget();
		double val;
		cin >> val;
		return Token(number,val);
	}
	default:
		if (isalpha(ch)) { // start with a letter
			string s;
			s += ch;
			while(cin.get(ch) && (isalpha(ch) || isdigit(ch))) s+=ch;  // letters digits and underscores
			cin.unget();

			if (s == autorize) return Token(let); // keyword "let"
			if (s == conkey) return Token(con); // keyword "const"
            if (s == sqrt_s) return Token(sqrt_t); //keyword for square_root function
			if (s == pow_s) return Token(pow_t); //keyword for power function
            if (s == quitkey) return Token(quit); // quit keyword

			return Token(name,s);
		}
		error("Bad token");
	}
}


//-----------------------------------------------------------------------------
// The unget() member function puts its argument back into the Token_stream's buffer:
void Token_stream::unget(Token t)
{
    if (full) error("unget() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

//-----------------------------------------------------------------------------
void Token_stream::ignore(char c)// c represents the kind of a Token
{
    // first look in buffer:
	if (full && c==buffer.kind) {
		full = false;
		return;
	}
	full = false;

    // now search input:
	char ch{' '};
	while (ch != c && ch !='\n')
        ch  = cin.get();
		return;
}

//-----------------------------------------------------------------------------
class Variable {
public:
    	string name;
	    double value;
	    bool var; // variable (true) or constant (false)
	    Variable(string n, double v, bool va = true ) :name(n), value(v), var(va) { }
};

//-----------------------------------------------------------------------------
// type for names and associated functions
class Symbol_table {
public:
    double get_value(string s);                           // return the value of the Variable named s
    void set_value(string s, double d);                   // set the Variable named s to d
    bool is_declared(string s);                   // is var already in names?
    double define_name(string var,double val,bool b);   // add (var,val) to names
private:
    vector<Variable> names; // vector of Variables
};

//-----------------------------------------------------------------------------
double Symbol_table::get_value(string s)         // return the value of the Variable names s
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined name ",s);
}

//-----------------------------------------------------------------------------
void Symbol_table::set_value(string s, double d)     // set the Variable named s to d
{
	for (int i = 0; i<=names.size(); ++i)
		if (names[i].name == s) {
                if (names[i].var) {
            error(s," is a constant");
			names[i].value = d;
			return;
		}
		}
	error("set: undefined name ",s);
}

//-----------------------------------------------------------------------------
bool Symbol_table::is_declared(string s)            // is var already in var_table?
{                                     // add (s,val,var) to var_table
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}
//------------------------------------------------------------------------------

double Symbol_table::define_name(string s, double val, bool var)
    // add (s,val,var) to var_table
{
    if (is_declared(s)) error(s," declared twice");
    names.push_back(Variable(s,val,var));
    return val;
}

//-----------------------------------------------------------------------------
Token_stream ts;   // provides get() and putback()
Symbol_table st; // provides get(), set(), is_declared() and declare()
double expression();         // declaration so that primary() can call expression()

//-----------------------------------------------------------------------------

// simple power function
// handles only integers >= 0 as exponents
double my_pow(double base, int expo)
{
    if (expo == 0) {
        if (base == 0) return 0;    // special case: pow(0,0)
        return 1;                   // something to power of 0
    }
    double res = base;              // corresponds to power of 1
    for (int i = 2; i<=expo; ++i)   // powers of 2 and more
        res *= base;
    return res;
}
//-----------------------------------------------------------------------------
double primary()             // deal with numbers and parentheses
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':// handle '(' expression ')
	{	double d = expression();
		t = ts.get();
		if (t.kind != ')') error("'(' expected");
		return d;
	}
	case '-':
		return - primary();
    case '+':
        return primary();
	case number:
		return t.value;  // return the number's value
 case name:
    {   Token t2 = ts.get();    // check next token
        if (t2.kind == '=') {   // handle name '=' expression
            double d = expression();
            st.set_value(t.name,d);
            return d;
        }
        else {  // not an assignment
            ts.unget(t2);
            return st.get_value(t.name);
        }
}
	case sqrt_t:   // handle 'sqrt(' expression ')'
    {   t = ts.get();
        if (t.kind != '(') error("'(' expected");
        double d = expression();
        if (d < 0) error("Square roots of negative numbers... nope!");
        t = ts.get();
        if (t.kind != ')') error("')' expected");
        return sqrt(d);
     }
    case pow_t: // handle 'pow(' expression ',' integer ')'
    {   t = ts.get();
        if (t.kind != '(') error("'(' expected");
       double d = expression();
        t = ts.get();
        if (t.kind != ',') error("',' expected");
        t = ts.get();
        if (t.kind != number) error("second argument of 'pow' is not a number");
        double i = double(t.value);
        if (i != t.value) error("second argument of 'pow' is not an integer");
        t = ts.get();
        if (t.kind != ')') error("')' expected");
        return my_pow(d,i);
    }
	default:
		error("primary expected");
	}
}

//------------------------------------------------------------------------------
double term()
// deal with *, /, and %
{
	double left = primary();
	Token t = ts.get();
	while(true) {
		switch(t.kind) {
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':
		{	double d = primary();
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
			ts.unget(t); // put t back into the token stream
			return left;
		}
	}
}

//-----------------------------------------------------------------------------
double expression()
{                        // deal with + and -
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
        case '=':
       error("use of '=' outside of a declaration");
		default:
			ts.unget(t);
			return left;
		}
	}
}

//-----------------------------------------------------------------------------
// assume we have seen "let" or "const"
// handle: name = expression
// declare a variable called "name" with the initial value "expression"
double declaration(bool b)
{
	Token t = ts.get();
	if (t.kind != name) error ("name expected in declaration");
	string names = t.name;

	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ",names);

	double d = expression();

    st.define_name(names,d,b);
	return d;
}
//-----------------------------------------------------------------------------
double statement()
{
	Token t = ts.get();
	switch(t.kind) {
	case let:
		return declaration(false);
    case con:
        return declaration(true);



	default:
		ts.unget(t);
		return expression();
	}
}

//-----------------------------------------------------------------------------
void clean_up_mess()
{
	ts.ignore(print); // Discard input until a print command or a new line
// is found (inclusive).
}

//-----------------------------------------------------------------------------
void calculate()
{
	while(true)
    try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t=ts.get();     // first discard all "prints"
		if (t.kind == quit){ return;}           // quit
		ts.unget(t);
		cout << result << statement() << endl;
	}
	catch(exception& e) {
		cerr << e.what() << endl;// write error message
		clean_up_mess();
	}
}

//-----------------------------------------------------------------------------
int main()

	try { // predefine names:
         st.define_name("k",1000, false);	// these pre-defiend names are constants
		 calculate();
         keep_window_open(); // cope with Windows console mode
		 return 0;
	}
	catch (exception& e) {
		cerr << "exception: " << e.what() << endl;
		char c;
		while (cin >>c&& c!= print) ;
		return 1;
	}
	catch (...) {
		cerr << "exception\n";
		char c;
		while (cin>>c && c!= print);
		return 2;
	}

//-----------------------------------------------------------------------------
