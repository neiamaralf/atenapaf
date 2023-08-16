#include "daruma.h"

static void* bibliotecaDinamica = NULL;

/**
Carrega a DarumaFramework para a memória.
*/
void carregarDarumaFramework() {
	string erro = NULL;
	if(!bibliotecaDinamica) {
#ifdef WIN32
		bibliotecaDinamica = LoadLibrary(TEXT("DarumaFrameWork.dll"));
#else
		bibliotecaDinamica = dlopen("./libDarumaFramework.so", RTLD_NOW);
#endif
	}

	if (!bibliotecaDinamica) {
#ifdef WIN32
		erro = (string) GetLastError();
#else
		erro = dlerror();
#endif
		printf("Erro ao carregar a DarumaFrameWork: %s.\n", erro);
		exit(EXIT_FAILURE);
	}
}

/**
Descarrega a DarumaFramework da memória.
*/
void descarregarDarumaFramework() {
	string erro = NULL;
	int descarregou = 0;

	if (bibliotecaDinamica) {
#ifdef WIN32
		descarregou = FreeLibrary((HMODULE) bibliotecaDinamica);
#else
		descarregou = dlclose(bibliotecaDinamica);
#endif
	}

	if (!descarregou) {
#ifdef WIN32
		erro = (string) GetLastError();
#else
		erro = dlerror();
#endif
		printf("Erro ao descarregar a DarumaFrameWork: %s\n", erro);
	}

}

/**
@param nomeFuncao nome da função a ser carregada da memória.
@return ponteiro para função ou NULL;
*/
void* carregarFuncaoDarumaFramework(const string nomeFuncao) {
	void* funcao = NULL;
	string erro = NULL;

	if (!bibliotecaDinamica) {
		carregarDarumaFramework();
	}

#ifdef WIN32
	funcao = GetProcAddress((HMODULE) bibliotecaDinamica, nomeFuncao);
#else
	funcao = dlsym(bibliotecaDinamica, nomeFuncao);
#endif

	if (!funcao) 
	{
#ifdef WIN32
		erro = (string) GetLastError();
#else
		erro = dlerror();
#endif
		printf("Erro ao carregar a funcao %s: %s\n", nomeFuncao, erro);
	}

	return funcao;
}

//FUNCOES ECF 

#pragma region ECF_CUPOM_FISCAL //OK

// Abertura de cupom fiscal
int iCFAbrir_ECF_Daruma(string CPF, string Nome, string Endereco) {
	return ((FUNCAO_P (string, string, string)) carregarFuncaoDarumaFramework("iCFAbrir_ECF_Daruma")) (CPF,  Nome,  Endereco);
}	
int iCFAbrirPadrao_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iCFAbrirPadrao_ECF_Daruma")) ();
}

// Registro de item
int iCFVender_ECF_Daruma(string CargaTributaria, string Quantidade, string PrecoUnitario, string TipoDescAcresc, string ValorDescAcresc, string CodigoItem, string UnidadeMedida, string DescricaoItem) {
	return ((FUNCAO_P (string, string, string, string, string, string, string, string)) carregarFuncaoDarumaFramework("iCFVender_ECF_Daruma")) (CargaTributaria,  Quantidade,  PrecoUnitario,  TipoDescAcresc,  ValorDescAcresc,  CodigoItem,  UnidadeMedida,  DescricaoItem);
}	
int iCFVenderSemDesc_ECF_Daruma(string CargaTributaria, string Quantidade, string PrecoUnitario, string CodigoItem, string UnidadeMedida, string DescricaoItem) {
	return ((FUNCAO_P (string, string, string, string, string, string)) carregarFuncaoDarumaFramework("iCFVenderSemDesc_ECF_Daruma")) (CargaTributaria,  Quantidade,  PrecoUnitario,  CodigoItem,  UnidadeMedida,  DescricaoItem);
}
int iCFVenderResumido_ECF_Daruma(string CargaTributaria, string PrecoUnitario, string CodigoItem, string DescricaoItem) {
	return ((FUNCAO_P (string, string, string, string)) carregarFuncaoDarumaFramework("iCFVenderResumido_ECF_Daruma")) (CargaTributaria,  PrecoUnitario,  CodigoItem,  DescricaoItem);
}

// Desconto ou acrescimo  em item de cupom fiscal
int iCFLancarAcrescimoItem_ECF_Daruma(string NumItem, string TipoDescAcresc, string ValorDescAcresc) {
	return ((FUNCAO_P (string, string, string)) carregarFuncaoDarumaFramework("iCFLancarAcrescimoItem_ECF_Daruma")) (NumItem, TipoDescAcresc, ValorDescAcresc);
}
int iCFLancarDescontoItem_ECF_Daruma(string NumItem, string TipoDescAcresc, string ValorDescAcresc) {
	return ((FUNCAO_P (string, string, string)) carregarFuncaoDarumaFramework("iCFLancarDescontoItem_ECF_Daruma")) (NumItem, TipoDescAcresc, ValorDescAcresc);
}
int iCFLancarAcrescimoUltimoItem_ECF_Daruma(string TipoDescAcresc, string ValorDescAcresc) {
	return ((FUNCAO_P (string, string)) carregarFuncaoDarumaFramework("iCFLancarAcrescimoUltimoItem_ECF_Daruma")) (TipoDescAcresc, ValorDescAcresc);
}
int iCFLancarDescontoUltimoItem_ECF_Daruma(string TipoDescAcresc, string ValorDescAcresc) {
	return ((FUNCAO_P (string, string)) carregarFuncaoDarumaFramework("iCFLancarDescontoUltimoItem_ECF_Daruma")) (TipoDescAcresc, ValorDescAcresc);
}

