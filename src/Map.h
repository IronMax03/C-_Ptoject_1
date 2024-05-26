#include "Global.h"

/**
*  Special Tiles
*/
#define RED_T "\033[;41m"

/**
* Island Tiles
*/
#define GREEN_T "\033[;42m"

/**
* Normal Tiles (water)
*/
#define BLUE_T "\033[;44m"


#ifndef MAP_H 
#define MAP_H 

using namespace std;


class Map
{
    public:
        /**
        * Main and only constructor for the map class. 
        */
        Map();

        void displayGameBoard(unsigned int player1Position, unsigned int player2Position) const;
        
        unsigned int getTileType(unsigned int Position) const;

    private:
        unsigned int _tileType[100];

};
#endif