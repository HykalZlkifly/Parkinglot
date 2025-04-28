#include <iostream>
#include <vector>
#include <string>
using namespace std;

class ParkingLot {
private:
    int totalSpaces;
    vector<bool> spaces; // True means occupied, False means available

public:
    ParkingLot(int totalSpaces) : totalSpaces(totalSpaces), spaces(totalSpaces, false) {}

    void displayAvailability() {
        cout << "Parking Space Availability:\n";
        for (int i = 0; i < totalSpaces; ++i) {
            cout << "Space " << i + 1 << ": " 
                      << (spaces[i] ? "Occupied" : "Available") << "\n";
        }
    }

    void parkCar(int spaceNumber) {
        if (spaceNumber < 1 || spaceNumber > totalSpaces) {
            cout << "Invalid space number.\n";
            return;
        }

        if (spaces[spaceNumber - 1]) {
            cout << "Space " << spaceNumber << " is already occupied.\n";
        } else {
            spaces[spaceNumber - 1] = true;
            cout << "Car parked in space " << spaceNumber << ".\n";
        }
    }

    void removeCar(int spaceNumber) {
        if (spaceNumber < 1 || spaceNumber > totalSpaces) {
            cout << "Invalid space number.\n";
            return;
        }

        if (!spaces[spaceNumber - 1]) {
            std::cout << "Space " << spaceNumber << " is already empty.\n";
        } else {
            spaces[spaceNumber - 1] = false;
            cout << "Car removed from space " << spaceNumber << ".\n";
        }
    }
};

int main() {
    int totalSpaces;
    cout << "Enter the total number of parking spaces: ";
    cin >> totalSpaces;

    ParkingLot parkingLot(totalSpaces);

    int choice, spaceNumber;
    do {
        cout << "\nParking Management System\n";
        cout << "1. Display Parking Availability\n";
        cout << "2. Park a Car\n";
        cout << "3. Remove a Car\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            parkingLot.displayAvailability();
            break;
        case 2:
            cout << "Enter the parking space number to park a car: ";
            cin >> spaceNumber;
            parkingLot.parkCar(spaceNumber);
            break;
        case 3:
            cout << "Enter the parking space number to remove a car: ";
            cin >> spaceNumber;
            parkingLot.removeCar(spaceNumber);
            break;
        case 4:
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
