#ifndef relatoriosH
#define relatoriosH
#include <stdlib.h>
#include  <stdio.h>


#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/objects.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include "listas.h"
#include "wx/progdlg.h"
#include "wx/datetime.h"

#define INIT_PROGRESS_INFO(caption,text,_max,owner)\
	static const int max = _max;\
	wxProgressDialog progress(_(caption),_(text),max,owner,\
	/*	wxPD_CAN_ABORT |*/wxPD_APP_MODAL |wxPD_ELAPSED_TIME |wxPD_ESTIMATED_TIME |wxPD_REMAINING_TIME|wxPD_AUTO_HIDE);\
	bool cont = true;

#define UPDATE_PROGRESS(_i,_text)\
	cont = progress.Update(_i, _(_text));	\
	if (!cont)	{if ( wxMessageBox(_("Você realmente quer cancelar?"),_("Confirmação"),wxYES_NO | wxICON_QUESTION) == wxYES )	return;progress.Resume();}

#define UPDATE_PROGRESS2(_i,_text)\
	cont = progress.Update(_i, _(_text));	


class TotalizadorParcial{
public:
	TotalizadorParcial *ant,*prx;
	int Valor_acumulado;
	char codigo[8];
};

class ListTotalizadorParcial:public Lista<TotalizadorParcial>{
public:
	void novo(const char *codigo,int Valor_acumulado);
};

class RedZ{
public:
	RedZ *ant,*prx;
	int nouser,crz,cro,hora,vendabrutadiaria;
	long data;
	ListTotalizadorParcial totalizadores;
};

class ListRedZ:public Lista<RedZ>{
public:
	void novo(int nouser,int crz,int cro,long data,int hora,int vendabrutadiaria);
};

class _String{
public:
	_String *ant,*prx;
	wxString str;
};

class List_String:public Lista<_String>{
public:
	void novo(const char* str);
};


#define Conferencia_de_Mesa "CM"
#define Registro_de_Venda "RV"
#define Comprovante_de_CD "CC"
#define Comprovante_NFiscal "CN"
#define Comprovante_NFiscal_Cancel "NC"
#define Relatorio_Gerencial "RG"

namespace RELATORIOS{
	namespace assinatura{
		extern	int savexml(char *pubmod,int lenght);
		extern	void createprivatekey();
		extern	void n_printf(unsigned char *str, int lenght);
		extern	void n_fprintf(FILE *f,unsigned char *str, int lenght);
		extern	EVP_PKEY * ReadPublicKey(const char *pkeyfile);
		extern	EVP_PKEY *ReadPrivateKey(const char *keyfile);
		extern	int  _encrypt( const unsigned char *_message,int lenght,unsigned char **_encryptedmessage);
		extern	int _decrypt(const unsigned char  *_encryptedmessage,int lenght,unsigned char  **_decriypted);
		extern	void monta128byteshash(FILE *file,char buf[16],unsigned char blk[128]);
		extern	char retdigit(char digit);
		extern	char retbyte(char byte[2]);
		extern	bool sign_file(const char *filename);
	};

	namespace requisitoIX{
		extern void registro_N1(FILE *file,const char *cnpj,const char *IE,const char *IM,const char *razaosocial);
		extern void registro_N2(FILE *file,const char *nolaudo,const char *nomeaplicativo,const char *versaoaplicativo);
		extern void registro_N3(FILE *file,const char *nomeexe);
		extern void registro_N9(FILE *file,const char *cnpj,const char *IE,int quantN3);
		extern void gravalistaexecutaveis();
	};
	
	namespace requisitoXX{
			extern	void gravarequisitoXX();
	};
	
	namespace requisitoVII_8{
		extern void estoquetotal();
	};
	
	namespace requisitoXXII{	
		extern void criptografa_buf(const char *fname,char *buf);
		extern void criptografa_arqaux();
		extern int descriptografa_arquivo(const char* fname,char **dbuf);
		extern void restaura_arquivo_auxiliar(const char *fname);
		extern bool ECF_autorizada(char *bd,int sz,char CNI[7]);
		extern void atualiza_arquivo_auxiliar(const char *campo,char *bd,int sz,const char *novovalor,char *valorantigo,bool atualiza,bool retorna,List_String *lst=0);
	};
	
	
	namespace requisitoXXV{
		extern	void gravarequisitoXXV(char *Dataini,char *Datafinal,bool dataatual,const char *ecfnoserie);
		extern void grava_registro_R01(FILE *file,char *Dataini,char *Datafinal);
		extern	void registro_R02_R03();
		extern	void registro_R04(char* Meio_de_pagamento,char *Nome_do_adquirente,char *CPF_CNPJ_do_adquirente,bool cancelado,bool criaR06=false);
		extern	void registro_R05(char *Numero_de_fabricacao,char *MF_adicional,char *Modelo_do_ECF,char *Numero_do_usuario,char *CCF_CVC_ou_CBP,
	char *COO,char *IAT,char *Cod_do_Produto_ou_Servico,char *Descricao,char *Quantidade,char *Unidade,char *Valor_unitario,
	char *Valor_total_liquido,char *Totalizador_parcial,bool cancelado,char* Casas_decimais_da_quantidade);
		extern void registro_R06(char *Valor_pago,char* Meio_de_pagamento,const char* Denominacao,bool estorno,char *Valor_estornado);
		extern void registro_R07(const char *Numero_de_fabricacao,const char *MF_adicional,const char *Modelo_do_ECF,const char *Numero_do_usuario,const char *COO,const char* Meio_de_pagamento, char *Valor_pago,bool estorno=false,const char *Valor_estornado="0");
	};


	namespace utils{
		extern void getdateandhourcotepe(wxDateTime &dt,char *data,char *hora);
		extern void mostralocalgravacaoarquivos(const char *fname,char *_dir=NULL); 
		extern char* caixaalta( char* s );
		extern void _md5_executavel(const char *executavel,char buf[33]);
		extern void _atualiza_items_cupom_cancelado();
		extern	void _copyfile (FILE *inFile,FILE *outFile);
		extern	void mountcotepefname(const char *prefix,char *buf);
		extern	void saveretornoimpressora(const char *prefix,char *buffname=0);
		extern			void removechar(char *str,char toremove);
		extern	void skipline(FILE *f);
		extern	void skipspaces(FILE *f);
		extern	int readline(FILE *f,char *buf);
		extern	void skipsection(FILE *f);
		extern	long formatdata(char *datastr);
		extern long formatdata2(char *datastr);
		extern	void transformadataparaFormatoCotepe(char *data);
		extern	char* le_ate_car(char *b,char car,int size);
		extern	char* le_enquanto_car(char *b,char car,int size);
		extern	char* le_ate_fim_linha(char *bufin,char *bufout,int nlinhas=1);
		extern int _load_file_to_buf(const char *filename, char **result,bool nulllast=true) ;
	};

	namespace atoCOTEP1704{
		extern	void cria_relatorio_atoCOTEP1704(const char *arqmemfiscal);
		extern	void criaregistroE01(ListRedZ *lstredz,FILE *MF,const char *arqmemfiscal);
		extern	void criaregistroE02(FILE *MF,const char *arqmemfiscal);
		//INSERIR registroE05 p/ impressoras termicao
		extern	void criaregistroE04(FILE *MF,const char *arqmemfiscal);
		extern	void criaregistroE09(FILE *MF,const char *arqmemfiscal);
		extern	void criaregistroE11(FILE *MF,const char *arqmemfiscal);
		extern	void criaregistroE12(FILE *MF,const char *arqmemfiscal,ListRedZ *lstredz);

	};
};


#endif
