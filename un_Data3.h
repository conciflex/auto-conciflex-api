//---------------------------------------------------------------------------

#ifndef un_Data3H
#define un_Data3H
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
class TData3 : public TDataModule
{
__published:	// IDE-managed Components
	TDataSource *DataSeguroVenda;
	TFDQuery *tbSeguroVenda;
	TFDAutoIncField *tbSeguroVendaCODIGO;
	TStringField *tbSeguroVendaMOVIMENTO_API_CODIGO;
	TIntegerField *tbSeguroVendaTIPO_REGISTRO;
	TStringField *tbSeguroVendaESTABELECIMENTO;
	TDateField *tbSeguroVendaDATA_INICIAL_TRANSACAO;
	TDateField *tbSeguroVendaDATA_VENDA_AJUSTE;
	TIntegerField *tbSeguroVendaTIPO_EVENTO;
	TIntegerField *tbSeguroVendaTIPO_TRANSACAO;
	TStringField *tbSeguroVendaNUMERO_SERIE_LEITOR;
	TStringField *tbSeguroVendaCODIGO_TRANSACAO;
	TStringField *tbSeguroVendaCODIGO_VENDA;
	TFloatField *tbSeguroVendaVALOR_TOTAL_TRANSACAO;
	TFloatField *tbSeguroVendaVALOR_PARCELA;
	TStringField *tbSeguroVendaPAGAMENTO_PRAZO;
	TIntegerField *tbSeguroVendaPLANO;
	TIntegerField *tbSeguroVendaPARCELA;
	TIntegerField *tbSeguroVendaQUANTIDADE_PARCELA;
	TDateField *tbSeguroVendaDATA_PREVISTA_PAGAMENTO;
	TFloatField *tbSeguroVendaTAXA_PARCELA_COMPRADOR;
	TFloatField *tbSeguroVendaTARIFA_BOLETO_COMPRA;
	TFloatField *tbSeguroVendaVALOR_ORIGINAL_TRANSACAO;
	TFloatField *tbSeguroVendaTAXA_PARCELA_VENDEDOR;
	TFloatField *tbSeguroVendaTAXA_INTERMEDIACAO;
	TFloatField *tbSeguroVendaTARIFA_INTERMEDIACAO;
	TFloatField *tbSeguroVendaTARIFA_BOLETO_VENDEDOR;
	TFloatField *tbSeguroVendaTAXA_REP_APLICACAO;
	TFloatField *tbSeguroVendaVALOR_LIQUIDO_TRANSACAO;
	TIntegerField *tbSeguroVendaSTATUS_PAGAMENTO;
	TStringField *tbSeguroVendaINSTITUICAO_FINANCEIRA;
	TStringField *tbSeguroVendaCANAL_ENTRADA;
	TStringField *tbSeguroVendaLEITOR;
	TIntegerField *tbSeguroVendaMEIO_CAPTURA;
	TStringField *tbSeguroVendaNUM_LOGICO;
	TStringField *tbSeguroVendaNSU;
	TStringField *tbSeguroVendaCARTAO_BIN;
	TStringField *tbSeguroVendaCARTAO_HOLDER;
	TStringField *tbSeguroVendaCODIGO_AUTORIZACAO;
	TStringField *tbSeguroVendaCODIGO_CV;
	TIntegerField *tbSeguroVendaMEIO_PAGAMENTO;
	TIntegerField *tbSeguroVendaCOD_CADASTRO;
	TTimeField *tbSeguroVendaHORA_VENDA_AJUSTE;
	TStringField *tbSeguroVendaTRATADO;
	TDateField *tbSeguroVendaDATA_LEITURA;
	TTimeField *tbSeguroVendaHORA_LEITURA;
	TIntegerField *tbSeguroVendaCOD_CLIENTE;
	TDataSource *DataSeguroPagamento;
	TFDQuery *tbSeguroPagamento;
	TFDAutoIncField *tbSeguroPagamentoCODIGO;
	TStringField *tbSeguroPagamentoMOVIMENTO_API_CODIGO;
	TIntegerField *tbSeguroPagamentoTIPO_REGISTRO;
	TStringField *tbSeguroPagamentoESTABELECIMENTO;
	TDateField *tbSeguroPagamentoDATA_INICIAL_TRANSACAO;
	TDateField *tbSeguroPagamentoDATA_VENDA_AJUSTE;
	TTimeField *tbSeguroPagamentoHORA_VENDA_AJUSTE;
	TIntegerField *tbSeguroPagamentoTIPO_EVENTO;
	TIntegerField *tbSeguroPagamentoTIPO_TRANSACAO;
	TStringField *tbSeguroPagamentoCODIGO_AUTORIZACAO;
	TStringField *tbSeguroPagamentoCODIGO_VENDA;
	TFloatField *tbSeguroPagamentoVALOR_TOTAL_TRANSACAO;
	TFloatField *tbSeguroPagamentoVALOR_PARCELA;
	TStringField *tbSeguroPagamentoPAGAMENTO_PRAZO;
	TIntegerField *tbSeguroPagamentoPLANO;
	TIntegerField *tbSeguroPagamentoPARCELA;
	TIntegerField *tbSeguroPagamentoQUANTIDADE_PARCELA;
	TDateField *tbSeguroPagamentoDATA_MOVIMENTACAO;
	TFloatField *tbSeguroPagamentoTAXA_PARCELA_COMPRADOR;
	TFloatField *tbSeguroPagamentoTARIFA_BOLETO_COMPRA;
	TFloatField *tbSeguroPagamentoVALOR_ORIGINAL_TRANSACAO;
	TFloatField *tbSeguroPagamentoTAXA_PARCELA_VENDEDOR;
	TFloatField *tbSeguroPagamentoTAXA_INTERMEDIACAO;
	TFloatField *tbSeguroPagamentoTARIFA_INTERMEDIACAO;
	TFloatField *tbSeguroPagamentoTARIFA_BOLETO_VENDEDOR;
	TFloatField *tbSeguroPagamentoTAXA_REP_APLICACAO;
	TFloatField *tbSeguroPagamentoVALOR_LIQUIDO_TRANSACAO;
	TFloatField *tbSeguroPagamentoTAXA_ANTECIPACAO;
	TFloatField *tbSeguroPagamentoVALOR_LIQUIDO_ANTECIPACAO;
	TIntegerField *tbSeguroPagamentoSTATUS_PAGAMENTO;
	TFloatField *tbSeguroPagamentoIDENTIFICADOR_REVENDA;
	TIntegerField *tbSeguroPagamentoMEIO_PAGAMENTO;
	TStringField *tbSeguroPagamentoINSTITUICAO_FINANCEIRA;
	TStringField *tbSeguroPagamentoCANAL_ENTRADA;
	TStringField *tbSeguroPagamentoLEITOR;
	TIntegerField *tbSeguroPagamentoMEIO_CAPTURA;
	TIntegerField *tbSeguroPagamentoCOD_BANCO;
	TStringField *tbSeguroPagamentoNUM_LOGICO;
	TStringField *tbSeguroPagamentoNSU;
	TStringField *tbSeguroPagamentoCARTAO_BIN;
	TStringField *tbSeguroPagamentoCARTAO_HOLDER;
	TStringField *tbSeguroPagamentoCODIGO_CV;
	TStringField *tbSeguroPagamentoCODIGO_TRANSACAO;
	TStringField *tbSeguroPagamentoBANCO_AGENCIA;
	TStringField *tbSeguroPagamentoCONTA_BANCO;
	TStringField *tbSeguroPagamentoTRATADO;
	TDateField *tbSeguroPagamentoDATA_LEITURA;
	TTimeField *tbSeguroPagamentoHORA_LEITURA;
	TIntegerField *tbSeguroPagamentoCOD_CLIENTE;
	TDataSource *DataSeguroCadastro;
	TFDQuery *tbSeguroCadastro;
	TFDAutoIncField *tbSeguroCadastroCODIGO;
	TSingleField *tbSeguroCadastroCOD_CLIENTE;
	TSingleField *tbSeguroCadastroCOD_ADQUIRENTE;
	TStringField *tbSeguroCadastroCODIGO_ESTABELECIMENTO;
	TStringField *tbSeguroCadastroCNPJ_ESTABELECIMENTO;
	TSingleField *tbSeguroCadastroCOD_GRUPO;
	TStringField *tbSeguroCadastroAFFILIATION_KEY;
	TStringField *tbSeguroCadastroINTEGRA_API_PAGSEGURO;
	TDataSource *DataSeguroAntecipacao;
	TFDQuery *tbSeguroAntecipacao;
	TFDAutoIncField *tbSeguroAntecipacaoCODIGO;
	TStringField *tbSeguroAntecipacaoMOVIMENTO_API_CODIGO;
	TIntegerField *tbSeguroAntecipacaoTIPO_REGISTRO;
	TStringField *tbSeguroAntecipacaoESTABELECIMENTO;
	TDateField *tbSeguroAntecipacaoDATA_INICIAL_TRANSACAO;
	TDateField *tbSeguroAntecipacaoDATA_VENDA_AJUSTE;
	TTimeField *tbSeguroAntecipacaoHORA_VENDA_AJUSTE;
	TIntegerField *tbSeguroAntecipacaoTIPO_EVENTO;
	TIntegerField *tbSeguroAntecipacaoTIPO_TRANSACAO;
	TStringField *tbSeguroAntecipacaoNUMERO_SERIE_LEITOR;
	TStringField *tbSeguroAntecipacaoCODIGO_TRANSACAO;
	TStringField *tbSeguroAntecipacaoCODIGO_VENDA;
	TFloatField *tbSeguroAntecipacaoVALOR_TOTAL_TRANSACAO;
	TFloatField *tbSeguroAntecipacaoVALOR_PARCELA;
	TStringField *tbSeguroAntecipacaoPAGAMENTO_PRAZO;
	TIntegerField *tbSeguroAntecipacaoPLANO;
	TIntegerField *tbSeguroAntecipacaoPARCELA;
	TIntegerField *tbSeguroAntecipacaoQUANTIDADE_PARCELA;
	TDateField *tbSeguroAntecipacaoDATA_PREVISTA_PAGAMENTO;
	TFloatField *tbSeguroAntecipacaoTAXA_PARCELA_COMPRADOR;
	TFloatField *tbSeguroAntecipacaoTARIFA_BOLETO_COMPRA;
	TFloatField *tbSeguroAntecipacaoVALOR_ORIGINAL_TRANSACAO;
	TFloatField *tbSeguroAntecipacaoTAXA_PARCELA_VENDEDOR;
	TFloatField *tbSeguroAntecipacaoTAXA_INTERMEDIACAO;
	TFloatField *tbSeguroAntecipacaoTARIFA_INTERMEDIACAO;
	TFloatField *tbSeguroAntecipacaoTARIFA_BOLETO_VENDEDOR;
	TFloatField *tbSeguroAntecipacaoTAXA_REP_APLICACAO;
	TFloatField *tbSeguroAntecipacaoVALOR_LIQUIDO_TRANSACAO;
	TIntegerField *tbSeguroAntecipacaoSTATUS_PAGAMENTO;
	TStringField *tbSeguroAntecipacaoINSTITUICAO_FINANCEIRA;
	TStringField *tbSeguroAntecipacaoCANAL_ENTRADA;
	TStringField *tbSeguroAntecipacaoLEITOR;
	TIntegerField *tbSeguroAntecipacaoMEIO_CAPTURA;
	TStringField *tbSeguroAntecipacaoNUM_LOGICO;
	TStringField *tbSeguroAntecipacaoNSU;
	TStringField *tbSeguroAntecipacaoCARTAO_BIN;
	TStringField *tbSeguroAntecipacaoCODIGO_AUTORIZACAO;
	TStringField *tbSeguroAntecipacaoCODIGO_CV;
	TIntegerField *tbSeguroAntecipacaoMEIO_PAGAMENTO;
	TIntegerField *tbSeguroAntecipacaoCOD_CADASTRO;
	TStringField *tbSeguroAntecipacaoCARTAO_HOLDER;
	TStringField *tbSeguroAntecipacaoTRATADO;
	TSingleField *tbSeguroAntecipacaoTAXA_ANTECIPACAO;
	TFloatField *tbSeguroAntecipacaoVALOR_LIQUIDO_ANTECIPADO;
	TDateField *tbSeguroAntecipacaoDATA_MOVIMENTACAO;
	TDateField *tbSeguroAntecipacaoDATA_LEITURA;
	TTimeField *tbSeguroAntecipacaoHORA_LEITURA;
	TIntegerField *tbSeguroAntecipacaoCOD_CLIENTE;
	TDataSource *DataVendasErp;
	TFDQuery *tbVendasErp;
	TFDAutoIncField *tbVendasErpCODIGO;
	TSingleField *tbVendasErpCOD_PRODUTO;
	TStringField *tbVendasErpDESCRICAO_TIPO_PRODUTO;
	TStringField *tbVendasErpCODIGO_AUTORIZACAO;
	TStringField *tbVendasErpIDENTIFICADOR_PAGAMENTO;
	TDateField *tbVendasErpDATA_VENDA;
	TDateField *tbVendasErpDATA_VENCIMENTO;
	TFloatField *tbVendasErpVALOR_VENDA_PARCELA;
	TFloatField *tbVendasErpVALOR_LIQUIDO_PARCELA;
	TFloatField *tbVendasErpTOTAL_VENDA;
	TFloatField *tbVendasErpTAXA;
	TIntegerField *tbVendasErpPARCELA;
	TIntegerField *tbVendasErpTOTAL_PARCELAS;
	TFloatField *tbVendasErpVALOR_BRUTO_MOEDA;
	TFloatField *tbVendasErpVALOR_LIQUIDO_MOEDA;
	TSingleField *tbVendasErpCOTACAO_MOEDA;
	TSingleField *tbVendasErpCOD_MOEDA;
	TStringField *tbVendasErpNSU;
	TStringField *tbVendasErpTID;
	TStringField *tbVendasErpTERMINAL;
	TSingleField *tbVendasErpCOD_MEIO_CAPTURA;
	TSingleField *tbVendasErpCOD_OPERADORA;
	TSingleField *tbVendasErpCOD_MODALIDADE;
	TSingleField *tbVendasErpCOD_VENDA_CLIENTE;
	TStringField *tbVendasErpCOD_PROD_VENDA_CLIENTE;
	TStringField *tbVendasErpCOD_CLIENTE;
	TStringField *tbVendasErpTRATADO;
	TSingleField *tbVendasErpCOD_STATUS_CONCILIACAO;
	TFloatField *tbVendasErpVALOR_TAXA;
	TStringField *tbVendasErpCOMPLEMENTO;
	TStringField *tbVendasErpDIVERGENCIA;
	TStringField *tbVendasErpBANDEIRA;
	TSingleField *tbVendasErpCOD_BANDEIRA;
	TSingleField *tbVendasErpCOD_BANCO;
	TStringField *tbVendasErpBANCO;
	TStringField *tbVendasErpCONTA_CORRENTE;
	TStringField *tbVendasErpAGENCIA;
	TStringField *tbVendasErpCAMPO_ADICIONAL1;
	TStringField *tbVendasErpCAMPO_ADICIONAL2;
	TStringField *tbVendasErpCAMPO_ADICIONAL3;
	TStringField *tbVendasErpJUSTIFICATIVA;
	TLargeintField *tbVendasErpCOD_VENDAS_OPERADORAS;
	TIntegerField *tbVendasErpCOD_STATUS_FINANCEIRO;
	TDateField *tbVendasErpDATA_IMPORTACAO;
	TTimeField *tbVendasErpHORA_IMPORTACAO;
	TDateField *tbVendasErpDATA_CONCILIACAO;
	TTimeField *tbVendasErpHORA_CONCILIACAO;
	TSingleField *tbVendasErpCOD_GRUPO_CLIENTE;
	TStringField *tbVendasErpRETORNO_ERP;
	TStringField *tbVendasErpESTABELECIMENTO;
	TSingleField *tbVendasErpTAXA_OPERADORA;
	TSingleField *tbVendasErpTAXA_DIFERENCA;
	TFloatField *tbVendasErpVALOR_LIQUIDO_OPERADORA;
	TFloatField *tbVendasErpDIFERENCA_LIQUIDO;
	TStringField *tbVendasErpDETALHAMENTO_DIVERGENCIA;
	TStringField *tbVendasErpRETORNO_ERP_BAIXA;
	TStringField *tbVendasErpCAMPO_INFOTECH;
	TStringField *tbVendasErpTID_ADICIONAL;
	TStringField *tbVendasErpBIN_CARTAO;
	TSingleField *tbVendasErpCOD_REGRA_CONCILIACAO;
	TStringField *tbVendasErpCHAVE_VENDA_ERP;
	TStringField *tbVendasErpCHAVE_VENDA_OPERADORA;
	TStringField *tbVendasErpDESCONCILIA_EXCLUIR;
	TStringField *tbVendasErpDUPLICIDADE;
	TStringField *tbVendasErpTEMPORARIO;
	TStringField *tbVendasErpAUTORIZADOR;
	TStringField *tbVendasErpOBSERVACAO_ERP;
private:	// User declarations
public:		// User declarations
	__fastcall TData3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TData3 *Data3;
//---------------------------------------------------------------------------
#endif