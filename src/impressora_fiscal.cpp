
#include "vilavilela.h"
#include "impressora_fiscal.h"
#include "sweda.h"
#include "relatorios.h"

using namespace RELATORIOS::assinatura;
using namespace RELATORIOS::atoCOTEP1704;
using namespace RELATORIOS::utils;
using namespace RELATORIOS::requisitoXXV;
using namespace RELATORIOS::requisitoXXII;
using namespace IMPRESSORA_FISCAL;

#define ASSERT_PRINTERON() if(!vilavielaframe->impressoraligada)return 1;

int IMPRESSORA_FISCAL::_LeituraMemoriaFiscalReducao(char *redi,char *redf,int flag) {
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	int Retorno=0;
	if (BEMATECH_MATRICIAL)
		Retorno = Bematech_FI_LeituraMemoriaFiscalReducao(redi,redf);
	else
		if (BEMATECH_TERMICAS ||BEMATECH_MATRICIAL_MFD)
			Retorno = Bematech_FI_LeituraMemoriaFiscalReducaoMFD(redi,redf,FLAG_LEITURA[flag]);
		else
			if (SWEDA_MATRICIAL)
				Retorno = ECF_LeituraMemoriaFiscalReducao(redi,redf);
			else
				if (BEMATECH_TERMICAS) {
					char C[]="C",S[]="S";
					Retorno = ECF_LeituraMemoriaFiscalReducaoMFD(redi,redf,flag==0?C:S);
				}
	vilavielaframe->Analisa_iRetorno(Retorno);
	return Retorno;
}

int IMPRESSORA_FISCAL::_LeituraMemoriaFiscalSerialReducao(char *redi,char *redf,int flag) {
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	int Retorno=0;
	if (BEMATECH_MATRICIAL)
		Retorno = Bematech_FI_LeituraMemoriaFiscalSerialReducao(redi,redf);
	else
		if (BEMATECH_TERMICAS ||BEMATECH_MATRICIAL_MFD)
			Retorno = Bematech_FI_LeituraMemoriaFiscalSerialReducaoMFD(redi,redf,FLAG_LEITURA[flag]);
		else
			if (SWEDA_MATRICIAL)
				Retorno = ECF_LeituraMemoriaFiscalSerialReducao(redi,redf);
			else
				if (BEMATECH_TERMICAS) {
					char C[]="C",S[]="S";
					Retorno = ECF_LeituraMemoriaFiscalSerialReducaoMFD(redi,redf,flag==0?C:S);
				}
	vilavielaframe->Analisa_iRetorno(Retorno);
	return Retorno;
}

int IMPRESSORA_FISCAL::_LeituraMemoriaFiscalData(char *dataini,char *datafim,int flag) {
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	int Retorno=0;
	if (BEMATECH_MATRICIAL)
		Retorno = Bematech_FI_LeituraMemoriaFiscalData(dataini,datafim);
	else
		if (BEMATECH_TERMICAS ||BEMATECH_MATRICIAL_MFD)
			Retorno = Bematech_FI_LeituraMemoriaFiscalDataMFD(dataini,datafim,FLAG_LEITURA[flag]);
		else
			if (SWEDA_MATRICIAL)
				Retorno = ECF_LeituraMemoriaFiscalData(dataini,datafim);
			else
				if (BEMATECH_TERMICAS) {
					char C[]="C",S[]="S";
					Retorno = ECF_LeituraMemoriaFiscalDataMFD(dataini,datafim,flag==0?C:S);
				}
	vilavielaframe->Analisa_iRetorno(Retorno);
	return Retorno;
}

int IMPRESSORA_FISCAL::_LeituraMemoriaFiscalSerialData(char *dataini,char *datafim,int flag) {
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	int Retorno=0;
	if (BEMATECH_MATRICIAL)
		Retorno = Bematech_FI_LeituraMemoriaFiscalSerialData(dataini,datafim);
	else
		if (BEMATECH_TERMICAS ||BEMATECH_MATRICIAL_MFD)
			Retorno = Bematech_FI_LeituraMemoriaFiscalSerialDataMFD(dataini,datafim,FLAG_LEITURA[flag]);
		else
			if (SWEDA_MATRICIAL)
				Retorno = ECF_LeituraMemoriaFiscalSerialData(dataini,datafim);
			else
				if (BEMATECH_TERMICAS) {
					char C[]="C",S[]="S";
					Retorno = ECF_LeituraMemoriaFiscalSerialDataMFD(dataini,datafim,flag==0?C:S);
				}
	vilavielaframe->Analisa_iRetorno(Retorno);
	return Retorno;
}

int IMPRESSORA_FISCAL::_NumSerieImpressora(char *buf) {
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	int Retorno=0;
	if (BEMATECH_MATRICIAL)
		Retorno = Bematech_FI_NumeroSerie(buf);
	else
		if (BEMATECH_TERMICAS ||BEMATECH_MATRICIAL_MFD)
			Retorno = Bematech_FI_NumeroSerieMFD(buf);
		else
			if (SWEDA_MATRICIAL)
				Retorno = ECF_NumeroSerie(buf);
			else
				if (BEMATECH_TERMICAS)
					Retorno = ECF_NumeroSerieMFD(buf);
	vilavielaframe->Analisa_iRetorno(Retorno);
	return Retorno;
}

int IMPRESSORA_FISCAL::_MarcaModeloTipoImpressora(char *marca,char *modelo,char *tipo) {
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	int Retorno=0;
	if (BEMATECH_MATRICIAL) {
		Retorno = Bematech_FI_ModeloImpressora(modelo);
		strcpy(marca,"BEMATECH");
		strcpy(tipo,"ECF-IF");
	}
	else
		if (BEMATECH_TERMICAS ||BEMATECH_MATRICIAL_MFD) {
			Retorno = Bematech_FI_MarcaModeloTipoImpressoraMFD(marca,modelo,tipo);
		}
		else
			if (SWEDA_TODOSOSMODELOS) {
				Retorno = ECF_MarcaModeloTipoImpressoraMFD(marca,modelo,tipo);
			}
	vilavielaframe->Analisa_iRetorno(Retorno);
	return Retorno;
}

int IMPRESSORA_FISCAL::_NumSubstituicoes(char *buf) {
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	int Retorno=0;
	if (BEMATECH_TODOSOSMODELOS) {
		Retorno = Bematech_FI_NumeroSubstituicoesProprietario(buf);
	}
	else
		if (SWEDA_TODOSOSMODELOS) {
			Retorno = ECF_NumeroSubstituicoesProprietario(buf);
		}
	vilavielaframe->Analisa_iRetorno(Retorno);
	return Retorno;
}

int IMPRESSORA_FISCAL::_ProgramaAliquota(char *buf,int tipo) {
	//MODOTESTE() 1;
 ASSERT_PRINTERON()
	int Retorno=0;
	if (BEMATECH_TODOSOSMODELOS) {
		Retorno = Bematech_FI_ProgramaAliquota(buf,tipo);
	}
	else
		if (SWEDA_TODOSOSMODELOS) {
			Retorno = ECF_ProgramaAliquota(buf,tipo);
		}
	vilavielaframe->Analisa_iRetorno(Retorno);
	return Retorno;
}

