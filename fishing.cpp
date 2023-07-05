#include <iostream>
#include <ctime>
#include <cstdlib>
#include <exception>

// Define the Fish and Boot classes
class Fish {};
class Boot {};

// Define the Sector class
class Sector {
public:
    Fish* fish;
    Boot* boot;

    Sector() : fish(nullptr), boot(nullptr) {}
};

// Custom exception for successful fishing
class SuccessfulFishingException : public std::exception {
public:
    int attempts;

    SuccessfulFishingException(int numAttempts) : attempts(numAttempts) {}

    const char* what() const noexcept override {
        return "Congratulations! You caught the fish.";
    }
};

// Custom exception for unsuccessful fishing
class UnsuccessfulFishingException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Sorry, you caught a boot.";
    }
};

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Create the playing field with nine sectors
    Sector field[9];

    // Randomly place the fish and boots in the sectors
    field[std::rand() % 9].fish = new Fish();
    for (int i = 0; i < 3; ++i) {
        int randomSector;
        do {
            randomSector = std::rand() % 9;
        } while (field[randomSector].boot != nullptr || field[randomSector].fish != nullptr);
        field[randomSector].boot = new Boot();
    }

    int attempts = 0;
    bool caughtFish = false;

    // Main game loop
    while (!caughtFish) {
        int sector;
        std::cout << "Enter the sector number to cast your fishing rod (0-8): ";
        std::cin >> sector;

        try {
            if (field[sector].fish != nullptr) {
                throw SuccessfulFishingException(attempts);
            } else if (field[sector].boot != nullptr) {
                throw UnsuccessfulFishingException();
            } else {
                std::cout << "You didn't catch anything. Try again." << std::endl;
                attempts++;
            }
        } catch (const SuccessfulFishingException& ex) {
            std::cout << ex.what() << " It took you " << ex.attempts << " attempts." << std::endl;
            caughtFish = true;
        } catch (const UnsuccessfulFishingException& ex) {
            std::cout << ex.what() << " Game over." << std::endl;
            break;
        }
    }

    // Clean up allocated memory
    for (auto& sector : field) {
        delete sector.fish;
        delete sector.boot;
    }

    return 0;
}
