#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include<windows.h>
using namespace std;

struct Product {
    string name;
    string storeName;
    double price;
    int quantity;
    string unitOfMeasurement;
};

string safeInputString(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (!input.empty()) {
            return input;
        }
        cout << "Error. Enter correct information.\n";
    }
}

double safeInputDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error. Enter a valid number.\n";
    }
}

void addProductToFile(const string& filename) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cout << "Error opening file.\n";
        return;
    }

    string name = safeInputString("Enter product name: ");
    string storeName = safeInputString("Enter store name: ");
    double price = safeInputDouble("Enter price: ");
    int quantity = static_cast<int>(safeInputDouble("Enter quantity: "));
    string unit = safeInputString("Enter unit of measurement: ");

    file << name << ";"
        << storeName << ";"
        << price << ";"
        << quantity << ";"
        << unit << endl;

    file.close();
    cout << "Product added successfully.\n";
}

void displayAllProducts(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file.\n";
        return;
    }

    string line;
    bool productsExist = false;
    while (getline(file, line)) {
        productsExist = true;
        istringstream iss(line);
        string name, storeName, priceStr, quantityStr, unit;

        getline(iss, name, ';');
        getline(iss, storeName, ';');
        getline(iss, priceStr, ';');
        getline(iss, quantityStr, ';');
        getline(iss, unit);

        cout << "Name: " << name
            << ", Store: " << storeName
            << ", Price: " << priceStr
            << ", Quantity: " << quantityStr
            << " " << unit << endl;
    }

    if (!productsExist) {
        cout << "No products found.\n";
    }
    file.close();
}

void findProductByName(const string& filename) {
    string searchName = safeInputString("Enter product name: ");
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file.\n";
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        istringstream iss(line);
        string name, storeName, priceStr, quantityStr, unit;

        getline(iss, name, ';');
        if (name == searchName) {
            getline(iss, storeName, ';');
            getline(iss, priceStr, ';');
            getline(iss, quantityStr, ';');
            getline(iss, unit);

            cout << "Name: " << name
                << ", Store: " << storeName
                << ", Price: " << priceStr
                << ", Quantity: " << quantityStr
                << " " << unit << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Product not found.\n";
    }
    file.close();
}

void findProductByStore(const string& filename) {
    string searchStore = safeInputString("Enter store name: ");
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file.\n";
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        istringstream iss(line);
        string name, storeName, priceStr, quantityStr, unit;

        getline(iss, name, ';');
        getline(iss, storeName, ';');
        if (storeName == searchStore) {
            getline(iss, priceStr, ';');
            getline(iss, quantityStr, ';');
            getline(iss, unit);

            cout << "Name: " << name
                << ", Price: " << priceStr
                << ", Quantity: " << quantityStr
                << " " << unit << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No products found in this store.\n";
    }
    file.close();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string filename = safeInputString("Enter file name: ");

    int choice;
    do {
        cout << "\n--- Menu ---\n"
            << "1. Add product\n"
            << "2. Display all products\n"
            << "3. Find product by name\n"
            << "4. Find product by store\n"
            << "5. Exit\n"
            << "Choose option: ";

        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            addProductToFile(filename);
            break;
        case 2:
            displayAllProducts(filename);
            break;
        case 3:
            findProductByName(filename);
            break;
        case 4:
            findProductByStore(filename);
            break;
        case 5:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid option. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}