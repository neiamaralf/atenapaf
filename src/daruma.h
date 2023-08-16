#ifndef darumaH
#define darumaH
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef WIN32
#define CLR "cls"
#include <windows.h>
#else
#define CLR "clear"
#define boolean bool
#define _sleep sleep
#include <dlfcn.h>
#include <fcntl.h>
#include "stdbool.h"
#include "string.h"

#endif

typedef char* string;
#define FUNCAO_P int (*)

void carregarDarumaFramework();
void descarregarDarumaFramework();
void* carregarFuncaoDarumaFramework(const string nomeFuncao);
void retornosExtendidos(int iRetornoMetodo);

#define CARREGAR_DARUMA_FRAMEWORK() carregarDarumaFramework();
#define DESCARREGAR_DARUMA_FRAMEWORK() descarregarDarumaFramework();
//#define iRetorno


#pragma region METODOS_ECF

#pragma region ECF_CUPOM_FISCAL
// Abertura de cupom fiscal
int iCFAbrir_ECF_Daruma(string CPF, string Nome, string Endereco) ;
int iCFAbrirPadrao_ECF_Daruma(void) ;
// Registro de item
int iCFVender_ECF_Daruma(string CargaTributaria, string Quantidade, string PrecoUnitario, string TipoDescAcresc, string ValorDescAcresc, string CodigoItem, string UnidadeMedida, string DescricaoItem) ;
int iCFVenderSemDesc_ECF_Daruma(string CargaTributaria, string Quantidade, string PrecoUnitario, string CodigoItem, string UnidadeMedida, string DescricaoItem) ;
int iCFVenderResumido_ECF_Daruma(string CargaTributaria, string PrecoUnitario, string CodigoItem, string DescricaoItem) ;
// Desconto ou acrescimo  em item de cupom fiscal
int iCFLancarAcrescimoItem_ECF_Daruma(string NumItem, string TipoDescAcresc, string ValorDescAcresc) ;
int iCFLancarDescontoItem_ECF_Daruma(string NumItem, string TipoDescAcresc, string ValorDescAcresc) ;
int iCFLancarAcrescimoUltimoItem_ECF_Daruma(string TipoDescAcresc, string ValorDescAcresc) ;
int iCFLancarDescontoUltimoItem_ECF_Daruma(string TipoDescAcresc, string ValorDescAcresc) ;
// Cancelamento total de item em cupom fiscal
int iCFCancelarItem_ECF_Daruma(string NumItem) ;
int iCFCancelarUltimoItem_ECF_Daruma(void) ;
// Cancelamento parcial de item em cupom fiscal
int iCFCancelarItemParcial_ECF_Daruma(string NumItem, string Quantidade) ;
int iCFCancelarUltimoItemParcial_ECF_Daruma(string Quantidade) ;
// Cancelamento de desconto em item
int iCFCancelarDescontoItem_ECF_Daruma(string NumItem) ;
int iCFCancelarDescontoUltimoItem_ECF_Daruma(void) ;
// Totalizacao de cupom fiscal
int iCFTotalizarCupom_ECF_Daruma(string TipoDescAcresc, string ValorDescAcresc) ;
int iCFTotalizarCupomPadrao_ECF_Daruma(void) ;
//Cancelamento de desconto e acrescimo em subtotal de cupom fiscal
int iCFCancelarDescontoSubtotal_ECF_Daruma(void) ;
int iCFCancelarAcrescimoSubtotal_ECF_Daruma(void) ;
//Descricao do meios de pagamento de cupom fiscal
int iCFEfetuarPagamentoPadrao_ECF_Daruma(void) ;
int iCFEfetuarPagamentoFormatado_ECF_Daruma(string FormaPgto, string Valor) ;
int iCFEfetuarPagamento_ECF_Daruma(string FormaPgto, string Valor, string InfoAdicional) ;
//Encerramento de cupom fiscal
int iCFEncerrarPadrao_ECF_Daruma(void) ;
int iCFEncerrarConfigMsg_ECF_Daruma(string Mensagem) ;
int iCFEncerrar_ECF_Daruma(string CupomAdicional, string Mensagem) ;
int iCFEncerrarResumido_ECF_Daruma(void) ;
int iCFEmitirCupomAdicional_ECF_Daruma(void) ;
//Cancelamento de cupom fiscal
int iCFCancelar_ECF_Daruma(void) ;
//Identificar consumidor rodape do Cupom fiscal
int iCFIdentificarConsumidor_ECF_Daruma(char *pszNome, char *pszEndereco, char *pszDoc) ;
//Bilhete Passagem
int iCFBPAbrir_ECF_Daruma(char *Origem,char *Destino, char *Destino_UF,char *Percurso, char *Prestadora, char *Plataforma, char *Poltrona, char *Modalidade, char *Categoria, char *DataHora_Embarque,char *RGPassageiro, char *NomePassageiro, char *EnderecoPassageiro);
int iCFBPVender_ECF_Daruma(char *pszAliquota, char *pszValor, char *pszTipoDescAcresc, char *pszValorDescAcresc, char *pszDescricao) ;
int confCFBPProgramarUF_ECF_Daruma(char *pszUF) ;

