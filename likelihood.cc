#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

// Poisson probability: P(k, mu) = mu^k * e^(-mu) / k!
double poisson(double mu, int k) {
    if (mu <= 0) return 0.0;

    // Calculate mu^k * e^(-mu) / k!
    double result = exp(-mu);  // e^(-mu)

    // Multiply by mu^k / k! iteratively to avoid overflow
    for (int i = 1; i <= k; i++) {
        result *= mu / i;
    }

    return result;
}

// Compute likelihood L(mu) = product of P(k_i, mu) for all data points
double prob(std::vector<int> daten, double mu) {
    double likelihood = 1.0;

    for (int k : daten) {
        likelihood *= poisson(mu, k);
    }

    return likelihood;
}

// Compute log-likelihood (more numerically stable)
double log_likelihood(std::vector<int> daten, double mu) {
    double log_L = 0.0;

    for (int k : daten) {
        // log(P(k, mu)) = -mu + k*log(mu) - log(k!)
        log_L += -mu + k * log(mu);

        // Subtract log(k!)
        for (int i = 1; i <= k; i++) {
            log_L -= log(i);
        }
    }

    return log_L;
}

// Compute saturated likelihood (mu = k for each data point)
double saturated_log_likelihood(std::vector<int> daten) {
    double log_L_sat = 0.0;

    for (int k : daten) {
        if (k > 0) {
            // For mu = k: log(P(k, k)) = -k + k*log(k) - log(k!)
            log_L_sat += -k + k * log(k);

            // Subtract log(k!)
            for (int i = 1; i <= k; i++) {
                log_L_sat -= log(i);
            }
        }
    }

    return log_L_sat;
}

int main() {
    using namespace std;

    // a) Read data from file into vector
    ifstream fin("datensumme.txt");
    vector<int> daten;
    int n_i;

    for(int i = 0; i < 234; i++) {
        fin >> n_i;
        daten.push_back(n_i);
    }
    fin.close();

    cout << "Loaded " << daten.size() << " data points." << endl;

    // Compute likelihood for mu = 3.11538 (sample mean)
    double mu_mean = 3.11538;
    double L_mean = prob(daten, mu_mean);

    cout << "L(mu=" << mu_mean << ") = " << L_mean << endl;
    cout << "This should be approximately 7.76841e-195" << endl;

    // b) Write likelihood values to file
    ofstream fout_likelihood("likelihood.txt");
    for (double mu = 0.1; mu <= 6.0; mu += 0.01) {
        double L = prob(daten, mu);
        fout_likelihood << mu << " " << L << endl;
    }
    fout_likelihood.close();
    cout << "Wrote likelihood.txt" << endl;

    // c) Write negative log-likelihood to file
    ofstream fout_nll("nll.txt");
    for (double mu = 0.1; mu <= 6.0; mu += 0.01) {
        double nll = -2.0 * log_likelihood(daten, mu);
        fout_nll << mu << " " << nll << endl;
    }
    fout_nll.close();
    cout << "Wrote nll.txt" << endl;

    // d) Write delta NLL and find minimum
    double nll_at_mean = -2.0 * log_likelihood(daten, mu_mean);

    ofstream fout_deltanll("deltanll.txt");
    double mu_best = mu_mean;
    double min_deltanll = 0.0;

    for (double mu = 0.1; mu <= 6.0; mu += 0.01) {
        double nll = -2.0 * log_likelihood(daten, mu);
        double deltanll = nll - nll_at_mean;
        fout_deltanll << mu << " " << deltanll << endl;

        // Find minimum
        if (deltanll < min_deltanll) {
            min_deltanll = deltanll;
            mu_best = mu;
        }
    }
    fout_deltanll.close();
    cout << "Wrote deltanll.txt" << endl;

    cout << "\nBest estimate: mu_hat = " << mu_best << endl;

    // Find uncertainty (where delta NLL = 1)
    double mu_lower = 0, mu_upper = 0;
    double nll_min = -2.0 * log_likelihood(daten, mu_best);

    // Search for lower bound
    for (double mu = mu_best; mu >= 0.1; mu -= 0.001) {
        double nll = -2.0 * log_likelihood(daten, mu);
        if (nll - nll_min >= 1.0) {
            mu_lower = mu;
            break;
        }
    }

    // Search for upper bound
    for (double mu = mu_best; mu <= 6.0; mu += 0.001) {
        double nll = -2.0 * log_likelihood(daten, mu);
        if (nll - nll_min >= 1.0) {
            mu_upper = mu;
            break;
        }
    }

    double uncertainty = (mu_upper - mu_lower) / 2.0;
    cout << "Uncertainty from likelihood: +/- " << uncertainty << endl;
    cout << "Interval: [" << mu_lower << ", " << mu_upper << "]" << endl;

    // Compare to sample mean uncertainty
    double sum = 0, sum_sq = 0;
    for (int k : daten) {
        sum += k;
        sum_sq += k * k;
    }
    double mean = sum / daten.size();
    double variance = sum_sq / daten.size() - mean * mean;
    double sigma = sqrt(variance);
    double uncertainty_mean = sigma / sqrt(daten.size());

    cout << "Sample mean: " << mean << endl;
    cout << "Sample std dev: " << sigma << endl;
    cout << "Uncertainty on sample mean: +/- " << uncertainty_mean << endl;

    // e) Likelihood ratio test
    double log_L_mu = log_likelihood(daten, mu_best);
    double log_L_sat = saturated_log_likelihood(daten);
    double minus_2ln_lambda = -2.0 * (log_L_mu - log_L_sat);

    cout << "\n-2 ln(Lambda) = " << minus_2ln_lambda << endl;

    // Compare to chi-squared distribution
    int ndof = 233;  // N - 1 degrees of freedom
    double expected_mean = ndof;
    double expected_sigma = sqrt(2.0 * ndof);
    double z = (minus_2ln_lambda - expected_mean) / expected_sigma;

    cout << "Expected mean (ndof): " << expected_mean << endl;
    cout << "Expected sigma: " << expected_sigma << endl;
    cout << "z-score: " << z << endl;

    if (abs(z) < 2) {
        cout << "The Poisson distribution describes the data well (|z| < 2)." << endl;
    } else {
        cout << "The Poisson distribution may not describe the data well (|z| >= 2)." << endl;
    }

    return 0;
}