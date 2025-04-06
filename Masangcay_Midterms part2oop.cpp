#include <iostream> 
#include <iomanip>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

//validates if input is a digit
bool isDigits(const string& str) {
    if (str.empty()) return false;
    for (char ch : str) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return true;
}

//makes all string inputs lowercase to be more resistent to errors
string LowerCase(string str) {
    for (int i = 0; i < str.size(); i++) {
        str[i] = tolower(str[i]);
    }
    return str;
} 

// decleration main class that stores the product data
class Product {
private:
    int id;
    string name;
    int quantity;
    float price;
    string category;

public:
//constructor
    Product(int Id, string Name, int Quantity, float Price, string Category) {
        id = Id;
        name = LowerCase(Name);
        quantity = Quantity;
        price = Price;
        category = LowerCase(Category);
    }
//getters
    int getID() const { return id; }
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    float getPrice() const { return price; }
    string getCategory() const { return category; }
//setters
    void setID(int input) { id = input; }
    void setName(string input) { name = LowerCase(input); }
    void setQuantity(int input) { quantity = input; }
    void setPrice(float input) { price = input; }
    void setCategory(string input) { category = LowerCase(input); }
//display function for product information
    void display() const {
        cout << left << setw(10) << id
             << setw(20) << name
             << setw(10) << quantity
             << setw(10) << fixed << setprecision(2) << price
             << setw(15) << category << endl;
    }
};

//class assigned to sort the products by quantity ascending
class SortByQuantity {
public:
    bool operator()(const Product& a, const Product& b) const {
        return a.getQuantity() < b.getQuantity();  // Sort by quantity in ascending order
    }
};

//class assigned to sort the products by price ascending
class SortByPrice {
public:
    bool operator()(const Product& a, const Product& b) const {
        return a.getPrice() < b.getPrice();  // Sort by price in ascending order
    }
};

//vector to hold the product information in "inventory"
vector<Product> inventory;

//header for the inventory table
void displayHeader() {
    cout << left << setw(10) << "ID";
    cout << setw(20) << "Name";
    cout << setw(10) << "Quantity";
    cout << setw(10) << "Price";
    cout << setw(15) << "Category" << endl;
    cout << string(76, '-') << endl;
}
//banner for design purposes
void banner() {
    cout << "----------------------------------------------------------------------------" << endl;
}

