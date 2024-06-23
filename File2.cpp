#include <iostream>
#include <thread>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>
#include <mutex>
#include <iomanip>

const int NUM_MANAGERS = 4;
const double R = 10.0;
const double V = 2.0;
const int N = 3;

static std::mutex print_mutex; // Зроблено print_mutex static

struct Position {
    double x;
    double y;
};

void move_manager(int id, Position& pos, std::default_random_engine& generator) {
    std::uniform_real_distribution<double> angle_dist(0.0, 2.0 * std::acos(-1.0));

    while (true) {
        double angle = angle_dist(generator);

        double new_x = R * std::cos(angle);
        double new_y = R * std::sin(angle);

        double dx = new_x - pos.x;
        double dy = new_y - pos.y;

        double distance = std::sqrt(dx * dx + dy * dy);
        int move_time = distance / V;

        std::this_thread::sleep_for(std::chrono::seconds(move_time));

        pos.x = new_x;
        pos.y = new_y;

        std::lock_guard<std::mutex> lock(print_mutex);

        std::cout << "\033[" << id + 1 << ";1H";
        std::cout << "Manager " << std::setw(2) << id << " Moved to (" << std::fixed << std::setprecision(2)
            << pos.x << ", " << pos.y << ")" << std::endl;
    }
}

void run_managers_simulation() {
    std::vector<std::thread> threads;
    std::vector<Position> positions(NUM_MANAGERS, { 0.0, 0.0 });
    std::random_device rd;
    std::default_random_engine generator(rd());

    for (int i = 0; i < NUM_MANAGERS; ++i) {
        threads.emplace_back(move_manager, i, std::ref(positions[i]), std::ref(generator));
    }

    for (auto& thread : threads) {
        thread.join();
    }
}
