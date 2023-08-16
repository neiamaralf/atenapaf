#ifndef epsonH
#define epsonH

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

#define Integer unsigned long
#define PInteger unsigned long*
#define PChar char*
#define Boolean bool

//=================================================================================================
// EPSON_Serial
//=================================================================================================
extern  Integer __stdcall DLL_IMPORT  EPSON_Serial_Abrir_Porta(Integer dwVelocidade, Integer wPorta);
extern  Integer __stdcall DLL_IMPORT  EPSON_Serial_Abrir_PortaEx();
extern  Integer __stdcall DLL_IMPORT  EPSON_Serial_Fechar_Porta ();
extern  Integer __stdcall DLL_IMPORT  EPSON_Serial_Obter_Estado_Com();
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Versao_SWBasicoEX(char *,char *,char *);
extern unsigned long __stdcall EPSON_Fiscal_Fechar_Cupom(int,int);
//=================================================================================================
// EPSON_Fiscal
//=================================================================================================
extern  Integer __stdcall DLL_IMPORT  EPSON_Fiscal_Abrir_Cupom(PChar pszCNPJ, PChar pszRazaoSocial, PChar pszEndereco1, PChar pszEndereco2, Integer dwPosicao);
extern  Integer __stdcall DLL_IMPORT  EPSON_Fiscal_Dados_Usuario(PChar pszCGC, PChar pszSocialReason, PChar pszAddress1, PChar pszAddress2, Integer dwPosition);
extern  Integer __stdcall DLL_IMPORT  EPSON_Fiscal_Vender_Item(PChar pszCodigo, PChar pszDescricao, PChar pszQuantidade, Integer dwQuantCasasDecimais, PChar pszUnidade, PChar pszPrecoUnidade, Integer dwPrecoCasasDecimais, PChar pszAliquotas, Integer dwLinhas);
extern  Integer __stdcall DLL_IMPORT  EPSON_Fiscal_Obter_SubTotal(PChar pszSubTotal);
extern  Integer __stdcall DLL_IMPORT  EPSON_Fiscal_Pagamento(PChar pszNumeroPagamento, PChar pszValorPagamento, Integer dwCasasDecimais, PChar pszDescricao1, PChar pszDescricao2);
extern  Integer __stdcall DLL_IMPORT  EPSON_Fiscal_Desconto_Acrescimo_Item(PChar pszValor, Integer dwCasasDecimais, Boolean bDesconto, Boolean bPercentagem);
extern  Integer __stdcall DLL_IMPORT  EPSON_Fiscal_Desconto_Acrescimo_Subtotal(PChar pszValor, Integer dwCasasDecimais, Boolean bDesconto, Boolean bPercentagem);
extern  Integer __stdcall DLL_IMPORT  EPSON_Fiscal_Cancelar_Cupom();
extern  Integer __stdcall DLL_IMPORT  EPSON_Fiscal_Cancelar_Item(PChar pszNumeroItem);
extern  Integer __stdcall DLL_IMPORT  EPSON_Fiscal_Cancelar_Ultimo_Item();
extern  Integer __stdcall DLL_IMPORT  EPSON_Fiscal_Cancelar_Desconto_Acrescimo_Item(Boolean bDesconto);
extern  Integer __stdcall DLL_IMPORT  EPSON_Fiscal_Cancelar_Acrescimo_Desconto_Subtotal(Boolean bDesconto);
extern  Integer __stdcall DLL_IMPORT  EPSON_Fiscal_Cancelar_Item_Parcial(PChar pszNumeroItem, PChar pszQuantidade, Integer dwQuantCasasDecimais);
extern  Integer __stdcall DLL_IMPORT  EPSON_Fiscal_Imprimir_Mensagem(PChar pszLinhaTexto1, PChar pszLinhaTexto2, PChar pszLinhaTexto3, PChar pszLinhaTexto4, PChar pszLinhaTexto5, PChar pszLinhaTexto6, PChar pszLinhaTexto7, PChar pszLinhaTexto8);
extern  Integer __stdcall DLL_IMPORT  EPSON_Fiscal_Configurar_Codigo_Barras_Mensagem(Integer dwLinha, Integer dwTipo, Integer dwAltura, Integer dwLargura, Integer dwPosicao, Integer dwCaracter);
extern  Integer __stdcall DLL_IMPORT  EPSON_Fiscal_Fechar_CupomEx(PChar pszTotalCupom);
extern  Integer __stdcall DLL_IMPORT  EPSON_Fiscal_Fechar_Cupom(Boolean bCortarPapel, Boolean bAdicional);
extern  Integer __stdcall DLL_IMPORT  EPSON_Fiscal_Mensagem_Aplicacao(PChar pszLinha01, PChar pszLinha02);
//=================================================================================================
// EPSON_NaoFiscal
//=================================================================================================
extern  Integer __stdcall DLL_IMPORT  EPSON_NaoFiscal_Abrir_Comprovante(PChar pszCNPJ, PChar pszRazaoSocial, PChar pszEndereco1, PChar pszEndereco2, Integer dwPosicao);
extern  Integer __stdcall DLL_IMPORT  EPSON_NaoFiscal_Vender_Item(PChar pszNumeroOperacao, PChar pszValorOperacao, Integer dwCasasDecimais);
extern  Integer __stdcall DLL_IMPORT  EPSON_NaoFiscal_Obter_SubTotal(PChar pszSubTotal);
extern  Integer __stdcall DLL_IMPORT  EPSON_NaoFiscal_Desconto_Acrescimo_Item(PChar pszValor, Integer dwCasasDecimais, Boolean bDesconto,Boolean bPercentagem);
extern  Integer __stdcall DLL_IMPORT  EPSON_NaoFiscal_Desconto_Acrescimo_Subtotal(PChar pszValor, Integer dwCasasDecimais, Boolean bDesconto, Boolean bPercentagem);
extern  Integer __stdcall DLL_IMPORT  EPSON_NaoFiscal_Pagamento(PChar pszNumeroPagamento, PChar pszValorPagamento, Integer dwCasasDecimais, PChar pszDescricao1, PChar pszDescricao2);
extern  Integer __stdcall DLL_IMPORT  EPSON_NaoFiscal_Cancelar_Item(PChar pszItem);
extern  Integer __stdcall DLL_IMPORT  EPSON_NaoFiscal_Cancelar_Ultimo_Item();
extern  Integer __stdcall DLL_IMPORT  EPSON_NaoFiscal_Cancelar_Desconto_Acrescimo_Item(Boolean bDesconto);
extern  Integer __stdcall DLL_IMPORT  EPSON_NaoFiscal_Cancelar_Desconto_Acrescimo_Subtotal(Boolean bDesconto);
extern  Integer __stdcall DLL_IMPORT  EPSON_NaoFiscal_Cancelar_Comprovante();
extern  Integer __stdcall DLL_IMPORT  EPSON_NaoFiscal_Fechar_Comprovante(Boolean bCortarPapel);
extern  Integer __stdcall DLL_IMPORT  EPSON_NaoFiscal_Abrir_CCD(PChar pszNumeroPagamento, PChar pszValor, Integer dwCasasDecimais, PChar pszParcelas);
extern  Integer __stdcall DLL_IMPORT  EPSON_NaoFiscal_Abrir_Relatorio_Gerencial(PChar pszNumeroRelatorio);
extern  Integer __stdcall DLL_IMPORT  EPSON_NaoFiscal_Imprimir_Linha(PChar pszLinha);
extern  Integer __stdcall DLL_IMPORT  EPSON_NaoFiscal_Fechar_CCD(Boolean bCortarPapel);
extern  Integer __stdcall DLL_IMPORT  EPSON_NaoFiscal_Fechar_Relatorio_Gerencial(Boolean bCortarPapel);
extern  Integer __stdcall DLL_IMPORT  EPSON_NaoFiscal_Cancelar_CCD(PChar pszNumeroPagamento, PChar pszValor, Integer dwCasasDecimais, PChar pszParcelas, PChar pszNumeroCupom);
extern  Integer __stdcall DLL_IMPORT  EPSON_NaoFiscal_Cancelar_Pagamento(PChar pszFormaPagamento, PChar pszNovaFormaPagamento, PChar pszValor, Integer dwCasasDecimais);
extern  Integer __stdcall DLL_IMPORT  EPSON_NaoFiscal_Nova_Parcela_CCD();
extern  Integer __stdcall DLL_IMPORT  EPSON_NaoFiscal_Nova_Via_CCD();
extern  Integer __stdcall DLL_IMPORT  EPSON_NaoFiscal_Reimprimir_CCD();
extern  Integer __stdcall DLL_IMPORT  EPSON_NaoFiscal_Sangria(PChar pszValor, Integer dwCasasDecimais);
extern  Integer __stdcall DLL_IMPORT  EPSON_NaoFiscal_Fundo_Troco(PChar pszValor, Integer dwCasasDecimais);
extern  Integer __stdcall DLL_IMPORT  EPSON_NaoFiscal_Imprimir_Codigo_Barras(Integer dwTipo, Integer dwAltura, Integer dwLargura, Integer dwPosicao, Integer dwCaracter, PChar pszCodigo);
//=================================================================================================
// EPSON_RelatorioFiscal
//=================================================================================================
extern  Integer __stdcall  EPSON_RelatorioFiscal_LeituraX(void);
extern  Integer __stdcall DLL_IMPORT  EPSON_RelatorioFiscal_RZ(PChar pszData, PChar pszHora, Integer dwHorarioVerao, PChar pszCRZ);
extern  Integer __stdcall DLL_IMPORT  EPSON_RelatorioFiscal_Leitura_MF (  PChar pszInicio, PChar pszFim, Integer dwTipoImpressao, PChar pszBuffer, PChar pszArquivo, 
	Integer *pdwTamanhoBuffer, Integer dwTamBuffer) ;
