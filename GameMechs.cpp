#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;

    score = 0;

    // default board size
    boardSizeX = 20;
    boardSizeY = 10;

    // seed the RNG function with current time
    srand(time(NULL));

    // default foodPos outside the map
    foodPos.setObjPos(-1, -1, 'o');

}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;

    score = 0;
    
    // costumized board size
    boardSizeX = boardX;
    boardSizeY = boardY;

    // seed the RNG function with current time
    srand(time(NULL));

    // default foodPos outside the map
    foodPos.setObjPos(-1, -1, 'o');

}

bool GameMechs::getExitFlagStatus()
{
    return exitFlag;

}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;

}

char GameMechs::getInput()
{
    return input;

}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;

}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;

}


void GameMechs::setExitTrue()
{
    exitFlag = true;

}

void GameMechs::setLoseTrue()
{
    loseFlag = true;

}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;

}

int GameMechs::getScore()
{
    return score;

}

void GameMechs::incrementScore()
{
    score ++;

}

void GameMechs::generateFood(objPosArrayList* blockOff)
{
    objPos currBody;
    int overLap = 1;

    // generate the food with out overlapping the snake
    while(overLap)
    {
        overLap = 0;

        // random number generation
        int candidateX = rand() % (boardSizeX - 2) + 1;
        int candidateY = rand() % (boardSizeY - 2) + 1;

        foodPos.setObjPos(candidateX, candidateY, 'o');

        // check if the generated food overlap any part of the snake
        for (int i = 0; i < blockOff->getSize(); i ++)
        {
            blockOff->getElement(currBody, i);

            // if overlapped, generate again
            if (foodPos.isPosEqual(&currBody) == 1)
            {
                overLap = 1;
            }

        }

    }

}

void GameMechs::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);

}