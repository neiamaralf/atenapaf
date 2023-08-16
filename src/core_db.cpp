#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "vilavilela.h"
#include "pg_type.h"
#include "relatorios.h"


void add_lstctrl_column(wxListCtrl* lstctrl,const wxString &label,int indcolumn,int width) {
	wxListItem itemCol;
	itemCol.SetText(label);
	//itemCol.SetImage(-1);
	itemCol.SetAlign(wxLIST_FORMAT_LEFT);
	lstctrl->InsertColumn(indcolumn, itemCol);
	lstctrl->SetColumnWidth(indcolumn, width);
}

wxString VilaVilela::listctrl_get_colomn_text(wxListCtrl* lst,long item,int column) {
	wxListItem info;
	info.m_itemId=item;
	info.m_col = column;
	info.m_mask = wxLIST_MASK_TEXT;
	lst->GetItem(info);
	return info.m_text;
}

void VilaVilela::_createsearchpopupmenu(wxMenu *menu) {
	TableInfo *tb,*rtb;
	FieldInfo *fi,*rf;
	wxString tmpstr,rtmpstr;
	wxWindow* ctrl;
	wxMenuItem* mnitem;
	bool canckeck;
	wxMenu *submenu;
	int i=0;
	if ((tb=lsttableinfo.find_by_pageid(_get_pageid())) !=NULL) {
		for (fi=tb->fields.prm;fi;fi=fi->prx) {
			if (fi->field_type==__DB_FIELD_TYPE_LIST||fi->field_type==__DB_FIELD_TYPE_NONE)
				continue;
			ctrl=this->FindWindowById(fi->idctrl,this);
			tmpstr=wxString::FromUTF8(fi->search_menulabel);

			if (fi->field_type==__DB_FIELD_TYPE_REFS||fi->field_type==__DB_FIELD_TYPE_REFM||fi->field_type==__DB_FIELD_TYPE_REFN) {
				if ((rtb=lsttableinfo.find_by_tableid(fi->reftable)) !=NULL) {
					submenu=new wxMenu();
					for (rf=rtb->fields.prm;rf;rf=rf->prx) {
						if (rf->field_type==__DB_FIELD_TYPE_LIST||rf->field_type==__DB_FIELD_TYPE_NONE)
							continue;
						rtmpstr=wxString::FromUTF8(rf->search_menulabel);
						mnitem=submenu->AppendCheckItem(ID_FIRSTPOPUP+i++, rtmpstr);
						canckeck=seachfieldinfo[tb->indtablename].searchfield==fi&&seachfieldinfo[tb->indtablename].fi==rf;
						mnitem->Check(canckeck);

						mnitem->SetRefData(new menuitemdado(tb->indtablename,fi,rf));
					}
					mnitem=menu->Append(ID_FIRSTPOPUP+i++, tmpstr,submenu);
				}
			}
			else {
				mnitem=menu->AppendCheckItem(ID_FIRSTPOPUP+i++, tmpstr);
				canckeck=seachfieldinfo[tb->indtablename].searchfield==fi&&seachfieldinfo[tb->indtablename].fi==NULL;
				mnitem->Check(canckeck);
				mnitem->SetRefData(new menuitemdado(-1,fi,NULL));
			}
		}
	}
}

void LstTableInfo::novo ( int indtablename,int pageid,int idfirstctrl,int pageindex ) {
			novoptr();
			ult->indtablename=indtablename;
			ult->pageid=pageid;
			ult->pageindex=pageindex;
			//ult->page=((wxNotebook*)wxWindow::FindWindowById(ID_NOTEBOOK,vilavielaframe))->GetPage(pageindex);
			ult->idfirstctrl=idfirstctrl;
		}

void VilaVilela::_createtablesinfos() {
	lsttableinfo.novo(TABLE_fornecedores,ID_PGFORNEC,ID_FORNEC_NOME,4);
	lsttableinfo.ult->fields.novo(1,"Id","idfornecedor",-1,__DB_FIELD_TYPE_NONE,__DB_CTRLS_TYPE_NONE);
	lsttableinfo.ult->fields.novo(2,"Nome","nome",ID_FORNEC_NOME,__DB_FIELD_TYPE_STR,__DB_CTRLS_TYPE_TXT,-1,-1,NULL,FIELD_FLAG_NOTNULL);
	lsttableinfo.ult->fields.novo(3,"Endereço","endr",ID_FORNEC_END);
	lsttableinfo.ult->fields.novo(4,"Complemento","complemento",ID_FORNEC_COMP);
	lsttableinfo.ult->fields.novo(5,"Email","email",ID_FORNEC_EMAIL);
	lsttableinfo.ult->fields.novo(6,"Contato","contato",ID_FORNEC_CONTATO);
	lsttableinfo.ult->fields.novo(7,"CNPJ","cnpj",ID_FORNEC_CNPJ);
	lsttableinfo.ult->fields.novo(-1,"Telefone","idfornecedor",ID_CBFORNECFONES,__DB_FIELD_TYPE_REFM,__DB_CTRLS_TYPE_CB,TABLE_fones_fornec,-1,"numero");
	lsttableinfo.ult->fields.novo(-1,NULL,"lista",ID_FORNEC_GRID,__DB_FIELD_TYPE_LIST,__DB_CTRLS_TYPE_GRID);
	lsttableinfo.novo(TABLE_cliente,ID_PGCLIENTES,ID_CLIENT_NOME,3);
	lsttableinfo.ult->fields.novo(1,"Id","idcliente",-1,__DB_FIELD_TYPE_NONE,__DB_CTRLS_TYPE_NONE);
	lsttableinfo.ult->fields.novo(2,"Nome","nome",ID_CLIENT_NOME,__DB_FIELD_TYPE_STR,__DB_CTRLS_TYPE_TXT,-1,-1,NULL,FIELD_FLAG_NOTNULL);
	lsttableinfo.ult->fields.novo(3,"Endereço","endr",ID_CLIENT_END);
	lsttableinfo.ult->fields.novo(4,"Complemento","complemento",ID_CLIENT_COMP);
	lsttableinfo.ult->fields.novo(5,"Email","email",ID_CLIENT_EMAIL);
	lsttableinfo.ult->fields.novo(6,"Data nascimento","data_nasc",ID_CLIENT_DATANASC,__DB_FIELD_TYPE_DATE,__DB_CTRLS_TYPE_DATE);
	lsttableinfo.ult->fields.novo(7,"CPF","cpf",ID_CLIENT_CPF);
	lsttableinfo.ult->fields.novo(-1,"Telefone","idcliente",ID_CBCLIENTFONES,__DB_FIELD_TYPE_REFM,__DB_CTRLS_TYPE_CB,TABLE_fones_cliente,-1,"numero");
	lsttableinfo.ult->fields.novo(-1,NULL,"lista",ID_CLIENT_GRID,__DB_FIELD_TYPE_LIST,__DB_CTRLS_TYPE_GRID);
	lsttableinfo.novo(TABLE_produtos,ID_PGPRODUTOS,ID_PROD_NOME,5);
	lsttableinfo.ult->fields.novo(1,"Id","idproduto",-1,__DB_FIELD_TYPE_NONE,__DB_CTRLS_TYPE_NONE);
	lsttableinfo.ult->fields.novo(2,"Nome","nome",ID_PROD_NOME,__DB_FIELD_TYPE_STR,__DB_CTRLS_TYPE_TXT,-1,-1,NULL,FIELD_FLAG_NOTNULL);
	lsttableinfo.ult->fields.novo(3,"Descrição","descricao",ID_PROD_DESC);
	lsttableinfo.ult->fields.novo(4,"Código","barcode",ID_PROD_BARCOD,__DB_FIELD_TYPE_BARCODE);
	lsttableinfo.ult->fields.novo(5,"Unidade","idunidade",ID_PROD_UNIT,__DB_FIELD_TYPE_REFS,__DB_CTRLS_TYPE_CB,TABLE_unidade,-1,"abrev");
	lsttableinfo.ult->fields.novo(6,"Valor unitário venda","val_unit_venda",ID_PROD_VALUNIT,__DB_FIELD_TYPE_FLOAT,__DB_CTRLS_TYPE_TXT,-1,-1,NULL,FIELD_FLAG_NOTNULL);
	lsttableinfo.ult->fields.novo(-1,NULL,"lista",ID_PROD_GRID,__DB_FIELD_TYPE_LIST,__DB_CTRLS_TYPE_GRID);
	lsttableinfo.ult->fields.novo(12,"Alíquota","idaliquota",ID_PROD_ICMS,__DB_FIELD_TYPE_REFS,__DB_CTRLS_TYPE_CB,TABLE_aliquotas,-1,"descricao");
	lsttableinfo.ult->fields.novo(8,"Imagem","image",ID_PROD_IMG,__DB_FIELD_TYPE_IMAGE,__DB_CTRLS_TYPE_STATICIMG);
	lsttableinfo.ult->fields.novo(9,"Categoria","idcategoria",ID_PROD_CATEGORIA,__DB_FIELD_TYPE_REFS,__DB_CTRLS_TYPE_CB,TABLE_categoria,-1,"descricao");
	lsttableinfo.ult->fields.novo(10,"Sugestão","sugestao",ID_PROD_SUGESTAO,__DB_FIELD_TYPE_INT,__DB_CTRLS_TYPE_CHECK);
	lsttableinfo.ult->fields.novo(11,"Destaque","destaque",ID_PROD_DESTAQUE,__DB_FIELD_TYPE_INT,__DB_CTRLS_TYPE_CHECK);
	lsttableinfo.ult->fields.novo(-1,NULL,"botaodelimg",ID_PROD_DELIMAGE,__DB_FIELD_TYPE_NONE,__DB_CTRLS_TYPE_BUTTON);

	lsttableinfo.ult->fields.novo(-1,NULL,"botaoimg",ID_BTPROD_IMG,__DB_FIELD_TYPE_NONE,__DB_CTRLS_TYPE_BUTTON);

	lsttableinfo.novo(TABLE_unidade,ID_PGUNIDADE,ID_UNIDADE_DESC,2);
	lsttableinfo.ult->fields.novo(1,"Id","idunidade",-1,__DB_FIELD_TYPE_NONE,__DB_CTRLS_TYPE_NONE);
	lsttableinfo.ult->fields.novo(2,"Descrição","descricao",ID_UNIDADE_DESC);
	lsttableinfo.ult->fields.novo(3,"Abreviatura","abrev",ID_UNIDADE_ABREV,__DB_FIELD_TYPE_STR,__DB_CTRLS_TYPE_TXT,-1,-1,NULL,FIELD_FLAG_NOTNULL);
	lsttableinfo.ult->fields.novo(-1,NULL,"lista",ID_UNIDADE_GRID,__DB_FIELD_TYPE_LIST,__DB_CTRLS_TYPE_GRID);

	lsttableinfo.novo(TABLE_aliquotas,ID_PGALIQUOTAS,ID_ALIQUOTAS_DESC,8);
	lsttableinfo.ult->fields.novo(1,"Id","idaliquota",-1,__DB_FIELD_TYPE_NONE,__DB_CTRLS_TYPE_NONE);
	lsttableinfo.ult->fields.novo(2,"Descrição","descricao",ID_ALIQUOTAS_DESC);
	lsttableinfo.ult->fields.novo(3,"Abreviatura","abrev",ID_ALIQUOTAS_ABREV,__DB_FIELD_TYPE_STR,__DB_CTRLS_TYPE_TXT,-1,-1,NULL,FIELD_FLAG_NOTNULL);
	lsttableinfo.ult->fields.novo(4,"Tipo alíquota","tipo",ID_ALIQUOTAS_TIPO,__DB_FIELD_TYPE_INT,__DB_CTRLS_TYPE_CHECK);
	lsttableinfo.ult->fields.novo(-1,NULL,"lista",ID_ALIQUOTAS_GRID,__DB_FIELD_TYPE_LIST,__DB_CTRLS_TYPE_GRID);

	lsttableinfo.novo(TABLE_compras,ID_PGCOMPRAS,ID_COMPRAS_BT_INS_PROD,1);
	lsttableinfo.ult->fields.novo(1,"Id","idcompra",-1,__DB_FIELD_TYPE_NONE,__DB_CTRLS_TYPE_NONE);
	lsttableinfo.ult->fields.novo(2,"Fornecedor","idfornecedor",ID_COMPRAS_FORNEC,__DB_FIELD_TYPE_REFS,__DB_CTRLS_TYPE_CB,TABLE_fornecedores,-1,"nome");
	lsttableinfo.ult->fields.novo(3,"Data","data",ID_COMPRAS_DATA,__DB_FIELD_TYPE_DATE,__DB_CTRLS_TYPE_DATE);
	lsttableinfo.ult->fields.novo(4,"No. Nota","no_nota",ID_COMPRAS_NO_NOTA);
	lsttableinfo.ult->fields.novo(-1,"Produto","idcompra",ID_COMPRAS_PROD_GRID,__DB_FIELD_TYPE_REFN,__DB_CTRLS_TYPE_LIST,TABLE_produto_entrada,-1,"idproduto",0,TABLE_produtos);
	lsttableinfo.ult->fields.novo(-1,NULL,"lista",ID_COMPRAS_GRID,__DB_FIELD_TYPE_LIST,__DB_CTRLS_TYPE_GRID);
	lsttableinfo.ult->fields.novo(-1,NULL,"botaoins",ID_COMPRAS_BT_INS_PROD,__DB_FIELD_TYPE_NONE,__DB_CTRLS_TYPE_BUTTON);
	lsttableinfo.novo(TABLE_vendas,ID_PGVENDAS,ID_VENDAS_INSPROD_GRID,0);
	lsttableinfo.ult->fields.novo(1,"Id","idvenda",-1,__DB_FIELD_TYPE_NONE,__DB_CTRLS_TYPE_NONE);
	lsttableinfo.ult->fields.novo(2,"Cliente","idcliente",ID_VENDAS_CLIENTE,__DB_FIELD_TYPE_REFS,__DB_CTRLS_TYPE_TXT,TABLE_cliente,-1,"nome",0);
	lsttableinfo.ult->fields.novo(3,"Data","data",ID_VENDAS_DATA,__DB_FIELD_TYPE_DATE,__DB_CTRLS_TYPE_DATE);
	lsttableinfo.ult->fields.novo(4,"No. Nota","no_nota",ID_VENDAS_NO_NOTA);
	lsttableinfo.ult->fields.novo(5,"Forma pagto.","idformapagto",ID_VENDAS_FORMAPAGTO,__DB_FIELD_TYPE_REFS,__DB_CTRLS_TYPE_CB,TABLE_formapagto,-1,"descricao",0);
	lsttableinfo.ult->fields.novo(-1,"Produto","idvenda",ID_VENDAS_INSPROD_GRID,__DB_FIELD_TYPE_REFN,__DB_CTRLS_TYPE_LIST,TABLE_saida,-1,"idproduto",0,TABLE_produtos);
	
	lsttableinfo.ult->fields.novo(7,"Desconto","desconto",ID_VENDAS_DESCONTO);
	lsttableinfo.ult->fields.novo(8,"Desconto por percentual","desconto_percentual",ID_CHK_PERCENTUAL,__DB_FIELD_TYPE_INT,__DB_CTRLS_TYPE_CHECK);
	lsttableinfo.ult->fields.novo(-1,NULL,"lista",ID_VENDAS_GRID,__DB_FIELD_TYPE_LIST,__DB_CTRLS_TYPE_GRID,-1,-1,NULL,0,-1,true);
	
	lsttableinfo.ult->fields.novo(-1,"Pagamento","idvenda",ID_VENDAS_VALREC,__DB_FIELD_TYPE_REFN,__DB_CTRLS_TYPE_LIST,TABLE_vendapagtos,-1,"idformapagto",0,TABLE_formapagto,true);
	lsttableinfo.novo(TABLE_formapagto,ID_PGFORMAPAGTO,ID_FORMAPGTO_DESC,6);
	lsttableinfo.ult->fields.novo(1,"Id","idformapagto",-1,__DB_FIELD_TYPE_NONE,__DB_CTRLS_TYPE_NONE);
	lsttableinfo.ult->fields.novo(2,"Descrição","descricao",ID_FORMAPGTO_DESC,__DB_FIELD_TYPE_STR,__DB_CTRLS_TYPE_TXT,-1,-1,NULL,FIELD_FLAG_NOTNULL);
	lsttableinfo.ult->fields.novo(-1,NULL,"lista",ID_FORMAPGTO_GRID,__DB_FIELD_TYPE_LIST,__DB_CTRLS_TYPE_GRID);
	lsttableinfo.novo(TABLE_categoria,ID_PGCATEGORIA,ID_CATEGORIA_DESC,7);
	lsttableinfo.ult->fields.novo(1,"Id","idcategoria",-1,__DB_FIELD_TYPE_NONE,__DB_CTRLS_TYPE_NONE);
	lsttableinfo.ult->fields.novo(2,"Descrição","descricao",ID_CATEGORIA_DESC,__DB_FIELD_TYPE_STR,__DB_CTRLS_TYPE_TXT,-1,-1,NULL,FIELD_FLAG_NOTNULL);
	lsttableinfo.ult->fields.novo(-1,NULL,"lista",ID_CATEGORIA_GRID,__DB_FIELD_TYPE_LIST,__DB_CTRLS_TYPE_GRID);

	lsttableinfo.novo(TABLE_fones_cliente,-1,-1,-1);
	lsttableinfo.ult->fields.novo(2,"Número","numero",-1);
	lsttableinfo.novo(TABLE_fones_fornec,-1,-1,-1);
	lsttableinfo.ult->fields.novo(2,"Número","numero",-1);
	lsttableinfo.novo(TABLE_saida,-1,-1,-1);
	lsttableinfo.ult->fields.novo(2,"Nome","nome",-1);
	lsttableinfo.ult->fields.novo(3,"Descrição","descricao",-1);
	lsttableinfo.ult->fields.novo(4,"Código","barcode",-1);
	lsttableinfo.ult->fields.novo(5,"ICMS","icms",-1);
	lsttableinfo.novo(TABLE_produto_entrada,-1,-1,-1);
	lsttableinfo.ult->fields.novo(2,"Nome","nome",-1);
	lsttableinfo.ult->fields.novo(3,"Descrição","descricao",-1);
	lsttableinfo.ult->fields.novo(4,"Código","barcode",-1);
	lsttableinfo.ult->fields.novo(5,"ICMS","icms",-1);
	lsttableinfo.novo(TABLE_vendapagtos,-1,-1,-1);	
	lsttableinfo.ult->fields.novo(4,"Valor","valor",-1);
	
}


