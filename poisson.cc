#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

double poisson(double mu, int k) {
    return pow(mu, k) * exp(-mu) / tgamma(k + 1);
}

int main() {
    using namespace std;
    vector<int> zaehler(11); //create 11 counters (0-10)

    ifstream fin("datensumme.txt");
    int n_i;
    for(int i = 0 ; i < 234 ; ++i) {
        fin >> n_i;
        zaehler[n_i] += 1; //Add number into the counter
    }

    fin.close();
    
    for(unsigned int k = 0; k < zaehler.size(); ++k) {
        cout << k << ":" << zaehler[k] << endl;
    }//print to terminal



    ofstream fout("hist.txt");
    for(unsigned int k = 0; k < zaehler.size(); ++k) {
        fout << k << " " << zaehler[k] << endl;
    }
    fout.close();

    //Write histpoi.txt with predictions
    double mu = 3.11538;  // mean from sheet 2
    int N = 234;          // total measurements
    
    ofstream fout2("histpoi.txt");
    for(unsigned int k = 0; k < zaehler.size(); ++k) {
        double prediction = N * poisson(mu, k);
        fout2 << k << " " << zaehler[k] << " " << prediction << endl;
    }
    fout2.close();
    
    return 0;
    
}