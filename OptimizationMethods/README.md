# Optimization methods course

## First task

1. Implement one-dimensional search methods: dichotomy, golden ratio, and Fibonacci. Measure iterations count and function calculations dependent on precision. Show the change of the interval on every iteration.

2. Implement gradient descend method. Measure convergence speed with different one-dimensional search methods for step calculation.

3. Analyze the trajectory of gradient descend on a few quadratic functions. Draw the graphs with level lines and trajectory. How the behavior of the method depends on the function's condition number, starting point, and step calculation.

4. Analyze the number of iterations of gradient descend dependent on condition number and amount of dimensions. For given _n_ and _k_ generate a quadratic problem of _n_ size with condition number _k_ and launch gradient descend with fixed precision. Measure the number of iterations until the convergence.

## Second task

1. Implement one of the conjugate directions methods and the Newton method.

2. Analyze the solutions on given functions:
    - quadratic function: $100 * (x_2 - x_1)^2 + (1 - x_1)^2$
    - Rosenbrock function: $100 * (x_2 - x_1)^2 + (1 - x_1)^2$
    Find the maximum of following function: $f(x, y) = 2 * exp(-((x - 1) / 2)^2 - (y - 1)^2) + 3 * exp(-((x - 2) / 3)^2 - ((y - 3) / 2)^2)$ with different starting points (not less than 5).

3. Analyze and compare the convergence of both methods with the gradient descend. Compare convergence speed, reliability, and resources (RAM, number of operations, lead time).

4. Draw the trajectory of different algorithms from the same starting point and with the same precision.

## Third task

1. Implement simplex-method to solve linear programming problems.
