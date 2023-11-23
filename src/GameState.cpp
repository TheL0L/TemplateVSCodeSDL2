#include "GameState.hpp"

GameState::GameState()
    : _currentTurn(Piece::RED), _board(), _hasEnded(false)
{
}

bool GameState::hasEnded() const
{
    return _hasEnded;
}

Piece GameState::getTurn() const
{
    return _currentTurn;
}

bool GameState::makeMove(int col)
{
    if (!_board.insertAtCol(col, _currentTurn))
    {
        return false;
    }

    if (_board.checkWin())
    {
        delcareWin();
    }
    else
    {
        swapTurn();
    }

    return true;
}

void GameState::reset()
{
    _board.clear();
    _hasEnded = false;
    swapTurn();
}

std::array<Piece, CONNECT4_BOARD_SIZE> GameState::getBoard() const
{
    return _board.getBoard();
}
