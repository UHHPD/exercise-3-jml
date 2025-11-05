#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    vector<int> zaehler(11, 0); 

    ifstream fin("datensumme.txt");
    if (!fin.is_open()) {
        cerr << "Error: could not open datensumme.txt" << endl;
        return 1;
    }

    int zahl;
    while (fin >> zahl) {
        if (zahl >= 0 && zahl <= 10) {
            zaehler[zahl] += 1;
        }
    }

    fin.close();

    for (unsigned int k = 0; k < zaehler.size(); ++k) {
        cout << k << " : " << zaehler[k] << endl;
    }

    return 0;
}
