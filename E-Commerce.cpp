#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <sstream>
#include <algorithm>

class Product {
public:
    std::string name;
    std::string category;
    double price;

    Product(const std::string& n, const std::string& c, double p) : name(n), category(c), price(p) {}
};

void setupProducts() {
    std::ifstream products("products.txt");
    std::ifstream orders("orders.txt");

    if (!products.is_open()) {
        std::ofstream fileOut("products.txt");
        fileOut.close();
    }

    if (!orders.is_open()) {
        std::ofstream details("orders.txt");
        details.close();
    }
}

std::vector<Product> getProducts() {
    std::vector<Product> products;
    std::ifstream fileIn("products.txt");

    if (!fileIn.is_open()) {
        std::cerr << "File Could Not Be Opened.\n";
        return products;
    }

    std::string name, category, price;
    while (std::getline(fileIn, name, '|') && std::getline(fileIn, category, '|') && std::getline(fileIn, price)) {
        products.emplace_back(name, category, std::stod(price));
    }

    return products;
}

void showProducts() {
    const auto products = getProducts();
    int i = 1;
    for (const auto& product : products) {
        std::cout << "Product #" << i << '\n';
        std::cout << "Name: " << product.name << '\n';
        std::cout << "Category: " << product.category << '\n';
        std::cout << "Price: " << product.price << '\n';
        std::cout << "************************************\n";
        i++;
    }
}

class User {
public:
    std::vector<int> cart;

    void loop() {
        int choice;
        bool running = true;

        while (running) {
            std::cout << "What Would You Like To Do?\n";
            std::cout << "1. Show Products\n";
            std::cout << "2. Show Shopping Cart\n";
            std::cout << "3. Add To Shopping Cart\n";
            std::cout << "4. Remove From Shopping Cart\n";
            std::cout << "5. Check Out\n";
            std::cout << "6. Quit\n";
            std::cin >> choice;

            if (std::cin.fail() || std::cin.peek() != '\n') {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid Input.\n";
                continue;
            }

            switch (choice) {
            case 1:
                showProducts();
                break;
            case 2:
                showCart();
                break;
            case 3:
                addCart();
                break;
            case 4:
                deleteCart();
                break;
            case 5:
                checkOut();
                break;
            case 6:
                running = false;
                break;
            default:
                std::cout << "Please Enter A Valid Number (1, 2, 3, 4, 5, 6).\n";
                break;
            }
        }
    }

    double showCart() {
        const auto products = getProducts();
        double price = 0;

        for (int id : cart) {
            const auto& product = products[id - 1];
            std::cout << "Product #" << id << '\n';
            std::cout << "Name: " << product.name << '\n';
            std::cout << "Category: " << product.category << '\n';
            std::cout << "Price: " << product.price << '\n';
            std::cout << "************************************\n";
            price += product.price;
        }

        std::cout << "Your Total Cost Is: " << price << '\n';
        std::cout << "************************************\n";

        return price;
    }

    void addCart() {
        const auto products = getProducts();
        int product;

        while (true) {
            std::cout << "Enter The Index Of The Product Or 0 To Quit:\n";
            std::cin >> product;

            if (std::cin.fail() || std::cin.peek() != '\n' || product < 0 || product > products.size()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid Input.\n";
                continue;
            }

            if (product == 0) {
                return;
            }

            cart.push_back(product);
        }
    }

    void deleteCart() {
        const auto products = getProducts();

        std::string name;
        std::cout << "Enter The Product's Name: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, name);

        auto it = std::find_if(products.begin(), products.end(), [&](const Product& product) {
            return product.name == name;
        });

        if (it != products.end()) {
            int deleteIndex = std::distance(products.begin(), it) + 1;
            auto cartIt = std::find(cart.begin(), cart.end(), deleteIndex);
            if (cartIt != cart.end()) {
                cart.erase(cartIt);
                std::cout << "Product Removed Successfully.\n";
            } else {
                std::cout << "Product Wasn't Found In Cart.\n";
            }
        } else {
            std::cout << "Product Wasn't Found.\n";
        }
    }

