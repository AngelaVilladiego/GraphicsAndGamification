#include "GameController.h"

int main()
{
    GameController::GetInstance().Initialize("Final Assignment - Angela Villadiego", false);
    GameController::GetInstance().RunGame();

    return 0;
}