int IMPRESSORA_FISCAL::_geracotepe1704_COO( char *fnameCotep1704,char *COOi,char *COOf,int tipo){
	//Bematech_FI_ArquivoMFD(fnameCotep1704,redi,redf,"C","1",0,"","",1);
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	int ret=0;
	if (BEMATECH_MATRICIAL||SWEDA_MATRICIAL) {
		ret=0;
	}
	else if (BEMATECH_MFD||BEMATECH_MFD2) {
		_DownloadMFD_COO(COOi,COOf);
		_DownloadMF();
#ifdef WIN32				
		HINSTANCE hDLL;              
		BemaGeraRegistrosTipoE _BemaGeraRegistrosTipoE=NULL; 
		BemaGeraTxtPorCOO _BemaGeraTxtPorCOO=NULL; 
		if(BEMATECH_MFD)
		 hDLL = LoadLibrary(L"BemaMFD");
		else
			hDLL = LoadLibrary(L"BemaMFD2");
		if (hDLL != NULL){
			_BemaGeraRegistrosTipoE = (BemaGeraRegistrosTipoE)GetProcAddress(hDLL,"BemaGeraRegistrosTipoE");
			_BemaGeraTxtPorCOO = (BemaGeraTxtPorCOO)GetProcAddress(hDLL,"BemaGeraTxtPorCOO");
			if (!_BemaGeraRegistrosTipoE||!_BemaGeraTxtPorCOO){  
				FreeLibrary(hDLL);       
				return 0;
			}
			else{
				_BemaGeraTxtPorCOO("DOWNLOAD.MFD","espelho.txt",atoi(vilavielaframe->ecf.Numero_do_usuario),atoi(COOi),atoi(COOf));
				char *mespelho=0,*ptr,linha[512],*lastptr;
				_load_file_to_buf("espelho.txt",&mespelho);
				ptr=mespelho;
				wxArrayString linhas;
				lastptr=mespelho+strlen(mespelho)-1;						
				while((ptr=le_ate_fim_linha(ptr,linha))<lastptr){
					if(strlen(linha)>0)
						linhas.Add(wxString::From8BitData(linha));
				}					
				if(mespelho)	free(mespelho);
				wxString tmpstr=linhas.Item(6);
				wxString dataini,datafim;
				dataini= tmpstr.SubString(0,9);
				if(MODELO_IMPRESSORA==Bematech_MP_2100_TH_FI){
					tmpstr=linhas.Item(linhas.GetCount()-2);
					datafim=tmpstr.SubString(19,28);
				}
				else{
					tmpstr=linhas.Item(linhas.GetCount()-3);
					datafim=tmpstr.SubString(28,37);
				}
				char cdi[11],cdf[11];
				strcpy(cdi,dataini.ToAscii().data());
				strcpy(cdf,datafim.ToAscii().data());
				ret=1;_BemaGeraRegistrosTipoE("DOWNLOAD.MFD",fnameCotep1704,cdi,cdf,vilavielaframe->ecf.Nome_do_contribuinte,vilavielaframe->ecf.Endereco,"","2","","","","","","","","","","","","","");
				remove("DOWNLOAD.MFD");
				remove("espelho.txt");
				mespelho=0;
				_load_file_to_buf(fnameCotep1704,&mespelho);
				ptr=mespelho;
				linhas.Clear();
				lastptr=mespelho+strlen(mespelho)-1;						
				while((ptr=le_ate_fim_linha(ptr,linha))<lastptr){
					if(tipo==COTEPE1704_MF){
						if((strlen(linha)>0)&&(linha[1]=='0'||((linha[1]=='1')&&(linha[2]>='0')&&(linha[2]<='3'))))
							linhas.Add(wxString::From8BitData(linha));
					}
					else{
						if((strlen(linha)>0)&&((linha[1]=='0'&&(linha[2]=='1'||linha[2]=='2'))||((linha[1]=='1')&&(linha[2]>='4')&&(linha[2]<='9'))||(linha[1]=='2')))
							linhas.Add(wxString::From8BitData(linha));
					}
				}		
				if(mespelho)	free(mespelho);	
				FILE *fdef=fopen(fnameCotep1704,"w+b");
				for(unsigned int i=0;i<linhas.GetCount();i++){
					fprintf(fdef,"%s\x0d\x0a",linhas.Item(i).To8BitData().data());
				}
				fclose(fdef);						
			}
			FreeLibrary(hDLL);
		}
#else
		wxString cmd;
		if(BEMATECH_MFD)
		 cmd=_("./bemamfd ");
		else
			cmd=_("./bemamfd2 ");
		cmd.Append(fnameCotep1704);
		if(tipo==COTEPE1704_MF)
		 cmd.Append(" DOWNLOAD.MF 5 ");
		else
			cmd.Append(" DOWNLOAD.MFD 8 ");
		cmd.Append(COOi);
		cmd.Append(" ");

		cmd.Append(COOf);
		cmd.Append(" ");
		cmd.Append(vilavielaframe->ecf.Numero_do_usuario);
		ret=1;
		if (!wxShell(cmd)) {
			ret=0;
		}
#endif
	}	
	else if(SWEDA_TERMICA){
		ret=ECF_DownloadMF("DOWNLOAD.MF");
	}
	vilavielaframe->Analisa_iRetorno(ret);
	return ret;

}

int IMPRESSORA_FISCAL::_geracotepe1704_DATA( char *fnameCotep1704,char *dti,char *dtf,int tipo){
	//Bematech_FI_ArquivoMFD(fnameCotep1704,redi,redf,"C","1",0,"","",1);
 ASSERT_PRINTERON()
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
	int ret=0;
	if (BEMATECH_MATRICIAL||SWEDA_MATRICIAL) {
		ret=0;
	}
	else if (BEMATECH_MFD||BEMATECH_MFD2) {
		_DownloadMFD_DATA(dti,dtf);
		_DownloadMF();
#ifdef WIN32				
		HINSTANCE hDLL;              
		BemaGeraRegistrosTipoE _BemaGeraRegistrosTipoE=NULL; 
		if(BEMATECH_MFD)
		 hDLL = LoadLibrary(L"BemaMFD");
		else
			hDLL = LoadLibrary(L"BemaMFD2");
		if (hDLL != NULL){
			_BemaGeraRegistrosTipoE = (BemaGeraRegistrosTipoE)GetProcAddress(hDLL,"BemaGeraRegistrosTipoE");
			if (!_BemaGeraRegistrosTipoE){  
				FreeLibrary(hDLL);       
				return 0;
			}
			else{			
				char *mespelho=0,*ptr,linha[512],*lastptr;				
				wxArrayString linhas;			
				ret=1;_BemaGeraRegistrosTipoE("DOWNLOAD.MFD",fnameCotep1704,dti,dtf,vilavielaframe->ecf.Nome_do_contribuinte,vilavielaframe->ecf.Endereco,"","2","","","","","","","","","","","","","");
				remove("DOWNLOAD.MFD");				
				mespelho=0;
				_load_file_to_buf(fnameCotep1704,&mespelho);
				ptr=mespelho;
				linhas.Clear();
				lastptr=mespelho+strlen(mespelho)-1;						
				while((ptr=le_ate_fim_linha(ptr,linha))<lastptr){
					if(tipo==COTEPE1704_MF){
						if((strlen(linha)>0)&&(linha[1]=='0'||((linha[1]=='1')&&(linha[2]>='0')&&(linha[2]<='3'))))
							linhas.Add(wxString::From8BitData(linha));
					}
					else{
						if((strlen(linha)>0)&&((linha[1]=='0'&&(linha[2]=='1'||linha[2]=='2'))||((linha[1]=='1')&&(linha[2]>='4')&&(linha[2]<='9'))||(linha[1]=='2')))
							linhas.Add(wxString::From8BitData(linha));
					}
				}		
				if(mespelho)	free(mespelho);	
				FILE *fdef=fopen(fnameCotep1704,"w+b");
				for(unsigned int i=0;i<linhas.GetCount();i++){
					fprintf(fdef,"%s\x0d\x0a",linhas.Item(i).To8BitData().data());
				}
				fclose(fdef);						
			}
			FreeLibrary(hDLL);
		}
#else
		wxString cmd;
		if(BEMATECH_MFD)
		 cmd=_("./bemamfd ");
		else
			cmd=_("./bemamfd2 ");
		cmd.Append(fnameCotep1704);
		if(tipo==COTEPE1704_MF)
		 cmd.Append(" DOWNLOAD.MF 4 ");
		else
			cmd.Append(" DOWNLOAD.MFD 7 ");
		cmd.Append(dti);
		cmd.Append(" ");

		cmd.Append(dtf);
		cmd.Append(" ");
		cmd.Append(vilavielaframe->ecf.Numero_do_usuario);
		ret=1;
		if (!wxShell(cmd)) {
			ret=0;
		}
#endif
	}	
	else if(SWEDA_TERMICA){
		ret=ECF_DownloadMF("DOWNLOAD.MF");
	}
	vilavielaframe->Analisa_iRetorno(ret);
	return ret;

}

