#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

vector<string> confirmationCodes;

int Seats;

class Flight {
private:
    string FlightNo, Des, Dep;

public:
    Flight(string flightNo, string des, string dep, int seats) {
        FlightNo = flightNo;
        Des = des;
        Dep = dep;
        Seats = seats;
    }

    string getFlightNo() const {
        return FlightNo;
    }

    string getDes() const {
        return Des;
    }

    string getDep() const {
        return Dep;
    }

    int getSeats() const {
        return Seats;
    }
};

class InternationalFlight : public Flight {
public:
    InternationalFlight(string flightNo, string des, string dep, int seats) : Flight(flightNo, des, dep, seats) {}
    
    string update_International(string flight, int numSeats) {
        ifstream in("D:/International Flight.txt");
        
        ofstream out("D:/International Flight Temp.txt");

        string line;
        string confirmationCode = "";
        while (getline(in, line)) {
            int pos = line.find(flight);
            if (pos != string::npos) {
                int current = getSeats() - numSeats;
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
        remove("D:/International Flight.txt");
        rename("D:/International Flight Temp.txt", "D:/International Flight.txt");
        cout << "Seats Reserved Successfully for International Flight " << flight << "! Confirmation Code: " << confirmationCode << endl;
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

class DomesticFlight : public Flight {
public:
    DomesticFlight(string flightNo, string des, string dep, int seats) : Flight(flightNo, des, dep, seats) {}

    string update_domestic(string flight, int numSeats) {
        ifstream in("D:/Domestic Flight.txt");
        ofstream out("D:/Domestic Flight Temp.txt");

        string line;
        string confirmationCode = "";
        while (getline(in, line)) {
            int pos = line.find(flight);
            if (pos != string::npos) {
                int current = getSeats() - numSeats;
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
        remove("D:/Domestic Flight.txt");
        rename("D:/Domestic Flight Temp.txt", "D:/Domestic Flight.txt");
        cout << "Seats Reserved Successfully for Domestic Flight " << flight << "! Confirmation Code: " << confirmationCode << endl;
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

void display_domestic() {
    ifstream in("D:/Domestic Flight.txt");
    if (!in) {
        cout << "Error: File Can't Open!" << endl;
    } else {
        string line;
        while (getline(in, line)) {
            cout << line << endl;
        }
    }
}


void display_international() {
    ifstream in("D:/International Flight.txt");
    if (!in) {
        cout << "Error: File Can't Open!" << endl;
    } else {
        string line;
        while (getline(in, line)) {
            cout << line << endl;
        }
    }
}



int main() {
    InternationalFlight flight1("F101", "Bhopal", "England", 50);
    DomesticFlight flight2("F202", "New Delhi", "Mumbai", 40);
    DomesticFlight flight3("F303", "Guwahati", "kolkata", 30);
    InternationalFlight flight4("F404", "UAE", "England", 50);
    ofstream out1("D:/Domestic Flight.txt");
    ofstream out2("D:/International Flight.txt");
    if (!out1 || !out2) {
        cout << "Error: File can't open!" << endl;
    } else {
        out2 << "\t " << flight1.getFlightNo() << " : " << flight1.getDes() << " : " << flight1.getDep() << " : " <<
            " : " << flight1.getSeats() << endl << endl;

        out1 << "\t " << flight2.getFlightNo() << " : " << flight2.getDes() << " : " << flight2.getDep() <<
            " : " << flight2.getSeats() << endl << endl;

        out1 << "\t " << flight3.getFlightNo() << " : " << flight3.getDes() << " : " << flight3.getDep() <<
            " : " << flight3.getSeats() << endl << endl;
        out2 << "\t " << flight4.getFlightNo() << " : " << flight4.getDes() << " : " << flight4.getDep() <<
            " : " << flight4.getSeats() << endl << endl;
        

        cout << "Data Saved Successfully!" << endl;
        out1.close();
        out2.close();
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
            cout << "\t 1. Reserve International Flight" << endl;
            cout << "\t 2. Reserve Domestic Flight" << endl;
            cout << "\t Enter Your Choice: ";
            int reserveChoice;
            cin >> reserveChoice;

            // string flight;
            // int numSeats;
            // cout << "Enter Flight No: ";
            // cin >> flight;
            // cout << "Enter Number of Seats to Reserve: ";
            // cin >> numSeats;

            string confirmationCode;
            if (reserveChoice == 1) {
              system("cls");
              display_international();
              string flight;
              int numSeats;
              cout << "Enter Flight No: ";
              cin >> flight;
              cout << "Enter Number of Seats to Reserve: ";
              cin >> numSeats;
              if (flight == flight1.getFlightNo() && flight1.getSeats() >= numSeats) {
                  confirmationCode = flight1.update_International(flight, numSeats);
              } else if (flight == flight4.getFlightNo() && flight4.getSeats() >= numSeats) {
                  confirmationCode = flight4.update_International(flight, numSeats);
              } else {
                  cout << "Invalid flight or insufficient seats available for International Flight." << endl;
              }
              
            } 
            else if (reserveChoice == 2) {
              system("cls");
              display_domestic();
              string flight;
              int numSeats;
              cout << "Enter Flight No: ";
              cin >> flight;
              cout << "Enter Number of Seats to Reserve: ";
              cin >> numSeats;
              if (flight == flight2.getFlightNo() && flight2.getSeats() >= numSeats) {
                  confirmationCode = flight2.update_domestic(flight, numSeats);
              } else if (flight == flight3.getFlightNo() && flight3.getSeats() >= numSeats) {
                  confirmationCode = flight3.update_domestic(flight, numSeats);
              } else {
                  cout << "Invalid flight or insufficient seats available for Domestic Flight." << endl;
              }
            } 
            else {
              cout << "Invalid option selected." << endl;
            }
            

            if (!confirmationCode.empty()) {
                cout << "Reservation Confirmed! Confirmation Code: " << confirmationCode << endl;
            }
            Sleep(7000);
        } else if (val == 2) {
            system("cls");
            string confirmationCode;
            cout << "Enter Confirmation Code: ";
            cin >> confirmationCode;

            bool status = false;
            if (!flight1.checkConfirmationStatus(confirmationCode) &&
                !flight2.checkConfirmationStatus(confirmationCode) &&
                !flight3.checkConfirmationStatus(confirmationCode) &&
                !flight4.checkConfirmationStatus(confirmationCode)) {
                status = false;
            } else {
                status = true;
            }

            if (status) {
                cout << "Reservation found." << endl;
            } else {
                cout << "Reservation not found" << endl;
            }
            Sleep(7000);
        } else if (val == 3) {
            exit = true;
            cout << "Goodbye!" << endl;
        } else {
            cout << "Invalid choice. Please enter a valid option." << endl;
            Sleep(7000);
        }
    }
}
