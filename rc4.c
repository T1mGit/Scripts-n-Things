/*
 *
 *	RC4 STREAM CIPHER VERSION 1.01.20171205
 *	WRITTEN BY TIM HYDE WITH REFERENCE TO
 *	COMPUTER SECURITY PRINCIPLES AND PRACTISE STALLINGS, W. & BROWN, L.
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char*argv[]){
	int i, j;
	int keylen;	
	unsigned char S[256];	//State Vector S
	unsigned char T[256]; 	//Temporary Vector T
	unsigned char*infile;	//byte array for input
	unsigned char*outfile;	//byte array for output
	unsigned long flen=0;	//length of input
	unsigned long fpos=0;	//position of byte being read/written
	int ofid=0;		//position in the argv array of the file path for the output file, 0 if no file.
	FILE* fp_i;		//file pointer for input file
	FILE* fp_o;		//file pointer for output file

	//Print Command instructions if less than 3 args
	if(argc<3){
		printf("rc4 KEY [[-i|-s] INFILE] [-o OUTFILE]\n \
				If -i is specified rc4 reads from the file INFILE.\n \
				If -s is specified rc4 read a string from command argument.\n \
				If neither -s nor -i is specified rc4 reads a maximum of 254 characters from standard input.\n \
				If OUTFILE is not specified output to stdout.\n");
		return 0;
	}

	//Parse CL args and read input streams
       if(argc>3){
		for(i=2;i<argc;i+=2){
			switch (*(argv[i]+1)){
				case 'i':
					//if the -i switch selected read from specified file.
					//calculate length of file by seeking to end of file (and back)
					//allocate sufficient memory
					//read file byte wise into memory
					//close the file
					printf("Reading Infile...\n");
					fp_i=fopen(argv[3],"rb");
					if(fp_i==NULL){
						printf("Cannot open Infile...exiting.\n");
						return 1;
					}
					flen=fseek(fp_i,0L,SEEK_END);
					flen=ftell(fp_i);
					fseek(fp_i,0L,SEEK_SET);
					infile=(unsigned char *)malloc(flen+1);
					unsigned long offset=0;
					while(feof(fp_i)==0){
						offset=fread(infile+offset,flen,1,fp_i);
						if(ferror(fp_i)!=0){
							printf("Error Reading infile. Exiting.\n");
							return 32;
						}
					}
					fclose(fp_i);
				break;
				case 's':
					//if -s specified get string from CL arg.
					//strlen function does not include the null terminator when calculating string length
					printf("Parsing command string...\n");
					flen=strlen(argv[3])+1;
					infile=argv[3];
				break;
				case 'o':
					//if input not specified but output is, read input from stdin max 255
					//Then open the output file
					//note the different location in the CL arg if input is not specified
					if(argc<5){
						printf("Waiting for input...\n");
						infile=(unsigned char *)malloc(256);
						fgets(infile,256,stdin);
						flen=strlen(infile)+1;
						ofid=3;
					}else{
						ofid=5;
					}
					fp_o=fopen(argv[ofid],"wb");
					if(fp_o==NULL){
						printf("Cannot open Outfile...exiting.\n");
						return 2;
					}
				break;
				default:
					printf("Invalid command argument...exiting.\n");
					return 4;
				break;
			}
		}
	}else{
		printf("Insufficient arguments provided...exiting.\n");
		return 8;
	}
	if(flen<1){
		printf("Input is 0 length...exiting.\n");
		return 16;
	}

	//allocate memory for the output based in input size
	outfile=(unsigned char *)malloc(flen);

	//initialisation of state vector S
	printf("Initialising state vector...\n");
	keylen=strlen(argv[1]);
	for(i=0;i<256;i++){
		S[i]=i;
		T[i]=*(argv[1]+i%keylen);
	}
	
	//Initial permutation of state Vector
	printf("Permuting state vector.\n");
	j=0;
	unsigned char temp;
	for(i=0;i<256;i++){
		j=( j + S[i] + T[i] ) % 256;
		//swap S[i] and S[j]
		temp=S[i];
		S[i]=S[j];
		S[j]=temp;
	}
	
	//Stream Generation
	printf("Stream Encrypting...\n");
	i=0; j=0; fpos=0;
	while(fpos<flen){
		i=( i + 1 ) % 256;
		j=( j + S[i] ) % 256;
		//swap S[i] and S[j]
		temp=S[i];
		S[i]=S[j];
		S[j]=temp;
		//encrypt infile by XOR with  key stream k where k=S[ (S[i] + S[j]) % 256]
		outfile[fpos]=S[ ( S[i] + S[j] ) % 256 ]^(infile[fpos]);
		fpos++;
	}

	//write to file
	printf("Writing output...\n");
	if(ofid>0){
		fwrite(outfile,1,flen,fp_o);
		fclose(fp_o);

	}else{
		fwrite(outfile,1,flen,stdout);
	}
	printf("\nProgram complete.\n\n");
	return 0;	
}
