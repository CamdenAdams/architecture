/**
 * my random notes:
 * ternary operator: variable = (condition) ? expressionTrue : expressionFalse;
 * | is refered to as bitwise operator
 * #include, #define, #if, #line... are preprocessor directives. 
 * preprocessor directives 'give instructions to the compiler to preprocess the information before actual compilation starts.' https://www.tutorialspoint.com/cplusplus/cpp_preprocessor.htm

 */

/**
 * THIS SOURCE IS FANTASTIC: https://www.learncpp.com/cpp-tutorial/variable-assignment-and-initialization/
 * AND THE AUTHOR IS THE KING OF THE COMMENTS
 * copy initialization
 *      i.e. int five = 5;
 * 
 *  direct dnitialization with parenthesis
 *      i.e. int five = 5; can also be written... int five( 5 );
 * 
 * 'To provide a more consistent initialization mechanism, there’s list initialization (also sometimes called uniform initialization or brace initialization) that uses curly braces.'
 *      'List initialization has the added benefit of disallowing “narrowing” conversions.'
 *      i.e. int five = 5; can also be written... 
 *          list initialization: int five = { 5 };
 *          direct list initialization: int five{ 5 };
 * 
 * 'Bjarne Stroustrup (creator of C++) and Herb Sutter (C++ expert) make this [ this = 'Initialize your variables upon creation' ] recommendation themselves'
 * 
 * 
 * 
 * 
 */
#include<windows.h>
#include<iostream>



using namespace std;

class pass {
    // public access functions and variables
    public:         
        pass(DWORD processID);
        ~pass();


        bool attach(DWORD processID);           // public access function declaration
        int return_five();


    private:
        // HANDLE h();                             // is this a direct initialization of a HANDLE
        // HANDLE xh{ };                           // is this a direct uniform initializtion of a HANDLE :o
        
};

#ifdef _DEBUG
    #define DBOUT cout
#else
    #define DBOUT 0 && cout
#endif

// constructor function
pass::pass(DWORD processID) {
    HANDLE h{ OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, processID) };
    if (h == NULL) DBOUT << "NULL HANDLE" << endl;
}

// deconstructor function
pass::~pass() {}

// ¯\_(ツ)_/¯
int pass::return_five() { int five( 5 ); return five; };

// 
bool pass::attach(DWORD processID) { if ((h = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, processID)) == NULL) return FALSE; return TRUE; };
// ((h = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, processID)) == NULL) ? return FALSE : return TRUE;    feels bad... ternary if statements don't like return function

int pass::return_five() { int five( 5 ); return five; };