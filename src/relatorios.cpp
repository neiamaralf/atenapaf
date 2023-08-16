#include "relatorios.h"
#include "vilavilela.h"
#include "md5.h"
#include "sweda.h"
#include "impressora_fiscal.h"
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/progdlg.h"

 
using namespace RELATORIOS::assinatura;
using namespace RELATORIOS::atoCOTEP1704;
using namespace RELATORIOS::utils;
using namespace RELATORIOS::requisitoXXV;
using namespace RELATORIOS::requisitoXXII;
using namespace IMPRESSORA_FISCAL;

void ListTotalizadorParcial::novo(const char *codigo,int Valor_acumulado){
	novoptr();
	ult->Valor_acumulado=Valor_acumulado;		
	strcpy(ult->codigo,codigo);		
}




void ListRedZ::novo(int nouser,int crz,int cro,long data,int hora,int vendabrutadiaria){
	novoptr();
	ult->nouser=nouser;		
	ult->crz=crz;		
	ult->cro=cro;		
	ult->data=data;		
	ult->hora=hora;		
	ult->vendabrutadiaria=vendabrutadiaria;		
}

int RELATORIOS::assinatura::savexml(char *pubmod,int lenght){
	FILE *fl=fopen("Atena3D_Ltda.xml","w+b");
	fprintf(fl,"<?xml version=\"1.0\"?>%c%c",0x0d,0x0a);
	fprintf(fl,"<empresa_desenvolvedora>%c%c",0x0d,0x0a);
	fprintf(fl,"\t<nome>");fprintf(fl,"Atena3D_Ltda");fprintf(fl,"</nome>%c%c",0x0d,0x0a);
	fprintf(fl,"\t<chave>%c%c",0x0d,0x0a);
	fprintf(fl,"\t\t<modulo>");
	for(int i=0;i<lenght;i++)
		fprintf(fl,"%02x",((int)pubmod[i])&0xff);
	fprintf(fl,"</modulo>%c%c",0x0d,0x0a);
	fprintf(fl,"\t\t<expoente_publico>");
	fprintf(fl,"%0256x",0x10001);
	fprintf(fl,"</expoente_publico>%c%c",0x0d,0x0a);
	fprintf(fl,"\t</chave>%c%c",0x0d,0x0a);
	fprintf(fl,"</empresa_desenvolvedora>%c%c",0x0d,0x0a);
	fclose(fl);
	return 1;
}

void RELATORIOS::assinatura::createprivatekey(){

}

void RELATORIOS::assinatura::n_printf(unsigned char *str, int lenght){
	for(int i=0;i<lenght;i++)
		printf("%02x",((int)*(str+i))&0xff);
}

void RELATORIOS::assinatura::n_fprintf(FILE *f,unsigned char *str, int lenght){
	for(int i=0;i<lenght;i++)
		fprintf(f,"%02X",((int)*(str+i))&0xff);
}

int pass_cb(char *buf, int size, int rwflag, void *u) {
        int len;
        char tmp[]="dirsicaf";
        len = strlen(tmp);
        if (len <= 0) return 0;
        /* if too long, truncate */
        if (len > size) len = size;
        memcpy(buf, tmp, len);
        return len;
        }

EVP_PKEY * RELATORIOS::assinatura::ReadPublicKey(const char *pkeyfile){
	FILE *fp = fopen (pkeyfile, "r");  
	EVP_PKEY *pkey;
	if (!fp)
		return NULL;
	char passwrd[]="dirsicaf";
	pkey =  PEM_read_PUBKEY(fp, NULL, pass_cb,passwrd);
	fclose (fp);
	if (pkey == NULL) 
		ERR_print_errors_fp (stderr);
	return pkey; 
}

EVP_PKEY *RELATORIOS::assinatura::ReadPrivateKey(const char *keyfile){
	FILE *fp = fopen(keyfile, "r");
	EVP_PKEY *pkey;
	char passwrd[]="dirsicaf";
	if (!fp)
		return NULL;OpenSSL_add_all_algorithms();
	pkey = PEM_read_PrivateKey(fp, NULL, pass_cb, passwrd);
	fclose (fp);
	if (pkey == NULL)  
		ERR_print_errors_fp (stderr);   
	return pkey;
}



int  RELATORIOS::assinatura::_encrypt( const unsigned char *_message,int lenght,unsigned char **_encryptedmessage){	
	int bytecount=0;
	EVP_PKEY *privKey = ReadPrivateKey("privkeyv.pem");
	if (!privKey) 	{  
		ERR_print_errors_fp (stderr);    
		return 0;  
	}	
	*_encryptedmessage=new unsigned  char[EVP_PKEY_size(privKey)];
	bytecount = RSA_private_encrypt(lenght, _message, *_encryptedmessage, privKey->pkey.rsa,RSA_NO_PADDING);
	if (bytecount != EVP_PKEY_size(privKey)){
		wxString ermsg;
		ermsg.Printf(_("Error: ciphertext should match length of key len=%d privkeysize=%d\n"),lenght,EVP_PKEY_size(privKey));
		wxMessageBox(ermsg);
		return 0;  
	}
	EVP_PKEY_free(privKey);  
	return bytecount;
}

int RELATORIOS::assinatura::_decrypt(const unsigned char  *_encryptedmessage,int lenght,unsigned char  **_decriypted){
	EVP_PKEY *pubKey= ReadPublicKey("pubkeyv.pem");  
	if(!pubKey){
		fprintf(stderr,"Error: can't load public key");
		return 0;  
	}
	*_decriypted=new unsigned  char[EVP_PKEY_size(pubKey)];
	int bytecount = RSA_public_decrypt(lenght, _encryptedmessage, *_decriypted, pubKey->pkey.rsa,RSA_NO_PADDING);	
	EVP_PKEY_free(pubKey);  
	return bytecount;
}

void RELATORIOS::assinatura::monta128byteshash(FILE *file,char buf[16],unsigned char blk[128]){
	unsigned char *ptrblk=blk+1,*endblk=blk+127;*blk=0x10;
	_MD5::MDFile (file,buf);
	for(int i=0;i<16;i++,ptrblk++)*ptrblk=buf[i];
	for(int j=18;;j++,ptrblk++){
		*ptrblk=(unsigned char)' ';
		if(ptrblk==endblk)break;
	}
}

char RELATORIOS::assinatura::retdigit(char digit){
	switch(digit){
	case '0':return 0;
	case '1':return 1;
	case '2':return 2;
	case '3':return 3;
	case '4':return 4;
	case '5':return 5;
	case '6':return 6;
	case '7':return 7;
	case '8':return 8;
	case '9':return 9;
	case 'a':case 'A':return 10;
	case 'b':case 'B':return 11;
	case 'c':case 'C':return 12;
	case 'd':case 'D':return 13;
	case 'e':case 'E':return 14;
	case 'f':case 'F':return 15;
	}
	return '0';
}

char RELATORIOS::assinatura::retbyte(char byte[2])
{
	return (retdigit(*byte)<<4)|retdigit(*(byte+1));

}

bool RELATORIOS::assinatura::sign_file(const char *filename){
	char buf[16];
	unsigned char EAD[128],OLDEAD[128];
	unsigned char *crypttext;

	FILE *f=fopen(filename,"r+b");
	if(f==NULL)return false;
	//fseek ( f , 0 , SEEK_SET );char c;
	//while(fscanf(f,"%c",&c)!=EOF){printf("%02x:",((int)c)&0xff);if(c=='\n')printf("\n");}


	char ead[4]="";bool assinado=true;
	fseek ( f , -259 , SEEK_END );//begin of ead record se existir
	fscanf(f,"%c%c%c",ead,ead+1,ead+2);
	if(strcmp(ead,"EAD")!=0){
		fseek ( f , -260 , SEEK_END );//begin of ead record se existir casohaja \n
		fscanf(f,"%c%c%c",ead,ead+1,ead+2);
		if(strcmp(ead,"EAD")!=0){
			fseek ( f , -261 , SEEK_END );//begin of ead record se existir casohaja \r
			fscanf(f,"%c%c%c",ead,ead+1,ead+2);
			if(strcmp(ead,"EAD")!=0)assinado=false;
		}
	}
	if(!assinado){
		monta128byteshash(f,buf,EAD);
		fseek ( f , 0 , SEEK_END );
		fprintf(f,"EAD");		
	}
	else{//já assinado, atualiza e informa se foi alterado
		FILE *tmpf=fopen("tmpfile.dat","w+");
		long eadpos=ftell (f)-2;
		fseek ( f , 0 , SEEK_SET );
		int bytes;
		char data[1024];
		while ((bytes = fread (data, 1, 1, f)) != 0){
			if(ftell (f)==eadpos)break;
			fwrite ( data, 1, bytes, tmpf);
		}
		monta128byteshash(tmpf,buf,EAD);
		fclose(tmpf);
		fseek ( f , eadpos+2 , SEEK_SET );
		char hexbyte[2];int ind=0;
		while((bytes = fread (hexbyte, 1, 2, f))!=0){
			OLDEAD[ind++]=(unsigned char)retbyte(hexbyte);
			//printf("%s\n",hexbyte);
		}

		//n_printf(OLDEAD,128);printf("\n");
		//	n_printf(EAD,128);printf("\n");		
		fseek ( f , eadpos+2 , SEEK_SET );
	}
	int lenghtcrypt;
	lenghtcrypt=_encrypt(EAD,128,&crypttext);
	if(assinado){
		if(memcmp(OLDEAD,crypttext,128)!=0)
			printf("arquivo foi alterado\n");
		else
			printf("arquivo integro\n");
	}
	else 	printf("arquivo nao assinado\n");
	//n_printf(crypttext,lenghtcrypt);
	if(crypttext!=NULL)n_fprintf(f,crypttext ,128);
	//printf("%s\n",ead);
	fclose(f);
	if(crypttext!=NULL)
		delete []crypttext;
	return true;
}

void RELATORIOS::utils::_copyfile (FILE *inFile,FILE *outFile){ 
	int bytes;
	char data[1024]; 
	while ((bytes = fread (data, 1, 1024, inFile)) != 0)
		fwrite(data, 1, bytes, outFile); 
}

int RELATORIOS::utils::_load_file_to_buf(const char *filename, char **result,bool nulllast) { 
	int size = 0;
	FILE *f = fopen(filename, "rb");
	if (f == NULL) { 
		*result = NULL;
		return -1; // -1 means file opening fail 
	} 
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	if(size==0){*result = NULL;return -3;}
	*result = (char *)malloc(2*size);
	if (size != fread(*result, sizeof(char), size, f)) { 
		free(*result);
		return -2; // -2 means file reading fail 
	} 
	fclose(f);
	if(nulllast)
 	(*result)[size] = 0;
	return size;
}

void RELATORIOS::utils::mountcotepefname(const char *prefix,char *buf){	
	wxDateTime datetime=wxDateTime::Now();
	sprintf(buf,"%s%s_%04d%02d%02d_%02d%02d%02d.txt",prefix,vilavielaframe->ecf.Numero_de_fabricacao,datetime.GetYear(),(int)datetime.GetMonth()+1,datetime.GetDay(),
		datetime.GetHour(),datetime.GetMinute(),datetime.GetSecond());
}

