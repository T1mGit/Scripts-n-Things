# Scripts-n-Things
<h2> PortScanPyV3.py</h2>
A Simple port scanner written in python that makes a TCP connection using the python socket.connect() to test for open ports.<br>
It can scan an arbitrary range of consecutive ports and an arbitrary range of consecutive IP addresses whos subnet mask is 255.255.255.0<br>
It print to the terminal window the number of ports scanned, which ports are open and any banners received.
<pre>
USAGE   python PortScan.py [-r] HOST [IPRANGE] START END

    HOST      The host IP address must be supplied
    START     The starting port number must be supplied
    END       The ending port must be supplied
    IPRANGE   is the last octet of the ending ip range. -r must specified to use this.
</pre>
<h2>ARC4</h2>
A implementatin of the ARC4 Algorithm written in C using the gcc compiler in linux. A copy of the algorithm was obtained from the one of my text books:<br>
<b>STALLINGS, W. & BROWN, L. (2015). COMPUTER SECURITY PRINCIPLES AND PRACTICE. THIRD EDITION. (PP. 673-674).  PEARSON EDUCATION LTD.</b>
<pre>
USAGE   rc4 KEY [[-i|-s] INFILE] [-o OUTFILE]

    If -i is specified rc4 reads from the file INFILE.
    If -s is specified rc4 read a string from command argument.
    If neither -s nor -i is specified rc4 reads a maximum of 254 characters from standard input.
    If OUTFILE is not specified output to stdout.
</pre>
<h2>JPEG Stego</h2>
CURRENTLY NOT WORKING - THE OUTPUT IS CORRUPT<br>
My attempt at producing steganophraphy using jpeg a file.<br>Currently this script seems to have an issue correctly identifying the JPEG markers.<br>What I have have learned about JPEG images, is that there are a number of marker bytes one of which is an SOS (Start of Scan) after which is image data.<br> My process was to search the file for this marker then adjust the following image data.<br>
This script is currently a work in progress as I am still working/researching the precise data structures of the JPEG image (evident from the fact the the processing output is not as exptected).<br>
<pre>
USAGE    jpegstego IMAGE DATA

    IMAGE   The jpeg image file to be processed
    DATA    Any literal or raw data supplied via the CLI
</pre>
<h2>bash_rip</h2>
A simple bash script that use opensll (openssl passwd -1 -salt <xyz> <pass>) to generate the password hash from a wordlist to compare with an offline password linux file.<br>
NOTE: I lost the original text and copied this from word document. There may be unintentional white space which can cause errors in bash.<br>
  <pre>
USAGE ./scriptname PASS LIST
    
    PASS	The path to the password file
    LIST	The path to the wordlist
</pre>
<h2>py_rip</h2>
A simple python implementation that uses the python crypt library to generate a hash to compare with the linux password file.<br>
I found that the python crypt library gave different results to the open ssl (above) for the same input.<br>
  <pre>
USAGE		python script.py PASS WORDLIST

    PASS		The name and path to the password file
    WORDLIST	The name and path to the wordlist file
</pre>
  <h2>py_pass.py</h2>
  This script generates a password file with password hashes based on the python crypt library.
  <pre>
USAGE		python <script.py> USER SALT PASS [USER SALT PASS …]
	
    USER		The Username
    SALT		The Salt value
    PASS		Plaintext password
</pre>
  
