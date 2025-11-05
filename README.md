
You can find this assignment on github:
<https://classroom.github.com/g/GBlMdMbp>.

Compare the frequency of the numbers in **datensumme.txt** with the
predictions of the Poisson distribution. Please write your code in the
file: **poisson.cc**

Using a **std::vector<int>**, count how often the values $k$ from 0
to 10 appear in the file. To do this, include the corresponding
header file with

    #include<vector>
    using namespace std;

Then create a vector object with eleven
entries: `vector<int> zaehler(11);` Then read all $N = 234$
numerical values $n_i$ from **datensumme.txt** and each time increase the
corresponding entry in the vector:

    zaehler[zahl] += 1;

At the end, print all entries in the vector `zaehler`.

Now create a file **hist.txt** with the results from a) in
the format:

    0 12
    1 23
    2 53
    ...

Display the values as a histogram by starting **gnuplot** in the
terminal and, in the program, entering

    plot "./hist.txt"  smooth freq with boxes

(Type `quit` to exit **gnuplot**.) Alternatively, you can use an
online version of gnuplot: <http://gnuplot.respawned.com/>.
Copy your data values into the upper text window and enter the
following into the lower one:

    set terminal svg size 400,300 enhanced fname 'arial'  fsize 10 butt solid
    set output 'out.svg'
    plot  "data.txt" using 1:2 smooth freq with boxes

Write a function `double poisson(double mu, int k)`, which computes the
Poisson probability $P(k,\mu) =  \frac{\mu^k e^{-\mu}}{k!}$.
Use the function `double exp(double x)` from **cmath** as the implementation
of the exponential function and the function
`double pow(double x, double k)` for $x^k$. You can compute the factorial via
the gamma function $k! = \Gamma(k+1)$ (`double tgamma(double x)` in
**cmath**).
Now write a new file **histpoi.txt**, which in a third
column contains the expectation from the Poisson distribution
$N \cdot P(k, \mu)$. Use the mean value from sheet 2 as $\mu$ of the
Poisson distribution (3.11538).
Compare the values and the predictions with **gnuplot**:\
`plot "./histpoi.txt" using 1:2, "./histpoi.txt" using 1:3 smooth freq with boxes`

We now want to estimate the value of $\mu$ from the data using the
[maximum likelihood method](https://en.wikipedia.org/wiki/Maximum_likelihood_estimation).
We also want to quantify the agreement with the
Poisson hypothesis. For this we use the
log-likelihood function
([likelihood-ratio test](https://en.wikipedia.org/wiki/Likelihood-ratio_test))
and its relation to the $\chi^2$ distribution. Please write your
code in the file: **likelihood.cc**

First compute the total probability of obtaining the 234 numerical
values $n_i$: $\mathcal{L}(\mu) = \prod_{i=1}^{234} P(n_i,\mu)$, assuming
that the Poisson distribution hypothesis is correct. To do this, store all
values from "datensumme.txt" in a vector **std::vector<int>
daten**.
Use **daten.push\_back(zahl)** to add the value of the variable
**zahl** to the vector.
Now write a function
`double prob(std::vector<int> daten, double mu)`, which computes the likelihood,
i.e. the probability
$\mathcal{L}(\mu) = \prod_i   \frac{\mu^{k_i}e^{-\mu}}{k_i!}$ of obtaining
the data for a given $\mu$.

To iterate over the values in **daten**, use:

    for(int k : daten) {
      ...
    }

Print the probability for $\mu = 3.11538$ (the sample mean).
The result should be $7.76841\cdot 10^{-195}$.

Now, for $\mu$ values between 0 and 6, write a file
"likelihood.txt" with the value pairs $\mu$ and $\mathcal{L}(\mu)$.
Scan $\mu$ with a step size of 0.1. Display the
values as a graph by starting **gnuplot** in the terminal and entering
in the program `plot "likelihood.txt"  with line`. (Use `quit`
to exit **gnuplot**.)
Decrease the step size to obtain a nicer plot. What
do you see?
Find the best estimate for $\mu$ from the maximum of the likelihood.
(With `plot [xmin:xmax] "likelihood.txt"  with line` you can display only a
section in $x$ of the graph.)

Now write a second file "nll.txt" with the value pairs $\mu$
and $- 2\ln \mathcal{L}(\mu)$, the negative log-likelihood. Use
the `log` function from **cmath**. Also create a graph for these values
with **gnuplot**.

The sample mean should be a good estimate for $\mu$.
Now, when writing the file "deltanll.txt", subtract
$-2\ln \mathcal{L}(3.11538)$ from the negative log-likelihood
$- 2\ln \mathcal{L}(\mu)$. Again create a graph with
**gnuplot**.
With `plot [xmin:xmax][ymin:ymax] "deltanll.txt"  with line` you can
display only a section of the graph.
Find the best estimate for $\mu$ from the minimum of the negative
log-likelihood. Determine the error on the estimated
$\mu$ value by finding the interval in which
$- \ln \mathcal{L}(\mu)$ is less than 1.0 larger than at the minimum.

Because this total probability becomes smaller and smaller the more
numerical values are considered, one divides this likelihood for a
Poisson distribution with $\mu = 3.11538$ by the best possible
Poisson probability, namely the one obtained when for each individual number
$\mu = n_i$ is assumed. Compute the likelihood ratio:
$\Lambda = \prod_{i=1}^{234} P(n_i,\mu)/\prod_{i=1}^{234} P(n_i,n_i)$
and output the value.
If the Poisson distribution hypothesis is correct, then $-2\ln \Lambda$
should be distributed according to a
[$\chi^2$ distribution](https://en.wikipedia.org/wiki/Chi-squared_distribution)
with $n_\textrm{dof} = 233$ degrees of freedom. For a number
of degrees of freedom greater than 100, the $\chi^2$ distribution should
be well approximated by a normal distribution with mean $n_\textrm{dof}$
and standard deviation $\sqrt{2n_\textrm{dof}}$. Compute the relative
deviation of your likelihood ratio from the mean:
$z = \frac{2\ln \Lambda - n_\textrm{dof}}{\sqrt{2n_\textrm{dof}}}$.
Use the `sqrt` function from **cmath**.
