# Poisson Distribution Analysis Project

## Overview
This is a C++ educational project for statistical analysis using the Poisson distribution. The project contains two command-line programs that analyze data from `datensumme.txt` and compare frequency distributions with Poisson distribution predictions.

## Project Structure
- `poisson.cc` - Program for analyzing data frequencies and comparing with Poisson distribution
- `likelihood.cc` - Program for Maximum Likelihood estimation and likelihood-ratio testing
- `datensumme.txt` - Input data file containing 234 numerical values
- `Makefile` - Build configuration for compiling both programs
- `README.md` - Original project instructions (in German)

## Current State
The project has been set up in the Replit environment with:
- C++ toolchain (Clang 14) installed
- Makefile configured to compile both programs
- Build workflow that automatically compiles the programs
- Both programs compile successfully (with expected warnings for unimplemented functions)

## How to Use

### Building the Programs
The programs are automatically compiled when you start the Replit. To manually rebuild:
```bash
make all
```

To clean build artifacts:
```bash
make clean
```

### Running the Programs
After building, run the programs from the terminal:
```bash
./poisson
```
or
```bash
./likelihood
```

## Project Goals (from README)
1. **poisson.cc**: Count frequency of values 0-10 in the data, compare with Poisson distribution predictions
2. **likelihood.cc**: Use Maximum Likelihood method to estimate μ parameter and test Poisson hypothesis

## Recent Changes
- 2025-11-05: Initial Replit environment setup
  - Added Makefile for C++ compilation
  - Updated .gitignore for C++ project artifacts
  - Configured build workflow
  - Created project documentation

## Technical Notes
- Uses C++11 standard
- Compiler: Clang++ with warnings enabled
- The student code currently contains stub implementations that need to be completed
- Programs read from `datensumme.txt` which contains 234 integer values
