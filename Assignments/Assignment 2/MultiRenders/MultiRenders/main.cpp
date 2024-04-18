#include "GameController.h"

int main()
{
    GameController::GetInstance().Initialize("Assignment 2 - Angela Villadiego", false);
    GameController::GetInstance().RunGame();

    return 0;
}