#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cctype>

using namespace std;

void help() {
    cout << "Command list:" << endl;
    cout << "\tprint" << endl;
    cout << "\tcols" << endl;
    cout << "\tsearch *|col_name val" << endl;
    cout << "\tmin col_name" << endl;
    cout << "\tmax col_name" << endl;
    cout << "\tavg col_name" << endl;
}

void cols(string file) {
    ifstream csv;
    csv.open(file);
    string line, col;
    getline(csv,line);
    istringstream iss(line);
    while (getline(iss, col, ',')) {
        cout << col << endl;
    }
    csv.close();
}

// void print(string file, int colW) { 
//     ifstream csv;
//     csv.open(file);
//     string line, col;
//     while (getline(csv, line)) {
//             istringstream iss(line);
//             while (getline(iss, col, ',')) {
//                 cout << setw(colW) << col;
//             }
//             cout << endl;
//     }
//     csv.close();
// }

void print(string arr[][50], int colW, int countC, int j) { 
    for (int i = 0; i < j; ++i) {
            for (int k = 0; k < countC; ++k) {
                cout << setw(colW) << arr[i][k];
            }
            cout << endl;
        }
}

void search(string arr[][50], int colW, string colN, string value, int countC, int rows) {
    int num;
    int occured = 0;
    if (colN != "*") {
    for (int i=0; i<countC; i++) {
        if (arr[0][i] == colN) {
            occured = 1;
        }
    }
    }else {
        occured = 1;
    }
    if (occured != 1) {
        cout << "Invalid column \"" << colN << "\""<< endl;
        return;
    }
    if (colN != "*") {
    for (int i=0; i<countC; i++) {
        if (arr[0][i] == colN) {
            num = i;
        }
    }
    int data=0;
    int occured = 0;
    for (int i=1; i<rows; i++) {
        if (arr[i][num] == value && value.length() > 0) {
            occured += 1;
            if (data==0) {
            for (int j=0; j<countC; j++) {
                cout << setw(colW) << arr[0][j];
            }
            cout << endl;
            }
            data = i;

            for (int j=0; j<countC; j++) {
                cout << setw(colW) << arr[data][j];
            }
            cout << endl;
        }else if (arr[i][num] == value && value == "") {
                occured += 1;
                if (data==0) {
                for (int j=0; j<countC; j++) {
                    cout << setw(colW) << arr[0][j];
                }
                cout << endl;
                }
                data = i;

                for (int j=0; j<countC; j++) {
                    cout << setw(colW) << arr[data][j];
                }
                cout << endl;
            }
    }
    if (occured == 0) {
        cout << "No results" << endl;
    }
    //////////
    } else {
    int data=0;
    int occured = 0;
    int redo = 0;
    for (int i=1; i<rows; i++) {
        redo = 0;
        for (int k=0; k<countC; k++) {
            if (arr[i][k] == value && value.length() > 0) {
                occured += 1;
                if (data==0) {
                for (int j=0; j<countC; j++) {
                    cout << setw(colW) << arr[0][j];
                }
                cout << endl;
                }
                data = i;
                if (redo == 0) {
                    redo +=1;
                    for (int j=0; j<countC; j++) {
                        cout << setw(colW) << arr[data][j];
                    }
                    cout << endl;
                }
            }
            else if (arr[i][k] == value && value == "") {
                occured += 1;
                if (data==0) {
                for (int j=0; j<countC; j++) {
                    cout << setw(colW) << arr[0][j];
                }
                cout << endl;
                }
                data = i;
                if (redo ==0) {
                    redo +=1;
                    for (int j=0; j<countC; j++) {
                        cout << setw(colW) << arr[data][j];
                    }
                    cout << endl;
                }
                
            }
        }
    }
    if (occured == 0) {
        cout << "No results" << endl;
    }
    }
}

void min(string arr[][50], string colN, int rows, int countC) {
    int occured = 0;
    int num;
    for (int i=0; i<countC; i++) {
        if (arr[0][i] == colN) {
            num = i;
            occured = 1;
        }
    }
    if (occured == 0) {
        cout << "Invalid column \"" << colN << "\"" << endl;
        return;
    }
    double min = 999999999;
    for (int j = 1; j<rows; j++) {
        if (!arr[j][num].empty() && stod(arr[j][num]) < min) min = stod(arr[j][num]);
    }
    if (min == 999999999) {
        cout << "The min for col \"" << arr[0][num] << "\" = " << "N/A" << endl;
        return;
    }
    cout << "The min for col \"" << arr[0][num] << "\" = " << min << endl;
}

