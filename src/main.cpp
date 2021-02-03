

// Tracing pointer chain to base player address
// "ac_client.exe" + 0010F418
// offset 0 = 58
// offset 1 = 2A8
// offset 2 = 150
// points to 00FDA5C0

// 'ac_client.exe'+0010F418 = 10F562C
// client address+0010F418 = ammo base address

// Player Base Address = "ac_client.exe"+00109B74
// Player Base address = 'client address'+00109B74
// Offset to Player Base Address = 0x00109B74


// <Elements>
//   <Element Offset="68" Vartype="Float" Bytesize="4" OffsetHex="00000044" Description="vBox y" DisplayMethod="Unsigned Integer"/>
//   <Element Offset="64" Vartype="Float" Bytesize="4" OffsetHex="00000040" Description="vBox x" DisplayMethod="Unsigned Integer"/>
//   <Element Offset="60" Vartype="Float" Bytesize="4" OffsetHex="0000003C" Description="pos vert -f" DisplayMethod="Unsigned Integer"/>
//   <Element Offset="56" Vartype="Float" Bytesize="4" OffsetHex="00000038" Description="pos W &lt; E -f" DisplayMethod="Unsigned Integer"/>
//   <Element Offset="52" Vartype="Float" Bytesize="4" OffsetHex="00000034" Description="pos N &lt; S -f" DisplayMethod="Unsigned Integer"/>
//   <Element Offset="12" Vartype="Float" Bytesize="4" OffsetHex="0000000C" Description="vert pos -h" DisplayMethod="Unsigned Integer"/>
//   <Element Offset="8" Vartype="Float" Bytesize="4" OffsetHex="00000008" Description="N &lt; S" DisplayMethod="Unsigned Integer"/>
//   <Element Offset="4" Vartype="Float" Bytesize="4" OffsetHex="00000004" Description="W &lt; E" DisplayMethod="Unsigned Integer"/>
// </Elements>


#include<iostream>
#include<windows.h>

int main() {


    // initialize by fetching client processID

    // load menu
}