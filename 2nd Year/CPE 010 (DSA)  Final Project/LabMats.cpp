#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <queue>

using namespace std;

/* Class for the Materials in the Laboratory */
class Material {
public:
    string name;
    int quantity;

    Material(const string& name, int quantity) : name(name), quantity(quantity) {}
};

/* Class for the Account Manager */
class AccountManager {
private:
    string filename;

public:
    AccountManager(const string& filename = "accounts.txt") : filename(filename) {}

    bool registerAccount(const string& name, const string& studentNumber) {
        ifstream file(filename);
        string line;

        while (getline(file, line)) {
            istringstream ss(line);
            string existingName, existingNumber;
            getline(ss, existingName, ',');
            getline(ss, existingNumber);
            if (existingName == name || existingNumber == studentNumber) {
                return false;  // User already exists
            }
        }

        ofstream outFile(filename, ios::app);
        outFile << name << "," << studentNumber << "\n";  // Save new user
        return true;  // Registration successful
    }

    bool login(const string& name, string& studentNumber) {
        ifstream file(filename);
        string line;

        while (getline(file, line)) {
            istringstream ss(line);
            string existingName, existingNumber;
            getline(ss, existingName, ',');
            getline(ss, existingNumber);
            if (existingName == name && existingNumber == studentNumber) {
                return true;  // Login successful
            }
        }
        return false;  // Credentials incorrect
    }
};

/* Class for the Database Manager */
class DatabaseManager {
private:
    string filename;
    map<string, int> materials;

public:
    DatabaseManager(const string& filename = "database.txt")
                    : filename(filename) {
                    loadMaterials();
    }

    void loadMaterials() {
        ifstream file(filename);
        string line;

        while (getline(file, line)) {
            istringstream ss(line);
            string name;
            int quantity;
            getline(ss, name, ',');
            ss >> quantity;
            materials[name] = quantity;
        }
    }

    void saveMaterials() {
        ofstream file(filename);
        for (const auto& material : materials) {
            file << material.first << "," << material.second << "\n";
        }
    }

    void addMaterial(const string& name, int quantity) {
        materials[name] += quantity;  // Add to existing quantity
        saveMaterials();
    }

    void removeMaterial(const string& name) {
        materials.erase(name);
        saveMaterials();
    }

    const map<string, int>& getMaterials() const {
        return materials;
    }
};

/* Class for the Borrowing Request */
class BorrowingRequest {
public:
    string studentName;
    string studentNumber;
    vector<Material> requestedMaterials;

    BorrowingRequest(const string& name, const string& number) 
        : studentName(name), studentNumber(number) {}
};

/* Class for the Borrowing Menu or App */
class BorrowingApp {
private:
    DatabaseManager dbManager;
    queue<BorrowingRequest> borrowingQueue;
    ofstream logFile;
    ofstream requestFile;
    string pendingRequestsFile = "pendingRequests.txt";

public:
    BorrowingApp() : dbManager(), logFile("log.txt", ios::app) {
        loadPendingRequests();
    }

    ~BorrowingApp() {
        savePendingRequests();
    }

    void loadPendingRequests() {
        ifstream file(pendingRequestsFile);
        string line;
        while (getline(file, line)) {
            istringstream ss(line);
            string studentName, studentNumber;
            getline(ss, studentName, ',');
            getline(ss, studentNumber, ',');
            BorrowingRequest request(studentName, studentNumber);
            while (getline(ss, line, ',')) {
                string materialName;
                int quantity;
                istringstream materialStream(line);
                getline(materialStream, materialName, ':');
                materialStream >> quantity;
                request.requestedMaterials.emplace_back(materialName, quantity);
            }
            borrowingQueue.push(request);
        }
    }

    void savePendingRequests() {
        ofstream file(pendingRequestsFile);
        queue<BorrowingRequest> tempQueue = borrowingQueue;
        while (!tempQueue.empty()) {
            BorrowingRequest request = tempQueue.front();
            tempQueue.pop();
            file << request.studentName << "," << request.studentNumber;
            for (const auto& material : request.requestedMaterials) {
                file << "," << material.name << ":" << material.quantity;
            }
            file << "\n";
        }
    }

    void start() {
        while (true) {
            cout << "\n-------------------------------------------------\n";
            cout << "Welcome to the Lab Materials Borrowing Interface!\n";
            cout << "-------------------------------------------------\n";
            cout << "Main Menu:\n";
            cout << "1. Borrower's Log In\n";
            cout << "2. Borrower's Registration\n";
            cout << "3. Admin Access\n";
            cout << "4. Exit\n\n";
            cout << "Enter choice (number only): ";

            int choice;
            if (!(cin >> choice)) {
                cin.clear();  // Clear the error flag
                cin.ignore(10000, '\n');  // Discard invalid input
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }
            cout << "\n";
            cin.ignore(10000, '\n');  // Clear the newline character from the input buffer

            if (choice == 1) {
                studentLogin();
            } else if (choice == 2) {
                studentRegister();
            } else if (choice == 3) {
                adminAccess();
            } else if (choice == 4) {
                break;
            } else {
                cout << "Invalid option. Please try again.\n";
            }
        }
    }

    void studentLogin() {
        cout << "----------------------\n";
        cout << "   Borrower's Login    \n";
        cout << "----------------------\n";
        string studentName, studentNumber;
        cout << "Enter your name (or 'return' to go back): ";
        getline(cin, studentName);

        if (studentName == "return") {
            return;  // Return to the main menu
        }

        cout << "Enter your student number: ";
        getline(cin, studentNumber);

        AccountManager accountManager;
        if (accountManager.login(studentName, studentNumber)) {
            BorrowingRequest request(studentName, studentNumber);
            handleBorrowingRequest(request);
        } else {
            cout << "Invalid credentials. Please try again.\n\n";
        }
    }

    void studentRegister() {
        cout << "-----------------------------\n";
        cout << "   Borrower's Registration    \n";
        cout << "-----------------------------\n";
        string studentName, studentNumber;
        cout << "Enter your name (or 'return' to go back): ";
        getline(cin, studentName);

        if (studentName == "return") {
            return;  // Return to the main menu
        }

        cout << "Enter your student number: ";
        getline(cin, studentNumber);

        // Check if student number is purely integers
        for (char c : studentNumber) {
            if (!isdigit(c)) {
                cout << "Invalid student number. Please enter numbers only.\n\n";
                return;
            }
        }

        AccountManager accountManager;
        if (accountManager.registerAccount(studentName, studentNumber)) {
            cout << "Registration successful!\n\n";
        } else {
            cout << "Registration failed. User already exists.\n\n";
        }
    }

    void adminAccess() {
        cout << "-----------------------------\n";
        cout << "         Admin Access    \n";
        cout << "-----------------------------\n";
        string adminName, adminPassword;
        cout << "Enter admin name (or 'return' to go back): ";
        getline(cin, adminName);

        if (adminName == "return") {
            return;  // Return to the main menu
        }

        cout << "Enter admin password: ";
        getline(cin, adminPassword);

        if (adminName == "Admin" && adminPassword == "admin") {
            while (true) {
                cout << "\nAdmin Menu:\n";
                cout << "1. View Materials\n";
                cout << "2. Add Material\n";
                cout << "3. Remove Material\n";
                cout << "4. Process Borrowing Requests\n";
                cout << "5. Exit Admin Access\n\n";
                cout << "Enter choice (number only): ";

            int choice;
            if (!(cin >> choice)) {
                cin.clear();  // Clear the error flag
                cin.ignore(10000, '\n');  // Discard invalid input
                cout << "Invalid input. Please enter a number.\n\n";
                continue;
            }
            cout << "\n";
            cin.ignore(10000, '\n');  // Clear the newline character from the input buffer

                if (choice == 1) {
                    viewMaterials();
                } else if (choice == 2) {
                    addMaterialAdmin();
                } else if (choice == 3) {
                    removeMaterialAdmin();
                } else if (choice == 4) {
                    processAdminRequests();
                } else if (choice == 5) {
                    break;
                } else {
                    cout << "Invalid option. Please try again. \n\n";
                }
            }
        } else {
            cout << "Invalid admin credentials.\n\n";
        }
    }

    void viewMaterials(){
        cout << "\n-------------------\n";
        cout << "Available Materials\n";
        cout << "-------------------\n";
        for (const auto& material : dbManager.getMaterials()) {
            cout << material.first << ": " << material.second << "\n";
        }
    }

    void addMaterialAdmin() {
        viewMaterials();

        string materialName;
        int quantity;

        cout << "\nEnter material name to add (or 'return' to go back): ";
        getline(cin, materialName);

         if (materialName == "return") {
            return;  // Return to the admin menu
        }

        cout << "Enter quantity: ";

        while (!(cin >> quantity)) {
            cin.clear();  // Clear the error flag
            cin.ignore(10000, '\n');  // Discard invalid input
            cout << "Invalid input. Please enter a number: ";
        }
        cin.ignore(10000, '\n');  // Clear the newline character from the input buffer

        dbManager.addMaterial(materialName, quantity);
        cout << "Material added successfully.\n";
    }

    void removeMaterialAdmin() {
        viewMaterials();

        string materialName;
        cout << "\nEnter material name to remove (or 'return' to go back): ";
        getline(cin, materialName);

        if (materialName == "return") {
            return;  // Return to the admin menu
        }

        if (dbManager.getMaterials().count(materialName) == 0) {
            cout << "Material not found.\n";
            return;
        }

        dbManager.removeMaterial(materialName);
        cout << "Material removed successfully.\n";
    }

    void handleBorrowingRequest(BorrowingRequest& request) {
        while (true) {
            
            viewMaterials();

            string materialName;
            int quantity;

            cout << "\nEnter material name to borrow (or 'done' to finish): ";
            getline(cin, materialName);
            if (materialName == "done") {
                finishBorrowing(request);
                break;
            }

            cout << "Enter quantity: ";
            if (!(cin >> quantity)) {
                cin.clear();  // Clear the error flag
                cin.ignore(10000, '\n');  // Discard invalid input
                cout << "Invalid input. Please input requested item's information properly.\n\n";
                continue;
            }
            cin.ignore(10000, '\n');  // Clear the newline character from the input buffer

            addMaterial(request, materialName, quantity);
        }
    }

    void addMaterial(BorrowingRequest& request, const string& materialName, int quantity) {
        const auto& materials = dbManager.getMaterials();
        if (materials.count(materialName) == 0) {
            cout << "Material not found.\n";
            return;
        }

        int availableQuantity = materials.at(materialName);
        if (quantity > availableQuantity) {
            cout << "Only " << availableQuantity << " available for " << materialName << ".\n";
            return;
        }

        request.requestedMaterials.emplace_back(materialName, quantity);
        dbManager.addMaterial(materialName, -quantity);  // Deduct the requested quantity from the database
        cout << "Added " << quantity << " of " << materialName << " to your borrowing request.\n";
    }


    void processAdminRequests() {
        cout << "You have " << borrowingQueue.size() << " pending requests.\n\n";
        if (!borrowingQueue.empty()) {
            BorrowingRequest request = borrowingQueue.front();
            borrowingQueue.pop();

            cout << "Processing request for " << request.studentName << "...\n";
            cout << "Materials Requested:\n";
            for (const auto& material : request.requestedMaterials) {
                cout << "- " << material.name << ": " << material.quantity << "\n";
            }

            string decision;
            while (true) {
                cout << "Approve this request? (y = yes/n = no): ";
                cin >> decision;
                cin.ignore(10000, '\n');  // Clear the newline character from the input buffer
                if (decision == "y" || decision == "n") {
                    break;
                }
                cout << "Invalid input. Please enter 'y' or 'n'.\n";
            }

            logFile << "Processing request for: " << request.studentName << " (" << request.studentNumber << ")\n";
            logFile << "Materials Requested:\n";
            for (const auto& material : request.requestedMaterials) {
                logFile << "- " << material.name << ": " << material.quantity << "\n";
            }

            if (decision == "y") {
                cout << "Request approved.\n";
                logFile << "Decision: Approved\n";
            } else {
                for (const auto& material : request.requestedMaterials) {
                    dbManager.addMaterial(material.name, material.quantity);  // Return the quantity back to the database
                }
                cout << "Request denied.\n";
                logFile << "Decision: Denied\n";
            }

            logFile << "-----------------------------------\n";
            savePendingRequests();  // Save the updated queue to the file
        } else {
            cout << "No pending requests.\n";
        }
    }
    
    void finishBorrowing(BorrowingRequest& request) {
        if (request.requestedMaterials.empty()) {
            cout << "No materials requested.\n\n";
            return;
        }

        borrowingQueue.push(request);  // Add the request to the queue

        logFile << "Borrowing Request Submitted:\n";
        logFile << "Borrower: " << request.studentName << " (" << request.studentNumber << ")\n";
        logFile << "Materials Requested:\n";
        for (const auto& material : request.requestedMaterials) {
            logFile << "- " << material.name << ": " << material.quantity << "\n";
        }
        logFile << "-----------------------------------\n";

        cout << "\nBorrowing Request Submitted:\n";
        cout << "Thank you for using the borrowing system! Please wait for your request to be processed.\n\n";
    }
};

int main() {
    BorrowingApp app;
    app.start();
    return 0;
}