#pragma endregion

#pragma region ECF_RELATORIO_GERENCIAL

int iRGAbrir_ECF_Daruma(string NomeRG);
int iRGAbrirIndice_ECF_Daruma(int iIndiceRG);
int iRGAbrirPadrao_ECF_Daruma(void);
int iRGImprimirTexto_ECF_Daruma(string texto);
int iRGFechar_ECF_Daruma(void);	

#pragma endregion

#pragma region ECF_RELATORIOS_FISCAIS

int iLeituraX_ECF_Daruma(void);
int rLeituraX_ECF_Daruma(void);
int iSangria_ECF_Daruma(string Valor, string Mensagem);
int iSangriaPadrao_ECF_Daruma(void);
int iSuprimento_ECF_Daruma(string Valor, string Mensagem);
int iSuprimentoPadrao_ECF_Daruma(void);
int iReducaoZ_ECF_Daruma(string Dataini, string Datafim);
int iMFLerSerial_ECF_Daruma(string DataIni, string DataFim);
int iMFLer_ECF_Daruma(string DataIni, string DataFim);

#pragma endregion

#pragma region ECF_COMPROVANTE_NAO_FISCAL
// --- ECF - Comprovante não fiscal - Inicio --- 
// Abertura de comprovante nao fiscal
int iCNFAbrir_ECF_Daruma(string pszCPF, string pszNome,  string pszEndereco);
int iCNFAbrirPadrao_ECF_Daruma(void);

// Recebimento de itens
int iCNFReceber_ECF_Daruma(string pszIndice, string pszValor,  string pszTipoDescAcresc, string pszValorDescAcresc);
int iCNFReceberSemDesc_ECF_Daruma(string pszIndice, string pszValor);

//Cancelamento de item
int iCNFCancelarItem_ECF_Daruma(string pszNumItem);
int iCNFCancelarUltimoItem_ECF_Daruma(void);

//Cancelamento de acrescimo em item
int iCNFCancelarAcrescimoItem_ECF_Daruma(string pszNumItem);
int iCNFCancelarAcrescUltimoItem_ECF_Daruma(void);

// Cancelamento de desconto em item
int iCNFCancelarDescontoItem_ECF_Daruma(string pszNumItem);
int iCNFCancelarDescUltimoItem_ECF_Daruma(void);

// Totalizacao de CNF
int iCNFTotalizarComprovante_ECF_Daruma(string pszTipoDescAcresc, string pszValorDescAcresc);
int iCNFTotalizarComprovPadrao_ECF_Daruma(void);

// Cancelamento de desconto e acrescimo em subtotal de CNF
int iCNFCancelarAcrescimoSubtotal_ECF_Daruma(void);
int iCNFCancelarDescontoSubtotal_ECF_Daruma(void);

// Descricao do meios de pagamento de CNF
int iCNFEfetuarPagamento_ECF_Daruma(string pszFormaPgto, string pszValor, string pszInfoAdicional);
int iCNFEfetuarPagamentoFormatado_ECF_Daruma(string pszFormaPgto, string pszValor);
int iCNFEfetuarPagamentoPadrao_ECF_Daruma(void);

