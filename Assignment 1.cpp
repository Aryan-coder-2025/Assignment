#include <iostream>
#include <string>
using namespace std;
// Enums
enum Category { ELECTRONICS, CLOTHING, BOOKS };
enum OrderStatus { PENDING, CONFIRMED, CANCELLED, DELIVERED };
enum PaymentStatus { PAYMENT_PENDING, PAYMENT_SUCCESS, PAYMENT_FAILED };
enum PaymentMethod { CREDIT_CARD, UPI, CASH };
// Union
union PaymentInfo {
    char cardLast4[5];
    char upiId[30];
};
// Product Class
class Product {
private:
    int productId;
    string name;
    double price;
    int stock;
    Category category;
public:
    Product(int id, string n, double p, int s, Category c) {
        productId = id;
        name = n;
        price = p;
        stock = s;
        category = c;
    }
    void displayProduct() {
        cout << productId << " | " << name
             << " | Rs." << price
             << " | Stock: " << stock << endl;
    }
    void updateStock(int quantity) {
        stock += quantity;
    }
    bool checkAvailability(int quantity) {
        return stock >= quantity;
    }
    int getId() { return productId; }
    double getPrice() { return price; }
    string getName() { return name; }
};
// Customer Class
class Customer {
private:
    int customerId;
    string name, email, phone, address;
public:
    Customer(int id, string n, string e, string p, string a) {
        customerId = id;
        name = n;
        email = e;
        phone = p;
        address = a;
    }
    void displayCustomer() {
        cout << customerId << " | " << name
             << " | " << email
             << " | " << phone
             << " | " << address << endl;
    }
    void updateDetails(string n, string e, string p, string a) {
        name = n;
        email = e;
        phone = p;
        address = a;
    }
    int getId() { return customerId; }
};
// Order Structure
struct Order {
    int orderId;
    int customerId;
    int productId;
    int quantity;
    double totalAmount;
    OrderStatus orderStatus;
    PaymentStatus paymentStatus;
    Order(int id, int cid, int pid, int q, double total) {
        orderId = id;
        customerId = cid;
        productId = pid;
        quantity = q;
        totalAmount = total;
        orderStatus = PENDING;
        paymentStatus = PAYMENT_PENDING;
    }
    void displayOrder() {
        cout << "\nOrder ID: " << orderId
             << "\nCustomer ID: " << customerId
             << "\nProduct ID: " << productId
             << "\nQuantity: " << quantity
             << "\nTotal: Rs." << totalAmount
             << "\nOrder Status: " << orderStatus
             << "\nPayment Status: " << paymentStatus << endl;
    }
};
int main() {
    Product products[3] = {
        Product(101, "Laptop", 55000, 5, ELECTRONICS),
        Product(102, "T-Shirt", 800, 10, CLOTHING),
        Product(103, "C++ Book", 600, 7, BOOKS)
    };
    Customer customers[2] = {
        Customer(1, "Aryan", "aryan@gmail.com", "9876543210", "Faridabad"),
        Customer(2, "Rahul", "rahul@gmail.com", "9876500000", "Delhi")
    };
    Order* order = nullptr;
    PaymentInfo payment;
    int choice;
    do {
        cout << "\n===== E-COMMERCE SYSTEM =====\n";
        cout << "1. Display Products\n";
        cout << "2. Display Customers\n";
        cout << "3. Create Order\n";
        cout << "4. Update Order\n";
        cout << "5. Make Payment\n";
        cout << "6. Confirm Order\n";
        cout << "7. Cancel Order\n";
        cout << "8. Display Order\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == 1) {
            for (int i = 0; i < 3; i++)
                products[i].displayProduct();
        }
        else if (choice == 2) {
            for (int i = 0; i < 2; i++)
                customers[i].displayCustomer();
        }
        else if (choice == 3) {
            int cid, pid, qty;
            cout << "Customer ID: ";
            cin >> cid;
            cout << "Product ID: ";
            cin >> pid;
            cout << "Quantity: ";
            cin >> qty;
            if (cid < 1 || cid > 2) {
                cout << "Invalid customer ID.\n";
                continue;
            }
            if (pid < 101 || pid > 103) {
                cout << "Invalid product ID.\n";
                continue;
            }
            int index = pid - 101;
            if (qty <= 0 || !products[index].checkAvailability(qty)) {
                cout << "Product is out of stock.\n";
                continue;
            }
            order = new Order(
                1001,
                cid,
                pid,
                qty,
                products[index].getPrice() * qty
            );
            products[index].updateStock(-qty);
            cout << "Order created successfully.\n";
        }
        else if (choice == 4) {
            if (order == nullptr || order->orderStatus != PENDING) {
                cout << "Order cannot be updated.\n";
                continue;
            }
            int newQty;
            cout << "Enter new quantity: ";
            cin >> newQty;
            if (newQty <= 0) {
                cout << "Invalid quantity.\n";
                continue;
            }
            Product& product = products[order->productId - 101];
            int difference = newQty - order->quantity;
            if (difference > 0 &&
                !product.checkAvailability(difference)) {
                cout << "Not enough stock.\n";
                continue;
            }
            product.updateStock(-difference);
            order->quantity = newQty;
            order->totalAmount = product.getPrice() * newQty;
            order->paymentStatus = PAYMENT_PENDING;

            cout << "Order updated successfully.\n";
        }
        else if (choice == 5) {
            if (order == nullptr) {
                cout << "No order exists.\n";
                continue;
            }
            if (order->orderStatus == CANCELLED) {
                cout << "Payment cannot be made for a cancelled order.\n";
                continue;
            }
            int method;
            cout << "1. Credit Card\n2. UPI\n3. Cash\n";
            cin >> method;
            if (method == CREDIT_CARD) {
                string card;
                cout << "Enter last 4 digits: ";
                cin >> card;
                if (card.length() != 4) {
                    cout << "Invalid card details.\n";
                    order->paymentStatus = PAYMENT_FAILED;
                    continue;
                }
                for (int i = 0; i < 4; i++)
                    payment.cardLast4[i] = card[i];
                payment.cardLast4[4] = '\0';
                order->paymentStatus = PAYMENT_SUCCESS;
            }
            else if (method == UPI) {
                string upi;
                cout << "Enter UPI ID: ";
                cin >> upi;
                if (upi.find('@') == string::npos) {
                    cout << "Invalid UPI ID.\n";
                    order->paymentStatus = PAYMENT_FAILED;
                    continue;
                }
                for (int i = 0; i < (int)upi.length(); i++)
                    payment.upiId[i] = upi[i];

                payment.upiId[upi.length()] = '\0';
                order->paymentStatus = PAYMENT_SUCCESS;
            }
            else if (method == CASH) {
                order->paymentStatus = PAYMENT_SUCCESS;
            }
            else {
                cout << "Invalid payment method.\n";
                order->paymentStatus = PAYMENT_FAILED;
            }

            cout << "Payment processed.\n";
        }
        else if (choice == 6) {
            if (order == nullptr) {
                cout << "No order exists.\n";
            }
            else if (order->paymentStatus != PAYMENT_SUCCESS) {
                cout << "Cannot confirm. Payment has failed or is pending.\n";
            }
            else if (order->orderStatus == CANCELLED) {
                cout << "Cancelled order cannot be confirmed.\n";
            }
            else {
                order->orderStatus = CONFIRMED;
                cout << "Order confirmed.\n";
            }
        }
        else if (choice == 7) {
            if (order == nullptr) {
                cout << "No order exists.\n";
            }
            else if (order->orderStatus == DELIVERED) {
                cout << "Delivered order cannot be cancelled.\n";
            }
            else if (order->orderStatus == CANCELLED) {
                cout << "Order is already cancelled.\n";
            }
            else {
                order->orderStatus = CANCELLED;
                products[order->productId - 101].updateStock(order->quantity);
                cout << "Order cancelled.\n";
            }
        }
        else if (choice == 8) {
            if (order == nullptr)
                cout << "No order exists.\n";
            else
                order->displayOrder();
        }
        else if (choice != 0) {
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);
    delete order;
    return 0;
}