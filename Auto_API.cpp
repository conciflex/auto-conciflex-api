//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("un_Principal.cpp", Principal);
USEFORM("un_Data1.cpp", Data1); /* TDataModule: File Type */
USEFORM("un_Data_Processamento.cpp", DataProcessamento); /* TDataModule: File Type */
USEFORM("un_Data2.cpp", Data2); /* TDataModule: File Type */
USEFORM("un_Data_Resumo.cpp", DataResumo); /* TDataModule: File Type */
USEFORM("un_Data3.cpp", Data3); /* TDataModule: File Type */
USEFORM("un_Data_Verificacao2.cpp", DataVerificacao2); /* TDataModule: File Type */
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		TStyleManager::TrySetStyle("Smokey Quartz Kamri");
		Application->CreateForm(__classid(TData1), &Data1);
		Application->CreateForm(__classid(TDataProcessamento), &DataProcessamento);
		Application->CreateForm(__classid(TData2), &Data2);
		Application->CreateForm(__classid(TDataResumo), &DataResumo);
		Application->CreateForm(__classid(TData3), &Data3);
		Application->CreateForm(__classid(TDataVerificacao2), &DataVerificacao2);
		Application->CreateForm(__classid(TPrincipal), &Principal);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
