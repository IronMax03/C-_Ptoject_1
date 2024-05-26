#include <iostream>
#include<fstream>
#include<cassert>
#include "Entity.h"
#include "Game.h"

using namespace std;

vector<Potion> Game::_allPotions;
vector<Equipment> Game::_allEquipment;

unsigned int Game::weponSubVecSize;

Game::Game()
{
    loadData();
    _position[0] = 0;
    _position[1] = 0;

    _sirenSong[0] = false;
    _sirenSong[1] = false;

    _gameMap = Map();
    if(debugMode) cout  << DEBUG_COLOR << "{Debug - Game instantiation}()" << RESET << endl;
}

void Game::startGame()
{
    calamityChance = initialCalamityChance;
    srand(time(0));
    clearTerminal();

    // character selection
    cout << "Welcome to the Odyssey!" << endl;
    cout << "Enter the first player name: ";
    cin >> _playerNames[0];
    cout << "Enter the second player name: ";
    cin >> _playerNames[1];
    clearTerminal();
    cin.ignore(1, '\n');

    for(unsigned int j = 0;  j <= 1; j++)
    {
        cout << "[" << _playerNames[j] << "](" << j + 1 << ") - " << "Which character would you like to choose? Enter a number." << endl;
        for(unsigned int i = 0; i < _playerCharacter.size(); ++i)
        {
            cout << i+1 << ". " << _playerCharacter.at(i).getName() << "    ";
        }
        cout << endl;
        uint8_t input = safeInput( 1, _playerCharacter.size());
        _players.push_back(_playerCharacter.at(input-1));
        cout << _playerCharacter.at(input-1).getName() << " chosen successfully!" << endl;
        hLine();
    }
    clearTerminal();

    // heads or tails 
    string str[2][2] = {{"(tails)\nYou lost.", "(heads)\nYou won."},
                        {"(heads)\nYou lost.", "(tails)\nYou won."}};
    uint8_t input = safeInput("[" + _playerNames[0] + "]\n" + "Heads or Tails to chose the first player to play.\n1. heads\n2. tails", 1, 2) - 1;
    int randInt = rand() % 2;
    cout << str[input][randInt] << endl;
    if(!randInt)
    {
        string temp = _playerNames[0];
        _playerNames[0] = _playerNames[1];
        _playerNames[1] = temp;
    }

    visitShop(0);
    visitShop(1);
    _turn = 1;
    if(debugMode) cout  << DEBUG_COLOR << "{Debug - Game started}(players number:" << _players.size() << ")" << RESET << endl;
}

bool Game::updateGame()
{
    for(unsigned int i = 0; i <= 1; i++)
    {
        hLine();
        cout << "[" << _playerNames[i] << "](" << i << ") - Turn:" << _turn << endl; 
        _gameMap.displayGameBoard(_position[0], _position[1]);
        unsigned int input;
        unsigned int dieRoll;
        string dummyVar;

        if(_sirenSong[i])
        {
            cout << "Siren's Song echoes through the air, you sense its magical pull, an otherworldly force that toys with the hearts of those who dare to listen." << endl;
            return true;
        }
        else if(_players.at(i).getStamina() == 0)
        {
            cout << "You dont have enougth stamina, Therefor you lose your Turn." << endl;
            _players.at(i).setStamina(10);
            return true;
        }

        playerMenu:
        cout << "0. Quit" << endl;
        cout << "1. Move" << endl;
        cout << "2. Swap/Drop Weapon" << endl;
        cout << "3. Use Potion" << endl;
        cout << "4. Print Player Stats" << endl;

        switch (safeInput(0, 4))
        {
            case 0: // Quit
                if(debugMode) cout  << DEBUG_COLOR << "{Debug - Quit}(The game has been manualy quit)" << RESET << endl;
                return false;
            break;
            case 1: // Move
                cout << "[PRESS ENTER TO ROLL A DIE]" << endl;
                getline(cin, dummyVar);
                clearTerminal();
                dieRoll = randomeInt(1, 6);
                _position[i] += dieRoll;
                cout << "You got " << dieRoll << "." << endl;
                _gameMap.displayGameBoard(_position[0], _position[1]);
                tileAction(i);

                if(_position[i] >= 100)
                {
                    cout << _playerNames[i] << " arrived at Ithaca.\nHe won the game." << endl;
                    _players.at(i).printStats();
                    return false;
                }

            break;  
            case 2: // Swap/Drop Weapon                     
                input = safeInput("0. Back\n1. Swap\n2. Drop Weapon", 0, 2);

                if(input == 1) 
                    _players.at(i).swap();
                else if(input == 2) 
                    _players.at(i).dropItem();
                goto playerMenu;
            break;
            case 3: // Use Potion
                _players.at(i).usePotion();
                goto playerMenu;
            break;
            case 4: // Print Player Stats
                _players.at(i).printStats();
                goto playerMenu;
            break;
        }
        _players.at(i).removeStamina(3);
    }
    _turn++;
    return true;
}

