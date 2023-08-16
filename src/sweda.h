#ifndef swedaH
#define swedaH
#ifdef __cplusplus 
#define externC  extern "C"
#else
#define externC extern
#endif
#ifndef WIN32
#define __stdcall
#endif
#ifndef DLL_IMPORT
#define DLL_IMPORT
#endif
externC int __stdcall DLL_IMPORT  ECF_AbrePortaSerial(void);
externC int __stdcall DLL_IMPORT  ECF_FechaPortaSerial(void);
externC int __stdcall DLL_IMPORT  ECF_RetornaPortaVelocidade(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_LigaDesligaJanelas(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_ZAUTO(char *);
externC int __stdcall DLL_IMPORT  ECF_CfgRedZAutomatico(char *);
externC int __stdcall DLL_IMPORT  ECF_Registry(void);
externC int __stdcall DLL_IMPORT  ECF_Registry_AlteraRegistry(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_Registry_Path(char *);
externC int __stdcall DLL_IMPORT  ECF_Registry_PathMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_Registry_Zautomatica(char *);
externC int __stdcall DLL_IMPORT  ECF_Registry_Verao(char *);
externC int __stdcall DLL_IMPORT  ECF_Registry_Log(char *);
externC int __stdcall DLL_IMPORT  ECF_Registry_AplMensagem1(char *);
externC int __stdcall DLL_IMPORT  ECF_Registry_AplMensagem2(char *);
externC int __stdcall DLL_IMPORT  ECF_Registry_Default(void);
externC int __stdcall DLL_IMPORT  ECF_Registry_RetornaValor(char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_RetornaPath(char *);
externC int __stdcall DLL_IMPORT  ECF_RetornaPathMFD(char *);


// ----------------------------------------- PROGRAMACAO
externC int __stdcall DLL_IMPORT  ECF_EnviarLogotipoCliche(char *);
externC int __stdcall DLL_IMPORT  ECF_GravarLogotipoCliche(void);
externC int __stdcall DLL_IMPORT  ECF_ExcluirLogotipoCliche(void);
externC int __stdcall DLL_IMPORT  ECF_ApagaTabelaAliquotas(void);
externC int __stdcall DLL_IMPORT  ECF_ApagaTabelaNomesNaoFiscais(void);
externC int __stdcall DLL_IMPORT  ECF_ApagaTabelaNomesRelatoriosGerenciais(void);
externC int __stdcall DLL_IMPORT  ECF_ApagaTabelaNomesFormasdePagamento(void);
externC int __stdcall DLL_IMPORT  ECF_ProgramarParametrosDiversos(char *, char *, char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_ProgramarCliche(char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_ProgramarTotalizadoresNaoTributados(char *, char *, char *, char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_ProgramaAliquota(char *, unsigned int);
externC int __stdcall DLL_IMPORT  ECF_ProgramarRelogio(char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_ProgramaHorarioVerao(void);
externC int __stdcall DLL_IMPORT  ECF_NomeiaTotalizadorNaoSujeitoIcms(int indice, char *cTot);
externC int __stdcall DLL_IMPORT  ECF_ProgramaFormaPagamentoMFD(char *cFormaPgto, char *cTef);
externC int __stdcall DLL_IMPORT  ECF_ProgramaFormasPagamento(char *);
externC int __stdcall DLL_IMPORT  ECF_NomeiaRelatorioGerencialMFD(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_ProgramaOperador(char *);
externC int __stdcall DLL_IMPORT  ECF_CfgFechaAutomaticoCupom(char *);
externC int __stdcall DLL_IMPORT  ECF_CfgHorarioVerao(char *);
externC int __stdcall DLL_IMPORT  ECF_CfgCupomAdicional(char *);
externC int __stdcall DLL_IMPORT  ECF_ImprimeConfiguracoesImpressora(void);
externC int __stdcall DLL_IMPORT  ECF_ConfigurarECF(char *, char *, char *, char *); 


// ------------------------------------ ABERTURA DO DIA
externC int __stdcall DLL_IMPORT  ECF_AberturaDoDia(char *, char *);


// ------------------------------------- CUPOM FISCAL 
externC int __stdcall DLL_IMPORT  ECF_AbreCupom(char *);
externC int __stdcall DLL_IMPORT  ECF_AbreCupomMFD(char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_IdentificaConsumidor(char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_AumentaDescricaoItem(char *);
externC int __stdcall DLL_IMPORT  ECF_UsaUnidadeMedida(char *);
externC int __stdcall DLL_IMPORT  ECF_VendeItem(char *,char *, char *, char *, char *, int, char *, char *, char *);
externC int __stdcall DLL_IMPORT ECF_VendeItemTresDecimais(char*,char*,char*,char*,char*,char*,char*);
externC int __stdcall DLL_IMPORT ECF_VendeItemDepartamento(char*,char*,char*,char*,char*,char*,char*,char*,char*);
externC int __stdcall DLL_IMPORT  ECF_DescontoSobreItemVendido(char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_AcrescimoDescontoItemMFD(char *,char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_CancelaItemAnterior(void);
externC int __stdcall DLL_IMPORT  ECF_CancelaItemGenerico(char *);
externC int __stdcall DLL_IMPORT  ECF_CancelaAcrescimoDescontoItemMFD(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_IniciaFechamentoCupom(char *,char *,char *);
externC int __stdcall DLL_IMPORT  ECF_IniciaFechamentoCupomMFD(char *,char *,char *,char *);
externC int __stdcall DLL_IMPORT  ECF_SubTotalizaCupomMFD(void);
externC int __stdcall DLL_IMPORT  ECF_AcrescimoDescontoSubtotalMFD(char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_CancelaAcrescimoDescontoSubtotalMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_TotalizaCupomMFD(void);
externC int __stdcall DLL_IMPORT  ECF_EfetuaFormaPagamento(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_EfetuaFormaPagamentoDescricaoForma(char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_EfetuaFormaPagamentoMFD(char *, char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_TerminaFechamentoCupom(char *);
externC int __stdcall DLL_IMPORT  ECF_FechaCupom(char *,char *, char *, char *,char *,char *);
externC int __stdcall DLL_IMPORT  ECF_FechaCupomResumido(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_AtivaDesativaCorteProximoMFD(unsigned int);
externC int __stdcall DLL_IMPORT  ECF_CupomAdicionalMFD(void);
externC int __stdcall DLL_IMPORT  ECF_ProgramaArredondamento(void);
externC int __stdcall DLL_IMPORT  ECF_ProgramaTruncamento(void);


// ------------------ CANCELAMENTO DE CUPOM E COMPROVANTE
externC int __stdcall DLL_IMPORT  ECF_CancelaCupom(void);
externC int __stdcall DLL_IMPORT  ECF_CancelaCupomMFD(char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_CancelaRecebimentoNaoFiscalMFD(char *, char *, char *);


// ------------------------ COMPROVANTE
externC int __stdcall DLL_IMPORT  ECF_EstornoFormasPagamento(char *, char *, char *);


// ------------------------ COMPROVANTE CDC - TEF
externC int __stdcall DLL_IMPORT  ECF_IniciaModoTEF(void);
externC int __stdcall DLL_IMPORT  ECF_AbreComprovanteNaoFiscalVinculado(char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_AbreComprovanteNaoFiscalVinculadoMFD(char *, char *,char *, char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_UsaComprovanteNaoFiscalVinculado(char *);
externC int __stdcall DLL_IMPORT  ECF_UsaComprovanteNaoFiscalVinculadoTEF(char *);
externC int __stdcall DLL_IMPORT  ECF_FechaComprovanteNaoFiscalVinculado(void);
externC int __stdcall DLL_IMPORT  ECF_FinalizaModoTEF(void);
externC int __stdcall DLL_IMPORT  ECF_TEF_TravarTeclado(void);
externC int __stdcall DLL_IMPORT  ECF_SegundaViaNaoFiscalVinculadoMFD(void);
externC int __stdcall DLL_IMPORT  ECF_SegundaViaCNFV(void);
externC int __stdcall DLL_IMPORT  ECF_ReimpressaoNaoFiscalVinculadoMFD(void);
externC int __stdcall DLL_IMPORT  ECF_EstornoNaoFiscalVinculadoMFD(char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_CancelamentoCNFV(char *ignorado);
externC int __stdcall DLL_IMPORT  ECF_TEF_ImprimirRespostaCartao(char *, char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_TEF_ImprimirResposta(char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_TEF_FechaRelatorio(void);
externC int __stdcall DLL_IMPORT  ECF_TEF_EsperarArquivo(char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_RelatorioGerencialTEF(char *);
externC int __stdcall DLL_IMPORT  ECF_UsaRelatorioGerencialMFDTEF(char *);


// --------------------------------- RECEBIMENTOS
externC int __stdcall DLL_IMPORT  ECF_Suprimento(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_Sangria(char *);
externC int __stdcall DLL_IMPORT  ECF_FundoCaixa(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_AbreRecebimentoNaoFiscalMFD(char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_AbreRecebimentoNaoFiscal(char *, char *, char *, char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_RecebimentoNaoFiscal(char *cIndiceTot,char *cValor ,char *cFormaPgto);
externC int __stdcall DLL_IMPORT  ECF_EfetuaRecebimentoNaoFiscalMFD(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_CancelaItemNaoFiscalMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_AcrescimoItemNaoFiscalMFD(char *, char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_AcrescimoDescontoSubtotalRecebimentoMFD(char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_TotalizaRecebimentoMFD(void);
externC int __stdcall DLL_IMPORT  ECF_IniciaFechamentoRecebimentoNaoFiscalMFD(char *, char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_FechaRecebimentoNaoFiscalMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_EfetuaFormaPagamentoNaoFiscal(char *, char *,char *);


// ---------------------------- RELATORIO GERENCIAL
externC int __stdcall DLL_IMPORT  ECF_AbreRelatorioGerencial(void);
externC int __stdcall DLL_IMPORT  ECF_AbreRelatorioGerencialMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_EnviarTextoCNF(char *);
externC int __stdcall DLL_IMPORT  ECF_RelatorioGerencial(char *);
externC int __stdcall DLL_IMPORT  ECF_UsaRelatorioGerencialMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_FechaRelatorioGerencial(void);
externC int __stdcall DLL_IMPORT  ECF_FechaRelatorioXouZ(void);


// --------------------------- LEITURAS FISCAIS
externC int __stdcall DLL_IMPORT  ECF_LeituraX(void);
externC int __stdcall DLL_IMPORT  ECF_LeituraMemoriaFiscalData(char *,char *);
externC int __stdcall DLL_IMPORT  ECF_LeituraMemoriaFiscalDataMFD(char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_LeituraMemoriaFiscalReducao(char *,char *);
externC int __stdcall DLL_IMPORT  ECF_LeituraMemoriaFiscalReducaoMFD(char *, char *, char *);




// --------------------------- ENCERRAMENTO DO DIA
externC int __stdcall DLL_IMPORT  ECF_FechamentoDoDia(void);
externC int __stdcall DLL_IMPORT  ECF_ReducaoZ(char *cDatai, char *cHorai);
externC int __stdcall DLL_IMPORT  ECF_ReducaoZAjustaDataHora(char *, char *);


// --------------------------- VALIDACAO
externC int __stdcall DLL_IMPORT  ECF_Autenticacao(void);
externC int __stdcall DLL_IMPORT  ECF_AutenticacaoMFD(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_AutenticacaoStr(char *);
externC int __stdcall DLL_IMPORT  ECF_VerificaDocAutenticacao(void);
externC int __stdcall DLL_IMPORT  ECF_ProgramaCaracterAutenticacao(char *);


// --------------------------- GAVETA
externC int __stdcall DLL_IMPORT  ECF_AcionaGaveta(void);
externC int __stdcall DLL_IMPORT  ECF_VerificaEstadoGaveta(unsigned int *);
externC int __stdcall DLL_IMPORT  ECF_VerificaEstadoGavetaStr(char *);


// --------------------------------------------------- CHEQUE
externC int __stdcall DLL_IMPORT  ECF_ProgramaMoedaSingular(char *);
externC int __stdcall DLL_IMPORT  ECF_ProgramaMoedaPlural(char *);
externC int __stdcall DLL_IMPORT  ECF_ProgramarLeiauteCheque(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_IncluiCidadeFavorecido(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_VerificaStatusCheque(unsigned int *);
externC int __stdcall DLL_IMPORT  ECF_VerificaStatusChequeStr(char *);
externC int __stdcall DLL_IMPORT  ECF_ImprimeCheque(char *,char *,char *,char *,char *,char *,char *);
externC int __stdcall DLL_IMPORT  ECF_ImprimeChequeMFD(char *,char *,char *,char *,char *,char *,char *,char *);
externC int __stdcall DLL_IMPORT  ECF_ImprimeCopiaCheque(void);
externC int __stdcall DLL_IMPORT  ECF_CancelaImpressaoCheque(void);
externC int __stdcall DLL_IMPORT  ECF_LeituraChequeMFD(char *sCMC7);
externC int __stdcall DLL_IMPORT  ECF_ImprimirCheque(char *,char *,char *,char *,char *,char *);
externC int __stdcall DLL_IMPORT  ECF_LiberarCheque(void);
externC int __stdcall DLL_IMPORT  ECF_LeituraCodigoMICR(char *);
externC int __stdcall DLL_IMPORT  ECF_CancelarCheque(void);
externC int __stdcall DLL_IMPORT  ECF_LeituraLeiautesCheques(void);
externC int __stdcall DLL_IMPORT  ECF_DataHoraGravacaoUsuarioSWBasicoMFAdicional(char *,char *,char *);


// -------------------------- STATUS DE PROGRAMACAO
externC int __stdcall DLL_IMPORT  ECF_RetornaTipoEcf(char *);
externC int __stdcall DLL_IMPORT  ECF_VersaoDll(char *);
externC int __stdcall DLL_IMPORT  ECF_VersaoFirmware(char *);
externC int __stdcall DLL_IMPORT  ECF_VersaoFirmwareMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_NumeroSerie(char *);
externC int __stdcall DLL_IMPORT  ECF_NumeroSerieMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_NumeroSerieMemoriaMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_MarcaModeloTipoImpressoraMFD(char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_CGC_IE(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_CNPJMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_InscricaoEstadualMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_InscricaoMunicipalMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_NumeroSubstituicoesProprietario(char *);
externC int __stdcall DLL_IMPORT  ECF_SimboloMoeda(char *);
externC int __stdcall DLL_IMPORT  ECF_ClicheProprietario(char *);
externC int __stdcall DLL_IMPORT  ECF_NumeroLoja(char *);
externC int __stdcall DLL_IMPORT  ECF_NumeroCaixa(char *);
externC int __stdcall DLL_IMPORT  ECF_DataHoraImpressora(char *, char *); 
externC int __stdcall DLL_IMPORT  ECF_RetornoAliquotas(char *);
externC int __stdcall DLL_IMPORT  ECF_VerificaAliquotasIss(char *);
externC int __stdcall DLL_IMPORT  ECF_VerificaIndiceAliquotasIss(char *);
externC int __stdcall DLL_IMPORT  ECF_VerificaTotalizadoresNaoFiscais(char *);
externC int __stdcall DLL_IMPORT  ECF_VerificaTotalizadoresNaoFiscaisMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_VerificaModoOperacao(char *);
externC int __stdcall DLL_IMPORT  ECF_RetornaIndiceComprovanteNaoFiscal(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_LerAliquotasComIndice(char *);
externC int __stdcall DLL_IMPORT  ECF_ClicheProprietarioEx(char *);
externC int __stdcall DLL_IMPORT  ECF_VerificaDescricaoFormasPagamento(char *);
externC int __stdcall DLL_IMPORT  ECF_VerificaTotalizadoresNaoFiscaisEx(char *);
externC int __stdcall DLL_IMPORT  ECF_VerificaRelatorioGerencialProgMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_CasasDecimaisProgramada(char *,char *);
externC int __stdcall DLL_IMPORT  ECF_VerificaTruncamento(char *);


// ---- RETORNO DE VALORES DO ULTIMO CUPOM / CUPOM CORRENTE
externC int __stdcall DLL_IMPORT  ECF_TipoUltimoDocumento(char *);
externC int __stdcall DLL_IMPORT  ECF_UltimoItemVendido(char *);
externC int __stdcall DLL_IMPORT  ECF_SubTotal(char *);
externC int __stdcall DLL_IMPORT  ECF_SubTotalComprovanteNaoFiscalMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_ValorPagoUltimoCupom(char *texto);
externC int __stdcall DLL_IMPORT  ECF_NumeroCupom(char *);
externC int __stdcall DLL_IMPORT  ECF_VerificaFormasPagamento(char *);
externC int __stdcall DLL_IMPORT  ECF_VerificaFormasPagamentoMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_UltimaFormaPagamento(char *,char *);
externC int __stdcall DLL_IMPORT  ECF_VerificaFormasPagamentoEx(char *);
externC int __stdcall DLL_IMPORT  ECF_TotaisVenda(char *);
externC int __stdcall DLL_IMPORT  ECF_ValorAcrescimosUltimoCupom(char *);
externC int __stdcall DLL_IMPORT  ECF_ValorDescontosUltimoCupom(char *);
externC int __stdcall DLL_IMPORT  ECF_ValorCancelamentosUltimoCupom(char *);
externC int __stdcall DLL_IMPORT  ECF_ValorCancelamentosUltimoCupomISS(char *);
externC int __stdcall DLL_IMPORT  ECF_ValorAliquotaUltimoCupom(char *);


// ---------------------------- RETORNO DE VALORES DO DIA 
externC int __stdcall DLL_IMPORT  ECF_Acrescimos(char *);
externC int __stdcall DLL_IMPORT  ECF_Descontos(char *);
externC int __stdcall DLL_IMPORT  ECF_ValorFormaPagamento(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_ValorFormaPagamentoMFD(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_ValorTotalizadorNaoFiscal(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_ValorTotalizadorNaoFiscalMFD(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_VerificaRecebimentoNaoFiscal(char *);
externC int __stdcall DLL_IMPORT  ECF_VerificaRecebimentoNaoFiscalMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_Cancelamentos(char *);
externC int __stdcall DLL_IMPORT  ECF_GrandeTotal(char *);
externC int __stdcall DLL_IMPORT  ECF_VerificaTotalizadoresParciais(char *);
externC int __stdcall DLL_IMPORT  ECF_VerificaTotalizadoresParciaisMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_VendaBruta(char *);
externC int __stdcall DLL_IMPORT  ECF_RetornaAcrescimoNF(char *);
externC int __stdcall DLL_IMPORT  ECF_RetornaDescontoNF(char *);
externC int __stdcall DLL_IMPORT  ECF_RetornaCancelamentoNF(char *);
externC int __stdcall DLL_IMPORT  ECF_RetornaTotalPagamentos(char *);
externC int __stdcall DLL_IMPORT  ECF_RetornaCNFNV(char *);
externC int __stdcall DLL_IMPORT  ECF_RetornaTroco(char *);
externC int __stdcall DLL_IMPORT  ECF_RetornaRegistradoresNaoFiscais(char *);
externC int __stdcall DLL_IMPORT  ECF_RetornaRegistradoresFiscais(char *);
externC int __stdcall DLL_IMPORT  ECF_RetornaValorComprovanteNaoFiscal(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_AcrescimosICMSISS(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_CancelamentosICMSISS(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_DescontosICMSISS(char *, char *);


// ----------------------- RETORNO DOS CONTADORES DIARIOS


externC int __stdcall DLL_IMPORT  ECF_NumeroIntervencoes(char *);
externC int __stdcall DLL_IMPORT  ECF_RetornaCOO(char *);
externC int __stdcall DLL_IMPORT  ECF_ContadorCupomFiscalMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_NumeroCuponsCancelados(char *);
externC int __stdcall DLL_IMPORT  ECF_NumeroOperacoesNaoFiscais(char *);
externC int __stdcall DLL_IMPORT  ECF_ContadorComprovantesCreditoMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_ComprovantesNaoFiscaisNaoEmitidosMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_ContadorOperacoesNaoFiscaisCanceladasMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_RetornaCNFCancelados(char *);
externC int __stdcall DLL_IMPORT  ECF_ContadorFitaDetalheMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_ContadorRelatoriosGerenciaisMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_NumeroReducoes(char *);
externC int __stdcall DLL_IMPORT  ECF_RetornaCRZ(char *);
externC int __stdcall DLL_IMPORT  ECF_COO(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_ContadoresTotalizadoresNaoFiscais(char *);
externC int __stdcall DLL_IMPORT  ECF_ContadoresTotalizadoresNaoFiscaisMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_VerificaRelatorioGerencialMFD(char *);
 
// ------------------------------------ STATUS 
externC int __stdcall DLL_IMPORT  ECF_VerificaImpressoraLigada(void);
externC int __stdcall DLL_IMPORT  ECF_FlagsFiscais(unsigned int *);
externC int __stdcall DLL_IMPORT  ECF_FlagsFiscaisStr(char *);
externC int __stdcall DLL_IMPORT  ECF_VerificaEstadoImpressora( int *, int *, int *);
externC int __stdcall DLL_IMPORT  ECF_VerificaEstadoImpressoraMFD(unsigned int *, unsigned int *, unsigned int *, unsigned int *);


externC int __stdcall DLL_IMPORT  ECF_VerificaEstadoImpressoraStr(char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_RetornoImpressora( int *,  int *,  int *);
externC int __stdcall DLL_IMPORT  ECF_RetornoImpressoraMFD(unsigned int *, unsigned int *, unsigned int *, unsigned int *);
externC int __stdcall DLL_IMPORT  ECF_RetornoImpressoraStr(char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_VerificaTipoImpressora(unsigned int *);
externC int __stdcall DLL_IMPORT  ECF_VerificaTipoImpressoraStr(char *);
externC int __stdcall DLL_IMPORT  ECF_StatusEstendidoMFD(unsigned int *);
externC int __stdcall DLL_IMPORT  ECF_StatusCupomFiscal(char *);
externC int __stdcall DLL_IMPORT  ECF_StatusRelatorioGerencial(char *);
externC int __stdcall DLL_IMPORT  ECF_StatusComprovanteNaoFiscalVinculado(char *);
externC int __stdcall DLL_IMPORT  ECF_StatusComprovanteNaoFiscalNaoVinculado(char *);
externC int __stdcall DLL_IMPORT  ECF_VerificaModeloEcf(void);
externC int __stdcall DLL_IMPORT  ECF_VerificaHorarioVerao(char *);
externC int __stdcall DLL_IMPORT  ECF_VerificaZPendente(char *);
externC int __stdcall DLL_IMPORT  ECF_VerificaDiaAberto(char *);
externC int __stdcall DLL_IMPORT  ECF_PalavraStatus(char *);
externC int __stdcall DLL_IMPORT  ECF_PalavraStatusBinario(char *);
externC int __stdcall DLL_IMPORT  ECF_VerificaFlagCorteMFD(unsigned int *);
externC int __stdcall DLL_IMPORT  ECF_GeraRFD(char *);
externC int __stdcall DLL_IMPORT  ECF_MsgLog(char *);


// -------------------------------------- DIVERSOS
externC int __stdcall DLL_IMPORT  ECF_PercentualLivreMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_TotalLivreMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_ReducoesRestantesMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_RetornaCRZRestante(char *);
externC int __stdcall DLL_IMPORT  ECF_TamanhoTotalMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_TempoRestanteComprovanteMFD(char *);


externC int __stdcall DLL_IMPORT  ECF_DataMovimento(char *);


// ------------------------ RETORNO DE VALORES APOS A REDUCAO Z
externC int __stdcall DLL_IMPORT  ECF_DataHoraUltimoDocumentoMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_DataHoraReducao(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_DataMovimentoUltimaReducaoMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_InicioFimCOOsMFD(char *,char *);
externC int __stdcall DLL_IMPORT  ECF_InicioFimGTsMFD(char *,char *);
externC int __stdcall DLL_IMPORT  ECF_GrandeTotalUltimaReducaoMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_DadosUltimaReducao(char *);
externC int __stdcall DLL_IMPORT  ECF_DadosUltimaReducaoMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_MapaResumo(void);
externC int __stdcall DLL_IMPORT  ECF_MapaResumoMFD(void);


// ------------------------------- SINTEGRA
externC int __stdcall DLL_IMPORT  ECF_RegistrosTipo60(void);
externC int __stdcall DLL_IMPORT  ECF_RelatorioTipo60Mestre(void);
externC int __stdcall DLL_IMPORT  ECF_RelatorioTipo60Analitico(void);
externC int __stdcall DLL_IMPORT  ECF_RelatorioTipo60AnaliticoMFD(void);
externC int __stdcall DLL_IMPORT  ECF_RelatorioSintegraMFD(unsigned int, char *,char *,char *,char *,char *, char *,char *,char *,char *,char *, char *,char *, char *);
externC int __stdcall DLL_IMPORT  ECF_ArquivoSintegra2004MFD(unsigned int, char *,char *,char *,char *,char *, char *,char *,char *,char *,char *, char *, char *,char *, char *, char *, char *);


// ------------------------------- CAPTURA
externC int __stdcall DLL_IMPORT  ECF_LeituraXSerial(void);
externC int __stdcall DLL_IMPORT  ECF_LeituraMemoriaFiscalSerialData(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_LeituraMemoriaFiscalSerialDataMFD(char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_LeituraMemoriaFiscalSerialReducao(char *, char *);
externC int __stdcall DLL_IMPORT  ECF_LeituraMemoriaFiscalSerialReducaoMFD(char *, char *, char *);
externC int __stdcall DLL_IMPORT  ECF_DownloadSB(char *);
externC int __stdcall DLL_IMPORT  ECF_DownloadMF(char *);
externC int __stdcall DLL_IMPORT  ECF_DownloadMFD(char *,char *,char *,char *,char *);
externC int __stdcall DLL_IMPORT  ECF_FormatoDadosMFD(char *,char *,char *,char *,char *,char *,char *);
externC int __stdcall DLL_IMPORT  ECF_CapturaDocumentos(char *, char *,char *, char *, char *);


// ------------------------------- COTEPE
externC int __stdcall DLL_IMPORT  ECF_TabelaMercadoriasServicos3404(char *,char *,char *);
externC int __stdcall DLL_IMPORT  ECF_ReproduzirMemoriaFiscalMFD(char *,char *,char *,char *,char *);
externC int __stdcall DLL_IMPORT  ECF_GeraRegistrosCAT52MFD(char *, char *);


// ------------------------------- COdigo DE BARRAS
externC int __stdcall DLL_IMPORT  ECF_ConfiguraCodigoBarrasMFD(unsigned int, unsigned int, unsigned int, unsigned int,unsigned int);
externC int __stdcall DLL_IMPORT  ECF_CodigoBarrasCODABARMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_CodigoBarrasPDF417MFD(unsigned int, unsigned int, unsigned int, unsigned int, char *);
externC int __stdcall DLL_IMPORT  ECF_CodigoBarrasCODE39MFD(char *);
externC int __stdcall DLL_IMPORT  ECF_CodigoBarrasEAN13MFD(char *);
externC int __stdcall DLL_IMPORT  ECF_CodigoBarrasEAN8MFD(char *);
externC int __stdcall DLL_IMPORT  ECF_CodigoBarrasITFMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_CodigoBarrasUPCAMFD(char *);
externC int __stdcall DLL_IMPORT  ECF_CodigoBarrasUPCEMFD(char *);



#endif