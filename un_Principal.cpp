//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <math.h>
#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <System.Math.hpp>
#include "System.JSON.hpp"
#include "System.DateUtils.hpp"

#include "un_Principal.h"
#include "un_Data1.h"
#include "un_Data2.h"
#include "un_Data3.h"
#include "un_Data_Processamento.h"
#include "un_Data_Resumo.h"
#include "un_Data_Verificacao2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPrincipal *Principal;

//VARIÁVEL GLOBAL
int numero_processos = 3;
int processo_atual = 1;
int num_loop = 0;
bool lido_stone = false;
bool autentificado = false;
bool lido_bonuscred = false;
bool reprocessado_seguro = false;
//---------------------------------------------------------------------------
__fastcall TPrincipal::TPrincipal(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

double RetirarPontuacao(AnsiString valor)
{
double valor_convertido = StrToFloat(ReplaceAll(valor, '.', ','));

return valor_convertido;
}

AnsiString alterarVirgulaPorPonto(AnsiString valor)
{
    //RETIRA OS ZEROS A ESQUERDA
	for(int posicao = 1; posicao <= valor.Length(); posicao++)
	{
		if(valor[posicao] == ',')
		{
		valor[posicao] = '.';
		}
	}

	return valor;
}

AnsiString alterarPontoPorVirgula(AnsiString valor)
{
    //RETIRA OS ZEROS A ESQUERDA
	for(int posicao = 1; posicao <= valor.Length(); posicao++)
	{
		if(valor[posicao] == '.')
		{
		valor[posicao] = ',';
		}
	}

	return valor;
}

TDate dataValida(TDate data_validacao)
{
//VERIFICA SE A DATA DE PAGAMENTO É SÁBADO / DOMINGO OU FERIDADO
AnsiString data_pagamento, consulta;
bool dia_aprovado = false;
int dia_da_semana;
TDate dtPresent;
Word Year, Month, Day;

	while(dia_aprovado == false)
	{
	dtPresent = data_validacao;
	DecodeDate(dtPresent, Year, Month, Day);

	Principal->Edit1->Text = Year;
	data_pagamento = Principal->Edit1->Text + "-";
	Principal->Edit1->Text = Month;
	data_pagamento = data_pagamento + Principal->Edit1->Text + "-";
	Principal->Edit1->Text = Day;
	data_pagamento = data_pagamento + Principal->Edit1->Text;

	dia_da_semana = DayOfWeek(data_validacao);

		//CASO SEJA SÁBADO
		if(dia_da_semana == 7)
		{
		dia_aprovado = false;
		}
		else
		{
			//CASO SEJA DOMINGO
			if(dia_da_semana == 1)
			{
			dia_aprovado = false;
			}
			else
			{
			//VERIFICA SE É UM FERIADO
			consulta = "Select * from feriados where feriados.DATA_FERIADO = '" + data_pagamento + "' ";

			Data1->tbFeriados->Close();
			Data1->tbFeriados->SQL->Clear();
			Data1->tbFeriados->SQL->Add(consulta);
			Data1->tbFeriados->Open();

				//VERIFICA SE O DIA EM QUESTÃO É FERIADO
				if(Data1->tbFeriados->RecordCount == 1)
				{
				dia_aprovado = false;
				}
				else
				{
				dia_aprovado = true;
				}
			}
		}

		if(dia_aprovado == false)
		{
		data_validacao = data_validacao + 1;
		}
		else
		{
		return data_validacao;
		}
	}
}

AnsiString retirarZerosEsquerda(AnsiString valor)
{
	//RETIRA OS ZEROS A ESQUERDA
	for(int posicao = 1; posicao <= valor.Length(); posicao++)
	{
		if(valor[posicao] != '0')
		{
		valor = valor.SubString(posicao, valor.Length());
		break;
		}
	}

	return valor;
}

AnsiString formatarZerosEsquerda(AnsiString valor, int quant_caracteres)
{
AnsiString dados;
int posicao;

	if(valor.Length() <= (quant_caracteres - 1))
	{
	posicao = quant_caracteres - valor.Length();
	dados = "";

		for(int aux = 0; aux < posicao; aux++)
		{
		dados += "0";
		}

	dados += valor;
	valor = dados;
	}

    return valor;
}

AnsiString formatarData(int formato, AnsiString data)
{
    //yyyymmdd -> yyyy-mm-dd
    if(formato == 1)
    {
    return data.SubString(1, 4) + "-" + data.SubString(5, 2) + "-" + data.SubString(7, 2);
    }
    //yyyymmdd -> dd/mm/yyyy
    else if(formato == 2)
    {
    return data.SubString(7,2) + "/" + data.SubString(5,2) + "/" + data.SubString(1,4);
    }
    //dd/mm/yyyy -> yyyy-mm-dd
    else if(formato == 3)
    {
    return data.SubString(7,4) + "-" + data.SubString(4,2) + "-" + data.SubString(1,2);
    }
    //yymmdd -> dd/mm/yyyy
    else if(formato == 4)
    {
    return data.SubString(5,2) + "/" + data.SubString(3,2) + "/" + "20" + data.SubString(1,2);
    }
    //yymmdd -> yyyy-mm-dd
    else if(formato == 5)
    {
    return "20" + data.SubString(1, 2) + "-" + data.SubString(3, 2) + "-" + data.SubString(5, 2);
    }
    //dd/mm/yyyy -> yyyymmdd
    else if(formato == 6)
    {
    return data.SubString(7,4) + "" + data.SubString(4,2) + "" + data.SubString(1,2);
    }
    //yyyy-mm-dd -> dd/mm/yyyy
    else if(formato == 7)
    {
    return data.SubString(9,2) + "/" + data.SubString(6,2) + "/" + data.SubString(1,4);
    }
}

AnsiString formatarHora(AnsiString hora)
{
return hora.SubString(1,2) + ":" + hora.SubString(3,2) + ":" + hora.SubString(5,2);
}

AnsiString retirar_caracteres(AnsiString dado)
{
AnsiString resultado = "";

	 for(int i = 1; i <= StrLen(dado.c_str()); i++)
	 {
        if(dado[i] != ',' && dado[i] != '-' && dado[i] != 'º' && dado[i] != 'ª' && dado[i] != '%' &&
             dado[i] != '.' && dado[i] != '/')
        {
             resultado += dado[i];
        }
	 }

return resultado;
}

AnsiString sem_digito(AnsiString agencia)
{
AnsiString resultado = "";

	 for(int i = 1; i <= StrLen(agencia.c_str()); i++)
	 {
        if(agencia[i] != '-')
        {
        resultado += agencia[i];
        }
        else
        {
        break;
        }
	 }

return resultado;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TPrincipal::FormCreate(TObject *Sender)
{
SetRoundMode(rmUp);
DateTimePicker1->Date = Date() - 1;
DateTimePicker2->Date = Date() - 1;

DateTimePicker3->Date = Date();
DateTimePicker4->Date = Date();

DateTimePicker5->Date = Date() - 1;
DateTimePicker6->Date = Date() - 1;

DataProcessamento->tbClientes->Close();
DataProcessamento->tbClientes->SQL->Clear();
DataProcessamento->tbClientes->SQL->Add("select * from clientes where clientes.CODIGO is not null order by clientes.nome");
DataProcessamento->tbClientes->Open();
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::Button17Click(TObject *Sender)
{
Label21->Caption = "Iniciando Leitura de API Stone";
Label27->Caption = "Iniciando Leitura de API Stone";

TDate ontem  = Date() - 1;

	if(DateOf(DateTimePicker2->Date) > ontem)
	{
	Application->MessageBoxA(L"A Data Final deve ser do dia anterior!", L"Mensagem do Sistema", MB_OK);
	}
	else if(DateTimePicker2->Date < DateTimePicker1->Date)
	{
	Application->MessageBoxA(L"A Data Final deve ser maior ou igual a data inicial!", L"Mensagem do Sistema", MB_OK);
	}
	else
	{
	int dias = DaysBetween(DateTimePicker1->Date, DateTimePicker2->Date) + 1;
    int erro = 0;

	ProgressBar2->Position = 0;
	ProgressBar2->Max = dias;
    Label15->Caption = "";
	Label17->Caption = erro;

	int total_charge = 0;
    int final = 0, contador_clientes = 0, final_clientes = 0;
    AnsiString data, data_referencia, data_consulta, consulta, retorno, dado, auxiliar, url;
    AnsiString NSU, codigo_transacao, data_autorizacao, hora_autorizacao, data_captura, hora_captura;
    AnsiString internacional, codigo_autorizacao, num_cartao, num_terminal, previsao_pagamento;
    AnsiString codigo_cancelamento, data_cancelamento, hora_cancelamento, previsao_cobranca, id_pagamento, atualiza;
    AnsiString agencia, num_conta, codigo_evento, descricao_evento, pagamento_parcela, pagamento_original, stone_code;
    int cod_tipo_conta, cod_tipo_pagamento, cod_tipo_terminal, total_parcelas, cod_bandeira, num_parcela;
    int arranjo_pagamento, banco, tipo_evento, code_transferencia;
    int codigo, capturas = 0, pagamentos = 0, cancelamentos = 0, chargebacks = 0, chargeback_estorno = 0, cod_cliente = 0;
    double valor_autorizado, valor_capturado, total_cancelado, valor_bruto_parcela, valor_liquido_parcela;
    double valor_estornado, valor_cancelamento, desconto_antecipacao, valor_pago, valor_pendente, valor_evento;
    bool cadastrado, continuar, duplicidade, reprocessamento, cliente = false;

    TJSONObject *json;
    _di_IXMLNode nodeTransaction, nodeParcelas, nodeParcela;
    _di_IXMLNode nodeAuxiliar, nodeAuxiliar2, node, nodeHeader;
    _di_IXMLNodeList nodes;

    Word Year, Month, Day;
    TDateTime dtPresent;

        if(DBLookupComboBox1->KeyValue > 0)
        {
        cliente = true;
        cod_cliente = DBLookupComboBox1->KeyValue;

        Edit1->Text = cod_cliente;
        consulta = "select * from cliente_operadora where cliente_operadora.COD_ADQUIRENTE = 7 ";
        consulta += " and cliente_operadora.COD_CLIENTE = '" + Edit1->Text + "'";

        DataProcessamento->tbClienteOperadora->Close();
        DataProcessamento->tbClienteOperadora->SQL->Clear();
        DataProcessamento->tbClienteOperadora->SQL->Add(consulta);
        DataProcessamento->tbClienteOperadora->Open();

        DataProcessamento->tbClienteOperadora->Last();
        final_clientes = DataProcessamento->tbClienteOperadora->RecordCount;
        DataProcessamento->tbClienteOperadora->First();
        }

    	for(int contador_dias = 0; contador_dias < dias; contador_dias++)
		{
        Button6Click(Sender);

		Application->ProcessMessages();

		Label15->Caption = DateOf(DateTimePicker1->Date + contador_dias);

		IdHTTP1->Request->CustomHeaders->Clear();
        IdHTTP1->Request->BasicAuthentication = false;
		IdHTTP1->Request->CustomHeaders->AddValue("authorization", "Bearer 028f2e66-0134-477a-8d4c-12f122767680");
		IdHTTP1->Request->CustomHeaders->AddValue("x-authorization-raw-data", "Conciflex");
		IdHTTP1->Request->CustomHeaders->AddValue("x-authorization-encrypted-data", "1351f414d687764000a993974029f1f20ac5b37e4b66e86841e22f85d5671926489dd848a0563c67e63ec61a5cdaff9756e3c142ae253e8d0a69b13338ebad40");

        	if(cod_cliente > 0)
            {
            DataProcessamento->tbClienteOperadora->First();
            contador_clientes = 0;
            Label23->Caption = contador_clientes;
            Label25->Caption = final_clientes;
            }

            do
            {
            consulta = "select * from credenciamento_stone where credenciamento_stone.CODIGO is not null";

                if(cod_cliente > 0)
                {
                consulta = "select * from credenciamento_stone where credenciamento_stone.CODIGO is not null ";
                consulta += " and credenciamento_stone.STONECODE = '" + DataProcessamento->tbClienteOperadoraCODIGO_ESTABELECIMENTO->AsString + "'";
                }

            Data2->tbCredenciadosStone->Close();
            Data2->tbCredenciadosStone->SQL->Clear();
            Data2->tbCredenciadosStone->SQL->Add(consulta);
            Data2->tbCredenciadosStone->Open();

            Data2->tbCredenciadosStone->Last();
            final = Data2->tbCredenciadosStone->RecordCount;
            Data2->tbCredenciadosStone->First();

            	if(cod_cliente > 0)
                {
                Label25->Caption = final_clientes;
                }
                else
                {
                Label25->Caption = final;
                }

            ProgressBar3->Max = final;
            ProgressBar3->Position = 0;

            dtPresent = DateTimePicker1->Date + contador_dias;
            DecodeDate(dtPresent, Year, Month, Day);

            Edit1->Text = Year;
            data_consulta = Edit1->Text;
            data_referencia = Edit1->Text + "-";
            Edit1->Text = Month;

                if(StrLen(Edit1->Text.c_str()) == 1)
                {
                data_consulta += "0" + Edit1->Text;
                data_referencia += "0" + Edit1->Text + "-";
                }
                else
                {
                data_consulta += Edit1->Text;
                data_referencia += Edit1->Text + "-";
                }

            Edit1->Text = Day;

                if(StrLen(Edit1->Text.c_str()) == 1)
                {
                data_consulta += "0" + Edit1->Text;
                data_referencia += "0" + Edit1->Text;
                }
                else
                {
                data_consulta += Edit1->Text;
                data_referencia += Edit1->Text;
                }

                for(int contador = 0; contador < final; contador++)
                {
                Label22->Caption = Data2->tbCredenciadosStoneSTONECODE->AsString;
                Application->ProcessMessages();

                    if(Data2->tbCredenciadosStoneCNPJ_ESTABELECIMENTO->AsString == "")
                    {
                    consulta = "select * FROM cliente_operadora where cliente_operadora.CODIGO is not null";
                    consulta += " and cliente_operadora.CODIGO_ESTABELECIMENTO = '" + Data2->tbCredenciadosStoneSTONECODE->AsString + "'";
                    consulta += " and cliente_operadora.COD_ADQUIRENTE = 7";

                    DataResumo->tbClientesOperadoras->Close();
                    DataResumo->tbClientesOperadoras->SQL->Clear();
                    DataResumo->tbClientesOperadoras->SQL->Add(consulta);
                    DataResumo->tbClientesOperadoras->Open();

                        if(DataResumo->tbClientesOperadoras->RecordCount == 1)
                        {
                        Data2->tbCredenciadosStone->Edit();
                        Data2->tbCredenciadosStoneCNPJ_ESTABELECIMENTO->Value = DataResumo->tbClientesOperadorasCNPJ_ESTABELECIMENTO->AsString;
                        Data2->tbCredenciadosStone->ApplyUpdates(0);
                        }
                    }

                    if(Data2->tbCredenciadosStoneLIBERADO->AsString != 'S')
                    {
                    IdHTTP1->Request->CustomHeaders->Clear();
                    IdHTTP1->Request->CustomHeaders->AddValue("authorization", "Bearer 028f2e66-0134-477a-8d4c-12f122767680");
                    IdHTTP1->Request->CustomHeaders->AddValue("x-authorization-raw-data", "Conciflex");
                    IdHTTP1->Request->CustomHeaders->AddValue("x-authorization-encrypted-data", "1351f414d687764000a993974029f1f20ac5b37e4b66e86841e22f85d5671926489dd848a0563c67e63ec61a5cdaff9756e3c142ae253e8d0a69b13338ebad40");

                    url = "https://conciliation.stone.com.br/v1/merchant/" + Data2->tbCredenciadosStoneSTONECODE->AsString;
                    url += "/access-authorization/status?since=" + data_consulta;

                    continuar = true;

                        try
                        {
                        Application->ProcessMessages();

                        Memo3->Text = IdHTTP1->Get(url);
                        }
                        catch (EIdHTTPProtocolException &E)
                        {
                            try
                            {
                            Memo3->Text = IdHTTP1->Get(url);
                            }
                            catch (EIdHTTPProtocolException &E)
                            {
                                try
                                {
                                Memo3->Text = IdHTTP1->Get(url);
                                }
                                catch (EIdHTTPProtocolException &E)
                                {
                                erro++;
                                Label17->Caption = erro;

                                consulta = "- Não foi possível consultar o status de autorização do stone code " + Data2->tbCredenciadosStoneSTONECODE->AsString;
                                consulta += " na data " + data_consulta;

                                Memo2->Lines->Add(consulta);
                                continuar = false;
                                }
                            }
                        }

                        if(IdHTTP1->ResponseCode == 200 && continuar)
                        {
                        json = (TJSONObject*) TJSONObject::ParseJSONValue(TEncoding::ASCII->GetBytes(Memo3->Lines->Text),0);

                        retorno = json->GetValue("currentAccessStatus")->ToString();

                            if(retorno == "\"Allowed\"")
                            {
                            Data2->tbCredenciadosStone->Edit();
                            Data2->tbCredenciadosStoneLIBERADO->Value = 'S';
                            Data2->tbCredenciadosStone->ApplyUpdates(0);
                            }

                        json->Free();
                        }
                    }

                    if(Data2->tbCredenciadosStoneLIBERADO->AsString == "S")
                    {
                    //A REQUISIÇÃO DOS ARQUIVOS FORAM FEITAS VIA API EM PHP POIS A STONE FAZ REDIRECIONAMENTO DEPOIS DE DISPARADA
                    //A REQUISIÇÃO E O INDY CLIENT (IDHTTP) PERDE O AUTHORIZATION
                    //url = "http://127.0.0.1/conciflex/Admin/public/api/stone/" + Data2->tbCredenciadosStoneSTONECODE->AsString + "/" + data_consulta;
                    url = "https://login.conciflex.com.br/api/stone/" + Data2->tbCredenciadosStoneSTONECODE->AsString + "/" + data_consulta;

                    continuar = true;

                        try
                        {
                        Application->ProcessMessages();
                        Memo3->Text = IdHTTP1->Get(url);
                        }
                        catch (EIdHTTPProtocolException &E)
                        {
                            try
                            {
                            Memo3->Text = IdHTTP1->Get(url);
                            }
                            catch (EIdHTTPProtocolException &E)
                            {
                                try
                                {
                                Memo3->Text = IdHTTP1->Get(url);
                                }
                                catch (EIdHTTPProtocolException &E)
                                {
                                erro++;
                                Label17->Caption = erro;

                                consulta = "- Não foi possível consultar os dados de vendas e pagamentos do stone code " + Data2->tbCredenciadosStoneSTONECODE->AsString;
                                consulta += " referente a data " + data_consulta;

                                Memo2->Lines->Add(consulta);
                                continuar = false;
                                }
                            }
                        }

                        if(IdHTTP1->ResponseCode == 200 && continuar)
                        {
                        Memo3->Text = "C:/SFTP_Root/stone/" + data_consulta + "_" + Data2->tbCredenciadosStoneSTONECODE->AsString + ".xml";

                            try
                            {
                            XMLDocument1->LoadFromFile(Memo3->Text);
                            }
                            catch(...)
                            {
                            erro++;
                            Label17->Caption = erro;

                            consulta = "- Não foi possível abrir o arquivo " + Memo3->Text + " de dados do stone code " + Data2->tbCredenciadosStoneSTONECODE->AsString;
                            consulta += " referente a data " + data_consulta;

                            Memo2->Lines->Add(consulta);

                            goto continuar;
                            }

                        nodes = XMLDocument1->DocumentElement->ChildNodes;

                        nodeHeader = nodes->FindNode("Header");

                        //--------------------------------------------

                            //HEADER
                            if(nodeHeader)
                            {
                            Application->ProcessMessages();

                            //VERIFICA SE JÁ FOI CONSIDERADO
                            consulta = "select * from edi_stone_header where edi_stone_header.CODIGO is not null";
                            consulta += " and edi_stone_header.COD_CREDENCIAMENTO = " + Data2->tbCredenciadosStoneCODIGO->AsString;
                            consulta += " and edi_stone_header.DATA_REFERENCIA = '" + data_referencia + "'";

                            Data2->tbHeaderStone->Close();
                            Data2->tbHeaderStone->SQL->Clear();
                            Data2->tbHeaderStone->SQL->Add(consulta);
                            Data2->tbHeaderStone->Open();

                            reprocessamento = false;

                            Label27->Caption = "Lendo o Header";
                            Label2->Caption = "Lendo o Header";

                                if(Data2->tbHeaderStone->RecordCount == 0)
                                {
                                Data2->tbHeaderStone->Insert();

                                dado = "";
                                auxiliar = "";

                                node = nodeHeader->ChildNodes->FindNode("GenerationDateTime");

                                    if(node)
                                    {
                                    auxiliar = node->Text;

                                    dado = auxiliar.SubString(7, 2) + "/";
                                    dado += auxiliar.SubString(5, 2) + "/";
                                    dado += auxiliar.SubString(0, 4);

                                    Data2->tbHeaderStoneDATA_GERACAO->Value = StrToDate(dado);
                                    }

                                node = nodeHeader->ChildNodes->FindNode("StoneCode");

                                    if(node)
                                        Data2->tbHeaderStoneSTONECODE->Value = node->Text;

                                node = nodeHeader->ChildNodes->FindNode("LayoutVersion");

                                    if(node)
                                        Data2->tbHeaderStoneLAYOUT_VERSION->Value = node->Text;

                                node = nodeHeader->ChildNodes->FindNode("ReferenceDate");

                                    if(node)
                                    {
                                    auxiliar = node->Text;

                                    dado = auxiliar.SubString(7, 2) + "/";
                                    dado += auxiliar.SubString(5, 2) + "/";
                                    dado += auxiliar.SubString(0, 4);

                                    Data2->tbHeaderStoneDATA_REFERENCIA->Value = StrToDate(dado);
                                    }

                                Data2->tbHeaderStoneCOD_CREDENCIAMENTO->Value = Data2->tbCredenciadosStoneCODIGO->AsFloat;
                                Data2->tbHeaderStone->ApplyUpdates(0);
                                }
                                else
                                {
                                reprocessamento = true;
                                }

                            codigo = Data2->tbHeaderStoneCODIGO->AsInteger;

                            capturas = pagamentos = cancelamentos = chargebacks = chargeback_estorno = 0;

                            //---------------------------------------------------------
                            //FinancialTransactions

                            nodeTransaction = nodes->FindNode("FinancialTransactions");

                                if(nodeTransaction)
                                {
                                //<FinancialTransactions>
                                Label27->Caption = "Lendo Vendas";
                                Label2->Caption = "Lendo Vendas";
                                Label30->Caption = 0;
                                Label6->Caption = 0;
                                Label31->Caption = nodeTransaction->ChildNodes->Count;
                                Label7->Caption = nodeTransaction->ChildNodes->Count;

                                    //<Transaction>
                                    for(int contador2 = 0; contador2 < nodeTransaction->ChildNodes->Count; contador2++)
                                    {

                                        if(contador2 == 642)
                                        {
                                        Edit1->Text = "ok";
                                        }

                                    Application->ProcessMessages();

                                    NSU = codigo_transacao = data_autorizacao = hora_autorizacao = data_captura = hora_captura = "";
                                    internacional = codigo_autorizacao = num_cartao = num_terminal = previsao_pagamento = "";
                                    cod_tipo_conta = cod_tipo_pagamento = cod_tipo_terminal = total_parcelas = cod_bandeira = num_parcela = 0;
                                    valor_autorizado = valor_capturado = total_cancelado = valor_bruto_parcela = valor_liquido_parcela = 0;

                                    node = nodeTransaction->ChildNodes->Get(contador2);

                                    //<Events>
                                    nodeAuxiliar = node->ChildNodes->FindNode("Events");

                                    capturas = StrToInt(nodeAuxiliar->ChildNodes->FindNode("Captures")->Text);
                                    pagamentos = StrToInt(nodeAuxiliar->ChildNodes->FindNode("Payments")->Text);
                                    cancelamentos = StrToInt(nodeAuxiliar->ChildNodes->FindNode("Cancellations")->Text);
                                    chargebacks = StrToInt(nodeAuxiliar->ChildNodes->FindNode("Chargebacks")->Text);
                                    chargeback_estorno = StrToInt(nodeAuxiliar->ChildNodes->FindNode("ChargebackRefunds")->Text);
                                    //---------------------------------------------------------

                                    NSU = node->ChildNodes->FindNode("AcquirerTransactionKey")->Text;
                                    codigo_transacao = node->ChildNodes->FindNode("InitiatorTransactionKey")->Text;

                                    auxiliar = node->ChildNodes->FindNode("AuthorizationDateTime")->Text;

                                    data_autorizacao = auxiliar.SubString(7, 2) + "/";
                                    data_autorizacao += auxiliar.SubString(5, 2) + "/";
                                    data_autorizacao += auxiliar.SubString(0,4);

                                    hora_autorizacao = auxiliar.SubString(9, 2) + ":";
                                    hora_autorizacao += auxiliar.SubString(11, 2) + ":";
                                    hora_autorizacao += auxiliar.SubString(13, 2);

                                    auxiliar = node->ChildNodes->FindNode("CaptureLocalDateTime")->Text;

                                    data_captura = auxiliar.SubString(7, 2) + "/";
                                    data_captura += auxiliar.SubString(5, 2) + "/";
                                    data_captura += auxiliar.SubString(0, 4);

                                    hora_captura = auxiliar.SubString(9, 2) + ":";
                                    hora_captura += auxiliar.SubString(11, 2) + ":";
                                    hora_captura += auxiliar.SubString(13, 2);

                                    //<Poi>
                                    nodeAuxiliar = node->ChildNodes->FindNode("Poi");

                                    cod_tipo_terminal = StrToInt(nodeAuxiliar->ChildNodes->FindNode("PoiType")->Text);

                                        if(cod_tipo_terminal == 1)
                                            num_terminal = nodeAuxiliar->ChildNodes->FindNode("SerialNumber")->Text;

                                        if(capturas > 0)
                                        {
                                        internacional = node->ChildNodes->FindNode("International")->Text;
                                        cod_tipo_conta = StrToInt(node->ChildNodes->FindNode("AccountType")->Text);
                                        cod_tipo_pagamento = StrToInt(node->ChildNodes->FindNode("InstallmentType")->Text);
                                        total_parcelas = StrToInt(node->ChildNodes->FindNode("NumberOfInstallments")->Text);
                                        valor_autorizado = RetirarPontuacao(node->ChildNodes->FindNode("AuthorizedAmount")->Text);
                                        valor_capturado = RetirarPontuacao(node->ChildNodes->FindNode("CapturedAmount")->Text);

                                            if(cancelamentos > 0)
                                            {
                                                if(node->ChildNodes->FindNode("CanceledAmount"))
                                                    total_cancelado = RetirarPontuacao(node->ChildNodes->FindNode("CanceledAmount")->Text);
                                            }

                                        codigo_autorizacao = node->ChildNodes->FindNode("IssuerAuthorizationCode")->Text;
                                        cod_bandeira = StrToInt(node->ChildNodes->FindNode("BrandId")->Text);
                                        num_cartao = node->ChildNodes->FindNode("CardNumber")->Text;

                                        //<Installments>
                                        nodeParcelas = node->ChildNodes->FindNode("Installments");

                                        Data2->tbVendaStone->Close();
                                        Data2->tbVendaStone->SQL->Clear();
                                        Data2->tbVendaStone->SQL->Add("select * from edi_stone_comprovante_venda where edi_stone_comprovante_venda.CODIGO is null");
                                        Data2->tbVendaStone->Open();

                                            for(int contador3 = 0; contador3 < nodeParcelas->ChildNodes->Count; contador3++)
                                            {
                                            Application->ProcessMessages();
                                            //<Installment>
                                            nodeParcela = nodeParcelas->ChildNodes->Get(contador3);

                                            num_parcela = StrToInt(nodeParcela->ChildNodes->FindNode("InstallmentNumber")->Text);
                                            valor_bruto_parcela = RetirarPontuacao(nodeParcela->ChildNodes->FindNode("GrossAmount")->Text);
                                            valor_liquido_parcela = RetirarPontuacao(nodeParcela->ChildNodes->FindNode("NetAmount")->Text);

                                                if(nodeParcela->ChildNodes->FindNode("PrevisionPaymentDate"))
                                                {
                                                dado = nodeParcela->ChildNodes->FindNode("PrevisionPaymentDate")->Text;
                                                }

                                                if(nodeParcela->ChildNodes->FindNode("OriginalPaymentDate"))
                                                {
                                                dado = nodeParcela->ChildNodes->FindNode("OriginalPaymentDate")->Text;
                                                }

                                            previsao_pagamento = dado.SubString(7, 2) + "/";
                                            previsao_pagamento += dado.SubString(5, 2) + "/";
                                            previsao_pagamento += dado.SubString(0, 4);

                                            duplicidade = false;

                                                //CONTROLE DE DUPLICIDADE
                                                if(reprocessamento)
                                                {
                                                consulta = "select * from edi_stone_comprovante_venda where edi_stone_comprovante_venda.CODIGO_AUTORIZACAO = '" + codigo_autorizacao + "'";
                                                consulta += " and edi_stone_comprovante_venda.CODIGO_TRANSACAO = '" + codigo_transacao + "'";
                                                consulta += " and edi_stone_comprovante_venda.STONECODE = '" + Data2->tbHeaderStoneSTONECODE->AsString + "'";
                                                consulta += " and edi_stone_comprovante_venda.NSU = '" + NSU + "'";
                                                consulta += " and edi_stone_comprovante_venda.NUM_PARCELA = '" + IntToStr(num_parcela) + "'";
                                                consulta += " and edi_stone_comprovante_venda.COD_HEADER = '" + Data2->tbHeaderStoneCODIGO->AsString + "'";

                                                Data2->tbVendaStone->Close();
                                                Data2->tbVendaStone->SQL->Clear();
                                                Data2->tbVendaStone->SQL->Add(consulta);
                                                Data2->tbVendaStone->Open();

                                                    if(Data2->tbVendaStone->RecordCount > 0)
                                                    {
                                                    duplicidade = true;
                                                    }
                                                }

                                                if(!duplicidade)
                                                {
                                                Data2->tbVendaStone->Insert();
                                                Data2->tbVendaStoneCODIGO_AUTORIZACAO->Value = codigo_autorizacao;
                                                Data2->tbVendaStoneCODIGO_TRANSACAO->Value = codigo_transacao;
                                                Data2->tbVendaStoneCOD_BANDEIRA->Value = cod_bandeira;
                                                Data2->tbVendaStoneCOD_HEADER->Value = codigo;
                                                Data2->tbVendaStoneCOD_TIPO_CONTA->Value = cod_tipo_conta;
                                                Data2->tbVendaStoneCOD_TIPO_PAGAMENTO->Value = cod_tipo_pagamento;
                                                Data2->tbVendaStoneCOD_TIPO_TERMINAL->Value = cod_tipo_terminal;
                                                Data2->tbVendaStoneDATA_AUTORIZACAO->Value = StrToDate(data_autorizacao);
                                                Data2->tbVendaStoneDATA_CAPTURA->Value = StrToDate(data_captura);
                                                Data2->tbVendaStoneHORA_AUTORIZACAO->Value = StrToTime(hora_autorizacao);
                                                Data2->tbVendaStoneHORA_CAPTURA->Value = StrToTime(hora_captura);
                                                Data2->tbVendaStoneINTERNACIONAL->Value = internacional;
                                                Data2->tbVendaStoneNSU->Value = NSU;
                                                Data2->tbVendaStoneNUM_CARTAO->Value = num_cartao;
                                                Data2->tbVendaStoneNUM_PARCELA->Value = num_parcela;
                                                Data2->tbVendaStoneNUM_TERMINAL->Value = num_terminal;
                                                Data2->tbVendaStonePREVISAO_PAGAMENTO->Value = StrToDate(previsao_pagamento);
                                                Data2->tbVendaStoneTOTAL_CANCELADO->Value = total_cancelado;
                                                Data2->tbVendaStoneTOTAL_PARCELAS->Value = total_parcelas;
                                                Data2->tbVendaStoneVALOR_AUTORIZADO->Value = valor_autorizado;
                                                Data2->tbVendaStoneVALOR_BRUTO_PARCELA->Value = valor_bruto_parcela;
                                                Data2->tbVendaStoneVALOR_CAPTURADO->Value = valor_capturado;
                                                Data2->tbVendaStoneVALOR_LIQUIDO_PARCELA->Value = valor_liquido_parcela;

                                                Data2->tbVendaStoneTRATADO->Value = 'N';
                                                Data2->tbVendaStoneSTONECODE->Value = Data2->tbHeaderStoneSTONECODE->AsString;

                                                Data2->tbVendaStone->ApplyUpdates(0);
                                                }

                                            Application->ProcessMessages();
                                            }
                                        }

                                        if(cancelamentos > 0)
                                        {
                                        //<Cancellations>
                                        Label27->Caption = "Lendo Cancelamento de Vendas";
                                        Label2->Caption = "Lendo Cancelamento de Vendas";

                                        nodeAuxiliar = node->ChildNodes->FindNode("Cancellations");

                                        Data2->tbCancelamentoStone->Close();
                                        Data2->tbCancelamentoStone->SQL->Clear();
                                        Data2->tbCancelamentoStone->SQL->Add("select * from edi_stone_cancelamento where edi_stone_cancelamento.CODIGO is null");
                                        Data2->tbCancelamentoStone->Open();

                                            for(int contador3 = 0; contador3 < nodeAuxiliar->ChildNodes->Count; contador3++)
                                            {
                                            Application->ProcessMessages();

                                            valor_estornado = num_parcela = 0;
                                            previsao_cobranca = id_pagamento = "";

                                            //<Cancellation>
                                            nodeParcela = nodeAuxiliar->ChildNodes->Get(contador3);

                                                if(nodeParcela->ChildNodes->FindNode("PaymentId"))
                                                    id_pagamento = nodeParcela->ChildNodes->FindNode("PaymentId")->Text;


                                            codigo_cancelamento = nodeParcela->ChildNodes->FindNode("OperationKey")->Text;

                                                if(nodeParcela->ChildNodes->FindNode("InstallmentNumber"))
                                                        num_parcela = StrToInt(nodeParcela->ChildNodes->FindNode("InstallmentNumber")->Text);

                                            dado = nodeParcela->ChildNodes->FindNode("CancellationDateTime")->Text;

                                            data_cancelamento = dado.SubString(7, 2) + "/";
                                            data_cancelamento += dado.SubString(5, 2) + "/";
                                            data_cancelamento += dado.SubString(0, 4);

                                            hora_cancelamento = dado.SubString(9, 2) + ":";
                                            hora_cancelamento += dado.SubString(11, 2) + ":";
                                            hora_cancelamento += dado.SubString(13, 2);

                                            valor_estornado = RetirarPontuacao(nodeParcela->ChildNodes->FindNode("ReturnedAmount")->Text);

                                            Data2->tbCancelamentoStone->Close();
                                            Data2->tbCancelamentoStone->SQL->Clear();
                                            Data2->tbCancelamentoStone->SQL->Add("select * from edi_stone_cancelamento where edi_stone_cancelamento.CODIGO is null");
                                            Data2->tbCancelamentoStone->Open();

                                                if(nodeParcela->ChildNodes->FindNode("Billing"))
                                                {
                                                nodeParcelas = nodeParcela->ChildNodes->FindNode("Billing");

                                                valor_cancelamento = RetirarPontuacao(nodeParcelas->ChildNodes->Get(0)->Text);

                                                dado = nodeParcelas->ChildNodes->Get(1)->Text;

                                                previsao_cobranca = dado.SubString(7, 2) + "/";
                                                previsao_cobranca += dado.SubString(5, 2) + "/";
                                                previsao_cobranca += dado.SubString(0, 4);

                                                duplicidade = false;

                                                    //CONTROLE DE DUPLICIDADE
                                                    if(reprocessamento)
                                                    {
                                                    consulta = "select * from edi_stone_cancelamento where edi_stone_cancelamento.ID_PAGAMENTO = '" + id_pagamento + "'";
                                                    consulta += " and edi_stone_cancelamento.CODIGO_CANCELAMENTO = '" + codigo_cancelamento + "'";
                                                    consulta += " and edi_stone_cancelamento.STONECODE = '" + Data2->tbHeaderStoneSTONECODE->AsString + "'";
                                                    consulta += " and edi_stone_cancelamento.NSU = '" + NSU + "'";
                                                    consulta += " and edi_stone_cancelamento.NUM_PARCELA = '" + IntToStr(num_parcela) + "'";
                                                    consulta += " and edi_stone_cancelamento.COD_HEADER = '" + Data2->tbHeaderStoneCODIGO->AsString + "'";

                                                    Data2->tbCancelamentoStone->Close();
                                                    Data2->tbCancelamentoStone->SQL->Clear();
                                                    Data2->tbCancelamentoStone->SQL->Add(consulta);
                                                    Data2->tbCancelamentoStone->Open();

                                                        if(Data2->tbCancelamentoStone->RecordCount > 0)
                                                        {
                                                        duplicidade = true;
                                                        }
                                                    }

                                                    if(!duplicidade)
                                                    {
                                                    Data2->tbCancelamentoStone->Insert();

                                                    Data2->tbCancelamentoStoneCODIGO_CANCELAMENTO->Value = codigo_cancelamento;
                                                    Data2->tbCancelamentoStoneCOD_HEADER->Value = codigo;
                                                    Data2->tbCancelamentoStoneID_PAGAMENTO->Value = id_pagamento;
                                                    Data2->tbCancelamentoStoneNSU->Value = NSU;
                                                    Data2->tbCancelamentoStoneNUM_PARCELA->Value = num_parcela;
                                                    Data2->tbCancelamentoStoneVALOR_ESTORNADO_CLIENTE->Value = valor_estornado;
                                                    Data2->tbCancelamentoStoneDATA_CANCELAMENTO->Value = StrToDate(data_cancelamento);
                                                    Data2->tbCancelamentoStoneHORA_CANCELAMENTO->Value = StrToTime(hora_cancelamento);
                                                    Data2->tbCancelamentoStoneDATA_AUTORIZACAO_VENDA->Value = StrToDate(data_autorizacao);
                                                    Data2->tbCancelamentoStoneHORA_AUTORIZACAO_VENDA->Value = StrToTime(hora_autorizacao);
                                                    Data2->tbCancelamentoStoneDATA_CAPTURA_VENDA->Value = StrToDate(data_captura);
                                                    Data2->tbCancelamentoStoneHORA_CAPTURA_VENDA->Value = StrToTime(hora_captura);
                                                    Data2->tbCancelamentoStoneDATA_PREVISAO_COBRANCA->Value = StrToDate(previsao_cobranca);
                                                    Data2->tbCancelamentoStoneVALOR_DESCONTADO_LOJISTA->Value = valor_cancelamento;
                                                    Data2->tbCancelamentoStoneTIPO->Value = 'V';

                                                    Data2->tbCancelamentoStoneTRATADO->Value = 'N';
                                                    Data2->tbCancelamentoStoneSTONECODE->Value = Data2->tbHeaderStoneSTONECODE->AsString;

                                                    Data2->tbCancelamentoStone->ApplyUpdates(0);
                                                    }
                                                }
                                                else
                                                {
                                                duplicidade = false;

                                                    //CONTROLE DE DUPLICIDADE
                                                    if(reprocessamento)
                                                    {
                                                    consulta = "select * from edi_stone_cancelamento where edi_stone_cancelamento.ID_PAGAMENTO = '" + id_pagamento + "'";
                                                    consulta += " and edi_stone_cancelamento.CODIGO_CANCELAMENTO = '" + codigo_cancelamento + "'";
                                                    consulta += " and edi_stone_cancelamento.STONECODE = '" + Data2->tbHeaderStoneSTONECODE->AsString + "'";
                                                    consulta += " and edi_stone_cancelamento.NSU = '" + NSU + "'";
                                                    consulta += " and edi_stone_cancelamento.NUM_PARCELA = '" + IntToStr(num_parcela) + "'";
                                                    consulta += " and edi_stone_cancelamento.COD_HEADER = '" + Data2->tbHeaderStoneCODIGO->AsString + "'";

                                                    Data2->tbCancelamentoStone->Close();
                                                    Data2->tbCancelamentoStone->SQL->Clear();
                                                    Data2->tbCancelamentoStone->SQL->Add(consulta);
                                                    Data2->tbCancelamentoStone->Open();

                                                        if(Data2->tbCancelamentoStone->RecordCount > 0)
                                                        {
                                                        duplicidade = true;
                                                        }
                                                    }

                                                    if(!duplicidade)
                                                    {
                                                    Data2->tbCancelamentoStone->Insert();

                                                    Data2->tbCancelamentoStoneCODIGO_CANCELAMENTO->Value = codigo_cancelamento;
                                                    Data2->tbCancelamentoStoneCOD_HEADER->Value = codigo;
                                                    Data2->tbCancelamentoStoneID_PAGAMENTO->Value = id_pagamento;
                                                    Data2->tbCancelamentoStoneNSU->Value = NSU;
                                                    Data2->tbCancelamentoStoneNUM_PARCELA->Value = num_parcela;
                                                    Data2->tbCancelamentoStoneVALOR_ESTORNADO_CLIENTE->Value = valor_estornado;
                                                    Data2->tbCancelamentoStoneDATA_CANCELAMENTO->Value = StrToDate(data_cancelamento);
                                                    Data2->tbCancelamentoStoneHORA_CANCELAMENTO->Value = StrToTime(hora_cancelamento);
                                                    Data2->tbCancelamentoStoneDATA_AUTORIZACAO_VENDA->Value = StrToDate(data_autorizacao);
                                                    Data2->tbCancelamentoStoneHORA_AUTORIZACAO_VENDA->Value = StrToTime(hora_autorizacao);
                                                    Data2->tbCancelamentoStoneDATA_CAPTURA_VENDA->Value = StrToDate(data_captura);
                                                    Data2->tbCancelamentoStoneHORA_CAPTURA_VENDA->Value = StrToTime(hora_captura);
                                                    Data2->tbCancelamentoStoneTIPO->Value = 'V';

                                                    Data2->tbCancelamentoStoneTRATADO->Value = 'N';
                                                    Data2->tbCancelamentoStoneSTONECODE->Value = Data2->tbHeaderStoneSTONECODE->AsString;

                                                    Data2->tbCancelamentoStone->ApplyUpdates(0);
                                                    }
                                                }

                                            Application->ProcessMessages();
                                            }
                                        }

                                    Label30->Caption = contador2 + 1;
                                    Label6->Caption = contador2 + 1;
                                    Application->ProcessMessages();
                                    }
                                }


                            //----------------------------------------------------------------------
                            //FinancialTransactionsAccounts
                            nodeTransaction = nodes->FindNode("FinancialTransactionsAccounts");

                                if(nodeTransaction)
                                {
                                //<FinancialTransactionsAccounts>
                                Label27->Caption = "Lendo Pagamentos";
                                Label2->Caption = "Lendo Pagamentos";
                                pagamentos = 0;
                                cancelamentos = 0;

                                Data2->tbPagamentoStone->Close();
                                Data2->tbPagamentoStone->SQL->Clear();
                                Data2->tbPagamentoStone->SQL->Add("select * from edi_stone_comprovante_pagamento where edi_stone_comprovante_pagamento.CODIGO is null");
                                Data2->tbPagamentoStone->Open();

                                Label30->Caption = 0;
                                Label6->Caption = 0;
                                Label31->Caption = nodeTransaction->ChildNodes->Count;
                                Label7->Caption = nodeTransaction->ChildNodes->Count;

                                    //<Transaction>
                                    for(int contador2 = 0; contador2 < nodeTransaction->ChildNodes->Count; contador2++)
                                    {
                                    Application->ProcessMessages();

                                    node = nodeTransaction->ChildNodes->Get(contador2);

                                    //<Events>
                                    nodeAuxiliar = node->ChildNodes->FindNode("Events");

                                    pagamentos = StrToInt(nodeAuxiliar->ChildNodes->FindNode("Payments")->Text);
                                    cancelamentos = StrToInt(nodeAuxiliar->ChildNodes->FindNode("CancellationCharges")->Text);
                                    //-----------------------------------------------------

                                    NSU = node->ChildNodes->FindNode("AcquirerTransactionKey")->Text;
                                    codigo_transacao = node->ChildNodes->FindNode("InitiatorTransactionKey")->Text;

                                    auxiliar = node->ChildNodes->FindNode("AuthorizationDateTime")->Text;

                                    data_autorizacao = auxiliar.SubString(7, 2) + "/";
                                    data_autorizacao += auxiliar.SubString(5, 2) + "/";
                                    data_autorizacao += auxiliar.SubString(0,4);

                                    hora_autorizacao = auxiliar.SubString(9, 2) + ":";
                                    hora_autorizacao += auxiliar.SubString(11, 2) + ":";
                                    hora_autorizacao += auxiliar.SubString(13, 2);

                                        if(pagamentos > 0)
                                        {
                                        //<Installments>
                                        nodeParcelas = node->ChildNodes->FindNode("Installments");

                                            for(int contador3 = 0; contador3 < nodeParcelas->ChildNodes->Count; contador3++)
                                            {
                                            Application->ProcessMessages();

                                            desconto_antecipacao = 0;
                                            pagamento_original = "";

                                            //<Installment>
                                            nodeParcela = nodeParcelas->ChildNodes->Get(contador3);

                                            num_parcela = StrToInt(nodeParcela->ChildNodes->FindNode("InstallmentNumber")->Text);
                                            valor_bruto_parcela = RetirarPontuacao(nodeParcela->ChildNodes->FindNode("GrossAmount")->Text);
                                            valor_liquido_parcela = RetirarPontuacao(nodeParcela->ChildNodes->FindNode("NetAmount")->Text);

                                            dado = nodeParcela->ChildNodes->FindNode("PaymentDate")->Text;

                                            pagamento_parcela = dado.SubString(7, 2) + "/";
                                            pagamento_parcela += dado.SubString(5, 2) + "/";
                                            pagamento_parcela += dado.SubString(0, 4);

                                                if(nodeParcela->ChildNodes->FindNode("AdvanceRateAmount"))
                                                {
                                                desconto_antecipacao = RetirarPontuacao(nodeParcela->ChildNodes->FindNode("AdvanceRateAmount")->Text);

                                                dado = nodeParcela->ChildNodes->FindNode("AdvancedReceivableOriginalPaymentDate")->Text;

                                                pagamento_original = dado.SubString(7, 2) + "/";
                                                pagamento_original += dado.SubString(5, 2) + "/";
                                                pagamento_original += dado.SubString(0, 4);
                                                }

                                            id_pagamento = nodeParcela->ChildNodes->FindNode("PaymentId")->Text;

                                            duplicidade = false;

                                                //CONTROLE DE DUPLICIDADE
                                                if(reprocessamento)
                                                {
                                                consulta = "select * from edi_stone_comprovante_pagamento where edi_stone_comprovante_pagamento.ID_PAGAMENTO = '" + id_pagamento + "'";
                                                consulta += " and edi_stone_comprovante_pagamento.STONECODE = '" + Data2->tbHeaderStoneSTONECODE->AsString + "'";
                                                consulta += " and edi_stone_comprovante_pagamento.NSU = '" + NSU + "'";
                                                consulta += " and edi_stone_comprovante_pagamento.NUM_PARCELA = '" + IntToStr(num_parcela) + "'";
                                                consulta += " and edi_stone_comprovante_pagamento.COD_HEADER = '" + Data2->tbHeaderStoneCODIGO->AsString + "'";

                                                Data2->tbPagamentoStone->Close();
                                                Data2->tbPagamentoStone->SQL->Clear();
                                                Data2->tbPagamentoStone->SQL->Add(consulta);
                                                Data2->tbPagamentoStone->Open();

                                                    if(Data2->tbPagamentoStone->RecordCount > 0)
                                                    {
                                                    duplicidade = true;
                                                    }
                                                }

                                                if(!duplicidade)
                                                {
                                                Data2->tbPagamentoStone->Insert();
                                                Data2->tbPagamentoStoneCOD_HEADER->Value = codigo;
                                                Data2->tbPagamentoStoneID_PAGAMENTO->Value = id_pagamento;
                                                Data2->tbPagamentoStoneNSU->Value = NSU;
                                                Data2->tbPagamentoStoneNUM_PARCELA->Value = num_parcela;
                                                Data2->tbPagamentoStonePAGAMENTO_PARCELA->Value = StrToDate(pagamento_parcela);
                                                Data2->tbPagamentoStoneCODIGO_TRANSACAO->Value = codigo_transacao;
                                                Data2->tbPagamentoStoneDATA_AUTORIZACAO->Value = StrToDate(data_autorizacao);
                                                Data2->tbPagamentoStoneHORA_AUTORIZACAO->Value = StrToTime(hora_autorizacao);

                                                    if(desconto_antecipacao > 0)
                                                    {
                                                    Data2->tbPagamentoStonePAGAMENTO_REAL_ANTECIPADO->Value = StrToDate(pagamento_original);
                                                    Data2->tbPagamentoStoneDESCONTO_ANTECIPACAO->Value = desconto_antecipacao;
                                                    }

                                                Data2->tbPagamentoStoneVALOR_BRUTO_PARCELA->Value = valor_bruto_parcela;
                                                Data2->tbPagamentoStoneVALOR_LIQUIDO_PARCELA->Value = valor_liquido_parcela;

                                                Data2->tbPagamentoStoneTRATADO->Value = 'N';
                                                Data2->tbPagamentoStoneSTONECODE->Value = Data2->tbHeaderStoneSTONECODE->AsString;

                                                Data2->tbPagamentoStone->ApplyUpdates(0);
                                                }

                                            Application->ProcessMessages();
                                            }
                                        }

                                        if(cancelamentos > 0)
                                        {
                                        //<Cancellations>
                                        Label27->Caption = "Lendo Cancelamento de Pagamentos";
                                        Label2->Caption = "Lendo Cancelamento de Pagamentos";
                                        nodeAuxiliar = node->ChildNodes->FindNode("Cancellations");

                                        Data2->tbCancelamentoStone->Close();
                                        Data2->tbCancelamentoStone->SQL->Clear();
                                        Data2->tbCancelamentoStone->SQL->Add("select * from edi_stone_cancelamento where edi_stone_cancelamento.CODIGO is null");
                                        Data2->tbCancelamentoStone->Open();

                                            for(int contador3 = 0; contador3 < nodeAuxiliar->ChildNodes->Count; contador3++)
                                            {
                                            Application->ProcessMessages();

                                            valor_estornado = num_parcela = 0;
                                            previsao_cobranca = id_pagamento = "";

                                            //<Cancellation>
                                            nodeParcela = nodeAuxiliar->ChildNodes->Get(contador3);

                                                if(nodeParcela->ChildNodes->FindNode("PaymentId"))
                                                    id_pagamento = nodeParcela->ChildNodes->FindNode("PaymentId")->Text;

                                            codigo_cancelamento = nodeParcela->ChildNodes->FindNode("OperationKey")->Text;

                                                if(nodeParcela->ChildNodes->FindNode("InstallmentNumber"))
                                                        num_parcela = StrToInt(nodeParcela->ChildNodes->FindNode("InstallmentNumber")->Text);

                                            dado = nodeParcela->ChildNodes->FindNode("CancellationDateTime")->Text;

                                            data_cancelamento = dado.SubString(7, 2) + "/";
                                            data_cancelamento += dado.SubString(5, 2) + "/";
                                            data_cancelamento += dado.SubString(0, 4);

                                            hora_cancelamento = dado.SubString(9, 2) + ":";
                                            hora_cancelamento += dado.SubString(11, 2) + ":";
                                            hora_cancelamento += dado.SubString(13, 2);

                                            valor_estornado = RetirarPontuacao(nodeParcela->ChildNodes->FindNode("ReturnedAmount")->Text);

                                            Data2->tbCancelamentoStone->Close();
                                            Data2->tbCancelamentoStone->SQL->Clear();
                                            Data2->tbCancelamentoStone->SQL->Add("select * from edi_stone_cancelamento where edi_stone_cancelamento.CODIGO is null");
                                            Data2->tbCancelamentoStone->Open();

                                                if(nodeParcela->ChildNodes->FindNode("Billing"))
                                                {
                                                nodeParcelas = nodeParcela->ChildNodes->FindNode("Billing");

                                                valor_cancelamento = RetirarPontuacao(nodeParcelas->ChildNodes->Get(0)->Text);

                                                dado = nodeParcelas->ChildNodes->Get(1)->Text;

                                                previsao_cobranca = dado.SubString(7, 2) + "/";
                                                previsao_cobranca += dado.SubString(5, 2) + "/";
                                                previsao_cobranca += dado.SubString(0, 4);

                                                duplicidade = false;

                                                    //CONTROLE DE DUPLICIDADE
                                                    if(reprocessamento)
                                                    {
                                                    consulta = "select * from edi_stone_cancelamento where edi_stone_cancelamento.ID_PAGAMENTO = '" + id_pagamento + "'";
                                                    consulta += " and edi_stone_cancelamento.CODIGO_CANCELAMENTO = '" + codigo_cancelamento + "'";
                                                    consulta += " and edi_stone_cancelamento.STONECODE = '" + Data2->tbHeaderStoneSTONECODE->AsString + "'";
                                                    consulta += " and edi_stone_cancelamento.NSU = '" + NSU + "'";
                                                    consulta += " and edi_stone_cancelamento.NUM_PARCELA = '" + IntToStr(num_parcela) + "'";
                                                    consulta += " and edi_stone_cancelamento.COD_HEADER = '" + Data2->tbHeaderStoneCODIGO->AsString + "'";

                                                    Data2->tbCancelamentoStone->Close();
                                                    Data2->tbCancelamentoStone->SQL->Clear();
                                                    Data2->tbCancelamentoStone->SQL->Add(consulta);
                                                    Data2->tbCancelamentoStone->Open();

                                                        if(Data2->tbCancelamentoStone->RecordCount > 0)
                                                        {
                                                        duplicidade = true;
                                                        }
                                                    }

                                                    if(!duplicidade)
                                                    {
                                                    Data2->tbCancelamentoStone->Insert();

                                                    Data2->tbCancelamentoStoneCODIGO_CANCELAMENTO->Value = codigo_cancelamento;
                                                    Data2->tbCancelamentoStoneCOD_HEADER->Value = codigo;
                                                    Data2->tbCancelamentoStoneID_PAGAMENTO->Value = id_pagamento;
                                                    Data2->tbCancelamentoStoneNSU->Value = NSU;
                                                    Data2->tbCancelamentoStoneNUM_PARCELA->Value = num_parcela;
                                                    Data2->tbCancelamentoStoneVALOR_ESTORNADO_CLIENTE->Value = valor_estornado;
                                                    Data2->tbCancelamentoStoneDATA_CANCELAMENTO->Value = StrToDate(data_cancelamento);
                                                    Data2->tbCancelamentoStoneHORA_CANCELAMENTO->Value = StrToTime(hora_cancelamento);
                                                    Data2->tbCancelamentoStoneDATA_AUTORIZACAO_VENDA->Value = StrToDate(data_autorizacao);
                                                    Data2->tbCancelamentoStoneHORA_AUTORIZACAO_VENDA->Value = StrToTime(hora_autorizacao);
                                                    Data2->tbCancelamentoStoneDATA_CAPTURA_VENDA->Value = StrToDate(data_captura);
                                                    Data2->tbCancelamentoStoneHORA_CAPTURA_VENDA->Value = StrToTime(hora_captura);
                                                    Data2->tbCancelamentoStoneDATA_PREVISAO_COBRANCA->Value = StrToDate(previsao_cobranca);
                                                    Data2->tbCancelamentoStoneVALOR_DESCONTADO_LOJISTA->Value = valor_cancelamento;
                                                    Data2->tbCancelamentoStoneTIPO->Value = 'P';

                                                    Data2->tbCancelamentoStoneTRATADO->Value = 'N';
                                                    Data2->tbCancelamentoStoneSTONECODE->Value = Data2->tbHeaderStoneSTONECODE->AsString;

                                                    Data2->tbCancelamentoStone->ApplyUpdates(0);
                                                    }
                                                }
                                                else
                                                {
                                                duplicidade = false;

                                                    //CONTROLE DE DUPLICIDADE
                                                    if(reprocessamento)
                                                    {
                                                    consulta = "select * from edi_stone_cancelamento where edi_stone_cancelamento.ID_PAGAMENTO = '" + id_pagamento + "'";
                                                    consulta += " and edi_stone_cancelamento.CODIGO_CANCELAMENTO = '" + codigo_cancelamento + "'";
                                                    consulta += " and edi_stone_cancelamento.STONECODE = '" + Data2->tbHeaderStoneSTONECODE->AsString + "'";
                                                    consulta += " and edi_stone_cancelamento.NSU = '" + NSU + "'";
                                                    consulta += " and edi_stone_cancelamento.NUM_PARCELA = '" + IntToStr(num_parcela) + "'";
                                                    consulta += " and edi_stone_cancelamento.COD_HEADER = '" + Data2->tbHeaderStoneCODIGO->AsString + "'";

                                                    Data2->tbCancelamentoStone->Close();
                                                    Data2->tbCancelamentoStone->SQL->Clear();
                                                    Data2->tbCancelamentoStone->SQL->Add(consulta);
                                                    Data2->tbCancelamentoStone->Open();

                                                        if(Data2->tbCancelamentoStone->RecordCount > 0)
                                                        {
                                                        duplicidade = true;
                                                        }
                                                    }

                                                    if(!duplicidade)
                                                    {
                                                    Data2->tbCancelamentoStone->Insert();

                                                    Data2->tbCancelamentoStoneCODIGO_CANCELAMENTO->Value = codigo_cancelamento;
                                                    Data2->tbCancelamentoStoneCOD_HEADER->Value = codigo;
                                                    Data2->tbCancelamentoStoneID_PAGAMENTO->Value = id_pagamento;
                                                    Data2->tbCancelamentoStoneNSU->Value = NSU;
                                                    Data2->tbCancelamentoStoneNUM_PARCELA->Value = num_parcela;
                                                    Data2->tbCancelamentoStoneVALOR_ESTORNADO_CLIENTE->Value = valor_estornado;
                                                    Data2->tbCancelamentoStoneDATA_CANCELAMENTO->Value = StrToDate(data_cancelamento);
                                                    Data2->tbCancelamentoStoneHORA_CANCELAMENTO->Value = StrToTime(hora_cancelamento);
                                                    Data2->tbCancelamentoStoneDATA_AUTORIZACAO_VENDA->Value = StrToDate(data_autorizacao);
                                                    Data2->tbCancelamentoStoneHORA_AUTORIZACAO_VENDA->Value = StrToTime(hora_autorizacao);
                                                    Data2->tbCancelamentoStoneDATA_CAPTURA_VENDA->Value = StrToDate(data_captura);
                                                    Data2->tbCancelamentoStoneHORA_CAPTURA_VENDA->Value = StrToTime(hora_captura);
                                                    Data2->tbCancelamentoStoneTIPO->Value = 'P';

                                                    Data2->tbCancelamentoStoneTRATADO->Value = 'N';
                                                    Data2->tbCancelamentoStoneSTONECODE->Value = Data2->tbHeaderStoneSTONECODE->AsString;

                                                    Data2->tbCancelamentoStone->ApplyUpdates(0);
                                                    }
                                                }

                                            Application->ProcessMessages();
                                            }
                                        }


                                    Label30->Caption = contador2 + 1;
                                    Label6->Caption = contador2 + 1;
                                    Application->ProcessMessages();
                                    }
                                }


                            //---------------------------------------------
                            //<FinancialEvents>
                            nodeTransaction = nodes->FindNode("FinancialEvents");

                                if(nodeTransaction)
                                {
                                Label27->Caption = "Lendo Evento Financeiro";
                                Label2->Caption = "Lendo Evento Financeiro";

                                Data2->tbEventoStone->Close();
                                Data2->tbEventoStone->SQL->Clear();
                                Data2->tbEventoStone->SQL->Add("select * from edi_stone_evento_financeiro where edi_stone_evento_financeiro.CODIGO is null");
                                Data2->tbEventoStone->Open();

                                Label30->Caption = 0;
                                Label6->Caption = 0;
                                Label31->Caption = nodeTransaction->ChildNodes->Count;
                                Label7->Caption = nodeTransaction->ChildNodes->Count;

                                    for(int contador2 = 0; contador2 < nodeTransaction->ChildNodes->Count; contador2++)
                                    {
                                    Application->ProcessMessages();

                                    //<Events>
                                    nodeParcelas = nodeTransaction->ChildNodes->Get(contador2);

                                    codigo_evento = nodeParcelas->ChildNodes->FindNode("EventId")->Text;
                                    descricao_evento = nodeParcelas->ChildNodes->FindNode("Description")->Text;
                                    tipo_evento = StrToInt(nodeParcelas->ChildNodes->FindNode("Type")->Text);

                                    dado = nodeParcelas->ChildNodes->FindNode("PrevisionPaymentDate")->Text;

                                    previsao_cobranca = dado.SubString(7, 2) + "/";
                                    previsao_cobranca += dado.SubString(5, 2) + "/";
                                    previsao_cobranca += dado.SubString(0, 4);

                                    valor_evento = RetirarPontuacao(nodeParcelas->ChildNodes->FindNode("Amount")->Text);

                                    duplicidade = false;

                                        //CONTROLE DE DUPLICIDADE
                                        if(reprocessamento)
                                        {
                                        consulta = "select * from edi_stone_evento_financeiro where edi_stone_evento_financeiro.CODIGO_EVENTO = '" + codigo_evento + "'";
                                        consulta += " and edi_stone_evento_financeiro.STONECODE = '" + Data2->tbHeaderStoneSTONECODE->AsString + "'";
                                        consulta += " and edi_stone_evento_financeiro.TIPO_EVENTO = '" + IntToStr(tipo_evento) + "'";
                                        consulta += " and edi_stone_evento_financeiro.DESCRICAO_EVENTO = '" + descricao_evento + "'";
                                        consulta += " and edi_stone_evento_financeiro.COD_HEADER = '" + Data2->tbHeaderStoneCODIGO->AsString + "'";

                                        Data2->tbEventoStone->Close();
                                        Data2->tbEventoStone->SQL->Clear();
                                        Data2->tbEventoStone->SQL->Add(consulta);
                                        Data2->tbEventoStone->Open();

                                            if(Data2->tbEventoStone->RecordCount > 0)
                                            {
                                            duplicidade = true;
                                            }
                                        }

                                        if(!duplicidade)
                                        {
                                        Data2->tbEventoStone->Insert();

                                        Data2->tbEventoStoneCODIGO_EVENTO->Value = codigo_evento;
                                        Data2->tbEventoStoneCOD_HEADER->Value = codigo;
                                        Data2->tbEventoStonePREVISAO_COBRANCA->Value = StrToDate(previsao_cobranca);
                                        Data2->tbEventoStoneDESCRICAO_EVENTO->Value = descricao_evento;
                                        Data2->tbEventoStoneTIPO_EVENTO->Value = tipo_evento;
                                        Data2->tbEventoStoneVALOR_EVENTO->Value = valor_evento;

                                        Data2->tbEventoStoneTRATADO->Value = 'N';
                                        Data2->tbEventoStoneSTONECODE->Value = Data2->tbHeaderStoneSTONECODE->AsString;

                                        Data2->tbEventoStone->ApplyUpdates(0);

                                        atualiza = "update edi_stone_evento_financeiro set edi_stone_evento_financeiro.VALOR_EVENTO = ROUND(VALOR_EVENTO, 2)";
                                        atualiza += " where edi_stone_evento_financeiro.CODIGO = " + Data2->tbEventoStoneCODIGO->AsString;

                                        Data1->tbExcluir->Close();
                                        Data1->tbExcluir->SQL->Clear();
                                        Data1->tbExcluir->SQL->Add(atualiza);
                                        Data1->tbExcluir->ExecSQL();
                                        }

                                    Label30->Caption = contador2 + 1;
                                    Label6->Caption = contador2 + 1;
                                    Application->ProcessMessages();
                                    }
                                }


                            //------------------------------------------------
                            //<FinancialEventAccounts>
                            nodeTransaction = nodes->FindNode("FinancialEventAccounts");

                                if(nodeTransaction)
                                {
                                Label27->Caption = "Lendo Evento Financeiro";
                                Label2->Caption = "Lendo Evento Financeiro";

                                Data2->tbEventoStone->Close();
                                Data2->tbEventoStone->SQL->Clear();
                                Data2->tbEventoStone->SQL->Add("select * from edi_stone_evento_financeiro where edi_stone_evento_financeiro.CODIGO is null");
                                Data2->tbEventoStone->Open();

                                Label30->Caption = 0;
                                Label6->Caption = 0;
                                Label31->Caption = nodeTransaction->ChildNodes->Count;
                                Label7->Caption = nodeTransaction->ChildNodes->Count;

                                    for(int contador2 = 0; contador2 < nodeTransaction->ChildNodes->Count; contador2++)
                                    {
                                    Application->ProcessMessages();

                                    code_transferencia = 0;
                                    id_pagamento = "";

                                    //<Events>
                                    nodeParcelas = nodeTransaction->ChildNodes->Get(contador2);

                                    codigo_evento = nodeParcelas->ChildNodes->FindNode("EventId")->Text;
                                    descricao_evento = nodeParcelas->ChildNodes->FindNode("Description")->Text;
                                    tipo_evento = StrToInt(nodeParcelas->ChildNodes->FindNode("Type")->Text);

                                    dado = nodeParcelas->ChildNodes->FindNode("PaymentDate")->Text;

                                    data_autorizacao = dado.SubString(7, 2) + "/";
                                    data_autorizacao += dado.SubString(5, 2) + "/";
                                    data_autorizacao += dado.SubString(0, 4);

                                        if(nodeParcelas->ChildNodes->FindNode("LinkedMerchant"))
                                            code_transferencia = StrToInt(nodeParcelas->ChildNodes->FindNode("LinkedMerchant")->Text);

                                    valor_evento = RetirarPontuacao(nodeParcelas->ChildNodes->FindNode("Amount")->Text);

                                        if(nodeParcelas->ChildNodes->FindNode("PaymentId"))
                                            id_pagamento = nodeParcelas->ChildNodes->FindNode("PaymentId")->Text;

                                    Edit1->Text = alterarVirgulaPorPonto(valor_evento);

                                    consulta = "select * from edi_stone_evento_financeiro where edi_stone_evento_financeiro.CODIGO_EVENTO = '" + codigo_evento + "'";
                                    consulta += " and edi_stone_evento_financeiro.VALOR_EVENTO = '" + Edit1->Text + "'";

                                    Data2->tbEventoStone->Close();
                                    Data2->tbEventoStone->SQL->Clear();
                                    Data2->tbEventoStone->SQL->Add(consulta);
                                    Data2->tbEventoStone->Open();

                                        if(Data2->tbEventoStone->RecordCount == 1)
                                        {
                                        Data2->tbEventoStone->Edit();

                                        Data2->tbEventoStoneCODE_TRANSFERENCIA_INTERNA->Value = code_transferencia;
                                        Data2->tbEventoStoneDESCRICAO_EVENTO->Value = descricao_evento;
                                        Data2->tbEventoStoneDATA_COBRANCA->Value = StrToDate(data_autorizacao);
                                        Data2->tbEventoStoneID_PAGAMENTO->Value = id_pagamento;

                                        Data2->tbEventoStone->ApplyUpdates(0);
                                        }
                                        else
                                        {
                                        duplicidade = false;

                                            //CONTROLE DE DUPLICIDADE
                                            if(reprocessamento)
                                            {
                                            Edit1->Text = alterarVirgulaPorPonto(valor_evento);

                                            consulta = "select * from edi_stone_evento_financeiro where edi_stone_evento_financeiro.CODIGO_EVENTO = '" + codigo_evento + "'";
                                            consulta += " and edi_stone_evento_financeiro.STONECODE = '" + Data2->tbHeaderStoneSTONECODE->AsString + "'";
                                            consulta += " and edi_stone_evento_financeiro.TIPO_EVENTO = '" + IntToStr(tipo_evento) + "'";
                                            consulta += " and edi_stone_evento_financeiro.DESCRICAO_EVENTO = '" + descricao_evento + "'";
                                            consulta += " and edi_stone_evento_financeiro.COD_HEADER = '" + Data2->tbHeaderStoneCODIGO->AsString + "'";
                                            consulta += " and edi_stone_evento_financeiro.CODE_TRANSFERENCIA_INTERNA = '" + IntToStr(code_transferencia) + "'";
                                            consulta += " and edi_stone_evento_financeiro.VALOR_EVENTO = '" + Edit1->Text + "'";

                                            Data2->tbEventoStone->Close();
                                            Data2->tbEventoStone->SQL->Clear();
                                            Data2->tbEventoStone->SQL->Add(consulta);
                                            Data2->tbEventoStone->Open();

                                                if(Data2->tbEventoStone->RecordCount > 0)
                                                {
                                                duplicidade = true;
                                                }
                                            }

                                            if(!duplicidade)
                                            {
                                            Data2->tbEventoStone->Insert();

                                            Data2->tbEventoStoneCODE_TRANSFERENCIA_INTERNA->Value = code_transferencia;
                                            Data2->tbEventoStoneID_PAGAMENTO->Value = id_pagamento;
                                            Data2->tbEventoStoneCODIGO_EVENTO->Value = codigo_evento;
                                            Data2->tbEventoStoneCOD_HEADER->Value = codigo;
                                            Data2->tbEventoStoneDESCRICAO_EVENTO->Value = descricao_evento;
                                            Data2->tbEventoStoneTIPO_EVENTO->Value = tipo_evento;
                                            Data2->tbEventoStoneVALOR_EVENTO->Value = valor_evento;
                                            Data2->tbEventoStoneDATA_COBRANCA->Value = StrToDate(data_autorizacao);

                                            Data2->tbEventoStoneTRATADO->Value = 'N';
                                            Data2->tbEventoStoneSTONECODE->Value = Data2->tbHeaderStoneSTONECODE->AsString;

                                            Data2->tbEventoStone->ApplyUpdates(0);

                                            atualiza = "update edi_stone_evento_financeiro set edi_stone_evento_financeiro.VALOR_EVENTO = ROUND(VALOR_EVENTO, 2)";
                                            atualiza += " where edi_stone_evento_financeiro.CODIGO = " + Data2->tbEventoStoneCODIGO->AsString;

                                            Data1->tbExcluir->Close();
                                            Data1->tbExcluir->SQL->Clear();
                                            Data1->tbExcluir->SQL->Add(atualiza);
                                            Data1->tbExcluir->ExecSQL();
                                            }
                                        }


                                        if(valor_evento > 0 && tipo_evento == 14)
                                        {
                                        //VERIFICA SE EXISTE UM EVENTO NEGATIVO E ALTERA TODOS ID PAGAMENTOS DO RECEBIMENTO
                                        consulta = "select * from edi_stone_evento_financeiro where edi_stone_evento_financeiro.CODIGO_EVENTO = '" + codigo_evento + "'";
                                        consulta += " and edi_stone_evento_financeiro.VALOR_EVENTO < 0";

                                        Data2->tbEventoStone->Close();
                                        Data2->tbEventoStone->SQL->Clear();
                                        Data2->tbEventoStone->SQL->Add(consulta);
                                        Data2->tbEventoStone->Open();

                                            if(Data2->tbEventoStone->RecordCount == 1)
                                            {
                                            consulta = "select * from edi_stone_comprovante_pagamento where edi_stone_comprovante_pagamento.CODIGO is not null";
                                            consulta += " and edi_stone_comprovante_pagamento.ID_PAGAMENTO = '" + Data2->tbEventoStoneID_PAGAMENTO->AsString + "'";

                                            Data2->tbPagamentoStone->Close();
                                            Data2->tbPagamentoStone->SQL->Clear();
                                            Data2->tbPagamentoStone->SQL->Add(consulta);
                                            Data2->tbPagamentoStone->Open();

                                                if(Data2->tbPagamentoStone->RecordCount >= 1)
                                                {
                                                Data2->tbPagamentoStone->Last();
                                                int final3 = Data2->tbPagamentoStone->RecordCount;
                                                Data2->tbPagamentoStone->First();

                                                    for(int contador3 = 0; contador3 < final3; contador3++)
                                                    {
                                                    Application->ProcessMessages();

                                                    Data2->tbPagamentoStone->Edit();

                                                    Data2->tbPagamentoStoneAGENCIA->Value = agencia;
                                                    Data2->tbPagamentoStoneARRANJO_PAGAMENTO->Value = arranjo_pagamento;
                                                    Data2->tbPagamentoStoneBANCO->Value = banco;
                                                    Data2->tbPagamentoStoneNUM_CONTA->Value = num_conta;
                                                    Data2->tbPagamentoStoneID_PAGAMENTO->Value = id_pagamento;

                                                    Data2->tbPagamentoStone->ApplyUpdates(0);

                                                    Data2->tbPagamentoStone->Next();
                                                    Application->ProcessMessages();
                                                    }
                                                }

                                            Data2->tbEventoStone->Edit();
                                            Data2->tbEventoStoneID_PAGAMENTO->Value = id_pagamento;
                                            Data2->tbEventoStone->ApplyUpdates(0);
                                            }
                                        }

                                    Label30->Caption = contador2 + 1;
                                    Label6->Caption = contador2 + 1;
                                    Application->ProcessMessages();
                                    }
                                }



                            //-----------------------------------------------------------
                            //Payments
                            nodeTransaction = nodes->FindNode("Payments");

                                if(nodeTransaction)
                                {
                                Label27->Caption = "Lendo dados bancários de pagamento";
                                Label2->Caption = "Lendo dados bancários de pagamento";

                                Data2->tbPagamentoStone->Close();
                                Data2->tbPagamentoStone->SQL->Clear();
                                Data2->tbPagamentoStone->SQL->Add("select * from edi_stone_comprovante_pagamento where edi_stone_comprovante_pagamento.CODIGO is null");
                                Data2->tbPagamentoStone->Open();

                                Label30->Caption = 0;
                                Label6->Caption = 0;
                                Label31->Caption = nodeTransaction->ChildNodes->Count;
                                Label7->Caption = nodeTransaction->ChildNodes->Count;

                                    for(int contador2 = 0; contador2 < nodeTransaction->ChildNodes->Count; contador2++)
                                    {
                                    Application->ProcessMessages();

                                    nodeParcela = nodeTransaction->ChildNodes->Get(contador2);
                                    id_pagamento = "";

                                        if(nodeParcela->ChildNodes->FindNode("Id"))
                                        {
                                        id_pagamento = nodeParcela->ChildNodes->FindNode("Id")->Text;
                                        }

                                    arranjo_pagamento = StrToInt(nodeParcela->ChildNodes->FindNode("WalletTypeId")->Text);

                                    //<FavoredBankAccount>
                                    nodeAuxiliar = nodeParcela->ChildNodes->FindNode("FavoredBankAccount");

                                    banco = StrToInt(nodeAuxiliar->ChildNodes->FindNode("BankCode")->Text);
                                    agencia = nodeAuxiliar->ChildNodes->FindNode("BankBranch")->Text;
                                    num_conta = nodeAuxiliar->ChildNodes->FindNode("BankAccountNumber")->Text;
                                    //------------------------------

                                    cadastrado = false;

                                        if(id_pagamento != "")
                                        {
                                        consulta = "select * from edi_stone_comprovante_pagamento where edi_stone_comprovante_pagamento.CODIGO is not null";
                                        consulta += " and edi_stone_comprovante_pagamento.ID_PAGAMENTO = " + id_pagamento;

                                        Data2->tbPagamentoStone->Close();
                                        Data2->tbPagamentoStone->SQL->Clear();
                                        Data2->tbPagamentoStone->SQL->Add(consulta);
                                        Data2->tbPagamentoStone->Open();

                                            if(Data2->tbPagamentoStone->RecordCount >= 1)
                                            {
                                            Data2->tbPagamentoStone->Last();
                                            int final3 = Data2->tbPagamentoStone->RecordCount;
                                            Data2->tbPagamentoStone->First();

                                                for(int contador3 = 0; contador3 < final3; contador3++)
                                                {
                                                Application->ProcessMessages();

                                                Data2->tbPagamentoStone->Edit();

                                                Data2->tbPagamentoStoneAGENCIA->Value = agencia;
                                                Data2->tbPagamentoStoneARRANJO_PAGAMENTO->Value = arranjo_pagamento;
                                                Data2->tbPagamentoStoneBANCO->Value = banco;
                                                Data2->tbPagamentoStoneNUM_CONTA->Value = num_conta;

                                                Data2->tbPagamentoStone->ApplyUpdates(0);

                                                Data2->tbPagamentoStone->Next();
                                                Application->ProcessMessages();
                                                }
                                            }


                                        consulta = "select * from edi_stone_evento_financeiro where edi_stone_evento_financeiro.CODIGO is not null";
                                        consulta += " and edi_stone_evento_financeiro.ID_PAGAMENTO = " + id_pagamento;

                                        Data2->tbEventoStone->Close();
                                        Data2->tbEventoStone->SQL->Clear();
                                        Data2->tbEventoStone->SQL->Add(consulta);
                                        Data2->tbEventoStone->Open();

                                            if(Data2->tbEventoStone->RecordCount >= 1)
                                            {
                                            Data2->tbEventoStone->Last();
                                            int final3 = Data2->tbEventoStone->RecordCount;
                                            Data2->tbEventoStone->First();

                                                for(int contador3 = 0; contador3 < final3; contador3++)
                                                {
                                                Application->ProcessMessages();

                                                Data2->tbEventoStone->Edit();

                                                Data2->tbEventoStoneAGENCIA->Value = agencia;
                                                Data2->tbEventoStoneARRANJO_PAGAMENTO->Value = arranjo_pagamento;
                                                Data2->tbEventoStoneBANCO->Value = banco;
                                                Data2->tbEventoStoneNUM_CONTA->Value = num_conta;

                                                Data2->tbEventoStone->ApplyUpdates(0);

                                                Data2->tbEventoStone->Next();
                                                Application->ProcessMessages();
                                                }
                                            }
                                        }

                                    Label30->Caption = contador2 + 1;
                                    Label6->Caption = contador2 + 1;
                                    Application->ProcessMessages();
                                    }
                                }
                            }

                            if(Data1->tbControleArquivos->Active)
                            {
                            Data1->tbControleArquivos->EmptyDataSet();
                            }

                        consulta = "Select * from controle_arquivos_processados where controle_arquivos_processados.NOME_ARQUIVO = '" + Memo3->Text + "'";
                        consulta += " and controle_arquivos_processados.COD_ADIQUIRENTE = 7";
                        consulta += " and controle_arquivos_processados.CNPJ_CLIENTE = '" + Data2->tbCredenciadosStoneCNPJ_ESTABELECIMENTO->AsString + "'";

                        Data1->tbControleArquivos->Close();
                        Data1->tbControleArquivos->SQL->Clear();
                        Data1->tbControleArquivos->SQL->Add(consulta);
                        Data1->tbControleArquivos->Open();

                            if(Data1->tbControleArquivos->RecordCount == 0)
                            {
                            //GRAVA AQUI O NOME DO ARQUIVO
                            Edit1->Text = Memo3->Text;

                                if(Edit1->Text != "." && Edit1->Text != "..")
                                {
                                Data1->tbControleArquivos->Insert();

                                Data1->tbControleArquivosCNPJ_CLIENTE->Value = Data2->tbCredenciadosStoneCNPJ_ESTABELECIMENTO->AsString;

                                Data1->tbControleArquivosCOD_ADIQUIRENTE->Value = 7;

                                Data1->tbControleArquivosDATA_PROCESSAMENTO->Value = Date();
                                Data1->tbControleArquivosHORA_PROCESSAMENTO->Value = Time();

                                Data1->tbControleArquivosLOCALIZACAO->Value = Edit1->Text;

                                Data1->tbControleArquivosDATA_ARQUIVO->Value = FileDateToDateTime(FileAge(XMLDocument1->FileName));

                                Data1->tbControleArquivosNOME_ARQUIVO->Value = XMLDocument1->FileName;

                                Data1->tbControleArquivos->ApplyUpdates(0);
                                }
                            }
                        }
                    }

                continuar:

                Data2->tbCredenciadosStone->Next();

                ProgressBar3->Position = contador + 1;
                Label23->Caption = contador + 1;
                Application->ProcessMessages();
                }

                if(cod_cliente > 0)
                {
                DataProcessamento->tbClienteOperadora->Next();
                contador_clientes++;
                }
            }
            while(contador_clientes < final_clientes);

        Application->ProcessMessages();
        ProgressBar2->Position = contador_dias + 1;
        }

//    json->Free();
//    jsonOperations->Free();
    }
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::Button6Click(TObject *Sender)
{
	try
    {
    SetProcessWorkingSetSize(GetCurrentProcess(), -1, -1);
    Application->ProcessMessages();
	}
	catch(...){}
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::Button2Click(TObject *Sender)
{
	if(DateTimePicker4->Date < DateTimePicker3->Date)
    {
    Application->MessageBoxA(L"A Data Final deve ser maior ou igual a data inicial !", L"Mensagem do Sistema", MB_OK);
    }
    else
    {
    int dias = DaysBetween(DateTimePicker3->Date, DateTimePicker4->Date) + 1;
    int erro = 0, pagina;
    bool continuar = false, proxima_pagina;
    TJSONObject *json, *detalhe, *item;
    Word Year, Month, Day;
    TDateTime dtPresent;
    int pageSize = 500;

    AnsiString auxiliar, consulta, retorno, dados;
    AnsiString data, url;
    AnsiString id;

    Label52->Caption = "0";
    Label53->Caption = "0";
    Label6->Caption = 0;
    Label7->Caption = 0;
    Label49->Caption = "";
    Label41->Caption = erro;

    Data3->tbSeguroVenda->Close();
    Data3->tbSeguroVenda->SQL->Clear();
    Data3->tbSeguroVenda->SQL->Add("select * from edi_pagseguro_venda where edi_pagseguro_venda.CODIGO is null");
    Data3->tbSeguroVenda->Open();

    Data3->tbSeguroPagamento->Close();
    Data3->tbSeguroPagamento->SQL->Clear();
    Data3->tbSeguroPagamento->SQL->Add("select * from edi_pagseguro_pagamento where edi_pagseguro_pagamento.CODIGO is null");
    Data3->tbSeguroPagamento->Open();

    Data3->tbSeguroAntecipacao->Close();
    Data3->tbSeguroAntecipacao->SQL->Clear();
    Data3->tbSeguroAntecipacao->SQL->Add("select * from edi_pagseguro_antecipacao where edi_pagseguro_antecipacao.CODIGO is null");
    Data3->tbSeguroAntecipacao->Open();

    	if(DBLookupComboBox2->KeyValue > 0)
        {
        Edit1->Text = DBLookupComboBox2->KeyValue;

        consulta = "Select * from cliente_operadora where cliente_operadora.COD_ADQUIRENTE = '108' and cliente_operadora.INTEGRA_API_PAGSEGURO = 'S'";
        consulta  += " and cliente_operadora.COD_CLIENTE = " + Edit1->Text;
        }
        else
        {
        consulta = "Select * from cliente_operadora where cliente_operadora.COD_ADQUIRENTE = '108' and cliente_operadora.INTEGRA_API_PAGSEGURO = 'S'";
        }

    //SELECIONA OS ESTABELECIMENTOS
    Data3->tbSeguroCadastro->Close();
    Data3->tbSeguroCadastro->SQL->Clear();
    Data3->tbSeguroCadastro->SQL->Add(consulta);
    Data3->tbSeguroCadastro->Open();

    Data3->tbSeguroCadastro->Last();
    int total_cadastros = Data3->tbSeguroCadastro->RecordCount;
    Data3->tbSeguroCadastro->First();

    ProgressBar4->Position = 0;
    ProgressBar4->Max = dias;
    ProgressBar5->Position = 0;
    ProgressBar5->Max = total_cadastros;

    Label46->Caption = 0;
    Label47->Caption = total_cadastros;

    Application->ProcessMessages();

        for(int contador_dias = 0; contador_dias < dias; contador_dias++)
        {
        Button6Click(Sender);

        Label39->Caption = DateOf(DateTimePicker3->Date + contador_dias);

        Data3->tbSeguroCadastro->First();
        ProgressBar5->Position = 0;

        Application->ProcessMessages();

            for(int contador_cadastros = 0; contador_cadastros < total_cadastros; contador_cadastros++)
            {
            id = Data3->tbSeguroCadastroCODIGO_ESTABELECIMENTO->AsString;

            continuar = true;
            Label45->Caption = id;
            Label46->Caption = contador_cadastros + 1;

            Application->ProcessMessages();

            IdHTTP2->Request->CustomHeaders->Clear();
            IdHTTP2->Request->BasicAuthentication = false;

            pagina = 1;

            //VERIFICA SE TEM AUTORIZAÇÃO PARA CONSULTAR OS DADOS
            url = "https://edi.api.pagseguro.com.br/edi/v1/users/" + id + "/token/a17402004b19419180586e2fd99a310f";

            	try
                {
                Memo3->Text = IdHTTP2->Get(url);
                }
                catch (EIdHTTPProtocolException &E)
                {
                    try
                    {
                    Memo3->Text = IdHTTP2->Get(url);
                    }
                    catch (EIdHTTPProtocolException &E)
                    {
                    erro++;
                    Label41->Caption = erro;
                    continuar = false;

                    consulta = "- Não foi possível verificar os dados de autorização do estabelecimento " + id;
                    Memo4->Lines->Add(consulta);
                    }
                }

               	if(continuar)
                {
                    if(IdHTTP2->ResponseCode == 200)
                    {
                    json = (TJSONObject*) TJSONObject::ParseJSONValue(TEncoding::ASCII->GetBytes(Memo3->Lines->Text),0);

                    retorno = json->GetValue("code")->ToString();

                    	if(retorno == "200")
                        {
                        IdHTTP2->Request->Clear();
                        IdHTTP2->Request->BasicAuthentication = true;

                            if(autentificado)
                            {
                            IdHTTP2->Request->Authentication->Username = id;
                            IdHTTP2->Request->Authentication->Password = "a17402004b19419180586e2fd99a310f";
                            }
                            else
                            {
                            IdHTTP2->Request->Username = id;
                            IdHTTP2->Request->Password = "a17402004b19419180586e2fd99a310f";

                            autentificado = true;
                            }

                        dtPresent = DateTimePicker3->Date + contador_dias;
                        DecodeDate(dtPresent, Year, Month, Day);

                        Edit1->Text = Year;
                        data = Edit1->Text + "-";
                        Edit1->Text = Month;

                        	if(Edit1->Text.Length() == 1)
                            {
                            auxiliar = Month;
                            Edit1->Text = "0" + auxiliar;
                            }

                        data += Edit1->Text + "-";
                        Edit1->Text = Day;

                            if(Edit1->Text.Length() == 1)
                            {
                            auxiliar = Day;
                            Edit1->Text = "0" + auxiliar;
                            }

                        data += Edit1->Text;

                            do
                            {
                            proxima_pagina = false;
                            continuar = true;

                            Label59->Caption = pagina;

                            //ARQUIVOS DE Tipo de movimento 1- Transacional
                            url = "https://edi.api.pagseguro.com.br/edi/v1/2.00/movimentos?dataMovimento=" + data + "&pageNumber=" + pagina +"&pageSize=" + pageSize + "&tipoMovimento=1";

                                try
                                {
                                Memo3->Text = IdHTTP2->Get(url);
                                }
                                catch (EIdHTTPProtocolException &E)
                                {
                                    try
                                    {
                                    Memo3->Text = IdHTTP2->Get(url);
                                    Memo3->Text = IdHTTP2->Get(url);
                                    }
                                    catch (EIdHTTPProtocolException &E)
                                    {
                                    erro++;
                                    Label41->Caption = erro;
                                    continuar = false;

                                    consulta = "- Não foi possível verificar vendas do estabelecimento " + id + " na data: " + data;
                    				Memo4->Lines->Add(consulta);
                                    }
                                }

                                //INÍCIO DO PROCESSO DE VENDAS
                                if(continuar)
                                {
                                    if(IdHTTP2->ResponseCode == 200)
                                    {
                                    json = (TJSONObject*) TJSONObject::ParseJSONValue(TEncoding::ASCII->GetBytes(Memo3->Lines->Text),0);

                                    detalhe = (TJSONObject*) json->GetValue("pagination");
                                    Label61->Caption = detalhe->GetValue("totalPages")->Value();

                                    detalhe = (TJSONObject*) json->GetValue("detalhes");

                                    Label52->Caption = 0;
                                    Label53->Caption = detalhe->Count;
                                    Label49->Caption = "Leitura de Vendas";

                                    Label6->Caption = 0;
                                    Label7->Caption = detalhe->Count;
                                    Label2->Caption = "Leitura de Vendas";

                                    Application->ProcessMessages();

                                        for(int cont_detalhe = 0; cont_detalhe < detalhe->Count; cont_detalhe++)
                                        {
                                        item = (TJSONObject*) detalhe->Get(cont_detalhe);

                                            if(item->GetValue("movimento_api_codigo")->Value() != "" && item->GetValue("estabelecimento")->Value() != ""
                                                && item->GetValue("codigo_autorizacao")->Value() != "" && item->GetValue("nsu")->Value() != "")
                                            {
                                            consulta = "select * from edi_pagseguro_venda where MOVIMENTO_API_CODIGO = '" + item->GetValue("movimento_api_codigo")->Value() + "'";

                                                if(DataVerificacao2->tbSeguroVenda->Active)
                                                {
                                                DataVerificacao2->tbSeguroVenda->EmptyDataSet();
                                                }

                                            DataVerificacao2->tbSeguroVenda->Close();
                                            DataVerificacao2->tbSeguroVenda->SQL->Clear();
                                            DataVerificacao2->tbSeguroVenda->SQL->Add(consulta);
                                            DataVerificacao2->tbSeguroVenda->Open();

                                                if(DataVerificacao2->tbSeguroVenda->RecordCount == 0)
                                                {
                                                Data3->tbSeguroVenda->Insert();

                                                Data3->tbSeguroVendaDATA_LEITURA->Value = Date();
                                                Data3->tbSeguroVendaHORA_LEITURA->Value = Time();
                                                Data3->tbSeguroVendaTRATADO->Value = 'N';
                                                Data3->tbSeguroVendaCOD_CLIENTE->Value = Data3->tbSeguroCadastroCOD_CLIENTE->AsInteger;

                                                Data3->tbSeguroVendaCANAL_ENTRADA->Value = item->GetValue("canal_entrada")->Value();;
                                                Data3->tbSeguroVendaCARTAO_BIN->Value = item->GetValue("cartao_bin")->Value();
                                                Data3->tbSeguroVendaCARTAO_HOLDER->Value = item->GetValue("cartao_holder")->Value();
                                                Data3->tbSeguroVendaCODIGO_AUTORIZACAO->Value = item->GetValue("codigo_autorizacao")->Value();
                                                Data3->tbSeguroVendaCODIGO_CV->Value = item->GetValue("codigo_cv")->Value();
                                                Data3->tbSeguroVendaCODIGO_TRANSACAO->Value = item->GetValue("codigo_transacao")->Value();
                                                Data3->tbSeguroVendaCODIGO_VENDA->Value = item->GetValue("codigo_venda")->Value();
                                                Data3->tbSeguroVendaESTABELECIMENTO->Value = item->GetValue("estabelecimento")->Value();
                                                Data3->tbSeguroVendaINSTITUICAO_FINANCEIRA->Value = item->GetValue("instituicao_financeira")->Value();
                                                Data3->tbSeguroVendaLEITOR->Value = item->GetValue("leitor")->Value();
                                                Data3->tbSeguroVendaMEIO_CAPTURA->Value = StrToInt(Trim(item->GetValue("meio_captura")->Value()));
                                                Data3->tbSeguroVendaMEIO_PAGAMENTO->Value = StrToInt(Trim(item->GetValue("meio_pagamento")->Value()));
                                                Data3->tbSeguroVendaMOVIMENTO_API_CODIGO->Value = item->GetValue("movimento_api_codigo")->Value();
                                                Data3->tbSeguroVendaNSU->Value = item->GetValue("nsu")->Value();
                                                Data3->tbSeguroVendaNUMERO_SERIE_LEITOR->Value = item->GetValue("numero_serie_leitor")->Value();
                                                Data3->tbSeguroVendaNUM_LOGICO->Value = item->GetValue("num_logico")->Value();
                                                Data3->tbSeguroVendaPAGAMENTO_PRAZO->Value = item->GetValue("pagamento_prazo")->Value();
                                                Data3->tbSeguroVendaPARCELA->Value = StrToInt(Trim(item->GetValue("parcela")->Value()));
                                                Data3->tbSeguroVendaPLANO->Value = StrToInt(Trim(item->GetValue("plano")->Value()));
                                                Data3->tbSeguroVendaQUANTIDADE_PARCELA->Value = StrToInt(Trim(item->GetValue("quantidade_parcela")->Value()));
                                                Data3->tbSeguroVendaSTATUS_PAGAMENTO->Value = StrToInt(Trim(item->GetValue("status_pagamento")->Value()));
                                                Data3->tbSeguroVendaTIPO_EVENTO->Value = StrToInt(Trim(item->GetValue("tipo_evento")->Value()));
                                                Data3->tbSeguroVendaTIPO_REGISTRO->Value = StrToInt(Trim(item->GetValue("tipo_registro")->Value()));
                                                Data3->tbSeguroVendaTIPO_TRANSACAO->Value = StrToInt(Trim(item->GetValue("tipo_transacao")->Value()));
                                                Data3->tbSeguroVendaVALOR_LIQUIDO_TRANSACAO->Value = StrToFloat(Trim(item->GetValue("valor_liquido_transacao")->Value()));
                                                Data3->tbSeguroVendaVALOR_ORIGINAL_TRANSACAO->Value = StrToFloat(Trim(item->GetValue("valor_original_transacao")->Value()));
                                                Data3->tbSeguroVendaVALOR_PARCELA->Value = StrToFloat(Trim(item->GetValue("valor_parcela")->Value()));
                                                Data3->tbSeguroVendaVALOR_TOTAL_TRANSACAO->Value = StrToFloat(Trim(item->GetValue("valor_total_transacao")->Value()));

                                                    if(item->GetValue("tarifa_boleto_compra")->Value() != "null")
                                                        Data3->tbSeguroVendaTARIFA_BOLETO_COMPRA->Value = StrToFloat(Trim(item->GetValue("tarifa_boleto_compra")->Value()));

                                                    if(item->GetValue("tarifa_boleto_vendedor")->Value() != "null")
                                                        Data3->tbSeguroVendaTARIFA_BOLETO_VENDEDOR->Value = StrToFloat(Trim(item->GetValue("tarifa_boleto_vendedor")->Value()));

                                                    if(item->GetValue("tarifa_intermediacao")->Value() != "null")
                                                        Data3->tbSeguroVendaTARIFA_INTERMEDIACAO->Value = StrToFloat(Trim(item->GetValue("tarifa_intermediacao")->Value()));

                                                    if(item->GetValue("taxa_intermediacao")->Value() != "null")
                                                        Data3->tbSeguroVendaTAXA_INTERMEDIACAO->Value = StrToFloat(Trim(item->GetValue("taxa_intermediacao")->Value()));

                                                    if(item->GetValue("taxa_parcela_comprador")->Value() != "null")
                                                        Data3->tbSeguroVendaTAXA_PARCELA_COMPRADOR->Value = StrToFloat(Trim(item->GetValue("taxa_parcela_comprador")->Value()));

                                                    if(item->GetValue("taxa_parcela_vendedor")->Value() != "null")
                                                         Data3->tbSeguroVendaTAXA_PARCELA_VENDEDOR->Value = StrToFloat(Trim(item->GetValue("taxa_parcela_vendedor")->Value()));

                                                    if(item->GetValue("taxa_rep_aplicacao")->Value() != "null")
                                                        Data3->tbSeguroVendaTAXA_REP_APLICACAO->Value = StrToFloat(Trim(item->GetValue("taxa_rep_aplicacao")->Value()));

                                                dados = item->GetValue("data_inicial_transacao")->Value();

                                                    if(dados != "")
                                                    {
                                                    auxiliar = dados.SubString(9, 2) + "/";
                                                    auxiliar += dados.SubString(6, 2) + "/";
                                                    auxiliar += dados.SubString(0, 4);

                                                    Data3->tbSeguroVendaDATA_INICIAL_TRANSACAO->Value = StrToDate(auxiliar);
                                                    }

                                                dados = item->GetValue("data_prevista_pagamento")->Value();

                                                    if(dados != "")
                                                    {
                                                    auxiliar = dados.SubString(9, 2) + "/";
                                                    auxiliar += dados.SubString(6, 2) + "/";
                                                    auxiliar += dados.SubString(0, 4);

                                                    Data3->tbSeguroVendaDATA_PREVISTA_PAGAMENTO->Value = StrToDate(auxiliar);
                                                    }

                                                dados = item->GetValue("data_venda_ajuste")->Value();

                                                    if(dados != "")
                                                    {
                                                    auxiliar = dados.SubString(9, 2) + "/";
                                                    auxiliar += dados.SubString(6, 2) + "/";
                                                    auxiliar += dados.SubString(0, 4);

                                                    Data3->tbSeguroVendaDATA_VENDA_AJUSTE->Value = StrToDate(auxiliar);
                                                    }

                                                Data3->tbSeguroVendaHORA_VENDA_AJUSTE->Value = StrToTime(item->GetValue("hora_venda_ajuste")->Value());
                                                Data3->tbSeguroVenda->ApplyUpdates(0);
                                                }
                                            }

                                        Label52->Caption = cont_detalhe + 1;
                                        Label6->Caption = cont_detalhe + 1;
                                        Application->ProcessMessages();
                                        }


                                        if(detalhe->Count == pageSize)
                                        {
                                        pagina++;

                                        Label59->Caption = pagina;
                                        Application->ProcessMessages();

                                        proxima_pagina = true;
                                        }

                                    json->Free();
                                	}
                                    else
                                    {
                                    erro++;
                                    Label41->Caption = erro;
                                    }
                                }
                            }
                            while(proxima_pagina);


                        pagina = 1;

                            do
                            {
                            proxima_pagina = false;
                            continuar = true;

                            Label59->Caption = pagina;

                            //ARQUIVOS DE Tipo de movimento 2 - Financeiro
                            url = "https://edi.api.pagseguro.com.br/edi/v1/2.00/movimentos?dataMovimento=" + data + "&pageNumber=" + pagina + "&pageSize=" + pageSize + "&tipoMovimento=2";

                                try
                                {
                                Memo3->Text = IdHTTP2->Get(url);
                                }
                                catch (EIdHTTPProtocolException &E)
                                {
                                    try
                                    {
                                    Memo3->Text = IdHTTP2->Get(url);
                                    Memo3->Text = IdHTTP2->Get(url);
                                    }
                                    catch (EIdHTTPProtocolException &E)
                                    {
                                    erro++;
                                    Label41->Caption = erro;
                                    continuar = false;

                                    consulta = "- Não foi possível verificar pagamentos do estabelecimento " + id + " na data: " + data;
                    				Memo4->Lines->Add(consulta);
                                    }
                                }

                                //INÍCIO DO PROCESSO DE VENDAS
                                if(continuar)
                                {
                                    if(IdHTTP2->ResponseCode == 200)
                                    {
                                    json = (TJSONObject*) TJSONObject::ParseJSONValue(TEncoding::ASCII->GetBytes(Memo3->Lines->Text),0);

                                    detalhe = (TJSONObject*) json->GetValue("pagination");
                                    Label61->Caption = detalhe->GetValue("totalPages")->Value();

                                    detalhe = (TJSONObject*) json->GetValue("detalhes");

                                    Label52->Caption = 0;
                                    Label53->Caption = detalhe->Count;
                                    Label49->Caption = "Leitura de Pagamentos";

                                    Label6->Caption = 0;
                                    Label7->Caption = detalhe->Count;
                                    Label2->Caption = "Leitura de Pagamentos";

                                    Application->ProcessMessages();

                                        for(int cont_detalhe = 0; cont_detalhe < detalhe->Count; cont_detalhe++)
                                        {
                                        item = (TJSONObject*) detalhe->Get(cont_detalhe);

                                            if(item->GetValue("movimento_api_codigo")->Value() != "" && item->GetValue("estabelecimento")->Value() != ""
                                                && item->GetValue("codigo_autorizacao")->Value() != "" && item->GetValue("nsu")->Value() != "")
                                            {
                                            consulta = "select * from edi_pagseguro_pagamento where MOVIMENTO_API_CODIGO = '" + item->GetValue("movimento_api_codigo")->Value() + "'";

                                                if(DataVerificacao2->tbSeguroPagamento->Active)
                                                {
                                                DataVerificacao2->tbSeguroPagamento->EmptyDataSet();
                                                }

                                            DataVerificacao2->tbSeguroPagamento->Close();
                                            DataVerificacao2->tbSeguroPagamento->SQL->Clear();
                                            DataVerificacao2->tbSeguroPagamento->SQL->Add(consulta);
                                            DataVerificacao2->tbSeguroPagamento->Open();

                                                if(DataVerificacao2->tbSeguroPagamento->RecordCount == 0)
                                                {
                                                Data3->tbSeguroPagamento->Insert();

                                                Data3->tbSeguroPagamentoDATA_LEITURA->Value = Date();
                                                Data3->tbSeguroPagamentoHORA_LEITURA->Value = Time();
                                                Data3->tbSeguroPagamentoTRATADO->Value = 'N';
                                                Data3->tbSeguroPagamentoCOD_CLIENTE->Value = Data3->tbSeguroCadastroCOD_CLIENTE->AsInteger;

                                                Data3->tbSeguroPagamentoBANCO_AGENCIA->Value = item->GetValue("banco_agencia")->Value();
                                                Data3->tbSeguroPagamentoCANAL_ENTRADA->Value = item->GetValue("canal_entrada")->Value();;
                                                Data3->tbSeguroPagamentoCARTAO_BIN->Value = item->GetValue("cartao_bin")->Value();
                                                Data3->tbSeguroPagamentoCARTAO_HOLDER->Value = item->GetValue("cartao_holder")->Value();
                                                Data3->tbSeguroPagamentoCODIGO_AUTORIZACAO->Value = item->GetValue("codigo_autorizacao")->Value();
                                                Data3->tbSeguroPagamentoCODIGO_CV->Value = item->GetValue("codigo_cv")->Value();
                                                Data3->tbSeguroPagamentoCODIGO_TRANSACAO->Value = item->GetValue("codigo_transacao")->Value();
                                                Data3->tbSeguroPagamentoCODIGO_VENDA->Value = item->GetValue("codigo_venda")->Value();
                                                Data3->tbSeguroPagamentoCONTA_BANCO->Value = item->GetValue("conta_banco")->Value();
                                                Data3->tbSeguroPagamentoESTABELECIMENTO->Value = item->GetValue("estabelecimento")->Value();

                                                Data3->tbSeguroPagamentoINSTITUICAO_FINANCEIRA->Value = item->GetValue("instituicao_financeira")->Value();
                                                Data3->tbSeguroPagamentoLEITOR->Value = item->GetValue("leitor")->Value();
                                                Data3->tbSeguroPagamentoMEIO_CAPTURA->Value = StrToInt(Trim(item->GetValue("meio_captura")->Value()));
                                                Data3->tbSeguroPagamentoMEIO_PAGAMENTO->Value = StrToInt(Trim(item->GetValue("meio_pagamento")->Value()));
                                                Data3->tbSeguroPagamentoMOVIMENTO_API_CODIGO->Value = item->GetValue("movimento_api_codigo")->Value();
                                                Data3->tbSeguroPagamentoNSU->Value = item->GetValue("nsu")->Value();
                                                Data3->tbSeguroPagamentoNUM_LOGICO->Value = item->GetValue("num_logico")->Value();
                                                Data3->tbSeguroPagamentoPAGAMENTO_PRAZO->Value = item->GetValue("pagamento_prazo")->Value();
                                                Data3->tbSeguroPagamentoPARCELA->Value = StrToInt(Trim(item->GetValue("parcela")->Value()));
                                                Data3->tbSeguroPagamentoPLANO->Value = StrToInt(Trim(item->GetValue("plano")->Value()));
                                                Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->Value = StrToInt(Trim(item->GetValue("quantidade_parcela")->Value()));
                                                Data3->tbSeguroPagamentoSTATUS_PAGAMENTO->Value = StrToInt(Trim(item->GetValue("status_pagamento")->Value()));
                                                Data3->tbSeguroPagamentoTIPO_EVENTO->Value = StrToInt(Trim(item->GetValue("tipo_evento")->Value()));
                                                Data3->tbSeguroPagamentoTIPO_TRANSACAO->Value = StrToInt(Trim(item->GetValue("tipo_transacao")->Value()));
                                                Data3->tbSeguroPagamentoVALOR_LIQUIDO_ANTECIPACAO->Value = StrToFloat(Trim(item->GetValue("valor_liquido_antecipacao")->Value()));
                                                Data3->tbSeguroPagamentoVALOR_LIQUIDO_TRANSACAO->Value = StrToFloat(Trim(item->GetValue("valor_liquido_transacao")->Value()));
                                                Data3->tbSeguroPagamentoVALOR_ORIGINAL_TRANSACAO->Value = StrToFloat(Trim(item->GetValue("valor_original_transacao")->Value()));
                                                Data3->tbSeguroPagamentoVALOR_PARCELA->Value = StrToFloat(Trim(item->GetValue("valor_parcela")->Value()));
                                                Data3->tbSeguroPagamentoVALOR_TOTAL_TRANSACAO->Value = StrToFloat(Trim(item->GetValue("valor_total_transacao")->Value()));
                                                Data3->tbSeguroPagamentoTAXA_ANTECIPACAO->Value = StrToFloat(Trim(item->GetValue("taxa_antecipacao")->Value()));

                                                    if(item->GetValue("cod_banco")->Value() != "")
                                                    	Data3->tbSeguroPagamentoCOD_BANCO->Value = StrToInt(Trim(item->GetValue("cod_banco")->Value()));

                                                    if(item->GetValue("tipo_registro")->Value() != "null" && item->GetValue("tipo_registro")->Value() != "")
                                                    	Data3->tbSeguroPagamentoTIPO_REGISTRO->Value = StrToInt(Trim(item->GetValue("tipo_registro")->Value()));

                                                    if(item->GetValue("identificador_revenda")->Value() != "" && item->GetValue("identificador_revenda")->Value() != "null")
                                                    	Data3->tbSeguroPagamentoIDENTIFICADOR_REVENDA->Value = StrToFloat(Trim(item->GetValue("identificador_revenda")->Value()));

                                                    if(item->GetValue("tarifa_boleto_compra")->Value() != "null")
                                                        Data3->tbSeguroPagamentoTARIFA_BOLETO_COMPRA->Value = StrToFloat(Trim(item->GetValue("tarifa_boleto_compra")->Value()));

                                                    if(item->GetValue("tarifa_boleto_vendedor")->Value() != "null")
                                                        Data3->tbSeguroPagamentoTARIFA_BOLETO_VENDEDOR->Value = StrToFloat(Trim(item->GetValue("tarifa_boleto_vendedor")->Value()));

                                                    if(item->GetValue("tarifa_intermediacao")->Value() != "null")
                                                        Data3->tbSeguroPagamentoTARIFA_INTERMEDIACAO->Value = StrToFloat(Trim(item->GetValue("tarifa_intermediacao")->Value()));

                                                    if(item->GetValue("taxa_intermediacao")->Value() != "null")
                                                        Data3->tbSeguroPagamentoTAXA_INTERMEDIACAO->Value = StrToFloat(Trim(item->GetValue("taxa_intermediacao")->Value()));

                                                    if(item->GetValue("taxa_parcela_comprador")->Value() != "null")
                                                        Data3->tbSeguroPagamentoTAXA_PARCELA_COMPRADOR->Value = StrToFloat(Trim(item->GetValue("taxa_parcela_comprador")->Value()));

                                                    if(item->GetValue("taxa_parcela_vendedor")->Value() != "null")
                                                            Data3->tbSeguroPagamentoTAXA_PARCELA_VENDEDOR->Value = StrToFloat(Trim(item->GetValue("taxa_parcela_vendedor")->Value()));

                                                    if(item->GetValue("taxa_rep_aplicacao")->Value() != "null")
                                                        Data3->tbSeguroPagamentoTAXA_REP_APLICACAO->Value = StrToFloat(Trim(item->GetValue("taxa_rep_aplicacao")->Value()));

                                                dados = item->GetValue("data_inicial_transacao")->Value();

                                                    if(dados != "")
                                                    {
                                                    auxiliar = dados.SubString(9, 2) + "/";
                                                    auxiliar += dados.SubString(6, 2) + "/";
                                                    auxiliar += dados.SubString(0, 4);

                                                    Data3->tbSeguroPagamentoDATA_INICIAL_TRANSACAO->Value = StrToDate(auxiliar);
                                                    }

                                                dados = item->GetValue("data_movimentacao")->Value();

                                                    if(dados != "")
                                                    {
                                                    auxiliar = dados.SubString(9, 2) + "/";
                                                    auxiliar += dados.SubString(6, 2) + "/";
                                                    auxiliar += dados.SubString(0, 4);

                                                    Data3->tbSeguroPagamentoDATA_MOVIMENTACAO->Value = StrToDate(auxiliar);
                                                    }

                                                dados = item->GetValue("data_venda_ajuste")->Value();

                                                    if(dados != "")
                                                    {
                                                    auxiliar = dados.SubString(9, 2) + "/";
                                                    auxiliar += dados.SubString(6, 2) + "/";
                                                    auxiliar += dados.SubString(0, 4);

                                                    Data3->tbSeguroPagamentoDATA_VENDA_AJUSTE->Value = StrToDate(auxiliar);
                                                    }

                                                Data3->tbSeguroPagamentoHORA_VENDA_AJUSTE->Value = StrToTime(item->GetValue("hora_venda_ajuste")->Value());
                                                Data3->tbSeguroPagamento->ApplyUpdates(0);
                                                }
                                            }

                                        Label52->Caption = cont_detalhe + 1;
                                        Label6->Caption = cont_detalhe + 1;
                                        Application->ProcessMessages();
                                        }


                                        if(detalhe->Count == pageSize)
                                        {
                                        pagina++;

                                        Label59->Caption = pagina;
                                        Application->ProcessMessages();

                                        proxima_pagina = true;
                                        }

                                    json->Free();
                                	}
                                    else
                                    {
                                    erro++;
                                    Label41->Caption = erro;
                                    }
                                }
                            }
                            while(proxima_pagina);


                        pagina = 1;

                            do
                            {
                            proxima_pagina = false;
                            continuar = true;

                            Label59->Caption = pagina;

                            //ARQUIVOS DE Tipo de movimento 3 - Antecipação
                            url = "https://edi.api.pagseguro.com.br/edi/v1/2.00/movimentos?dataMovimento=" + data + "&pageNumber=" + pagina + "&pageSize=" + pageSize + "&tipoMovimento=3";

                                try
                                {
                                Memo3->Text = IdHTTP2->Get(url);
                                }
                                catch (EIdHTTPProtocolException &E)
                                {
                                    try
                                    {
                                    Memo3->Text = IdHTTP2->Get(url);
                                    Memo3->Text = IdHTTP2->Get(url);
                                    }
                                    catch (EIdHTTPProtocolException &E)
                                    {
                                    erro++;
                                    Label41->Caption = erro;
                                    continuar = false;

                                    consulta = "- Não foi possível verificar antecipações do estabelecimento " + id + " na data: " + data;
                    				Memo4->Lines->Add(consulta);
                                    }
                                }

                                //INÍCIO DO PROCESSO DE VENDAS
                                if(continuar)
                                {
                                    if(IdHTTP2->ResponseCode == 200)
                                    {
                                    json = (TJSONObject*) TJSONObject::ParseJSONValue(TEncoding::ASCII->GetBytes(Memo3->Lines->Text),0);

                                    detalhe = (TJSONObject*) json->GetValue("pagination");
                                    Label61->Caption = detalhe->GetValue("totalPages")->Value();

                                    detalhe = (TJSONObject*) json->GetValue("detalhes");

                                    Label52->Caption = 0;
                                    Label53->Caption = detalhe->Count;
                                    Label49->Caption = "Leitura de Antecipações";

                                    Label6->Caption = 0;
                                    Label7->Caption = detalhe->Count;
                                    Label2->Caption = "Leitura de Antecipações";

                                    Application->ProcessMessages();

                                        for(int cont_detalhe = 0; cont_detalhe < detalhe->Count; cont_detalhe++)
                                        {
                                        item = (TJSONObject*) detalhe->Get(cont_detalhe);

                                            if(item->GetValue("movimento_api_codigo")->Value() != "" && item->GetValue("estabelecimento")->Value() != ""
                                                && item->GetValue("codigo_autorizacao")->Value() != "" && item->GetValue("nsu")->Value() != "")
                                            {
                                            consulta = "select * from edi_pagseguro_antecipacao where MOVIMENTO_API_CODIGO = '" + item->GetValue("movimento_api_codigo")->Value() + "'";

                                                if(DataVerificacao2->tbSeguroAntecipacao->Active)
                                                {
                                                DataVerificacao2->tbSeguroAntecipacao->EmptyDataSet();
                                                }

                                            DataVerificacao2->tbSeguroAntecipacao->Close();
                                            DataVerificacao2->tbSeguroAntecipacao->SQL->Clear();
                                            DataVerificacao2->tbSeguroAntecipacao->SQL->Add(consulta);
                                            DataVerificacao2->tbSeguroAntecipacao->Open();

                                                if(DataVerificacao2->tbSeguroAntecipacao->RecordCount == 0)
                                                {
                                                Data3->tbSeguroAntecipacao->Insert();

                                                Data3->tbSeguroAntecipacaoDATA_LEITURA->Value = Date();
                                                Data3->tbSeguroAntecipacaoHORA_LEITURA->Value = Time();
                                                Data3->tbSeguroAntecipacaoTRATADO->Value = 'N';
                                                Data3->tbSeguroAntecipacaoCOD_CLIENTE->Value = Data3->tbSeguroCadastroCOD_CLIENTE->AsInteger;

                                                Data3->tbSeguroAntecipacaoMOVIMENTO_API_CODIGO->Value = item->GetValue("movimento_api_codigo")->Value();
                                                Data3->tbSeguroAntecipacaoESTABELECIMENTO->Value = item->GetValue("estabelecimento")->Value();
                                                Data3->tbSeguroAntecipacaoTIPO_EVENTO->Value = StrToInt(Trim(item->GetValue("tipo_evento")->Value()));
                                                Data3->tbSeguroAntecipacaoTIPO_TRANSACAO->Value = StrToInt(Trim(item->GetValue("tipo_transacao")->Value()));
                                                Data3->tbSeguroAntecipacaoCODIGO_TRANSACAO->Value = item->GetValue("codigo_transacao")->Value();
                                                Data3->tbSeguroAntecipacaoCODIGO_VENDA->Value = item->GetValue("codigo_venda")->Value();
                                                Data3->tbSeguroAntecipacaoVALOR_TOTAL_TRANSACAO->Value = StrToFloat(Trim(item->GetValue("valor_total_transacao")->Value()));
                                                Data3->tbSeguroAntecipacaoVALOR_PARCELA->Value = StrToFloat(Trim(item->GetValue("valor_parcela")->Value()));
                                                Data3->tbSeguroAntecipacaoPARCELA->Value = StrToInt(Trim(item->GetValue("parcela")->Value()));
                                                Data3->tbSeguroAntecipacaoPLANO->Value = StrToInt(Trim(item->GetValue("plano")->Value()));
                                                Data3->tbSeguroAntecipacaoQUANTIDADE_PARCELA->Value = StrToInt(Trim(item->GetValue("quantidade_parcela")->Value()));
                                                Data3->tbSeguroAntecipacaoVALOR_LIQUIDO_ANTECIPADO->Value = StrToFloat(Trim(item->GetValue("valor_liquido_antecipacao")->Value()));
                                                Data3->tbSeguroAntecipacaoVALOR_LIQUIDO_TRANSACAO->Value = StrToFloat(Trim(item->GetValue("valor_liquido_transacao")->Value()));
                                                Data3->tbSeguroAntecipacaoSTATUS_PAGAMENTO->Value = StrToInt(Trim(item->GetValue("status_pagamento")->Value()));
                                                Data3->tbSeguroAntecipacaoNUM_LOGICO->Value = item->GetValue("num_logico")->Value();
                                                Data3->tbSeguroAntecipacaoNSU->Value = item->GetValue("nsu")->Value();
                                                Data3->tbSeguroAntecipacaoCARTAO_BIN->Value = item->GetValue("cartao_bin")->Value();
                                                Data3->tbSeguroAntecipacaoCARTAO_HOLDER->Value = item->GetValue("cartao_holder")->Value();
                                                Data3->tbSeguroAntecipacaoCODIGO_AUTORIZACAO->Value = item->GetValue("codigo_autorizacao")->Value();
                                                Data3->tbSeguroAntecipacaoCODIGO_CV->Value = item->GetValue("codigo_cv")->Value();


                                                	if(item->GetValue("taxa_antecipacao")->Value() != "null")
                                                		Data3->tbSeguroAntecipacaoTAXA_ANTECIPACAO->Value = StrToFloat(Trim(item->GetValue("taxa_antecipacao")->Value()));

                                               		if(item->GetValue("tipo_registro")->Value() != "null" && item->GetValue("tipo_registro")->Value() != "")
                                                    	Data3->tbSeguroAntecipacaoTIPO_REGISTRO->Value = StrToInt(Trim(item->GetValue("tipo_registro")->Value()));

                                                dados = item->GetValue("data_inicial_transacao")->Value();

                                                    if(dados != "")
                                                    {
                                                    auxiliar = dados.SubString(9, 2) + "/";
                                                    auxiliar += dados.SubString(6, 2) + "/";
                                                    auxiliar += dados.SubString(0, 4);

                                                    Data3->tbSeguroAntecipacaoDATA_INICIAL_TRANSACAO->Value = StrToDate(auxiliar);
                                                    }

                                                dados = item->GetValue("data_venda_ajuste")->Value();

                                                    if(dados != "")
                                                    {
                                                    auxiliar = dados.SubString(9, 2) + "/";
                                                    auxiliar += dados.SubString(6, 2) + "/";
                                                    auxiliar += dados.SubString(0, 4);

                                                    Data3->tbSeguroAntecipacaoDATA_VENDA_AJUSTE->Value = StrToDate(auxiliar);
                                                    }

                                                dados = item->GetValue("data_prevista_pagamento")->Value();

                                                    if(dados != "")
                                                    {
                                                    auxiliar = dados.SubString(9, 2) + "/";
                                                    auxiliar += dados.SubString(6, 2) + "/";
                                                    auxiliar += dados.SubString(0, 4);

                                                    Data3->tbSeguroAntecipacaoDATA_PREVISTA_PAGAMENTO->Value = StrToDate(auxiliar);
                                                    }

                                                dados = item->GetValue("data_movimentacao")->Value();

                                                    if(dados != "")
                                                    {
                                                    auxiliar = dados.SubString(9, 2) + "/";
                                                    auxiliar += dados.SubString(6, 2) + "/";
                                                    auxiliar += dados.SubString(0, 4);

                                                    Data3->tbSeguroAntecipacaoDATA_MOVIMENTACAO->Value = StrToDate(auxiliar);
                                                    }

                                                Data3->tbSeguroAntecipacaoHORA_VENDA_AJUSTE->Value = StrToTime(item->GetValue("hora_venda_ajuste")->Value());
                                                Data3->tbSeguroAntecipacao->ApplyUpdates(0);
                                                }
                                            }

                                        Label52->Caption = cont_detalhe + 1;
                                        Label6->Caption = cont_detalhe + 1;
                                        Application->ProcessMessages();
                                        }


                                        if(detalhe->Count == pageSize)
                                        {
                                        pagina++;

                                        Label59->Caption = pagina;
                                        Application->ProcessMessages();

                                        proxima_pagina = true;
                                        }

                                    json->Free();
                                	}
                                    else
                                    {
                                    erro++;
                                    Label41->Caption = erro;
                                    }
                                }
                            }
                            while(proxima_pagina);
                        }
                    }
                }

            Data3->tbSeguroCadastro->Next();
            Label46->Caption = contador_cadastros + 1;
            ProgressBar5->Position = contador_cadastros + 1;

            Application->ProcessMessages();
            }

        ProgressBar4->Position = contador_dias + 1;

        Application->ProcessMessages();
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::TratarVendasStoneClick(TObject *Sender)
{
int contador = 0, final = 0, posicao;
int contador_contador, total_cv, contador_cv;
double valor_taxa_total, valor_bruto_total, valor_diferenca, valor_parcela_bruto, valor_parcela, valor_bruto;
double taxa;
bool continuar_domicilio;
AnsiString cnpj_cliente, dados, autorizacao, consulta, chave, data_venda, nsu, atualiza;
Word Year, Month, Day;
TDate dtPresent;

Label21->Caption = "Tratandos Arquivos Stone";
Label2->Caption = "Sem dados";
Label10->Caption = 0;
Label7->Caption = 0;
Label6->Caption = 0;

    do
	{
	Button6Click(Sender);

		if(Data2->tbVendaStone->Active)
		{
		Data2->tbVendaStone->EmptyDataSet();
		}

	Data2->tbVendaStone->Close();
	Data2->tbVendaStone->SQL->Clear();
	Data2->tbVendaStone->SQL->Add("select * from edi_stone_comprovante_venda where edi_stone_comprovante_venda.TRATADO = 'N' limit 30000");
	Data2->tbVendaStone->Open();

	final = 0;

		if(Data2->tbVendaStone->RecordCount > 0)
		{
        Label2->Caption = "Tratando Vendas";

		contador = 0;
		taxa = 0;
		contador_contador = 1;

		final = Data2->tbVendaStone->RecordCount;

		Label6->Caption = 0;
		Label7->Caption  = final;
		ProgressBar1->Max = final;

			if(!DataResumo->tbVendasOperadoras->Active)
			{
			DataResumo->tbVendasOperadoras->Close();
			DataResumo->tbVendasOperadoras->SQL->Clear();
			DataResumo->tbVendasOperadoras->SQL->Add("select * from vendas where vendas.CODIGO is null");
			DataResumo->tbVendasOperadoras->Open();
			}
			else
			{
			DataResumo->tbVendasOperadoras->EmptyDataSet();
			}

             //EFETUA ESTE BLOCO ATÉ REGISTRAR TODAS AS VENDAS
			while(contador < final)
			{
			cnpj_cliente = "";
			autorizacao = "";
			nsu = "";

            Edit1->Text = Data2->tbVendaStoneSTONECODE->AsString;
			//LOCALIZA O CLIENTE
			consulta = "Select * from cliente_operadora where cliente_operadora.COD_ADQUIRENTE = 7 and cliente_operadora.CODIGO_ESTABELECIMENTO = '" + Edit1->Text + "'";

				if(DataResumo->tbClientesOperadoras->Active)
				{
				DataResumo->tbClientesOperadoras->EmptyDataSet();
				}

			DataResumo->tbClientesOperadoras->Close();
			DataResumo->tbClientesOperadoras->SQL->Clear();
			DataResumo->tbClientesOperadoras->SQL->Add(consulta);
			DataResumo->tbClientesOperadoras->Open();

				if(DataResumo->tbClientesOperadoras->RecordCount == 1)
				{
				cnpj_cliente = DataResumo->tbClientesOperadorasCNPJ_ESTABELECIMENTO->AsString;
				}

            nsu = retirarZerosEsquerda(Data2->tbVendaStoneNSU->AsString);
            autorizacao = Data2->tbVendaStoneCODIGO_AUTORIZACAO->AsString;

            //CONTROLE DE DUPLICIDADE
            consulta = "SELECT * FROM vendas where vendas.COD_STATUS_FINANCEIRO = '1' and vendas.CNPJ = '" + cnpj_cliente + "'";
            consulta += " and vendas.ADQID = 7";

            consulta += " and vendas.PARCELA = '" + Data2->tbVendaStoneNUM_PARCELA->AsString + "'";
            consulta += " and vendas.NSU = '" + nsu + "'";
            consulta += " and vendas.AUTORIZACAO = '" + autorizacao + "'";

            Edit1->Text = Data2->tbVendaStoneDATA_AUTORIZACAO->AsString.SubString(7,4) + "-" + Data2->tbVendaStoneDATA_AUTORIZACAO->AsString.SubString(4,2) + "-" + Data2->tbVendaStoneDATA_AUTORIZACAO->AsString.SubString(0,2);

            consulta += " and vendas.DATA_VENDA = '" + Edit1->Text + "'";

                if(DataResumo->tbVendasOperadoras->Active)
                {
                DataResumo->tbVendasOperadoras->EmptyDataSet();
                }

            DataResumo->tbVendasOperadoras->Close();
            DataResumo->tbVendasOperadoras->SQL->Clear();
            DataResumo->tbVendasOperadoras->SQL->Add(consulta);
            DataResumo->tbVendasOperadoras->Open();

                if(DataResumo->tbVendasOperadoras->RecordCount == 0)
                {
                DataResumo->tbVendasOperadoras->Insert();

                //LOCALIZA O CLIENTE
                consulta = "select * from grupos_clientes where grupos_clientes.CNPJ = '" + cnpj_cliente + "'";

                    if(Data1->tbGrupos->Active)
                    {
                    Data1->tbGrupos->EmptyDataSet();
                    }

                Data1->tbGrupos->Close();
                Data1->tbGrupos->SQL->Clear();
                Data1->tbGrupos->SQL->Add(consulta);
                Data1->tbGrupos->Open();

                    if(Data1->tbGrupos->RecordCount == 1)
                    {
                    DataResumo->tbVendasOperadorasCOD_CLIENTE->Value = Data1->tbGruposCOD_CLIENTE->AsFloat;
                    DataResumo->tbVendasOperadorasCOD_GRUPO_CLIENTE->Value = Data1->tbGruposCODIGO->AsFloat;
                    DataResumo->tbVendasOperadorasEMPRESA->Value = Data1->tbGruposNOME_EMPRESA->AsString;
                    DataResumo->tbVendasOperadorasCNPJ->Value = Data1->tbGruposCNPJ->AsString;

                    //MARCA NO CLIENTE COMO ARQUIVO_PROCESSADO = 'N';
                    consulta = "select * from clientes where clientes.CODIGO = " + Data1->tbGruposCOD_CLIENTE->AsString;

                        if(Data1->tbClientes->Active)
                        {
                        Data1->tbClientes->EmptyDataSet();
                        }

                    Data1->tbClientes->Close();
                    Data1->tbClientes->SQL->Clear();
                    Data1->tbClientes->SQL->Add(consulta);
                    Data1->tbClientes->Open();

                        if(Data1->tbClientes->RecordCount == 1)
                        {
                        Data1->tbClientes->Edit();
                        Data1->tbClientesARQUIVOS_PROCESSADOS->Value = 'N';
                        Data1->tbClientes->ApplyUpdates();
                        }
                    }
                    else
                    {
                    DataResumo->tbVendasOperadorasEMPRESA->Value = "EMPRESA NÃO IDENTIFICADA";
                    }

                DataResumo->tbVendasOperadorasADQID->Value = 7;
                DataResumo->tbVendasOperadorasADQUIRENTE->Value = "Stone";

                DataResumo->tbVendasOperadorasDATA_PREVISTA_PAGTO->Value = Data2->tbVendaStonePREVISAO_PAGAMENTO->AsDateTime;
                DataResumo->tbVendasOperadorasDATA_VENDA->Value = Data2->tbVendaStoneDATA_AUTORIZACAO->AsDateTime;
                DataResumo->tbVendasOperadorasHORA_TRANSACAO->Value = Data2->tbVendaStoneHORA_AUTORIZACAO->AsDateTime;
                DataResumo->tbVendasOperadorasCARTAO->Value = Data2->tbVendaStoneNUM_CARTAO->AsString;
                DataResumo->tbVendasOperadorasAUTORIZACAO->Value = autorizacao;
                DataResumo->tbVendasOperadorasNSU->Value = nsu;

                DataResumo->tbVendasOperadorasPARCELA->Value = Data2->tbVendaStoneNUM_PARCELA->AsInteger;
                DataResumo->tbVendasOperadorasTOTAL_PARCELAS->Value = Data2->tbVendaStoneTOTAL_PARCELAS->AsInteger;
                DataResumo->tbVendasOperadorasESTABELECIMENTO->Value = Data2->tbVendaStoneSTONECODE->AsString;

                valor_bruto = SimpleRoundTo(Data2->tbVendaStoneVALOR_BRUTO_PARCELA->AsFloat, -2);
				DataResumo->tbVendasOperadorasVALOR_BRUTO->Value = StrToFloat(FormatFloat("#0.00", valor_bruto));

                valor_bruto = SimpleRoundTo(Data2->tbVendaStoneVALOR_LIQUIDO_PARCELA->AsFloat, -6);
                Edit1->Text = valor_bruto;
				DataResumo->tbVendasOperadorasVALOR_LIQUIDO->Value = StrToFloat(Edit1->Text);

                DataResumo->tbVendasOperadorasVALOR_TAXA->Value = DataResumo->tbVendasOperadorasVALOR_BRUTO->AsFloat - DataResumo->tbVendasOperadorasVALOR_LIQUIDO->AsFloat;

                taxa = 0;
				taxa = DataResumo->tbVendasOperadorasVALOR_TAXA->AsFloat / DataResumo->tbVendasOperadorasVALOR_BRUTO->AsFloat;
				taxa = taxa * 100;

                taxa = SimpleRoundTo(taxa, -2);

				DataResumo->tbVendasOperadorasPERCENTUAL_TAXA->Value = taxa;

                //STATUS = NÃO CONCILIADA
                DataResumo->tbVendasOperadorasCOD_STATUS_CONCILIACAO->Value = 2;

                //STATUS FINANCEIRO = PREVISTO
                DataResumo->tbVendasOperadorasCOD_STATUS_FINANCEIRO->Value = 1;

                DataResumo->tbVendasOperadorasCANCELADO->Value = 'N';
                DataResumo->tbVendasOperadorasTERMINAL->Value = Data2->tbVendaStoneNUM_TERMINAL->AsString;
                DataResumo->tbVendasOperadorasVERIFICADO_DUPLICIDADE->Value = 'S';

                //SELECIONA O DOMICÍLIO BANCÁRIO DO CLIENTE
                Edit1->Text = DataResumo->tbVendasOperadorasADQID->AsString;
                consulta = "select * from domicilio_cliente where domicilio_cliente.CODIGO is not null and domicilio_cliente.COD_ADQUIRENTE = '" + Edit1->Text + "'";
                Edit1->Text = DataResumo->tbVendasOperadorasCOD_CLIENTE->AsString;
                consulta += " and domicilio_cliente.COD_CLIENTE = '" + Edit1->Text + "'";
                consulta += " and domicilio_cliente.CNPJ = '" + DataResumo->tbVendasOperadorasCNPJ->AsString + "'";

                    if(Data1->tbDomicilioCliente->Active)
                    {
                    Data1->tbDomicilioCliente->EmptyDataSet();
                    }

                Data1->tbDomicilioCliente->Close();
                Data1->tbDomicilioCliente->SQL->Clear();
                Data1->tbDomicilioCliente->SQL->Add(consulta);
                Data1->tbDomicilioCliente->Open();

                continuar_domicilio = true;

                    if(Data1->tbDomicilioCliente->RecordCount >= 1)
                    {
                        if(Data1->tbDomicilioCliente->RecordCount > 1)
                        {
                        //SELECIONA O DOMICÍLIO BANCÁRIO DO CLIENTE
                        Edit1->Text = DataResumo->tbVendasOperadorasADQID->AsString;
                        consulta = "select * from domicilio_cliente where domicilio_cliente.CODIGO is not null and domicilio_cliente.COD_ADQUIRENTE = '" + Edit1->Text + "'";
                        Edit1->Text = DataResumo->tbVendasOperadorasCOD_CLIENTE->AsString;
                        consulta += " and domicilio_cliente.COD_CLIENTE = '" + Edit1->Text + "'";
                        consulta += " and domicilio_cliente.CNPJ = '" + DataResumo->tbVendasOperadorasCNPJ->AsString + "'";
                        consulta += " and domicilio_cliente.COD_ESTABELECIMENTO = '" + DataResumo->tbVendasOperadorasESTABELECIMENTO->AsString + "'";

                            if(Data1->tbDomicilioCliente->Active)
                            {
                            Data1->tbDomicilioCliente->EmptyDataSet();
                            }

                        Data1->tbDomicilioCliente->Close();
                        Data1->tbDomicilioCliente->SQL->Clear();
                        Data1->tbDomicilioCliente->SQL->Add(consulta);
                        Data1->tbDomicilioCliente->Open();

                        	if(Data1->tbDomicilioCliente->RecordCount != 1)
                            {
                            continuar_domicilio = false;
                            }
                        }

                        if(continuar_domicilio)
                        {
                        DataResumo->tbVendasOperadorasBANCO->Value = Data1->tbDomicilioClienteCOD_BANCO->AsFloat;
                        DataResumo->tbVendasOperadorasAGENCIA->Value = Data1->tbDomicilioClienteAGENCIA->AsString;
                        DataResumo->tbVendasOperadorasCONTA->Value = Data1->tbDomicilioClienteCONTA->AsString;
                        }
                    }


                //PRODUTO = NÃO IDENTIFICADO
                DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 54;

                    //DÉBITO
                    if(Data2->tbVendaStoneCOD_TIPO_CONTA->AsInteger == 1)
                    {
                    DataResumo->tbVendasOperadorasCODIGO_MODALIDADE->Value = 0;
                    DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 21;
                    }
                    //CRÉDITO
                    else if(Data2->tbVendaStoneCOD_TIPO_CONTA->AsInteger == 2)
                    {

                        //CRÉDITO A VISTA
                        if(DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger == 1)
                        {
                        DataResumo->tbVendasOperadorasCODIGO_MODALIDADE->Value = 1;
                        DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 20;
                        }
                        else
                        {
                        //PARCELADO
                        DataResumo->tbVendasOperadorasCODIGO_MODALIDADE->Value = 17;

                            //VERIFICA O PRODUTO CORRETO COM BASE NO N° DE PARCELAS
                            if(DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger == 2)
                            {
                            DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 40;
                            }
                            else if(DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger == 3)
                            {
                            DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 41;
                            }
                            else if(DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger == 4)
                            {
                            DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 42;
                            }
                            else if(DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger == 5)
                            {
                            DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 43;
                            }
                            else if(DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger == 6)
                            {
                            DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 44;
                            }
                            else if(DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger == 7)
                            {
                            DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 45;
                            }
                            else if(DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger == 8)
                            {
                            DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 46;
                            }
                            else if(DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger == 9)
                            {
                            DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 47;
                            }
                            else if(DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger == 10)
                            {
                            DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 48;
                            }
                            else if(DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger == 11)
                            {
                            DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 50;
                            }
                            else if(DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger == 12)
                            {
                            DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 51;
                            }
                            else if(DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger == 13)
                            {
                            DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 55;
                            }
                            else if(DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger == 14)
                            {
                            DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 56;
                            }
                            else if(DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger == 15)
                            {
                            DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 57;
                            }
                            else if(DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger == 16)
                            {
                            DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 58;
                            }
                            else if(DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger == 17)
                            {
                            DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 59;
                            }
                            else if(DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger == 18)
                            {
                            DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 60;
                            }
                        }
                    }


                //CONTROLE DAS BANDEIRAS

                    //MasterCard
                    if(Data2->tbVendaStoneCOD_BANDEIRA->AsInteger == 2)
                    {
                    DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 160;
                    }
                    //Visa
                    else if(Data2->tbVendaStoneCOD_BANDEIRA->AsInteger == 1)
                    {
                    DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 159;
                    }
                    //Hipercard
                    else if(Data2->tbVendaStoneCOD_BANDEIRA->AsInteger == 9)
                    {
                    DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 162;
                    }
                    //Elo
                    else if(Data2->tbVendaStoneCOD_BANDEIRA->AsInteger == 171)
                    {
                    DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 166;
                    }
                    //Amex
                    else if(Data2->tbVendaStoneCOD_BANDEIRA->AsInteger == 3)
                    {
                    DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 165;
                    }
                    //Cabal
                    else if(Data2->tbVendaStoneCOD_BANDEIRA->AsInteger == 4)
                    {
                    DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 169;
                    }
                    //Union Pay
                    else if(Data2->tbVendaStoneCOD_BANDEIRA->AsInteger == 5)
                    {
                    DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 182;
                    }


                //CONTROLE O TIPO DE CAPTURA

                    //POS
                    if(Data2->tbVendaStoneCOD_TIPO_TERMINAL->AsInteger == 1 || Data2->tbVendaStoneCOD_TIPO_TERMINAL->AsInteger == 2)
                    {
                    DataResumo->tbVendasOperadorasCOD_MEIO_CAPTURA->Value = 1;
                    }
                    //TEF
                    else if(Data2->tbVendaStoneCOD_TIPO_TERMINAL->AsInteger == 3)
                    {
                    DataResumo->tbVendasOperadorasCOD_MEIO_CAPTURA->Value = 2;
                    }
                    //INTERNET
                    else if(Data2->tbVendaStoneCOD_TIPO_TERMINAL->AsInteger == 4)
                    {
                    DataResumo->tbVendasOperadorasCOD_MEIO_CAPTURA->Value = 3;
                    }
                    //MOBILE
                    else if(Data2->tbVendaStoneCOD_TIPO_TERMINAL->AsInteger == 7)
                    {
                    DataResumo->tbVendasOperadorasCOD_MEIO_CAPTURA->Value = 8;
                    }

                //COMPLETA A CHAVE NO PADRÃO
                //cod_cliente-cod_operadora-data_venda_formato_americano-Parcela_atual-total_parcelas_NSU_AUTORIZAÇÃO-cod_Bandeira-cod_modalidade

                Edit1->Text = DataResumo->tbVendasOperadorasCOD_CLIENTE->AsFloat;
                chave = Edit1->Text;

                    //VERIFICA SE FOI INFORMADA A OPERADORA
                    if(DataResumo->tbVendasOperadorasADQID->AsFloat > 0)
                    {
                    Edit1->Text = DataResumo->tbVendasOperadorasADQID->AsFloat;
                    chave += "-" + Edit1->Text;
                    }

                //COMPLETA A DATA DA VENDA
                dtPresent = DataResumo->tbVendasOperadorasDATA_VENDA->AsDateTime;
                DecodeDate(dtPresent, Year, Month, Day);

                Edit1->Text = Year;
                data_venda = Edit1->Text + "-";
                Edit1->Text = Month;
                data_venda = data_venda + Edit1->Text + "-";
                Edit1->Text = Day;
                data_venda = data_venda + Edit1->Text;

                Edit1->Text = data_venda;

                chave += "-" + Edit1->Text;

                //COMPLETA A PARCELA ATUAL
                Edit1->Text = DataResumo->tbVendasOperadorasPARCELA->AsFloat;

                chave += "-" + Edit1->Text;

                //COMPLETA O CAMPO TOTAL DE PARCELAS
                Edit1->Text = DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsFloat;
                chave += "-" + Edit1->Text;

                    //VERIFICA SE A VENDA POSSUI NSU
                    if(DataResumo->tbVendasOperadorasNSU->AsString != "")
                    {
                    chave += "-" + DataResumo->tbVendasOperadorasNSU->AsString;
                    }

                    //VERIFICA SE A VENDA POSSUI AUTORIZAÇÃO
                    if(DataResumo->tbVendasOperadorasAUTORIZACAO->AsString != "")
                    {
                    chave += "-" + DataResumo->tbVendasOperadorasAUTORIZACAO->AsString;
                    }

                    if(DataResumo->tbVendasOperadorasCOD_BANDEIRA->AsFloat > 0)
                    {
                    Edit1->Text = DataResumo->tbVendasOperadorasCOD_BANDEIRA->AsFloat;
                    chave += "-" + Edit1->Text;
                    }

                    if(DataResumo->tbVendasOperadorasCODIGO_MODALIDADE->AsFloat > 0)
                    {
                    Edit1->Text = DataResumo->tbVendasOperadorasCODIGO_MODALIDADE->AsFloat;
                    chave += "-" + Edit1->Text;
                    }

                DataResumo->tbVendasOperadorasCHAVE_VENDA->Value = chave;

                DataResumo->tbVendasOperadoras->ApplyUpdates(0);

                atualiza = "update vendas set vendas.VALOR_LIQUIDO = ROUND(vendas.VALOR_LIQUIDO, 6), vendas.VALOR_BRUTO = ROUND(vendas.VALOR_BRUTO, 2) ";
                atualiza += " where vendas.CODIGO = " + DataResumo->tbVendasOperadorasCODIGO->AsString;

                Data1->tbExcluir->Close();
                Data1->tbExcluir->SQL->Clear();
                Data1->tbExcluir->SQL->Add(atualiza);
                Data1->tbExcluir->ExecSQL();
				}

			contador++;

			Data2->tbVendaStone->Edit();
			Data2->tbVendaStoneTRATADO->Value = 'S';
			Data2->tbVendaStone->ApplyUpdates(0);

			Data2->tbVendaStone->Next();

			Application->ProcessMessages();

			Label6->Caption = contador;
			ProgressBar1->Position = contador;

				if(contador == (5000 * contador_contador))
				{
				Button6Click(Sender);
				contador_contador++;
				}
			}
		}
	}
	while(final > 0);

	if(Data2->tbVendaStone->Active)
	{
	Data2->tbVendaStone->EmptyDataSet();
	}

Button6Click(Sender);

Edit2->Text = Date();
Edit3->Text = Time();
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::TratarAntecipacoesStoneClick(TObject *Sender)
{
int contador = 0, final = 0, posicao;
double taxa, valor_credito_original, valor_lancamento, valor_bruto;
int contador_contador;
AnsiString cnpj_cliente, dados, autorizacao, consulta, chave, data_venda, nsu, data, atualiza;
Word Year, Month, Day;
TDate dtPresent;

Label21->Caption = "Tratandos Arquivos Stone";
Label2->Caption = "Sem dados";
Label10->Caption = 0;
Label7->Caption = 0;
Label6->Caption = 0;

	do
	{
	Button6Click(Sender);

		if(Data2->tbPagamentoStone->Active)
		{
		Data2->tbPagamentoStone->EmptyDataSet();
		}

	Data2->tbPagamentoStone->Close();
	Data2->tbPagamentoStone->SQL->Clear();
	Data2->tbPagamentoStone->SQL->Add("select * from edi_stone_comprovante_pagamento where edi_stone_comprovante_pagamento.TRATADO = 'N' and edi_stone_comprovante_pagamento.DESCONTO_ANTECIPACAO > 0 limit 30000");
	Data2->tbPagamentoStone->Open();

	final = 0;

		if(Data2->tbPagamentoStone->RecordCount > 0)
		{
        Label2->Caption = "Tratando Antecipações";

		contador = 0;
		taxa = 0;
		contador_contador = 1;

		final = Data2->tbPagamentoStone->RecordCount;

		Label6->Caption = 0;
		Label7->Caption  = final;
		ProgressBar1->Max = final;

            if(!DataResumo->tbPagamentosOperadoras->Active)
			{
			DataResumo->tbPagamentosOperadoras->Close();
			DataResumo->tbPagamentosOperadoras->SQL->Clear();
			DataResumo->tbPagamentosOperadoras->SQL->Add("Select * from pagamentos_operadoras where pagamentos_operadoras.CODIGO is null");
			DataResumo->tbPagamentosOperadoras->Open();
			}
			else
			{
			DataResumo->tbPagamentosOperadoras->EmptyDataSet();
			}

			//EFETUA ESSE BLOCO ATÉ ATUALIZAR TODOS OS REGISTROS
			while(contador < final)
			{
			cnpj_cliente = "";
			autorizacao = "";
			nsu  = "";

            Edit1->Text = Data2->tbPagamentoStoneSTONECODE->AsString;
            //LOCALIZA O CLIENTE
            consulta = "Select * from cliente_operadora where cliente_operadora.COD_ADQUIRENTE = 7";
            consulta += " and cliente_operadora.CODIGO_ESTABELECIMENTO = '" + Edit1->Text + "'";

                if(DataResumo->tbClientesOperadoras->Active)
                {
                DataResumo->tbClientesOperadoras->EmptyDataSet();
                }

            DataResumo->tbClientesOperadoras->Close();
            DataResumo->tbClientesOperadoras->SQL->Clear();
            DataResumo->tbClientesOperadoras->SQL->Add(consulta);
            DataResumo->tbClientesOperadoras->Open();

                if(DataResumo->tbClientesOperadoras->RecordCount == 1)
                {
                cnpj_cliente = DataResumo->tbClientesOperadorasCNPJ_ESTABELECIMENTO->AsString;
                }

            nsu = retirarZerosEsquerda(Data2->tbPagamentoStoneNSU->AsString);
            autorizacao = "";

            //CONTROLE DE DUPLICIDADE
            consulta = "select * from pagamentos_operadoras where pagamentos_operadoras.CODIGO is not null";
            consulta += " and pagamentos_operadoras.COD_ADQUIRENTE = 7";

            Edit1->Text = cnpj_cliente;
            consulta += " and pagamentos_operadoras.CNPJ = '" + Edit1->Text + "'";

            consulta += " and pagamentos_operadoras.PARCELA = '" + Data2->tbPagamentoStoneNUM_PARCELA->AsString + "'";
            consulta += " and pagamentos_operadoras.NSU = '" + nsu + "'";

            Edit1->Text = Data2->tbPagamentoStonePAGAMENTO_PARCELA->AsString.SubString(7,4) + "-" + Data2->tbPagamentoStonePAGAMENTO_PARCELA->AsString.SubString(4,2) + "-" + Data2->tbPagamentoStonePAGAMENTO_PARCELA->AsString.SubString(0,2);
            consulta += " and pagamentos_operadoras.DATA_PAGAMENTO = '" + Edit1->Text + "'";

                if(DataResumo->tbPagamentosOperadoras->Active)
                {
                DataResumo->tbPagamentosOperadoras->EmptyDataSet();
                }

            DataResumo->tbPagamentosOperadoras->Close();
            DataResumo->tbPagamentosOperadoras->SQL->Clear();
            DataResumo->tbPagamentosOperadoras->SQL->Add(consulta);
            DataResumo->tbPagamentosOperadoras->Open();

                if(DataResumo->tbPagamentosOperadoras->RecordCount == 0)
                {
                DataResumo->tbPagamentosOperadoras->Insert();

                DataResumo->tbPagamentosOperadorasCNPJ->Value = cnpj_cliente;
                DataResumo->tbPagamentosOperadorasCOD_ADQUIRENTE->Value = 7;

                //LOCALIZA O CLIENTE
                consulta = "select * from grupos_clientes where grupos_clientes.CNPJ = '" + cnpj_cliente + "'";

                    if(Data1->tbGrupos->Active)
                    {
                    Data1->tbGrupos->EmptyDataSet();
                    }

                Data1->tbGrupos->Close();
                Data1->tbGrupos->SQL->Clear();
                Data1->tbGrupos->SQL->Add(consulta);
                Data1->tbGrupos->Open();

                    if(Data1->tbGrupos->RecordCount > 0)
                    {
                    DataResumo->tbPagamentosOperadorasCOD_CLIENTE->Value = Data1->tbGruposCOD_CLIENTE->AsFloat;
                    DataResumo->tbPagamentosOperadorasEMPRESA->Value = Data1->tbGruposNOME_EMPRESA->AsString;
                    DataResumo->tbPagamentosOperadorasCOD_GRUPO_CLIENTE->Value = Data1->tbGruposCODIGO->AsFloat;
                    DataResumo->tbPagamentosOperadorasCNPJ->Value = cnpj_cliente;
                    }
                    else
                    {
                    DataResumo->tbPagamentosOperadorasEMPRESA->Value = "EMPRESA NÃO IDENTIFICADA";
                    }

                DataResumo->tbPagamentosOperadorasAGENCIA->Value = retirarZerosEsquerda(Data2->tbPagamentoStoneAGENCIA->AsString);
                DataResumo->tbPagamentosOperadorasBANCO->Value = Data2->tbPagamentoStoneBANCO->AsInteger;
                DataResumo->tbPagamentosOperadorasCOD_BANCO->Value = StrToFloat(DataResumo->tbPagamentosOperadorasBANCO->AsFloat);
                DataResumo->tbPagamentosOperadorasCONTA->Value = retirarZerosEsquerda(Data2->tbPagamentoStoneNUM_CONTA->AsString);

                //NÃO CONCILIADO
                DataResumo->tbPagamentosOperadorasCOD_STATUS->Value = 2;

                //STATUS = NÃO LIQUIDADO
                DataResumo->tbPagamentosOperadorasCOD_STATUS_FINANCEIRO->Value = 1;

                DataResumo->tbPagamentosOperadorasVINCULADO_VENDA->Value = 'N';
                DataResumo->tbPagamentosOperadorasENCONTRADA_VENDA->Value = 'N';
                DataResumo->tbPagamentosOperadorasDUPLICIDADE_VERIFICADA->Value = 'S';
                DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->Value = autorizacao;
                DataResumo->tbPagamentosOperadorasNSU->Value = nsu;
                DataResumo->tbPagamentosOperadorasNUMERO_RESUMO_VENDA->Value = Data2->tbPagamentoStoneID_PAGAMENTO->AsString;

                DataResumo->tbPagamentosOperadorasDATA_PROCESSAMENTO->Value = Date();
                DataResumo->tbPagamentosOperadorasHORA_PROCESSAMENTO->Value = Time();

                DataResumo->tbPagamentosOperadorasID_LOJA->Value = Data2->tbPagamentoStoneSTONECODE->AsString;

                DataResumo->tbPagamentosOperadorasDATA_PREV_PAG_ORIGINAL->Value = Data2->tbPagamentoStonePAGAMENTO_REAL_ANTECIPADO->AsDateTime;
                DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->Value = Data2->tbPagamentoStonePAGAMENTO_PARCELA->AsDateTime;
                DataResumo->tbPagamentosOperadorasDATA_VENDA->Value = Data2->tbPagamentoStoneDATA_AUTORIZACAO->AsDateTime;
                DataResumo->tbPagamentosOperadorasHORA_VENDA->Value = Data2->tbPagamentoStoneHORA_AUTORIZACAO->AsDateTime;

                /*PAGAMENTO NORMAL
                1 - NORMAL
                2 - ANTECIPADO
                */

                DataResumo->tbPagamentosOperadorasCOD_TIPO_PAGAMENTO->Value = 2;

                //1 - PAGAMENTO
                DataResumo->tbPagamentosOperadorasCOD_TIPO_LANCAMENTO->Value = 1;

                DataResumo->tbPagamentosOperadorasPARCELA->Value = Data2->tbPagamentoStoneNUM_PARCELA->AsInteger;
                DataResumo->tbPagamentosOperadorasTOTAL_PARCELAS->Value = Data2->tbPagamentoStoneNUM_PARCELA->AsInteger;

                valor_bruto = SimpleRoundTo(Data2->tbPagamentoStoneVALOR_BRUTO_PARCELA->AsFloat, -2);
                DataResumo->tbPagamentosOperadorasVALOR_BRUTO->Value = StrToFloat(FormatFloat("#0.00", valor_bruto));

                valor_bruto = SimpleRoundTo(Data2->tbPagamentoStoneDESCONTO_ANTECIPACAO->AsFloat, -6);
                DataResumo->tbPagamentosOperadorasVALOR_TAXA_ANTECIPACAO->Value = StrToFloat(FormatFloat("#0.000000", valor_bruto));

                taxa = 0;
				taxa = DataResumo->tbPagamentosOperadorasVALOR_TAXA_ANTECIPACAO->AsFloat / DataResumo->tbPagamentosOperadorasVALOR_BRUTO->AsFloat;
				taxa = taxa * 100;

                taxa = SimpleRoundTo(taxa, -2);

				DataResumo->tbPagamentosOperadorasTAXA_ANTECIPACAO->Value = taxa;

               	valor_bruto = SimpleRoundTo(Data2->tbPagamentoStoneVALOR_LIQUIDO_PARCELA->AsFloat, -6);
                DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->Value = StrToFloat(FormatFloat("#0.000000", valor_bruto));

                DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value = (DataResumo->tbPagamentosOperadorasVALOR_BRUTO->AsFloat - DataResumo->tbPagamentosOperadorasVALOR_TAXA_ANTECIPACAO->AsFloat) - DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->AsFloat;

                taxa = 0;
                taxa = DataResumo->tbPagamentosOperadorasVALOR_TAXA->AsFloat / DataResumo->tbPagamentosOperadorasVALOR_BRUTO->AsFloat;
                taxa = taxa * 100;

                taxa = SimpleRoundTo(taxa, -2);

                DataResumo->tbPagamentosOperadorasTAXA_PERCENTUAL->Value = taxa;

                //PRODUTO = NÃO IDENTIFICADO
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 54;

                	//CRÉDITO A VISTA
                    if(DataResumo->tbPagamentosOperadorasPARCELA->AsFloat == 1)
                    {
                    DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 1;
                    DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 20;
                    }
                    else
                    {
                    //PARCELADO
                    DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 17;

                        //VERIFICA O PRODUTO CORRETO COM BASE NO N° DE PARCELAS
                        if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 2)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 40;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 3)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 41;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 4)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 42;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 5)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 43;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 6)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 44;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 7)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 45;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 8)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 46;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 9)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 47;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 10)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 48;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 11)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 50;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 12)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 51;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 13)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 55;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 14)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 56;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 15)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 57;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 16)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 58;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 17)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 59;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 18)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 60;
                        }
                    }

                //CONTROLE DAS BANDEIRAS

                    //MasterCard
                    if(Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 7)
                    {
                    DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 160;
                    }
                    //Visa
                    else if(Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 4)
                    {
                    DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 159;
                    }
                    //Hipercard
                    else if(Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 10)
                    {
                    DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 162;
                    }
                    //Elo
                    else if(Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 13)
                    {
                    DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 166;
                    }
                    //Amex
                    else if(Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 16)
                    {
                    DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 165;
                    }
                    //Cabal
                    else if(Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 22)
                    {
                    DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 169;
                    }
                    //Union Pay
                    else if(Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 25)
                    {
                    DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 182;
                    }


                    if(DataResumo->tbPagamentosOperadorasCOD_BANCO->AsInteger == 0 || DataResumo->tbPagamentosOperadorasCOD_CLIENTE->AsInteger == 801)
                    {
                    //SELECIONA O DOMICÍLIO BANCÁRIO DO CLIENTE
                    Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_ADQUIRENTE->AsString;
                    consulta = "select * from domicilio_cliente where domicilio_cliente.CODIGO is not null and domicilio_cliente.COD_ADQUIRENTE = '" + Edit1->Text + "'";
                    consulta += " and domicilio_cliente.CNPJ = '" + DataResumo->tbPagamentosOperadorasCNPJ->AsString + "'";

                        if(DataResumo->tbPagamentosOperadorasCONTA->AsString != "")
                        {
                        consulta += " and domicilio_cliente.CONTA = '" + DataResumo->tbPagamentosOperadorasCONTA->AsString + "'";
                        }

                        if(Data1->tbDomicilioCliente->Active)
                        {
                        Data1->tbDomicilioCliente->EmptyDataSet();
                        }

                    Data1->tbDomicilioCliente->Close();
                    Data1->tbDomicilioCliente->SQL->Clear();
                    Data1->tbDomicilioCliente->SQL->Add(consulta);
                    Data1->tbDomicilioCliente->Open();

                        if(Data1->tbDomicilioCliente->RecordCount == 1)
                        {
                        DataResumo->tbPagamentosOperadorasBANCO->Value = Data1->tbDomicilioClienteCOD_BANCO->AsString;
                        DataResumo->tbPagamentosOperadorasCOD_BANCO->Value = DataResumo->tbPagamentosOperadorasBANCO->AsInteger;
                        DataResumo->tbPagamentosOperadorasAGENCIA->Value = Data1->tbDomicilioClienteAGENCIA->AsString;
                        DataResumo->tbPagamentosOperadorasCONTA->Value = Data1->tbDomicilioClienteCONTA->AsString;
                        }
                    }

                //COMPLETA A CHAVE NO PADRÃO
                //cod_cliente-cod_operadora-data_venda_formato_americano-Parcela_atual-total_parcelas_NSU_AUTORIZAÇÃO-cod_Bandeira-cod_modalidade

                Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_CLIENTE->AsFloat;
                chave = Edit1->Text;

                    //VERIFICA SE FOI INFORMADA A OPERADORA
                    if(DataResumo->tbPagamentosOperadorasCOD_ADQUIRENTE->AsFloat > 0)
                    {
                    Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_ADQUIRENTE->AsFloat;
                    chave += "-" + Edit1->Text;
                    }

                dtPresent = DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->AsDateTime;
                DecodeDate(dtPresent, Year, Month, Day);

                Edit1->Text = Year;
                data_venda = Edit1->Text + "-";
                Edit1->Text = Month;
                data_venda = data_venda + Edit1->Text + "-";
                Edit1->Text = Day;
                data_venda = data_venda + Edit1->Text;

                Edit1->Text = data_venda;

                chave += "-" + Edit1->Text;

                //COMPLETA A PARCELA ATUAL
                Edit1->Text = DataResumo->tbPagamentosOperadorasPARCELA->AsFloat;

                chave += "-" + Edit1->Text;

                //COMPLETA O CAMPO TOTAL DE PARCELAS
                Edit1->Text = DataResumo->tbPagamentosOperadorasTOTAL_PARCELAS->AsFloat;
                chave += "-" + Edit1->Text;

                    //VERIFICA SE A VENDA POSSUI NSU
                    if(DataResumo->tbPagamentosOperadorasNSU->AsString != "")
                    {
                    chave += "-" + DataResumo->tbPagamentosOperadorasNSU->AsString;
                    }

                    //VERIFICA SE A VENDA POSSUI AUTORIZAÇÃO
                    if(DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->AsString != "")
                    {
                    chave += "-" + DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->AsString;
                    }

                    if(DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->AsFloat > 0)
                    {
                    Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->AsFloat;
                    chave += "-" + Edit1->Text;
                    }

                DataResumo->tbPagamentosOperadorasCHAVE_PAGAMENTO->Value = chave;

                DataResumo->tbPagamentosOperadoras->ApplyUpdates(0);

                atualiza = "update pagamentos_operadoras set pagamentos_operadoras.VALOR_LIQUIDO = ROUND(pagamentos_operadoras.VALOR_LIQUIDO, 6), pagamentos_operadoras.VALOR_BRUTO = ROUND(pagamentos_operadoras.VALOR_BRUTO, 2), pagamentos_operadoras.VALOR_TAXA_ANTECIPACAO = ROUND(pagamentos_operadoras.VALOR_TAXA_ANTECIPACAO, 6) ";
                atualiza += " where pagamentos_operadoras.CODIGO = " + DataResumo->tbPagamentosOperadorasCODIGO->AsString;

                Data1->tbExcluir->Close();
                Data1->tbExcluir->SQL->Clear();
                Data1->tbExcluir->SQL->Add(atualiza);
                Data1->tbExcluir->ExecSQL();

                //TENTA LOCALIZAR A VENDA
                consulta = "SELECT * FROM vendas where vendas.COD_STATUS_FINANCEIRO = '1' and vendas.CNPJ = '" + cnpj_cliente + "'";
                consulta += " and vendas.ADQID = 7";

                consulta += " and vendas.PARCELA = '" + DataResumo->tbPagamentosOperadorasPARCELA->AsString + "'";
                consulta += " and vendas.NSU = '" + nsu + "'";

                Edit1->Text = Data2->tbPagamentoStoneDATA_AUTORIZACAO->AsString.SubString(7,4) + "-" + Data2->tbPagamentoStoneDATA_AUTORIZACAO->AsString.SubString(4,2) + "-" + Data2->tbPagamentoStoneDATA_AUTORIZACAO->AsString.SubString(0,2);

                consulta += " and vendas.DATA_VENDA = '" + Edit1->Text + "'";

                    if(DataResumo->tbVendasOperadoras->Active)
                    {
                    DataResumo->tbVendasOperadoras->EmptyDataSet();
                    }

                DataResumo->tbVendasOperadoras->Close();
                DataResumo->tbVendasOperadoras->SQL->Clear();
                DataResumo->tbVendasOperadoras->SQL->Add(consulta);
                DataResumo->tbVendasOperadoras->Open();

                    if(DataResumo->tbVendasOperadoras->RecordCount == 1)
                    {
                    DataResumo->tbPagamentosOperadoras->Edit();

                    //CONCILIADA
                    DataResumo->tbPagamentosOperadorasCOD_STATUS->Value = 1;

                    //STATUS = LIQUIDADO
                    DataResumo->tbPagamentosOperadorasCOD_STATUS_FINANCEIRO->Value = 2;

                    DataResumo->tbPagamentosOperadorasVINCULADO_VENDA->Value = 'S';
                    DataResumo->tbPagamentosOperadorasENCONTRADA_VENDA->Value = 'S';
                    DataResumo->tbPagamentosOperadorasCOD_VENDA->Value = DataResumo->tbVendasOperadorasCODIGO->AsFloat;
                    DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->Value = DataResumo->tbVendasOperadorasAUTORIZACAO->AsString;
                    DataResumo->tbPagamentosOperadorasTOTAL_PARCELAS->Value = DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger;
                    DataResumo->tbPagamentosOperadorasNUMERO_CARTAO->Value = DataResumo->tbVendasOperadorasCARTAO->AsString;
                    DataResumo->tbPagamentosOperadorasNUMERO_TERMINAL->Value = DataResumo->tbVendasOperadorasTERMINAL->AsString;
                    DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = DataResumo->tbVendasOperadorasCOD_PRODUTO->AsInteger;
                    DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = DataResumo->tbVendasOperadorasCODIGO_MODALIDADE->AsInteger;
                    DataResumo->tbPagamentosOperadorasCOD_MEIO_CAPTURA->Value = DataResumo->tbVendasOperadorasCOD_MEIO_CAPTURA->AsInteger;
                    DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = DataResumo->tbVendasOperadorasCODIGO_MODALIDADE->AsInteger;
                    DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = DataResumo->tbVendasOperadorasCOD_PRODUTO->AsFloat;
                    DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = DataResumo->tbVendasOperadorasCOD_BANDEIRA->AsFloat;

                    DataResumo->tbPagamentosOperadoras->ApplyUpdates(0);

                    DataResumo->tbVendasOperadoras->Edit();
                    DataResumo->tbVendasOperadorasCOD_STATUS_FINANCEIRO->Value = 2;
                    DataResumo->tbVendasOperadorasVINCULADO_PAGAMENTO->Value = 'S';
                    DataResumo->tbVendasOperadorasCOD_PAGAMENTO->Value = DataResumo->tbPagamentosOperadorasCODIGO->AsFloat;
                    DataResumo->tbVendasOperadorasDATA_PAGAMENTO->Value = DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->AsDateTime;

                    DataResumo->tbVendasOperadoras->ApplyUpdates(0);
                    }
                }

            Data2->tbPagamentoStone->Edit();
            Data2->tbPagamentoStoneTRATADO->Value = 'S';
            Data2->tbPagamentoStone->ApplyUpdates(0);

            Data2->tbPagamentoStone->Next();
            contador++;

            Label6->Caption = contador;
            ProgressBar1->Position = contador;

            Application->ProcessMessages();
            }

            if(contador == (5000 * contador_contador))
            {
            Button6Click(Sender);
            contador_contador++;
            }
        }
	}
	while(final > 0);

	if(Data2->tbPagamentoStone->Active)
	{
	Data2->tbPagamentoStone->EmptyDataSet();
	}

Button6Click(Sender);

Edit2->Text = Date();
Edit3->Text = Time();
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::TratarPagamentosStoneClick(TObject *Sender)
{
int contador = 0, final = 0, posicao;
double taxa, valor_credito_original, valor_lancamento, valor_bruto;
int contador_contador;
AnsiString cnpj_cliente, dados, autorizacao, consulta, chave, data_venda, nsu, data, atualiza;
Word Year, Month, Day;
TDate dtPresent;

Label21->Caption = "Tratandos Arquivos Stone";
Label2->Caption = "Sem dados";
Label10->Caption = 0;
Label7->Caption = 0;
Label6->Caption = 0;

	do
	{
	Button6Click(Sender);

		if(Data2->tbPagamentoStone->Active)
		{
		Data2->tbPagamentoStone->EmptyDataSet();
		}

	Data2->tbPagamentoStone->Close();
	Data2->tbPagamentoStone->SQL->Clear();
	Data2->tbPagamentoStone->SQL->Add("select * from edi_stone_comprovante_pagamento where edi_stone_comprovante_pagamento.TRATADO = 'N' limit 30000");
	Data2->tbPagamentoStone->Open();

	final = 0;

		if(Data2->tbPagamentoStone->RecordCount > 0)
		{
        Label2->Caption = "Tratando Pagamentos";

		contador = 0;
		taxa = 0;
		contador_contador = 1;

		final = Data2->tbPagamentoStone->RecordCount;

		Label6->Caption = 0;
		Label7->Caption  = final;
		ProgressBar1->Max = final;

            if(!DataResumo->tbPagamentosOperadoras->Active)
			{
			DataResumo->tbPagamentosOperadoras->Close();
			DataResumo->tbPagamentosOperadoras->SQL->Clear();
			DataResumo->tbPagamentosOperadoras->SQL->Add("Select * from pagamentos_operadoras where pagamentos_operadoras.CODIGO is null");
			DataResumo->tbPagamentosOperadoras->Open();
			}
			else
			{
			DataResumo->tbPagamentosOperadoras->EmptyDataSet();
			}

			//EFETUA ESSE BLOCO ATÉ ATUALIZAR TODOS OS REGISTROS
			while(contador < final)
			{
			cnpj_cliente = "";
			autorizacao = "";
			nsu  = "";

                //VERIFICA SE É PAGAMENTO DE UMA PARCELA JÁ ANTECIPADA
                if(Data2->tbPagamentoStoneDESCONTO_ANTECIPACAO->AsFloat == 0)
                {
                Edit1->Text = Data2->tbPagamentoStoneSTONECODE->AsString;

                //LOCALIZA O CLIENTE
                consulta = "Select * from cliente_operadora where cliente_operadora.COD_ADQUIRENTE = 7";
                consulta += " and cliente_operadora.CODIGO_ESTABELECIMENTO = '" + Edit1->Text + "'";

                    if(DataResumo->tbClientesOperadoras->Active)
                    {
                    DataResumo->tbClientesOperadoras->EmptyDataSet();
                    }

                DataResumo->tbClientesOperadoras->Close();
                DataResumo->tbClientesOperadoras->SQL->Clear();
                DataResumo->tbClientesOperadoras->SQL->Add(consulta);
                DataResumo->tbClientesOperadoras->Open();

                    if(DataResumo->tbClientesOperadoras->RecordCount == 1)
                    {
                    cnpj_cliente = DataResumo->tbClientesOperadorasCNPJ_ESTABELECIMENTO->AsString;
                    }

                nsu = retirarZerosEsquerda(Data2->tbPagamentoStoneNSU->AsString);
                autorizacao = "";

                //CONTROLE DE DUPLICIDADE
                consulta = "select * from pagamentos_operadoras where pagamentos_operadoras.CODIGO is not null";
                consulta += " and pagamentos_operadoras.COD_ADQUIRENTE = 7";

                Edit1->Text = cnpj_cliente;
                consulta += " and pagamentos_operadoras.CNPJ = '" + Edit1->Text + "'";

                consulta += " and pagamentos_operadoras.PARCELA = '" + Data2->tbPagamentoStoneNUM_PARCELA->AsString + "'";
                consulta += " and pagamentos_operadoras.NSU = '" + nsu + "'";

                Edit1->Text = Data2->tbPagamentoStonePAGAMENTO_PARCELA->AsString.SubString(7,4) + "-" + Data2->tbPagamentoStonePAGAMENTO_PARCELA->AsString.SubString(4,2) + "-" + Data2->tbPagamentoStonePAGAMENTO_PARCELA->AsString.SubString(0,2);
				consulta += " and pagamentos_operadoras.DATA_PAGAMENTO = '" + Edit1->Text + "'";

                    if(DataResumo->tbPagamentosOperadoras->Active)
                    {
                    DataResumo->tbPagamentosOperadoras->EmptyDataSet();
                    }

                DataResumo->tbPagamentosOperadoras->Close();
                DataResumo->tbPagamentosOperadoras->SQL->Clear();
                DataResumo->tbPagamentosOperadoras->SQL->Add(consulta);
                DataResumo->tbPagamentosOperadoras->Open();

                    if(DataResumo->tbPagamentosOperadoras->RecordCount == 0)
                    {
                    DataResumo->tbPagamentosOperadoras->Insert();

                    DataResumo->tbPagamentosOperadorasCNPJ->Value = cnpj_cliente;
                    DataResumo->tbPagamentosOperadorasCOD_ADQUIRENTE->Value = 7;

                    //LOCALIZA O CLIENTE
                    consulta = "select * from grupos_clientes where grupos_clientes.CNPJ = '" + cnpj_cliente + "'";

                        if(Data1->tbGrupos->Active)
                        {
                        Data1->tbGrupos->EmptyDataSet();
                        }

                    Data1->tbGrupos->Close();
                    Data1->tbGrupos->SQL->Clear();
                    Data1->tbGrupos->SQL->Add(consulta);
                    Data1->tbGrupos->Open();

                        if(Data1->tbGrupos->RecordCount > 0)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_CLIENTE->Value = Data1->tbGruposCOD_CLIENTE->AsFloat;
                        DataResumo->tbPagamentosOperadorasEMPRESA->Value = Data1->tbGruposNOME_EMPRESA->AsString;
                        DataResumo->tbPagamentosOperadorasCOD_GRUPO_CLIENTE->Value = Data1->tbGruposCODIGO->AsFloat;
                        DataResumo->tbPagamentosOperadorasCNPJ->Value = cnpj_cliente;
                        }
                        else
                        {
                        DataResumo->tbPagamentosOperadorasEMPRESA->Value = "EMPRESA NÃO IDENTIFICADA";
                        }

                    DataResumo->tbPagamentosOperadorasAGENCIA->Value = retirarZerosEsquerda(Data2->tbPagamentoStoneAGENCIA->AsString);
                    DataResumo->tbPagamentosOperadorasBANCO->Value = Data2->tbPagamentoStoneBANCO->AsInteger;
                    DataResumo->tbPagamentosOperadorasCOD_BANCO->Value = StrToFloat(DataResumo->tbPagamentosOperadorasBANCO->AsFloat);
                    DataResumo->tbPagamentosOperadorasCONTA->Value = retirarZerosEsquerda(Data2->tbPagamentoStoneNUM_CONTA->AsString);

                    //NÃO CONCILIADO
                    DataResumo->tbPagamentosOperadorasCOD_STATUS->Value = 2;

                    //STATUS = NÃO LIQUIDADO
                    DataResumo->tbPagamentosOperadorasCOD_STATUS_FINANCEIRO->Value = 1;

                    DataResumo->tbPagamentosOperadorasVINCULADO_VENDA->Value = 'N';
                    DataResumo->tbPagamentosOperadorasENCONTRADA_VENDA->Value = 'N';
                    DataResumo->tbPagamentosOperadorasDUPLICIDADE_VERIFICADA->Value = 'S';
                    DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->Value = autorizacao;
                    DataResumo->tbPagamentosOperadorasNSU->Value = nsu;
                    DataResumo->tbPagamentosOperadorasNUMERO_RESUMO_VENDA->Value = Data2->tbPagamentoStoneID_PAGAMENTO->AsString;

                    DataResumo->tbPagamentosOperadorasDATA_PROCESSAMENTO->Value = Date();
                    DataResumo->tbPagamentosOperadorasHORA_PROCESSAMENTO->Value = Time();

                    DataResumo->tbPagamentosOperadorasID_LOJA->Value = Data2->tbPagamentoStoneSTONECODE->AsString;

                    DataResumo->tbPagamentosOperadorasDATA_PREV_PAG_ORIGINAL->Value = Data2->tbPagamentoStonePAGAMENTO_PARCELA->AsDateTime;
                    DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->Value = DataResumo->tbPagamentosOperadorasDATA_PREV_PAG_ORIGINAL->AsDateTime;
                    DataResumo->tbPagamentosOperadorasDATA_VENDA->Value = Data2->tbPagamentoStoneDATA_AUTORIZACAO->AsDateTime;
                    DataResumo->tbPagamentosOperadorasHORA_VENDA->Value = Data2->tbPagamentoStoneHORA_AUTORIZACAO->AsDateTime;

                    /*PAGAMENTO NORMAL
                    1 - NORMAL
                    2 - ANTECIPADO
                    */

                    DataResumo->tbPagamentosOperadorasCOD_TIPO_PAGAMENTO->Value = 1;

                    //1 - PAGAMENTO
                    DataResumo->tbPagamentosOperadorasCOD_TIPO_LANCAMENTO->Value = 1;

                    DataResumo->tbPagamentosOperadorasPARCELA->Value = Data2->tbPagamentoStoneNUM_PARCELA->AsInteger;
                    DataResumo->tbPagamentosOperadorasTOTAL_PARCELAS->Value = Data2->tbPagamentoStoneNUM_PARCELA->AsInteger;

                    valor_bruto = SimpleRoundTo(Data2->tbPagamentoStoneVALOR_BRUTO_PARCELA->AsFloat, -2);
                    DataResumo->tbPagamentosOperadorasVALOR_BRUTO->Value = StrToFloat(FormatFloat("#0.00", valor_bruto));

                    valor_bruto = SimpleRoundTo(Data2->tbPagamentoStoneVALOR_LIQUIDO_PARCELA->AsFloat, -6);
                    DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->Value = StrToFloat(FormatFloat("#0.000000", valor_bruto));

                    DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value = DataResumo->tbPagamentosOperadorasVALOR_BRUTO->AsFloat - DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->AsFloat;

                    taxa = 0;
                    taxa = DataResumo->tbPagamentosOperadorasVALOR_TAXA->AsFloat / DataResumo->tbPagamentosOperadorasVALOR_BRUTO->AsFloat;
                    taxa = taxa * 100;

                    taxa = SimpleRoundTo(taxa, -2);

                    DataResumo->tbPagamentosOperadorasTAXA_PERCENTUAL->Value = taxa;

                    //PRODUTO = NÃO IDENTIFICADO
                    DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 54;

                        //DÉBITO
                        if(Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 2 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 5
                            || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 8 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 11
                            || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 20 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 23)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 0;
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 21;
                        }
                        //CRÉDITO
                        else if(Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 3 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 6
                            || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 9 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 12
                            || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 15 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 21
                            || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 24)
                        {

                            //CRÉDITO A VISTA
                            if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 1)
                            {
                            DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 1;
                            DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 20;
                            }
                            else
                            {
                            //PARCELADO
                            DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 17;

                                //VERIFICA O PRODUTO CORRETO COM BASE NO N° DE PARCELAS
                                if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 2)
                                {
                                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 40;
                                }
                                else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 3)
                                {
                                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 41;
                                }
                                else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 4)
                                {
                                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 42;
                                }
                                else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 5)
                                {
                                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 43;
                                }
                                else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 6)
                                {
                                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 44;
                                }
                                else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 7)
                                {
                                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 45;
                                }
                                else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 8)
                                {
                                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 46;
                                }
                                else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 9)
                                {
                                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 47;
                                }
                                else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 10)
                                {
                                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 48;
                                }
                                else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 11)
                                {
                                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 50;
                                }
                                else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 12)
                                {
                                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 51;
                                }
                                else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 13)
                                {
                                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 55;
                                }
                                else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 14)
                                {
                                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 56;
                                }
                                else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 15)
                                {
                                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 57;
                                }
                                else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 16)
                                {
                                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 58;
                                }
                                else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 17)
                                {
                                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 59;
                                }
                                else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 18)
                                {
                                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 60;
                                }
                            }
                        }

                    //CONTROLE DAS BANDEIRAS

                        //MasterCard
                        if(Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 5 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 6)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 160;
                        }
                        //Visa
                        else if(Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 2 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 3)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 159;
                        }
                        //Hipercard
                        else if(Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 8 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 9)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 162;
                        }
                        //Elo
                        else if(Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 11 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 12)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 166;
                        }
                        //Amex
                        else if(Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 15)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 165;
                        }
                        //Cabal
                        else if(Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 20 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 21)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 169;
                        }
                        //Union Pay
                        else if(Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 23 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 24)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 182;
                        }


                        if(DataResumo->tbPagamentosOperadorasCOD_BANCO->AsInteger == 0 || DataResumo->tbPagamentosOperadorasCOD_CLIENTE->AsInteger == 801)
                        {
                        //SELECIONA O DOMICÍLIO BANCÁRIO DO CLIENTE
                        Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_ADQUIRENTE->AsString;
                        consulta = "select * from domicilio_cliente where domicilio_cliente.CODIGO is not null and domicilio_cliente.COD_ADQUIRENTE = '" + Edit1->Text + "'";
                        consulta += " and domicilio_cliente.CNPJ = '" + DataResumo->tbPagamentosOperadorasCNPJ->AsString + "'";

                            if(DataResumo->tbPagamentosOperadorasCONTA->AsString != "")
                            {
                            consulta += " and domicilio_cliente.CONTA = '" + DataResumo->tbPagamentosOperadorasCONTA->AsString + "'";
                            }

                            if(Data1->tbDomicilioCliente->Active)
                            {
                            Data1->tbDomicilioCliente->EmptyDataSet();
                            }

                        Data1->tbDomicilioCliente->Close();
                        Data1->tbDomicilioCliente->SQL->Clear();
                        Data1->tbDomicilioCliente->SQL->Add(consulta);
                        Data1->tbDomicilioCliente->Open();

                            if(Data1->tbDomicilioCliente->RecordCount == 1)
                            {
                            DataResumo->tbPagamentosOperadorasBANCO->Value = Data1->tbDomicilioClienteCOD_BANCO->AsString;
                            DataResumo->tbPagamentosOperadorasCOD_BANCO->Value = DataResumo->tbPagamentosOperadorasBANCO->AsInteger;
                            DataResumo->tbPagamentosOperadorasAGENCIA->Value = Data1->tbDomicilioClienteAGENCIA->AsString;
                            DataResumo->tbPagamentosOperadorasCONTA->Value = Data1->tbDomicilioClienteCONTA->AsString;
                            }
                        }

                    //COMPLETA A CHAVE NO PADRÃO
                    //cod_cliente-cod_operadora-data_venda_formato_americano-Parcela_atual-total_parcelas_NSU_AUTORIZAÇÃO-cod_Bandeira-cod_modalidade

                    Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_CLIENTE->AsFloat;
                    chave = Edit1->Text;

                        //VERIFICA SE FOI INFORMADA A OPERADORA
                        if(DataResumo->tbPagamentosOperadorasCOD_ADQUIRENTE->AsFloat > 0)
                        {
                        Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_ADQUIRENTE->AsFloat;
                        chave += "-" + Edit1->Text;
                        }

                    dtPresent = DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->AsDateTime;
                    DecodeDate(dtPresent, Year, Month, Day);

                    Edit1->Text = Year;
                    data_venda = Edit1->Text + "-";
                    Edit1->Text = Month;
                    data_venda = data_venda + Edit1->Text + "-";
                    Edit1->Text = Day;
                    data_venda = data_venda + Edit1->Text;

                    Edit1->Text = data_venda;

                    chave += "-" + Edit1->Text;

                    //COMPLETA A PARCELA ATUAL
                    Edit1->Text = DataResumo->tbPagamentosOperadorasPARCELA->AsFloat;

                    chave += "-" + Edit1->Text;

                    //COMPLETA O CAMPO TOTAL DE PARCELAS
                    Edit1->Text = DataResumo->tbPagamentosOperadorasTOTAL_PARCELAS->AsFloat;
                    chave += "-" + Edit1->Text;

                        //VERIFICA SE A VENDA POSSUI NSU
                        if(DataResumo->tbPagamentosOperadorasNSU->AsString != "")
                        {
                        chave += "-" + DataResumo->tbPagamentosOperadorasNSU->AsString;
                        }

                        //VERIFICA SE A VENDA POSSUI AUTORIZAÇÃO
                        if(DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->AsString != "")
                        {
                        chave += "-" + DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->AsString;
                        }

                        if(DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->AsFloat > 0)
                        {
                        Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->AsFloat;
                        chave += "-" + Edit1->Text;
                        }

                    DataResumo->tbPagamentosOperadorasCHAVE_PAGAMENTO->Value = chave;

                    DataResumo->tbPagamentosOperadoras->ApplyUpdates(0);

                    atualiza = "update pagamentos_operadoras set pagamentos_operadoras.VALOR_LIQUIDO = ROUND(pagamentos_operadoras.VALOR_LIQUIDO, 6), pagamentos_operadoras.VALOR_BRUTO = ROUND(pagamentos_operadoras.VALOR_BRUTO, 2) ";
                    atualiza += " where pagamentos_operadoras.CODIGO = " + DataResumo->tbPagamentosOperadorasCODIGO->AsString;

                    Data1->tbExcluir->Close();
                    Data1->tbExcluir->SQL->Clear();
                    Data1->tbExcluir->SQL->Add(atualiza);
                    Data1->tbExcluir->ExecSQL();

                    //TENTA LOCALIZAR A VENDA
                    consulta = "SELECT * FROM vendas where vendas.COD_STATUS_FINANCEIRO = '1' and vendas.CNPJ = '" + cnpj_cliente + "'";
                    consulta += " and vendas.ADQID = 7";

                    consulta += " and vendas.PARCELA = '" + DataResumo->tbPagamentosOperadorasPARCELA->AsString + "'";
                    consulta += " and vendas.NSU = '" + nsu + "'";

                    Edit1->Text = Data2->tbPagamentoStoneDATA_AUTORIZACAO->AsString.SubString(7,4) + "-" + Data2->tbPagamentoStoneDATA_AUTORIZACAO->AsString.SubString(4,2) + "-" + Data2->tbPagamentoStoneDATA_AUTORIZACAO->AsString.SubString(0,2);

                    consulta += " and vendas.DATA_VENDA = '" + Edit1->Text + "'";

                        if(DataResumo->tbVendasOperadoras->Active)
                        {
                        DataResumo->tbVendasOperadoras->EmptyDataSet();
                        }

                    DataResumo->tbVendasOperadoras->Close();
                    DataResumo->tbVendasOperadoras->SQL->Clear();
                    DataResumo->tbVendasOperadoras->SQL->Add(consulta);
                    DataResumo->tbVendasOperadoras->Open();

                        if(DataResumo->tbVendasOperadoras->RecordCount == 1)
                        {
                        DataResumo->tbPagamentosOperadoras->Edit();

                        //CONCILIADA
                        DataResumo->tbPagamentosOperadorasCOD_STATUS->Value = 1;

                        //STATUS = LIQUIDADO
                        DataResumo->tbPagamentosOperadorasCOD_STATUS_FINANCEIRO->Value = 2;

                        DataResumo->tbPagamentosOperadorasVINCULADO_VENDA->Value = 'S';
                        DataResumo->tbPagamentosOperadorasENCONTRADA_VENDA->Value = 'S';
                        DataResumo->tbPagamentosOperadorasCOD_VENDA->Value = DataResumo->tbVendasOperadorasCODIGO->AsFloat;
                        DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->Value = DataResumo->tbVendasOperadorasAUTORIZACAO->AsString;
                        DataResumo->tbPagamentosOperadorasTOTAL_PARCELAS->Value = DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger;
                        DataResumo->tbPagamentosOperadorasNUMERO_CARTAO->Value = DataResumo->tbVendasOperadorasCARTAO->AsString;
                        DataResumo->tbPagamentosOperadorasNUMERO_TERMINAL->Value = DataResumo->tbVendasOperadorasTERMINAL->AsString;
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = DataResumo->tbVendasOperadorasCOD_PRODUTO->AsInteger;
                        DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = DataResumo->tbVendasOperadorasCODIGO_MODALIDADE->AsInteger;
                        DataResumo->tbPagamentosOperadorasCOD_MEIO_CAPTURA->Value = DataResumo->tbVendasOperadorasCOD_MEIO_CAPTURA->AsInteger;
                        DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = DataResumo->tbVendasOperadorasCOD_BANDEIRA->AsFloat;

                        DataResumo->tbPagamentosOperadoras->ApplyUpdates(0);

                        DataResumo->tbVendasOperadoras->Edit();
                        DataResumo->tbVendasOperadorasCOD_STATUS_FINANCEIRO->Value = 2;
                        DataResumo->tbVendasOperadorasVINCULADO_PAGAMENTO->Value = 'S';
                        DataResumo->tbVendasOperadorasCOD_PAGAMENTO->Value = DataResumo->tbPagamentosOperadorasCODIGO->AsFloat;
                        DataResumo->tbVendasOperadorasDATA_PAGAMENTO->Value = DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->AsDateTime;

                        DataResumo->tbVendasOperadoras->ApplyUpdates(0);
                        }
                    }

                Data2->tbPagamentoStone->Edit();
                Data2->tbPagamentoStoneTRATADO->Value = 'S';
                Data2->tbPagamentoStone->ApplyUpdates(0);
                }
                else
                {
                Data2->tbPagamentoStone->Edit();
                Data2->tbPagamentoStoneTRATADO->Value = 'A';
                Data2->tbPagamentoStone->ApplyUpdates(0);
                }

			Data2->tbPagamentoStone->Next();
            contador++;

			Application->ProcessMessages();

			Label6->Caption = contador;
			ProgressBar1->Position = contador;

				if(contador == (5000 * contador_contador))
				{
				Button6Click(Sender);
				contador_contador++;
				}
            }
        }
	}
	while(final > 0);

	if(Data2->tbPagamentoStone->Active)
	{
	Data2->tbPagamentoStone->EmptyDataSet();
	}

Button6Click(Sender);

Edit2->Text = Date();
Edit3->Text = Time();
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::TratarAjustesStoneClick(TObject *Sender)
{
int contador = 0, final = 0, posicao;
double taxa, valor_taxa_total, valor_bruto_total;
double valor_credito_original, valor_lancamento;
int contador_contador;
bool cancelamento = false;
AnsiString cnpj_cliente, dados, autorizacao, consulta, chave, data_venda, nsu, data;
Word Year, Month, Day;
TDate dtPresent;

Label21->Caption = "Tratandos Arquivos Stone";
Label2->Caption = "Sem dados";
Label10->Caption = 0;
Label7->Caption = 0;
Label6->Caption = 0;

	do
	{
	Button6Click(Sender);

		if(Data2->tbEventoStone->Active)
		{
		Data2->tbEventoStone->EmptyDataSet();
		}

	Data2->tbEventoStone->Close();
	Data2->tbEventoStone->SQL->Clear();
	Data2->tbEventoStone->SQL->Add("select * from edi_stone_evento_financeiro where edi_stone_evento_financeiro.TRATADO = 'N' limit 30000");
	Data2->tbEventoStone->Open();

	final = 0;

		if(Data2->tbEventoStone->RecordCount > 0)
		{
        Label2->Caption = "Tratando Ajustes";

		contador = 0;
		taxa = 0;
		contador_contador = 1;

		final = Data2->tbEventoStone->RecordCount;

		Label6->Caption = 0;
		Label7->Caption  = final;
		ProgressBar1->Max = final;

			if(!DataResumo->tbPagamentosOperadoras->Active)
			{
			DataResumo->tbPagamentosOperadoras->Close();
			DataResumo->tbPagamentosOperadoras->SQL->Clear();
			DataResumo->tbPagamentosOperadoras->SQL->Add("Select * from pagamentos_operadoras where pagamentos_operadoras.CODIGO is null");
			DataResumo->tbPagamentosOperadoras->Open();
			}
			else
			{
			DataResumo->tbPagamentosOperadoras->EmptyDataSet();
			}

			//EFETUA ESSE BLOCO ATÉ ATUALIZAR TODOS OS REGISTROS
			while(contador < final)
			{
            	if(Data2->tbEventoStoneDATA_COBRANCA->AsString != "")
                {
                cnpj_cliente = "";
                autorizacao = "";
                nsu  = "";

                Edit1->Text = Data2->tbEventoStoneSTONECODE->AsString;
                //LOCALIZA O CLIENTE
                consulta = "Select * from cliente_operadora where cliente_operadora.COD_ADQUIRENTE = 7 and cliente_operadora.CODIGO_ESTABELECIMENTO = '" + Edit1->Text + "'";

                    if(DataResumo->tbClientesOperadoras->Active)
                    {
                    DataResumo->tbClientesOperadoras->EmptyDataSet();
                    }

                DataResumo->tbClientesOperadoras->Close();
                DataResumo->tbClientesOperadoras->SQL->Clear();
                DataResumo->tbClientesOperadoras->SQL->Add(consulta);
                DataResumo->tbClientesOperadoras->Open();

                    if(DataResumo->tbClientesOperadoras->RecordCount == 1)
                    {
                    cnpj_cliente = DataResumo->tbClientesOperadorasCNPJ_ESTABELECIMENTO->AsString;
                    }

                //LOCALIZA O CLIENTE
                consulta = "select * from grupos_clientes where grupos_clientes.CNPJ = '" + cnpj_cliente + "'";

                    if(Data1->tbGrupos->Active)
                    {
                    Data1->tbGrupos->EmptyDataSet();
                    }

                Data1->tbGrupos->Close();
                Data1->tbGrupos->SQL->Clear();
                Data1->tbGrupos->SQL->Add(consulta);
                Data1->tbGrupos->Open();

                DataResumo->tbPagamentosOperadoras->Insert();

                DataResumo->tbPagamentosOperadorasCNPJ->Value = cnpj_cliente;
                DataResumo->tbPagamentosOperadorasCOD_ADQUIRENTE->Value = 7;

                    if(Data1->tbGrupos->RecordCount > 0)
                    {
                    DataResumo->tbPagamentosOperadorasCOD_CLIENTE->Value = Data1->tbGruposCOD_CLIENTE->AsFloat;
                    DataResumo->tbPagamentosOperadorasEMPRESA->Value = Data1->tbGruposNOME_EMPRESA->AsString;
                    DataResumo->tbPagamentosOperadorasCOD_GRUPO_CLIENTE->Value = Data1->tbGruposCODIGO->AsFloat;
                    DataResumo->tbPagamentosOperadorasCNPJ->Value = cnpj_cliente;
                    }
                    else
                    {
                    DataResumo->tbPagamentosOperadorasEMPRESA->Value = "EMPRESA NÃO IDENTIFICADA";
                    }

                DataResumo->tbPagamentosOperadorasAGENCIA->Value = retirarZerosEsquerda(Data2->tbEventoStoneAGENCIA->AsString);

                    if(Data2->tbEventoStoneBANCO->AsString != "")
                    {
                    DataResumo->tbPagamentosOperadorasBANCO->Value = StrToInt(Data2->tbEventoStoneBANCO->AsString);
                    DataResumo->tbPagamentosOperadorasCOD_BANCO->Value = StrToFloat(DataResumo->tbPagamentosOperadorasBANCO->AsFloat);
                    }

                DataResumo->tbPagamentosOperadorasCONTA->Value = retirarZerosEsquerda(Data2->tbEventoStoneNUM_CONTA->AsString);

                //CONCILIADO
                DataResumo->tbPagamentosOperadorasCOD_STATUS->Value = 1;

                //STATUS = LIQUIDADO
                DataResumo->tbPagamentosOperadorasCOD_STATUS_FINANCEIRO->Value = 2;

                DataResumo->tbPagamentosOperadorasVINCULADO_VENDA->Value = 'N';
                DataResumo->tbPagamentosOperadorasENCONTRADA_VENDA->Value = 'N';
                DataResumo->tbPagamentosOperadorasDUPLICIDADE_VERIFICADA->Value = 'S';

                DataResumo->tbPagamentosOperadorasDATA_PROCESSAMENTO->Value = Date();
                DataResumo->tbPagamentosOperadorasHORA_PROCESSAMENTO->Value = Time();

                DataResumo->tbPagamentosOperadorasID_LOJA->Value = Data2->tbEventoStoneSTONECODE->AsString;

                    if(Data2->tbEventoStoneDATA_COBRANCA->AsString != "")
                    {
                    DataResumo->tbPagamentosOperadorasDATA_PREV_PAG_ORIGINAL->Value = Data2->tbEventoStoneDATA_COBRANCA->AsDateTime;
                    }
                    else
                    {
                    DataResumo->tbPagamentosOperadorasDATA_PREV_PAG_ORIGINAL->Value = Data2->tbEventoStonePREVISAO_COBRANCA->AsDateTime;
                    }

                DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->Value = DataResumo->tbPagamentosOperadorasDATA_PREV_PAG_ORIGINAL->AsDateTime;

                /*PAGAMENTO NORMAL
                1 - NORMAL
                2 - ANTECIPADO
                */

                DataResumo->tbPagamentosOperadorasCOD_TIPO_PAGAMENTO->Value = 1;

                DataResumo->tbPagamentosOperadorasVALOR_BRUTO->Value = Data2->tbEventoStoneVALOR_EVENTO->AsFloat;
                DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->Value = Data2->tbEventoStoneVALOR_EVENTO->AsFloat;
                DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value = 0;
                DataResumo->tbPagamentosOperadorasTAXA_PERCENTUAL->Value = 0;
                DataResumo->tbPagamentosOperadorasOBSERVACOES->Value = Data2->tbEventoStoneCODE_TRANSFERENCIA_INTERNA->AsString;
                DataResumo->tbPagamentosOperadorasNUMERO_OPERACAO_ANTECIPACAO->Value = Data2->tbEventoStoneCODIGO_EVENTO->AsString;
                DataResumo->tbPagamentosOperadorasNUMERO_RESUMO_VENDA->Value = Data2->tbEventoStoneID_PAGAMENTO->AsString;

                    if(DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->AsFloat < 0)
                    {
                    //DÉBITO
                    DataResumo->tbPagamentosOperadorasCOD_TIPO_LANCAMENTO->Value = 2;
                    }
                    else
                    {
                    //CRÉDITO
                    DataResumo->tbPagamentosOperadorasCOD_TIPO_LANCAMENTO->Value = 3;
                    }

                //PRODUTO = NÃO IDENTIFICADO
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 54;

                    //DÉBITO
                    if(Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 2 || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 5
                        || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 8 || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 11
                        || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 20 || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 23)
                    {
                    DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 0;
                    DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 21;
                    }
                    //CRÉDITO
                    else if(Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 3 || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 6
                        || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 9 || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 12
                        || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 15 || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 21
                        || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 24)
                    {
                    //CRÉDITO A VISTA

                    DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 1;
                    DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 20;
                    }

                //CONTROLE DAS BANDEIRAS

                    //MasterCard
                    if(Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 5 || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 6)
                    {
                    DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 160;
                    }
                    //Visa
                    else if(Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 2 || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 3)
                    {
                    DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 159;
                    }
                    //Hipercard
                    else if(Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 8 || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 9)
                    {
                    DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 162;
                    }
                    //Elo
                    else if(Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 11 || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 12)
                    {
                    DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 166;
                    }
                    //Amex
                    else if(Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 15)
                    {
                    DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 165;
                    }
                    //Cabal
                    else if(Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 20 || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 21)
                    {
                    DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 169;
                    }
                    //Union Pay
                    else if(Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 23 || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 24)
                    {
                    DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 182;
                    }

                //LOCALIZA O CÓDIGO DO AJUSTE
                consulta = "select * from controle_ajustes where controle_ajustes.CODIGO is not null";
                consulta += " and controle_ajustes.COD_ADQUIRENTE = 7";
                consulta += " and controle_ajustes.CODIGO_OPERADORA = '" + Data2->tbEventoStoneTIPO_EVENTO->AsString + "'";

                    if(Data1->tbControleAjustes->Active)
                    {
                    Data1->tbControleAjustes->EmptyDataSet();
                    }

                Data1->tbControleAjustes->Close();
                Data1->tbControleAjustes->SQL->Clear();
                Data1->tbControleAjustes->SQL->Add(consulta);
                Data1->tbControleAjustes->Open();

                    if(Data1->tbControleAjustes->RecordCount > 0)
                    {
                    DataResumo->tbPagamentosOperadorasCOD_AJUSTE->Value = Data1->tbControleAjustesCODIGO->AsFloat;
                    }

                    if(DataResumo->tbPagamentosOperadorasCOD_BANCO->AsInteger == 0 || DataResumo->tbPagamentosOperadorasCOD_CLIENTE->AsInteger == 801)
                    {
                    //SELECIONA O DOMICÍLIO BANCÁRIO DO CLIENTE
                    Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_ADQUIRENTE->AsString;
                    consulta = "select * from domicilio_cliente where domicilio_cliente.CODIGO is not null and domicilio_cliente.COD_ADQUIRENTE = '" + Edit1->Text + "'";
                    Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_CLIENTE->AsString;
                    consulta += " and domicilio_cliente.COD_CLIENTE = '" + Edit1->Text + "'";
                    consulta += " and domicilio_cliente.CNPJ = '" + DataResumo->tbPagamentosOperadorasCNPJ->AsString + "'";

                    	if(DataResumo->tbPagamentosOperadorasCONTA->AsString != "")
                        {
                        consulta += " and domicilio_cliente.CONTA = '" + DataResumo->tbPagamentosOperadorasCONTA->AsString + "'";
                        }

                        if(Data1->tbDomicilioCliente->Active)
                        {
                        Data1->tbDomicilioCliente->EmptyDataSet();
                        }

                    Data1->tbDomicilioCliente->Close();
                    Data1->tbDomicilioCliente->SQL->Clear();
                    Data1->tbDomicilioCliente->SQL->Add(consulta);
                    Data1->tbDomicilioCliente->Open();

                        if(Data1->tbDomicilioCliente->RecordCount == 1)
                        {
                        DataResumo->tbPagamentosOperadorasBANCO->Value = Data1->tbDomicilioClienteCOD_BANCO->AsString;
                        DataResumo->tbPagamentosOperadorasCOD_BANCO->Value = DataResumo->tbPagamentosOperadorasBANCO->AsInteger;
                        DataResumo->tbPagamentosOperadorasAGENCIA->Value = Data1->tbDomicilioClienteAGENCIA->AsString;
                        DataResumo->tbPagamentosOperadorasCONTA->Value = Data1->tbDomicilioClienteCONTA->AsString;
                        }
                    }

                //CONTROLE DE DUPLICIDADE
                consulta = "select * from pagamentos_operadoras where pagamentos_operadoras.CODIGO is not null";
                consulta += " and pagamentos_operadoras.COD_ADQUIRENTE = 7";

                Edit1->Text = cnpj_cliente;
                consulta += " and pagamentos_operadoras.CNPJ = '" + Edit1->Text + "'";

                consulta += " and pagamentos_operadoras.COD_TIPO_LANCAMENTO = '" + DataResumo->tbPagamentosOperadorasCOD_TIPO_LANCAMENTO->AsString + "'";
                consulta += " and pagamentos_operadoras.COD_AJUSTE = '" + DataResumo->tbPagamentosOperadorasCOD_AJUSTE->AsString + "'";

                Edit1->Text = DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->AsString.SubString(7,4) + "-" + DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->AsString.SubString(4,2) + "-" + DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->AsString.SubString(0,2);
                consulta += " and pagamentos_operadoras.DATA_PAGAMENTO = '" + Edit1->Text + "'";

                Edit1->Text = alterarVirgulaPorPonto(DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->AsString);
                consulta += " and pagamentos_operadoras.VALOR_LIQUIDO = '" + Edit1->Text + "'";

                Edit1->Text = DataResumo->tbPagamentosOperadorasNUMERO_OPERACAO_ANTECIPACAO->AsString;
                consulta += " and pagamentos_operadoras.NUMERO_OPERACAO_ANTECIPACAO = '" + Edit1->Text + "'";

                    if(Data1->tbPagamentosOperadoras->Active)
                    {
                    Data1->tbPagamentosOperadoras->EmptyDataSet();
                    }

                Data1->tbPagamentosOperadoras->Close();
                Data1->tbPagamentosOperadoras->SQL->Clear();
                Data1->tbPagamentosOperadoras->SQL->Add(consulta);
                Data1->tbPagamentosOperadoras->Open();

                    if(Data1->tbPagamentosOperadoras->RecordCount == 0)
                    {
                    //COMPLETA A CHAVE NO PADRÃO
                    //cod_cliente-cod_operadora-data_venda_formato_americano-Parcela_atual-total_parcelas_NSU_AUTORIZAÇÃO-cod_Bandeira-cod_modalidade

                    Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_CLIENTE->AsFloat;
                    chave = Edit1->Text;

                        //VERIFICA SE FOI INFORMADA A OPERADORA
                        if(DataResumo->tbPagamentosOperadorasCOD_ADQUIRENTE->AsFloat > 0)
                        {
                        Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_ADQUIRENTE->AsFloat;
                        chave += "-" + Edit1->Text;
                        }

                    dtPresent = DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->AsDateTime;
                    DecodeDate(dtPresent, Year, Month, Day);

                    Edit1->Text = Year;
                    data_venda = Edit1->Text + "-";
                    Edit1->Text = Month;
                    data_venda = data_venda + Edit1->Text + "-";
                    Edit1->Text = Day;
                    data_venda = data_venda + Edit1->Text;

                    Edit1->Text = data_venda;

                    chave += "-" + Edit1->Text;

                    //COMPLETA A PARCELA ATUAL
                    Edit1->Text = DataResumo->tbPagamentosOperadorasPARCELA->AsFloat;

                    chave += "-" + Edit1->Text;

                    //COMPLETA O CAMPO TOTAL DE PARCELAS
                    Edit1->Text = DataResumo->tbPagamentosOperadorasTOTAL_PARCELAS->AsFloat;
                    chave += "-" + Edit1->Text;

                        //VERIFICA SE A VENDA POSSUI NSU
                        if(DataResumo->tbPagamentosOperadorasNSU->AsString != "")
                        {
                        chave += "-" + DataResumo->tbPagamentosOperadorasNSU->AsString;
                        }

                        //VERIFICA SE A VENDA POSSUI AUTORIZAÇÃO
                        if(DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->AsString != "")
                        {
                        chave += "-" + DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->AsString;
                        }

                        if(DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->AsFloat > 0)
                        {
                        Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->AsFloat;
                        chave += "-" + Edit1->Text;
                        }

                    DataResumo->tbPagamentosOperadorasCHAVE_PAGAMENTO->Value = chave;

                    DataResumo->tbPagamentosOperadoras->ApplyUpdates(0);
                    }
                    else
                    {
                    DataResumo->tbPagamentosOperadoras->Cancel();
                    }
                }


			contador++;

			Data2->tbEventoStone->Edit();
			Data2->tbEventoStoneTRATADO->Value = 'S';
			Data2->tbEventoStone->ApplyUpdates(0);

			Data2->tbEventoStone->Next();

			Application->ProcessMessages();

			Label6->Caption = contador;
			ProgressBar1->Position = contador;

				if(contador == (5000 * contador_contador))
				{
				Button6Click(Sender);
				contador_contador++;
				}
			}
		}
	}
	while(final > 0);

	if(Data2->tbEventoStone->Active)
	{
	Data2->tbEventoStone->EmptyDataSet();
	}

Button6Click(Sender);

Edit2->Text = Date();
Edit3->Text = Time();
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::Stone5Click(TObject *Sender)
{
Button17Click(Sender);
TratarVendasStoneClick(Sender);
TratarAntecipacoesStoneClick(Sender);
TratarPagamentosStoneClick(Sender);
TratarAjustesStoneClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::MarcarDadosBrutosparaTRATADON2Click(TObject *Sender)
{
	//VERIFICA SE O USUÁRIO DESEJA REALMENTE EXCLUIR TODOS OS DADOS DA OPERADORA
	if(Application->MessageBoxA(L"Deseja realmente marcar os dados da operadora Stone para TRATADO = 'N'?",L"Mensagem do Sistema",MB_YESNO) == ID_YES)
	{
	Data1->tbExcluir->Close();
	Data1->tbExcluir->SQL->Clear();
	Data1->tbExcluir->SQL->Add("update edi_stone_comprovante_venda set edi_stone_comprovante_venda.TRATADO = 'N'");
	Data1->tbExcluir->ExecSQL();

    Data1->tbExcluir->Close();
	Data1->tbExcluir->SQL->Clear();
	Data1->tbExcluir->SQL->Add("update edi_stone_comprovante_pagamento set edi_stone_comprovante_pagamento.TRATADO = 'N'");
	Data1->tbExcluir->ExecSQL();

    Data1->tbExcluir->Close();
	Data1->tbExcluir->SQL->Clear();
	Data1->tbExcluir->SQL->Add("update edi_stone_evento_financeiro set edi_stone_evento_financeiro.TRATADO = 'N'");
	Data1->tbExcluir->ExecSQL();

    Data1->tbExcluir->Close();
	Data1->tbExcluir->SQL->Clear();
	Data1->tbExcluir->SQL->Add("update edi_stone_cancelamento set edi_stone_cancelamento.TRATADO = 'N'");
	Data1->tbExcluir->ExecSQL();
	}
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::ExcluirDadosBrutos9Click(TObject *Sender)
{
	//VERIFICA SE O USUÁRIO DESEJA REALMENTE EXCLUIR TODOS OS DADOS DA OPERADORA
	if(Application->MessageBoxA(L"Deseja realmente excluir os dados da operadora Stone ?",L"Mensagem do Sistema",MB_YESNO) == ID_YES)
	{
	Data1->tbExcluir->Close();
	Data1->tbExcluir->SQL->Clear();
	Data1->tbExcluir->SQL->Add("delete from edi_stone_header ");
	Data1->tbExcluir->ExecSQL();

	Data1->tbExcluir->Close();
	Data1->tbExcluir->SQL->Clear();
	Data1->tbExcluir->SQL->Add("delete from edi_stone_comprovante_pagamento ");
	Data1->tbExcluir->ExecSQL();

	Data1->tbExcluir->Close();
	Data1->tbExcluir->SQL->Clear();
	Data1->tbExcluir->SQL->Add("delete from edi_stone_comprovante_venda ");
	Data1->tbExcluir->ExecSQL();

	Data1->tbExcluir->Close();
	Data1->tbExcluir->SQL->Clear();
	Data1->tbExcluir->SQL->Add("delete from edi_stone_cancelamento");
	Data1->tbExcluir->ExecSQL();

	Data1->tbExcluir->Close();
	Data1->tbExcluir->SQL->Clear();
	Data1->tbExcluir->SQL->Add("delete from edi_stone_evento_financeiro");
	Data1->tbExcluir->ExecSQL();
    }
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::ExcluirVendas10Click(TObject *Sender)
{
	//VERIFICA SE O USUÁRIO DESEJA REALMENTE EXCLUIR TODOS OS DADOS DA OPERADORA
	if(Application->MessageBoxA(L"Deseja realmente excluir os dados de vendas da operadora Stone ?",L"Mensagem do Sistema",MB_YESNO) == ID_YES)
	{
	Data1->tbExcluir->Close();
	Data1->tbExcluir->SQL->Clear();
	Data1->tbExcluir->SQL->Add("delete from vendas where vendas.ADQID = 7");
	Data1->tbExcluir->ExecSQL();
	}
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::ExcluirPagamentos10Click(TObject *Sender)
{
	//VERIFICA SE O USUÁRIO DESEJA REALMENTE EXCLUIR TODOS OS DADOS DA OPERADORA
	if(Application->MessageBoxA(L"Deseja realmente excluir os dados de pagamento da operadora Stone ?",L"Mensagem do Sistema",MB_YESNO) == ID_YES)
	{
	Data1->tbExcluir->Close();
	Data1->tbExcluir->SQL->Clear();
	Data1->tbExcluir->SQL->Add("delete from pagamentos_operadoras where pagamentos_operadoras.COD_ADQUIRENTE = 7");
	Data1->tbExcluir->ExecSQL();
	}
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::Excluirduplicidadedevendas1Click(TObject *Sender)
{
Label21->Caption = "Excluir duplicidades stone - Venda";

AnsiString consulta;

consulta = "select vendas.NSU, vendas.PARCELA, vendas.AUTORIZACAO, vendas.DATA_VENDA, vendas.CNPJ, count(vendas.CODIGO) as total";
consulta += " from vendas where vendas.ADQID = 7";
consulta += " group by vendas.NSU, vendas.PARCELA, vendas.AUTORIZACAO, vendas.DATA_VENDA, vendas.CNPJ";
consulta += " HAVING COUNT(vendas.CODIGO) > 1";

DataProcessamento->tbVendasDuplicidade->Close();
DataProcessamento->tbVendasDuplicidade->SQL->Clear();
DataProcessamento->tbVendasDuplicidade->SQL->Add(consulta);
DataProcessamento->tbVendasDuplicidade->Open();

DataProcessamento->tbVendasDuplicidade->Last();
int final = DataProcessamento->tbVendasDuplicidade->RecordCount;
DataProcessamento->tbVendasDuplicidade->First();

Label6->Caption = 0;
Label7->Caption = final;
ProgressBar1->Position = 0;
ProgressBar1->Max = final;

Application->ProcessMessages();

	for(int contador = 0; contador < final; contador++)
    {
    //TENTA LOCALIZAR A VENDA
    consulta = "SELECT * FROM vendas where vendas.COD_STATUS_FINANCEIRO = '1'";
    consulta += " and vendas.CNPJ = '" + DataProcessamento->tbVendasDuplicidadeCNPJ->AsString + "'";
    consulta += " and vendas.ADQID = 7";

    consulta += " and vendas.PARCELA = '" + DataProcessamento->tbVendasDuplicidadePARCELA->AsString + "'";
    consulta += " and vendas.NSU = '" + DataProcessamento->tbVendasDuplicidadeNSU->AsString + "'";

    Edit1->Text = DataProcessamento->tbVendasDuplicidadeDATA_VENDA->AsString.SubString(7,4) + "-" + DataProcessamento->tbVendasDuplicidadeDATA_VENDA->AsString.SubString(4,2) + "-" + DataProcessamento->tbVendasDuplicidadeDATA_VENDA->AsString.SubString(0,2);

    consulta += " and vendas.DATA_VENDA = '" + Edit1->Text + "'";

    DataResumo->tbVendasOperadoras->Close();
    DataResumo->tbVendasOperadoras->SQL->Clear();
    DataResumo->tbVendasOperadoras->SQL->Add(consulta);
    DataResumo->tbVendasOperadoras->Open();

        if(DataResumo->tbVendasOperadoras->RecordCount > 0)
        {
        DataResumo->tbVendasOperadoras->Last();

        DataResumo->tbVendasOperadoras->Delete();
        DataResumo->tbVendasOperadoras->ApplyUpdates(0);
        }

    DataProcessamento->tbVendasDuplicidade->Next();
    Label6->Caption = contador + 1;
    Application->ProcessMessages();
    }
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::Excluirduplicidadedepagamentos1Click(TObject *Sender)

{
Label21->Caption = "Excluir duplicidades stone - pagamentos";

AnsiString consulta;

consulta = "select pagamentos_operadoras.NSU, pagamentos_operadoras.PARCELA, pagamentos_operadoras.DATA_PAGAMENTO, pagamentos_operadoras.CNPJ, count(pagamentos_operadoras.CODIGO) as total";
consulta += " from pagamentos_operadoras where pagamentos_operadoras.COD_ADQUIRENTE = 7";
consulta += " group by pagamentos_operadoras.NSU, pagamentos_operadoras.PARCELA, pagamentos_operadoras.DATA_PAGAMENTO, pagamentos_operadoras.CNPJ";
consulta += " HAVING COUNT(pagamentos_operadoras.CODIGO) > 1";

DataProcessamento->tbPagamentosDuplicidade->Close();
DataProcessamento->tbPagamentosDuplicidade->SQL->Clear();
DataProcessamento->tbPagamentosDuplicidade->SQL->Add(consulta);
DataProcessamento->tbPagamentosDuplicidade->Open();

DataProcessamento->tbPagamentosDuplicidade->Last();
int final = DataProcessamento->tbPagamentosDuplicidade->RecordCount;
DataProcessamento->tbPagamentosDuplicidade->First();

Label6->Caption = 0;
Label7->Caption = final;
ProgressBar1->Position = 0;
ProgressBar1->Max = final;

Application->ProcessMessages();

	for(int contador = 0; contador < final; contador++)
    {
    //TENTA LOCALIZAR A VENDA
    consulta = "SELECT * FROM pagamentos_operadoras where pagamentos_operadoras.CNPJ = '" + DataProcessamento->tbPagamentosDuplicidadeCNPJ->AsString + "'";
    consulta += " and pagamentos_operadoras.COD_ADQUIRENTE = 7";

    consulta += " and pagamentos_operadoras.PARCELA = '" + DataProcessamento->tbPagamentosDuplicidadePARCELA->AsString + "'";
    consulta += " and pagamentos_operadoras.NSU = '" + DataProcessamento->tbPagamentosDuplicidadeNSU->AsString + "'";

    Edit1->Text = DataProcessamento->tbPagamentosDuplicidadeDATA_PAGAMENTO->AsString.SubString(7,4) + "-" + DataProcessamento->tbPagamentosDuplicidadeDATA_PAGAMENTO->AsString.SubString(4,2) + "-" + DataProcessamento->tbPagamentosDuplicidadeDATA_PAGAMENTO->AsString.SubString(0,2);

    consulta += " and pagamentos_operadoras.DATA_PAGAMENTO = '" + Edit1->Text + "'";

    DataResumo->tbPagamentosOperadoras->Close();
    DataResumo->tbPagamentosOperadoras->SQL->Clear();
    DataResumo->tbPagamentosOperadoras->SQL->Add(consulta);
    DataResumo->tbPagamentosOperadoras->Open();

        if(DataResumo->tbPagamentosOperadoras->RecordCount > 0)
        {
            if(DataResumo->tbPagamentosOperadorasVINCULADO_VENDA->AsString == "S")
            {
            DataResumo->tbPagamentosOperadoras->Last();
            }

        DataResumo->tbPagamentosOperadoras->Delete();
        DataResumo->tbPagamentosOperadoras->ApplyUpdates(0);
        }

    DataProcessamento->tbPagamentosDuplicidade->Next();
    Label6->Caption = contador + 1;
    Application->ProcessMessages();
    }
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::Atualizardadosbancriosvenda1Click(TObject *Sender)
{
Label21->Caption = "Atualizando dados bancários - Stone";
Label2->Caption = "";
Label10->Caption = 0;
Label7->Caption = 0;
Label6->Caption = 0;

AnsiString consulta;
bool continuar_domicilio;

//seleciona as vendas
DataResumo->tbVendasOperadoras->Close();
DataResumo->tbVendasOperadoras->SQL->Clear();
DataResumo->tbVendasOperadoras->SQL->Add("select * from vendas where vendas.ADQID = 7 and vendas.BANCO is null");
DataResumo->tbVendasOperadoras->Open();

DataResumo->tbVendasOperadoras->Last();
int final = DataResumo->tbVendasOperadoras->RecordCount;
DataResumo->tbVendasOperadoras->First();

ProgressBar1->Max = final;
ProgressBar1->Position = 0;
Label7->Caption = final;

    for(int contador = 0; contador < final; contador++)
    {
    //SELECIONA O DOMICÍLIO BANCÁRIO DO CLIENTE
    Edit1->Text = DataResumo->tbVendasOperadorasADQID->AsString;
    consulta = "select * from domicilio_cliente where domicilio_cliente.CODIGO is not null and domicilio_cliente.COD_ADQUIRENTE = '" + Edit1->Text + "'";
    Edit1->Text = DataResumo->tbVendasOperadorasCOD_CLIENTE->AsString;
    consulta += " and domicilio_cliente.COD_CLIENTE = '" + Edit1->Text + "'";
    consulta += " and domicilio_cliente.CNPJ = '" + DataResumo->tbVendasOperadorasCNPJ->AsString + "'";

        if(Data1->tbDomicilioCliente->Active)
        {
        Data1->tbDomicilioCliente->EmptyDataSet();
        }

    Data1->tbDomicilioCliente->Close();
    Data1->tbDomicilioCliente->SQL->Clear();
    Data1->tbDomicilioCliente->SQL->Add(consulta);
    Data1->tbDomicilioCliente->Open();

    continuar_domicilio = true;

        if(Data1->tbDomicilioCliente->RecordCount >= 1)
        {
            if(Data1->tbDomicilioCliente->RecordCount > 1)
            {
            //SELECIONA O DOMICÍLIO BANCÁRIO DO CLIENTE
            Edit1->Text = DataResumo->tbVendasOperadorasADQID->AsString;
            consulta = "select * from domicilio_cliente where domicilio_cliente.CODIGO is not null and domicilio_cliente.COD_ADQUIRENTE = '" + Edit1->Text + "'";
            Edit1->Text = DataResumo->tbVendasOperadorasCOD_CLIENTE->AsString;
            consulta += " and domicilio_cliente.COD_CLIENTE = '" + Edit1->Text + "'";
            consulta += " and domicilio_cliente.CNPJ = '" + DataResumo->tbVendasOperadorasCNPJ->AsString + "'";
            consulta += " and domicilio_cliente.COD_ESTABELECIMENTO = '" + DataResumo->tbVendasOperadorasESTABELECIMENTO->AsString + "'";

             	if(Data1->tbDomicilioCliente->Active)
                {
                Data1->tbDomicilioCliente->EmptyDataSet();
                }

            Data1->tbDomicilioCliente->Close();
            Data1->tbDomicilioCliente->SQL->Clear();
            Data1->tbDomicilioCliente->SQL->Add(consulta);
            Data1->tbDomicilioCliente->Open();

            	if(Data1->tbDomicilioCliente->RecordCount != 1)
                    continuar_domicilio = false;
            }

            if(continuar_domicilio)
            {
            DataResumo->tbVendasOperadoras->Edit();
            DataResumo->tbVendasOperadorasBANCO->Value = Data1->tbDomicilioClienteCOD_BANCO->AsFloat;
            DataResumo->tbVendasOperadorasAGENCIA->Value = Data1->tbDomicilioClienteAGENCIA->AsString;
            DataResumo->tbVendasOperadorasCONTA->Value = Data1->tbDomicilioClienteCONTA->AsString;
            DataResumo->tbVendasOperadoras->ApplyUpdates(0);
            }
        }

    DataResumo->tbVendasOperadoras->Next();

    Label6->Caption = contador + 1;
    Application->ProcessMessages();
    }
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::Atualizardadosbancriospagamento1Click(TObject *Sender)

{
Label21->Caption = "Atualizando dados bancários pagamento- Stone";
Label2->Caption = "";
Label10->Caption = 0;
Label7->Caption = 0;
Label6->Caption = 0;

AnsiString consulta;

DataResumo->tbPagamentosOperadoras->Close();
DataResumo->tbPagamentosOperadoras->SQL->Clear();
DataResumo->tbPagamentosOperadoras->SQL->Add("select * from pagamentos_operadoras where pagamentos_operadoras.COD_BANCO = 0 and pagamentos_operadoras.CONTA <> ''");
DataResumo->tbPagamentosOperadoras->Open();

DataResumo->tbPagamentosOperadoras->Last();
int final = DataResumo->tbPagamentosOperadoras->RecordCount;
DataResumo->tbPagamentosOperadoras->First();

ProgressBar1->Max = final;
ProgressBar1->Position = 0;
Label7->Caption = final;

    for(int contador = 0; contador < final; contador++)
    {
    //SELECIONA O DOMICÍLIO BANCÁRIO DO CLIENTE
    Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_ADQUIRENTE->AsString;
    consulta = "select * from domicilio_cliente where domicilio_cliente.CODIGO is not null and domicilio_cliente.COD_ADQUIRENTE = '" + Edit1->Text + "'";
    Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_CLIENTE->AsString;
    consulta += " and domicilio_cliente.COD_CLIENTE = '" + Edit1->Text + "'";
    consulta += " and domicilio_cliente.CNPJ = '" + DataResumo->tbPagamentosOperadorasCNPJ->AsString + "'";
    consulta += " and domicilio_cliente.CONTA = '" + DataResumo->tbPagamentosOperadorasCONTA->AsString + "'";

        if(Data1->tbDomicilioCliente->Active)
        {
        Data1->tbDomicilioCliente->EmptyDataSet();
        }

    Data1->tbDomicilioCliente->Close();
    Data1->tbDomicilioCliente->SQL->Clear();
    Data1->tbDomicilioCliente->SQL->Add(consulta);
    Data1->tbDomicilioCliente->Open();

        if(Data1->tbDomicilioCliente->RecordCount == 1)
        {
        DataResumo->tbPagamentosOperadoras->Edit();
        DataResumo->tbPagamentosOperadorasBANCO->Value = Data1->tbDomicilioClienteCOD_BANCO->AsFloat;
        DataResumo->tbPagamentosOperadorasCOD_BANCO->Value = Data1->tbDomicilioClienteCOD_BANCO->AsFloat;
        DataResumo->tbPagamentosOperadoras->ApplyUpdates(0);
        }

    DataResumo->tbPagamentosOperadoras->Next();

    Label6->Caption = contador + 1;
    Application->ProcessMessages();
    }
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::ResetarVendas1Click(TObject *Sender)
{
Label21->Caption = "Vincular vendas e pagamentos operadora - stone";

//SELECIONA PAGAMENTOS SEM VÍNCULO COM VENDA

	if(DataResumo->tbPagamentosOperadoras->Active)
	{
	DataResumo->tbPagamentosOperadoras->EmptyDataSet();
	}

DataResumo->tbPagamentosOperadoras->Close();
DataResumo->tbPagamentosOperadoras->SQL->Clear();
DataResumo->tbPagamentosOperadoras->SQL->Add("Select * from pagamentos_operadoras where pagamentos_operadoras.CODIGO is not null and pagamentos_operadoras.COD_STATUS_FINANCEIRO = 1 and pagamentos_operadoras.COD_VENDA is null and pagamentos_operadoras.COD_CLIENTE > 0 and pagamentos_operadoras.COD_ADQUIRENTE = 7 and pagamentos_operadoras.DATA_PAGAMENTO >= '2022-01-01'");
DataResumo->tbPagamentosOperadoras->Open();

DataResumo->tbPagamentosOperadoras->Last();
int final = DataResumo->tbPagamentosOperadoras->RecordCount;
DataResumo->tbPagamentosOperadoras->First();

int contador = 0;
AnsiString consulta;
AnsiString data;
Word Year, Month, Day;
TDateTime dtPresent;

ProgressBar1->Max = final;
ProgressBar1->Position = 0;

Label6->Caption = contador;
Label7->Caption = final;
Label10->Caption = "";

	for(contador = 0; contador < final; contador++)
	{
	Label6->Caption = contador+1;

    //TENTA LOCALIZAR A VENDA
    consulta = "SELECT * FROM vendas where vendas.COD_STATUS_FINANCEIRO = '1' ";
    consulta += " and vendas.CNPJ = '" + DataResumo->tbPagamentosOperadorasCNPJ->AsString + "'";
    consulta += " and vendas.ADQID = 7";

    consulta += " and vendas.PARCELA = '" + DataResumo->tbPagamentosOperadorasPARCELA->AsString + "'";
    consulta += " and vendas.NSU = '" + DataResumo->tbPagamentosOperadorasNSU->AsString + "'";

    Edit1->Text = DataResumo->tbPagamentosOperadorasDATA_VENDA->AsString.SubString(7,4) + "-" + DataResumo->tbPagamentosOperadorasDATA_VENDA->AsString.SubString(4,2) + "-" + DataResumo->tbPagamentosOperadorasDATA_VENDA->AsString.SubString(0,2);

    consulta += " and vendas.DATA_VENDA = '" + Edit1->Text + "'";

        if(DataResumo->tbVendasOperadoras->Active)
        {
        DataResumo->tbVendasOperadoras->EmptyDataSet();
        }

    DataResumo->tbVendasOperadoras->Close();
    DataResumo->tbVendasOperadoras->SQL->Clear();
    DataResumo->tbVendasOperadoras->SQL->Add(consulta);
    DataResumo->tbVendasOperadoras->Open();

        if(DataResumo->tbVendasOperadoras->RecordCount == 1)
        {
        DataResumo->tbPagamentosOperadoras->Edit();

        //CONCILIADA
        DataResumo->tbPagamentosOperadorasCOD_STATUS->Value = 1;

        //STATUS = LIQUIDADO
        DataResumo->tbPagamentosOperadorasCOD_STATUS_FINANCEIRO->Value = 2;

        DataResumo->tbPagamentosOperadorasVINCULADO_VENDA->Value = 'S';
        DataResumo->tbPagamentosOperadorasENCONTRADA_VENDA->Value = 'S';
        DataResumo->tbPagamentosOperadorasCOD_VENDA->Value = DataResumo->tbVendasOperadorasCODIGO->AsFloat;
        DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->Value = DataResumo->tbVendasOperadorasAUTORIZACAO->AsString;
        DataResumo->tbPagamentosOperadorasTOTAL_PARCELAS->Value = DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger;
        DataResumo->tbPagamentosOperadorasNUMERO_CARTAO->Value = DataResumo->tbVendasOperadorasCARTAO->AsString;
        DataResumo->tbPagamentosOperadorasNUMERO_TERMINAL->Value = DataResumo->tbVendasOperadorasTERMINAL->AsString;
        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = DataResumo->tbVendasOperadorasCOD_PRODUTO->AsInteger;
        DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = DataResumo->tbVendasOperadorasCODIGO_MODALIDADE->AsInteger;
        DataResumo->tbPagamentosOperadorasCOD_MEIO_CAPTURA->Value = DataResumo->tbVendasOperadorasCOD_MEIO_CAPTURA->AsInteger;

        DataResumo->tbPagamentosOperadoras->ApplyUpdates(0);

        DataResumo->tbVendasOperadoras->Edit();
        DataResumo->tbVendasOperadorasCOD_STATUS_FINANCEIRO->Value = 2;
        DataResumo->tbVendasOperadorasVINCULADO_PAGAMENTO->Value = 'S';
        DataResumo->tbVendasOperadorasCOD_PAGAMENTO->Value = DataResumo->tbPagamentosOperadorasCODIGO->AsFloat;
        DataResumo->tbVendasOperadorasDATA_PAGAMENTO->Value = DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->AsDateTime;

        DataResumo->tbVendasOperadoras->ApplyUpdates(0);
        }

    DataResumo->tbPagamentosOperadoras->Next();

    ProgressBar1->Position = contador+1;

	Application->ProcessMessages();
	}
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::Preencherbandeiranospagamentos1Click(TObject *Sender)

{
Label21->Caption = "Preencher bandeira nos pagamentos - stone";

//SELECIONA PAGAMENTOS CONCILIADO COM VENDAS E SEM BANDEIRA

	if(DataResumo->tbPagamentosOperadoras->Active)
	{
	DataResumo->tbPagamentosOperadoras->EmptyDataSet();
	}

DataResumo->tbPagamentosOperadoras->Close();
DataResumo->tbPagamentosOperadoras->SQL->Clear();
DataResumo->tbPagamentosOperadoras->SQL->Add("Select * from pagamentos_operadoras where pagamentos_operadoras.CODIGO is not null and pagamentos_operadoras.COD_STATUS_FINANCEIRO = 2 and pagamentos_operadoras.COD_VENDA is not null and pagamentos_operadoras.COD_CLIENTE > 0 and pagamentos_operadoras.COD_ADQUIRENTE = 7 and pagamentos_operadoras.DATA_PAGAMENTO >= '2022-01-01' and pagamentos_operadoras.COD_BANDEIRA is null");
DataResumo->tbPagamentosOperadoras->Open();

DataResumo->tbPagamentosOperadoras->Last();
int final = DataResumo->tbPagamentosOperadoras->RecordCount;
DataResumo->tbPagamentosOperadoras->First();

int contador = 0;
AnsiString consulta;
AnsiString data;
Word Year, Month, Day;
TDateTime dtPresent;

ProgressBar1->Max = final;
ProgressBar1->Position = 0;

Label6->Caption = contador;
Label7->Caption = final;
Label10->Caption = "";

	for(contador = 0; contador < final; contador++)
	{
	Label6->Caption = contador+1;

    //TENTA LOCALIZAR A VENDA
    consulta = "SELECT * FROM vendas where vendas.CODIGO is not null";
    consulta += " and vendas.CNPJ = '" + DataResumo->tbPagamentosOperadorasCNPJ->AsString + "'";
    consulta += " and vendas.ADQID = 7";

    consulta += " and vendas.PARCELA = '" + DataResumo->tbPagamentosOperadorasPARCELA->AsString + "'";
    consulta += " and vendas.NSU = '" + DataResumo->tbPagamentosOperadorasNSU->AsString + "'";

    Edit1->Text = DataResumo->tbPagamentosOperadorasDATA_VENDA->AsString.SubString(7,4) + "-" + DataResumo->tbPagamentosOperadorasDATA_VENDA->AsString.SubString(4,2) + "-" + DataResumo->tbPagamentosOperadorasDATA_VENDA->AsString.SubString(0,2);

    consulta += " and vendas.DATA_VENDA = '" + Edit1->Text + "'";

        if(DataResumo->tbVendasOperadoras->Active)
        {
        DataResumo->tbVendasOperadoras->EmptyDataSet();
        }

    DataResumo->tbVendasOperadoras->Close();
    DataResumo->tbVendasOperadoras->SQL->Clear();
    DataResumo->tbVendasOperadoras->SQL->Add(consulta);
    DataResumo->tbVendasOperadoras->Open();

        if(DataResumo->tbVendasOperadoras->RecordCount == 1)
        {
        DataResumo->tbPagamentosOperadoras->Edit();
        DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = DataResumo->tbVendasOperadorasCOD_BANDEIRA->AsInteger;
        DataResumo->tbPagamentosOperadoras->ApplyUpdates(0);
        }

    DataResumo->tbPagamentosOperadoras->Next();

    ProgressBar1->Position = contador+1;

	Application->ProcessMessages();
	}
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::Preencherdadosbancriosnospagamentos1Click(TObject *Sender)

{
Label21->Caption = "Preencher dados bancários nos pagamentos - stone";

	if(DataResumo->tbPagamentosOperadoras->Active)
	{
	DataResumo->tbPagamentosOperadoras->EmptyDataSet();
	}

int contador = 0;
AnsiString consulta;
AnsiString data;
Word Year, Month, Day;
TDateTime dtPresent;

consulta = "Select * from pagamentos_operadoras where pagamentos_operadoras.COD_ADQUIRENTE = 7 ";
consulta += " and pagamentos_operadoras.DATA_PAGAMENTO >= '2022-01-01'";
consulta += " and pagamentos_operadoras.AGENCIA = ''";

DataResumo->tbPagamentosOperadoras->Close();
DataResumo->tbPagamentosOperadoras->SQL->Clear();
DataResumo->tbPagamentosOperadoras->SQL->Add(consulta);
DataResumo->tbPagamentosOperadoras->Open();

DataResumo->tbPagamentosOperadoras->Last();
int final = DataResumo->tbPagamentosOperadoras->RecordCount;
DataResumo->tbPagamentosOperadoras->First();

ProgressBar1->Max = final;
ProgressBar1->Position = 0;

Label6->Caption = contador;
Label7->Caption = final;
Label10->Caption = "";

	for(contador = 0; contador < final; contador++)
	{
    //TENTA LOCALIZAR O COMPROVANTE

        if(DataResumo->tbPagamentosOperadorasCOD_TIPO_LANCAMENTO->AsInteger == 2 || DataResumo->tbPagamentosOperadorasCOD_TIPO_LANCAMENTO->AsInteger == 3)
        {
        consulta = "select * from edi_stone_evento_financeiro where edi_stone_evento_financeiro.STONECODE = '" + DataResumo->tbPagamentosOperadorasID_LOJA->AsString + "'";
        consulta += " and edi_stone_evento_financeiro.CODIGO_EVENTO = '" + DataResumo->tbPagamentosOperadorasNUMERO_OPERACAO_ANTECIPACAO->AsString + "'";

        	if(DataResumo->tbPagamentosOperadorasCOD_TIPO_LANCAMENTO->AsInteger == 2)
            {
            consulta += " and edi_stone_evento_financeiro.VALOR_EVENTO < 0";
            }
            else
            {
            consulta += " and edi_stone_evento_financeiro.VALOR_EVENTO > 0";
            }

        Data2->tbEventoStone->Close();
        Data2->tbEventoStone->SQL->Clear();
        Data2->tbEventoStone->SQL->Add(consulta);
        Data2->tbEventoStone->Open();

            if(Data2->tbEventoStone->RecordCount == 1)
            {
            DataResumo->tbPagamentosOperadoras->Edit();

            DataResumo->tbPagamentosOperadorasAGENCIA->Value = retirarZerosEsquerda(Data2->tbEventoStoneAGENCIA->AsString);

                if(Data2->tbEventoStoneBANCO->AsString != "")
                {
                DataResumo->tbPagamentosOperadorasBANCO->Value = StrToInt(Data2->tbEventoStoneBANCO->AsString);
                DataResumo->tbPagamentosOperadorasCOD_BANCO->Value = StrToFloat(DataResumo->tbPagamentosOperadorasBANCO->AsFloat);
                }

            DataResumo->tbPagamentosOperadorasCONTA->Value = retirarZerosEsquerda(Data2->tbEventoStoneNUM_CONTA->AsString);

            	//DÉBITO
                if(Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 2 || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 5
                    || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 8 || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 11
                    || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 20 || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 23)
                {
                DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 0;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 21;
                }
                //CRÉDITO
                else if(Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 3 || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 6
                    || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 9 || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 12
                    || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 15 || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 21
                    || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 24)
                {
                //CRÉDITO A VISTA

                DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 1;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 20;
                }

            //CONTROLE DAS BANDEIRAS

                //MasterCard
                if(Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 5 || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 6)
                {
                DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 160;
                }
                //Visa
                else if(Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 2 || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 3)
                {
                DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 159;
                }
                //Hipercard
                else if(Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 8 || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 9)
                {
                DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 162;
                }
                //Elo
                else if(Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 11 || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 12)
                {
                DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 166;
                }
                //Amex
                else if(Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 15)
                {
                DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 165;
                }
                //Cabal
                else if(Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 20 || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 21)
                {
                DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 169;
                }
                //Union Pay
                else if(Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 23 || Data2->tbEventoStoneARRANJO_PAGAMENTO->AsInteger == 24)
                {
                DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 182;
                }



                if(DataResumo->tbPagamentosOperadorasCOD_BANCO->AsInteger == 0)
                {
                //SELECIONA O DOMICÍLIO BANCÁRIO DO CLIENTE
                Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_ADQUIRENTE->AsString;
                consulta = "select * from domicilio_cliente where domicilio_cliente.CODIGO is not null and domicilio_cliente.COD_ADQUIRENTE = '" + Edit1->Text + "'";
                consulta += " and domicilio_cliente.CNPJ = '" + DataResumo->tbPagamentosOperadorasCNPJ->AsString + "'";

                    if(DataResumo->tbPagamentosOperadorasCONTA->AsString != "")
                    {
                    consulta += " and domicilio_cliente.CONTA = '" + DataResumo->tbPagamentosOperadorasCONTA->AsString + "'";
                    }

                    if(Data1->tbDomicilioCliente->Active)
                    {
                    Data1->tbDomicilioCliente->EmptyDataSet();
                    }

                Data1->tbDomicilioCliente->Close();
                Data1->tbDomicilioCliente->SQL->Clear();
                Data1->tbDomicilioCliente->SQL->Add(consulta);
                Data1->tbDomicilioCliente->Open();

                    if(Data1->tbDomicilioCliente->RecordCount == 1)
                    {
                    DataResumo->tbPagamentosOperadorasBANCO->Value = Data1->tbDomicilioClienteCOD_BANCO->AsString;
                    DataResumo->tbPagamentosOperadorasCOD_BANCO->Value = DataResumo->tbPagamentosOperadorasBANCO->AsInteger;
                    DataResumo->tbPagamentosOperadorasAGENCIA->Value = Data1->tbDomicilioClienteAGENCIA->AsString;
                    DataResumo->tbPagamentosOperadorasCONTA->Value = Data1->tbDomicilioClienteCONTA->AsString;
                    }
                }

            DataResumo->tbPagamentosOperadoras->ApplyUpdates(0);
            }
        }
        else
        {
        consulta = "select * from edi_stone_comprovante_pagamento where edi_stone_comprovante_pagamento.STONECODE = '" + DataResumo->tbPagamentosOperadorasID_LOJA->AsString + "'";
        consulta += " and edi_stone_comprovante_pagamento.NUM_PARCELA = '" + DataResumo->tbPagamentosOperadorasPARCELA->AsString + "'";
        consulta += " and edi_stone_comprovante_pagamento.NSU = '" + DataResumo->tbPagamentosOperadorasNSU->AsString + "'";

        Edit1->Text = formatarData(3, DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->AsString);
        consulta += " and edi_stone_comprovante_pagamento.PAGAMENTO_PARCELA = '" + Edit1->Text + "'";

        Data2->tbPagamentoStone->Close();
        Data2->tbPagamentoStone->SQL->Clear();
        Data2->tbPagamentoStone->SQL->Add(consulta);
        Data2->tbPagamentoStone->Open();

            if(Data2->tbPagamentoStone->RecordCount == 1)
            {
            DataResumo->tbPagamentosOperadoras->Edit();

            DataResumo->tbPagamentosOperadorasAGENCIA->Value = retirarZerosEsquerda(Data2->tbPagamentoStoneAGENCIA->AsString);
            DataResumo->tbPagamentosOperadorasBANCO->Value = Data2->tbPagamentoStoneBANCO->AsInteger;
            DataResumo->tbPagamentosOperadorasCOD_BANCO->Value = StrToFloat(DataResumo->tbPagamentosOperadorasBANCO->AsFloat);
            DataResumo->tbPagamentosOperadorasCONTA->Value = retirarZerosEsquerda(Data2->tbPagamentoStoneNUM_CONTA->AsString);

                //DÉBITO
                if(Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 2 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 5
                    || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 8 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 11
                    || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 20 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 23)
                {
                DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 0;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 21;
                }
                //CRÉDITO
                else if(Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 3 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 6
                    || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 9 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 12
                    || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 15 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 21
                    || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 24 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 4
                    || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 7 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 10
                    || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 13 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 16
                    || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 22 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 25)
                {

                    //CRÉDITO A VISTA
                    if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 1)
                    {
                    DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 1;
                    DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 20;
                    }
                    else
                    {
                    //PARCELADO
                    DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 17;

                        //VERIFICA O PRODUTO CORRETO COM BASE NO N° DE PARCELAS
                        if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 2)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 40;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 3)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 41;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 4)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 42;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 5)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 43;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 6)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 44;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 7)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 45;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 8)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 46;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 9)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 47;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 10)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 48;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 11)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 50;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 12)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 51;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 13)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 55;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 14)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 56;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 15)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 57;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 16)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 58;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 17)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 59;
                        }
                        else if(DataResumo->tbPagamentosOperadorasPARCELA->AsInteger == 18)
                        {
                        DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 60;
                        }
                    }
                }

                //CONTROLE DAS BANDEIRAS

                //MasterCard
                if(Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 5 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 6
                    || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 7)
                {
                DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 160;
                }
                //Visa
                else if(Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 2 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 3
                    || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 4)
                {
                DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 159;
                }
                //Hipercard
                else if(Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 8 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 9
                    || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 10)
                {
                DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 162;
                }
                //Elo
                else if(Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 11 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 12
                    || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 13)
                {
                DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 166;
                }
                //Amex
                else if(Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 15 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 16)
                {
                DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 165;
                }
                //Cabal
                else if(Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 20 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 21
                    || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 22)
                {
                DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 169;
                }
                //Union Pay
                else if(Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 23 || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 24
                    || Data2->tbPagamentoStoneARRANJO_PAGAMENTO->AsInteger == 25)
                {
                DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 182;
                }


                if(DataResumo->tbPagamentosOperadorasCOD_BANCO->AsInteger == 0)
                {
                //SELECIONA O DOMICÍLIO BANCÁRIO DO CLIENTE
                Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_ADQUIRENTE->AsString;
                consulta = "select * from domicilio_cliente where domicilio_cliente.CODIGO is not null and domicilio_cliente.COD_ADQUIRENTE = '" + Edit1->Text + "'";
                consulta += " and domicilio_cliente.CNPJ = '" + DataResumo->tbPagamentosOperadorasCNPJ->AsString + "'";

                    if(DataResumo->tbPagamentosOperadorasCONTA->AsString != "")
                    {
                    consulta += " and domicilio_cliente.CONTA = '" + DataResumo->tbPagamentosOperadorasCONTA->AsString + "'";
                    }

                    if(Data1->tbDomicilioCliente->Active)
                    {
                    Data1->tbDomicilioCliente->EmptyDataSet();
                    }

                Data1->tbDomicilioCliente->Close();
                Data1->tbDomicilioCliente->SQL->Clear();
                Data1->tbDomicilioCliente->SQL->Add(consulta);
                Data1->tbDomicilioCliente->Open();

                    if(Data1->tbDomicilioCliente->RecordCount == 1)
                    {
                    DataResumo->tbPagamentosOperadorasBANCO->Value = Data1->tbDomicilioClienteCOD_BANCO->AsString;
                    DataResumo->tbPagamentosOperadorasCOD_BANCO->Value = DataResumo->tbPagamentosOperadorasBANCO->AsInteger;
                    DataResumo->tbPagamentosOperadorasAGENCIA->Value = Data1->tbDomicilioClienteAGENCIA->AsString;
                    DataResumo->tbPagamentosOperadorasCONTA->Value = Data1->tbDomicilioClienteCONTA->AsString;
                    }
                }

            DataResumo->tbPagamentosOperadoras->ApplyUpdates(0);
            }
        }

    DataResumo->tbPagamentosOperadoras->Next();

    ProgressBar1->Position = contador+1;
    Label6->Caption = contador + 1;

	Application->ProcessMessages();
	}
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::AutomaticoPagSeguroClick(TObject *Sender)
{
Button2Click(Sender);
TratarVendasPagSeguroClick(Sender);
TratarPagamentosPagSeguroClick(Sender);
TratarAntecipacoesPagSeguroClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::TratarVendasPagSeguroClick(TObject *Sender)
{
AnsiString consulta, cnpj_cliente;
double valor_total_transacao, total_parcelas = 0, diferenca, parcela1, parcela2, parcela3, parcela4;
double total_valor, valor_taxa, aux_diferenca;
int num_parcela = 1, auxiliar;

//SELECIONA TODAS AS VENDAS DO PAGSEGURO EM TABELA BRUTA AINDA NÃO TRATADOS DE RECEBIMENTO MÚLTIPLO
Data3->tbSeguroVenda->Close();
Data3->tbSeguroVenda->SQL->Clear();
Data3->tbSeguroVenda->SQL->Add("Select * from edi_pagseguro_venda where edi_pagseguro_venda.TRATADO = 'N' and edi_pagseguro_venda.TIPO_EVENTO = '1' and edi_pagseguro_venda.PAGAMENTO_PRAZO = 'M' ");
Data3->tbSeguroVenda->Open();

Data3->tbSeguroVenda->Last();
int final = Data3->tbSeguroVenda->RecordCount;
Data3->tbSeguroVenda->First();

Label21->Caption = "Tratandos Arquivos PagSeguro";
Label2->Caption = "Tratando Vendas com Recebimento Parcelado";
Label10->Caption = 0;
Label6->Caption = 0;
Label7->Caption = final;

ProgressBar1->Max = final;
ProgressBar1->Position = 0;

Application->ProcessMessages();

	//EFETUA ESSE BLOCO ATÉ TRATAR TODAS AS VENDAS
	for(int contador = 0; contador < final; contador++)
	{
    cnpj_cliente = "";

		if(Data3->tbSeguroVendaMEIO_PAGAMENTO->Value == 3 || Data3->tbSeguroVendaMEIO_PAGAMENTO->Value == 8 || Data3->tbSeguroVendaMEIO_PAGAMENTO->Value == 11)
		{
        //LOCALIZA O CLIENTE
        Edit1->Text = Data3->tbSeguroVendaESTABELECIMENTO->AsAnsiString;

		consulta = "Select * from cliente_operadora where cliente_operadora.COD_ADQUIRENTE = 108 and cliente_operadora.CODIGO_ESTABELECIMENTO = '" + Edit1->Text + "' ";

            if(DataResumo->tbClientesOperadoras->Active)
            {
            DataResumo->tbClientesOperadoras->EmptyDataSet();
            }

        DataResumo->tbClientesOperadoras->Close();
        DataResumo->tbClientesOperadoras->SQL->Clear();
        DataResumo->tbClientesOperadoras->SQL->Add(consulta);
        DataResumo->tbClientesOperadoras->Open();

            if(DataResumo->tbClientesOperadoras->RecordCount == 1)
            {
            cnpj_cliente = DataResumo->tbClientesOperadorasCNPJ_ESTABELECIMENTO->AsString;
            }


        //CONTROLE DE DUPLICIDADE
        consulta = "SELECT * FROM vendas where vendas.CNPJ = '" + cnpj_cliente + "'";
        consulta += " and vendas.ADQID = 108";

        	if(Data3->tbSeguroVendaPARCELA->AsInteger == 0)
            {
            Edit1->Text = "1";
            }
            else
            {
            Edit1->Text = Data3->tbSeguroVendaPARCELA->AsInteger;
            }

        consulta += " and vendas.PARCELA = '" + Edit1->Text + "'";

            //PIX
            if(Data3->tbSeguroVendaMEIO_PAGAMENTO->AsInteger == 11)
            {
            consulta += " and vendas.NSU = '" + Data3->tbSeguroVendaCODIGO_TRANSACAO->AsString + "'";
        	consulta += " and vendas.AUTORIZACAO = '" + Data3->tbSeguroVendaCODIGO_TRANSACAO->AsString + "'";
            }
            else
            {
            consulta += " and vendas.NSU = '" + Data3->tbSeguroVendaNSU->AsString + "'";
        	consulta += " and vendas.AUTORIZACAO = '" + Data3->tbSeguroVendaCODIGO_AUTORIZACAO->AsString + "'";
            }

        Edit1->Text = Data3->tbSeguroVendaDATA_VENDA_AJUSTE->AsString.SubString(7,4) + "-" + Data3->tbSeguroVendaDATA_VENDA_AJUSTE->AsString.SubString(4,2) + "-" + Data3->tbSeguroVendaDATA_VENDA_AJUSTE->AsString.SubString(0,2);

        consulta += " and vendas.DATA_VENDA = '" + Edit1->Text + "'";

            if(DataResumo->tbVendasOperadoras->Active)
            {
            DataResumo->tbVendasOperadoras->EmptyDataSet();
            }

        DataResumo->tbVendasOperadoras->Close();
        DataResumo->tbVendasOperadoras->SQL->Clear();
        DataResumo->tbVendasOperadoras->SQL->Add(consulta);
        DataResumo->tbVendasOperadoras->Open();

            if(DataResumo->tbVendasOperadoras->RecordCount == 0)
            {
            DataResumo->tbVendasOperadoras->Insert();

            //PAGSEGURO
            DataResumo->tbVendasOperadorasADQID->Value = 108;
            DataResumo->tbVendasOperadorasADQUIRENTE->Value = "PAGSEGURO";

            DataResumo->tbVendasOperadorasESTABELECIMENTO->Value = Data3->tbSeguroVendaESTABELECIMENTO->AsAnsiString;

                //CONFIRMA QUE FOI LOCALIZADO OS DADOS DO CLIENTE / OPERADORA
                if(DataResumo->tbClientesOperadoras->RecordCount == 1)
                {
                //BUSCA OS DADOS DO CLIENTE NA TABELA DE GRUPOS
                Edit1->Text = DataResumo->tbClientesOperadorasCOD_GRUPO->AsFloat;

                consulta = "Select * from grupos_clientes where grupos_clientes.CODIGO = '" + Edit1->Text + "' ";

                Data1->tbGrupos->Close();
                Data1->tbGrupos->SQL->Clear();
                Data1->tbGrupos->SQL->Add(consulta);
                Data1->tbGrupos->Open();

                    if(Data1->tbGrupos->RecordCount == 1)
                    {
                    DataResumo->tbVendasOperadorasEMPRESA->Value = Data1->tbGruposNOME_EMPRESA->AsString;
                    DataResumo->tbVendasOperadorasCNPJ->Value = Data1->tbGruposCNPJ->AsString;
                    DataResumo->tbVendasOperadorasCOD_CLIENTE->Value = Data1->tbGruposCOD_CLIENTE->AsFloat;
                    DataResumo->tbVendasOperadorasCOD_GRUPO_CLIENTE->Value = Data1->tbGruposCODIGO->AsFloat;

                    //MARCA O CLIENTE COMO PENDENTE DE CÁLCULO
                    Edit1->Text = DataResumo->tbVendasOperadorasCOD_CLIENTE->AsFloat;

                    consulta = "Select * from clientes where clientes.CODIGO = '" + Edit1->Text + "' ";

                    Data1->tbClientes->Close();
                    Data1->tbClientes->SQL->Clear();
                    Data1->tbClientes->SQL->Add(consulta);
                    Data1->tbClientes->Open();

                        if(Data1->tbClientes->RecordCount == 1)
                        {
                        Data1->tbClientes->Edit();
                        Data1->tbClientesARQUIVOS_PROCESSADOS->Value = "N";
                        Data1->tbClientes->ApplyUpdates(0);
                        }
                    }
                }

                if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 0)
                {
                //DÉBITO
                DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 21;
                DataResumo->tbVendasOperadorasCODIGO_MODALIDADE->Value = 0;
                }
                else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 1)
                {
                //CRÉDITO
                DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 20;
                DataResumo->tbVendasOperadorasCODIGO_MODALIDADE->Value = 1;
                }
                else
                {
                //PARCELADO
                DataResumo->tbVendasOperadorasCODIGO_MODALIDADE->Value = 17;

                    if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 2)
                    {
                    //PARCELADO EM 2X;
                    DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 40;
                    }
                    else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 3)
                    {
                    //PARCELADO EM 3X;
                    DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 41;
                    }
                    else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 4)
                    {
                    //PARCELADO EM 4X;
                    DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 42;
                    }
                    else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 5)
                    {
                    //PARCELADO EM 5X;
                    DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 43;
                    }
                    else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 6)
                    {
                    //PARCELADO EM 6X;
                    DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 44;
                    }
                    else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 7)
                    {
                    //PARCELADO EM 6X;
                    DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 45;
                    }
                    else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 7)
                    {
                    //PARCELADO EM 7X;
                    DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 45;
                    }
                    else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 8)
                    {
                    //PARCELADO EM 8X;
                    DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 46;
                    }
                    else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 9)
                    {
                    //PARCELADO EM 9X;
                    DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 47;
                    }
                    else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 10)
                    {
                    //PARCELADO EM 10X;
                    DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 48;
                    }
                    else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 11)
                    {
                    //PARCELADO EM 11X;
                    DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 50;
                    }
                    else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 12)
                    {
                    //PARCELADO EM 12X;
                    DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 51;
                    }
                    else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 13)
                    {
                    //PARCELADO EM 13X;
                    DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 55;
                    }
                    else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 14)
                    {
                    //PARCELADO EM 14X;
                    DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 56;
                    }
                    else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 15)
                    {
                    //PARCELADO EM 15X;
                    DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 57;
                    }
                    else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 16)
                    {
                    //PARCELADO EM 16X;
                    DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 58;
                    }
                    else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 17)
                    {
                    //PARCELADO EM 16X;
                    DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 59;
                    }
                    else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 18)
                    {
                    //PARCELADO EM 16X;
                    DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 60;
                    }
                }


                if(Data3->tbSeguroVendaINSTITUICAO_FINANCEIRA->AsString == "AMEX")
                {
                DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 165;
                }
                else if(Data3->tbSeguroVendaINSTITUICAO_FINANCEIRA->AsString == "BOLETO")
                {
                DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 192;
                }
                else if(Data3->tbSeguroVendaINSTITUICAO_FINANCEIRA->AsString == "ELO")
                {
                DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 166;
                }
                else if(Data3->tbSeguroVendaINSTITUICAO_FINANCEIRA->AsString == "HIPERCARD")
                {
                DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 162;
                }
                else if(Data3->tbSeguroVendaINSTITUICAO_FINANCEIRA->AsString == "MAESTRO")
                {
                DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 160;
                }
                else if(Data3->tbSeguroVendaINSTITUICAO_FINANCEIRA->AsString == "MASTERCARD")
                {
                DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 160;
                }
                else if(Data3->tbSeguroVendaINSTITUICAO_FINANCEIRA->AsString == "VISA")
                {
                DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 159;
                }
                else if(Data3->tbSeguroVendaINSTITUICAO_FINANCEIRA->AsString == "VISA ELECTRON")
                {
                DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 159;
                }
                else if(Data3->tbSeguroVendaINSTITUICAO_FINANCEIRA->AsString == "PS_BALANCE")
                {
                DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 191;
                }
                else if(Data3->tbSeguroVendaINSTITUICAO_FINANCEIRA->AsString == "CABAL")
                {
                DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 169;
                }

            DataResumo->tbVendasOperadorasPARCELA->Value = Data3->tbSeguroVendaPARCELA->AsFloat;

                if(DataResumo->tbVendasOperadorasPARCELA->AsFloat == 0)
                {
                DataResumo->tbVendasOperadorasPARCELA->Value = 1;
                }

            DataResumo->tbVendasOperadorasTOTAL_PARCELAS->Value = Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat;

                if(DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsFloat == 0)
                {
                DataResumo->tbVendasOperadorasTOTAL_PARCELAS->Value = 1;
                }

            //STATUS = NÃO CONCILIADA
            DataResumo->tbVendasOperadorasCOD_STATUS_CONCILIACAO->Value = 2;

            //STATUS FINANCEIRO = PREVISTO
            DataResumo->tbVendasOperadorasCOD_STATUS_FINANCEIRO->Value = 1;

            DataResumo->tbVendasOperadorasPERC_TAXA_CALC->Value = 'S';

            DataResumo->tbVendasOperadorasTID->Value = Data3->tbSeguroVendaCODIGO_TRANSACAO->AsString;
            DataResumo->tbVendasOperadorasTID_ADICIONAL->Value = Data3->tbSeguroVendaCODIGO_TRANSACAO ->AsString.SubString(1,8);

                if(DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger > 1)
                {
                DataResumo->tbVendasOperadorasVALOR_BRUTO->Value = Data3->tbSeguroVendaVALOR_TOTAL_TRANSACAO->AsFloat / DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger;
                DataResumo->tbVendasOperadorasVALOR_TAXA->Value = (Data3->tbSeguroVendaTAXA_INTERMEDIACAO->AsFloat + Data3->tbSeguroVendaTAXA_PARCELA_VENDEDOR->AsFloat) / DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger;
                DataResumo->tbVendasOperadorasVALOR_LIQUIDO->Value = Data3->tbSeguroVendaVALOR_PARCELA->AsFloat;

                DataResumo->tbVendasOperadorasVALOR_BRUTO->Value = SimpleRoundTo(DataResumo->tbVendasOperadorasVALOR_BRUTO->Value, -2);
                DataResumo->tbVendasOperadorasVALOR_LIQUIDO->Value = SimpleRoundTo(DataResumo->tbVendasOperadorasVALOR_LIQUIDO->Value, -2);
                DataResumo->tbVendasOperadorasVALOR_TAXA->Value = SimpleRoundTo(DataResumo->tbVendasOperadorasVALOR_TAXA->Value, -2);

                total_valor = DataResumo->tbVendasOperadorasVALOR_BRUTO->AsFloat * DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger;
                diferenca = total_valor - Data3->tbSeguroVendaVALOR_TOTAL_TRANSACAO->AsFloat;
                diferenca = SimpleRoundTo(diferenca, -2);

                aux_diferenca = (diferenca * 100);

                    if(aux_diferenca < 0)
                        aux_diferenca = aux_diferenca * -1;

                Edit1->Text = aux_diferenca;
                auxiliar = StrToInt(Edit1->Text);

                    if(DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsInteger <= auxiliar)
                    {
                        if(diferenca > 0)
                        {
                        DataResumo->tbVendasOperadorasVALOR_BRUTO->Value = DataResumo->tbVendasOperadorasVALOR_BRUTO->AsFloat - 0.01;
                        }
                        else
                        {
                        DataResumo->tbVendasOperadorasVALOR_BRUTO->Value = DataResumo->tbVendasOperadorasVALOR_BRUTO->AsFloat + 0.01;
                        }

                    }

                DataResumo->tbVendasOperadorasVALOR_TAXA->Value = DataResumo->tbVendasOperadorasVALOR_BRUTO->AsFloat - DataResumo->tbVendasOperadorasVALOR_LIQUIDO->AsFloat;
                DataResumo->tbVendasOperadorasVALOR_TAXA->Value = SimpleRoundTo(DataResumo->tbVendasOperadorasVALOR_TAXA->Value, -2);
                }
                else
                {
                DataResumo->tbVendasOperadorasVALOR_BRUTO->Value = Data3->tbSeguroVendaVALOR_TOTAL_TRANSACAO->AsFloat;
                DataResumo->tbVendasOperadorasVALOR_TAXA->Value = Data3->tbSeguroVendaTAXA_INTERMEDIACAO->AsFloat + Data3->tbSeguroVendaTAXA_PARCELA_VENDEDOR->AsFloat;
                DataResumo->tbVendasOperadorasVALOR_LIQUIDO->Value = Data3->tbSeguroVendaVALOR_PARCELA->AsFloat;
                }

                if(DataResumo->tbVendasOperadorasVALOR_BRUTO->AsFloat > 0)
                {
                DataResumo->tbVendasOperadorasPERCENTUAL_TAXA->Value = ( DataResumo->tbVendasOperadorasVALOR_TAXA->AsFloat / DataResumo->tbVendasOperadorasVALOR_BRUTO->AsFloat) * 100;
                }

            DataResumo->tbVendasOperadorasDATA_VENDA->Value = Data3->tbSeguroVendaDATA_VENDA_AJUSTE->AsDateTime;
            DataResumo->tbVendasOperadorasHORA_TRANSACAO->Value = Data3->tbSeguroVendaHORA_VENDA_AJUSTE->AsDateTime;
            DataResumo->tbVendasOperadorasNSU->Value = Data3->tbSeguroVendaNSU->AsString;
            DataResumo->tbVendasOperadorasDATA_PREVISTA_PAGTO->Value = dataValida(Data3->tbSeguroVendaDATA_PREVISTA_PAGAMENTO->AsDateTime);
            DataResumo->tbVendasOperadorasAUTORIZACAO->Value = Data3->tbSeguroVendaCODIGO_AUTORIZACAO->AsString;
            DataResumo->tbVendasOperadorasBIN_CARTAO->Value = Data3->tbSeguroVendaCARTAO_BIN->AsString;
            DataResumo->tbVendasOperadorasNUMERO_RESUMO_VENDA->Value = Data3->tbSeguroVendaCODIGO_CV->AsString;

            //CONFIGURA O MEIO DE CAPTURA

                //POS
                if(Data3->tbSeguroVendaMEIO_CAPTURA->AsInteger == 1 || Data3->tbSeguroVendaMEIO_CAPTURA->AsInteger == 2)
                {
                //POS
                DataResumo->tbVendasOperadorasCOD_MEIO_CAPTURA->Value = 1;
                }
                else if(Data3->tbSeguroVendaMEIO_CAPTURA->AsInteger == 3)
                {
                //E-COMMERCE
                DataResumo->tbVendasOperadorasCOD_MEIO_CAPTURA->Value = 3;
                }
                else if(Data3->tbSeguroVendaMEIO_CAPTURA->AsInteger == 4)
                {
                //TEF
                DataResumo->tbVendasOperadorasCOD_MEIO_CAPTURA->Value = 2;
                }

                //3 = CARTÃO DE CRÉDITO
                if(Data3->tbSeguroVendaMEIO_PAGAMENTO->AsInteger == 3)
                {
                    if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat > 1)
                    {
                    //PARCELADO
                    DataResumo->tbVendasOperadorasCODIGO_MODALIDADE->Value = 17;
                    }
                    else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 1)
                    {
                    //CRÉDITO
                    DataResumo->tbVendasOperadorasCODIGO_MODALIDADE->Value = 1;
                    }
                }
                //8 = CARTÃO DE DÉBITO*
                else if(Data3->tbSeguroVendaMEIO_PAGAMENTO->AsInteger == 8)
                {
                //DÉBITO
                DataResumo->tbVendasOperadorasCODIGO_MODALIDADE->Value = 0;
                DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 21;
                }
                //MEIO DE PAGAMENTO = 11 = PIX
                else if(Data3->tbSeguroVendaMEIO_PAGAMENTO->AsInteger == 11)
                {
                //PIX
                DataResumo->tbVendasOperadorasCODIGO_MODALIDADE->Value = 21;
                DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 53;
                }


                if(Data3->tbSeguroVendaCARTAO_BIN->AsString != "" && Data3->tbSeguroVendaCARTAO_HOLDER->AsString != "")
                {
                DataResumo->tbVendasOperadorasCARTAO->Value = Data3->tbSeguroVendaCARTAO_BIN->AsString + "******" + Data3->tbSeguroVendaCARTAO_HOLDER->AsString;
                }


            Edit1->Text = DataResumo->tbVendasOperadorasCOD_CLIENTE->AsFloat;

            consulta = "Select * from domicilio_cliente where domicilio_cliente.COD_CLIENTE = '" + Edit1->Text + "' ";

            Edit1->Text = DataResumo->tbVendasOperadorasCNPJ->AsString;

            consulta = consulta + " and domicilio_cliente.COD_ADQUIRENTE = '108' ";

                //VERIFICA SE O CLIENTE É DIFERENTE DE MCTINTAS
                if(DataResumo->tbVendasOperadorasCOD_CLIENTE->AsFloat != 562)
                {
                //SE FOR DIFERNETE DE MCTINTAS, BUSCA O CNPJ DA EMPRESA PARA LOCALIZAR O BANCO
                Edit1->Text = DataResumo->tbVendasOperadorasCNPJ->AsString;

                consulta = consulta + " and domicilio_cliente.CNPJ = '" + Edit1->Text + "' ";
                }

            Data1->tbDomicilioCliente->Close();
            Data1->tbDomicilioCliente->SQL->Clear();
            Data1->tbDomicilioCliente->SQL->Add(consulta);
            Data1->tbDomicilioCliente->Open();

                if(Data1->tbDomicilioCliente->RecordCount == 1)
                {
                DataResumo->tbVendasOperadorasBANCO->Value = Data1->tbDomicilioClienteCOD_BANCO->AsInteger;
                DataResumo->tbVendasOperadorasAGENCIA->Value = Data1->tbDomicilioClienteAGENCIA->AsString;
                DataResumo->tbVendasOperadorasCONTA->Value = Data1->tbDomicilioClienteCONTA->AsString;
                }

                if(DataResumo->tbVendasOperadorasVALOR_TAXA->AsFloat < 0)
                {
                DataResumo->tbVendasOperadorasVALOR_TAXA->Value = 0;
                }

                if(DataResumo->tbVendasOperadorasCOD_PRODUTO->AsFloat == 53)
                {
                DataResumo->tbVendasOperadorasNSU->Value = Data3->tbSeguroVendaCODIGO_TRANSACAO->AsString;
                DataResumo->tbVendasOperadorasAUTORIZACAO->Value = Data3->tbSeguroVendaCODIGO_TRANSACAO->AsString;
                DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 200;
                }

            DataResumo->tbVendasOperadoras->ApplyUpdates(0);
            }
        }


	Data3->tbSeguroVenda->Edit();
	Data3->tbSeguroVendaTRATADO->Value = 'S';
	Data3->tbSeguroVenda->ApplyUpdates(0);

    Data3->tbSeguroVenda->Next();

	Label6->Caption = contador + 1;
    ProgressBar1->Position = contador + 1;

	Application->ProcessMessages();
	}






//SELECIONA TODAS AS VENDAS DO PAGSEGURO EM TABELA BRUTA AINDA NÃO TRATADOS DE RECEBIMENTO ÚNICO
Data3->tbSeguroVenda->Close();
Data3->tbSeguroVenda->SQL->Clear();
Data3->tbSeguroVenda->SQL->Add("Select * from edi_pagseguro_venda where edi_pagseguro_venda.TRATADO = 'N' and edi_pagseguro_venda.TIPO_EVENTO = '1' and edi_pagseguro_venda.PAGAMENTO_PRAZO = 'U' ");
Data3->tbSeguroVenda->Open();

Data3->tbSeguroVenda->Last();
final = Data3->tbSeguroVenda->RecordCount;
Data3->tbSeguroVenda->First();

Label21->Caption = "Tratandos Arquivos PagSeguro";
Label2->Caption = "Tratando Vendas com Recebimento Único";
Label10->Caption = 0;
Label6->Caption = 0;
Label7->Caption = final;

ProgressBar1->Max = final;
ProgressBar1->Position = 0;

Application->ProcessMessages();

int final_parcelas;

	//EFETUA ESSE BLOCO ATÉ TRATAR TODAS AS VENDAS
	for(int contador = 0; contador < final; contador++)
	{
    cnpj_cliente = "";

		if(Data3->tbSeguroVendaMEIO_PAGAMENTO->Value == 3 || Data3->tbSeguroVendaMEIO_PAGAMENTO->Value == 8 || Data3->tbSeguroVendaMEIO_PAGAMENTO->Value == 11)
		{
        //LOCALIZA O CLIENTE
        Edit1->Text = Data3->tbSeguroVendaESTABELECIMENTO->AsAnsiString;

		consulta = "Select * from cliente_operadora where cliente_operadora.COD_ADQUIRENTE = 108 and cliente_operadora.CODIGO_ESTABELECIMENTO = '" + Edit1->Text + "' ";

            if(DataResumo->tbClientesOperadoras->Active)
            {
            DataResumo->tbClientesOperadoras->EmptyDataSet();
            }

        DataResumo->tbClientesOperadoras->Close();
        DataResumo->tbClientesOperadoras->SQL->Clear();
        DataResumo->tbClientesOperadoras->SQL->Add(consulta);
        DataResumo->tbClientesOperadoras->Open();

            if(DataResumo->tbClientesOperadoras->RecordCount == 1)
            {
            cnpj_cliente = DataResumo->tbClientesOperadorasCNPJ_ESTABELECIMENTO->AsString;
            }

        final_parcelas =  Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsInteger;

        		if(final_parcelas == 0)
                {
                final_parcelas = 1;
                }

            for(int contador_parcelas = 1; contador_parcelas <= final_parcelas; contador_parcelas++)
            {
            //CONTROLE DE DUPLICIDADE
            consulta = "SELECT * FROM vendas where vendas.CNPJ = '" + cnpj_cliente + "'";
            consulta += " and vendas.ADQID = 108";

            Edit1->Text = contador_parcelas;

            consulta += " and vendas.PARCELA = '" + Edit1->Text + "'";

                //PIX
                if(Data3->tbSeguroVendaMEIO_PAGAMENTO->AsInteger == 11)
                {
                consulta += " and vendas.NSU = '" + Data3->tbSeguroVendaCODIGO_TRANSACAO->AsString + "'";
                consulta += " and vendas.AUTORIZACAO = '" + Data3->tbSeguroVendaCODIGO_TRANSACAO->AsString + "'";
                }
                else
                {
                consulta += " and vendas.NSU = '" + Data3->tbSeguroVendaNSU->AsString + "'";
                consulta += " and vendas.AUTORIZACAO = '" + Data3->tbSeguroVendaCODIGO_AUTORIZACAO->AsString + "'";
                }

            Edit1->Text = Data3->tbSeguroVendaDATA_VENDA_AJUSTE->AsString.SubString(7,4) + "-" + Data3->tbSeguroVendaDATA_VENDA_AJUSTE->AsString.SubString(4,2) + "-" + Data3->tbSeguroVendaDATA_VENDA_AJUSTE->AsString.SubString(0,2);

            consulta += " and vendas.DATA_VENDA = '" + Edit1->Text + "'";

                if(DataResumo->tbVendasOperadoras->Active)
                {
                DataResumo->tbVendasOperadoras->EmptyDataSet();
                }

            DataResumo->tbVendasOperadoras->Close();
            DataResumo->tbVendasOperadoras->SQL->Clear();
            DataResumo->tbVendasOperadoras->SQL->Add(consulta);
            DataResumo->tbVendasOperadoras->Open();

                if(DataResumo->tbVendasOperadoras->RecordCount == 0)
                {
                DataResumo->tbVendasOperadoras->Insert();

                //PAGSEGURO
                DataResumo->tbVendasOperadorasADQID->Value = 108;
                DataResumo->tbVendasOperadorasADQUIRENTE->Value = "PAGSEGURO";

                DataResumo->tbVendasOperadorasESTABELECIMENTO->Value = Data3->tbSeguroVendaESTABELECIMENTO->AsAnsiString;

                    //CONFIRMA QUE FOI LOCALIZADO OS DADOS DO CLIENTE / OPERADORA
                    if(DataResumo->tbClientesOperadoras->RecordCount == 1)
                    {
                    //BUSCA OS DADOS DO CLIENTE NA TABELA DE GRUPOS
                    Edit1->Text = DataResumo->tbClientesOperadorasCOD_GRUPO->AsFloat;

                    consulta = "Select * from grupos_clientes where grupos_clientes.CODIGO = '" + Edit1->Text + "' ";

                    Data1->tbGrupos->Close();
                    Data1->tbGrupos->SQL->Clear();
                    Data1->tbGrupos->SQL->Add(consulta);
                    Data1->tbGrupos->Open();

                        if(Data1->tbGrupos->RecordCount == 1)
                        {
                        DataResumo->tbVendasOperadorasEMPRESA->Value = Data1->tbGruposNOME_EMPRESA->AsString;
                        DataResumo->tbVendasOperadorasCNPJ->Value = Data1->tbGruposCNPJ->AsString;
                        DataResumo->tbVendasOperadorasCOD_CLIENTE->Value = Data1->tbGruposCOD_CLIENTE->AsFloat;
                        DataResumo->tbVendasOperadorasCOD_GRUPO_CLIENTE->Value = Data1->tbGruposCODIGO->AsFloat;

                        //MARCA O CLIENTE COMO PENDENTE DE CÁLCULO
                        Edit1->Text = DataResumo->tbVendasOperadorasCOD_CLIENTE->AsFloat;

                        consulta = "Select * from clientes where clientes.CODIGO = '" + Edit1->Text + "' ";

                        Data1->tbClientes->Close();
                        Data1->tbClientes->SQL->Clear();
                        Data1->tbClientes->SQL->Add(consulta);
                        Data1->tbClientes->Open();

                            if(Data1->tbClientes->RecordCount == 1)
                            {
                            Data1->tbClientes->Edit();
                            Data1->tbClientesARQUIVOS_PROCESSADOS->Value = "N";
                            Data1->tbClientes->ApplyUpdates(0);
                            }
                        }
                    }

                    if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 0)
                    {
                    //DÉBITO
                    DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 21;
                    DataResumo->tbVendasOperadorasCODIGO_MODALIDADE->Value = 0;
                    }
                    else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 1)
                    {
                    //CRÉDITO
                    DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 20;
                    DataResumo->tbVendasOperadorasCODIGO_MODALIDADE->Value = 1;
                    }
                    else
                    {
                    //PARCELADO
                    DataResumo->tbVendasOperadorasCODIGO_MODALIDADE->Value = 17;

                        if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 2)
                        {
                        //PARCELADO EM 2X;
                        DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 40;
                        }
                        else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 3)
                        {
                        //PARCELADO EM 3X;
                        DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 41;
                        }
                        else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 4)
                        {
                        //PARCELADO EM 4X;
                        DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 42;
                        }
                        else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 5)
                        {
                        //PARCELADO EM 5X;
                        DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 43;
                        }
                        else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 6)
                        {
                        //PARCELADO EM 6X;
                        DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 44;
                        }
                        else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 7)
                        {
                        //PARCELADO EM 6X;
                        DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 45;
                        }
                        else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 7)
                        {
                        //PARCELADO EM 7X;
                        DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 45;
                        }
                        else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 8)
                        {
                        //PARCELADO EM 8X;
                        DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 46;
                        }
                        else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 9)
                        {
                        //PARCELADO EM 9X;
                        DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 47;
                        }
                        else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 10)
                        {
                        //PARCELADO EM 10X;
                        DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 48;
                        }
                        else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 11)
                        {
                        //PARCELADO EM 11X;
                        DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 50;
                        }
                        else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 12)
                        {
                        //PARCELADO EM 12X;
                        DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 51;
                        }
                        else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 13)
                        {
                        //PARCELADO EM 13X;
                        DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 55;
                        }
                        else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 14)
                        {
                        //PARCELADO EM 14X;
                        DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 56;
                        }
                        else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 15)
                        {
                        //PARCELADO EM 15X;
                        DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 57;
                        }
                        else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 16)
                        {
                        //PARCELADO EM 16X;
                        DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 58;
                        }
                        else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 17)
                        {
                        //PARCELADO EM 16X;
                        DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 59;
                        }
                        else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 18)
                        {
                        //PARCELADO EM 16X;
                        DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 60;
                        }
                    }


                    if(Data3->tbSeguroVendaINSTITUICAO_FINANCEIRA->AsString == "AMEX")
                    {
                    DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 165;
                    }
                    else if(Data3->tbSeguroVendaINSTITUICAO_FINANCEIRA->AsString == "BOLETO")
                    {
                    DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 192;
                    }
                    else if(Data3->tbSeguroVendaINSTITUICAO_FINANCEIRA->AsString == "ELO")
                    {
                    DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 166;
                    }
                    else if(Data3->tbSeguroVendaINSTITUICAO_FINANCEIRA->AsString == "HIPERCARD")
                    {
                    DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 162;
                    }
                    else if(Data3->tbSeguroVendaINSTITUICAO_FINANCEIRA->AsString == "MAESTRO")
                    {
                    DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 160;
                    }
                    else if(Data3->tbSeguroVendaINSTITUICAO_FINANCEIRA->AsString == "MASTERCARD")
                    {
                    DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 160;
                    }
                    else if(Data3->tbSeguroVendaINSTITUICAO_FINANCEIRA->AsString == "VISA")
                    {
                    DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 159;
                    }
                    else if(Data3->tbSeguroVendaINSTITUICAO_FINANCEIRA->AsString == "VISA ELECTRON")
                    {
                    DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 159;
                    }
                    else if(Data3->tbSeguroVendaINSTITUICAO_FINANCEIRA->AsString == "PS_BALANCE")
                    {
                    DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 191;
                    }
                    else if(Data3->tbSeguroVendaINSTITUICAO_FINANCEIRA->AsString == "CABAL")
                    {
                    DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 169;
                    }

                DataResumo->tbVendasOperadorasPARCELA->Value = contador_parcelas;
                DataResumo->tbVendasOperadorasTOTAL_PARCELAS->Value = Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat;

                    if(DataResumo->tbVendasOperadorasTOTAL_PARCELAS->AsFloat == 0)
                    {
                    DataResumo->tbVendasOperadorasTOTAL_PARCELAS->Value = 1;
                    }

                //STATUS = NÃO CONCILIADA
                DataResumo->tbVendasOperadorasCOD_STATUS_CONCILIACAO->Value = 2;

                //STATUS FINANCEIRO = PREVISTO
                DataResumo->tbVendasOperadorasCOD_STATUS_FINANCEIRO->Value = 1;

                DataResumo->tbVendasOperadorasPERC_TAXA_CALC->Value = 'S';

                DataResumo->tbVendasOperadorasTID->Value = Data3->tbSeguroVendaCODIGO_TRANSACAO->AsString;
                DataResumo->tbVendasOperadorasTID_ADICIONAL->Value = Data3->tbSeguroVendaCODIGO_TRANSACAO ->AsString.SubString(1,8);

                    if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsInteger > 0)
                    {
                    DataResumo->tbVendasOperadorasVALOR_BRUTO->Value = Data3->tbSeguroVendaVALOR_TOTAL_TRANSACAO->AsFloat / Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsInteger;
                    DataResumo->tbVendasOperadorasVALOR_TAXA->Value = (Data3->tbSeguroVendaTAXA_INTERMEDIACAO->AsFloat + Data3->tbSeguroVendaTAXA_PARCELA_VENDEDOR->AsFloat) / Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsInteger;
                    DataResumo->tbVendasOperadorasVALOR_LIQUIDO->Value = Data3->tbSeguroVendaVALOR_PARCELA->AsFloat / Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsInteger;

                    DataResumo->tbVendasOperadorasVALOR_BRUTO->Value = SimpleRoundTo(DataResumo->tbVendasOperadorasVALOR_BRUTO->Value, -2);
                    DataResumo->tbVendasOperadorasVALOR_LIQUIDO->Value = SimpleRoundTo(DataResumo->tbVendasOperadorasVALOR_LIQUIDO->Value, -2);
                    DataResumo->tbVendasOperadorasVALOR_TAXA->Value = SimpleRoundTo(DataResumo->tbVendasOperadorasVALOR_TAXA->Value, -2);

                    total_valor = DataResumo->tbVendasOperadorasVALOR_BRUTO->AsFloat * Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsInteger;
                    diferenca = total_valor - Data3->tbSeguroVendaVALOR_TOTAL_TRANSACAO->AsFloat;
                    diferenca = SimpleRoundTo(diferenca, -2);

                	aux_diferenca = (diferenca * 100);

                        if(aux_diferenca < 0)
                            aux_diferenca = aux_diferenca * -1;

                    Edit1->Text = aux_diferenca;
                    auxiliar = StrToInt(Edit1->Text);

                        if(contador_parcelas <= auxiliar)
                        {
                        	if(diferenca > 0)
                            {
                            DataResumo->tbVendasOperadorasVALOR_BRUTO->Value = DataResumo->tbVendasOperadorasVALOR_BRUTO->AsFloat - 0.01;
                            }
                            else
                            {
                            DataResumo->tbVendasOperadorasVALOR_BRUTO->Value = DataResumo->tbVendasOperadorasVALOR_BRUTO->AsFloat + 0.01;
                            }
                        }

                    total_valor = DataResumo->tbVendasOperadorasVALOR_LIQUIDO->AsFloat * Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsInteger;
                    diferenca = total_valor - Data3->tbSeguroVendaVALOR_PARCELA->AsFloat;
                    diferenca = SimpleRoundTo(diferenca, -2);

                    aux_diferenca = (diferenca * 100);

                    	if(aux_diferenca < 0)
                            aux_diferenca = aux_diferenca * -1;

                    Edit1->Text = aux_diferenca;
                    auxiliar = StrToInt(Edit1->Text);

                        if(contador_parcelas <= auxiliar)
                        {
                            if(diferenca > 0)
                            {
                            DataResumo->tbVendasOperadorasVALOR_LIQUIDO->Value = DataResumo->tbVendasOperadorasVALOR_LIQUIDO->AsFloat - 0.01;
                            }
                            else
                            {
                            DataResumo->tbVendasOperadorasVALOR_LIQUIDO->Value = DataResumo->tbVendasOperadorasVALOR_LIQUIDO->AsFloat + 0.01;
                            }
                        }

                    DataResumo->tbVendasOperadorasVALOR_TAXA->Value = DataResumo->tbVendasOperadorasVALOR_BRUTO->AsFloat - DataResumo->tbVendasOperadorasVALOR_LIQUIDO->AsFloat;
                	DataResumo->tbVendasOperadorasVALOR_TAXA->Value = SimpleRoundTo(DataResumo->tbVendasOperadorasVALOR_TAXA->Value, -2);
                    }
                    else
                    {
                    DataResumo->tbVendasOperadorasVALOR_BRUTO->Value = Data3->tbSeguroVendaVALOR_TOTAL_TRANSACAO->AsFloat;
                    DataResumo->tbVendasOperadorasVALOR_TAXA->Value = Data3->tbSeguroVendaTAXA_INTERMEDIACAO->AsFloat + Data3->tbSeguroVendaTAXA_PARCELA_VENDEDOR->AsFloat;
                    DataResumo->tbVendasOperadorasVALOR_LIQUIDO->Value = Data3->tbSeguroVendaVALOR_PARCELA->AsFloat;
                    }

                    if(DataResumo->tbVendasOperadorasVALOR_BRUTO->AsFloat > 0)
                    {
                    DataResumo->tbVendasOperadorasPERCENTUAL_TAXA->Value = ( DataResumo->tbVendasOperadorasVALOR_TAXA->AsFloat / DataResumo->tbVendasOperadorasVALOR_BRUTO->AsFloat) * 100;
                    }

                DataResumo->tbVendasOperadorasDATA_VENDA->Value = Data3->tbSeguroVendaDATA_VENDA_AJUSTE->AsDateTime;
                DataResumo->tbVendasOperadorasHORA_TRANSACAO->Value = Data3->tbSeguroVendaHORA_VENDA_AJUSTE->AsDateTime;
                DataResumo->tbVendasOperadorasNSU->Value = Data3->tbSeguroVendaNSU->AsString;
                DataResumo->tbVendasOperadorasDATA_PREVISTA_PAGTO->Value = dataValida(Data3->tbSeguroVendaDATA_PREVISTA_PAGAMENTO->AsDateTime);
                DataResumo->tbVendasOperadorasAUTORIZACAO->Value = Data3->tbSeguroVendaCODIGO_AUTORIZACAO->AsString;
                DataResumo->tbVendasOperadorasBIN_CARTAO->Value = Data3->tbSeguroVendaCARTAO_BIN->AsString;
                DataResumo->tbVendasOperadorasNUMERO_RESUMO_VENDA->Value = Data3->tbSeguroVendaCODIGO_CV->AsString;
                DataResumo->tbVendasOperadorasOBSERVACOES->Value = "Venda com recebimento único";

                //CONFIGURA O MEIO DE CAPTURA

                    //POS
                    if(Data3->tbSeguroVendaMEIO_CAPTURA->AsInteger == 1 || Data3->tbSeguroVendaMEIO_CAPTURA->AsInteger == 2)
                    {
                    //POS
                    DataResumo->tbVendasOperadorasCOD_MEIO_CAPTURA->Value = 1;
                    }
                    else if(Data3->tbSeguroVendaMEIO_CAPTURA->AsInteger == 3)
                    {
                    //E-COMMERCE
                    DataResumo->tbVendasOperadorasCOD_MEIO_CAPTURA->Value = 3;
                    }
                    else if(Data3->tbSeguroVendaMEIO_CAPTURA->AsInteger == 4)
                    {
                    //TEF
                    DataResumo->tbVendasOperadorasCOD_MEIO_CAPTURA->Value = 2;
                    }

                    //3 = CARTÃO DE CRÉDITO
                    if(Data3->tbSeguroVendaMEIO_PAGAMENTO->AsInteger == 3)
                    {
                        if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat > 1)
                        {
                        //PARCELADO
                        DataResumo->tbVendasOperadorasCODIGO_MODALIDADE->Value = 17;
                        }
                        else if(Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsFloat == 1)
                        {
                        //CRÉDITO
                        DataResumo->tbVendasOperadorasCODIGO_MODALIDADE->Value = 1;
                        }
                    }
                    //8 = CARTÃO DE DÉBITO*
                    else if(Data3->tbSeguroVendaMEIO_PAGAMENTO->AsInteger == 8)
                    {
                    //DÉBITO
                    DataResumo->tbVendasOperadorasCODIGO_MODALIDADE->Value = 0;
                    DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 21;
                    }
                    //MEIO DE PAGAMENTO = 11 = PIX
                    else if(Data3->tbSeguroVendaMEIO_PAGAMENTO->AsInteger == 11)
                    {
                    //PIX
                    DataResumo->tbVendasOperadorasCODIGO_MODALIDADE->Value = 21;
                    DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 53;
                    }


                    if(Data3->tbSeguroVendaCARTAO_BIN->AsString != "" && Data3->tbSeguroVendaCARTAO_HOLDER->AsString != "")
                    {
                    DataResumo->tbVendasOperadorasCARTAO->Value = Data3->tbSeguroVendaCARTAO_BIN->AsString + "******" + Data3->tbSeguroVendaCARTAO_HOLDER->AsString;
                    }


                Edit1->Text = DataResumo->tbVendasOperadorasCOD_CLIENTE->AsFloat;

                consulta = "Select * from domicilio_cliente where domicilio_cliente.COD_CLIENTE = '" + Edit1->Text + "' ";

                Edit1->Text = DataResumo->tbVendasOperadorasCNPJ->AsString;

                consulta = consulta + " and domicilio_cliente.COD_ADQUIRENTE = '108' ";

                    //VERIFICA SE O CLIENTE É DIFERENTE DE MCTINTAS
                    if(DataResumo->tbVendasOperadorasCOD_CLIENTE->AsFloat != 562)
                    {
                    //SE FOR DIFERNETE DE MCTINTAS, BUSCA O CNPJ DA EMPRESA PARA LOCALIZAR O BANCO
                    Edit1->Text = DataResumo->tbVendasOperadorasCNPJ->AsString;

                    consulta = consulta + " and domicilio_cliente.CNPJ = '" + Edit1->Text + "' ";
                    }

                Data1->tbDomicilioCliente->Close();
                Data1->tbDomicilioCliente->SQL->Clear();
                Data1->tbDomicilioCliente->SQL->Add(consulta);
                Data1->tbDomicilioCliente->Open();

                    if(Data1->tbDomicilioCliente->RecordCount == 1)
                    {
                    DataResumo->tbVendasOperadorasBANCO->Value = Data1->tbDomicilioClienteCOD_BANCO->AsInteger;
                    DataResumo->tbVendasOperadorasAGENCIA->Value = Data1->tbDomicilioClienteAGENCIA->AsString;
                    DataResumo->tbVendasOperadorasCONTA->Value = Data1->tbDomicilioClienteCONTA->AsString;
                    }

                    if(DataResumo->tbVendasOperadorasVALOR_TAXA->AsFloat < 0)
                    {
                    DataResumo->tbVendasOperadorasVALOR_TAXA->Value = 0;
                    }

                    if(DataResumo->tbVendasOperadorasCOD_PRODUTO->AsFloat == 53)
                    {
                    DataResumo->tbVendasOperadorasNSU->Value = Data3->tbSeguroVendaCODIGO_TRANSACAO->AsString;
                    DataResumo->tbVendasOperadorasAUTORIZACAO->Value = Data3->tbSeguroVendaCODIGO_TRANSACAO->AsString;
                    DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = 200;
                    }

                DataResumo->tbVendasOperadoras->ApplyUpdates(0);
                }
            }
        }


	Data3->tbSeguroVenda->Edit();
	Data3->tbSeguroVendaTRATADO->Value = 'S';
	Data3->tbSeguroVenda->ApplyUpdates(0);

    Data3->tbSeguroVenda->Next();

	Label6->Caption = contador + 1;
    ProgressBar1->Position = contador + 1;

	Application->ProcessMessages();
	}

Button6Click(Sender);

Edit2->Text = Date();
Edit3->Text = Time();
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::TratarPagamentosPagSeguroClick(TObject *Sender)
{
AnsiString consulta, cnpj_cliente, atualiza, data;
double valor_total_transacao, total_parcelas = 0, diferenca, parcela1, parcela2, parcela3, parcela4, total_valor, aux_diferenca;
int num_parcela = 1, auxiliar;
Word Year, Month, Day;
TDate dtPresent;

//SELECIONA TODAS AS VENDAS DO PAGSEGURO EM TABELA BRUTA AINDA NÃO TRATADOS
Data3->tbSeguroPagamento->Close();
Data3->tbSeguroPagamento->SQL->Clear();
Data3->tbSeguroPagamento->SQL->Add("Select * from edi_pagseguro_pagamento where edi_pagseguro_pagamento.CODIGO is not null and edi_pagseguro_pagamento.TRATADO = 'N' and ( edi_pagseguro_pagamento.MEIO_PAGAMENTO = '3' or edi_pagseguro_pagamento.MEIO_PAGAMENTO = '8' or edi_pagseguro_pagamento.MEIO_PAGAMENTO = '11' ) and edi_pagseguro_pagamento.TIPO_EVENTO = '1'  and edi_pagseguro_pagamento.PAGAMENTO_PRAZO = 'M'");
Data3->tbSeguroPagamento->Open();

Data3->tbSeguroPagamento->Last();
int final = Data3->tbSeguroPagamento->RecordCount;
Data3->tbSeguroPagamento->First();

Label21->Caption = "Tratando Arquivos PagSeguro";
Label2->Caption = "Tratando Pagamentos de Recebimento Múltiplo";
Label10->Caption = 0;
Label6->Caption = 0;
Label7->Caption = final;

ProgressBar1->Max = final;
ProgressBar1->Position = 0;

Application->ProcessMessages();

	//EFETUA ESSE BLOCO ATÉ TRATAR TODAS AS VENDAS
	for(int contador = 0; contador < final; contador++)
	{
    cnpj_cliente = "";

    //LOCALIZA O CLIENTE
    Edit1->Text = Data3->tbSeguroPagamentoESTABELECIMENTO->AsAnsiString;

    consulta = "Select * from cliente_operadora where cliente_operadora.COD_ADQUIRENTE = 108 and cliente_operadora.CODIGO_ESTABELECIMENTO = '" + Edit1->Text + "' ";

        if(DataResumo->tbClientesOperadoras->Active)
        {
        DataResumo->tbClientesOperadoras->EmptyDataSet();
        }

    DataResumo->tbClientesOperadoras->Close();
    DataResumo->tbClientesOperadoras->SQL->Clear();
    DataResumo->tbClientesOperadoras->SQL->Add(consulta);
    DataResumo->tbClientesOperadoras->Open();

        if(DataResumo->tbClientesOperadoras->RecordCount == 1)
        {
        cnpj_cliente = DataResumo->tbClientesOperadorasCNPJ_ESTABELECIMENTO->AsString;
        }

    //CONTROLE DE DUPLICIDADE
    consulta = "Select * from pagamentos_operadoras where pagamentos_operadoras.CNPJ = '" + cnpj_cliente + "'";
    consulta += " and pagamentos_operadoras.COD_ADQUIRENTE = '108' ";

        //PIX
        if(Data3->tbSeguroPagamentoMEIO_PAGAMENTO->AsInteger == 11)
        {
        consulta += " and pagamentos_operadoras.NSU = '" + Data3->tbSeguroPagamentoCODIGO_TRANSACAO->AsString + "'";
        consulta += " and pagamentos_operadoras.CODIGO_AUTORIZACAO = '" + Data3->tbSeguroPagamentoCODIGO_TRANSACAO->AsString + "'";
        }
        else
        {
        consulta += " and pagamentos_operadoras.NSU = '" + Data3->tbSeguroPagamentoNSU->AsString + "'";
        consulta += " and pagamentos_operadoras.CODIGO_AUTORIZACAO = '" + Data3->tbSeguroPagamentoCODIGO_AUTORIZACAO->AsString + "'";
        }

        if(Data3->tbSeguroPagamentoPARCELA->AsFloat == 0)
        {
        Edit1->Text = 1;
        }
        else
        {
        Edit1->Text = Data3->tbSeguroPagamentoPARCELA->AsFloat;
        }

    consulta += " and pagamentos_operadoras.PARCELA = '" + Edit1->Text + "' ";

    Edit1->Text = Data3->tbSeguroPagamentoDATA_INICIAL_TRANSACAO->AsString.SubString(7,4) + "-" + Data3->tbSeguroPagamentoDATA_INICIAL_TRANSACAO->AsString.SubString(4,2) + "-" + Data3->tbSeguroPagamentoDATA_INICIAL_TRANSACAO->AsString.SubString(0,2);
    consulta += " and pagamentos_operadoras.DATA_VENDA = '" + Edit1->Text + "'";

    dtPresent = dataValida(StrToDate(Data3->tbSeguroPagamentoDATA_MOVIMENTACAO->AsString));
    DecodeDate(dtPresent, Year, Month, Day);

    Edit1->Text = Year;
    data = Edit1->Text + "-";
    Edit1->Text = Month;
    data = data + Edit1->Text + "-";
    Edit1->Text = Day;
    data = data + Edit1->Text;

    consulta += " and pagamentos_operadoras.DATA_PAGAMENTO = '" + data + "'";

        if(DataResumo->tbPagamentosOperadoras->Active)
        {
        DataResumo->tbPagamentosOperadoras->EmptyDataSet();
        }

    DataResumo->tbPagamentosOperadoras->Close();
    DataResumo->tbPagamentosOperadoras->SQL->Clear();
    DataResumo->tbPagamentosOperadoras->SQL->Add(consulta);
    DataResumo->tbPagamentosOperadoras->Open();

        if(DataResumo->tbPagamentosOperadoras->RecordCount == 0)
        {
        DataResumo->tbPagamentosOperadoras->Insert();

        //PAGSEGURO
        DataResumo->tbPagamentosOperadorasCOD_ADQUIRENTE->Value = 108;

        DataResumo->tbPagamentosOperadorasID_LOJA->Value = Data3->tbSeguroPagamentoESTABELECIMENTO->AsAnsiString;
        DataResumo->tbPagamentosOperadorasAGENCIA->Value = Data3->tbSeguroPagamentoBANCO_AGENCIA->AsString;
        DataResumo->tbPagamentosOperadorasBANCO->Value = Data3->tbSeguroPagamentoCOD_BANCO->AsString;
        DataResumo->tbPagamentosOperadorasCONTA->Value = Data3->tbSeguroPagamentoCONTA_BANCO->AsString;

            //CONFIRMA QUE FOI LOCALIZADO OS DADOS DO CLIENTE / OPERADORA
            if(DataResumo->tbClientesOperadoras->RecordCount == 1)
            {
            //BUSCA OS DADOS DO CLIENTE NA TABELA DE GRUPOS
            Edit1->Text = DataResumo->tbClientesOperadorasCOD_GRUPO->AsFloat;

            consulta = "Select * from grupos_clientes where grupos_clientes.CODIGO = '" + Edit1->Text + "' ";

            Data1->tbGrupos->Close();
            Data1->tbGrupos->SQL->Clear();
            Data1->tbGrupos->SQL->Add(consulta);
            Data1->tbGrupos->Open();

                if(Data1->tbGrupos->RecordCount == 1)
                {
                DataResumo->tbPagamentosOperadorasEMPRESA->Value = Data1->tbGruposNOME_EMPRESA->AsString;
                DataResumo->tbPagamentosOperadorasCNPJ->Value = Data1->tbGruposCNPJ->AsString;
                DataResumo->tbPagamentosOperadorasCOD_CLIENTE->Value = Data1->tbGruposCOD_CLIENTE->AsFloat;
                DataResumo->tbPagamentosOperadorasCOD_GRUPO_CLIENTE->Value = Data1->tbGruposCODIGO->AsFloat;

                //MARCA O CLIENTE COMO PENDENTE DE CÁLCULO
                Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_CLIENTE->AsFloat;

                consulta = "Select * from clientes where clientes.CODIGO = '" + Edit1->Text + "' ";

                Data1->tbClientes->Close();
                Data1->tbClientes->SQL->Clear();
                Data1->tbClientes->SQL->Add(consulta);
                Data1->tbClientes->Open();

                    if(Data1->tbClientes->RecordCount == 1)
                    {
                    Data1->tbClientes->Edit();
                    Data1->tbClientesARQUIVOS_PROCESSADOS->Value = "N";
                    Data1->tbClientes->ApplyUpdates(0);
                    }
                }
            }

            if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 0)
            {
            //DÉBITO
            DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 21;
            DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 0;
            }
            else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 1)
            {
            //CRÉDITO
            DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 20;
            DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 1;
            }
            else
            {
            //PARCELADO
            DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 17;

                if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 2)
                {
                //PARCELADO EM 2X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 40;
                }
                else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 3)
                {
                //PARCELADO EM 3X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 41;
                }
                else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 4)
                {
                //PARCELADO EM 4X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 42;
                }
                else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 5)
                {
                //PARCELADO EM 5X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 43;
                }
                else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 6)
                {
                //PARCELADO EM 6X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 44;
                }
                else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 7)
                {
                //PARCELADO EM 6X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 45;
                }
                else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 7)
                {
                //PARCELADO EM 7X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 45;
                }
                else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 8)
                {
                //PARCELADO EM 8X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 46;
                }
                else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 9)
                {
                //PARCELADO EM 9X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 47;
                }
                else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 10)
                {
                //PARCELADO EM 10X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 48;
                }
                else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 11)
                {
                //PARCELADO EM 11X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 50;
                }
                else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 12)
                {
                //PARCELADO EM 12X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 51;
                }
                else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 13)
                {
                //PARCELADO EM 13X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 55;
                }
                else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 14)
                {
                //PARCELADO EM 14X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 56;
                }
                else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 15)
                {
                //PARCELADO EM 15X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 57;
                }
                else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 16)
                {
                //PARCELADO EM 16X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 58;
                }
                else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 17)
                {
                //PARCELADO EM 16X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 59;
                }
                else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 18)
                {
                //PARCELADO EM 16X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 60;
                }
            }


            if(Data3->tbSeguroPagamentoINSTITUICAO_FINANCEIRA->AsString == "AMEX")
            {
            DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 165;
            }
            else if(Data3->tbSeguroPagamentoINSTITUICAO_FINANCEIRA->AsString == "BOLETO")
            {
            DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 192;
            }
            else if(Data3->tbSeguroPagamentoINSTITUICAO_FINANCEIRA->AsString == "ELO")
            {
            DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 166;
            }
            else if(Data3->tbSeguroPagamentoINSTITUICAO_FINANCEIRA->AsString == "HIPERCARD")
            {
            DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 162;
            }
            else if(Data3->tbSeguroPagamentoINSTITUICAO_FINANCEIRA->AsString == "MAESTRO")
            {
            DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 160;
            }
            else if(Data3->tbSeguroPagamentoINSTITUICAO_FINANCEIRA->AsString == "MASTERCARD")
            {
            DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 160;
            }
            else if(Data3->tbSeguroPagamentoINSTITUICAO_FINANCEIRA->AsString == "VISA")
            {
            DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 159;
            }
            else if(Data3->tbSeguroPagamentoINSTITUICAO_FINANCEIRA->AsString == "VISA ELECTRON")
            {
            DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 159;
            }
            else if(Data3->tbSeguroPagamentoINSTITUICAO_FINANCEIRA->AsString == "PS_BALANCE")
            {
            DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 191;
            }
            else if(Data3->tbSeguroPagamentoINSTITUICAO_FINANCEIRA->AsString == "CABAL")
            {
            DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 169;
            }

        DataResumo->tbPagamentosOperadorasPARCELA->Value = Data3->tbSeguroPagamentoPARCELA->AsFloat;

            if(DataResumo->tbPagamentosOperadorasPARCELA->AsFloat == 0)
            {
            DataResumo->tbPagamentosOperadorasPARCELA->Value = 1;
            }

        DataResumo->tbPagamentosOperadorasTOTAL_PARCELAS->Value = Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat;

            if(DataResumo->tbPagamentosOperadorasTOTAL_PARCELAS->AsFloat == 0)
            {
            DataResumo->tbPagamentosOperadorasTOTAL_PARCELAS->Value = 1;
            }

        //STATUS = NÃO CONCILIADA
        DataResumo->tbPagamentosOperadorasCOD_STATUS->Value = 2;

        //STATUS FINANCEIRO = PREVISTO
        DataResumo->tbPagamentosOperadorasCOD_STATUS_FINANCEIRO->Value = 1;

        //TIPO DE LANÇAMENTO = PAGAMENTO
        DataResumo->tbPagamentosOperadorasCOD_TIPO_LANCAMENTO->Value = 1;

        //TIPO DE LANÇAMENTO = NORMAL
        DataResumo->tbPagamentosOperadorasCOD_TIPO_PAGAMENTO->Value = 1;

        DataResumo->tbPagamentosOperadorasPERCENTUAL_TAXA_CALC->Value = 'S';

        DataResumo->tbPagamentosOperadorasTID->Value = Data3->tbSeguroPagamentoCODIGO_TRANSACAO->AsString;

            if(Data3->tbSeguroPagamentoPLANO->AsInteger > 1)
            {
            DataResumo->tbPagamentosOperadorasVALOR_BRUTO->Value = Data3->tbSeguroPagamentoVALOR_TOTAL_TRANSACAO->AsFloat / Data3->tbSeguroPagamentoPLANO->AsInteger;
            DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value = (Data3->tbSeguroPagamentoTAXA_INTERMEDIACAO->AsFloat + Data3->tbSeguroPagamentoTAXA_PARCELA_VENDEDOR->AsFloat) / Data3->tbSeguroPagamentoPLANO->AsInteger;
            DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->Value = Data3->tbSeguroPagamentoVALOR_PARCELA->AsFloat;

            DataResumo->tbPagamentosOperadorasVALOR_BRUTO->Value = SimpleRoundTo(DataResumo->tbPagamentosOperadorasVALOR_BRUTO->Value, -2);
            DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->Value = SimpleRoundTo(DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->Value, -2);
            DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value = SimpleRoundTo(DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value, -2);

            total_valor = DataResumo->tbPagamentosOperadorasVALOR_BRUTO->AsFloat * Data3->tbSeguroPagamentoPLANO->AsInteger;
            diferenca = total_valor - Data3->tbSeguroPagamentoVALOR_TOTAL_TRANSACAO->AsFloat;
            diferenca = SimpleRoundTo(diferenca, -2);

            aux_diferenca = (diferenca * 100);

                if(aux_diferenca < 0)
                    aux_diferenca = aux_diferenca * -1;

            Edit1->Text = aux_diferenca;
            auxiliar = StrToInt(Edit1->Text);

                if(DataResumo->tbPagamentosOperadorasTOTAL_PARCELAS->AsInteger <= auxiliar)
                {
                    if(diferenca > 0)
                    {
                    DataResumo->tbPagamentosOperadorasVALOR_BRUTO->Value = DataResumo->tbPagamentosOperadorasVALOR_BRUTO->AsFloat - 0.01;
                    }
                    else
                    {
                    DataResumo->tbPagamentosOperadorasVALOR_BRUTO->Value = DataResumo->tbPagamentosOperadorasVALOR_BRUTO->AsFloat + 0.01;
                    }
                }

            DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value = DataResumo->tbPagamentosOperadorasVALOR_BRUTO->AsFloat - DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->AsFloat;
            DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value = SimpleRoundTo(DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value, -2);
            }
            else
            {
            DataResumo->tbPagamentosOperadorasVALOR_BRUTO->Value = Data3->tbSeguroPagamentoVALOR_TOTAL_TRANSACAO->AsFloat;
            DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value = Data3->tbSeguroPagamentoTAXA_INTERMEDIACAO->AsFloat + Data3->tbSeguroPagamentoTAXA_PARCELA_VENDEDOR->AsFloat;
            DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->Value = Data3->tbSeguroPagamentoVALOR_PARCELA->AsFloat;
            }

            if(DataResumo->tbPagamentosOperadorasVALOR_BRUTO->AsFloat > 0)
            {
            DataResumo->tbPagamentosOperadorasTAXA_PERCENTUAL->Value = ( DataResumo->tbPagamentosOperadorasVALOR_TAXA->AsFloat * 100 ) / DataResumo->tbPagamentosOperadorasVALOR_BRUTO->AsFloat;
            }

        DataResumo->tbPagamentosOperadorasDATA_VENDA->Value = Data3->tbSeguroPagamentoDATA_INICIAL_TRANSACAO->AsDateTime;
        DataResumo->tbPagamentosOperadorasHORA_VENDA->Value = Data3->tbSeguroPagamentoHORA_VENDA_AJUSTE->AsDateTime;
        DataResumo->tbPagamentosOperadorasDATA_PREV_PAG_ORIGINAL->Value = dataValida(Data3->tbSeguroPagamentoDATA_MOVIMENTACAO->AsDateTime);
        DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->Value = dataValida(Data3->tbSeguroPagamentoDATA_MOVIMENTACAO->AsDateTime);
        DataResumo->tbPagamentosOperadorasDATA_PROCESSAMENTO->Value = Date();
        DataResumo->tbPagamentosOperadorasHORA_PROCESSAMENTO->Value = Time();
        DataResumo->tbPagamentosOperadorasNUMERO_RESUMO_VENDA->Value = Data3->tbSeguroPagamentoCODIGO_CV->AsString;


        DataResumo->tbPagamentosOperadorasNSU->Value = Data3->tbSeguroPagamentoNSU->AsString;
        DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->Value = Data3->tbSeguroPagamentoCODIGO_AUTORIZACAO->AsString;
        //CONFIGURA O MEIO DE CAPTURA

            //POS
            if(Data3->tbSeguroPagamentoMEIO_CAPTURA->AsInteger == 1 || Data3->tbSeguroPagamentoMEIO_CAPTURA->AsInteger == 2)
            {
            //POS
            DataResumo->tbPagamentosOperadorasCOD_MEIO_CAPTURA->Value = 1;
            }
            else if(Data3->tbSeguroPagamentoMEIO_CAPTURA->AsInteger == 3)
            {
            //E-COMMERCE
            DataResumo->tbPagamentosOperadorasCOD_MEIO_CAPTURA->Value = 3;
            }
            else if(Data3->tbSeguroPagamentoMEIO_CAPTURA->AsInteger == 4)
            {
            //TEF
            DataResumo->tbPagamentosOperadorasCOD_MEIO_CAPTURA->Value = 2;
            }

            //3 = CARTÃO DE CRÉDITO
            if(Data3->tbSeguroPagamentoMEIO_PAGAMENTO->AsInteger == 3)
            {
                if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat > 1)
                {
                //PARCELADO
                DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 17;
                }
                else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 1)
                {
                //CRÉDITO
                DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 1;
                }
            }
            //8 = CARTÃO DE DÉBITO*
            else if(Data3->tbSeguroPagamentoMEIO_PAGAMENTO->AsInteger == 8)
            {
            //DÉBITO
            DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 0;
            DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 21;
            }
            //MEIO DE PAGAMENTO = 11 = PIX
            else if(Data3->tbSeguroPagamentoMEIO_PAGAMENTO->AsInteger == 11)
            {
            //PIX
            DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 21;
            DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 53;
            }


            if(Data3->tbSeguroPagamentoCARTAO_BIN->AsString != "" && Data3->tbSeguroPagamentoCARTAO_HOLDER->AsString != "")
            {
            DataResumo->tbPagamentosOperadorasNUMERO_CARTAO->Value = Data3->tbSeguroPagamentoCARTAO_BIN->AsString + "******" + Data3->tbSeguroPagamentoCARTAO_HOLDER->AsString;
            }


        Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_CLIENTE->AsFloat;

        consulta = "Select * from domicilio_cliente where domicilio_cliente.COD_CLIENTE = '" + Edit1->Text + "' ";

        Edit1->Text = DataResumo->tbPagamentosOperadorasCNPJ->AsString;

        consulta = consulta + " and domicilio_cliente.COD_ADQUIRENTE = '108' ";

            //VERIFICA SE O CLIENTE É DIFERENTE DE MCTINTAS
            if(DataResumo->tbPagamentosOperadorasCOD_CLIENTE->AsFloat != 562)
            {
            //SE FOR DIFERNETE DE MCTINTAS, BUSCA O CNPJ DA EMPRESA PARA LOCALIZAR O BANCO
            Edit1->Text = DataResumo->tbPagamentosOperadorasCNPJ->AsString;

            consulta = consulta + " and domicilio_cliente.CNPJ = '" + Edit1->Text + "' ";
            }

        Data1->tbDomicilioCliente->Close();
        Data1->tbDomicilioCliente->SQL->Clear();
        Data1->tbDomicilioCliente->SQL->Add(consulta);
        Data1->tbDomicilioCliente->Open();

            if(Data1->tbDomicilioCliente->RecordCount == 1)
            {
            DataResumo->tbPagamentosOperadorasBANCO->Value = Data1->tbDomicilioClienteCOD_BANCO->AsInteger;
            DataResumo->tbPagamentosOperadorasCOD_BANCO->Value = Data1->tbDomicilioClienteCOD_BANCO->AsInteger;
            DataResumo->tbPagamentosOperadorasAGENCIA->Value = Data1->tbDomicilioClienteAGENCIA->AsString;
            DataResumo->tbPagamentosOperadorasCONTA->Value = Data1->tbDomicilioClienteCONTA->AsString;
            }

            if(DataResumo->tbPagamentosOperadorasVALOR_TAXA->AsFloat < 0)
            {
            DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value = 0;
            }

            if(DataResumo->tbPagamentosOperadorasCOD_PRODUTO->AsFloat == 53)
            {
            DataResumo->tbPagamentosOperadorasNSU->Value = Data3->tbSeguroPagamentoCODIGO_TRANSACAO->AsString;
            DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->Value = Data3->tbSeguroPagamentoCODIGO_TRANSACAO->AsString;
            DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 200;
            }

        DataResumo->tbPagamentosOperadoras->ApplyUpdates(0);

        atualiza = "update pagamentos_operadoras set pagamentos_operadoras.VALOR_LIQUIDO = ROUND(pagamentos_operadoras.VALOR_LIQUIDO, 2), pagamentos_operadoras.VALOR_BRUTO = ROUND(pagamentos_operadoras.VALOR_BRUTO, 2) ";
        atualiza += " where pagamentos_operadoras.CODIGO = " + DataResumo->tbPagamentosOperadorasCODIGO->AsString;

        Data1->tbExcluir->Close();
        Data1->tbExcluir->SQL->Clear();
        Data1->tbExcluir->SQL->Add(atualiza);
        Data1->tbExcluir->ExecSQL();

        //TENTA LOCALIZAR A VENDA
        consulta = "SELECT * FROM vendas where vendas.COD_STATUS_FINANCEIRO = '1' and vendas.CNPJ = '" + cnpj_cliente + "'";
        consulta += " and vendas.ADQID = 108";

        consulta += " and vendas.PARCELA = '" + DataResumo->tbPagamentosOperadorasPARCELA->AsString + "'";
        consulta += " and vendas.NSU = '" + DataResumo->tbPagamentosOperadorasNSU->AsString + "'";
        consulta += " and vendas.AUTORIZACAO = '" + DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->AsString + "'";

        Edit1->Text = Data3->tbSeguroPagamentoDATA_INICIAL_TRANSACAO->AsString.SubString(7,4) + "-" + Data3->tbSeguroPagamentoDATA_INICIAL_TRANSACAO->AsString.SubString(4,2) + "-" + Data3->tbSeguroPagamentoDATA_INICIAL_TRANSACAO->AsString.SubString(0,2);

        consulta += " and vendas.DATA_VENDA = '" + Edit1->Text + "'";

            if(DataResumo->tbVendasOperadoras->Active)
            {
            DataResumo->tbVendasOperadoras->EmptyDataSet();
            }

        DataResumo->tbVendasOperadoras->Close();
        DataResumo->tbVendasOperadoras->SQL->Clear();
        DataResumo->tbVendasOperadoras->SQL->Add(consulta);
        DataResumo->tbVendasOperadoras->Open();

            if(DataResumo->tbVendasOperadoras->RecordCount == 1)
            {
            DataResumo->tbPagamentosOperadoras->Edit();

            //CONCILIADA
            DataResumo->tbPagamentosOperadorasCOD_STATUS->Value = 1;

            //STATUS = LIQUIDADO
            DataResumo->tbPagamentosOperadorasCOD_STATUS_FINANCEIRO->Value = 2;

            DataResumo->tbPagamentosOperadorasVINCULADO_VENDA->Value = 'S';
            DataResumo->tbPagamentosOperadorasENCONTRADA_VENDA->Value = 'S';
            DataResumo->tbPagamentosOperadorasCOD_VENDA->Value = DataResumo->tbVendasOperadorasCODIGO->AsFloat;
            DataResumo->tbPagamentosOperadoras->ApplyUpdates(0);

            DataResumo->tbVendasOperadoras->Edit();
            DataResumo->tbVendasOperadorasCOD_STATUS_FINANCEIRO->Value = 2;
            DataResumo->tbVendasOperadorasVINCULADO_PAGAMENTO->Value = 'S';
            DataResumo->tbVendasOperadorasCOD_PAGAMENTO->Value = DataResumo->tbPagamentosOperadorasCODIGO->AsFloat;
            DataResumo->tbVendasOperadorasDATA_PAGAMENTO->Value = DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->AsDateTime;

            DataResumo->tbVendasOperadoras->ApplyUpdates(0);
            }
        }

	Data3->tbSeguroPagamento->Edit();
	Data3->tbSeguroPagamentoTRATADO->Value = 'S';
	Data3->tbSeguroPagamento->ApplyUpdates(0);

	Label6->Caption = contador + 1;
    ProgressBar1->Position = contador + 1;

	Data3->tbSeguroPagamento->Next();
	Application->ProcessMessages();
	}


//SELECIONA TODAS AS VENDAS DO PAGSEGURO EM TABELA BRUTA AINDA NÃO TRATADOS
Data3->tbSeguroPagamento->Close();
Data3->tbSeguroPagamento->SQL->Clear();
Data3->tbSeguroPagamento->SQL->Add("Select * from edi_pagseguro_pagamento where edi_pagseguro_pagamento.CODIGO is not null and edi_pagseguro_pagamento.TRATADO = 'N' and ( edi_pagseguro_pagamento.MEIO_PAGAMENTO = '3' or edi_pagseguro_pagamento.MEIO_PAGAMENTO = '8' or edi_pagseguro_pagamento.MEIO_PAGAMENTO = '11' ) and edi_pagseguro_pagamento.TIPO_EVENTO = '1'  and edi_pagseguro_pagamento.PAGAMENTO_PRAZO = 'U'");
Data3->tbSeguroPagamento->Open();

Data3->tbSeguroPagamento->Last();
final = Data3->tbSeguroPagamento->RecordCount;
Data3->tbSeguroPagamento->First();

int final_parcelas;

Label21->Caption = "Tratando Arquivos PagSeguro";
Label2->Caption = "Tratando Pagamentos de Recebimento Único";
Label10->Caption = 0;
Label6->Caption = 0;
Label7->Caption = final;

ProgressBar1->Max = final;
ProgressBar1->Position = 0;

Application->ProcessMessages();


	//EFETUA ESSE BLOCO ATÉ TRATAR TODAS AS VENDAS
	for(int contador = 0; contador < final; contador++)
	{
    cnpj_cliente = "";

    //LOCALIZA O CLIENTE
    Edit1->Text = Data3->tbSeguroPagamentoESTABELECIMENTO->AsAnsiString;

    consulta = "Select * from cliente_operadora where cliente_operadora.COD_ADQUIRENTE = 108 and cliente_operadora.CODIGO_ESTABELECIMENTO = '" + Edit1->Text + "' ";

        if(DataResumo->tbClientesOperadoras->Active)
        {
        DataResumo->tbClientesOperadoras->EmptyDataSet();
        }

    DataResumo->tbClientesOperadoras->Close();
    DataResumo->tbClientesOperadoras->SQL->Clear();
    DataResumo->tbClientesOperadoras->SQL->Add(consulta);
    DataResumo->tbClientesOperadoras->Open();

        if(DataResumo->tbClientesOperadoras->RecordCount == 1)
        {
        cnpj_cliente = DataResumo->tbClientesOperadorasCNPJ_ESTABELECIMENTO->AsString;
        }

    final_parcelas =  Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsInteger;

        if(final_parcelas == 0)
        {
        final_parcelas = 1;
        }

        for(int contador_parcelas = 1; contador_parcelas <= final_parcelas; contador_parcelas++)
        {
        //CONTROLE DE DUPLICIDADE
        consulta = "Select * from pagamentos_operadoras where pagamentos_operadoras.CNPJ = '" + cnpj_cliente + "'";
        consulta += " and pagamentos_operadoras.COD_ADQUIRENTE = '108' ";

            //PIX
            if(Data3->tbSeguroPagamentoMEIO_PAGAMENTO->AsInteger == 11)
            {
            consulta += " and pagamentos_operadoras.NSU = '" + Data3->tbSeguroPagamentoCODIGO_TRANSACAO->AsString + "'";
            consulta += " and pagamentos_operadoras.CODIGO_AUTORIZACAO = '" + Data3->tbSeguroPagamentoCODIGO_TRANSACAO->AsString + "'";
            }
            else
            {
            consulta += " and pagamentos_operadoras.NSU = '" + Data3->tbSeguroPagamentoNSU->AsString + "'";
            consulta += " and pagamentos_operadoras.CODIGO_AUTORIZACAO = '" + Data3->tbSeguroPagamentoCODIGO_AUTORIZACAO->AsString + "'";
            }

        Edit1->Text = contador_parcelas;
        consulta += " and pagamentos_operadoras.PARCELA = '" + Edit1->Text + "' ";

        Edit1->Text = Data3->tbSeguroPagamentoDATA_INICIAL_TRANSACAO->AsString.SubString(7,4) + "-" + Data3->tbSeguroPagamentoDATA_INICIAL_TRANSACAO->AsString.SubString(4,2) + "-" + Data3->tbSeguroPagamentoDATA_INICIAL_TRANSACAO->AsString.SubString(0,2);
        consulta += " and pagamentos_operadoras.DATA_VENDA = '" + Edit1->Text + "'";

        dtPresent = dataValida(StrToDate(Data3->tbSeguroPagamentoDATA_MOVIMENTACAO->AsString));
        DecodeDate(dtPresent, Year, Month, Day);

        Edit1->Text = Year;
        data = Edit1->Text + "-";
        Edit1->Text = Month;
        data = data + Edit1->Text + "-";
        Edit1->Text = Day;
        data = data + Edit1->Text;

        consulta += " and pagamentos_operadoras.DATA_PAGAMENTO = '" + data + "'";

            if(DataResumo->tbPagamentosOperadoras->Active)
            {
            DataResumo->tbPagamentosOperadoras->EmptyDataSet();
            }

        DataResumo->tbPagamentosOperadoras->Close();
        DataResumo->tbPagamentosOperadoras->SQL->Clear();
        DataResumo->tbPagamentosOperadoras->SQL->Add(consulta);
        DataResumo->tbPagamentosOperadoras->Open();

            if(DataResumo->tbPagamentosOperadoras->RecordCount == 0)
            {
            DataResumo->tbPagamentosOperadoras->Insert();

            //PAGSEGURO
            DataResumo->tbPagamentosOperadorasCOD_ADQUIRENTE->Value = 108;

            DataResumo->tbPagamentosOperadorasID_LOJA->Value = Data3->tbSeguroPagamentoESTABELECIMENTO->AsAnsiString;
            DataResumo->tbPagamentosOperadorasAGENCIA->Value = Data3->tbSeguroPagamentoBANCO_AGENCIA->AsString;
            DataResumo->tbPagamentosOperadorasBANCO->Value = Data3->tbSeguroPagamentoCOD_BANCO->AsString;
            DataResumo->tbPagamentosOperadorasCONTA->Value = Data3->tbSeguroPagamentoCONTA_BANCO->AsString;

                //CONFIRMA QUE FOI LOCALIZADO OS DADOS DO CLIENTE / OPERADORA
                if(DataResumo->tbClientesOperadoras->RecordCount == 1)
                {
                //BUSCA OS DADOS DO CLIENTE NA TABELA DE GRUPOS
                Edit1->Text = DataResumo->tbClientesOperadorasCOD_GRUPO->AsFloat;

                consulta = "Select * from grupos_clientes where grupos_clientes.CODIGO = '" + Edit1->Text + "' ";

                Data1->tbGrupos->Close();
                Data1->tbGrupos->SQL->Clear();
                Data1->tbGrupos->SQL->Add(consulta);
                Data1->tbGrupos->Open();

                    if(Data1->tbGrupos->RecordCount == 1)
                    {
                    DataResumo->tbPagamentosOperadorasEMPRESA->Value = Data1->tbGruposNOME_EMPRESA->AsString;
                    DataResumo->tbPagamentosOperadorasCNPJ->Value = Data1->tbGruposCNPJ->AsString;
                    DataResumo->tbPagamentosOperadorasCOD_CLIENTE->Value = Data1->tbGruposCOD_CLIENTE->AsFloat;
                    DataResumo->tbPagamentosOperadorasCOD_GRUPO_CLIENTE->Value = Data1->tbGruposCODIGO->AsFloat;

                    //MARCA O CLIENTE COMO PENDENTE DE CÁLCULO
                    Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_CLIENTE->AsFloat;

                    consulta = "Select * from clientes where clientes.CODIGO = '" + Edit1->Text + "' ";

                    Data1->tbClientes->Close();
                    Data1->tbClientes->SQL->Clear();
                    Data1->tbClientes->SQL->Add(consulta);
                    Data1->tbClientes->Open();

                        if(Data1->tbClientes->RecordCount == 1)
                        {
                        Data1->tbClientes->Edit();
                        Data1->tbClientesARQUIVOS_PROCESSADOS->Value = "N";
                        Data1->tbClientes->ApplyUpdates(0);
                        }
                    }
                }

                if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 0)
                {
                //DÉBITO
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 21;
                DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 0;
                }
                else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 1)
                {
                //CRÉDITO
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 20;
                DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 1;
                }
                else
                {
                //PARCELADO
                DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 17;

                    if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 2)
                    {
                    //PARCELADO EM 2X;
                    DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 40;
                    }
                    else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 3)
                    {
                    //PARCELADO EM 3X;
                    DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 41;
                    }
                    else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 4)
                    {
                    //PARCELADO EM 4X;
                    DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 42;
                    }
                    else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 5)
                    {
                    //PARCELADO EM 5X;
                    DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 43;
                    }
                    else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 6)
                    {
                    //PARCELADO EM 6X;
                    DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 44;
                    }
                    else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 7)
                    {
                    //PARCELADO EM 6X;
                    DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 45;
                    }
                    else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 7)
                    {
                    //PARCELADO EM 7X;
                    DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 45;
                    }
                    else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 8)
                    {
                    //PARCELADO EM 8X;
                    DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 46;
                    }
                    else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 9)
                    {
                    //PARCELADO EM 9X;
                    DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 47;
                    }
                    else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 10)
                    {
                    //PARCELADO EM 10X;
                    DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 48;
                    }
                    else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 11)
                    {
                    //PARCELADO EM 11X;
                    DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 50;
                    }
                    else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 12)
                    {
                    //PARCELADO EM 12X;
                    DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 51;
                    }
                    else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 13)
                    {
                    //PARCELADO EM 13X;
                    DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 55;
                    }
                    else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 14)
                    {
                    //PARCELADO EM 14X;
                    DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 56;
                    }
                    else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 15)
                    {
                    //PARCELADO EM 15X;
                    DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 57;
                    }
                    else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 16)
                    {
                    //PARCELADO EM 16X;
                    DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 58;
                    }
                    else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 17)
                    {
                    //PARCELADO EM 16X;
                    DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 59;
                    }
                    else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 18)
                    {
                    //PARCELADO EM 16X;
                    DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 60;
                    }
                }


                if(Data3->tbSeguroPagamentoINSTITUICAO_FINANCEIRA->AsString == "AMEX")
                {
                DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 165;
                }
                else if(Data3->tbSeguroPagamentoINSTITUICAO_FINANCEIRA->AsString == "BOLETO")
                {
                DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 192;
                }
                else if(Data3->tbSeguroPagamentoINSTITUICAO_FINANCEIRA->AsString == "ELO")
                {
                DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 166;
                }
                else if(Data3->tbSeguroPagamentoINSTITUICAO_FINANCEIRA->AsString == "HIPERCARD")
                {
                DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 162;
                }
                else if(Data3->tbSeguroPagamentoINSTITUICAO_FINANCEIRA->AsString == "MAESTRO")
                {
                DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 160;
                }
                else if(Data3->tbSeguroPagamentoINSTITUICAO_FINANCEIRA->AsString == "MASTERCARD")
                {
                DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 160;
                }
                else if(Data3->tbSeguroPagamentoINSTITUICAO_FINANCEIRA->AsString == "VISA")
                {
                DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 159;
                }
                else if(Data3->tbSeguroPagamentoINSTITUICAO_FINANCEIRA->AsString == "VISA ELECTRON")
                {
                DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 159;
                }
                else if(Data3->tbSeguroPagamentoINSTITUICAO_FINANCEIRA->AsString == "PS_BALANCE")
                {
                DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 191;
                }
                else if(Data3->tbSeguroPagamentoINSTITUICAO_FINANCEIRA->AsString == "CABAL")
                {
                DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 169;
                }

            DataResumo->tbPagamentosOperadorasPARCELA->Value = contador_parcelas;

            DataResumo->tbPagamentosOperadorasTOTAL_PARCELAS->Value = Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat;

                if(DataResumo->tbPagamentosOperadorasTOTAL_PARCELAS->AsFloat == 0)
                {
                DataResumo->tbPagamentosOperadorasTOTAL_PARCELAS->Value = 1;
                }

            //STATUS = NÃO CONCILIADA
            DataResumo->tbPagamentosOperadorasCOD_STATUS->Value = 2;

            //STATUS FINANCEIRO = PREVISTO
            DataResumo->tbPagamentosOperadorasCOD_STATUS_FINANCEIRO->Value = 1;

            //TIPO DE LANÇAMENTO = PAGAMENTO
            DataResumo->tbPagamentosOperadorasCOD_TIPO_LANCAMENTO->Value = 1;

            //TIPO DE LANÇAMENTO = NORMAL
            DataResumo->tbPagamentosOperadorasCOD_TIPO_PAGAMENTO->Value = 1;

            DataResumo->tbPagamentosOperadorasPERCENTUAL_TAXA_CALC->Value = 'S';

            DataResumo->tbPagamentosOperadorasTID->Value = Data3->tbSeguroPagamentoCODIGO_TRANSACAO->AsString;

                if(Data3->tbSeguroPagamentoPLANO->AsInteger > 1)
                {
                DataResumo->tbPagamentosOperadorasVALOR_BRUTO->Value = Data3->tbSeguroPagamentoVALOR_TOTAL_TRANSACAO->AsFloat / Data3->tbSeguroPagamentoPLANO->AsInteger;
                DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value = (Data3->tbSeguroPagamentoTAXA_INTERMEDIACAO->AsFloat + Data3->tbSeguroPagamentoTAXA_PARCELA_VENDEDOR->AsFloat) / Data3->tbSeguroPagamentoPLANO->AsInteger;
                DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->Value = Data3->tbSeguroPagamentoVALOR_PARCELA->AsFloat / DataResumo->tbPagamentosOperadorasTOTAL_PARCELAS->AsInteger;

                DataResumo->tbPagamentosOperadorasVALOR_BRUTO->Value = SimpleRoundTo(DataResumo->tbPagamentosOperadorasVALOR_BRUTO->Value, -2);
                DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->Value = SimpleRoundTo(DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->Value, -2);
                DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value = SimpleRoundTo(DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value, -2);

                total_valor = DataResumo->tbPagamentosOperadorasVALOR_BRUTO->AsFloat * Data3->tbSeguroPagamentoPLANO->AsInteger;
                diferenca = total_valor - Data3->tbSeguroPagamentoVALOR_TOTAL_TRANSACAO->AsFloat;
                diferenca = SimpleRoundTo(diferenca, -2);

                aux_diferenca = (diferenca * 100);

                    if(aux_diferenca < 0)
                        aux_diferenca = aux_diferenca * -1;

                Edit1->Text = aux_diferenca;
                auxiliar = StrToInt(Edit1->Text);

                    if(DataResumo->tbPagamentosOperadorasTOTAL_PARCELAS->AsInteger <= auxiliar)
                    {
                        if(diferenca > 0)
                        {
                        DataResumo->tbPagamentosOperadorasVALOR_BRUTO->Value = DataResumo->tbPagamentosOperadorasVALOR_BRUTO->AsFloat - 0.01;
                        }
                        else
                        {
                        DataResumo->tbPagamentosOperadorasVALOR_BRUTO->Value = DataResumo->tbPagamentosOperadorasVALOR_BRUTO->AsFloat + 0.01;
                        }
                    }

                total_valor = DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->AsFloat * Data3->tbSeguroPagamentoPLANO->AsInteger;
                diferenca = total_valor - Data3->tbSeguroPagamentoVALOR_PARCELA->AsFloat;
                diferenca = SimpleRoundTo(diferenca, -2);

                aux_diferenca = (diferenca * 100);

                    if(aux_diferenca < 0)
                        aux_diferenca = aux_diferenca * -1;

                Edit1->Text = aux_diferenca;
                auxiliar = StrToInt(Edit1->Text);

                    if(contador_parcelas <= auxiliar)
                    {
                        if(diferenca > 0)
                        {
                        DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->Value = DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->AsFloat - 0.01;
                        }
                        else
                        {
                        DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->Value = DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->AsFloat + 0.01;
                        }
                    }

                DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value = DataResumo->tbPagamentosOperadorasVALOR_BRUTO->AsFloat - DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->AsFloat;
                DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value = SimpleRoundTo(DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value, -2);
                }
                else
                {
                DataResumo->tbPagamentosOperadorasVALOR_BRUTO->Value = Data3->tbSeguroPagamentoVALOR_TOTAL_TRANSACAO->AsFloat;
                DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value = Data3->tbSeguroPagamentoTAXA_INTERMEDIACAO->AsFloat + Data3->tbSeguroPagamentoTAXA_PARCELA_VENDEDOR->AsFloat;
                DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->Value = Data3->tbSeguroPagamentoVALOR_PARCELA->AsFloat;
                }

                if(DataResumo->tbPagamentosOperadorasVALOR_BRUTO->AsFloat > 0)
                {
                DataResumo->tbPagamentosOperadorasTAXA_PERCENTUAL->Value = ( DataResumo->tbPagamentosOperadorasVALOR_TAXA->AsFloat * 100 ) / DataResumo->tbPagamentosOperadorasVALOR_BRUTO->AsFloat;
                }

            DataResumo->tbPagamentosOperadorasDATA_VENDA->Value = Data3->tbSeguroPagamentoDATA_INICIAL_TRANSACAO->AsDateTime;
            DataResumo->tbPagamentosOperadorasHORA_VENDA->Value = Data3->tbSeguroPagamentoHORA_VENDA_AJUSTE->AsDateTime;
            DataResumo->tbPagamentosOperadorasDATA_PREV_PAG_ORIGINAL->Value = dataValida(Data3->tbSeguroPagamentoDATA_MOVIMENTACAO->AsDateTime);
            DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->Value = dataValida(Data3->tbSeguroPagamentoDATA_MOVIMENTACAO->AsDateTime);
            DataResumo->tbPagamentosOperadorasDATA_PROCESSAMENTO->Value = Date();
            DataResumo->tbPagamentosOperadorasHORA_PROCESSAMENTO->Value = Time();
            DataResumo->tbPagamentosOperadorasNUMERO_RESUMO_VENDA->Value = Data3->tbSeguroPagamentoCODIGO_CV->AsString;
            DataResumo->tbPagamentosOperadorasOBSERVACOES->Value = "Venda com recebimento único";

            DataResumo->tbPagamentosOperadorasNSU->Value = Data3->tbSeguroPagamentoNSU->AsString;
            DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->Value = Data3->tbSeguroPagamentoCODIGO_AUTORIZACAO->AsString;
            //CONFIGURA O MEIO DE CAPTURA

                //POS
                if(Data3->tbSeguroPagamentoMEIO_CAPTURA->AsInteger == 1 || Data3->tbSeguroPagamentoMEIO_CAPTURA->AsInteger == 2)
                {
                //POS
                DataResumo->tbPagamentosOperadorasCOD_MEIO_CAPTURA->Value = 1;
                }
                else if(Data3->tbSeguroPagamentoMEIO_CAPTURA->AsInteger == 3)
                {
                //E-COMMERCE
                DataResumo->tbPagamentosOperadorasCOD_MEIO_CAPTURA->Value = 3;
                }
                else if(Data3->tbSeguroPagamentoMEIO_CAPTURA->AsInteger == 4)
                {
                //TEF
                DataResumo->tbPagamentosOperadorasCOD_MEIO_CAPTURA->Value = 2;
                }

                //3 = CARTÃO DE CRÉDITO
                if(Data3->tbSeguroPagamentoMEIO_PAGAMENTO->AsInteger == 3)
                {
                    if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat > 1)
                    {
                    //PARCELADO
                    DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 17;
                    }
                    else if(Data3->tbSeguroPagamentoQUANTIDADE_PARCELA->AsFloat == 1)
                    {
                    //CRÉDITO
                    DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 1;
                    }
                }
                //8 = CARTÃO DE DÉBITO*
                else if(Data3->tbSeguroPagamentoMEIO_PAGAMENTO->AsInteger == 8)
                {
                //DÉBITO
                DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 0;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 21;
                }
                //MEIO DE PAGAMENTO = 11 = PIX
                else if(Data3->tbSeguroPagamentoMEIO_PAGAMENTO->AsInteger == 11)
                {
                //PIX
                DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 21;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 53;
                }


                if(Data3->tbSeguroPagamentoCARTAO_BIN->AsString != "" && Data3->tbSeguroPagamentoCARTAO_HOLDER->AsString != "")
                {
                DataResumo->tbPagamentosOperadorasNUMERO_CARTAO->Value = Data3->tbSeguroPagamentoCARTAO_BIN->AsString + "******" + Data3->tbSeguroPagamentoCARTAO_HOLDER->AsString;
                }


            Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_CLIENTE->AsFloat;

            consulta = "Select * from domicilio_cliente where domicilio_cliente.COD_CLIENTE = '" + Edit1->Text + "' ";

            Edit1->Text = DataResumo->tbPagamentosOperadorasCNPJ->AsString;

            consulta = consulta + " and domicilio_cliente.COD_ADQUIRENTE = '108' ";

                //VERIFICA SE O CLIENTE É DIFERENTE DE MCTINTAS
                if(DataResumo->tbPagamentosOperadorasCOD_CLIENTE->AsFloat != 562)
                {
                //SE FOR DIFERNETE DE MCTINTAS, BUSCA O CNPJ DA EMPRESA PARA LOCALIZAR O BANCO
                Edit1->Text = DataResumo->tbPagamentosOperadorasCNPJ->AsString;

                consulta = consulta + " and domicilio_cliente.CNPJ = '" + Edit1->Text + "' ";
                }

            Data1->tbDomicilioCliente->Close();
            Data1->tbDomicilioCliente->SQL->Clear();
            Data1->tbDomicilioCliente->SQL->Add(consulta);
            Data1->tbDomicilioCliente->Open();

                if(Data1->tbDomicilioCliente->RecordCount == 1)
                {
                DataResumo->tbPagamentosOperadorasBANCO->Value = Data1->tbDomicilioClienteCOD_BANCO->AsInteger;
                DataResumo->tbPagamentosOperadorasCOD_BANCO->Value = Data1->tbDomicilioClienteCOD_BANCO->AsInteger;
                DataResumo->tbPagamentosOperadorasAGENCIA->Value = Data1->tbDomicilioClienteAGENCIA->AsString;
                DataResumo->tbPagamentosOperadorasCONTA->Value = Data1->tbDomicilioClienteCONTA->AsString;
                }

                if(DataResumo->tbPagamentosOperadorasVALOR_TAXA->AsFloat < 0)
                {
                DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value = 0;
                }

                if(DataResumo->tbPagamentosOperadorasCOD_PRODUTO->AsFloat == 53)
                {
                DataResumo->tbPagamentosOperadorasNSU->Value = Data3->tbSeguroPagamentoCODIGO_TRANSACAO->AsString;
                DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->Value = Data3->tbSeguroPagamentoCODIGO_TRANSACAO->AsString;
                DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 200;
                }

            DataResumo->tbPagamentosOperadoras->ApplyUpdates(0);

            atualiza = "update pagamentos_operadoras set pagamentos_operadoras.VALOR_LIQUIDO = ROUND(pagamentos_operadoras.VALOR_LIQUIDO, 2), pagamentos_operadoras.VALOR_BRUTO = ROUND(pagamentos_operadoras.VALOR_BRUTO, 2) ";
            atualiza += " where pagamentos_operadoras.CODIGO = " + DataResumo->tbPagamentosOperadorasCODIGO->AsString;

            Data1->tbExcluir->Close();
            Data1->tbExcluir->SQL->Clear();
            Data1->tbExcluir->SQL->Add(atualiza);
            Data1->tbExcluir->ExecSQL();

            //TENTA LOCALIZAR A VENDA
            consulta = "SELECT * FROM vendas where vendas.COD_STATUS_FINANCEIRO = '1' and vendas.CNPJ = '" + cnpj_cliente + "'";
            consulta += " and vendas.ADQID = 108";

            consulta += " and vendas.PARCELA = '" + DataResumo->tbPagamentosOperadorasPARCELA->AsString + "'";
            consulta += " and vendas.NSU = '" + DataResumo->tbPagamentosOperadorasNSU->AsString + "'";
            consulta += " and vendas.AUTORIZACAO = '" + DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->AsString + "'";

            Edit1->Text = Data3->tbSeguroPagamentoDATA_INICIAL_TRANSACAO->AsString.SubString(7,4) + "-" + Data3->tbSeguroPagamentoDATA_INICIAL_TRANSACAO->AsString.SubString(4,2) + "-" + Data3->tbSeguroPagamentoDATA_INICIAL_TRANSACAO->AsString.SubString(0,2);

            consulta += " and vendas.DATA_VENDA = '" + Edit1->Text + "'";

                if(DataResumo->tbVendasOperadoras->Active)
                {
                DataResumo->tbVendasOperadoras->EmptyDataSet();
                }

            DataResumo->tbVendasOperadoras->Close();
            DataResumo->tbVendasOperadoras->SQL->Clear();
            DataResumo->tbVendasOperadoras->SQL->Add(consulta);
            DataResumo->tbVendasOperadoras->Open();

                if(DataResumo->tbVendasOperadoras->RecordCount == 1)
                {
                DataResumo->tbPagamentosOperadoras->Edit();

                //CONCILIADA
                DataResumo->tbPagamentosOperadorasCOD_STATUS->Value = 1;

                //STATUS = LIQUIDADO
                DataResumo->tbPagamentosOperadorasCOD_STATUS_FINANCEIRO->Value = 2;

                DataResumo->tbPagamentosOperadorasVINCULADO_VENDA->Value = 'S';
                DataResumo->tbPagamentosOperadorasENCONTRADA_VENDA->Value = 'S';
                DataResumo->tbPagamentosOperadorasCOD_VENDA->Value = DataResumo->tbVendasOperadorasCODIGO->AsFloat;
                DataResumo->tbPagamentosOperadoras->ApplyUpdates(0);

                DataResumo->tbVendasOperadoras->Edit();
                DataResumo->tbVendasOperadorasCOD_STATUS_FINANCEIRO->Value = 2;
                DataResumo->tbVendasOperadorasVINCULADO_PAGAMENTO->Value = 'S';
                DataResumo->tbVendasOperadorasCOD_PAGAMENTO->Value = DataResumo->tbPagamentosOperadorasCODIGO->AsFloat;
                DataResumo->tbVendasOperadorasDATA_PAGAMENTO->Value = DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->AsDateTime;

                DataResumo->tbVendasOperadoras->ApplyUpdates(0);
                }
            }
        }

	Data3->tbSeguroPagamento->Edit();
	Data3->tbSeguroPagamentoTRATADO->Value = 'S';
	Data3->tbSeguroPagamento->ApplyUpdates(0);

	Label6->Caption = contador + 1;
    ProgressBar1->Position = contador + 1;

	Data3->tbSeguroPagamento->Next();
	Application->ProcessMessages();
	}

Button6Click(Sender);

Edit2->Text = Date();
Edit3->Text = Time();
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::TratarAntecipacoesPagSeguroClick(TObject *Sender)
{
AnsiString consulta, cnpj_cliente, atualiza, data;
double valor_total_transacao, total_parcelas = 0, diferenca, parcela1, parcela2, parcela3, parcela4, total_valor, aux_diferenca;
int num_parcela = 1, auxiliar;
Word Year, Month, Day;
TDate dtPresent;

//SELECIONA TODAS AS VENDAS DO PAGSEGURO EM TABELA BRUTA AINDA NÃO TRATADOS
Data3->tbSeguroAntecipacao->Close();
Data3->tbSeguroAntecipacao->SQL->Clear();
Data3->tbSeguroAntecipacao->SQL->Add("Select * from edi_pagseguro_antecipacao where edi_pagseguro_antecipacao.TRATADO = 'N'");
Data3->tbSeguroAntecipacao->Open();

Data3->tbSeguroAntecipacao->Last();
int final = Data3->tbSeguroAntecipacao->RecordCount;
Data3->tbSeguroAntecipacao->First();

Label21->Caption = "Tratando Arquivos PagSeguro";
Label2->Caption = "Tratando Antecipações";
Label10->Caption = 0;
Label6->Caption = 0;
Label7->Caption = final;

ProgressBar1->Max = final;
ProgressBar1->Position = 0;

Application->ProcessMessages();

	//EFETUA ESSE BLOCO ATÉ TRATAR TODAS AS VENDAS
	for(int contador = 0; contador < final; contador++)
	{
    cnpj_cliente = "";

    //LOCALIZA O CLIENTE
    Edit1->Text = Data3->tbSeguroAntecipacaoESTABELECIMENTO->AsAnsiString;

    consulta = "Select * from cliente_operadora where cliente_operadora.COD_ADQUIRENTE = 108";
    consulta += " and cliente_operadora.CODIGO_ESTABELECIMENTO = '" + Edit1->Text + "' ";

        if(DataResumo->tbClientesOperadoras->Active)
        {
        DataResumo->tbClientesOperadoras->EmptyDataSet();
        }

    DataResumo->tbClientesOperadoras->Close();
    DataResumo->tbClientesOperadoras->SQL->Clear();
    DataResumo->tbClientesOperadoras->SQL->Add(consulta);
    DataResumo->tbClientesOperadoras->Open();

        if(DataResumo->tbClientesOperadoras->RecordCount == 1)
        {
        cnpj_cliente = DataResumo->tbClientesOperadorasCNPJ_ESTABELECIMENTO->AsString;
        }

    //CONTROLE DE DUPLICIDADE
    consulta = "Select * from pagamentos_operadoras where pagamentos_operadoras.CNPJ = '" + cnpj_cliente + "'";
    consulta += " and pagamentos_operadoras.COD_ADQUIRENTE = '108' ";
    consulta += " and pagamentos_operadoras.NSU = '" + Data3->tbSeguroAntecipacaoNSU->AsString + "'";
    consulta += " and pagamentos_operadoras.CODIGO_AUTORIZACAO = '" + Data3->tbSeguroAntecipacaoCODIGO_AUTORIZACAO->AsString + "'";


        if(Data3->tbSeguroAntecipacaoPARCELA->AsFloat == 0)
        {
        Edit1->Text = 1;
        }
        else
        {
        Edit1->Text = Data3->tbSeguroAntecipacaoPARCELA->AsFloat;
        }

    consulta += " and pagamentos_operadoras.PARCELA = '" + Edit1->Text + "' ";

    //TIPO DE PAGAMENTO ANTECIPADO
    consulta +=" and pagamentos_operadoras.COD_TIPO_PAGAMENTO = '2' ";

    Edit1->Text = Data3->tbSeguroAntecipacaoDATA_INICIAL_TRANSACAO->AsString.SubString(7,4) + "-" + Data3->tbSeguroAntecipacaoDATA_INICIAL_TRANSACAO->AsString.SubString(4,2) + "-" + Data3->tbSeguroAntecipacaoDATA_INICIAL_TRANSACAO->AsString.SubString(0,2);
    consulta += " and pagamentos_operadoras.DATA_VENDA = '" + Edit1->Text + "'";

    dtPresent = dataValida(StrToDate(Data3->tbSeguroAntecipacaoDATA_MOVIMENTACAO->AsString));
    DecodeDate(dtPresent, Year, Month, Day);

    Edit1->Text = Year;
    data = Edit1->Text + "-";
    Edit1->Text = Month;
    data = data + Edit1->Text + "-";
    Edit1->Text = Day;
    data = data + Edit1->Text;

    consulta += " and pagamentos_operadoras.DATA_PAGAMENTO = '" + data + "'";

        if(DataResumo->tbPagamentosOperadoras->Active)
        {
        DataResumo->tbPagamentosOperadoras->EmptyDataSet();
        }

    DataResumo->tbPagamentosOperadoras->Close();
    DataResumo->tbPagamentosOperadoras->SQL->Clear();
    DataResumo->tbPagamentosOperadoras->SQL->Add(consulta);
    DataResumo->tbPagamentosOperadoras->Open();

        if(DataResumo->tbPagamentosOperadoras->RecordCount == 0)
        {
        DataResumo->tbPagamentosOperadoras->Insert();

        //PAGSEGURO
        DataResumo->tbPagamentosOperadorasCOD_ADQUIRENTE->Value = 108;

        DataResumo->tbPagamentosOperadorasID_LOJA->Value = Data3->tbSeguroAntecipacaoESTABELECIMENTO->AsAnsiString;

            //CONFIRMA QUE FOI LOCALIZADO OS DADOS DO CLIENTE / OPERADORA
            if(DataResumo->tbClientesOperadoras->RecordCount == 1)
            {
            //BUSCA OS DADOS DO CLIENTE NA TABELA DE GRUPOS
            Edit1->Text = DataResumo->tbClientesOperadorasCOD_GRUPO->AsFloat;

            consulta = "Select * from grupos_clientes where grupos_clientes.CODIGO = '" + Edit1->Text + "' ";

            Data1->tbGrupos->Close();
            Data1->tbGrupos->SQL->Clear();
            Data1->tbGrupos->SQL->Add(consulta);
            Data1->tbGrupos->Open();

                if(Data1->tbGrupos->RecordCount == 1)
                {
                DataResumo->tbPagamentosOperadorasEMPRESA->Value = Data1->tbGruposNOME_EMPRESA->AsString;
                DataResumo->tbPagamentosOperadorasCNPJ->Value = Data1->tbGruposCNPJ->AsString;
                DataResumo->tbPagamentosOperadorasCOD_CLIENTE->Value = Data1->tbGruposCOD_CLIENTE->AsFloat;
                DataResumo->tbPagamentosOperadorasCOD_GRUPO_CLIENTE->Value = Data1->tbGruposCODIGO->AsFloat;

                //MARCA O CLIENTE COMO PENDENTE DE CÁLCULO
                Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_CLIENTE->AsFloat;

                consulta = "Select * from clientes where clientes.CODIGO = '" + Edit1->Text + "' ";

                Data1->tbClientes->Close();
                Data1->tbClientes->SQL->Clear();
                Data1->tbClientes->SQL->Add(consulta);
                Data1->tbClientes->Open();

                    if(Data1->tbClientes->RecordCount == 1)
                    {
                    Data1->tbClientes->Edit();
                    Data1->tbClientesARQUIVOS_PROCESSADOS->Value = "N";
                    Data1->tbClientes->ApplyUpdates(0);
                    }
                }
            }

            if(Data3->tbSeguroAntecipacaoQUANTIDADE_PARCELA->AsFloat == 0)
            {
            //DÉBITO
            DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 21;
            DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 0;
            }
            else if(Data3->tbSeguroAntecipacaoQUANTIDADE_PARCELA->AsFloat == 1)
            {
            //CRÉDITO
            DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 20;
            DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 1;
            }
            else
            {
            //PARCELADO
            DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 17;

                if(Data3->tbSeguroAntecipacaoQUANTIDADE_PARCELA->AsFloat == 2)
                {
                //PARCELADO EM 2X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 40;
                }
                else if(Data3->tbSeguroAntecipacaoQUANTIDADE_PARCELA->AsFloat == 3)
                {
                //PARCELADO EM 3X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 41;
                }
                else if(Data3->tbSeguroAntecipacaoQUANTIDADE_PARCELA->AsFloat == 4)
                {
                //PARCELADO EM 4X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 42;
                }
                else if(Data3->tbSeguroAntecipacaoQUANTIDADE_PARCELA->AsFloat == 5)
                {
                //PARCELADO EM 5X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 43;
                }
                else if(Data3->tbSeguroAntecipacaoQUANTIDADE_PARCELA->AsFloat == 6)
                {
                //PARCELADO EM 6X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 44;
                }
                else if(Data3->tbSeguroAntecipacaoQUANTIDADE_PARCELA->AsFloat == 7)
                {
                //PARCELADO EM 6X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 45;
                }
                else if(Data3->tbSeguroAntecipacaoQUANTIDADE_PARCELA->AsFloat == 7)
                {
                //PARCELADO EM 7X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 45;
                }
                else if(Data3->tbSeguroAntecipacaoQUANTIDADE_PARCELA->AsFloat == 8)
                {
                //PARCELADO EM 8X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 46;
                }
                else if(Data3->tbSeguroAntecipacaoQUANTIDADE_PARCELA->AsFloat == 9)
                {
                //PARCELADO EM 9X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 47;
                }
                else if(Data3->tbSeguroAntecipacaoQUANTIDADE_PARCELA->AsFloat == 10)
                {
                //PARCELADO EM 10X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 48;
                }
                else if(Data3->tbSeguroAntecipacaoQUANTIDADE_PARCELA->AsFloat == 11)
                {
                //PARCELADO EM 11X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 50;
                }
                else if(Data3->tbSeguroAntecipacaoQUANTIDADE_PARCELA->AsFloat == 12)
                {
                //PARCELADO EM 12X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 51;
                }
                else if(Data3->tbSeguroAntecipacaoQUANTIDADE_PARCELA->AsFloat == 13)
                {
                //PARCELADO EM 13X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 55;
                }
                else if(Data3->tbSeguroAntecipacaoQUANTIDADE_PARCELA->AsFloat == 14)
                {
                //PARCELADO EM 14X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 56;
                }
                else if(Data3->tbSeguroAntecipacaoQUANTIDADE_PARCELA->AsFloat == 15)
                {
                //PARCELADO EM 15X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 57;
                }
                else if(Data3->tbSeguroAntecipacaoQUANTIDADE_PARCELA->AsFloat == 16)
                {
                //PARCELADO EM 16X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 58;
                }
                else if(Data3->tbSeguroAntecipacaoQUANTIDADE_PARCELA->AsFloat == 17)
                {
                //PARCELADO EM 16X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 59;
                }
                else if(Data3->tbSeguroAntecipacaoQUANTIDADE_PARCELA->AsFloat == 18)
                {
                //PARCELADO EM 16X;
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 60;
                }
            }




        DataResumo->tbPagamentosOperadorasPARCELA->Value = Data3->tbSeguroAntecipacaoPARCELA->AsFloat;

            if(DataResumo->tbPagamentosOperadorasPARCELA->AsFloat == 0)
            {
            DataResumo->tbPagamentosOperadorasPARCELA->Value = 1;
            }

        DataResumo->tbPagamentosOperadorasTOTAL_PARCELAS->Value = Data3->tbSeguroAntecipacaoQUANTIDADE_PARCELA->AsFloat;

            if(DataResumo->tbPagamentosOperadorasTOTAL_PARCELAS->AsFloat == 0)
            {
            DataResumo->tbPagamentosOperadorasTOTAL_PARCELAS->Value = 1;
            }

        //STATUS = NÃO CONCILIADA
        DataResumo->tbPagamentosOperadorasCOD_STATUS->Value = 2;

        //STATUS FINANCEIRO = PREVISTO
        DataResumo->tbPagamentosOperadorasCOD_STATUS_FINANCEIRO->Value = 1;

        //TIPO DE LANÇAMENTO = PAGAMENTO
        DataResumo->tbPagamentosOperadorasCOD_TIPO_LANCAMENTO->Value = 1;

        //TIPO DE LANÇAMENTO = antecipado
        DataResumo->tbPagamentosOperadorasCOD_TIPO_PAGAMENTO->Value = 2;

        DataResumo->tbPagamentosOperadorasPERCENTUAL_TAXA_CALC->Value = 'S';

        DataResumo->tbPagamentosOperadorasTID->Value = Data3->tbSeguroAntecipacaoCODIGO_TRANSACAO->AsString;

            if(Data3->tbSeguroAntecipacaoPLANO->AsInteger > 1)
            {
            DataResumo->tbPagamentosOperadorasVALOR_BRUTO->Value = Data3->tbSeguroAntecipacaoVALOR_TOTAL_TRANSACAO->AsFloat / Data3->tbSeguroAntecipacaoPLANO->AsInteger;
            DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value = (Data3->tbSeguroAntecipacaoTAXA_INTERMEDIACAO->AsFloat + Data3->tbSeguroAntecipacaoTAXA_PARCELA_VENDEDOR->AsFloat) / Data3->tbSeguroAntecipacaoPLANO->AsInteger;
            DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->Value = Data3->tbSeguroAntecipacaoVALOR_PARCELA->AsFloat;

            DataResumo->tbPagamentosOperadorasVALOR_BRUTO->Value = SimpleRoundTo(DataResumo->tbPagamentosOperadorasVALOR_BRUTO->Value, -2);
            DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->Value = SimpleRoundTo(DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->Value, -2);
            DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value = SimpleRoundTo(DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value, -2);

            total_valor = DataResumo->tbPagamentosOperadorasVALOR_BRUTO->AsFloat * Data3->tbSeguroAntecipacaoPLANO->AsInteger;
            diferenca = total_valor - Data3->tbSeguroAntecipacaoVALOR_TOTAL_TRANSACAO->AsFloat;
            diferenca = SimpleRoundTo(diferenca, -2);

            aux_diferenca = (diferenca * 100);

                if(aux_diferenca < 0)
                    aux_diferenca = aux_diferenca * -1;

            Edit1->Text = aux_diferenca;
            auxiliar = StrToInt(Edit1->Text);

                if(DataResumo->tbPagamentosOperadorasTOTAL_PARCELAS->AsInteger <= auxiliar)
                {
                    if(diferenca > 0)
                    {
                    DataResumo->tbPagamentosOperadorasVALOR_BRUTO->Value = DataResumo->tbPagamentosOperadorasVALOR_BRUTO->AsFloat - 0.01;
                    }
                    else
                    {
                    DataResumo->tbPagamentosOperadorasVALOR_BRUTO->Value = DataResumo->tbPagamentosOperadorasVALOR_BRUTO->AsFloat + 0.01;
                    }
                }

            DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value = DataResumo->tbPagamentosOperadorasVALOR_BRUTO->AsFloat - DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->AsFloat;
            DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value = SimpleRoundTo(DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value, -2);
            }
            else
            {
            DataResumo->tbPagamentosOperadorasVALOR_BRUTO->Value = Data3->tbSeguroAntecipacaoVALOR_TOTAL_TRANSACAO->AsFloat;
            DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->Value = Data3->tbSeguroAntecipacaoVALOR_PARCELA->AsFloat;
            DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value = DataResumo->tbPagamentosOperadorasVALOR_BRUTO->AsFloat - DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->AsFloat;
            }

            if(DataResumo->tbPagamentosOperadorasVALOR_BRUTO->AsFloat > 0)
            {
            DataResumo->tbPagamentosOperadorasTAXA_PERCENTUAL->Value = ( DataResumo->tbPagamentosOperadorasVALOR_TAXA->AsFloat * 100 ) / DataResumo->tbPagamentosOperadorasVALOR_BRUTO->AsFloat;
            }

        DataResumo->tbPagamentosOperadorasVALOR_TAXA_ANTECIPACAO->Value = Data3->tbSeguroAntecipacaoTAXA_ANTECIPACAO->AsFloat;
        DataResumo->tbPagamentosOperadorasTAXA_ANTECIPACAO->Value = ( DataResumo->tbPagamentosOperadorasVALOR_TAXA_ANTECIPACAO->AsFloat * 100 ) / DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->AsFloat;
        DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->Value = Data3->tbSeguroAntecipacaoVALOR_LIQUIDO_ANTECIPADO->AsFloat;

        DataResumo->tbPagamentosOperadorasDATA_VENDA->Value = Data3->tbSeguroAntecipacaoDATA_INICIAL_TRANSACAO->AsDateTime;
        DataResumo->tbPagamentosOperadorasHORA_VENDA->Value = Data3->tbSeguroAntecipacaoHORA_VENDA_AJUSTE->AsDateTime;
        DataResumo->tbPagamentosOperadorasDATA_PREV_PAG_ORIGINAL->Value = dataValida(Data3->tbSeguroAntecipacaoDATA_MOVIMENTACAO->AsDateTime);
        DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->Value = dataValida(Data3->tbSeguroAntecipacaoDATA_MOVIMENTACAO->AsDateTime);
        DataResumo->tbPagamentosOperadorasDATA_PROCESSAMENTO->Value = Date();
        DataResumo->tbPagamentosOperadorasHORA_PROCESSAMENTO->Value = Time();
        DataResumo->tbPagamentosOperadorasNUMERO_RESUMO_VENDA->Value = Data3->tbSeguroAntecipacaoCODIGO_CV->AsString;

        DataResumo->tbPagamentosOperadorasNSU->Value = Data3->tbSeguroAntecipacaoNSU->AsString;
        DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->Value = Data3->tbSeguroAntecipacaoCODIGO_AUTORIZACAO->AsString;
        //CONFIGURA O MEIO DE CAPTURA

            //POS
            if(Data3->tbSeguroAntecipacaoMEIO_CAPTURA->AsInteger == 1 || Data3->tbSeguroAntecipacaoMEIO_CAPTURA->AsInteger == 2)
            {
            //POS
            DataResumo->tbPagamentosOperadorasCOD_MEIO_CAPTURA->Value = 1;
            }
            else if(Data3->tbSeguroAntecipacaoMEIO_CAPTURA->AsInteger == 3)
            {
            //E-COMMERCE
            DataResumo->tbPagamentosOperadorasCOD_MEIO_CAPTURA->Value = 3;
            }
            else if(Data3->tbSeguroAntecipacaoMEIO_CAPTURA->AsInteger == 4)
            {
            //TEF
            DataResumo->tbPagamentosOperadorasCOD_MEIO_CAPTURA->Value = 2;
            }

            //3 = CARTÃO DE CRÉDITO
            if(Data3->tbSeguroAntecipacaoMEIO_PAGAMENTO->AsInteger == 3)
            {
                if(Data3->tbSeguroAntecipacaoQUANTIDADE_PARCELA->AsFloat > 1)
                {
                //PARCELADO
                DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 17;
                }
                else if(Data3->tbSeguroAntecipacaoQUANTIDADE_PARCELA->AsFloat == 1)
                {
                //CRÉDITO
                DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 1;
                }
            }
            //8 = CARTÃO DE DÉBITO*
            else if(Data3->tbSeguroAntecipacaoMEIO_PAGAMENTO->AsInteger == 8)
            {
            //DÉBITO
            DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 0;
            DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 21;
            }
            //MEIO DE PAGAMENTO = 11 = PIX
            else if(Data3->tbSeguroAntecipacaoMEIO_PAGAMENTO->AsInteger == 11)
            {
            //PIX
            DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 21;
            DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 53;
            }


            if(Data3->tbSeguroAntecipacaoCARTAO_BIN->AsString != "" && Data3->tbSeguroAntecipacaoCARTAO_HOLDER->AsString != "")
            {
            DataResumo->tbPagamentosOperadorasNUMERO_CARTAO->Value = Data3->tbSeguroAntecipacaoCARTAO_BIN->AsString + "******" + Data3->tbSeguroAntecipacaoCARTAO_HOLDER->AsString;
            }


        Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_CLIENTE->AsFloat;

        consulta = "Select * from domicilio_cliente where domicilio_cliente.COD_CLIENTE = '" + Edit1->Text + "' ";

        Edit1->Text = DataResumo->tbPagamentosOperadorasCNPJ->AsString;

        consulta = consulta + " and domicilio_cliente.COD_ADQUIRENTE = '108' ";

            //VERIFICA SE O CLIENTE É DIFERENTE DE MCTINTAS
            if(DataResumo->tbPagamentosOperadorasCOD_CLIENTE->AsFloat != 562)
            {
            //SE FOR DIFERNETE DE MCTINTAS, BUSCA O CNPJ DA EMPRESA PARA LOCALIZAR O BANCO
            Edit1->Text = DataResumo->tbPagamentosOperadorasCNPJ->AsString;

            consulta = consulta + " and domicilio_cliente.CNPJ = '" + Edit1->Text + "' ";
            }

        Data1->tbDomicilioCliente->Close();
        Data1->tbDomicilioCliente->SQL->Clear();
        Data1->tbDomicilioCliente->SQL->Add(consulta);
        Data1->tbDomicilioCliente->Open();

            if(Data1->tbDomicilioCliente->RecordCount == 1)
            {
            DataResumo->tbPagamentosOperadorasBANCO->Value = Data1->tbDomicilioClienteCOD_BANCO->AsInteger;
            DataResumo->tbPagamentosOperadorasCOD_BANCO->Value = Data1->tbDomicilioClienteCOD_BANCO->AsInteger;
            DataResumo->tbPagamentosOperadorasAGENCIA->Value = Data1->tbDomicilioClienteAGENCIA->AsString;
            DataResumo->tbPagamentosOperadorasCONTA->Value = Data1->tbDomicilioClienteCONTA->AsString;
            }

            if(DataResumo->tbPagamentosOperadorasVALOR_TAXA->AsFloat < 0)
            {
            DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value = 0;
            }

            if(DataResumo->tbPagamentosOperadorasCOD_PRODUTO->AsFloat == 53)
            {
            DataResumo->tbPagamentosOperadorasNSU->Value = Data3->tbSeguroAntecipacaoCODIGO_TRANSACAO->AsString;
            DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->Value = Data3->tbSeguroAntecipacaoCODIGO_TRANSACAO->AsString;
            DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = 200;
            }

        DataResumo->tbPagamentosOperadoras->ApplyUpdates(0);

        atualiza = "update pagamentos_operadoras set pagamentos_operadoras.VALOR_LIQUIDO = ROUND(pagamentos_operadoras.VALOR_LIQUIDO, 2), pagamentos_operadoras.VALOR_BRUTO = ROUND(pagamentos_operadoras.VALOR_BRUTO, 2) ";
        atualiza += " where pagamentos_operadoras.CODIGO = " + DataResumo->tbPagamentosOperadorasCODIGO->AsString;

        Data1->tbExcluir->Close();
        Data1->tbExcluir->SQL->Clear();
        Data1->tbExcluir->SQL->Add(atualiza);
        Data1->tbExcluir->ExecSQL();

        //TENTA LOCALIZAR A VENDA
        consulta = "SELECT * FROM vendas where vendas.COD_STATUS_FINANCEIRO = '1' and vendas.CNPJ = '" + cnpj_cliente + "'";
        consulta += " and vendas.ADQID = 108";

        consulta += " and vendas.PARCELA = '" + DataResumo->tbPagamentosOperadorasPARCELA->AsString + "'";
        consulta += " and vendas.NSU = '" + DataResumo->tbPagamentosOperadorasNSU->AsString + "'";
        consulta += " and vendas.AUTORIZACAO = '" + DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->AsString + "'";

        Edit1->Text = Data3->tbSeguroAntecipacaoDATA_INICIAL_TRANSACAO->AsString.SubString(7,4) + "-" + Data3->tbSeguroAntecipacaoDATA_INICIAL_TRANSACAO->AsString.SubString(4,2) + "-" + Data3->tbSeguroAntecipacaoDATA_INICIAL_TRANSACAO->AsString.SubString(0,2);

        consulta += " and vendas.DATA_VENDA = '" + Edit1->Text + "'";

            if(DataResumo->tbVendasOperadoras->Active)
            {
            DataResumo->tbVendasOperadoras->EmptyDataSet();
            }

        DataResumo->tbVendasOperadoras->Close();
        DataResumo->tbVendasOperadoras->SQL->Clear();
        DataResumo->tbVendasOperadoras->SQL->Add(consulta);
        DataResumo->tbVendasOperadoras->Open();

            if(DataResumo->tbVendasOperadoras->RecordCount == 1)
            {
            DataResumo->tbPagamentosOperadoras->Edit();

            //CONCILIADA
            DataResumo->tbPagamentosOperadorasCOD_STATUS->Value = 1;

            //STATUS = LIQUIDADO
            DataResumo->tbPagamentosOperadorasCOD_STATUS_FINANCEIRO->Value = 2;

            DataResumo->tbPagamentosOperadorasVINCULADO_VENDA->Value = 'S';
            DataResumo->tbPagamentosOperadorasENCONTRADA_VENDA->Value = 'S';
            DataResumo->tbPagamentosOperadorasCOD_VENDA->Value = DataResumo->tbVendasOperadorasCODIGO->AsFloat;
            DataResumo->tbPagamentosOperadoras->ApplyUpdates(0);

            DataResumo->tbVendasOperadoras->Edit();
            DataResumo->tbVendasOperadorasCOD_STATUS_FINANCEIRO->Value = 2;
            DataResumo->tbVendasOperadorasVINCULADO_PAGAMENTO->Value = 'S';
            DataResumo->tbVendasOperadorasCOD_PAGAMENTO->Value = DataResumo->tbPagamentosOperadorasCODIGO->AsFloat;
            DataResumo->tbVendasOperadorasDATA_PAGAMENTO->Value = DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->AsDateTime;

            DataResumo->tbVendasOperadoras->ApplyUpdates(0);
            }
        }

	Data3->tbSeguroAntecipacao->Edit();
	Data3->tbSeguroAntecipacaoTRATADO->Value = 'S';
	Data3->tbSeguroAntecipacao->ApplyUpdates(0);

	Label6->Caption = contador + 1;
    ProgressBar1->Position = contador + 1;

	Data3->tbSeguroAntecipacao->Next();
	Application->ProcessMessages();
	}

Button6Click(Sender);

Edit2->Text = Date();
Edit3->Text = Time();
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::ExcluirDuplicidadedeVendas2Click(TObject *Sender)
{
Label21->Caption = "Excluir duplicidades PagSeguro - Venda";

AnsiString consulta;

consulta = "select vendas.NSU, vendas.PARCELA, vendas.AUTORIZACAO, vendas.DATA_VENDA, vendas.CNPJ, count(vendas.CODIGO) as total";
consulta += " from vendas where vendas.ADQID = 108 and vendas.DATA_VENDA >= '2022-01-01' and vendas.CNPJ <> '' and vendas.CNPJ is not null";
consulta += " group by vendas.NSU, vendas.PARCELA, vendas.AUTORIZACAO, vendas.DATA_VENDA, vendas.CNPJ";
consulta += " HAVING COUNT(vendas.CODIGO) > 1";

DataProcessamento->tbVendasDuplicidade->Close();
DataProcessamento->tbVendasDuplicidade->SQL->Clear();
DataProcessamento->tbVendasDuplicidade->SQL->Add(consulta);
DataProcessamento->tbVendasDuplicidade->Open();

DataProcessamento->tbVendasDuplicidade->Last();
int final = DataProcessamento->tbVendasDuplicidade->RecordCount;
DataProcessamento->tbVendasDuplicidade->First();

Label6->Caption = 0;
Label7->Caption = final;
ProgressBar1->Position = 0;
ProgressBar1->Max = final;

Application->ProcessMessages();

	for(int contador = 0; contador < final; contador++)
    {
    //TENTA LOCALIZAR A VENDA
    consulta = "SELECT * FROM vendas";
    consulta += " where vendas.CNPJ = '" + DataProcessamento->tbVendasDuplicidadeCNPJ->AsString + "'";
    consulta += " and vendas.ADQID = 108";

    consulta += " and vendas.PARCELA = '" + DataProcessamento->tbVendasDuplicidadePARCELA->AsString + "'";
    consulta += " and vendas.NSU = '" + DataProcessamento->tbVendasDuplicidadeNSU->AsString + "'";

    Edit1->Text = DataProcessamento->tbVendasDuplicidadeDATA_VENDA->AsString.SubString(7,4) + "-" + DataProcessamento->tbVendasDuplicidadeDATA_VENDA->AsString.SubString(4,2) + "-" + DataProcessamento->tbVendasDuplicidadeDATA_VENDA->AsString.SubString(0,2);

    consulta += " and vendas.DATA_VENDA = '" + Edit1->Text + "'";

    DataResumo->tbVendasOperadoras->Close();
    DataResumo->tbVendasOperadoras->SQL->Clear();
    DataResumo->tbVendasOperadoras->SQL->Add(consulta);
    DataResumo->tbVendasOperadoras->Open();

        if(DataResumo->tbVendasOperadoras->RecordCount >= 2)
        {
        DataResumo->tbVendasOperadoras->Last();

        DataResumo->tbVendasOperadoras->Delete();
        DataResumo->tbVendasOperadoras->ApplyUpdates(0);
        }

    DataProcessamento->tbVendasDuplicidade->Next();
    Label6->Caption = contador + 1;
    Application->ProcessMessages();
    }
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::ExcluirDuplicidadedePagamento6Click(TObject *Sender)
{
Label21->Caption = "Excluir duplicidades PagSeguro - Pagamentos";

AnsiString consulta;

consulta = "select pagamentos_operadoras.NSU, pagamentos_operadoras.CODIGO_AUTORIZACAO, pagamentos_operadoras.PARCELA, pagamentos_operadoras.DATA_PAGAMENTO, pagamentos_operadoras.DATA_VENDA, pagamentos_operadoras.CNPJ, count(pagamentos_operadoras.CODIGO) as total";
consulta += " from pagamentos_operadoras where pagamentos_operadoras.COD_ADQUIRENTE = 108";
consulta += " and pagamentos_operadoras.DATA_PAGAMENTO >= '2022-01-01'";
consulta += " and pagamentos_operadoras.CNPJ is not null and pagamentos_operadoras.CNPJ <> '' and pagamentos_operadoras.CODIGO_AUTORIZACAO is not null";
consulta += " group by pagamentos_operadoras.NSU, pagamentos_operadoras.CODIGO_AUTORIZACAO, pagamentos_operadoras.PARCELA, pagamentos_operadoras.DATA_PAGAMENTO, pagamentos_operadoras.DATA_VENDA, pagamentos_operadoras.CNPJ";
consulta += " HAVING COUNT(pagamentos_operadoras.CODIGO) > 1";
consulta += " limit 30000";

DataProcessamento->tbPagamentosDuplicidade2->Close();
DataProcessamento->tbPagamentosDuplicidade2->SQL->Clear();
DataProcessamento->tbPagamentosDuplicidade2->SQL->Add(consulta);
DataProcessamento->tbPagamentosDuplicidade2->Open();

DataProcessamento->tbPagamentosDuplicidade2->Last();
int final = DataProcessamento->tbPagamentosDuplicidade2->RecordCount;
DataProcessamento->tbPagamentosDuplicidade2->First();

Label6->Caption = 0;
Label7->Caption = final;
ProgressBar1->Position = 0;
ProgressBar1->Max = final;

Application->ProcessMessages();

	for(int contador = 0; contador < final; contador++)
    {
    //TENTA LOCALIZAR O PAGAMENTO
    consulta = "SELECT * FROM pagamentos_operadoras where";

    	if(DataProcessamento->tbPagamentosDuplicidade2CNPJ->AsString != "")
        {
        consulta += " pagamentos_operadoras.CNPJ = '" + DataProcessamento->tbPagamentosDuplicidade2CNPJ->AsString + "'";
        }
        else
        {
        consulta += " pagamentos_operadoras.CNPJ is null";
        }

    consulta += " and pagamentos_operadoras.COD_ADQUIRENTE = 108";

    consulta += " and pagamentos_operadoras.PARCELA = '" + DataProcessamento->tbPagamentosDuplicidade2PARCELA->AsString + "'";
    consulta += " and pagamentos_operadoras.NSU = '" + DataProcessamento->tbPagamentosDuplicidade2NSU->AsString + "'";
    consulta += " and pagamentos_operadoras.CODIGO_AUTORIZACAO = '" + DataProcessamento->tbPagamentosDuplicidade2CODIGO_AUTORIZACAO->AsString + "'";

    Edit1->Text = DataProcessamento->tbPagamentosDuplicidade2DATA_VENDA->AsString.SubString(7,4) + "-" + DataProcessamento->tbPagamentosDuplicidade2DATA_VENDA->AsString.SubString(4,2) + "-" + DataProcessamento->tbPagamentosDuplicidade2DATA_VENDA->AsString.SubString(0,2);

    consulta += " and pagamentos_operadoras.DATA_VENDA = '" + Edit1->Text + "'";

    DataResumo->tbPagamentosOperadoras->Close();
    DataResumo->tbPagamentosOperadoras->SQL->Clear();
    DataResumo->tbPagamentosOperadoras->SQL->Add(consulta);
    DataResumo->tbPagamentosOperadoras->Open();

        if(DataResumo->tbPagamentosOperadoras->RecordCount >= 2)
        {
        DataResumo->tbPagamentosOperadoras->Last();

        DataResumo->tbPagamentosOperadoras->Delete();
        DataResumo->tbPagamentosOperadoras->ApplyUpdates(0);
        }

    DataProcessamento->tbPagamentosDuplicidade2->Next();
    Label6->Caption = contador + 1;
    Application->ProcessMessages();
    }
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::DeletardadosDalgaloPneus1Click(TObject *Sender)
{
Label21->Caption = "Excluir vendas";

AnsiString consulta;

int final = 0;

//781 - Dalgallo Pneus
//562 - Tintas MC

    do
    {
    consulta = "select * from vendas where vendas.ADQID = 108 and vendas.COD_CLIENTE = 562 limit 10000";

    DataResumo->tbVendasOperadoras->Close();
    DataResumo->tbVendasOperadoras->SQL->Clear();
    DataResumo->tbVendasOperadoras->SQL->Add(consulta);
    DataResumo->tbVendasOperadoras->Open();

    DataResumo->tbVendasOperadoras->Last();
    final = DataResumo->tbVendasOperadoras->RecordCount;
    DataResumo->tbVendasOperadoras->First();

    Label6->Caption = 0;
    Label7->Caption = final;
    ProgressBar1->Position = 0;
    ProgressBar1->Max = final;

    Application->ProcessMessages();

        for(int contador = 0; contador < final; contador++)
        {
        DataResumo->tbVendasOperadoras->Delete();
        DataResumo->tbVendasOperadoras->ApplyUpdates(0);

        Label6->Caption = contador + 1;
        Application->ProcessMessages();
        }

    Button6Click(Sender);
    }while(final > 0);

Label21->Caption = "Excluir pagamentos";

    do
    {
    consulta = "select * from pagamentos_operadoras where pagamentos_operadoras.COD_ADQUIRENTE = 108 and pagamentos_operadoras.COD_CLIENTE = 562 limit 10000";

    DataResumo->tbPagamentosOperadoras->Close();
    DataResumo->tbPagamentosOperadoras->SQL->Clear();
    DataResumo->tbPagamentosOperadoras->SQL->Add(consulta);
    DataResumo->tbPagamentosOperadoras->Open();

    DataResumo->tbPagamentosOperadoras->Last();
    final = DataResumo->tbPagamentosOperadoras->RecordCount;
    DataResumo->tbPagamentosOperadoras->First();

    Label6->Caption = 0;
    Label7->Caption = final;
    ProgressBar1->Position = 0;
    ProgressBar1->Max = final;

    Application->ProcessMessages();

        for(int contador = 0; contador < final; contador++)
        {
        DataResumo->tbPagamentosOperadoras->Delete();
        DataResumo->tbPagamentosOperadoras->ApplyUpdates(0);

        Label6->Caption = contador + 1;
        Application->ProcessMessages();
        }

    Button6Click(Sender);
    }while(final > 0);

Label21->Caption = "Excluir dados brutos";

//SELECIONA OS ESTABELECIMENTOS
consulta = "Select * from cliente_operadora where cliente_operadora.COD_ADQUIRENTE = '108' and cliente_operadora.INTEGRA_API_PAGSEGURO = 'S'";
consulta  += " and cliente_operadora.COD_CLIENTE = 562";

DataResumo->tbClientesOperadoras->Close();
DataResumo->tbClientesOperadoras->SQL->Clear();
DataResumo->tbClientesOperadoras->SQL->Add(consulta);
DataResumo->tbClientesOperadoras->Open();

DataResumo->tbClientesOperadoras->Last();
final = DataResumo->tbClientesOperadoras->RecordCount;
DataResumo->tbClientesOperadoras->First();

Label6->Caption = 0;
Label7->Caption = final;
ProgressBar1->Position = 0;
ProgressBar1->Max = final;

Application->ProcessMessages();

int final2;

    for(int contador = 0; contador < final; contador++)
    {
    	do
        {
        //SELECIONA OS DADOS
        consulta = "select * from edi_pagseguro_venda where ESTABELECIMENTO = '" + DataResumo->tbClientesOperadorasCODIGO_ESTABELECIMENTO->AsString + "' or COD_CLIENTE = 562 limit 10000";

        Data3->tbSeguroVenda->Close();
        Data3->tbSeguroVenda->SQL->Clear();
        Data3->tbSeguroVenda->SQL->Add(consulta);
        Data3->tbSeguroVenda->Open();

        Label2->Caption = "Excluindo Vendas";

        Data3->tbSeguroVenda->Last();
        final2 = Data3->tbSeguroVenda->RecordCount;
        Data3->tbSeguroVenda->First();

        Label6->Caption = 0;
        Label7->Caption = final2;
        ProgressBar1->Position = 0;
        ProgressBar1->Max = final2;

            for(int contador2 = 0; contador2 < final2; contador2++)
            {
            Data3->tbSeguroVenda->Delete();
            Data3->tbSeguroVenda->ApplyUpdates(0);

            Label6->Caption = contador2 + 1;
            Application->ProcessMessages();
            }

        Button6Click(Sender);
        }while(final2 > 0);

        do
        {
        //SELECIONA OS DADOS
        consulta = "select * from edi_pagseguro_pagamento where ESTABELECIMENTO = '" + DataResumo->tbClientesOperadorasCODIGO_ESTABELECIMENTO->AsString + "' or COD_CLIENTE = 562 limit 10000";

        Data3->tbSeguroPagamento->Close();
        Data3->tbSeguroPagamento->SQL->Clear();
        Data3->tbSeguroPagamento->SQL->Add(consulta);
        Data3->tbSeguroPagamento->Open();

        Label2->Caption = "Excluindo Pagamentos";

        Data3->tbSeguroPagamento->Last();
        final2 = Data3->tbSeguroPagamento->RecordCount;
        Data3->tbSeguroPagamento->First();

        Label6->Caption = 0;
        Label7->Caption = final2;
        ProgressBar1->Position = 0;
        ProgressBar1->Max = final2;

            for(int contador2 = 0; contador2 < final2; contador2++)
            {
            Data3->tbSeguroPagamento->Delete();
            Data3->tbSeguroPagamento->ApplyUpdates(0);

            Label6->Caption = contador2 + 1;
            Application->ProcessMessages();
            }

        Button6Click(Sender);
        }while(final2 > 0);

        do
        {
        //SELECIONA OS DADOS
        consulta = "select * from edi_pagseguro_antecipacao where ESTABELECIMENTO = '" + DataResumo->tbClientesOperadorasCODIGO_ESTABELECIMENTO->AsString + "' or COD_CLIENTE = 562 limit 10000";

        Data3->tbSeguroAntecipacao->Close();
        Data3->tbSeguroAntecipacao->SQL->Clear();
        Data3->tbSeguroAntecipacao->SQL->Add(consulta);
        Data3->tbSeguroAntecipacao->Open();

        Label2->Caption = "Excluindo Vendas Brutas";

        Data3->tbSeguroAntecipacao->Last();
        final2 = Data3->tbSeguroAntecipacao->RecordCount;
        Data3->tbSeguroAntecipacao->First();

        Label6->Caption = 0;
        Label7->Caption = final2;
        ProgressBar1->Position = 0;
        ProgressBar1->Max = final2;

            for(int contador2 = 0; contador2 < final2; contador2++)
            {
            Data3->tbSeguroAntecipacao->Delete();
            Data3->tbSeguroAntecipacao->ApplyUpdates(0);

            Label6->Caption = contador2 + 1;
            Application->ProcessMessages();
            }

        Button6Click(Sender);
        }while(final2 > 0);

    DataResumo->tbClientesOperadoras->Next();
    }
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::Vincularvendasepagamentosoperadora1Click(TObject *Sender)

{
Label21->Caption = "Vincular vendas e pagamentos operadora - PagSeguro";

//SELECIONA PAGAMENTOS SEM VÍNCULO COM VENDA

	if(DataResumo->tbPagamentosOperadoras->Active)
	{
	DataResumo->tbPagamentosOperadoras->EmptyDataSet();
	}

DataResumo->tbPagamentosOperadoras->Close();
DataResumo->tbPagamentosOperadoras->SQL->Clear();
DataResumo->tbPagamentosOperadoras->SQL->Add("Select * from pagamentos_operadoras where pagamentos_operadoras.CODIGO is not null and pagamentos_operadoras.COD_STATUS_FINANCEIRO = 1 and pagamentos_operadoras.COD_VENDA is null and pagamentos_operadoras.COD_CLIENTE > 0 and pagamentos_operadoras.COD_ADQUIRENTE = 108 and pagamentos_operadoras.DATA_PAGAMENTO >= '2022-01-01'");
DataResumo->tbPagamentosOperadoras->Open();

DataResumo->tbPagamentosOperadoras->Last();
int final = DataResumo->tbPagamentosOperadoras->RecordCount;
DataResumo->tbPagamentosOperadoras->First();

int contador = 0;
AnsiString consulta;
AnsiString data;
Word Year, Month, Day;
TDateTime dtPresent;

ProgressBar1->Max = final;
ProgressBar1->Position = 0;

Label6->Caption = contador;
Label7->Caption = final;
Label10->Caption = "";

	for(contador = 0; contador < final; contador++)
	{
	Label6->Caption = contador+1;

    //TENTA LOCALIZAR A VENDA
    consulta = "SELECT * FROM vendas where vendas.COD_STATUS_FINANCEIRO = '1' ";
    consulta += " and vendas.CNPJ = '" + DataResumo->tbPagamentosOperadorasCNPJ->AsString + "'";
    consulta += " and vendas.ADQID = 108";

    consulta += " and vendas.PARCELA = '" + DataResumo->tbPagamentosOperadorasPARCELA->AsString + "'";
    consulta += " and vendas.NSU = '" + DataResumo->tbPagamentosOperadorasNSU->AsString + "'";
    consulta += " and vendas.AUTORIZACAO = '" + DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->AsString + "'";

    Edit1->Text = DataResumo->tbPagamentosOperadorasDATA_VENDA->AsString.SubString(7,4) + "-" + DataResumo->tbPagamentosOperadorasDATA_VENDA->AsString.SubString(4,2) + "-" + DataResumo->tbPagamentosOperadorasDATA_VENDA->AsString.SubString(0,2);

    consulta += " and vendas.DATA_VENDA = '" + Edit1->Text + "'";

        if(DataResumo->tbVendasOperadoras->Active)
        {
        DataResumo->tbVendasOperadoras->EmptyDataSet();
        }

    DataResumo->tbVendasOperadoras->Close();
    DataResumo->tbVendasOperadoras->SQL->Clear();
    DataResumo->tbVendasOperadoras->SQL->Add(consulta);
    DataResumo->tbVendasOperadoras->Open();

        if(DataResumo->tbVendasOperadoras->RecordCount == 1)
        {
        DataResumo->tbPagamentosOperadoras->Edit();

        //CONCILIADA
        DataResumo->tbPagamentosOperadorasCOD_STATUS->Value = 1;

        //STATUS = LIQUIDADO
        DataResumo->tbPagamentosOperadorasCOD_STATUS_FINANCEIRO->Value = 2;

        DataResumo->tbPagamentosOperadorasVINCULADO_VENDA->Value = 'S';
        DataResumo->tbPagamentosOperadorasENCONTRADA_VENDA->Value = 'S';
        DataResumo->tbPagamentosOperadorasCOD_VENDA->Value = DataResumo->tbVendasOperadorasCODIGO->AsFloat;
        DataResumo->tbPagamentosOperadoras->ApplyUpdates(0);

        DataResumo->tbVendasOperadoras->Edit();
        DataResumo->tbVendasOperadorasCOD_STATUS_FINANCEIRO->Value = 2;
        DataResumo->tbVendasOperadorasVINCULADO_PAGAMENTO->Value = 'S';
        DataResumo->tbVendasOperadorasCOD_PAGAMENTO->Value = DataResumo->tbPagamentosOperadorasCODIGO->AsFloat;
        DataResumo->tbVendasOperadorasDATA_PAGAMENTO->Value = DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->AsDateTime;

        DataResumo->tbVendasOperadoras->ApplyUpdates(0);
        }

    DataResumo->tbPagamentosOperadoras->Next();

    ProgressBar1->Position = contador+1;

	Application->ProcessMessages();
	}
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::Timer1Timer(TObject *Sender)
{
//PARA O TIMER PARA RODAR TODOS OS PROCESSOS
Timer1->Enabled = false;

Edit2->Text = Date();
Edit3->Text = Time();

//VARIÁVEIS GLOBAIS UTILIZADAS
//PROCESSO_ATUAL = NÚMERO DO PROCESSO ATUAL EM PROCESSO
//NUMERO_PROCESSOS = NÚMERO TOTAL DE PROCESSOS

    //VERIFICA SE O PROCESSO ESTÁ ATIVO
	if(RadioGroup1->ItemIndex == 0)
	{
    	if(Time() <= "05:00")
        {
        lido_stone = false;
        reprocessado_seguro = false;
        lido_bonuscred = false;
        }

        if(processo_atual == 1)
        {
        Label21->Caption = "Leitura de Arquivos Stone";

        DateTimePicker1->Date = Date() - 2;
        DateTimePicker2->Date = Date() - 1;

            if(Time() >= "05:10" && !lido_stone)
            {
            Stone5Click(Sender);
            lido_stone = true;
            }
        }
        else if(processo_atual == 2)
        {
            try
            {
            Label21->Caption = "Leitura de Arquivos PagSeguro";

                if(Time() <= "05:10" && !reprocessado_seguro)
                {
                DateTimePicker3->Date = Date() - 1;
                }
                else
                {
                DateTimePicker3->Date = Date();
                }

            DateTimePicker4->Date = Date();

            AutomaticoPagSeguroClick(Sender);

            } catch (...) {
            }
        }
        else if(processo_atual == 3)
        {
        Label21->Caption = "Leitura de Arquivos Bônuscred";

        DateTimePicker5->Date = Date() - 2;
        DateTimePicker6->Date = Date() - 1;

            if(Time() >= "05:10" && !lido_bonuscred)
            {
            AutomaticoBonuscredClick(Sender);
            lido_bonuscred = true;
            }
        }

	//SOMA 1 REGISTRO NO PROCESSO QUE SERÁ CONSIDERADO EM SEQUÊNCIA
	processo_atual = processo_atual + 1;

		//VERIFICA SE TODOS OS PROCESSOS FORAM VERIFICADOS E RETORNA PARA O PRIMEIRO NOVAMENTE
		if(processo_atual > numero_processos)
		{
		processo_atual = 1;

        num_loop++;
		Label79->Caption = num_loop;
		}
	}
	else
	{
	//INFORMA AO USUÁRIO QUE NÃO HÁ PROCESSO RODANDO OU ESTÁ PARALIZADO

		//VERIFICA SE NÃO HÁ ALGUM PROCESSO RODANDO, INICIADO MANUALMENTE
		if(Label6->Caption == "0")
		{
		//CONFIRMADO COMO NADA RODANDO, INFORMA AO USUÁRIO
		Label2->Caption = "Processo paralisado ou não iniciado";
		}
	}

//REINICIA O TIMER PARA CONTROLE DE LEITURA DE ARQUIVOS
Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::Label33Click(TObject *Sender)
{
DBLookupComboBox1->KeyValue = 0;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::Label35Click(TObject *Sender)
{
Memo2->Lines->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::Label55Click(TObject *Sender)
{
DBLookupComboBox2->KeyValue = 0;
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::Label57Click(TObject *Sender)
{
Memo4->Lines->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::Button1Click(TObject *Sender)
{
Label21->Caption = "Iniciando Leitura de API BônusCred";
Label27->Caption = "Iniciando Leitura de API BônusCred";

TDate ontem  = Date() - 1;

	if(DateOf(DateTimePicker6->Date) > ontem)
	{
	Application->MessageBoxA(L"A Data Final deve ser do dia anterior!", L"Mensagem do Sistema", MB_OK);
	}
	else if(DateTimePicker6->Date < DateTimePicker5->Date)
	{
	Application->MessageBoxA(L"A Data Final deve ser maior ou igual a data inicial!", L"Mensagem do Sistema", MB_OK);
	}
	else
	{
    int dias = DaysBetween(DateTimePicker5->Date, DateTimePicker6->Date) + 1;
    int erro = 0, pagina;
    bool continuar = false;
    TJSONObject *json, *detalhe, *item, *detalheOperadora, *itemVencimentos;
    Word Year, Month, Day;
    TDateTime dtPresent;

    TStringStream *stream;

    AnsiString auxiliar, consulta, retorno, dados, body, operadora;
    AnsiString data, url, ispb, banco, agencia, conta, message;
    AnsiString cnpj;
    int cod_banco;

    Label52->Caption = "0";
    Label53->Caption = "0";
    Label6->Caption = 0;
    Label7->Caption = 0;
    Label49->Caption = "";
    Label41->Caption = erro;

    Data2->tbBonuscredVenda->Close();
    Data2->tbBonuscredVenda->SQL->Clear();
    Data2->tbBonuscredVenda->SQL->Add("select * from edi_bonuscred_venda where edi_bonuscred_venda.CODIGO is null");
    Data2->tbBonuscredVenda->Open();

    Data2->tbBonuscredPagamento->Close();
    Data2->tbBonuscredPagamento->SQL->Clear();
    Data2->tbBonuscredPagamento->SQL->Add("select * from edi_bonuscred_pagamento where edi_bonuscred_pagamento.CODIGO is null");
    Data2->tbBonuscredPagamento->Open();

    Data2->tbBonuscredExtra->Close();
    Data2->tbBonuscredExtra->SQL->Clear();
    Data2->tbBonuscredExtra->SQL->Add("select * from edi_bonuscred_extras where edi_bonuscred_extras.CODIGO is null");
    Data2->tbBonuscredExtra->Open();

    	if(DBLookupComboBox3->KeyValue > 0)
        {
        Edit1->Text = DBLookupComboBox3->KeyValue;

        consulta = "Select * from cliente_operadora where cliente_operadora.COD_ADQUIRENTE in ('111', '112', '113', '114') and cliente_operadora.INTEGRA_API_BONUSCRED = 'S'";
        consulta  += " and cliente_operadora.COD_CLIENTE = " + Edit1->Text;
        }
        else
        {
        consulta = "Select * from cliente_operadora where cliente_operadora.COD_ADQUIRENTE in ('111', '112', '113', '114') and cliente_operadora.INTEGRA_API_BONUSCRED = 'S'";
        }

    //SELECIONA OS ESTABELECIMENTOS
    Data2->tbBonuscredCadastro->Close();
    Data2->tbBonuscredCadastro->SQL->Clear();
    Data2->tbBonuscredCadastro->SQL->Add(consulta);
    Data2->tbBonuscredCadastro->Open();

    Data2->tbBonuscredCadastro->Last();
    int total_cadastros = Data2->tbBonuscredCadastro->RecordCount;
    Data2->tbBonuscredCadastro->First();

    ProgressBar6->Position = 0;
    ProgressBar6->Max = dias;
    ProgressBar7->Position = 0;
    ProgressBar7->Max = total_cadastros;

    Label66->Caption = 0;
    Label67->Caption = total_cadastros;

    Application->ProcessMessages();

        for(int contador_dias = 0; contador_dias < dias; contador_dias++)
        {
        Button6Click(Sender);

        Label43->Caption = DateOf(DateTimePicker5->Date + contador_dias);

        Data2->tbBonuscredCadastro->First();
        ProgressBar5->Position = 0;

        Application->ProcessMessages();

            for(int contador_cadastros = 0; contador_cadastros < total_cadastros; contador_cadastros++)
            {
            cnpj = Data2->tbBonuscredCadastroCODIGO_ESTABELECIMENTO->AsString;

            continuar = true;
            Label65->Caption = cnpj;
            Label66->Caption = contador_cadastros + 1;

            dtPresent = DateTimePicker5->Date + contador_dias;
            DecodeDate(dtPresent, Year, Month, Day);

            Edit1->Text = Year;
            data = Edit1->Text + "-";
            Edit1->Text = Month;

                if(Edit1->Text.Length() == 1)
                {
                auxiliar = Month;
                Edit1->Text = "0" + auxiliar;
                }

            data += Edit1->Text + "-";
            Edit1->Text = Day;

                if(Edit1->Text.Length() == 1)
                {
                auxiliar = Day;
                Edit1->Text = "0" + auxiliar;
                }

            data += Edit1->Text;

            Application->ProcessMessages();

            IdHTTP1->Request->CustomHeaders->Clear();

            body = "{";
            body += "\"key\" : \"98659823-7898-6092-6619-539826956897\", ";
            body += "\"key_parceiro\" : \"6B9FD1E6-DDE9-48F7-AA8C-6BC413C1D8FC\", ";
            body += "\"cpf_ou_cnpj\" : \"" + cnpj + "\", ";
            body += "\"data\" : \"" + data + "\"";
            body += "}";

            stream = new TStringStream(body, TEncoding::UTF8, false);
            url = "https://api.bonuscred.com.br/conciliacao/dados";

            continuar = true;

                try
                {
                Memo3->Text = IdHTTP1->Post(url, stream);
                }
                catch (EIdHTTPProtocolException &E)
                {
                    try
                    {
                    Memo3->Text = IdHTTP1->Post(url, stream);
                    }
                    catch (EIdHTTPProtocolException &E)
                    {
                    erro++;
                    Label63->Caption = erro;
                    continuar = false;

                        //Bônuscred
                        if(Data2->tbBonuscredCadastroCOD_ADQUIRENTE->AsInteger == 111)
                        {
                        operadora = "Bônuscred";
                        }
                        //Cartão Pré-Datado
                        else if(Data2->tbBonuscredCadastroCOD_ADQUIRENTE->AsInteger == 113)
                        {
                        operadora = "Cartão Pré-Datado";
                        }
                        //Nutricard
                        else if(Data2->tbBonuscredCadastroCOD_ADQUIRENTE->AsInteger == 112)
                        {
                        operadora = "Nutricard";
                        }
                        //Alimentare
                        else if(Data2->tbBonuscredCadastroCOD_ADQUIRENTE->AsInteger == 114)
                        {
                        operadora = "Alimentare";
                        }

                    consulta = "- CNPJ= " + cnpj + "; DATA= " + data;
                    consulta += "; OPERADORA= " + operadora + "; MENSAGEM= " + E.ErrorMessage;

                    Memo1->Lines->Add(consulta);
                    }
                }

                //INÍCIO DO PROCESSO DE VENDAS
                if(continuar)
                {
                Application->ProcessMessages();

                    if(IdHTTP1->ResponseCode == 200)
                    {
                    json = (TJSONObject*) TJSONObject::ParseJSONValue(TEncoding::ASCII->GetBytes(Memo3->Lines->Text),0);

                         if(json != NULL)
                        {
                            //Bônuscred
                            if(Data2->tbBonuscredCadastroCOD_ADQUIRENTE->AsInteger == 111)
                            {
                            detalheOperadora = (TJSONObject*) json->GetValue("bnc");
                            operadora = "bnc";
                            }
                            //Cartão Pré-Datado
                            else if(Data2->tbBonuscredCadastroCOD_ADQUIRENTE->AsInteger == 113)
                            {
                            detalheOperadora = (TJSONObject*) json->GetValue("cpd");
                            operadora = "cpd";
                            }
                            //Nutricard
                            else if(Data2->tbBonuscredCadastroCOD_ADQUIRENTE->AsInteger == 112)
                            {
                            detalheOperadora = (TJSONObject*) json->GetValue("ntc");
                            operadora = "ntc";
                            }
                            //Alimentare
                            else if(Data2->tbBonuscredCadastroCOD_ADQUIRENTE->AsInteger == 114)
                            {
                            detalheOperadora = (TJSONObject*) json->GetValue("ali");
                            operadora = "ali";
                            }

                        //DADOS BANCÁRIOS
                        detalhe = (TJSONObject*) detalheOperadora->GetValue("dados_bancarios");

                        Label72->Caption = 1;
                        Label73->Caption = 1;
                        Label69->Caption = "Leitura de Dados Bancários";

                        Label6->Caption = 1;
                        Label7->Caption = 1;
                        Label2->Caption = "Leitura de Dados Bancários";

                        Application->ProcessMessages();

                            if(detalhe->Count > 0)
                            {
                            ispb = detalhe->GetValue("ispb")->Value();
                            cod_banco = StrToInt(detalhe->GetValue("numero_codigo")->Value());
                            banco = detalhe->GetValue("banco")->Value();
                            agencia = detalhe->GetValue("agencia")->Value();
                            conta = detalhe->GetValue("conta")->Value();
                            }
                            else
                            {
                            ispb = "";
                            cod_banco = 0;
                            banco = "";
                            agencia = "";
                            conta = "";
                            }

                        //VENDAS
                        detalhe = (TJSONObject*) detalheOperadora->GetValue("vendas");

                        Label72->Caption = 0;
                        Label73->Caption = detalhe->Count;
                        Label69->Caption = "Leitura de Vendas";

                        Label6->Caption = 0;
                        Label7->Caption = detalhe->Count;
                        Label2->Caption = "Leitura de Vendas";

                        Application->ProcessMessages();

                            for(int cont_detalhe = 0; cont_detalhe < detalhe->Count; cont_detalhe++)
                            {
                            item = (TJSONObject*) detalhe->Get(cont_detalhe);

                            Data2->tbBonuscredVenda->Insert();

                            Data2->tbBonuscredVendaDATA_PROCESSAMENTO->Value = Date();
                            Data2->tbBonuscredVendaHORA_PROCESSAMENTO->Value = Time();
                            Data2->tbBonuscredVendaTRATADO->Value = 'N';
                            Data2->tbBonuscredVendaCOD_CLIENTE->Value = Data2->tbBonuscredCadastroCOD_CLIENTE->AsInteger;

                            Data2->tbBonuscredVendaOPERADORA->Value = operadora;
                            Data2->tbBonuscredVendaISPB->Value = ispb;
                            Data2->tbBonuscredVendaNUMERO_CODIGO->Value = cod_banco;
                            Data2->tbBonuscredVendaBANCO->Value = banco;
                            Data2->tbBonuscredVendaAGENCIA->Value = agencia;
                            Data2->tbBonuscredVendaCONTA->Value = conta;
                            Data2->tbBonuscredVendaCPF_CNPJ->Value = cnpj;
                            Data2->tbBonuscredVendaDATA_MOVIMENTO->Value = StrToDate(formatarData(7, data));

                            Data2->tbBonuscredVendaAUTORIZACAO->Value = item->GetValue("autorizacao")->Value();;
                            Data2->tbBonuscredVendaNSU_HOST->Value = item->GetValue("nsu_host")->Value();
                            Data2->tbBonuscredVendaNSU_PDV->Value = item->GetValue("nsu_pdv")->Value();
                            Data2->tbBonuscredVendaPDV->Value = item->GetValue("pdv")->Value();
                            Data2->tbBonuscredVendaHORA_VENDA->Value = StrToTime(item->GetValue("hora_venda")->Value());
                            Data2->tbBonuscredVendaCARTAO->Value = item->GetValue("cartao")->Value();
                            Data2->tbBonuscredVendaTIPO_CARTAO->Value = item->GetValue("tipo_cartao")->Value();
                            Data2->tbBonuscredVendaVALOR_BRUTO->Value = StrToFloat(item->GetValue("valor_bruto")->Value());
                            Data2->tbBonuscredVendaVALOR_LIQUIDO->Value = StrToFloat(item->GetValue("valor_liquido")->Value());
                            Data2->tbBonuscredVendaTAXA_PERCENTUAL->Value = StrToFloat(item->GetValue("taxa_percentual")->Value());
                            Data2->tbBonuscredVendaPARCELAS->Value = StrToInt(item->GetValue("parcelas")->Value());

                            itemVencimentos = (TJSONObject*) item->GetValue("vencimentos");

                            Data2->tbBonuscredVendaDATA_VENCIMENTO->Value = StrToDate(itemVencimentos->Get(0)->ToString().SubString(3, 10));

                            consulta = "select * from edi_bonuscred_venda where edi_bonuscred_venda.CPF_CNPJ = '" + cnpj + "'";
                            consulta += " and edi_bonuscred_venda.DATA_MOVIMENTO = '" + data + "'";
                            consulta += " and edi_bonuscred_venda.AUTORIZACAO = '" + Data2->tbBonuscredVendaAUTORIZACAO->AsString + "'";
                            consulta += " and edi_bonuscred_venda.NSU_HOST = '" + Data2->tbBonuscredVendaNSU_HOST->AsString + "'";
                            consulta += " and edi_bonuscred_venda.PARCELAS = '" + Data2->tbBonuscredVendaPARCELAS->AsString + "'";

                                if(DataVerificacao2->tbBonuscredVenda->Active)
                                {
                                DataVerificacao2->tbBonuscredVenda->EmptyDataSet();
                                }

                            DataVerificacao2->tbBonuscredVenda->Close();
                            DataVerificacao2->tbBonuscredVenda->SQL->Clear();
                            DataVerificacao2->tbBonuscredVenda->SQL->Add(consulta);
                            DataVerificacao2->tbBonuscredVenda->Open();

                                if(DataVerificacao2->tbBonuscredVenda->RecordCount == 1)
                                {
                                Data2->tbBonuscredVenda->Cancel();
                                }
                                else
                                {
                                Data2->tbBonuscredVenda->ApplyUpdates(0);
                                }

                            Label72->Caption = cont_detalhe + 1;
                            Label6->Caption = cont_detalhe + 1;
                            Application->ProcessMessages();
                            }


                        //--------------------------------------------------------------

                        //PAGAMENTOS
                        detalhe = (TJSONObject*) detalheOperadora->GetValue("pagamentos");

                        Label72->Caption = 0;
                        Label73->Caption = detalhe->Count;
                        Label69->Caption = "Leitura de Pagamentos";

                        Label6->Caption = 0;
                        Label7->Caption = detalhe->Count;
                        Label2->Caption = "Leitura de Pagamentos";

                        Application->ProcessMessages();

                            for(int cont_detalhe = 0; cont_detalhe < detalhe->Count; cont_detalhe++)
                            {
                            item = (TJSONObject*) detalhe->Get(cont_detalhe);

                            Data2->tbBonuscredPagamento->Insert();

                            Data2->tbBonuscredPagamentoDATA_PROCESSAMENTO->Value = Date();
                            Data2->tbBonuscredPagamentoHORA_PROCESSAMENTO->Value = Time();
                            Data2->tbBonuscredPagamentoTRATADO->Value = 'N';
                            Data2->tbBonuscredPagamentoCOD_CLIENTE->Value = Data2->tbBonuscredCadastroCOD_CLIENTE->AsInteger;

                            Data2->tbBonuscredPagamentoOPERADORA->Value = operadora;
                            Data2->tbBonuscredPagamentoISPB->Value = ispb;
                            Data2->tbBonuscredPagamentoNUMERO_CODIGO->Value = cod_banco;
                            Data2->tbBonuscredPagamentoBANCO->Value = banco;
                            Data2->tbBonuscredPagamentoAGENCIA->Value = agencia;
                            Data2->tbBonuscredPagamentoCONTA->Value = conta;
                            Data2->tbBonuscredPagamentoCPF_CNPJ->Value = cnpj;
                            Data2->tbBonuscredPagamentoDATA_MOVIMENTO->Value = StrToDate(formatarData(7, data));

                            Data2->tbBonuscredPagamentoAUTORIZACAO->Value = item->GetValue("autorizacao")->Value();;
                            Data2->tbBonuscredPagamentoNSU_HOST->Value = item->GetValue("nsu_host")->Value();
                            Data2->tbBonuscredPagamentoNSU_PDV->Value = item->GetValue("nsu_pdv")->Value();
                            Data2->tbBonuscredPagamentoPDV->Value = item->GetValue("pdv")->Value();
                            Data2->tbBonuscredPagamentoDATA_VENDA->Value = StrToDate(formatarData(7, item->GetValue("data_venda")->Value()));
                            Data2->tbBonuscredPagamentoHORA_VENDA->Value = StrToTime(item->GetValue("hora_venda")->Value());
                            Data2->tbBonuscredPagamentoCARTAO->Value = item->GetValue("cartao")->Value();
                            Data2->tbBonuscredPagamentoTIPO_CARTAO->Value = item->GetValue("tipo_cartao")->Value();
                            Data2->tbBonuscredPagamentoVALOR_BRUTO->Value = StrToFloat(item->GetValue("valor_bruto_venda")->Value());
                            Data2->tbBonuscredPagamentoVALOR_LIQUIDO->Value = StrToFloat(item->GetValue("valor_parcela")->Value());
                            Data2->tbBonuscredPagamentoANTECIPACAO->Value = StrToBool(item->GetValue("antecipacao")->Value());
                            Data2->tbBonuscredPagamentoPARCELA->Value = StrToInt(item->GetValue("parcela")->Value());
                            Data2->tbBonuscredPagamentoQUANTIDADE_PARCELAS->Value = StrToInt(item->GetValue("quantidade_parcelas")->Value());

                            consulta = "select * from edi_bonuscred_pagamento where edi_bonuscred_pagamento.CPF_CNPJ = '" + cnpj + "'";
                            consulta += " and edi_bonuscred_pagamento.DATA_MOVIMENTO = '" + data + "'";
                            consulta += " and edi_bonuscred_pagamento.AUTORIZACAO = '" + Data2->tbBonuscredPagamentoAUTORIZACAO->AsString + "'";
                            consulta += " and edi_bonuscred_pagamento.NSU_HOST = '" + Data2->tbBonuscredPagamentoNSU_HOST->AsString + "'";
                            consulta += " and edi_bonuscred_pagamento.PARCELA = '" + Data2->tbBonuscredPagamentoPARCELA->AsString + "'";

                                if(DataVerificacao2->tbBonuscredPagamento->Active)
                                {
                                DataVerificacao2->tbBonuscredPagamento->EmptyDataSet();
                                }

                            DataVerificacao2->tbBonuscredPagamento->Close();
                            DataVerificacao2->tbBonuscredPagamento->SQL->Clear();
                            DataVerificacao2->tbBonuscredPagamento->SQL->Add(consulta);
                            DataVerificacao2->tbBonuscredPagamento->Open();

                                if(DataVerificacao2->tbBonuscredPagamento->RecordCount == 1)
                                {
                                Data2->tbBonuscredPagamento->Cancel();
                                }
                                else
                                {
                                Data2->tbBonuscredPagamento->ApplyUpdates(0);
                                }

                            Label72->Caption = cont_detalhe + 1;
                            Label6->Caption = cont_detalhe + 1;
                            Application->ProcessMessages();
                            }

                        //EXTRAS
                        detalhe = (TJSONObject*) detalheOperadora->GetValue("extras");

                        Label72->Caption = 0;
                        Label73->Caption = detalhe->Count;
                        Label69->Caption = "Leitura de Extras";

                        Label6->Caption = 0;
                        Label7->Caption = detalhe->Count;
                        Label2->Caption = "Leitura de Extras";

                        Application->ProcessMessages();

                            for(int cont_detalhe = 0; cont_detalhe < detalhe->Count; cont_detalhe++)
                            {
                            item = (TJSONObject*) detalhe->Get(cont_detalhe);

                            Data2->tbBonuscredExtra->Insert();

                            Data2->tbBonuscredExtraDATA_PROCESSAMENTO->Value = Date();
                            Data2->tbBonuscredExtraHORA_PROCESSAMENTO->Value = Time();
                            Data2->tbBonuscredExtraTRATADO->Value = 'N';
                            Data2->tbBonuscredExtraCOD_CLIENTE->Value = Data2->tbBonuscredCadastroCOD_CLIENTE->AsInteger;

                            Data2->tbBonuscredExtraOPERADORA->Value = operadora;
                            Data2->tbBonuscredExtraISPB->Value = ispb;
                            Data2->tbBonuscredExtraNUMERO_CODIGO->Value = cod_banco;
                            Data2->tbBonuscredExtraBANCO->Value = banco;
                            Data2->tbBonuscredExtraAGENCIA->Value = agencia;
                            Data2->tbBonuscredExtraCONTA->Value = conta;
                            Data2->tbBonuscredExtraCPF_CNPJ->Value = cnpj;
                            Data2->tbBonuscredExtraDATA_MOVIMENTO->Value = StrToDate(formatarData(7, data));

                            Data2->tbBonuscredExtraDOCUMENTO->Value = item->GetValue("documento")->Value();;
                            Data2->tbBonuscredExtraHISTORICO->Value = item->GetValue("historico")->Value();
                            Data2->tbBonuscredExtraVALOR_LIQUIDO->Value = StrToFloat(item->GetValue("valor_liquido")->Value());

                            consulta = "select * from edi_bonuscred_extras where edi_bonuscred_extras.CPF_CNPJ = '" + cnpj + "'";
                            consulta += " and edi_bonuscred_extras.DATA_MOVIMENTO = '" + data + "'";
                            consulta += " and edi_bonuscred_extras.DOCUMENTO = '" + Data2->tbBonuscredExtraDOCUMENTO->AsString + "'";
                            consulta += " and edi_bonuscred_extras.HISTORICO = '" + Data2->tbBonuscredExtraHISTORICO->AsString + "'";

                                if(DataVerificacao2->tbBonuscredExtra->Active)
                                {
                                DataVerificacao2->tbBonuscredExtra->EmptyDataSet();
                                }

                            DataVerificacao2->tbBonuscredExtra->Close();
                            DataVerificacao2->tbBonuscredExtra->SQL->Clear();
                            DataVerificacao2->tbBonuscredExtra->SQL->Add(consulta);
                            DataVerificacao2->tbBonuscredExtra->Open();

                                if(DataVerificacao2->tbBonuscredExtra->RecordCount == 1)
                                {
                                Data2->tbBonuscredExtra->Cancel();
                                }
                                else
                                {
                                Data2->tbBonuscredExtra->ApplyUpdates(0);
                                }

                            Label72->Caption = cont_detalhe + 1;
                            Label6->Caption = cont_detalhe + 1;
                            Application->ProcessMessages();
                            }

                        //CANCELAMENTOS
                        detalhe = (TJSONObject*) detalheOperadora->GetValue("cancelamentos");

                        Label72->Caption = 0;
                        Label73->Caption = detalhe->Count;
                        Label69->Caption = "Leitura de Cancelamentos";

                        Label6->Caption = 0;
                        Label7->Caption = detalhe->Count;
                        Label2->Caption = "Leitura de Cancelamentos";

                        Application->ProcessMessages();

                            if(detalhe->Count > 0)
                            {
                            ShowMessage("Cancelamentos");
                            }
                        }
                        else
                        {
                        erro++;
                        Label63->Caption = erro;
                        continuar = false;

                        consulta = "- Não foi possível consultar os dados do cnpj " + cnpj + " na data: " + data;
                        consulta += ", pois json não trouxe retorno.";

                        Memo1->Lines->Add(consulta);
                        }

                    json->Free();
                    }
                    else
                    {
                    erro++;
                    Label63->Caption = erro;

                    json = (TJSONObject*) TJSONObject::ParseJSONValue(TEncoding::ASCII->GetBytes(Memo3->Lines->Text),0);
                    message =  json->GetValue("message")->Value();

                    	//Bônuscred
                        if(Data2->tbBonuscredCadastroCOD_ADQUIRENTE->AsInteger == 111)
                        {
                        operadora = "Bônuscred";
                        }
                        //Cartão Pré-Datado
                        else if(Data2->tbBonuscredCadastroCOD_ADQUIRENTE->AsInteger == 113)
                        {
                        operadora = "Cartão Pré-Datado";
                        }
                        //Nutricard
                        else if(Data2->tbBonuscredCadastroCOD_ADQUIRENTE->AsInteger == 112)
                        {
                        operadora = "Nutricard";
                        }
                        //Alimentare
                        else if(Data2->tbBonuscredCadastroCOD_ADQUIRENTE->AsInteger == 114)
                        {
                        operadora = "Alimentare";
                        }

                    consulta = "- CNPJ= " + cnpj;
                    consulta += "; OPERADORA= " + operadora + "; MENSAGEM= " + message;

                    Memo1->Lines->Add(consulta);
                    }
                }

            Data2->tbBonuscredCadastro->Next();
            Label66->Caption = contador_cadastros + 1;
            ProgressBar7->Position = contador_cadastros + 1;

            Application->ProcessMessages();

            stream->Free();
            }

        ProgressBar6->Position = contador_dias + 1;

        Application->ProcessMessages();
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::VendasBonuscredClick(TObject *Sender)
{
AnsiString consulta, cnpj_cliente, bandeira, operadora, atualiza;
int auxiliar, cod_bandeira, cod_operadora;

//SELECIONA TODAS AS VENDAS
Data2->tbBonuscredVenda->Close();
Data2->tbBonuscredVenda->SQL->Clear();
Data2->tbBonuscredVenda->SQL->Add("Select * from edi_bonuscred_venda where edi_bonuscred_venda.TRATADO = 'N'");
Data2->tbBonuscredVenda->Open();

Data2->tbBonuscredVenda->Last();
int final = Data2->tbBonuscredVenda->RecordCount;
Data2->tbBonuscredVenda->First();

Label21->Caption = "Tratando Arquivos BônusCred";
Label2->Caption = "Tratando Vendas";
Label10->Caption = 0;
Label6->Caption = 0;
Label7->Caption = final;

ProgressBar1->Max = final;
ProgressBar1->Position = 0;

Application->ProcessMessages();

	//EFETUA ESSE BLOCO ATÉ TRATAR TODAS AS VENDAS
	for(int contador = 0; contador < final; contador++)
	{
    cnpj_cliente = "";

    	if(Data2->tbBonuscredVendaOPERADORA->AsString == "bnc")
        {
        cod_operadora = 111;
        cod_bandeira = 201;
        operadora = "Bonuscred";
        bandeira = "Bonuscred";
        }
        else if(Data2->tbBonuscredVendaOPERADORA->AsString == "cpd")
        {
        cod_operadora = 113;
        cod_bandeira = 203;
        operadora = "Cartão Pre Datado";
        bandeira = "Cartão Pre Datado";
        }
        else if(Data2->tbBonuscredVendaOPERADORA->AsString == "ntc")
        {
        cod_operadora = 112;
        cod_bandeira = 194;
        operadora = "Nutricard";
        bandeira = "Nutricard";
        }
        else if(Data2->tbBonuscredVendaOPERADORA->AsString == "ali")
        {
        cod_operadora = 114;
        cod_bandeira = 202;
        operadora = "Alimentare";
        bandeira = "Alimentare";
        }

    //LOCALIZA O CLIENTE
    Edit1->Text = Data2->tbBonuscredVendaCPF_CNPJ->AsAnsiString;

    consulta = "Select * from cliente_operadora where cliente_operadora.COD_ADQUIRENTE = '" + IntToStr(cod_operadora) + "'";
    consulta += " and cliente_operadora.CODIGO_ESTABELECIMENTO = '" + Edit1->Text + "' ";

        if(DataResumo->tbClientesOperadoras->Active)
        {
        DataResumo->tbClientesOperadoras->EmptyDataSet();
        }

    DataResumo->tbClientesOperadoras->Close();
    DataResumo->tbClientesOperadoras->SQL->Clear();
    DataResumo->tbClientesOperadoras->SQL->Add(consulta);
    DataResumo->tbClientesOperadoras->Open();

        if(DataResumo->tbClientesOperadoras->RecordCount == 1)
        {
        cnpj_cliente = DataResumo->tbClientesOperadorasCNPJ_ESTABELECIMENTO->AsString;
        }

    //CONTROLE DE DUPLICIDADE
    consulta = "SELECT * FROM vendas where vendas.CNPJ = '" + cnpj_cliente + "'";
    consulta += " and vendas.ADQID = '" + IntToStr(cod_operadora) + "'";
    consulta += " and vendas.PARCELA = '" + Data2->tbBonuscredVendaPARCELAS->AsString + "'";
    consulta += " and vendas.NSU = '" + Data2->tbBonuscredVendaNSU_HOST->AsString + "'";
    consulta += " and vendas.AUTORIZACAO = '" + Data2->tbBonuscredVendaAUTORIZACAO->AsString + "'";

    Edit1->Text = formatarData(3, Data2->tbBonuscredVendaDATA_MOVIMENTO->AsString);
    consulta += " and vendas.DATA_VENDA = '" + Edit1->Text + "'";

        if(DataResumo->tbVendasOperadoras->Active)
        {
        DataResumo->tbVendasOperadoras->EmptyDataSet();
        }

    DataResumo->tbVendasOperadoras->Close();
    DataResumo->tbVendasOperadoras->SQL->Clear();
    DataResumo->tbVendasOperadoras->SQL->Add(consulta);
    DataResumo->tbVendasOperadoras->Open();

        if(DataResumo->tbVendasOperadoras->RecordCount == 0)
        {
        DataResumo->tbVendasOperadoras->Insert();

        DataResumo->tbVendasOperadorasDATA_PROCESSAMENTO->Value = Date();
        DataResumo->tbVendasOperadorasHORA_PROCESSAMENTO->Value = Time();

        DataResumo->tbVendasOperadorasADQID->Value = cod_operadora;
        DataResumo->tbVendasOperadorasADQUIRENTE->Value = operadora;

        DataResumo->tbVendasOperadorasESTABELECIMENTO->Value = Data2->tbBonuscredVendaCPF_CNPJ->AsString;

            //CONFIRMA QUE FOI LOCALIZADO OS DADOS DO CLIENTE / OPERADORA
            if(DataResumo->tbClientesOperadoras->RecordCount == 1)
            {
            //BUSCA OS DADOS DO CLIENTE NA TABELA DE GRUPOS
            Edit1->Text = DataResumo->tbClientesOperadorasCOD_GRUPO->AsFloat;

            consulta = "Select * from grupos_clientes where grupos_clientes.CODIGO = '" + Edit1->Text + "' ";

            Data1->tbGrupos->Close();
            Data1->tbGrupos->SQL->Clear();
            Data1->tbGrupos->SQL->Add(consulta);
            Data1->tbGrupos->Open();

                if(Data1->tbGrupos->RecordCount == 1)
                {
                DataResumo->tbVendasOperadorasEMPRESA->Value = Data1->tbGruposNOME_EMPRESA->AsString;
                DataResumo->tbVendasOperadorasCNPJ->Value = Data1->tbGruposCNPJ->AsString;
                DataResumo->tbVendasOperadorasCOD_CLIENTE->Value = Data1->tbGruposCOD_CLIENTE->AsFloat;
                DataResumo->tbVendasOperadorasCOD_GRUPO_CLIENTE->Value = Data1->tbGruposCODIGO->AsFloat;

                //MARCA O CLIENTE COMO PENDENTE DE CÁLCULO
                Edit1->Text = DataResumo->tbVendasOperadorasCOD_CLIENTE->AsFloat;

                consulta = "Select * from clientes where clientes.CODIGO = '" + Edit1->Text + "' ";

                Data1->tbClientes->Close();
                Data1->tbClientes->SQL->Clear();
                Data1->tbClientes->SQL->Add(consulta);
                Data1->tbClientes->Open();

                    if(Data1->tbClientes->RecordCount == 1)
                    {
                    Data1->tbClientes->Edit();
                    Data1->tbClientesARQUIVOS_PROCESSADOS->Value = "N";
                    Data1->tbClientes->ApplyUpdates(0);
                    }
                }
            }


        DataResumo->tbVendasOperadorasCOD_BANDEIRA->Value = cod_bandeira;

        DataResumo->tbVendasOperadorasPARCELA->Value = Data2->tbBonuscredVendaPARCELAS->AsInteger;
        DataResumo->tbVendasOperadorasTOTAL_PARCELAS->Value = Data2->tbBonuscredVendaPARCELAS->AsInteger;

        	//PRODUTO
            if(Data2->tbBonuscredVendaTIPO_CARTAO->AsString == "Credito")
            {
            //Credito
        	DataResumo->tbVendasOperadorasCODIGO_MODALIDADE->Value = 1;
            DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 20;
            }
            else
            {
            //Vouncher
        	DataResumo->tbVendasOperadorasCODIGO_MODALIDADE->Value = 3;

                if(Data2->tbBonuscredVendaTIPO_CARTAO->AsString == "Alimentacao")
                {
                DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 2;
                }
                else if(Data2->tbBonuscredVendaTIPO_CARTAO->AsString == "Refeicao")
                {
                DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 3;
                }
                else
                {
                DataResumo->tbVendasOperadorasCOD_PRODUTO->Value = 22;
                }
            }

        //STATUS = NÃO CONCILIADA
        DataResumo->tbVendasOperadorasCOD_STATUS_CONCILIACAO->Value = 2;

        //STATUS FINANCEIRO = PREVISTO
        DataResumo->tbVendasOperadorasCOD_STATUS_FINANCEIRO->Value = 1;

        DataResumo->tbVendasOperadorasVALOR_BRUTO->Value = Data2->tbBonuscredVendaVALOR_BRUTO->AsFloat;
        DataResumo->tbVendasOperadorasVALOR_LIQUIDO->Value = Data2->tbBonuscredVendaVALOR_LIQUIDO->AsFloat;
        DataResumo->tbVendasOperadorasPERCENTUAL_TAXA->Value = Data2->tbBonuscredVendaTAXA_PERCENTUAL->AsFloat;
        DataResumo->tbVendasOperadorasVALOR_TAXA->Value = Data2->tbBonuscredVendaVALOR_BRUTO->AsFloat - Data2->tbBonuscredVendaVALOR_LIQUIDO->AsFloat;

        DataResumo->tbVendasOperadorasDATA_VENDA->Value = Data2->tbBonuscredVendaDATA_MOVIMENTO->AsDateTime;
        DataResumo->tbVendasOperadorasHORA_TRANSACAO->Value = Data2->tbBonuscredVendaHORA_VENDA->AsDateTime;
        DataResumo->tbVendasOperadorasNSU->Value = Data2->tbBonuscredVendaNSU_HOST->AsString;
        DataResumo->tbVendasOperadorasDATA_PREVISTA_PAGTO->Value = dataValida(Data2->tbBonuscredVendaDATA_VENCIMENTO->AsDateTime);
        DataResumo->tbVendasOperadorasAUTORIZACAO->Value = Data2->tbBonuscredVendaAUTORIZACAO->AsString;
        DataResumo->tbVendasOperadorasCARTAO->Value = Data2->tbBonuscredVendaCARTAO->AsString;

        //CONFIGURA O MEIO DE CAPTURA

            if(Data2->tbBonuscredVendaPDV->AsString == "POS")
            {
            //POS
            DataResumo->tbVendasOperadorasCOD_MEIO_CAPTURA->Value = 1;
            }
            else if(Data2->tbBonuscredVendaPDV->AsString == "TEF")
            {
            //TEF
            DataResumo->tbVendasOperadorasCOD_MEIO_CAPTURA->Value = 2;
            }
            else
            {
            DataResumo->tbVendasOperadorasCOD_MEIO_CAPTURA->Value = 13;
            }

        DataResumo->tbVendasOperadorasBANCO->Value = Data2->tbBonuscredVendaNUMERO_CODIGO->AsInteger;
        DataResumo->tbVendasOperadorasAGENCIA->Value = retirarZerosEsquerda(sem_digito(Data2->tbBonuscredVendaAGENCIA->AsString));
        DataResumo->tbVendasOperadorasCONTA->Value = retirarZerosEsquerda(retirar_caracteres(Data2->tbBonuscredVendaCONTA->AsString));

        DataResumo->tbVendasOperadoras->ApplyUpdates(0);

        atualiza = "update vendas set vendas.VALOR_LIQUIDO = ROUND(vendas.VALOR_LIQUIDO, 2), vendas.VALOR_BRUTO = ROUND(vendas.VALOR_BRUTO, 2) ";
        atualiza += " where vendas.CODIGO = " + DataResumo->tbVendasOperadorasCODIGO->AsString;

        Data1->tbExcluir->Close();
        Data1->tbExcluir->SQL->Clear();
        Data1->tbExcluir->SQL->Add(atualiza);
        Data1->tbExcluir->ExecSQL();
        }

	Data2->tbBonuscredVenda->Edit();
	Data2->tbBonuscredVendaTRATADO->Value = 'S';
	Data2->tbBonuscredVenda->ApplyUpdates(0);

    Data2->tbBonuscredVenda->Next();

	Label6->Caption = contador + 1;
    ProgressBar1->Position = contador + 1;

	Application->ProcessMessages();
	}
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::PagamentosBonuscredClick(TObject *Sender)
{
AnsiString consulta, cnpj_cliente, atualiza, data, bandeira, operadora;
int cod_bandeira, cod_operadora;
double taxa;
Word Year, Month, Day;
TDate dtPresent;

//SELECIONA TODAS AS VENDAS DO PAGSEGURO EM TABELA BRUTA AINDA NÃO TRATADOS
Data2->tbBonuscredPagamento->Close();
Data2->tbBonuscredPagamento->SQL->Clear();
Data2->tbBonuscredPagamento->SQL->Add("Select * from edi_bonuscred_pagamento where edi_bonuscred_pagamento.TRATADO = 'N' and edi_bonuscred_pagamento.ANTECIPACAO = 0");
Data2->tbBonuscredPagamento->Open();

Data2->tbBonuscredPagamento->Last();
int final = Data2->tbBonuscredPagamento->RecordCount;
Data2->tbBonuscredPagamento->First();

Label21->Caption = "Tratando Arquivos Bônuscred";
Label2->Caption = "Tratando Pagamentos";
Label10->Caption = 0;
Label6->Caption = 0;
Label7->Caption = final;

ProgressBar1->Max = final;
ProgressBar1->Position = 0;

Application->ProcessMessages();

	//EFETUA ESSE BLOCO ATÉ TRATAR TODAS AS VENDAS
	for(int contador = 0; contador < final; contador++)
	{
    cnpj_cliente = "";

        if(Data2->tbBonuscredPagamentoOPERADORA->AsString == "bnc")
        {
        cod_operadora = 111;
        cod_bandeira = 201;
        operadora = "Bonuscred";
        bandeira = "Bonuscred";
        }
        else if(Data2->tbBonuscredPagamentoOPERADORA->AsString == "cpd")
        {
        cod_operadora = 113;
        cod_bandeira = 203;
        operadora = "Cartão Pre Datado";
        bandeira = "Cartão Pre Datado";
        }
        else if(Data2->tbBonuscredPagamentoOPERADORA->AsString == "ntc")
        {
        cod_operadora = 112;
        cod_bandeira = 194;
        operadora = "Nutricard";
        bandeira = "Nutricard";
        }
        else if(Data2->tbBonuscredPagamentoOPERADORA->AsString == "ali")
        {
        cod_operadora = 114;
        cod_bandeira = 202;
        operadora = "Alimentare";
        bandeira = "Alimentare";
        }

    //LOCALIZA O CLIENTE
    Edit1->Text = Data2->tbBonuscredPagamentoCPF_CNPJ->AsAnsiString;

    consulta = "Select * from cliente_operadora where cliente_operadora.COD_ADQUIRENTE = '" + IntToStr(cod_operadora) + "'";
    consulta += " and cliente_operadora.CODIGO_ESTABELECIMENTO = '" + Edit1->Text + "' ";

        if(DataResumo->tbClientesOperadoras->Active)
        {
        DataResumo->tbClientesOperadoras->EmptyDataSet();
        }

    DataResumo->tbClientesOperadoras->Close();
    DataResumo->tbClientesOperadoras->SQL->Clear();
    DataResumo->tbClientesOperadoras->SQL->Add(consulta);
    DataResumo->tbClientesOperadoras->Open();

        if(DataResumo->tbClientesOperadoras->RecordCount == 1)
        {
        cnpj_cliente = DataResumo->tbClientesOperadorasCNPJ_ESTABELECIMENTO->AsString;
        }

    //CONTROLE DE DUPLICIDADE
    consulta = "Select * from pagamentos_operadoras where pagamentos_operadoras.CNPJ = '" + cnpj_cliente + "'";
    consulta += " and pagamentos_operadoras.COD_ADQUIRENTE = '" + IntToStr(cod_operadora) + "'";
    consulta += " and pagamentos_operadoras.NSU = '" + Data2->tbBonuscredPagamentoNSU_HOST->AsString + "'";
    consulta += " and pagamentos_operadoras.CODIGO_AUTORIZACAO = '" + Data2->tbBonuscredPagamentoAUTORIZACAO->AsString + "'";
    consulta += " and pagamentos_operadoras.PARCELA = '" + Data2->tbBonuscredPagamentoPARCELA->AsString + "' ";

    Edit1->Text = formatarData(3, Data2->tbBonuscredPagamentoDATA_VENDA->AsString);
    consulta += " and pagamentos_operadoras.DATA_VENDA = '" + Edit1->Text + "'";

    dtPresent = dataValida(Data2->tbBonuscredPagamentoDATA_MOVIMENTO->AsDateTime);
    DecodeDate(dtPresent, Year, Month, Day);

    Edit1->Text = Year;
    data = Edit1->Text + "-";
    Edit1->Text = Month;
    data = data + Edit1->Text + "-";
    Edit1->Text = Day;
    data = data + Edit1->Text;

    consulta += " and pagamentos_operadoras.DATA_PAGAMENTO = '" + data + "'";

        if(DataResumo->tbPagamentosOperadoras->Active)
        {
        DataResumo->tbPagamentosOperadoras->EmptyDataSet();
        }

    DataResumo->tbPagamentosOperadoras->Close();
    DataResumo->tbPagamentosOperadoras->SQL->Clear();
    DataResumo->tbPagamentosOperadoras->SQL->Add(consulta);
    DataResumo->tbPagamentosOperadoras->Open();

        if(DataResumo->tbPagamentosOperadoras->RecordCount == 0)
        {
        DataResumo->tbPagamentosOperadoras->Insert();

        //PAGSEGURO
        DataResumo->tbPagamentosOperadorasCOD_ADQUIRENTE->Value = cod_operadora;

        DataResumo->tbPagamentosOperadorasID_LOJA->Value = Data2->tbBonuscredPagamentoCPF_CNPJ->AsAnsiString;
        DataResumo->tbPagamentosOperadorasAGENCIA->Value = retirarZerosEsquerda(sem_digito(Data2->tbBonuscredPagamentoAGENCIA->AsString));
        DataResumo->tbPagamentosOperadorasBANCO->Value = Data2->tbBonuscredPagamentoNUMERO_CODIGO->AsInteger;
        DataResumo->tbPagamentosOperadorasCOD_BANCO->Value = DataResumo->tbPagamentosOperadorasBANCO->AsInteger;
        DataResumo->tbPagamentosOperadorasCONTA->Value = retirarZerosEsquerda(retirar_caracteres(Data2->tbBonuscredPagamentoCONTA->AsString));

            //CONFIRMA QUE FOI LOCALIZADO OS DADOS DO CLIENTE / OPERADORA
            if(DataResumo->tbClientesOperadoras->RecordCount == 1)
            {
            //BUSCA OS DADOS DO CLIENTE NA TABELA DE GRUPOS
            Edit1->Text = DataResumo->tbClientesOperadorasCOD_GRUPO->AsFloat;

            consulta = "Select * from grupos_clientes where grupos_clientes.CODIGO = '" + Edit1->Text + "' ";

            Data1->tbGrupos->Close();
            Data1->tbGrupos->SQL->Clear();
            Data1->tbGrupos->SQL->Add(consulta);
            Data1->tbGrupos->Open();

                if(Data1->tbGrupos->RecordCount == 1)
                {
                DataResumo->tbPagamentosOperadorasEMPRESA->Value = Data1->tbGruposNOME_EMPRESA->AsString;
                DataResumo->tbPagamentosOperadorasCNPJ->Value = Data1->tbGruposCNPJ->AsString;
                DataResumo->tbPagamentosOperadorasCOD_CLIENTE->Value = Data1->tbGruposCOD_CLIENTE->AsFloat;
                DataResumo->tbPagamentosOperadorasCOD_GRUPO_CLIENTE->Value = Data1->tbGruposCODIGO->AsFloat;

                //MARCA O CLIENTE COMO PENDENTE DE CÁLCULO
                Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_CLIENTE->AsFloat;

                consulta = "Select * from clientes where clientes.CODIGO = '" + Edit1->Text + "' ";

                Data1->tbClientes->Close();
                Data1->tbClientes->SQL->Clear();
                Data1->tbClientes->SQL->Add(consulta);
                Data1->tbClientes->Open();

                    if(Data1->tbClientes->RecordCount == 1)
                    {
                    Data1->tbClientes->Edit();
                    Data1->tbClientesARQUIVOS_PROCESSADOS->Value = "N";
                    Data1->tbClientes->ApplyUpdates(0);
                    }
                }
            }

            //PRODUTO
            if(Data2->tbBonuscredPagamentoTIPO_CARTAO->AsString == "Credito")
            {
            //Credito
        	DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 1;
            DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 20;
            }
            else
            {
            //Vouncher
        	DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 3;

                if(Data2->tbBonuscredPagamentoTIPO_CARTAO->AsString == "Alimentacao")
                {
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 2;
                }
                else if(Data2->tbBonuscredPagamentoTIPO_CARTAO->AsString == "Refeicao")
                {
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 3;
                }
                else
                {
                DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 22;
                }
            }

        DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = cod_bandeira;
        DataResumo->tbPagamentosOperadorasPARCELA->Value = Data2->tbBonuscredPagamentoPARCELA->AsFloat;
        DataResumo->tbPagamentosOperadorasTOTAL_PARCELAS->Value = Data2->tbBonuscredPagamentoQUANTIDADE_PARCELAS->AsFloat;

        //STATUS = NÃO CONCILIADA
        DataResumo->tbPagamentosOperadorasCOD_STATUS->Value = 2;

        //STATUS FINANCEIRO = PREVISTO
        DataResumo->tbPagamentosOperadorasCOD_STATUS_FINANCEIRO->Value = 1;

        //TIPO DE LANÇAMENTO = PAGAMENTO
        DataResumo->tbPagamentosOperadorasCOD_TIPO_LANCAMENTO->Value = 1;

        //TIPO DE LANÇAMENTO = NORMAL
        DataResumo->tbPagamentosOperadorasCOD_TIPO_PAGAMENTO->Value = 1;

        DataResumo->tbPagamentosOperadorasVALOR_BRUTO->Value = Data2->tbBonuscredPagamentoVALOR_BRUTO->AsFloat;
        DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->Value = Data2->tbBonuscredPagamentoVALOR_LIQUIDO->AsFloat;
        DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value = Data2->tbBonuscredPagamentoVALOR_BRUTO->AsFloat - Data2->tbBonuscredPagamentoVALOR_LIQUIDO->AsFloat;

        taxa = 0;
        taxa = DataResumo->tbPagamentosOperadorasVALOR_TAXA->AsFloat / DataResumo->tbPagamentosOperadorasVALOR_BRUTO->AsFloat;
        taxa = taxa * 100;

        DataResumo->tbPagamentosOperadorasTAXA_PERCENTUAL->Value = taxa;
        DataResumo->tbPagamentosOperadorasPERCENTUAL_TAXA_CALC->Value = 'S';

        DataResumo->tbPagamentosOperadorasDATA_VENDA->Value = Data2->tbBonuscredPagamentoDATA_VENDA->AsDateTime;
        DataResumo->tbPagamentosOperadorasHORA_VENDA->Value = Data2->tbBonuscredPagamentoHORA_VENDA->AsDateTime;
        DataResumo->tbPagamentosOperadorasDATA_PREV_PAG_ORIGINAL->Value = dataValida(Data2->tbBonuscredPagamentoDATA_MOVIMENTO->AsDateTime);
        DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->Value = dataValida(Data2->tbBonuscredPagamentoDATA_MOVIMENTO->AsDateTime);
        DataResumo->tbPagamentosOperadorasDATA_PROCESSAMENTO->Value = Date();
        DataResumo->tbPagamentosOperadorasHORA_PROCESSAMENTO->Value = Time();

        DataResumo->tbPagamentosOperadorasNSU->Value = Data2->tbBonuscredPagamentoNSU_HOST->AsString;
        DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->Value = Data2->tbBonuscredPagamentoAUTORIZACAO->AsString;
        //CONFIGURA O MEIO DE CAPTURA

            if(Data2->tbBonuscredPagamentoPDV->AsString == "POS")
            {
            //POS
            DataResumo->tbPagamentosOperadorasCOD_MEIO_CAPTURA->Value = 1;
            }
            else if(Data2->tbBonuscredPagamentoPDV->AsString == "TEF")
            {
            //TEF
            DataResumo->tbPagamentosOperadorasCOD_MEIO_CAPTURA->Value = 2;
            }
            else
            {
            DataResumo->tbPagamentosOperadorasCOD_MEIO_CAPTURA->Value = 13;
            }

        DataResumo->tbPagamentosOperadorasNUMERO_CARTAO->Value = Data2->tbBonuscredPagamentoCARTAO->AsString;

        DataResumo->tbPagamentosOperadoras->ApplyUpdates(0);

        atualiza = "update pagamentos_operadoras set pagamentos_operadoras.VALOR_LIQUIDO = ROUND(pagamentos_operadoras.VALOR_LIQUIDO, 2), pagamentos_operadoras.VALOR_BRUTO = ROUND(pagamentos_operadoras.VALOR_BRUTO, 2) ";
        atualiza += " where pagamentos_operadoras.CODIGO = " + DataResumo->tbPagamentosOperadorasCODIGO->AsString;

        Data1->tbExcluir->Close();
        Data1->tbExcluir->SQL->Clear();
        Data1->tbExcluir->SQL->Add(atualiza);
        Data1->tbExcluir->ExecSQL();

        //TENTA LOCALIZAR A VENDA
        consulta = "SELECT * FROM vendas where vendas.COD_STATUS_FINANCEIRO = '1' and vendas.CNPJ = '" + cnpj_cliente + "'";
        consulta += " and vendas.ADQID = '" + IntToStr(cod_operadora) + "'";
        consulta += " and vendas.PARCELA = '" + DataResumo->tbPagamentosOperadorasPARCELA->AsString + "'";
        consulta += " and vendas.NSU = '" + DataResumo->tbPagamentosOperadorasNSU->AsString + "'";
        consulta += " and vendas.AUTORIZACAO = '" + DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->AsString + "'";

        Edit1->Text = formatarData(3, Data2->tbBonuscredPagamentoDATA_VENDA->AsString);
        consulta += " and vendas.DATA_VENDA = '" + Edit1->Text + "'";

            if(DataResumo->tbVendasOperadoras->Active)
            {
            DataResumo->tbVendasOperadoras->EmptyDataSet();
            }

        DataResumo->tbVendasOperadoras->Close();
        DataResumo->tbVendasOperadoras->SQL->Clear();
        DataResumo->tbVendasOperadoras->SQL->Add(consulta);
        DataResumo->tbVendasOperadoras->Open();

            if(DataResumo->tbVendasOperadoras->RecordCount == 1)
            {
            DataResumo->tbPagamentosOperadoras->Edit();

            //CONCILIADA
            DataResumo->tbPagamentosOperadorasCOD_STATUS->Value = 1;

            //STATUS = LIQUIDADO
            DataResumo->tbPagamentosOperadorasCOD_STATUS_FINANCEIRO->Value = 2;

            DataResumo->tbPagamentosOperadorasVINCULADO_VENDA->Value = 'S';
            DataResumo->tbPagamentosOperadorasENCONTRADA_VENDA->Value = 'S';
            DataResumo->tbPagamentosOperadorasCOD_VENDA->Value = DataResumo->tbVendasOperadorasCODIGO->AsFloat;
            DataResumo->tbPagamentosOperadoras->ApplyUpdates(0);

            DataResumo->tbVendasOperadoras->Edit();
            DataResumo->tbVendasOperadorasCOD_STATUS_FINANCEIRO->Value = 2;
            DataResumo->tbVendasOperadorasVINCULADO_PAGAMENTO->Value = 'S';
            DataResumo->tbVendasOperadorasCOD_PAGAMENTO->Value = DataResumo->tbPagamentosOperadorasCODIGO->AsFloat;
            DataResumo->tbVendasOperadorasDATA_PAGAMENTO->Value = DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->AsDateTime;

            DataResumo->tbVendasOperadoras->ApplyUpdates(0);
            }
        }

	Data2->tbBonuscredPagamento->Edit();
	Data2->tbBonuscredPagamentoTRATADO->Value = 'S';
	Data2->tbBonuscredPagamento->ApplyUpdates(0);

	Label6->Caption = contador + 1;
    ProgressBar1->Position = contador + 1;

	Data2->tbBonuscredPagamento->Next();
	Application->ProcessMessages();
	}

Button6Click(Sender);

Edit2->Text = Date();
Edit3->Text = Time();
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::ExcluirVendas1Click(TObject *Sender)
{
    //VERIFICA SE O USUÁRIO DESEJA REALMENTE EXCLUIR TODOS OS DADOS DA OPERADORA
	if(Application->MessageBoxA(L"Deseja realmente excluir os dados de vendas da operadora Bônuscred ?",L"Mensagem do Sistema",MB_YESNO) == ID_YES)
	{
	Data1->tbExcluir->Close();
	Data1->tbExcluir->SQL->Clear();
	Data1->tbExcluir->SQL->Add("delete from vendas where vendas.ADQID in (111, 112, 113, 114)");
	Data1->tbExcluir->ExecSQL();
	}
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::ExcluirPagamentos1Click(TObject *Sender)
{
	//VERIFICA SE O USUÁRIO DESEJA REALMENTE EXCLUIR TODOS OS DADOS DA OPERADORA
	if(Application->MessageBoxA(L"Deseja realmente excluir os dados de pagamento da operadora Bônuscred ?",L"Mensagem do Sistema",MB_YESNO) == ID_YES)
	{
	Data1->tbExcluir->Close();
	Data1->tbExcluir->SQL->Clear();
	Data1->tbExcluir->SQL->Add("delete from pagamentos_operadoras where pagamentos_operadoras.COD_ADQUIRENTE in (111, 112, 113, 114)");
	Data1->tbExcluir->ExecSQL();
	}
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::Marcardadosbrutospa1Click(TObject *Sender)
{
	//VERIFICA SE O USUÁRIO DESEJA REALMENTE EXCLUIR TODOS OS DADOS DA OPERADORA
	if(Application->MessageBoxA(L"Deseja realmente marcar os dados da operadora Bônuscred para TRATADO = 'N'?",L"Mensagem do Sistema",MB_YESNO) == ID_YES)
	{
	Data1->tbExcluir->Close();
	Data1->tbExcluir->SQL->Clear();
	Data1->tbExcluir->SQL->Add("update edi_bonuscred_venda set edi_bonuscred_venda.TRATADO = 'N'");
	Data1->tbExcluir->ExecSQL();

    Data1->tbExcluir->Close();
	Data1->tbExcluir->SQL->Clear();
	Data1->tbExcluir->SQL->Add("update edi_bonuscred_pagamento set edi_bonuscred_pagamento.TRATADO = 'N'");
	Data1->tbExcluir->ExecSQL();

    Data1->tbExcluir->Close();
	Data1->tbExcluir->SQL->Clear();
	Data1->tbExcluir->SQL->Add("update edi_bonuscred_extras set edi_bonuscred_extras.TRATADO = 'N'");
	Data1->tbExcluir->ExecSQL();
	}
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::AjustesBonuscredClick(TObject *Sender)
{
int contador = 0, final = 0, posicao, cod_operadora, cod_bandeira;
bool cancelamento = false;
AnsiString cnpj_cliente, dados, consulta, chave, data_venda, data, bandeira, operadora;
Word Year, Month, Day;
TDate dtPresent;

Label21->Caption = "Tratando Arquivos BônusCred";
Label2->Caption = "Tratando Ajustes";
Label10->Caption = 0;
Label7->Caption = 0;
Label6->Caption = 0;

Application->ProcessMessages();

	do
	{
	Button6Click(Sender);

		if(Data2->tbBonuscredExtra->Active)
		{
		Data2->tbBonuscredExtra->EmptyDataSet();
		}

	Data2->tbBonuscredExtra->Close();
	Data2->tbBonuscredExtra->SQL->Clear();
	Data2->tbBonuscredExtra->SQL->Add("select * from edi_bonuscred_extras where edi_bonuscred_extras.TRATADO = 'N' limit 30000");
	Data2->tbBonuscredExtra->Open();

	final = 0;

		if(Data2->tbBonuscredExtra->RecordCount > 0)
		{
		contador = 0;

		final = Data2->tbBonuscredExtra->RecordCount;

		Label6->Caption = 0;
		Label7->Caption  = final;
		ProgressBar1->Max = final;

        Application->ProcessMessages();

			if(!DataResumo->tbPagamentosOperadoras->Active)
			{
			DataResumo->tbPagamentosOperadoras->Close();
			DataResumo->tbPagamentosOperadoras->SQL->Clear();
			DataResumo->tbPagamentosOperadoras->SQL->Add("Select * from pagamentos_operadoras where pagamentos_operadoras.CODIGO is null");
			DataResumo->tbPagamentosOperadoras->Open();
			}
			else
			{
			DataResumo->tbPagamentosOperadoras->EmptyDataSet();
			}

			//EFETUA ESSE BLOCO ATÉ ATUALIZAR TODOS OS REGISTROS
			while(contador < final)
			{
                if(Data2->tbBonuscredExtraOPERADORA->AsString == "bnc")
                {
                cod_operadora = 111;
                cod_bandeira = 201;
                operadora = "Bonuscred";
                bandeira = "Bonuscred";
                }
                else if(Data2->tbBonuscredExtraOPERADORA->AsString == "cpd")
                {
                cod_operadora = 113;
                cod_bandeira = 203;
                operadora = "Cartão Pre Datado";
                bandeira = "Cartão Pre Datado";
                }
                else if(Data2->tbBonuscredExtraOPERADORA->AsString == "ntc")
                {
                cod_operadora = 112;
                cod_bandeira = 194;
                operadora = "Nutricard";
                bandeira = "Nutricard";
                }
                else if(Data2->tbBonuscredExtraOPERADORA->AsString == "ali")
                {
                cod_operadora = 114;
                cod_bandeira = 202;
                operadora = "Alimentare";
                bandeira = "Alimentare";
                }

            cnpj_cliente = "";

            Edit1->Text = Data2->tbBonuscredExtraCPF_CNPJ->AsString;
            //LOCALIZA O CLIENTE
            consulta = "Select * from cliente_operadora where cliente_operadora.COD_ADQUIRENTE = '" + IntToStr(cod_operadora) + "'";
            consulta += " and cliente_operadora.CODIGO_ESTABELECIMENTO = '" + Edit1->Text + "'";

                if(DataResumo->tbClientesOperadoras->Active)
                {
                DataResumo->tbClientesOperadoras->EmptyDataSet();
                }

            DataResumo->tbClientesOperadoras->Close();
            DataResumo->tbClientesOperadoras->SQL->Clear();
            DataResumo->tbClientesOperadoras->SQL->Add(consulta);
            DataResumo->tbClientesOperadoras->Open();

                if(DataResumo->tbClientesOperadoras->RecordCount == 1)
                {
                cnpj_cliente = DataResumo->tbClientesOperadorasCNPJ_ESTABELECIMENTO->AsString;
                }

            //LOCALIZA O CLIENTE
            consulta = "select * from grupos_clientes where grupos_clientes.CNPJ = '" + cnpj_cliente + "'";

                if(Data1->tbGrupos->Active)
                {
                Data1->tbGrupos->EmptyDataSet();
                }

            Data1->tbGrupos->Close();
            Data1->tbGrupos->SQL->Clear();
            Data1->tbGrupos->SQL->Add(consulta);
            Data1->tbGrupos->Open();

            DataResumo->tbPagamentosOperadoras->Insert();

            DataResumo->tbPagamentosOperadorasCNPJ->Value = cnpj_cliente;
            DataResumo->tbPagamentosOperadorasCOD_ADQUIRENTE->Value = cod_operadora;

                if(Data1->tbGrupos->RecordCount > 0)
                {
                DataResumo->tbPagamentosOperadorasCOD_CLIENTE->Value = Data1->tbGruposCOD_CLIENTE->AsFloat;
                DataResumo->tbPagamentosOperadorasEMPRESA->Value = Data1->tbGruposNOME_EMPRESA->AsString;
                DataResumo->tbPagamentosOperadorasCOD_GRUPO_CLIENTE->Value = Data1->tbGruposCODIGO->AsFloat;
                DataResumo->tbPagamentosOperadorasCNPJ->Value = cnpj_cliente;
                }
                else
                {
                DataResumo->tbPagamentosOperadorasEMPRESA->Value = "EMPRESA NÃO IDENTIFICADA";
                }

            DataResumo->tbPagamentosOperadorasAGENCIA->Value = retirarZerosEsquerda(sem_digito(Data2->tbBonuscredExtraAGENCIA->AsString));
            DataResumo->tbPagamentosOperadorasBANCO->Value = StrToInt(Data2->tbBonuscredExtraNUMERO_CODIGO->AsString);
            DataResumo->tbPagamentosOperadorasCOD_BANCO->Value = StrToFloat(DataResumo->tbPagamentosOperadorasBANCO->AsFloat);
            DataResumo->tbPagamentosOperadorasCONTA->Value = retirarZerosEsquerda(retirar_caracteres(Data2->tbBonuscredExtraCONTA->AsString));

            //CONCILIADO
            DataResumo->tbPagamentosOperadorasCOD_STATUS->Value = 1;

            //STATUS = LIQUIDADO
            DataResumo->tbPagamentosOperadorasCOD_STATUS_FINANCEIRO->Value = 2;

            DataResumo->tbPagamentosOperadorasVINCULADO_VENDA->Value = 'N';
            DataResumo->tbPagamentosOperadorasENCONTRADA_VENDA->Value = 'N';
            DataResumo->tbPagamentosOperadorasDUPLICIDADE_VERIFICADA->Value = 'S';

            DataResumo->tbPagamentosOperadorasDATA_PROCESSAMENTO->Value = Date();
            DataResumo->tbPagamentosOperadorasHORA_PROCESSAMENTO->Value = Time();

            DataResumo->tbPagamentosOperadorasID_LOJA->Value = Data2->tbBonuscredExtraCPF_CNPJ->AsString;

            DataResumo->tbPagamentosOperadorasDATA_VENDA->Value = Data2->tbBonuscredExtraDATA_MOVIMENTO->AsDateTime;
            DataResumo->tbPagamentosOperadorasDATA_PREV_PAG_ORIGINAL->Value = Data2->tbBonuscredExtraDATA_MOVIMENTO->AsDateTime;
            DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->Value = DataResumo->tbPagamentosOperadorasDATA_PREV_PAG_ORIGINAL->AsDateTime;

            /*PAGAMENTO NORMAL
            1 - NORMAL
            2 - ANTECIPADO
            */

            DataResumo->tbPagamentosOperadorasCOD_TIPO_PAGAMENTO->Value = 1;

            DataResumo->tbPagamentosOperadorasVALOR_BRUTO->Value = Data2->tbBonuscredExtraVALOR_LIQUIDO->AsFloat;
            DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->Value = Data2->tbBonuscredExtraVALOR_LIQUIDO->AsFloat;
            DataResumo->tbPagamentosOperadorasVALOR_TAXA->Value = 0;
            DataResumo->tbPagamentosOperadorasTAXA_PERCENTUAL->Value = 0;

                if(DataResumo->tbPagamentosOperadorasVALOR_LIQUIDO->AsFloat < 0)
                {
                //DÉBITO
                DataResumo->tbPagamentosOperadorasCOD_TIPO_LANCAMENTO->Value = 2;
                }
                else
                {
                //CRÉDITO
                DataResumo->tbPagamentosOperadorasCOD_TIPO_LANCAMENTO->Value = 3;
                }

            //PRODUTO = NÃO IDENTIFICADO
            DataResumo->tbPagamentosOperadorasCOD_PRODUTO->Value = 54;
            DataResumo->tbPagamentosOperadorasCOD_FORMA_PAGAMENTO->Value = 23;

            //CONTROLE DAS BANDEIRAS
            DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->Value = cod_bandeira;

            //LOCALIZA O CÓDIGO DO AJUSTE
            consulta = "select * from controle_ajustes where controle_ajustes.CODIGO is not null";
            consulta += " and controle_ajustes.COD_ADQUIRENTE = 111";
            consulta += " and controle_ajustes.DESCRICAO_OPERADORA = '" + Data2->tbBonuscredExtraHISTORICO->AsString + "'";

                if(Data1->tbControleAjustes->Active)
                {
                Data1->tbControleAjustes->EmptyDataSet();
                }

            Data1->tbControleAjustes->Close();
            Data1->tbControleAjustes->SQL->Clear();
            Data1->tbControleAjustes->SQL->Add(consulta);
            Data1->tbControleAjustes->Open();

                if(Data1->tbControleAjustes->RecordCount > 0)
                {
                DataResumo->tbPagamentosOperadorasCOD_AJUSTE->Value = Data1->tbControleAjustesCODIGO->AsFloat;
                }

            //CONTROLE DE DUPLICIDADE
            consulta = "select * from pagamentos_operadoras where pagamentos_operadoras.CODIGO is not null";
            consulta += " and pagamentos_operadoras.COD_ADQUIRENTE = '" + IntToStr(cod_operadora) + "'";

            Edit1->Text = cnpj_cliente;
            consulta += " and pagamentos_operadoras.CNPJ = '" + Edit1->Text + "'";

            consulta += " and pagamentos_operadoras.COD_TIPO_LANCAMENTO = '" + DataResumo->tbPagamentosOperadorasCOD_TIPO_LANCAMENTO->AsString + "'";
            consulta += " and pagamentos_operadoras.COD_AJUSTE = '" + DataResumo->tbPagamentosOperadorasCOD_AJUSTE->AsString + "'";

            Edit1->Text = DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->AsString.SubString(7,4) + "-" + DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->AsString.SubString(4,2) + "-" + DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->AsString.SubString(0,2);
            consulta += " and pagamentos_operadoras.DATA_PAGAMENTO = '" + Edit1->Text + "'";

                if(Data1->tbPagamentosOperadoras->Active)
                {
                Data1->tbPagamentosOperadoras->EmptyDataSet();
                }

            Data1->tbPagamentosOperadoras->Close();
            Data1->tbPagamentosOperadoras->SQL->Clear();
            Data1->tbPagamentosOperadoras->SQL->Add(consulta);
            Data1->tbPagamentosOperadoras->Open();

                if(Data1->tbPagamentosOperadoras->RecordCount == 0)
                {
                //COMPLETA A CHAVE NO PADRÃO
                //cod_cliente-cod_operadora-data_venda_formato_americano-Parcela_atual-total_parcelas_NSU_AUTORIZAÇÃO-cod_Bandeira-cod_modalidade

                Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_CLIENTE->AsFloat;
                chave = Edit1->Text;

                    //VERIFICA SE FOI INFORMADA A OPERADORA
                    if(DataResumo->tbPagamentosOperadorasCOD_ADQUIRENTE->AsFloat > 0)
                    {
                    Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_ADQUIRENTE->AsFloat;
                    chave += "-" + Edit1->Text;
                    }

                dtPresent = DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->AsDateTime;
                DecodeDate(dtPresent, Year, Month, Day);

                Edit1->Text = Year;
                data_venda = Edit1->Text + "-";
                Edit1->Text = Month;
                data_venda = data_venda + Edit1->Text + "-";
                Edit1->Text = Day;
                data_venda = data_venda + Edit1->Text;

                Edit1->Text = data_venda;

                chave += "-" + Edit1->Text;

                //COMPLETA A PARCELA ATUAL
                Edit1->Text = DataResumo->tbPagamentosOperadorasPARCELA->AsFloat;

                chave += "-" + Edit1->Text;

                //COMPLETA O CAMPO TOTAL DE PARCELAS
                Edit1->Text = DataResumo->tbPagamentosOperadorasTOTAL_PARCELAS->AsFloat;
                chave += "-" + Edit1->Text;

                    //VERIFICA SE A VENDA POSSUI NSU
                    if(DataResumo->tbPagamentosOperadorasNSU->AsString != "")
                    {
                    chave += "-" + DataResumo->tbPagamentosOperadorasNSU->AsString;
                    }

                    //VERIFICA SE A VENDA POSSUI AUTORIZAÇÃO
                    if(DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->AsString != "")
                    {
                    chave += "-" + DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->AsString;
                    }

                    if(DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->AsFloat > 0)
                    {
                    Edit1->Text = DataResumo->tbPagamentosOperadorasCOD_BANDEIRA->AsFloat;
                    chave += "-" + Edit1->Text;
                    }

                DataResumo->tbPagamentosOperadorasCHAVE_PAGAMENTO->Value = chave;

                DataResumo->tbPagamentosOperadoras->ApplyUpdates(0);
                }
                else
                {
                DataResumo->tbPagamentosOperadoras->Cancel();
                }



			Data2->tbBonuscredExtra->Edit();
			Data2->tbBonuscredExtraTRATADO->Value = 'S';
			Data2->tbBonuscredExtra->ApplyUpdates(0);

			Data2->tbBonuscredExtra->Next();

            contador++;
			Label6->Caption = contador;
			ProgressBar1->Position = contador;

            Application->ProcessMessages();
			}
		}
	}
	while(final > 0);

	if(Data2->tbBonuscredExtra->Active)
	{
	Data2->tbBonuscredExtra->EmptyDataSet();
	}

Button6Click(Sender);

Edit2->Text = Date();
Edit3->Text = Time();
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::Label77Click(TObject *Sender)
{
Memo1->Lines->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::AutomaticoBonuscredClick(TObject *Sender)
{
Button1Click(Sender);
VendasBonuscredClick(Sender);
PagamentosBonuscredClick(Sender);
AjustesBonuscredClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TPrincipal::ratarCancelamentos1Click(TObject *Sender)
{
AnsiString consulta, cnpj_cliente, atualiza, data;
int final_parcelas;
Word Year, Month, Day;
TDate dtPresent;

//SELECIONA TODAS AS VENDAS DO PAGSEGURO EM TABELA BRUTA AINDA NÃO TRATADOS
Data3->tbSeguroVenda->Close();
Data3->tbSeguroVenda->SQL->Clear();
Data3->tbSeguroVenda->SQL->Add("select * from edi_pagseguro_venda where edi_pagseguro_venda.TIPO_EVENTO = '6' and edi_pagseguro_venda.PAGAMENTO_PRAZO = 'M' and edi_pagseguro_venda.TRATADO = 'N'");
Data3->tbSeguroVenda->Open();

Data3->tbSeguroVenda->Last();
int final = Data3->tbSeguroVenda->RecordCount;
Data3->tbSeguroVenda->First();

Label21->Caption = "Tratando Arquivos PagSeguro";
Label2->Caption = "Tratando Cancelamento de Vendas - Múltiplo";
Label10->Caption = 0;
Label6->Caption = 0;
Label7->Caption = final;

ProgressBar1->Max = final;
ProgressBar1->Position = 0;

Application->ProcessMessages();

	for(int contador = 0; contador < final; contador++)
	{
    //TENTA LOCALIZAR A VENDA
    consulta = "select * from vendas where vendas.CODIGO is not null";
    consulta += " and vendas.ADQID = 108";

    Edit1->Text = Data3->tbSeguroVendaESTABELECIMENTO->AsString;
    consulta += " and vendas.ESTABELECIMENTO = '" + Edit1->Text + "'";

        //PIX
        if(Data3->tbSeguroVendaMEIO_PAGAMENTO->AsInteger == 11)
        {
        consulta += " and vendas.NSU = '" + Data3->tbSeguroVendaCODIGO_TRANSACAO->AsString + "'";
        consulta += " and vendas.AUTORIZACAO = '" + Data3->tbSeguroVendaCODIGO_TRANSACAO->AsString + "'";
        }
        else
        {
        consulta += " and vendas.NSU = '" + Data3->tbSeguroVendaNSU->AsString + "'";
        consulta += " and vendas.AUTORIZACAO = '" + Data3->tbSeguroVendaCODIGO_AUTORIZACAO->AsString + "'";
        }

        if(Data3->tbSeguroVendaPARCELA->AsFloat == 0)
        {
        Edit1->Text = 1;
        }
        else
        {
        Edit1->Text = Data3->tbSeguroVendaPARCELA->AsFloat;
        }

    consulta += " and vendas.PARCELA = '" + Edit1->Text + "'";

    Edit1->Text = formatarData(3, Data3->tbSeguroVendaDATA_INICIAL_TRANSACAO->AsString);
    consulta += " and vendas.DATA_VENDA = '" + Edit1->Text + "'";


        if(DataResumo->tbVendasOperadoras->Active)
        {
        DataResumo->tbVendasOperadoras->EmptyDataSet();
        }

    DataResumo->tbVendasOperadoras->Close();
    DataResumo->tbVendasOperadoras->SQL->Clear();
    DataResumo->tbVendasOperadoras->SQL->Add(consulta);
    DataResumo->tbVendasOperadoras->Open();

        if(DataResumo->tbVendasOperadoras->RecordCount == 1)
        {
        DataResumo->tbVendasOperadoras->Edit();

        DataResumo->tbVendasOperadorasCOD_STATUS_FINANCEIRO->Value = 3; // CANCELADO
        DataResumo->tbVendasOperadorasVINCULADO_PAGAMENTO->Value = 'N';
       	DataResumo->tbVendasOperadorasDATA_CANCELAMENTO->Value = Data3->tbSeguroVendaDATA_VENDA_AJUSTE->AsDateTime;

        DataResumo->tbVendasOperadoras->ApplyUpdates(0);
        }

    Data3->tbSeguroVenda->Edit();
    Data3->tbSeguroVendaTRATADO->Value = 'S';
    Data3->tbSeguroVenda->ApplyUpdates(0);

    Data3->tbSeguroVenda->Next();

    Label6->Caption = contador+1;
    ProgressBar1->Position = contador+1;

    Application->ProcessMessages();
    }

	if(Data3->tbSeguroVenda->Active)
	{
	Data3->tbSeguroVenda->EmptyDataSet();
	}

Button6Click(Sender);

Edit2->Text = Date();
Edit3->Text = Time();


//SELECIONA TODAS AS VENDAS DO PAGSEGURO EM TABELA BRUTA AINDA NÃO TRATADOS
Data3->tbSeguroVenda->Close();
Data3->tbSeguroVenda->SQL->Clear();
Data3->tbSeguroVenda->SQL->Add("select * from edi_pagseguro_venda where edi_pagseguro_venda.TIPO_EVENTO = '6' and edi_pagseguro_venda.PAGAMENTO_PRAZO = 'U' and edi_pagseguro_venda.TRATADO = 'N'");
Data3->tbSeguroVenda->Open();

Data3->tbSeguroVenda->Last();
final = Data3->tbSeguroVenda->RecordCount;
Data3->tbSeguroVenda->First();

Label21->Caption = "Tratando Arquivos PagSeguro";
Label2->Caption = "Tratando Cancelamento de Vendas - Único";
Label10->Caption = 0;
Label6->Caption = 0;
Label7->Caption = final;

ProgressBar1->Max = final;
ProgressBar1->Position = 0;

Application->ProcessMessages();

	for(int contador = 0; contador < final; contador++)
	{
    final_parcelas =  Data3->tbSeguroVendaQUANTIDADE_PARCELA->AsInteger;

        if(final_parcelas == 0)
        {
        final_parcelas = 1;
        }

        for(int contador_parcelas = 1; contador_parcelas <= final_parcelas; contador_parcelas++)
        {
        //TENTA LOCALIZAR A VENDA
        consulta = "select * from vendas where vendas.CODIGO is not null";
        consulta += " and vendas.ADQID = 108";

        Edit1->Text = Data3->tbSeguroVendaESTABELECIMENTO->AsString;
        consulta += " and vendas.ESTABELECIMENTO = '" + Edit1->Text + "'";

            //PIX
            if(Data3->tbSeguroVendaMEIO_PAGAMENTO->AsInteger == 11)
            {
            consulta += " and vendas.NSU = '" + Data3->tbSeguroVendaCODIGO_TRANSACAO->AsString + "'";
            consulta += " and vendas.AUTORIZACAO = '" + Data3->tbSeguroVendaCODIGO_TRANSACAO->AsString + "'";
            }
            else
            {
            consulta += " and vendas.NSU = '" + Data3->tbSeguroVendaNSU->AsString + "'";
            consulta += " and vendas.AUTORIZACAO = '" + Data3->tbSeguroVendaCODIGO_AUTORIZACAO->AsString + "'";
            }

        Edit1->Text = contador_parcelas;
        consulta += " and vendas.PARCELA = '" + Edit1->Text + "'";

        Edit1->Text = formatarData(3, Data3->tbSeguroVendaDATA_INICIAL_TRANSACAO->AsString);
        consulta += " and vendas.DATA_VENDA = '" + Edit1->Text + "'";


            if(DataResumo->tbVendasOperadoras->Active)
            {
            DataResumo->tbVendasOperadoras->EmptyDataSet();
            }

        DataResumo->tbVendasOperadoras->Close();
        DataResumo->tbVendasOperadoras->SQL->Clear();
        DataResumo->tbVendasOperadoras->SQL->Add(consulta);
        DataResumo->tbVendasOperadoras->Open();

            if(DataResumo->tbVendasOperadoras->RecordCount == 1)
            {
            DataResumo->tbVendasOperadoras->Edit();

            DataResumo->tbVendasOperadorasCOD_STATUS_FINANCEIRO->Value = 3; // CANCELADO
            DataResumo->tbVendasOperadorasVINCULADO_PAGAMENTO->Value = 'N';
            DataResumo->tbVendasOperadorasDATA_CANCELAMENTO->Value = Data3->tbSeguroVendaDATA_VENDA_AJUSTE->AsDateTime;

            DataResumo->tbVendasOperadoras->ApplyUpdates(0);
            }
        }

    Data3->tbSeguroVenda->Edit();
    Data3->tbSeguroVendaTRATADO->Value = 'S';
    Data3->tbSeguroVenda->ApplyUpdates(0);

    Data3->tbSeguroVenda->Next();

    Label6->Caption = contador+1;
    ProgressBar1->Position = contador+1;

    Application->ProcessMessages();
    }

	if(Data3->tbSeguroVenda->Active)
	{
	Data3->tbSeguroVenda->EmptyDataSet();
	}

Button6Click(Sender);

Edit2->Text = Date();
Edit3->Text = Time();
}
//---------------------------------------------------------------------------


void __fastcall TPrincipal::Corrigirndeparcelarecebimentonico1Click(TObject *Sender)

{
Label21->Caption = "Corrigir nº de parcela recebimento único - PagSeguro";

AnsiString consulta;
int final_parcelas;

consulta = "select NSU, CODIGO_AUTORIZACAO, ID_LOJA, PARCELA, TOTAL_PARCELAS, DATA_PAGAMENTO, count(pagamentos_operadoras.CODIGO) as total from pagamentos_operadoras where COD_ADQUIRENTE = 108";
consulta += " and OBSERVACOES = 'Venda com recebimento único'";
consulta += " and TOTAL_PARCELAS > 1";
consulta += " and PARCELA = 1";
consulta += " group by NSU, CODIGO_AUTORIZACAO, ID_LOJA, PARCELA, TOTAL_PARCELAS, DATA_PAGAMENTO";
consulta += " HAVING COUNT(pagamentos_operadoras.CODIGO) > 1";

DataProcessamento->tbPagamentosDuplicidade3->Close();
DataProcessamento->tbPagamentosDuplicidade3->SQL->Clear();
DataProcessamento->tbPagamentosDuplicidade3->SQL->Add(consulta);
DataProcessamento->tbPagamentosDuplicidade3->Open();

DataProcessamento->tbPagamentosDuplicidade3->Last();
int final = DataProcessamento->tbPagamentosDuplicidade3->RecordCount;
DataProcessamento->tbPagamentosDuplicidade3->First();

Label6->Caption = 0;
Label7->Caption = final;
ProgressBar1->Position = 0;
ProgressBar1->Max = final;

Application->ProcessMessages();

	for(int contador = 0; contador < final; contador++)
    {
    //TENTA LOCALIZAR O PAGAMENTO
    consulta = "SELECT * FROM pagamentos_operadoras where";
    consulta += " pagamentos_operadoras.ID_LOJA = '" + DataProcessamento->tbPagamentosDuplicidade3ID_LOJA->AsString + "'";
    consulta += " and pagamentos_operadoras.COD_ADQUIRENTE = 108";
    consulta += " and pagamentos_operadoras.PARCELA = '1'";
    consulta += " and pagamentos_operadoras.NSU = '" + DataProcessamento->tbPagamentosDuplicidade3NSU->AsString + "'";
    consulta += " and pagamentos_operadoras.CODIGO_AUTORIZACAO = '" + DataProcessamento->tbPagamentosDuplicidade3CODIGO_AUTORIZACAO->AsString + "'";

    Edit1->Text = formatarData(3, DataProcessamento->tbPagamentosDuplicidade3DATA_PAGAMENTO->AsString);
    consulta += " and pagamentos_operadoras.DATA_PAGAMENTO = '" + Edit1->Text + "'";

    DataResumo->tbPagamentosOperadoras->Close();
    DataResumo->tbPagamentosOperadoras->SQL->Clear();
    DataResumo->tbPagamentosOperadoras->SQL->Add(consulta);
    DataResumo->tbPagamentosOperadoras->Open();

        if(DataResumo->tbPagamentosOperadoras->RecordCount == DataProcessamento->tbPagamentosDuplicidade3TOTAL_PARCELAS->AsInteger)
        {
        final_parcelas = DataResumo->tbPagamentosOperadoras->RecordCount;

            for(int contador_parcelas = 1; contador_parcelas <= final_parcelas; contador_parcelas++)
            {
            DataResumo->tbPagamentosOperadoras->Edit();
            DataResumo->tbPagamentosOperadorasPARCELA->Value = contador_parcelas;
            DataResumo->tbPagamentosOperadoras->ApplyUpdates(0);

            //TENTA LOCALIZAR A VENDA
            consulta = "SELECT * FROM vendas where vendas.COD_STATUS_FINANCEIRO = '1' and vendas.ESTABELECIMENTO = '" + DataResumo->tbPagamentosOperadorasID_LOJA->AsString  + "'";
            consulta += " and vendas.ADQID = 108";

            consulta += " and vendas.PARCELA = '" + DataResumo->tbPagamentosOperadorasPARCELA->AsString + "'";
            consulta += " and vendas.NSU = '" + DataResumo->tbPagamentosOperadorasNSU->AsString + "'";
            consulta += " and vendas.AUTORIZACAO = '" + DataResumo->tbPagamentosOperadorasCODIGO_AUTORIZACAO->AsString + "'";

            Edit1->Text = formatarData(3, DataResumo->tbPagamentosOperadorasDATA_VENDA->AsString);
            consulta += " and vendas.DATA_VENDA = '" + Edit1->Text + "'";

                if(DataResumo->tbVendasOperadoras->Active)
                {
                DataResumo->tbVendasOperadoras->EmptyDataSet();
                }

            DataResumo->tbVendasOperadoras->Close();
            DataResumo->tbVendasOperadoras->SQL->Clear();
            DataResumo->tbVendasOperadoras->SQL->Add(consulta);
            DataResumo->tbVendasOperadoras->Open();

                if(DataResumo->tbVendasOperadoras->RecordCount == 1)
                {
                DataResumo->tbPagamentosOperadoras->Edit();

                //CONCILIADA
                DataResumo->tbPagamentosOperadorasCOD_STATUS->Value = 1;

                //STATUS = LIQUIDADO
                DataResumo->tbPagamentosOperadorasCOD_STATUS_FINANCEIRO->Value = 2;

                DataResumo->tbPagamentosOperadorasVINCULADO_VENDA->Value = 'S';
                DataResumo->tbPagamentosOperadorasENCONTRADA_VENDA->Value = 'S';
                DataResumo->tbPagamentosOperadorasCOD_VENDA->Value = DataResumo->tbVendasOperadorasCODIGO->AsFloat;
                DataResumo->tbPagamentosOperadoras->ApplyUpdates(0);

                DataResumo->tbVendasOperadoras->Edit();
                DataResumo->tbVendasOperadorasCOD_STATUS_FINANCEIRO->Value = 2;
                DataResumo->tbVendasOperadorasVINCULADO_PAGAMENTO->Value = 'S';
                DataResumo->tbVendasOperadorasCOD_PAGAMENTO->Value = DataResumo->tbPagamentosOperadorasCODIGO->AsFloat;
                DataResumo->tbVendasOperadorasDATA_PAGAMENTO->Value = DataResumo->tbPagamentosOperadorasDATA_PAGAMENTO->AsDateTime;

                DataResumo->tbVendasOperadoras->ApplyUpdates(0);
                }

            DataResumo->tbPagamentosOperadoras->Next();

            Application->ProcessMessages();
            }
        }

    DataProcessamento->tbPagamentosDuplicidade3->Next();
    Label6->Caption = contador + 1;
    Application->ProcessMessages();
    }
}
//---------------------------------------------------------------------------

