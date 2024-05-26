#include <iostream>
#include "Global.h"
#include "Entity.h"
#include <string>

unsigned int  Entity::EntityCount = 0;
vector<Potion> Entity::allPotions;
vector<Equipment> Entity::allEquipment;

Entity::Entity()
{
    ++EntityCount;

    _name = "Entity " + to_string(EntityCount);
    _maxHP = 0;
    _HP = 0;
    _maxStamina = 0;
    _stamina = 0;
    _defense = 0;
    _condition = 0;
    _advantage = 0;

    if(debugMode) cout  << DEBUG_COLOR << "{Debug - Entity instantiated}("<< "Name: " << _name 
                                                                    << " | EntityCount: " << EntityCount 
                                                                    << " | HP: " << _HP 
                                                                    << " | _maxHP: " << _maxHP 
                                                                    << " | Stamina: " << _stamina 
                                                                    << " | _maxStamina: " << _maxStamina 
                                                                    << " | Defense: " << _defense 
                                                                    << " | Condition: " << _condition 
                                                                    << " | Potions Size: " << _potions.size() 
                                                                    << " | Inventory Size: " << _inventory.size() 
                                                                    << ")" << RESET << endl;
}
                    

Entity::Entity(string import)
{
    string equipmentName;
    string potionName;
    _equipped[0] = 0;
    _equipped[1] = 0;

    for(int i = 0, count = 0; i < import.length(); ++i)
    {
        if(import[i] == '|')
        {
            switch (count)
            {
                case 0:
                    _gold = stoi(import.substr(0,i));
                break;
                case 1:
                    _name = import.substr(0,i);
                break;
                case 2:
                   _HP = stoi(import.substr(0,i));
                   _maxHP = _HP;
                break; 
                case 3:
                   _stamina = stoi(import.substr(0,i));
                   _maxStamina = _stamina;
                break;
                case 4:
                   _defense = stoi(import.substr(0,i));
                break;
                case 5:
                    _condition = import[0];
                break;
                case 6:
                    _advantage = 0;
                break;
                case 7:
                    _weakness = import[0];
                break;
                case 8:
                    for(int j = 0; j < i; j++)
                    {
                        if(import[j] == ',')
                        {
                            potionName = import.substr(0, j);
                            equipmentName = import.substr(j+1, i - j - 1);
                            break;
                        }
                    }
                break;
                case 9: // items number
                    for(int j = 0; j < i; j++)
                    {
                        if(import[j] == ',')
                        {
                            _itemsNum.push_back(stoi(import.substr(0, j)));
                            _itemsNum.push_back(stoi(import.substr(j+1, i)));
                            break;
                        }
                    }
                break;
            }
            count++;
            import = import.substr(i+1, import.length());
            i = 0;
        }
    }

    for(int i = 0; i < allPotions.size(); ++i)
    {
        if(allPotions.at(i).name == potionName)
        {
            _potions.push_back(allPotions.at(i));
            if(debugMode) cout  << DEBUG_COLOR << "{Debug - Entity}(potion found| name:" << potionName << ")" << RESET << endl;
            break;
        }
    }

    for(int i = 0; i < allEquipment.size(); ++i)
    {
        if(allEquipment.at(i).name == equipmentName)
        {
            if(debugMode) cout  << DEBUG_COLOR << "{Debug - Entity}(equipment found | name:" << equipmentName << ")" << RESET << endl;
            _inventory.push_back(allEquipment.at(i));
            break;
        }
    }
    

    if(debugMode) cout  << DEBUG_COLOR << "{Debug - Entity instantiated}("<< "Name: " << _name 
                                                                    << " | EntityCount: " << EntityCount 
                                                                    << " | HP: " << _HP 
                                                                    << " | _maxHP: " << _maxHP 
                                                                    << " | Stamina: " << _stamina 
                                                                    << " | _maxStamina: " << _maxStamina 
                                                                    << " | Defense: " << _defense 
                                                                    << " | Condition: " << _condition 
                                                                    << " | Potions Size: " << _potions.size() 
                                                                    << " | Inventory Size: " << _inventory.size() 
                                                                    << ")" << RESET << endl;
}