// Encerramento de CNF
int iCNFEncerrar_ECF_Daruma(string pszMensagem);
int iCNFEncerrarPadrao_ECF_Daruma(void);

//Cancelamento de CNF
int iCNFCancelar_ECF_Daruma(void);

#pragma endregion

#pragma region ECF_COMPROVANTE_CREDITO_DEBITO

int iCCDAbrir_ECF_Daruma(string FormaPgto, string Parcelas, string DocOrigem, string Valor, string CPF, string Nome,  string Endereco);
int iCCDAbrirSimplificado_ECF_Daruma(string FormaPgto, string Parcelas, string DocOrigem,  string Valor);
int iCCDAbrirPadrao_ECF_Daruma(void);
int iCCDImprimirTexto_ECF_Daruma(string Texto);
int iCCDImprimirArquivo_ECF_Daruma(string ArqOrigem);
int iCCDFechar_ECF_Daruma(void);
int iCCDEstornarPadrao_ECF_Daruma(void);
int iCCDEstornar_ECF_Daruma(string pszCOO, string pszCPF, string pszNome, string pszEndereco);
int eTEF_EsperarArquivo_ECF_Daruma(string ArqOrigem, boolean TravarTeclado, string Tempo);
int eTEF_TravarTeclado_ECF_Daruma(boolean travar);
int eTEF_SetarFoco_ECF_Daruma(string titulo);
int iTEF_ImprimirRespostaCartao_ECF_Daruma(string ArqOrigem, boolean TravarTeclado, string Pagamento, string Valor);
int iTEF_ImprimirResposta_ECF_Daruma(string ArqOrigem, boolean TravarTeclado, string Pagamento, string Valor);
int iTEF_Fechar_ECF_Daruma(void);

#pragma endregion

#pragma region ECF_METODOS_RETORNO_STATUS

//Status Cupom Fiscal
int rCFVerificarStatus_ECF_Daruma(char *cStatus, int *piStatus) ;
//Status ultimo comando
int rStatusUltimoCmd_ECF_Daruma(char *Erro, char *Aviso, int *piErro, int *piAviso) ;
int rStatusUltimoCmdInt_ECF_Daruma(int *cErro, int *piAviso) ;
//Status Impressora
int rDataHoraImpressora_ECF_Daruma(string Data, string Hora) ;
int rVerificarImpressoraLigada_ECF_Daruma(void) ;
int rStatusImpressora_ECF_Daruma(string Status) ;
//Retorna Informações Estendidas
int rInfoEstentida_ECF_Daruma(int i, char *c) ;
int rInfoEstentida1_ECF_Daruma(char *cInfoEx) ;
int rInfoEstentida2_ECF_Daruma(char *cInfoEx) ;
int rInfoEstentida3_ECF_Daruma(char *cInfoEx) ;
int rInfoEstentida4_ECF_Daruma(char *cInfoEx) ;
int rInfoEstentida5_ECF_Daruma(char *cInfoEx) ;
int rVerificarReducaoZ_ECF_Daruma(char *zPendente) ;
//Retornos da Impressora
int rRetornarInformacao_ECF_Daruma(string Indice, char *Retornar) ;
int rRetornarNumeroSerie_ECF_Daruma(string SerialCriptografado, string Serial) ;
int rLerAliquotas_ECF_Daruma(char *cAliquotas) ;
int rLerMeiosPagto_ECF_Daruma(string Relatorios);
int rLerRG_ECF_Daruma(string Relatorios) ;
int rLerDecimais_ECF_Daruma(string DecimalQtde, string DecimalValor, int *piDecimalQtde, int *piDecimalValor) ;
int rRetornarDadosReducaoZ_ECF_Daruma(string Dados) ;
int eInterpretarErro_ECF_Daruma(int iIndice, char *pszRetorno);
int eInterpretarAviso_ECF_Daruma(int iIndice, char *pszRetorno);

#pragma endregion

#pragma region ECF_ESPECIAIS


int eBuscarPortaVelocidade_ECF_Daruma(void);
int eBuscarPortaVelocidade_ECF(void);
int eEnviarComando_ECF_Daruma(char * cComando, int iTamanhoComando, int iType);	
int eRetornarAviso_ECF_Daruma(void);
int eRetornarErro_ECF_Daruma(void);