void RELATORIOS::utils::saveretornoimpressora(const char *prefix,char *buffname){
	char fname[64];
	mountcotepefname(prefix,fname);
	if(buffname)strcpy(buffname,fname);
	FILE *LMFC=fopen(fname,"w+b"),*fret=fopen("retorno.txt","rb");
	if(LMFC==NULL||fret==NULL){wxMessageBox(_("Erro ao salvar arquivo, tente novamente!"));goto _return;}

	_copyfile(fret,LMFC);
_return:
	fclose(LMFC);fclose(fret);
	sign_file(fname);
	wxString str,path,dir=wxGetCwd(),fn=wxString::FromAscii(fname);
	dir.Replace(_("\\"),_("/"));
	path=dir+_("/")+fn;
	str=_("arquivo salvo como:\n")+path;
	wxMessageBox(str); 
	wxLaunchDefaultBrowser(path);
}

void RELATORIOS::utils::removechar(char *str,char toremove){
	char *ptr=str,*buf=new char[strlen(str)+1],*ptrbuf=buf;int count=0;
	for(;*ptr;ptr++){
		if(*ptr!=toremove){
			*ptrbuf=*ptr;ptrbuf++;
		}			
	}
	buf[ptrbuf-buf]=0;
	strcpy(str,buf);
}


void RELATORIOS::utils::skipline(FILE *f){
	char c;
	do{
		c=fgetc(f);//printf("%c",c);
	}while(c!=EOF&&c!='\n');
}

void RELATORIOS::utils::skipspaces(FILE *f){
	char c;
	do{
		c=fgetc(f);
	}while(c!=EOF&&(c==' '||c=='\t')&&c!='\n');
	fseek(f,-1,SEEK_CUR);
}

int RELATORIOS::utils::readline(FILE *f,char *buf){
	char c,*ptr=buf;
	do{
		c=fgetc(f);
		if(c!=EOF&&c!=0x0a&&c!=0x0d){
			*ptr=c;ptr++;}
	}while(c!=EOF&&c!='\n');
	*(ptr)=0;
	return ptr-buf;
}

void RELATORIOS::utils::skipsection(FILE *f){
	char c;
	do{
		skipline(f);
		c=fgetc(f);
		//printf("%c\n",c);
	}while(c!=EOF&&c!='-');
}

long RELATORIOS::utils::formatdata(char *datastr){
	char fdata[9]="";
	long ano,mes,dia;
	removechar(datastr,'/');removechar(datastr,'\\');
	if(strcmp(datastr,"000000")==0||strcmp(datastr,"00000000")==0)return 0;
	strcpy(fdata,"");			
	strncpy(fdata,datastr+2,2);
	mes=atoi(fdata)*100;
	strncpy(fdata,datastr,2);
	dia=atoi(fdata);
	strncpy(fdata,datastr+4,2);
	ano=atoi(fdata);
	if(ano<50)ano+=2000;else ano+=1900;ano*=10000;
	return (dia+mes+ano);
}

long RELATORIOS::utils::formatdata2(char *datastr){
	char fdata[9]="";
	long ano,mes,dia;
	removechar(datastr,'/');removechar(datastr,'\\');
	if(strcmp(datastr,"000000")==0||strcmp(datastr,"00000000")==0)return 0;
	strcpy(fdata,"");			
	strncpy(fdata,datastr+2,2);
	mes=atoi(fdata)*10000;
	strncpy(fdata,datastr,2);
	dia=atoi(fdata)*1000000;
	strncpy(fdata,datastr+4,2);
	ano=atoi(fdata);
	if(ano<50)ano+=2000;else ano+=1900;
	return (dia+mes+ano);
}



char* RELATORIOS::utils::le_ate_car(char *b,char car,int size){
	char *ptr=b,*lst=b+size-1;
	for(;;ptr++){
		if(car==*ptr)return ptr+1;
		if(ptr==lst)break;
	}
	return 0;
}

char* RELATORIOS::utils::le_enquanto_car(char *b,char car,int size){
	char *ptr=b,*lst=b+size-1;
	for(;;ptr++){
		if(car!=*ptr)return ptr;
		if(ptr==lst)break;
	}
	return 0;
}

char* RELATORIOS::utils::le_ate_fim_linha(char *bufin,char *bufout,int nlinhas){
	for(int i=0;i<nlinhas;i++){
		while(*bufin!=0x0a){
			if(bufout&&*bufin!=0x0d)
				*(bufout++)=*(bufin);		
			bufin++;
		}
		bufin++;
	}
	if(bufout)
		*bufout=0;
	return bufin;
}

void RELATORIOS::utils::transformadataparaFormatoCotepe(char *data){
	long iData_do_movimento= RELATORIOS::utils::formatdata(data);
	sprintf(data,"%8ld",iData_do_movimento);	
}

void RELATORIOS::requisitoXXV::registro_R04(char* Meio_de_pagamento,char *Nome_do_adquirente,char *CPF_CNPJ_do_adquirente,bool cancelado,bool criaR06){
	MODOTESTE() ;
 NENHUMRELATORIO();
	if(vilavielaframe->impressorabloqueada)return;
	Palavra query;
	sql_ResultSet *res;	
	int Retorno;
	removechar(CPF_CNPJ_do_adquirente,'.');removechar(CPF_CNPJ_do_adquirente,'/');removechar(CPF_CNPJ_do_adquirente,'-');removechar(CPF_CNPJ_do_adquirente,'\\');
	char Data[9]="",Hora[7]="",
		SubTotal [15]="0",Desconto[16]="0",Acrescimo[16]="0",Valor_Total_Liquido[16]="0",Ind_de_Cancelamento[2]="",tmpstr[32],
		tipodesc[2]="P";
	int descpercentual;
	_atualiza_dados_impressora();
	Retorno=_DataHoraImpressora(Data, Hora);
	sprintf(Data,"%8ld",formatdata(Data));
	if(!cancelado)
	 Retorno=_SubTotal(SubTotal);
	if(!cancelado){
		query="SELECT MAX(idvenda) FROM vendas ";
		if((res=vilavielaframe->_execquerywithresult(query))!=NULL&&vilavielaframe->_nextrow(res)){	
			query="SELECT desconto,desconto_percentual FROM vendas WHERE idvenda=";
			sprintf(tmpstr,"%d",vilavielaframe->_getint(res,1));
			vilavielaframe->_deleteresult(&res);
			query.append(tmpstr);
			if((res=vilavielaframe->_execquerywithresult(query))!=NULL&&vilavielaframe->_nextrow(res)){	
				sprintf(Desconto,"%.2f",vilavielaframe->_getdouble(res,1));			
				descpercentual=vilavielaframe->_getint(res,2);
				if(descpercentual==1)*tipodesc='P';else *tipodesc='V';
				removechar(Desconto,',');removechar(Desconto,'.');	
				float valliquido;
				if(*tipodesc=='P'){
				 valliquido=(float)atoi(SubTotal)/100.0;
					valliquido=valliquido-((float)atoi(Desconto)/10000.0)*valliquido;
				}
				else if(*tipodesc=='V')
					valliquido=(float)atoi(SubTotal)/100.0-(float)atoi(Desconto)/100.0;
				if(valliquido<=0)valliquido*=-1.0;
				sprintf(Valor_Total_Liquido,"%.2f",valliquido);		
				removechar(Valor_Total_Liquido,',');removechar(Valor_Total_Liquido,'.');		
				vilavielaframe->_deleteresult(&res);
			}
		}
	}
	else{
		bool desconto_percentual;
		wxTextCtrl *eddesconto=(wxTextCtrl *)vilavielaframe->FindWindowById(ID_VENDAS_DESCONTO,vilavielaframe),
			*edsubtotal=(wxTextCtrl *)vilavielaframe->FindWindowById(ID_VENDAS_TOTAL,vilavielaframe);
		wxCheckBox *chkdescperc=(wxCheckBox *)vilavielaframe->FindWindowById(ID_CHK_PERCENTUAL,vilavielaframe);		
		float fsubtotal=atof(edsubtotal->GetValue().ToAscii()),fdesc=atof(eddesconto->GetValue().ToAscii()),valliquido;
		desconto_percentual=chkdescperc->GetValue();
		if(desconto_percentual)valliquido=fsubtotal-fdesc*0.01*fsubtotal;
		else valliquido=fsubtotal-fdesc;
		if(valliquido<=0)valliquido*=-1.0;
		sprintf(Valor_Total_Liquido,"%.2f",valliquido);
		removechar(Valor_Total_Liquido,'.');removechar(Valor_Total_Liquido,',');
	}
	if(cancelado)*Ind_de_Cancelamento='S';else *Ind_de_Cancelamento='N';
 

	query="INSERT INTO r04(Numero_de_fabricacao,MF_adicional,Modelo_do_ECF,Numero_do_usuario,CCF_CVC_ou_CBP,COO,Data_de_inicio_da_emissao,Subtotal_do_Documento,\
								Desc_sobre_subtotal,Valor_Total_Liquido,Ind_de_Cancelamento,Nome_do_adquirente,CPF_CNPJ_do_adquirente,Ind_do_Tipo_de_Desc_sobre_subtotal,Meio_de_pagamento) VALUES('";
	query.append(vilavielaframe->ecf.Numero_de_fabricacao);query.append("','");
	query.append(vilavielaframe->ecf.MF_adicional);query.append("','");
	query.append(vilavielaframe->ecf.Modelo_do_ECF);query.append("',");
	query.append(vilavielaframe->ecf.Numero_do_usuario);query.append(",");
	query.append(vilavielaframe->ecf.CCF);query.append(",");
	query.append(vilavielaframe->ecf.COO);query.append(",");
	query.append(Data);query.append(",");
	query.append(SubTotal);query.append(",");
	query.append(Desconto);query.append(",");
	query.append(Valor_Total_Liquido);query.append(",'");
	query.append(Ind_de_Cancelamento);query.append("','");
	query.append(Nome_do_adquirente);query.append("','");
	query.append(CPF_CNPJ_do_adquirente);query.append("','");
	query.append(tipodesc);query.append("','");
	query.append(Meio_de_pagamento);
	query.append("')");
	vilavielaframe->_execquery(query);

	registro_R07(vilavielaframe->ecf.Numero_de_fabricacao,vilavielaframe->ecf.MF_adicional,vilavielaframe->ecf.Modelo_do_ECF,vilavielaframe->ecf.Numero_do_usuario,vilavielaframe->ecf.COO,Meio_de_pagamento,Valor_Total_Liquido);
	if(criaR06)
		registro_R06(Valor_Total_Liquido,Meio_de_pagamento,Comprovante_NFiscal_Cancel,true,Valor_Total_Liquido);	
}

void RELATORIOS::requisitoXXV::registro_R05(char *Numero_de_fabricacao,char *MF_adicional,char *Modelo_do_ECF,char *Numero_do_usuario,char *CCF_CVC_ou_CBP,	char *COO,char *IAT,
	char *Cod_do_Produto_ou_Servico,char *Descricao,char *Quantidade,char *Unidade,char *Valor_unitario,
	char *Valor_total_liquido,char *Totalizador_parcial,bool cancelado,char* Casas_decimais_da_quantidade){
		if(vilavielaframe->impressorabloqueada)return;
		Palavra query;
		int Retorno;
		char 	Numero_do_item[5]="",Indicador_de_cancelamento[2]="N";		
		Retorno=_UltimoItemVendido(Numero_do_item);
		if(cancelado)*Indicador_de_cancelamento='S';
		
		query="INSERT INTO r05(Numero_de_fabricacao,MF_adicional,Modelo_do_ECF,Numero_do_usuario,COO,CCF_CVC_ou_CBP,\
								Numero_do_item,Cod_do_Produto_ou_Servico,Descricao,Quantidade,Unidade,Valor_unitario,Valor_total_liquido,\
								Totalizador_parcial,Indicador_de_cancelamento,IAT,Casas_decimais_da_quantidade) VALUES('";
		query.append(Numero_de_fabricacao);query.append("','");
		query.append(MF_adicional);query.append("','");
		query.append(vilavielaframe->ecf.Modelo_do_ECF);query.append("',");
		query.append(Numero_do_usuario);query.append(",");
		query.append(COO);query.append(",");
		query.append(CCF_CVC_ou_CBP);query.append(",");
		query.append(Numero_do_item);query.append(",'");
		query.append(Cod_do_Produto_ou_Servico);query.append("','");
		query.append(Descricao);query.append("',");
		query.append(Quantidade);query.append(",'");
		query.append(Unidade);query.append("',");
		query.append(Valor_unitario);query.append(",");
		query.append(Valor_total_liquido);query.append(",'");
		query.append(Totalizador_parcial);query.append("','");
		query.append(Indicador_de_cancelamento);query.append("','");
		query.append(IAT);query.append("',");
		query.append(Casas_decimais_da_quantidade);
		query.append(")");
		vilavielaframe->_execquery(query);
}