int IMPRESSORA_FISCAL::_DownloadMF(){
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	int ret=0;
	if (BEMATECH_MATRICIAL||SWEDA_MATRICIAL) {
		ret=0;
	}
	else if (BEMATECH_TERMICAS ||BEMATECH_MATRICIAL_MFD) {
		ret=Bematech_FI_DownloadMF("DOWNLOAD.MF");
	}
	else if(SWEDA_TERMICA){
		ret=ECF_DownloadMF("DOWNLOAD.MF");
	}
	vilavielaframe->Analisa_iRetorno(ret);
	return ret;
}

int  IMPRESSORA_FISCAL::_DownloadMFD_COO(char* COOInicial,char* COOFinal){
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	int ret=0;
	if (BEMATECH_MATRICIAL||SWEDA_MATRICIAL) {
		ret=0;
	}
	else if (BEMATECH_TERMICAS ||BEMATECH_MATRICIAL_MFD) {
		ret=Bematech_FI_DownloadMFD("DOWNLOAD.MFD","2",COOInicial,COOFinal,vilavielaframe->ecf.Numero_do_usuario);
	}
	else if(SWEDA_TERMICA){
		ret=ECF_DownloadMFD("DOWNLOAD.MFD","2",COOInicial,COOFinal,vilavielaframe->ecf.Numero_do_usuario);
	}
	vilavielaframe->Analisa_iRetorno(ret);
	return ret;
}

int  IMPRESSORA_FISCAL::_DownloadMFD_DATA(char* DataInicial,char* DataFinal){
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	int ret=0;
	if (BEMATECH_MATRICIAL||SWEDA_MATRICIAL) {
		ret=0;
	}
	else if (BEMATECH_TERMICAS ||BEMATECH_MATRICIAL_MFD) {
		ret=Bematech_FI_DownloadMFD("DOWNLOAD.MFD","1",DataInicial,DataFinal,vilavielaframe->ecf.Numero_do_usuario);
	}
	else if(SWEDA_TERMICA){
		ret=ECF_DownloadMFD("DOWNLOAD.MFD","1",DataInicial,DataFinal,vilavielaframe->ecf.Numero_do_usuario);
	}
	vilavielaframe->Analisa_iRetorno(ret);
	return ret;
}

int  IMPRESSORA_FISCAL::_FormatoDadosMFD_DATA(char *fdest,char* DataInicial,char* DataFinal){
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	int ret=0;
	if (BEMATECH_MATRICIAL||SWEDA_MATRICIAL) {
		ret=0;
	}
	else if (BEMATECH_TERMICAS ||BEMATECH_MATRICIAL_MFD) {
		ret=Bematech_FI_FormatoDadosMFD("DOWNLOAD.MFD",fdest,"0","1",DataInicial,DataFinal,vilavielaframe->ecf.Numero_do_usuario);
	}
	else if(SWEDA_TERMICA){
		ret=ECF_FormatoDadosMFD("DOWNLOAD.MFD",fdest,"0","1",DataInicial,DataFinal,vilavielaframe->ecf.Numero_do_usuario);
	}
	vilavielaframe->Analisa_iRetorno(ret);
	return ret;
}

int  IMPRESSORA_FISCAL::_FormatoDadosMFD_COO(char *fdest,char* COOi,char* COOf){
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	int ret=0;
	if (BEMATECH_MATRICIAL||SWEDA_MATRICIAL) {
		ret=0;
	}
	else if (BEMATECH_TERMICAS ||BEMATECH_MATRICIAL_MFD) {
		ret=Bematech_FI_FormatoDadosMFD("DOWNLOAD.MFD",fdest,"0","2",COOi,COOf,vilavielaframe->ecf.Numero_do_usuario);
	}
	else if(SWEDA_TERMICA){
		ret=ECF_FormatoDadosMFD("DOWNLOAD.MFD",fdest,"0","2",COOi,COOf,vilavielaframe->ecf.Numero_do_usuario);
	}
	vilavielaframe->Analisa_iRetorno(ret);
	return ret;
}



int IMPRESSORA_FISCAL::_DadosUltRedZ(char **buf,int *size,bool sintegra,char *datamovsintegra) {
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	int Retorno=0;
	*size=0;
	if (BEMATECH_MATRICIAL) {
		char nomearq[256];
		if (sintegra) {
			Retorno =Bematech_FI_DadosSintegra(datamovsintegra,datamovsintegra);
			strcpy(nomearq,"sintegra.txt");
		}
		else {
			Retorno = Bematech_FI_MapaResumo();
			strcpy(nomearq,"maparesumo.txt");
		}
		*size=_load_file_to_buf("retorno.txt",buf);
		FILE *tf=fopen(nomearq,"w+b");
		fwrite((void*)*buf,*size,1,tf);
		fclose(tf);
	}
	else
		if (BEMATECH_TERMICAS ||BEMATECH_MATRICIAL_MFD) {
			if (sintegra) {
				*size=1279;
				*buf=(char*)malloc(sizeof(char)*1279);
				Retorno = Bematech_FI_DadosUltimaReducaoMFD(*buf);
			}
			else {
				Retorno = Bematech_FI_MapaResumoMFD();
				*size=_load_file_to_buf("retorno.txt",buf);
				FILE *tf=fopen("maparesumomfd.txt","w+b");
				fwrite((void*)*buf,*size,1,tf);
				fclose(tf);
			}
		}
	vilavielaframe->Analisa_iRetorno(Retorno);
	return Retorno;
}

bool IMPRESSORA_FISCAL::testa_impressora() {
//	MODOTESTE() true;
	int ret=0;
	if (BEMATECH_TODOSOSMODELOS)
		ret=Bematech_FI_VerificaImpressoraLigada();
	else
		if (SWEDA_TODOSOSMODELOS)
			ret=ECF_VerificaImpressoraLigada();
	//vilavielaframe->Analisa_iRetorno(ret);

	return (ret==1);
}

