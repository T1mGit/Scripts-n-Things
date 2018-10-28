#!/usr/bin/python
#
#
###############################################################################
#
#
#            Phython MD5 Pass File Generator
#                Version 1.0
#            Written by Tim Hyde, 2017
#
#
###############################################################################

import crypt
import sys
try:
    f=open("shadow","w+")
except:
    print("could not open file")
    sys.exit(1)
if (len(sys.argv) % 3) !=1: #extra symbols - should be remainder of 1
     print("Invalid argument count. Missing a username or salt or password")
     sys.exit(1)

#write password hashes to file
for i in range(1,len(sys.argv),3):
    newhash=crypt.crypt(sys.argv[i+2],sys.argv[i+1])
    print(sys.argv[i]+":$1$"+sys.argv[i+1]+"$"+newhash+":::")
    f.write(sys.argv[i]+":$1$"+sys.argv[i+1]+"$"+newhash+":::\n")
f.close()
sys.exit(0)
