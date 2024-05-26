#include<iostream>
#include<cassert>
#include "Global.h"
#include "Entity.h"
#include "Game.h"
#include "Map.h"

using namespace std;

void runTests();

int main()
{   
    runTests();    
    clearTerminal();
    Game myGame;

    myGame.startGame();

    while(myGame.updateGame());

    return 0;
}

void runTests()
{
    hLine();

    // Game class tests
    Game test4;
    test4.runTest();
    cout << "  [Game tests passed]" << endl;

    // Equipment struct tests
    Equipment test1;
    test1.name = "name Test 1";
    test1.description = "description Test 1";
    test1.name = "Test 1";
    assert(test1.name == "Test 1");
    cout << "  [Structs tests passed]" << endl;

    // Entity struct tests
    Entity test2("test 2", 100, 50, 10, 'a');
    assert(test2.getHP() == 100);
    assert(test2.getName() == "test 2");
    assert(test2.getStamina() == 50);

    assert(test2.setHP(120).getHP() == 100);
    assert(test2.setHP(50).getHP() == 50);

    assert(test2.setStamina(100).getStamina() == 50);
    assert(test2.setStamina(25).getStamina() == 25);

    Entity test3;
    assert(test3.getName() == "Entity 2");

    Entity loadingTest("95|The Laestrygonian King|220|100|55|H|True|E|Lesser Health Potion,King's Blade|1,1|none");
    assert(loadingTest.getName() == "The Laestrygonian King");
    assert(loadingTest.getHP() == 220);
    assert(loadingTest.getStamina() == 100);

    loadingTest = Entity("40|Cicones|140|90|20|H|False|E|Lesser Health Potion,Ciconian Spear|1,1|none");
    assert(loadingTest.getName() == "Cicones");
    assert(loadingTest.getHP() == 140);
    assert(loadingTest.getStamina() == 90);

    loadingTest = Entity("50|Odysseus|100|100|0|H|False|W|Lesser Health Potion,Bow of Odysseus|1,1|none");
    assert(loadingTest.getName() == "Odysseus");
    assert(loadingTest.getHP() == 100);
    assert(loadingTest.getStamina() == 100);

    cout << "  [Entity tests passed]" << endl;

    vector<int> vecTest;
    vecTest.push_back(1);
    vecTest.push_back(2);
    vecTest.push_back(3);
    vecTest.push_back(4);
    removeFromVec<int>(vecTest, 1);
    assert(vecTest.size() == 3);
    assert(vecTest.at(0) == 1);
    assert(vecTest.at(1) == 3);
    assert(vecTest.at(2) == 4);

    vecTest.clear();
    vecTest.push_back(5);
    vecTest.push_back(4);
    vecTest.push_back(3);
    removeFromVec<int>(vecTest, 0);
    assert(vecTest.size() == 2);
    assert(vecTest.at(0) == 4);
    assert(vecTest.at(1) == 3);

    vecTest.clear();
    vecTest.push_back(10);
    vecTest.push_back(5);
    removeFromVec<int>(vecTest, 1);
    assert(vecTest.size() == 1);
    assert(vecTest.at(0) == 10);

    for(unsigned int i = 0; i < 50; i++)
    {
        assert(randomeInt(0, 10) <= 10 && randomeInt(0, 10) >= 0);
        assert(randomeInt(1, 2) <= 2 && randomeInt(1, 2) >= 1);
    }
    cout << "  [Global functions tests passed]" << endl;
    cout << "[All tests cases passed]" << endl;
    hLine();
}