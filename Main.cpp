#include <iostream>

void run_developers_simulation();
void run_managers_simulation();

int main() {
    std::cout << "Choose simulation:" << std::endl;
    std::cout << "1. Developers" << std::endl;
    std::cout << "2. Managers" << std::endl;

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
        run_developers_simulation();
        break;
    case 2:
        run_managers_simulation();
        break;
    default:
        std::cout << "Invalid choice. Exiting." << std::endl;
        return 1;
    }

    return 0;
}
