#include <iostream>
#include <string>
using namespace std;

class Product {
private:
    string ProductId;
    string Name;
    float Price;

public:
    Product(string id = "", string name = "", float price = 0.0)
        : ProductId(id), Name(name), Price(price) {}

    string getId() const {
        return ProductId;
    }

    string getName() const {
        return Name;
    }

    float getPrice() const {
        return Price;
    }

    void ViewProduct() const {
        cout << ProductId << "\t" << Name << "\t" << Price << endl;
    }
};

class ShoppingCart {
private:
    struct CartItem {
        Product product;
        int quantity;
    };

    CartItem cart[5];
    int itemCount = 0;

public:
    void addProduct(const Product& product) {
        for (int i = 0; i < itemCount; ++i) {
            if (cart[i].product.getId() == product.getId()) {
                cart[i].quantity++;
                cout << "Product quantity updated!" << endl;
                return;
            }
        }

        if (itemCount < 5) {
            cart[itemCount].product = product;
            cart[itemCount].quantity = 1;
            itemCount++;
            cout << "Product added successfully!" << endl;
        } else {
            cout << "Shopping cart is full!" << endl;
        }
    }

    void viewCart() const {
        if (itemCount == 0) {
            cout << "Your shopping cart is empty." << endl;
            return;
        }

        cout << "Product ID\tName\tPrice\tQuantity" << endl;
        for (int i = 0; i < itemCount; ++i) {
            cout << cart[i].product.getId() << "\t" 
                 << cart[i].product.getName() << "\t" 
                 << cart[i].product.getPrice() << "\t" 
                 << cart[i].quantity << endl;
        }
    }

    float checkout() {
        if (itemCount == 0) {
            cout << "Your shopping cart is empty. Nothing to checkout." << endl;
            return 0;
        }

        float totalAmount = 0;
        cout << "Products for checkout:" << endl;
        cout << "Product ID\tName\tPrice\tQuantity" << endl;
        for (int i = 0; i < itemCount; ++i) {
            float itemTotal = cart[i].product.getPrice() * cart[i].quantity;
            totalAmount += itemTotal;
            cout << cart[i].product.getId() << "\t" 
                 << cart[i].product.getName() << "\t" 
                 << cart[i].product.getPrice() << "\t" 
                 << cart[i].quantity << endl;
        }
        cout << "Total amount: " << totalAmount << endl;
        cout << "You have successfully checked out the products!" << endl;

        itemCount = 0;

        return totalAmount;
    }
};

class OrderSystem {
private:
    struct Order {
        int orderId;
        float totalAmount;
    };

    Order orders[10];
    int orderCount = 0;

public:
    void addOrder(float amount) {
        if (orderCount < 10) {
            orders[orderCount].orderId = orderCount + 1;
            orders[orderCount].totalAmount = amount;
            orderCount++;
        } else {
            cout << "Order history is full!" << endl;
        }
    }

    void viewOrders() const {
        if (orderCount == 0) {
            cout << "No orders available." << endl;
            return;
        }

        for (int i = 0; i < orderCount; ++i) {
            cout << "Order ID: " << orders[i].orderId << endl;
            cout << "Total amount: " << orders[i].totalAmount << endl;
        }
    }
};

int main() {
    Product products[4] = {
        Product("ABC", "Watercolor", 200.00),
        Product("DEF", "Paintbrush", 20.00),
        Product("GHI", "Sketchbook", 35.00),
        Product("JKL", "Kneaded Eraser", 41.00)
    };

    ShoppingCart cart;
    OrderSystem orderSystem;
    int choice;

    while (true) {
        cout << "Enter View products-1, View Shopping Cart-2, Checkout-3, View Orders-4, Exit-5: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Product ID\tName\tPrice" << endl;
                for (int i = 0; i < 4; ++i) {
                    products[i].ViewProduct();
                }
                break;

            case 2:
                while (true) {
                    cout << "Enter the ID of the product you want to add to the shopping cart: ";
                    string id;
                    cin >> id;

                    bool found = false;
                    for (int i = 0; i < 4; ++i) {
                        if (products[i].getId() == id) {
                            cart.addProduct(products[i]);
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        cout << "Product not found. Please enter a valid ID." << endl;
                    }

                    cout << "Do you want to add another product? (yes/no): ";
                    string response;
                    cin >> response;
                    if (response == "no") {
                        break;
                    }
                }
                break;

            case 3:
                cart.viewCart();
                cout << "Do you want to check out all the products? (Y/N): ";
                char checkoutResponse;
                cin >> checkoutResponse;
                if (checkoutResponse == 'Y' || checkoutResponse == 'y') {
                    float totalAmount = cart.checkout();
                    if (totalAmount > 0) {
                        orderSystem.addOrder(totalAmount);
                    }
                }
                break;

            case 4:
                orderSystem.viewOrders();
                break;

            case 5:
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
