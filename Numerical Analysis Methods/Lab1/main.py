import numpy as np
#import matplotlib.pyplot as plt

e = 10 ** -7


# x = np.arange(-2.5, 3.75, 0.01)
# plt.plot(x, (3 ** x) - 5 * (x ** 2) + 1, [-2, 2], [0, 0], [0, 0], [-15, 5])
# plt.grid(True)
# plt.show()

def f(x):
    return 3 ** x - 5 * x ** 2 + 1


a = -1
b = 0
k = 0

while abs(b - a) > 0.2:
    x = (a + b) / 2
    if f(x) * f(a) < 0:
        b = x
    else:
        a = x
    print("k = ", k)
    print("a = ", a, " b = ", b)
    print("f(a) = ", f(a), " f(b) = ", f(b))
    print("(a + b) / 2 = ", (a + b) / 2)
    print("b - a = ", b - a, '\n')
    k += 1


def phi(x):
    return - np.sqrt((3 ** x + 1) / 5)


print("MPI: ")
xZero = -0.5625
accuracy = abs(phi(xZero) - xZero)
x = xZero
k = 0
while accuracy >= e:
    temp = x
    x = phi(x)
    accuracy = abs(x - temp)
    print("k = ", k)
    print("x = ", x)
    print("x[k] - x[k - 1] = ", accuracy)
    k += 1


def df(x):
    return np.log(3) * 3 ** x - 10 * x


print("\nNewton Method: ")
xZero = -0.5625
accuracy = abs(f(xZero) / df(xZero))
x = xZero
k = 0

while accuracy >= e:
    temp = x
    x = x - f(x) / df(x)
    accuracy = abs(x - temp)
    print("k = ", k)
    print("x = ", x)
    print("x[k] - x[k - 1] = ", accuracy)
    k += 1

def d2f(x):
    return np.log(3) ** 2 * 3 ** x - 10


print("\nСhebyshev Third Order Method: ")
xZero = -0.5625
accuracy = abs(f(xZero) / df(xZero) + (d2f(xZero) * f(xZero) ** 2) / (2 * df(xZero ** 2) ** 3))
x = xZero
k = 0

while accuracy >= e:
    temp = x
    x = x - f(x) / df(x) - (d2f(x) * f(x) ** 2) / (2 * df(x ** 2) ** 3)
    accuracy = abs(x - temp)
    print("k = ", k)
    print("x = ", x)
    print("x[k] - x[k - 1] = ", accuracy)
    k += 1
