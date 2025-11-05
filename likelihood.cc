#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <iomanip>

static double logL_mu(const std::vector<int>& data, double mu) {
    if (mu <= 0.0) return -std::numeric_limits<double>::infinity();
    double s = 0.0;
    for (int n : data) {
        s += n * std::log(mu) - mu - std::lgamma(n + 1.0);
    }
    return s;
}

int main() {
    std::ifstream fin("datensumme.txt");
    if (!fin) { std::cerr << "ERROR: cannot open datensumme.txt\n"; return 1; }
    std::vector<int> data; data.reserve(300);
    int v; while (fin >> v) data.push_back(v);
    if (data.empty()) { std::cerr << "ERROR: no data read\n"; return 1; }

    double mu_min = 0.1, mu_max = 10.0, step = 0.01;
    double best_mu = mu_min, best_logL = -std::numeric_limits<double>::infinity();
    for (double mu = mu_min; mu <= mu_max + 1e-12; mu += step) {
        double ll = logL_mu(data, mu);
        if (ll > best_logL) { best_logL = ll; best_mu = mu; }
    }

    std::ofstream like_out("likelihood.txt");
    std::ofstream nll_out("nll.txt");
    if (!like_out || !nll_out) {
        std::cerr << "ERROR: cannot write likelihood.txt or nll.txt\n"; return 1;
    }
    like_out.setf(std::ios::fixed); nll_out.setf(std::ios::fixed);
    like_out << std::setprecision(6);
    nll_out  << std::setprecision(6);

    for (double mu = mu_min; mu <= mu_max + 1e-12; mu += step) {
        double ll = logL_mu(data, mu);
        double rel = std::exp(ll - best_logL);   
        double nll = -2.0 * (ll - best_logL);    
        like_out << mu << " " << rel << "\n";
        nll_out  << mu << " " << nll << "\n";
    }

    std::cout.setf(std::ios::fixed);
    std::cout << std::setprecision(5) << best_mu << "\n";
    return 0;
}
