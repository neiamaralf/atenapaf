//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
#ifdef __cplusplus 
#define externC  extern "C"
#else
#define externC extern
#endif
#ifndef WIN32
#define __stdcall
#endif

#define Bematech_MP_20_FI_II 0
#define Bematech_MP_40_FI_II 1
#define Bematech_MP_2000_TH_FI 2
#define Bematech_MP_2100_TH_FI 3
#define Bematech_MP_3000_TH_FI 4
#define Bematech_MP_4000_TH_FI 5
#define Bematech_MP_6000_TH_FI 6
#define Bematech_MP_6100_TH_FI 7
#define Bematech_MP_7000_TH_FI 8
#define Bematech_MP_25_FI 9
#define Bematech_MP_50_FI 10
#define Sweda_Matricial 11
#define Sweda_Termica 12
 
externC int __stdcall Bematech_FI_VendaBruta(char* VendaBruta);
externC int __stdcall  Bematech_FI_DadosSintegra(char* DataInicial,char* DataFinal);
externC int __stdcall  Bematech_FI_DadosUltimaReducaoMFD(char *sDados);
externC int __stdcall  Bematech_FI_ContadorRelatoriosGerenciaisMFD(char * sRel );
externC int __stdcall  Bematech_FI_ContadorComprovantesCreditoMFD(char *  sComp );
externC int __stdcall  Bematech_FI_DataHoraUltimoDocumentoMFD(char * sDataHora );
externC int __stdcall  Bematech_FI_AbreCupomMFD(char *cgc,char *nome,char *end);
externC int __stdcall  Bematech_FI_CancelaCupomMFD( char * cCPF ,char * cNomeCliente ,char * cEnderecoCliente  );
externC int __stdcall  Bematech_FI_FechaCupom(char *cFormaPgto,char *cAcresDesc,char *cTipoAcresDesc,char *cValorAcresDesc,char *cValorPago,char *cMsgPromocional);
externC int __stdcall Bematech_FI_VerificaFormasPagamentoMFD(char *sFgto);
externC int __stdcall Bematech_FI_VersaoFirmwareMFD(char* vSB  );
externC int __stdcall Bematech_FI_CNPJMFD(char* CNPJUSUARIO);
externC int __stdcall Bematech_FI_InscricaoEstadualMFD(char *IEUSUARIO);
externC int __stdcall Bematech_FI_MarcaModeloTipoImpressoraMFD(char *marca,char *modelo,char *tipo);	
externC int __stdcall Bematech_FI_FormatoDadosMFD(char *cArquivoOrigem, 
char *cDestino, 
char *cFormatoDados/*
"0" (zero) para formato .TXT  (é criado um arquivo TXT com a imagem dos cupons referentes ao movimento)
"1" (um) para formato .RTF (é criado um arquivo RTF com a imagem dos cupons referentes ao movimento)
"2" (dois) para formato .MDB (é criado um arquivo MDB com tabelas referentes ao movimento)*/,
 
char *cTipoDownload,/*
"0" (zero): download total
"1" (um): download por data
"2" (dois): download por COO*/
 
char *cDadoInicial,
char *cDadoFinal,
char *cUsuario);
externC int __stdcall Bematech_FI_DownloadMFD(char *cArquivo,char* cTipoDownload/*"0" (zero): download total.
"1" (um): download por data.
"2" (dois): download por COO.*/,
 
char* cDadoInicial,
char* cDadoFinal,
char* cUsuario);
externC int __stdcall Bematech_FI_EspelhoMFD(char* NomeArquivo,char* DadoInicial,char* DadoFinal,
																																													char* TipoDownload,char* Usuario,char* ChavePublica,char* ChavePrivada);
externC int __stdcall Bematech_FI_ArquivoMFD(char*, char*,char*, char*, char*, int,char*, char*, int) ;
externC int __stdcall Bematech_FI_LeituraX(void);
externC int __stdcall Bematech_FI_FechaPortaSerial(void);
externC int __stdcall Bematech_FI_VerificaImpressoraLigada(void);
externC int __stdcall Bematech_FI_RetornoImpressora (int* ACK, int* ST1, int* ST2);
externC int __stdcall Bematech_FI_AumentaDescricaoItem (char* Descricao);
externC int __stdcall Bematech_FI_AbrePortaSerial(void);
externC int __stdcall Bematech_FI_ProgramaAliquota (char* Aliquota, int Tipo);
externC int __stdcall Bematech_FI_LeituraMemoriaFiscalSerialDataPAFECF(char *strDataInicial,char *strDataFinal,char *String,char *strChavePublica, char *strChavePrivada);

