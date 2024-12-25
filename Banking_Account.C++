#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

struct CurrentValidID {
    int year;
    string branch;
    int totalVoters;
};

struct Candidate {
    int cid;
    string cname;
    int votes;
};

// Global
CurrentValidID currentVID;
int numberOfCandidates;
Candidate candidates[5];
char studentVotes[500];

void encode() {
    cout << "\x1B[40m" << "\x1B[30m";
}

void decode() {
    cout << "\x1B[0m";
}

int extractYear(const string& userID) {
    int year = 0;
    for (int i = 0; i < 4; i++) {
        year = (year * 10) + (userID[i] - '0');
    }
    return year;
}

int extractRollNo(const string& userID) {
    int rollno = 0;
    for (int i = 9; i < 14; i++) {
        rollno = (rollno * 10) + (userID[i] - '0');
    }
    return rollno;
}

int checkBranchCode(const string& userID) {
    string branchCode = userID.substr(4, 5);
    if (branchCode == currentVID.branch) {
        return 1;
    } else {
        return 0;
    }
}

int authenticationCheck() {
    string username, password;
    cout << "\nEnter username: ";
    cin >> username;
    if (username != "Admin") {
        return 0;
    } else {
        cout << "Enter Password: ";
        encode();
        cin >> password;
        decode();
        if (password != "Admin") {
            return 0;
        }
    }
    return 1;
}

void createCandidateFiles() {
    cout << "\nCreating candidate files...\n";
    ofstream fp;
    string filename;
    for (int i = 1; i <= numberOfCandidates; i++) {
        filename = "candidate" + to_string(i) + ".txt";
        fp.open(filename);
        fp << "0\n" << candidates[i - 1].cname;
        fp.close();
    }
    cout << "Created Files successfully\n";
}

int getWinner() {
    int maxV = -1;
    int winnerCid;
    for (int i = 0; i < numberOfCandidates; i++) {
        if (candidates[i].votes > maxV) {
            winnerCid = candidates[i].cid;
            maxV = candidates[i].votes;
        } else if (candidates[i].votes == maxV) {
            return -1;
        }
    }
    return winnerCid;
}

void saveElectionInfoInFile() {
    cout << "Saving Election Info in File...\n";
    ofstream fp("ElectionInfo.txt");
    if (!fp.is_open()) {
        cout << "\nError in file creation\n";
        return;
    }
    fp << currentVID.year << "\n" << currentVID.branch << "\n" << currentVID.totalVoters << "\n" << numberOfCandidates;
    fp.close();
    cout << "Saved Successfully : )";
}

void loadElectionInfoFromFile() {
    ifstream f1("ElectionInfo.txt");
    if (!f1.is_open()) {
        cout << "\nNo Campaign Exists";
        return;
    }
    f1 >> currentVID.year;
    f1.ignore();
    getline(f1, currentVID.branch);
    f1 >> currentVID.totalVoters;
    f1 >> numberOfCandidates;

    // load candidates info and student votes
    for (int i = 0; i < currentVID.totalVoters; i++) {
        studentVotes[i] = '0';
    }
    for (int i = 1; i <= numberOfCandidates; i++) {
        int location;
        string filename = "candidate" + to_string(i) + ".txt";
        ifstream f2(filename);
        candidates[i - 1].cid = i;
        f2 >> candidates[i - 1].votes;
        f2.ignore();
        getline(f2, candidates[i - 1].cname);
        while (f2 >> location) {
            studentVotes[location - 1] = i + '0';
        }
        f2.close();
    }
    f1.close();
}

int isValid(const string& userID) {
    if (userID.length() != 14) {
        return 0;
    }

    int inputedYear = extractYear(userID);
    int inputedRollNo = extractRollNo(userID);

    if (inputedYear != currentVID.year || checkBranchCode(userID) != 1 || inputedRollNo > currentVID.totalVoters) {
        return 0;
    }

    return 1;
}

int isVoted(const string& userID) {
    int location = extractRollNo(userID);
    if (studentVotes[location - 1] == '0') {
        return 0;
    } else {
        return 1;
    }
}

void saveVote(const string& userID, char voteInput) {
    string filename = "candidate" + to_string(voteInput - '0') + ".txt";
    ofstream fp(filename, ios::app);
    int location = extractRollNo(userID);
    studentVotes[location - 1] = voteInput;
    candidates[voteInput - '1'].votes++;
    fp << "\n" << location;
    fp.close();
}

