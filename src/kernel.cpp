#include <stdio.h>
#include <signal.h>
#include <assert.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termio.h>

#define STX 0x02
#define ETX 0x03
#define SOH 0x01
#define EOT 0x04
#define ACK 0x06
#define NACK 0x15
#define ENQ 0x05

#define NO_VEZES 2

#include "kernel.h"

const char	*message[] = {
	"[OK]*CARGA ENCERRADA COM SUCESSO*\n",
	"[ERRO 01]*DEFINIR CORRETAMENTE PARAMETROS*\n",
	"[ERRO 02]*CANAL SERIAL NAO DISPONIVEL NESTE EQUIPAMENTO*\n",
	"[ERRO 03]*No. BALANCA INVALIDO*\n",
	"[ERRO 04]*INDICE INICIAL NAO DISPONIVEL*\n",
	"[ERRO 05]*INDICE FINAL NAO DISPONIVEL*\n",
	"[ERRO 06]*INDICE INICIAL > INDICE FINAL*\n",
	"[ERRO 07]*TIPO DESCARGA NAO DISPONIVEL*\n",
	"[ERRO 08]*ERRO NO FECHAMENTO ARQUIVO DESCARGA*\n",
	"[ERRO 09]*ERRO NA ABERTURA DO ARQUIVO*\n",
	"[ERRO 10]*ERRO NA TRANSMISSAO DA LINHA DE COMANDO*\n",
	"[ERRO 11]*ERRO NO RECEBIMENTO DE DADOS DA BALANCA*\n",
	"[ERRO 12]*ERRO NA TRANSMISSAO DO ENQUIRE*\n",
	"[ERRO 13]*ERRO NA GRAVACAO DE ARQUIVO*\n",
	"[ERRO 14]*ARQUIVO NAO POSSUI TODOS OS INDICES, CARGA TERMINADA*\n",
	"[ERRO 15]*EXCESSO NO BUFFER DE TRANSMISSAO*\n",
	"[ERRO 16]*ERRO NA LEITURA DE ARQUIVO*\n",
	"[ERRO 17]*ERRO NA TRANSMISSAO DE DADOS PARA BALANCA*\n",
	"[ERRO 18]*TERMINADOR NAO TRANSMITIDO*\n",
	"[ERRO 19]*ERRO NA LEITURA DO ARQUIVO*\n",
	"[ERRO 20]*ERRO NA ABERTURA DA PORTA DE COMUNICACAO*\n",
	"[ERRO 21]*ERRO PARAMETRO PORTA DE COMUNICACAO NAO E UM DISPOSITIVO TTY*\n",
	"[ERRO 22]*ERRO NA LEITURA DA CONFIGURACAO DA PORTA DE COMUNICACAO*\n",
	"[ERRO 23]*ERRO NA CONFIGURACAO DA PORTA DE COMUNICACAO*\n",
	"[ERRO 24]*NAO PODE CRIAR BCSAR.DAT\n",
	"[ERRO 25]*ERRO NA LEITURA DA SERIAL\n",
	0
};

int ret_mes ( int pt ){
	printf("%s\n", message[pt] );	return 0; 
}




/*linkSpeed == B1200 | B2400 | B4800 | B9600 */
int PortaConfig(const char* devName, int linkSpeed, struct termio* pOldTermio ) {
	int link_fd,errret=1;
	struct termio link_termio;
	if ( ( link_fd = open( devName, O_RDWR, 0666 ) ) < 0 ) {
		errret= ret_mes(20);
	}
	/* Verifica se e' uma interface serial */
	if (isatty(link_fd) == 0) {
		errret= ret_mes(21);
	}
	/* Recupera TERMIO desta interface */
	if (ioctl(link_fd, TCGETA, &link_termio) == -1 ) {
		errret= ret_mes(22);
	}
	/* Salva configuracao anterior se pedido */
	if (pOldTermio != NULL)
		memcpy(pOldTermio, &link_termio, sizeof(struct termio));

/*
 * TERMIO da interface serial 
 *
 *    B19200    19200 baud
 *    CS8       8 bits
 *    CSTOPB    2 stop-bits
 *    CREAD     enable receiver
 *
 * Alternativas para o campo 'cflag':
 *
 *    Velocidade: B1200, B2400, B4800, B9600, B19200
 *    Tamanho de caracter: CS5, CS6, CS7 ou CS8
 *    Stop bit: para 1 stop-bit remover CSTOPB
 *    Habilitar paridade: incluir PARENB (even parity enable)
 *    Tipo de paridade: incluir PARODD
 */

	/* Atribui novas caracteristicas a interface */

	link_termio.c_iflag = IGNBRK;
	link_termio.c_oflag = 0;
 switch (linkSpeed) {
  case 19200:link_termio.c_cflag = B19200 | CREAD | CS8;break;                 
  case  9600:link_termio.c_cflag = B9600 | CREAD | CS8;break;         
  case  4800:link_termio.c_cflag = B4800 | CREAD | CS8;break; 
  case  2400:link_termio.c_cflag = B2400 | CREAD | CS8;break; 
		case  1200:link_termio.c_cflag = B1200 | CREAD | CS8;break; 
 }
	link_termio.c_lflag = NOFLSH;
	link_termio.c_line  = 0;
	link_termio.c_cc[VMIN] = 0;
	link_termio.c_cc[VTIME] = 30;
	if (ioctl(link_fd, TCSETA, &link_termio) < 0) {
		PortaUnconfig(link_fd,pOldTermio);
		//close(link_fd);
		errret= ret_mes(23);
	}
	return(link_fd);
} 