#pragma endregion

#pragma region GERACAO_ARQUIVOS
int rGerarRelatorio_ECF_Daruma(string Str_Relatorio,string Str_Tipo,string Str_Inicial,string Str_Final);
int rGerarRelatorioOffline_ECF_Daruma(string Str_Relatorio,string Str_Tipo,string Str_Inicial,string Str_Final,string Str_ArquivoMF,string Str_ArquivoMFD,string Str_ArquivoInfo);
int rGerarEspelhoMFD_ECF_Daruma(string pszTipo, string pszInicial, string pszFinal);

#pragma endregion

#pragma region PROGRAMACAO_ECF
int confCadastrarPadrao_ECF_Daruma(string pszCadastrar, string pszValor);
int confCadastrar_ECF_Daruma(string pszCadastrar, string pszValor, string pszSeparador);
int confHabilitarHorarioVerao_ECF_Daruma(void);
int confDesabilitarHorarioVerao_ECF_Daruma(void);
int confHabilitarModoPreVenda_ECF_Daruma(void);
int confDesabilitarModoPreVenda_ECF_Daruma(void);
int confProgramarAvancoPapel_ECF_Daruma(string pszSepEntreLinhas,string pszSepEntreDoc,string pszLinhasGuilhotina,string pszGuilhotina,string pszImpClicheAntecipada);
int confFBProgramarIDLoja_ECF_Daruma(string pszValor);
int confProgramarOperador_ECF_Daruma(string pszValor);
#pragma endregion 

#pragma region REGISTRY
//Obter valor do Registry
int regRetornaValorChave_DarumaFramework(string pszProduto, string pszChave, char *pszValor);
//ECF
int regAlterarValor_Daruma(string pszPathChave, string pszValor);
int regECFAguardarImpressao_ECF_Daruma(string pszValor);
int regECFArquivoLeituraX_ECF_Daruma(string pszValor);
int regECFAuditoria_ECF_Daruma(string pszValor);
int regECFCaracterSeparador_ECF_Daruma(string pszValor);
//Cupom Fiscal 
int regCFCupomAdicionalDllConfig_ECF_Daruma(string pszValor);
int regCFCupomAdicionalDllTitulo_ECF_Daruma(string pszValor);
int regCupomMania_ECF_Daruma(string pszValor);
int regCFFormaPgto_ECF_Daruma(string pszValor);
int regCFMensagemPromocional_ECF_Daruma(string pszValor);
int regCFQuantidade_ECF_Daruma(string pszValor);
int regCFTamanhoMinimoDescricao_ECF_Daruma(string pszValor);
int regCFTipoDescAcresc_ECF_Daruma(string pszValor);
int regCFUnidadeMedida_ECF_Daruma(string pszValor);
int regCFValorDescAcresc_ECF_Daruma(string pszValor);
//CCD
int regCCD_ECF_Daruma(string pszChave, string pszValor);
int regCCDDocOrigem_ECF_Daruma(string pszValor);
int regCCDFormaPgto_ECF_Daruma(string pszValor);
int regCCDLinhasTEF_ECF_Daruma(string pszValor);
int regCCDParcelas_ECF_Daruma(string pszValor);
int regCCDValor_ECF_Daruma(string pszValor);
//Ato Cotepe
int regAtoCotepe_ECF_Daruma(string pszChave, string pszValor);
//Sintegra
int regSintegra_ECF_Daruma(string pszChave, string pszValor);
//Especiais
int eDefinirProduto_ECF_Daruma(string pszValor);
int eDefinirModoRegistro_ECF_Daruma(string pszValor);



#pragma endregion

#pragma region PAF-ECF

//MD5
int rCalcularMD5_ECF_Daruma(string pszPathArquivo, char * pszMD5GeradoHex, char * pszMD5GeradoAscii);
//RSA-EAD 
int rAssinarRSA_ECF_Daruma(string pszPathArquivo, string pszChavePrivada, char * pszAssinaturaGerada);
//GT CODIFICADO
int rRetornarGTCodificado_ECF_Daruma(char*pszValor);
int rVerificarGTCodificado_ECF_Daruma(char*pszValor);
//NUMERO DE SERIE CODIFICADO
int rRetornarNumeroSerieCodificado_ECF_Daruma(char*pszValor);
int rVerificarNumeroSerieCodificado_ECF_Daruma(char*pszValor);
//Codigo Modelo Fiscal
int rCodigoModeloFiscal_ECF_Daruma(char*pszValor);

