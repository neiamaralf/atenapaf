
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
#include "wx/msgdlg.h"
#include "vilavilela.h"
#include "bematech.h"
#include "kernel.h"
#include "impressora_fiscal.h"

char Fiscal_Printer::ST1_ERRORS[][48]={
	"ST1 ok",
	"n�mero de par�metros de CMD inv�lido",
	"cupom aberto",
	"comando inexistente",
	"primeiro dado de CMD n�o foi ESC (1BH)",
	"impressora em erro",
	"erro no rel�gio",
	"pouco papel",
	"fim de papel",
};

char Fiscal_Printer::ST2_ERRORS[][48]={
	"ST2 ok",
	"comando n�o executado",
	"CGC/IE do propriet�rio n�o programados",
	"cancelamento n�o permitido",
	"capacidade de al�q. program�veis lotada",
	"al�quota n�o programada",
	"erro na Mem�ria RAM CMOS N�o Vol�til",
	"Mem�ria Fiscal lotada",
	"tipo de par�metro de CMD inv�lido"
};

bool Fiscal_Printer::parse_printer_bytes(char _ACK,char _ST1,char _ST2) {
	if (_ACK==0x15) {
		printf("Erro NAK:sequ�ncia incorreta ou timeout\n");
		return false;
	}
	else
		printf("recebimento ok\n");
	bool error=false;
	int i;
	if (_ST1!=0) {
		for (i=1;i<=7;i++)
			if (_ST1&(0x01<<i)) {
				printf("Erro ST1:%s\n",ST1_ERRORS[i]);
				error=true;
			}
	}
	else
		printf("ST1 ok\n");
	if (_ST2!=0) {
		for (i=1;i<=7;i++)
			if (_ST2&(0x01<<i)) {
				printf("Erro ST2:%s\n",ST2_ERRORS[i]);
				error=true;
			}
	}
	else
		printf("ST2 ok\n");
	return !error;
}

int Fiscal_Printer::montacmd(char **buf,char *cmd) {
	int lengc=(int)*cmd ;
	cmd++;
	char *ptr,*lstchar=cmd+lengc-1,*ptr2;
	long NB=2,CS=0;
	int lenght=lengc+5;
	for (ptr=cmd;;ptr++) {
		NB++;
		CS+=(long)*ptr;
		if (ptr==lstchar)
			break;
	}
	*buf=new char[lenght];
	ptr=*buf;
	*ptr=0x02;
	ptr++;
	*ptr=(char)(NB&0xff);
	ptr++;
	*ptr=(char)((NB&0xff00)>>8);
	lstchar=ptr+lengc;
	for (ptr++,ptr2=cmd;;ptr++,ptr2++) {
		*ptr=*ptr2;
		if (ptr==lstchar)
			break;
	}
	ptr++;
	*ptr=(char)(CS&0xff);
	ptr++;
	*ptr=(char)((NB&0xff00)>>8);
	return lenght;
}

HANDLE Fiscal_Printer::_AbrePorta(const char* devName,  termios *pnewTermio,  termios *pOldTermio) {
	HANDLE porta;
#ifdef WIN32
	BOOL fSuccess;
	porta = CreateFile(_(PORTACOM4),GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0, NULL);
	if (porta == INVALID_HANDLE_VALUE)
		return (0);
	SecureZeroMemory(pnewTermio, sizeof(DCB));
	pnewTermio->DCBlength = sizeof(DCB);
	fSuccess = GetCommState(porta, pnewTermio);
	if (!fSuccess)
		return 0;
	pnewTermio->BaudRate = CBR_9600;
	pnewTermio->ByteSize = 8;
	pnewTermio->Parity   = NOPARITY;
	pnewTermio->StopBits = ONESTOPBIT;
	pnewTermio->fDtrControl = DTR_CONTROL_ENABLE;
	pnewTermio->fRtsControl = RTS_CONTROL_ENABLE;
	GetCommState(porta, pOldTermio);
	fSuccess = SetCommState(porta, pnewTermio);
	if (!fSuccess)
		return 0;
	fSuccess = GetCommState(porta, pnewTermio);
	if (!fSuccess)
		return 0;
#else
	if ((porta = open(devName, O_RDWR | O_NOCTTY | O_NDELAY)) == -1) {
		printf("N�o foi poss�vel abrir a porta");
	}
	tcgetattr(porta, pOldTermio);
	memcpy(pnewTermio, pOldTermio, sizeof(struct termio));
	cfsetispeed(pnewTermio, B9600);
	cfsetospeed(pnewTermio, B9600);
	pnewTermio->c_iflag = IGNBRK;
	pnewTermio->c_oflag = 0;
	pnewTermio->c_cflag |= CS8;
	pnewTermio->c_cflag |= B9600;
	pnewTermio->c_cflag |= CRTSCTS;
	pnewTermio->c_lflag |= NOFLSH;
	pnewTermio->c_lflag |= CREAD;
	pnewTermio->c_line = 0;
	pnewTermio->c_cc [VMIN] = 0;
	pnewTermio->c_cc [VTIME] = 2;
	tcsetattr(porta, TCSANOW, pnewTermio);
#endif
	return porta;
}

