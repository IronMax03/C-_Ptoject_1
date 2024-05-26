#include "Map.h"
#include "Global.h"

Map::Map()
{
    if(debugMode) cout << DEBUG_COLOR << "{Debug - Map instantiation}(";
    for(unsigned int i = 0; i < 100; ++i)
    {
        _tileType[i] = randomeInt(0, 3);
        if(_tileType[i] == 3)
            _tileType[i] = 2;
    }
    if(debugMode)cout << endl;
    if(debugMode) cout << DEBUG_COLOR << "{Debug - Map instantiation}()" << RESET << endl;
}

void Map::displayGameBoard(unsigned int player1Position, unsigned int player2Position) const
{
    for(unsigned int p = 0; p < 100; ++p)
    {
        if(p == 50) cout << endl;
        switch (_tileType[p])
        {
            case 0: // Special Tiles
                cout << RED_T;
            break;
            case 1: // Island Tiles
                cout << GREEN_T;
            break;
            case 2: // Normal Tiles (water)
                cout << BLUE_T;
            break;
        }

        if(p == player1Position)
            cout << "1";
        else
            cout << " ";

        if(p == player2Position)
            cout << "2";
        else
            cout << " ";
        
        cout << RESET;
    }
    cout << endl;
}

unsigned int Map::getTileType(unsigned int Position) const
{
    if(debugMode) cout << DEBUG_COLOR << "{Debug - Map getTileType}(Position: " << Position << " | _tileType: " << _tileType[Position] <<")" << RESET << endl;
    return _tileType[Position];
}