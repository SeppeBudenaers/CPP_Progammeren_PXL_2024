#include <iostream>
#include "pawn.h"
#include "king.h"

using namespace std;

int main()
{
    Pawn * foo;
    foo = new Pawn(1,0);
    Pawn pion2(1,1);
    King king (0,3);
    cout <<"("<<foo->Xcordinate<< "," <<foo->Ycordinate<< ") " <<foo->Move()<< " end cordinate ("<<foo->Xcordinate<< "," <<foo->Ycordinate<< ") " << endl;
    //cout <<"("<<pion1.Xcordinate<< "," <<pion1.Ycordinate<< ") " <<pion1.Move()<< " end cordinate ("<<pion1.Xcordinate<< "," <<pion1.Ycordinate<< ") " << endl;
    cout <<"("<<pion2.Xcordinate<< " " <<pion2.Ycordinate<< ") " <<pion2.Move()<< " end cordinate ("<<pion2.Xcordinate<< "," <<pion2.Ycordinate<< ") " << endl;
    cout <<"("<<king.Xcordinate<< "," <<king.Ycordinate<< ") " <<king.Move()<< " end cordinate ("<<king.Xcordinate<< "," <<king.Ycordinate<< ") " << endl;
    cout <<"("<<pion2.Xcordinate<< "," <<pion2.Ycordinate<< ") " <<pion2.Move()<< " end cordinate ("<<pion2.Xcordinate<< "," <<pion2.Ycordinate<< ") " << endl;
    delete foo;
    return 0;
}
