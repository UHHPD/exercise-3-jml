CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra

all: poisson likelihood

poisson: poisson.cc
	$(CXX) $(CXXFLAGS) -o poisson poisson.cc

likelihood: likelihood.cc
	$(CXX) $(CXXFLAGS) -o likelihood likelihood.cc

clean:
	rm -f poisson likelihood hist.txt histpoi.txt likelihood.txt nll.txt deltanll.txt

.PHONY: all clean