bool  IMPRESSORA_FISCAL::_retornasDadoUltRedZ(char *bufdados,int size,int DADOARETORNAR,char *bufret,ListTotalizadorParcial2 *lsttot) {
	MODOTESTE() true;
 NENHUMRELATORIO() true;
 ASSERT_PRINTERON()
	char *ptr;
	{
		switch (DADOARETORNAR) {
		case REDZ_CRZ:

			ptr=le_ate_car(bufdados,':',size);
			if (ptr) {
				ptr=le_enquanto_car(ptr,' ',size-(ptr-bufdados));
				le_ate_fim_linha(ptr,bufret);
				return true;
			}

			break;
		case REDZ_COO:
			ptr=le_ate_fim_linha(bufdados,0);
			if (ptr) {
				ptr=le_ate_car(ptr,':',size-(ptr-bufdados));
				if (ptr) {
					ptr=le_enquanto_car(ptr,' ',size-(ptr-bufdados));
					le_ate_fim_linha(ptr,bufret);
					return true;
				}
			}
			break;
		case REDZ_TOTALBRUTO:
			ptr=le_ate_fim_linha(bufdados,0);
			if (ptr) {
				ptr=le_ate_fim_linha(ptr,0);
				ptr=le_ate_car(ptr,':',size-(ptr-bufdados));
				if (ptr) {
					ptr=le_enquanto_car(ptr,' ',size-(ptr-bufdados));
					le_ate_fim_linha(ptr,bufret);
					RELATORIOS::utils::removechar(bufret,',');
					RELATORIOS::utils::removechar(bufret,'.');
					return true;
				}
			}
			break;
		case REDZ_TOTALIZADORES_PARCIAIS: {
				int nskip=0;
				nskip=4;
				ptr=le_ate_fim_linha(bufdados,0,nskip);
				if (ptr) {
					char tot[128],abrev[8],*ptrtot;
					int ntot=1;
					do {
						//sscanf(ptr,"%s",tot);
						ptrtot=tot;
						ptr=le_enquanto_car(ptr,0x0d,size-(ptr-bufdados));
						ptr=le_enquanto_car(ptr,0x0a,size-(ptr-bufdados));

						do {
							*ptrtot=*ptr;
							if (!*ptr)
								break;
							ptr++;
							ptrtot++;
						}
						while (*ptr!='.'&&*ptr!=':');
						*ptrtot=0;

						if (*tot&&*tot!=0x0d&&*tot!=0x0a&&(strcmp(tot,"0000")!=0)) {

							printf("totalizador=%s\n",tot);
							if (strcmp(tot,Isencao)==0||strcmp(tot,Isencao_de_ICMS)==0)
								strcpy(abrev,"I1");
							else
								if (strcmp(tot,Nao_Incidencia)==0||strcmp(tot,Nao_Incidencia_de_ICMS)==0)
									strcpy(abrev,"N1");
								else
									if (strcmp(tot,Substituicao_Tributaria)==0||strcmp(tot,Substituicao_Tributaria_de_ICMS)==0)
										strcpy(abrev,"F1");
									else
										if (strcmp(tot,Substituicao_Tributaria_de_ICSSQN)==0)
											strcpy(abrev,"FS1");
										else
											if (strcmp(tot,Isencao_de_ISSQN)==0)
												strcpy(abrev,"IS1");
											else
												if (strcmp(tot,Nao_Incidencia_de_ISSQN)==0)
													strcpy(abrev,"NS1");
												else
													if (strcmp(tot,"Cancelamentos")==0||strcmp(tot,"Cancelamentos de ICMS")==0)
														strcpy(abrev,"Can-T");
													else
														if (strcmp(tot,Acrescimos)==0||strcmp(tot,Acrescimos_de_ICMS)==0)
															strcpy(abrev,"AT");
														else
															if (strcmp(tot,"Descontos")==0||strcmp(tot,"Descontos de ICMS")==0)
																strcpy(abrev,"DT");
															else
																if (strcmp(tot,"Cancelamentos de ISSQN")==0)
																	strcpy(abrev,"Can-S");
																else
																	if (strcmp(tot,Acrescimos_de_ISSQN)==0)
																		strcpy(abrev,"AS");
																	else
																		if (strcmp(tot,"Descontos de ISSQN")==0)
																			strcpy(abrev,"DS");
																		else
																			if (strcmp(tot,"ISS")==0) {
																				strcpy(abrev,"01S0000");
																			}
																			else {
																				sprintf(abrev,"%02dT%s",ntot++,tot);//printf("abrev=%s,tot=%s\n",abrev,tot);
																			}
							ptr=le_enquanto_car(ptr,'.',size-(ptr-bufdados));
							ptr=le_enquanto_car(ptr,':',size-(ptr-bufdados));
							ptr=le_enquanto_car(ptr,' ',size-(ptr-bufdados));

							ptr=le_ate_fim_linha(ptr,bufret);
							RELATORIOS::utils::removechar(bufret,',');
							RELATORIOS::utils::removechar(bufret,'.');
							if (atoi(bufret)!=0) {
								lsttot->novo(atoi(bufret),abrev);
								//printf("abrev=%s,bufret=%s\n",abrev,bufret);
							}
						}
						else
							break;
					}
					while (1);
					//printf("abrev=%s\n",abrev);
				}
				return true;
			}
			break;
		case REDZ_CRO: {
				int index,ncar;
				if (BEMATECH_MATRICIAL||SWEDA_MATRICIAL) {
					index=37;
					ncar=6;
				}
				else {
					index=3;
					ncar=4;
				}
				char *ptrc=bufdados+index;
				int i;
				for (i=0;i<ncar;i++,ptrc++)
					bufret[i]=*ptrc;
				bufret[i]=0;
			}
			break;
		}
	}
	return false;
}

bool IMPRESSORA_FISCAL::_DataMovUltRedZ(char *Data_do_movimento) {
	MODOTESTE() true;
 NENHUMRELATORIO() true;
 ASSERT_PRINTERON()
	char DadosReducao[1279];
	int Retorno,index=0;
	if (BEMATECH_MATRICIAL) {
		Retorno = Bematech_FI_DadosUltimaReducao(DadosReducao);
		if (Retorno==1) {
			FILE *tf=fopen("reddm.txt","w+b");
			fwrite((void*)DadosReducao,631,1,tf);
			fclose(tf);
			index=595;
		}
	}
	else
		if (BEMATECH_TERMICAS ||BEMATECH_MATRICIAL_MFD) {
			Retorno = Bematech_FI_DadosUltimaReducaoMFD(DadosReducao);
			index=248;
			FILE *tf=fopen("Bematech_FI_DadosUltimaReducaoMFD.txt","w+b");
			fwrite((void*)DadosReducao,1278,1,tf);
			fclose(tf);
		}
		else
			if (SWEDA_MATRICIAL) {
				Retorno = ECF_DadosUltimaReducao(DadosReducao);
				if (Retorno==1) {
					FILE *tf=fopen("reddm.txt","w+b");
					fwrite((void*)DadosReducao,631,1,tf);
					fclose(tf);
					index=595;
				}
			}
			else
				if (SWEDA_TERMICA) {
					Retorno = ECF_DadosUltimaReducaoMFD(DadosReducao);
					index=248;
					FILE *tf=fopen("Bematech_FI_DadosUltimaReducaoMFD.txt","w+b");
					fwrite((void*)DadosReducao,1278,1,tf);
					fclose(tf);
				}
	vilavielaframe->Analisa_iRetorno(Retorno);
	if (Retorno==1) {
		char *ptrc=DadosReducao+index;
		int i;
		for (i=0;i<6;i++,ptrc++)
			Data_do_movimento[i]=*ptrc;
		Data_do_movimento[i]=0;
		return true;
	}
	return false;
}

