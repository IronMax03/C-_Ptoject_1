#include <string>
#include<vector>
#include "Global.h"

#ifndef ENTITY_H 
#define ENTITY_H 

using namespace std;


class Entity
{
    public:
    // Constructors
        Entity(); // Default constructor
        Entity(string); // Constructor used to load an entity
        Entity(const string, const int, const int, const double, const char);

    // Getters
        /**
        * @return the name of the entity.
        */
        string getName() const;

        /**
        * @return the current HP of the entity.
        */
        double getHP() const;

        /**
        * Calculates and returns the ratio (_HP/_maxHP).
        * 
        * @return The ratio of current hit points to maximum hit points as a double.
        */
        double getHPRatio() const;

        /**
        *  Calculates the attack damage for the entity.
        * 
        * @return The calculated attack damage as an unsigned integer.
        */
        unsigned int getAttackDamage() const; 

        /**
        * @return the current stamina of the entity.
        */        
        double getStamina() const;

        /**
        * @return the current gold hold by the entity.
        */   
        unsigned int getGold() const;

    // Setters
        /**
        * Set the current HP of the entity.
        * If the new value dont exced the maximum value.
        * 
        * @param HP The new value for _HP.
        * @return A pointer to this entity.
        */
        Entity setHP(double);

        /**
        * Set the current stamina of the entity.
        * If the new value dont exced the maximum value.
        * 
        * @param stamina The new value for _stamina.
        * @return A pointer to this entity.
        */
        Entity setStamina(double);

        /**
        * Refills the stamina of the entity to its maximum value.
        * @return A reference to the modified entity.
        */
        Entity fillStamina();

        /**
        * Decreases the entity's stamina by the specified amount.
        * 
        * @param stamina The amount of stamina to remove.
        * @return A reference to the modified entity.
        */
        Entity removeStamina(double);  

    // Other member functions
        /**
        * This function deducts the specified amount of gold from the entity's current
        * gold balance. If the entity has sufficient gold to cover the payment, the
        * payment is made, and the function returns true. If the entity does not have
        * enough gold, no deduction is made, and the function returns false.
        * 
        * @param paymentAmount The amount of gold to deduct from the entity's balance.
        * @return true if the payment was successful, false otherwise.
        */
        bool removeGold(unsigned int);

        /**
        * Purchases a equipment for the entity.
        * Deducts equipment price from entity's gold using removeGold().
        * If successful, adds equipment to entity's inventory.
        * 
        * @param item The equipment to purchase.
        * @return True if successful, false otherwise.
        */
        bool buyEquipment(Equipment);

        /**
        * Purchases a potion for the entity.
        * Deducts potion price from entity's gold using removeGold().
        * If successful, adds potion to entity's inventory.
        * @param item The potion to purchase.
        * @return True if successful, false otherwise.
        */
        bool buyPotion(Potion);

        /**
        * Display the shop menu to sell items.
        * And sell the item.
        */
        void sellItem();

        /**
        * Prints the entity stats 
        */
        void printStats() const;

        /**
        * Allows the entity to consume potions from its inventory.
        */
        void usePotion();

        /**
        * Process the entity being attacked and takes damage.
        * 
        * @param damage The amount of damage inflicted by the attacker.
        */
        void attack(double dammage);

        /**
        * Adds an item to the entity's inventory.
        * 
        * @param item The equipment item to add to the inventory.
        */
        void addItem(Equipment);

        /**
        * Allows the entity to loot another entity, transferring items to the looter's inventory.
        * 
        * @param looter The entity that is looting.
        */
        void loot(Entity&);

        /**
         * Allows the entity  equipp items.
         */
        void swap();

        /**
        * Allows the entity to drop an item from its inventory.
        */
        void dropItem();


        /**
        * Provides the entity with a damage bonus.
        */
        void addAdvantage();


        static vector<Potion> allPotions;
        static vector<Equipment> allEquipment;

    private:
        /**
        * Displays the contents of the entity's inventory, including equipped items.
        */
        void showInventory() const;

        /**
        * Displays information about a weapon (or equipment) item.
        * 
        * @param weapon The weapon item to display information about.
        */
        void showWepon(Equipment) const;


    // static variable
        static unsigned int EntityCount;         // Holds the current amount of entitys instances

    // Attributes
        unsigned int _maxHP, _maxStamina, _damageBoost;        // the maximum values of HP and stamina
        string _name;                   // Name of the entity
        double _HP;                     // Current HP of the entity
        double _stamina;                // Current stamina of the entity
        double _defense;                // Defense value of the entity
        char _condition;                // Condition of the entity
        unsigned int _advantage;         // Damage Advantage

        vector<Potion> _potions;        // List of potions held by the entity
        int _equipped[2];    // List of equipment currently equipped by the entity
        vector<Equipment> _inventory;   // List of equipment in the entity's inventory
        vector<int> _itemsNum; 
        float _calamity;

        unsigned int _gold;

        char _weakness;                 // elemental weakness
};
#endif