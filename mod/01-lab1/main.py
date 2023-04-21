import matplotlib.pyplot as plt
import numpy as np
from math import exp


def exponential_distribution(lmbd, x):
    if x < 0:
        return 0
    return 1 - exp(-lmbd * x)


def exponential_distribution_density(lmbd, x):
    if x < 0:
        return 0
    return lmbd * exp(-lmbd * x)


def uniform_distribution(a, b, x):
    if x < a:
        return 0
    if x >= b:
        return 1
    return (x - a)/(b - a)


def uniform_distribution_density(a, b, x):
    if x < a or x > b:
        return 0
    return 1 / (b - a)


def read_params():
    return float(input("Input a: ")), float(input("Input b: ")), float(input("Input lambda: "))


def uniform_values(a, b, is_density):
    dot_count = 100
    x_dist = (b - a) / 2
    x_start = a - x_dist
    x_end = b + x_dist
    step = (x_end - x_start) / dot_count
    x = []
    y = []
    while x_start <= x_end:
        x.append(x_start)
        if is_density:
            y.append(uniform_distribution_density(a, b, x_start))
        else:
            y.append(uniform_distribution(a, b, x_start))
        x_start += step
    return x, y


def exponential_values(lmbd, is_density):
    dot_count = 100
    x_start = 0
    x_end = 20
    step = (x_end - x_start) / dot_count
    x = []
    y = []
    while x_start <= x_end:
        x.append(x_start)
        if is_density:
            y.append(exponential_distribution_density(lmbd, x_start))
        else:
            y.append(exponential_distribution(lmbd, x_start))
        x_start += step
    return x, y


def main():
    a, b, lmbd = read_params()
    x_un, y_un = uniform_values(a, b, is_density=False)
    x_un_d, y_un_d = uniform_values(a, b, is_density=True)
    x_exp, y_exp = exponential_values(lmbd, is_density=False)
    x_exp_d, y_exp_d = exponential_values(lmbd, is_density=True)

    plt.figure()
    plt.title("Равномерное распределение")
    plt.plot(x_un, y_un)

    plt.figure()
    plt.title("Плотность равномерного распределения")
    plt.plot(x_un_d, y_un_d)

    plt.figure()
    plt.title("Экспоненциальное распределение")
    plt.plot(x_exp, y_exp)

    plt.figure()
    plt.title("Плотность экспоненциального распределения")
    plt.plot(x_exp_d, y_exp_d)

    plt.show()


if __name__ == "__main__":
    main()
