#ifndef PAWN_H
#define PAWN_H

#include "chesspiece.h"


class Pawn : public ChessPiece
{
public:
    Pawn(int X, int Y)  : ChessPiece(X,Y)   {}
     const char* Move();
};

#endif // PAWN_H
