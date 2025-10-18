#include "Game/Game.h"
#include "Game/ResourceManager/ResourceManager.h"

int main() {
    ResourceManager::GetInstance().PreloadChessTextures();
    Game chessGame = Game();
    chessGame.Run();
    return EXIT_SUCCESS;
}
