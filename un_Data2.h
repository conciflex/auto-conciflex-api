//---------------------------------------------------------------------------

#ifndef un_Data2H
#define un_Data2H
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
class TData2 : public TDataModule
{
__published:	// IDE-managed Components
	TDataSource *DataHeaderStone;
	TFDQuery *tbHeaderStone;
	TFDAutoIncField *tbHeaderStoneCODIGO;
	TStringField *tbHeaderStoneSTONECODE;
	TStringField *tbHeaderStoneLAYOUT_VERSION;
	TStringField *tbHeaderStoneCOD_CREDENCIAMENTO;
	TDateField *tbHeaderStoneDATA_GERACAO;
	TDateField *tbHeaderStoneDATA_REFERENCIA;
	TDataSource *DataEventoStone;
	TFDQuery *tbEventoStone;
	TFDAutoIncField *tbEventoStoneCODIGO;
	TStringField *tbEventoStoneCODIGO_EVENTO;
	TStringField *tbEventoStoneDESCRICAO_EVENTO;
	TIntegerField *tbEventoStoneTIPO_EVENTO;
	TDateField *tbEventoStonePREVISAO_COBRANCA;
	TFloatField *tbEventoStoneVALOR_EVENTO;
	TIntegerField *tbEventoStoneCODE_TRANSFERENCIA_INTERNA;
	TDateField *tbEventoStoneDATA_COBRANCA;
	TIntegerField *tbEventoStoneCOD_HEADER;
	TStringField *tbEventoStoneTRATADO;
	TStringField *tbEventoStoneSTONECODE;
	TIntegerField *tbEventoStoneARRANJO_PAGAMENTO;
	TIntegerField *tbEventoStoneBANCO;
	TStringField *tbEventoStoneAGENCIA;
	TStringField *tbEventoStoneNUM_CONTA;
	TStringField *tbEventoStoneID_PAGAMENTO;
	TDataSource *DataCredenciadosStone;
	TFDQuery *tbCredenciadosStone;
	TFDAutoIncField *tbCredenciadosStoneCODIGO;
	TDateField *tbCredenciadosStoneDATA_CREDENCIAMENTO;
	TStringField *tbCredenciadosStoneSTONECODE;
	TStringField *tbCredenciadosStoneCNPJ_ESTABELECIMENTO;
	TStringField *tbCredenciadosStoneLIBERADO;
	TDataSource *DataVendaStone;
	TFDQuery *tbVendaStone;
	TFDAutoIncField *tbVendaStoneCODIGO;
	TStringField *tbVendaStoneNSU;
	TStringField *tbVendaStoneCODIGO_TRANSACAO;
	TDateField *tbVendaStoneDATA_AUTORIZACAO;
	TTimeField *tbVendaStoneHORA_AUTORIZACAO;
	TDateField *tbVendaStoneDATA_CAPTURA;
	TTimeField *tbVendaStoneHORA_CAPTURA;
	TStringField *tbVendaStoneINTERNACIONAL;
	TIntegerField *tbVendaStoneCOD_TIPO_CONTA;
	TIntegerField *tbVendaStoneCOD_TIPO_PAGAMENTO;
	TIntegerField *tbVendaStoneTOTAL_PARCELAS;
	TFloatField *tbVendaStoneVALOR_AUTORIZADO;
	TFloatField *tbVendaStoneVALOR_CAPTURADO;
	TFloatField *tbVendaStoneTOTAL_CANCELADO;
	TStringField *tbVendaStoneCODIGO_AUTORIZACAO;
	TIntegerField *tbVendaStoneCOD_BANDEIRA;
	TStringField *tbVendaStoneNUM_CARTAO;
	TIntegerField *tbVendaStoneCOD_TIPO_TERMINAL;
	TStringField *tbVendaStoneNUM_TERMINAL;
	TIntegerField *tbVendaStoneNUM_PARCELA;
	TFloatField *tbVendaStoneVALOR_BRUTO_PARCELA;
	TFloatField *tbVendaStoneVALOR_LIQUIDO_PARCELA;
	TDateField *tbVendaStonePREVISAO_PAGAMENTO;
	TIntegerField *tbVendaStoneCOD_HEADER;
	TStringField *tbVendaStoneTRATADO;
	TStringField *tbVendaStoneSTONECODE;
	TDataSource *DataPagamentoStone;
	TFDQuery *tbPagamentoStone;
	TFDAutoIncField *tbPagamentoStoneCODIGO;
	TIntegerField *tbPagamentoStoneCOD_HEADER;
	TStringField *tbPagamentoStoneNSU;
	TIntegerField *tbPagamentoStoneNUM_PARCELA;
	TFloatField *tbPagamentoStoneVALOR_BRUTO_PARCELA;
	TFloatField *tbPagamentoStoneVALOR_LIQUIDO_PARCELA;
	TDateField *tbPagamentoStonePAGAMENTO_PARCELA;
	TFloatField *tbPagamentoStoneDESCONTO_ANTECIPACAO;
	TDateField *tbPagamentoStonePAGAMENTO_REAL_ANTECIPADO;
	TIntegerField *tbPagamentoStoneARRANJO_PAGAMENTO;
	TFloatField *tbPagamentoStoneVALOR_PAGO;
	TFloatField *tbPagamentoStoneVALOR_PENDENTE_LOJISTA;
	TIntegerField *tbPagamentoStoneBANCO;
	TStringField *tbPagamentoStoneAGENCIA;
	TStringField *tbPagamentoStoneNUM_CONTA;
	TStringField *tbPagamentoStoneTRATADO;
	TStringField *tbPagamentoStoneSTONECODE;
	TStringField *tbPagamentoStoneCODIGO_TRANSACAO;
	TDateField *tbPagamentoStoneDATA_AUTORIZACAO;
	TTimeField *tbPagamentoStoneHORA_AUTORIZACAO;
	TStringField *tbPagamentoStoneID_PAGAMENTO;
	TDataSource *DataCancelamentoStone;
	TFDQuery *tbCancelamentoStone;
	TFDAutoIncField *tbCancelamentoStoneCODIGO;
	TStringField *tbCancelamentoStoneCODIGO_CANCELAMENTO;
	TIntegerField *tbCancelamentoStoneNUM_PARCELA;
	TDateField *tbCancelamentoStoneDATA_CANCELAMENTO;
	TTimeField *tbCancelamentoStoneHORA_CANCELAMENTO;
	TFloatField *tbCancelamentoStoneVALOR_ESTORNADO_CLIENTE;
	TFloatField *tbCancelamentoStoneVALOR_DESCONTADO_LOJISTA;
	TDateField *tbCancelamentoStoneDATA_COBRANCA;
	TIntegerField *tbCancelamentoStoneCOD_HEADER;
	TStringField *tbCancelamentoStoneNSU;
	TDateField *tbCancelamentoStoneDATA_AUTORIZACAO_VENDA;
	TTimeField *tbCancelamentoStoneHORA_AUTORIZACAO_VENDA;
	TDateField *tbCancelamentoStoneDATA_CAPTURA_VENDA;
	TTimeField *tbCancelamentoStoneHORA_CAPTURA_VENDA;
	TDateField *tbCancelamentoStoneDATA_PREVISAO_COBRANCA;
	TStringField *tbCancelamentoStoneTRATADO;
	TStringField *tbCancelamentoStoneSTONECODE;
	TStringField *tbCancelamentoStoneTIPO;
	TStringField *tbCancelamentoStoneID_PAGAMENTO;
private:	// User declarations
public:		// User declarations
	__fastcall TData2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TData2 *Data2;
//---------------------------------------------------------------------------
#endif
