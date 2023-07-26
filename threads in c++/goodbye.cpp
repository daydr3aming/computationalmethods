#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <chrono>
#include <atomic>

const int WIDTH = 80;  // Width of the console
const int HEIGHT = 24; // Height of the console

std::mutex mtx; // Mutex to synchronize console output

// Function to generate a random color code
int getRandomColorCode() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    return dis(gen);
}

std::atomic<bool> stopGeneration(false); // Global flag variable to stop generation

// Thread function to set random colors on the console
void setRandomColors() {
    while (!stopGeneration) {
        int x = std::rand() % WIDTH;
        int y = std::rand() % HEIGHT;

        int red = getRandomColorCode();
        int green = getRandomColorCode();
        int blue = getRandomColorCode();

        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << "\033[" << y + 1 << ";" << x + 1 << "H"; // Set cursor position
            std::cout << "\033[48;2;" << red << ";" << green << ";" << blue << "m"; // Set background color
            std::cout << " "; // Print a space to occupy the cell (no symbol)
            std::cout.flush();
        }

        // Sleep for a short time to control the speed of generation
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Create multiple threads for setting random colors
    const int numThreads = 10;
    std::thread threads[numThreads];

    for (int i = 0; i < numThreads; ++i) {
        threads[i] = std::thread(setRandomColors);
    }

    // Wait for the user to press Enter to stop the generation
    std::cin.ignore();

    stopGeneration = true; // Set the flag to stop the generation

    // Wait for all threads to finish
    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
    }

    // Print the goodbye message below the art piece
    {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "\033[" << HEIGHT + 2 << ";1H"; // Set cursor position below the art piece
        std::cout << "goodbye." << std::endl;
    }

    return 0;
}