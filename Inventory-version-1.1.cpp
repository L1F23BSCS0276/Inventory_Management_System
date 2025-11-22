#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

// Maximum number of products the system can handle
const int MAX_PRODUCTS = 100;

// Function prototypes
void addProduct (char** names, int* quantities, double* prices, int& count);
void removeProduct (char** names, int* quantities, double* prices, int& count);
void displayInventory (char** names, const int* quantities, const double* prices, int count);
void generateReport (char** names, const int* quantities, const double* prices, int count);
void saveToFile (char** names, const int* quantities, const double* prices, int count);
void loadFromFile (char** names, int* quantities, double* prices, int& count);
void searchProduct (char** names, const int* quantities, const double* prices, int count);
void modifyProduct (char** names, int* quantities, double* prices, int count);

int main() 
{
    char* names[MAX_PRODUCTS];
    for (int i = 0; i < MAX_PRODUCTS; ++i) 
	{
        names[i] = new char[50];
    }
    int* quantities = new int[MAX_PRODUCTS];
    double* prices = new double[MAX_PRODUCTS];
    int productCount = 0;
    char choice;

    loadFromFile(names, quantities, prices, productCount);

    do {
        cout << "\n======= Inventory Management System =======\n";
        cout << "1. Add Product\n";
        cout << "2. Remove Product\n";
        cout << "3. Display Inventory\n";
        cout << "4. Generate Report\n";
        cout << "5. Search Product\n";
        cout << "6. Modify Product\n";
        cout << "7. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
		{
            case '1':
                addProduct(names, quantities, prices, productCount);
                break;
            case '2':
                removeProduct(names, quantities, prices, productCount);
                break;
            case '3':
                displayInventory(names, quantities, prices, productCount);
                break;
            case '4':
                generateReport(names, quantities, prices, productCount);
                break;
            case '5':
                searchProduct(names, quantities, prices, productCount);
                break;
            case '6':
                modifyProduct(names, quantities, prices, productCount);
                break;
            case '7':
                saveToFile(names, quantities, prices, productCount);
                cout << "Inventory saved. Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please enter again.\n";
        }
    } while (choice != '7');

    for(int i = 0; i < MAX_PRODUCTS; ++i) 
	{
        delete[] names[i];
    }
    delete[] quantities;
    delete[] prices;

    return 0;
}

void addProduct(char** names, int* quantities, double* prices, int& count) 
{
    if (count < MAX_PRODUCTS) 
	{
        cout << "Enter product name: ";
        cin.ignore();  // Ignore newline character left in buffer
        cin.getline(names[count], 50);
        cout << "Enter quantity: ";
        cin >> quantities[count];
        cout << "Enter price: ";
        cin >> prices[count];
        count++;
        cout << "Product added successfully.\n";
    }
	else
	{
        cout << "Inventory is full. Cannot add more products.\n";
    }
}

void removeProduct(char** names, int* quantities, double* prices, int& count) 
{
    if (count > 0) 
	{
        cout << "Remove by (1) Index or (2) Name: ";
        int choice;
        cin >> choice;
        if (choice == 1) 
		{
            cout << "Enter index of product to remove (1-" << count << "): ";
            int index;
            cin >> index;
            
            if (index >= 1 && index <= count) 
			{
                index--;  // Adjust index to zero-based
                // Shift elements to fill the gap
                for (int i = index; i < count - 1; ++i) 
				{
                    strcpy(names[i], names[i + 1]);
                    quantities[i] = quantities[i + 1];
                    prices[i] = prices[i + 1];
                }
                count--;
                cout << "Product removed successfully.\n";
            } 
			else 
			{
                cout << "Invalid index. No product removed.\n";
            }
        } 
		else if (choice == 2) 
		{
        	cout << "\n(Note: First Letter of Every Word Must be Capital e.g : Water Bottle)\n";
            cout << "Enter name of product to remove: ";
            cin.ignore();  // Ignore newline character left in buffer
            char name[50];
            cin.getline(name, 50);
            bool found = false;
            for (int i = 0; i < count; ++i) 
			{
                if (strcmp(names[i], name) == 0) 
				{
                    // Shift elements to fill the gap
                    for (int j = i; j < count - 1; ++j) 
					{
                        strcpy(names[j], names[j + 1]);
                        quantities[j] = quantities[j + 1];
                        prices[j] = prices[j + 1];
                    }
                    count--;
                    found = true;
                    cout << "Product removed successfully.\n";
                    break;
                }
            }
            if (!found) 
			{
                cout << "Product not found. No product removed.\n";
            }
        } 
		else 
		{
            cout << "Invalid choice. No product removed.\n";
        }
    } 
	else 
	{
        cout << "Inventory is empty. No product to remove.\n";
    }
}

