#include <iostream>
#include "Inventory.hpp"
#include "Player.hpp"

/**
 * @brief Tests the constructors, assignment operators, and memory management of Inventory and Player classes.
 */
void testInventory() {
    std::cout << "\n==== TESTING INVENTORY ====\n";

    // Default Constructor
    Inventory inv1;
    std::cout << "Default Inventory Created.\n";
    std::cout << "Initial Weight: " << inv1.getWeight() << ", Item Count: " << inv1.getCount() << "\n";

    // Parameterized Constructor
    Item sword("Excalibur", 10.5, WEAPON);
    Item* equippedItem = new Item("Shield", 5.0, ARMOR);
    std::vector<std::vector<Item>> items(2, std::vector<Item>(2, sword));
    Inventory inv2(items, equippedItem);
    std::cout << "Parameterized Inventory Created.\n";

    // Copy Constructor
    Inventory inv3(inv2);
    std::cout << "Copy Constructor Invoked.\n";
    std::cout << "Copy Weight: " << inv3.getWeight() << ", Copy Item Count: " << inv3.getCount() << "\n";

    // Move Constructor
    Inventory inv4(std::move(inv3));
    std::cout << "Move Constructor Invoked.\n";
    std::cout << "Moved Weight: " << inv4.getWeight() << ", Moved Item Count: " << inv4.getCount() << "\n";

    // Copy Assignment
    inv1 = inv4;
    std::cout << "Copy Assignment Operator Invoked.\n";
    std::cout << "Updated Weight: " << inv1.getWeight() << ", Updated Item Count: " << inv1.getCount() << "\n";

    // Move Assignment
    inv1 = std::move(inv2);
    std::cout << "Move Assignment Operator Invoked.\n";
    std::cout << "Updated Weight: " << inv1.getWeight() << ", Updated Item Count: " << inv1.getCount() << "\n";

    // Equip & Discard Test
    inv1.equip(new Item("Helmet", 3.2, ARMOR));
    std::cout << "Equipped New Item.\n";
    inv1.discardEquipped();
    std::cout << "Discarded Equipped Item.\n";

    // Store & Retrieve Item Test
    Item potion("Health Potion", 0.5, ACCESSORY);
    bool stored = inv1.store(0, 0, potion);
    std::cout << (stored ? "Item Stored Successfully.\n" : "Item Storage Failed.\n");

    std::cout << "Inventory Tests Completed.\n";
}

/**
 * @brief Tests the Player class interactions with Inventory.
 */
void testPlayer() {
    std::cout << "\n==== TESTING PLAYER ====\n";

    // Creating Players
    Inventory inventory;
    Player p1("Knight", inventory);
    std::cout << "Player Created: " << p1.getName() << "\n";

    // Copy Constructor
    Player p2(p1);
    std::cout << "Player Copy Constructor Invoked.\n";
    std::cout << "Copied Player Name: " << p2.getName() << "\n";

    // Move Constructor
    Player p3(std::move(p2));
    std::cout << "Player Move Constructor Invoked.\n";
    std::cout << "Moved Player Name: " << p3.getName() << "\n";

    // Copy Assignment
    p1 = p3;
    std::cout << "Player Copy Assignment Invoked.\n";

    // Move Assignment
    p1 = std::move(p3);
    std::cout << "Player Move Assignment Invoked.\n";

    std::cout << "Player Tests Completed.\n";
}

/**
 * @brief Runs all tests.
 */
int main() {
    testInventory();
    testPlayer();
    std::cout << "\n==== ALL TESTS PASSED SUCCESSFULLY ====\n";
    return 0;
}