char* RELATORIOS::utils::caixaalta( char* s ){
	char* p = s;
	while (*p = toupper( *p )) p++;
	return s;
}

void RELATORIOS::utils::_md5_executavel(const char *executavel,char buf[33]){
FILE *f=fopen(executavel,"rb");
	if(f!=NULL){
		char md5[16];
		_MD5::MDFile (f,md5);		
		for(int i=0;i<32;i+=2){
			sprintf(buf+i,"%01x%01x",(((int)md5[i/2])&0xf0)>>4,((int)md5[i/2])&0xf);
		}
		buf[32]=0;
		caixaalta(buf);
		fclose(f);
	}
}

void RELATORIOS::utils::_atualiza_items_cupom_cancelado(){
	Palavra query;
	sql_ResultSet *res,*res2;
	char CCF[16];
	_ContadorCupomFiscal(false,CCF);
	query="SELECT COO FROM r04 WHERE idR04=";
	query.append(CCF);
	if(((res=vilavielaframe->_execquerywithresult(query))!=NULL)&&vilavielaframe->_nextrow(res)){
		query="SELECT idR05 FROM r05 WHERE COO=";
		query.append(vilavielaframe->_getstring(res,1).ToAscii());
		if(((res2=vilavielaframe->_execquerywithresult(query))!=NULL)&&vilavielaframe->_nextrow(res2)){
			do{
				query="UPDATE r05 SET Indicador_de_cancelamento='S' WHERE idR05=";
				query.append(vilavielaframe->_getstring(res2,1).ToAscii());
				vilavielaframe->_execquery(query);
			}while(vilavielaframe->_nextrow(res2));
			vilavielaframe->_deleteresult(&res2);
		}
		vilavielaframe->_deleteresult(&res);
	}
}

void RELATORIOS::requisitoXXV::registro_R06(char *Valor_pago,char* Meio_de_pagamento,const char* Denominacao,bool estorno,char *Valor_estornado){
	MODOTESTE() ;NENHUMRELATORIO();
		Palavra query;
		int Retorno;
		char GNF[7]="1",CRG[7]="0",CDC[5]="0",Data[9]="",Hora[7]="";
		_atualiza_dados_impressora();
		Retorno=_ContadorOperacoesNaoFiscal(GNF);
		if(strcmp(Relatorio_Gerencial,Denominacao)==0)
			Retorno=_Contador_GRG(CRG);
		if(strcmp(Comprovante_de_CD,Denominacao)==0)
			Retorno=_Contador_de_CDC(CDC);
		Retorno=_DataHoraUltimoMovimento(Data,Hora);
		
		registro_R07(vilavielaframe->ecf.Numero_de_fabricacao,vilavielaframe->ecf.MF_adicional,vilavielaframe->ecf.Modelo_do_ECF,vilavielaframe->ecf.Numero_do_usuario,vilavielaframe->ecf.COO,Meio_de_pagamento,Valor_pago,estorno,Valor_estornado);
		if(strcmp(Denominacao,Comprovante_NFiscal_Cancel)==0){
			_atualiza_items_cupom_cancelado();
		}
		query="INSERT INTO r06(Numero_de_fabricacao,MF_adicional,Modelo_do_ECF,Numero_do_usuario,COO,GNF,\
								CRG,CDC,Denominacao,Data_final_de_emissao,Hora_final_de_emissao) VALUES('";
		query.append(vilavielaframe->ecf.Numero_de_fabricacao);query.append("','");
		query.append(vilavielaframe->ecf.MF_adicional);query.append("','");
		query.append(vilavielaframe->ecf.Modelo_do_ECF);query.append("',");
		query.append(vilavielaframe->ecf.Numero_do_usuario);query.append(",");
		query.append(vilavielaframe->ecf.COO);query.append(",");
		query.append(GNF);query.append(",");
		query.append(CRG);query.append(",");
		query.append(CDC);query.append(",'");
		query.append(Denominacao);query.append("',");
		query.append(Data);query.append(",");
		query.append(Hora);
		query.append(")");
		vilavielaframe->_execquery(query);
		
}

void RELATORIOS::requisitoXXV::registro_R07(const char *Numero_de_fabricacao,const char *MF_adicional,const char *Modelo_do_ECF,const char *Numero_do_usuario,const char *COO,const char* Meio_de_pagamento, char *Valor_pago,bool estorno,const char *Valor_estornado){
	MODOTESTE() ;NENHUMRELATORIO();NENHUMRELATORIO();
		Palavra query;
		int Retorno;
		removechar(Valor_pago,',');removechar(Valor_pago,'.');
		char GNF[7]="1",Indicador_de_estorno[2]="N",CCF[16];
		//_atualiza_dados_impressora();
		_ContadorCupomFiscal(false,CCF);
		Retorno=_ContadorOperacoesNaoFiscal(GNF);
		if(estorno)*Indicador_de_estorno='S';
		query="INSERT INTO r07(Numero_de_fabricacao,MF_adicional,Modelo_do_ECF,Numero_do_usuario,COO,GNF,CCF,Meio_de_pagamento,Valor_pago,Indicador_de_estorno,Valor_estornado) VALUES('";
		query.append(Numero_de_fabricacao);query.append("','");
		query.append(MF_adicional);query.append("','");
		query.append(vilavielaframe->ecf.Modelo_do_ECF);query.append("',");
		query.append(Numero_do_usuario);query.append(",");
		query.append(COO);query.append(",");
		query.append(GNF);query.append(",");
		query.append(CCF);query.append(",'");
		query.append(Meio_de_pagamento);query.append("',");
		query.append(Valor_pago);query.append(",'");
		query.append(Indicador_de_estorno);query.append("',");
		query.append(Valor_estornado);
		query.append(")");
		vilavielaframe->_execquery(query);
}


void RELATORIOS::requisitoIX::registro_N1(FILE *file,const char *cnpj,const char *IE,const char *IM,const char *razaosocial){
	fprintf(file,"N1%014d%-14s%-14s%-50s%c%c",atoi(cnpj),IE,IM,razaosocial,0x0d,0x0a);
}

void RELATORIOS::requisitoIX::registro_N2(FILE *file,const char *nolaudo,const char *nomeaplicativo,const char *versaoaplicativo){
	fprintf(file,"N2%-10s%-50s%-10s%c%c",nolaudo,nomeaplicativo,versaoaplicativo,0x0d,0x0a);
}


void RELATORIOS::requisitoIX::registro_N3(FILE *file,const char *nomeexe){
	char md5[33],_nomeexe[50];
	_md5_executavel(nomeexe,md5);
	strcpy(_nomeexe,nomeexe);
	caixaalta(_nomeexe);
	fprintf(file,"N3%-50s%-32s%c%c",_nomeexe,md5,0x0d,0x0a);
}

void RELATORIOS::requisitoIX::registro_N9(FILE *file,const char *cnpj,const char *IE,int quantN3){
	fprintf(file,"N9%014d%-14s%06d%c%c",atoi(cnpj),IE,quantN3,0x0d,0x0a);
}

char* inifileb_skipline(char *buf,char *ptrbuf,int lenght){
	char *c,*lstptr;
	for(c=ptrbuf,lstptr=buf+lenght-1;c<lstptr;c++)if(*c==0x0a){c++;break;}
	return c;
}


char* inifileb_nextsection(char *buf,char *ptrbuf,int lenght){
	char *c,*lstptr;
	for(c=ptrbuf,lstptr=buf+lenght-1;c<lstptr;c++)if(*c=='['){c++;break;}
	return c;
}

char* inifileb_sectiontitle(char *buf,char *ptrbuf,int lenght,char *title){
	char *c,*lstptr,*ptrtitle=title;
	for(c=ptrbuf,lstptr=buf+lenght-1;c<lstptr;c++){
		if(*c!=0x0d&&*c!=0x0a){
		 *ptrtitle=*c;ptrtitle++;
		}
		if(*c==0x0a){c++;break;}
	}
	*(ptrtitle-1)=0;
	return c;
}


void RELATORIOS::requisitoIX::gravalistaexecutaveis(){
	MODOTESTE();NENHUMRELATORIO();NENHUMRELATORIO();
	FILE *f=fopen("lista_arquivos.txt","w+b");
	registro_N1(f, "16656232000132","9060393629","4239924","Atena3D");
	registro_N2(f,"3241","atenaPAF","1.0.0");
	int narq;
#ifdef WIN32
	narq=1;
	registro_N3(f,"atenapaf.exe");
#else
	narq=1;
	registro_N3(f,"atenapaf");
#endif
	registro_N9(f,"16656232000132","9060393629",narq);
	fclose(f);
	sign_file("lista_arquivos.txt");
	mostralocalgravacaoarquivos("lista_arquivos.txt");
	char md5file[33];
	_md5_executavel("lista_arquivos.txt",md5file);
	char *bd;
	int sz=descriptografa_arquivo("arquivo_auxiliare.txt",&bd);
	atualiza_arquivo_auxiliar("MD5",bd,sz,md5file,NULL,true,false);
	criptografa_buf("arquivo_auxiliare.txt",bd);
	delete []bd;
#ifdef DEVELOPING
	char *nbuf;
	sz=descriptografa_arquivo("arquivo_auxiliare.txt",&nbuf);
	FILE *dest=fopen("descriptnew.txt","w+b");
	fwrite(nbuf,1,sz,dest);
	delete []nbuf;
	fclose(dest); 
#endif
}

bool RELATORIOS::requisitoXXII::ECF_autorizada(char *bd,int sz,char CNI[7]){
#ifdef USANDO_EMULADOR
	return true;
#endif
	wxString erromsg;
	bool retval=false;
	char noserieteste[21]="";
	int i;
	_NumSerieImpressora(noserieteste);
	char title[256],*ptr=bd,*lstbd=bd+sz-1,noserie[21]="",*ptrns,*ptrnstest=noserieteste;
	while(*ptrnstest=='0')ptrnstest++;
	while(ptr&&(ptr=inifileb_nextsection(bd,ptr,sz))!=lstbd){
		ptr=inifileb_sectiontitle(bd,ptr,sz,title);
		if(*ptr==0x0a)continue;
		if(strcmp(title,"ECFS")==0){			
			while(ptr){
				for(i=0;i<20;i++,ptr++)noserie[i]=*ptr;ptr++;
				if((ptr=le_ate_fim_linha(ptr,CNI))>=lstbd)break;
				if(*ptr==0x0a)continue;
				ptrns=noserie;while(*ptrns=='0')ptrns++;
				if(strcmp(ptrns,ptrnstest)==0){
					retval= true;
					goto Retorno;
				}
				if(*ptr=='['){ptr--;break;}
			}
			break;			
		}		 		
		if(ptr>=lstbd)break;
	}
	Retorno:
	if(!retval){
		wxString erstr=wxString::FromAscii(noserieteste);
		erromsg.Printf(___("ecf %s não autorizada"),noserieteste);
	 wxMessageBox(erromsg);
	}
	return retval;
}

