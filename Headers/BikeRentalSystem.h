#include "Bike.h"

using namespace std;
#define MAX_BIKES 100

#ifndef UNTITLED5_BIKERENTALSYSTEM_H
#define UNTITLED5_BIKERENTALSYSTEM_H


class BikeRentalSystem {
private:
    vector<Bike> bikes;

    void readBikesFromFile();

    void saveBikesToFile() const;

    static Bike parseBike(const string &line);

    static string bikeToString(const Bike &bike);

public:
    BikeRentalSystem();

    void addBike(const Bike &newBike);

    void displayBikes() const;

    void updateBike(int id, const Bike &updatedBike);

    void deleteBike(int id);

    void rentBike(int id);

    void returnBike(int id);
};

BikeRentalSystem::BikeRentalSystem() {
    readBikesFromFile();
}

void BikeRentalSystem::readBikesFromFile() {
    ifstream file("DBS/bikes.csv");
    if (!file.is_open()) {
        cerr << "File not found or empty.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        bikes.push_back(parseBike(line));
    }

    file.close();
}

void BikeRentalSystem::saveBikesToFile() const {
    ofstream file("DBS/bikes.csv");
    if (!file.is_open()) {
        cerr << "Error opening file.\n";
        return;
    }

    for (const auto &bike: bikes) {
        file << bikeToString(bike) << '\n';
    }

    file.close();
}

Bike BikeRentalSystem::parseBike(const string &line) {
    stringstream ss(line);
    string item;
    Bike bike;

    getline(ss, item, ',');
    bike.id = stoi(item);

    getline(ss, item, ',');
    bike.brand = item;

    getline(ss, item, ',');
    bike.model = item;

    getline(ss, item, ',');
    bike.year = stoi(item);

    getline(ss, item, ',');
    bike.price_per_hour = stof(item);

    getline(ss, item, ',');
    bike.location = item;

    getline(ss, item, ',');
    bike.available = stoi(item);

    return bike;
}

string BikeRentalSystem::bikeToString(const Bike &bike) {
    return to_string(bike.id) + ',' +
           bike.brand + ',' +
           bike.model + ',' +
           to_string(bike.year) + ',' +
           to_string(bike.price_per_hour) + ',' +
           bike.location + ',' +
           to_string(bike.available);
}

void BikeRentalSystem::addBike(const Bike &newBike) {
    if (bikes.size() >= MAX_BIKES) {
        cerr << "Cannot add more bikes. Limit reached.\n";
        return;
    }

    bikes.push_back(newBike);
    saveBikesToFile();
    cout << "Bike added successfully.\n";
}

void BikeRentalSystem::displayBikes() const {
    cout << "ID\tBrand\tModel\tYear\tPrice per Hour\tLocation\tAvailable\n";
    for (const auto &bike: bikes) {
        cout << bike.id << '\t'
             << bike.brand << '\t'
             << bike.model << '\t'
             << bike.year << '\t'
             << bike.price_per_hour << '\t'
             << bike.location << '\t'
             << (bike.available ? "Yes" : "No") << '\n';
    }
}

void BikeRentalSystem::updateBike(int id, const Bike &updatedBike) {
    for (auto &bike: bikes) {
        if (bike.id == id) {
            bike = updatedBike;
            saveBikesToFile();
            cout << "Bike updated successfully.\n";
            return;
        }
    }
    cerr << "Bike not found with ID " << id << ".\n";
}

void BikeRentalSystem::deleteBike(int id) {
    auto it = remove_if(bikes.begin(), bikes.end(), [id](const Bike &bike) {
        return bike.id == id;
    });

    if (it != bikes.end()) {
        bikes.erase(it, bikes.end());
        saveBikesToFile();
        cout << "Bike deleted successfully.\n";
    } else {
        cerr << "Bike not found with ID " << id << ".\n";
    }
}

void BikeRentalSystem::rentBike(int id) {
    for (auto &bike: bikes) {
        if (bike.id == id) {
            if (bike.available) {
                bike.available = false;
                saveBikesToFile();
                cout << "Bike with ID " << id << " has been rented.\n";
            } else {
                cerr << "Bike with ID " << id << " is already rented.\n";
            }
            return;
        }
    }
    cerr << "Bike not found with ID " << id << ".\n";
}

void BikeRentalSystem::returnBike(int id) {
    for (auto &bike: bikes) {
        if (bike.id == id) {
            if (!bike.available) {
                bike.available = true;
                saveBikesToFile();
                cout << "Bike with ID " << id << " has been returned.\n";
            } else {
                cerr << "Bike with ID " << id << " is not currently rented.\n";
            }
            return;
        }
    }
    cerr << "Bike not found with ID " << id << ".\n";
}

#endif //UNTITLED5_BIKERENTALSYSTEM_H