#!/usr/bin/python

class fraction:
    def __init__(self, num=0, den=1):
        self.num = num
        self.den = den

    def __str__(self):
       g = gcd(self.num, self.den)
       return "[%d / %s]" % (self.num/g, self.den/g)

    def __del__(self):
        pass

    def __add__(self, other):
        n = self.num*other.den + self.den*other.num 
        d = self.den * other.den
        g = gcd(n, d)
        return fraction(n/g, d/g)

    def __sub__(self, other):
        n = self.num*other.den - self.den*other.num 
        d = self.den * other.den
        g = gcd(n, d)
        return fraction(n/g, d/g)

    def __mul__(self, other):
        n = self.num * other.num
        d = self.den * other.den
        g = gcd(n, d)
        return fraction(n/g, d/g)

    def __div__(self, other):
        n = self.num * other.den
        d = self.den * other.num
        g = gcd(n, d)
        return fraction(n/g, d/g)

def gcd(n, d):
    a, b = n, d
    tmp = a % b
    if a != 0 and b != 0:
        while abs(a % b) > 0 and abs(a) > 1 and abs(b) > 1:
            tmp = a % b
            a = b
            b = tmp
        if a * b > 0:
            return b
        else:
            return -b
    else:
        return 1


