//---------------------------------------------------------------------------

#ifndef un_Data1H
#define un_Data1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.UI.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Phys.MySQL.hpp>
#include <FireDAC.Phys.MySQLDef.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Def.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Pool.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.VCLUI.Wait.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Stan.Param.hpp>
//---------------------------------------------------------------------------
class TData1 : public TDataModule
{
__published:	// IDE-managed Components
	TFDConnection *Conexao;
	TFDPhysMySQLDriverLink *FDPhysMySQLDriverLink1;
	TFDGUIxWaitCursor *FDGUIxWaitCursor1;
	TFDTransaction *FDTransaction1;
	TDataSource *DataExcluir;
	TFDQuery *tbExcluir;
	TDataSource *DataControleArquivos;
	TFDQuery *tbControleArquivos;
	TFDAutoIncField *tbControleArquivosCODIGO;
	TStringField *tbControleArquivosNOME_ARQUIVO;
	TStringField *tbControleArquivosLOCALIZACAO;
	TDateField *tbControleArquivosDATA_PROCESSAMENTO;
	TTimeField *tbControleArquivosHORA_PROCESSAMENTO;
	TSingleField *tbControleArquivosCOD_ADIQUIRENTE;
	TStringField *tbControleArquivosCNPJ_CLIENTE;
	TDateField *tbControleArquivosDATA_ARQUIVO;
	TDateField *tbControleArquivosDATA_MENOR_VENDA;
	TDateField *tbControleArquivosDATA_MAIOR_VENDA;
	TDateField *tbControleArquivosDATA_MENOR_PAGAMENTO;
	TDateField *tbControleArquivosDATA_MAIOR_PAGAMENTO;
	TStringField *tbControleArquivosESTABELECIMENTO;
	TStringField *tbControleArquivosARQUIVO_COM_FALHA;
	TStringField *tbControleArquivosCONFIRMADO;
	TDataSource *DataClientes;
	TFDQuery *tbClientes;
	TStringField *tbClientesNOME;
	TStringField *tbClientesNOME_FANTASIA;
	TSingleField *tbClientesCOD_TIPO_PESSOA;
	TStringField *tbClientesENDERECO;
	TStringField *tbClientesCOMPLEMENTO;
	TSingleField *tbClientesCOD_BAIRRO;
	TSingleField *tbClientesCOD_CIDADE;
	TSingleField *tbClientesCOD_UF;
	TSingleField *tbClientesCOD_PAIS;
	TStringField *tbClientesCEP;
	TStringField *tbClientesFONE1;
	TStringField *tbClientesFONE2;
	TStringField *tbClientesRAMAL1;
	TStringField *tbClientesRAMAL2;
	TStringField *tbClientesTEL0800;
	TStringField *tbClientesCONTATO1;
	TStringField *tbClientesCONTATO2;
	TStringField *tbClientesCELULAR1;
	TStringField *tbClientesCELULAR2;
	TStringField *tbClientesEMAIL;
	TStringField *tbClientesCPF_CNPJ;
	TStringField *tbClientesINSC_ESTADUAL;
	TMemoField *tbClientesOBS;
	TStringField *tbClientesEMAIL2;
	TStringField *tbClientesNUMERO;
	TStringField *tbClientesSALA_LOJA;
	TStringField *tbClientesHOME_PAGE;
	TStringField *tbClientesDDD;
	TStringField *tbClientesDDI;
	TDateField *tbClientesDATA_CADASTRO;
	TDateField *tbClientesDATA_ALTERACAO;
	TMemoField *tbClientesSERVICOS;
	TSingleField *tbClientesN_ATENDIMENTOS;
	TSingleField *tbClientesCOD_FUNCIONARIO;
	TStringField *tbClientesIMPRIMIR;
	TBlobField *tbClientesFOTO;
	TStringField *tbClientesFLAG_CONTATO;
	TDateField *tbClientesDATA_NASC;
	TStringField *tbClientesTIPO_CLIENTE;
	TSingleField *tbClientesLIMITE_CREDITO;
	TIntegerField *tbClientesMES_ANIVERSARIO;
	TDateField *tbClientesDATA_ULTIMA_COMPRA;
	TDateField *tbClientesDATA_ULTIMO_SERVICO;
	TStringField *tbClientesRESTRICAO_INTERNA;
	TIntegerField *tbClientesNUM_OCORRENCIAS;
	TIntegerField *tbClientesNUM_OCORRENCIAS_PEND;
	TStringField *tbClientesNOTIF_CLIENTE;
	TDateField *tbClientesULTIMO_CONTATO;
	TSingleField *tbClientesCOD_ALTERNATIVO;
	TStringField *tbClientesCONTROLA_FIDELIDADE;
	TStringField *tbClientesMOTIVO_RESTRICAO;
	TSingleField *tbClientesTOTAL_PONTOS;
	TSingleField *tbClientesTOTAL_CREDITO;
	TStringField *tbClientesLISTA_NEGRA;
	TMemoField *tbClientesMOTIVO_LISTA_NEGRA_EXCLUSAO;
	TDateField *tbClientesDATA_ULT_CONTATO;
	TSingleField *tbClientesCOD_STATUS_TRANSMISSAO;
	TStringField *tbClientesSUPORTE_BLOQUEADO;
	TSingleField *tbClientesCOD_CATEGORIA_CLIENTE;
	TStringField *tbClientesCODIGO_ANTERIOR;
	TFloatField *tbClientesSALDO_TOTAL;
	TFloatField *tbClientesSALDO_UTILIZADO;
	TFloatField *tbClientesSALDO_DISPONIVEL;
	TSingleField *tbClientesTAXA_JUROS;
	TStringField *tbClientesUSUARIO;
	TStringField *tbClientesSENHA;
	TStringField *tbClientesBLOQUEADO;
	TSingleField *tbClientesCOD_ERP;
	TDateField *tbClientesDATA_ULTIMO_LOGIN;
	TIntegerField *tbClientesDIAS_SEM_LOGAR;
	TSingleField *tbClientesCOD_FUNCIONARIO_INTEGRACAO;
	TSingleField *tbClientesCOD_COMERCIAL;
	TStringField *tbClientesACCESS_TOKEN;
	TStringField *tbClientesREFRESH_TOKEN;
	TStringField *tbClientesREGISTER_ID;
	TStringField *tbClientesMAIN_MERCHANT_ID;
	TIntegerField *tbClientesCOD_CREDENCIMANTO;
	TStringField *tbClientesGERA_PGTO_AUTO;
	TIntegerField *tbClientesDIAS_AUTO;
	TStringField *tbClientesCAMPO_ADICIONAL1;
	TStringField *tbClientesCAMPO_ADICIONAL2;
	TStringField *tbClientesCAMPO_ADICIONAL3;
	TStringField *tbClientesINTEGRA_DIVERGENTE;
	TStringField *tbClientesINTEGRACAO_HABILITADA;
	TStringField *tbClientesINTEGRA_VENDAS;
	TStringField *tbClientesINTEGRA_RECEBIMENTOS;
	TTimeField *tbClientesHORA_RETORNO_VENDA;
	TTimeField *tbClientesHORA_RETORNO_PAGAMENTO;
	TIntegerField *tbClientesDIAS_RETORNO_BAIXA;
	TIntegerField *tbClientesDIAS_RETORNO_VENDA;
	TStringField *tbClientesARQUIVOS_PROCESSADOS;
	TStringField *tbClientesINTEGRACAO_GLOBAL;
	TFDAutoIncField *tbClientesCODIGO;
	TDataSource *DataFeriados;
	TFDQuery *tbFeriados;
	TDateTimeField *tbFeriadosDATA;
	TStringField *tbFeriadosDIA_SEMANA;
	TStringField *tbFeriadosDESCRICAO_FERIADO;
	TDateField *tbFeriadosDATA_FERIADO;
	TDataSource *DataGrupos;
	TFDQuery *tbGrupos;
	TFDAutoIncField *tbGruposCODIGO;
	TSingleField *tbGruposCOD_CLIENTE;
	TStringField *tbGruposNOME_EMPRESA;
	TStringField *tbGruposCNPJ;
	TSingleField *tbGruposCOD_FUNCIONARIO_RESP;
	TDateField *tbGruposDATA_CADASTRO;
	TTimeField *tbGruposHORA_CADASTRO;
	TStringField *tbGruposID_ERP;
	TStringField *tbGruposID_ERP_EXT;
	TStringField *tbGruposVINCULO_API_PAG_SEGURO;
	TIntegerField *tbGruposQUANTIDADE_VINCULOS_API;
	TDataSource *DataDomicilioCliente;
	TFDQuery *tbDomicilioCliente;
	TFDAutoIncField *tbDomicilioClienteCODIGO;
	TSingleField *tbDomicilioClienteCOD_CLIENTE;
	TSingleField *tbDomicilioClienteCOD_GRUPO;
	TStringField *tbDomicilioClienteCNPJ;
	TStringField *tbDomicilioClienteBANCO;
	TSingleField *tbDomicilioClienteCOD_BANCO;
	TStringField *tbDomicilioClienteAGENCIA;
	TStringField *tbDomicilioClienteCONTA;
	TSingleField *tbDomicilioClienteCOD_ADQUIRENTE;
	TDataSource *DataControleAjustes;
	TFDQuery *tbControleAjustes;
	TFDAutoIncField *tbControleAjustesCODIGO;
	TSingleField *tbControleAjustesCOD_ADQUIRENTE;
	TStringField *tbControleAjustesCODIGO_OPERADORA;
	TStringField *tbControleAjustesDESCRICAO_OPERADORA;
	TSingleField *tbControleAjustesCOD_TIPO_AJUSTE_SISTEMA;
	TDateField *tbControleAjustesDATA_CADASTRO;
	TDateField *tbControleAjustesDATA_ALTERACAO;
	TSingleField *tbControleAjustesCOD_FUNCIONARIO_RESP;
	TStringField *tbControleAjustesDESCRICAO_TIPO_AJUSTE_SISTEMA;
	TDataSource *DataPagamentosOperadoras;
	TFDQuery *tbPagamentosOperadoras;
	TFDAutoIncField *tbPagamentosOperadorasCODIGO;
	TDateField *tbPagamentosOperadorasDATA_PROCESSAMENTO;
	TTimeField *tbPagamentosOperadorasHORA_PROCESSAMENTO;
	TStringField *tbPagamentosOperadorasID_LOJA;
	TFloatField *tbPagamentosOperadorasVALOR_BRUTO;
	TFloatField *tbPagamentosOperadorasVALOR_DESCONTO;
	TFloatField *tbPagamentosOperadorasVALOR_LIQUIDO;
	TStringField *tbPagamentosOperadorasNUMERO_CARTAO;
	TStringField *tbPagamentosOperadorasBANCO;
	TSingleField *tbPagamentosOperadorasCOD_BANCO;
	TStringField *tbPagamentosOperadorasAGENCIA;
	TStringField *tbPagamentosOperadorasCONTA;
	TStringField *tbPagamentosOperadorasCODIGO_AUTORIZACAO;
	TStringField *tbPagamentosOperadorasNSU;
	TSingleField *tbPagamentosOperadorasCOD_CLIENTE;
	TSingleField *tbPagamentosOperadorasCOD_STATUS;
	TSingleField *tbPagamentosOperadorasCOD_ADQUIRENTE;
	TSingleField *tbPagamentosOperadorasTAXA_PERCENTUAL;
	TSingleField *tbPagamentosOperadorasVALOR_TAXA;
	TSingleField *tbPagamentosOperadorasCOD_BANDEIRA;
	TSingleField *tbPagamentosOperadorasCOD_TIPO_PAGAMENTO;
	TStringField *tbPagamentosOperadorasENCONTRADA_VENDA;
	TSingleField *tbPagamentosOperadorasCOD_GRUPO_CLIENTE;
	TStringField *tbPagamentosOperadorasCNPJ;
	TStringField *tbPagamentosOperadorasEMPRESA;
	TDateField *tbPagamentosOperadorasDATA_VENDA;
	TTimeField *tbPagamentosOperadorasHORA_VENDA;
	TDateField *tbPagamentosOperadorasDATA_PAGAMENTO;
	TFloatField *tbPagamentosOperadorasOUTROS_CREDITOS;
	TSingleField *tbPagamentosOperadorasCOD_MEIO_CAPTURA;
	TIntegerField *tbPagamentosOperadorasPARCELA;
	TIntegerField *tbPagamentosOperadorasTOTAL_PARCELAS;
	TSingleField *tbPagamentosOperadorasCOD_STATUS_FINANCEIRO;
	TStringField *tbPagamentosOperadorasVINCULADO_VENDA;
	TSingleField *tbPagamentosOperadorasCOD_VENDA;
	TSingleField *tbPagamentosOperadorasCOD_FORMA_PAGAMENTO;
	TSingleField *tbPagamentosOperadorasTAXA_MANUAL;
	TFloatField *tbPagamentosOperadorasRESUMO_DESCONTO;
	TFloatField *tbPagamentosOperadorasRESUMO_LIQUIDO;
	TFloatField *tbPagamentosOperadorasDIFERENCA_DESCONTO;
	TFloatField *tbPagamentosOperadorasDIFERENCA_LIQUIDO;
	TStringField *tbPagamentosOperadorasIDENTIFICADOR_RO;
	TFloatField *tbPagamentosOperadorasCALCULADO_DESCONTO;
	TFloatField *tbPagamentosOperadorasCALCULADORA_LIQUIDO;
	TStringField *tbPagamentosOperadorasRO_TRATADO;
	TDateField *tbPagamentosOperadorasDATA_PREV_PAG_ORIGINAL;
	TStringField *tbPagamentosOperadorasID_VENDA_ERP;
	TStringField *tbPagamentosOperadorasNOME_ARQUIVO;
	TSingleField *tbPagamentosOperadorasCOD_PRODUTO;
	TStringField *tbPagamentosOperadorasTID;
	TStringField *tbPagamentosOperadorasOBSERVACOES;
	TStringField *tbPagamentosOperadorasDUPLICIDADE_VERIFICADA;
	TStringField *tbPagamentosOperadorasNUMERO_RESUMO_VENDA;
	TStringField *tbPagamentosOperadorasCHAVE_VENDA_OPERADORA;
	TStringField *tbPagamentosOperadorasCHAVE_VENDA_ERP;
	TStringField *tbPagamentosOperadorasCHAVE_PAGAMENTO;
	TStringField *tbPagamentosOperadorasNUMERO_TERMINAL;
	TSingleField *tbPagamentosOperadorasCOD_TIPO_LANCAMENTO;
	TSingleField *tbPagamentosOperadorasCOD_AJUSTE;
	TSingleField *tbPagamentosOperadorasTAXA_ANTECIPACAO;
	TFloatField *tbPagamentosOperadorasVALOR_TAXA_ANTECIPACAO;
	TStringField *tbPagamentosOperadorasNUMERO_OPERACAO_ANTECIPACAO;
	TDateField *tbPagamentosOperadorasDATA_CANCELAMENTO;
	TIntegerField *tbDomicilioClienteCOD_ESTABELECIMENTO;
private:	// User declarations
public:		// User declarations
	__fastcall TData1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TData1 *Data1;
//---------------------------------------------------------------------------
#endif
