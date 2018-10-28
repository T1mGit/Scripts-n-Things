# Scripts-n-Things
<h2> PortScanPyV3.py</h2>
A Simple port scanner written in python that makes a TCP connection using the python socket.connect() to test for open ports.<br>
It can scan an arbitrary range of consecutive ports and an arbitrary range of consecutive IP addresses whos subnet mask is 255.255.255.0<br>
It print to the terminal window the number of ports scanned, which ports are open and any banners received.
<p>
<p>
<h2>ARC4</h2>
A implementatin of the ARC4 Algorithm written in C using the gcc compiler in linux. A copy of the algorithm was obtained from the one of my text books:<br>
<b>STALLINGS, W. & BROWN, L. (2015). COMPUTER SECURITY PRINCIPLES AND PRACTICE. THIRD EDITION. (PP. 673-674).  PEARSON EDUCATION LTD.</b>
<p><p>
<h2>JPEG Stego</h2>
CURRENTLY NOT WORKING - THE OUTPUT IS CORRUPT<br>
My attempt at producing steganophraphy using jpeg a file.<br>Currently this script seems to have an issue correctly identifying the JPEG markers.<br>What I have have learned about JPEG images, is that there are a number of marker bytes one of which is an SOS (Start of Scan) after which is image data.<br> My process was to search the file for this marker then adjust the following image data.<br>
This script is currently a work in progress as I am still working/researching the precise data structures of the JPEG image (evident from the fact the the processing output is not as exptected).