// Cancelamento total de item em cupom fiscal
int iCFCancelarItem_ECF_Daruma(string NumItem) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("iCFCancelarItem_ECF_Daruma")) (NumItem);
}
int iCFCancelarUltimoItem_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iCFCancelarUltimoItem_ECF_Daruma")) ();
}

// Cancelamento parcial de item em cupom fiscal
int iCFCancelarItemParcial_ECF_Daruma(string NumItem, string Quantidade) {
	return ((FUNCAO_P (string, string)) carregarFuncaoDarumaFramework("iCFCancelarItemParcial_ECF_Daruma")) (NumItem, Quantidade);
}
int iCFCancelarUltimoItemParcial_ECF_Daruma(string Quantidade) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("iCFCancelarUltimoItemParcial_ECF_Daruma")) (Quantidade);
}

// Cancelamento de desconto em item
int iCFCancelarDescontoItem_ECF_Daruma(string NumItem) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("iCFCancelarDescontoItem_ECF_Daruma")) (NumItem);
}
int iCFCancelarDescontoUltimoItem_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iCFCancelarDescontoUltimoItem_ECF_Daruma")) ();
}

// Totalizacao de cupom fiscal
int iCFTotalizarCupom_ECF_Daruma(string TipoDescAcresc, string ValorDescAcresc) {
	return ((FUNCAO_P (string, string)) carregarFuncaoDarumaFramework("iCFTotalizarCupom_ECF_Daruma")) (TipoDescAcresc, ValorDescAcresc);
}
int iCFTotalizarCupomPadrao_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iCFTotalizarCupomPadrao_ECF_Daruma")) ();
}

//Cancelamento de desconto e acrescimo em subtotal de cupom fiscal
int iCFCancelarDescontoSubtotal_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iCFCancelarDescontoSubtotal_ECF_Daruma")) ();
}
int iCFCancelarAcrescimoSubtotal_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iCFCancelarAcrescimoSubtotal_ECF_Daruma")) ();
}

//Descricao do meios de pagamento de cupom fiscal
int iCFEfetuarPagamentoPadrao_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iCFEfetuarPagamentoPadrao_ECF_Daruma")) ();
}
int iCFEfetuarPagamentoFormatado_ECF_Daruma(string FormaPgto, string Valor) {
	return ((FUNCAO_P (string, string)) carregarFuncaoDarumaFramework("iCFEfetuarPagamentoFormatado_ECF_Daruma")) (FormaPgto, Valor);
}
int iCFEfetuarPagamento_ECF_Daruma(string FormaPgto, string Valor, string InfoAdicional) {
	return ((FUNCAO_P (string, string, string)) carregarFuncaoDarumaFramework("iCFEfetuarPagamento_ECF_Daruma")) (FormaPgto, Valor, InfoAdicional);
}

//Encerramento de cupom fiscal
int iCFEncerrarPadrao_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iCFEncerrarPadrao_ECF_Daruma")) ();
}
int iCFEncerrarConfigMsg_ECF_Daruma(string Mensagem) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("iCFEncerrarConfigMsg_ECF_Daruma")) (Mensagem);
}
int iCFEncerrar_ECF_Daruma(string CupomAdicional, string Mensagem) {
	return ((FUNCAO_P (string, string)) carregarFuncaoDarumaFramework("iCFEncerrarConfigMsg_ECF_Daruma")) (CupomAdicional, Mensagem);
}
int iCFEncerrarResumido_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iCFEncerrarResumido_ECF_Daruma")) ();
}
int iCFEmitirCupomAdicional_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iCFEmitirCupomAdicional_ECF_Daruma")) ();
}

//Cancelamento de cupom fiscal
int iCFCancelar_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iCFCancelar_ECF_Daruma")) ();
}

//Identificar consumidor rodape do Cupom fiscal
int iCFIdentificarConsumidor_ECF_Daruma(char *pszNome, char *pszEndereco, char *pszDoc) {
	return ((FUNCAO_P (char *, char *, char *)) carregarFuncaoDarumaFramework("iCFIdentificarConsumidor_ECF_Daruma")) (pszNome, pszEndereco, pszDoc);
}