int Fiscal_Printer::_WriteBytes(HANDLE porta,char *bytes,DWORD lenght) {
#ifdef WIN32
	WriteFile(porta,bytes,lenght,&lenght,NULL);
#else
	lenght=enviabuf(porta,bytes,lenght);
#endif
	return lenght;
}

int Fiscal_Printer::_ReadBytes(HANDLE porta,char *bytes,DWORD lenght) {
	DWORD BytesRead=0;
#ifdef WIN32
	ReadFile(porta, bytes, lenght, &BytesRead, NULL);
#else
	char *ptrbytes = bytes;//,valor=0;
//while (valor != 0x03){
	//for(int i=0;i<lenght;i++,ptrbytes++)
// BytesRead+=read(porta, ptrbytes, 1);
	/*enviaENQ(porta);
		BytesRead=	recebeBuffer2( porta, bytes );*/

	// BytesRead++;*ptrbytes=valor;ptrbytes++;
	//}
//}

	int valor = 0,count=0;
	int erro;
	while ((count++)<0x03) {
		if ((erro = read(porta, &valor, 1)) == 1) {
			printf("0x%2x\n",valor);
			*(ptrbytes++)=(char)valor;
			BytesRead++;
		}
	}
#endif
	return BytesRead;
}

void Fiscal_Printer::_FechaPorta(HANDLE porta,  termios* pOldTermio) {
#ifdef WIN32
	SetCommState(porta, pOldTermio);
	CloseHandle(porta);
#else
	//tcsetattr(porta, TCSANOW, pOldTermio);
	close(porta);
#endif
}

bool Fiscal_Printer::_sendcmdtoprinter(char *cmdbuf,char *bufread,DWORD lenghtread,DWORD *BytesRead) {
	char *bbuf;
	DWORD write, _BytesRead = 0;
	HANDLE hCom;
	termios pnewTermio, pOldTermio;
	hCom =_AbrePorta(PORTACOM4, &pnewTermio, &pOldTermio);
	if (hCom==0)
		return false;
	write= montacmd(&bbuf,cmdbuf);
	write=_WriteBytes(hCom,bbuf,write);
	if (write>0) {
		delete []bbuf;
		if (lenghtread>0) {
			_BytesRead=_ReadBytes(hCom,bufread,lenghtread);
			if (_BytesRead>0)
				parse_printer_bytes(bufread[0],bufread[1],bufread[2]);
			else
				printf("erro leitura\n");
		}
		if (BytesRead)
			*BytesRead=_BytesRead;
	}
	_FechaPorta(hCom,&pOldTermio);
	return (write>0);
}

int Fiscal_Printer::reducao_X() {
	char bufread[3];
	DWORD _BytesRead;
	char cmd[]={	2,0x1b,0x06};
	_sendcmdtoprinter(cmd,bufread,3,&_BytesRead);
	return 1;
}

int Fiscal_Printer::abre_cupom_fiscal() {
	char bufread[3];
	DWORD _BytesRead;
	char cmd[]={	2,0x1b,0x00};
	if (!_sendcmdtoprinter(cmd,bufread,3,&_BytesRead))
		printf("erro envio dado");
	return 1;
}

int Fiscal_Printer::cancela_cupom_fiscal() {
	char bufread[3];
	DWORD _BytesRead;
	char cmd[]={2,0x1b,0x0e};
	_sendcmdtoprinter(cmd,bufread,3,&_BytesRead);
	return 1;
}


