#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"


using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
Player* myPlayer;

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

    myGM = new GameMechs(26, 13); 
    myPlayer = new Player(myGM);

}

void GetInput(void)
{
    if (MacUILib_hasChar() == 1)
    {   
        this_input = MacUILib_getChar();

    }

    myGM->setInput(this_input);
    
}

void RunLogic(void)
{   
    if (myGM->getInput() != 0)
    {
        if (myGM->getInput() == ' ')
        {
            myGM->setExitTrue();

        }

        else
        {
            myPlayer->updatePlayerDir();
            myPlayer->movePlayer();

        }
        
        myGM->clearInput();

    }

}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    char myMap[myGM->getBoardSizeX()][myGM->getBoardSizeY()] = {' '};

    objPos tempPos;
    myPlayer->getPlayerPos(tempPos); 
    
    for (int i = 0; i < myGM->getBoardSizeY(); i ++)
    {
        for (int j = 0; j < myGM->getBoardSizeX(); j ++)
        {
            if (i == 0 || i == (myGM->getBoardSizeY() - 1) || j == 0 || j == (myGM->getBoardSizeX() - 1))
            {
                myMap[i][j] = '#'; 

            }

            else if (i == tempPos.y && j == tempPos.x)
            {
                myMap[i][j] = tempPos.symbol;

            }

            else
            {
                myMap[i][j] = ' ';

            }

            MacUILib_printf("%c", myMap[i][j]);
        
        }

        MacUILib_printf("\n");

    }

    MacUILib_printf("BoardSize: %d x %d, PlayerPos: <%d, %d>, + %c\n", 
                    myGM->getBoardSizeX(), myGM->getBoardSizeY(), 
                    tempPos.x, tempPos.y, tempPos.symbol);   


}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();

    MacUILib_uninit();

    delete myPlayer;
    myPlayer = NULL;

    delete myGM;
    myGM = NULL; 

}