//Bilhete Passagem
int iCFBPAbrir_ECF_Daruma(char *Origem,char *Destino, char *Destino_UF,char *Percurso, char *Prestadora, char *Plataforma, char *Poltrona, char *Modalidade, char *Categoria, char *DataHora_Embarque,char *RGPassageiro, char *NomePassageiro, char *EnderecoPassageiro) {
	return ((FUNCAO_P (char *, char *, char *, char *, char *, char *, char *, char *, char *, char *, char *, char *, char *)) carregarFuncaoDarumaFramework("iCFBPAbrir_ECF_Daruma")) (Origem,Destino, Destino_UF,Percurso, Prestadora, Plataforma, Poltrona, Modalidade, Categoria, DataHora_Embarque,RGPassageiro, NomePassageiro, EnderecoPassageiro);
}
int iCFBPVender_ECF_Daruma(char *pszAliquota, char *pszValor, char *pszTipoDescAcresc, char *pszValorDescAcresc, char *pszDescricao) {
	return ((FUNCAO_P (char *, char *, char *, char *, char *)) carregarFuncaoDarumaFramework("iCFBPVender_ECF_Daruma")) (pszAliquota, pszValor, pszTipoDescAcresc, pszValorDescAcresc, pszDescricao);
}
int confCFBPProgramarUF_ECF_Daruma(char *pszUF) {
	return ((FUNCAO_P (char *)) carregarFuncaoDarumaFramework("confCFBPProgramarUF_ECF_Daruma")) (pszUF);
}

#pragma endregion

#pragma region ECF_DOWNLOAD_MEMORIAS //OK

//Download das Memórias - MF/MFD/TDM
int rEfetuarDownloadMFD_ECF_Daruma(char *pszTipo, char *pszInicial, char *pszFinal, char *pszNomeArquivo) {
	return ((FUNCAO_P (char *, char *, char *, char *)) carregarFuncaoDarumaFramework("rEfetuarDownloadMFD_ECF_Daruma")) (pszTipo, pszInicial, pszFinal, pszNomeArquivo);
}
int rEfetuarDownloadMF_ECF_Daruma(char *pszTipo, char *pszInicial, char *pszFinal, char *pszNomeArquivo) {
	return ((FUNCAO_P (char *, char *, char *, char *)) carregarFuncaoDarumaFramework("rEfetuarDownloadMF_ECF_Daruma")) (pszTipo, pszInicial, pszFinal, pszNomeArquivo);
}
int rEfetuarDownloadTDM_ECF_Daruma(char *pszTipo, char *pszInicial, char *pszFinal, char *pszNomeArquivo) {
	return ((FUNCAO_P (char *, char *, char *, char *)) carregarFuncaoDarumaFramework("rEfetuarDownloadMF_ECF_Daruma")) (pszTipo, pszInicial, pszFinal, pszNomeArquivo);
}

#pragma endregion

#pragma region PAF-ECF
//MD5
int rCalcularMD5_ECF_Daruma(string pszPathArquivo, char * pszMD5GeradoHex, char * pszMD5GeradoAscii) {
	return ((FUNCAO_P (string, char *, char *)) carregarFuncaoDarumaFramework("rCalcularMD5_ECF_Daruma"))( pszPathArquivo, pszMD5GeradoHex, pszMD5GeradoAscii);	
}
//RSA-EAD 
int rAssinarRSA_ECF_Daruma(string pszPathArquivo, string pszChavePrivada, char * pszAssinaturaGerada) {
	return ((FUNCAO_P (string, string, char *)) carregarFuncaoDarumaFramework("rAssinarRSA_ECF_Daruma"))( pszPathArquivo, pszChavePrivada, pszAssinaturaGerada);
}
//GT CODIFICADO
int rRetornarGTCodificado_ECF_Daruma(char*pszValor) {
	return ((FUNCAO_P (char *)) carregarFuncaoDarumaFramework("rRetornarGTCodificado_ECF_Daruma"))( pszValor);
}
int rVerificarGTCodificado_ECF_Daruma(char*pszValor) {
	return ((FUNCAO_P (char *)) carregarFuncaoDarumaFramework("rVerificarGTCodificado_ECF_Daruma"))( pszValor);
}
//NUMERO DE SERIE CODIFICADO
int rRetornarNumeroSerieCodificado_ECF_Daruma(char*pszValor) {
	return ((FUNCAO_P (char *)) carregarFuncaoDarumaFramework("rRetornarNumeroSerieCodificado_ECF_Daruma"))(pszValor);
}
int rVerificarNumeroSerieCodificado_ECF_Daruma(char*pszValor) {
	return ((FUNCAO_P (char *)) carregarFuncaoDarumaFramework("rVerificarNumeroSerieCodificado_ECF_Daruma"))(pszValor);
}
//Codigo Modelo Fiscal
int rCodigoModeloFiscal_ECF_Daruma(char*pszValor) {
	return ((FUNCAO_P (char *)) carregarFuncaoDarumaFramework("rCodigoModeloFiscal_ECF_Daruma"))(pszValor);
}

#pragma endregion

#pragma region ECF_METODOS_RETORNO_STATUS
//Status Cupom Fiscal
int rCFVerificarStatus_ECF_Daruma(char *cStatus, int *piStatus) {
	return ((FUNCAO_P (char *, int *)) carregarFuncaoDarumaFramework("rCFVerificarStatus_ECF_Daruma")) (cStatus, piStatus);
}