int IMPRESSORA_FISCAL::_DHUsuario_DHSB_MFAdicional(char dataUsuario[21],char dataSWBasico[21],char horaUsuario[21],char horaSWBasico[21],char *MFAdicional) {
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	int ret=0;
	if (BEMATECH_MATRICIAL) {
		*dataUsuario=0;
		*dataSWBasico=0;
		strcpy(MFAdicional," ");
		ret=1;
		*horaUsuario=*horaSWBasico=0;
	}
	else
		if (BEMATECH_TERMICAS ||BEMATECH_MATRICIAL_MFD) {
			//ret= Bematech_FI_DataHoraGravacaoUsuarioSWBasicoMFAdicional(ecf.dataUsuario, ecf.dataSWBasico, MFAdicional);
			*dataUsuario=0;
			*dataSWBasico=0;
			strcpy(MFAdicional," ");
			ret=1;
			*horaUsuario=*horaSWBasico=0;
		}
		else
			if (SWEDA_TODOSOSMODELOS) {
				*dataUsuario=0;
				*dataSWBasico=0;
				strcpy(MFAdicional," ");
				ret=1;
				*horaUsuario=*horaSWBasico=0;
				//ret= ECF_DataHoraGravacaoUsuarioSWBasicoMFAdicional(ecf.dataUsuario, ecf.dataSWBasico, MFAdicional);
			}
	vilavielaframe->Analisa_iRetorno(ret);
	return ret;
}

int IMPRESSORA_FISCAL::_VersaoDll(char *versaodll) {
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	int ret=0;
	if (BEMATECH_TODOSOSMODELOS){
#ifdef WIN32
		ret= Bematech_FI_VersaoDll(versaodll);
#else
		ret= 1;
		strcpy(versaodll,"0.2.6");
#endif
	}
	else
		if (SWEDA_TODOSOSMODELOS)
			ret=ECF_VersaoDll(versaodll);
	vilavielaframe->Analisa_iRetorno(ret);
	return ret;
};

int IMPRESSORA_FISCAL::_dataehoraEmissaoRZ(char *Data_de_emissao,char *Hora_de_emissao) {
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	int ret=0;
	if (BEMATECH_TODOSOSMODELOS)
		ret= Bematech_FI_DataHoraReducao(Data_de_emissao, Hora_de_emissao);
	else
		if (SWEDA_TODOSOSMODELOS)
			ret=ECF_DataHoraReducao(Data_de_emissao, Hora_de_emissao);
	vilavielaframe->Analisa_iRetorno(ret);
	return ret;
}

int IMPRESSORA_FISCAL::_ContadorCupomFiscal(bool incidr04,char *sCupom) {
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	if (BEMATECH_MATRICIAL) {
		Palavra query;
		sql_ResultSet *res;
		query="SELECT MAX(idr04) FROM r04";
		if ((res=vilavielaframe->_execquerywithresult(query))!=NULL&&vilavielaframe->_nextrow(res)) {
			int ccf=incidr04?1:0;
			ccf+=vilavielaframe->_getint(res,1);
			sprintf(sCupom,"%d",ccf);
			vilavielaframe->_deleteresult(&res);
		}
		else
			strcpy(sCupom,"1");
		return 1;
	}
	else
		if (BEMATECH_TERMICAS ||BEMATECH_MATRICIAL_MFD) {
			return Bematech_FI_ContadorCupomFiscalMFD(sCupom);
		}
		else
			if (SWEDA_TODOSOSMODELOS)
				return ECF_ContadorCupomFiscalMFD(sCupom) ;
	return 0;
}

int IMPRESSORA_FISCAL::_NumeroCupom(char *NumeroCupom) {
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	if (BEMATECH_TODOSOSMODELOS)
		return Bematech_FI_NumeroCupom(NumeroCupom);
	else
		if (SWEDA_TODOSOSMODELOS)
			return ECF_NumeroCupom(NumeroCupom);
	return 0;
}

int IMPRESSORA_FISCAL::_DataHoraImpressora(char *Data,char *Hora) {
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	if (BEMATECH_TODOSOSMODELOS)
		return Bematech_FI_DataHoraImpressora(Data, Hora);
	else
		if (SWEDA_TODOSOSMODELOS)
			return  ECF_DataHoraImpressora(Data, Hora);
	return 0;
}

int IMPRESSORA_FISCAL::_SubTotal(char *SubTotal) {
	//MODOTESTE() 1;
 ASSERT_PRINTERON()
	if (BEMATECH_TODOSOSMODELOS)
		return Bematech_FI_SubTotal(SubTotal);
	else
		if (SWEDA_TODOSOSMODELOS)
			return  ECF_SubTotal(SubTotal);
	return 0;
}

int IMPRESSORA_FISCAL::_UltimoItemVendido(char *UltimoItem) {
	//MODOTESTE() 1;
 ASSERT_PRINTERON()
	if (BEMATECH_TODOSOSMODELOS)
		return Bematech_FI_UltimoItemVendido(UltimoItem);
	else
		if (SWEDA_TODOSOSMODELOS)
			return  ECF_UltimoItemVendido(UltimoItem);
	return 0;
}

int IMPRESSORA_FISCAL::_VerificaTruncamento(char *IAT) {
	//MODOTESTE() 1;
	int retimp;
 ASSERT_PRINTERON()
	if (BEMATECH_TODOSOSMODELOS)
		retimp= Bematech_FI_VerificaTruncamento(IAT);
	else
		if (SWEDA_TODOSOSMODELOS)
			retimp=  ECF_VerificaTruncamento(IAT);
	if (*IAT=='1')
		*IAT='T';
	else
		*IAT='A';
	return retimp;
}

int IMPRESSORA_FISCAL::_ContadorOperacoesNaoFiscal(char *nop) {
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	if (BEMATECH_TODOSOSMODELOS)
		return Bematech_FI_NumeroOperacoesNaoFiscais(nop);
	else
		if (SWEDA_TODOSOSMODELOS)
			return  ECF_NumeroOperacoesNaoFiscais(nop);
	return 0;
}

int IMPRESSORA_FISCAL::_Contador_GRG(char *CRG,bool update) {
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	if (BEMATECH_MATRICIAL) {
		Palavra query;
		sql_ResultSet *res;
		query="SELECT * FROM CRG";
		if ((res=vilavielaframe->_execquerywithresult(query))!=NULL&&vilavielaframe->_nextrow(res)) {
			sprintf(CRG,"%d",vilavielaframe->_getint(res,1));
			vilavielaframe->_deleteresult(&res);
			query="UPDATE CRG SET quant = quant + 1";
		}
		else
			query="INSERT INTO CRG(quant) VALUE(1)";
		if (update)
			vilavielaframe->_execquery(query);
		return 1;
	}
	else
		if (BEMATECH_MATRICIAL_MFD||BEMATECH_TERMICAS)
			return Bematech_FI_ContadorRelatoriosGerenciaisMFD(CRG);
		else
			if (SWEDA_TODOSOSMODELOS)
				return  ECF_ContadorRelatoriosGerenciaisMFD(CRG);
	return 0;
}

int IMPRESSORA_FISCAL::_Contador_de_CDC(char *CDC,bool update) {
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	if (BEMATECH_MATRICIAL) {
		Palavra query;
		sql_ResultSet *res;
		query="SELECT * FROM CDC";
		if ((res=vilavielaframe->_execquerywithresult(query))!=NULL&&vilavielaframe->_nextrow(res)) {
			sprintf(CDC,"%d",vilavielaframe->_getint(res,1));
			vilavielaframe->_deleteresult(&res);
			query="UPDATE CDC SET quant = quant + 1";
		}
		else
			query="INSERT INTO CDC(quant) VALUE(1)";
		if (update)
			vilavielaframe->_execquery(query);
		return 1;
	}
	else
		if (BEMATECH_MATRICIAL_MFD||BEMATECH_TERMICAS)
			return Bematech_FI_ContadorComprovantesCreditoMFD(CDC);
		else
			if (SWEDA_TODOSOSMODELOS)
				return  ECF_ContadorComprovantesCreditoMFD(CDC);
	return 0;
}

