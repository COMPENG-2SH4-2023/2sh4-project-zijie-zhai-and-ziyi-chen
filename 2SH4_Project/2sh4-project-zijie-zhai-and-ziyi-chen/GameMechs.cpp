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

}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;

    score = 0;
    // defaut board size
    boardSizeX = boardX;
    boardSizeY = boardY;

}

// do you need a destructor?
// GameMechs::~GameMechs()
// {
//     // delete any heap members here

// }



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