int PortaUnconfig(int linkFd, struct termio* pOldTermio) {
	if(linkFd==0)return 0;
	/* Verifica se e' uma interface serial */
	if (isatty(linkFd) == 0)
		 ret_mes(21);
	/* Restaura configuracao anterior da interface */
	if (pOldTermio != NULL && ioctl(linkFd, TCSETA, pOldTermio) < 0)
		 ret_mes(22);
	close(linkFd);
	return(0);
} 
/* Retorna numero de bytes lido, 0 se fim, -1 se erro */
/* As variaveis globais time_out e flgto devem estar devidamente configuradas */
int inportb( int fileDescriptor, int timeOut ) {
	int byte;
	char buffer;
	int tentativa = timeOut;
	do {
		lseek(fileDescriptor,0,SEEK_SET);
		byte = read(fileDescriptor, &buffer, 1);
		if ( ( errno == EINTR ) && (byte <= 0) ) {
			tentativa--;
		}
		else {
			byte = buffer;
			break;
		}
	} while( tentativa );
	return ( byte );
}
/*----------------------------------------------------------------------------*/
int enviaENQ( int Porta ) {
	if(Porta==0)return 0;
	unsigned char BufTrm[ 100 ];
	int	ret;
 BufTrm[0] = 0x05;
 BufTrm[1] = 0x00;
	do {
		ret = write( Porta, BufTrm, 1 );
	} while( ret < 0 && errno == EINTR );
	if( ret < 0 ) 
		return ret_mes(12);
	return 1;
}

int enviabuf( int Porta,char *BufTrm,int lenght ) {
	if(Porta==0)return 0;
	int	ret;
	char *ptr=BufTrm,*lst=ptr+lenght-1;
	//for(;;ptr++)
	{
	//do {
		ret = write( Porta, BufTrm, lenght );
	//} while( ret < 0 && errno == EINTR );
	//if(ptr==lst)break;
	}
fcntl(Porta, F_SETFL, FNDELAY);
	if( ret < 0 ) 
		return ret_mes(12);
	return ret;
}
/*----------------------------------------------------------------------------*/
int recebeBuffer( int Porta,  char buffer[] ){
	if(Porta==0)return 0;
	int i;
	int ch;
	ch = inportb( Porta, NO_VEZES );
	if( ch == 0 )
		return (-1);
	if ( ch == EOT ) {
		buffer[ 0 ] = EOT;
		buffer[ 1 ] = '\0';
		return 1;
	}
	if ( ch != STX )
		return 0;
	i = 1;
	do {
		ch = inportb( Porta, NO_VEZES );
		if ( ch == -1 ) return 0;
		buffer[ i++ ] = ch;
	} while ( ch != ETX );
	/* Limpo o \x03 */
	//buffer[ i-1 ] = '\0';	
}

int recebeBuffer2( int Porta,  char buffer[] ){
	if(Porta==0)return 0;
	int i;
	int ch;
	ch = inportb( Porta, NO_VEZES );
	if( ch == 0 )
		return (-1);
	if ( ch == EOT ) {
		buffer[ 0 ] = EOT;
		buffer[ 1 ] = '\0';
		return 1;
	}
	if ( ch != STX )
		return 0;
	i = 0;
	do {
		ch = inportb( Porta, NO_VEZES );
		if ( ch == -1 ) return 0;
		buffer[ i++ ] = ch;
	} while ( ch != ETX );
	/* Limpo o \x03 */
 buffer[ i-1 ] = '\0';	
 return i-1;
}