externC int __stdcall Bematech_FI_DownloadMF(const char *cArquivo);
externC int __stdcall Bematech_FI_VersaoDll(char*);
externC int __stdcall Bematech_FI_ProgramaHorarioVerao(void);
externC int __stdcall Bematech_FI_NomeiaTotalizadorNaoSujeitoIcms(int Indice, char* Totalizador);
externC int __stdcall Bematech_FI_ProgramaArredondamento(void);
externC int __stdcall Bematech_FI_ProgramaTruncamento (void);
externC int __stdcall Bematech_FI_NomeiaDepartamento (int Indice, char* Departamento);
externC int __stdcall Bematech_FI_LinhasEntreCupons (int Linhas);
externC int __stdcall Bematech_FI_EspacoEntreLinhas (int Dots);
externC int __stdcall Bematech_FI_ForcaImpactoAgulhas (int ForcaImpacto);
externC int __stdcall Bematech_FI_ResetaImpressora(void);
externC int __stdcall Bematech_FI_AbreCupom (char* CGC);
externC int __stdcall Bematech_FI_VendeItem (char* Codigo, char* Descricao, char* Aliquota,char* TipoQuantidade, char* Quantidade,short CasasDecimais,char* ValorUnitario,char* TipoDesconto, char* ValorDesconto );
externC int __stdcall Bematech_FI_VendeItemDepartamento (char* Codigo, char* Descricao,char* Aliquota, char* ValorUnitario,char* Quantidade, char* Acrescimo,char* Desconto, char* IndiceDepartamento,char* cUnidadeMedida);
externC int __stdcall Bematech_FI_CupomResumido (char* FormaPagamento,char* Mensagem);
externC int __stdcall Bematech_FI_CancelaCupom(void);
externC int __stdcall Bematech_FI_CancelaItemAnterior ( void );
externC int __stdcall Bematech_FI_CancelaItemGenerico ( char * NumeroItem );
externC int __stdcall Bematech_FI_FechaCupomResumido ( char * FormaPagamento,char * Mensagem );
externC int __stdcall Bematech_FI_UsaUnidadeMedida (char* UnidadeMedida);
externC int __stdcall Bematech_FI_ReducaoZ (char* Data, char* Hora);
externC int __stdcall Bematech_FI_LeituraXSerial(void);
externC int __stdcall Bematech_FI_LeituraMemoriaFiscalData (char* DataInicial, char* DataFinal);
externC int __stdcall Bematech_FI_LeituraMemoriaFiscalReducao (char* ReducaoInicial,char* ReducaoFinal);
externC int __stdcall Bematech_FI_LeituraMemoriaFiscalSerialData (char* DataInicial,char* DataFinal);
externC int __stdcall Bematech_FI_LeituraMemoriaFiscalSerialReducao (char* ReducaoInicial,char* ReducaoFinal);
externC int __stdcall Bematech_FI_LeituraMemoriaFiscalDataMFD (char* DataInicial, char* DataFinal,char *FlagLeitura);
externC int __stdcall Bematech_FI_LeituraMemoriaFiscalReducaoMFD (char* ReducaoInicial,char* ReducaoFinal,char *FlagLeitura);
externC int __stdcall Bematech_FI_LeituraMemoriaFiscalSerialDataMFD (char* DataInicial,char* DataFinal,char *FlagLeitura);
externC int __stdcall Bematech_FI_LeituraMemoriaFiscalSerialReducaoMFD (char* ReducaoInicial,char* ReducaoFinal,char *FlagLeitura);
externC int __stdcall Bematech_FI_InfoBalanca(char* Porta,int Modelo,char*  Peso,char*  PrecoKilo,char*  Total );

