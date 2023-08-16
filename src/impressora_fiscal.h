#ifndef impressora_fiscalH
#define impressora_fiscalH
#include <string.h>

#include "listas.h"
 

#define MODELO_IMPRESSORA vilavielaframe->MODELO_IMPRESSORA

#define BEMATECH_MATRICIAL (MODELO_IMPRESSORA==Bematech_MP_20_FI_II||MODELO_IMPRESSORA==Bematech_MP_40_FI_II)
#define SWEDA_MATRICIAL (MODELO_IMPRESSORA==Sweda_Matricial)
#define SWEDA_TERMICA (MODELO_IMPRESSORA==Sweda_Termica)
#define SWEDA_TODOSOSMODELOS SWEDA_MATRICIAL||SWEDA_TERMICA
#define BEMATECH_MATRICIAL_MFD (MODELO_IMPRESSORA==Bematech_MP_25_FI||MODELO_IMPRESSORA==Bematech_MP_50_FI)
#define BEMATECH_TERMICAS (MODELO_IMPRESSORA==Bematech_MP_2000_TH_FI||MODELO_IMPRESSORA==Bematech_MP_2100_TH_FI ||MODELO_IMPRESSORA==Bematech_MP_3000_TH_FI ||\
	MODELO_IMPRESSORA==Bematech_MP_4000_TH_FI ||MODELO_IMPRESSORA==Bematech_MP_6000_TH_FI ||MODELO_IMPRESSORA==Bematech_MP_6100_TH_FI ||MODELO_IMPRESSORA==Bematech_MP_7000_TH_FI)
#define BEMATECH_TODOSOSMODELOS BEMATECH_MATRICIAL||BEMATECH_MATRICIAL_MFD||BEMATECH_TERMICAS
#define BEMATECH_MFD (MODELO_IMPRESSORA==Bematech_MP_2000_TH_FI||MODELO_IMPRESSORA==Bematech_MP_6000_TH_FI)
#define BEMATECH_MFD2 (MODELO_IMPRESSORA==Bematech_MP_2100_TH_FI||MODELO_IMPRESSORA==Bematech_MP_3000_TH_FI||\
MODELO_IMPRESSORA==Bematech_MP_4000_TH_FI||MODELO_IMPRESSORA==Bematech_MP_6100_TH_FI||\
MODELO_IMPRESSORA==Bematech_MP_7000_TH_FI||MODELO_IMPRESSORA==Bematech_MP_25_FI||MODELO_IMPRESSORA==Bematech_MP_50_FI)

#define REDZ_CRZ 1
#define REDZ_COO 2
#define REDZ_TOTALBRUTO 3
#define REDZ_CRO 4
#define REDZ_TOTALIZADORES_PARCIAIS 5

class clTotalizadorParcial{
public:
	clTotalizadorParcial *ant,*prx;
	int valacumulado;
	char abrev[16];
};

class ListTotalizadorParcial2:public Lista<clTotalizadorParcial>{
public:
	void novo(	int valacumulado,char *abrev){
		novoptr();
		ult->valacumulado=valacumulado;		
		strcpy(ult->abrev,abrev);	
	}
};


