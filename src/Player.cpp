// NONE OF THIS COMES CLOSE TO WORKING - GET BACK TO STUDYING
//
// /**
//  * Current Objective:
//  * - Create an object that represents a player - fields consist of health, armor, location, view box, ...
//  * - Build functions that act on the Player object values. Functions will leverage Pass functions
//  * 
//  */

// #include<iostream>
// #include "Pass.h"
// #include<windows.h> // I believe this will need to be removed when compiled since "Pass.h" includes windows.h

// // <Elements>
// //   <Element Offset="68" Vartype="Float" Bytesize="4" OffsetHex="00000044" Description="vBox y" DisplayMethod="Unsigned Integer"/>
// //   <Element Offset="64" Vartype="Float" Bytesize="4" OffsetHex="00000040" Description="vBox x" DisplayMethod="Unsigned Integer"/>
// //   <Element Offset="60" Vartype="Float" Bytesize="4" OffsetHex="0000003C" Description="pos vert -f" DisplayMethod="Unsigned Integer"/>
// //   <Element Offset="56" Vartype="Float" Bytesize="4" OffsetHex="00000038" Description="pos W &lt; E -f" DisplayMethod="Unsigned Integer"/>
// //   <Element Offset="52" Vartype="Float" Bytesize="4" OffsetHex="00000034" Description="pos N &lt; S -f" DisplayMethod="Unsigned Integer"/>
// //   <Element Offset="12" Vartype="Float" Bytesize="4" OffsetHex="0000000C" Description="vert pos -h" DisplayMethod="Unsigned Integer"/>
// //   <Element Offset="8" Vartype="Float" Bytesize="4" OffsetHex="00000008" Description="N &lt; S" DisplayMethod="Unsigned Integer"/>
// //   <Element Offset="4" Vartype="Float" Bytesize="4" OffsetHex="00000004" Description="W &lt; E" DisplayMethod="Unsigned Integer"/>
// // </Elements>

// class Player {

//     public:
//         Player(LPVOID client, DWORD processID);
//         ~Player();

//         // LPVOID clientAddress{ };
//         // uintptr_t const offsetToClassObject{ 0x00109B74 };
//         // uintptr_t *baseAddress{ (uintptr_t)clientAddress + offsetToClassObject };


//     private:

//         Pass pass{};

//         // int maxHealth{ 9999 };

//         // char *nick{ (char*)(baseAddress + 0x255) };
//         // int *coordinatesHead[3]{ (int*)baseAddress + 0x8, (int*)baseAddress + 0x4, (int*)baseAddress + 0xC};
//         // int *health{ (int*)baseAddress + 0xF8};
//         // int *armor{ (int*)baseAddress + 0xFC};


//         WINBOOL setMaxHealth();
// };

// Player::Player(LPVOID client, DWORD processID) { 
//     pass.attach(processID);
//     clientAddress = client;

//     if(pass.handleCheck() == FALSE) cout << "HANDLE INIT FAILURE: " << GetLastError() << endl;

//     // todo, function to get processID by process name. would be best written in Pass class and called here
//     // function to get client base address afterwards
// }

// Player::~Player() {}

// WINBOOL Player::setMaxHealth() {
//     pass.write((LPVOID)health, &maxHealth, sizeof(int));
//     return (*health == 9999) ? TRUE : FALSE;
// }