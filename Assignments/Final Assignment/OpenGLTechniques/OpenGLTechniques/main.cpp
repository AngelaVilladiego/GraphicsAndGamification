#include "GameController.h"

int main()
{
    GameController::GetInstance().Initialize("Final Assignment - Angela Villadiego", true);
    GameController::GetInstance().RunGame();

    return 0;
}