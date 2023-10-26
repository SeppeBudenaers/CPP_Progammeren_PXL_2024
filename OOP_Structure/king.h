#ifndef KING_H
#define KING_H

#include "chesspiece.h"

class King :public ChessPiece
{
public:
    King(int X, int Y)  : ChessPiece(X,Y)   {}
    const char* Move();
};

#endif // KING_H
