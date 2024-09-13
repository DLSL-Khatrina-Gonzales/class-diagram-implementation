#include <iostream>
#include <iomanip>  // For proper spacing in tables
#include <cctype>   // For toupper to handle case insensitivity
#include <cstring>

using namespace std;

class Product {
private:
    string productId;
    string name;
    double price;
    int stock;

public:
    // Constructor
    Product() {} // Default constructor for array initialization
    Product(string id, string n, double p, int s) : productId(id), name(n), price(p), stock(s) {}

    void displayProduct() const {
        cout << left << setw(20) << productId << setw(35) << name << setw(15) << fixed << setprecision(2) << price 
             << setw(10) << stock << endl;
    }

    string getProductId() const {
        return productId;
    }

    double getPrice() const {
        return price;
    }

    string getName() const {
        return name;
    }

    int getStock() const {
        return stock;
    }

    bool isInStock() const {
        return stock > 0;
    }

    void reduceStock(int quantity) {
        stock -= quantity;
    }

    void addStock(int quantity) {
        stock += quantity;
    }
};

class Customer {
private:
    string name;
    string username;
    string phoneNumber;
    string address;

public:
    void inputDetails() {
        cout << "Name: ";
        getline(cin, name);
        cout << "Username: ";
        getline(cin, username);
        cout << "Phone Number: ";
        getline(cin, phoneNumber);
        cout << "Address: ";
        getline(cin, address);
    }

    void registerUser() {
        cout << "Register User\n\n";
        inputDetails();
        cout << "\nYou have successfully registered!\n\n";
    }

    string getName() const {
        return name;
    }
};

class ShoppingCart {
private:
    struct CartItem {
        Product product;
        int quantity;
    } cartItems[100];  // Array to store cart items

    int totalItems = 0;
    double totalPrice = 0.0;

public:
    // Add item to cart
    void addItem(const Product& product, int quantity) {
        // Check if the product is already in the cart
        for (int i = 0; i < totalItems; i++) {
            if (cartItems[i].product.getProductId() == product.getProductId()) {
                cartItems[i].quantity += quantity;  // Update quantity
                totalPrice += product.getPrice() * quantity;  // Update total price
                return;
            }
        }

        // If product is not already in the cart, add new product
        if (totalItems < 100) {  // Check array bounds
            cartItems[totalItems].product = product;  // Assign product correctly
            cartItems[totalItems].quantity = quantity; // Set the entered quantity
            totalPrice += product.getPrice() * quantity; // Update total price
            totalItems++;
        } else {
            cout << "Shopping cart is full!\n";
        }
    }

    // View cart items
    void viewCart() const {
        if (totalItems == 0) {
            cout << "Your cart is empty.\n";
            return;
        }
        cout << left << setw(25) << "Product" << setw(30) << "Name" << setw(18) << "Price" << setw(10) << "Quantity" << endl;
        for (int i = 0; i < totalItems; i++) {
            cout << left << setw(25) << cartItems[i].product.getProductId() << setw(30) << cartItems[i].product.getName() 
                 << setw(18) << fixed << setprecision(2) << cartItems[i].product.getPrice() 
                 << setw(10) << cartItems[i].quantity << endl;
        }
    }

    double getTotalPrice() const {
        return totalPrice;
    }

    void clearCart() {
        totalItems = 0;
        totalPrice = 0;
    }

    bool isEmpty() const {
        return totalItems == 0;
    }
};

class Order {
private:
    int orderId = 0;
    double totalAmount = 0.0;
    ShoppingCart cart;  // Shopping cart for the order

public:
    Order() = default;

    void placeOrder(const ShoppingCart& shoppingCart, int id) {
        cart = shoppingCart;  // Copy the entire shopping cart
        totalAmount = shoppingCart.getTotalPrice();
        orderId = id;
        cout << "\nOrder successfully placed!\n";
    }

    void viewOrderDetails() const {
        cout << "\nOrder ID: " << orderId << endl;
        cart.viewCart();  // Show the cart items in the order
        cout << "\nTotal Amount: " << totalAmount << " Php\n";
    }
};

// Helper function to convert a string to uppercase
string toUpperCase(string str) {
    for (size_t i = 0; i < str.length(); i++) {
        str[i] = toupper(str[i]);
    }
    return str;
}

// Helper function to display menu
void displayMenu() {
    cout << "\nMenu\n";
    cout << "1 - View Products\n";
    cout << "2 - View Shopping Cart\n";
    cout << "3 - View Orders\n";
    cout << "4 - Exit\n";
}