//function to add item
void AddItem() {
    string name, category, idAdd;
    int quantity, id;
    float price;

    // Clear any previous input errors.
    cin.clear();


    cout << "Enter The Name Of The Product: ";
    getline(cin, name);

    
    cout << "Enter The Category Of The Product: ";
    getline(cin, category);

    // Loop until a valid product ID is entered.
    while (true) {
        cout << "Enter The ID Of The Product (numbers only): ";
        cin >> idAdd;
        if (isDigits(idAdd)) {
            id = stoi(idAdd);  // Convert the string ID to an integer.
            break;
        }
        cout << "Invalid ID. Please enter numbers only.\n";
    }

    // Get the quantity of the product and validate it.
    cout << "Enter The Quantity Of The Product To Add: ";
    while (!(cin >> quantity) || quantity < 0) {
        cout << "Invalid Input. Please Enter a Whole Number Greater Than or Equal to 0: ";
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    }

    // Get the price of the product and validate it.
    cout << "Enter The Price Of The Product: ";
    while (!(cin >> price) || price < 0) {
        cout << "Invalid Input. Please Enter a Positive Price: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Add the product to the inventory.
    inventory.push_back(Product(id, name, quantity, price, category));

    // Confirm that the item has been added successfully.
    cout << "Your Item Has Been Added Successfully!\n";
    banner();
}

//function to update item
void UpdateItem() {
    if (inventory.empty()) {
        cout << "Inventory is empty." << endl;
        banner();
        return;
    }

    string IdUpd;
    int id;
    bool found = false;

    cout << "Enter The ID Of The Product To Update: ";
    cin >> IdUpd;

    if (!isDigits(IdUpd)) {
        cout << "Invalid ID. Please Enter Numbers Only." << endl;
        banner();
        return;
    }
    id = stoi(IdUpd);

//search for product with id
    for (auto& product : inventory) {
        if (product.getID() == id) {
            found = true;
            int choice;
            cout << "What To Update?" << endl;
            cout << "1 - Quantity" << endl;
            cout << "2 - Price" << endl;
            cout << "Enter Choice: ";
            cin >> choice;

//update quantity
            if (choice == 1) {
                int oldQty = product.getQuantity();
                int newQty;
                cout << "Enter New Quantity: ";
                while (!(cin >> newQty)) {
                    cout << "Invalid Input. Please Enter Whole Numbers Only: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                product.setQuantity(newQty);
                cout << "Quantity Of Item " << product.getName() 
                     << " Is Updated From " << oldQty 
                     << " To " << newQty << endl;
            }

//update price
            else if (choice == 2) {
                float oldPrice = product.getPrice();
                float newPrice;
                cout << "Enter New Price: ";
                cin >> newPrice;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                product.setPrice(newPrice);
                cout << "Price Of Item " << product.getName() 
                     << " Is Updated From " << oldPrice 
                     << " To " << newPrice << endl;
            }
            else {
                cout << "Invalid Choice." << endl;
            }
            break;
        }
    }
// if no item is found invalid
    if (!found) {
        cout << "Item Not Found!" << endl;
    }
}
//function to remove item
void RemoveItem() {
    //check if inventory is emptly 
    if (inventory.empty()) {
        banner();
        cout << "Inventory is empty." << endl;
        banner();
        return;
    }
    //search ID
    string inputID;
    cout << "Enter Product ID to remove: ";
    cin >> inputID;
    //validator if input is valid
    if (!isDigits(inputID)) {
        cout << "Invalid ID." << endl;
        return;
    }
    //converts Products Id if string to int
    int productID = stoi(inputID);

    //search and remove the item
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if (it->getID() == productID) {
            string itemName = it->getName();
            inventory.erase(it);
            cout << "Item " << itemName << " has been removed from the inventory." << endl;
            banner();
            return;
        }
    }
//if no item is found
    cout << "Item not found!" << endl;
}
//functiondisplays all item inventiry
void DisplayAll() {
    //check if inventory is empty
    if (inventory.empty()) {
        cout << "Inventory is empty.\n";
        return;
    }
    //displays everything inside inventory
    cout << "\nCurrent Inventory:\n";
    displayHeader();
    for (const auto& product : inventory) {
        product.display();
    }
}
//function that search for item using id
void SearchItem() {
    //checks if inventory is empty
    if (inventory.empty()) {
        banner();
        cout << "Inventory is empty." << endl;
        banner();
        return;
    }


    string idSearch;
    cout << "Enter Product ID to search: ";
    cin >> idSearch;

    //validation if input is a digit
    if (!isDigits(idSearch)) {
        cout << "Invalid ID. Please enter numbers only." << endl;
        banner();
        return;
    }
    //converts string to int
    int searchID = stoi(idSearch);
    bool found = false;

    //search for specific product with ID
    for (const auto& product : inventory) {
        if (product.getID() == searchID) {
            displayHeader();
            product.display();
            found = true;
            break;
        }
    }
    //if nothing found print not found
    if (!found) {
        cout << "Item not found!" << endl;
    }
    banner();
}
//Sort Product by either quantity or price, ascending or descending
void SortItem(int field, int order) {
    //check if inventiory is empty
    if (inventory.empty()) {
        cout << "Inventory is empty." << endl;
        banner();
        return;
    }

    if (field == 1) {  // Sort by quantity
        if (order == 1) {  // Ascending
            sort(inventory.begin(), inventory.end(), SortByQuantity());
        } else if (order == 2) {  // Descending
            sort(inventory.begin(), inventory.end(), [](const Product& a, const Product& b) {
                return a.getQuantity() > b.getQuantity();  // Sort by quantity descending
            });
        } else {
            cout << "Invalid input for order. Please enter 1 for Ascending or 2 for Descending." << endl;
            return;
        }
    } else if (field == 2) {  // Sort by price
        if (order == 1) {  // Ascending
            sort(inventory.begin(), inventory.end(), SortByPrice());
        } else if (order == 2) {  // Descending
            sort(inventory.begin(), inventory.end(), [](const Product& a, const Product& b) {
                return a.getPrice() > b.getPrice();  // Sort by price descending
            });
        } else {
            cout << "Invalid input for order. Please enter 1 for Ascending or 2 for Descending." << endl;
            return;
        }
    } else {
        cout << "Invalid input for field. Please enter 1 for Quantity or 2 for Price." << endl;
        return;
    }

    cout << "\nInventory sorted!\n";
    DisplayAll();
}
//Display low stock Items
void DisplayLow() {
    //checks if inventory is empty
    if (inventory.empty()) {
        banner();
        cout << "Inventory is empty." << endl;
        banner();
        return;
    }

    cout << "Low Stock Items (Quantity <= 5):" << endl;
    displayHeader();
    bool found = false;

    //search Items that are low in stock <5
    for (const auto& product : inventory) {
        if (product.getQuantity() <= 5) {
            product.display();
            found = true;
        }
    }
    //if none are found
    if (!found) {
        cout << "No low stock items found." << endl;
    }

    cout << "----------------------------------------------------------------------------" << endl;
}

//displays general UI and allows for users choice of action
void DisplayUI(int* choice) {
    cout << "MENU" << endl;
    cout << "1 - Add Item" << endl;
    cout << "2 - Update Item" << endl;
    cout << "3 - Remove Item" << endl;
    cout << "4 - Display All Items" << endl;
    cout << "5 - Search Items" << endl;
    cout << "6 - Sort Items" << endl;
    cout << "7 - Display Low Stock Items" << endl;
    cout << "8 - Exit" << endl;

    string input;
    //checks if user inputs a valid choice
    while (true) {
        cout << "Enter Choice: ";
        getline(cin, input);
        if (isDigits(input)) {
            *choice = stoi(input);
            break;
        } else {
            cout << "Invalid input. Please enter a number from 1 to 8." << endl;
        }
    }

    //if else statements for users choice that calls functions
    if (*choice == 1) {
        cout << "--------------------------ADDING ITEM---------------------------------------" << endl;
        AddItem();
    } else if (*choice == 2) {
        cout << "--------------------------Updating Item-------------------------------------" << endl;
        UpdateItem();
    } else if (*choice == 3) {
        RemoveItem();
    } else if (*choice == 4) {
        cout << "--------------------------Displaying All Items------------------------------" << endl;
        DisplayAll();
        banner();
    } else if (*choice == 5) {
        SearchItem();
    } else if (*choice == 6) {
        int sortField, sortOrder;
        cout << "Sort by (1 for quantity, 2 for price): ";
        cin >> sortField;
        cout << "Order (1 for Ascending, 2 for Descending): ";
        cin >> sortOrder;
        cin.ignore();
        SortItem(sortField, sortOrder);
    } else if (*choice == 7) {
        DisplayLow();
    } else if (*choice == 8) {
        return;
    } else {
        cout << "Invalid choice. Please select from 1 to 8." << endl;
    }

}

int main() {
    int choice, Confirmation;

    do {
        banner();
        DisplayUI(&choice);
        if (choice == 8) {
            break;  // Exit immediately if choice is 8
        }

        // Confirmation loop 
        do {
            cout << "Display Menu again?" << endl;
            cout << "1 = Yes" << endl;
            cout << "2 = No" << endl;
            cout << "Enter Choice: ";
            cin >> Confirmation;
            cin.ignore();
        } while (Confirmation != 1 && Confirmation != 2);

        if (Confirmation == 2) {
            break;  // Exit main loop if user doesn't want to continue
        }

    } while (true);

    cout << "\nExiting...";
    return 0;
}