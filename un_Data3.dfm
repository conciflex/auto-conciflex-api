object Data3: TData3
  OldCreateOrder = False
  Height = 288
  Width = 693
  object DataSeguroVenda: TDataSource
    DataSet = tbSeguroVenda
    Left = 40
    Top = 28
  end
  object tbSeguroVenda: TFDQuery
    CachedUpdates = True
    Connection = Data1.Conexao
    SQL.Strings = (
      
        'select * from edi_pagseguro_venda where edi_pagseguro_venda.CODI' +
        'GO is null')
    Left = 40
    Top = 15
    object tbSeguroVendaCODIGO: TFDAutoIncField
      FieldName = 'CODIGO'
      Origin = 'CODIGO'
      ProviderFlags = [pfInWhere, pfInKey]
      ReadOnly = True
    end
    object tbSeguroVendaMOVIMENTO_API_CODIGO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'MOVIMENTO_API_CODIGO'
      Origin = 'MOVIMENTO_API_CODIGO'
      Size = 255
    end
    object tbSeguroVendaTIPO_REGISTRO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'TIPO_REGISTRO'
      Origin = 'TIPO_REGISTRO'
    end
    object tbSeguroVendaESTABELECIMENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'ESTABELECIMENTO'
      Origin = 'ESTABELECIMENTO'
      Size = 60
    end
    object tbSeguroVendaDATA_INICIAL_TRANSACAO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_INICIAL_TRANSACAO'
      Origin = 'DATA_INICIAL_TRANSACAO'
    end
    object tbSeguroVendaDATA_VENDA_AJUSTE: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_VENDA_AJUSTE'
      Origin = 'DATA_VENDA_AJUSTE'
    end
    object tbSeguroVendaTIPO_EVENTO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'TIPO_EVENTO'
      Origin = 'TIPO_EVENTO'
    end
    object tbSeguroVendaTIPO_TRANSACAO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'TIPO_TRANSACAO'
      Origin = 'TIPO_TRANSACAO'
    end
    object tbSeguroVendaNUMERO_SERIE_LEITOR: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NUMERO_SERIE_LEITOR'
      Origin = 'NUMERO_SERIE_LEITOR'
      Size = 60
    end
    object tbSeguroVendaCODIGO_TRANSACAO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_TRANSACAO'
      Origin = 'CODIGO_TRANSACAO'
      Size = 255
    end
    object tbSeguroVendaCODIGO_VENDA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_VENDA'
      Origin = 'CODIGO_VENDA'
      Size = 255
    end
    object tbSeguroVendaVALOR_TOTAL_TRANSACAO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_TOTAL_TRANSACAO'
      Origin = 'VALOR_TOTAL_TRANSACAO'
    end
    object tbSeguroVendaVALOR_PARCELA: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_PARCELA'
      Origin = 'VALOR_PARCELA'
    end
    object tbSeguroVendaPAGAMENTO_PRAZO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'PAGAMENTO_PRAZO'
      Origin = 'PAGAMENTO_PRAZO'
      Size = 10
    end
    object tbSeguroVendaPLANO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'PLANO'
      Origin = 'PLANO'
    end
    object tbSeguroVendaPARCELA: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'PARCELA'
      Origin = 'PARCELA'
    end
    object tbSeguroVendaQUANTIDADE_PARCELA: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'QUANTIDADE_PARCELA'
      Origin = 'QUANTIDADE_PARCELA'
    end
    object tbSeguroVendaDATA_PREVISTA_PAGAMENTO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_PREVISTA_PAGAMENTO'
      Origin = 'DATA_PREVISTA_PAGAMENTO'
    end
    object tbSeguroVendaTAXA_PARCELA_COMPRADOR: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'TAXA_PARCELA_COMPRADOR'
      Origin = 'TAXA_PARCELA_COMPRADOR'
    end
    object tbSeguroVendaTARIFA_BOLETO_COMPRA: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'TARIFA_BOLETO_COMPRA'
      Origin = 'TARIFA_BOLETO_COMPRA'
    end
    object tbSeguroVendaVALOR_ORIGINAL_TRANSACAO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_ORIGINAL_TRANSACAO'
      Origin = 'VALOR_ORIGINAL_TRANSACAO'
    end
    object tbSeguroVendaTAXA_PARCELA_VENDEDOR: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'TAXA_PARCELA_VENDEDOR'
      Origin = 'TAXA_PARCELA_VENDEDOR'
    end
    object tbSeguroVendaTAXA_INTERMEDIACAO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'TAXA_INTERMEDIACAO'
      Origin = 'TAXA_INTERMEDIACAO'
    end
    object tbSeguroVendaTARIFA_INTERMEDIACAO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'TARIFA_INTERMEDIACAO'
      Origin = 'TARIFA_INTERMEDIACAO'
    end
    object tbSeguroVendaTARIFA_BOLETO_VENDEDOR: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'TARIFA_BOLETO_VENDEDOR'
      Origin = 'TARIFA_BOLETO_VENDEDOR'
    end
    object tbSeguroVendaTAXA_REP_APLICACAO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'TAXA_REP_APLICACAO'
      Origin = 'TAXA_REP_APLICACAO'
    end
    object tbSeguroVendaVALOR_LIQUIDO_TRANSACAO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_LIQUIDO_TRANSACAO'
      Origin = 'VALOR_LIQUIDO_TRANSACAO'
    end
    object tbSeguroVendaSTATUS_PAGAMENTO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'STATUS_PAGAMENTO'
      Origin = 'STATUS_PAGAMENTO'
    end
    object tbSeguroVendaINSTITUICAO_FINANCEIRA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'INSTITUICAO_FINANCEIRA'
      Origin = 'INSTITUICAO_FINANCEIRA'
      Size = 60
    end
    object tbSeguroVendaCANAL_ENTRADA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CANAL_ENTRADA'
      Origin = 'CANAL_ENTRADA'
      Size = 10
    end
    object tbSeguroVendaLEITOR: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'LEITOR'
      Origin = 'LEITOR'
      Size = 60
    end
    object tbSeguroVendaMEIO_CAPTURA: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'MEIO_CAPTURA'
      Origin = 'MEIO_CAPTURA'
    end
    object tbSeguroVendaNUM_LOGICO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NUM_LOGICO'
      Origin = 'NUM_LOGICO'
      Size = 30
    end
    object tbSeguroVendaNSU: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NSU'
      Origin = 'NSU'
      Size = 255
    end
    object tbSeguroVendaCARTAO_BIN: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CARTAO_BIN'
      Origin = 'CARTAO_BIN'
      Size = 255
    end
    object tbSeguroVendaCARTAO_HOLDER: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CARTAO_HOLDER'
      Origin = 'CARTAO_HOLDER'
      Size = 255
    end
    object tbSeguroVendaCODIGO_AUTORIZACAO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_AUTORIZACAO'
      Origin = 'CODIGO_AUTORIZACAO'
      Size = 255
    end
    object tbSeguroVendaCODIGO_CV: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_CV'
      Origin = 'CODIGO_CV'
      Size = 255
    end
    object tbSeguroVendaMEIO_PAGAMENTO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'MEIO_PAGAMENTO'
      Origin = 'MEIO_PAGAMENTO'
    end
    object tbSeguroVendaCOD_CADASTRO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'COD_CADASTRO'
      Origin = 'COD_CADASTRO'
    end
    object tbSeguroVendaHORA_VENDA_AJUSTE: TTimeField
      AutoGenerateValue = arDefault
      FieldName = 'HORA_VENDA_AJUSTE'
      Origin = 'HORA_VENDA_AJUSTE'
    end
    object tbSeguroVendaTRATADO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'TRATADO'
      Origin = 'TRATADO'
      Size = 1
    end
    object tbSeguroVendaDATA_LEITURA: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_LEITURA'
      Origin = 'DATA_LEITURA'
    end
    object tbSeguroVendaHORA_LEITURA: TTimeField
      AutoGenerateValue = arDefault
      FieldName = 'HORA_LEITURA'
      Origin = 'HORA_LEITURA'
    end
    object tbSeguroVendaCOD_CLIENTE: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'COD_CLIENTE'
      Origin = 'COD_CLIENTE'
    end
  end
  object DataSeguroPagamento: TDataSource
    DataSet = tbSeguroPagamento
    Left = 160
    Top = 28
  end
  object tbSeguroPagamento: TFDQuery
    CachedUpdates = True
    Connection = Data1.Conexao
    SQL.Strings = (
      
        'select * from edi_pagseguro_pagamento where edi_pagseguro_pagame' +
        'nto.CODIGO is null')
    Left = 160
    Top = 15
    object tbSeguroPagamentoCODIGO: TFDAutoIncField
      FieldName = 'CODIGO'
      Origin = 'CODIGO'
      ProviderFlags = [pfInWhere, pfInKey]
      ReadOnly = True
    end
    object tbSeguroPagamentoMOVIMENTO_API_CODIGO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'MOVIMENTO_API_CODIGO'
      Origin = 'MOVIMENTO_API_CODIGO'
      Size = 255
    end
    object tbSeguroPagamentoTIPO_REGISTRO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'TIPO_REGISTRO'
      Origin = 'TIPO_REGISTRO'
    end
    object tbSeguroPagamentoESTABELECIMENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'ESTABELECIMENTO'
      Origin = 'ESTABELECIMENTO'
      Size = 30
    end
    object tbSeguroPagamentoDATA_INICIAL_TRANSACAO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_INICIAL_TRANSACAO'
      Origin = 'DATA_INICIAL_TRANSACAO'
    end
    object tbSeguroPagamentoDATA_VENDA_AJUSTE: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_VENDA_AJUSTE'
      Origin = 'DATA_VENDA_AJUSTE'
    end
    object tbSeguroPagamentoHORA_VENDA_AJUSTE: TTimeField
      AutoGenerateValue = arDefault
      FieldName = 'HORA_VENDA_AJUSTE'
      Origin = 'HORA_VENDA_AJUSTE'
    end
    object tbSeguroPagamentoTIPO_EVENTO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'TIPO_EVENTO'
      Origin = 'TIPO_EVENTO'
    end
    object tbSeguroPagamentoTIPO_TRANSACAO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'TIPO_TRANSACAO'
      Origin = 'TIPO_TRANSACAO'
    end
    object tbSeguroPagamentoCODIGO_AUTORIZACAO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_AUTORIZACAO'
      Origin = 'CODIGO_AUTORIZACAO'
      Size = 255
    end
    object tbSeguroPagamentoCODIGO_VENDA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_VENDA'
      Origin = 'CODIGO_VENDA'
    end
    object tbSeguroPagamentoVALOR_TOTAL_TRANSACAO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_TOTAL_TRANSACAO'
      Origin = 'VALOR_TOTAL_TRANSACAO'
    end
    object tbSeguroPagamentoVALOR_PARCELA: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_PARCELA'
      Origin = 'VALOR_PARCELA'
    end
    object tbSeguroPagamentoPAGAMENTO_PRAZO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'PAGAMENTO_PRAZO'
      Origin = 'PAGAMENTO_PRAZO'
      Size = 10
    end
    object tbSeguroPagamentoPLANO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'PLANO'
      Origin = 'PLANO'
    end
    object tbSeguroPagamentoPARCELA: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'PARCELA'
      Origin = 'PARCELA'
    end
    object tbSeguroPagamentoQUANTIDADE_PARCELA: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'QUANTIDADE_PARCELA'
      Origin = 'QUANTIDADE_PARCELA'
    end
    object tbSeguroPagamentoDATA_MOVIMENTACAO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_MOVIMENTACAO'
      Origin = 'DATA_MOVIMENTACAO'
    end
    object tbSeguroPagamentoTAXA_PARCELA_COMPRADOR: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'TAXA_PARCELA_COMPRADOR'
      Origin = 'TAXA_PARCELA_COMPRADOR'
    end
    object tbSeguroPagamentoTARIFA_BOLETO_COMPRA: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'TARIFA_BOLETO_COMPRA'
      Origin = 'TARIFA_BOLETO_COMPRA'
    end
    object tbSeguroPagamentoVALOR_ORIGINAL_TRANSACAO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_ORIGINAL_TRANSACAO'
      Origin = 'VALOR_ORIGINAL_TRANSACAO'
    end
    object tbSeguroPagamentoTAXA_PARCELA_VENDEDOR: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'TAXA_PARCELA_VENDEDOR'
      Origin = 'TAXA_PARCELA_VENDEDOR'
    end
    object tbSeguroPagamentoTAXA_INTERMEDIACAO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'TAXA_INTERMEDIACAO'
      Origin = 'TAXA_INTERMEDIACAO'
    end
    object tbSeguroPagamentoTARIFA_INTERMEDIACAO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'TARIFA_INTERMEDIACAO'
      Origin = 'TARIFA_INTERMEDIACAO'
    end
    object tbSeguroPagamentoTARIFA_BOLETO_VENDEDOR: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'TARIFA_BOLETO_VENDEDOR'
      Origin = 'TARIFA_BOLETO_VENDEDOR'
    end
    object tbSeguroPagamentoTAXA_REP_APLICACAO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'TAXA_REP_APLICACAO'
      Origin = 'TAXA_REP_APLICACAO'
    end
    object tbSeguroPagamentoVALOR_LIQUIDO_TRANSACAO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_LIQUIDO_TRANSACAO'
      Origin = 'VALOR_LIQUIDO_TRANSACAO'
    end
    object tbSeguroPagamentoTAXA_ANTECIPACAO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'TAXA_ANTECIPACAO'
      Origin = 'TAXA_ANTECIPACAO'
    end
    object tbSeguroPagamentoVALOR_LIQUIDO_ANTECIPACAO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_LIQUIDO_ANTECIPACAO'
      Origin = 'VALOR_LIQUIDO_ANTECIPACAO'
    end
    object tbSeguroPagamentoSTATUS_PAGAMENTO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'STATUS_PAGAMENTO'
      Origin = 'STATUS_PAGAMENTO'
    end
    object tbSeguroPagamentoIDENTIFICADOR_REVENDA: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'IDENTIFICADOR_REVENDA'
      Origin = 'IDENTIFICADOR_REVENDA'
    end
    object tbSeguroPagamentoMEIO_PAGAMENTO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'MEIO_PAGAMENTO'
      Origin = 'MEIO_PAGAMENTO'
    end
    object tbSeguroPagamentoINSTITUICAO_FINANCEIRA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'INSTITUICAO_FINANCEIRA'
      Origin = 'INSTITUICAO_FINANCEIRA'
      Size = 60
    end
    object tbSeguroPagamentoCANAL_ENTRADA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CANAL_ENTRADA'
      Origin = 'CANAL_ENTRADA'
      Size = 10
    end
    object tbSeguroPagamentoLEITOR: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'LEITOR'
      Origin = 'LEITOR'
      Size = 255
    end
    object tbSeguroPagamentoMEIO_CAPTURA: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'MEIO_CAPTURA'
      Origin = 'MEIO_CAPTURA'
    end
    object tbSeguroPagamentoCOD_BANCO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'COD_BANCO'
      Origin = 'COD_BANCO'
    end
    object tbSeguroPagamentoNUM_LOGICO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NUM_LOGICO'
      Origin = 'NUM_LOGICO'
      Size = 255
    end
    object tbSeguroPagamentoNSU: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NSU'
      Origin = 'NSU'
      Size = 60
    end
    object tbSeguroPagamentoCARTAO_BIN: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CARTAO_BIN'
      Origin = 'CARTAO_BIN'
      Size = 60
    end
    object tbSeguroPagamentoCARTAO_HOLDER: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CARTAO_HOLDER'
      Origin = 'CARTAO_HOLDER'
      Size = 60
    end
    object tbSeguroPagamentoCODIGO_CV: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_CV'
      Origin = 'CODIGO_CV'
      Size = 60
    end
    object tbSeguroPagamentoCODIGO_TRANSACAO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_TRANSACAO'
      Origin = 'CODIGO_TRANSACAO'
      Size = 255
    end
    object tbSeguroPagamentoBANCO_AGENCIA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'BANCO_AGENCIA'
      Origin = 'BANCO_AGENCIA'
      Size = 50
    end
    object tbSeguroPagamentoCONTA_BANCO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CONTA_BANCO'
      Origin = 'CONTA_BANCO'
      Size = 15
    end
    object tbSeguroPagamentoTRATADO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'TRATADO'
      Origin = 'TRATADO'
      Size = 1
    end
    object tbSeguroPagamentoDATA_LEITURA: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_LEITURA'
      Origin = 'DATA_LEITURA'
    end
    object tbSeguroPagamentoHORA_LEITURA: TTimeField
      AutoGenerateValue = arDefault
      FieldName = 'HORA_LEITURA'
      Origin = 'HORA_LEITURA'
    end
    object tbSeguroPagamentoCOD_CLIENTE: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'COD_CLIENTE'
      Origin = 'COD_CLIENTE'
    end
  end
  object DataSeguroCadastro: TDataSource
    DataSet = tbSeguroCadastro
    Left = 296
    Top = 28
  end
  object tbSeguroCadastro: TFDQuery
    CachedUpdates = True
    Connection = Data1.Conexao
    SQL.Strings = (
      
        'Select * from cliente_operadora where cliente_operadora.INTEGRA_' +
        'API_PAGSEGURO = '#39'S'#39
      ''
      'and cliente_operadora.COD_ADQUIRENTE = '#39'108'#39)
    Left = 296
    Top = 15
    object tbSeguroCadastroCODIGO: TFDAutoIncField
      FieldName = 'CODIGO'
      Origin = 'CODIGO'
      ProviderFlags = [pfInUpdate, pfInWhere, pfInKey]
      IdentityInsert = True
    end
    object tbSeguroCadastroCOD_CLIENTE: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_CLIENTE'
      Origin = 'COD_CLIENTE'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroCadastroCOD_ADQUIRENTE: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_ADQUIRENTE'
      Origin = 'COD_ADQUIRENTE'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroCadastroCODIGO_ESTABELECIMENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_ESTABELECIMENTO'
      Origin = 'CODIGO_ESTABELECIMENTO'
      ProviderFlags = [pfInUpdate]
      Size = 50
    end
    object tbSeguroCadastroCNPJ_ESTABELECIMENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CNPJ_ESTABELECIMENTO'
      Origin = 'CNPJ_ESTABELECIMENTO'
      ProviderFlags = [pfInUpdate]
      Size = 45
    end
    object tbSeguroCadastroCOD_GRUPO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_GRUPO'
      Origin = 'COD_GRUPO'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroCadastroAFFILIATION_KEY: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'AFFILIATION_KEY'
      Origin = 'AFFILIATION_KEY'
      ProviderFlags = [pfInUpdate]
      Size = 60
    end
    object tbSeguroCadastroINTEGRA_API_PAGSEGURO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'INTEGRA_API_PAGSEGURO'
      Origin = 'INTEGRA_API_PAGSEGURO'
      ProviderFlags = [pfInUpdate]
      Size = 1
    end
  end
  object DataSeguroAntecipacao: TDataSource
    DataSet = tbSeguroAntecipacao
    Left = 428
    Top = 24
  end
  object tbSeguroAntecipacao: TFDQuery
    CachedUpdates = True
    Connection = Data1.Conexao
    SQL.Strings = (
      
        'Select * from edi_pagseguro_antecipacao where edi_pagseguro_ante' +
        'cipacao.CODIGO is null')
    Left = 428
    Top = 11
    object tbSeguroAntecipacaoCODIGO: TFDAutoIncField
      FieldName = 'CODIGO'
      Origin = 'CODIGO'
      ProviderFlags = [pfInUpdate, pfInWhere, pfInKey]
      IdentityInsert = True
    end
    object tbSeguroAntecipacaoMOVIMENTO_API_CODIGO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'MOVIMENTO_API_CODIGO'
      Origin = 'MOVIMENTO_API_CODIGO'
      ProviderFlags = [pfInUpdate]
      Size = 255
    end
    object tbSeguroAntecipacaoTIPO_REGISTRO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'TIPO_REGISTRO'
      Origin = 'TIPO_REGISTRO'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoESTABELECIMENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'ESTABELECIMENTO'
      Origin = 'ESTABELECIMENTO'
      ProviderFlags = [pfInUpdate]
      Size = 60
    end
    object tbSeguroAntecipacaoDATA_INICIAL_TRANSACAO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_INICIAL_TRANSACAO'
      Origin = 'DATA_INICIAL_TRANSACAO'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoDATA_VENDA_AJUSTE: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_VENDA_AJUSTE'
      Origin = 'DATA_VENDA_AJUSTE'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoHORA_VENDA_AJUSTE: TTimeField
      AutoGenerateValue = arDefault
      FieldName = 'HORA_VENDA_AJUSTE'
      Origin = 'HORA_VENDA_AJUSTE'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoTIPO_EVENTO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'TIPO_EVENTO'
      Origin = 'TIPO_EVENTO'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoTIPO_TRANSACAO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'TIPO_TRANSACAO'
      Origin = 'TIPO_TRANSACAO'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoNUMERO_SERIE_LEITOR: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NUMERO_SERIE_LEITOR'
      Origin = 'NUMERO_SERIE_LEITOR'
      ProviderFlags = [pfInUpdate]
      Size = 60
    end
    object tbSeguroAntecipacaoCODIGO_TRANSACAO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_TRANSACAO'
      Origin = 'CODIGO_TRANSACAO'
      ProviderFlags = [pfInUpdate]
      Size = 255
    end
    object tbSeguroAntecipacaoCODIGO_VENDA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_VENDA'
      Origin = 'CODIGO_VENDA'
      ProviderFlags = [pfInUpdate]
      Size = 255
    end
    object tbSeguroAntecipacaoVALOR_TOTAL_TRANSACAO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_TOTAL_TRANSACAO'
      Origin = 'VALOR_TOTAL_TRANSACAO'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoVALOR_PARCELA: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_PARCELA'
      Origin = 'VALOR_PARCELA'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoPAGAMENTO_PRAZO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'PAGAMENTO_PRAZO'
      Origin = 'PAGAMENTO_PRAZO'
      ProviderFlags = [pfInUpdate]
      Size = 10
    end
    object tbSeguroAntecipacaoPLANO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'PLANO'
      Origin = 'PLANO'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoPARCELA: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'PARCELA'
      Origin = 'PARCELA'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoQUANTIDADE_PARCELA: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'QUANTIDADE_PARCELA'
      Origin = 'QUANTIDADE_PARCELA'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoDATA_PREVISTA_PAGAMENTO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_PREVISTA_PAGAMENTO'
      Origin = 'DATA_PREVISTA_PAGAMENTO'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoTAXA_PARCELA_COMPRADOR: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'TAXA_PARCELA_COMPRADOR'
      Origin = 'TAXA_PARCELA_COMPRADOR'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoTARIFA_BOLETO_COMPRA: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'TARIFA_BOLETO_COMPRA'
      Origin = 'TARIFA_BOLETO_COMPRA'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoVALOR_ORIGINAL_TRANSACAO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_ORIGINAL_TRANSACAO'
      Origin = 'VALOR_ORIGINAL_TRANSACAO'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoTAXA_PARCELA_VENDEDOR: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'TAXA_PARCELA_VENDEDOR'
      Origin = 'TAXA_PARCELA_VENDEDOR'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoTAXA_INTERMEDIACAO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'TAXA_INTERMEDIACAO'
      Origin = 'TAXA_INTERMEDIACAO'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoTARIFA_INTERMEDIACAO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'TARIFA_INTERMEDIACAO'
      Origin = 'TARIFA_INTERMEDIACAO'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoTARIFA_BOLETO_VENDEDOR: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'TARIFA_BOLETO_VENDEDOR'
      Origin = 'TARIFA_BOLETO_VENDEDOR'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoTAXA_REP_APLICACAO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'TAXA_REP_APLICACAO'
      Origin = 'TAXA_REP_APLICACAO'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoVALOR_LIQUIDO_TRANSACAO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_LIQUIDO_TRANSACAO'
      Origin = 'VALOR_LIQUIDO_TRANSACAO'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoSTATUS_PAGAMENTO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'STATUS_PAGAMENTO'
      Origin = 'STATUS_PAGAMENTO'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoINSTITUICAO_FINANCEIRA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'INSTITUICAO_FINANCEIRA'
      Origin = 'INSTITUICAO_FINANCEIRA'
      ProviderFlags = [pfInUpdate]
      Size = 60
    end
    object tbSeguroAntecipacaoCANAL_ENTRADA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CANAL_ENTRADA'
      Origin = 'CANAL_ENTRADA'
      ProviderFlags = [pfInUpdate]
      Size = 10
    end
    object tbSeguroAntecipacaoLEITOR: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'LEITOR'
      Origin = 'LEITOR'
      ProviderFlags = [pfInUpdate]
      Size = 60
    end
    object tbSeguroAntecipacaoMEIO_CAPTURA: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'MEIO_CAPTURA'
      Origin = 'MEIO_CAPTURA'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoNUM_LOGICO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NUM_LOGICO'
      Origin = 'NUM_LOGICO'
      ProviderFlags = [pfInUpdate]
      Size = 30
    end
    object tbSeguroAntecipacaoNSU: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NSU'
      Origin = 'NSU'
      ProviderFlags = [pfInUpdate]
      Size = 255
    end
    object tbSeguroAntecipacaoCARTAO_BIN: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CARTAO_BIN'
      Origin = 'CARTAO_BIN'
      ProviderFlags = [pfInUpdate]
      Size = 255
    end
    object tbSeguroAntecipacaoCODIGO_AUTORIZACAO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_AUTORIZACAO'
      Origin = 'CODIGO_AUTORIZACAO'
      ProviderFlags = [pfInUpdate]
      Size = 255
    end
    object tbSeguroAntecipacaoCODIGO_CV: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_CV'
      Origin = 'CODIGO_CV'
      ProviderFlags = [pfInUpdate]
      Size = 255
    end
    object tbSeguroAntecipacaoMEIO_PAGAMENTO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'MEIO_PAGAMENTO'
      Origin = 'MEIO_PAGAMENTO'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoCOD_CADASTRO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'COD_CADASTRO'
      Origin = 'COD_CADASTRO'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoCARTAO_HOLDER: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CARTAO_HOLDER'
      Origin = 'CARTAO_HOLDER'
      ProviderFlags = [pfInUpdate]
      Size = 255
    end
    object tbSeguroAntecipacaoTRATADO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'TRATADO'
      Origin = 'TRATADO'
      ProviderFlags = [pfInUpdate]
      Size = 1
    end
    object tbSeguroAntecipacaoTAXA_ANTECIPACAO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'TAXA_ANTECIPACAO'
      Origin = 'TAXA_ANTECIPACAO'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoVALOR_LIQUIDO_ANTECIPADO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_LIQUIDO_ANTECIPADO'
      Origin = 'VALOR_LIQUIDO_ANTECIPADO'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoDATA_MOVIMENTACAO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_MOVIMENTACAO'
      Origin = 'DATA_MOVIMENTACAO'
      ProviderFlags = [pfInUpdate]
    end
    object tbSeguroAntecipacaoDATA_LEITURA: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_LEITURA'
      Origin = 'DATA_LEITURA'
    end
    object tbSeguroAntecipacaoHORA_LEITURA: TTimeField
      AutoGenerateValue = arDefault
      FieldName = 'HORA_LEITURA'
      Origin = 'HORA_LEITURA'
    end
    object tbSeguroAntecipacaoCOD_CLIENTE: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'COD_CLIENTE'
      Origin = 'COD_CLIENTE'
    end
  end
  object DataVendasErp: TDataSource
    DataSet = tbVendasErp
    Left = 556
    Top = 24
  end
  object tbVendasErp: TFDQuery
    CachedUpdates = True
    Connection = Data1.Conexao
    SQL.Strings = (
      'Select * from vendas_erp where vendas_erp.CODIGO is null')
    Left = 556
    Top = 11
    object tbVendasErpCODIGO: TFDAutoIncField
      FieldName = 'CODIGO'
      Origin = 'CODIGO'
      ProviderFlags = [pfInWhere, pfInKey]
      ReadOnly = True
    end
    object tbVendasErpCOD_PRODUTO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_PRODUTO'
      Origin = 'COD_PRODUTO'
    end
    object tbVendasErpDESCRICAO_TIPO_PRODUTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'DESCRICAO_TIPO_PRODUTO'
      Origin = 'DESCRICAO_TIPO_PRODUTO'
      Size = 100
    end
    object tbVendasErpCODIGO_AUTORIZACAO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_AUTORIZACAO'
      Origin = 'CODIGO_AUTORIZACAO'
      Size = 80
    end
    object tbVendasErpIDENTIFICADOR_PAGAMENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'IDENTIFICADOR_PAGAMENTO'
      Origin = 'IDENTIFICADOR_PAGAMENTO'
      Size = 80
    end
    object tbVendasErpDATA_VENDA: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_VENDA'
      Origin = 'DATA_VENDA'
    end
    object tbVendasErpDATA_VENCIMENTO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_VENCIMENTO'
      Origin = 'DATA_VENCIMENTO'
    end
    object tbVendasErpVALOR_VENDA_PARCELA: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_VENDA_PARCELA'
      Origin = 'VALOR_VENDA_PARCELA'
    end
    object tbVendasErpVALOR_LIQUIDO_PARCELA: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_LIQUIDO_PARCELA'
      Origin = 'VALOR_LIQUIDO_PARCELA'
    end
    object tbVendasErpTOTAL_VENDA: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'TOTAL_VENDA'
      Origin = 'TOTAL_VENDA'
    end
    object tbVendasErpTAXA: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'TAXA'
      Origin = 'TAXA'
    end
    object tbVendasErpPARCELA: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'PARCELA'
      Origin = 'PARCELA'
    end
    object tbVendasErpTOTAL_PARCELAS: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'TOTAL_PARCELAS'
      Origin = 'TOTAL_PARCELAS'
    end
    object tbVendasErpVALOR_BRUTO_MOEDA: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_BRUTO_MOEDA'
      Origin = 'VALOR_BRUTO_MOEDA'
    end
    object tbVendasErpVALOR_LIQUIDO_MOEDA: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_LIQUIDO_MOEDA'
      Origin = 'VALOR_LIQUIDO_MOEDA'
    end
    object tbVendasErpCOTACAO_MOEDA: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COTACAO_MOEDA'
      Origin = 'COTACAO_MOEDA'
    end
    object tbVendasErpCOD_MOEDA: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_MOEDA'
      Origin = 'COD_MOEDA'
    end
    object tbVendasErpNSU: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NSU'
      Origin = 'NSU'
      Size = 255
    end
    object tbVendasErpTID: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'TID'
      Origin = 'TID'
      Size = 80
    end
    object tbVendasErpTERMINAL: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'TERMINAL'
      Origin = 'TERMINAL'
      Size = 50
    end
    object tbVendasErpCOD_MEIO_CAPTURA: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_MEIO_CAPTURA'
      Origin = 'COD_MEIO_CAPTURA'
    end
    object tbVendasErpCOD_OPERADORA: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_OPERADORA'
      Origin = 'COD_OPERADORA'
    end
    object tbVendasErpCOD_MODALIDADE: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_MODALIDADE'
      Origin = 'COD_MODALIDADE'
    end
    object tbVendasErpCOD_VENDA_CLIENTE: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_VENDA_CLIENTE'
      Origin = 'COD_VENDA_CLIENTE'
    end
    object tbVendasErpCOD_PROD_VENDA_CLIENTE: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'COD_PROD_VENDA_CLIENTE'
      Origin = 'COD_PROD_VENDA_CLIENTE'
      Size = 255
    end
    object tbVendasErpCOD_CLIENTE: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'COD_CLIENTE'
      Origin = 'COD_CLIENTE'
      Size = 50
    end
    object tbVendasErpTRATADO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'TRATADO'
      Origin = 'TRATADO'
      Size = 1
    end
    object tbVendasErpCOD_STATUS_CONCILIACAO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_STATUS_CONCILIACAO'
      Origin = 'COD_STATUS_CONCILIACAO'
    end
    object tbVendasErpVALOR_TAXA: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_TAXA'
      Origin = 'VALOR_TAXA'
    end
    object tbVendasErpCOMPLEMENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'COMPLEMENTO'
      Origin = 'COMPLEMENTO'
      Size = 90
    end
    object tbVendasErpDIVERGENCIA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'DIVERGENCIA'
      Origin = 'DIVERGENCIA'
      Size = 255
    end
    object tbVendasErpBANDEIRA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'BANDEIRA'
      Origin = 'BANDEIRA'
      Size = 90
    end
    object tbVendasErpCOD_BANDEIRA: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_BANDEIRA'
      Origin = 'COD_BANDEIRA'
    end
    object tbVendasErpCOD_BANCO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_BANCO'
      Origin = 'COD_BANCO'
    end
    object tbVendasErpBANCO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'BANCO'
      Origin = 'BANCO'
      Size = 25
    end
    object tbVendasErpCONTA_CORRENTE: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CONTA_CORRENTE'
      Origin = 'CONTA_CORRENTE'
      Size = 25
    end
    object tbVendasErpAGENCIA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'AGENCIA'
      Origin = 'AGENCIA'
      Size = 25
    end
    object tbVendasErpCAMPO_ADICIONAL1: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CAMPO_ADICIONAL1'
      Origin = 'CAMPO_ADICIONAL1'
      Size = 160
    end
    object tbVendasErpCAMPO_ADICIONAL2: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CAMPO_ADICIONAL2'
      Origin = 'CAMPO_ADICIONAL2'
      Size = 160
    end
    object tbVendasErpCAMPO_ADICIONAL3: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CAMPO_ADICIONAL3'
      Origin = 'CAMPO_ADICIONAL3'
      Size = 160
    end
    object tbVendasErpJUSTIFICATIVA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'JUSTIFICATIVA'
      Origin = 'JUSTIFICATIVA'
      Size = 160
    end
    object tbVendasErpCOD_VENDAS_OPERADORAS: TLargeintField
      AutoGenerateValue = arDefault
      FieldName = 'COD_VENDAS_OPERADORAS'
      Origin = 'COD_VENDAS_OPERADORAS'
    end
    object tbVendasErpCOD_STATUS_FINANCEIRO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'COD_STATUS_FINANCEIRO'
      Origin = 'COD_STATUS_FINANCEIRO'
    end
    object tbVendasErpDATA_IMPORTACAO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_IMPORTACAO'
      Origin = 'DATA_IMPORTACAO'
    end
    object tbVendasErpHORA_IMPORTACAO: TTimeField
      AutoGenerateValue = arDefault
      FieldName = 'HORA_IMPORTACAO'
      Origin = 'HORA_IMPORTACAO'
    end
    object tbVendasErpDATA_CONCILIACAO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_CONCILIACAO'
      Origin = 'DATA_CONCILIACAO'
    end
    object tbVendasErpHORA_CONCILIACAO: TTimeField
      AutoGenerateValue = arDefault
      FieldName = 'HORA_CONCILIACAO'
      Origin = 'HORA_CONCILIACAO'
    end
    object tbVendasErpCOD_GRUPO_CLIENTE: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_GRUPO_CLIENTE'
      Origin = 'COD_GRUPO_CLIENTE'
    end
    object tbVendasErpRETORNO_ERP: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'RETORNO_ERP'
      Origin = 'RETORNO_ERP'
      Size = 1
    end
    object tbVendasErpESTABELECIMENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'ESTABELECIMENTO'
      Origin = 'ESTABELECIMENTO'
      Size = 50
    end
    object tbVendasErpTAXA_OPERADORA: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'TAXA_OPERADORA'
      Origin = 'TAXA_OPERADORA'
    end
    object tbVendasErpTAXA_DIFERENCA: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'TAXA_DIFERENCA'
      Origin = 'TAXA_DIFERENCA'
    end
    object tbVendasErpVALOR_LIQUIDO_OPERADORA: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_LIQUIDO_OPERADORA'
      Origin = 'VALOR_LIQUIDO_OPERADORA'
    end
    object tbVendasErpDIFERENCA_LIQUIDO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'DIFERENCA_LIQUIDO'
      Origin = 'DIFERENCA_LIQUIDO'
    end
    object tbVendasErpDETALHAMENTO_DIVERGENCIA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'DETALHAMENTO_DIVERGENCIA'
      Origin = 'DETALHAMENTO_DIVERGENCIA'
      Size = 255
    end
    object tbVendasErpRETORNO_ERP_BAIXA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'RETORNO_ERP_BAIXA'
      Origin = 'RETORNO_ERP_BAIXA'
      Size = 1
    end
    object tbVendasErpCAMPO_INFOTECH: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CAMPO_INFOTECH'
      Origin = 'CAMPO_INFOTECH'
      Size = 90
    end
    object tbVendasErpTID_ADICIONAL: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'TID_ADICIONAL'
      Origin = 'TID_ADICIONAL'
      Size = 60
    end
    object tbVendasErpBIN_CARTAO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'BIN_CARTAO'
      Origin = 'BIN_CARTAO'
      Size = 30
    end
    object tbVendasErpCOD_REGRA_CONCILIACAO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_REGRA_CONCILIACAO'
      Origin = 'COD_REGRA_CONCILIACAO'
    end
    object tbVendasErpCHAVE_VENDA_ERP: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CHAVE_VENDA_ERP'
      Origin = 'CHAVE_VENDA_ERP'
      Size = 60
    end
    object tbVendasErpCHAVE_VENDA_OPERADORA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CHAVE_VENDA_OPERADORA'
      Origin = 'CHAVE_VENDA_OPERADORA'
      Size = 60
    end
    object tbVendasErpDESCONCILIA_EXCLUIR: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'DESCONCILIA_EXCLUIR'
      Origin = 'DESCONCILIA_EXCLUIR'
      Size = 1
    end
    object tbVendasErpDUPLICIDADE: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'DUPLICIDADE'
      Origin = 'DUPLICIDADE'
      Size = 1
    end
    object tbVendasErpTEMPORARIO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'TEMPORARIO'
      Origin = 'TEMPORARIO'
      Size = 60
    end
    object tbVendasErpAUTORIZADOR: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'AUTORIZADOR'
      Origin = 'AUTORIZADOR'
      Size = 60
    end
    object tbVendasErpOBSERVACAO_ERP: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'OBSERVACAO_ERP'
      Origin = 'OBSERVACAO_ERP'
      Size = 200
    end
  end
end
