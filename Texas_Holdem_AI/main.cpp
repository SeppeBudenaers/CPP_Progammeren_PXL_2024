#include <iostream>
#include <string.h>
#define DEBUG_PRINT
#include "texasholdem.h"

enum spelerIDs
{
	IK,
	JIJ,
	HIJ,
	ZIJ,
	STUDENT_2022,
	MAX_PLAYER_ID
};


bool init = false;
int maxBetEver[MAX_PLAYER_ID];

//seppe global inits
enum HAND_SEPPE
{
	UNPLAYABLE_HAND = 0,
	LOW_HAND,
	MEDIUM_HAND,
	HIGH_HAND,
};

int NumberOfCallersOnStart (struct Game *game, struct Player *player)
{
	int total = -1;
	if (player->bet <= game->blind || (game->players[(game->dealer+2)%game->playersSize] == player && player->bet == game->blind *2))
	{
		unsigned int CurrentBet = game->blind*2;
		for (int i = 0; i < game->playersSize; i++)
		{
			Player* PlayerAtTable = game->players[(game->dealer+3+i)%game->playersSize];
			if (PlayerAtTable == player)
			{
				break;
			}

			if (PlayerAtTable->bet == CurrentBet)
			{
				total++;
			}
			else if (PlayerAtTable->bet > CurrentBet)
			{
				CurrentBet = PlayerAtTable->bet;
			}
		
		}
	}
}
int FilteringPreflop(struct Player *player)
{   
	//initss
	int HandSeppe = 0;
	int LutSuited [14][14] = {
			{HIGH_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND}, //ace
			{LOW_HAND,LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND},//two
			{LOW_HAND,UNPLAYABLE_HAND,LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND},//three
			{LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND},//four
			{LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,MEDIUM_HAND,LOW_HAND,LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND},//five
			{MEDIUM_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,MEDIUM_HAND},//six
			{MEDIUM_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,UNPLAYABLE_HAND,LOW_HAND,MEDIUM_HAND},//seven
			{MEDIUM_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND},//eight
			{MEDIUM_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND},//nine
			{HIGH_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND,MEDIUM_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND},//ten
			{HIGH_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,MEDIUM_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND}, //jack
			{HIGH_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,MEDIUM_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND}, //queen
			{HIGH_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,MEDIUM_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND}, //king
			{HIGH_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND} //ace
		};
	int LutNotSuited [14][14] = {
			{HIGH_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND,LOW_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND}, //ace
			{UNPLAYABLE_HAND,LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND},//two
			{UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND},//three
			{UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND},//four
			{UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,MEDIUM_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND},//five
			{UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,MEDIUM_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND},//six
			{LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,HIGH_HAND,LOW_HAND,LOW_HAND,LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND},//seven
			{LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,HIGH_HAND,LOW_HAND,LOW_HAND,LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND},//eight
			{LOW_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND,HIGH_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND,LOW_HAND},//nine
			{HIGH_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND,HIGH_HAND,MEDIUM_HAND,MEDIUM_HAND,MEDIUM_HAND,HIGH_HAND},//ten
			{HIGH_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND,MEDIUM_HAND,HIGH_HAND,MEDIUM_HAND,HIGH_HAND,HIGH_HAND},//jack
			{HIGH_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,MEDIUM_HAND,MEDIUM_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND},//queen
			{HIGH_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,MEDIUM_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND},//king
			{HIGH_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,UNPLAYABLE_HAND,LOW_HAND,LOW_HAND,LOW_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND,HIGH_HAND},//ace
		};
	
	//fiding highest card
	int higher_card = 0;
	int lower_card = 1;
	if (player->hand->cards[0]->rank <= player->hand->cards[1]->rank || player->hand->cards[1]->rank == 1)
	{
		higher_card = 1;
		lower_card = 0;
	}
	
	// filtering hand combinations
	if (player->hand->cards[0]->suit == player->hand->cards[1]->suit) // suited
	{
		LutSuited[player->hand->cards[higher_card]->rank - 1][player->hand->cards[lower_card]->rank - 1];
	}
	else // not suited
	{
		LutNotSuited[player->hand->cards[higher_card]->rank - 1][player->hand->cards[lower_card]->rank - 1];
	}
	
	return HandSeppe;
}

