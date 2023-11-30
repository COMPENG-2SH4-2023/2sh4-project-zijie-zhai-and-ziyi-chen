#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');

}


Player::~Player()
{
    // delete any heap members here
    // delete playerPos;

}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos array list
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);

}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();

    switch(input)
    {                   
        case 'w': case 'W':
            if (myDir != UP && myDir != DOWN)
            {
                myDir = UP;

            }
                
            break;
            
        case 's': case 'S':
            if (myDir != DOWN && myDir != UP)
            {    
                myDir = DOWN;

            }

            break;

        case 'a': case 'A':
            if (myDir != LEFT && myDir != RIGHT)
            {
                myDir = LEFT;

            }

            break;

        case 'd': case 'D':
            if (myDir != RIGHT && myDir != LEFT)
            {
                myDir = RIGHT;
                
            }

            break;

        default:
            myDir = STOP;
            break;

    }

}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    int boardSizeX = mainGameMechsRef->getBoardSizeX();
    int boardSizeY = mainGameMechsRef->getBoardSizeY();

    switch (myDir)
    {
        case UP:
            playerPos.y --;
            // moveCount ++;
            break;

        case DOWN:
            playerPos.y ++;
            // moveCount ++;
            break;

        case LEFT:
            playerPos.x --;
            // moveCount ++;
            break;

        case RIGHT:
            playerPos.x ++;
            // moveCount ++;
            break;

        case STOP:
            break;

        default:
            break;

    }

    if (playerPos.x > boardSizeX - 2)
    {
        playerPos.x = 1;

    }

    else if (playerPos.x < 1)
    {
        playerPos.x = boardSizeX - 2;

    }

    else if (playerPos.y > boardSizeY - 2)
    {
        playerPos.y = 1;
        
    }

    else if (playerPos.y < 1)
    {
        playerPos.y = boardSizeY - 2;

    }

}

