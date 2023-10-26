#include "pawn.h"

#include <iostream>

const char* Pawn::Move()
{
    if (Xcordinate == 1){
        Xcordinate = Xcordinate + 2;
        return "move two spaces forwards";
    }
    else {
        Xcordinate++;
        return "move one spaces forwards";
    }

}