void List_String::novo(const char* str){
	novoptr();
	ult->str=___(str);
}

void RELATORIOS::requisitoXXII::atualiza_arquivo_auxiliar(const char *campo,char *bd,int sz,const char *novovalor,char *valorantigo,bool atualiza,bool retorna,List_String *lst){
	char title[256],*ptr=bd,*lstbd=bd+sz-1,CNI[7];
	int i;
	if(strcmp(campo,"CNPJ")==0||strcmp(campo,"IE")==0||strcmp(campo,"IM")==0||strcmp(campo,"CNPJ_USER")==0||strcmp(campo,"IE_USER")==0||strcmp(campo,"IM_USER")==0){
		while(ptr&&(ptr=inifileb_nextsection(bd,ptr,sz))!=lstbd){
			ptr=inifileb_sectiontitle(bd,ptr,sz,title);
			if(*ptr==0x0a)continue;
			if(strcmp(title,campo)==0){
				for(i=0;i<14;i++,ptr++){
					if(retorna)valorantigo[i]=*ptr;
					if(atualiza)*ptr=novovalor[i];
				}
				if(retorna)valorantigo[14]=0;
				return;
			}		 		
			if(ptr>=lstbd)break;
		}
	}
	else if(strcmp(campo,"DEN")==0||strcmp(campo,"NOME")==0||strcmp(campo,"NOME_USER")==0){
		while(ptr&&(ptr=inifileb_nextsection(bd,ptr,sz))!=lstbd){
			ptr=inifileb_sectiontitle(bd,ptr,sz,title);
			if(*ptr==0x0a)continue;
			if(strcmp(title,campo)==0){
				for(i=0;i<40;i++,ptr++){
					if(retorna)valorantigo[i]=*ptr;
					if(atualiza)*ptr=novovalor[i];
				}
				if(retorna)valorantigo[40]=0;
				return;
			}		 		
			if(ptr>=lstbd)break;
		}
	}
	if(strcmp(campo,"ECFS")==0){			
		char noserie[21]="",*ptrns;
		while(ptr&&(ptr=inifileb_nextsection(bd,ptr,sz))!=lstbd){
			ptr=inifileb_sectiontitle(bd,ptr,sz,title);
			if(*ptr==0x0a)continue;
			if(strcmp(title,campo)==0){
				while(ptr){
					for(i=0;i<20;i++,ptr++)noserie[i]=*ptr;ptr++;
					if((ptr=le_ate_fim_linha(ptr,CNI))>=lstbd)break;
					if(*ptr==0x0a)continue;
					ptrns=noserie;
					while(*ptrns=='0')ptrns++;
					lst->novo(ptrns);
					if(*ptr=='['){ptr--;return;}
				}
			}		 		
			if(ptr>=lstbd)break;
		}
	}		 		
	else if(strcmp(campo,"VERSAO")==0){
		while(ptr&&(ptr=inifileb_nextsection(bd,ptr,sz))!=lstbd){
			ptr=inifileb_sectiontitle(bd,ptr,sz,title);
			if(*ptr==0x0a)continue;
			if(strcmp(title,"VERSAO")==0){
				for(i=0;i<10;i++,ptr++){
					if(retorna)valorantigo[i]=*ptr;
					if(atualiza)*ptr=novovalor[i];
				}
				if(retorna)valorantigo[10]=0;
				return;
			}		 		
			if(ptr>=lstbd)break;
		}
	}
	else if(strcmp(campo,"TOTAL_GT")==0){
		while(ptr&&(ptr=inifileb_nextsection(bd,ptr,sz))!=lstbd){
			ptr=inifileb_sectiontitle(bd,ptr,sz,title);
			if(*ptr==0x0a)continue;
			if(strcmp(title,"TOTAL_GT")==0){
				for(i=0;i<18;i++,ptr++){
					if(retorna)valorantigo[i]=*ptr;
					if(atualiza)*ptr=novovalor[i];
				}
				if(retorna)valorantigo[18]=0;
				return;
			}		 		
			if(ptr>=lstbd)break;
		}
	}
	else if(strcmp(campo,"MD5")==0){
		while(ptr&&(ptr=inifileb_nextsection(bd,ptr,sz))!=lstbd){
			ptr=inifileb_sectiontitle(bd,ptr,sz,title);
			if(*ptr==0x0a)continue;
			if(strcmp(title,"MD5")==0){
				for(i=0;i<32;i++,ptr++){
					if(retorna)valorantigo[i]=*ptr;
					if(atualiza)*ptr=novovalor[i];
				}
				if(retorna)valorantigo[32]=0;
				return;
			}			
			if(ptr>=lstbd)break;
		}
	}
	else if(strcmp(campo,"ABERTURA_DIA")==0){
		while(ptr&&(ptr=inifileb_nextsection(bd,ptr,sz))!=lstbd){
			ptr=inifileb_sectiontitle(bd,ptr,sz,title);
			if(*ptr==0x0a)continue;
			if(strcmp(title,"ABERTURA_DIA")==0){
				for(i=0;i<15;i++,ptr++){
					if(retorna)valorantigo[i]=*ptr;
					if(atualiza)*ptr=novovalor[i];
				}
				if(retorna)valorantigo[15]=0;
				return;
			}			
			if(ptr>=lstbd)break;
		}
	}	
	else if(strcmp(campo,"FECHAMENTO_DIA")==0||strcmp(campo,"IMPRIMINDO")==0){
		while(ptr&&(ptr=inifileb_nextsection(bd,ptr,sz))!=lstbd){
			ptr=inifileb_sectiontitle(bd,ptr,sz,title);
			if(*ptr==0x0a)continue;
			if(strcmp(title,campo)==0){
				if(retorna)*valorantigo=*ptr;
				if(atualiza)*ptr=*novovalor;
				return;
			}			
			if(ptr>=lstbd)break;
		}
	}	
}

void RELATORIOS::requisitoXXII::restaura_arquivo_auxiliar(const char *fname){
	char buf[1024];
	sprintf(buf,
"[CNPJ]%c\
04368898000102%c\
[IE]%c\
00009023307399%c\
[IM]%c\
00000004239924%c\
[DEN]%c\
Atena3D                                 %c\
[NOME]%c\
atenaPAF                                %c\
[VERSAO]%c\
1.0.0     %c\
[ECFS]%c\
00000004708991129051 030506%c\
00000004708991129054 030507%c\
00000004708991129052 030508%c\
[MD5]%c\
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX%c\
[TOTAL_GT]%c\
XXXXXXXXXXXXXXXXXX%c\
[IMPRIMINDO]%c\
0%c\
[NOME_USER]%c\
                                        %c\
[CNPJ_USER]%c\
00000000000000%c\
[IE_USER]%c\
00000000000000%c\
[IM_USER]%c\
00000000000000%c\
[ABERTURA_DIA]%c\
AAAAMMDD HHMMSS%c\
[FECHAMENTO_DIA]%c\
0%c",
0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,
0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,
0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,0x0a,
0x0a,0x0a,0x0a,0x0a,0x0a);
	criptografa_buf(fname,buf);
}


void RELATORIOS::requisitoXXII::criptografa_buf(const char *fname,char *buf){
	char *nbuf,*ptrbuf,*lstptr;
	int buflenmod128=strlen(buf)%128,ncarpreeench,i,lenc;
	if(buflenmod128!=0)ncarpreeench=128-buflenmod128;else ncarpreeench=0;
	nbuf=new char[strlen(buf)+ncarpreeench+1];
	strcpy(nbuf,buf);
	lstptr=nbuf+strlen(nbuf);
	for(i=0,ptrbuf=lstptr;i<ncarpreeench;i++,ptrbuf++)*ptrbuf=0x0a;*ptrbuf=0x00;
	lstptr=nbuf+strlen(nbuf)-1;//novo lstptr
	unsigned char *encbuf,ubuf[128];
	FILE *fencorg=fopen(fname,"w+b");
	for (ptrbuf=nbuf;ptrbuf<lstptr;ptrbuf+=128){
		memcpy(ubuf,ptrbuf,128);
		lenc= _encrypt( ubuf,128,&encbuf);
		if(encbuf!=NULL){
			fwrite(encbuf, 1, lenc, fencorg);
			delete []encbuf;
		}
	}
	fclose(fencorg);
	delete []nbuf;
}

void RELATORIOS::requisitoXXII::criptografa_arqaux(){
	unsigned char *encbuf,ubuf[128];
	int bytes,lenc,i;
	FILE *fenc=fopen("arquivo_auxiliare.txt","w+b"),*forg=fopen("arquivo_auxiliar.txt","rb");
	while ((bytes = fread (ubuf, 1, 128, forg)) != 0){
		if(bytes<128){
			for(i=bytes;i<128;i++)
				ubuf[i]='\n';
		}
		lenc= _encrypt( ubuf,128,&encbuf);
		if(encbuf!=NULL){
			fwrite(encbuf, 1, lenc, fenc);
			delete []encbuf;
		}
	}
	fclose(fenc);
	fclose(forg);
}

int RELATORIOS::requisitoXXII::descriptografa_arquivo(const char* fname,char **dbuf){
	FILE *fenc=fopen(fname,"rb");
	unsigned char *decbuf,ubuf[128];
	char *ptrc;
	int bytes,size=0,lend;
	if(fenc!=NULL){
	fseek(fenc, 0, SEEK_END);
	size = ftell(fenc);
	fseek(fenc, 0, SEEK_SET);
	*dbuf=new char[size+1];
	ptrc=*dbuf;
 while ((bytes = fread (ubuf, 1, 128, fenc)) != 0){
		lend=_decrypt(ubuf,128,&decbuf);
		if(decbuf!=NULL){
			memcpy(ptrc,decbuf,128);
			delete []decbuf;
			ptrc+=128;
		}
	}
	(*dbuf)[size]=0;
	fclose(fenc);
	}
	return size;
}