#pragma endregion

#pragma region GAVETA_AUTENTICA_E_OUTROS

int eAcionarGuilhotina_ECF_Daruma(string pszTipoCorte);
int eAbrirGaveta_ECF_Daruma(void);

#pragma endregion

#pragma endregion

#pragma region ECF_METODOS_ESPECIAIS

// --- Especiais - Inicio --- 

int eDefinirProduto_Daruma(string produto);
int eRetornarAviso_ECF_Daruma() ;
int eRetornarErro_ECF_Daruma() ;
int eBuscarPortaVelocidade_ECF_Daruma(void) ;
int eBuscarPortaVelocidade_ECF(void) ;
int eEnviarComando_ECF_Daruma(string Comando, int iTamanhoComando, int iType) ;
int regAlterarValor_Daruma(string Chave, string Valor);
int iEjetarCheque_ECF_Daruma(void) ;
int iEstornarPagamento_ECF_Daruma(string FormaPgtoEstornado, string FormaPgtoEfetivado, string Valor, string InfoAdicional) ;

#pragma endregion

#pragma region METODOS_DUAL

#pragma region REGISTRO_DUAL

int regAguardarProcesso_DUAL_DarumaFramework(string valor);
int regCodePageAutomatico_DUAL_DarumaFramework(string valor);
int regEnterFinal_DUAL_DarumaFramework(string valor);
int regInicializou_DUAL_DarumaFramework(string valor);
int regLinhasGuilhotina_DUAL_DarumaFramework(string valor);
int regModoGaveta_DUAL_DarumaFramework(string valor);
int regPortaComunicacao_DUAL_DarumaFramework(string valor);
int regTabulacao_DUAL_DarumaFramework(string valor);
int regTermica_DUAL_DarumaFramework(string valor);
int regVelocidade_DUAL_DarumaFramework(string valor);
int regZeroCortado_DUAL_DarumaFramework(string valor);

#pragma endregion

#pragma region STATUS_IMPRESSORA_DUAL
int rStatusDocumento_DUAL_DarumaFramework(void);
int rStatusGaveta_DUAL_DarumaFramework(int *gavetaStatus);
int rStatusImpressora_DUAL_DarumaFramework(void);
int rStatusGuilhotina_DUAL_DarumaFramework(void);
#pragma endregion

#pragma region AUTENTICACAO_IMPRESSAO_DUAL

int iAcionarGaveta_DUAL_DarumaFramework(void);
int iAutenticarDocumento_DUAL_DarumaFramework(string documento, string local, string timeout);
int iImprimirArquivo_DUAL_DarumaFramework(string arquivo);
int iImprimirTexto_DUAL_DarumaFramework(string texto, int tamahoTexto);
int iConfigurarGuilhotina_DUAL_DarumaFramework(int habilitar, int quantidadeLinha);
int iEnviarBMP_DUAL_DarumaFramework(string arquivoOrigem);
int iLimparBuffer_DUAL_DarumaFramework(void);
int iReinicializar_DUAL_DarumaFramework(void);

#pragma endregion

#pragma endregion

#pragma region METODOS_MODEM

