#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Player.h"
#include "GameMechs.h"


using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
objPos myFoodPos;

Player* myPlayer;
objPosArrayList* myPlayerPos;

char this_input;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    
    // initialize gamemech and snake
    myGM = new GameMechs(36, 18);
    myPlayer = new Player(myGM);

    // get position of snake bodies and use it to create food
    myPlayerPos = myPlayer->getPlayerPos();
    myGM->generateFood(myPlayerPos);

}

void GetInput(void)
{
    // get the input from user and store it in gamemechs class
    if (MacUILib_hasChar() == 1)
    {   
        this_input = MacUILib_getChar();

    }

    myGM->setInput(this_input);
    
}

void RunLogic(void)
{   
    // if there is a input stored in gamemechs class, process
    if (myGM->getInput() != 0)
    {
        if (myGM->getInput() == ' ')
        {
            // end the game if user press space
            myGM->setExitTrue();

        }

        else
        {
            // move the snake otherwise
            myPlayer->updatePlayerDir();
            myPlayer->movePlayer();

        }
        
        // delete the input from this routine to prevent from bugs
        myGM->clearInput();

    }

}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    // create a 2D array to store the gamemap for printing
    char myMap[myGM->getBoardSizeX()][myGM->getBoardSizeY()] = {' '};

    // get the position of food and snake
    myGM->getFoodPos(myFoodPos);
    objPos currBody;
    
    for (int i = 0; i < myGM->getBoardSizeY(); i ++)
    {
        for (int j = 0; j < myGM->getBoardSizeX(); j ++)
        {   
            
            if (i == 0 || i == (myGM->getBoardSizeY() - 1) || j == 0 || j == (myGM->getBoardSizeX() - 1))
            {
                myMap[i][j] = '#'; // store the boarder of the map

            }
            
            else if (i == myFoodPos.y && j == myFoodPos.x)
            {
                myMap[i][j] = myFoodPos.symbol; // store the food

            }

            else
            {
                myMap[i][j] = ' '; // store the blank spaces

            }

            for (int k = 0; k < myPlayerPos->getSize(); k ++)
            {
                myPlayerPos->getElement(currBody, k);

                if (i == currBody.y && j == currBody.x)
                {
                    myMap[i][j] = currBody.symbol; // store the snake bodies

                }

            }

            MacUILib_printf("%c", myMap[i][j]); // print the current element of the map
        
        }

        MacUILib_printf("\n"); // move to a new row after finishing printing a whole row of the map

    }

    // print message depends on the status of exitFlag
    if (myGM->getLoseFlagStatus() == true)
    {
        // end game message if user lose the game
        MacUILib_printf("GAME OVER!\nYou Scored: %d.\n", myGM->getScore());

    }

    else if (myGM->getExitFlagStatus() == true)
    {
        // end game message if user exit the game manually
        MacUILib_printf("Game exitted.\nYou Scored: %d.\n", myGM->getScore());

    }
    
    else
    {   
        // get the info of head element for tracking the position of player
        objPos currHead;
        myPlayerPos->getHeadElement(currHead);

        // normal messages
        MacUILib_printf("Score: %d.\n", myGM->getScore());
        MacUILib_printf("======== DEBUG MESSAGE ========\n");
        MacUILib_printf("Board Size: %d X %d\n", myGM->getBoardSizeX(), myGM->getBoardSizeY());
        MacUILib_printf("Player direction: %c\n", myPlayer->getPlayerDir());
        MacUILib_printf("Player Position: %d, %d\n", currHead.x, currHead.y);
        MacUILib_printf("Food Position: %d, %d\n", myFoodPos.x, myFoodPos.y);

    }

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_uninit();

    //delete heap members
    delete myPlayer;
    myPlayer = NULL;

    delete myGM;
    myGM = NULL; 

}
