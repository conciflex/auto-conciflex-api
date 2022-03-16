object DataVerificacao2: TDataVerificacao2
  OldCreateOrder = False
  Height = 255
  Width = 571
  object DataSeguroVenda: TDataSource
    DataSet = tbSeguroVenda
    Left = 40
    Top = 20
  end
  object tbSeguroVenda: TFDQuery
    CachedUpdates = True
    Connection = Data1.Conexao
    SQL.Strings = (
      
        'select * from edi_pagseguro_venda where edi_pagseguro_venda.CODI' +
        'GO is null')
    Left = 40
    Top = 7
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
    Top = 20
  end
  object tbSeguroPagamento: TFDQuery
    CachedUpdates = True
    Connection = Data1.Conexao
    SQL.Strings = (
      
        'select * from edi_pagseguro_pagamento where edi_pagseguro_pagame' +
        'nto.CODIGO is null')
    Left = 160
    Top = 7
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
  object DataSeguroAntecipacao: TDataSource
    DataSet = tbSeguroAntecipacao
    Left = 300
    Top = 16
  end
  object tbSeguroAntecipacao: TFDQuery
    CachedUpdates = True
    Connection = Data1.Conexao
    SQL.Strings = (
      
        'Select * from edi_pagseguro_antecipacao where edi_pagseguro_ante' +
        'cipacao.CODIGO is null')
    Left = 300
    Top = 3
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
  end
end