void VilaVilela::_show_hide_auxcontrols(int pageid,bool show,bool resettotal) {
	wxRect ret;
	switch (pageid) {
	case ID_PGCLIENTES:
		this->FindWindowById(ID_CLIENT_INS_FONE,this)->Show(!show);
		this->FindWindowById(ID_CLIENT_DEL_FONE,this)->Show(!show);
		this->FindWindowById(ID_CLIENT_DELALL_FONE,this)->Show(!show);
		this->FindWindowById(ID_CBCLIENTFONES,this)->Show(!show);
		this->FindWindowById(wxID_STATIC_CLFONE,this)->Show(!show);

		break;
	case ID_PGFORNEC:
		this->FindWindowById(ID_FORNEC_INS_FONE,this)->Show(!show);
		this->FindWindowById(ID_FORNEC_DEL_FONE,this)->Show(!show);
		this->FindWindowById(ID_FORNEC_DELALL_FONE,this)->Show(!show);
		this->FindWindowById(ID_CBFORNECFONES,this)->Show(!show);
		this->FindWindowById(wxID_STATIC_FNFONE,this)->Show(!show);
		break;
	case ID_PGVENDAS:
		this->FindWindowById(wxID_STATIC_VALREC,this)->Show(admin?true:show);
		this->FindWindowById(ID_VENDAS_VALREC,this)->Show(admin?true:show);

		this->FindWindowById(wxID_STATIC_TOTDESC,this)->Show(admin?true:show);
		this->FindWindowById(ID_VENDAS_TOTAL,this)->Show(admin?true:show);

		this->FindWindowById(wxID_STATIC_DESCPERC,this)->Show(admin?true:show);
		this->FindWindowById(ID_CHK_PERCENTUAL,this)->Show(admin?true:show);

		this->FindWindowById(wxID_STATIC_VALDESC,this)->Show(admin?true:show);
		this->FindWindowById(ID_VENDAS_DESCONTO,this)->Show(admin?true:show);

		this->FindWindowById(wxID_STATIC_TOTAL,this)->Show(admin?true:show);
		this->FindWindowById(ID_VENDAS_TOTAL_GERAL,this)->Show(admin?true:show);
		

		this->FindWindowById(wxID_STATIC_TROCO,this)->Show(show);
		this->FindWindowById(ID_VENDAS_TROCO,this)->Show(show);
		
		
		this->FindWindowById(ID_PANEL_VENDAS,this)->Show(admin?!show:false);
		this->FindWindowById(ID_PANEL_VENDAS1,this)->Layout();
		this->FindWindowById(pageid,this)->Layout();
		if (resettotal) {
			((wxTextCtrl*) this->FindWindowById(ID_VENDAS_TOTAL,this))->SetValue(_("0.00"));
			((wxTextCtrl*) this->FindWindowById(ID_VENDAS_DESCONTO,this))->SetValue(_("0"));
			((wxTextCtrl*) this->FindWindowById(ID_VENDAS_TOTAL_GERAL,this))->SetValue(_("0.00"));
		}
		break;
	case  ID_PGCOMPRAS:
		if (resettotal)
			((wxTextCtrl*) this->FindWindowById(ID_COMPRAS_TOTAL,this))->SetValue(_("0.00"));
		break;
	}
}

void VilaVilela::_db_update(int pageid,bool selectgridrow,bool atualizagrid) {
	Palavra query;
	sql_ResultSet  *res,*res2,*res3;
	bool emptydb=false;
	query="SELECT * FROM ";
	wxChoice *cbx;
	wxTextCtrl *edx;
	wxListCtrl* list;
	char fieldrefid[16];
	TableInfo *tb;
	int i,size;
	long cursel;
	FieldInfo *fi,*sfi;
	wxString tmpstr;
	if ((tb=lsttableinfo.find_by_pageid(pageid)) !=NULL) {
		if (db_table_id[tb->indtablename]) {
			query.append(main_tables[tb->indtablename]);
			query.append(" WHERE ");
			query.append(main_tablekeys[tb->indtablename]);
			query.append("=");
			query.append(wxString::Format(_("%d"),db_table_id[tb->indtablename]).ToAscii());
			if ((res=_execquerywithresult(query)) !=NULL) {
				while (_nextrow(res)) {
					for (fi=tb->fields.prm;fi;fi=fi->prx) {
						if ((fi->field_type==__DB_FIELD_TYPE_REFM)) {
							if (fi->control_type==__DB_CTRLS_TYPE_CB) {
								query="SELECT ";
								query.append(fi->fieldnameref);   //tenha certeza de iniciar com o nome correto!
								query.append(" FROM ");
								query.append(main_tables[fi->reftable]);
								query.append(" WHERE ");
								query.append(fi->fieldname);   //tenha certeza de iniciar com o nome correto!
								query.append("=");
								sprintf(fieldrefid,"%d",db_table_id[tb->indtablename]);
								query.append(fieldrefid);
								if ((res2=_execquerywithresult(query)) !=NULL) {
									cbx= ((wxChoice*) this->FindWindowById(fi->idctrl,this));
									cbx->Clear();
									while (_nextrow(res2)) {
										tmpstr=_getstring(res2,1);
										cbx->Append(tmpstr);
									}
									cbx->Select(0);
									_deleteresult(&res2);
								}
							}
						}
						else
							if (fi->field_type==__DB_FIELD_TYPE_REFS) {
								{
									query="SELECT ";
									query.append(fi->fieldname);
									query.append(",");
									query.append(fi->fieldnameref);
									query.append(" FROM ");
									query.append(main_tables[fi->reftable]);
									query.append(" ORDER BY ");
									query.append(main_tablesortfield[fi->reftable]);
									if ((res2=_execquerywithresult(query)) !=NULL) {
										if (fi->control_type==__DB_CTRLS_TYPE_CB) {
											cbx= ((wxChoice*) this->FindWindowById(fi->idctrl,this));
											cbx->Clear();
											while (_nextrow(res2)) {
												tmpstr=_getstring(res2,2);
												cbx->Append(tmpstr, (wxClientData*)(new chcIdRef(_getint(res2,1))));
											}
										}
										else
											if (fi->control_type==__DB_CTRLS_TYPE_TXT)
												edx= ((wxTextCtrl*) this->FindWindowById(fi->idctrl,this));
										_deleteresult(&res2);
										query="SELECT ";
										query.append(fi->fieldnameref);
										query.append(" FROM ");
										query.append(main_tables[fi->reftable]);
										query.append(" WHERE ");
										query.append(fi->fieldname);
										query.append("=");
										sprintf(fieldrefid,"%d",_getint(res,fi->fieldname));
										query.append(fieldrefid);
										if ((res2=_execquerywithresult(query)) !=NULL) {
											if (_nextrow(res2)) {
												tmpstr=_getstring(res2,1);
												if (fi->control_type==__DB_CTRLS_TYPE_CB)
													cbx->Select(cbx->FindString(tmpstr));
												else
													if (fi->control_type==__DB_CTRLS_TYPE_TXT) {
														edx->SetValue(tmpstr);
														edx->SetClientObject((wxClientData*)(new chcIdRef(_getint(res,fi->fieldname))));
													}
											}
											_deleteresult(&res2);
										}
									}
								}
							}
							else
								if (fi->field_type==__DB_FIELD_TYPE_REFN) {
									if (fi->control_type==__DB_CTRLS_TYPE_LIST) {
										LstCellInfo *lstcellinfo;
										int i=0;
										double subtotal;
										venda_total=0;
										wxString vtot;
										list= (wxListCtrl*) this->FindWindowById(fi->idctrl,this);
										if (list->GetColumnCount() >0) {
											if (pageid==ID_PGCOMPRAS) {
												query="SELECT prod.idproduto,prod.nome,prod.descricao,unid.abrev,prod_ent.quant,prod.val_unit_venda,prod_ent.val_unit_compra \
																FROM produtos AS prod,unidade AS unid,produto_entrada AS prod_ent \
																WHERE prod.idunidade=unid.idunidade AND prod_ent.idproduto=prod.idproduto AND prod_ent.idcompra=";
												tmpstr=wxString::Format(_("%d"),db_table_id[tb->indtablename]);
												query.append(tmpstr.ToAscii());
												query.append(" ORDER BY prod.nome");
												if ((res2=_execquerywithresult(query)) !=NULL) {
													if (list->GetItemCount() >0)
														list->DeleteAllItems();
													while (_nextrow(res2)) {
														subtotal= (_getdouble(res2,5) *_getdouble(res2,7));
														venda_total+=subtotal;
														tmpstr=_getstring(res2,2);
														list->InsertItem(i, tmpstr);
														lstcellinfo=new LstCellInfo();
														list->SetItemPtrData(i, (wxUIntPtr) lstcellinfo);
														tmpstr=_getstring(res2,2);
														lstcellinfo->novo(0,_getint(res2,1),tmpstr);

														for (int j=1;j<6;j++) {
															tmpstr=_getstring(res2,j+2);
															list->SetItem(i,j,tmpstr);
															tmpstr=_getstring(res2,j+2);
															lstcellinfo->novo(j,-1,tmpstr);
														}
														vtot.Printf(_("%.2f"),subtotal);
														list->SetItem(i,6,vtot);
														i++;
													}
													wxTextCtrl* stvaltot= (wxTextCtrl*) this->FindWindowById(ID_COMPRAS_TOTAL,this);
													vtot.Printf(_("%.2f"),venda_total);
													stvaltot->SetValue(vtot);
													_deleteresult(&res2);
												}
											}
											else	if (pageid==ID_PGVENDAS) {
												if(fi->reftable==TABLE_vendapagtos){
													query="SELECT fpagto.idformapagto,fpagto.descricao,_out.valor \
																			FROM formapagto AS fpagto, vendapagtos AS _out \
																			WHERE ( fpagto.idformapagto=_out.idformapagto AND _out.idvenda=";
													tmpstr=wxString::Format(_("%d"),db_table_id[tb->indtablename]);
													query.append(tmpstr.ToAscii());
													query.append(" )");
													if (list->GetItemCount() >0)
														list->DeleteAllItems();
													long item;
													if ((res2=_execquerywithresult(query)) !=NULL) {
														while (_nextrow(res2)) {
															subtotal= _getdouble(res2,3) ;
															venda_total+=subtotal;
															item=list->InsertItem(i,_getstring(res2,2));			
															tmpstr.Printf(_("%.2f"),_getdouble(res2,3));
															list->SetItem(i,1,tmpstr);
															i++;
														}
														_deleteresult(&res2);
													}
												}
												else {
													query="SELECT prod.idproduto,prod.barcode,prod.nome,prod.descricao,unid.abrev,_out.quant,prod.val_unit_venda \
																			FROM produtos AS prod,unidade AS unid, saida AS _out \
																			WHERE ( prod.idunidade=unid.idunidade AND _out.idproduto=prod.idproduto AND _out.idvenda=";
													tmpstr=wxString::Format(_("%d"),db_table_id[tb->indtablename]);
													query.append(tmpstr.ToAscii());
													query.append(" ) ORDER BY _out.idsaida");
													if (list->GetItemCount() >0)
														list->DeleteAllItems();
													long item;
													if(admin)
													if ((res2=_execquerywithresult(query)) !=NULL) {
														while (_nextrow(res2)) {
															subtotal= (_getdouble(res2,6) *_getdouble(res2,7));
															venda_total+=subtotal;
															tmpstr.Printf(_("%03d"),list->GetItemCount()+1);
															item=list->InsertItem(i,tmpstr);
															lstcellinfo=new LstCellInfo();
															list->SetItemPtrData(i, (wxUIntPtr) lstcellinfo);
															tmpstr=_getstring(res2,2);
															lstcellinfo->novo(0,_getint(res2,1),tmpstr);
															for (int j=1;j<7;j++) {
																tmpstr=_getstring(res2,j+1);
																list->SetItem(i,j,tmpstr);
																lstcellinfo->novo(j,-1,tmpstr);
															}
															if (subtotal==0.0) {
																wxFont font=list->GetItemFont(item);
#ifndef WIN32
																font.SetStrikethrough(true);
#endif
																list->SetItemFont(item,font);
																list->SetItemBackgroundColour(item,wxColour(255,0,0));
															}

															vtot.Printf(_("%.2f"),subtotal);
															list->SetItem(i,7,vtot);
															i++;
														}

														wxTextCtrl* stvaltot= (wxTextCtrl*) this->FindWindowById(ID_VENDAS_TOTAL,this);
														vtot.Printf(_("%.2f"),venda_total);
														stvaltot->SetValue(vtot);
														_deleteresult(&res2);
													}
												}
											}
										}
									}
								}
								else {
									if (fi->control_type==__DB_CTRLS_TYPE_TXT) {
										tmpstr=_getstring(res,fi->fieldname);
										((wxTextCtrl*) this->FindWindowById(fi->idctrl,this))->SetValue(tmpstr);
									}
									else
										if (fi->control_type==__DB_CTRLS_TYPE_CHECK) {
											((wxCheckBox*) this->FindWindowById(fi->idctrl,this))->SetValue(_getint(res,fi->fieldname) ==1);
										}
										else
											if (fi->control_type==__DB_CTRLS_TYPE_DATE) {
												wxDateTime date;
												wxString str;
												str=_getstring(res,fi->fieldname);
												date.ParseDate(str.data());
												if (!date.IsValid())
													date=wxDateTime::Now();
												((wxDatePickerCtrl*) this->FindWindowById(fi->idctrl,this))->SetValue(date);
											}
											else
												if (fi->control_type==__DB_CTRLS_TYPE_STATICIMG) {
													wxStaticBitmap* stbmp= (wxStaticBitmap*) this->FindWindowById(fi->idctrl,this);
													query=_getstringSQL(res,fi->fieldname);
													size=query.length();
													if (size>0) {
														imgpath=wxString::FromAscii(query.c_str());
														wxString ptcr;
														ptcr=_(_IMAGE_DIR) +wxString::FromAscii(query.c_str());
														if (wxFileExists(ptcr)) {
															wxImage img(ptcr);
															wxBitmap _bitmap(img);
															stbmp->SetBitmap(_bitmap);
															stbmp->Show();
														}
														else {
															stbmp->SetBitmap(wxNullBitmap);
															stbmp->Hide();
															imgpath=wxEmptyString;
														}
													}
													else {
														stbmp->SetBitmap(wxNullBitmap);
														stbmp->Hide();
														imgpath=wxEmptyString;
													}
													stbmp->SetSize(DEFAULT_IMG_SIZE,DEFAULT_IMG_SIZE);
													stbmp->GetParent()->Layout();
													stbmp->Refresh();
													this->FindWindowById(ID_PROD_DELIMAGE,this)->Refresh();


												}
												else
													if (fi->control_type==__DB_CTRLS_TYPE_CB) {
														((wxChoice*) this->FindWindowById(fi->idctrl,this))->Clear();
													}
													else
														if ((fi->control_type==__DB_CTRLS_TYPE_GRID)) {
															list= (wxListCtrl*) this->FindWindowById(fi->idctrl,this);
															if (atualizagrid) {
																if (list) {
																	if (list->GetColumnCount() ==0) {
																		int cind;
																		for (sfi=tb->fields.prm,cind=0;sfi;sfi=sfi->prx) {
																			if (sfi->fieldindex==-1)
																				continue;
																			tmpstr=wxString::FromUTF8(sfi->search_menulabel);
																			add_lstctrl_column(list,tmpstr,cind++,140);
																		}
																	}
																	res3=0;
																	int nrows=list->GetItemCount();
																	list->Show(false);
																	if (nrows>0&&list->GetItemCount() >0)
																		list->DeleteAllItems();
																	_DbResult *glbres=glb_res[tb->indtablename];
																	_DbRow *actualrow=glbres->current;
																	if (glbres->first()) {
																		wxString colstr;
																		int row=0;
																		do {
																			for (i=0,sfi=tb->fields.prm;sfi;sfi=sfi->prx) {
																				if (sfi->fieldindex==-1)
																					continue;
																				if (sfi->field_type==__DB_FIELD_TYPE_REFS) {
																					query="SELECT ";
																					query.append(sfi->fieldnameref);
																					query.append(" FROM ");
																					query.append(main_tables[sfi->reftable]);
																					query.append(" WHERE ");
																					query.append(sfi->fieldname);
																					query.append("=");
																					char *cstr=glbres->current->getcstr(sfi->fieldindex) ;
																					query.append(cstr);
																					tmpstr=wxEmptyString;
																					if ((res3=_execquerywithresult(query)) !=NULL) {
																						if (_nextrow(res3)) {
																							tmpstr=_getstring(res3,1);
																						}
																						_deleteresult(&res3);
																					}
																				}
																				else
																					tmpstr=glbres->current->getstr(sfi->fieldindex);
																				if (i==0)
																					list->InsertItem(row,tmpstr);
																				else
																					list->SetItem(row,i,tmpstr);
																				i++;
																			}
																			row++;
																		}
																		while (glbres->next());

																		list->Show();
																		list->SetAutoLayout(true);
																	}
																	glbres->current=actualrow;
																}
															}
															if (selectgridrow) {
																tmpstr.Printf(_("%d"),db_table_id[tb->indtablename]);
																cursel=list->FindItem(-1,tmpstr);
																long item = -1;
																item = list->GetNextItem(item,wxLIST_NEXT_ALL);
																if (item != -1) {
																	__DB_MODE olddbmode=db_mode;
																	db_mode=__DB_MODE_UPDATINGGRID;
																	list->SetItemState(cursel,wxLIST_STATE_SELECTED,wxLIST_STATE_SELECTED);
																	db_mode=olddbmode;
																	list->EnsureVisible(cursel);
																}
															}
														}
								}
					}
				}
				_deleteresult(&res);
			}
		}
		else
			emptydb=true;
	}
	else
		emptydb=true;
	wxToolBar* toolbar=this->GetToolBar();
	if (emptydb)
		_clearcontrols(pageid,true,true);
	_EnableTool(ID_TOOLPREVREC,!emptydb);
	_EnableTool(ID_TOOLNEXTREC,!emptydb);
	_EnableTool(ID_TOOLLASTREC,!emptydb);
	_EnableTool(ID_TOOLFIRSTREC,!emptydb);
	_EnableTool(ID_TOOLInsert,true);
	_EnableTool(ID_TOOLDelete,!emptydb);
	_EnableTool(ID_TOOLEdit,!emptydb);
}


