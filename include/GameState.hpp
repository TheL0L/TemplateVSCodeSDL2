#pragma once
#include "Board.hpp"

class GameState
{
public:
    GameState();

    bool hasEnded() const;
    Piece getTurn() const;
    bool makeMove(int col);
    void reset();
    std::array<Piece, CONNECT4_BOARD_SIZE> getBoard() const;

private:
    Piece _currentTurn;
    Board _board;
    bool _hasEnded;

    inline void delcareWin() { _hasEnded = true; }
    inline void swapTurn() { _currentTurn = (_currentTurn == Piece::RED) ? Piece::BLACK : Piece::RED; }
};
