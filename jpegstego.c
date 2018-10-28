#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//int reversebytes(char*data,int len){char tmp;for (int i=0;i<(len/2);i++){tmp=*(data+i);*(data+i)=*(data+len-i-1);*(data+len-i-1)=tmp;}}
int main(int argc, char*argv[]){
	if(argc<3){
		printf("USAGE:\tjpegstego SOURCE_IMAGE DATA\n\n");
		return 1;
	}
	//convert data into array of bits
	unsigned int len_bitarray=8*strlen(argv[2]);
	printf("Array: <%s>.\nBit array length: %d bits.\n",argv[2],len_bitarray);
	char*bitarray=(char*)malloc(len_bitarray);
	if(bitarray==NULL){printf("Could not allocate memory for bit array.\n");return 1;}
	for(int i=strlen(argv[2]);i>0;i--){
		//printf("before the seocnd for loop i=%d\n",i);
		for(int j=0;j<8;j++){
		//printf("I got here i:%d j:%d\n",i,j);
		//printf("argv[%d]=%c\n",i,(*(argv+2))[j]);
		(bitarray[8*i+j])=( (*(argv+2))[i]>>(7-j))&1;
		}
	}
	//printf("bit arr=\n%s",bitarray);
	FILE * fp=fopen(argv[1],"rb");
	if(fp==NULL){fprintf(stderr,"Could not open file: %s\n",argv[1]);exit(2);}

	//calculate file size for allocation
	fseek(fp,0,SEEK_END);
	unsigned long len_file=ftell(fp);
	printf("File length: %ld bytes.\n",len_file);

	//reset file ointer
	rewind(fp);

	//Allocate memory and read file into memory
	void*jpeg=malloc(len_file);
	if(jpeg==NULL){fprintf(stderr,"Could not allocate file memory. Exiting...\n");exit(1);}
	unsigned int count=fread(jpeg,1,len_file,fp);
	if(count<len_file){fprintf(stderr,"Error raeding file. Exiting...\n");exit(1);}
	fclose(fp);

	//see what we've read
	//for(unsigned long i=0;i<len_file;i++){
	//printf("%x",*(char*)(jpeg+i));}

	//Try to parse JPEG file
	//JPEG starts with SOI 0xffd8
	unsigned long pos=0;
	short SOI=*(short *)(jpeg);	//a short is 2 bytes;
	printf("SOI marker: %x\n",SOI);
	pos+=2;

	//jpeg segment headers are 4 bytes (int)
	//0xff identifies the segement
	//0xnn iddentifies the type
	//2 bytes for size
	//App0 marker 0xffe0 immediately follow SOI
	
	//search segments for the SOS marker 0xffda
	unsigned short seg = *(unsigned short *)(jpeg+pos);
	while((seg)!=0xffda){
		pos+=2;	//increment positiion by segment length, should arrive at next segment
		//printf("Segment Marker: %x, File Position:%ld\n",seg,pos);

		seg=*(unsigned short *)(jpeg+pos);
	}
	printf("Found Segment Marker: %x\n",seg);
	unsigned short seg_len=*(unsigned short *)(jpeg+pos+2);
	printf("Segment Length: %x (%d)\n",seg_len,seg_len);
	pos+=4;
	char num_comp=*(char *)(jpeg+pos);
	pos+=seg_len;
	unsigned long image=pos;
	if((len_file-image)<len_bitarray){
		printf("Warning: Not enough image pixels. Data will be truncated.\n");
	}
	int k=0;
	while(pos<(len_file-2)){
		*(char*)(jpeg+pos)=(*(char*)(jpeg+pos))&0xfe + *(char*)(bitarray+(k%len_bitarray));
	//printf("Position:%ld  k:%d, value:%d\n",pos,k,(*(char *)(bitarray+(k%len_bitarray))) );
	k+=1;pos+=1;
	}

	//Write new jpeg
	fp=fopen("steg_out.jpeg","wb");
	if(fp==NULL){fprintf(stderr,"Failed to open output file. Exiting...\n");exit(1);}
	count=fwrite(jpeg,1,len_file,fp);
	if(count<len_file){fprintf(stderr,"Error writing new file.\n");}
	fclose(fp);
	free(jpeg);
	free(bitarray);
}
