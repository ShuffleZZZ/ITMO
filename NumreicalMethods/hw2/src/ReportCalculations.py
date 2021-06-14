import numpy as np

from Matrices import *

print("Determinant of diagonal matrix:")
print(np.linalg.det(diag_A))
diag_A_rev = np.linalg.inv(diag_A)
print("Condition number of diagonal matrix:")
print(np.linalg.norm(diag_A_rev) * np.linalg.norm(diag_A))

print("Determinant of random matrix:")
print(np.linalg.det(random_A))
random_A_rev = np.linalg.inv(random_A)
print("Condition number of random matrix:")
print(np.linalg.norm(random_A_rev) * np.linalg.norm(random_A))

print("Determinant of Hilbert matrix:")
print(np.linalg.det(hilbert_A))
hilbert_A_rev = np.linalg.inv(hilbert_A)
print("Condition number of Hilbert matrix:")
print(np.linalg.norm(hilbert_A_rev) * np.linalg.norm(hilbert_A))