Entity::Entity(const string name, const int maxHP, const int maxStamina, const double defense, const char condition)
{
    ++EntityCount;

    if(name != "")
        _name = name;
    else
        _name = "Entity " + to_string(EntityCount);

    _maxHP = maxHP;
    _HP = maxHP;
    _maxStamina = maxStamina;
    _stamina = maxStamina;
    _defense = defense;
    _condition = condition;
    _advantage = 0;

    if(debugMode) cout  << DEBUG_COLOR << "{Debug - Entity instantiated}("<< "Name: " << _name 
                                                                    << " | EntityCount: " << EntityCount 
                                                                    << " | HP: " << _HP 
                                                                    << " | _maxHP: " << _maxHP 
                                                                    << " | Stamina: " << _stamina 
                                                                    << " | _maxStamina: " << _maxStamina 
                                                                    << " | Defense: " << _defense 
                                                                    << " | Condition: " << _condition 
                                                                    << " | Potions Size: " << _potions.size() 
                                                                    << " | Inventory Size: " << _inventory.size() 
                                                                    << ")" << RESET << endl;
}

// Getters
string Entity:: getName() const
{
    return _name;
}

double Entity:: getHP() const
{
    return _HP;
}

double Entity::getStamina() const
{
    return _stamina;
}

unsigned int Entity::getGold() const
{
    return _gold;
}

// Setters
Entity Entity::setHP(double HP)
{
    if(HP <= _maxHP && HP >= 0)
    {
        _HP = HP;
    }
    if(debugMode) cout << DEBUG_COLOR << "{Debug - Entity(" << _name << ") setHP}(HP: " << HP 
                                                                    << " | _HP:" << _HP 
                                                                    << " | _maxHP:" << _maxHP <<")" << RESET << endl;
    return *this;
}

Entity Entity::setStamina(double stamina)
{
    if(stamina <= _maxStamina && stamina >= 0)
    {
        _stamina = stamina;
    }
    if(debugMode) cout << DEBUG_COLOR << "{Debug - Entity(" << _name << ") setStamina}(stamina: "  << stamina 
                                                                            << " | _stamina: " << _stamina 
                                                                            << " | _maxStamina: " << _maxStamina 
                                                                            << ")" << RESET << endl;
    return *this;
}

Entity Entity::fillStamina()
{
    _stamina = _maxStamina;
    return *this;
}

Entity Entity::removeStamina(double stamina)
{
    if(stamina <= _stamina)
        setStamina(_stamina - stamina);
    else 
        setStamina(0);
    return *this;
}

//other member functions
bool Entity::removeGold(unsigned int paymentAmount)
{
    if(_gold >= paymentAmount)
    {
        _gold -= paymentAmount;
        if(debugMode) cout << DEBUG_COLOR << "{Debug - Entity(" << _name << ") setHP}(paymentAmount: " << paymentAmount << " | _gold:" << _gold << ")" << RESET << endl;
        return true;
    }
    return false;
}

bool Entity::buyEquipment(Equipment item)
{
    if(removeGold(item.price))
    {
        _inventory.push_back(item);
        if(debugMode) cout  << DEBUG_COLOR << "{Debug - Entity(" << _name << ") buyEquipment}(item name: " << item.name << ")" << RESET << endl;
        return true;
    }
    return false;
}

bool Entity::buyPotion(Potion item)
{
    if(removeGold(item.price))
    {
        _potions.push_back(item);
        if(debugMode) cout  << DEBUG_COLOR << "{Debug - Entity(" << _name << ") buyPotion}(item name: " << item.name << ")" << RESET << endl;
        return true;
    }
    return false;
}

