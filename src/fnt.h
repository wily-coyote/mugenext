const char SIGNATURE[12] = "ElecbyteFnt";

struct Header {
	char signature[12];
	unsigned short nHiVer;
	unsigned short nLoVer;
	unsigned long oPcx;
	unsigned long cbPcx;
	unsigned long oTxt;
	unsigned long cbTxt;
	char comment[40];
};

typedef struct Header Header;