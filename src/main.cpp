#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <math.h>
#include "Utils.hpp"
#include "RenderWindow.hpp"
#include "Entity.hpp"

#include "GameState.hpp"
#define CELL_SIZE 98
#include <string>

bool init();

Vector2D screenToGrid(const RenderWindow& window, const Vector2D& clickPos);
void drawGrid(RenderWindow& window);
void drawPieces(RenderWindow& window, const GameState& gameState,
    CustomTexture& circleRed, CustomTexture& circleBlack);

int main(int argc, char** argv)
{
    if (init() == false)
    {
        system("pause");
        return 0;
    }

    RenderWindow window("Connect 4  |  press ESC to reset game",
        CELL_SIZE * CONNECT4_COLS, CELL_SIZE * CONNECT4_ROWS,
        false, 25
    );
    window.setDrawColor(CustomColor::NAVY);

    bool isRunning = true;
    SDL_Event event;


    SDL_Texture* circleRedTexture = window.loadTexture("./resources/redCircle_49x49.png");
    CustomTexture circleRed(circleRedTexture, CustomRect(0, 0, 49, 49));

    SDL_Texture* circleBlackTexture = window.loadTexture("./resources/blackCircle_49x49.png");
    CustomTexture circleBlack(circleBlackTexture, CustomRect(0, 0, 49, 49));


    GameState gameState;
    Vector2D clickPos;
    bool madeMove = false;
    bool mouseDown = false;
    bool escapeDown = false;

    while (isRunning)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_EventType::SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT && !mouseDown)
                {
                    mouseDown = true;
                    clickPos = Vector2D(event.button.x, event.button.y);
                    madeMove = true;
                }
                break;

            case SDL_EventType::SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    mouseDown = false;
                }
                break;

            case SDL_EventType::SDL_KEYDOWN:
                if (event.key.keysym.sym == SDL_KeyCode::SDLK_ESCAPE && !escapeDown)
                {
                    escapeDown = true;
                    gameState.reset();
                    window.setTitle("Connect 4  |  press ESC to reset game");
                    madeMove = false;
                }
                break;

            case SDL_EventType::SDL_KEYUP:
                if (event.key.keysym.sym == SDL_KeyCode::SDLK_ESCAPE)
                {
                    escapeDown = false;
                }
                break;

            default:
                break;
            }
        }

        window.clear();

        if (gameState.hasEnded())
        {
            std::string player = gameState.getTurn() == Piece::RED ? "RED" : "BLACK";
            std::string title = "Player " + player + " has won!  press ESC to reset game";
            window.setTitle(title.c_str());
        }

        if (madeMove && gameState.hasEnded() == false)
        {
            madeMove = false;
            Vector2D gridPos = screenToGrid(window, clickPos);

            if (gameState.makeMove(gridPos.x) == false)
            {
                std::cout << "bad move!" << std::endl;
            }
        }

        drawGrid(window);
        drawPieces(window, gameState, circleRed, circleBlack);

        window.display();
        window.frameLimiter();
    }

    SDL_Quit();
    return 0;
}

bool init()
{
    // IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP | IMG_INIT_JXL | IMG_INIT_AVIF
    const uint32_t sdl_imgFlags = IMG_INIT_PNG;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
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

Vector2D screenToGrid(const RenderWindow& window, const Vector2D& clickPos)
{
    Vector2D winSize = window.getSize();

    // get the clickPos as [0,1] ratio of the window
    float x = clickPos.x / winSize.x;
    float y = clickPos.y / winSize.y;

    // multiply by grid size and round down
    x = (int)(x * CONNECT4_COLS);
    y = (int)(y * CONNECT4_ROWS);

    return Vector2D{ x, y };
}

void drawGrid(RenderWindow& window)
{
    Vector2D A, B;

    // vertial lines
    A.y = 0;
    B.y = window.getSize().y;
    for (int col = 1; col < CONNECT4_COLS; ++col)
    {
        A.x = col * CELL_SIZE;
        B.x = col * CELL_SIZE;
        window.drawLine(A, B, CustomColor::WHITE);
    }

    // horizontal lines
    A.x = 0;
    B.x = window.getSize().x;
    for (int row = 1; row < CONNECT4_ROWS; ++row)
    {
        A.y = row * CELL_SIZE;
        B.y = row * CELL_SIZE;
        window.drawLine(A, B, CustomColor::WHITE);
    }
}

void drawPieces(RenderWindow& window, const GameState& gameState,
    CustomTexture& circleRed, CustomTexture& circleBlack)
{
    auto board = gameState.getBoard();
    for (int col = 0; col < CONNECT4_COLS; ++col)
    {
        for (int row = 0; row < CONNECT4_ROWS; ++row)
        {
            if (board[col + row * CONNECT4_COLS] == Piece::NONE)
            {
                continue;
            }
            Vector2D pieceDrawPos(
                col * CELL_SIZE,
                (CONNECT4_ROWS - row - 1) * CELL_SIZE  // screen(0,0) is topleft, but player expects bottomleft
            );
            if (board[col + row * CONNECT4_COLS] == Piece::RED)
            {
                window.draw(circleRed.getTexture(), circleRed.getSrcRect(),
                    CustomFRect(
                        pieceDrawPos.x, pieceDrawPos.y,
                        CELL_SIZE, CELL_SIZE
                    )
                );
            }
            else if (board[col + row * CONNECT4_COLS] == Piece::BLACK)
            {
                window.draw(circleBlack.getTexture(), circleBlack.getSrcRect(),
                    CustomFRect(
                        pieceDrawPos.x, pieceDrawPos.y,
                        CELL_SIZE, CELL_SIZE
                    )
                );
            }
        }
    }
}