void RELATORIOS::requisitoXXV::gravarequisitoXXV(char *Dataini,char *Datafinal,bool dataatual,const char *ecfnoserie){
	MODOTESTE();NENHUMRELATORIO();NENHUMRELATORIO();
	char fname[33];
	FILE *file;
	char Data[21]="",Hora[21]="",*lstchar,_ecfnoserie[21];
	char _Dataini[21],_Datafinal[21];
	if(Dataini)
		strcpy(_Dataini,Dataini);
	else{
		_DataMovUltRedZ(Data);		
		sprintf(_Dataini,"%08ld",formatdata(Data));
	}
	if(Datafinal)
		strcpy(_Datafinal,Datafinal);
	else{
		_DataMovUltRedZ(Data);		
		sprintf(_Datafinal,"%08ld",formatdata(Data));
	}
	if(ecfnoserie)
		strcpy(_ecfnoserie,ecfnoserie);
	else
		_NumSerieImpressora(_ecfnoserie);
	if(dataatual)_DataHoraImpressora(Data,Hora);
	else{
		_DataMovUltRedZ(Data);			
	}
	char *ptrnfabr=vilavielaframe->ecf.Numero_de_fabricacao;
	while(strlen(ptrnfabr)>14)ptrnfabr++;
	sprintf(fname,"%6s%14s%08ld.txt",vilavielaframe->ecf.CNI,ptrnfabr,formatdata2(Data));
	ptrnfabr=fname;lstchar=fname+strlen(fname);
	for(ptrnfabr;ptrnfabr!=lstchar;ptrnfabr++)
		if(*ptrnfabr==' ')*ptrnfabr='0';
	file=fopen(fname,"w+b");
	grava_registro_R01(file,_Dataini,_Datafinal);
	Palavra query;
	sql_ResultSet *res;

		query=
"SELECT * FROM r02 AS _r02  WHERE \
_r02.Data_do_movimento >= ";
	query.append(_Dataini);
	query.append(" AND _r02.Data_do_movimento <= ");
	query.append(_Datafinal);
	query.append(" AND _r02.Numero_de_fabricacao = '");query.append(_ecfnoserie);query.append("'");
	if((res=vilavielaframe->_execquerywithresult(query))!=NULL&&vilavielaframe->_nextrow(res)){
		do{
			fprintf(file,
				"R02%-20s%1s%-20s%02d%06d%06d%06d%08d%08d%06d%014d%1s%c%c",
				vilavielaframe->_getstring(res,"Numero_de_fabricacao").ToAscii().data(),
				vilavielaframe->_getstring(res,"MF_adicional").ToAscii().data(),
				vilavielaframe->_getstring(res,"vilavielaframe->ecf.Modelo_do_ECF").ToAscii().data(),
				vilavielaframe->_getint(res,"Numero_do_usuario"),
				vilavielaframe->_getint(res,"CRZ"),
				vilavielaframe->_getint(res,"COO"),
				vilavielaframe->_getint(res,"CRO"),
				vilavielaframe->_getint(res,"Data_do_movimento"),
				vilavielaframe->_getint(res,"Data_de_emissao"),
				vilavielaframe->_getint(res,"Hora_de_emissao"),
				vilavielaframe->_getint(res,"Venda_Bruta_Diaria"),
				vilavielaframe->_getstring(res,"Parametro_desconto_ISSQN").ToAscii().data(),
				0x0d,0x0a);	
		}while(vilavielaframe->_nextrow(res));
		vilavielaframe->_deleteresult(&res);
	}

		query=
"SELECT _r03.* FROM r02 AS _r02, r03 AS _r03 WHERE _r03.CRZ=_r02.CRZ AND \
_r02.Data_do_movimento >= ";
	query.append(_Dataini);
	query.append(" AND _r02.Data_do_movimento <= ");
	query.append(_Datafinal);
	query.append(" AND _r03.Numero_de_fabricacao = '");query.append(_ecfnoserie);query.append("'");
	if((res=vilavielaframe->_execquerywithresult(query))!=NULL&&vilavielaframe->_nextrow(res)){
		do{
			fprintf(file,
				"R03%-20s%1s%-20s%02d%06d%-7s%013d%c%c",
				vilavielaframe->_getstring(res,"Numero_de_fabricacao").ToAscii().data(),
				vilavielaframe->_getstring(res,"MF_adicional").ToAscii().data(),
				vilavielaframe->_getstring(res,"vilavielaframe->ecf.Modelo_do_ECF").ToAscii().data(),
				vilavielaframe->_getint(res,"Numero_do_usuario"),
				vilavielaframe->_getint(res,"CRZ"),
				vilavielaframe->_getstring(res,"Totalizador_Parcial").ToAscii().data(),
				vilavielaframe->_getint(res,"Valor_acumulado"),
				0x0d,0x0a);	
		}while(vilavielaframe->_nextrow(res));
		vilavielaframe->_deleteresult(&res);
	}

		query=
"SELECT _r04.* FROM r02 AS _r02, r04 AS _r04  WHERE _r04.Data_de_inicio_da_emissao=_r02.Data_do_movimento AND \
_r02.Data_do_movimento >= ";
	query.append(_Dataini);
	query.append(" AND _r02.Data_do_movimento <= ");
	query.append(_Datafinal);
	query.append(" AND _r04.Numero_de_fabricacao = '");query.append(_ecfnoserie);query.append("'");
	if((res=vilavielaframe->_execquerywithresult(query))!=NULL&&vilavielaframe->_nextrow(res)){
		do{		
			fprintf(file,
				"R04%-20s%1s%-20s%02d%06d%06d%08d%014d%013d%1s%013d%1s%014d%1s%013d%1s%-40s%-14s%c%c",
				vilavielaframe->_getstring(res,"Numero_de_fabricacao").ToAscii().data(),
				vilavielaframe->_getstring(res,"MF_adicional").ToAscii().data(),
				vilavielaframe->_getstring(res,"vilavielaframe->ecf.Modelo_do_ECF").ToAscii().data(),
				vilavielaframe->_getint(res,"Numero_do_usuario"),				
				vilavielaframe->_getint(res,"CCF_CVC_ou_CBP"),
				vilavielaframe->_getint(res,"COO"),
				vilavielaframe->_getint(res,"Data_de_inicio_da_emissao"),
				vilavielaframe->_getint(res,"Subtotal_do_Documento"),
				vilavielaframe->_getint(res,"Desc_sobre_subtotal"),
				vilavielaframe->_getstring(res,"Ind_do_Tipo_de_Desc_sobre_subtotal").ToAscii().data(),
				vilavielaframe->_getint(res,"Acrescimo_sobre_subtotal"),
				vilavielaframe->_getstring(res,"Ind_do_Tipo_de_Acresc_sobre_subtotal").ToAscii().data(),
				vilavielaframe->_getint(res,"Valor_Total_Liquido"),
				vilavielaframe->_getstring(res,"Ind_de_Cancelamento").ToAscii().data(),
				vilavielaframe->_getint(res,"Cancelamento_de_Acresc_no_Subtotal"),
				vilavielaframe->_getstring(res,"Ordem_de_aplicacao_de_Desc_e_Acresc").ToAscii().data(),
				vilavielaframe->_getstring(res,"Nome_do_adquirente").ToAscii().data(),
				vilavielaframe->_getstring(res,"CPF_CNPJ_do_adquirente").ToAscii().data(),
				0x0d,0x0a);	
		}while(vilavielaframe->_nextrow(res));
		vilavielaframe->_deleteresult(&res);
	}

	query=
"SELECT _r05.* FROM r02 AS _r02, r04 AS _r04, r05 AS _r05  WHERE _r04.Data_de_inicio_da_emissao=_r02.Data_do_movimento AND \
_r04.CCF_CVC_ou_CBP=_r05.CCF_CVC_ou_CBP AND \
_r02.Data_do_movimento >= ";
	query.append(_Dataini);
	query.append(" AND _r02.Data_do_movimento <= ");
	query.append(_Datafinal);
	query.append(" AND _r05.Numero_de_fabricacao = '");query.append(_ecfnoserie);query.append("'");
	if((res=vilavielaframe->_execquerywithresult(query))!=NULL&&vilavielaframe->_nextrow(res)){
		do{
			fprintf(file,
				"R05%-20s%1s%-20s%02d%06d%06d%03d%-14s%-100s%07d%-3s%08d%08d%08d%014d%-7s%1s%07d%013d%013d%1s%1s%1d%1d%c%c",
				vilavielaframe->_getstring(res,"Numero_de_fabricacao").ToAscii().data(),
				vilavielaframe->_getstring(res,"MF_adicional").ToAscii().data(),
				vilavielaframe->_getstring(res,"vilavielaframe->ecf.Modelo_do_ECF").ToAscii().data(),
				vilavielaframe->_getint(res,"Numero_do_usuario"),		
				vilavielaframe->_getint(res,"COO"),		
				vilavielaframe->_getint(res,"CCF_CVC_ou_CBP"),
				vilavielaframe->_getint(res,"Numero_do_item"),		
				vilavielaframe->_getstring(res,"Cod_do_Produto_ou_Servico").ToAscii().data(),
				vilavielaframe->_getstring(res,"Descricao").ToAscii().data(),
				vilavielaframe->_getint(res,"Quantidade"),
				vilavielaframe->_getstring(res,"Unidade").ToAscii().data(),
				vilavielaframe->_getint(res,"Valor_unitario"),
				vilavielaframe->_getint(res,"Desconto_sobre_item"),
				vilavielaframe->_getint(res,"Acrescimo_sobre_item"),
				vilavielaframe->_getint(res,"Valor_total_liquido"),
				vilavielaframe->_getstring(res,"Totalizador_parcial").ToAscii().data(),
				vilavielaframe->_getstring(res,"Indicador_de_cancelamento").ToAscii().data(),
				vilavielaframe->_getint(res,"Quantidade_cancelada"),
				vilavielaframe->_getint(res,"Valor_cancelado"),
				vilavielaframe->_getint(res,"Cancelamento_de_acrescimo_no_item"),
				vilavielaframe->_getstring(res,"IAT").ToAscii().data(),
				vilavielaframe->_getstring(res,"IPPT").ToAscii().data(),
				vilavielaframe->_getint(res,"Casas_decimais_da_quantidade"),
				vilavielaframe->_getint(res,"Casas_decimais_de_valor_unitario"),
				0x0d,0x0a);	
		}while(vilavielaframe->_nextrow(res));
		vilavielaframe->_deleteresult(&res);
	}

	query=
"SELECT * FROM r06  WHERE \
Data_final_de_emissao >= ";
	query.append(_Dataini);
	query.append(" AND Data_final_de_emissao <= ");
	query.append(_Datafinal);
	query.append(" AND Numero_de_fabricacao = '");query.append(_ecfnoserie);query.append("'");
	if((res=vilavielaframe->_execquerywithresult(query))!=NULL&&vilavielaframe->_nextrow(res)){
		do{
			fprintf(file,
				"R06%-20s%1s%-20s%02d%06d%06d%06d%04d%-2s%08d%06d%c%c",
				vilavielaframe->_getstring(res,"Numero_de_fabricacao").ToAscii().data(),
				vilavielaframe->_getstring(res,"MF_adicional").ToAscii().data(),
				vilavielaframe->_getstring(res,"vilavielaframe->ecf.Modelo_do_ECF").ToAscii().data(),
				vilavielaframe->_getint(res,"Numero_do_usuario"),		
				vilavielaframe->_getint(res,"COO"),		
				vilavielaframe->_getint(res,"GNF"),
				vilavielaframe->_getint(res,"CRG"),	
				vilavielaframe->_getint(res,"CDC"),	
				vilavielaframe->_getstring(res,"Denominacao").ToAscii().data(),
				vilavielaframe->_getint(res,"Data_final_de_emissao"),
				vilavielaframe->_getint(res,"Hora_final_de_emissao"),
				0x0d,0x0a);	
		}while(vilavielaframe->_nextrow(res));
		vilavielaframe->_deleteresult(&res);
	}

	query=
"SELECT _r07.* FROM r04 AS _r04,r07 AS _r07  WHERE _r07.COO=_r04.COO AND \
_r04.Data_de_inicio_da_emissao >= ";
	query.append(_Dataini);
	query.append(" AND _r04.Data_de_inicio_da_emissao <= ");
	query.append(_Datafinal);
	query.append(" AND _r07.Numero_de_fabricacao = '");query.append(_ecfnoserie);query.append("'");
	if((res=vilavielaframe->_execquerywithresult(query))!=NULL&&vilavielaframe->_nextrow(res)){
		do{
			fprintf(file,
				"R07%-20s%1s%-20s%02d%06d%06d%06d%-15s%013d%1s%013d%c%c",
				vilavielaframe->_getstring(res,"Numero_de_fabricacao").ToAscii().data(),
				vilavielaframe->_getstring(res,"MF_adicional").ToAscii().data(),
				vilavielaframe->_getstring(res,"vilavielaframe->ecf.Modelo_do_ECF").ToAscii().data(),
				vilavielaframe->_getint(res,"Numero_do_usuario"),		
				vilavielaframe->_getint(res,"COO"),		
				vilavielaframe->_getint(res,"CCF"),
				vilavielaframe->_getint(res,"GNF"),	
				vilavielaframe->_getstring(res,"Meio_de_pagamento").ToAscii().data(),
				vilavielaframe->_getint(res,"Valor_pago"),
				vilavielaframe->_getstring(res,"Indicador_de_estorno").ToAscii().data(),
				vilavielaframe->_getint(res,"Valor_estornado"),
				0x0d,0x0a);	
		}while(vilavielaframe->_nextrow(res));
		vilavielaframe->_deleteresult(&res);
	}

		query=
"SELECT _r07.* FROM r06 AS _r06,r07 AS _r07  WHERE _r07.COO=_r06.COO AND \
_r06.Data_final_de_emissao >= ";
	query.append(_Dataini);
	query.append(" AND _r06.Data_final_de_emissao <= ");
	query.append(_Datafinal);
	query.append(" AND _r07.Numero_de_fabricacao = '");query.append(_ecfnoserie);query.append("'");
	if((res=vilavielaframe->_execquerywithresult(query))!=NULL&&vilavielaframe->_nextrow(res)){
		do{
			fprintf(file,
				"R07%-20s%1s%-20s%02d%06d%06d%06d%-15s%013d%1s%013d%c%c",
				vilavielaframe->_getstring(res,"Numero_de_fabricacao").ToAscii().data(),
				vilavielaframe->_getstring(res,"MF_adicional").ToAscii().data(),
				vilavielaframe->_getstring(res,"vilavielaframe->ecf.Modelo_do_ECF").ToAscii().data(),
				vilavielaframe->_getint(res,"Numero_do_usuario"),		
				vilavielaframe->_getint(res,"COO"),		
				vilavielaframe->_getint(res,"CCF"),
				vilavielaframe->_getint(res,"GNF"),	
				vilavielaframe->_getstring(res,"Meio_de_pagamento").ToAscii().data(),
				vilavielaframe->_getint(res,"Valor_pago"),
				vilavielaframe->_getstring(res,"Indicador_de_estorno").ToAscii().data(),
				vilavielaframe->_getint(res,"Valor_estornado"),
				0x0d,0x0a);	
		}while(vilavielaframe->_nextrow(res));
		vilavielaframe->_deleteresult(&res);
	}
	fclose(file);
	
	sign_file(fname);
	mostralocalgravacaoarquivos(fname);
}