extern  Integer __stdcall DLL_IMPORT  EPSON_RelatorioFiscal_Salvar_LeituraX(PChar pszArquivo);
extern  Integer __stdcall DLL_IMPORT  EPSON_RelatorioFiscal_Abrir_Dia();
//=================================================================================================
// EPSON_Obter
//=================================================================================================
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Arquivo_Binario_MF(char *);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Arquivo_Binario_MFD(char *);
extern  Integer __stdcall DLL_IMPORT EPSON_Obter_Arquivos_Binarios(char *,char *,unsigned long,char *,char *);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Numero_Usuario(char *);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Dados_Usuario(PChar pszDadosUsuario);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Tabela_Aliquotas(PChar pszTabelaAliquotas);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Total_Jornada(PChar chOption, PChar pszZnumber, PChar pszData);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Tabela_Pagamentos(PChar pszTabelaPagamentos);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Tabela_NaoFiscais(PChar pszTabelaNaoFiscais);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Tabela_Relatorios_Gerenciais(PChar pszTabelaRelatoriosGerenciais);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Total_Cancelado(PChar pszTotalCancelado);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Total_Aliquotas(PChar pszAliquotasTotal);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Total_Bruto(PChar pszVendaBruta);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Total_Descontos(PChar pszTotalDescontos);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Total_Acrescimos(PChar pszTotalAcrescimos);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Dados_Impressora(PChar pszDadosImpressora);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Cliche_Usuario(PChar pszDadosUsuario);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Data_Hora_Jornada(PChar pszDataHora);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Numero_ECF_Loja(PChar pszDados);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Hora_Relogio(PChar pszDados);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Simbolo_Moeda(PChar pszDados);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Casas_Decimais(PChar pszDados);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Contadores(PChar pszDados);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Estado_Impressora(PChar pszDados);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_GT(PChar pszDados);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Linhas_Impressas(PChar pszDados);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Linhas_Impressas_RG(PChar pszDados);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Linhas_Impressas_CCD(PChar pszDados);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Linhas_Impressas_Vendas(PChar pszLinhasImpressas);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Linhas_Impressas_Pagamentos(PChar pszLinhasImpressas);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Total_Itens_Vendidos(PChar pszItens);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Estado_Memoria_Fiscal(PChar pszEstado);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Estado_MFD(PChar pszEstado);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Total_Leituras_X_Impressas(PChar pszLeituras);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Dados_Jornada(PChar pszDados);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Caracteres_Linha(PChar pszDados);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Operador(PChar pszDados);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Numero_Ultimo_Item(PChar pszDados);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Informacao_Item(PChar pszNumeroItem, PChar pszDadosItem);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Estado_Cupom(PChar pszEstado);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Informacao_Ultimo_Documento(PChar pszInfo);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Estado_Corte_Papel( Boolean bHabilitado);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Estado_Horario_Verao( Boolean bEstado);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Versao_DLL(PChar pszVersao);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Mensagem_Erro(PChar pszCodigoErro, PChar pszMensagemErro);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Venda_Bruta(PChar pszBrutAmount, PChar pszLastBrutAmount);
extern  Integer __stdcall DLL_IMPORT  EPSON_Obter_Dados_MF_MFD(PChar pszInicio, PChar pszFinal, Integer dwTipoEntrada, Integer dwEspelhos, Integer dwAtoCotepe, Integer dwSintegra, PChar pszArquivoSaida);
extern  Integer __stdcall DLL_IMPORT EPSON_Obter_Dados_Arquivos_MF_MFD(char *,char *,unsigned long,unsigned long,unsigned long,unsigned long,char *,char *,char *);
extern  Integer __stdcall DLL_IMPORT EPSON_Obter_Dados_Ultima_RZ( char *);
unsigned long __stdcall EPSON_RelatorioFiscal_Abrir_Jornada(void);
//=================================================================================================
// EPSON_Config
//=================================================================================================
extern  Integer __stdcall DLL_IMPORT  EPSON_Config_Aliquota(PChar pszTaxa, int bTipoISS);
extern  Integer __stdcall DLL_IMPORT  EPSON_Config_Relatorio_Gerencial(PChar pszReportDescription);
extern  Integer __stdcall DLL_IMPORT  EPSON_Config_Forma_Pagamento(Boolean bVinculado, PChar pszNumeroMeio, PChar pszDescricao);
extern  Integer __stdcall DLL_IMPORT  EPSON_Config_Totalizador_NaoFiscal(PChar pszDescricao,  Integer pdwNumeroTotalizador);
extern  Integer __stdcall DLL_IMPORT  EPSON_Config_Corte_Papel(Boolean bHabilitado);
extern  Integer __stdcall DLL_IMPORT  EPSON_Config_Horario_Verao();
extern  Integer __stdcall DLL_IMPORT  EPSON_Config_Espaco_Entre_Documentos(PChar pszLinhas);
extern  Integer __stdcall DLL_IMPORT  EPSON_Config_Espaco_Entre_Linhas(PChar pszEspacos);
extern  Integer __stdcall DLL_IMPORT  EPSON_Config_Logotipo(PChar pszDados, Integer dwTamDados, PChar pszLinha);
extern  Integer __stdcall DLL_IMPORT  EPSON_Config_Habilita_Logotipo(Boolean bHabilita);
extern  Integer __stdcall DLL_IMPORT  EPSON_Config_Operador(PChar pszDados);
extern  Integer __stdcall DLL_IMPORT  EPSON_Config_OperadorEX(PChar pszDados, Integer dwReport);
extern  Integer __stdcall DLL_IMPORT  EPSON_Config_Serial_Impressora(PChar pszVelocidade);
extern  Integer __stdcall DLL_IMPORT  EPSON_Config_Dados_Sintegra(PChar pszRazaoSocial, PChar pszLogradouro, PChar pszNumero, PChar pszComplemento, PChar pszBairro, PChar pszMunicipio, PChar pszCEP, PChar pszUF, PChar pszFax, PChar pszFone, PChar pszNomeContato);
//=================================================================================================
// EPSON_Cheque
//=================================================================================================
extern  Integer __stdcall DLL_IMPORT  EPSON_Cheque_Configurar_Moeda(PChar pszSingular, PChar pszPlural);
extern  Integer __stdcall DLL_IMPORT  EPSON_Cheque_Configurar_Parametros1(PChar pszNumeroRegistro, PChar pszValorX, PChar pszValorY, PChar pszDescricao1X, PChar pszDescricao1Y, PChar pszDescricao2X, PChar pszDescricao2Y);
extern  Integer __stdcall DLL_IMPORT  EPSON_Cheque_Configurar_Parametros2(PChar pszNumeroRegistro, PChar pszParaX, PChar pszParaY, PChar pszCidadeX, PChar pszCidadeY, PChar pszOffsetDia, PChar pszOffsetMes, PChar pszOffsetAno, PChar pszAdicionalX, PChar pszAdicionalY);
extern  Integer __stdcall DLL_IMPORT  EPSON_Cheque_Imprimir(PChar pszNumeroRegistro, PChar pszValor, Integer dwCasasDecimais, PChar pszPara, PChar pszCidade, PChar pszDados, PChar pszTexto);
extern  Integer __stdcall DLL_IMPORT  EPSON_Cheque_ImprimirEX(PChar pszNumeroRegistro, PChar pszValor, Integer dwCasasDecimais, PChar pszPara, PChar pszCidade, PChar pszDados, PChar pszTexto);
extern  Integer __stdcall DLL_IMPORT  EPSON_Cheque_Preparar_Endosso();
extern  Integer __stdcall DLL_IMPORT  EPSON_Cheque_Imprimir_Endosso(PChar pszLinhaTexto);
extern  Integer __stdcall DLL_IMPORT  EPSON_Cheque_Ejetar_Endosso();
extern  Integer __stdcall DLL_IMPORT  EPSON_Cheque_Cancelar_Impressao();
extern  Integer __stdcall DLL_IMPORT  EPSON_Cheque_Ler_MICR(PChar pszMICR);
//=================================================================================================
// EPSON_Impressora
//=================================================================================================
extern  Integer __stdcall DLL_IMPORT  EPSON_Impressora_Abrir_Gaveta();
extern  Integer __stdcall DLL_IMPORT  EPSON_Impressora_Avancar_Papel(Integer dwLines);
extern  Integer __stdcall DLL_IMPORT  EPSON_Impressora_Cortar_Papel();
//=================================================================================================
// EPSON_Autenticar
//=================================================================================================
extern  Integer __stdcall DLL_IMPORT  EPSON_Autenticar_Imprimir(PChar pszMensagem);
extern  Integer __stdcall DLL_IMPORT  EPSON_Autenticar_Reimprimir();
//=================================================================================================
// EPSON_Sys
//=================================================================================================
//extern  Integer __stdcall DLL_IMPORT  EPSON_Sys_Informar_Handle_Janela( hwndEdit:HWND );
extern  Integer __stdcall DLL_IMPORT  EPSON_Sys_Atualizar_Janela();
extern  Integer __stdcall DLL_IMPORT  EPSON_Sys_Aguardar_Arquivo(PChar pszArquivo, Integer dwTimeout, Boolean bBloqueiaEntradas, Boolean bSincrono);
extern  Integer __stdcall DLL_IMPORT  EPSON_Sys_Bloquear_Entradas(Boolean bBloqueiaEntradas);
extern  Integer __stdcall DLL_IMPORT  EPSON_Sys_Log(PChar pszPath, Integer dwAction);
//=================================================================================================
// EPSON_Display
//=================================================================================================
extern  Integer __stdcall DLL_IMPORT  EPSON_Display_Enviar_Texto(PChar pszTexto);
extern  Integer __stdcall DLL_IMPORT  EPSON_Display_Set_Cursor(Integer dwAcao, Integer dwColuna, Integer dwLinha);
extern  Integer __stdcall DLL_IMPORT  EPSON_Display_Apagar_Texto(Integer dwLinha);
extern  Integer __stdcall DLL_IMPORT  EPSON_Display_Configurar(Integer dwBrilho, Integer dwLampejo, Integer dwRolagem);
extern  Integer __stdcall DLL_IMPORT  EPSON_Display_Inicializar(Integer dwAcao);
//=================================================================================================

#endif