void Entity::sellItem()
{
    clearTerminal();
    cout << "0. Back to main shop menu" << endl;
    for(uint8_t i = 0; i < _potions.size(); ++i)
    {
        cout << i + 1 << ". " << _potions.at(i).name << " - " << _potions.at(i).description << "   [" << _potions.at(i).price << "$]" << endl;                 
    }

    for(unsigned int i = 0; i < _inventory.size(); ++i)
    {
        cout << i + _potions.size() + 1 << ". ";
        showWepon(_inventory.at(i));
        cout << "   [" << _inventory.at(i).price << "$]" << endl;
    }

    uint8_t input = safeInput(0, _potions.size() + _inventory.size()) -1;

    if(input != -1)
    {
        if(input >= _potions.size())
        {
            input -= _potions.size();
            cout << _inventory.at(input).name << " has been sold for " << _inventory.at(input).price << "$." << endl;
            _gold += _inventory.at(input).price;
            if(debugMode) cout  << DEBUG_COLOR << "{Debug - Entity sellItem}(type: " << _inventory.at(input).type 
                                                            << " | potion name: " << _inventory.at(input).name 
                                                            << " | price: " << _inventory.at(input).price
                                                            << " | _gold: " << _gold
                                                            << ")" << RESET << endl;
            removeFromVec(_inventory, input);
        }
        else
        {
            cout << _potions.at(input).name << " has been sold for " << _potions.at(input).price << "$." << endl;
            _gold += _potions.at(input).price;
            if(debugMode) cout  << DEBUG_COLOR << "{Debug - Entity sellItem}(type: potion | potion name: " << _potions.at(input).name 
                                                                                        << " | price: " << _potions.at(input).price
                                                                                        << " | _gold: " << _gold
                                                                                        << ")" << RESET << endl;
            removeFromVec(_potions, input);
        } 
    }   
}

void Entity::printStats() const
{
    clearTerminal();
    cout << "Character Name: " << _name << endl; 
    cout << "HP: " << _HP << endl; 
    cout << "Stamina: " << _stamina << endl; 
    cout << "Defense: " << _defense << endl;
    cout << "Condition: " << _condition << endl;
    cout << "Gold: " << _gold << "$" << endl;
    clearTerminal();
}

void Entity::usePotion()
{
    unsigned int input;
    while(true)
    {
        if(_potions.size() == 0)
        {
            clearTerminal();
            cout << "You dont have any potions." << endl;
            return;
        }

        clearTerminal();
        cout << "0. Back to main menu" << endl;
        for(unsigned int i = 0; i < _potions.size(); ++i)
            cout << i+1 << ". " << _potions.at(i).name << " - " << _potions.at(i).description << endl;
        input = safeInput(0, _potions.size());

        if(input != 0)
        {
            input -= 1;
            const Potion usedPotion = _potions.at(input);

            switch(_potions.at(input).type)
            {
                case 'H':
                    setHP(getHP() + _potions.at(input).effectValue);
                break;
                case 'S':
                    setStamina(_potions.at(input).effectValue);
                break;
                case 'A':
                    setHP(_potions.at(input).effectValue);
                    setStamina(_potions.at(input).effectValue);
                break;
                case 'D':
                    _damageBoost = _potions.at(input).effectValue;
                break;
                case 'X':

                break;
            }
            removeFromVec<Potion>(_potions, input);
            cout << usedPotion.name << " has been used." << endl;
            if(debugMode) cout  << DEBUG_COLOR << "{Debug - Entity(" << _name << ") usePotion}(potion name: " << usedPotion.name 
                                                                                  << " | potion type: " << usedPotion.type
                                                                                  << " | potion effect value: " << usedPotion.effectValue 
                                                                                  << " | _potions size: " << _potions.size()
                                                                                  << ")" << RESET << endl;
        }
        else break;
    }    
}