void studentPanel() {
    string userID;
    char voteInput;
    while (1) {
        cout << "\n\n  To exit press 0";
        cout << "\n  Enter user ID: ";
        cin >> userID;
        if (userID == "0") {
            return;
        }
        if (isValid(userID) != 1) {
            cout << "\n  Invalid User ID(Press Enter)";
            cin.ignore();
            cin.ignore();
            continue;
        }
        if (isVoted(userID) != 0) {
            cout << "\n  Your PRN entered is already voted\n  Contact Admin for furthur query...(Press Enter to continue";
            cin.ignore();
            cin.ignore();
            continue;
        }
        cout << "\n\n  Candidates for election:";
        for (int i = 0; i < numberOfCandidates; i++) {
            cout << "\n  " << i + 1 << ". " << candidates[i].cname;
        }
        cout << "\n\n  Your Vote(Enter Number):";
        cin >> voteInput;
        if (voteInput - '0' < 1 || voteInput - '0' > numberOfCandidates) {
            cout << "\nInvalid Vote\nPress Enter to Try Again...";
            cin.ignore();
            cin.ignore();
            continue;
        }
        saveVote(userID, voteInput);
        cout << "\n\nThanks for your precious vote(Press Enter)";
        cin.ignore();
        cin.ignore();
    }
}

void initiateNewElection() {
    cout << "\n New Election Creation \n";

    cout << "\nElection for year: ";
    cin >> currentVID.year;
    cout << "\nElection for branch: ";
    cin >> currentVID.branch;
    cout << "\nTotal Students (in the year and branch): ";
    cin >> currentVID.totalVoters;

    for (int i = 0; i < currentVID.totalVoters; i++) {
        studentVotes[i] = '0';
    }

    do {
        cout << "\nEnter the number of Candidates (Min: 2,Max: 5): ";
        cin >> numberOfCandidates;
    } while (numberOfCandidates < 2 || numberOfCandidates > 5);

    for (int i = 0; i < numberOfCandidates; i++) {
        candidates[i].cid = i + 1;
        cout << "Enter the name of the Candidate " << i + 1 << ": ";
        cin >> candidates[i].cname;
        candidates[i].votes = 0;
    }
}

void adminPanel() {
    while (1) {
        if (authenticationCheck() != 1) {
            cout << "Invalid Username/Password! Try Again!";
            break;
        }

        cout << "Login Successful! You can continue... (Press Enter)";
        cin.ignore();
        cin.ignore();

        while (1) {
            char input;
            cout << "\n1. New Election\n2. Current Election\n3. Result\n4. Logout\nOption: ";
            cin >> input;

            switch (input) {
                case '1':
                    initiateNewElection();
                    saveElectionInfoInFile();
                    createCandidateFiles();
                    break;
                case '2':
                    loadElectionInfoFromFile();
                    break;
                case '3': {
                    int totalVoted = 0;
                    int WinnerCid = getWinner();
                    if (WinnerCid != -1) {
                        cout << "\nWinner is " << candidates[WinnerCid - 1].cname << " with " << candidates[WinnerCid - 1].votes << " votes\n";
                    } else {
                        cout << "\nIts A TIE";
                    }
                    cout << "\nFull Result\n";
                    for (int i = 0; i < numberOfCandidates; i++) {
                        totalVoted += candidates[i].votes;
                        cout << i + 1 << ". " << candidates[i].cname << " -> " << candidates[i].votes << " votes\n";
                    }
                    cout << "\nVoting Percentage: " << (totalVoted * 100) / currentVID.totalVoters << " %\n\n";
                    break;
                }
                case '4':
                    return;
                    break;
                default:
                    cout << "Invalid Option! Press Enter to continue...";
                    cin.ignore();
                    cin.ignore();
            }
        }
    }
}

int main() {
    while (1) {
        cout << "\n\t\t\t   1.Student panel \n\t\t\t   2.Admin panel \n\t\t\t   3.Exit \n\t\t\t   Option:";
        char input;
        cin >> input;

        switch (input) {
            case '1':
                studentPanel();
                break;
            case '2':
                adminPanel();
                break;
            case '3':
                return 0;
            default:
                cout << "\nInvalid option...(Press Enter to continue)";
                cin.ignore();
                cin.ignore();
        }
    }
    return 0;
}