#!/bin/python3

#
# Esse script foi feito para testar a corretude da calculadora de gradientes 
# para o caso da norma euclidiana (a derivada da identidade trigonométrica é zero)
# 
# Aqui se assume que a derivada direcional dv/dx da norma euclidiana é x/||v||
#

import math

def euclidean_norm (xs):
    return math.sqrt( sum( (x*x for x in xs) ) )

def euclidean_norm_gradient (xs):
    return [ x/euclidean_norm(xs) for x in xs ]

if __name__ == '__main__':
    str_in = input()
    xs = [float(str_x) for str_x in str_in.split(' ') if str_x]
    grad = euclidean_norm_gradient(xs)
    
    for dx in grad:
        print('{:e}'.format(dx), end=' ')
    print(end='\n')
    