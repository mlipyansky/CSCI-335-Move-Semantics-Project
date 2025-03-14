#include "Inventory.hpp"
#include <stdexcept> // For std::out_of_range

/**
* @brief Constructor with optional parameters for initialization.
* @param items A const reference to a 2D vector of items.
*  Defaults to a 10x10 grid of default-constructed items, if none provided.
* @param equipped A pointer to an Item object.
*  Defaults to nullptr, if none provided.
*
* @post Initializes members in the following way:
* 1) Initializes `weight_` as the total weight of all items in `items` (excluding NONE type)
* 2) Initialies `item_count_` as the count of non-NONE items.
*
* NOTE: The `equipped` item is excluded from these calculations.
*/
Inventory::Inventory(
        const std::vector<std::vector<Item>>& items,
        Item* equipped
) : inventory_grid_(items), equipped_(equipped), weight_(0), item_count_(0) {
    // Compute initial weight and item count (excluding equipped item)
    for (const auto& row : inventory_grid_) {
        for (const auto& item : row) {
            if (item.type_ != NONE) {
                weight_ += item.weight_;
                item_count_++;
            }
        }
    }
}

/**
* @brief Retrieves the value stored in `equipped_`
* @return The Item pointer stored in `equipped_`
*/
Item* Inventory::getEquipped() const {
    return equipped_;
}

/**
* @brief Equips a new item.
* @param itemToEquip A pointer to the item to equip.
* @post Updates `equipped` to the specified item
* without deallocating the original.
*/
void Inventory::equip(Item* itemToEquip) {
    equipped_ = itemToEquip;
}

/**
* @brief Discards the currently equipped item.
* @post Deallocates the item pointed to by `equipped`
* and sets `equipped` to nullptr, if `equipped` is not nullptr already.
*/
void Inventory::discardEquipped() {
    if (equipped_) {
        delete equipped_;
        equipped_ = nullptr;
    }
}

/**
* @brief Retrieves the value stored in `inventory_grid_`
* @return The vector<vector<Item>> value stored in `inventory_grid_`
*/
std::vector<std::vector<Item>> Inventory::getItems() const {
    return inventory_grid_;
}

/**
* @brief Retrieves the value stored in `weight_`
* @return The float value stored in `weight_`
*/
float Inventory::getWeight() const {
    return weight_;
}

/**
* @brief Retrieves the value stored in `item_count_`
* @return The size_t value stored in `item_count_`
*/
size_t Inventory::getCount() const {
    return item_count_;
}

/**
* @brief Retrieves the item located at the specified row and column
* in the inventory grid.
*
* @param row A size_t parameter for the row index in the inventory grid.
* @param col A size_t parameter for the column index in the inventory grid.
* @return The item at the specified row and column.
* @throws std::out_of_range If the row or column is out of bounds.
*/
Item Inventory::at(const size_t& row, const size_t& col) const {
    if (row >= inventory_grid_.size() || col >= inventory_grid_[row].size()) {
        throw std::out_of_range("Invalid inventory index."); // Out of bounds
    }
    return inventory_grid_[row][col]; // Return the item at the specified location
}

/**
* @brief Stores an item at the specified row and column in the inventory grid.
*
* @param row A size_t parameter for the row index in the inventory grid.
* @param col  A size_t parameter for the column index in the inventory grid.
* @param pickup A const ref. to the item to store at the specified location.
* @return True if the item was successfully stored, false if the cell is already occupied.
*
* @post Updates `item_count_` and `weight_` if the Item is sucessfully added
* @throws std::out_of_range If the row or column is out of bounds.
*/
bool Inventory::store(const size_t& row, const size_t& col, const Item& pickup) {
    if (row >= inventory_grid_.size() || col >= inventory_grid_[row].size()) {
        throw std::out_of_range("Invalid inventory index."); // Out of bounds
    }
    if (inventory_grid_[row][col].type_ != NONE) {
        return false; // Cell is occupied
    }
    inventory_grid_[row][col] = pickup;
    weight_ += pickup.weight_;
    item_count_++;
    return true;
}

/**
* @brief Copy constructor for the Inventory class.
* @param rhs A const l-value ref. to the Inventory object to copy.
* @post Creates a deep copy of `rhs`,
*  including duplicating the dynamically
*  allocated item in `equipped`.
*/
Inventory::Inventory(const Inventory& rhs)
        : inventory_grid_(rhs.inventory_grid_), weight_(rhs.weight_), item_count_(rhs.item_count_) {
    equipped_ = (rhs.equipped_) ? new Item(*rhs.equipped_) : nullptr;
}

/**
* @brief Move constructor for the Inventory class.
* @param rhs An r-value ref. to the Inventory object to move from.
* @post Transfers ownership of resources from `rhs`
* to the newly constructed Inventory object.
*
* Sets `rhs` to a valid but empty state.
* - All pointers are set to nullptr
* - All numerical values are set to 0
* - All containers are cleared to have size 0
*/
Inventory::Inventory(Inventory&& rhs)
        : inventory_grid_(std::move(rhs.inventory_grid_)),
          equipped_(rhs.equipped_),
          weight_(rhs.weight_),
          item_count_(rhs.item_count_) {
    rhs.equipped_ = nullptr;
    rhs.weight_ = 0;
    rhs.item_count_ = 0;
}

/**
* @brief Copy assignment operator for the Inventory class.
* @param rhs A const l-value ref. to the Inventory object to copy.
* @return A reference to the updated Inventory object.
* @post Performs a deep copy of `rhs`, including
* re-allocating and copying the item in `equipped`.
*
* NOTE: The resources of the overridden object
* should be destroyed.
*/
Inventory& Inventory::operator=(const Inventory& rhs) {
    if (this != &rhs) {
        // Cleanup existing resources
        delete equipped_;

        // Copy resources
        inventory_grid_ = rhs.inventory_grid_;
        weight_ = rhs.weight_;
        item_count_ = rhs.item_count_;
        equipped_ = (rhs.equipped_) ? new Item(*rhs.equipped_) : nullptr;
    }
    return *this;
}

/**
* @brief Move assignment operator for the Inventory class.
* @param rhs An r-value ref. to the Inventory object to move from.
* @return A reference to the updated Inventory object.
* @post Transfers ownership of resources from `rhs`
* to the newly constructed Inventory object.
*
* Sets `rhs` to a valid but empty state.
* - All pointers are set to nullptr
* - All numerical values are set to 0
* - All containers are cleared to have size 0
*
* NOTE: The resources of the overridden object
* should be destroyed.
*/
Inventory& Inventory::operator=(Inventory&& rhs) {
    if (this != &rhs) {
        // Cleanup existing resources
        delete equipped_;

        // Move resources
        inventory_grid_ = std::move(rhs.inventory_grid_);
        equipped_ = rhs.equipped_;
        weight_ = rhs.weight_;
        item_count_ = rhs.item_count_;

        // Leave rhs in valid empty state
        rhs.equipped_ = nullptr;
        rhs.weight_ = 0;
        rhs.item_count_ = 0;
    }
    return *this;
}

/**
* @brief Destructor for the Inventory class.
* @post Deallocates any dynamically allocated resources.
*/
Inventory::~Inventory() {
    delete equipped_;
    equipped_ = nullptr;
}