namespace IMPRESSORA_FISCAL{
	extern bool testa_impressora();
	extern int _GrandeTotal(char *GT);
	extern int _RetornoImpressora(int *_ACK,int *ST1,int *ST2);
	extern int _VerificaEstadoImpressora(int *_ACK,int *ST1,int *ST2);
	extern bool _cupomaberto();
	extern int _LeituraX();
	extern int _ProgramaAliquota(char *buf,int tipo/*0=ICMS,1=ISS*/);
	extern int _LeituraMemoriaFiscalData(char *dataini,char *datafim,int flag/*0=completa,1=simplificada*/);
	extern int _LeituraMemoriaFiscalReducao(char *redi,char *redf,int flag);
	extern int _LeituraMemoriaFiscalSerialData(char *dataini,char *datafim,int flag/*0=completa,1=simplificada*/);
	extern int _LeituraMemoriaFiscalSerialReducao(char *redi,char *redf,int flag);
	extern int _LeituraXSerial();
	extern int _FechamentoDoDia();
	extern int _AberturaDoDia(char *valor,char *fpagto);
	extern int _ReducaoZ(char *data,char *hora);
	extern int _nome_contribuinte(char *nomecontribuite);
	extern int _end_contribuinte(char *endcontribuinte);
	extern int _NumeroCaixa(char *NumeroCaixa);
	extern int _NumeroIntervencoes(char *numintervencoes);
	extern int _NumeroReducoes(char *numreducoes);
	extern int _NumSerieImpressora(char *buf);
	extern int _MarcaModeloTipoImpressora(char *marca,char *modelo,char *tipo);
	extern int _VersaoSB(char *vSB);
	extern int _CGC_IE(char *CNPJUSUARIO,char *IEUSUARIO);
	extern int _NumSubstituicoes(char *buf);
	extern int _geracotepe1704_COO( char *fnameCotep1704,char *COOi,char *COOf,int tipo);
	extern int _geracotepe1704_DATA( char *fnameCotep1704,char *dti,char *dtf,int tipo);
	extern int _DownloadMF();
	extern int  _DownloadMFD_DATA(char* DataInicial,char* DataFinal);
	extern int  _DownloadMFD_COO(char* COOInicial,char* COOFinal);
	extern int _DadosUltRedZ(char **buf,int *size,bool sintegra=false,char *datamovsintegra=0);
	extern bool _retornasDadoUltRedZ(char *bufdados,int size,int DADOARETORNAR,char *bufret,ListTotalizadorParcial2 *lsttot=0);
	extern bool _DataMovUltRedZ(char *Data_do_movimento);
	extern int _DHUsuario_DHSB_MFAdicional(char dataUsuario[21],char dataSWBasico[21],char horaUsuario[21],char horaSWBasico[21],char *MFAdicional);
	extern int _VersaoDll(char *versaodll);
	extern int _dataehoraEmissaoRZ(char *Data_de_emissao,char *Hora_de_emissao);
	extern int _ContadorCupomFiscal(bool incidr04,char *sCupom);
	extern int _NumeroCupom(char *NumeroCupom);
	extern int _DataHoraImpressora(char *Data,char *Hora);
	extern int _SubTotal(char *SubTotal );
	extern int _UltimoItemVendido(char *UltimoItem);
	extern int _VerificaTruncamento(char *IAT);
	extern int _ContadorOperacoesNaoFiscal(char *nop);
	extern int _Contador_GRG(char *CRG,bool update=false);
	extern int _Contador_de_CDC(char *CDC,bool update=false);
	extern int _DataHoraUltimoMovimento(char *Data,char *Hora);
	extern int _abre_cupom(char *cgc,char *nome,char *end);
	extern int _cancela_cupom(char* Meio_de_pagamento,char *cgc,char *nome,char *end,bool criaR06=false);
	extern int _CancelaItem( char *item);
	extern int _cancela_cupom();
	extern int _FechaCupom(char *cFormaPgto,bool desconto_percentual,char* cValorAcresDesc,char *cValorPago);
	extern int _VendeItem(char *cCodigo,char *cDescricao ,char *cAliquota,char *cTipoQtde ,char *cValor ,char *cQtde ,char *cUnidade);
	extern int _VerificaFormasPagamento(char *sFgto);
	extern	int _atualiza_dados_impressora(bool incidr04=true,bool atualizaCCFeCOO=true);
	extern	int _marca_impressora(bool incidr04=true,bool atualizaCCFeCOO=true);
	extern	int _FormatoDadosMFD_DATA(char *fdest,char* DataInicial,char* DataFinal);
	extern	int _FormatoDadosMFD_COO(char *fdest,char* COOi,char* COOf);
 extern int _RelatorioGerencial(char *text);
 extern int _FechaRelatorioGerencial();
};
#define COTEPE1704_MF 0
#define COTEPE1704_MFD 1
#endif
