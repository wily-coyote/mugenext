#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "snd.h"

int main(int argc, char** argv){
	char* sndPath = NULL;
	if(argc > 1){
		sndPath = argv[1];
	}
	if(sndPath == NULL){
		printf("Enter path to SND: ");
		char buf[260];
		if(fgets(buf, sizeof buf, stdin) != NULL){
			if(buf[strlen(buf)-1] == '\n'){
				buf[strlen(buf)-1] = '\0';
			}
			sndPath = buf;
		}
	}
	FILE* sndHandle = fopen(sndPath, "rb");
	if(sndHandle == NULL) {
		printf("Couldn't read %s\n", sndPath);
		return -1;
	}
	Header header;
	fread(&header, sizeof(Header), 1, sndHandle);
	if(strcmp(header.signature, SIGNATURE) != 0){
		printf("Not an SND file\n");
		return -1;
	}
	fseek(sndHandle, header.oFirst, 0);
	for(int i = 0; i < header.cSounds; i++){
		SubfileHeader curSubfile;
		fread(&curSubfile, sizeof(SubfileHeader), 1, sndHandle);
		char filename[260];
		snprintf(filename, sizeof filename, "%ld-%ld.wav", curSubfile.nGroup, curSubfile.nIndex);
		FILE* wavFile = fopen(filename, "wb");
		if(wavFile == NULL){
			printf("Couldn't write to %s\n", filename);
			continue;
		}
		unsigned char* wavData = malloc(curSubfile.cbSubfile);
		fread(wavData, curSubfile.cbSubfile, 1, sndHandle);
		fwrite(wavData, curSubfile.cbSubfile, 1, wavFile);
		fclose(wavFile);
		free(wavData);
		printf("Wrote %s\n", filename);
		fseek(sndHandle, curSubfile.oNext, 0);
	}
	fclose(sndHandle);
	return 0;
}