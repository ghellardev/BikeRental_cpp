#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef UNTITLED5_BIKE_H
#define UNTITLED5_BIKE_H


class Bike {
public:
    int id;
    string brand;
    string model;
    int year;
    float price_per_hour;
    bool available;
    string location;

    Bike() = default;

    Bike(int id, const string &brand, const string &model, int year, float price_per_hour, const string &location,
         bool available)
            : id(id), brand(brand), model(model), year(year), price_per_hour(price_per_hour), location(location),
              available(available) {}
};


#endif //UNTITLED5_BIKE_H
