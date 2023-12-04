#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    objPos firstBody;

    firstBody.setObjPos(mainGameMechsRef->getBoardSizeX() / 2,
                        mainGameMechsRef->getBoardSizeY() / 2, '*');
    
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(firstBody);

}


Player::~Player()
{
    delete playerPosList;

}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPosList
    return playerPosList;

}

char Player::getPlayerDir()
{
    // return dirction of player to the user
    if (myDir == UP)
    {
        return 'U';

    }

    else if (myDir == DOWN)
    {
        return 'D';

    }

    else if (myDir == LEFT)
    {
        return 'L';

    }

    else if (myDir == RIGHT)
    {
        return 'R';

    }

    else
    {
        return 'S';

    }

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

    objPos currHead;
    playerPosList->getHeadElement(currHead);
    
    // calculate the location of snake head going to
    switch (myDir)
    {
        case UP:
            currHead.y --;

            // Wraparound logic when snake head hit the board edge
            if (currHead.y < 1)
            {
                currHead.y = boardSizeY - 2;

            }

            break;

        case DOWN:
            currHead.y ++;

            // Wraparound logic
            if (currHead.y > boardSizeY - 2)
            {
                currHead.y = 1;
                
            }

            break;

        case LEFT:
            currHead.x --;

            // Wraparound logic
            if (currHead.x < 1)
            {
                currHead.x = boardSizeX - 2;

            }

            break;

        case RIGHT:
            currHead.x ++;

            // Wraparound logic
            if (currHead.x > boardSizeX - 2)
            {
                currHead.x = 1;

            }

            break;

        case STOP:
            break;

        default:
            break;

    }

    // check if new currHead collides with other body elements
    while (mainGameMechsRef->getLoseFlagStatus() != 1)
    {
        objPos currBody;

        for (int i = 0; i < playerPosList->getSize(); i ++)
        {
            playerPosList->getElement(currBody, i);

            // exit the game and print lose message if collide happened
            if (currHead.isPosEqual(&currBody) == 1)
            {
                mainGameMechsRef->setLoseTrue();
                mainGameMechsRef->setExitTrue();

            }

        }

        // continue the game otherwise
        break;

    }

    // insert new currHead to the snake body
    playerPosList->insertHead(currHead);

    // check if food eaten
    objPos currFoodPos;
    mainGameMechsRef->getFoodPos(currFoodPos);

    if (currHead.isPosEqual(&currFoodPos) != 1)
    {
        // remove the tail if no food eat
        playerPosList->removeTail();
        
    }

    else
    {
        // generate new food & increment score if food eaten
        mainGameMechsRef->incrementScore();
        mainGameMechsRef->generateFood(playerPosList);

    }

}