void displayInventory(char** names, const int* quantities, const double* prices, int count) 
{
    if (count > 0) 
	{
        cout << "\n===================== Inventory =====================\n\n";
        cout << "Index     Name                 Quantity       Price\n";  //5 spaces=before name, 17 spaces= before quantity, 7 spaces= before price
        for (int i = 0; i < count; ++i) 
		{
            cout<< left << setw(7) << i + 1 << "   " 
                << left << setw(20)<< names[i] << "   " 
                << left << setw(10)<< quantities[i] << "   $" 
                << left << setw(8) << fixed << setprecision(2) << prices[i] << "\n";   //left is used for left aligning data and setwidth== setw() is used for spaces
        }
    } 
	else 
	{
        cout << "Inventory is empty.\n";
    }
}

void generateReport(char** names, const int* quantities, const double* prices, int count) 
{
    if (count > 0) 
	{
        ofstream report("inventory_report.txt");
        if (report.is_open()) 
		{
            report << "\n================== Inventory Report ==================\n\n";
            report << "Index     Name                 Quantity       Price\n";  //5 spaces=before name, 17 spaces= before quantity, 7 spaces= before price
            for (int i = 0; i < count; ++i)
			{
                report << left << setw(7) << i + 1 << "   " 
                       << left << setw(20)<< names[i] << "   " 
                       << left << setw(10)<< quantities[i] << "   $" 
                       << left << setw(8) << fixed << setprecision(2) << prices[i] << "\n";
            }
            report.close();
            cout << "Inventory report generated to inventory_report.txt\n";
        } 
		else 
		{
            cout << "Unable to open file for report generation.\n";
        }
    } 
	else 
	{
        cout << "Inventory is empty. Cannot generate report.\n";
    }
}

void saveToFile(char** names, const int* quantities, const double* prices, int count) 
{
    ofstream outFile("inventory_data.txt");
    if (outFile.is_open()) 
	{
        outFile << count << "\n";  // Store the number of products first
        for (int i = 0; i < count; ++i) 
		{
            outFile << names[i] << "\n";
            outFile << quantities[i] << "\n";
            outFile << prices[i] << "\n";
        }
        outFile.close();
    } 
	else 
	{
        cout << "Unable to save inventory data to file.\n";
    }
}

void loadFromFile(char** names, int* quantities, double* prices, int& count) 
{
    ifstream inFile("inventory_data.txt");
    if (inFile.is_open()) 
	{
        inFile >> count;  // Read the number of products
        inFile.ignore();  // Ignore newline character after count
        for (int i = 0; i < count; ++i) 
		{
            inFile.getline(names[i], 50);
            inFile >> quantities[i];
            inFile >> prices[i];
            inFile.ignore();  // Ignore newline after prices
        }
        inFile.close();
    } 
	else 
	{
        cout << "No previous inventory data found. Starting with empty inventory.\n";
    }
}

void searchProduct(char** names, const int* quantities, const double* prices, int count) 
{
    if (count > 0) 
	{
    	cout << "\n(Note: First Letter of Every Word Must be Capital e.g : Water Bottle)\n";
        cout << "Enter name of product to search: ";
        cin.ignore();  // Ignore newline character left in buffer
        char name[50];
        cin.getline(name, 50);
        bool found = false;
        for (int i = 0; i < count; ++i) 
		{
            if (strcmp(names[i], name) == 0) 
			{
                cout << "Product found at index " << i + 1 << ":\n";
                cout << "Name: " << names[i] << "\n";
                cout << "Quantity: " << quantities[i] << "\n";
                cout << "Price: $" << fixed << setprecision(2) << prices[i] << "\n";
                found = true;
                break;
            }
        }
        if (!found) 
		{
            cout << "Product not found.\n";
        }
    } 
	else 
	{
        cout << "Inventory is empty.\n";
    }
}

void modifyProduct(char** names, int* quantities, double* prices, int count) 
{
    if (count > 0) 
	{
        cout << "Enter index of product to modify (1-" << count << "): ";
        int index;
        cin >> index;
        if (index >= 1 && index <= count) 
		{
            index--;  // Adjust index to zero-based
            char choice;
            cout << "\n======= Modify Product =======\n";
            cout << "1. Modify Name\n";
            cout << "2. Modify Quantity\n";
            cout << "3. Modify Price\n";
            cout << "4. Modify All\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) 
			{
                case '1':
                    cout << "Enter new name: ";
                    cin.ignore();  // Ignore newline character left in buffer
                    cin.getline(names[index], 50);
                    cout << "Product name modified successfully.\n";
                    break;
                case '2':
                    cout << "Enter new quantity: ";
                    cin >> quantities[index];
                    cout << "Product quantity modified successfully.\n";
                    break;
                case '3':
                    cout << "Enter new price: ";
                    cin >> prices[index];
                    cout << "Product price modified successfully.\n";
                    break;
                case '4':
                    cout << "Enter new name: ";
                    cin.ignore();  // Ignore newline character left in buffer
                    cin.getline(names[index], 50);
                    cout << "Enter new quantity: ";
                    cin >> quantities[index];
                    cout << "Enter new price: ";
                    cin >> prices[index];
                    cout << "Product modified successfully.\n";
                    break;
                default:
                    cout << "Invalid choice. No modifications made.\n";
            }
        } 
		else 
		{
            cout << "Invalid index. No modifications made.\n";
        }
    } 
	else 
	{
        cout << "Inventory is empty. No product to modify.\n";
    }
}