int willYouRaise(struct Game *game, struct Player *player, unsigned int totalBet)
{
	if (!init)
	{
		init = true;
		for (int i = 0; i < MAX_PLAYER_ID; i++)
		{
			maxBetEver[i] = 0;
		}
	}
	switch (player->ID)
	{
	case IK:
	{
		printf("debug: in case");
		// int
		int BetSeppe = 0;
		int HandSeppe = 0;
		int BigBlind = game->blind * 2;


		// settings
		int MaxBetSeppe = player->chips;
		int AllInPreflopSeppe = 35; 
		int EarlyPosition = game->playersSize - 6;
		int MidPosition = game->playersSize - 2;
		// preflop
		if (table[0] == nullptr)
		{

			//hand filtering
			HandSeppe = FilteringPreflop(player);
			
			// betting
			if (game->plays > EarlyPosition)
			{
				if (HandSeppe >= MEDIUM_HAND)
				{
					if (player->chips < (20 * BigBlind))
					{
						int limpers = NumberOfCallersOnStart(game,player);
						if (limpers == 0)
						{
							BetSeppe = 2*BigBlind;
						}
						else
						{
							BetSeppe = ((2,5 + limpers * 1)*BigBlind);
						}	
					}
					else if ((20 * BigBlind) <= player->chips < (35 * BigBlind))
					{
						int limpers = NumberOfCallersOnStart(game,player);	
						if (limpers == 0)
						{
							BetSeppe = 2,25*BigBlind;
						}
						else
						{
							BetSeppe = ((3 + limpers * 1)*BigBlind);
						}	
					}
					else if ((35 * BigBlind) <= player->chips < (60 * BigBlind))
					{
						int limpers = NumberOfCallersOnStart(game,player);	
						if (limpers == 0)
						{
							BetSeppe = 2,5*BigBlind;
						}
						else
						{
							BetSeppe = ((3,25 + limpers * 1)*BigBlind);
						}	
					}
					else
					{
						int limpers = NumberOfCallersOnStart(game,player);	
						if (limpers == 0)
						{
							BetSeppe = 2,75*BigBlind;
						}
						else
						{
							BetSeppe = ((3,5 + limpers * 1)*BigBlind);
						}	
					}
				}
				else
				{
					return -1; //fold
				}
			}
			else if (game->plays > MidPosition)
			{
				if (HandSeppe >= MEDIUM_HAND)
				{
					if (player->chips < (20 * BigBlind))
					{
						int limpers = NumberOfCallersOnStart(game,player);	
						if (limpers == 0)
						{
							BetSeppe = 2*BigBlind;
						}
						else
						{
							BetSeppe = ((2,5 + limpers * 1)*BigBlind);
						}	
					}
					else if ((20 * BigBlind) <= player->chips < (35 * BigBlind))
					{
						int limpers = NumberOfCallersOnStart(game,player);	
						if (limpers == 0)
						{
							BetSeppe = 2,25*BigBlind;
						}
						else
						{
							BetSeppe = ((3 + limpers * 1)*BigBlind);
						}	
					}
					else if ((35 * BigBlind) <= player->chips < (60 * BigBlind))
					{
						int limpers = NumberOfCallersOnStart(game,player);	
						if (limpers == 0)
						{
							BetSeppe = 2,5*BigBlind;
						}
						else
						{
							BetSeppe = ((3,25 + limpers * 1)*BigBlind);
						}	
					}
					else
					{
						int limpers = NumberOfCallersOnStart(game,player);	
						if (limpers == 0)
						{
							BetSeppe = 2,75*BigBlind;
						}
						else
						{
							BetSeppe = ((3,5 + limpers * 1)*BigBlind);
						}	
					}
				}
				else
				{
					return -1;// fold
				}
			}
			else
			{
				if (HandSeppe >= LOW_HAND)
				{
					if (player->chips < (20 * BigBlind))
					{
						int limpers = NumberOfCallersOnStart(game,player);	
						if (limpers == 0)
						{
							BetSeppe = 3*BigBlind;
						}
						else
						{
							BetSeppe = ((2,5 + limpers * 1)*BigBlind);
						}	
					}
					else if ((20 * BigBlind) <= player->chips < (35 * BigBlind))
					{
						int limpers = NumberOfCallersOnStart(game,player);	
						if (limpers == 0)
						{
							BetSeppe = 3,25*BigBlind;
						}
						else
						{
							BetSeppe = ((3 + limpers * 1)*BigBlind);
						}	
					}
					else if ((35 * BigBlind) <= player->chips < (60 * BigBlind))
					{
						int limpers = NumberOfCallersOnStart(game,player);	
						if (limpers == 0)
						{
							BetSeppe = 3,5*BigBlind;
						}
						else
						{
							BetSeppe = ((3,25 + limpers * 1)*BigBlind);
						}	
					}
					else
					{
						int limpers = NumberOfCallersOnStart(game,player);	
						if (limpers == 0)
						{
							BetSeppe = 3,5*BigBlind;
						}
						else
						{
							BetSeppe = ((3,5 + limpers * 1)*BigBlind);
						}	
					}
				}
				else
				{
					return -1; //fold
				}
			}
			if (((BetSeppe*100)/player->chips) >= AllInPreflopSeppe) //if higher than 35 percent than all in
			{
				return player->chips;
			}
			else if((BetSeppe - totalBet) >= 0)
			{
				return BetSeppe - totalBet;// total is the bet to match right?
			}
			else if((player->chips - player->bet) <= BigBlind)
			{
				return 0;
			}
			else
			{
				return BetSeppe - totalBet;
			}
		}
		else 
		{
			printf("debug: on river");
			PokerRank mijnHandRank = getMyHandRank(player->hand);
			printf("mijnHandRank.category %i",mijnHandRank.category);
			switch (mijnHandRank.category)
			{
			case STRAIGHT_FLUSH:
			case FOUR_OF_A_KIND:
			case FULL_HOUSE:
				return player->chips;
				break;
			case FLUSH:
				if ((totalBet *100 / player->chips) <= 60 )
				{
					return 10;
				}
				else if ((totalBet * 100 / player->chips) >= 70 && (totalBet * 100 / player->chips) <= 110)
				{
					return 0;
				}
				else
				{
					return -1;
				}
				break;
			case STRAIGHT:
			case THREE_OF_A_KIND:
				if ((totalBet *100 / player->chips) <= 55 )
				{
					return 7;
				}
				else if ((totalBet * 100 / player->chips) >= 70 && (totalBet * 100 / player->chips) <= 110)
				{
					return 0;
				}
				else
				{
					return -1;
				}
				break;
			case TWO_PAIR:
				if ((totalBet *100 / player->chips) <= 45 )
				{
					return 5;
				}
				else if ((totalBet * 100 / player->chips) >= 70 && (totalBet * 100 / player->chips) <= 90)
				{
					return 0;
				}
				else
				{
					return -1;
				}
				break;
			
			default:
				if ((totalBet *100 / player->chips) <= 40 )
				{
					return 1;
				}
				else if ((totalBet * 100 / player->chips) >= 70 && (totalBet * 100 / player->chips) <= 90)
				{
					return 0;
				}
				else
				{
					return -1;
				}
				break;
			}
		}
		
		
		break;
	}
	case JIJ:
		for (int i = 0; i < game->playersSize; i++)
		{
			if (game->players[i]->bet > maxBetEver[game->players[i]->ID])
			{
				maxBetEver[game->players[i]->ID] = game->players[i]->bet;
			}
		}
		if (game->amountHands > 2)
		{
			return (-1);
		}
		for (int i = 0; i < game->playersSize; i++)
		{
			if (game->players[i]->ID != JIJ && isHandFilled(game->players[i]->hand))
			{
				return (maxBetEver[game->players[i]->ID] - totalBet + 1);
			}
		}
		return (-1);
		break;
	case HIJ:
		if (totalBet > 50)
		{
			return (-1);
		}
		return (0 - totalBet);
		break;
	case ZIJ:
	{
		bool fold = true;
		for (int i = 0; !fold && i < game->playersSize; i++)
		{
			if (game->players[i]->ID != HIJ && game->players[i]->ID != ZIJ && game->players[i]->hand->cards[0] != nullptr)
			{
				fold = false;
			}
			if (game->players[i]->ID == HIJ && game->players[i]->hand->cards[0] == nullptr)
			{
				fold = false;
			}
		}
		if (fold)
		{
			return -1;
		}

		return (0);
		break;
	}
	case STUDENT_2022:
		PokerRank mijnHandRank = getMyHandRank(player->hand);
		if (table[0] == nullptr) // Pre flop
		{
			if (player->hand->cards[0]->suit == player->hand->cards[1]->suit)
			{ // suited hands
				int diffBetweenOrderedCards = mijnHandRank.hand[0]->rank - mijnHandRank.hand[1]->rank;
				if (diffBetweenOrderedCards == 1 || diffBetweenOrderedCards == 13)
				{										 // suited connected
					return (game->blind * 7) - totalBet; // max 7x blind and fold otherwise
				}
				return (game->blind * 3) - totalBet; // max 3x blind and fold otherwise
			}
			if (player->hand->cards[0]->rank == player->hand->cards[1]->rank)
			{										 // 1 pair to start
				return (game->blind * 5) - totalBet; // max 5x blind and fold otherwise
			}
			int diffBetweenOrderedCards = mijnHandRank.hand[0]->rank - mijnHandRank.hand[1]->rank;
			if (diffBetweenOrderedCards == 1 || diffBetweenOrderedCards == 13)
			{										 // unsuited connected
				return (game->blind * 3) - totalBet; // max 3x blind and fold otherwise
			}
			if (totalBet > game->blind * 2)
			{
				return -1;
			}
			return 0;
		}
		else if (table[3] == nullptr)
		{ // on flop
			return 0;
		}
		else if (table[4] == nullptr)
		{ // on turn
			return 0;
		}
		else
		{ // on river
			return 0;
		}
		break;
	}
	return (0);
}

