#pragma once
#include <array>

#define CONNECT4_COLS 7
#define CONNECT4_ROWS 6
#define CONNECT4_BOARD_SIZE CONNECT4_COLS * CONNECT4_ROWS

enum class Piece
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

    bool insertAtCol(int col, Piece player);
    std::array<Piece, CONNECT4_BOARD_SIZE> getBoard() const;
    void clear();
    bool checkWin() const;

private:
    Piece _grid[CONNECT4_BOARD_SIZE];

    Piece at(int col, int row) const;

    inline static bool isValid(int col, int row) { return (col < CONNECT4_COLS && col >= 0) && (row < CONNECT4_ROWS && row >= 0); }
    inline static unsigned int flattenCoord(int col, int row) { return col + row * CONNECT4_COLS; }

    void dropDown(int col, int row);
    bool checkUp(int col, int row) const;
    bool checkUpRight(int col, int row) const;
    bool checkRight(int col, int row) const;
};
