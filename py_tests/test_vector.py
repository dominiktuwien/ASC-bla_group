# search for libraray like bla.cpython-312-darwin.so in the build directory:
import sys
sys.path.append(r'C:\Users\eichl\Uni\7. Semester\Scientific Computing\Git-Clone\ASC-ODE_physics_group\ASC-bla_group\_skbuild\win-amd64-3.10\cmake-install\ASCsoft')
#import os
#os.add_dll_directory(r'C:\Users\eichl\Uni\7. Semester\Scientific Computing\Git-Clone\ASC-ODE_physics_group\ASC-bla_group\_skbuild\win-amd64-3.10\cmake-install\ASCsoft')

print(sys.path)
#from ASCsoft import Vector

# import from the installed ASCsoft package:
from ASCsoft.bla import *


x = Vector(3)
y = Vector(3)

for i in range(len(x)):
    x[i] = i
y[:] = 2    

print ("x =", x)
print ("y =", y)
print ("x+3*y =", x+3*y)


x = Vector(10)
x[0:] = 1
print (x)

x[3:7] = 2
print (x)

x[0:10:2] = 3
print (x)