bool copyfile(const char *fin,const char *fout) {
	FILE *pFile;
	bool sobrepoe=true;
	long lSize;
	char * buffer;
	size_t result;
	pFile=fopen(fin,"rb");
	if (pFile==NULL) {
		return false;
	}
	fseek(pFile , 0 , SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);
	buffer = (char*) malloc(sizeof(char) *lSize);
	if (buffer == NULL)
		return false;
	result = fread(buffer,1,lSize,pFile);
	if (result != lSize)
		goto return_;
	fclose(pFile);
	pFile=fopen(fout,"rb");

	if (pFile!=NULL) {
		wxMessageDialog mdlg(NULL,___("um arquivo com o mesmo nome já existe, gostaria de sobrescrever?"),___("confirme sobreposição de arquivo"),
		                     wxYES_NO|wxICON_WARNING);
		mdlg.Centre();
		if (mdlg.ShowModal() ==wxID_NO)
			sobrepoe=false;
		fclose(pFile);
	}
	if (sobrepoe) {
		pFile=fopen(fout,"w+b");
		if (pFile==NULL)
			goto return_;
		result = fwrite(buffer,1,lSize,pFile);
		if (result != lSize)
			goto return_;
		fclose(pFile);
	}
return_:
	free(buffer);
	return true;
}

void VilaVilela::_restaura_do_bkup(wxString &dir,wxString &filename) {
	wxZipEntry* entry;
	INIT_PROGRESS_INFO("restaurando do backup","iniciando backup",6,this);
	UPDATE_PROGRESS(1,"iniciando backup");
	dir.Replace(_("\\"),_("/"));
	wxFFileInputStream in(filename);
	wxZipInputStream zip(in);
	wxDataInputStream txt(zip);
	wxUint8 data;
	UPDATE_PROGRESS(2,"descomprimindo arquivos");
	while ((entry = zip.GetNextEntry()) !=NULL) {
		wxString name = entry->GetName(); // access meta-data
		wxFFileOutputStream out(name);
		wxDataOutputStream fout(out);
		if (txt.IsOk())
			do {
				txt >> data; // access data
				fout << data;
			}
			while (txt.IsOk());
		delete entry;
	}
	Palavra query,tbquery,oquer;
	sql_ResultSet *res,*res2,*res3;
	wxString filerestore,tmpstr;
	char cdir[256];
	getcwd(cdir,256);
	wxString wdir=wxString::FromAscii(cdir);
	wdir.Replace(_("\\"),_("/"));
	UPDATE_PROGRESS(3,"excluindo tabelas antigas");
#ifdef VILAVIELASQLITE3
	sqlite3_close(glb_stmt.db);
	query=wdir.ToAscii();
	query.append("/");
	query.append("vilaviela.db");
	oquer=wdir.ToAscii();
	oquer.append("/");
	oquer.append("vilavielaold.db");
	rename(query.c_str(),oquer.c_str());
	tbquery=wdir.ToAscii();
	tbquery.append("/");
	tbquery.append("bkup.db");
	copyfile(tbquery.c_str(),query.c_str());
	remove(tbquery.c_str());
	_open_db();
#else
#ifdef VILAVIELAPOSTGRESQL
	tbquery="SELECT relname FROM pg_stat_user_tables WHERE schemaname='public' ORDER BY relid";
#endif
#ifdef VILAVIELAMYSQL
	tbquery="SHOW TABLES";
#endif
	Palavra tablename,fbkname;
	if ((res=_execquerywithresult(tbquery)) !=NULL&&_nextrow(res)) {
#ifdef VILAVIELAMYSQL
		_execquery("SET FOREIGN_KEY_CHECKS = 0");
#endif
		do {
			tablename=_getstringSQL(res,1);
			query="DROP TABLE ";
			query.append(tablename);
			query.append(" CASCADE");
			_execquery(query);
		}
		while (_nextrow(res));
#ifdef VILAVIELAMYSQL
		_execquery("SET FOREIGN_KEY_CHECKS = 1");
#endif
		UPDATE_PROGRESS(4,"criando novas tabelas");
		_create_tables(&glb_stmt);
		UPDATE_PROGRESS(5,"inserindo dados do backup");
		if (_firstrow(res)) {
			do {
				tablename=_getstringSQL(res,1);
				fbkname=wdir.ToAscii();
				fbkname.append("/");
				fbkname.append(tablename);
				fbkname.append(".dat");
#ifdef VILAVIELAMYSQL
				query="LOAD DATA INFILE '";
				query.append(fbkname);
				query.append("' IGNORE INTO TABLE ");
				query.append(tablename);
				//	query.append(" FIELDS TERMINATED BY '|' OPTIONALLY ENCLOSED BY '\\'' LINES STARTING BY '_' TERMINATED BY '\\n'");
#endif
#ifdef VILAVIELAPOSTGRESQL
				//query="CREATE TEMPORARY TABLE temptable AS TABLE ";
				//query.append(tablename);
				//_execquery(query);
				query="COPY ";
				query.append(tablename);
				query.append(" FROM '");
				query.append(fbkname);
				query.append("'");
#endif
				char *buf;
				int larq=	RELATORIOS::utils::_load_file_to_buf(fbkname.c_str(),&buf);
				if (larq>0) {
					FILE *nfile=fopen(fbkname.c_str(),"w+b");
					fwrite(buf,1,larq-2,nfile);
					fclose(nfile);
					free(buf);
				}
				_execquery(query);
#ifdef VILAVIELAPOSTGRESQL
				/*	query="INSERT INTO ";
					query.append(tablename);
					query.append(" SELECT * FROM temptable");
					_execquery(query);	*/
				Palavra tmpsqlstr;
				query="SELECT column_name FROM information_schema.columns WHERE table_name='";
				query.append(tablename);
				query.append("' AND ordinal_position=1");
				if ((res2=_execquerywithresult(query)) !=NULL&&_nextrow(res2)) {
					query="SELECT pg_get_serial_sequence('";
					query.append(tablename);
					query.append("','");
					query.append(_getstringSQL(res2,1));
					query.append("')");
					if ((res3=_execquerywithresult(query)) !=NULL&&_nextrow(res3)) {
						query="SELECT setval('";
						tmpsqlstr=_getstringSQL(res3,1);

						if (tmpsqlstr.length() >0) {
							query.append(tmpsqlstr);
							query.append("',max(");
							query.append(_getstringSQL(res2,1));
							query.append(")) FROM ");
							query.append(tablename);
							_execquery(query);
						}
						_deleteresult(&res3);
					}
					_deleteresult(&res2);
				}
				//query="DROP TABLE temptable CASCADE";
				//_execquery(query);
#endif
				filerestore=wxString::FromAscii(tablename.c_str());
				filerestore.Append(_(".dat"));
				remove(filerestore.ToAscii());
			}
			while (_nextrow(res));

			_deleteresult(&res);
		}
	}
#endif
	UPDATE_PROGRESS(6,"concluindo backup");
}

void VilaVilela::_set_dbmode(int pageid,__DB_MODE new_mode) {
	db_mode=new_mode;

	switch (new_mode) {
	case __DB_MODE_READ:
		_setreadonly_ctrls_of_page(pageid,false);
		break;
	case __DB_MODE_INSERT:
		_setreadonly_ctrls_of_page(pageid);
		if (pageid==ID_PGPRODUTOS) {
			imgpath=wxEmptyString;
			wxStaticBitmap* stbmp= (wxStaticBitmap*) this->FindWindowById(ID_PROD_IMG,this);
			stbmp->Hide();
		}
		break;
	case __DB_MODE_EDIT:
		_setreadonly_ctrls_of_page(pageid,true);
		break;
	}
}

void VilaVilela::_clearcontrols(int pageid,int insert_ref_s,bool cleargrid) {
	Palavra query;
	sql_ResultSet  *res;
	wxChoice *cbx;
	wxTextCtrl* edx;
	TableInfo *tb;
	FieldInfo *fi;
	wxString tmpstr;
	if ((tb=lsttableinfo.find_by_pageid(pageid)) !=NULL) {
		for (fi=tb->fields.prm;fi;fi=fi->prx) {
			if (insert_ref_s&& (fi->field_type==__DB_FIELD_TYPE_REFS)) {
				if (fi->control_type==__DB_CTRLS_TYPE_CB) {
					query="SELECT ";
					query.append(fi->fieldname);
					query.append(",");
					query.append(fi->fieldnameref);
					query.append(" FROM ");
					query.append(main_tables[fi->reftable]);
					query.append(" ORDER BY ");
					query.append(main_tablesortfield[fi->reftable]);
					if ((res=_execquerywithresult(query)) !=NULL) {
						cbx= ((wxChoice*) this->FindWindowById(fi->idctrl,this));
						cbx->Clear();
						while (_nextrow(res)) {
							tmpstr=_getstring(res,2);
							cbx->Append(tmpstr, (wxClientData*)(new chcIdRef(_getint(res,1))));
						}
						cbx->Select(0);
						_deleteresult(&res);
					}

				}
				else
					if (fi->control_type==__DB_CTRLS_TYPE_TXT) {
						edx= ((wxTextCtrl*) this->FindWindowById(fi->idctrl,this));
						//edx->SetValue(wxEmptyString);
					}
			}
			else {
				if (fi->control_type==__DB_CTRLS_TYPE_TXT)
					((wxTextCtrl*) this->FindWindowById(fi->idctrl,this))->Clear();
				else
					if (fi->control_type==__DB_CTRLS_TYPE_CHECK)
						((wxCheckBox*) this->FindWindowById(fi->idctrl,this))->SetValue(false);
					else
						if (fi->control_type==__DB_CTRLS_TYPE_DATE) {
							wxDateTime date;
							date=wxDateTime::Now();
							((wxDatePickerCtrl*) this->FindWindowById(fi->idctrl,this))->SetValue(date);
						}
						else
							if (fi->control_type==__DB_CTRLS_TYPE_CB) {
								((wxChoice*) this->FindWindowById(fi->idctrl,this))->Clear();
							}
							else
								if (fi->control_type==__DB_CTRLS_TYPE_STATICIMG) {
									wxStaticBitmap* stbmp= ((wxStaticBitmap*) this->FindWindowById(fi->idctrl,this));
									stbmp	->SetBitmap(wxNullBitmap);
									stbmp->Hide();
								}
								else
									if (fi->control_type==__DB_CTRLS_TYPE_LIST) {
										wxListCtrl* list= ((wxListCtrl*) this->FindWindowById(fi->idctrl,this));
										if (list->GetItemCount() >0)
											list->DeleteAllItems();
										venda_total=0;
									}
									else
										if (cleargrid&& (fi->control_type==__DB_CTRLS_TYPE_GRID)) {
											wxListCtrl* list= ((wxListCtrl*) this->FindWindowById(fi->idctrl,this));
											if (list->GetItemCount() >0)
												list->DeleteAllItems();
										}
			}
		}
	}
}

void VilaVilela::_delete_gl_res(int index,bool realoc) {
	if (glb_res[index]) {
		delete glb_res[index];
		glb_res[index]=0;
		db_table_id[index]=0;
	}
	if (realoc)
		glb_res[index]=new _DbResult;
}