int main() {
    Customer customer;
    customer.registerUser();

    Product products[20] = {
        Product("WP1", "The Rain in Espanya", 450.00, 10),
        Product("WP2", "Golden Scenery of Tomorrow", 450.00, 10),
        Product("WP3", "The 10 Year Gap", 300.00, 20),
        Product("WP4", "Hell University", 210.00, 15),
        Product("WP5", "Chasing in the Wild", 450.00, 20),
        Product("AU1", "Avenues of the Diamond", 450.00, 20),
        Product("AU2", "Riding the Skies", 200.00, 10),
        Product("AU3", "Typical Heartbreaker", 150.00, 5),
        Product("AU4", "Class Picture", 100.00, 20),
        Product("AU5", "Volleyball Sweetheart", 120.00, 15),
        Product("BK1", "Embers of Love", 200.00, 10),
        Product("BK2", "Safe Skies Archer", 450.00, 20),
        Product("BK3", "Hold you Accountable", 350.00, 30),
        Product("BK4", "Tears of Love", 220.00, 5),
        Product("BK5", "Chained by Fate", 220.00, 5),
        Product("CS1", "Lost in Translation", 290.00, 10),
        Product("CS2", "His Possessive Ways", 190.00, 15),
        Product("CS3", "Against the Barriers", 200.00, 10),
        Product("CS4", "Fundamentals of Marriage", 280.00, 20),
        Product("CS5", "Master of Deception", 290.00, 5)
    };

    ShoppingCart cart;
    Order orders[100];  // Array to hold up to 100 orders
    int totalOrders = 0;  // Number of orders placed
    int choice, quantity;
    string productId;
    char addMore, checkOut;

    while (true) {
        displayMenu();
        cout << "\nChoose an option: ";
        cin >> choice;
        cin.ignore();  // Consume the newline character after entering an integer

        switch (choice) {
            case 1:  // View Products
                cout << left << setw(20) << "Product ID" << setw(35) << "Name" << setw(15) << "Price" << setw(10) << "Stock" << endl;
                for (int i = 0; i < 20; i++) {  // Fix the loop to display all 20 products
                    products[i].displayProduct();
                }

                do {
                    cout << "\nEnter the ID of the product you want to add to the shopping cart: ";
                    getline(cin, productId);
                    productId = toUpperCase(productId);  // Convert product ID to uppercase for case-insensitive comparison
                    bool productFound = false;

                    for (int i = 0; i < 20; i++) {  // Check all products, not just the first 3
                        if (products[i].getProductId() == productId) {
                            if (products[i].isInStock()) {
                                cout << "Enter the quantity: ";
                                cin >> quantity;
                                cin.ignore();  // Consume the newline character

                                if (quantity > 0 && quantity <= products[i].getStock()) {
                                    cart.addItem(products[i], quantity);  // Add product with quantity to cart
                                    products[i].reduceStock(quantity);  // Reduce stock
                                    cout << "Product added successfully!\n";
                                } else {
                                    cout << "Invalid quantity! Only " << products[i].getStock() << " in stock.\n";
                                }
                            } else {
                                cout << "Sorry, this product is out of stock.\n";
                            }
                            productFound = true;
                            break;
                        }
                    }

                    if (!productFound) {
                        cout << "Product not found!\n";
                    }

                    cout << "Do you want to add more products? [Y/N]: ";
                    cin >> addMore;
                    cin.ignore();  // Consume the newline character
                } while (addMore == 'Y' || addMore == 'y');

                break;

            case 2:  // View Shopping Cart
                cart.viewCart();
                if (!cart.isEmpty()) {
                    cout << "\nDo you want to check out all the products? [Y/N]: ";
                    cin >> checkOut;
                    cin.ignore();  // Consume the newline character
                    if (checkOut == 'Y' || checkOut == 'y') {
                        cout << "\nCheckout Details:\n";
                        cart.viewCart();
                        cout << "\nTotal Amount: " << cart.getTotalPrice() << " Php\n";

                        if (totalOrders < 100) {  // Check array bounds
                            orders[totalOrders].placeOrder(cart, totalOrders + 1);  // Add the order to the array
                            totalOrders++;
                        } else {
                            cout << "Cannot place more than 100 orders.\n";
                        }
                        cart.clearCart();  // Clear the cart after checkout
                        cout << "You have successfully checked out the products!\n";
                    }
                }
                break;

            case 3:  // View Orders
                if (totalOrders > 0) {
                    for (int i = 0; i < totalOrders; i++) {
                        orders[i].viewOrderDetails();  // Display each order
                    }
                } else {
                    cout << "No orders placed yet.\n";
                }
                cout << "Press Enter to go back to the Menu...\n";
                cin.get();  // Wait for user input
                break;

            case 4:  // Exit
                cout << "Logging Out....\n";
                return 0;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}