void RELATORIOS::requisitoXX::gravarequisitoXX(){
	FILE *file;
	//setlocale(LC_ALL, "pt_BR.ISO-8859-1");
#define requisitoXX_txt "requisitoXX.txt"
	file=fopen(requisitoXX_txt,"w+b");
	wxString nome(wxString::FromUTF8(vilavielaframe->NOME_USER));
	
	fprintf(file,
		"P1%14s%-14s%-14s%-50s\x0d\x0a",
		vilavielaframe->CNPJ_USER,vilavielaframe->IE_USER,vilavielaframe->IM_USER,nome.mb_str(wxConvISO8859_1).data());
	Palavra query;
	sql_ResultSet *res;
	char sit_trib[2]={0,0},abrevaliq[16],aliquota[5];
	double valunit;
	query="SELECT prod.barcode,prod.nome,unid.abrev,prod.iat,prod.ippt,aliq.abrev,prod.val_unit_venda \
	FROM produtos AS prod, unidade AS unid,aliquotas AS aliq \
	WHERE unid.idunidade=prod.idunidade AND aliq.idaliquota=prod.idaliquota \
	ORDER BY prod.barcode";
	int numP2=0;
	
	if((res=vilavielaframe->_execquerywithresult(query))!=NULL && vilavielaframe->_nextrow(res)){
		do{
			numP2++;
			valunit=vilavielaframe->_getdouble(res,7)*100.0;
			strcpy(abrevaliq,vilavielaframe->_getstringSQL(res,6).c_str());
			if(*abrevaliq=='I')*sit_trib='I';
			else if(*abrevaliq=='N')*sit_trib='N';
			else if(*abrevaliq=='F')*sit_trib='F';
			else *sit_trib='T';
			if(*sit_trib=='T')strcpy(aliquota,abrevaliq);
			else strcpy(aliquota,"0000");
			fprintf(file,
				"P2%14s%-14s%-50s%-6s%1s%1s%1s%4s%012d\x0d\x0a",
				vilavielaframe->CNPJ_USER,
				vilavielaframe->_getstringSQL(res,1).c_str(),
				vilavielaframe->_getstring(res,2).mb_str(wxConvISO8859_1).data(),
				vilavielaframe->_getstringSQL(res,3).c_str(),
				vilavielaframe->_getstringSQL(res,4).c_str(),
				vilavielaframe->_getstringSQL(res,5).c_str(),
				sit_trib,aliquota,(int)valunit
			);
		}while(vilavielaframe->_nextrow(res));
		vilavielaframe->_deleteresult(&res);
	}
	fprintf(file,
		"P9%14s%-14s%06d\x0d\x0a",
		vilavielaframe->CNPJ_USER,vilavielaframe->IE_USER,numP2);
	fclose(file);
 sign_file(requisitoXX_txt);
	mostralocalgravacaoarquivos(requisitoXX_txt);
}

void RELATORIOS::requisitoVII_8::estoquetotal(){
	#define requisitoVII_8_TOTAL_txt "requisitoVII_8_TOTAL.txt"	
	FILE *file=fopen(requisitoVII_8_TOTAL_txt,"w+b");
	wxString nome(wxString::FromUTF8(vilavielaframe->NOME_USER));		
	fprintf(file,
		"E1%14s%-14s%-14s%-50s%-20s%1s%-7s%-20s%-20s%8s%6s\x0d\x0a",
		vilavielaframe->CNPJ_USER,vilavielaframe->IE_USER,vilavielaframe->IM_USER,nome.mb_str(wxConvISO8859_1).data(),
									vilavielaframe->ecf.Numero_de_fabricacao,vilavielaframe->ecf.MF_adicional,vilavielaframe->ecf.tipo_ECF,vilavielaframe->ecf.Marca_ECF,vilavielaframe->ecf.Modelo_do_ECF,vilavielaframe->data_abertura_dia,vilavielaframe->hora_abertura_dia);
	Palavra query;
	sql_ResultSet  *res;
	double quantestoque;int iestoque;
	query="SELECT prod.idproduto,prod.barcode,prod.nome,unid.abrev		FROM unidade AS unid,produtos AS prod		WHERE unid.idunidade=prod.idunidade		ORDER BY prod.barcode";
	int i=0;
	if ((res=vilavielaframe->_execquerywithresult(query)) !=0) {		
		while (vilavielaframe->_nextrow(res)) {
			quantestoque=vilavielaframe->_retorna_estoque(vilavielaframe->_getint(res,1));
			iestoque=fabs(quantestoque)*1000.0;
			fprintf(file,
				"E2%14s%-14s%-50s%-6s%c%09d\x0d\x0a",
				vilavielaframe->CNPJ_USER,vilavielaframe->_getstringSQL(res,2).c_str(),vilavielaframe->_getstring(res,3).mb_str(wxConvISO8859_1).data(),
				vilavielaframe->_getstringSQL(res,4).c_str(),quantestoque>0?'+':'-',iestoque);
			i++;
		}		
		vilavielaframe->_deleteresult(&res);
	}
	fprintf(file,
		"E9%14s%-14s%06d\x0d\x0a",
		vilavielaframe->CNPJ_USER,vilavielaframe->IE_USER,i);
	fclose(file);
	sign_file(requisitoVII_8_TOTAL_txt);
	mostralocalgravacaoarquivos(requisitoVII_8_TOTAL_txt);
}

void RELATORIOS::requisitoXXV::grava_registro_R01(FILE *file,char *Dataini,char *Datafinal){
	char CNPJSH[21]="",IESH[21]="",IMSH[21]="",DENSH[41]="",NOMEPAF[41]="",VERSAOPAF[11]="",MD5LSTARQ[33]="";
	char *bd;
	int sz=descriptografa_arquivo("arquivo_auxiliare.txt",&bd);	
	_atualiza_dados_impressora(false,false);
	atualiza_arquivo_auxiliar("CNPJ",bd,sz,NULL,CNPJSH,false,true);
	atualiza_arquivo_auxiliar("IE",bd,sz,NULL,IESH,false,true);
	atualiza_arquivo_auxiliar("IM",bd,sz,NULL,IMSH,false,true);
	atualiza_arquivo_auxiliar("DEN",bd,sz,NULL,DENSH,false,true);
	atualiza_arquivo_auxiliar("NOME",bd,sz,NULL,NOMEPAF,false,true);
	atualiza_arquivo_auxiliar("MD5",bd,sz,NULL,MD5LSTARQ,false,true);
	atualiza_arquivo_auxiliar("VERSAO",bd,sz,NULL,VERSAOPAF,false,true);
	fprintf(file,
		"R01%-20s%1s%-7s%-20s%-20s%-10s%08d%06d%03d%14s%-14s%-14s%-14s%-14s%-40s%-40s%-10s%-32s%8s%8s0111%c%c",
		vilavielaframe->ecf.Numero_de_fabricacao,
		vilavielaframe->ecf.MF_adicional,
		vilavielaframe->ecf.tipo_ECF,
		vilavielaframe->ecf.Marca_ECF,
		vilavielaframe->ecf.Modelo_do_ECF,
		vilavielaframe->ecf.versao_SB,
		atoi(vilavielaframe->ecf.dataSWBasico),
		atoi(vilavielaframe->ecf.horaSWBasico),
		atoi(vilavielaframe->ecf.NumeroCaixa),
		vilavielaframe->ecf.CNPJUSUARIO,
		vilavielaframe->ecf.IEUSUARIO,
		CNPJSH,
		IESH,
		IMSH,
		DENSH,
		NOMEPAF,
		VERSAOPAF,
		MD5LSTARQ,
		Dataini,
		Datafinal,0x0d,0x0a);	
	delete []bd;
}

