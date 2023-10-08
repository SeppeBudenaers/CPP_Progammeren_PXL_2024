#ifndef SEPPE_H
#define SEPPE_H

#include "player.h"
namespace PXL2023
{
class seppe : public Player //Bart is Player
{
public:
    seppe( unsigned char instance = 0 )	: Player(instance)	{}
    const char* getName( void ) const						; //{ return "Bart"; }
    int willYouRaise( unsigned int totalBet )				;
private:
    enum HAND_SEPPE
    {
        UNPLAYABLE_HAND = 0,
        LOW_HAND,
        MEDIUM_HAND,
        HIGH_HAND,
    };
    int PreflopFiltering();
};
}
#endif // SEPPE_H