int IMPRESSORA_FISCAL::_DataHoraUltimoMovimento(char *Data,char *Hora) {
	//MODOTESTE() 1;
 ASSERT_PRINTERON()
	int ret= 	_DataHoraImpressora(Data,Hora);
	sprintf(Data,"%8ld",formatdata(Data));
	removechar(Hora,':');
	return ret;
}

int IMPRESSORA_FISCAL::_NumeroCaixa(char *NumeroCaixa) {
	//MODOTESTE() 1;
 ASSERT_PRINTERON()
	if (BEMATECH_TODOSOSMODELOS)
		return Bematech_FI_NumeroCaixa(NumeroCaixa);
	else
		if (SWEDA_TODOSOSMODELOS)
			return  ECF_NumeroCaixa(NumeroCaixa);
	return 0;
}

int IMPRESSORA_FISCAL::_GrandeTotal(char *GT) {
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	int ret=0;
	if (BEMATECH_TODOSOSMODELOS)
		ret= Bematech_FI_GrandeTotal(GT);
	else
		if (SWEDA_TODOSOSMODELOS)
			ret=  ECF_GrandeTotal(GT);
	vilavielaframe->Analisa_iRetorno(ret);
	return ret;
}

int IMPRESSORA_FISCAL::_NumeroIntervencoes(char *numintervencoes) {
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	int ret=0;
	if (BEMATECH_TODOSOSMODELOS)
		ret= Bematech_FI_NumeroIntervencoes(numintervencoes);
	else
		if (SWEDA_TODOSOSMODELOS)
			ret=  ECF_NumeroIntervencoes(numintervencoes);
	vilavielaframe->Analisa_iRetorno(ret);
	return ret;
}

int IMPRESSORA_FISCAL::_ReducaoZ(char *data,char *hora) {
	MODOTESTE() 1;
 //NENHUMRELATORIO() 1;
	int ret=0;
 ASSERT_PRINTERON()
	if (BEMATECH_TODOSOSMODELOS)
		ret= Bematech_FI_ReducaoZ(data,hora);
	else
		if (SWEDA_TODOSOSMODELOS)
			ret=  ECF_ReducaoZ(data,hora);
	vilavielaframe->Analisa_iRetorno(ret);
	return ret;
}

int IMPRESSORA_FISCAL::_RetornoImpressora(int *_ACK,int *ST1,int *ST2) {
	//MODOTESTE() 1;
	int ret=0;
 ASSERT_PRINTERON()
	if (BEMATECH_TODOSOSMODELOS)
		ret= Bematech_FI_RetornoImpressora(_ACK,ST1,ST2);
	else
		if (SWEDA_TODOSOSMODELOS)
			ret=  ECF_RetornoImpressora(_ACK,ST1,ST2);
	vilavielaframe->Analisa_iRetorno(ret);
	return ret;
}

int IMPRESSORA_FISCAL::_VerificaEstadoImpressora(int *_ACK,int *ST1,int *ST2) {
	//MODOTESTE() 1;
	int ret=0;
 ASSERT_PRINTERON()
	if (BEMATECH_TODOSOSMODELOS)
		ret= Bematech_FI_VerificaEstadoImpressora(_ACK,ST1,ST2);
	else
		if (SWEDA_TODOSOSMODELOS)
			ret=  ECF_VerificaEstadoImpressora(_ACK,ST1,ST2);
	vilavielaframe->Analisa_iRetorno(ret);
	return ret;
}

bool IMPRESSORA_FISCAL::_cupomaberto() {
	int _ACK=0,ST1=0,ST2=0;
	int ret;
 ASSERT_PRINTERON()
	ret=_VerificaEstadoImpressora(&_ACK,&ST1,&ST2);
	if (ret==1) {
		if (ST1&0x02)
			return true;
	}
	return false;
}

int IMPRESSORA_FISCAL::_LeituraX() {
	MODOTESTE() 1;
 //NENHUMRELATORIO() 1;
	int ret=0;
 ASSERT_PRINTERON()
	if (BEMATECH_TODOSOSMODELOS)
		ret= Bematech_FI_LeituraX();
	else
		if (SWEDA_TODOSOSMODELOS)
			ret=  ECF_LeituraX();
	vilavielaframe->Analisa_iRetorno(ret);
	return ret;
}

int IMPRESSORA_FISCAL::_LeituraXSerial() {
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	int ret=0;
	if (BEMATECH_TODOSOSMODELOS)
		ret= Bematech_FI_LeituraXSerial();
	else
		if (SWEDA_TODOSOSMODELOS)
			ret=  ECF_LeituraXSerial();
	vilavielaframe->Analisa_iRetorno(ret);
	return ret;
}

int IMPRESSORA_FISCAL::_FechamentoDoDia() {
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	int ret=0;
	if (BEMATECH_TODOSOSMODELOS)
		ret= Bematech_FI_FechamentoDoDia();
	else
		if (SWEDA_TODOSOSMODELOS)
			ret=  ECF_FechamentoDoDia();
	vilavielaframe->Analisa_iRetorno(ret);
	return ret;
}

int IMPRESSORA_FISCAL::_AberturaDoDia(char *valor,char *fpagto) {
	//MODOTESTE() 1;
	int ret=0;
 ASSERT_PRINTERON()
	if (BEMATECH_TODOSOSMODELOS)
		ret= Bematech_FI_AberturaDoDia(valor,fpagto);
	else
		if (SWEDA_TODOSOSMODELOS)
			ret=  ECF_AberturaDoDia(valor,fpagto);
	vilavielaframe->Analisa_iRetorno(ret);
	return ret;
}

int IMPRESSORA_FISCAL::_NumeroReducoes(char *numreducoes) {
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	int ret=0;
	if (BEMATECH_TODOSOSMODELOS)
		ret= Bematech_FI_NumeroReducoes(numreducoes);
	else
		if (SWEDA_TODOSOSMODELOS)
			ret=  ECF_NumeroReducoes(numreducoes);
	vilavielaframe->Analisa_iRetorno(ret);
	return ret;
}

int IMPRESSORA_FISCAL::_end_contribuinte(char *endcontribuinte) {
	//MODOTESTE() 1;
	char clicheprop[512];
	int ret=0;
 ASSERT_PRINTERON()
	if (BEMATECH_TODOSOSMODELOS)
		ret= Bematech_FI_ClicheProprietario(clicheprop);
	else
		if (SWEDA_TODOSOSMODELOS)
			ret=  ECF_ClicheProprietario(clicheprop);
	vilavielaframe->Analisa_iRetorno(ret);
	if (ret==1) {
		char *pchar=clicheprop,*plchar=pchar+strlen(clicheprop),*pend=endcontribuinte;
		for (;pchar<plchar;pchar++) {
			if (*pchar==0x0a) {
				*pchar=0;
				pchar++;
				break;
			}
		}
		for (;pchar<plchar;pchar++) {
			if (*pchar==0x0a) {
				pchar++;
				break;
			}
		}
		for (;pchar<plchar;pchar++,pend++) {
			if (*pchar==0x0a) {
				*pend=0;
				break;
			}
			*pend=*pchar;
		}
		endcontribuinte[120]=0;
		pchar=clicheprop;
		while (*pchar==' ')
			pchar++;
		*(pchar+40)=0;
	}
	return ret;
}

