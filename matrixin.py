import sympy
from sympy import Matrix
from sympy import Symbol as s
from sympy import pprint

A = Matrix([[s('1/r'),s('1/(2r)'),s('1/(3r)')],[s('1/(2r)'),s('1/(2r)'),s('1/(3r)')],[s('1/(3r)'),s('1/(3r)'),s('1/(3r)')]])
#A = Matrix([[s('c11'),s('c12')],[s('c12'),s('c22')]])

inv = A.inv()

pprint(A)

pprint(inv)



