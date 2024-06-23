#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <chrono>
#include <mutex>
#include <iomanip>
#include <cmath>

const int NUM_DEVELOPERS = 5;
const double V = 1.0;
const int N = 2;

static std::mutex print_mutex; // Зроблено print_mutex static

struct Position {
    double x;
    double y;
};

void move_developer(int id, Position& pos, std::default_random_engine& generator) {
    std::uniform_real_distribution<double> direction_dist(0.0, 2.0 * std::acos(-1.0));

    while (true) {
        double direction = direction_dist(generator);
        double dx = V * std::cos(direction);
        double dy = V * std::sin(direction);

        std::this_thread::sleep_for(std::chrono::seconds(N));

        pos.x += dx;
        pos.y += dy;

        std::lock_guard<std::mutex> lock(print_mutex);

        std::cout << "\033[" << id + 1 << ";1H";
        std::cout << "Development " << std::setw(2) << id << " Moved to (" << std::fixed << std::setprecision(6)
            << pos.x << ", " << pos.y << ")" << std::endl;
    }
}

void run_developers_simulation() {
    std::vector<std::thread> threads;
    std::vector<Position> positions(NUM_DEVELOPERS, { 0.0, 0.0 });
    std::random_device rd;
    std::default_random_engine generator(rd());

    for (int i = 0; i < NUM_DEVELOPERS; ++i) {
        threads.emplace_back(move_developer, i, std::ref(positions[i]), std::ref(generator));
    }

    for (auto& thread : threads) {
        thread.join();
    }
}
