#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fnt.h"

int main(int argc, char** argv){
	char* pcxPath = NULL;
	char* txtPath = NULL;
	char* fntPath = NULL;
	if(argc > 3){
		pcxPath = argv[1];
		txtPath = argv[2];
		fntPath = argv[3];
	}
	if(pcxPath == NULL){
		printf("Enter path to PCX: ");
		char buf[260];
		if(fgets(buf, sizeof buf, stdin) != NULL){
			if(buf[strlen(buf)-1] == '\n'){
				buf[strlen(buf)-1] = '\0';
			}
			pcxPath = buf;
		}
	}
	if(txtPath == NULL){
		printf("Enter path to TXT: ");
		char buf[260];
		if(fgets(buf, sizeof buf, stdin) != NULL){
			if(buf[strlen(buf)-1] == '\n'){
				buf[strlen(buf)-1] = '\0';
			}
			txtPath = buf;
		}
	}
	if(fntPath == NULL){
		printf("Enter path to FNT: ");
		char buf[260];
		if(fgets(buf, sizeof buf, stdin) != NULL){
			if(buf[strlen(buf)-1] == '\n'){
				buf[strlen(buf)-1] = '\0';
			}
			fntPath = buf;
		}
	}

	FILE* pcxHandle = fopen(pcxPath, "rb");
	FILE* txtHandle = fopen(txtPath, "rb");
	FILE* fntHandle = fopen(fntPath, "wb");

	if(pcxHandle == NULL) {
		printf("Couldn't read PCX %s\n", pcxPath);
		return -1;
	}

	if(txtHandle == NULL) {
		printf("Couldn't read TXT %s\n", txtPath);
		return -1;
	}

	if(fntHandle == NULL) {
		printf("Couldn't open FNT %s for writing\n", fntPath);
		return -1;
	}

	Header header;
	memcpy(header.signature, SIGNATURE, 12);

	fseek(pcxHandle, 0, SEEK_END);
	fseek(txtHandle, 0, SEEK_END);

	header.nHiVer = 0x0100;
	header.nLoVer = 0x0000;

	header.cbPcx = ftell(pcxHandle);
	header.cbTxt = ftell(txtHandle);

	header.oPcx = sizeof(Header);
	header.oTxt = sizeof(Header)+header.cbPcx;

	memset(header.comment, 0, 32);
	//strcpy(header.comment, "pcx2fnt");

	rewind(pcxHandle);
	rewind(txtHandle);

	fwrite(&header, sizeof(Header), 1, fntHandle);
	
	char pcxData[header.cbPcx];
	char txtData[header.cbTxt];

	fread(pcxData, header.cbPcx, 1, pcxHandle);
	fread(txtData, header.cbTxt, 1, txtHandle);

	fwrite(pcxData, header.cbPcx, 1, fntHandle);
	fwrite(txtData, header.cbTxt, 1, fntHandle);

	printf("Wrote %s\n", fntPath);

	fclose(fntHandle);
	fclose(pcxHandle);
	fclose(txtHandle);

	return 0;
}
