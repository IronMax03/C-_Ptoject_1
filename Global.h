/**
* This header file hold all structs and non-member functions used in different class and some developer settings.
*/
#include <string>
#include <iostream>
#include<cstdlib>

#ifndef GLOBAL_H 
#define GLOBAL_H

#define RED     "\033[31m" // fire
#define BLUE    "\033[34m" // water
#define WHITE   "\033[37m" // air
#define GREEN   "\033[32m" // earth

#define DEBUG_COLOR  "\033[33m"

#define RESET   "\033[0m"

using namespace std;

/**
* Developer setting:
* if set to true, will output most function calls for debugging.
*/
static const bool debugMode = false;

/**
* Developer setting:
* The amount of newlines printed by clearTerminal().
*/
static const unsigned int clearTerminalSize = 5;

/**
* Developer setting:
* Size of the horizontal line printed by hLine().
*/
static const unsigned int hLineSize = 75;

/**
* Developer setting:
* The initial value of calamity chance
*/
static const unsigned int initialCalamityChance = 30;

/**
* Developer setting:
* Chance to miss an attack during combat(1/chanceToMiss).
*/
static const unsigned int chanceToMiss = 5;

/**
* Struct defining Equipment attributes
*/
struct Equipment
{
    string name;        // Name of the equipment
    string description; // Description of the equipment
    char type;          // Type of the equipment ('D' denotes damage, 'S' denotes a shield)
    char element;       // Element associated with the equipment ('W' = water, 'A' = air, 'F' = fire, and 'E' = earth)
    int damage;         // Damage value of the equipment. damage weapons will have a value here, and their defense will be 0.
    int defense;        // Defense value of the equipment. shield weapons will have a value here, and their damage will be 0.
    int price;          // Price of the equipment
};

/**
* Struct defining Potion attributes
*/
struct Potion
{
    string name;        // Name of the potion
    string description; // Description of the potion
    char type;          // Type of the potion. 'P' for potion (to help identify from all other items).
    int effectValue;    // Effect value of the potion. default this to 0 for cleansing potions.
    int price;          // price of the potion in the shop.
};

/**
* Clears the terminal screen by outputting multiple newline characters.
* The amount of newlines is define by the constante clearTerminalSize.
*/
static void clearTerminal()
{
    for(unsigned int i = 0; i < clearTerminalSize; i++) cout << endl;
}

/**
* Print an horizontal line.
* The length of the line is define by hLineSize
*/
static void hLine()
{
    cout << endl;
    for(unsigned int i = 0; i < hLineSize; i++) cout << "-";
    cout << endl << endl;
}

/**
 * Prompts the user for input within a specified range.
 * 
 * @param min The minimum correct input value.
 * @param max The maximum correct input value.
 * @return The input value entered by the user within the specified range.
 * 
 * @note Both the parameters and return types are a 8 bits int.
 */
static uint8_t safeInput(uint8_t min, uint8_t max)
{
    cin.clear();
    int input;
    string temp;
    cout << ">";
    getline(cin, temp);

    try 
    {
        input = stoi(temp);
        if(input < min || input > max)
        {
            cout << "The given integer is out of bounds." << endl;
            throw 0;
        }
    }
    catch (...) 
    {
        cout << "Incorrect input try again." << endl;
        return safeInput(min, max);
    } 

    if(debugMode) cout  << DEBUG_COLOR << "{Debug - safeInput}(return value: " << input << ")" << RESET << endl;
    return input;
}

/**
* Prompts the user for input within a specified range.
* 
* @param message The message to display to the user when the function is called.
* @param min The minimum correct input value.
* @param max The maximum correct input value.
* @return The input value entered by the user within the specified range.
* 
* @note Both the parameters(execepte the first one) and return types are a 8 bits int.
*/
static uint8_t safeInput(string message, uint8_t min, uint8_t max)
{
    cin.clear();
    int input;
    string temp;
    clearTerminal();
    cout << message << "\n>";
    getline(cin, temp);

    try 
    {
        input = stoi(temp);
        if(input < min || input > max)
        {
            cout << "The given integer is out of bounds." << endl;
            throw 0;
        }
    }
    catch (...) 
    {
        clearTerminal();
        cout << message << endl;
        cout << "Incorrect input try again." << endl;
        return safeInput(min, max);
    } 

    if(debugMode) cout  << DEBUG_COLOR << "{Debug - safeInput}(return value: " << input << ")" << RESET << endl;
    return input;
}

/**
 * Execute and return the rand() function.
 * prints the randome value if Debug mode is activated.
 * @return Random unsigned integer.
 */
static unsigned int randomeInt()
{
    unsigned int temp = rand();
    if(debugMode) cout  << DEBUG_COLOR << "{Debug - randomeInt}(random integer: " << temp << ")" << RESET << endl;
    return temp;
}

/**
 * Generates a random unsigned integer within a specified range.
 * 
 * @param max The maximum value of the generated random integer.
 * @param min The minimum value of the generated random integer.
 * @return An unsigned integer randomly generated within the range [min, max].
 */
static unsigned int randomeInt(unsigned int min, unsigned int max)
{
    unsigned int temp = (rand() % (max - min + 1)) + min;
    if(debugMode) cout  << DEBUG_COLOR << "{Debug - randomeInt}(min:" << min << " | max: " << max << " | random integer: " << temp << ")" << RESET << endl;
    return temp;
}

/**
 * Removes an element from a vector at a specified index. 
 * 
 * @tparam type The type of elements stored in the vector.
 * @param vec The vector from which to remove the element.
 * @param index The index of the element to be removed.
 * @note This function modifie the vector by the refference.
 */
template<typename type>
static void removeFromVec(vector<type> &vec, unsigned int index)
{
    vector<type> newVec;
    for(unsigned int i = 0; i < vec.size(); i++)
    {
        if(i != index)
            newVec.push_back(vec.at(i));
    }
    vec = newVec;
    if(debugMode) cout  << DEBUG_COLOR << "{Debug - removeFromVec}(addresse: " << &vec << " | index: " << index <<  ")" << RESET << endl;
}

/**
 * @brief Limits a variable within a specified range.
 * 
 * @param var The variable to be limited.
 * @param min The minimum allowed value.
 * @param max The maximum allowed value.
 * @return int The limited value of the variable.
 */
static int limit(int var, int min, int max)
{
    if(var < min)
    {
        if(debugMode) cout  << DEBUG_COLOR << "{Debug - limit}(var: " << var << " | min: " << min << " | max: " << max << " | return: " << min <<  ")" << RESET << endl;
        return min;
    }
    else if(var > max)
    {
        if(debugMode) cout  << DEBUG_COLOR << "{Debug - limit}(var: " << var << " | min: " << min << " | max: " << max << " | return: " << max <<  ")" << RESET << endl;
        return max;
    }

    if(debugMode) cout  << DEBUG_COLOR << "{Debug - limit}(var: " << var << " | min: " << min << " | max: " << max << " | return: " << var <<  ")" << RESET << endl;
    return var;
}

#endif