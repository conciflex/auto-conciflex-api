object Data2: TData2
  OldCreateOrder = False
  Height = 410
  Width = 675
  object DataHeaderStone: TDataSource
    DataSet = tbHeaderStone
    Left = 35
    Top = 15
  end
  object tbHeaderStone: TFDQuery
    CachedUpdates = True
    Connection = Data1.Conexao
    SQL.Strings = (
      
        'select * from edi_stone_header where edi_stone_header.CODIGO is ' +
        'null')
    Left = 35
    Top = 2
    object tbHeaderStoneCODIGO: TFDAutoIncField
      FieldName = 'CODIGO'
      Origin = 'CODIGO'
      ProviderFlags = [pfInWhere, pfInKey]
      ReadOnly = True
    end
    object tbHeaderStoneSTONECODE: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'STONECODE'
      Origin = 'STONECODE'
    end
    object tbHeaderStoneLAYOUT_VERSION: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'LAYOUT_VERSION'
      Origin = 'LAYOUT_VERSION'
      Size = 5
    end
    object tbHeaderStoneCOD_CREDENCIAMENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'COD_CREDENCIAMENTO'
      Origin = 'COD_CREDENCIAMENTO'
      Size = 255
    end
    object tbHeaderStoneDATA_GERACAO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_GERACAO'
      Origin = 'DATA_GERACAO'
    end
    object tbHeaderStoneDATA_REFERENCIA: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_REFERENCIA'
      Origin = 'DATA_REFERENCIA'
    end
  end
  object DataEventoStone: TDataSource
    DataSet = tbEventoStone
    Left = 147
    Top = 14
  end
  object tbEventoStone: TFDQuery
    CachedUpdates = True
    Connection = Data1.Conexao
    SQL.Strings = (
      
        'select * from edi_stone_evento_financeiro where edi_stone_evento' +
        '_financeiro.CODIGO is null')
    Left = 147
    Top = 1
    object tbEventoStoneCODIGO: TFDAutoIncField
      FieldName = 'CODIGO'
      Origin = 'CODIGO'
      ProviderFlags = [pfInWhere, pfInKey]
      ReadOnly = True
    end
    object tbEventoStoneCODIGO_EVENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_EVENTO'
      Origin = 'CODIGO_EVENTO'
      Size = 36
    end
    object tbEventoStoneDESCRICAO_EVENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'DESCRICAO_EVENTO'
      Origin = 'DESCRICAO_EVENTO'
      Size = 60
    end
    object tbEventoStoneTIPO_EVENTO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'TIPO_EVENTO'
      Origin = 'TIPO_EVENTO'
    end
    object tbEventoStonePREVISAO_COBRANCA: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'PREVISAO_COBRANCA'
      Origin = 'PREVISAO_COBRANCA'
    end
    object tbEventoStoneVALOR_EVENTO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_EVENTO'
      Origin = 'VALOR_EVENTO'
    end
    object tbEventoStoneCODE_TRANSFERENCIA_INTERNA: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'CODE_TRANSFERENCIA_INTERNA'
      Origin = 'CODE_TRANSFERENCIA_INTERNA'
    end
    object tbEventoStoneDATA_COBRANCA: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_COBRANCA'
      Origin = 'DATA_COBRANCA'
    end
    object tbEventoStoneCOD_HEADER: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'COD_HEADER'
      Origin = 'COD_HEADER'
    end
    object tbEventoStoneTRATADO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'TRATADO'
      Origin = 'TRATADO'
      Size = 1
    end
    object tbEventoStoneSTONECODE: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'STONECODE'
      Origin = 'STONECODE'
      Size = 50
    end
    object tbEventoStoneARRANJO_PAGAMENTO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'ARRANJO_PAGAMENTO'
      Origin = 'ARRANJO_PAGAMENTO'
    end
    object tbEventoStoneBANCO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'BANCO'
      Origin = 'BANCO'
    end
    object tbEventoStoneAGENCIA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'AGENCIA'
      Origin = 'AGENCIA'
      Size = 10
    end
    object tbEventoStoneNUM_CONTA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NUM_CONTA'
      Origin = 'NUM_CONTA'
      Size = 12
    end
    object tbEventoStoneID_PAGAMENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'ID_PAGAMENTO'
      Origin = 'ID_PAGAMENTO'
      Size = 30
    end
  end
  object DataCredenciadosStone: TDataSource
    DataSet = tbCredenciadosStone
    Left = 264
    Top = 15
  end
  object tbCredenciadosStone: TFDQuery
    CachedUpdates = True
    Connection = Data1.Conexao
    SQL.Strings = (
      
        'select * from credenciamento_stone where credenciamento_stone.CO' +
        'DIGO is null')
    Left = 264
    Top = 2
    object tbCredenciadosStoneCODIGO: TFDAutoIncField
      FieldName = 'CODIGO'
      Origin = 'CODIGO'
      ProviderFlags = [pfInWhere, pfInKey]
      ReadOnly = True
    end
    object tbCredenciadosStoneDATA_CREDENCIAMENTO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_CREDENCIAMENTO'
      Origin = 'DATA_CREDENCIAMENTO'
    end
    object tbCredenciadosStoneSTONECODE: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'STONECODE'
      Origin = 'STONECODE'
      Size = 15
    end
    object tbCredenciadosStoneCNPJ_ESTABELECIMENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CNPJ_ESTABELECIMENTO'
      Origin = 'CNPJ_ESTABELECIMENTO'
    end
    object tbCredenciadosStoneLIBERADO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'LIBERADO'
      Origin = 'LIBERADO'
      Size = 1
    end
  end
  object DataVendaStone: TDataSource
    DataSet = tbVendaStone
    Left = 163
    Top = 86
  end
  object tbVendaStone: TFDQuery
    CachedUpdates = True
    Connection = Data1.Conexao
    SQL.Strings = (
      
        'select * from edi_stone_comprovante_venda where edi_stone_compro' +
        'vante_venda.CODIGO is null')
    Left = 163
    Top = 73
    object tbVendaStoneCODIGO: TFDAutoIncField
      FieldName = 'CODIGO'
      Origin = 'CODIGO'
      ProviderFlags = [pfInWhere, pfInKey]
      ReadOnly = True
    end
    object tbVendaStoneNSU: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NSU'
      Origin = 'NSU'
      Size = 35
    end
    object tbVendaStoneCODIGO_TRANSACAO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_TRANSACAO'
      Origin = 'CODIGO_TRANSACAO'
      Size = 255
    end
    object tbVendaStoneDATA_AUTORIZACAO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_AUTORIZACAO'
      Origin = 'DATA_AUTORIZACAO'
    end
    object tbVendaStoneHORA_AUTORIZACAO: TTimeField
      AutoGenerateValue = arDefault
      FieldName = 'HORA_AUTORIZACAO'
      Origin = 'HORA_AUTORIZACAO'
    end
    object tbVendaStoneDATA_CAPTURA: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_CAPTURA'
      Origin = 'DATA_CAPTURA'
    end
    object tbVendaStoneHORA_CAPTURA: TTimeField
      AutoGenerateValue = arDefault
      FieldName = 'HORA_CAPTURA'
      Origin = 'HORA_CAPTURA'
    end
    object tbVendaStoneINTERNACIONAL: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'INTERNACIONAL'
      Origin = 'INTERNACIONAL'
      Size = 5
    end
    object tbVendaStoneCOD_TIPO_CONTA: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'COD_TIPO_CONTA'
      Origin = 'COD_TIPO_CONTA'
    end
    object tbVendaStoneCOD_TIPO_PAGAMENTO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'COD_TIPO_PAGAMENTO'
      Origin = 'COD_TIPO_PAGAMENTO'
    end
    object tbVendaStoneTOTAL_PARCELAS: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'TOTAL_PARCELAS'
      Origin = 'TOTAL_PARCELAS'
    end
    object tbVendaStoneVALOR_AUTORIZADO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_AUTORIZADO'
      Origin = 'VALOR_AUTORIZADO'
    end
    object tbVendaStoneVALOR_CAPTURADO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_CAPTURADO'
      Origin = 'VALOR_CAPTURADO'
    end
    object tbVendaStoneTOTAL_CANCELADO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'TOTAL_CANCELADO'
      Origin = 'TOTAL_CANCELADO'
    end
    object tbVendaStoneCODIGO_AUTORIZACAO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_AUTORIZACAO'
      Origin = 'CODIGO_AUTORIZACAO'
      Size = 6
    end
    object tbVendaStoneCOD_BANDEIRA: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'COD_BANDEIRA'
      Origin = 'COD_BANDEIRA'
    end
    object tbVendaStoneNUM_CARTAO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NUM_CARTAO'
      Origin = 'NUM_CARTAO'
      Size = 19
    end
    object tbVendaStoneCOD_TIPO_TERMINAL: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'COD_TIPO_TERMINAL'
      Origin = 'COD_TIPO_TERMINAL'
    end
    object tbVendaStoneNUM_TERMINAL: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NUM_TERMINAL'
      Origin = 'NUM_TERMINAL'
      Size = 32
    end
    object tbVendaStoneNUM_PARCELA: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'NUM_PARCELA'
      Origin = 'NUM_PARCELA'
    end
    object tbVendaStoneVALOR_BRUTO_PARCELA: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_BRUTO_PARCELA'
      Origin = 'VALOR_BRUTO_PARCELA'
    end
    object tbVendaStoneVALOR_LIQUIDO_PARCELA: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_LIQUIDO_PARCELA'
      Origin = 'VALOR_LIQUIDO_PARCELA'
    end
    object tbVendaStonePREVISAO_PAGAMENTO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'PREVISAO_PAGAMENTO'
      Origin = 'PREVISAO_PAGAMENTO'
    end
    object tbVendaStoneCOD_HEADER: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'COD_HEADER'
      Origin = 'COD_HEADER'
    end
    object tbVendaStoneTRATADO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'TRATADO'
      Origin = 'TRATADO'
      Size = 1
    end
    object tbVendaStoneSTONECODE: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'STONECODE'
      Origin = 'STONECODE'
      Size = 50
    end
  end
  object DataPagamentoStone: TDataSource
    DataSet = tbPagamentoStone
    Left = 43
    Top = 86
  end
  object tbPagamentoStone: TFDQuery
    CachedUpdates = True
    Connection = Data1.Conexao
    SQL.Strings = (
      
        'select * from edi_stone_comprovante_pagamento where edi_stone_co' +
        'mprovante_pagamento.CODIGO is null')
    Left = 43
    Top = 73
    object tbPagamentoStoneCODIGO: TFDAutoIncField
      FieldName = 'CODIGO'
      Origin = 'CODIGO'
      ProviderFlags = [pfInWhere, pfInKey]
      ReadOnly = True
    end
    object tbPagamentoStoneCOD_HEADER: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'COD_HEADER'
      Origin = 'COD_HEADER'
    end
    object tbPagamentoStoneNSU: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NSU'
      Origin = 'NSU'
      Size = 35
    end
    object tbPagamentoStoneNUM_PARCELA: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'NUM_PARCELA'
      Origin = 'NUM_PARCELA'
    end
    object tbPagamentoStoneVALOR_BRUTO_PARCELA: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_BRUTO_PARCELA'
      Origin = 'VALOR_BRUTO_PARCELA'
    end
    object tbPagamentoStoneVALOR_LIQUIDO_PARCELA: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_LIQUIDO_PARCELA'
      Origin = 'VALOR_LIQUIDO_PARCELA'
    end
    object tbPagamentoStonePAGAMENTO_PARCELA: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'PAGAMENTO_PARCELA'
      Origin = 'PAGAMENTO_PARCELA'
    end
    object tbPagamentoStoneDESCONTO_ANTECIPACAO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'DESCONTO_ANTECIPACAO'
      Origin = 'DESCONTO_ANTECIPACAO'
    end
    object tbPagamentoStonePAGAMENTO_REAL_ANTECIPADO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'PAGAMENTO_REAL_ANTECIPADO'
      Origin = 'PAGAMENTO_REAL_ANTECIPADO'
    end
    object tbPagamentoStoneARRANJO_PAGAMENTO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'ARRANJO_PAGAMENTO'
      Origin = 'ARRANJO_PAGAMENTO'
    end
    object tbPagamentoStoneVALOR_PAGO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_PAGO'
      Origin = 'VALOR_PAGO'
    end
    object tbPagamentoStoneVALOR_PENDENTE_LOJISTA: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_PENDENTE_LOJISTA'
      Origin = 'VALOR_PENDENTE_LOJISTA'
    end
    object tbPagamentoStoneBANCO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'BANCO'
      Origin = 'BANCO'
    end
    object tbPagamentoStoneAGENCIA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'AGENCIA'
      Origin = 'AGENCIA'
      Size = 10
    end
    object tbPagamentoStoneNUM_CONTA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NUM_CONTA'
      Origin = 'NUM_CONTA'
      Size = 12
    end
    object tbPagamentoStoneTRATADO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'TRATADO'
      Origin = 'TRATADO'
      Size = 1
    end
    object tbPagamentoStoneSTONECODE: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'STONECODE'
      Origin = 'STONECODE'
      Size = 50
    end
    object tbPagamentoStoneCODIGO_TRANSACAO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_TRANSACAO'
      Origin = 'CODIGO_TRANSACAO'
      Size = 255
    end
    object tbPagamentoStoneDATA_AUTORIZACAO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_AUTORIZACAO'
      Origin = 'DATA_AUTORIZACAO'
    end
    object tbPagamentoStoneHORA_AUTORIZACAO: TTimeField
      AutoGenerateValue = arDefault
      FieldName = 'HORA_AUTORIZACAO'
      Origin = 'HORA_AUTORIZACAO'
    end
    object tbPagamentoStoneID_PAGAMENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'ID_PAGAMENTO'
      Origin = 'ID_PAGAMENTO'
      Size = 30
    end
  end
  object DataCancelamentoStone: TDataSource
    DataSet = tbCancelamentoStone
    Left = 411
    Top = 14
  end
  object tbCancelamentoStone: TFDQuery
    CachedUpdates = True
    Connection = Data1.Conexao
    SQL.Strings = (
      
        'select * from edi_stone_cancelamento where edi_stone_cancelament' +
        'o.CODIGO is null')
    Left = 411
    Top = 1
    object tbCancelamentoStoneCODIGO: TFDAutoIncField
      FieldName = 'CODIGO'
      Origin = 'CODIGO'
      ProviderFlags = [pfInWhere, pfInKey]
      ReadOnly = True
    end
    object tbCancelamentoStoneCODIGO_CANCELAMENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_CANCELAMENTO'
      Origin = 'CODIGO_CANCELAMENTO'
      Size = 32
    end
    object tbCancelamentoStoneNUM_PARCELA: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'NUM_PARCELA'
      Origin = 'NUM_PARCELA'
    end
    object tbCancelamentoStoneDATA_CANCELAMENTO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_CANCELAMENTO'
      Origin = 'DATA_CANCELAMENTO'
    end
    object tbCancelamentoStoneHORA_CANCELAMENTO: TTimeField
      AutoGenerateValue = arDefault
      FieldName = 'HORA_CANCELAMENTO'
      Origin = 'HORA_CANCELAMENTO'
    end
    object tbCancelamentoStoneVALOR_ESTORNADO_CLIENTE: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_ESTORNADO_CLIENTE'
      Origin = 'VALOR_ESTORNADO_CLIENTE'
    end
    object tbCancelamentoStoneVALOR_DESCONTADO_LOJISTA: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_DESCONTADO_LOJISTA'
      Origin = 'VALOR_DESCONTADO_LOJISTA'
    end
    object tbCancelamentoStoneDATA_COBRANCA: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_COBRANCA'
      Origin = 'DATA_COBRANCA'
    end
    object tbCancelamentoStoneCOD_HEADER: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'COD_HEADER'
      Origin = 'COD_HEADER'
    end
    object tbCancelamentoStoneNSU: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NSU'
      Origin = 'NSU'
      Size = 35
    end
    object tbCancelamentoStoneDATA_AUTORIZACAO_VENDA: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_AUTORIZACAO_VENDA'
      Origin = 'DATA_AUTORIZACAO_VENDA'
    end
    object tbCancelamentoStoneHORA_AUTORIZACAO_VENDA: TTimeField
      AutoGenerateValue = arDefault
      FieldName = 'HORA_AUTORIZACAO_VENDA'
      Origin = 'HORA_AUTORIZACAO_VENDA'
    end
    object tbCancelamentoStoneDATA_CAPTURA_VENDA: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_CAPTURA_VENDA'
      Origin = 'DATA_CAPTURA_VENDA'
    end
    object tbCancelamentoStoneHORA_CAPTURA_VENDA: TTimeField
      AutoGenerateValue = arDefault
      FieldName = 'HORA_CAPTURA_VENDA'
      Origin = 'HORA_CAPTURA_VENDA'
    end
    object tbCancelamentoStoneDATA_PREVISAO_COBRANCA: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_PREVISAO_COBRANCA'
      Origin = 'DATA_PREVISAO_COBRANCA'
    end
    object tbCancelamentoStoneTRATADO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'TRATADO'
      Origin = 'TRATADO'
      Size = 1
    end
    object tbCancelamentoStoneSTONECODE: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'STONECODE'
      Origin = 'STONECODE'
      Size = 50
    end
    object tbCancelamentoStoneTIPO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'TIPO'
      Origin = 'TIPO'
      Size = 1
    end
    object tbCancelamentoStoneID_PAGAMENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'ID_PAGAMENTO'
      Origin = 'ID_PAGAMENTO'
      Size = 30
    end
  end
end
