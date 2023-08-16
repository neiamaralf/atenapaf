#define STX 0x02
#define ETX 0x03
#define SOH 0x01
#define EOT 0x04
#define ACK 0x06
#define NACK 0x15
#define ENQ 0x05

#ifdef _DEBUG
#define DEBUG(x) printf(x)
#define DEBUG2(x,y) printf(x,y)
#else
#define DEBUG(x)
#define DEBUG2(x,y)
#endif

extern int inportb( int fileDescriptor, int timeOut );
extern int outportb( int fileDescriptor, int byte );
extern int enviaENQ( int Porta );
extern int recebeBuffer( int Porta,  char buffer[] );
extern int recebeBuffer2( int Porta,  char buffer[] );
extern int PortaConfig(const char* devName, int linkSpeed,  termio* pOldTermio=NULL );
extern int PortaUnconfig(int linkFd,  termio* pOldTermio=NULL);
extern int enviabuf( int Porta,char *BufTrm,int lenght ) ;
extern int AbrePorta(const char* devName,  termios* pnewTermio,  termios* pOldTermio);