bool VilaVilela::_db_walk_around(bool next,bool updatedb) {
	wxToolBar* toolbar=this->GetToolBar();
	bool falhou=false,walk=false;
	int pageid=_get_pageid();
	TableInfo *tb;
	_DbResult *glbres;
	if ((tb=lsttableinfo.find_by_pageid(pageid)) !=NULL&&db_table_id[tb->indtablename]) {
		glbres=glb_res[tb->indtablename];
		if (next) {
			walk=glbres->next();
		}
		else {
			walk=glbres->prev();
		}
		if (walk) {
			db_table_id[tb->indtablename]=glbres->current->getint(1);
			if (updatedb)
				_db_update(pageid,true,false);
		}
		else {
			falhou=true;
//			if(next)glbres->prev();else glbres->next();
		}
	}
	if (falhou) {
		_EnableTool(next?ID_TOOLNEXTREC:ID_TOOLPREVREC,false);
		_EnableTool(next?ID_TOOLLASTREC:ID_TOOLFIRSTREC,false);
	}
	else{
		_EnableTool(next?ID_TOOLPREVREC:ID_TOOLNEXTREC,true);
		_EnableTool(next?ID_TOOLFIRSTREC:ID_TOOLLASTREC,true);
	}
	return walk;
}

void VilaVilela::_fetch_and_update_gl_res(int i,__DB_UPD_MODE mode,int curgrav,const wxString &filter,const wxString &filter2) {
	static Palavra querystr;
	_delete_gl_res(i);
	querystr="SELECT ";
	querystr.append(main_tables[i]);
	querystr.append(".* FROM ");
	querystr.append(main_tables[i]);
	if (!filter.IsEmpty() &&seachfieldinfo[i].searchfield) {
		if (seachfieldinfo[i].searchfield->field_type==__DB_FIELD_TYPE_REFS) {
			querystr.append(" , ");
			querystr.append(main_tables[seachfieldinfo[i].searchfield->reftable]);
			querystr.append(" WHERE ");
			querystr.append(main_tables[i]);
			querystr.append(".");
			querystr.append(seachfieldinfo[i].searchfield->fieldname);
			querystr.append(" = ");
			querystr.append(main_tables[seachfieldinfo[i].searchfield->reftable]);
			querystr.append(".");
			querystr.append(seachfieldinfo[i].searchfield->fieldname);
			querystr.append(" AND ");
			querystr.append(main_tables[seachfieldinfo[i].searchfield->reftable]);
			querystr.append(".");
			querystr.append(seachfieldinfo[i].fi->fieldname);
			if (seachfieldinfo[i].fi->field_type==__DB_FIELD_TYPE_DATE&&!filter2.IsEmpty()) {
				querystr.append(" >= ");
				querystr.append("'");
				querystr.append(filter.ToAscii());
				querystr.append("'");
				querystr.append(" AND ");
				querystr.append(main_tables[seachfieldinfo[i].searchfield->reftable]);
				querystr.append(".");
				querystr.append(seachfieldinfo[i].fi->fieldname);
				querystr.append(" <= ");
				querystr.append("'");
				querystr.append(filter2.ToAscii());
				querystr.append(" 23:59:00'");
			}
			else {
				querystr.append(" LIKE ");
				if (seachfieldinfo[i].fi->field_type!=__DB_FIELD_TYPE_FLOAT&&seachfieldinfo[i].fi->field_type!=__DB_FIELD_TYPE_INT)
					querystr.append("'");
				querystr.append(filter.ToAscii());
				querystr.append("%");
				if (seachfieldinfo[i].fi->field_type!=__DB_FIELD_TYPE_FLOAT&&seachfieldinfo[i].fi->field_type!=__DB_FIELD_TYPE_INT)
					querystr.append("'");
			}
		}
		else
			if (seachfieldinfo[i].searchfield->field_type==__DB_FIELD_TYPE_REFN) {
				querystr.append(" , ");
				querystr.append(main_tables[seachfieldinfo[i].searchfield->reftable]);
				querystr.append(" , ");
				querystr.append(main_tables[seachfieldinfo[i].searchfield->reftable2]);
				querystr.append(" WHERE ");
				querystr.append(main_tables[i]);
				querystr.append(".");
				querystr.append(seachfieldinfo[i].searchfield->fieldname);
				querystr.append(" = ");
				querystr.append(main_tables[seachfieldinfo[i].searchfield->reftable]);
				querystr.append(".");
				querystr.append(seachfieldinfo[i].searchfield->fieldname);
				querystr.append(" AND ");
				querystr.append(main_tables[seachfieldinfo[i].searchfield->reftable]);
				querystr.append(".");
				querystr.append(seachfieldinfo[i].searchfield->fieldnameref);
				querystr.append(" = ");
				querystr.append(main_tables[seachfieldinfo[i].searchfield->reftable2]);
				querystr.append(".");
				querystr.append(seachfieldinfo[i].searchfield->fieldnameref);
				querystr.append(" AND ");
				querystr.append(main_tables[seachfieldinfo[i].searchfield->reftable2]);
				querystr.append(".");
				querystr.append(seachfieldinfo[i].fi->fieldname);
				querystr.append(" LIKE ");
				if (seachfieldinfo[i].fi->field_type!=__DB_FIELD_TYPE_FLOAT&&seachfieldinfo[i].fi->field_type!=__DB_FIELD_TYPE_INT)
					querystr.append("'");
				querystr.append(filter.ToAscii());
				querystr.append("%");
				if (seachfieldinfo[i].fi->field_type!=__DB_FIELD_TYPE_FLOAT&&seachfieldinfo[i].fi->field_type!=__DB_FIELD_TYPE_INT)
					querystr.append("'");
			}
			else
				if (seachfieldinfo[i].searchfield->field_type==__DB_FIELD_TYPE_REFM) {
					querystr.append(" , ");
					querystr.append(main_tables[seachfieldinfo[i].searchfield->reftable]);
					querystr.append(" WHERE ");
					querystr.append(main_tables[i]);
					querystr.append(".");
					querystr.append(seachfieldinfo[i].searchfield->fieldname);
					querystr.append(" = ");
					querystr.append(main_tables[seachfieldinfo[i].searchfield->reftable]);
					querystr.append(".");
					querystr.append(seachfieldinfo[i].searchfield->fieldname);
					querystr.append(" AND ");
					querystr.append(main_tables[seachfieldinfo[i].searchfield->reftable]);
					querystr.append(".");
					querystr.append(seachfieldinfo[i].searchfield->fieldnameref);
					querystr.append(" LIKE ");
					querystr.append("'");
					querystr.append(filter.ToAscii());
					querystr.append("%");
					querystr.append("'");
				}
				else {
					querystr.append(" WHERE ");
					querystr.append(seachfieldinfo[i].searchfield->fieldname);
					if (seachfieldinfo[i].searchfield->field_type==__DB_FIELD_TYPE_DATE) {
						querystr.append(" >= ");
						querystr.append("'");
						querystr.append(filter.ToAscii());
						querystr.append("'");
						querystr.append(" AND ");
						querystr.append(seachfieldinfo[i].searchfield->fieldname);
						querystr.append(" <= ");
						querystr.append("'");
						if(!filter2.IsEmpty())
						 querystr.append(filter2.ToAscii());
						else
							querystr.append(filter.ToAscii());
						querystr.append(" 23:59:00'");
					}
					else {
					 querystr.append(" LIKE ");					
						if (seachfieldinfo[i].searchfield->field_type!=__DB_FIELD_TYPE_FLOAT&&seachfieldinfo[i].searchfield->field_type!=__DB_FIELD_TYPE_INT)
							querystr.append("'");
						querystr.append(filter.ToAscii());
					 querystr.append("%");
						if (seachfieldinfo[i].searchfield->field_type!=__DB_FIELD_TYPE_FLOAT&&seachfieldinfo[i].searchfield->field_type!=__DB_FIELD_TYPE_INT)
							querystr.append("'");
					}
				}
	}
	querystr.append(" ORDER BY ");
	querystr.append(main_tablesortfield[i]);
	sql_ResultSet *res;
	if ((res=_execquerywithresult(querystr)) !=NULL) {
		_DbResult *glbres=glb_res[i];
		_DbRow *row;
		_DbCell *field;
		__DB_FIELD_TYPES ftype;
		void *val;
		Palavra charfield;
		int findex,rowsCount;
		rowsCount=_rowsCount(res);
		if (_firstrow(res)) {
			glbres->init(rowsCount,_getColumnCount(res));
			row=glbres->rows;
			do {
				for (findex=1,field=row->cols;;field++,findex++) {
					val=NULL;
					ftype=_getColumnType(res,findex);
					switch (ftype) {
					case __DB_FIELD_TYPE_INT:
						val=malloc(sizeof(int));
						* ((int*) val) =_getint(res,findex);
						break;
					case __DB_FIELD_TYPE_FLOAT:
						val=malloc(sizeof(float));
						* ((float*) val) =_getdouble(res,findex);
						break;
					case __DB_FIELD_TYPE_STR:
						charfield=_getstringSQL(res,findex);
						val=malloc(sizeof(char) *charfield.length() +1);

						if (val!=NULL)
							strcpy(((char*) val),charfield.c_str());
						break;
					}
					field->Create(ftype,val);
					if (field==row->lastcol)
						break;
				}
				row++;
			}
			while (_nextrow(res));
			_deleteresult(&res);
		}
		if (curgrav==-1) {
			if (mode==__DB_UPD_MODE_FIRST?glbres->first() :glbres->last())
				db_table_id[i]=glbres->current->getint(1);
			else
				_delete_gl_res(i);
		}
		else {
			bool find=false;
			if (glbres->first()) {
				do {
					if (glbres->current->getint(1) ==curgrav) {
						db_table_id[i]=glbres->current->getint(1);
						find=true;
						break;
					}
				}
				while (glbres->next());
				if (!find) {
					glbres->first();
					db_table_id[i]=glbres->current->getint(1);
				}
			}
			else		{
				db_table_id[i]=0;
				_delete_gl_res(i);
			}
		}
	}
	else		{
		_delete_gl_res(i);
	}
}



int VilaVilela::_get_pageid() {
	wxNotebook*	notebook= (wxNotebook*) this->FindWindowById(ID_NOTEBOOK,this);
	wxScrolledWindow* page= (wxScrolledWindow*) notebook->GetCurrentPage();
	if (page)
		return page->GetId();
	else
		return 0;
}

void VilaVilela::_selectfirsttxtctrl(int pageid) {
	TableInfo *tb;
	if ((tb=lsttableinfo.find_by_pageid(pageid)) !=NULL) {
		this->FindWindowById(tb->idfirstctrl,this)->SetFocus();
	}
}

void VilaVilela::_setreadonly_ctrls_of_page(int pageid,bool enable) {
	TableInfo *tb;
	FieldInfo *fi;
	wxWindow* ctrlw;
	if ((tb=lsttableinfo.find_by_pageid(pageid)) !=NULL) {
		for (fi=tb->fields.prm;fi;fi=fi->prx) {
			ctrlw=this->FindWindowById(fi->idctrl,this);
			if (ctrlw)
				switch (fi->control_type) {
				case __DB_CTRLS_TYPE_TXT:
					if ((fi->field_type!=__DB_FIELD_TYPE_REFS))
						((wxTextCtrl*) ctrlw)->SetEditable(enable);
					break;
				case __DB_CTRLS_TYPE_CHECK:
				case __DB_CTRLS_TYPE_BUTTON:
				case __DB_CTRLS_TYPE_DATE:
					ctrlw->Enable(enable);
					break;
				case __DB_CTRLS_TYPE_CB:
					if ((fi->field_type==__DB_FIELD_TYPE_REFS))
						ctrlw->Enable(enable);
					break;
				case __DB_CTRLS_TYPE_LIST:
					if ((fi->field_type==__DB_FIELD_TYPE_REFN)&&fi->reftable==TABLE_vendapagtos) {
						//ctrlw->GetSizer()->Show(!enable);						
						if (admin) {
							this->FindWindowById(ID_VENDAS_VALREC,this)->Show(true);
	     	this->FindWindowById(wxID_STATIC_VALREC,this)->Show(true);
							
						}
						else if(!admin){
							this->FindWindowById(ID_VENDAS_VALREC,this)->Show(false);
	     	this->FindWindowById(wxID_STATIC_VALREC,this)->Show(false);
						}
					}
					//	if((fi->field_type==__DB_FIELD_TYPE_REFN))
					//  ctrlw->Enable(enable);
					break;
				case __DB_CTRLS_TYPE_GRID:
					if ((fi->field_type==__DB_FIELD_TYPE_LIST)) {
						//ctrlw->GetSizer()->Show(!enable);
						if(!admin&fi->soadmin)
							ctrlw->Show(false);
						else
						if (((!enable) &&!ctrlw->IsShown()) || ((enable) &&ctrlw->IsShown())) {
							ctrlw->Show(!enable);
						}
					}

					break;
				}
		}
	}
}

void VilaVilela::_delete_row(int pageid) {
	wxString fieldval,tmpstr;
	char fieldrefid[16];
	Palavra queryfields;
	TableInfo *tb;
	FieldInfo *fi;
	if ((tb=lsttableinfo.find_by_pageid(pageid)) !=NULL) {
		for (fi=tb->fields.prm;fi;fi=fi->prx) {
			if (fi->field_type==__DB_FIELD_TYPE_REFM||fi->field_type==__DB_FIELD_TYPE_REFN) {  //delete reference table records
				queryfields="DELETE FROM ";
				queryfields.append(main_tables[fi->reftable]);
				queryfields.append(" WHERE ");
				queryfields.append(fi->fieldname);   //tenha certeza de iniciar com o nome correto!
				queryfields.append("=");
				sprintf(fieldrefid,"%d",db_table_id[tb->indtablename]);
				queryfields.append(fieldrefid);
				_execquery(queryfields);
			}
		}
		int old_curr_id=db_table_id[tb->indtablename],new_curid;
		if (!_db_walk_around(true,false)) {
			if (!_db_walk_around(false,false))
				new_curid=0;
			else
				new_curid=db_table_id[tb->indtablename];
		}
		else {
			new_curid=db_table_id[tb->indtablename];
		}
		queryfields="DELETE FROM ";
		queryfields.append(main_tables[tb->indtablename]);
		queryfields.append(" WHERE ");
		queryfields.append(main_tablekeys[tb->indtablename]);
		queryfields.append("=");
		tmpstr=wxString::Format(_("%d"),old_curr_id);
		queryfields.append(tmpstr.ToAscii());
		_execquery(queryfields);
		_fetch_and_update_gl_res(tb->indtablename,__DB_UPD_MODE_LAST,new_curid);
		_db_update(pageid,true);
	}
}

