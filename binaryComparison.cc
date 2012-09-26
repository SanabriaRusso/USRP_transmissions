/*This little script is intended to check in which octect an image differs from
other. 

It does not work for all purposes. And no warranty is given under any circumstances.

For our work, an image is sent over TV White Spaces with no security measures (upper layers, etc.).
At arrival, the image is compared with the one that was sent. This script just points
out in which octect the connection failed, producing a corrupted image.

Feel free to modify it.

Luis Sanabria-Russo
luis.sanabria@upf.edu
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include <algorithm>

#include <stdio.h>
#include <stdlib.h>

using namespace std;


int main(int argc, const char * argv[]){
	
	const char* sourceFile;
	const char* transferedFile;
	
	FILE* origin;
	FILE* transfer;
	long originFileSize, transferFileSize;
	char *bufferOrigin;	//stores values of the origin file
	char *bufferTransfer;
	int readBytesOrigin;
	int readBytesTransfer;
	
	int *badOctects;	//arrat to store mismatched octects
	
	
	if(argc >= 2) sourceFile = (argv[1]);
	if(argc >= 3) transferedFile = (argv[2]);
	
	origin = fopen(sourceFile, "rb");
	if (origin == NULL) {fputs ("File error: origin", stderr); exit (1);}
	transfer = fopen(transferedFile, "rb");
	if (transfer == NULL) {fputs ("File error: transfer", stderr); exit (1);}

	
	//Obtaining file size, the cool way
	//You may find easy-to-read documentation about this subject
	//File sizes are returned in bytes
	fseek(origin, 0, SEEK_END);
	originFileSize = ftell(origin);
	rewind(origin);
	cout << "------------------------------------" << endl;
	cout << "Origin file size: " << originFileSize << " bytes" << endl;
	
	fseek(transfer, 0, SEEK_END);
	transferFileSize = ftell(transfer);
	rewind(transfer);
	cout << "Transfer file size: " << transferFileSize << " bytes" << endl;
	
	
	//Building the buffer that will hold the contents of the origin file
	bufferOrigin = (char *)malloc(sizeof(char) * originFileSize);
	if (bufferOrigin == NULL) {fputs ("Memory error: origin", stderr); exit (2);}
	
	bufferTransfer = (char *)malloc(sizeof(char) * transferFileSize);
	if (bufferTransfer == NULL) {fputs ("Memory error: transfer", stderr); exit (2);}
	
	//Reading the source file one byte at a time
	readBytesOrigin = fread(bufferOrigin, 1, originFileSize, origin);	
	if (readBytesOrigin != originFileSize) {fputs ("Reading error: origin", stderr); exit (3);}
	
	//Reading the transfer file one byte at a time
	readBytesTransfer = fread(bufferTransfer, 1, transferFileSize, transfer);	
	if (readBytesTransfer != transferFileSize) {fputs ("Reading error: transfer", stderr); exit (3);}
	
	
	//Compairing the buffers that now store the binary data as an array
	badOctects = new int[transferFileSize];
	
	if((originFileSize - transferFileSize) == 0){
		cout << "Files seem to have the same size" << endl;
	}
	
	else{
		cout << "Files are going to be compared" << endl;
		for(long i = 0; i <= originFileSize; i++){ //surfing through octects
			int decimalOrigin, decimalTransfer;
			
			decimalOrigin = 0;
			decimalTransfer = 0;
			
			stringstream originOctect (stringstream::app | stringstream::binary | stringstream::out);
			stringstream transferOctect (stringstream::app | stringstream::binary | stringstream::out);
			
			if(i < transferFileSize){
				for(int j = 0; j < 8; j++){ //grabbing 8 bits at a time
					originOctect << bufferOrigin[j];
					transferOctect << bufferTransfer[j];
				}
				
				//Now the filled octects are compared in decimal form for ease
				decimalOrigin = atoi(originOctect.str().c_str());
				decimalTransfer = atoi(transferOctect.str().c_str());
				
				if(decimalOrigin != decimalTransfer){ 
					badOctects[i] = 1;
					cout << "The bad octect: " << i << " was detected" << endl;
				}
				else{ 
					badOctects[i] = 0;
				}
			}
			else{
				cout << "------------------------------------" << endl;
				cout << "Transfer file corrupted at octect: " << i << endl;
				cout << "------------------------------------" << endl;
				cout << "Amount of untrusted data: " << originFileSize - i << " bytes" << endl;
				cout << "------------------------------------" << endl;
				break;
			}

			//cout << decimalOrigin << endl;
		}
			
	}
	
	fclose(origin);
	fclose(transfer);
	free(bufferOrigin);
	free(bufferTransfer);
	free(badOctects);
	
	return 0;
}
