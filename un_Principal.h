//---------------------------------------------------------------------------

#ifndef un_PrincipalH
#define un_PrincipalH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdCompressorZLib.hpp>
#include <IdCookieManager.hpp>
#include <IdHTTP.hpp>
#include <IdIOHandler.hpp>
#include <IdIOHandlerSocket.hpp>
#include <IdIOHandlerStack.hpp>
#include <IdSSL.hpp>
#include <IdSSLOpenSSL.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdZLibCompressorBase.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>
//---------------------------------------------------------------------------
class TPrincipal : public TForm
{
__published:	// IDE-managed Components
	TPageControl *TPageControl;
	TTabSheet *TabSheet1;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label24;
	TEdit *Edit2;
	TEdit *Edit3;
	TRadioGroup *RadioGroup1;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label3;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label21;
	TProgressBar *ProgressBar1;
	TMemo *Memo3;
	TEdit *Edit1;
	TEdit *Edit4;
	TButton *Button6;
	TTabSheet *TabSheet2;
	TGroupBox *GroupBox4;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TLabel *Label20;
	TLabel *Label22;
	TLabel *Label23;
	TLabel *Label25;
	TLabel *Label26;
	TLabel *Label27;
	TLabel *Label28;
	TLabel *Label29;
	TLabel *Label30;
	TLabel *Label31;
	TLabel *Label32;
	TLabel *Label33;
	TLabel *Label34;
	TLabel *Label35;
	TDateTimePicker *DateTimePicker1;
	TDateTimePicker *DateTimePicker2;
	TButton *Button17;
	TProgressBar *ProgressBar2;
	TProgressBar *ProgressBar3;
	TDBLookupComboBox *DBLookupComboBox1;
	TMemo *Memo2;
	TTabSheet *TabSheet3;
	TGroupBox *GroupBox5;
	TLabel *Label36;
	TLabel *Label37;
	TLabel *Label38;
	TLabel *Label39;
	TLabel *Label40;
	TLabel *Label41;
	TLabel *Label44;
	TLabel *Label45;
	TLabel *Label46;
	TLabel *Label47;
	TLabel *Label48;
	TLabel *Label49;
	TLabel *Label50;
	TLabel *Label51;
	TLabel *Label52;
	TLabel *Label53;
	TLabel *Label54;
	TLabel *Label55;
	TLabel *Label56;
	TLabel *Label57;
	TLabel *Label58;
	TLabel *Label59;
	TLabel *Label60;
	TLabel *Label61;
	TDateTimePicker *DateTimePicker3;
	TDateTimePicker *DateTimePicker4;
	TButton *Button2;
	TProgressBar *ProgressBar4;
	TProgressBar *ProgressBar5;
	TDBLookupComboBox *DBLookupComboBox2;
	TMemo *Memo4;
	TTimer *Timer1;
	TMainMenu *MainMenu1;
	TMenuItem *Arquivo1;
	TMenuItem *Fechar1;
	TMenuItem *Automaticva1;
	TMenuItem *Stone5;
	TMenuItem *AutomaticoPagSeguro;
	TMenuItem *Atualizaes1;
	TMenuItem *Stone3;
	TMenuItem *MarcarDadosBrutosparaTRATADON2;
	TMenuItem *Funcoes1;
	TMenuItem *Stone2;
	TMenuItem *TratarVendasStone;
	TMenuItem *TratarAntecipacoesStone;
	TMenuItem *TratarPagamentosStone;
	TMenuItem *TratarAjustesStone;
	TMenuItem *Excluses1;
	TMenuItem *PagSeguro3;
	TMenuItem *ExcluirDuplicidadedeVendas2;
	TMenuItem *ExcluirDuplicidadedePagamento6;
	TMenuItem *Stone1;
	TMenuItem *ExcluirDadosBrutos9;
	TMenuItem *ExcluirVendas10;
	TMenuItem *ExcluirPagamentos10;
	TMenuItem *Excluirduplicidadedevendas1;
	TMenuItem *Excluirduplicidadedepagamentos1;
	TMenuItem *Manual1;
	TMenuItem *Stone4;
	TMenuItem *Atualizardadosbancriosvenda1;
	TMenuItem *Atualizardadosbancriospagamento1;
	TMenuItem *ResetarVendas1;
	TMenuItem *Preencherbandeiranospagamentos1;
	TMenuItem *Preencherdadosbancriosnospagamentos1;
	TMenuItem *PagSeguro2;
	TMenuItem *DeletardadosDalgaloPneus1;
	TMenuItem *Vincularvendasepagamentosoperadora1;
	TOpenDialog *OpenDialog1;
	TIdHTTP *IdHTTP2;
	TIdSSLIOHandlerSocketOpenSSL *IdSSLIOHandlerSocketOpenSSL1;
	TXMLDocument *XMLDocument1;
	TIdCookieManager *IdCookieManager1;
	TIdCompressorZLib *IdCompressorZLib1;
	TMenuItem *PagSeguro1;
	TMenuItem *TratarVendasPagSeguro;
	TMenuItem *TratarPagamentosPagSeguro;
	TMenuItem *TratarAntecipacoesPagSeguro;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button17Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall TratarVendasStoneClick(TObject *Sender);
	void __fastcall TratarAntecipacoesStoneClick(TObject *Sender);
	void __fastcall TratarPagamentosStoneClick(TObject *Sender);
	void __fastcall TratarAjustesStoneClick(TObject *Sender);
	void __fastcall Stone5Click(TObject *Sender);
	void __fastcall MarcarDadosBrutosparaTRATADON2Click(TObject *Sender);
	void __fastcall ExcluirDadosBrutos9Click(TObject *Sender);
	void __fastcall ExcluirVendas10Click(TObject *Sender);
	void __fastcall ExcluirPagamentos10Click(TObject *Sender);
	void __fastcall Excluirduplicidadedevendas1Click(TObject *Sender);
	void __fastcall Excluirduplicidadedepagamentos1Click(TObject *Sender);
	void __fastcall Atualizardadosbancriosvenda1Click(TObject *Sender);
	void __fastcall Atualizardadosbancriospagamento1Click(TObject *Sender);
	void __fastcall ResetarVendas1Click(TObject *Sender);
	void __fastcall Preencherbandeiranospagamentos1Click(TObject *Sender);
	void __fastcall Preencherdadosbancriosnospagamentos1Click(TObject *Sender);
	void __fastcall AutomaticoPagSeguroClick(TObject *Sender);
	void __fastcall TratarVendasPagSeguroClick(TObject *Sender);
	void __fastcall TratarPagamentosPagSeguroClick(TObject *Sender);
	void __fastcall TratarAntecipacoesPagSeguroClick(TObject *Sender);
	void __fastcall ExcluirDuplicidadedeVendas2Click(TObject *Sender);
	void __fastcall ExcluirDuplicidadedePagamento6Click(TObject *Sender);
	void __fastcall DeletardadosDalgaloPneus1Click(TObject *Sender);
	void __fastcall Vincularvendasepagamentosoperadora1Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Label33Click(TObject *Sender);
	void __fastcall Label35Click(TObject *Sender);
	void __fastcall Label55Click(TObject *Sender);
	void __fastcall Label57Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TPrincipal(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrincipal *Principal;
//---------------------------------------------------------------------------
#endif
