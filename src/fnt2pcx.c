#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fnt.h"

int main(int argc, char** argv){
	char* fntPath = NULL;
	if(argc > 1){
		fntPath = argv[1];
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
	char* basename = malloc(strlen(fntPath)+1);
	memcpy(basename, fntPath, strlen(fntPath)+1);
	char* extPos = strrchr(basename, '.');
	*extPos = '\0';
	char pcxPath[260];
	char txtPath[260];
	snprintf(pcxPath, sizeof pcxPath, "%s.pcx", basename);
	snprintf(txtPath, sizeof txtPath, "%s.txt", basename);
	FILE* fntHandle = fopen(fntPath, "rb");
	if(fntHandle == NULL) {
		printf("Couldn't read %s\n", fntPath);
		return -1;
	}
	Header header;
	fread(&header, sizeof(Header), 1, fntHandle);
	if(strcmp(header.signature, SIGNATURE) != 0){
		printf("Not an FNT file\n");
		return -1;
	}
	unsigned char* pcxData = malloc(header.cbPcx);
	unsigned char* txtData = malloc(header.cbTxt);
	fseek(fntHandle, header.oPcx, 0);
	fread(pcxData, header.cbPcx, 1, fntHandle);
	fseek(fntHandle, header.oTxt, 0);	
	fread(txtData, header.cbTxt, 1, fntHandle);
	FILE* pcxHandle = fopen(pcxPath, "wb");
	FILE* txtHandle = fopen(txtPath, "wb");
	if(pcxHandle == NULL){
		printf("Couldn't write %s\n", pcxPath);
		return -1;
	}
	if(txtHandle == NULL){
		printf("Couldn't write %s\n", txtPath);
		return -1;
	}
	fwrite(pcxData, header.cbPcx, 1, pcxHandle);
	printf("Wrote %s\n", pcxPath);
	fwrite(txtData, header.cbTxt, 1, txtHandle);
	printf("Wrote %s\n", txtPath);
	free(pcxData);
	free(txtData);
	free(basename);
	fclose(fntHandle);
	fclose(pcxHandle);
	fclose(txtHandle);
	return 0;
}