void VilaVilela::_edit_values(int pageid) {
	wxTextCtrl* editbox;
	wxDatePickerCtrl* date;
	wxChoice *cb;
	wxString tmpstr;
	wxString fieldval;
	Palavra queryfields,tmpquery;
	queryfields.append("UPDATE ");
	TableInfo *tb;
	FieldInfo *fi,*prmfi=NULL,*fieldrefn=NULL;
	if ((tb=lsttableinfo.find_by_pageid(pageid)) !=NULL) {
		queryfields.append(main_tables[tb->indtablename]);
		queryfields.append(" SET ");
		for (fi=tb->fields.prm;fi;fi=fi->prx) {
			if (fi->field_type==__DB_FIELD_TYPE_REFM||fi->field_type==__DB_FIELD_TYPE_LIST||fi->field_type==__DB_FIELD_TYPE_NONE)
				continue;

			if (fi->control_type==__DB_CTRLS_TYPE_TXT&&fi->field_type!=__DB_FIELD_TYPE_REFS) {
				editbox= (wxTextCtrl*) this->FindWindowById(fi->idctrl,this);
				fieldval=editbox->GetValue();
			}
			else
				if (fi->control_type==__DB_CTRLS_TYPE_CHECK) {
					int chv= (int)((wxCheckBox*) this->FindWindowById(fi->idctrl,this))->GetValue()	;
					fieldval=wxString::Format(_("%d"),chv).c_str();
				}
				else
					if (fi->control_type==__DB_CTRLS_TYPE_DATE) {
						date= (wxDatePickerCtrl*) this->FindWindowById(fi->idctrl,this);
						wxDateTime time=wxDateTime::Now();
						fieldval=date->GetValue().FormatISODate();
						fieldval.Append(_(" "));
						fieldval.Append(time.FormatISOTime());
					}
					else
						if (fi->field_type==__DB_FIELD_TYPE_REFS) {
							if (fi->control_type==__DB_CTRLS_TYPE_CB) {
								cb= (wxChoice*) this->FindWindowById(fi->idctrl,this);
								if (cb->GetSelection() >=0) {
									int flag= ((chcIdRef*) cb->GetClientObject(cb->GetSelection()))->val;
									fieldval=wxString::Format(_("%d"),flag).c_str();
								}
								else
									fieldval=_("0");
							}
							else
								if (fi->control_type==__DB_CTRLS_TYPE_TXT) {
									wxTextCtrl *ed= (wxTextCtrl*) this->FindWindowById(fi->idctrl,this);
									chcIdRef* cd= (chcIdRef*) ed->GetClientObject();
									int flag=0;
									if (cd)
										flag=cd->val;
									fieldval=wxString::Format(_("%d"),flag).c_str();
								}
						}
						else
							if (fi->field_type==__DB_FIELD_TYPE_REFN) {
								fieldrefn=fi;
								continue;
							}

			if (!prmfi)
				prmfi=fi;
			if (fi!=prmfi) {
				queryfields.append(",");
			}
			if (fieldval.IsEmpty() && (fi->flag&FIELD_FLAG_NOTNULL)) {
				wxString ermsg;
				tmpstr=___(fi->fieldname);
				ermsg.Printf(___("o campo %s não pode ser nulo"),tmpstr.c_str());
				this->FindWindowById(fi->idctrl,this)->SetFocus();
				wxMessageBox(ermsg);
				return;
			}
			if (fieldval.IsEmpty() && (fi->flag&FIELD_FLAG_DEFAULTZERO))
				fieldval.Printf(_("%d"),0);
			queryfields.append(fi->fieldname);
			queryfields.append("=");
			if (fi->field_type!=__DB_FIELD_TYPE_INT&&fi->field_type!=__DB_FIELD_TYPE_FLOAT&&fi->field_type!=__DB_FIELD_TYPE_REFS)
				queryfields.append("'");
			if (fi->field_type==__DB_FIELD_TYPE_IMAGE) {
				if (imgpath!=wxEmptyString) {
					wxString ptcr;
					wxString filename=imgpath;
					ptcr=_(_IMAGE_DIR) +filename;
					if (!wxFileExists(ptcr)) {
						wxImage image(imgpath);
						int height= (int)(DEFAULT_IMG_SIZE*image.GetHeight() / (double) image.GetWidth());
						image.Rescale(DEFAULT_IMG_SIZE,height,wxIMAGE_QUALITY_HIGH);
						filename=_("img");
						wxDateTime datetime=wxDateTime::Now();
						filename.Append(datetime.Format());
						filename.Append(_(".png"));
						filename.Replace(_("/"),_("-"));
						filename.Replace(_(" "),_("_"));
						filename.Replace(_(":"),_("-"));
						if (!wxFileExists(_(_IMAGE_DIR) +filename))
							image.SaveFile(_(_IMAGE_DIR) +filename,wxBITMAP_TYPE_PNG);
					}
					queryfields.append(filename.ToAscii());
					imgpath=wxEmptyString;
				}
			}
			else
				queryfields.append(fieldval.ToUTF8());
			if (fi->field_type!=__DB_FIELD_TYPE_INT&&fi->field_type!=__DB_FIELD_TYPE_FLOAT&&fi->field_type!=__DB_FIELD_TYPE_REFS)
				queryfields.append("'");
		}
		queryfields.append(" WHERE ");
		queryfields.append(main_tablekeys[tb->indtablename]);
		queryfields.append("=");
		tmpstr=wxString::Format(_("%d"),db_table_id[tb->indtablename]);
		queryfields.append(tmpstr.ToAscii());
		_execquery(queryfields);
		if (fieldrefn) {
			if (fieldrefn->control_type==__DB_CTRLS_TYPE_LIST) {
				Palavra query;
				wxListCtrl *list= (wxListCtrl*) this->FindWindowById(fieldrefn->idctrl,this);
				if (pageid==ID_PGCOMPRAS) {
					query="DELETE FROM ";
					query.append(main_tables[fieldrefn->reftable]);
					query.append(" WHERE idcompra=");
					tmpstr=wxString::Format(_("%d"),db_table_id[tb->indtablename]);
					query.append(tmpstr.ToAscii());
					_execquery(query);
					long item = -1;
					wxListCtrl* lstprodcompra= (wxListCtrl*) this->FindWindowById(ID_COMPRAS_PROD_GRID,this);
					for (;;) {
						item = list->GetNextItem(item,wxLIST_NEXT_ALL,wxLIST_STATE_DONTCARE);
						if (item == -1)
							break;
						LstCellInfo *lstcellinfo= (LstCellInfo*) lstprodcompra->GetItemData(item);
						if (lstcellinfo) {
							CellInfo *cellinfo=lstcellinfo->find_by_collumn(0);
							if (cellinfo) {
								query="INSERT INTO ";
								query.append(main_tables[fieldrefn->reftable]);
								query.append("(idproduto,idcompra,quant,val_unit_compra)");
								query.append("VALUES(");
								tmpstr=wxString::Format(_("%d"),cellinfo->reffield);
								query.append(tmpstr.ToAscii());
								query.append(",");
								tmpstr=wxString::Format(_("%d"),db_table_id[tb->indtablename]);
								query.append(tmpstr.ToAscii());
								cellinfo=lstcellinfo->find_by_collumn(3);   //quant
								query.append(",");
								query.append(cellinfo->str.ToAscii());
								cellinfo=lstcellinfo->find_by_collumn(5);   //valunit
								query.append(",");
								query.append(cellinfo->str.ToAscii());

								query.append(")");
								_execquery(query);
							}
						}
					}
				}
				else
					if (pageid==ID_PGVENDAS) {
						query="DELETE FROM ";
						query.append(main_tables[fieldrefn->reftable]);
						query.append(" WHERE idvenda=");
						tmpstr=wxString::Format(_("%d"),db_table_id[tb->indtablename]);
						query.append(tmpstr.ToAscii());
						_execquery(query);
						long item = -1;
						wxListCtrl* lstprodvenda= (wxListCtrl*) this->FindWindowById(ID_VENDAS_INSPROD_GRID,this);
						for (;;) {
							item = list->GetNextItem(item,wxLIST_NEXT_ALL,wxLIST_STATE_DONTCARE);
							if (item == -1)
								break;
							LstCellInfo *lstcellinfo= (LstCellInfo*) lstprodvenda->GetItemData(item);
							if (lstcellinfo) {
								CellInfo *cellinfo=lstcellinfo->find_by_collumn(0);
								if (cellinfo) {
									query="INSERT INTO ";
									query.append(main_tables[fieldrefn->reftable]);
									query.append("(idproduto,idvenda,quant)");
									query.append("VALUES(");
									tmpstr=wxString::Format(_("%d"),cellinfo->reffield);
									query.append(tmpstr.ToAscii());
									query.append(",");
									tmpstr=wxString::Format(_("%d"),db_table_id[tb->indtablename]);
									query.append(tmpstr.ToAscii());
									cellinfo=lstcellinfo->find_by_collumn(5);
									query.append(",");
									query.append(cellinfo->str.ToAscii());
									query.append(")");
									_execquery(query);
								}
							}
						}
					}
			}
		}
		_fetch_and_update_gl_res(tb->indtablename,__DB_UPD_MODE_LAST,db_table_id[tb->indtablename]);
		_db_update(pageid,true);
	}
}

bool VilaVilela::_insert_values(int pageid) {
	wxTextCtrl* editbox;
	wxDatePickerCtrl* date;
	wxChoice *cb;
	wxTextCtrl *ed;
	wxListCtrl* list;
	wxString fieldval,ermsg,tmstr;
	Palavra queryfields,queryvalues,tmpquery;
	queryfields.append("INSERT INTO ");
	TableInfo *tb;
	FieldInfo *fi,*fieldrefn=0,*prmfi=0;
	if ((tb=lsttableinfo.find_by_pageid(pageid)) !=NULL) {
		queryfields.append(main_tables[tb->indtablename]);
		queryfields.append("(");
		queryvalues.append(") VALUES (");
		for (fi=tb->fields.prm;fi;fi=fi->prx) {
			if (fi->field_type==__DB_FIELD_TYPE_REFM||fi->field_type==__DB_FIELD_TYPE_LIST||fi->field_type==__DB_FIELD_TYPE_NONE)
				continue;
   if(fi->field_type==__DB_FIELD_TYPE_BARCODE){
    editbox= (wxTextCtrl*) this->FindWindowById(fi->idctrl,this);
				fieldval=editbox->GetValue();
    if(fieldval.IsEmpty()){
     Palavra query;
     sql_ResultSet *res;
     query="SELECT MAX(idproduto) FROM produtos";
     long cdbr;
     if ((res=vilavielaframe->_execquerywithresult(query))!=NULL&&vilavielaframe->_nextrow(res)) {
      cdbr=vilavielaframe->_getint(res,1)+1;
      vilavielaframe->_deleteresult(&res);
     }
     else
      cdbr=1;
     fieldval=wxString::Format(_("%d"),cdbr).c_str();
    }
   }
			else if (fi->control_type==__DB_CTRLS_TYPE_TXT&&fi->field_type!=__DB_FIELD_TYPE_REFS) {
				editbox= (wxTextCtrl*) this->FindWindowById(fi->idctrl,this);
				fieldval=editbox->GetValue();
			}
			else
				if (fi->control_type==__DB_CTRLS_TYPE_CHECK) {
					int chv= (int)((wxCheckBox*) this->FindWindowById(fi->idctrl,this))->GetValue()	;
					fieldval=wxString::Format(_("%d"),chv).c_str();
				}
				else
					if (fi->control_type==__DB_CTRLS_TYPE_DATE) {
						date= (wxDatePickerCtrl*) this->FindWindowById(fi->idctrl,this);
						wxDateTime time=wxDateTime::Now();

						fieldval=date->GetValue().FormatISODate();
						fieldval.Append(_(" "));
						tmstr=time.FormatISOTime();
						fieldval.Append(tmstr);
					}
					else
						if (fi->field_type==__DB_FIELD_TYPE_REFS) {
							if (fi->control_type==__DB_CTRLS_TYPE_CB) {
								cb= (wxChoice*) this->FindWindowById(fi->idctrl,this);
								chcIdRef* refobj=0;
								int cbindsel=cb->GetSelection();
								if (cbindsel>=0)
									refobj= (chcIdRef*) cb->GetClientObject(cbindsel);
								int flag=0;
								if (refobj)
									flag=refobj->val;
								else {
									wxString msg;
									msg=_("a tabela ") +___(main_tables[fi->reftable]) +___(" está vazia, tem certeza que quer continuar? ");
									wxMessageDialog mdlg(this,msg,___("Confirme inserção"),wxNO_DEFAULT|wxYES_NO|wxCANCEL|wxICON_INFORMATION);
									mdlg.Centre();
									if (mdlg.ShowModal() ==wxID_NO)
										return false;
								}
								fieldval=wxString::Format(_("%d"),flag).c_str();
							}
							else
								if (fi->control_type==__DB_CTRLS_TYPE_TXT) {
									ed= (wxTextCtrl*) this->FindWindowById(fi->idctrl,this);
									chcIdRef* cd= (chcIdRef*) ed->GetClientObject();
									int flag=0;
									if (cd)
										flag=cd->val;
									fieldval=wxString::Format(_("%d"),flag).c_str();
								}
						}
						else
							if (fi->field_type==__DB_FIELD_TYPE_REFN) {
								fieldrefn=fi;
								continue;
							}
			if (!prmfi)
				prmfi=fi;
			if (fi!=prmfi) {
				queryfields.append(",");
				queryvalues.append(",");
			}

			if (fieldval.IsEmpty() && (fi->flag&FIELD_FLAG_NOTNULL)) {
				tmstr=___(fi->fieldname);
				ermsg.Printf(___("o campo %s não pode ser nulo"),tmstr.c_str());
				this->FindWindowById(fi->idctrl,this)->SetFocus();
				wxMessageBox(ermsg);
				return false;
			}
			if (fieldval.IsEmpty() && (fi->flag&FIELD_FLAG_DEFAULTZERO))
				fieldval.Printf(_("%d"),0);
			queryfields.append(fi->fieldname);
			if (fi->field_type!=__DB_FIELD_TYPE_INT&&fi->field_type!=__DB_FIELD_TYPE_FLOAT&&fi->field_type!=__DB_FIELD_TYPE_REFS)
				queryvalues.append("'");
			if (fi->control_type==__DB_CTRLS_TYPE_STATICIMG) {
				if (imgpath!=wxEmptyString) {
					wxImage image(imgpath);
					int height= (int)(DEFAULT_IMG_SIZE*image.GetHeight() / (double) image.GetWidth());
					image.Rescale(DEFAULT_IMG_SIZE,height,wxIMAGE_QUALITY_HIGH);
					wxString filename=_("img");
					wxDateTime datetime=wxDateTime::Now();
					filename.Append(datetime.Format());
					filename.Append(_(".png"));
					filename.Replace(_("/"),_("-"));
					filename.Replace(_(" "),_("_"));
					filename.Replace(_(":"),_("-"));
					if (!wxFileExists(_(_IMAGE_DIR) +filename))
						image.SaveFile(_(_IMAGE_DIR) +filename,wxBITMAP_TYPE_PNG);
					queryvalues.append(filename.ToAscii());
					imgpath=wxEmptyString;
				}
				else
					queryvalues.append("");
			}
			else
				queryvalues.append(fieldval.ToUTF8());
			if (fi->field_type!=__DB_FIELD_TYPE_INT&&fi->field_type!=__DB_FIELD_TYPE_FLOAT&&fi->field_type!=__DB_FIELD_TYPE_REFS)
				queryvalues.append("'");
		}
		queryvalues.append(")");
		Palavra query=queryfields;
		query.append(queryvalues);
		_execquery(query);
		queryfields="SELECT ";
		queryfields.append(main_tablekeys[tb->indtablename]);
		queryfields.append(" FROM ");
		queryfields.append(main_tables[tb->indtablename]);
		queryfields.append(" ORDER BY ");
		queryfields.append(main_tablekeys[tb->indtablename]);
		sql_ResultSet *res;
		int currec=-1;
		if ((res=_execquerywithresult(queryfields)) !=NULL) {
			if (_lastrow(res))
				currec=_getint(res,1);
			_deleteresult(&res);
		}
		_fetch_and_update_gl_res(tb->indtablename,__DB_UPD_MODE_LAST,currec);
		if (fieldrefn) {
			if (fieldrefn->control_type==__DB_CTRLS_TYPE_LIST) {
				list= (wxListCtrl*) this->FindWindowById(fieldrefn->idctrl,this);
				long item = -1;
				if (pageid==ID_PGCOMPRAS) {
					wxListCtrl* lstprodcompra= (wxListCtrl*) this->FindWindowById(ID_COMPRAS_PROD_GRID,this);
					for (;;) {
						item = list->GetNextItem(item,wxLIST_NEXT_ALL,wxLIST_STATE_DONTCARE);
						if (item == -1)
							break;
						query="INSERT INTO ";
						query.append(main_tables[fieldrefn->reftable]);
						query.append("(idproduto,idcompra,quant,val_unit_compra)");
						query.append("VALUES(");
						LstCellInfo *lstcellinfo= (LstCellInfo*) lstprodcompra->GetItemData(item);
						CellInfo *cellinfo=lstcellinfo->find_by_collumn(0);
						tmstr=wxString::Format(_("%d"),cellinfo->reffield);
						query.append(tmstr.ToAscii());
						query.append(",");
						tmstr=wxString::Format(_("%d"),currec);
						query.append(tmstr.ToAscii());
						cellinfo=lstcellinfo->find_by_collumn(3);
						query.append(",");
						query.append(cellinfo->str.ToAscii());
						cellinfo=lstcellinfo->find_by_collumn(5);
						query.append(",");
						query.append(cellinfo->str.ToAscii());
						query.append(")");
						_execquery(query);
					}
				}
					
			}
		}
		if (pageid==ID_PGVENDAS){ 
			long item=-1;
			wxString tmstr;
			sql_ResultSet *res;
			int currec=-1;
			if ((res=_execquerywithresult("SELECT last_value FROM vendas_idvenda_seq")) !=NULL&&_nextrow(res)) {
				currec=_getint(res,1);
				_deleteresult(&res);
			}
			Palavra query;
			wxListCtrl* lstprodvenda= (wxListCtrl*) this->FindWindowById(ID_VENDAS_INSPROD_GRID,this);
			for (;;) {
				item = lstprodvenda->GetNextItem(item,wxLIST_NEXT_ALL,wxLIST_STATE_DONTCARE);
				if (item == -1)
					break;
				LstCellInfo *lstcellinfo= (LstCellInfo*) lstprodvenda->GetItemData(item);
				if (lstcellinfo) {
					CellInfo *cellinfo=lstcellinfo->find_by_collumn(0);
					if (cellinfo) {
						query="INSERT INTO saida(idproduto,idvenda,quant)";
						query.append("VALUES(");
						tmstr=wxString::Format(_("%d"),cellinfo->reffield);
						query.append(tmstr.ToAscii());
						query.append(",");
						tmstr=wxString::Format(_("%d"),currec);
						query.append(tmstr.ToAscii());
						cellinfo=lstcellinfo->find_by_collumn(5);
						query.append(",");
						query.append(cellinfo->str.ToAscii());
						query.append(")");
						_execquery(query);
					}
				}
			}			
			wxListCtrl *lstvalpago= (wxListCtrl *) this->FindWindowById(ID_VENDAS_VALREC,this);					
			item=-1;
			for (;;) {
				item = lstvalpago->GetNextItem(item,wxLIST_NEXT_ALL,wxLIST_STATE_DONTCARE);
				if (item == -1)
					break;
				chcIdRef *keyfieldpagto= (chcIdRef*) lstvalpago->GetItemData(item);
				if (keyfieldpagto) {						
					query="INSERT INTO vendapagtos";
					query.append("(idformapagto,idvenda,valor)");
					query.append("VALUES(");
					tmstr=wxString::Format(_("%d"),keyfieldpagto->val);
					query.append(tmstr.ToAscii());
					query.append(",");
					tmstr=wxString::Format(_("%d"),currec);
					query.append(tmstr.ToAscii());
					query.append(",");
					query.append(get_lstctrl_column_text(lstvalpago,item,1).ToAscii());
					query.append(")");
					_execquery(query);
				}
			}
		}
		_db_update(pageid);
	}
	return true;
}


