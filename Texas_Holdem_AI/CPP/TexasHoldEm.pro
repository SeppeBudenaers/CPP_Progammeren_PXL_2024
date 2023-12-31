TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += #FULL_PRINT \
#DEBUG_PRINT

SOURCES += main.cpp \
	bart.cpp \
	deck.cpp \
	game.cpp \
	hand.cpp \
	king_of_aces.cpp \
	poker_rank.cpp \
	seppe.cpp \
        dries.cpp\
        kobed.cpp\
	table.cpp \
	tournament.cpp

HEADERS += \
	bart.h \
	card.h \
	deck.h \
	game.h \
	hand.h \
	king_of_aces.h \
	player.h \
	playerid.h \
	poker_rank.h \
	seppe.h \
        dries.h\
        kobed.h\
	table.h \
	tournament.h \
	shootout.h
