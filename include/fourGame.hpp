#pragma once
#include <array>

// 7x7 grid, 2 players, goal: 4 in row/col/diag
// pieces drop from top to bottom

enum Piece
{
    NONE = 0,
    RED,
    BLACK,
    INVALID
};

class Board
{
public:
    Board();

    Piece at(int col, int row) const;
    bool insertAtCol(int col, Piece player);
    void clear();
    void print() const;

    bool checkFour(int col, int row) const;
    bool checkAll() const;

    std::array<Piece, 7 * 7> getBoard() const;
    static bool isValid(int col, int row);

private:
    Piece _grid[7][7];

    void dropDown(int col, int row);
};

class GameState
{
public:
    GameState();

    Piece getTurn() const;
    bool makeMove(int col);
    void reset();

    std::array<Piece, 7 * 7> getBoard() const;

    Board _board;
private:
    Piece _turn;

    void swapTurn();
    void delcareWin();
};