bool VilaVilela::_nextrow(sql_ResultSet  *res) {
#ifdef VILAVIELASQLITE3
	return (sqlite3_step(res->res) == SQLITE_ROW);
#endif
#ifdef VILAVIELAMYSQL
	return (res->res->next());
#endif
#ifdef VILAVIELAPOSTGRESQL
	res->i++;
	res->j=0;
	return (res->i <= PQntuples(res->res));
#endif
}


bool VilaVilela::_prevrow(sql_ResultSet  *res) {
#ifdef VILAVIELASQLITE3
	return false;
#endif
#ifdef VILAVIELAMYSQL
	return (res->res->previous());
#endif
#ifdef VILAVIELAPOSTGRESQL
	res->i--;
	res->j=0;
	return (res->i >=0);
#endif
}

bool VilaVilela::_lastrow(sql_ResultSet  *res) {
#ifdef VILAVIELASQLITE3
	sqlite3_reset(res->res);
	int nrows=0,nrows2=0;
	if (_firstrow(res)) {
		do {
			nrows++;
		}
		while (_nextrow(res));
	}
	sqlite3_reset(res->res);
	if (_firstrow(res)) {
		do {
			nrows2++;
			if (nrows2==nrows)
				return true;
		}
		while (_nextrow(res));
	}
	return false;
#endif
#ifdef VILAVIELAMYSQL
	return (res->res->last());
#endif
#ifdef VILAVIELAPOSTGRESQL
	res->i=PQntuples(res->res);
	res->j=0;
	return (res->i > 0);
#endif
}

bool VilaVilela::_firstrow(sql_ResultSet  *res) {
#ifdef VILAVIELASQLITE3
	sqlite3_reset(res->res);
	return (sqlite3_step(res->res) == SQLITE_ROW);
#endif
#ifdef VILAVIELAMYSQL
	return (res->res->first());
#endif
#ifdef VILAVIELAPOSTGRESQL
	res->i=1;
	res->j=0;
	return (PQntuples(res->res) > 0);
#endif
}

int VilaVilela::_getint(sql_ResultSet  *res,int column) {
#ifdef VILAVIELASQLITE3
	return sqlite3_column_int(res->res, column-1);
#endif
#ifdef VILAVIELAMYSQL
	return res->res->getInt(column);
#endif
#ifdef VILAVIELAPOSTGRESQL
	char *ptrc=PQgetvalue(res->res,res->i-1,column-1);
	int ri=0;
	if(ptrc)ri=atoi(ptrc);
	return ri;
#endif
}

int VilaVilela::_getint(sql_ResultSet  *res,const char *columnname) {
#ifdef VILAVIELASQLITE3
	int N,colcount=sqlite3_column_count(res->res),retint=-1;
	char *colname=0;
	for (N=0;N<colcount;N++) {
		if (strcmp(columnname,sqlite3_column_name(res->res,N))==0) {
			retint=sqlite3_column_int(res->res, N);
			break;
		}
	}
	return retint;
#endif
#ifdef VILAVIELAMYSQL
	return res->res->getInt(columnname);
#endif
#ifdef VILAVIELAPOSTGRESQL
	char *ptrc=PQgetvalue(res->res,res->i-1,PQfnumber(res->res,columnname));
	int ri=0;
	if(ptrc)ri=atoi(ptrc);
	return ri;
#endif
}

wxString VilaVilela::_getstring(sql_ResultSet  *res,int column) {
#ifdef VILAVIELASQLITE3
	return wxString::FromUTF8((const char*)sqlite3_column_text(res->res, column-1));
#endif
#ifdef VILAVIELAMYSQL
	return wxString::FromUTF8(res->res->getString(column).c_str());
#endif
#ifdef VILAVIELAPOSTGRESQL
	return wxString::FromUTF8(PQgetvalue(res->res,res->i-1,column-1));
#endif
}

wxString VilaVilela::_getstring(sql_ResultSet  *res,const char *columnname) {
#ifdef VILAVIELASQLITE3
	int N,colcount=sqlite3_column_count(res->res);
	wxString retstr;
	char *colname=0;
	for (N=0;N<colcount;N++) {
		if (strcmp(columnname,sqlite3_column_name(res->res,N))==0) {
			retstr=wxString::FromUTF8((const char*)sqlite3_column_text(res->res,N));
			break;
		}
	}
	return retstr;
#endif
#ifdef VILAVIELAMYSQL
	return wxString::FromUTF8(res->res->getString(columnname).c_str());
#endif
#ifdef VILAVIELAPOSTGRESQL
	return wxString::FromUTF8(PQgetvalue(res->res,res->i-1,PQfnumber(res->res,columnname)));
#endif
}

void VilaVilela::_deleteresult(sql_ResultSet  **res) {
	delete *res;
}

void VilaVilela:: _delete_prep_stmt(sql_PreparedStatement	**prep_stmt) {
#ifdef VILAVIELASQLITE3
	sqlite3_finalize(*prep_stmt);
#endif
#ifdef VILAVIELAMYSQL
	delete *prep_stmt;
#endif
}


Palavra VilaVilela::_getstringSQL(sql_ResultSet  *res,int column) {
	Palavra str;

#ifdef VILAVIELASQLITE3
	str.append((const char*)sqlite3_column_text(res->res, column-1));
	return str;
#endif
#ifdef VILAVIELAMYSQL
	str.append(res->res->getString(column).c_str());
	return str;
#endif
#ifdef VILAVIELAPOSTGRESQL
	str.append(PQgetvalue(res->res,res->i-1,column-1));
	return str;
#endif
}

Palavra VilaVilela::_getstringSQL(sql_ResultSet  *res,const char *columnname) {
	Palavra retstr;

#ifdef VILAVIELASQLITE3
	int N,colcount=sqlite3_column_count(res->res);
	char *colname=0;
	for (N=0;N<colcount;N++) {
		if (strcmp(columnname,sqlite3_column_name(res->res,N))==0) {
			retstr.append((const char*)sqlite3_column_text(res->res,N));
			break;
		}
	}
#endif
#ifdef VILAVIELAMYSQL
	retstr.append(res->res->getString(columnname).c_str());
#endif
#ifdef VILAVIELAPOSTGRESQL
	retstr.append(PQgetvalue(res->res,res->i-1,PQfnumber(res->res,columnname)));
#endif
	return retstr;
}

double VilaVilela::_getdouble(sql_ResultSet  *res,const char *columnname) {
#ifdef VILAVIELASQLITE3
	int N,colcount=sqlite3_column_count(res->res);
	double retdb;
	char *colname=0;
	for (N=0;N<colcount;N++) {
		if (strcmp(columnname,sqlite3_column_name(res->res,N))==0) {
			retdb=sqlite3_column_double(res->res,N);
			break;
		}
	}
	return retdb;
#endif
#ifdef VILAVIELAMYSQL
	return res->res->getDouble(columnname);
#endif
#ifdef VILAVIELAPOSTGRESQL
	return atof(PQgetvalue(res->res,res->i-1,PQfnumber(res->res,columnname)));
#endif
}

double VilaVilela::_getdouble(sql_ResultSet  *res,int column) {
#ifdef VILAVIELASQLITE3
	return sqlite3_column_double(res->res, column-1);
#endif
#ifdef VILAVIELAMYSQL
	return res->res->getDouble(column);
#endif
#ifdef VILAVIELAPOSTGRESQL
	return atof(PQgetvalue(res->res,res->i-1,column-1));
#endif
}

__DB_FIELD_TYPES VilaVilela::_getColumnType(sql_ResultSet  *res,int iCol) {
	int coltype;
#ifdef VILAVIELASQLITE3
	coltype= sqlite3_column_type(res->res, iCol-1);
	switch (coltype) {
	case SQLITE_INTEGER:
		return __DB_FIELD_TYPE_INT;
	case SQLITE_FLOAT:
		return __DB_FIELD_TYPE_FLOAT;
	case SQLITE3_TEXT:
		return __DB_FIELD_TYPE_STR;
	}
#endif
#ifdef VILAVIELAMYSQL
	sql::ResultSetMetaData *meta;
	meta=res->res->getMetaData();
	coltype= meta->getColumnType(iCol);
	switch (coltype) {
	case DataType::BIT:
	case DataType::TINYINT:
	case DataType::SMALLINT:
	case DataType::MEDIUMINT:
	case DataType::BIGINT:
	case DataType::INTEGER:
		return __DB_FIELD_TYPE_INT;
	case DataType::REAL:
	case DataType::DOUBLE:
	case DataType::DECIMAL:
	case DataType::NUMERIC:
		return __DB_FIELD_TYPE_FLOAT;
	case DataType::CHAR:
	case DataType::VARCHAR:
	case DataType::LONGVARCHAR:
	case DataType::TIMESTAMP:
	case DataType::DATE:
	case DataType::TIME:
		return __DB_FIELD_TYPE_STR;
	}
#endif
#ifdef VILAVIELAPOSTGRESQL
	coltype= PQftype(res->res, iCol-1);
	switch (coltype) {
	case INT2OID:
	case INT4OID:
	case INT8OID:
		return __DB_FIELD_TYPE_INT;
	case FLOAT4OID:
	case FLOAT8OID:
		return __DB_FIELD_TYPE_FLOAT;
	case VARCHAROID:
	case TEXTOID:
	case TEXTARRAYOID:
	case TIMESTAMPOID:
	case CSTRINGARRAYOID:
	case DATEOID:
		return __DB_FIELD_TYPE_STR;
	}
#endif
	return __DB_FIELD_TYPE_INT;
}

int VilaVilela::_getColumnCount(sql_ResultSet  *res) {
#ifdef VILAVIELASQLITE3
	return sqlite3_column_count(res->res);
#endif
#ifdef VILAVIELAMYSQL
	sql::ResultSetMetaData *meta;
	meta=res->res->getMetaData();
	return meta->getColumnCount();
#endif
#ifdef VILAVIELAPOSTGRESQL
	return PQnfields(res->res);
#endif
}

int VilaVilela::_rowsCount(sql_ResultSet  *res) {
#ifdef VILAVIELASQLITE3
	int nrows=0;
	if (_firstrow(res)) {
		do {
			nrows++;
		}
		while (_nextrow(res));
	}
	sqlite3_reset(res->res);
	return nrows;
#endif
#ifdef VILAVIELAMYSQL
	return res->res->rowsCount();
#endif
#ifdef VILAVIELAPOSTGRESQL
	return PQntuples(res->res);
#endif
}

bool VilaVilela::_open_secdb(_DBVAR *dbvar,bool showmsg,bool setflag) {
	if (conexao_de_seguranca)
		return false;
	if (showmsg)
		wxMessageBox(_("O servidor é inacessível ou o endereço do host é inválido, verifique ,\n uma nova conexão com o banco de dados de segurança será estabelecida."));
	_close_db(dbvar);
	if (!	_open_db("seccopydb",dbvar,"127.0.0.1", "root", "dirsicaf","vilaviela.db")) {
		wxMessageBox(_("Erro inesperado, saindo!!!"));
		//exit(0);
		return false;
	}
	if (showmsg)
		wxMessageBox(_("Conexão local de segurança estabelecida."));
	if (setflag)
		conexao_de_seguranca=true;
	return true;
}

bool VilaVilela:: _verificaconexao(_DBVAR *dbvar) {

	if (PQstatus(dbvar->db) != CONNECTION_OK||_execquery("SELECT * FROM crg",false)==PGRES_FATAL_ERROR) {
		if (_open_secdb(dbvar)) {
			_update_db_cache();
			if(db_mode==__DB_MODE_READ)
			 _db_update(_get_pageid());
		}
	}
	else
		if (conexao_de_seguranca) {
			_DBVAR tdbvar;
			if (_open_db(&tdbvar)) {
				conexao_de_seguranca=false;
				_close_db(&tdbvar);

				if (_open_db(dbvar)) {//conexão original ok,atualiza
					_update_db_cache();
					if(db_mode==__DB_MODE_READ)
					_db_update(_get_pageid());
					wxMessageBox(_("Conexão com o servidor reestabelecida, atualizando banco de dados."));
					_DBVAR secdb;
					if (_open_secdb(&secdb,false,false)) {
						Palavra query;
						sql_ResultSet *rvendas,*rsaida;
						query="SELECT * FROM vendas";
						if ((rvendas=_execquerywithresult(&secdb,query))!=NULL&&_nextrow(rvendas)) {
							do {
								query="INSERT INTO vendas(idcliente,data,no_nota,idformapagto,desconto,desconto_percentual) VALUES(";
								query.append(_getstringSQL(rvendas,"idcliente"));
								query.append(",'");
								query.append(_getstringSQL(rvendas,"data"));
								query.append("','");
								query.append(_getstringSQL(rvendas,"no_nota"));
								query.append("',");
								query.append(_getstringSQL(rvendas,"idformapagto"));
								query.append(",");
								query.append(_getstringSQL(rvendas,"desconto"));
								query.append(",");
								query.append(_getstringSQL(rvendas,"desconto_percentual"));
								query.append(")");
								_execquery(query);
								sql_ResultSet *res;
								int idvenda=-1;
								if ((res=_execquerywithresult("SELECT idvenda FROM vendas")) !=NULL) {
									if (_lastrow(res))
										idvenda=_getint(res,1);
									_deleteresult(&res);
								}
								query="SELECT * FROM saida WHERE idvenda=";
								query.append(_getstringSQL(rvendas,"idvenda"));
								if ((rsaida=_execquerywithresult(&secdb,query))!=NULL&&_nextrow(rsaida)) {
									do {
										query="INSERT INTO saida(idvenda,idproduto,quant) VALUES(";
										query.append(idvenda);
										query.append(",");
										query.append(_getstringSQL(rsaida,"idproduto"));
										query.append(",");
										query.append(_getstringSQL(rsaida,"quant"));
										query.append(")");
										_execquery(query);
									}
									while (_nextrow(rsaida));
									_deleteresult(&rsaida);
								}
							}
							while (_nextrow(rvendas));
							_deleteresult(&rvendas);
						}
						_execquery(&secdb,"DELETE FROM saida");
						_execquery(&secdb,"DELETE FROM vendas");
						_close_db(&secdb);
					}
				}
			}
		}
	return true;
}

