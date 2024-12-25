#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>  // For password input hiding (Windows)
using namespace std;

// Structure to store user login information
struct login {
    char id[100];
    char pass[100];

    void getid() {
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Password: ";
        cin >> pass;
    }

    void displayid() {
        cout << "ID: " << id << "\tPassword: " << pass << endl;
    }
};

// Structure to store reservation details
struct reser {
    char tno[10];      // Train number
    char tname[50];    // Train name
    char bp[50];       // Boarding point
    char dest[50];     // Destination point
    int nosr;          // Number of seats
    char pname[10][50]; // Passenger names
    int age[10];       // Passenger ages
    char clas[10];     // Class type (e.g., AC, Sleeper)
    int pnr;           // PNR number
    int amc;           // Amount charged for booking

    void displayresdet() {
        cout << "Train No: " << tno << "\tTrain Name: " << tname << endl;
        cout << "Boarding: " << bp << "\tDestination: " << dest << endl;
        cout << "Passengers: " << endl;
        for (int i = 0; i < nosr; i++) {
            cout << "Name: " << pname[i] << "\tAge: " << age[i] << endl;
        }
    }
};

// Structure for cancellation details
struct canc {
    int pnr;
    char tno[10];
    char tname[50];
    char bp[50];
    char dest[50];
    int nosc;
    char pname[10][50];
    int age[10];
    char clas[10];
    int d, m;  // Date and month of cancellation
    float amr; // Amount refunded
    int tamt;  // Total amount

    void getcancdet() {
        cout << "Enter PNR for cancellation: ";
        cin >> pnr;
        cout << "Enter Date of Cancellation: ";
        cin >> d;
        cout << "Enter Month of Cancellation: ";
        cin >> m;
    }

    void displaycancdet() {
        cout << "PNR: " << pnr << "\tRefund Amount: " << amr << endl;
    }
};

// Structure for train details
struct detail {
    int tno;
    int c1;     // Number of sleeper class seats
    int c2;     // Number of AC class seats
    int d, m;   // Departure date and month

    void displaydetail() {
        cout << "Train No: " << tno << "\tSleeper Class Seats: " << c1 << "\tAC Class Seats: " << c2 << endl;
    }
};

// Function prototypes
void reserve();
void displaypassdetail();
void enquiry();
void cancell();
void can();
void user();
void manage();

int main() {
    int ch;
    do {
        cout << "********** WELCOME TO RAILWAY BOOKING SYSTEM **********" << endl;
        cout << "1. User Menu" << endl;
        cout << "2. Manage User Database" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> ch;
        cout << endl;

        switch (ch) {
            case 1: user(); break;
            case 2: manage(); break;
            case 3: cout << "Exiting the system." << endl; break;
            default: cout << "Invalid choice, please try again." << endl;
        }
    } while (ch != 3);

    return 0;
}

void reserve() {
    // Reserve function implementation
    fstream f;
    reser b;
    f.open("p.txt", ios::in | ios::out | ios::binary);
    if (!f) {
        cout << "Error opening file!" << endl;
        return;
    }
    cout << "Enter train details for reservation:\n";
    // Taking input for reservation
    cout << "Enter Train No: ";
    cin >> b.tno;
    cout << "Enter Train Name: ";
    cin >> b.tname;
    cout << "Enter Boarding Point: ";
    cin >> b.bp;
    cout << "Enter Destination: ";
    cin >> b.dest;
    cout << "Enter Number of Passengers: ";
    cin >> b.nosr;
    for (int i = 0; i < b.nosr; i++) {
        cout << "Enter Name of Passenger " << i + 1 << ": ";
        cin >> b.pname[i];
        cout << "Enter Age of Passenger " << i + 1 << ": ";
        cin >> b.age[i];
    }
    cout << "Enter Class (AC/Sleeper): ";
    cin >> b.clas;
    cout << "Enter Amount: ";
    cin >> b.amc;
    f.write((char*)&b, sizeof(b));
    cout << "Reservation Successful!" << endl;
    f.close();
}

void displaypassdetail() {
    // Function to display reservation details
    fstream f;
    reser b;
    f.open("p.txt", ios::in | ios::out | ios::binary);
    if (!f) {
        cout << "Error opening file!" << endl;
        return;
    }
    while (f.read((char*)&b, sizeof(b))) {
        b.displayresdet();
    }
    f.close();
}

void enquiry() {
    // Function to display available trains
    fstream f;
    detail a;
    f.open("t.txt", ios::in | ios::out | ios::binary);
    if (!f) {
        cout << "Error opening file!" << endl;
        return;
    }
    while (f.read((char*)&a, sizeof(a))) {
        a.displaydetail();
    }
    f.close();
}

void cancell() {
    // Cancellation function
    fstream f1, f2, f3;
    f1.open("t.txt", ios::in | ios::out | ios::binary);
    f2.open("p.txt", ios::in | ios::out | ios::binary);
    f3.open("cn.txt", ios::in | ios::out | ios::binary);
    canc c;
    reser b;
    detail a;
    cout << "Enter cancellation details:" << endl;
    c.getcancdet();
    while (f2.read((char*)&b, sizeof(b))) {
        if (b.pnr == c.pnr) {
            strcpy(c.tno, b.tno); // Use strcpy for string copying
            strcpy(c.tname, b.tname);
            strcpy(c.bp, b.bp);
            strcpy(c.dest, b.dest);
            c.nosc = b.nosr;
            for (int j = 0; j < c.nosc; j++) {
                strcpy(c.pname[j], b.pname[j]);
                c.age[j] = b.age[j];
            }
            strcpy(c.clas, b.clas);
            // Calculate refund logic here
            c.displaycancdet();
            return;
        }
    }
    cout << "Invalid PNR" << endl;
    f1.close();
    f2.close();
    f3.close();
}

void user() {
    // User menu
    login a;
    int ch;
    char password[100];
    fstream f;
    f.open("id.txt", ios::in | ios::out | ios::binary);
    char id[100];
    cout << "Enter your id: ";
    cin >> id;
    cout << "Enter your password: ";
    // Use normal input for password (you can use conio.h for hiding input if on Windows)
    cin >> password;
    while (f.read((char*)&a, sizeof(a))) {
        if (strcmp(a.id, id) == 0 && strcmp(a.pass, password) == 0) {
            do {
                cout << "1. Reserve\n2. Cancel\n3. Enquiry\n4. Return to main menu\n";
                cout << "Enter your choice: ";
                cin >> ch;
                switch (ch) {
                    case 1: reserve(); break;
                    case 2: cancell(); break;
                    case 3: enquiry(); break;
                }
            } while (ch <= 3);
        }
    }
    cout << "Invalid ID or Password." << endl;
    f.close();
}

void manage() {
    // Manage user database
    fstream f;
    char c;
    login a;
    cout << "User Management Menu\n";
    do {
        cout << "1. Create ID database\n2. Add User\n3. Display User details\n4. Return to main menu\n";
        cout << "Enter your choice: ";
        cin >> c;
        switch (c) {
            case '1': f.open("id.txt", ios::out | ios::binary); break;
            case '2': f.open("id.txt", ios::in | ios::out | ios::binary | ios::app); break;
            case '3': f.open("id.txt", ios::in | ios::out | ios::binary); break;
        }
    } while (c != '4');
}
