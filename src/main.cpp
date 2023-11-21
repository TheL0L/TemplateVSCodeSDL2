#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <math.h>
#include "Utils.hpp"
#include "RenderWindow.hpp"
#include "Entity.hpp"

#include "fourGame.hpp"
#include <vector>

bool init();
void boundEntity(Entity& entity, Vector2D& velocity, const Vector2D& windowSize);
void boundEntity(Entity& entity, Vector2D& velocity, const SDL_FRect& boundingFrame);

Vector2D screenToGrid(const RenderWindow& window, const Vector2D& clickPos);

int main(int argc, char** argv)
{
    if (init() == false)
    {
        system("pause");
        return 0;
    }

    RenderWindow window("4 in a Row  |  press ESC to reset board", 490, 490, false, 25);

    bool isRunning = true;
    SDL_Event event;

    GameState gameState;

    SDL_Texture* gameBoardTexture = window.loadTexture("./resources/board_49x49.png");
    CustomTexture gameBoard(gameBoardTexture, CustomRect(0, 0, 49, 49));

    SDL_Texture* circleRedTexture = window.loadTexture("./resources/redCircle_49x49.png");
    CustomTexture circleRed(circleRedTexture, CustomRect(0, 0, 49, 49));

    SDL_Texture* circleBlackTexture = window.loadTexture("./resources/blackCircle_49x49.png");
    CustomTexture circleBlack(circleBlackTexture, CustomRect(0, 0, 49, 49));

    window.setDrawColor(CustomColor::NAVY);

    Vector2D clickPos;
    bool clicked = false;

    while (isRunning)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_EventType::SDL_MOUSEBUTTONUP:
                clickPos = Vector2D(event.button.x, event.button.y);
                clicked = true;
                break;

            case SDL_EventType::SDL_KEYUP:
                gameState.reset();
                break;

            default:
                break;
            }
        }

        window.clear();

        window.draw(gameBoard.getTexture(), gameBoard.getSrcRect(), CustomFRect(0, 0, window.getSize().x, window.getSize().y));

        if (clicked)
        {
            Vector2D gridPos = screenToGrid(window, clickPos);

            if (gameState.makeMove(gridPos.x) == false)
            {
                std::cout << "bad move!" << std::endl;
            }
            gameState._board.print();

            clicked = false;
        }

        auto board = gameState.getBoard();
        for (int row = 6; row >= 0; --row)
        {
            for (int col = 0; col < 7; ++col)
            {
                Vector2D roundedPos(col * window.getSize().y / 7, window.getSize().y - (row + 1) * window.getSize().y / 7);
                // RED=1 BLACK=2
                if (board[col + row * 7] == Piece::RED)
                {
                    window.draw(circleRed.getTexture(), circleRed.getSrcRect(), CustomFRect(roundedPos.x, roundedPos.y, circleRed.getSrcRect().w, circleRed.getSrcRect().h));
                }
                else if (board[col + row * 7] == Piece::BLACK)
                {
                    window.draw(circleBlack.getTexture(), circleBlack.getSrcRect(), CustomFRect(roundedPos.x, roundedPos.y, circleBlack.getSrcRect().w, circleBlack.getSrcRect().h));
                }
            }
        }

        window.display();
        window.frameLimiter();
    }

    return 0;
}

bool init()
{
    // IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP | IMG_INIT_JXL | IMG_INIT_AVIF
    const uint32_t sdl_imgFlags = IMG_INIT_PNG;

    if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
    {
        std::cerr << "SDL failed to initialize. Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (IMG_Init(sdl_imgFlags) == 0)
    {
        std::cerr << "SDL failed to initialize. Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void boundEntity(Entity& entity, Vector2D& velocity, const Vector2D& windowSize)
{
    SDL_FRect boundingFrame;
    boundingFrame.x = boundingFrame.y = 0;
    boundingFrame.w = windowSize.x;
    boundingFrame.h = windowSize.y;

    boundEntity(entity, velocity, boundingFrame);
}

void boundEntity(Entity& entity, Vector2D& velocity, const SDL_FRect& boundingFrame)
{
    SDL_FRect entityBound = entity.getBoundingBox();

    if (entityBound.x < boundingFrame.x)
    {
        velocity.x = abs(velocity.x);
    }
    else if (entityBound.w > boundingFrame.w)
    {
        velocity.x = -1 * abs(velocity.x);
    }

    if (entityBound.y < boundingFrame.y)
    {
        velocity.y = abs(velocity.y);
    }
    else if (entityBound.h > boundingFrame.h)
    {
        velocity.y = -1 * abs(velocity.y);
    }
}

Vector2D screenToGrid(const RenderWindow& window, const Vector2D& clickPos)
{
    Vector2D winSize = window.getSize() / 7;
    Vector2D gridCoord((int)clickPos.x / (int)winSize.x % 7, (int)clickPos.y / (int)winSize.y % 7);

    return gridCoord;
}