int VilaVilela::_execquery(_DBVAR *dbvar, const char *queryfields,bool showerrmsg) {
	wxString tmpstr;
	int rc;
#ifdef VILAVIELASQLITE3
	char *zErrMsg = 0;
	rc = sqlite3_exec(dbvar->db, queryfields, NULL, 0, &zErrMsg);
	if (rc!=SQLITE_OK) {
		tmpstr=wxString::FromUTF8(zErrMsg);
		if (showerrmsg)
			wxMessageBox(tmpstr);
		sqlite3_free(zErrMsg);
	}
#endif
#ifdef VILAVIELAMYSQL
	try {
		dbvar->db->execute(queryfields);
	}
	catch (sql::SQLException &e) {
		tmpstr=wxString::FromAscii(e.what());
		if (showerrmsg)
			wxMessageBox(tmpstr);
	}
#endif
#ifdef VILAVIELAPOSTGRESQL
	PGresult   *res;
	res = PQexec(dbvar->db,queryfields);
	rc=PQresultStatus(res);
	if (rc!=PGRES_COMMAND_OK&&rc!=PGRES_TUPLES_OK) {
		tmpstr=wxString::FromUTF8(PQerrorMessage(dbvar->db));
		const char *ptr=PQresultErrorField(res,PG_DIAG_SQLSTATE);
		if (showerrmsg)
			wxMessageBox(tmpstr+_("-Erro=")
			             +(ptr?wxString::Format(_("%d"),((int)*ptr)&0xff):_(""))
			            );
		PQclear(res);
	}

#endif
	return rc;
}

sql_ResultSet *VilaVilela::_execquerywithresult(_DBVAR *dbvar, const char *query) {
	sql_ResultSet *res=new sql_ResultSet();
	wxString tmpstr;
#ifdef VILAVIELASQLITE3
	if (sqlite3_prepare_v2(dbvar->db, query, -1, &res->res, NULL) != SQLITE_OK) {
		tmpstr=wxString::FromUTF8(sqlite3_errmsg(dbvar->db));
		wxMessageBox(tmpstr);
		return NULL;
	}
#endif
#ifdef VILAVIELAMYSQL
	try {
		res->res=dbvar->db->executeQuery(query);
	}
	catch (sql::SQLException &e) {
		tmpstr=wxString::FromUTF8(e.what());
		wxMessageBox(tmpstr);
		return NULL;
	}
#endif
#ifdef VILAVIELAPOSTGRESQL
	res->res = PQexec(dbvar->db,query);
	if (PQresultStatus(res->res) != PGRES_TUPLES_OK) {
		tmpstr=wxString::FromUTF8(PQerrorMessage(dbvar->db));
		const char *ptr=PQresultErrorField(res->res,PG_DIAG_SQLSTATE);
		wxMessageBox(tmpstr+_("-Erro=")
		             +(ptr?wxString::Format(_("%d"),((int)*ptr)&0xff):_(""))

		            );
		PQclear(res->res);
	}

#endif
	return res;
}

int VilaVilela::_execquery(_DBVAR *dbvar, Palavra &queryfields,bool showerrmsg) {
	return _execquery(dbvar, queryfields.c_str(), showerrmsg);
}

sql_ResultSet  *VilaVilela::_execquerywithresult(_DBVAR *dbvar, Palavra &query) {
	return _execquerywithresult(dbvar, query.c_str());
}

int VilaVilela::_execquery(Palavra &queryfields,bool showerrmsg) {
	return _execquery(&glb_stmt,queryfields,showerrmsg);
}

sql_ResultSet *VilaVilela::_execquerywithresult(Palavra &query) {
	return _execquerywithresult(&glb_stmt,query);
}

int VilaVilela::_execquery(const char *queryfields,bool showerrmsg) {
	return _execquery(&glb_stmt,queryfields,showerrmsg);
}

sql_ResultSet  *VilaVilela::_execquerywithresult(const char *query) {
	return _execquerywithresult(&glb_stmt,query);
}

void VilaVilela::_update_db_cache(){
	for (int i=0;i<NUM_TABS;i++) {
		TableInfo *tb=lsttableinfo.find_by_tableid(i);
		FieldInfo *fi;
		if (tb) {
			fi=tb->fields.find_by_name(main_tablesortfield[tb->indtablename]);
			if (fi) {
				seachfieldinfo[tb->indtablename].searchfield=fi;
				seachfieldinfo[tb->indtablename].fi=NULL;
			}
		}
		glb_res[i]=0;
		isfiltered[i]=false;
		_fetch_and_update_gl_res(i,__DB_UPD_MODE_FIRST);
	}
}

void VilaVilela::_close_db(_DBVAR *dbvar) {
#ifdef VILAVIELASQLITE3
	sqlite3_close(dbvar->db);
#endif
#ifdef VILAVIELAMYSQL
	delete dbvar->db;
	delete dbvar->con;
#endif
#ifdef VILAVIELAPOSTGRESQL
	PQfinish(dbvar->db);
#endif
}

bool VilaVilela::_prepareStatement(_DBVAR *dbvar,sql_PreparedStatement **prepstm,const char *prepchar) {
#ifdef VILAVIELASQLITE3
	if (sqlite3_prepare_v2(dbvar->db,prepchar,-1,	prepstm,	NULL)!= SQLITE_OK) {
		return false;
	}
#endif
#ifdef VILAVIELAMYSQL
	*prepstm = dbvar->con->prepareStatement(prepchar);
#endif
#ifdef VILAVIELAPOSTGRESQL
	/*PGresulr *res;
	res = PQprepare(dbvar->db,"",prepchar);
	if (PQresultStatus(res->res) != PGRES_COMMAND_OK){
		tmpstr=wxString::FromUTF8(PQerrorMessage(dbvar->db));
		PQclear(res);
		wxMessageBox(tmpstr);
		return false;
	}*/

#endif
	return true;
}

bool VilaVilela::prep_stmt_execute(sql_PreparedStatement	*prep_stmt) {
	bool retval=true;
#ifdef VILAVIELASQLITE3
	return (sqlite3_step(prep_stmt) == SQLITE_DONE);
#endif
#ifdef VILAVIELAMYSQL
	prep_stmt->execute();
#endif
#ifdef VILAVIELAPOSTGRESQL

#endif
	return retval;
}

bool VilaVilela::prep_stmt_setString(sql_PreparedStatement	*prep_stmt,int index, const Palavra &val) {
	bool retval=true;
#ifdef VILAVIELASQLITE3
	return (sqlite3_bind_text(prep_stmt, index,val.c_str(),-1,SQLITE_STATIC)== SQLITE_OK);
#endif
#ifdef VILAVIELAMYSQL
	prep_stmt->setString(index, val);
#endif
	return retval;
}

bool VilaVilela::prep_stmt_setInt(sql_PreparedStatement	*prep_stmt,int index,  int val) {
	bool retval=true;
#ifdef VILAVIELASQLITE3
	return (sqlite3_bind_int(prep_stmt, index,val)== SQLITE_OK);
#endif
#ifdef VILAVIELAMYSQL
	prep_stmt->setInt(index,val);
#endif
	return retval;
}

bool VilaVilela::prep_stmt_setDouble(sql_PreparedStatement	*prep_stmt,int index,  float val) {
	bool retval=true;
#ifdef VILAVIELASQLITE3
	return (sqlite3_bind_double(prep_stmt, index,(double)val)== SQLITE_OK);
#endif
#ifdef VILAVIELAMYSQL
	prep_stmt->setDouble(index,val);
#endif
	return retval;
}

#define TMPBKUPFNAME "tmpbackup.vla"

void VilaVilela::_atualiza_bkupdb() {
	if (conexao_de_seguranca)
		return;
	_DBVAR secdb;
	if (_open_db("seccopydb",&secdb,"127.0.0.1", "root", "dirsicaf","seccopy.db")) {
		_execquery(&secdb,"USE seccopydb",false);
		Palavra query,tbquery,oquer,prefix,postfix,colquery,datatype;
		sql_ResultSet *res,*tabledata,*columns;
		wxString filerestore,tmpstr;
		bool needaspas;
		tbquery="SELECT relname FROM pg_stat_user_tables WHERE schemaname='public' ORDER BY relid";
		Palavra tablename,fbkname;
		if ((res=_execquerywithresult(tbquery)) !=NULL&&_nextrow(res)) {
			do {
				tablename=_getstringSQL(res,1);
				query="DROP TABLE ";
				query.append(tablename);
				query.append(" CASCADE");
				_execquery(&secdb,query,false);
			}
			while (_nextrow(res));
			_create_tables(&secdb);
			if (_firstrow(res)) {
				do {
					tablename=_getstringSQL(res,1);
					if (tablename!="vendas"&&tablename!="r02"&&tablename!="r03"&&tablename!="r04"&&tablename!="r05"&&
					    tablename!="r06"&&tablename!="r07"&&tablename!="cdc"&&tablename!="crg"&&tablename!="saida"&&tablename!="vendapagtos") {
						query="SELECT column_name,udt_name FROM information_schema.columns WHERE table_name='";
						query.append(tablename);
						query.append("'");
						prefix="INSERT INTO ";
						prefix.append(tablename);
						prefix.append("(");
						if ((columns=_execquerywithresult(query)) !=NULL&&_nextrow(columns)) {
							prefix.append(_getstringSQL(columns,1));
							while (_nextrow(columns)) {
								prefix.append(",");
								prefix.append(_getstringSQL(columns,1));
							}
							prefix.append(") VALUES(");

							query="SELECT * FROM ";
							query.append(tablename);
							if ((tabledata=_execquerywithresult(query)) !=NULL&&_nextrow(tabledata)) {
								do {
									postfix="";
									if (_firstrow(columns)) {
										datatype=_getstringSQL(columns,2);
										needaspas=(datatype=="date"||datatype=="timestamp"||datatype=="varchar");
										if (needaspas)
											postfix.append("'");
										postfix.append(_getstringSQL(tabledata,_getstringSQL(columns,1).c_str()));
										if (needaspas)
											postfix.append("'");
										while (_nextrow(columns)) {
											postfix.append(",");
											datatype=_getstringSQL(columns,2);
											needaspas=(datatype=="date"||datatype=="timestamp"||datatype=="varchar");
											colquery=_getstringSQL(tabledata,_getstringSQL(columns,1).c_str());
											if (colquery=="") {
												if (datatype=="date")
													colquery="2000-01-01";
												else
													colquery="0";
											}
											if (needaspas)
												postfix.append("'");
											postfix.append(colquery);
											if (needaspas)
												postfix.append("'");
										}
										postfix.append(")");
										query=prefix+postfix;
										_execquery(&secdb,query);
									}
								}
								while (_nextrow(tabledata));
								_deleteresult(&tabledata);
							}
							_deleteresult(&columns);
						}
					}
				}
				while (_nextrow(res));
				_deleteresult(&res);
			}
		}
		_close_db(&secdb);
	}
}


bool VilaVilela::_open_db(const char *_dbname,_DBVAR *dbvar,const char *host,const char *user,const char *password,const char *sqlitedbname) {
	bool retval=true;
	wxString tmpstr;
#ifdef VILAVIELASQLITE3
	char *zErrMsg = 0;
	int rc;
	rc = sqlite3_open(sqlitedbname, &dbvar->db);
	if (rc) {
		tmpstr=wxString::FromUTF8(sqlite3_errmsg(dbvar->db));
		wxMessageBox(tmpstr);
		sqlite3_close(dbvar->db);
		retval= false;
	}
#endif
#ifdef VILAVIELAMYSQL
	sql::Driver *driver;
	try {
		driver = get_driver_instance();
		dbvar->con = driver->connect(host, user,password);
		if (!(dbvar->con)) {
			wxMessageBox(_("Falha ao conectar com o mysql"));
		}
		dbvar->db=(dbvar->con)->createStatement();
	}
	catch (sql::SQLException &e) {
		retval= false;
		tmpstr=wxString::FromUTF8(e.what());
		wxMessageBox(tmpstr);
		try {
			delete(dbvar->con);
		}
		catch (sql::SQLException &e) {
			tmpstr=wxString::FromUTF8(e.what());
			wxMessageBox(tmpstr);
		}
	}
#endif
#ifdef VILAVIELAPOSTGRESQL
	char conninfo[265];
	sprintf(conninfo,"user = postgres password = %s hostaddr = %s dbname = %s",password,host,_dbname);
	dbvar->db = PQconnectdb(conninfo);
	if (PQstatus(dbvar->db) != CONNECTION_OK) {
		sprintf(conninfo,"user = postgres password = %s hostaddr = %s dbname = postgres",password,host,_dbname);
		dbvar->db = PQconnectdb(conninfo);
		if (PQstatus(dbvar->db) == CONNECTION_OK) {
			char query[128];
			sprintf(query,"CREATE DATABASE "IF_NOT_EXISTS" %s",_dbname);
			_execquery(query,true);
			PQfinish(dbvar->db);
			sprintf(conninfo,"user = postgres password = %s hostaddr = %s dbname = %s",password,host,_dbname);
			dbvar->db = PQconnectdb(conninfo);
			if (PQstatus(dbvar->db) != CONNECTION_OK) {
				tmpstr=wxString::FromUTF8(PQerrorMessage(dbvar->db));
				wxMessageBox(tmpstr);
				retval= false;
			}
		}
		else
			retval= false;
	}
#endif
	return  retval;
}

bool VilaVilela::_open_db(_DBVAR *dbvar,bool setflag) {
	if (_open_db("vila_viela_db",dbvar,db_host, "root", "dirsicaf","vilaviela.db")) {
		if(setflag)
		conexao_de_seguranca=false;
		return true;
	}
	else
		return _open_secdb(dbvar);
	return false;
}

double VilaVilela::_retorna_estoque(int idproduto) {
	Palavra query;
	sql_ResultSet  *res;
	query="SELECT quant FROM produto_entrada WHERE idproduto=";
	query.append(idproduto);
	double quantestoque=0;
	if ((res=_execquerywithresult(query)) !=0) {
		while (_nextrow(res)) {
			quantestoque+=_getdouble(res,1);
		}
		_deleteresult(&res);
		query="SELECT quant FROM saida WHERE idproduto=";
		query.append(idproduto);
		if ((res=_execquerywithresult(query)) !=0) {
			while (_nextrow(res)) {
				quantestoque-=_getdouble(res,1);
			}
			_deleteresult(&res);
		}
	}
	return quantestoque;
}

