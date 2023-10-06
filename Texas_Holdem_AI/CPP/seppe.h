#ifndef SEPPE_H
#define SEPPE_H

#include "player.h"
namespace PXL2023
{
    class seppe : public Player // seppe is een player
    {
    public:
        seppe(unsigned char instance = 0) : Player(instance) {}
        const char* getName( void ) const;
        int willYouRaise (unsigned int totalBet);
    private:
    };
}
#endif // SEPPE_H
