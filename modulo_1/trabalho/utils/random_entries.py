#!/bin/python3

import random

if __name__ == '__main__':
    from sys import argv
    
    if len(argv) >= 3:
        seed = int(argv[2])
        random.seed(seed)

    n = int(argv[1])
    for _ in range(n):
        print( random.normalvariate(mu=0, sigma=1), end=' ' )
    print()