void Game::visitShop(unsigned int playerNum)
{
    // select randome items
    unsigned int rand1 = randomeInt();
    unsigned int rand2 = randomeInt();

    Potion potions[3] = {_allPotions.at(rand1 % _allPotions.size()), 
                         _allPotions.at((rand1 + rand2) % _allPotions.size()),
                         _allPotions.at((rand1 + 2 * rand2) % _allPotions.size())};

    Equipment weapons[3] = {_allEquipment.at(rand2 % weponSubVecSize), 
                           _allEquipment.at((rand2 + rand1) % weponSubVecSize),
                           _allEquipment.at((rand2 + 2 * rand1) % weponSubVecSize)};
    
    bool quantity[2][3] = {{true, true, true},
                         {true, true, true}};

    // shop interface
    bool flag = true;
    while(flag)
    {
        clearTerminal();
        cout << "[" << _playerNames[playerNum] << "](" << playerNum << ")" << endl;
        cout << "0. Leave Shop" << endl;
        cout << "1. Buy Weapon" << endl;
        cout << "2. Buy Potion" << endl;
        cout << "3. Sell Items" << endl;

        switch (safeInput(0, 3))
        {
            case 0: // Leave Shop
                flag = false;
            break; 
            case 1: // Buy Weapon
                while (true)
                {
                    clearTerminal();
                    // display wepons menu
                    cout << "0. Back to main shop menu" << endl;
                    for(unsigned int i = 0; i < 3; ++i)
                    {
                        cout << i+1 << ".  " << weapons[i].name << " - " << weapons[i].description << " - " << weapons[i].price << "$";
                        if(!quantity[0][i]) cout << " - " << "      [Out Of Stock]";
                        cout << endl;
                    }
                    uint8_t input = safeInput(0, 3);

                    // purchase execution
                    if(input == 0) break;            
                    else if(quantity[0][input-1])
                    {
                        if(_players.at(playerNum).buyEquipment(weapons[input-1]))
                            quantity[0][input-1] = false;
                        else
                            cout << "You don't have enough gold." << endl;
                    }
                    else cout <<  weapons[input-1].name << "is out of stock." << endl;
                }
            break;
            case 2: // Buy Potion
                while (true)
                {
                    clearTerminal();
                    // display wepons menu
                    cout << "0. Back to main shop menu" << endl;
                    for(unsigned int i = 0; i < 3; ++i)
                    {
                        cout << i+1 << ".  " << potions[i].name << " - " << potions[i].description << " - " << potions[i].price << "$";
                        if(!quantity[1][i]) cout << " - " << "      [Out Of Stock]";
                        cout << endl;
                    }
                    uint8_t input = safeInput(0, 3);

                    // purchase execution
                    if(input == 0) break;            
                    else if(quantity[1][input-1])
                    {
                        if(_players.at(playerNum).buyPotion(potions[input-1]))
                            quantity[1][input-1] = false;
                        else
                            cout << "You don't have enough gold." << endl;
                    }
                    else cout <<  potions[input-1].name << "is out of stock." << endl;
                }
            break;
            case 3: // sell Items (Extra credit)
                _players.at(playerNum).sellItem();
            break;   
        }
    }
}


