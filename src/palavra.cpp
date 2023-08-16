#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include "palavra.h"

	Palavra::Palavra(char *conteudo){
			if(conteudo==0){cstr=0;return;}
			cstr=new char[n_strlen(conteudo)+1];
			strcpy(cstr,conteudo);
		}

Palavra& Palavra::operator +(Palavra &p2)
{
	Palavra tmp;
	tmp=*this;
	apagaezera();
	cstr=new char[n_strlen(tmp.cstr)+n_strlen(p2.cstr)+1];
	strcpy(cstr,tmp.cstr);
	strcat(cstr,p2.cstr);
	return(*this);
}

Palavra& Palavra::operator +(char *c){ 
 Palavra tmp;
	tmp=*this;
	apagaezera();
	cstr=new char[tmp.cstr==0?n_strlen(c)+1:n_strlen(tmp.cstr)+n_strlen(c)+1];
	if(tmp.cstr&&*tmp.cstr!=0){
	strcpy(cstr,tmp.cstr);
	strcat(cstr,c);}else if(cstr)strcpy(cstr,c);
	return(*this);
}

void Palavra::append(const char *c){ 
	Palavra tmp;
	tmp=*this;
	apagaezera();
	cstr=new char[tmp.cstr==0?n_strlen(c)+1:n_strlen(tmp.cstr)+n_strlen(c)+1];
	if(tmp.cstr&&*tmp.cstr!=0){
		strcpy(cstr,tmp.cstr);
		strcat(cstr,c);
	}
	else if(cstr) strcpy(cstr,c);
}

	void Palavra::append(Palavra &pal){ 
 *this=*this+pal;	
}

void Palavra::append(int i){ 
	static Palavra tmp;
	tmp=*this;
	apagaezera();
	static char c[32];
	sprintf(c,"%d",i);
	cstr=new char[tmp.cstr==0?n_strlen(c)+1:n_strlen(tmp.cstr)+n_strlen(c)+1];
	if(tmp.cstr&&*tmp.cstr!=0){
		strcpy(cstr,tmp.cstr);
		strcat(cstr,c);
	}
	else if(cstr)strcpy(cstr,c);
}

void Palavra::append(double d){ 
	static Palavra tmp;
	tmp=*this;
	apagaezera();
	static char c[32];
	sprintf(c,"%g",d);
	cstr=new char[tmp.cstr==0?n_strlen(c)+1:n_strlen(tmp.cstr)+n_strlen(c)+1];
	if(tmp.cstr&&*tmp.cstr!=0){
		strcpy(cstr,tmp.cstr);
		strcat(cstr,c);
	}
	else if(cstr)strcpy(cstr,c);
}

Palavra& Palavra::operator +(char c){ 
 Palavra tmp;
	tmp=*this;
	int len=n_strlen(tmp.cstr);
	apagaezera();
	cstr=new char[tmp.cstr==0?2:len+2]; 
	if(tmp.cstr&&*tmp.cstr!=0){
		strcpy(cstr,tmp.cstr);
		cstr[len]=c;cstr[len+1]=0;
	}
	else if(cstr){ cstr[0]=c;cstr[1]=0;}
	return(*this);
}

Palavra& Palavra::operator +(int n){ 
	static char bf[33];
 Palavra tmp;
	tmp=*this;
	sprintf(bf,"%d",n);
	apagaezera();
	cstr=new char[tmp.cstr==0?n_strlen(bf)+1:n_strlen(tmp.cstr)+n_strlen(bf)+1];
	if(tmp.cstr){
	 strcpy(cstr,tmp.cstr);
	 strcat(cstr,bf);}
	else strcpy(cstr,bf);
	return(*this);
}

NDOUBLE Palavra::comodouble(){
	 return (NDOUBLE)n_atof(cstr);
}


int Palavra::comoint(){
	 return n_atoi(cstr);
}

void Palavra::apagaezera(){ 
 if(cstr){
 	delete []cstr;
  cstr=0;
	}
}

Palavra& Palavra::operator =(const char *c){
	apagaezera();
	if(c){
  cstr=new char[n_strlen(c)+1];
		strcpy(cstr,c);
	}
	return *this;
}

Palavra& Palavra::operator =(int n){
 static char bf[33];
 apagaezera();
	sprintf(bf,"%d",n);
 cstr=new char[n_strlen(bf)+1];
	sprintf(cstr,"%d",n);
 return *this;
}

int Palavra::operator ==(char *c){
 if(n_strcmp(cstr,c)==0)
  return 1;
 else 
  return 0;
}



Palavra& Palavra::operator =(Palavra &p)
{
	if(this==&p)return *this;
	apagaezera();
	if(p.cstr)
	{
  cstr=new char[n_strlen(p.cstr)+1];
		strcpy(cstr,p.cstr);
	}
	return *this;
}
