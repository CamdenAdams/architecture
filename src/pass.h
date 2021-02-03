/**
 * my random notes:
 * ternary operator: variable = (condition) ? expressionTrue : expressionFalse;
 * | is refered to as bitwise operator
 * #include, #define, #if, #line... are preprocessor directives. 
 * preprocessor directives 'give instructions to the compiler to preprocess the information before actual compilation starts.' https://www.tutorialspoint.com/cplusplus/cpp_preprocessor.htm

 */

/**
 * THIS SOURCE IS FANTASTIC : https://www.learncpp.com/cpp-tutorial/variable-assignment-and-initialization/
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

#ifdef DBUG
    #define DBOUT cout
#else
    #define DBOUT 0 && cout
#endif

using namespace std;

// all variables should be initialized upon creation unless done intentionally for reasons i cannot remember
// I believe that c/cpp classes should use capital casing
// I need to create a player objects struct
//      Where do I create the struct?

/**
 * I need to create a player objects struct > Where do I create the struct?
 *      What does the struct do? provides a number of player based variables and the memory offsets from the game's base address
 *      Since public access is required for the struct and this class simply takes memory address, let's build it into another file
*/
class Pass {
    // public access functions and variables
    public:         
        // Pass(DWORD processID);
        Pass();
        ~Pass();


        void attach(DWORD processID);           // public access function declaration
        WINBOOL handleCheck();
        int return_five();

        void read(LPCVOID readVarBaseAddress, LPVOID readVarBufferAddress, SIZE_T size);
        void write(LPVOID writeVarBaseAddress, LPVOID writeVarBufferAddress, SIZE_T size);


    private:
        HANDLE xh{ };

        SIZE_T byteReadBuffer{ };
        SIZE_T byteWroteBuffer{ };
        

        
};

// constructor function - this function might give public access to h
// Pass::Pass(DWORD processID) { 
//     HANDLE h{ OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, processID) };
//     if (h == NULL) DBOUT << "NULL HANDLE" << endl;
// }

Pass::Pass() { }
Pass::~Pass() {
    if (xh != NULL) CloseHandle(xh);
}

void Pass::attach(DWORD processID) {
    xh = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, processID);
    if(xh == NULL) DBOUT << "NULL HANDLE" << endl;
}

void Pass::read(LPCVOID readVarBaseAddress, LPVOID readVarBufferAddress, SIZE_T size) {
    WINBOOL read = ReadProcessMemory(xh, readVarBaseAddress, readVarBufferAddress, size, &byteReadBuffer);
    if(read == FALSE) DBOUT << "READ FAIL: " << GetLastError() << endl << "byteReadBuffer: " << byteReadBuffer << endl;
}

void Pass::write(LPVOID writeVarBaseAddress, LPVOID writeVarBufferAddress, SIZE_T size) {
    WINBOOL write = WriteProcessMemory(xh, writeVarBaseAddress, writeVarBufferAddress, size, &byteWroteBuffer);
    if(write == FALSE) DBOUT << "WRITE FAIL: " << GetLastError() << endl << "byteWroteBuffer: " << byteWroteBuffer << endl;
}

WINBOOL Pass::handleCheck() { return xh != NULL ? TRUE : FALSE; }

// ¯\_(ツ)_/¯
int Pass::return_five() { int five{ 5 }; return five; }