int eAtivarConexaoCsd_MODEM_DarumaFramework(void);
int eApagarSms_MODEM_DarumaFramework(string indice);
int eFinalizarChamadaCsd_MODEM_DarumaFramework(void);
int eInicializar_MODEM_DarumaFramework(void);
int eRealizarChamadaCsd_MODEM_DarumaFramework(string telefone);
int eTrocarBandeja_MODEM_DarumaFramework(void);
int regLerApagar_MODEM_DarumaFramework(string valor);
int regPorta_MODEM_DarumaFramework(string valor);
int regThread_MODEM_DarumaFramework(string valor);
int regVelocidade_MODEM_DarumaFramework(string valor);
int regCaptionWinAPP_MODEM_DarumaFramework(string valor);
int regBandejaInicio_MODEM_DarumaFramework(string valor);
int regTempoAlertar_MODEM_DarumaFramework(string valor);
int rReceberSms_MODEM_DarumaFramework(char *indice, char *mensagem, char *data, char *hora, char *remetente);
int rRetornarImei_MODEM_DarumaFramework(char *imei );
int rRetornarOperadora_MODEM_DarumaFramework(char *operadora);
int rReceberDadosCsd_MODEM_DarumaFramework(char *resposta);
int rNivelSinalRecebido_MODEM_DarumaFramework(void);
int rListarSms_MODEM_DarumaFramework(void);
int tEnviarDadosCsd_MODEM_DarumaFramework(string dados);
int tEnviarSms_MODEM_DarumaFramework(string telefone, string mensagem);

#pragma endregion

#pragma region METODOS_TA2000

int eAtivarCampo_TA2000_Daruma(char *retorno, int numeroCampo);
int fnEncerrar_TA2000_Daruma(int shutdown);
int iAdicionarCampo_TA2000_Daruma(string valorAtual, int tipoDado, int linha, int coluna, int tamanhoDisplay);
int iApagarCaracter_TA2000_Daruma(void);
int iCarriageReturn_TA2000_Daruma(void);
int icomEnviarByte_TA2000_Daruma(unsigned char byte);
int iDesabilitarCursor_TA2000_Daruma(void);
int iEditarDadosDisplay_TA2000_Daruma(char *retorno, string ctrlString, ...);
int iEntrarDadosDisplay_TA2000_Daruma(string eco, int tipoDados, int tamanhoParametros, int ESC, int linhaParametro, int colunaParametro, char *bufferInputDisplay);
int iEnviarDadosFormatados_TA2000_Daruma(string bufferXML, char *retorno);
int iImprimirDisplay_TA2000_Daruma(string bufferDisplay, int linha, int coluna);
int iLimparDisplay_TA2000_Daruma(void);
int iLimparDisplayLinha_TA2000_Daruma(int linha);
int iPosicionarCursor_TA2000_Daruma(int linha, int coluna);
int regADLinha_TA2000_Daruma(string valor);
int regAELinha_TA2000_Daruma(string valor);
int regAuditoria_TA2000_Daruma(string valor);
int regCLinha_TA2000_Daruma(string valor);
int regEdicaoColuna_TA2000_Daruma(string valor);
int regEdicaoEco_TA2000_Daruma(string valor);
int regEdicaoESC_TA2000_Daruma(string valor);
int regEdicaoLinha_TA2000_Daruma(string valor);
int regEdicaoTamanho_TA2000_Daruma(string valor);
int regEdicaoTipo_TA2000_Daruma(string valor);
int regImprimirColuna_TA2000_Daruma(string valor);
int regImprimirLinha_TA2000_Daruma(string valor);
int regMarcadorOpcao_TA2000_Daruma(string valor);
int regMascara_TA2000_Daruma(string valor);
int regMascaraEco_TA2000_Daruma(string valor);
int regMascaraLetra_TA2000_Daruma(string valor);
int regMascaraNumero_TA2000_Daruma(string valor);
int regMensagemBoasVindasLinha1_TA2000_Daruma(string valor);
int regMensagemBoasVindasLinha2_TA2000_Daruma(string valor);
int regMenuDirecao_TA2000_Daruma(string valor);
int regMenuESC_TA2000_Daruma(string valor);
int regMenuEstilo_TA2000_Daruma(string valor);
int regPorta_TA2000_Daruma(string valor);
int regPosColuna_TA2000_Daruma(string valor);
int regPosLinha_TA2000_Daruma(string valor);
int rLerValorCampoString_TA2000_Daruma(int numeroCampo, char *retorno);
int rLerValorOpcaoCombo_TA2000_Daruma(int combo, char *retorno);
int rLerDadoCombo_TA2000_Daruma(int numeroCombo, string dado, char *retorno);
int rLerDadoCampo_TA2000_Daruma(int numeroCampo,string dado, char *retorno);

#pragma endregion
#endif
