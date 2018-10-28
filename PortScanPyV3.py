#!/usr/bin/python
#
#
###############################################################################
#
#
#            Phython Simple Port Scan
#                Version 1.0
#            Written by Tim Hyde, 2017
#
#
###############################################################################

#import python libraries
import sys
import socket
import time
print("USAGE\n\tPython PortScan.py [-r] HOST [IPRANGE] START END\n\nNOTES\n\tHOST must be supplied.\n\tBoth START and END must be supplied.\n\tIPRANGE is the last octet of the ending ip range. -r must specified to use this.\n\n")
results=[]
if len(sys.argv)>1:

    #get target address and port from commandline
    if sys.argv[1].strip()=="-r":
        domain=sys.argv[2].strip()
        try:
            ipstart=int(domain.split(".")[3])
            ipstop=int(sys.argv[3])
            portStart=int(sys.argv[4])
            portStop=int(sys.argv[5])
        except:
            print ("Error: Unexpected IP or Port Range")
            sys.exit(1)
    else:
        domain=sys.argv[1].strip()
        try:
            ipstart=int(domain.split(".")[3])
            ipstop=ipstart
            portStart=int(sys.argv[2])
            portStop=int(sys.argv[3])
        except:
            print ("Error: Unexpected IP or Port Range.")
            sys.exit(1)

    domain=domain.split(".")[0]+"."+domain.split(".")[1]+"."+domain.split(".")[2]+"."

    #start scanning
    #try every port in range to see if it connects
    for ip in range(ipstart,ipstop+1):
        portCount=0
        openCount=0
        host=domain+str(ip)
        print("[*]Checking for open ports on host: "+host)
        print("[*]PARAMS\n  >HOST="+host+"\n  >START="+str(portStart)+"\n  >STOP="+str(portStop))
        for port in range(portStart,portStop):
            s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
            s.settimeout(0.002)
            try:
                s.connect((host,port))
                s.send(b'Hello World')
                banner=s.recv(4096)
                time.sleep(1)
                openCount+=1
                print ("[*]Port:",port,"Open\t\t"+str(banner))
                s.close()
                results.append("[*]Host: "+host+":"+str(port)+", Open\t"+str(banner))
            except socket.error as err:
                pass
            portCount=portCount+1
        print("[*]"+str(portCount)+" ports tried. "+str(openCount)+" ports open. "+str(portCount-openCount)+" ports fail.\n\n"+"="*20+"\n")
    print ("[*]"+str(ipstop-ipstart+1)+" IPs scanned.")
    for i in range(0,len(results)):
        print (results[i])
sys.exit()