Equipment Game::loadEquipment(string import) const
{
    Equipment newEquipment;

    for(unsigned int i = 0, count = 0; i < import.length(); ++i)
    {
        if(import[i] == '|')
        {
            switch (count)
            {
                case 0:
                    newEquipment.name = import.substr(0,i);
                break;                
                case 1:
                    newEquipment.description = import.substr(0,i);
                break;
                case 2:
                    newEquipment.type = import[0];
                break;
                case 3:
                    newEquipment.damage = stoi(import.substr(0,i));
                break;
                case 4:
                    newEquipment.defense = stoi(import.substr(0,i));
                break;
                case 5:
                    newEquipment.element = import[0];
                break;
            }
            count++;
            import = import.substr(i+1, import.length());
            i = 0;
        }
    }
    newEquipment.price = stoi(import);

    if(debugMode) cout  << DEBUG_COLOR << "{Debug - Game loadEquipment}(" << "Name: " << newEquipment.name 
                        << " | description: " << newEquipment.description 
                        <<" | type: " << newEquipment.type 
                        <<" | damage: " << newEquipment.damage 
                        <<" | defense: " << newEquipment.defense 
                        <<" | element: " << newEquipment.element 
                        <<" | price: " << newEquipment.price 
                        << ")" << RESET << endl;
    return newEquipment;
}

Potion Game::loadPotion(string import)  const
{
    Potion newPotion;

    for(unsigned int i = 0, count = 0; i < import.length(); ++i)
    {
        if(import[i] == '|')
        {
            switch (count)
            {
                case 0:
                    newPotion.name = import.substr(0,i);
                break;                
                case 1:
                    newPotion.description = import.substr(0,i);
                break;
                case 2:
                    newPotion.type = import[0];
                break;
                case 3:
                    newPotion.effectValue = stoi(import.substr(0,i));
                break;
            }
            count++;
            import = import.substr(i+1, import.length());
            i = 0;
        }
    }
    newPotion.price = stoi(import);

    if(debugMode) cout  << DEBUG_COLOR << "{Debug - Game loadPotion}(" 
                        << "Name: " << newPotion.name 
                        << " | description: " << newPotion.description 
                        <<" | type: " << newPotion.type 
                        <<" | effectValue: " << newPotion.effectValue 
                        <<" | price: " << newPotion.price 
                        << ")" << RESET << endl;
    return newPotion;
}

void Game::loadData()
{
    ifstream gameData;
    string str;
    int count = 0;

    // load items
    gameData.open("items.txt");
    while(getline(gameData, str))
    {
        if(str[0] != '*')
        {
            if(count == 0 || count == 1) 
                _allEquipment.push_back(loadEquipment(str));
            else if(count == 2) 
                _allPotions.push_back(loadPotion(str));
        }
        else if(str[1] == '*')
        {
            if(count == 0) weponSubVecSize = _allEquipment.size();
            count++;
        }
    }
    gameData.close();

    Entity::allPotions = _allPotions;
    Entity::allEquipment = _allEquipment;

    // load entitys
    gameData.open("entity.txt");
    count = 0;
    while(getline(gameData, str))
    {
        if(str[0] != '*')
        {
            if(count == 0)
            {
                Entity temp(str);
                _enemies.push_back(temp);            
            }
            else if(count == 1)
            {
                Entity temp(str);
                _playerCharacter.push_back(temp);
            }
        }
        else if(str[1] == '*') count++;
    }
    gameData.close();

    if(debugMode) cout  << DEBUG_COLOR << "{Debug - Game loadData}(" 
                        << "_playerCharacter size:" << _playerCharacter.size()
                        << " | _enemies size:" << _enemies.size() 
                        << " | _allPotions size:" << _allPotions.size() 
                        << " | _allEquipment size:" << _allEquipment.size() 
                        <<")" << RESET << endl;
}

