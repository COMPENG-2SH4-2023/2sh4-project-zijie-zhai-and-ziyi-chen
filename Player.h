#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // direction states

        Player(GameMechs* thisGMRef);
        ~Player();

        objPosArrayList* getPlayerPos(); // returns a reference of playerposList
        char getPlayerDir();
        void updatePlayerDir();
        void movePlayer();

    private:
        objPosArrayList *playerPosList;   // a pointer to arrayList       
        enum Dir myDir;

        // reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif