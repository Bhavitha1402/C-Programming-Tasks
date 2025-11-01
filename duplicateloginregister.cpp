#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <sys/stat.h>
#include <direct.h> 

using namespace std;

string hashPassword(const string& password) {
    unsigned long hash = 5381;
    for (char c : password) {
        hash = ((hash << 5) + hash) + c;
    }
    return to_string(hash);
}

bool isValidUsername(const string& username) {
    if (username.length() < 3 || username.length() > 20) {
        return false;
    }
    return all_of(username.begin(), username.end(), 
                  [](char c) { return isalnum(c) || c == '_'; });
}

bool isValidPassword(const string& password) {
    return password.length() >= 6;
}

bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

bool directoryExists(const string& path) {
    struct stat info;
    if (stat(path.c_str(), &info) != 0) {
        return false;
    }
    return (info.st_mode & S_IFDIR) != 0;
}

bool createDirectory(const string& path) {
#ifdef _WIN32
    return _mkdir(path.c_str()) == 0 || directoryExists(path);
#else
    return mkdir(path.c_str(), 0755) == 0 || directoryExists(path);
#endif
}

bool usernameExists(const string& username) {
    string filename = "users/" + username + ".txt";
    return fileExists(filename);
}

bool registerUser(const string& username, const string& password) {
    if (!isValidUsername(username)) {
        cout << "\n[ERROR] Invalid username! Username must be 3-20 characters and contain only letters, numbers, or underscores.\n";
        return false;
    }
    
    if (!isValidPassword(password)) {
        cout << "\n[ERROR] Invalid password! Password must be at least 6 characters long.\n";
        return false;
    }
    
    if (usernameExists(username)) {
        cout << "\n[ERROR] Username already exists! Please choose a different username.\n";
        return false;
    }
    
    if (!directoryExists("users")) {
        if (!createDirectory("users")) {
            cout << "\n[ERROR] Could not create users directory!\n";
            return false;
        }
    }

    string filename = "users/" + username + ".txt";
    ofstream file(filename);
    
    if (!file.is_open()) {
        cout << "\n[ERROR] Error creating user file!\n";
        return false;
    }
    
    string hashedPassword = hashPassword(password);
    file << username << endl;
    file << hashedPassword << endl;
    file.close();
    
    cout << "\n[SUCCESS] Registration successful! Welcome, " << username << "!\n";
    return true;
}

bool loginUser(const string& username, const string& password) {
    if (!usernameExists(username)) {
        cout << "\n[ERROR] Username not found! Please register first.\n";
        return false;
    }
    
    string filename = "users/" + username + ".txt";
    ifstream file(filename);
    
    if (!file.is_open()) {
        cout << "\n[ERROR] Error reading user file!\n";
        return false;
    }
    
    string storedUsername, storedPasswordHash;
    getline(file, storedUsername);
    getline(file, storedPasswordHash);
    file.close();
    
    string inputPasswordHash = hashPassword(password);
    
    if (inputPasswordHash == storedPasswordHash) {
        cout << "\n[SUCCESS] Login successful! Welcome back, " << username << "!\n";
        return true;
    } else {
        cout << "\n[ERROR] Incorrect password! Please try again.\n";
        return false;
    }
}

void displayMenu() {
    cout << "\n========================================\n";
    cout << "   LOGIN & REGISTRATION SYSTEM\n";
    cout << "========================================\n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";
    cout << "========================================\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;
    string username, password;
    
    cout << "Welcome to the Authentication System!\n";
    
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(); 
        
        switch (choice) {
            case 1: { 
                cout << "\n--- REGISTRATION ---\n";
                cout << "Enter username (3-20 chars, alphanumeric): ";
                getline(cin, username);
                
                cout << "Enter password (min 6 characters): ";
                getline(cin, password);
                
                registerUser(username, password);
                break;
            }
            
            case 2: { 
                cout << "\n--- LOGIN ---\n";
                cout << "Enter username: ";
                getline(cin, username);
                
                cout << "Enter password: ";
                getline(cin, password);
                
                loginUser(username, password);
                break;
            }
            
            case 3: { 
                cout << "\nThank you for using the Authentication System!\n";
                cout << "Goodbye!\n";
                return 0;
            }
            
            default:
                cout << "\n[ERROR] Invalid choice! Please enter 1, 2, or 3.\n";
        }
    }
    
    return 0;
}