#include <iostream>
#include <limits>

// Template function to calculate the arithmetic mean
template<typename T>
T calculateMean(const T* array, int size) {
    T sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += array[i];
    }
    return sum / size;
}

// Template function to input elements into the array
template<typename T>
void input(T* array, int size) {
    std::cout << "Fill the array (" << size << "): ";
    for (int i = 0; i < size; ++i) {
        if (!(std::cin >> array[i])) {
            std::cout << "Invalid input. Please enter a valid number." << std::endl;
            // Clear the input buffer
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            i--;
        }
    }
    // Clear the remaining input in case the user entered more than 8 digits
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    // Create an array of integers
    int intArray[8];
    input(intArray, 8);

    // Calculate the mean of integers
    int intMean = calculateMean(intArray, 8);
    std::cout << "Mean of integers: " << intMean << std::endl;

    // Create an array of doubles
    double doubleArray[8];
    input(doubleArray, 8);

    // Calculate the mean of doubles
    double doubleMean = calculateMean(doubleArray, 8);
    std::cout << "Mean of doubles: " << doubleMean << std::endl;

    // Create an array of floats
    float floatArray[8];
    input(floatArray, 8);

    // Calculate the mean of floats
    float floatMean = calculateMean(floatArray, 8);
    std::cout << "Mean of floats: " << floatMean << std::endl;

    return 0;
}
