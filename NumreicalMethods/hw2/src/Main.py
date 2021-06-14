import numpy as np
import random
import math

from Jacobi import jacobi
from Matrices import *
from Seidel import seidelIterations
from Relaxation import relaxation
from Gradient import gradient
from Gauss import gaussFunc

EPS = 0.000001
MAX_ITERATIONS = 1000000
OMEGA = 0.5

print("Diagonal matrix:")
print("Exact solution:")
print(np.linalg.solve(diag_A, diag_b))
print("\nJacobi solution:")
jacobi(diag_A, diag_b, EPS, MAX_ITERATIONS)
print("\nSeidel solution:")
seidelIterations(diag_A, diag_b, EPS, MAX_ITERATIONS)
print("\nRelaxation solution:")
relaxation(diag_A, diag_b, OMEGA, EPS, MAX_ITERATIONS)
print("\nGradient solution:")
gradient(*symmetric(diag_A, diag_b), EPS, MAX_ITERATIONS)
print("\nGaussian solution:")
print(gaussFunc(addColumn(diag_A, diag_b2)))

print("\n\n\nRandom matrix:")
print("Exact solution:")
print(np.linalg.solve(random_A, random_b))
print("\nJacobi solution:")
jacobi(random_A, random_b, EPS, MAX_ITERATIONS)
print("\nSeidel solution:")
seidelIterations(*symmetric(random_A, random_b), EPS, MAX_ITERATIONS)
print("\nRelaxation solution:")
relaxation(*symmetric(random_A, random_b), OMEGA, EPS, MAX_ITERATIONS)
print("\nGradient solution:")
gradient(*symmetric(random_A, random_b), EPS, MAX_ITERATIONS)
print("\nGaussian solution:")
print(gaussFunc(addColumn(random_A, random_b2)))

print("\n\n\nHilbert matrix:")
print("Exact solution:")
print(np.linalg.solve(hilbert_A, hilbert_b))
print("\nJacobi solution:")
jacobi(hilbert_A, hilbert_b, EPS, MAX_ITERATIONS)
print("\nSeidel solution:")
seidelIterations(*symmetric(hilbert_A, hilbert_b), EPS, MAX_ITERATIONS)
print("\nRelaxation solution:")
relaxation(*symmetric(hilbert_A, hilbert_b), OMEGA, EPS, MAX_ITERATIONS)
print("\nGradient solution:")
gradient(*symmetric(hilbert_A, hilbert_b), EPS, MAX_ITERATIONS)
print("\nGaussian solution:")
print(gaussFunc(addColumn(hilbert_A, hilbert_b2)))
