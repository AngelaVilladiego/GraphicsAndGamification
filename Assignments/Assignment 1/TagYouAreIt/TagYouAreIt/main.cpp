// TagYouAreIt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "GameController.h"

int main()
{
    GameController::GetInstance().Initialize("Assignment 1 - Angela Villadiego", true);
    GameController::GetInstance().RunGame();

    return 0;
}