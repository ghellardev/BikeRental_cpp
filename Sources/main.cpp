#include <iostream>
#include "../Headers/BikeRentalSystem.h"

#define MAX_BIKES 100

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <operation>\n";
        cerr << "Operations:\n";
        cerr << "add <id> <brand> <model> <year> <price_per_hour> <location> <available>\n";
        cerr << "display\n";
        cerr << "update <id> <brand> <model> <year> <price_per_hour> <location> <available>\n";
        cerr << "delete <id>\n";
        cerr << "rent <id>\n";
        cerr << "return <id>\n";
        return 1;
    }

    BikeRentalSystem bikeRentalSystem;

    const string operation = argv[1];
    if (operation == "add" && argc == 9) {
        Bike newBike(
                stoi(argv[2]),
                argv[3],
                argv[4],
                stoi(argv[5]),
                stof(argv[6]),
                argv[7],
                static_cast<bool>(stoi(argv[8]))
        );
        bikeRentalSystem.addBike(newBike);
    } else if (operation == "display" && argc == 2) {
        bikeRentalSystem.displayBikes();
    } else if (operation == "update" && argc == 9) {
        Bike updatedBike(
                stoi(argv[2]),
                argv[3],
                argv[4],
                stoi(argv[5]),
                stof(argv[6]),
                argv[7],
                static_cast<bool>(stoi(argv[8]))
        );
        bikeRentalSystem.updateBike(stoi(argv[2]), updatedBike);
    } else if (operation == "delete" && argc == 3) {
        bikeRentalSystem.deleteBike(stoi(argv[2]));
    } else if (operation == "rent" && argc == 3) {
        bikeRentalSystem.rentBike(stoi(argv[2]));
    } else if (operation == "return" && argc == 3) {
        bikeRentalSystem.returnBike(stoi(argv[2]));
    } else {
        cerr << "Invalid operation or arguments.\n";
        return 1;
    }

    return 0;
}
