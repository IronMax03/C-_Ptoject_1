#include<vector>
#include"Entity.h"
#include "Global.h"
#include "Map.h"

#ifndef GAME_H 
#define GAME_H 

using namespace std;


class Game
{
    public:
        /**
        * The default constructor for the Game class.
        */
        Game();

        /**
        * Starts the game by initializing players and determining the order of play.
        * Prompts players for their names, character selection, and heads or tails choice.
        * Determines the order of play based on the outcome of the coin toss.
        */
        void startGame();

        /**
        * Updates the game state by handling player turns and actions.
        * 
        * @return True if the game should continue, false if the game is over.
        */
        bool updateGame();

        /**
        * Allows a player to visit the shop  .
        * 
        * @param playerNum The index of the player visiting the shop.
        */
        void visitShop(unsigned int playerNum);

        /**
         * Manages combat between the player and an enemy.
         * 
         * @param playerNum The index of the player in the _players vector.
         * @param enemy The enemy entity the player is facing.
         * @return 1 if the player wins the fight, 0 if the player successfully runs away.
         */
        int combat(int playerNum, Entity& enemy);

        /**
        * Run some assert to preserve encapsulation. 
        */
        void runTest() const;

    private:

        /**
        * Performs actions based on the type of tile the player lands on.
        * 
        * @param playerNum The index of the player.
        */
        void tileAction(unsigned int playerNum);

        /**
         * Convert equipment in the string format(from items.txt) to an Entity struc instance.
         * 
         * @param import Equipment in the string format.
         * @return The Equipment as an struc instance.
         */
        Equipment loadEquipment(string) const;

        /**
         * Convert potion in the string format(from items.txt) to an Entity struc instance.
         * 
         * @param import Potion in the string format.
         * @return The Potion as an struc instance.
         */
        Potion loadPotion(string) const;

        /**
         * Load the game data from entity.txt and items.txt by creating instances and storing them in either: 
         * _playerCharacter, _enemies, _allPotions and _allEquipment.
         */
        void loadData();

        /**
        *  Function to present riddles to the player and check their answers.
        * 
        * @return True if the player's answer is correct, false otherwise.
        */
        bool riddles() const;

        // game skeleton
        Map _gameMap;
        unsigned int _turn;
        unsigned int calamityChance;


        // player
        string _playerNames[2];
        unsigned int _position[2];
        vector<Entity> _players;
        bool _sirenSong[2];

        vector<Entity> _playerCharacter;
        vector<Entity> _enemies;
        
        static vector<Potion> _allPotions;
        static vector<Equipment> _allEquipment;

        /**
        * this variable holds the size of the weppons sub vector() inside of _allEquipment.
        */
        static unsigned weponSubVecSize; 
};
#endif 