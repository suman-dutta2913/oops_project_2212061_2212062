#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>   
#include <windows.h>
using namespace std;

class Airline {
private:
    string Flight, Des, Dep;
    int Seats;
    vector<string> confirmationCodes; 

public:
    Airline(string flight, string des, string dep, int seats) {
        Flight = flight;
        Des = des;
        Dep = dep;
        Seats = seats;
    }

    string getFlight() {
        return Flight;
    }

    string getDes() {
        return Des;
    }

    string getDep() {
        return Dep;
    }

    int getSeat() {
        return Seats;
    }

    string update(string flight, int numSeats) {
        ifstream in("D:/Flight.txt");
        ofstream out("D:/Flight Temp.txt");

        string line;
        string confirmationCode = ""; 
        while (getline(in, line)) {
            int pos = line.find(flight);
            if (pos != string::npos) {
                int current = Seats - numSeats;
                if (current < 0) {
                    cout << "Not enough seats available for reservation!" << endl;
                    return ""; 
                }
                Seats = current;
                stringstream ss;
                ss << current;
                string strCurrent = ss.str();

                int seatPos = line.find_last_of(':');
                line.replace(seatPos + 2, string::npos, strCurrent);
                
                confirmationCode = generateConfirmationCode();
                confirmationCodes.push_back(confirmationCode); 
            }
            out << line << endl;
        }
        out.close();
        in.close();
        remove("D:/Flight.txt");
        rename("D:/Flight Temp.txt", "D:/Flight.txt");
        cout << "Seats Reserved Successfully! Confirmation Code: " << confirmationCode << endl;
        return confirmationCode; 
    }

    bool checkConfirmationStatus(string confirmationCode) {
        
        for (const auto &code : confirmationCodes) {
            if (code == confirmationCode) {
                cout << "Reservation Confirmed!" << endl;
                return true; 
            }
        }
        
        return false; 
    }

private:
    string generateConfirmationCode() {
        const string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const int codeLength = 8;
        string code;
        srand(static_cast<unsigned int>(time(0))); 
        for (int i = 0; i < codeLength; ++i) {
            code += charset[rand() % charset.length()]; 
        }
        return code;
    }
};

void display() {
    ifstream in("D:/Flight.txt");
    if (!in) {
        cout << "Error: File Can't Open!" << endl;
    }
    else {
        string line;
        while (getline(in, line)) {
            cout << line << endl;
        }
    }
}

int main() {
    Airline flight1("F101", "UAE", "England", 50);
    Airline flight2("F202", "UAE", "USA", 40);
    Airline flight3("F303", "UAE", "Canada", 2);

    ofstream out("D:/Flight.txt");
    if (!out) {
        cout << "Error: File can't open!" << endl;
    }
    else {
        out << "\t " << flight1.getFlight() << " : " << flight1.getDes() << " : " << flight1.getDep() << " : " <<
            " : " << flight1.getSeat() << endl << endl;

        out << "\t " << flight2.getFlight() << " : " << flight2.getDes() << " : " << flight2.getDep() <<
            " : " << flight2.getSeat() << endl << endl;

        out << "\t " << flight3.getFlight() << " : " << flight3.getDes() << " : " << flight3.getDep() <<
            " : " << flight3.getSeat() << endl << endl;

        cout << "Data Saved Successfully!" << endl;
        out.close();
    }

    bool exit = false;
    while (!exit) {
        system("cls");
        cout << "\t Welcome To Airline Management System" << endl;
        cout << "\t ************************************" << endl;
        cout << "\t 1. Reserve A Seat" << endl;
        cout << "\t 2. Check Reservation Status" << endl;
        cout << "\t 3. Exit" << endl;
        cout << "\t Enter Your Choice: ";
        int val;
        cin >> val;

        if (val == 1) {
            system("cls");
            display();
            string flight;
            int numSeats;
            cout << "Enter Flight No: ";
            cin >> flight;
            cout << "Enter Number of Seats to Reserve: ";
            cin >> numSeats;

            string confirmationCode;
            if (flight == flight1.getFlight() && flight1.getSeat() >= numSeats) {
                confirmationCode = flight1.update(flight, numSeats);
            }
            else if (flight == flight2.getFlight() && flight2.getSeat() >= numSeats) {
                confirmationCode = flight2.update(flight, numSeats);
            }
            else if (flight == flight3.getFlight() && flight3.getSeat() >= numSeats) {
                confirmationCode = flight3.update(flight, numSeats);
            }
            else {
                cout << "Invalid flight or insufficient seats available." << endl;
            }

            if (!confirmationCode.empty()) {
                cout << "Reservation Confirmed! Confirmation Code: " << confirmationCode << endl;
            }
            Sleep(10000);
        }
        else if (val == 2) {
            system("cls");
            string confirmationCode;
            cout << "Enter Confirmation Code: ";
            cin >> confirmationCode;

            bool status = false;
            if (!flight1.checkConfirmationStatus(confirmationCode) && !flight2.checkConfirmationStatus(confirmationCode) && !flight3.checkConfirmationStatus(confirmationCode)) {
	      status = false;          
            }
            else {		    
              status = true;
            }
            
            if (status) {
                cout << "Reservation found." << endl;
            }
	    else{
		cout<<"Reservation not found"<<endl;
            }
            Sleep(3000);
        }
        else if (val == 3) {
            exit = true;
            cout << "Goodbye!" << endl;
        }
        else {
            cout << "Invalid choice. Please enter a valid option." << endl;
            Sleep(3000);
        }
    }

    return 0;
}
