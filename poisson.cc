#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {

    vector<int> zaehler(11, 0);


    ifstream fin("datensumme.txt");
    if (!fin) {
        cerr << "Error: could not open datensumme.txt" << endl;
        return 1;
    }
    int zahl;
    while (fin >> zahl) {
        if (0 <= zahl && zahl <= 10) {
            zaehler[zahl] += 1;
        }
    }
    fin.close();


    for (unsigned int k = 0; k < zaehler.size(); ++k) {
        cout << k << " : " << zaehler[k] << endl;
    }

    ofstream fout("hist.txt");
    if (!fout) {
        cerr << "Error: could not write hist.txt" << endl;
        return 1;
    }
    for (int k = 0; k <= 10; ++k) {
        fout << k << " " << zaehler[k] << "\n";
    }
    fout.close();

    cout << "Wrote counts to hist.txt" << endl;
    return 0;
}
