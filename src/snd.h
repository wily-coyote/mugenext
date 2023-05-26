const char SIGNATURE[12] = "ElecbyteSnd";

struct Header {
	char signature[12];
	unsigned short nHiVer;
	unsigned short nLoVer;
	unsigned long cSounds;
	unsigned long oFirst;
	char comment[488];
};

struct SubfileHeader {
	unsigned long oNext;
	unsigned long cbSubfile;
	unsigned long nGroup;
	unsigned long nIndex;
};

typedef struct Header Header;
typedef struct SubfileHeader SubfileHeader;