#include <iostream>
#include <map>
#include <stdexcept>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Function to validate the quantity input
void validateQuantity(int quantity, int availableQuantity) {
    if (quantity <= 0) {
        throw std::invalid_argument("Quantity must be greater than zero.");
    }

    if (quantity > availableQuantity) {
        throw std::runtime_error("Quantity exceeds available stock.");
    }
}

// Function to add a product to the cart
void addToCart(json& cart, const json& database, const std::string& productSku, int quantity) {
    if (!database.contains(productSku)) {
        throw std::invalid_argument("Product SKU not found in the store's database.");
    }

    validateQuantity(quantity, database[productSku]);

    cart[productSku] = cart[productSku].get<int>() + quantity;
}

// Function to remove a product from the cart
void removeFromCart(json& cart, const json& database, const std::string& productSku, int quantity) {
    if (!cart.contains(productSku)) {
        throw std::invalid_argument("Product SKU not found in the cart.");
    }

    validateQuantity(quantity, cart[productSku]);

    if (quantity >= cart[productSku]) {
        cart.erase(productSku);
    } else {
        cart[productSku] = cart[productSku].get<int>() - quantity;
    }
}

int main() {
    // Database of the store
    json database = {
            {"SKU1", 10},
            {"SKU2", 5},
            {"SKU3", 8}
    };

    // Shopping cart
    json cart;

    try {
        // Add products to the cart
        addToCart(cart, database, "SKU1", 2);
        addToCart(cart, database, "SKU2", 3);
        addToCart(cart, database, "SKU3", 4);
        addToCart(cart, database, "SKU4", 1);  // Invalid SKU, throws an exception
    } catch (const std::exception& ex) {
        std::cout << "Exception occurred: " << ex.what() << std::endl;
    }

    try {
        // Remove products from the cart
        removeFromCart(cart, database, "SKU1", 1);
        removeFromCart(cart, database, "SKU2", 4);  // Quantity exceeds available stock, throws an exception
        removeFromCart(cart, database, "SKU3", 2);
        removeFromCart(cart, database, "SKU4", 1);  // Invalid SKU, throws an exception
    } catch (const std::exception& ex) {
        std::cout << "Exception occurred: " << ex.what() << std::endl;
    }

    // Print the items in the cart
    std::cout << "Items in the cart:" << std::endl;
    for (const auto& item : cart.items()) {
        std::cout << item.key() << ": " << item.value() << std::endl;
    }

    return 0;
}
