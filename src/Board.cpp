#include "Board.hpp"
#include <iostream>

Board::Board()
    : _grid()
{
}

Piece Board::at(int col, int row) const
{
    return isValid(col, row) ? _grid[flattenCoord(col, row)] : Piece::INVALID;
}

bool Board::insertAtCol(int col, Piece player)
{
    if (at(col, CONNECT4_ROWS - 1) == Piece::NONE)
    {
        _grid[flattenCoord(col, CONNECT4_ROWS - 1)] = player;
        dropDown(col, CONNECT4_ROWS - 1);
        return true;
    }
    return false;
}

void Board::clear()
{
    for (int i = 0; i < CONNECT4_BOARD_SIZE; ++i)
    {
        _grid[i] = Piece::NONE;
    }
}

void Board::dropDown(int col, int row)
{
    if (at(col, row - 1) == Piece::NONE)
    {
        _grid[flattenCoord(col, row - 1)] = _grid[flattenCoord(col, row)];
        _grid[flattenCoord(col, row)] = Piece::NONE;
        dropDown(col, row - 1);
    }
}

std::array<Piece, CONNECT4_BOARD_SIZE> Board::getBoard() const
{
    std::array<Piece, CONNECT4_BOARD_SIZE> data;

    for (int i = 0; i < CONNECT4_BOARD_SIZE; ++i)
    {
        data[i] = _grid[i];
    }

    return data;
}

bool Board::checkUp(int col, int row) const
{
    Piece player = _grid[flattenCoord(col, row)];

    if (player == Piece::INVALID || player == Piece::NONE)
    {
        return false;
    }

    return player == _grid[flattenCoord(col, row + 1)]
        && player == _grid[flattenCoord(col, row + 2)]
        && player == _grid[flattenCoord(col, row + 3)];
}

bool Board::checkUpRight(int col, int row) const
{
    Piece player = _grid[flattenCoord(col, row)];

    if (player == Piece::INVALID || player == Piece::NONE)
    {
        return false;
    }

    return player == _grid[flattenCoord(col + 1, row + 1)]
        && player == _grid[flattenCoord(col + 2, row + 2)]
        && player == _grid[flattenCoord(col + 3, row + 3)];
}

bool Board::checkRight(int col, int row) const
{
    Piece player = _grid[flattenCoord(col, row)];

    if (player == Piece::INVALID || player == Piece::NONE)
    {
        return false;
    }

    return player == _grid[flattenCoord(col + 1, row)]
        && player == _grid[flattenCoord(col + 2, row)]
        && player == _grid[flattenCoord(col + 3, row)];
}

bool Board::checkWin() const
{
    for (int col = 0; col < CONNECT4_COLS; ++col)
    {
        for (int row = 0; row < CONNECT4_ROWS - 3; ++row)
        {
            if (checkUp(col, row))
            {
                return true;
            }
        }
    }

    for (int col = 0; col < CONNECT4_COLS - 3; ++col)
    {
        for (int row = 0; row < CONNECT4_ROWS - 3; ++row)
        {
            if (checkUpRight(col, row))
            {
                return true;
            }
        }
    }

    for (int col = 0; col < CONNECT4_COLS - 3; ++col)
    {
        for (int row = 0; row < CONNECT4_ROWS; ++row)
        {
            if (checkRight(col, row))
            {
                return true;
            }
        }
    }

    return false;
}
