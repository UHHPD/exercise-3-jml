#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

double poisson(double mu, int k)
{
  return pow(mu, k) * exp(-mu) / tgamma(k + 1);
}

int main()
{
  using namespace std;
  vector<int> counter(11);
  ifstream fin("datensumme.txt");
  ofstream hist("hist.txt"), histpoi("histpoi.txt");
  int goal;
  while (fin >> goal)
  {
    counter[goal] += 1;
  }
  for (unsigned int k = 0; k < counter.size(); ++k)
  {
    cout << k << ":" << counter[k] << endl;
    hist << k << "\t" << counter[k] << endl;
    histpoi << k << "\t" << counter[k] << "\t" << 234 * poisson(3.11538, k)
            << endl;
  }
}