//Status ultimo comando
int rStatusUltimoCmd_ECF_Daruma(char *Erro, char *Aviso, int *piErro, int *piAviso) {
	return ((FUNCAO_P (string, string, int *, int *)) carregarFuncaoDarumaFramework("rStatusUltimoCmd_ECF_Daruma")) (Erro, Aviso, piErro, piAviso);
}
int rStatusUltimoCmdInt_ECF_Daruma(int *cErro, int *piAviso) {
	return ((FUNCAO_P (int *, int *)) carregarFuncaoDarumaFramework("rStatusUltimoCmdInt_ECF_Daruma")) (cErro, piAviso);
}


//Status Impressora
int rDataHoraImpressora_ECF_Daruma(string Data, string Hora) {
	return ((FUNCAO_P (string, string)) carregarFuncaoDarumaFramework("rDataHoraImpressora_ECF_Daruma")) (Data, Hora);
}
int rVerificarImpressoraLigada_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("rVerificarImpressoraLigada_ECF_Daruma")) ();
}
int rStatusImpressora_ECF_Daruma(string Status) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("rStatusImpressora_ECF_Daruma")) (Status);
}

//Retorna Informações Estendidas
int rInfoEstentida_ECF_Daruma(int i, char *c) {
	return ((FUNCAO_P (int,  char *)) carregarFuncaoDarumaFramework("rInfoEstentida_ECF_Daruma")) (i, c);
}
int rInfoEstentida1_ECF_Daruma(char *cInfoEx) {
	return ((FUNCAO_P (char *)) carregarFuncaoDarumaFramework("rInfoEstentida1_ECF_Daruma")) (cInfoEx);
}
int rInfoEstentida2_ECF_Daruma(char *cInfoEx) {
	return ((FUNCAO_P (char *)) carregarFuncaoDarumaFramework("rInfoEstentida2_ECF_Daruma")) (cInfoEx);
}
int rInfoEstentida3_ECF_Daruma(char *cInfoEx) {
	return ((FUNCAO_P (char *)) carregarFuncaoDarumaFramework("rInfoEstentida3_ECF_Daruma")) (cInfoEx);
}
int rInfoEstentida4_ECF_Daruma(char *cInfoEx) {
	return ((FUNCAO_P (char *)) carregarFuncaoDarumaFramework("rInfoEstentida4_ECF_Daruma")) (cInfoEx);
}
int rInfoEstentida5_ECF_Daruma(char *cInfoEx) {
	return ((FUNCAO_P (char *)) carregarFuncaoDarumaFramework("rInfoEstentida5_ECF_Daruma")) (cInfoEx);
}
int rVerificarReducaoZ_ECF_Daruma(char *zPendente) {
	return ((FUNCAO_P (char *)) carregarFuncaoDarumaFramework("rVerificarReducaoZ_ECF_Daruma")) (zPendente);
}

//Retornos da Impressora
int rRetornarInformacao_ECF_Daruma(string Indice, char *Retornar) {
	return ((FUNCAO_P (string, char *)) carregarFuncaoDarumaFramework("rRetornarInformacao_ECF_Daruma")) (Indice, Retornar);
}
int rRetornarNumeroSerie_ECF_Daruma(string SerialCriptografado, string Serial) {
	return ((FUNCAO_P (string, string)) carregarFuncaoDarumaFramework("rRetornarNumeroSerie_ECF_Daruma")) (SerialCriptografado, Serial);
}
int rLerAliquotas_ECF_Daruma(char *cAliquotas) {
	return ((FUNCAO_P (char *)) carregarFuncaoDarumaFramework("rLerAliquotas_ECF_Daruma")) (cAliquotas);
}
int rLerMeiosPagto_ECF_Daruma(string Relatorios) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("rLerMeiosPagto_ECF_Daruma")) (Relatorios);
}
int rLerRG_ECF_Daruma(string Relatorios) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("rLerRG_ECF_Daruma")) (Relatorios);
}
int rLerDecimais_ECF_Daruma(string DecimalQtde, string DecimalValor, int *piDecimalQtde, int *piDecimalValor) {
	return ((FUNCAO_P (string, string, int*, int*)) carregarFuncaoDarumaFramework("rLerDecimais_ECF_Daruma")) (DecimalQtde, DecimalValor, piDecimalQtde, piDecimalValor);
}
int rRetornarDadosReducaoZ_ECF_Daruma(string Dados) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("rRetornarDadosReducaoZ_ECF_Daruma")) (Dados);
}




#pragma endregion

#pragma region ECF_RELATORIO_GERENCIAL 

// --- ECF - Relatorio Gerencial - Inicio --- 
int iRGAbrir_ECF_Daruma(string NomeRG) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("iRGAbrir_ECF_Daruma")) (NomeRG);
}	
int iRGAbrirIndice_ECF_Daruma(int iIndiceRG) {
	return ((FUNCAO_P (int)) carregarFuncaoDarumaFramework("iRGAbrirIndice_ECF_Daruma")) (iIndiceRG);
}	
int iRGAbrirPadrao_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iRGAbrirPadrao_ECF_Daruma")) ();
}	
int iRGImprimirTexto_ECF_Daruma(string texto) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("iRGImprimirTexto_ECF_Daruma")) (texto);
}
int iRGFechar_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iRGFechar_ECF_Daruma")) ();
}
// --- ECF - Relatorio Gerencial - Fim --- 


