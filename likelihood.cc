#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>

double poisson(double mu, int k) {
    if (mu <= 0.0) return (k == 0) ? 1.0 : 0.0;
    return std::pow(mu, k) * std::exp(-mu) / std::tgamma(k + 1.0);
}

int main() {
    const double mu = 3.11538;
    const int kmin = 0, kmax = 10;

    std::ifstream fin("datensumme.txt");
    if (!fin) {
        std::cerr << "ERROR: cannot open datensumme.txt\n";
        return 1;
    }

    std::vector<int> counts(kmax - kmin + 1, 0);
    int N = 0;
    int x;
    while (fin >> x) {
        if (x >= kmin && x <= kmax) counts[x - kmin] += 1;
        N++;
    }
    fin.close();

    std::ofstream fout("histpoi.txt");
    if (!fout) {
        std::cerr << "ERROR: cannot write histpoi.txt\n";
        return 1;
    }

    fout.setf(std::ios::fixed);
    fout << std::setprecision(6);

    // Write: k  observed_count  N * P(k; mu)
    for (int k = kmin; k <= kmax; ++k) {
        double expected = N * poisson(mu, k);
        fout << k << " " << counts[k - kmin] << " " << expected << "\n";
    }
    fout.close();

    return 0;
}
