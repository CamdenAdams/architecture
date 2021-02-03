/**
 * function definition and function pointer declaration syntax: 
 * int foo(int x) { return x; }
 *      int (*ptr2Fnc)(){ &foo };
 * calling function through pointer: (*ptr2Fnc)(5) OR ptr2Fnc(5)
 * 
 */

#include<iostream>

using namespace std;

enum Monster{
    monster_orc,
    monster_goblin,
    monster_troll,
    monster_ogre,
    monster_skeleton
};

int main() {
    
    // Monster pType = monster_troll; <<<< copy variable assignment, inefficient - use direct list initialization
    Monster pType{ monster_troll };

    if(pType == monster_orc) cout << "Orc" << endl;
    if(pType == monster_goblin) cout << "goblin" << endl;
    if(pType == monster_troll) cout << "troll" << endl;
    if(pType == monster_ogre) cout << "ogre" << endl;
    if(pType == monster_skeleton) cout << "skeleton" << endl;

}