#pragma endregion

#pragma region ECF_CCD-TEF 

// Abertura de comprovante de credito e debito
int	iCCDAbrir_ECF_Daruma(string FormaPgto, string Parcelas, string DocOrigem, string Valor, string CPF, string Nome, string Endereco) {
	return ((FUNCAO_P (string, string, string, string, string, string, string)) carregarFuncaoDarumaFramework("iCCDAbrir_ECF_Daruma")) (FormaPgto,  Parcelas,  DocOrigem,  Valor,  CPF,  Nome,  Endereco);
}
int iCCDAbrirSimplificado_ECF_Daruma(string FormaPgto, string Parcelas, string DocOrigem,  string Valor) {
	return ((FUNCAO_P (string, string, string, string)) carregarFuncaoDarumaFramework("iCCDAbrirSimplificado_ECF_Daruma")) (FormaPgto, Parcelas, DocOrigem, Valor);
}
int iCCDAbrirPadrao_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iCCDAbrirPadrao_ECF_Daruma")) ();
}

// Impressao de texto no comprovante de credito e debito
int iCCDImprimirTexto_ECF_Daruma(string Texto) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("iCCDImprimirTexto_ECF_Daruma")) (Texto);
}
int iCCDImprimirArquivo_ECF_Daruma(string ArqOrigem) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("iCCDImprimirArquivo_ECF_Daruma")) (ArqOrigem);
}

// Fechamento de texto no comprovante de credito e debito
int iCCDFechar_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iCCDFechar_ECF_Daruma")) ();
}

// Estorno de comprovante de credito e debito
int iCCDEstornarPadrao_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iCCDEstornarPadrao_ECF_Daruma")) ();
}
int iCCDEstornar_ECF_Daruma(string pszCOO, string pszCPF, string pszNome, string pszEndereco) {
	return ((FUNCAO_P (string, string, string, string)) carregarFuncaoDarumaFramework("iCCDEstornar_ECF_Daruma")) (pszCOO, pszCPF, pszNome, pszEndereco);
}
int eTEF_EsperarArquivo_ECF_Daruma(string ArqOrigem, boolean TravarTeclado, string Tempo) {
	return ((FUNCAO_P (string, boolean, string)) carregarFuncaoDarumaFramework("eTEF_EsperarArquivo_ECF_Daruma")) (ArqOrigem,TravarTeclado,Tempo);
}
int eTEF_TravarTeclado_ECF_Daruma(boolean TravarTeclado) {
	return ((FUNCAO_P (boolean)) carregarFuncaoDarumaFramework("eTEF_TravarTeclado_ECF_Daruma")) (TravarTeclado);
}
int eTEF_SetarFoco_ECF_Daruma(string titulo) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("eTEF_SetarFoco_ECF_Daruma")) (titulo);
}
int iTEF_ImprimirRespostaCartao_ECF_Daruma(string ArqOrigem, boolean TravarTeclado, string Pagamento, string Valor) {
	return ((FUNCAO_P (string, boolean,string, string)) carregarFuncaoDarumaFramework("iTEF_ImprimirRespostaCartao_ECF_Daruma")) (ArqOrigem, TravarTeclado, Pagamento, Valor);
}	
int iTEF_ImprimirResposta_ECF_Daruma(string ArqOrigem, boolean TravarTeclado, string Pagamento, string Valor) {
	return ((FUNCAO_P (string, boolean,string, string)) carregarFuncaoDarumaFramework("iTEF_ImprimirResposta_ECF_Daruma")) (ArqOrigem, TravarTeclado, Pagamento, Valor);
}
int iTEF_Fechar_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iTEF_Fechar_ECF_Daruma")) ();
}

#pragma endregion 

#pragma region ECF_RELATORIOS_FISCAIS 

int iLeituraX_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iLeituraX_ECF_Daruma")) ();
}
int rLeituraX_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("rLeituraX_ECF_Daruma")) ();
}
int iSangria_ECF_Daruma(string Valor, string Mensagem) {
	return ((FUNCAO_P (string, string)) carregarFuncaoDarumaFramework("iSangria_ECF_Daruma")) (Valor, Mensagem);
}
int iSangriaPadrao_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iSangriaPadrao_ECF_Daruma")) ();
}
int iSuprimento_ECF_Daruma(string Valor, string Mensagem) {
	return ((FUNCAO_P (string, string)) carregarFuncaoDarumaFramework("iSuprimento_ECF_Daruma")) (Valor, Mensagem);
}
int iSuprimentoPadrao_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iSuprimentoPadrao_ECF_Daruma")) ();
}
int iReducaoZ_ECF_Daruma(string Dataini, string Datafim) {
	return ((FUNCAO_P (string, string)) carregarFuncaoDarumaFramework("iReducaoZ_ECF_Daruma")) (Dataini, Datafim);
}
int iMFLer_ECF_Daruna(string Dataini, string Datafim) {
	return ((FUNCAO_P (string , string)) carregarFuncaoDarumaFramework("iMFLer_ECF_Daruna")) (Dataini, Datafim);
}
int iMFLerSerial_ECF_Daruna(string Dataini, string Datafim) {
	return ((FUNCAO_P (string, string)) carregarFuncaoDarumaFramework("iMFLerSerial_ECF_Daruna")) (Dataini, Datafim);
}