externC int __stdcall Bematech_FI_versaoDll(char* Texto);
externC int __stdcall Bematech_FI_ModeloImpressora(char* Texto);
externC int __stdcall Bematech_FI_RelatorioGerencial (char* Texto);
externC int __stdcall Bematech_FI_FechaRelatorioGerencial(void);
externC int __stdcall Bematech_FI_RecebimentoNaoFiscal (char* IndiceTotalizador,char* ValorRecebimento,char* FormaPagamento);
externC int __stdcall Bematech_FI_AbreComprovanteNaoFiscalVinculado(char* FormaPagamento,char* Valor,char* NumeroCupom);
externC int __stdcall Bematech_FI_IniciaFechamentoCupom( char * cAcrescimoDesconto,char * cTipoAcrescimoDesconto,char * cValorAcrescimoDesconto );
externC int __stdcall Bematech_FI_EfetuaFormaPagamentoDescricaoForma(char * cFormaPagamento,char * cValorFormaPagamento,char * cDescricaoForma );
externC int __stdcall Bematech_FI_EfetuaFormaPagamento( char * cFormaPagamento,char * cValorFormaPagamento );
externC int __stdcall Bematech_FI_TerminaFechamentoCupom ( char * cMensagem );
externC int __stdcall Bematech_FI_UsaComprovanteNaoFiscalVinculado (char* Texto);
externC int __stdcall Bematech_FI_FechaComprovanteNaoFiscalVinculado(void);
externC int __stdcall Bematech_FI_Sangria (char* Valor);
externC int __stdcall Bematech_FI_Suprimento (char* Valor, char* FormaPagamento);
externC int __stdcall Bematech_FI_Autenticacao(void);
externC int __stdcall Bematech_FI_ProgramaCaracterAutenticacao(char* Coordenadas);
externC int __stdcall Bematech_FI_AcionaGaveta(void);
externC int __stdcall Bematech_FI_VerificaEstadoGaveta (short int* Estado);
externC int __stdcall Bematech_FI_VerificaEstadoImpressora ( int* ACK, int* ST1, int* ST2);
externC int __stdcall Bematech_FI_RetornoAliquotas(char* Aliquotas);
externC int __stdcall Bematech_FI_SubTotal (char* SubTotal);
externC int __stdcall Bematech_FI_MonitoramentoPapel (int* LinhasImpressas);
externC int __stdcall Bematech_FI_DadosUltimaReducao (char* DadosReducao);
externC int __stdcall Bematech_FI_NumeroSerie (char* NumeroSerie);
externC int __stdcall Bematech_FI_NumeroSerieMFD (char* NumeroSerie);
externC int __stdcall Bematech_FI_VersaoFirmware (char* VersaoFirmware);
externC int __stdcall Bematech_FI_CGC_IE (char* CGC, char* IE);
externC int __stdcall Bematech_FI_GrandeTotal (char* GrandeTotal);
externC int __stdcall Bematech_FI_Descontos (char* Descontos);
externC int __stdcall Bematech_FI_Cancelamentos (char* Cancelamentos);
externC int __stdcall Bematech_FI_NumeroCupom (char* NumeroCupom);
externC int __stdcall Bematech_FI_NumeroOperacoesNaoFiscais (char* Operacoes);
externC int __stdcall Bematech_FI_NumeroCuponsCancelados (char* CuponsCancelados);
externC int __stdcall Bematech_FI_NumeroReducoes (char* Reducoes);
externC int __stdcall Bematech_FI_NumeroIntervencoes (char* Intervencoes);
externC int __stdcall Bematech_FI_NumeroSubstituicoesProprietario (char* Substituicoes);
externC int __stdcall Bematech_FI_UltimoItemVendido (char* UltimoItem);
externC int __stdcall Bematech_FI_ClicheProprietario(char* ClicheProprietario);
externC int __stdcall Bematech_FI_NumeroCaixa (char* NumeroCaixa);
externC int __stdcall Bematech_FI_NumeroLoja (char* NumeroLoja);
externC int __stdcall Bematech_FI_AlteraSimboloMoeda (char* SimboloMoeda);
externC int __stdcall Bematech_FI_SimboloMoeda (char* SimboloMoeda);
externC int __stdcall Bematech_FI_FlagsFiscais (int* FlagFiscal);
externC int __stdcall Bematech_FI_MinutosLigada (char* MinutosLigada);
externC int __stdcall Bematech_FI_MinutosImprimindo (char* MinutosImprimindo);
externC int __stdcall Bematech_FI_ModoOperacao (char* ModoOperacao);
externC int __stdcall Bematech_FI_VerificaEpromConectada (char* FlagEprom );
externC int __stdcall Bematech_FI_ValorPagoUltimoCupom (char* Valor);
externC int __stdcall Bematech_FI_DataHoraImpressora (char* Data, char* Hora);
externC int __stdcall Bematech_FI_ContadoresTotalizadoresNaoFiscais (char* Contadores);
externC int __stdcall Bematech_FI_VerificaTotalizadoresNaoFiscais (char* Totalizadores);
externC int __stdcall Bematech_FI_VerificaTotalizadoresParciais ( char * cTotalizadores );
externC int __stdcall Bematech_FI_VerificaModoOperacao( char * cModo );
externC int __stdcall Bematech_FI_DataHoraReducao (char* DataReducao, char* HoraReducao);
externC int __stdcall Bematech_FI_VerificaIndiceAliquotasIss ( char * cIndices );
externC int __stdcall Bematech_FI_VerificaFormasPagamento ( char * cFormas );
externC int __stdcall Bematech_FI_VerificaDepartamentos ( char * cDepartamentos );
externC int __stdcall Bematech_FI_UsaComprovanteNaoFiscalVinculado ( char * cTexto );
externC int __stdcall Bematech_FI_DataMovimento (char* DataMovimento);
externC int __stdcall Bematech_FI_VerificaTruncamento (char* FlagTruncamento);
externC int __stdcall Bematech_FI_VerificaAliquotasIss (char* AliquotasIss);
externC int __stdcall Bematech_FI_Acrescimos (char* ValorAcrescimo);
externC int __stdcall Bematech_FI_ContadorBilhetePassagem (char* NumeroBilhetes);
externC int __stdcall Bematech_FI_VerificaFormasPagamento (char* FormasPagamento);
externC int __stdcall Bematech_FI_VerificaRecebimentoNaoFiscal (char* Recebimentos);
externC int __stdcall Bematech_FI_VerificaDepartamentos (char* Departamentos);
externC int __stdcall Bematech_FI_VerificaTipoImpressora (int* TipoImpressora );
externC int __stdcall Bematech_FI_ProgramaMoedaSingular (char* MoedaSingular);
externC int __stdcall Bematech_FI_ProgramaMoedaPlural (char* MoedaPlural);
externC int __stdcall Bematech_FI_VerificaStatusCheque (short int * StatusCheque);
externC int __stdcall Bematech_FI_CancelaImpressaoCheque(void);
externC int __stdcall Bematech_FI_ImprimeCheque (char* NumeroBanco, char* Valor,char* Favorecido, char* Cidade,char* Data, char*  Mensagem);
externC int __stdcall Bematech_FI_IncluiCidadeFavorecido (char* Cidade, char* Favorecido);
externC int __stdcall Bematech_FI_EstornoFormasPagamento (char * FormaOrigem, char * FormaDestino, char * Valor );
externC int __stdcall Bematech_FI_AbreBilhetePassagem( char * ImprimeValorFinal, char * ImprimeEnfatizado,
                                                          char * Embarque, char * Destino, char * Linha,
                                                          char * Prefixo, char * Agente, char * Agencia,
                                                          char * Data, char * Hora, char * Poltrona, char * Plataforma );
