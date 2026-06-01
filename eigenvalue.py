import numpy as np
print(np.__version__)

np.linalg.eigh
a = np.array([[2, 0, 0], [0, 2, 0], [0, 0, 2]])
eigenvalues, eigenvectors = np.linalg.eigh(a)
print(eigenvalues)
print(eigenvectors)
