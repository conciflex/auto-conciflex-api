//---------------------------------------------------------------------------

#ifndef un_Data_ResumoH
#define un_Data_ResumoH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
//---------------------------------------------------------------------------
class TDataResumo : public TDataModule
{
__published:	// IDE-managed Components
	TDataSource *DataClientesOperadoras;
	TFDQuery *tbClientesOperadoras;
	TFDAutoIncField *tbClientesOperadorasCODIGO;
	TSingleField *tbClientesOperadorasCOD_CLIENTE;
	TSingleField *tbClientesOperadorasCOD_ADQUIRENTE;
	TStringField *tbClientesOperadorasCODIGO_ESTABELECIMENTO;
	TStringField *tbClientesOperadorasCNPJ_ESTABELECIMENTO;
	TSingleField *tbClientesOperadorasCOD_GRUPO;
	TDataSource *DataVendasOperadoras;
	TFDQuery *tbVendasOperadoras;
	TFDAutoIncField *tbVendasOperadorasCODIGO;
	TIntegerField *tbVendasOperadorasREFOID;
	TStringField *tbVendasOperadorasEMPRESA;
	TStringField *tbVendasOperadorasESTABELECIMENTO;
	TStringField *tbVendasOperadorasCNPJ;
	TIntegerField *tbVendasOperadorasADQID;
	TStringField *tbVendasOperadorasADQUIRENTE;
	TIntegerField *tbVendasOperadorasCODIGO_PRODUTO;
	TStringField *tbVendasOperadorasPRODUTO;
	TIntegerField *tbVendasOperadorasCODIGO_MODALIDADE;
	TStringField *tbVendasOperadorasDESCRICAO_MODALIDADE;
	TDateField *tbVendasOperadorasDATA_VENDA;
	TDateField *tbVendasOperadorasDATA_PREVISTA_PAGTO;
	TStringField *tbVendasOperadorasRESUMO_VENDA;
	TStringField *tbVendasOperadorasAUTORIZACAO;
	TStringField *tbVendasOperadorasNSU;
	TStringField *tbVendasOperadorasTID;
	TStringField *tbVendasOperadorasCARTAO;
	TFloatField *tbVendasOperadorasVALOR_BRUTO;
	TFloatField *tbVendasOperadorasPERCENTUAL_TAXA;
	TFloatField *tbVendasOperadorasVALOR_TAXA;
	TFloatField *tbVendasOperadorasOUTRAS_DESPESAS;
	TFloatField *tbVendasOperadorasVALOR_LIQUIDO;
	TStringField *tbVendasOperadorasTERMINAL;
	TIntegerField *tbVendasOperadorasBANCO;
	TStringField *tbVendasOperadorasAGENCIA;
	TStringField *tbVendasOperadorasCONTA;
	TTimeField *tbVendasOperadorasHORA_TRANSACAO;
	TIntegerField *tbVendasOperadorasPARCELA;
	TIntegerField *tbVendasOperadorasTOTAL_PARCELAS;
	TStringField *tbVendasOperadorasOBSERVACOES;
	TIntegerField *tbVendasOperadorasSTATUS;
	TStringField *tbVendasOperadorasREJEITADO;
	TStringField *tbVendasOperadorasCANCELADO;
	TDateField *tbVendasOperadorasDATA_PAGAMENTO;
	TFloatField *tbVendasOperadorasVALOR_PAGO;
	TStringField *tbVendasOperadorasID_PAGAMENTO;
	TStringField *tbVendasOperadorasPEDIDO;
	TFloatField *tbVendasOperadorasID;
	TSingleField *tbVendasOperadorasCOD_STATUS_CONCILIACAO;
	TSingleField *tbVendasOperadorasCOD_BANDEIRA;
	TStringField *tbVendasOperadorasBANDEIRA;
	TSingleField *tbVendasOperadorasCOD_CLIENTE;
	TSingleField *tbVendasOperadorasCOD_STATUS_FINANCEIRO;
	TSingleField *tbVendasOperadorasCOD_PRODUTO;
	TSingleField *tbVendasOperadorasCOD_GRUPO_CLIENTE;
	TFloatField *tbVendasOperadorasVALOR_DIFERENCA;
	TSingleField *tbVendasOperadorasCOD_MEIO_CAPTURA;
	TStringField *tbVendasOperadorasVINCULADO_PAGAMENTO;
	TSingleField *tbVendasOperadorasCOD_PAGAMENTO;
	TSingleField *tbVendasOperadorasCOD_TIPO_PAGAMENTO;
	TStringField *tbVendasOperadorasJUSTIFICATIVA;
	TLargeintField *tbVendasOperadorasCOD_VENDA_ERP;
	TStringField *tbVendasOperadorasPRODUTO_ERP;
	TStringField *tbVendasOperadorasID_VENDAS_ERP;
	TSingleField *tbVendasOperadorasTAXA_MINIMA;
	TStringField *tbVendasOperadorasDIVERGENCIA;
	TBCDField *tbVendasOperadorasVARIAVEL;
	TStringField *tbVendasOperadorasPAGAMENTO_GERADO;
	TStringField *tbVendasOperadorasNOME_ARQUIVO;
	TStringField *tbVendasOperadorasID_VENDA_PAGAMENTO_TRATADO;
	TStringField *tbVendasOperadorasTID_ADICIONAL;
	TStringField *tbVendasOperadorasBIN_CARTAO;
	TSingleField *tbVendasOperadorasCOD_REGRA_CONCILIACAO;
	TStringField *tbVendasOperadorasVERIFICADO_DUPLICIDADE;
	TStringField *tbVendasOperadorasNUMERO_RESUMO_VENDA;
	TStringField *tbVendasOperadorasCHAVE_VENDA;
	TStringField *tbVendasOperadorasCHAVE_VENDA_ERP;
	TStringField *tbVendasOperadorasCHAVE_PAGAMENTO;
	TDateField *tbVendasOperadorasDATA_CANCELAMENTO;
	TStringField *tbVendasOperadorasAUTORIZADOR;
	TStringField *tbVendasOperadorasPERC_TAXA_CALC;
	TStringField *tbVendasOperadorasCAMPO_ADICIONAL1;
	TStringField *tbVendasOperadorasCAMPO_ADICIONAL2;
	TStringField *tbVendasOperadorasCAMPO_ADICIONAL3;
	TFloatField *tbVendasOperadorasVALOR_BRUTO_ERP;
	TSingleField *tbVendasOperadorasPERCENTUAL_TAXA_CALC;
	TDateField *tbVendasOperadorasDATA_PROCESSAMENTO;
	TTimeField *tbVendasOperadorasHORA_PROCESSAMENTO;
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
	TStringField *tbPagamentosOperadorasAUTORIZADOR;
	TStringField *tbPagamentosOperadorasPERCENTUAL_TAXA_CALC;
private:	// User declarations
public:		// User declarations
	__fastcall TDataResumo(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDataResumo *DataResumo;
//---------------------------------------------------------------------------
#endif
