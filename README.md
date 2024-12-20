# E-Commerce System in C++

This is a simple e-commerce system implemented in C++ that allows both users and admins to interact with products, manage a shopping cart, and process orders. It demonstrates key concepts such as file handling, object-oriented programming, user input validation, and basic algorithms.

## Features

### For Users:
- **View Products**: Browse a list of available products, including their names, categories, and prices.
- **Shopping Cart**: Add and remove products from the shopping cart.
- **Checkout**: Review the items in the cart, enter personal details, and finalize the purchase.
  
### For Admins:
- **Manage Products**: Add new products or remove existing ones from the product list.
- **View Orders**: Admins can view all completed orders, including customer details and ordered products.

## Technologies Used
- **C++**: Core language used for development.
- **Standard Library**: Utilizes containers like `std::vector`, file I/O, and algorithms like `std::find_if`.

## File Structure

- `products.txt`: A text file containing product information (name, category, price).
- `orders.txt`: A text file used to store completed orders (including customer details and purchased products).

## Installation

### Requirements:
- A C++ compiler (e.g., GCC, Clang).
- Basic command-line interface to compile and run C++ programs.

### Instructions:
1. Clone the repository or download the source code to your local machine.
2. Open a terminal/command prompt and navigate to the project directory.
3. Compile the code using the following command:
   ```bash
   g++ -o ecommerce_system main.cpp
   ```
4. Run the compiled program:
    ```bash
    ./ecommerce_system
    ```
## Input Data:
- The system uses products.txt and orders.txt to store product and order information. These files will be created automatically if they do not exist.
- Products are stored in the following format: name|category|price.
## Usage
When the program runs, you will be prompted to choose between being a **User** or **Admin**.

### For Users:
1. **Show Products**: Displays all available products.
2. **Show Shopping Cart**: Displays the items currently in the cart.
3. **Add to Shopping Cart**: Allows you to add products to the cart by entering the product index.
4. **Remove from Shopping Cart**: Allows you to remove products from the cart by entering the product name.
5. **Checkout**: Allows you to proceed with the purchase by entering your details (name, phone number, and credit card number).

### For Admins:
1. **Show Products**: Displays all available products.
2. **Add Products**: Allows the admin to add a new product to the list.
3. **Delete Products**: Allows the admin to remove a product from the list.
4. **Show Orders**: Displays all completed orders along with customer details and the purchased items.

## Example Workflow
1. When you start the application, choose whether you are an **Admin** or a **User**.
2. As a **User**, you can browse products, add them to your cart, and proceed to checkout.
3. As an **Admin**, you can add new products, delete old ones, and view all orders placed by customers.

## Limitations
- **Security**: User data such as credit card information is stored in plain text. In a real-world application, sensitive data should be encrypted or handled securely.
- **Error Handling**: Basic error handling is implemented, but more robust checks could be added for input validation and file operations.
- **Persistence**: The system uses text files for data persistence, which could be replaced by a database for better scalability.

## Future Improvements
- **Database Integration**: Integrate a database such as SQLite for better data storage.
- **User Authentication**: Add functionality for user registration and login.
- **UI/UX**: Implement a graphical user interface (GUI) for a more user-friendly experience.
- **Security**: Secure sensitive information like credit card numbers using encryption.

## Contributing
Feel free to fork this repository and make improvements or enhancements. If you have any suggestions or bug fixes, please submit a pull request.

## License
This project is open-source and available under the MIT License.