void RELATORIOS::requisitoXXV::registro_R02_R03(){
	MODOTESTE() ;NENHUMRELATORIO();NENHUMRELATORIO();
	int Retorno,size;	
	char *dadosultredZ,CRZ[16],COO[16]="0",CRO[16]="0",Data_de_emissao[16]="",Hora_de_emissao[16]="",Parametro_desconto_ISSQN[2]="S",
		DadosReducao[1279]="",Data_do_movimento[16]="",VendaBruta[19]="",buf[256];
	_atualiza_dados_impressora(false);
 INIT_PROGRESS_INFO("registros R02 e R03","criando registros R02 e R03",13,vilavielaframe);
	UPDATE_PROGRESS(4,"obtendo dados redução Z");
	Retorno=_DadosUltRedZ(&dadosultredZ,&size);
	UPDATE_PROGRESS(5,"obtendo CRZ");
	_retornasDadoUltRedZ(dadosultredZ,size,REDZ_CRZ,CRZ);
	
	sql_ResultSet *res,*res2;	
	Palavra query;
	query="SELECT * FROM r02 WHERE CRZ=";
	query.append(CRZ);
	if((res=vilavielaframe->_execquerywithresult(query))==NULL||!vilavielaframe->_nextrow(res)){	
		
		UPDATE_PROGRESS(6,"obtendo COO");
		_retornasDadoUltRedZ(dadosultredZ,size,REDZ_COO,COO);
		UPDATE_PROGRESS(7,"obtendo VendaBruta");
		_retornasDadoUltRedZ(dadosultredZ,size,REDZ_TOTALBRUTO,VendaBruta);
		ListTotalizadorParcial2 lsttotpar;
		_retornasDadoUltRedZ(dadosultredZ,size,REDZ_TOTALIZADORES_PARCIAIS,DadosReducao,&lsttotpar);
		UPDATE_PROGRESS(8,"obtendo data e hora da emissão");
		Retorno=_dataehoraEmissaoRZ(Data_de_emissao, Hora_de_emissao);
		transformadataparaFormatoCotepe(Data_de_emissao);
		UPDATE_PROGRESS(9,"obtendo data movimento");
		_DataMovUltRedZ(Data_do_movimento);

		if(size>0)free(dadosultredZ);
		UPDATE_PROGRESS(10,"obtendo CRO");
		Retorno=_DadosUltRedZ(&dadosultredZ,&size,true,Data_do_movimento);
		if(Retorno==1)
			_retornasDadoUltRedZ(dadosultredZ,size,REDZ_CRO,CRO);		
		transformadataparaFormatoCotepe(Data_do_movimento);
		UPDATE_PROGRESS(11,"criando registro R02");
		query="INSERT INTO r02(Numero_de_fabricacao,MF_adicional,Modelo_do_ECF,Numero_do_usuario,CRZ,COO,CRO,\
								Data_do_movimento,Data_de_emissao,Hora_de_emissao,Venda_Bruta_Diaria,Parametro_desconto_ISSQN) VALUES('";
		query.append(vilavielaframe->ecf.Numero_de_fabricacao);query.append("','");
		query.append(vilavielaframe->ecf.MF_adicional);query.append("','");
		query.append(vilavielaframe->ecf.Modelo_do_ECF);query.append("',");
		query.append(vilavielaframe->ecf.Numero_do_usuario);query.append(",");
		query.append(CRZ);query.append(",");
		query.append(COO);query.append(",");
		query.append(CRO);query.append(",");
		query.append(Data_do_movimento);query.append(",");
		query.append(Data_de_emissao);query.append(",");
		query.append(Hora_de_emissao);query.append(",");
		query.append(VendaBruta);query.append(",'");
		query.append(Parametro_desconto_ISSQN);
		query.append("')");
		vilavielaframe->_execquery(query);

		UPDATE_PROGRESS(12,"criando registro R03");
		free(dadosultredZ);
		clTotalizadorParcial* tp;
		query="SELECT * FROM r03 WHERE CRZ=";
		query.append(CRZ);
		if((res2=vilavielaframe->_execquerywithresult(query))==NULL||!vilavielaframe->_nextrow(res2)){	
			for(tp=lsttotpar.prm;tp;tp=tp->prx){
				query="INSERT INTO r03(Numero_de_fabricacao,MF_adicional,Modelo_do_ECF,Numero_do_usuario,CRZ,Totalizador_Parcial,Valor_acumulado) VALUES('";
				query.append(vilavielaframe->ecf.Numero_de_fabricacao);query.append("','");
				query.append(vilavielaframe->ecf.MF_adicional);query.append("','");
				query.append(vilavielaframe->ecf.Modelo_do_ECF);query.append("',");
				query.append(vilavielaframe->ecf.Numero_do_usuario);query.append(",");
				query.append(CRZ);query.append(",'");
				query.append(tp->abrev);query.append("',");
				sprintf(buf,"%d",tp->valacumulado);
				query.append(buf);
				query.append(")");
				vilavielaframe->_execquery(query);		
			}
		}
		else
			vilavielaframe->_deleteresult(&res2);

		gravarequisitoXXV(NULL,NULL,false,NULL);
	}
	else 
		vilavielaframe->_deleteresult(&res);
	
	UPDATE_PROGRESS(13,"operação concluída");
}

void RELATORIOS::atoCOTEP1704::criaregistroE01(ListRedZ *lstredz,FILE *MF,const char *arqmemfiscal){		
	FILE *LMFC=fopen(arqmemfiscal,"rb");
	char TMPSTR[256];
	int Numero_Sequencial_do_ECF=1;
	Numero_Sequencial_do_ECF=atoi(vilavielaframe->ecf.NumeroCaixa);	
	skipsection(LMFC);//--------------REINÍCIO DE OPERAÇÃO--------------
	fscanf(LMFC,"%s",TMPSTR);//printf("\n%s\n",TMPSTR);
	skipsection(LMFC);//--------------------USUÁRIOS--------------------
	fscanf(LMFC,"%s",TMPSTR);//printf("\n%s\n",TMPSTR);
	skipsection(LMFC);//----------------REDUÇÕES DIÁRIAS----------------
	fscanf(LMFC,"%s",TMPSTR);//printf("\n%s\n",TMPSTR);
	skipline(LMFC);	
	fscanf(LMFC,"%s",TMPSTR);//printf("\n%s\n",TMPSTR);
	while(strcmp(TMPSTR,"Modo")==0){ 
		fscanf(LMFC,"%s",TMPSTR);//printf("\n%s\n",TMPSTR);
		fscanf(LMFC,"%s",TMPSTR);//printf("\n%s\n",TMPSTR);
		fscanf(LMFC,"%s",TMPSTR);//printf("\n%s\n",TMPSTR);
		char Numero_do_usuario[5],ctot[16],vtot[16];
		strncpy(Numero_do_usuario,TMPSTR+9,4);//printf("\n%04d\n",atoi(Numero_do_usuario));
		skipsection(LMFC);			//printf("tr=%s",TMPSTR);
		skipline(LMFC);
		int numero_usuario=atoi(vilavielaframe->ecf.Numero_do_usuario),crz,cro,hora,vendabruta,total;
		long data;
		char car;

		do{
			fscanf(LMFC,"%s",TMPSTR);//printf("tr=%s",TMPSTR);
			if(*TMPSTR=='*'){
				total=0;break;
			}
			else if(strcmp(TMPSTR,"Total")!=0){
				crz=atoi(TMPSTR);
				fscanf(LMFC,"%s",TMPSTR);
				cro=atoi(TMPSTR);

				fscanf(LMFC,"%s",TMPSTR);
				data=formatdata(TMPSTR);

				fscanf(LMFC,"%s",TMPSTR);
				removechar(TMPSTR,':');
				hora=atoi(TMPSTR)*100;
				fscanf(LMFC,"%s",TMPSTR);
				removechar(TMPSTR,',');removechar(TMPSTR,'.');
				vendabruta=atoi(TMPSTR);
				lstredz->novo(numero_usuario,crz,cro,data,hora,vendabruta);
				//agora analisa totalizadores
				skipline(LMFC); 
				ctot[0]=fgetc(LMFC);
				if(*ctot!=0x0d&&*ctot!=0x0a){				
					do{
						int index=1;
						do{
							ctot[index]=fgetc(LMFC);index++;
						}while(ctot[index-1]!='=');
						ctot[index-1]=0;
						removechar(ctot,',');	removechar(ctot,'%');	
						if(strcmp(ctot,"c")==0)strcpy(ctot,"Can-T");
						else if(strcmp(ctot,"d")==0)strcpy(ctot,"DT");
						else if(strcmp(ctot,"I")==0)strcpy(ctot,"I1");
						int indexv=0;
						do{
							vtot[indexv]=fgetc(LMFC);
							if(vtot[indexv]!=0x0d&&vtot[indexv]!=0x0a)
								indexv++;
						}while(vtot[indexv-1]!=' ');
						vtot[indexv-1]=0;
						removechar(vtot,',');				
						lstredz->ult->totalizadores.novo(ctot,atoi(vtot));
						ctot[0]=fgetc(LMFC);
						if(*ctot==0x0d){
							ctot[0]=fgetc(LMFC);ctot[0]=fgetc(LMFC);
							if(*ctot==0x0d||*ctot==0x0a)break;
						}
						else if(*ctot==0x0a){
							ctot[0]=fgetc(LMFC);
							if(*ctot==0x0d||*ctot==0x0a)break;
						}

					}while(1);
					fseek(LMFC,-2,SEEK_CUR);
					//ctot=fgetc(LMFC);
					//printf("prox 2 char depois vendabruta=%c\n",((int)ctot)&0xff);
				}
				//printf("%04d %04d %04d %8d %6d %d\n",numero_usuario,crz,cro,data,hora,vendabruta);
			}
			else{
				fscanf(LMFC,"%s",TMPSTR);fscanf(LMFC,"%s",TMPSTR);fscanf(LMFC,"%s",TMPSTR);
				removechar(TMPSTR,'.');removechar(TMPSTR,',');
				total=atoi(TMPSTR);
				//	printf("total=%d\n\n",total);
			}
			do{				
				skipline(LMFC); 
				fscanf(LMFC,"%c",&car);//printf("\n%02x",car);
				fscanf(LMFC,"%c",&car);//printf("%02x\n",car);
			}while(car!=0x0a&&car!='-');
			if(car=='-')break;
		}while(*TMPSTR!='-');
		skipline(LMFC);	
		fscanf(LMFC,"%s",TMPSTR);
	}
	RedZ *redzini=lstredz->ult,*redzfim=lstredz->prm;
	fprintf(MF,"E01%-20s%s%-7s%-20s%-20sVER%c%c.%c%c  %8s%6s%03d%14sMF %06d%06d%08ld%08ld%-8sAC1704 01.00.00%c%c",
		vilavielaframe->ecf.Numero_de_fabricacao,vilavielaframe->ecf.MF_adicional,vilavielaframe->ecf.tipo_ECF,vilavielaframe->ecf.Marca_ECF,vilavielaframe->ecf.Modelo_do_ECF,
		*vilavielaframe->ecf.versao_SB,*(vilavielaframe->ecf.versao_SB+1),*(vilavielaframe->ecf.versao_SB+2),*(vilavielaframe->ecf.versao_SB+3),
		vilavielaframe->ecf.dataSWBasico,vilavielaframe->ecf.horaSWBasico,Numero_Sequencial_do_ECF,
		vilavielaframe->ecf.CNPJUSUARIO,redzini?redzini->crz:0,redzfim?redzfim->crz:0,redzini?redzini->data:0,redzfim?redzfim->data:0,vilavielaframe->ecf.Versao_da_biblioteca,0x0d,0x0a
		);				
	fclose(LMFC);			
}