int main(void)
{
	Game game;
	makeNewDeck(&game);

	Player ik;
	strcpy(ik.name, "seppe ");
	ik.ID = IK;

	Player jij;
	strcpy(jij.name, "Gijse zot");
	jij.ID = JIJ;

	Player hij;
	strcpy(hij.name, "Hij weet niet beter");
	hij.ID = HIJ;

	Player zij;
	strcpy(zij.name, "Zij speelt vals");
	zij.ID = ZIJ;

	Player student2022;
	strcpy(student2022.name, "student 2022 example");
	student2022.ID = STUDENT_2022;

	addPlayerToGame(&game, &ik);
	addPlayerToGame(&game, &jij);
	addPlayerToGame(&game, &hij);
	addPlayerToGame(&game, &zij);
	addPlayerToGame(&game, &student2022);

	playGame(&game, 1);
	printf("The winner is %s with %d chips !", game.players[0]->name, game.players[0]->chips);
	return 0;
}
/*case IK:
	{
		if( getMyHandRank( player->hand ).category == STRAIGHT_FLUSH )
		{
			return 10000;
		}
		if( game->plays > 10 && table[4] != nullptr ) //Play on river
		{
			PokerRank mijnHandRank = getMyHandRank( player->hand );
			PokerRank tafelRank = getMyHandRank( nullptr );
			if( mijnHandRank.category >= TWO_PAIR && mijnHandRank.category > tafelRank.category )
			{
				return( 20 - totalBet );
			}
		}
		if( totalBet > game->blind * 5 )
		{
			return( -1 );
		}
		return( 0 );
		break;
	}*/