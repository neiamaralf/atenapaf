#ifndef listasH
#define listasH


typedef int FuncCompara(void *a,void *b);
template <class ITEMLISTA>
class Lista{ 
public:
	int quant;
	unsigned int maxident;
	ITEMLISTA *prm,*ult,*atual,*highlander;
	ITEMLISTA *novoptr(){
		quant++;
		atual = new ITEMLISTA;
		if (!atual) {/*FuncUtils::erroMsg("Falha na Alocação");*/return 0;}
		if(prm){
			atual->ant=ult;
			atual->prx=0;
			ult->prx=atual;
			ult=atual;
		}
		else{
			atual->ant=atual->prx=0;
			prm=ult=atual;
		}
		return atual;
	}	

	
	ITEMLISTA *novoptrant(){
		quant++;
		atual = new ITEMLISTA;
		if (!atual) {/*FuncUtils::erroMsg("Falha na Alocação");*/return 0;}
		if(prm){
			atual->ant=0;
			atual->prx=prm;
			prm->ant=atual;
			prm=atual;
		}
		else{
			atual->ant=atual->prx=0;
			prm=ult=atual;
		}
		return atual;
	}	

	ITEMLISTA *RetornaItemPorIdent(int ident){
		ITEMLISTA *temp; 
		temp=prm;
		while(temp&&(int)temp->ident!=ident)
			temp=temp->prx;
		return temp;
	}

	ITEMLISTA *RetornaItemPorIndice(int index)
	{
		ITEMLISTA *temp;
		int cont=0;
		if(index<0||index>quant-1)
			return 0;
		temp=prm;
		while(cont<index&&temp){
			cont++;
			temp=temp->prx;
		}
		return temp;
	}

	int RetornaIndicePorItem(ITEMLISTA *item){
		ITEMLISTA *temp;
		int cont=0;
		if(!item)	return -1;		
		for(temp=prm,cont=0;temp;temp=temp->prx,cont++){
   if(item==temp)return cont;
		}
		return -1;
	}

	void append(Lista *org)
	{
		quant+=org->quant;
		if(ult)ult->prx=org->prm;
		else prm=org->prm;
		ult=org->ult;
		org->prm=NULL;
	}

	void  transmite(Lista *org){
		quant=org->quant;
		prm=org->prm;
		ult=org->ult;
	}

	void insereitem(ITEMLISTA *item){
		quant++;
		atual=item;
		if(prm){
			atual->ant=ult;
			atual->prx=0;
			ult->prx=atual;
			ult=atual;
		}
		else{
			atual->ant=atual->prx=0;
			prm=ult=atual;
		}			
	}

	void  transfereitem(Lista *org,ITEMLISTA *item){
		if(quant==0||!item)return;		
  org->removeitem(item);
		insereitem(item);		
	}

	void removeitem(ITEMLISTA *item){
		if(quant==0||!item)return;
		if(item->prx) item->prx->ant=item->ant;
		else ult=item->ant;
		if(item->ant) item->ant->prx=item->prx;
		else prm=item->prx;
		if(item->ant) atual=item->ant;
		else atual=item->prx; 
		quant--;
	}

	void apaga(ITEMLISTA *item){
		removeitem(item);
		delete item;
		
	}

	void limpa()
	{
		ITEMLISTA *temp;
		atual=prm;
		while(atual){
			temp=atual->prx;			
			delete atual;
			atual=temp;
		}
		zera();
	}


	void zera(){
		quant=0;
		prm=ult=atual=0;
		maxident=0;
		highlander=0;
	}

	void novoptrafter(ITEMLISTA *anterior){		
		if(anterior)
		{
			quant++;
			atual=new ITEMLISTA;		
			atual->ant=anterior;
			atual->prx=anterior->prx;
			if(anterior->prx)
				anterior->prx->ant=atual;
			else
				ult=atual;
			anterior->prx=atual;
		}
		else novoptr();
	}	

	Lista(){
		zera();
	}

	~Lista(){
		if(prm)
			limpa();
	}

	static ITEMLISTA *ordena(ITEMLISTA *cabeca,ITEMLISTA **cauda,FuncCompara *funccomp) 	{
		ITEMLISTA *p, *q, *e;
		int insize, nmerges, psize, qsize, i,loop=1;
		if (!cabeca)
			return NULL;
		insize = 1;
		while (loop) {
			p = cabeca;
			cabeca = NULL;
			*cauda = NULL;
			nmerges = 0; 
			while (p){
				nmerges++; 
				q = p;
				psize = 0;
				for (i = 0; i < insize; i++) {
					psize++;
					q = q->prx;
					if (!q) break;
				}
				qsize = insize;
				while (psize > 0 || (qsize > 0 && q)){
					if (psize == 0){
						e = q; q = q->prx; qsize--;
					}
					else if (qsize == 0 || !q){
						e = p; p = p->prx; psize--;
					}
					else if (funccomp(p,q)){
						e = p; p = p->prx; psize--;
					} 
					else{
						e = q; q = q->prx; qsize--;
					}
					if (*cauda) 
						(*cauda)->prx = e;
					else 
						cabeca = e;
					e->ant = *cauda;
					*cauda = e;
				}
				p = q;
			}
			(*cauda)->prx = NULL;
			if (nmerges <= 1)
				return cabeca;
			insize *= 2;
		}
		return 0;
	}
};
#endif