void RELATORIOS::atoCOTEP1704::criaregistroE02(FILE *MF,const char *arqmemfiscal){
	FILE *LMFC=fopen(arqmemfiscal,"rb");
	char TMPSTR[256]="";
	int nosubst;
	nosubst=atoi(vilavielaframe->ecf.NoSubstProp);	
	skipsection(LMFC);
	fscanf(LMFC,"%s",TMPSTR);//REINICIO DE OPERACAO			
	char *nousr=TMPSTR+9;
	skipsection(LMFC);//USUARIOS
	int HORA,CRO,GT;			
	long	DATA;
	for(int i=0;i<nosubst;i++){
		//printf("\n%d\n",i);
		skipline(LMFC);			
		fscanf(LMFC,"%s",TMPSTR);//printf("\n%s\n",nousr);
		if(atoi(nousr)==nosubst){//encontrou ok
			fscanf(LMFC,"%s",TMPSTR);CRO=atoi(TMPSTR+4);//CRO printf("\n%s\n",TMPSTR+4);
			fscanf(LMFC,"%s",TMPSTR);//DATA printf("\n%s\n",TMPSTR);
			DATA=formatdata(TMPSTR);
			fscanf(LMFC,"%s",TMPSTR);//HORA printf("\n%s\n",TMPSTR);
			removechar(TMPSTR,':');
			HORA=atoi(TMPSTR)*100;
			skipline(LMFC);		
			fscanf(LMFC,"%s",TMPSTR);//printf("\n%s\n",TMPSTR);
			skipline(LMFC);		
			fscanf(LMFC,"%s",TMPSTR);//printf("\n%s",TMPSTR);
			fscanf(LMFC,"%s",TMPSTR);//GT printf(" %s\n",TMPSTR);
			removechar(TMPSTR,'.');removechar(TMPSTR,',');
			GT=atoi(TMPSTR);
			break;
		}
		skipline(LMFC);			
		skipline(LMFC);			
		fscanf(LMFC,"%s",TMPSTR);
		if(strcmp(TMPSTR,"IM:")==0)
			skipline(LMFC);			
	}			
	skipsection(LMFC);
	fscanf(LMFC,"%s",TMPSTR);//REDUCOES DIARIAS
	skipline(LMFC);	
	fscanf(LMFC,"%s",TMPSTR);//printf("\n%s\n",TMPSTR);			
	fprintf(MF,"E02%-20s%s%-20s%14s%-14s%-40s",	vilavielaframe->ecf.Numero_de_fabricacao,vilavielaframe->ecf.MF_adicional,vilavielaframe->ecf.Modelo_do_ECF,vilavielaframe->ecf.CNPJUSUARIO,vilavielaframe->ecf.IEUSUARIO,vilavielaframe->ecf.Nome_do_contribuinte);			
	fprintf(MF,"%-120s%08ld%06d%06d%018d%02d%c%c",vilavielaframe->ecf.Endereco,DATA,HORA,CRO,GT,nosubst,0x0d,0x0a);				
	fclose(LMFC);
}

void RELATORIOS::atoCOTEP1704::criaregistroE04(FILE *MF,const char *arqmemfiscal){
	FILE *LMFC=fopen(arqmemfiscal,"rb");
	char TMPSTR[256]="",CNPJUSUARIO[32],IEUSUARIO[32];	
	int nosubst;	
	nosubst=atoi(vilavielaframe->ecf.NoSubstProp);	
	skipsection(LMFC);
	fscanf(LMFC,"%s",TMPSTR);//REINICIO DE OPERACAO			
	char *nousr=TMPSTR+9;
	skipsection(LMFC);//USUARIOS
	int HORA,CRO,GT,i;			long DATA	;
	for(i=0;i<nosubst-1;i++){
		//printf("\n%d\n",i);
		skipline(LMFC);	
		fscanf(LMFC,"%s",TMPSTR);
		fscanf(LMFC,"%s",TMPSTR);CRO=atoi(TMPSTR+4);//CRO printf("\n%s\n",TMPSTR+4);
		fscanf(LMFC,"%s",TMPSTR); //printf("\n%s\n",TMPSTR);
		DATA=formatdata(TMPSTR);
		fscanf(LMFC,"%s",TMPSTR);//HORA printf("\n%s\n",TMPSTR);
		removechar(TMPSTR,':');
		HORA=atoi(TMPSTR)*100;
		skipline(LMFC);		
		fscanf(LMFC,"%s",TMPSTR);//printf("\n%s\n",TMPSTR);
		fscanf(LMFC,"%s",CNPJUSUARIO);//CNPJ
		if(strcmp(CNPJUSUARIO,"MODO")==0)strcpy(CNPJUSUARIO,"00000000000000");
		else{
			removechar(CNPJUSUARIO,'.');
			removechar(CNPJUSUARIO,'/');
			removechar(CNPJUSUARIO,'-');	}

		fscanf(LMFC,"%s",TMPSTR);
		if(strcmp(TMPSTR,"TREINAMENTO")==0)fscanf(LMFC,"%s",TMPSTR);
		fscanf(LMFC,"%s",IEUSUARIO);//IE
		removechar(IEUSUARIO,'.');
		removechar(IEUSUARIO,'/');
		removechar(IEUSUARIO,'-');	
  if(*IEUSUARIO=='X')strcpy(IEUSUARIO,"              ");
		skipline(LMFC);		
		fscanf(LMFC,"%s",TMPSTR);
		if(strcmp(TMPSTR,"IM:")==0){
			skipline(LMFC);		
			fscanf(LMFC,"%s",TMPSTR);//printf("\n%s",TMPSTR);
		}
		fscanf(LMFC,"%s",TMPSTR);//printf(" %s\n",TMPSTR);
		removechar(TMPSTR,'.');removechar(TMPSTR,',');
		GT=atoi(TMPSTR);    	
		fprintf(MF,"E04%-20s%s%-20s%02d%08ld%06d%14s%-14s%06d%018d%c%c",vilavielaframe->ecf.Numero_de_fabricacao,vilavielaframe->ecf.MF_adicional,vilavielaframe->ecf.Modelo_do_ECF,i+1,DATA,HORA,CNPJUSUARIO,IEUSUARIO,CRO,GT,0x0d,0x0a);
	}				
	fclose(LMFC);
}

void RELATORIOS::atoCOTEP1704::criaregistroE09(FILE *MF,const char *arqmemfiscal){
	FILE *LMFC=fopen(arqmemfiscal,"rb");
	char TMPSTR[256]="";		
	skipsection(LMFC);		
	fscanf(LMFC,"%s",TMPSTR);//REINICIO DE OPERACAO						
	skipline(LMFC);skipline(LMFC);

	int CRO,HORA;long DATA;
	while((fscanf(LMFC,"%s",TMPSTR)!=EOF)&&*TMPSTR!='-'){
		CRO=atoi(TMPSTR);
		fscanf(LMFC,"%s",TMPSTR);
		DATA=formatdata(TMPSTR);
		fscanf(LMFC,"%s",TMPSTR);
		removechar(TMPSTR,':');
		HORA=atoi(TMPSTR)*100;
		fprintf(MF,"E09%-20s%s%-20s%06d%08ld%06dN%c%c",vilavielaframe->ecf.Numero_de_fabricacao,vilavielaframe->ecf.MF_adicional,vilavielaframe->ecf.Modelo_do_ECF,CRO,DATA,HORA,0x0d,0x0a);
	}
	fclose(LMFC);
}

void RELATORIOS::utils::getdateandhourcotepe(wxDateTime &dt,char *data,char *hora){
	long ldata,lhora;
	ldata=dt.GetYear()*10000+((int)dt.GetMonth()+1)*100+dt.GetDay();
	lhora=dt.GetHour()*10000+dt.GetMinute()*100+dt.GetSecond();
	sprintf(data,"%08ld",ldata);
	sprintf(hora,"%06ld",lhora);
}

void RELATORIOS::atoCOTEP1704::criaregistroE11(FILE *MF,const char *arqmemfiscal){
	FILE *LMFC=fopen(arqmemfiscal,"rb");
	char TMPSTR[256]="";	
	int CRZ,CRO,COO=0,GNF=0,CCF=0,CVC=0,CBP=0,GRG=0,CMV=0,CFD=0,GT;
	char Data_da_captura[9],Hora_da_captura[7];
	_GrandeTotal(TMPSTR);removechar(TMPSTR,',');removechar(TMPSTR,'.');GT=atoi(TMPSTR);
	_NumeroReducoes(TMPSTR);CRZ=atoi(TMPSTR);
	_NumeroIntervencoes(TMPSTR);CRO=atoi(TMPSTR);
	wxDateTime dt=wxDateTime::Now();
	getdateandhourcotepe(dt,Data_da_captura,Hora_da_captura);
	skipsection(LMFC);		
	fscanf(LMFC,"%s",TMPSTR);//REINICIO DE OPERACAO						
	skipline(LMFC);skipline(LMFC);

	fprintf(MF,"E11%-20s%s%-20s%06d%06d%06d%06d%06d%06d%06d%06d%06d%06d%018d%8s%6s\x0d\x0a",vilavielaframe->ecf.Numero_de_fabricacao,vilavielaframe->ecf.MF_adicional,vilavielaframe->ecf.Modelo_do_ECF,
		CRZ,CRO,COO,GNF,CCF,CVC,CBP,GRG,CMV,CFD,GT,Data_da_captura,Hora_da_captura);

	fclose(LMFC);
}


void RELATORIOS::atoCOTEP1704::criaregistroE12(FILE *MF,const char *arqmemfiscal,ListRedZ *lstredz){
	FILE *LMFC=fopen(arqmemfiscal,"rb");
	char TMPSTR[256]="";
	RedZ *rz;
	for(rz=lstredz->ult;rz;rz=rz->ant)
		fprintf(MF,"E12%-20s%s%-20s%02d%06d%06d%06d%8s%08ld%06d%014dS%c%c",vilavielaframe->ecf.Numero_de_fabricacao,vilavielaframe->ecf.MF_adicional,vilavielaframe->ecf.Modelo_do_ECF,
		rz->nouser,rz->crz,0/*COO*/,rz->cro,""/*Data do movimento*/,rz->data,rz->hora,rz->vendabrutadiaria,0x0d,0x0a);
	TotalizadorParcial *tp;
	for(rz=lstredz->ult;rz;rz=rz->ant){
		for(tp=rz->totalizadores.prm;tp;tp=tp->prx){
			fprintf(MF,"E13%-20s%s%-20s%02d%06d%-7s%013d%c%c",vilavielaframe->ecf.Numero_de_fabricacao,vilavielaframe->ecf.MF_adicional,vilavielaframe->ecf.Modelo_do_ECF,
				rz->nouser,rz->crz,tp->codigo,tp->Valor_acumulado,0x0d,0x0a);
		}

	}
	fclose(LMFC);
}

void RELATORIOS::utils::mostralocalgravacaoarquivos(const char *fname,char *_dir){
	wxString str,path,dir,fn=wxString::FromAscii(fname);
	if(_dir!=NULL)dir=wxString::FromAscii(_dir);
	else dir=wxGetCwd();
	dir.Replace(_("\\"),_("/"));
	path=dir+_("/")+fn;
	str=_("arquivo salvo como:\n")+path;
	str.Append(_("\nclique Sim para visualizar."));
	wxMessageDialog dialog( NULL, str,___("Localização do arquivo"),wxYES_NO|wxYES_DEFAULT|wxICON_INFORMATION);
	switch ( dialog.ShowModal() )
	{
	case wxID_YES:
		wxLaunchDefaultBrowser(path);
		break;
	}
}

void RELATORIOS::atoCOTEP1704::cria_relatorio_atoCOTEP1704(const char *arqmemfiscal){
	char fnameCotep1704[64];
	ListRedZ lstredz;
	mountcotepefname("MF",fnameCotep1704);	
	FILE *MF=fopen(fnameCotep1704,"w+b");
	criaregistroE01(&lstredz,MF,arqmemfiscal);
	criaregistroE02(MF,arqmemfiscal);
	criaregistroE04(MF,arqmemfiscal);
	criaregistroE09(MF,arqmemfiscal);
	criaregistroE11(MF,arqmemfiscal);
	criaregistroE12(MF,arqmemfiscal,&lstredz);
	fclose(MF);		
	sign_file(fnameCotep1704);
	mostralocalgravacaoarquivos(fnameCotep1704);
}
