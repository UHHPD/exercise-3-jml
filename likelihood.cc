#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <iomanip>

using namespace std;

// log-likelihood for a given mu
double logL_mu(const vector<int> &data, double mu) {
    if (mu <= 0.0) return -numeric_limits<double>::infinity();

    double s = 0.0;
    for (int k : data) {
        s += k * log(mu) - mu - lgamma(k + 1.0);  // log(mu^k e^-mu / k!)
    }
    return s;
}

// likelihood L(mu) = exp(log L)
double prob(const vector<int> &data, double mu) {
    return exp(logL_mu(data, mu));
}

int main() {
    // ---- read data ----
    ifstream fin("datensumme.txt");
    if (!fin) {
        cerr << "ERROR: cannot open datensumme.txt\n";
        return 1;
    }

    vector<int> daten;
    daten.reserve(300);
    int v;
    long long sum_k = 0;
    while (fin >> v) {
        daten.push_back(v);
        sum_k += v;
    }
    fin.close();

    if (daten.empty()) {
        cerr << "ERROR: no data read\n";
        return 1;
    }

    const int N = static_cast<int>(daten.size());

    // ---- (a) likelihood at mu = 3.11538 ----
    const double mu_sheet = 3.11538;
    const double L_sheet  = prob(daten, mu_sheet);
    const double logL_sheet = logL_mu(daten, mu_sheet);

    // ---- scan mu from 0 to 6 in steps of 0.1 ----
    const double mu_min = 0.0;
    const double mu_max = 6.0;
    const double step   = 0.1;

    ofstream like_out("likelihood.txt");
    ofstream nll_out("nll.txt");
    ofstream dnll_out("deltanll.txt");

    if (!like_out || !nll_out || !dnll_out) {
        cerr << "ERROR: cannot open output files\n";
        return 1;
    }

    like_out.setf(ios::fixed);
    nll_out.setf(ios::fixed);
    dnll_out.setf(ios::fixed);
    like_out << setprecision(6);
    nll_out  << setprecision(6);
    dnll_out << setprecision(6);

    double best_mu   = mu_min;
    double best_logL = -numeric_limits<double>::infinity();

    for (double mu = mu_min; mu <= mu_max + 1e-12; mu += step) {
        double ll  = logL_mu(daten, mu);
        double L   = exp(ll);
        double nll = -2.0 * ll;

        if (ll > best_logL) {
            best_logL = ll;
            best_mu   = mu;
        }

        // (b) likelihood.txt : mu, L(mu)
        like_out << mu << " " << L << "\n";

        // (c) nll.txt : mu, -2 ln L(mu)
        nll_out << mu << " " << nll << "\n";

        // (d) deltanll.txt : mu, -2 ln L(mu) + 2 ln L(mu_sheet)
        double delta_nll = nll + 2.0 * logL_sheet;  // = -2(ll - logL_sheet)
        dnll_out << mu << " " << delta_nll << "\n";
    }

    like_out.close();
    nll_out.close();
    dnll_out.close();


    double logL_sat = 0.0;
    for (int k : daten) {
        if (k > 0) {
            logL_sat += k * log(static_cast<double>(k))
                        - k
                        - lgamma(k + 1.0);
        } else {

            logL_sat += 0.0;
        }
    }

    double minus2lnLambda = -2.0 * (best_logL - logL_sat);

    int ndof = N - 1;                    // number of degrees of freedom
    double sigma_chi = sqrt(2.0 * ndof);
    double z = (minus2lnLambda - ndof) / sigma_chi;


    cout << scientific << setprecision(6);
    cout << L_sheet << "\n";
    cout << best_mu << "\n";
    cout << minus2lnLambda << "\n";
    cout << z << "\n";

    return 0;
}
