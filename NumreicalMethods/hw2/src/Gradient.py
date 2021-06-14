import numpy as np

def gradient(A, b, eps, maxIterations):
  m = len(A)
  xk = np.zeros(m)
  rk = b - np.dot(A, xk)
  zk = rk

  for k in range(maxIterations):
    a = np.dot(rk, rk) / np.dot(np.dot(A, zk), zk)
    x = xk + a * zk
    r = rk - a * np.dot(A, zk)
    beta = np.dot(r, r) / np.dot(rk, rk)
    z = r + zk * beta
    print(f"{k}-th iteration:")
    print(xk)
    if np.linalg.norm(np.dot(A, xk) - b) <= eps * np.linalg.norm(b):
      print("^^^^^^^^^^^^^^")
      print(">> Малость невязки << Solution found")
      return
    if np.linalg.norm(x - xk) <= eps * np.linalg.norm(xk):
      print("^^^^^^^^^^^^^^")
      print(">> Малость нормы приближений << Solution found")
      return
    xk, rk, zk = x, r, z

  print("Number of iterations exceeded")
