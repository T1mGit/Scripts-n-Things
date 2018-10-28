#!/usr/bin/python
#
#
###############################################################################
#
#
#            Phython Simple Wordlist Password Attack
#                          Version 1.0
#                   Written by Tim Hyde, 2017
#
#
###############################################################################

import crypt
import sys
lines=[]
words=[]
cracked=[]
#print (sys.argv[1]+" "+sys.argv[2])
#Open Files
try:
    f=open(sys.argv[1],'r')
    lines=f.readlines()
    f.close()
except:
    print("Could not open a password file")
    sys.exit(1)
try:
    g=open(sys.argv[2],'r')
    wordlist=g.readlines()
    g.close()
except:
    print("Could not open wordlist")
    sys.exit(1)

#For every Enty in the Password File Split into Component Parts (username, salt, hash) - md5 assumed
for line in lines:
    args=line.split(":")
    user=args[0].strip()
    if args[1]=='*':
	print("[*]No Password('*')>>  "+user+":"+args[1])
    elif args[1]=='!':
	print("[*]     Locked('!')>>  "+user+":"+args[1])
    else:
        hashtext=args[1].split('$')
        salt=hashtext[2].strip()
        pwhash=hashtext[3].strip()
        print("[*] Found Hash     >>  "+user+":"+salt+":"+pwhash)

        #Calculate the hash for every password in the word list using salt from password file
        for word in wordlist:
            word=word.strip()
            testhash=crypt.crypt(word,salt)
            #Display password if found
            if pwhash==testhash:
                print("[*]        Password>>  "+user+":"+word)
                cracked.append(user+":"+word)
                break
print("[*]\n[*]"+str(len(cracked))+" Hashes cracked!")
for i in range(0,len(cracked)):
	print("[*]        Password>>  "+cracked[i])
