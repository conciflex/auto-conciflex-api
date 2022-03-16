object DataResumo: TDataResumo
  OldCreateOrder = False
  Height = 261
  Width = 568
  object DataClientesOperadoras: TDataSource
    DataSet = tbClientesOperadoras
    Left = 56
    Top = 20
  end
  object tbClientesOperadoras: TFDQuery
    CachedUpdates = True
    Connection = Data1.Conexao
    SQL.Strings = (
      
        'Select * from cliente_operadora where cliente_operadora.CODIGO_E' +
        'STABELECIMENTO is null')
    Left = 56
    Top = 8
    object tbClientesOperadorasCODIGO: TFDAutoIncField
      FieldName = 'CODIGO'
      Origin = 'CODIGO'
      ProviderFlags = [pfInUpdate, pfInWhere, pfInKey]
      IdentityInsert = True
    end
    object tbClientesOperadorasCOD_CLIENTE: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_CLIENTE'
      Origin = 'COD_CLIENTE'
      ProviderFlags = [pfInUpdate]
    end
    object tbClientesOperadorasCOD_ADQUIRENTE: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_ADQUIRENTE'
      Origin = 'COD_ADQUIRENTE'
      ProviderFlags = [pfInUpdate]
    end
    object tbClientesOperadorasCODIGO_ESTABELECIMENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_ESTABELECIMENTO'
      Origin = 'CODIGO_ESTABELECIMENTO'
      ProviderFlags = [pfInUpdate]
      Size = 50
    end
    object tbClientesOperadorasCNPJ_ESTABELECIMENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CNPJ_ESTABELECIMENTO'
      Origin = 'CNPJ_ESTABELECIMENTO'
      ProviderFlags = [pfInUpdate]
      Size = 45
    end
    object tbClientesOperadorasCOD_GRUPO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_GRUPO'
      Origin = 'COD_GRUPO'
      ProviderFlags = [pfInUpdate]
    end
  end
  object DataVendasOperadoras: TDataSource
    DataSet = tbVendasOperadoras
    Left = 192
    Top = 19
  end
  object tbVendasOperadoras: TFDQuery
    CachedUpdates = True
    Connection = Data1.Conexao
    SQL.Strings = (
      'Select * from vendas where vendas.CODIGO is null')
    Left = 192
    Top = 7
    object tbVendasOperadorasCODIGO: TFDAutoIncField
      FieldName = 'CODIGO'
      Origin = 'CODIGO'
      ProviderFlags = [pfInWhere, pfInKey]
      ReadOnly = True
    end
    object tbVendasOperadorasREFOID: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'REFOID'
      Origin = 'REFOID'
    end
    object tbVendasOperadorasEMPRESA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'EMPRESA'
      Origin = 'EMPRESA'
      Size = 160
    end
    object tbVendasOperadorasESTABELECIMENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'ESTABELECIMENTO'
      Origin = 'ESTABELECIMENTO'
      Size = 160
    end
    object tbVendasOperadorasCNPJ: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CNPJ'
      Origin = 'CNPJ'
      Size = 45
    end
    object tbVendasOperadorasADQID: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'ADQID'
      Origin = 'ADQID'
    end
    object tbVendasOperadorasADQUIRENTE: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'ADQUIRENTE'
      Origin = 'ADQUIRENTE'
      Size = 90
    end
    object tbVendasOperadorasCODIGO_PRODUTO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_PRODUTO'
      Origin = 'CODIGO_PRODUTO'
    end
    object tbVendasOperadorasPRODUTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'PRODUTO'
      Origin = 'PRODUTO'
      Size = 140
    end
    object tbVendasOperadorasCODIGO_MODALIDADE: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_MODALIDADE'
      Origin = 'CODIGO_MODALIDADE'
    end
    object tbVendasOperadorasDESCRICAO_MODALIDADE: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'DESCRICAO_MODALIDADE'
      Origin = 'DESCRICAO_MODALIDADE'
      Size = 160
    end
    object tbVendasOperadorasDATA_VENDA: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_VENDA'
      Origin = 'DATA_VENDA'
    end
    object tbVendasOperadorasDATA_PREVISTA_PAGTO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_PREVISTA_PAGTO'
      Origin = 'DATA_PREVISTA_PAGTO'
    end
    object tbVendasOperadorasRESUMO_VENDA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'RESUMO_VENDA'
      Origin = 'RESUMO_VENDA'
      Size = 160
    end
    object tbVendasOperadorasAUTORIZACAO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'AUTORIZACAO'
      Origin = 'AUTORIZACAO'
      Size = 120
    end
    object tbVendasOperadorasNSU: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NSU'
      Origin = 'NSU'
      Size = 90
    end
    object tbVendasOperadorasTID: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'TID'
      Origin = 'TID'
      Size = 60
    end
    object tbVendasOperadorasCARTAO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CARTAO'
      Origin = 'CARTAO'
      Size = 90
    end
    object tbVendasOperadorasVALOR_BRUTO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_BRUTO'
      Origin = 'VALOR_BRUTO'
    end
    object tbVendasOperadorasPERCENTUAL_TAXA: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'PERCENTUAL_TAXA'
      Origin = 'PERCENTUAL_TAXA'
    end
    object tbVendasOperadorasVALOR_TAXA: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_TAXA'
      Origin = 'VALOR_TAXA'
    end
    object tbVendasOperadorasOUTRAS_DESPESAS: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'OUTRAS_DESPESAS'
      Origin = 'OUTRAS_DESPESAS'
    end
    object tbVendasOperadorasVALOR_LIQUIDO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_LIQUIDO'
      Origin = 'VALOR_LIQUIDO'
    end
    object tbVendasOperadorasTERMINAL: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'TERMINAL'
      Origin = 'TERMINAL'
      Size = 50
    end
    object tbVendasOperadorasBANCO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'BANCO'
      Origin = 'BANCO'
    end
    object tbVendasOperadorasAGENCIA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'AGENCIA'
      Origin = 'AGENCIA'
      Size = 25
    end
    object tbVendasOperadorasCONTA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CONTA'
      Origin = 'CONTA'
      Size = 25
    end
    object tbVendasOperadorasHORA_TRANSACAO: TTimeField
      AutoGenerateValue = arDefault
      FieldName = 'HORA_TRANSACAO'
      Origin = 'HORA_TRANSACAO'
    end
    object tbVendasOperadorasPARCELA: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'PARCELA'
      Origin = 'PARCELA'
    end
    object tbVendasOperadorasTOTAL_PARCELAS: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'TOTAL_PARCELAS'
      Origin = 'TOTAL_PARCELAS'
    end
    object tbVendasOperadorasOBSERVACOES: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'OBSERVACOES'
      Origin = 'OBSERVACOES'
      Size = 160
    end
    object tbVendasOperadorasSTATUS: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'STATUS'
      Origin = '`STATUS`'
    end
    object tbVendasOperadorasREJEITADO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'REJEITADO'
      Origin = 'REJEITADO'
      Size = 10
    end
    object tbVendasOperadorasCANCELADO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CANCELADO'
      Origin = 'CANCELADO'
      Size = 10
    end
    object tbVendasOperadorasDATA_PAGAMENTO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_PAGAMENTO'
      Origin = 'DATA_PAGAMENTO'
    end
    object tbVendasOperadorasVALOR_PAGO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_PAGO'
      Origin = 'VALOR_PAGO'
    end
    object tbVendasOperadorasID_PAGAMENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'ID_PAGAMENTO'
      Origin = 'ID_PAGAMENTO'
      Size = 50
    end
    object tbVendasOperadorasPEDIDO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'PEDIDO'
      Origin = 'PEDIDO'
      Size = 90
    end
    object tbVendasOperadorasID: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'ID'
      Origin = 'ID'
    end
    object tbVendasOperadorasCOD_STATUS_CONCILIACAO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_STATUS_CONCILIACAO'
      Origin = 'COD_STATUS_CONCILIACAO'
    end
    object tbVendasOperadorasCOD_BANDEIRA: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_BANDEIRA'
      Origin = 'COD_BANDEIRA'
    end
    object tbVendasOperadorasBANDEIRA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'BANDEIRA'
      Origin = 'BANDEIRA'
      Size = 45
    end
    object tbVendasOperadorasCOD_CLIENTE: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_CLIENTE'
      Origin = 'COD_CLIENTE'
    end
    object tbVendasOperadorasCOD_STATUS_FINANCEIRO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_STATUS_FINANCEIRO'
      Origin = 'COD_STATUS_FINANCEIRO'
    end
    object tbVendasOperadorasCOD_PRODUTO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_PRODUTO'
      Origin = 'COD_PRODUTO'
    end
    object tbVendasOperadorasCOD_GRUPO_CLIENTE: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_GRUPO_CLIENTE'
      Origin = 'COD_GRUPO_CLIENTE'
    end
    object tbVendasOperadorasVALOR_DIFERENCA: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_DIFERENCA'
      Origin = 'VALOR_DIFERENCA'
    end
    object tbVendasOperadorasCOD_MEIO_CAPTURA: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_MEIO_CAPTURA'
      Origin = 'COD_MEIO_CAPTURA'
    end
    object tbVendasOperadorasVINCULADO_PAGAMENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'VINCULADO_PAGAMENTO'
      Origin = 'VINCULADO_PAGAMENTO'
      Size = 1
    end
    object tbVendasOperadorasCOD_PAGAMENTO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_PAGAMENTO'
      Origin = 'COD_PAGAMENTO'
    end
    object tbVendasOperadorasCOD_TIPO_PAGAMENTO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_TIPO_PAGAMENTO'
      Origin = 'COD_TIPO_PAGAMENTO'
    end
    object tbVendasOperadorasJUSTIFICATIVA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'JUSTIFICATIVA'
      Origin = 'JUSTIFICATIVA'
      Size = 160
    end
    object tbVendasOperadorasCOD_VENDA_ERP: TLargeintField
      AutoGenerateValue = arDefault
      FieldName = 'COD_VENDA_ERP'
      Origin = 'COD_VENDA_ERP'
    end
    object tbVendasOperadorasPRODUTO_ERP: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'PRODUTO_ERP'
      Origin = 'PRODUTO_ERP'
      Size = 160
    end
    object tbVendasOperadorasID_VENDAS_ERP: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'ID_VENDAS_ERP'
      Origin = 'ID_VENDAS_ERP'
      Size = 160
    end
    object tbVendasOperadorasTAXA_MINIMA: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'TAXA_MINIMA'
      Origin = 'TAXA_MINIMA'
    end
    object tbVendasOperadorasDIVERGENCIA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'DIVERGENCIA'
      Origin = 'DIVERGENCIA'
      Size = 200
    end
    object tbVendasOperadorasVARIAVEL: TBCDField
      AutoGenerateValue = arDefault
      FieldName = 'VARIAVEL'
      Origin = 'VARIAVEL'
      Precision = 10
      Size = 2
    end
    object tbVendasOperadorasPAGAMENTO_GERADO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'PAGAMENTO_GERADO'
      Origin = 'PAGAMENTO_GERADO'
      Size = 1
    end
    object tbVendasOperadorasNOME_ARQUIVO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NOME_ARQUIVO'
      Origin = 'NOME_ARQUIVO'
      Size = 255
    end
    object tbVendasOperadorasID_VENDA_PAGAMENTO_TRATADO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'ID_VENDA_PAGAMENTO_TRATADO'
      Origin = 'ID_VENDA_PAGAMENTO_TRATADO'
      Size = 1
    end
    object tbVendasOperadorasTID_ADICIONAL: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'TID_ADICIONAL'
      Origin = 'TID_ADICIONAL'
      Size = 60
    end
    object tbVendasOperadorasBIN_CARTAO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'BIN_CARTAO'
      Origin = 'BIN_CARTAO'
      Size = 30
    end
    object tbVendasOperadorasCOD_REGRA_CONCILIACAO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_REGRA_CONCILIACAO'
      Origin = 'COD_REGRA_CONCILIACAO'
    end
    object tbVendasOperadorasVERIFICADO_DUPLICIDADE: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'VERIFICADO_DUPLICIDADE'
      Origin = 'VERIFICADO_DUPLICIDADE'
      Size = 1
    end
    object tbVendasOperadorasNUMERO_RESUMO_VENDA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NUMERO_RESUMO_VENDA'
      Origin = 'NUMERO_RESUMO_VENDA'
      Size = 30
    end
    object tbVendasOperadorasCHAVE_VENDA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CHAVE_VENDA'
      Origin = 'CHAVE_VENDA'
      Size = 60
    end
    object tbVendasOperadorasCHAVE_VENDA_ERP: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CHAVE_VENDA_ERP'
      Origin = 'CHAVE_VENDA_ERP'
      Size = 60
    end
    object tbVendasOperadorasCHAVE_PAGAMENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CHAVE_PAGAMENTO'
      Origin = 'CHAVE_PAGAMENTO'
      Size = 60
    end
    object tbVendasOperadorasDATA_CANCELAMENTO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_CANCELAMENTO'
      Origin = 'DATA_CANCELAMENTO'
    end
    object tbVendasOperadorasAUTORIZADOR: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'AUTORIZADOR'
      Origin = 'AUTORIZADOR'
      Size = 60
    end
    object tbVendasOperadorasPERC_TAXA_CALC: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'PERC_TAXA_CALC'
      Origin = 'PERC_TAXA_CALC'
      Size = 1
    end
    object tbVendasOperadorasCAMPO_ADICIONAL1: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CAMPO_ADICIONAL1'
      Origin = 'CAMPO_ADICIONAL1'
      Size = 90
    end
    object tbVendasOperadorasCAMPO_ADICIONAL2: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CAMPO_ADICIONAL2'
      Origin = 'CAMPO_ADICIONAL2'
      Size = 90
    end
    object tbVendasOperadorasCAMPO_ADICIONAL3: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CAMPO_ADICIONAL3'
      Origin = 'CAMPO_ADICIONAL3'
      Size = 90
    end
    object tbVendasOperadorasVALOR_BRUTO_ERP: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_BRUTO_ERP'
      Origin = 'VALOR_BRUTO_ERP'
    end
    object tbVendasOperadorasPERCENTUAL_TAXA_CALC: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'PERCENTUAL_TAXA_CALC'
      Origin = 'PERCENTUAL_TAXA_CALC'
    end
    object tbVendasOperadorasDATA_PROCESSAMENTO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_PROCESSAMENTO'
      Origin = 'DATA_PROCESSAMENTO'
    end
    object tbVendasOperadorasHORA_PROCESSAMENTO: TTimeField
      AutoGenerateValue = arDefault
      FieldName = 'HORA_PROCESSAMENTO'
      Origin = 'HORA_PROCESSAMENTO'
    end
  end
  object DataPagamentosOperadoras: TDataSource
    DataSet = tbPagamentosOperadoras
    Left = 336
    Top = 17
  end
  object tbPagamentosOperadoras: TFDQuery
    CachedUpdates = True
    Connection = Data1.Conexao
    SQL.Strings = (
      
        'Select * from pagamentos_operadoras where pagamentos_operadoras.' +
        'CODIGO is null')
    Left = 336
    Top = 5
    object tbPagamentosOperadorasCODIGO: TFDAutoIncField
      FieldName = 'CODIGO'
      Origin = 'CODIGO'
      ProviderFlags = [pfInUpdate, pfInWhere, pfInKey]
      IdentityInsert = True
    end
    object tbPagamentosOperadorasDATA_PROCESSAMENTO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_PROCESSAMENTO'
      Origin = 'DATA_PROCESSAMENTO'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasHORA_PROCESSAMENTO: TTimeField
      AutoGenerateValue = arDefault
      FieldName = 'HORA_PROCESSAMENTO'
      Origin = 'HORA_PROCESSAMENTO'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasID_LOJA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'ID_LOJA'
      Origin = 'ID_LOJA'
      ProviderFlags = [pfInUpdate]
      Size = 25
    end
    object tbPagamentosOperadorasVALOR_BRUTO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_BRUTO'
      Origin = 'VALOR_BRUTO'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasVALOR_DESCONTO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_DESCONTO'
      Origin = 'VALOR_DESCONTO'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasVALOR_LIQUIDO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_LIQUIDO'
      Origin = 'VALOR_LIQUIDO'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasNUMERO_CARTAO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NUMERO_CARTAO'
      Origin = 'NUMERO_CARTAO'
      ProviderFlags = [pfInUpdate]
      Size = 50
    end
    object tbPagamentosOperadorasBANCO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'BANCO'
      Origin = 'BANCO'
      ProviderFlags = [pfInUpdate]
      Size = 10
    end
    object tbPagamentosOperadorasCOD_BANCO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_BANCO'
      Origin = 'COD_BANCO'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasAGENCIA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'AGENCIA'
      Origin = 'AGENCIA'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasCONTA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CONTA'
      Origin = 'CONTA'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasCODIGO_AUTORIZACAO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_AUTORIZACAO'
      Origin = 'CODIGO_AUTORIZACAO'
      ProviderFlags = [pfInUpdate]
      Size = 50
    end
    object tbPagamentosOperadorasNSU: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NSU'
      Origin = 'NSU'
      ProviderFlags = [pfInUpdate]
      Size = 50
    end
    object tbPagamentosOperadorasCOD_CLIENTE: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_CLIENTE'
      Origin = 'COD_CLIENTE'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasCOD_STATUS: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_STATUS'
      Origin = 'COD_STATUS'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasCOD_ADQUIRENTE: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_ADQUIRENTE'
      Origin = 'COD_ADQUIRENTE'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasTAXA_PERCENTUAL: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'TAXA_PERCENTUAL'
      Origin = 'TAXA_PERCENTUAL'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasVALOR_TAXA: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_TAXA'
      Origin = 'VALOR_TAXA'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasCOD_BANDEIRA: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_BANDEIRA'
      Origin = 'COD_BANDEIRA'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasCOD_TIPO_PAGAMENTO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_TIPO_PAGAMENTO'
      Origin = 'COD_TIPO_PAGAMENTO'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasENCONTRADA_VENDA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'ENCONTRADA_VENDA'
      Origin = 'ENCONTRADA_VENDA'
      ProviderFlags = [pfInUpdate]
      Size = 1
    end
    object tbPagamentosOperadorasCOD_GRUPO_CLIENTE: TSingleField
      FieldName = 'COD_GRUPO_CLIENTE'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasCNPJ: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CNPJ'
      Origin = 'CNPJ'
      ProviderFlags = [pfInUpdate]
      Size = 45
    end
    object tbPagamentosOperadorasEMPRESA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'EMPRESA'
      Origin = 'EMPRESA'
      ProviderFlags = [pfInUpdate]
      Size = 90
    end
    object tbPagamentosOperadorasDATA_VENDA: TDateField
      FieldName = 'DATA_VENDA'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasHORA_VENDA: TTimeField
      FieldName = 'HORA_VENDA'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasDATA_PAGAMENTO: TDateField
      FieldName = 'DATA_PAGAMENTO'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasOUTROS_CREDITOS: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'OUTROS_CREDITOS'
      Origin = 'OUTROS_CREDITOS'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasCOD_MEIO_CAPTURA: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_MEIO_CAPTURA'
      Origin = 'COD_MEIO_CAPTURA'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasPARCELA: TIntegerField
      FieldName = 'PARCELA'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasTOTAL_PARCELAS: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'TOTAL_PARCELAS'
      Origin = 'TOTAL_PARCELAS'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasCOD_STATUS_FINANCEIRO: TSingleField
      FieldName = 'COD_STATUS_FINANCEIRO'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasVINCULADO_VENDA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'VINCULADO_VENDA'
      Origin = 'VINCULADO_VENDA'
      ProviderFlags = [pfInUpdate]
      Size = 1
    end
    object tbPagamentosOperadorasCOD_VENDA: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_VENDA'
      Origin = 'COD_VENDA'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasCOD_FORMA_PAGAMENTO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_FORMA_PAGAMENTO'
      Origin = 'COD_FORMA_PAGAMENTO'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasTAXA_MANUAL: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'TAXA_MANUAL'
      Origin = 'TAXA_MANUAL'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasRESUMO_DESCONTO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'RESUMO_DESCONTO'
      Origin = 'RESUMO_DESCONTO'
      ProviderFlags = [pfInUpdate]
      currency = True
    end
    object tbPagamentosOperadorasRESUMO_LIQUIDO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'RESUMO_LIQUIDO'
      Origin = 'RESUMO_LIQUIDO'
      ProviderFlags = [pfInUpdate]
      currency = True
    end
    object tbPagamentosOperadorasDIFERENCA_DESCONTO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'DIFERENCA_DESCONTO'
      Origin = 'DIFERENCA_DESCONTO'
      ProviderFlags = [pfInUpdate]
      currency = True
    end
    object tbPagamentosOperadorasDIFERENCA_LIQUIDO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'DIFERENCA_LIQUIDO'
      Origin = 'DIFERENCA_LIQUIDO'
      ProviderFlags = [pfInUpdate]
      currency = True
    end
    object tbPagamentosOperadorasIDENTIFICADOR_RO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'IDENTIFICADOR_RO'
      Origin = 'IDENTIFICADOR_RO'
      ProviderFlags = [pfInUpdate]
      Size = 90
    end
    object tbPagamentosOperadorasCALCULADO_DESCONTO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'CALCULADO_DESCONTO'
      Origin = 'CALCULADO_DESCONTO'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasCALCULADORA_LIQUIDO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'CALCULADORA_LIQUIDO'
      Origin = 'CALCULADORA_LIQUIDO'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasRO_TRATADO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'RO_TRATADO'
      Origin = 'RO_TRATADO'
      ProviderFlags = [pfInUpdate]
      Size = 1
    end
    object tbPagamentosOperadorasDATA_PREV_PAG_ORIGINAL: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_PREV_PAG_ORIGINAL'
      Origin = 'DATA_PREV_PAG_ORIGINAL'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasID_VENDA_ERP: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'ID_VENDA_ERP'
      Origin = 'ID_VENDA_ERP'
      ProviderFlags = [pfInUpdate]
      Size = 50
    end
    object tbPagamentosOperadorasNOME_ARQUIVO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NOME_ARQUIVO'
      Origin = 'NOME_ARQUIVO'
      ProviderFlags = [pfInUpdate]
      Size = 255
    end
    object tbPagamentosOperadorasCOD_PRODUTO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_PRODUTO'
      Origin = 'COD_PRODUTO'
      ProviderFlags = [pfInUpdate]
    end
    object tbPagamentosOperadorasTID: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'TID'
      Origin = 'TID'
      ProviderFlags = [pfInUpdate]
      Size = 90
    end
    object tbPagamentosOperadorasOBSERVACOES: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'OBSERVACOES'
      Origin = 'OBSERVACOES'
      ProviderFlags = [pfInUpdate]
      Size = 160
    end
    object tbPagamentosOperadorasDUPLICIDADE_VERIFICADA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'DUPLICIDADE_VERIFICADA'
      Origin = 'DUPLICIDADE_VERIFICADA'
      ProviderFlags = [pfInUpdate]
      Size = 1
    end
    object tbPagamentosOperadorasNUMERO_RESUMO_VENDA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NUMERO_RESUMO_VENDA'
      Origin = 'NUMERO_RESUMO_VENDA'
      ProviderFlags = [pfInUpdate]
      Size = 30
    end
    object tbPagamentosOperadorasCHAVE_VENDA_OPERADORA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CHAVE_VENDA_OPERADORA'
      Origin = 'CHAVE_VENDA_OPERADORA'
      ProviderFlags = [pfInUpdate]
      Size = 60
    end
    object tbPagamentosOperadorasCHAVE_VENDA_ERP: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CHAVE_VENDA_ERP'
      Origin = 'CHAVE_VENDA_ERP'
      ProviderFlags = [pfInUpdate]
      Size = 60
    end
    object tbPagamentosOperadorasCHAVE_PAGAMENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CHAVE_PAGAMENTO'
      Origin = 'CHAVE_PAGAMENTO'
      ProviderFlags = [pfInUpdate]
      Size = 60
    end
    object tbPagamentosOperadorasNUMERO_TERMINAL: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NUMERO_TERMINAL'
      Origin = 'NUMERO_TERMINAL'
      Size = 50
    end
    object tbPagamentosOperadorasCOD_TIPO_LANCAMENTO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_TIPO_LANCAMENTO'
      Origin = 'COD_TIPO_LANCAMENTO'
    end
    object tbPagamentosOperadorasCOD_AJUSTE: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_AJUSTE'
      Origin = 'COD_AJUSTE'
    end
    object tbPagamentosOperadorasTAXA_ANTECIPACAO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'TAXA_ANTECIPACAO'
      Origin = 'TAXA_ANTECIPACAO'
    end
    object tbPagamentosOperadorasVALOR_TAXA_ANTECIPACAO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'VALOR_TAXA_ANTECIPACAO'
      Origin = 'VALOR_TAXA_ANTECIPACAO'
    end
    object tbPagamentosOperadorasNUMERO_OPERACAO_ANTECIPACAO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NUMERO_OPERACAO_ANTECIPACAO'
      Origin = 'NUMERO_OPERACAO_ANTECIPACAO'
      Size = 60
    end
    object tbPagamentosOperadorasDATA_CANCELAMENTO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_CANCELAMENTO'
      Origin = 'DATA_CANCELAMENTO'
    end
    object tbPagamentosOperadorasAUTORIZADOR: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'AUTORIZADOR'
      Origin = 'AUTORIZADOR'
      Size = 50
    end
    object tbPagamentosOperadorasPERCENTUAL_TAXA_CALC: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'PERCENTUAL_TAXA_CALC'
      Origin = 'PERCENTUAL_TAXA_CALC'
      Size = 1
    end
  end
end
