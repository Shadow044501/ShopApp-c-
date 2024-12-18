#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Product {
    int id;
    string name;
    float price;
    int stock;
};

struct User {
    string username;
    string password;
    vector<pair<int, int>> cart; // Product id and quantity
};

vector<User> users;
vector<Product> products = {
    {101, "Laptop", 499.99, 10},
    {102, "Smartphone", 299.99, 20},
    {103, "Headphones", 49.99, 50},
    {104, "Tablet", 199.99, 15},
    {105, "Monitor", 149.99, 25},
    {106, "Keyboard", 29.99, 100}
};

bool registerUser(const string& username, const string& password) {
    for (const auto& user : users)
        if (user.username == username) {
            cout << "Username exists.\n";
            return false;
        }
    users.push_back({username, password});
    cout << "Registered!\n";
    return true;
}

User* loginUser(const string& username, const string& password) {
    for (auto& user : users)
        if (user.username == username && user.password == password) {
            cout << "Login successful!\n";
            return &user;
        }
    cout << "Login failed.\n";
    return nullptr;
}

void displayProducts() {
    for (const auto& product : products)
        cout << "ID: " << product.id << " | " << product.name << " | $" << product.price << " | Stock: " << product.stock << "\n";
}

void addToCart(User* user, int productId, int quantity) {
    for (auto& product : products)
        if (product.id == productId) {
            if (product.stock >= quantity) {
                product.stock -= quantity;
                user->cart.push_back({productId, quantity});
                cout << "Added to cart: " << product.name << " x" << quantity << "\n";
            } else {
                cout << "Not enough stock.\n";
            }
            return;
        }
    cout << "Product not found.\n";
}

void checkout(User* user) {
    if (user->cart.empty()) {
        cout << "Cart is empty.\n";
        return;
    }

    float total = 0;
    cout << "\nReceipt:\n";
    for (auto& item : user->cart) {
        for (auto& product : products)
            if (product.id == item.first) {
                cout << product.name << " x" << item.second << "\n";
                total += product.price * item.second;
            }
    }
    user->cart.clear();
    cout << "Total: $" << total << "\n";
}

int main() {
    int choice;
    User* currentUser = nullptr;

    while (true) {
        if (!currentUser) {
            cout << "1. Registration\n2. Authorization\nChoice: ";
            cin >> choice;

            if (choice == 1) {
                string username, password;
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;
                registerUser(username, password);
            } else if (choice == 2) {
                string username, password;
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;
                currentUser = loginUser(username, password);
            }
        } else {
            cout << "\n1. View Products\n2. Add product to cart\n3. Make a purchase\n4. Logout\nChoice: ";
            cin >> choice;

            if (choice == 1) {
                displayProducts();
            } else if (choice == 2) {
                displayProducts();
                int productId, quantity;
                cout << "Product ID: ";
                cin >> productId;
                cout << "Quantity: ";
                cin >> quantity;
                addToCart(currentUser, productId, quantity);
            } else if (choice == 3) {
                checkout(currentUser);
            } else if (choice == 4) {
                currentUser = nullptr;
                cout << "Logged out.\n";
            }
        }
    }

    return 0;
}