    void checkOut() {
        double cost = showCart();

        std::string name, creditNumber, phoneNumber;

        std::cout << "Enter Your Full Name:\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, name);

        std::cout << "Enter Your Phone Number:\n";
        std::cin >> phoneNumber;

        std::cout << "Enter Your Credit Card Number:\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> creditNumber;

        std::ofstream details("orders.txt", std::ios::app);

        if (!details.is_open()) {
            std::cerr << "File Could Not Be Opened.\n";
            return;
        }

        details << name << '|' << phoneNumber << '|' << creditNumber << '|';

        for (size_t i = 0; i < cart.size(); i++) {
            details << cart[i];
            if (i != cart.size() - 1) {
                details << ' ';
            }
        }

        details << '|' << cost << '\n';
        std::cout << "Check-Out Was Successful!\n";
    }
};

class Admin {
public:
    void loop() {
        int choice;
        bool running = true;

        while (running) {
            std::cout << "What Would You Like To Do?\n";
            std::cout << "1. Show Products\n";
            std::cout << "2. Add Products\n";
            std::cout << "3. Delete Products\n";
            std::cout << "4. Show Orders\n";
            std::cout << "5. Quit\n";
            std::cin >> choice;

            if (std::cin.fail() || std::cin.peek() != '\n') {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid Input.\n";
                continue;
            }

            switch (choice) {
            case 1:
                showProducts();
                break;
            case 2:
                addProducts();
                break;
            case 3:
                deleteProducts();
                break;
            case 4:
                showOrders();
                break;
            case 5:
                running = false;
                break;
            default:
                std::cout << "Please Enter A Valid Number (1, 2, 3, 4, 5).\n";
                break;
            }
        }
    }

    void addProducts() {
        std::ofstream fileOut("products.txt", std::ios::app);

        if (!fileOut.is_open()) {
            std::cerr << "File Could Not Be Opened.\n";
            return;
        }

        std::string name, category;
        double price;

        std::cout << "What Is The Name Of The Product?\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, name);

        std::cout << "What Is The Category Of The Product?\n";
        std::getline(std::cin, category);

        std::cout << "What Is The Price Of The Product?\n";
        std::cin >> price;

        fileOut << name << '|' << category << '|' << price << '\n';
    }

    void deleteProducts() {
        auto products = getProducts();
        std::ofstream fileOut("products.txt");

        if (!fileOut.is_open()) {
            std::cerr << "File Could Not Be Opened.\n";
            return;
        }

        std::string name;
        std::cout << "Enter The Product's Name:\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, name);

        bool found = false;
        for (const auto& product : products) {
            if (product.name == name) {
                found = true;
            } else {
                fileOut << product.name << '|' << product.category << '|' << product.price << '\n';
            }
        }

        if (found) {
            std::cout << "Product Deleted Successfully.\n";
        } else {
            std::cout << "Product Wasn't Found.\n";
        }
    }

    void showOrders() {
        const auto products = getProducts();
        std::ifstream fileIn("orders.txt");

        if (!fileIn.is_open()) {
            std::cerr << "File Could Not Be Opened.\n";
            return;
        }

        std::string name, phoneNumber, creditNumber, cost, orders, order;

        while (std::getline(fileIn, name, '|') &&
              std::getline(fileIn, phoneNumber, '|') &&
              std::getline(fileIn, creditNumber, '|')) {

            std::cout << "Name: " << name << '\n';
            std::cout << "Phone Number: " << phoneNumber << '\n';
            std::cout << "Credit Card Number: " << creditNumber << '\n';
            std::cout << "Order:\n";

            std::getline(fileIn, orders, '|');
            std::stringstream ss(orders);
            while (ss >> order) {
                int id = std::stoi(order);
                const auto& product = products[id - 1];
                std::cout << "Product #" << id << '\n';
                std::cout << "Name: " << product.name << '\n';
                std::cout << "Category: " << product.category << '\n';
                std::cout << "************************************\n";
            }

            std::getline(fileIn, cost);
            std::cout << "Cost: " << cost << '\n';
            std::cout << '\n';
        }
    }
};

int main() {
    setupProducts();

    char user;

    while (true) {
        std::cout << "Are You An Admin Or A User? (A/U)\n";
        std::cin >> user;
        user = toupper(user);

        if (user == 'A') {
            Admin admin;
            admin.loop();
        } else if (user == 'U') {
            User userInstance;
            userInstance.loop();
        } else {
            std::cout << "Invalid Input. Please Enter 'A' for Admin or 'U' for User.\n";
        }

        char exitChoice;
        std::cout << "Do You Want To Exit The Application? (Y/N)\n";
        std::cin >> exitChoice;
        if (toupper(exitChoice) == 'Y') {
            break;
        }
    }

    return 0;
}