void max(string arr[][50], string colN, int rows, int countC) {
    int num;
    int occured = 0;
    for (int i=0; i<countC; i++) {
        if (arr[0][i] == colN) {
            num = i;
            occured = 1;
        }
    }
    if (occured == 0) {
        cout << "Invalid column \"" << colN << "\"" << endl;
        return;
    }
    double max = -999999999;
    for (int j = 1; j<rows; j++) {
        if (!arr[j][num].empty() && stod(arr[j][num]) > max) max = stod(arr[j][num]);
    }
    if (max == -999999999) {
        cout << "The max for col \"" << arr[0][num] << "\" = " << "N/A" << endl;
        return;
    }
    cout << "The max for col \"" << arr[0][num] << "\" = " << max << endl;
}

// void min(string arr[][50], string colN, int rows, int countC) {
//     int num;
//     for (int i=0; i<countC; i++) {
//         if (arr[0][i] == colN) {
//             num = i;
//         }
//     }
//     string min = arr[1][num];
//     for (int j = 2; j<=rows; j++) {
//         if (arr[j][num] == "\0") continue;
//         if (arr[j][num] < min) min = arr[j][num];
//     }
//     cout << "The min for col \"" << arr[0][num] << "\" = " << min << endl;
// }

// void max(string arr[][50], string colN, int rows, int countC) {
//     int num;
//     for (int i=0; i<countC; i++) {
//         if (arr[0][i] == colN) {
//             num = i;
//         }
//     }
//     string max = arr[1][num];
//     for (int j = 1; j<=rows; j++) {
//         if (arr[j][num] > max && !arr[j][num].empty()) max = arr[j][num];
//     }
//     cout << "The max for col \"" << arr[0][num] << "\" = " << max << endl;
// }

void avg(string arr[][50], string colN, int rows, int countC) {
    int num;
    int newRow = rows;
    for (int i=0; i<countC; i++) {
        if (arr[0][i] == colN) {
            num = i;
            break;
        }
        if (i==countC-1) {
            cout << "Invalid column \"" << colN << "\"" << endl;
            return;
        }
    }
    double sum = 0;
    for (int j = 1; j<=rows; j++) {
        if (!arr[j][num].empty()) {
        sum += stod(arr[j][num]);
        }
        if (arr[j][num].empty()) newRow = newRow-1;
    }
    
    if (sum==0) {
        cout << "The avg for col \"" << arr[0][num] << "\" = " << "N/A" << endl;
        return;
    }
    double avg = sum / (newRow);
    cout << "The avg for col \"" << arr[0][num] << "\" = " << avg << endl;
}

int main(int argc, char* argv[]) {
    ifstream csv;
    if (argc != 3) {
        cout << "Usage: ./a database.csv #col_width" << endl;
        return 1;
    }
    int colW = atoi(argv[2]);
    csv.open(argv[1]);

    string file = argv[1];
    if (!csv.is_open()) {
        cout << "Failed to open \"" << argv[1] << "\"" << endl;
        return 0;
    }
    string arr[5000][50];
    string line;
    getline(csv, line);
    istringstream column(line);
    int countC = 0;
    while (getline(column, arr[0][countC], ',')) {
        countC += 1;
    }
    string row;
    int j=1;
    while (getline(csv, row)) {
        istringstream data(row);
        for (int i=0; i<=countC; i++) {
            // if (getline(data, arr[j][i], ',')) {
            
            // } else {
            //     arr[j][countC] = "\0";
            // }
            getline(data, arr[j][i], ',');
        }
        j++;
    }
    int rows = j;
    while (1) {
        cout << "Enter a command or \"help\" for a command list: " << endl;
        string cmd;
        cin >> cmd;
        if (cmd == "quit") break;

        else if (cmd == "help") {
            help();
        }
        else if (cmd == "cols") {
            cols(file);
        }
        else if (cmd == "print") {
            print(arr, colW, countC, j);
        }
        else if (cmd == "search") {
            string colN;
            cin >> quoted(colN);
            string value;
            cin >> quoted(value);
            search(arr, colW, colN, value, countC, rows);
        }
        else if (cmd == "min") {
            string colN;  
            cin >> quoted(colN);
            min(arr, colN, rows, countC);
        }
        else if (cmd == "max") {
            string colN;
            cin >> quoted(colN);
            max(arr, colN, rows, countC);
        }
        else if (cmd == "avg") {
            string colN;
            cin >> quoted(colN);
            avg(arr, colN, rows, countC);
        }
        else {
            cout << "Invalid command" << endl;
        }
    }
    csv.close();

    return 0;
}