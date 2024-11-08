#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Product {
    string name;
    double price;
    int stock;
};

// Function to add a new product
void addProduct() {
    Product p;
    cout << "Enter product name: ";
    cin >> p.name;
    cout << "Enter product price: ";
    cin >> p.price;
    cout << "Enter product stock: ";
    cin >> p.stock;

    ofstream file("inventory.txt", ios::app); // Open file in append mode
    if (file.is_open()) {
        file << p.name << " " << p.price << " " << p.stock << endl;
        file.close();
        cout << "Product added successfully!" << endl;
    } else {
        cout << "Unable to open file." << endl;
    }
}

// Function to update stock level of a product
void updateStock() {
    string productName;
    int newStock;
    bool found = false;
    
    cout << "Enter product name to update stock: ";
    cin >> productName;
    cout << "Enter new stock quantity: ";
    cin >> newStock;

    ifstream file("inventory.txt");
    ofstream tempFile("temp.txt"); // Temporary file to hold updated data

    if (file.is_open() && tempFile.is_open()) {
        Product p;
        while (file >> p.name >> p.price >> p.stock) {
            if (p.name == productName) {
                p.stock = newStock;
                found = true;
            }
            tempFile << p.name << " " << p.price << " " << p.stock << endl;
        }
        file.close();
        tempFile.close();
        remove("inventory.txt"); // Remove old file
        rename("temp.txt", "inventory.txt"); // Rename temp file to original

        if (found) {
            cout << "Stock updated successfully!" << endl;
        } else {
            cout << "Product not found." << endl;
        }
    } else {
        cout << "Unable to open file." << endl;
    }
}

// Function to generate sales report (total inventory value)
void generateSalesReport() {
    ifstream file("inventory.txt");
    double totalValue = 0;

    if (file.is_open()) {
        Product p;
        cout << left << setw(15) << "Product" << setw(10) << "Price" << setw(10) << "Stock" << setw(15) << "Total Value" << endl;
        cout << "------------------------------------------------------" << endl;
        while (file >> p.name >> p.price >> p.stock) {
            double value = p.price * p.stock;
            totalValue += value;
            cout << left << setw(15) << p.name << setw(10) << p.price << setw(10) << p.stock << setw(15) << value << endl;
        }
        file.close();
        cout << "------------------------------------------------------" << endl;
        cout << "Total Inventory Value: $" << totalValue << endl;
    } else {
        cout << "Unable to open file." << endl;
    }
}

// Main Menu
int main() {
    int choice;
    do {
        cout << "\nInventory Management System" << endl;
        cout << "1. Add New Product" << endl;
        cout << "2. Update Stock Level" << endl;
        cout << "3. Generate Sales Report" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                updateStock();
                break;
            case 3:
                generateSalesReport();
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
