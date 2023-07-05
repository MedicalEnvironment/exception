#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

// Template class for key-value pairs
template<typename KeyType, typename ValueType>
class RegistryItem {
public:
    KeyType key;
    ValueType value;

    RegistryItem(const KeyType& k, const ValueType& v) : key(k), value(v) {}
};

// Template class for the registry
template<typename KeyType, typename ValueType>
class Registry {
public:
    // Type alias for the registry item
    using Item = RegistryItem<KeyType, ValueType>;

    // Function to add an element with a key
    void add(const KeyType& key, const ValueType& value) {
        items.push_back(Item(key, value));
    }

    // Function to remove elements with a given key
    void remove(const KeyType& key) {
        items.erase(std::remove_if(items.begin(), items.end(),
            [key](const Item& item) { return item.key == key; }), items.end());
    }

    // Function to print all elements with their keys
    void print() const {
        for (const auto& item : items) {
            std::cout << "Key: " << item.key << ", Value: " << item.value << std::endl;
        }
    }

    // Function to find elements by key
    std::vector<ValueType> find(const KeyType& key) const {
        std::vector<ValueType> result;
        for (const auto& item : items) {
            if (item.key == key) {
                result.push_back(item.value);
            }
        }
        return result;
    }

private:
    std::vector<Item> items;
};

// Helper function to get input from the console
template<typename ValueType>
ValueType getInput(const std::string& prompt) {
    ValueType input;
    std::cout << prompt;
    std::cin >> input;
    return input;
}

int main() {
    // Create registry objects for different value types
    Registry<int, int> intRegistry;
    Registry<double, std::string> doubleRegistry;
    Registry<std::string, double> stringRegistry;

    std::string command;

    while (true) {
        std::cout << "Enter a command (add, remove, print, find) or 'exit' to quit: ";
        std::cin >> command;

        if (command == "exit") {
            break;
        }
        else if (command == "add") {
            std::string keyType;
            std::cout << "Enter the key type (int, double, string): ";
            std::cin >> keyType;

            if (keyType == "int") {
                int key = getInput<int>("Enter the key (int): ");
                int value = getInput<int>("Enter the value (int): ");
                intRegistry.add(key, value);
            }
            else if (keyType == "double") {
                double key = getInput<double>("Enter the key (double): ");
                std::string value = getInput<std::string>("Enter the value (string): ");
                doubleRegistry.add(key, value);
            }
            else if (keyType == "string") {
                std::string key = getInput<std::string>("Enter the key (string): ");
                double value = getInput<double>("Enter the value (double): ");
                stringRegistry.add(key, value);
            }
            else {
                std::cout << "Invalid key type." << std::endl;
            }
        }
        else if (command == "remove") {
            std::string keyType;
            std::cout << "Enter the key type (int, double, string): ";
            std::cin >> keyType;

            if (keyType == "int") {
                int key = getInput<int>("Enter the key (int): ");
                intRegistry.remove(key);
            }
            else if (keyType == "double") {
                double key = getInput<double>("Enter the key (double): ");
                doubleRegistry.remove(key);
            }
            else if (keyType == "string") {
                std::string key = getInput<std::string>("Enter the key (string): ");
                stringRegistry.remove(key);
            }
            else {
                std::cout << "Invalid key type." << std::endl;
            }
        }
        else if (command == "print") {
            std::cout << "Int Registry:" << std::endl;
            intRegistry.print();

            std::cout << "Double Registry:" << std::endl;
            doubleRegistry.print();

            std::cout << "String Registry:" << std::endl;
            stringRegistry.print();
        }
        else if (command == "find") {
            std::string keyType;
            std::cout << "Enter the key type (int, double, string): ";
            std::cin >> keyType;

            if (keyType == "int") {
                int key = getInput<int>("Enter the key (int): ");
                std::vector<int> result = intRegistry.find(key);
                std::cout << "Values found:" << std::endl;
                for (const auto& value : result) {
                    std::cout << value << std::endl;
                }
            }
            else if (keyType == "double") {
                double key = getInput<double>("Enter the key (double): ");
                std::vector<std::string> result = doubleRegistry.find(key);
                std::cout << "Values found:" << std::endl;
                for (const auto& value : result) {
                    std::cout << value << std::endl;
                }
            }
            else if (keyType == "string") {
                std::string key = getInput<std::string>("Enter the key (string): ");
                std::vector<double> result = stringRegistry.find(key);
                std::cout << "Values found:" << std::endl;
                for (const auto& value : result) {
                    std::cout << value << std::endl;
                }
            }
            else {
                std::cout << "Invalid key type." << std::endl;
            }
        }
        else {
            std::cout << "Invalid command." << std::endl;
        }
    }

    return 0;
}