int IMPRESSORA_FISCAL::_nome_contribuinte(char *nomecontribuite) {
	//MODOTESTE() 1;
 ASSERT_PRINTERON()
	char clicheprop[512];
	int ret=0;
	if (BEMATECH_TODOSOSMODELOS)
		ret= Bematech_FI_ClicheProprietario(clicheprop);
	else
		if (SWEDA_TODOSOSMODELOS)
			ret=  ECF_ClicheProprietario(clicheprop);
	vilavielaframe->Analisa_iRetorno(ret);
	if (ret==1) {
		char *pchar=clicheprop,*plchar=pchar+strlen(clicheprop);
		for (;pchar<plchar;pchar++) {
			if (*pchar==0x0a) {
				*pchar=0;
				pchar++;
				break;
			}
		}		
		pchar=clicheprop;
		while (*pchar==' ')
			pchar++;
		*(pchar+40)=0;
		strcpy(nomecontribuite,pchar);
	}
	return ret;
}

int IMPRESSORA_FISCAL::_VersaoSB(char *vSB) {
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	int ret=0;
	if (BEMATECH_MATRICIAL) {
		ret= Bematech_FI_VersaoFirmware(vSB);
	}
	else
		if (BEMATECH_MATRICIAL_MFD||BEMATECH_TERMICAS) {
			ret= Bematech_FI_VersaoFirmwareMFD(vSB);
		}
		else
			if (SWEDA_MATRICIAL) {
				ret=  ECF_VersaoFirmware(vSB);
			}
			else
				if (SWEDA_TERMICA) {
					ret=  ECF_VersaoFirmwareMFD(vSB);
				}
	vilavielaframe->Analisa_iRetorno(ret);
	return ret;
}

int IMPRESSORA_FISCAL::_CGC_IE(char *CNPJUSUARIO,char *IEUSUARIO) {
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	int ret=0;
	bool analisa=false;
	if (BEMATECH_MATRICIAL) {
		ret= Bematech_FI_CGC_IE(CNPJUSUARIO,IEUSUARIO);
		analisa=true;
	}
	else
		if (BEMATECH_MATRICIAL_MFD||BEMATECH_TERMICAS) {
			ret=Bematech_FI_CNPJMFD(CNPJUSUARIO);
			ret=Bematech_FI_InscricaoEstadualMFD(IEUSUARIO);
		}
		else
			if (SWEDA_MATRICIAL) {
				ret=  ECF_CGC_IE(CNPJUSUARIO,IEUSUARIO);
				analisa=true;
			}
			else
				if (SWEDA_TERMICA) {
					ret=ECF_CNPJMFD(CNPJUSUARIO);
					ret=ECF_InscricaoEstadualMFD(IEUSUARIO);
				}
	vilavielaframe->Analisa_iRetorno(ret);
	if (analisa)
		if (*IEUSUARIO==0||*IEUSUARIO==' ') {
			strncpy(IEUSUARIO,CNPJUSUARIO+18,12);
		}
	removechar(IEUSUARIO,'.');
	removechar(IEUSUARIO,'-');
	CNPJUSUARIO[18]=0;
	removechar(CNPJUSUARIO,'.');
	removechar(CNPJUSUARIO,'/');
	removechar(CNPJUSUARIO,'-');
	vilavielaframe->Analisa_iRetorno(ret);
	return ret;
}

int IMPRESSORA_FISCAL::_atualiza_dados_impressora(bool incidr04,bool atualizaCCFeCOO) {
	MODOTESTE() 1;
 NENHUMRELATORIO() 1;
 ASSERT_PRINTERON()
	char Numero_de_fabricacaoant[20];
	INIT_PROGRESS_INFO("dados impressora","atualizando dados impressora",8,vilavielaframe);
	strcpy(Numero_de_fabricacaoant,vilavielaframe->ecf.Numero_de_fabricacao);
	UPDATE_PROGRESS2(1,"verificando número de série");
	_NumSerieImpressora(vilavielaframe->ecf.Numero_de_fabricacao);

	if ((!vilavielaframe->dados_imp_fiscal_ok)||(strcmp(Numero_de_fabricacaoant,vilavielaframe->ecf.Numero_de_fabricacao)!=0)) {
		UPDATE_PROGRESS2(2,"obtendo modelo");
		_MarcaModeloTipoImpressora(vilavielaframe->ecf.Marca_ECF,vilavielaframe->ecf.Modelo_do_ECF,vilavielaframe->ecf.tipo_ECF);
		_NumeroCaixa(vilavielaframe->ecf.NumeroCaixa);
		UPDATE_PROGRESS2(3,"obtendo MF adicional");
		_DHUsuario_DHSB_MFAdicional(vilavielaframe->ecf.dataUsuario,vilavielaframe->ecf.dataSWBasico,vilavielaframe->ecf.horaUsuario,vilavielaframe->ecf.horaSWBasico,vilavielaframe->ecf.MF_adicional);
		UPDATE_PROGRESS2(4,"obtendo número do usuário");
		_NumSubstituicoes(vilavielaframe->ecf.Numero_do_usuario);
		_VersaoSB(vilavielaframe->ecf.versao_SB);
		UPDATE_PROGRESS2(5,"obtendo tipo arredondamento");
		_VerificaTruncamento(vilavielaframe->ecf.IAT);
		vilavielaframe->dados_imp_fiscal_ok=true;
	}
	if (atualizaCCFeCOO) {
		UPDATE_PROGRESS2(6,"obtendo ecf.CCF");
		_ContadorCupomFiscal(incidr04,vilavielaframe->ecf.CCF);
		UPDATE_PROGRESS2(7,"obtendo COO");
		_NumeroCupom(vilavielaframe->ecf.COO);
	}
	_VersaoDll(vilavielaframe->ecf.Versao_da_biblioteca);
	_VersaoSB(vilavielaframe->ecf.versao_SB);
	_nome_contribuinte(vilavielaframe->ecf.Nome_do_contribuinte);
	_end_contribuinte(vilavielaframe->ecf.Endereco);
	_NumSubstituicoes(vilavielaframe->ecf.NoSubstProp);
	_CGC_IE(vilavielaframe->ecf.CNPJUSUARIO,vilavielaframe->ecf.IEUSUARIO);
	UPDATE_PROGRESS2(8,"concluido");
	return 1;
}


int IMPRESSORA_FISCAL::_abre_cupom(char *cgc,char *nome,char *end) {
	//MODOTESTE() 1;
 ASSERT_PRINTERON()
	int retimp=0;
	if (BEMATECH_MATRICIAL)
		retimp= Bematech_FI_AbreCupom(cgc);
	else
		if (BEMATECH_MATRICIAL_MFD||BEMATECH_TERMICAS)
			retimp= Bematech_FI_AbreCupomMFD(cgc,nome,end);
		else
			if (SWEDA_MATRICIAL)
				retimp= ECF_AbreCupom(cgc);
			else
				if (SWEDA_TERMICA)
					retimp= ECF_AbreCupomMFD(cgc,nome,end);
	if (retimp==1)
		vilavielaframe->pode_cancelar_cupom=true;
	_atualiza_dados_impressora();
	vilavielaframe->Analisa_iRetorno(retimp);
	return retimp;
}

int IMPRESSORA_FISCAL::_CancelaItem(char *item) {
	//MODOTESTE() 1;
	int retimp=0;
 ASSERT_PRINTERON()
	if (BEMATECH_TODOSOSMODELOS)
		retimp=Bematech_FI_CancelaItemGenerico(item);
	else
		if (SWEDA_TODOSOSMODELOS)
			retimp=ECF_CancelaItemGenerico(item);
	vilavielaframe->Analisa_iRetorno(retimp);
	return retimp;
}