void Entity::swap()
{
    clearTerminal();
    cout << "0. back" << endl;
    showInventory();
    uint8_t input = safeInput(0, _inventory.size());
    if(input != 0)
    {
        unsigned int input2 = safeInput("Do you want to equiped this Equipment in which slote(1. or 2.)?", 1, 2) - 1;
        _equipped[input2] = input - 1;
        clearTerminal();
        cout << _inventory.at(_equipped[input2]).name << " has been equiped at slote " << input2 << ".";
    }
}

void Entity::dropItem()
{
    if(_inventory.size() == 0)
    {
        cout << "Your inventory is empty." << endl;
        return;
    }

    clearTerminal();
    cout << "Select the item to drop([*] = equiped):" << endl;
    cout << "0. back" << endl;
    showInventory();
    uint8_t input = safeInput(0, _inventory.size());
    if(input != 0)
    {
        cout << _inventory.at(input - 1).name << " as been droped." << endl;
        removeFromVec<Equipment>(_inventory, input - 1);

        if(_equipped[0] == input - 1) 
            _equipped[0] = -1;
        else if(_equipped[1] == input - 1) 
            _equipped[1] = -1;
    }
}

void Entity::showInventory() const
{
    for(unsigned int i = 0; i < _inventory.size(); ++i)
    {
        cout << i + 1 << ". ";
        showWepon(_inventory.at(i));

        if(_equipped[0] == i || _equipped[1] == i)
            cout << "  [*]";
        cout << endl;
    }
}

void Entity::showWepon(Equipment wepon) const
{
    cout <<  wepon.name;

    if(wepon.type == 'D') 
        cout << "(+" << wepon.damage << " damage)";
    else if(wepon.type == 'S') 
        cout << "(+" << wepon.defense << " defense)";

    switch (wepon.element)
    {
        case 'W': // water
            cout << BLUE << "  [WATER]" << RESET;
        break;
        case 'A': // air
            cout << WHITE << "  [AIR]" << RESET;
        break;
        case 'F': // fire
            cout << RED << "  [FIRE]" << RESET;
        break;
        case 'E': // earth
            cout << GREEN << "  [EARTH]" << RESET;
        break;
    }
}

double Entity::getHPRatio() const
{
    return _HP/_maxHP;
}

void Entity::loot(Entity& looter)
{

    cout << "0. finish turn." << endl;
    for(unsigned int i = 0; i < _inventory.size(); i++)
    {
        cout << i + 1 << ". ";
        showWepon(_inventory.at(i));
        cout << endl;
    }

    unsigned int input = safeInput(0, _inventory.size()) - 1;
    if(input == -1) return; 
    looter.addItem(_inventory.at(input));        
}

void Entity::addItem(Equipment item)
{
    _inventory.push_back(item);
    if(debugMode) cout << DEBUG_COLOR <<  "{Debug - Entity addItem}(name:" << item.name << " | description: " << item.description <<  ")" << RESET << endl;
}

void Entity::attack(double damages)
{
    unsigned int defense = _defense + _inventory.at(_equipped[0]).defense + _inventory.at(_equipped[1]).defense;
    damages = limit(damages - defense, 0, damages - 1) + 1;
    if(damages > _HP) 
        _HP = 0;
    else
        _HP -= damages;

    cout << _name << " got hit, taking " << damages << " damages." << endl;
    if(debugMode) cout << DEBUG_COLOR <<  "{Debug - Entity Attack}(Name:" << _name << " | dammage: " << damages << " | _HP: " << _HP << ")" << RESET << endl;
}

unsigned int Entity::getAttackDamage() const
{
    unsigned int damage = _inventory.at(_equipped[0]).damage + _inventory.at(_equipped[1]).damage + _advantage;
    return randomeInt(1, damage + 1);
}

void Entity::addAdvantage()
{
    _advantage = randomeInt(5, 10);
    cout << _name << " gained +" << _advantage << " damage bonus." << endl;
}