void Game::tileAction(unsigned int playerNum)
{
    unsigned int randInt;
    Entity enemyT;
    unsigned int tileType = _gameMap.getTileType(_position[playerNum]);

    switch (tileType)
    {
        case 0: // Special Tiles
            if(debugMode) cout  << DEBUG_COLOR << "{Debug - Game tileAction}(playerNum: " << playerNum << " | tiles type: Special Tiles)" << RESET << endl;

            cout << "You landed on a special tile." << endl;
            randInt = randomeInt(0, 4);
            if(randInt == 0)
            {
                randInt = randomeInt(0, 3);
                if(randInt == 0) // Shortcut
                {
                    cout << "Your spirits soar as you're propelled four tiles ahead. Ithaca isn't far." << endl;
                    _position[playerNum] = limit(_position[playerNum] + 4, 0, 100);
                }
                else if(randInt == 1) // Siren's Song
                {
                    cout << "Siren's Song echoes through the air, you sense its magical pull, an otherworldly force that toys with the hearts of those who dare to listen." << endl;
                    cout << "You cannot move on your next turn only." << endl;
                    _sirenSong[playerNum] = true;
                }
                else if(randInt == 2) // Helios' Beacon
                {
                    cout << "As you stand in the brilliance of Helios' Beacon, you feel the warmth of the sun god's favor shining upon you." << endl;
                    cout << "You feel luckier. Reduce calamity chances by 5%, permanently." << endl;
                    calamityChance = limit(calamityChance - 5, 0, initialCalamityChance);
                }
                else if(randInt == 3) // Nymph's Spring
                {
                    cout << "In the embrace of the Nymph's Spring, you feel the embrace of nature itself." << endl;
                    cout << " Your stamina is replenished(stamina is maximised)." << endl;
                    _players.at(playerNum).fillStamina();
                }
            }
            else if(randInt == 1)
            {
                string dummy;
                cout << "You found an Hidden Treasures! Solve the following riddle to open it." << endl;

                if(!riddles())
                {
                    cout << "Wrong answer, the treasures cant be opened." << endl;
                    return;
                }
                cout << "Correct answer." << endl;

                cout << "[PRESS ENTER TO OPEN THE Treasures]" << endl;
                getline(cin, dummy);

                randInt = randomeInt(1, 3);
                if(randInt == 1) // Stamina Refill
                {
                    randInt = randomeInt(10, 30);
                    cout << "Stamina Refill: You gain " << randInt << " stamina." << endl;
                    _players.at(playerNum).setStamina(_players.at(playerNum).getStamina() + randInt);
                }
                else if(randInt == 2) // Gold Windfall
                {
                    randInt = randomeInt(20, 40);
                    cout << "Gold Windfall: You gain " << randInt << " Gold." << endl;
                    _players.at(playerNum).setStamina(_players.at(playerNum).getStamina() + randInt);
                }
                else if(randInt == 3) // Damage Buff
                {
                    cout << "Damage Buff: ";
                    _players.at(playerNum).addAdvantage();
                }
            }
        break;
        case 1: // Island Tiles
            if(debugMode) cout  << DEBUG_COLOR << "{Debug - Game tileAction}(playerNum: " << playerNum << " | tiles type: Island Tiles)" << RESET << endl;

            enemyT = _enemies.at(randomeInt(0, _enemies.size() - 1));
            cout << "You arrived on an island and you must fight " << enemyT.getName() << "." << endl;
            if(combat(playerNum,  enemyT) != 0)
                visitShop(playerNum);

        break;
        case 2: // Normal Tiles (water)
            if(debugMode) cout  << DEBUG_COLOR << "{Debug - Game tileAction}(playerNum: " << playerNum << " | tiles type: Normal Tiles (water))" << RESET << endl;

            // calamity chance
            if(randomeInt(1, 100) <= 30)
            {
                cout << "[CALAMITIES STRIKE!]" << endl; 
                randInt = randomeInt(1, 100);

                if(randInt <= 20) // poisonous rat
                {
                    cout << "Much to your dismay, it seems you are not the only one on your ship." << endl;
                }
                else if(randInt > 20 && randInt <= 55) // Plague Outbreak
                {
                    cout << "The spread of the plague seems unstoppable, defying your best efforts to contain it and leaving you to confront the harsh reality of your own mortality." << endl;
                }
                else // Stormy Seas
                {
                    cout << "With each passing moment, the storm grows fiercer, testing your courage and resolve as you struggle to keep your ship afloat amidst the wrath of Poseidon." << endl;
                    _position[playerNum] = limit(_position[playerNum] - randomeInt(1, 3), 0, 100);
                }
            }
            
        break;
    }
}