#pragma endregion

#pragma region ECF_COMPROVANTE_NAO_FISCAL
// --- ECF - Comprovante não fiscal - Inicio --- 
// Abertura de comprovante nao fiscal
int iCNFAbrir_ECF_Daruma(string pszCPF, string pszNome,  string pszEndereco) {
	return ((FUNCAO_P (string, string, string)) carregarFuncaoDarumaFramework("iCNFAbrir_ECF_Daruma")) (pszCPF, pszNome, pszEndereco);
}
int iCNFAbrirPadrao_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iCNFAbrirPadrao_ECF_Daruma")) ();
}

// Recebimento de itens
int iCNFReceber_ECF_Daruma(string pszIndice, string pszValor,  string pszTipoDescAcresc, string pszValorDescAcresc) {
	return ((FUNCAO_P (string, string, string, string)) carregarFuncaoDarumaFramework("iCNFReceber_ECF_Daruma")) (pszIndice, pszValor, pszTipoDescAcresc, pszValorDescAcresc);
}
int iCNFReceberSemDesc_ECF_Daruma(string pszIndice, string pszValor) {
	return ((FUNCAO_P (string, string)) carregarFuncaoDarumaFramework("iCNFReceberSemDesc_ECF_Daruma")) (pszIndice, pszValor);
}

//Cancelamento de item
int iCNFCancelarItem_ECF_Daruma(string pszNumItem) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("iCNFCancelarItem_ECF_Daruma")) (pszNumItem);
}
int iCNFCancelarUltimoItem_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iCNFCancelarUltimoItem_ECF_Daruma")) ();
}

//Cancelamento de acrescimo em item
int iCNFCancelarAcrescimoItem_ECF_Daruma(string pszNumItem) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("iCNFCancelarAcrescimoItem_ECF_Daruma")) (pszNumItem);
}
int iCNFCancelarAcrescUltimoItem_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iCNFCancelarAcrescUltimoItem_ECF_Daruma")) ();
}

// Cancelamento de desconto em item
int iCNFCancelarDescontoItem_ECF_Daruma(string pszNumItem) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("iCNFCancelarDescontoItem_ECF_Daruma")) (pszNumItem);
}
int iCNFCancelarDescUltimoItem_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iCNFCancelarDescUltimoItem_ECF_Daruma")) ();
}

// Totalizacao de CNF
int iCNFTotalizarComprovante_ECF_Daruma(string pszTipoDescAcresc, string pszValorDescAcresc) {
	return ((FUNCAO_P (string, string)) carregarFuncaoDarumaFramework("iCNFTotalizarComprovante_ECF_Daruma")) (pszTipoDescAcresc, pszValorDescAcresc);
}
int iCNFTotalizarComprovPadrao_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iCNFTotalizarComprovPadrao_ECF_Daruma")) ();
}

// Cancelamento de desconto e acrescimo em subtotal de CNF
int iCNFCancelarAcrescimoSubtotal_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iCNFCancelarAcrescimoSubtotal_ECF_Daruma")) ();
}
int iCNFCancelarDescontoSubtotal_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iCNFCancelarDescontoSubtotal_ECF_Daruma")) ();
}

// Descricao do meios de pagamento de CNF
int iCNFEfetuarPagamento_ECF_Daruma(string pszFormaPgto, string pszValor, string pszInfoAdicional) {
	return ((FUNCAO_P (string, string, string)) carregarFuncaoDarumaFramework("iCNFEfetuarPagamento_ECF_Daruma")) (pszFormaPgto, pszValor, pszInfoAdicional);
}
int iCNFEfetuarPagamentoFormatado_ECF_Daruma(string pszFormaPgto, string pszValor) {
	return ((FUNCAO_P (string, string)) carregarFuncaoDarumaFramework("iCNFEfetuarPagamentoFormatado_ECF_Daruma")) (pszFormaPgto, pszValor);
}
int iCNFEfetuarPagamentoPadrao_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iCNFEfetuarPagamentoPadrao_ECF_Daruma")) ();
}

// Encerramento de CNF
int iCNFEncerrar_ECF_Daruma(string pszMensagem) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("iCNFEncerrar_ECF_Daruma")) (pszMensagem);
}
int iCNFEncerrarPadrao_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iCNFEncerrarPadrao_ECF_Daruma")) ();
}

//Cancelamento de CNF
int iCNFCancelar_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iCNFCancelar_ECF_Daruma")) ();
}

#pragma endregion

#pragma region GERACAO_ARQUIVOS
int rGerarRelatorio_ECF_Daruma(string Str_Relatorio,string Str_Tipo,string Str_Inicial,string Str_Final){
	return ((FUNCAO_P (string,string,string,string)) carregarFuncaoDarumaFramework("rGerarRelatorio_ECF_Daruma")) (Str_Relatorio, Str_Tipo, Str_Inicial, Str_Final);
}