externC int __stdcall Bematech_FI_MapaResumo(void);
externC int __stdcall Bematech_FI_MapaResumoMFD(void);
externC int __stdcall Bematech_FI_ContadorCupomFiscalMFD(char *sCupom);
externC int __stdcall Bematech_FI_RelatorioTipo60Analitico(void);
externC int __stdcall Bematech_FI_RelatorioTipo60Mestre(void);
externC int __stdcall Bematech_FI_AberturaDoDia(char* Valor, char* FormaPagamento);
externC int __stdcall Bematech_FI_FechamentoDoDia(void);
externC int __stdcall Bematech_FI_VerificaIndiceAliquotasIss( char * IndiceAliquotasISS );
externC int __stdcall Bematech_FI_ImprimeConfiguracoesImpressora( void );
externC int __stdcall Bematech_FI_ImprimeDepartamentos( void );
externC int __stdcall Bematech_FI_DataHoraGravacaoUsuarioSWBasicoMFAdicional(
	char *dataUsuario,char *dataSWBasico,char *MFAdicional );


// Funções para a impressora restaurante

externC int __stdcall Bematech_FIR_RegistraVenda (char* Mesa, char* Codigo, char* Descricao,char *  Aliquota,  char  *  Quantidade,char* ValorUnitario, char* FlagAcrescimoDesconto,char* ValorAcrescimoDesconto);
externC int __stdcall Bematech_FIR_CancelaVenda(char*,char*,char*,char*,char*,char*,char*,char*);
externC int __stdcall Bematech_FIR_AbreConferenciaMesa (char* Mesa);
externC int __stdcall Bematech_FIR_FechaConferenciaMesa (char* FlagAcrescimoDesconto,char* TipoAcrescimoDesconto,char* ValorAcrescimoDesconto);
externC int __stdcall Bematech_FIR_ConferenciaMesa(char* Mesa,char* FlagAcrescimoDesconto,char* TipoAcrescimoDesconto,char* ValorAcrescimoDesconto);
externC int __stdcall Bematech_FIR_TransferenciaMesa(char* MesaOrigem, char* MesaDestino);
externC int __stdcall Bematech_FIR_TransferenciaItem (char* MesaOrigem, char* Codigo,char* Descricao, char *  Aliquota,char* Quantidade,  char* ValorUnitario,char* FlagAcrescimoDesconto,char* ValorAcrescimoDesconto,char* MesaDestino);
externC int __stdcall Bematech_FIR_AbreCupomRestaurante (char* Mesa, char* CPF);
externC int __stdcall Bematech_FIR_FechaCupomRestaurante (char* FormaPagamento,char* AcrescimoDesconto,char* TipoAcrescimoDesconto,char* ValorAcrescimoDesconto,char* ValorPago,char* Mensagem);
externC int __stdcall Bematech_FIR_FechaCupomResumidoRestaurante(char* FormaPagamento,char* Mensagem);
externC int __stdcall Bematech_FIR_ContaDividida (char* NumeroCupons,  char* ValorPago,char* CPF);
externC int __stdcall Bematech_FIR_FechaCupomContaDividida (char* NumeroCupons,char* AcrescimoDesconto,char* TipoAcrescimoDesconto,char* ValorAcrescimoDesconto,char* FormaPagamento,char* ValorFormaPagamento,char* ValorPagoCliente,char* CPF);
externC int __stdcall Bematech_FIR_RelatorioMesasAbertas (short int TipoRelatorio);
externC int __stdcall Bematech_FIR_RelatorioMesasAbertasSerial (void);
externC int __stdcall Bematech_FIR_ImprimeCardapio (void);
externC int __stdcall Bematech_FIR_CardapioPelaSerial (void);
externC int __stdcall Bematech_FIR_RegistroVendaSerial (char* Mesa);
externC int __stdcall Bematech_FIR_VerificaMemoriaLivre(char* Bytes);
externC int __stdcall Bematech_FIR_TransferenciaItem( char * cMesaOrigem,char * cCodigo,char * cDescricao,char * cAliquota,char * cQuantidade,char * cValorUnitario,char * cFlagAcrescimoDesconto,char * cValorAcrescimoDesconto,char * cMesaDestino );

typedef int (__stdcall *BemaGeraRegistrosTipoE) (char * szMemFileName, char * szReportFileName, char * szDataInicial, char * szDataFinal, char * szRazaoSocial, char * szEndereco, char * szModelo, char * szCmd, char * szCRZ, char * szCRO, char * szCOO, char * szGNF, char * szCCF, char * szCVC, char * szCBP, char * szGRG, char * szCMV, char * szCFD, char * szGT, char * szNECF, char * szBP); 

typedef int (__stdcall *BemaGeraTxtPorCOO) (char *mfd_fname , char *txt_filename , int usuario,int cooini,int coofim); 

#endif