int Game::combat(int playerNum, Entity& enemy)
{
    unsigned int damage;
    while(true)
    {
      // player turn
        clearTerminal();
        cout << _players.at(playerNum).getHP() << "HP [" << _players.at(playerNum).getName() << "]  V" << RED << "S  [" << enemy.getName() << "] " << enemy.getHP() << "HP" << RESET << endl;
        if(enemy.getHP() == 0)
        {
            cout << enemy.getName() << " died. You won the fight." << endl;
            enemy.loot(_players.at(playerNum));
            return 1;
        }
        else if (_players.at(playerNum).getHP() == 0)
        {
            cout << _playerNames[playerNum] << " died." << endl;
            cout << "Therefore " << _playerNames[(playerNum + 1) % 2] << " won the game." << endl;
            cout << "[" << _playerNames[(playerNum + 1) % 2] << "]" << endl;
            _players.at((playerNum + 1) % 2).printStats();

            exit(0);
        }

        cout << "1. Attack" << endl;
        cout << "2. Use Potion" << endl;
        cout << "3. Swap Weapon" << endl;
        cout << "4. Attempt to Run" << endl;

        switch (safeInput(1, 4))
        {
            case 1: // Attack

                if(randomeInt(1, chanceToMiss) == 1)
                {
                    cout << "You missed your attack." << endl;
                }
                else
                {
                    damage = _players.at(playerNum).getAttackDamage();
                    enemy.attack(damage);
                }
            break;
            case 2: // Use Potion
                _players.at(playerNum).usePotion();
            break;
            case 3: // Swap Weapon
                _players.at(playerNum).swap();
            break;
            case 4: // Attempt to Run
                if(randomeInt(0, 150) > _players.at(playerNum).getHPRatio() * 100)
                {
                    cout << "You succesfully run away." << endl;
                    _players.at(playerNum).removeStamina(35);
                    return 0;
                }
                cout << "You faileding run away." << endl;
            break;
        }

      // enemy turn
        damage = enemy.getAttackDamage();
        _players.at(playerNum).attack(damage);
    }
}

bool Game::riddles() const
{
    unsigned int ranInt = randomeInt(0,4);
    string input;

    switch (randomeInt(0,3))
    {
        case 0: // answer = 7
            cout << "I am an odd number. Take away one letter and I become even. What number am I? (integer)" << endl;
            if(input == "7")
                return true;
        break;
        case 1: // answer = 12
            cout << "What is the square root of 144? (integer)" << endl;
            if(input == "12")
                return true;
        break;
        case 2: // answer = 36
            cout << "I am an even number. If you subtract 4 from me and then divide me by 8, the result is 7. What number am I? (integer)" << endl;
            if(input == "36")
                return true;
        break;
        case 3: // answer = 45
            cout << "I am a number between 1 and 50. If you add up all of my digits, the sum is 9. What number am I? (integer)" << endl;
            if(input == "45")
                return true;
        break;
    }
    return false;
}

void Game::runTest() const
{
    assert(_allEquipment.at(0).name == "Bow of Odysseus");
    assert(_allEquipment.at(0).description == "Increases player weapon damage by 10"); 
    assert(_allEquipment.at(0).type == 'D');
    assert(_allEquipment.at(0).damage == 10);
    assert(_allEquipment.at(0).defense == 0);
    assert(_allEquipment.at(0).element == 'W');
    assert(_allEquipment.at(0).price == 100);
    cout << "   [loadData tests passed]" << endl;

    Equipment test1 = loadEquipment("Bow of Odysseus|Increases player weapon damage by 10|D|10|0|W|100");
    assert(test1.name == "Bow of Odysseus");
    assert(test1.description == "Increases player weapon damage by 10"); 
    assert(test1.type == 'D');
    assert(test1.damage == 10);
    assert(test1.defense == 0);
    assert(test1.element == 'W');
    assert(test1.price == 100);

    test1 = loadEquipment("Shield of Achilles|Increases player defense by 10|S|0|10|E|100");
    assert(test1.name == "Shield of Achilles");
    assert(test1.description == "Increases player defense by 10"); 
    assert(test1.type == 'S');
    assert(test1.damage == 0);
    assert(test1.defense == 10);
    assert(test1.element == 'E');
    assert(test1.price == 100);
    cout << "   [loadEquipment tests passed]" << endl;

    Potion testP = loadPotion("Lesser Health Potion|Restore HP by 10|P|10|None|25");
    assert(testP.name == "Lesser Health Potion");
    assert(testP.description == "Restore HP by 10");
    assert(testP.type == 'P');
    assert(testP.effectValue == 10);
    assert(testP.price == 25);

    testP = loadPotion("Minor Strength Potion|Permanently increase weapon damage by 2|P|2|None|50");
    assert(testP.name == "Minor Strength Potion");
    assert(testP.description == "Permanently increase weapon damage by 2");
    assert(testP.type == 'P');
    assert(testP.effectValue == 2);
    assert(testP.price == 50);
    cout << "   [loadEquipment tests passed]" << endl;
}