int IMPRESSORA_FISCAL::_cancela_cupom(char* Meio_de_pagamento,char *cgc,char *nome,char *end,bool criaR06) {
	//MODOTESTE() 1;
	int retimp=0;
 ASSERT_PRINTERON()
	if (BEMATECH_MATRICIAL)
		retimp= Bematech_FI_CancelaCupom();
	else
		if (BEMATECH_MATRICIAL_MFD||BEMATECH_TERMICAS)
			retimp= Bematech_FI_CancelaCupomMFD(cgc,nome,end);
		else
			if (SWEDA_MATRICIAL)
				retimp= ECF_CancelaCupom();
			else
				if (SWEDA_TERMICA)
					retimp= ECF_CancelaCupomMFD(cgc,nome,end);
	if (retimp==1) {
		vilavielaframe->pode_cancelar_cupom=false;
		registro_R04(Meio_de_pagamento,nome,cgc,true,criaR06);
	}
	vilavielaframe->Analisa_iRetorno(retimp);
	return retimp;
}

int IMPRESSORA_FISCAL::_cancela_cupom() {
	//
	int ret=0;
 ASSERT_PRINTERON()
	if (BEMATECH_TODOSOSMODELOS)
		ret= Bematech_FI_CancelaCupom();
	else
		if (SWEDA_TODOSOSMODELOS)
			ret= ECF_CancelaCupom();
 NENHUMRELATORIO() ret;
	if (ret==1)
		_atualiza_items_cupom_cancelado();
	return ret;
}

 int IMPRESSORA_FISCAL::_RelatorioGerencial(char *text){
  int ret=0;
  ASSERT_PRINTERON()
	if (BEMATECH_TODOSOSMODELOS)
		ret= Bematech_FI_RelatorioGerencial(text);
	else
		if (SWEDA_TODOSOSMODELOS)
			ret= ECF_RelatorioGerencial(text);

	return ret;
 }

 int IMPRESSORA_FISCAL::_FechaRelatorioGerencial(){
   int ret=0;
   ASSERT_PRINTERON()
	if (BEMATECH_TODOSOSMODELOS)
		ret= Bematech_FI_FechaRelatorioGerencial();
	else
		if (SWEDA_TODOSOSMODELOS)
			ret= ECF_FechaRelatorioGerencial();

	return ret;
 }

int IMPRESSORA_FISCAL::_FechaCupom(char *cFormaPgto,bool desconto_percentual,char* cValorAcresDesc,char *cValorPago) {
	//MODOTESTE() 1;
 ASSERT_PRINTERON()
	char cAcresDesc[2]="D",cTipoAcresDesc[2]="";
	char cMsgPromocional[64]="MD5:",tmpsg[64]="";
	int ret=0;
	char *bd;
	int sz=descriptografa_arquivo("arquivo_auxiliare.txt",&bd);
	atualiza_arquivo_auxiliar("MD5",bd,sz,NULL,tmpsg,false,true);
	strcat(cMsgPromocional,tmpsg);
	criptografa_buf("arquivo_auxiliare.txt",bd);
	delete []bd;
	if (desconto_percentual)
		*cTipoAcresDesc='%';
	else
		*cTipoAcresDesc='$';
	if (BEMATECH_TODOSOSMODELOS)
		ret= 	Bematech_FI_FechaCupom(cFormaPgto,cAcresDesc,cTipoAcresDesc,cValorAcresDesc,cValorPago,cMsgPromocional);
	else
		if (SWEDA_TODOSOSMODELOS)
			ret= ECF_FechaCupom(cFormaPgto, cAcresDesc, cTipoAcresDesc,cValorAcresDesc, cValorPago, cMsgPromocional);
	vilavielaframe->Analisa_iRetorno(ret);
	return ret;
}

int IMPRESSORA_FISCAL::_VendeItem(char *cCodigo,char *cDescricao ,char *cAliquota,char *cTipoQtde ,char *cValor ,char *cQtde ,char *cUnidade) {
//	MODOTESTE() 1;
 ASSERT_PRINTERON()
	char cTipoDesconto[]="%",cValorDesc[]="0000";
	short iCasasDecimais=2;
	wxString tmpstr=wxString::FromAscii(cQtde);
	char Valor_total_liquido[16],Casas_decimais_da_quantidade[16]="0";
	double fracquant,dquant,vunit=atof(cValor)*100;
	tmpstr.ToDouble(&dquant);
	fracquant=dquant-floor(dquant);
	sprintf(cValor,"%d",(int)vunit);
	if (fracquant==0.0) {
		strcpy(cTipoQtde,"I");
		sprintf(cQtde,"%d",(int)dquant);
	}
	else {
		strcpy(cTipoQtde,"F");
		*Casas_decimais_da_quantidade='3';
		int iquant=(int)(dquant*1000.0);
		sprintf(cQtde,"%g",dquant*1000.0);//printf("%s dquant=%f iquant=%d\n",cQtde,dquant,iquant);
	}
	if (*cAliquota==0)
		strcpy(cAliquota,"II");
	if (!*cCodigo)
		strcpy(cCodigo,"00000");

	int retimp=0;
	if (BEMATECH_TODOSOSMODELOS) {
		Bematech_FI_UsaUnidadeMedida(cUnidade);
		retimp= Bematech_FI_VendeItem(cCodigo ,cDescricao ,cAliquota ,cTipoQtde ,cQtde ,iCasasDecimais,cValor ,cTipoDesconto ,cValorDesc);
	}
	else
		if (SWEDA_TODOSOSMODELOS) {
			ECF_UsaUnidadeMedida(cUnidade);
			retimp= ECF_VendeItem(cCodigo ,cDescricao ,cAliquota ,cTipoQtde ,cQtde ,iCasasDecimais,cValor ,cTipoDesconto ,cValorDesc);
		}
	sprintf(Valor_total_liquido,"%.2f",vunit*dquant);
 NENHUMRELATORIO() retimp;
	registro_R05(vilavielaframe->ecf.Numero_de_fabricacao,vilavielaframe->ecf.MF_adicional,vilavielaframe->ecf.Modelo_do_ECF,vilavielaframe->ecf.Numero_do_usuario,
	             vilavielaframe->ecf.CCF,vilavielaframe->ecf.COO,vilavielaframe->ecf.IAT,
	             cCodigo,cDescricao,cQtde,cUnidade,cValor,Valor_total_liquido,cAliquota,false, Casas_decimais_da_quantidade);
	vilavielaframe->Analisa_iRetorno(retimp);
	return retimp;
}

int IMPRESSORA_FISCAL::_VerificaFormasPagamento(char *sFgto) {
//	MODOTESTE() 1;
	int retimp=0;
 ASSERT_PRINTERON()
	if (BEMATECH_MATRICIAL)
		retimp= Bematech_FI_VerificaFormasPagamento(sFgto);
	else
		if (BEMATECH_MATRICIAL_MFD||BEMATECH_TERMICAS)
			retimp= Bematech_FI_VerificaFormasPagamentoMFD(sFgto);
		else
			if (SWEDA_MATRICIAL)
				retimp= ECF_VerificaFormasPagamento(sFgto);
			else
				if (SWEDA_TERMICA)
					retimp= ECF_VerificaFormasPagamentoMFD(sFgto);
	vilavielaframe->Analisa_iRetorno(retimp);
	return retimp;
}
