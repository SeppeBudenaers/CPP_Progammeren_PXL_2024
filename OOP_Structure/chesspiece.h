#ifndef CHESSPIECE_H
#define CHESSPIECE_H


class ChessPiece
{
public:
    ChessPiece(int X, int Y)    : Xcordinate(X), Ycordinate(Y) {}
    int Xcordinate = 0;
    int Ycordinate = 0;
private:
    virtual const char* Move()	= 0;
};

#endif // CHESSPIECE_H