int rGerarRelatorioOffline_ECF_Daruma(string Str_Relatorio,string Str_Tipo,string Str_Inicial,string Str_Final,string Str_ArquivoMF,string Str_ArquivoMFD,string Str_ArquivoInfo){
	return ((FUNCAO_P (string,string,string,string,string,string,string)) carregarFuncaoDarumaFramework("rGerarRelatorioOffline_ECF_Daruma")) (Str_Relatorio, Str_Tipo, Str_Inicial, Str_Final, Str_ArquivoMF, Str_ArquivoMFD, Str_ArquivoInfo);
}

//Espelho MFD
int rGerarEspelhoMFD_ECF_Daruma(string pszTipo, string pszInicial, string pszFinal) {
	return ((FUNCAO_P (string, string, string)) carregarFuncaoDarumaFramework("rGerarEspelhoMFD_ECF_Daruma"))(pszTipo,  pszInicial,  pszFinal);
}



#pragma endregion

#pragma region ECF_METODOS_ESPECIAIS

// --- Especiais - Inicio --- 
int eRetornarAviso_ECF_Daruma() {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("eRetornarAviso_ECF_Daruma")) ();
}
int eRetornarErro_ECF_Daruma() {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("eRetornarErro_ECF_Daruma")) ();
}
int eAguardarCompactacao_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("eAguardarCompactacao_ECF_Daruma")) ();
}
int eBuscarPortaVelocidade_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("eBuscarPortaVelocidade_ECF_Daruma")) ();
}
int eBuscarPortaVelocidade_ECF(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("eBuscarPortaVelocidade_ECF")) ();
}
int eEnviarComando_ECF_Daruma(string Comando, int iTamanhoComando, int iType) {
	return ((FUNCAO_P (string, int, int)) carregarFuncaoDarumaFramework("eEnviarComando_ECF_Daruma")) (Comando, iTamanhoComando, iType);
}
int iEjetarCheque_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("iEjetarCheque_ECF_Daruma")) ();
}
int iEstornarPagamento_ECF_Daruma(string FormaPgtoEstornado, string FormaPgtoEfetivado, string Valor, string InfoAdicional) {
	return ((FUNCAO_P (string, string, string, string)) carregarFuncaoDarumaFramework("iEstornarPagamento_ECF_Daruma")) (FormaPgtoEstornado, FormaPgtoEfetivado, Valor, InfoAdicional);
}

#pragma endregion

#pragma region PROGRAMACAO_ECF

int confCadastrarPadrao_ECF_Daruma(string pszCadastrar, string pszValor) {
	return ((FUNCAO_P (string, string)) carregarFuncaoDarumaFramework("confCadastrarPadrao_ECF_Daruma")) (pszCadastrar, pszValor);
}
int confCadastrar_ECF_Daruma(string pszCadastrar, string pszValor,string pszSeparador) {
	return ((FUNCAO_P (string, string, string)) carregarFuncaoDarumaFramework("confCadastrar_ECF_Daruma")) (pszCadastrar, pszValor, pszSeparador);
}
int confHabilitarHorarioVerao_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("confHabilitarHorarioVerao_ECF_Daruma")) ();
}
int confDesabilitarHorarioVerao_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("confDesabilitarHorarioVerao_ECF_Daruma")) ();
}
int confHabilitarModoPreVenda_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("confHabilitarModoPreVenda_ECF_Daruma")) ();
}
int confDesabilitarModoPreVenda_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("confDesabilitarModoPreVenda_ECF_Daruma")) ();
}
int confProgramarAvancoPapel_ECF_Daruma(string pszSepEntreLinhas,string pszSepEntreDoc,string pszLinhasGuilhotina,string pszGuilhotina,string pszImpClicheAntecipada){
	return ((FUNCAO_P (string,string,string,string,string)) carregarFuncaoDarumaFramework("confProgramarAvancoPapel_ECF_Daruma")) (pszSepEntreLinhas,pszSepEntreDoc,pszLinhasGuilhotina,pszGuilhotina,pszImpClicheAntecipada);
}

int confFBProgramarIDLoja_ECF_Daruma(string pszValor) {
	return ((FUNCAO_P (string )) carregarFuncaoDarumaFramework("confFBProgramarIDLoja_ECF_Daruma")) (pszValor);
}
int confProgramarOperador_ECF_Daruma(string pszValor) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("confProgramarOperador_ECF_Daruma")) (pszValor);
}

#pragma endregion

#pragma region GAVETA_AUTENTICA_E_OUTROS

int eAcionarGuilhotina_ECF_Daruma(string pszTipoCorte) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("eAcionarGuilhotina_ECF_Daruma")) (pszTipoCorte);
}
int eAbrirGaveta_ECF_Daruma(void) {
	return ((FUNCAO_P (void)) carregarFuncaoDarumaFramework("eAbrirGaveta_ECF_Daruma")) ();
}

#pragma endregion

