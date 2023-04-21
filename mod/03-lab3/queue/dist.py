from numpy.random import exponential
import random


class EvenDistribution:
    def __init__(self, a: float, b: float):
        self.a = a
        self.b = b

    def generate(self):
        return self.a + (self.b - self.a) * random.random()


class ExponentialDistribution:
    def __init__(self, lam):
        self.lam = lam

    def generate(self):
        return exponential(self.lam)