void VilaVilela::_ini_default_table_values() {
	Palavra query;
	sql_ResultSet *res;
	wxString tstring;
	query="SELECT * FROM categoria";

	if ((res=_execquerywithresult(query))==NULL||!_nextrow(res)) {
		_execquery("INSERT INTO categoria(descricao) VALUES('GRÃOS')");
		_execquery("INSERT INTO categoria(descricao) VALUES('FARINÁCEOS')");
		_execquery("INSERT INTO categoria(descricao) VALUES('FRUTAS')");
		_execquery("INSERT INTO categoria(descricao) VALUES('VERDURAS')");
		_execquery("INSERT INTO categoria(descricao) VALUES('LEGUMES')");
		_execquery("INSERT INTO categoria(descricao) VALUES('PÃES')");
		_execquery("INSERT INTO categoria(descricao) VALUES('SALAMERIA')");
		_execquery("INSERT INTO categoria(descricao) VALUES('CHÁS')");
		_execquery("INSERT INTO categoria(descricao) VALUES('DOCES')");
		_execquery("INSERT INTO categoria(descricao) VALUES('ESPECIAIS')");
	}
	else
		_deleteresult(&res);

	query="SELECT * FROM CRG";
	if ((res=_execquerywithresult(query))==NULL||!_nextrow(res)) {
		query="INSERT INTO CRG(quant) VALUES(1)";
		_execquery(query);
	}
	else
		_deleteresult(&res);
	query="SELECT * FROM CDC";
	if ((res=_execquerywithresult(query))==NULL||!_nextrow(res)) {
		query="INSERT INTO CDC(quant) VALUES(1)";
		_execquery(query);
	}
	else
		_deleteresult(&res);
	query="SELECT * FROM unidade";
	if ((res=_execquerywithresult(query))==NULL||!_nextrow(res)) {
		query="INSERT INTO unidade(descricao,abrev) VALUES('Unidade','un')";
		_execquery(query);
		query="INSERT INTO unidade(descricao,abrev) VALUES('Quilograma','kg')";
		_execquery(query);
	}
	else
		_deleteresult(&res);
	query="SELECT * FROM aliquotas";
	if ((res=_execquerywithresult(query))==NULL||!_nextrow(res)) {
		query="INSERT INTO aliquotas(descricao,abrev) VALUES('Isentos ICMS tipo I','II')";
		_execquery(query);
		query="INSERT INTO aliquotas(descricao,abrev) VALUES('Substituição Tributária ICMS tipo F1','FF')";
		_execquery(query);
		query="INSERT INTO aliquotas(descricao,abrev) VALUES('Não tributável ICMS  tipo N','NN')";
		_execquery(query);
		query="INSERT INTO aliquotas(descricao,abrev) VALUES('ICMS ( 7% )','0700')";
		_execquery(query);
	 query="INSERT INTO aliquotas(descricao,abrev) VALUES('ICMS ( 12% )','1200')";
		_execquery(query);
		query="INSERT INTO aliquotas(descricao,abrev,tipo) VALUES('ISSQN ( 3% )','0300',1)";
		_execquery(query);
	}
	else
		_deleteresult(&res);
	query="SELECT * FROM formapagto";
	if ((res=_execquerywithresult(query))==NULL||!_nextrow(res)) {
		query="INSERT INTO formapagto(descricao) VALUES('Dinheiro')";
		_execquery(query);
		query="INSERT INTO formapagto(descricao) VALUES('Cheque')";
		_execquery(query);
		query="INSERT INTO formapagto(descricao) VALUES('Visa')";
		_execquery(query);
		query="INSERT INTO formapagto(descricao) VALUES('Mastercard')";
		_execquery(query);
	}
	else
		_deleteresult(&res);
	query="SELECT * FROM cliente";
	if ((res=_execquerywithresult(query))==NULL||!_nextrow(res)) {
		query="INSERT INTO cliente(nome) VALUES(' ao consumidor')";
		_execquery(query);
	}
	else
		_deleteresult(&res);
}

bool VilaVilela::_create_tables(_DBVAR *dbvar) {
	bool retval=true;
	_execquery(dbvar,"CREATE TABLE  IF NOT EXISTS categoria (idcategoria "INT_PRIMARY_KEY_NOT_NULL" "AUTO_INCREMENT" ,descricao VARCHAR(45) NULL )"DB_ENGINE);

	_execquery(dbvar,"CREATE  TABLE  IF NOT EXISTS  R02 (idR02 "INT_PRIMARY_KEY_NOT_NULL" "AUTO_INCREMENT"  ,Numero_de_fabricacao VARCHAR(21) NULL ,MF_adicional VARCHAR(2) NULL ,Modelo_do_ECF VARCHAR(21) NULL ,Numero_do_usuario INT NULL ,CRZ INT NULL ,COO INT NULL ,CRO INT NULL ,Data_do_movimento INT NULL ,Data_de_emissao INT NULL ,Hora_de_emissao INT NULL ,Venda_Bruta_Diaria INT NULL ,Parametro_desconto_ISSQN VARCHAR(2) NULL  )"DB_ENGINE"");

	_execquery(dbvar,"CREATE  TABLE  IF NOT EXISTS  R03 (idR03 "INT_PRIMARY_KEY_NOT_NULL" "AUTO_INCREMENT"  ,Numero_de_fabricacao VARCHAR(21) NULL ,MF_adicional VARCHAR(2) NULL ,Modelo_do_ECF VARCHAR(21) NULL ,Numero_do_usuario INT NULL ,CRZ INT NULL ,Totalizador_Parcial VARCHAR(8) NULL ,Valor_acumulado INT NULL  )"DB_ENGINE"");

	_execquery(dbvar,"CREATE  TABLE  IF NOT EXISTS  R04 (idR04 "INT_PRIMARY_KEY_NOT_NULL" "AUTO_INCREMENT"  ,Numero_de_fabricacao VARCHAR(21) NULL ,MF_adicional VARCHAR(2) NULL ,Modelo_do_ECF VARCHAR(21) NULL ,Numero_do_usuario INT NULL ,CCF_CVC_ou_CBP INT NULL ,COO INT NULL ,Data_de_inicio_da_emissao INT NULL ,Subtotal_do_Documento INT NULL ,Desc_sobre_subtotal INT NULL ,Ind_do_Tipo_de_Desc_sobre_subtotal VARCHAR(2) DEFAULT 'V' ,Acrescimo_sobre_subtotal	 INT DEFAULT 0 ,Ind_do_Tipo_de_Acresc_sobre_subtotal		 VARCHAR(2) DEFAULT 'V' ,Valor_Total_Liquido		INT NULL ,Ind_de_Cancelamento		 VARCHAR(2) NULL ,Cancelamento_de_Acresc_no_Subtotal		INT DEFAULT 0 ,Ordem_de_aplicacao_de_Desc_e_Acresc VARCHAR(2) DEFAULT 'D' ,Nome_do_adquirente VARCHAR(40) NULL ,CPF_CNPJ_do_adquirente VARCHAR(20) NULL ,Meio_de_pagamento VARCHAR(45) NULL )"DB_ENGINE"");

	_execquery(dbvar,"CREATE  TABLE  IF NOT EXISTS  R05 (idR05 "INT_PRIMARY_KEY_NOT_NULL" "AUTO_INCREMENT"  ,Numero_de_fabricacao VARCHAR(21) NULL ,MF_adicional VARCHAR(2) NULL ,Modelo_do_ECF VARCHAR(21) NULL ,Numero_do_usuario INT NULL ,COO INT NULL ,CCF_CVC_ou_CBP INT NULL ,Numero_do_item INT NULL ,Cod_do_Produto_ou_Servico VARCHAR(15) NULL ,Descricao VARCHAR(101) NULL ,Quantidade INT NULL ,Unidade		 VARCHAR(4) NULL ,Valor_unitario		INT NULL ,Desconto_sobre_item		INT NULL ,Acrescimo_sobre_item		INT DEFAULT 0 ,Valor_total_liquido		INT NULL ,Totalizador_parcial		 VARCHAR(8) NULL ,Indicador_de_cancelamento		 VARCHAR(2) NULL ,Quantidade_cancelada		INT DEFAULT 0 ,Valor_cancelado		INT DEFAULT 0 ,Cancelamento_de_acrescimo_no_item		INT DEFAULT 0 ,IAT VARCHAR(2) DEFAULT 'T' ,IPPT VARCHAR(2) DEFAULT 'T' ,Casas_decimais_da_quantidade INT NULL ,Casas_decimais_de_valor_unitario INT DEFAULT 2 )"DB_ENGINE"");

	_execquery(dbvar,"CREATE  TABLE  IF NOT EXISTS  R06 (idR06 "INT_PRIMARY_KEY_NOT_NULL" "AUTO_INCREMENT"  ,Numero_de_fabricacao VARCHAR(21) NULL ,MF_adicional VARCHAR(2) NULL ,Modelo_do_ECF VARCHAR(21) NULL ,Numero_do_usuario INT NULL ,COO INT NULL ,GNF INT NULL ,CRG INT NULL ,CDC INT NULL ,Denominacao		 VARCHAR(4) NULL ,Data_final_de_emissao		INT NULL ,Hora_final_de_emissao		INT NULL  )"DB_ENGINE"");

	_execquery(dbvar,"CREATE  TABLE  IF NOT EXISTS  R07 (idR07 "INT_PRIMARY_KEY_NOT_NULL" "AUTO_INCREMENT"  ,Numero_de_fabricacao VARCHAR(21) NULL ,MF_adicional VARCHAR(2) NULL ,Modelo_do_ECF VARCHAR(21) NULL ,Numero_do_usuario INT NULL ,COO INT NULL ,CCF INT NULL ,GNF INT NULL ,Meio_de_pagamento VARCHAR(16) NULL ,Valor_pago INT NULL ,Indicador_de_estorno VARCHAR(2) DEFAULT 'N' ,Valor_estornado INT NULL  )"DB_ENGINE"");

	_execquery(dbvar,"CREATE  TABLE IF NOT EXISTS ECFS (id "INT_PRIMARY_KEY_NOT_NULL" "AUTO_INCREMENT"  ,no_serie VARCHAR(45) NULL ,md5 VARCHAR(17) )"DB_ENGINE"");

	_execquery(dbvar,"CREATE  TABLE IF NOT EXISTS CRG (quant INT NOT NULL ,md5 VARCHAR(17),PRIMARY KEY (quant) )"DB_ENGINE"");

	_execquery(dbvar,"CREATE  TABLE IF NOT EXISTS CDC (quant INT NOT NULL ,md5 VARCHAR(17),PRIMARY KEY (quant) )"DB_ENGINE"");

	_execquery(dbvar,"CREATE  TABLE IF NOT EXISTS unidade (idunidade "INT_PRIMARY_KEY_NOT_NULL" "AUTO_INCREMENT" ,descricao VARCHAR(45) NULL ,abrev VARCHAR(16) NULL ,tipo VARCHAR(4) NULL DEFAULT 'I' )"DB_ENGINE"");

	_execquery(dbvar,"CREATE TABLE IF NOT EXISTS fornecedores (idfornecedor "INT_PRIMARY_KEY_NOT_NULL" "AUTO_INCREMENT",nome VARCHAR(125) NULL ,endr VARCHAR(45) NULL ,complemento VARCHAR(45) NULL ,email VARCHAR(45) NULL ,contato VARCHAR(45) NULL ,cnpj VARCHAR(45) NULL  )"DB_ENGINE"");


	_execquery(dbvar,"CREATE  TABLE IF NOT EXISTS aliquotas (idaliquota "INT_PRIMARY_KEY_NOT_NULL" "AUTO_INCREMENT" ,descricao VARCHAR(45) NULL ,abrev VARCHAR(16) NULL,tipo INT NOT NULL DEFAULT 0 )");

	_execquery(dbvar,"CREATE  TABLE IF NOT EXISTS produtos (idproduto "INT_PRIMARY_KEY_NOT_NULL" "AUTO_INCREMENT" ,nome VARCHAR(45) NULL ,descricao VARCHAR(45) NULL ,barcode VARCHAR(45) NULL ,idunidade INT NULL ,val_unit_venda FLOAT NULL ,icms VARCHAR(6) NULL DEFAULT 0 ,image VARCHAR(45) NULL ,idcategoria INT NULL ,sugestao INT NULL DEFAULT 0,destaque INT NULL DEFAULT 0,idaliquota INT NULL,iat VARCHAR(2) DEFAULT 'T', ippt VARCHAR(2) DEFAULT 'T',FOREIGN KEY (idunidade )REFERENCES unidade (idunidade)ON DELETE NO ACTION ON UPDATE NO ACTION,FOREIGN KEY (idaliquota )REFERENCES aliquotas (idaliquota)ON DELETE NO ACTION ON UPDATE NO ACTION,CONSTRAINT _barcode UNIQUE(barcode))"DB_ENGINE"");

	_execquery(dbvar,"CREATE  TABLE IF NOT EXISTS cliente (idcliente "INT_PRIMARY_KEY_NOT_NULL" "AUTO_INCREMENT",nome VARCHAR(45) NULL ,endr VARCHAR(45) NULL ,complemento VARCHAR(45) NULL ,email VARCHAR(45) NULL ,data_nasc DATE NULL ,cpf VARCHAR(45) NULL  )"DB_ENGINE"");

	_execquery(dbvar,"CREATE  TABLE IF NOT EXISTS fones_fornec (idfones_fornec "INT_PRIMARY_KEY_NOT_NULL" "AUTO_INCREMENT" ,idfornecedor INT NULL ,numero VARCHAR(45) NULL ,FOREIGN KEY (idfornecedor )REFERENCES fornecedores (idfornecedor )ON DELETE NO ACTION ON UPDATE NO ACTION)"DB_ENGINE"");

	_execquery(dbvar,"CREATE  TABLE IF NOT EXISTS compras (idcompra "INT_PRIMARY_KEY_NOT_NULL" "AUTO_INCREMENT" ,idfornecedor INT NULL ,data "DATETIME" NULL ,no_nota VARCHAR(45) NULL ,FOREIGN KEY (idfornecedor )REFERENCES fornecedores (idfornecedor )ON DELETE NO ACTION ON UPDATE NO ACTION)"DB_ENGINE"");

	_execquery(dbvar,"CREATE  TABLE IF NOT EXISTS produto_entrada (idproduto_entrada "INT_PRIMARY_KEY_NOT_NULL" "AUTO_INCREMENT" ,idproduto INT NOT NULL ,idcompra INT NULL ,quant FLOAT NULL ,val_unit_compra FLOAT NULL ,FOREIGN KEY (idproduto )REFERENCES produtos (idproduto )ON DELETE NO ACTION ON UPDATE NO ACTION,FOREIGN KEY (idcompra )REFERENCES compras (idcompra )ON DELETE NO ACTION ON UPDATE NO ACTION)"DB_ENGINE"");

	_execquery(dbvar,"CREATE  TABLE IF NOT EXISTS fones_cliente (idfones_cliente "INT_PRIMARY_KEY_NOT_NULL" "AUTO_INCREMENT" ,idcliente INT NULL ,numero VARCHAR(45) NULL ,FOREIGN KEY (idcliente )REFERENCES cliente (idcliente )ON DELETE NO ACTION ON UPDATE NO ACTION)"DB_ENGINE"");

		
	_execquery(dbvar,"CREATE  TABLE IF NOT EXISTS formapagto (idformapagto "INT_PRIMARY_KEY_NOT_NULL" "AUTO_INCREMENT"  ,descricao VARCHAR(45) NULL  )"DB_ENGINE"");

	_execquery(dbvar,"CREATE  TABLE IF NOT EXISTS vendas (idvenda "INT_PRIMARY_KEY_NOT_NULL" "AUTO_INCREMENT",idcliente INT NULL DEFAULT NULL ,data "DATETIME" NULL DEFAULT NULL ,no_nota VARCHAR(45) NULL DEFAULT NULL ,idformapagto INT NULL ,nota_emitida INT NULL DEFAULT 0 ,desconto FLOAT NULL DEFAULT 0,desconto_percentual INT NULL DEFAULT 1,FOREIGN KEY (idcliente )REFERENCES cliente (idcliente )ON DELETE NO ACTION ON UPDATE NO ACTION,FOREIGN KEY (idformapagto )REFERENCES formapagto (idformapagto )ON DELETE NO ACTION ON UPDATE NO ACTION)"DB_ENGINE"");

	_execquery(dbvar,"CREATE  TABLE IF NOT EXISTS vendapagtos (idvendapagtos "INT_PRIMARY_KEY_NOT_NULL" "AUTO_INCREMENT" ,idformapagto INT NULL ,idvenda INT NULL ,valor FLOAT NULL DEFAULT NULL ,FOREIGN KEY (idvenda )REFERENCES vendas (idvenda )ON DELETE NO ACTION ON UPDATE NO ACTION)"DB_ENGINE"");

	_execquery(dbvar,"CREATE  TABLE IF NOT EXISTS saida (idsaida "INT_PRIMARY_KEY_NOT_NULL" "AUTO_INCREMENT" ,idvenda INT NULL DEFAULT NULL ,idproduto INT NULL DEFAULT NULL ,quant FLOAT NULL DEFAULT NULL ,FOREIGN KEY (idvenda )REFERENCES vendas (idvenda )ON DELETE NO ACTION ON UPDATE NO ACTION,FOREIGN KEY (idproduto )REFERENCES produtos (idproduto )ON DELETE NO ACTION ON UPDATE NO ACTION)"DB_ENGINE"");

	return  retval;
}

bool VilaVilela::_create_tables_and_db() {
	bool retval=true;
	_execquery("CREATE DATABASE "IF_NOT_EXISTS" vila_viela_db",false);
	_execquery("USE vila_viela_db",false);
	_create_tables(&glb_stmt);

	_ini_default_table_values();
	return  retval;
}