#pragma region REGISTRY
//Obter valor do Registry
int regRetornaValorChave_DarumaFramework(string pszProduto, string pszChave, string pszValor) {
	return ((FUNCAO_P (string, string, string)) carregarFuncaoDarumaFramework("regRetornaValorChave_DarumaFramework")) (pszProduto,pszChave,pszValor);
}
//ECF
int regAlterarValor_Daruma(string pszPathChave, string pszValor) {
	return ((FUNCAO_P (string,string)) carregarFuncaoDarumaFramework("regAlterarValor_Daruma")) (pszPathChave, pszValor);
}

int regECFAguardarImpressao_ECF_Daruma(string pszValor) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("regECFAguardarImpressao_ECF_Daruma")) (pszValor);
}
int regECFArquivoLeituraX_ECF_Daruma(string pszValor) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("regECFArquivoLeituraX_ECF_Daruma")) (pszValor);
}
int regECFAuditoria_ECF_Daruma(string pszValor) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("regECFAuditoria_ECF_Daruma")) (pszValor);
}
int regECFCaracterSeparador_ECF_Daruma(string pszValor) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("regECFCaracterSeparador_ECF_Daruma")) (pszValor);
}
//Cupom Fiscal 
int regCFCupomAdicionalDllConfig_ECF_Daruma(string pszValor) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("regCFCupomAdicionalDllConfig_ECF_Daruma")) (pszValor);
}
int regCFCupomAdicionalDllTitulo_ECF_Daruma(string pszValor) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("regCFCupomAdicionalDllTitulo_ECF_Daruma")) (pszValor);
}
int regCupomMania_ECF_Daruma(string pszValor) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("regCupomMania_ECF_Daruma")) (pszValor);
}
int regCFFormaPgto_ECF_Daruma(string pszValor) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("regCFFormaPgto_ECF_Daruma")) (pszValor);
}
int regCFMensagemPromocional_ECF_Daruma(string pszValor) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("regCFMensagemPromocional_ECF_Daruma")) (pszValor);
}
int regCFQuantidade_ECF_Daruma(string pszValor) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("regCFQuantidade_ECF_Daruma")) (pszValor);
}
int regCFTamanhoMinimoDescricao_ECF_Daruma(string pszValor) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("regCFTamanhoMinimoDescricao_ECF_Daruma")) (pszValor);
}
int regCFTipoDescAcresc_ECF_Daruma(string pszValor) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("regCFTipoDescAcresc_ECF_Daruma")) (pszValor);
}
int regCFUnidadeMedida_ECF_Daruma(string pszValor) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("regCFUnidadeMedida_ECF_Daruma")) (pszValor);
}
int regCFValorDescAcresc_ECF_Daruma(string pszValor) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("regCFValorDescAcresc_ECF_Daruma")) (pszValor);
}
//CCD
int regCCD_ECF_Daruma(string pszChave, string pszValor) {
	return ((FUNCAO_P (string, string)) carregarFuncaoDarumaFramework("regCCD_ECF_Daruma")) (pszChave, pszValor);
}
int regCCDDocOrigem_ECF_Daruma(string pszValor) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("regCCDDocOrigem_ECF_Daruma")) (pszValor);
}
int regCCDFormaPgto_ECF_Daruma(string pszValor) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("regCCDFormaPgto_ECF_Daruma")) (pszValor);
}
int regCCDLinhasTEF_ECF_Daruma(string pszValor) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("regCCDLinhasTEF_ECF_Daruma")) (pszValor);
}
int regCCDParcelas_ECF_Daruma(string pszValor) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("regCCDParcelas_ECF_Daruma")) (pszValor);
}
int regCCDValor_ECF_Daruma(string pszValor) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("regCCDValor_ECF_Daruma")) (pszValor);
}
//Ato Cotepe
int regAtoCotepe_ECF_Daruma(string pszChave, string pszValor) {
	return ((FUNCAO_P (string, string)) carregarFuncaoDarumaFramework("regAtoCotepe_ECF_Daruma")) (pszChave,pszValor);
}
//Sintegra
int regSintegra_ECF_Daruma(string pszChave, string pszValor) {
	return ((FUNCAO_P (string, string)) carregarFuncaoDarumaFramework("regSintegra_ECF_Daruma")) (pszChave,pszValor);
}
//Especiais
int eDefinirProduto_ECF_Daruma(string pszValor) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("eDefinirProduto_ECF_Daruma")) (pszValor);
}
int eDefinirModoRegistro_ECF_Daruma(string pszValor) {
	return ((FUNCAO_P (string)) carregarFuncaoDarumaFramework("eDefinirModoRegistro_ECF_Daruma")) (pszValor);
}
int eInterpretarErro_ECF_Daruma(int iIndice, char *pszRetorno){
	return ((FUNCAO_P (int , char*))carregarFuncaoDarumaFramework("eInterpretarErro_ECF_Daruma"))(iIndice, pszRetorno);
}
int eInterpretarAviso_ECF_Daruma(int iIndice, char *pszRetorno){
	return ((FUNCAO_P (int , char*))carregarFuncaoDarumaFramework("eInterpretarErro_ECF_Daruma"))(iIndice, pszRetorno);
}

#pragma endregion