void Analisa_RetornoImpressora() {
	int _ACK,ST1,ST2;
	wxString Erros = _("");
	_ACK = ST1 = ST2 =0;
	IMPRESSORA_FISCAL::_RetornoImpressora(&_ACK,&ST1,&ST2);
	if (ST1&128)Erros += ___("BIT 7 - Fim de Papel\x0D");
	if (ST1&64) Erros +=___("BIT 6 - Pouco Papel\x0D");
	if (ST1&32) Erros +=___("BIT 5 - Erro no Rel�gio\x0D");
	if (ST1&16) Erros +=___("BIT 4 - Impressora em ERRO\x0D");
	if (ST1&8)  Erros +=___("BIT 3 - CMD n�o iniciado com ESC\x0D");
	if (ST1&4)  Erros +=___("BIT 2 - Comando Inexistente\x0D");
	if (ST1&2)  Erros +=___("BIT 1 - Cupom Aberto\x0D");
	if (ST1&1)  Erros +=___("BIT 0 - N� de Par�metros Inv�lidos\x0D");

	if (ST2&128)Erros +=___("BIT 7 - Tipo de Par�metro Inv�lido\x0D");
	if (ST2&64) Erros +=___("BIT 6 - Mem�ria Fiscal Lotada\x0D");
	if (ST2&32) Erros +=___("BIT 5 - CMOS n�o Vol�til\x0D");
	if (ST2&16) Erros +=___("BIT 4 - Al�quota N�o Programada\x0D");
	if (ST2&8)  Erros +=___("BIT 3 - Al�quotas lotadas\x0D");
	if (ST2&4)  Erros +=___("BIT 2 - Cancelamento � Permitido\x0D");
	if (ST2&2)  Erros +=___("BIT 1 - CGC/IE n�o Programados\x0D");
	if (ST2&1)  Erros +=___("BIT 0 - Comando n�o Executado\x0D");
	if (Erros.Length() != 0)
		wxMessageBox(Erros,___("Erro na Execu��o do Comando"));
}

bool VilaVilela::Analisa_iRetorno(int IRetorno) {
	MODOTESTE() false;
	wxString MSG = _("");
	switch (IRetorno)	{
	case  0:	MSG = ___("Erro de Comunica��o !");	break;
	case -1:	MSG = ___("Erro de Execu��o na Fun��o. Verifique!");	break;
	case -2:	MSG = ___("Par�metro Inv�lido !");	break;
	case -3: MSG = ___("Al�quota n�o programada !");	break;
	case -4:	MSG = ___("Arquivo BemaFI32.INI n�o encontrado. Verifique!");	break;
	case -5:	MSG = ___("Erro ao Abrir a Porta de Comunica��o");	break;
	case -6:	MSG = ___("Impressora Desligada ou Desconectada.");	break;
	case -7:	MSG = ___("Banco N�o Cadastrado no Arquivo BemaFI32.ini");	break;
	case -8:	MSG = ___("Erro ao Criar ou Gravar no Arquivo Retorno.txt ou Status.txt.");	break;
	case -18:	MSG = ___("N�o foi poss�vel abrir arquivo INTPOS.001!");	break;
	case -19:	MSG = ___("Par�metros diferentes!");	break;
	case -20:	MSG = ___("Transa��o cancelada pelo Operador!");	break;
	case -21:	MSG = ___("A Transa��o n�o foi aprovada!");	break;
	case -22:	MSG = ___("N�o foi poss�vel terminar a Impress�o!");	break;
	case -23:	MSG = ___("N�o foi poss�vel terminar a Opera��o!");	break;
	case -24:	MSG = ___("N�o foi poss�vel terminal a Opera��o!");	break;
	case -25:	MSG = ___("Totalizador n�o fiscal n�o programado.");	break;
	case -26:	MSG = ___("Transa��o j� Efetuada!");	break;
	case -27:	Analisa_RetornoImpressora();	break;
	case -28:	MSG = ___("N�o h� Informa��es para serem Impressas!");	break;
	}
	if (MSG.Length() != 0) {
		wxMessageBox(MSG,_("Erro"));
		return false;
	}
	return true;
}



