//---------------------------------------------------------------------------


#pragma hdrstop

#include "un_Data1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "Vcl.Controls.TControl"
#pragma resource "*.dfm"
TData1 *Data1;
//---------------------------------------------------------------------------
__fastcall TData1::TData1(TComponent* Owner)
	: TDataModule(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TData1::ConexaoError(TObject *ASender, TObject *AInitiator, Exception *&AException)

{
AnsiString erro = AException->ToString();
bool ping;

	if(erro == "[FireDAC][Phys][MySQL] Lost connection to MySQL server during query" || erro == "[FireDAC][Phys][MySQL] MySQL server has gone away")
	{
	ping = Conexao->Ping();

		if(ping)
		{
		Conexao->Connected = true;
		}
	}
}
//---------------------------------------------------------------------------

