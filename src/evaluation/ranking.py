import math

EPS = 1e-06

def sign(x):
    return 0 if math.isclose(x, 0, rel_tol=EPS) else 1 if x > 0 else -1

def kendallsTau(x, y):
    count = 0
    for i in range(1, len(x)):
        for j in range(i):
            count += sign(x[i] - x[j]) * sign(y[i] - y[j])
    return 2 * count / (len(x) * (len(x) - 1))