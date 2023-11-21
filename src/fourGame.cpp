#include "fourGame.hpp"
#include <iostream>

Board::Board()
    : _grid()
{
}

bool Board::isValid(int col, int row)
{
    return (col < 7 && row < 7) && (col >= 0 && row >= 0);
}

Piece Board::at(int col, int row) const
{
    if (isValid(col, row))
    {
        return _grid[col][row];
    }
    else return Piece::INVALID;
}

bool Board::insertAtCol(int col, Piece player)
{
    if (isValid(col, 6) && at(col, 6) == Piece::NONE)
    {
        _grid[col][6] = player;
        dropDown(col, 6);

        return true;
    }
    return false;
}

void Board::clear()
{
    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            _grid[i][j] = Piece::NONE;
        }
    }
}

void Board::dropDown(int col, int row)
{
    if (at(col, row - 1) == Piece::NONE)
    {
        _grid[col][row - 1] = _grid[col][row];
        _grid[col][row] = Piece::NONE;
        dropDown(col, row - 1);
    }
}

std::array<Piece, 7 * 7> Board::getBoard() const
{
    std::array<Piece, 7 * 7> data;

    for (int col = 0; col < 7; ++col)
    {
        for (int row = 0; row < 7; ++row)
        {
            data[col + row * 7] = _grid[col][row];
        }
    }

    return data;
}

bool Board::checkFour(int col, int row) const
{
    Piece player = at(col, row);

    if (player == Piece::INVALID || player == Piece::NONE) return false;
    // check 4 in each direction (current + 3) ~ dumb way

    Piece a, b, c;

    //up
    a = at(col, row + 1);
    b = at(col, row + 2);
    c = at(col, row + 3);
    if ((player == a) && (a == b) && (a == c))
    {
        return true;
    }

    //diag up-right
    a = at(col + 1, row + 1);
    b = at(col + 2, row + 2);
    c = at(col + 3, row + 3);
    if ((player == a) && (a == b) && (a == c))
    {
        return true;
    }

    //right
    a = at(col + 1, row);
    b = at(col + 2, row);
    c = at(col + 3, row);
    if ((player == a) && (a == b) && (a == c))
    {
        return true;
    }

    //diag down-right
    a = at(col + 1, row - 1);
    b = at(col + 2, row - 2);
    c = at(col + 3, row - 3);
    if ((player == a) && (a == b) && (a == c))
    {
        return true;
    }

    //down
    a = at(col, row - 1);
    b = at(col, row - 2);
    c = at(col, row - 3);
    if ((player == a) && (a == b) && (a == c))
    {
        return true;
    }

    //diag down-left
    a = at(col - 1, row - 1);
    b = at(col - 2, row - 2);
    c = at(col - 3, row - 3);
    if ((player == a) && (a == b) && (a == c))
    {
        return true;
    }

    //left
    a = at(col - 1, row);
    b = at(col - 2, row);
    c = at(col - 3, row);
    if ((player == a) && (a == b) && (a == c))
    {
        return true;
    }

    //diag up-left
    a = at(col - 1, row + 1);
    b = at(col - 2, row + 2);
    c = at(col - 3, row + 3);
    if ((player == a) && (a == b) && (a == c))
    {
        return true;
    }

    return false;
}

bool Board::checkAll() const
{
    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            if (checkFour(i, j)) return true;
        }
    }

    return false;
}

void Board::print() const
{
    char chars[] = { '_', 'R', 'B', 'x' };

    for (int row = 6; row >= 0; --row)
    {
        for (int col = 0; col < 7; ++col)
        {
            std::cout << chars[(int)at(col, row)];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl << std::endl;
}



GameState::GameState()
    : _turn(Piece::RED), _board()
{
}

Piece GameState::getTurn() const
{
    return _turn;
}

bool GameState::makeMove(int col)
{
    if (Board::isValid(col, 0) == false)
    {
        return false;
    }

    if (_board.insertAtCol(col, _turn) == false)
    {
        return false;
    }

    if (_board.checkAll() == true)
    {
        delcareWin();
    }

    swapTurn();
    return true;
}

void GameState::delcareWin()
{
    std::cout << "Player  ";
    if (_turn == Piece::RED) std::cout << "RED";
    else std::cout << "BLACK";
    std::cout << "  won!" << std::endl;
}

void GameState::reset()
{
    _board.clear();
}

void GameState::swapTurn()
{
    if (_turn == Piece::RED)
    {
        _turn = Piece::BLACK;
    }
    else
    {
        _turn = Piece::RED;
    }
}

std::array<Piece, 7 * 7> GameState::getBoard() const
{
    return _board.getBoard();
}
