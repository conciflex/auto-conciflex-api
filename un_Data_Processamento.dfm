object DataProcessamento: TDataProcessamento
  OldCreateOrder = False
  Height = 250
  Width = 603
  object DataClientes: TDataSource
    DataSet = tbClientes
    Left = 36
    Top = 16
  end
  object tbClientes: TFDQuery
    CachedUpdates = True
    Connection = Data1.Conexao
    SQL.Strings = (
      'select * from clientes where clientes.CODIGO is null')
    Left = 36
    Top = 4
    object tbClientesNOME: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NOME'
      Origin = 'NOME'
      Size = 90
    end
    object tbClientesNOME_FANTASIA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NOME_FANTASIA'
      Origin = 'NOME_FANTASIA'
      Size = 90
    end
    object tbClientesCOD_TIPO_PESSOA: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_TIPO_PESSOA'
      Origin = 'COD_TIPO_PESSOA'
    end
    object tbClientesENDERECO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'ENDERECO'
      Origin = 'ENDERECO'
      Size = 60
    end
    object tbClientesCOMPLEMENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'COMPLEMENTO'
      Origin = 'COMPLEMENTO'
      Size = 45
    end
    object tbClientesCOD_BAIRRO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_BAIRRO'
      Origin = 'COD_BAIRRO'
    end
    object tbClientesCOD_CIDADE: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_CIDADE'
      Origin = 'COD_CIDADE'
    end
    object tbClientesCOD_UF: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_UF'
      Origin = 'COD_UF'
    end
    object tbClientesCOD_PAIS: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_PAIS'
      Origin = 'COD_PAIS'
    end
    object tbClientesCEP: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CEP'
      Origin = 'CEP'
      Size = 15
    end
    object tbClientesFONE1: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'FONE1'
      Origin = 'FONE1'
      Size = 15
    end
    object tbClientesFONE2: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'FONE2'
      Origin = 'FONE2'
      Size = 15
    end
    object tbClientesRAMAL1: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'RAMAL1'
      Origin = 'RAMAL1'
      Size = 10
    end
    object tbClientesRAMAL2: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'RAMAL2'
      Origin = 'RAMAL2'
      Size = 10
    end
    object tbClientesTEL0800: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'TEL0800'
      Origin = 'TEL0800'
    end
    object tbClientesCONTATO1: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CONTATO1'
      Origin = 'CONTATO1'
      Size = 60
    end
    object tbClientesCONTATO2: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CONTATO2'
      Origin = 'CONTATO2'
      Size = 60
    end
    object tbClientesCELULAR1: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CELULAR1'
      Origin = 'CELULAR1'
    end
    object tbClientesCELULAR2: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CELULAR2'
      Origin = 'CELULAR2'
    end
    object tbClientesEMAIL: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'EMAIL'
      Origin = 'EMAIL'
      Size = 120
    end
    object tbClientesCPF_CNPJ: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CPF_CNPJ'
      Origin = 'CPF_CNPJ'
    end
    object tbClientesINSC_ESTADUAL: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'INSC_ESTADUAL'
      Origin = 'INSC_ESTADUAL'
    end
    object tbClientesOBS: TMemoField
      AutoGenerateValue = arDefault
      FieldName = 'OBS'
      Origin = 'OBS'
      BlobType = ftMemo
    end
    object tbClientesEMAIL2: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'EMAIL2'
      Origin = 'EMAIL2'
      Size = 120
    end
    object tbClientesNUMERO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NUMERO'
      Origin = 'NUMERO'
      Size = 10
    end
    object tbClientesSALA_LOJA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'SALA_LOJA'
      Origin = 'SALA_LOJA'
    end
    object tbClientesHOME_PAGE: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'HOME_PAGE'
      Origin = 'HOME_PAGE'
      Size = 25
    end
    object tbClientesDDD: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'DDD'
      Origin = 'DDD'
      Size = 10
    end
    object tbClientesDDI: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'DDI'
      Origin = 'DDI'
      Size = 10
    end
    object tbClientesDATA_CADASTRO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_CADASTRO'
      Origin = 'DATA_CADASTRO'
    end
    object tbClientesDATA_ALTERACAO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_ALTERACAO'
      Origin = 'DATA_ALTERACAO'
    end
    object tbClientesSERVICOS: TMemoField
      AutoGenerateValue = arDefault
      FieldName = 'SERVICOS'
      Origin = 'SERVICOS'
      BlobType = ftMemo
    end
    object tbClientesN_ATENDIMENTOS: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'N_ATENDIMENTOS'
      Origin = 'N_ATENDIMENTOS'
    end
    object tbClientesCOD_FUNCIONARIO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_FUNCIONARIO'
      Origin = 'COD_FUNCIONARIO'
    end
    object tbClientesIMPRIMIR: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'IMPRIMIR'
      Origin = 'IMPRIMIR'
      Size = 3
    end
    object tbClientesFOTO: TBlobField
      AutoGenerateValue = arDefault
      FieldName = 'FOTO'
      Origin = 'FOTO'
    end
    object tbClientesFLAG_CONTATO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'FLAG_CONTATO'
      Origin = 'FLAG_CONTATO'
      Size = 1
    end
    object tbClientesDATA_NASC: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_NASC'
      Origin = 'DATA_NASC'
    end
    object tbClientesTIPO_CLIENTE: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'TIPO_CLIENTE'
      Origin = 'TIPO_CLIENTE'
      Size = 3
    end
    object tbClientesLIMITE_CREDITO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'LIMITE_CREDITO'
      Origin = 'LIMITE_CREDITO'
    end
    object tbClientesMES_ANIVERSARIO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'MES_ANIVERSARIO'
      Origin = 'MES_ANIVERSARIO'
    end
    object tbClientesDATA_ULTIMA_COMPRA: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_ULTIMA_COMPRA'
      Origin = 'DATA_ULTIMA_COMPRA'
    end
    object tbClientesDATA_ULTIMO_SERVICO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_ULTIMO_SERVICO'
      Origin = 'DATA_ULTIMO_SERVICO'
    end
    object tbClientesRESTRICAO_INTERNA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'RESTRICAO_INTERNA'
      Origin = 'RESTRICAO_INTERNA'
      Size = 1
    end
    object tbClientesNUM_OCORRENCIAS: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'NUM_OCORRENCIAS'
      Origin = 'NUM_OCORRENCIAS'
    end
    object tbClientesNUM_OCORRENCIAS_PEND: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'NUM_OCORRENCIAS_PEND'
      Origin = 'NUM_OCORRENCIAS_PEND'
    end
    object tbClientesNOTIF_CLIENTE: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NOTIF_CLIENTE'
      Origin = 'NOTIF_CLIENTE'
      Size = 1
    end
    object tbClientesULTIMO_CONTATO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'ULTIMO_CONTATO'
      Origin = 'ULTIMO_CONTATO'
    end
    object tbClientesCOD_ALTERNATIVO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_ALTERNATIVO'
      Origin = 'COD_ALTERNATIVO'
    end
    object tbClientesCONTROLA_FIDELIDADE: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CONTROLA_FIDELIDADE'
      Origin = 'CONTROLA_FIDELIDADE'
      Size = 1
    end
    object tbClientesMOTIVO_RESTRICAO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'MOTIVO_RESTRICAO'
      Origin = 'MOTIVO_RESTRICAO'
      Size = 150
    end
    object tbClientesTOTAL_PONTOS: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'TOTAL_PONTOS'
      Origin = 'TOTAL_PONTOS'
    end
    object tbClientesTOTAL_CREDITO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'TOTAL_CREDITO'
      Origin = 'TOTAL_CREDITO'
    end
    object tbClientesLISTA_NEGRA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'LISTA_NEGRA'
      Origin = 'LISTA_NEGRA'
      Size = 1
    end
    object tbClientesMOTIVO_LISTA_NEGRA_EXCLUSAO: TMemoField
      AutoGenerateValue = arDefault
      FieldName = 'MOTIVO_LISTA_NEGRA_EXCLUSAO'
      Origin = 'MOTIVO_LISTA_NEGRA_EXCLUSAO'
      BlobType = ftMemo
    end
    object tbClientesDATA_ULT_CONTATO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_ULT_CONTATO'
      Origin = 'DATA_ULT_CONTATO'
    end
    object tbClientesCOD_STATUS_TRANSMISSAO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_STATUS_TRANSMISSAO'
      Origin = 'COD_STATUS_TRANSMISSAO'
    end
    object tbClientesSUPORTE_BLOQUEADO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'SUPORTE_BLOQUEADO'
      Origin = 'SUPORTE_BLOQUEADO'
      Size = 1
    end
    object tbClientesCOD_CATEGORIA_CLIENTE: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_CATEGORIA_CLIENTE'
      Origin = 'COD_CATEGORIA_CLIENTE'
    end
    object tbClientesCODIGO_ANTERIOR: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_ANTERIOR'
      Origin = 'CODIGO_ANTERIOR'
      Size = 45
    end
    object tbClientesSALDO_TOTAL: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'SALDO_TOTAL'
      Origin = 'SALDO_TOTAL'
    end
    object tbClientesSALDO_UTILIZADO: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'SALDO_UTILIZADO'
      Origin = 'SALDO_UTILIZADO'
    end
    object tbClientesSALDO_DISPONIVEL: TFloatField
      AutoGenerateValue = arDefault
      FieldName = 'SALDO_DISPONIVEL'
      Origin = 'SALDO_DISPONIVEL'
    end
    object tbClientesTAXA_JUROS: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'TAXA_JUROS'
      Origin = 'TAXA_JUROS'
    end
    object tbClientesUSUARIO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'USUARIO'
      Origin = 'USUARIO'
      Size = 60
    end
    object tbClientesSENHA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'SENHA'
      Origin = 'SENHA'
      Size = 60
    end
    object tbClientesBLOQUEADO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'BLOQUEADO'
      Origin = 'BLOQUEADO'
      Size = 1
    end
    object tbClientesCOD_ERP: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_ERP'
      Origin = 'COD_ERP'
    end
    object tbClientesDATA_ULTIMO_LOGIN: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_ULTIMO_LOGIN'
      Origin = 'DATA_ULTIMO_LOGIN'
    end
    object tbClientesDIAS_SEM_LOGAR: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'DIAS_SEM_LOGAR'
      Origin = 'DIAS_SEM_LOGAR'
    end
    object tbClientesCOD_FUNCIONARIO_INTEGRACAO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_FUNCIONARIO_INTEGRACAO'
      Origin = 'COD_FUNCIONARIO_INTEGRACAO'
    end
    object tbClientesCOD_COMERCIAL: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_COMERCIAL'
      Origin = 'COD_COMERCIAL'
    end
    object tbClientesACCESS_TOKEN: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'ACCESS_TOKEN'
      Origin = 'ACCESS_TOKEN'
      Size = 200
    end
    object tbClientesREFRESH_TOKEN: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'REFRESH_TOKEN'
      Origin = 'REFRESH_TOKEN'
      Size = 200
    end
    object tbClientesREGISTER_ID: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'REGISTER_ID'
      Origin = 'REGISTER_ID'
      Size = 200
    end
    object tbClientesMAIN_MERCHANT_ID: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'MAIN_MERCHANT_ID'
      Origin = 'MAIN_MERCHANT_ID'
    end
    object tbClientesCOD_CREDENCIMANTO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'COD_CREDENCIMANTO'
      Origin = 'COD_CREDENCIMANTO'
    end
    object tbClientesGERA_PGTO_AUTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'GERA_PGTO_AUTO'
      Origin = 'GERA_PGTO_AUTO'
      Size = 1
    end
    object tbClientesDIAS_AUTO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'DIAS_AUTO'
      Origin = 'DIAS_AUTO'
    end
    object tbClientesCAMPO_ADICIONAL1: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CAMPO_ADICIONAL1'
      Origin = 'CAMPO_ADICIONAL1'
      Size = 60
    end
    object tbClientesCAMPO_ADICIONAL2: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CAMPO_ADICIONAL2'
      Origin = 'CAMPO_ADICIONAL2'
      Size = 60
    end
    object tbClientesCAMPO_ADICIONAL3: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CAMPO_ADICIONAL3'
      Origin = 'CAMPO_ADICIONAL3'
      Size = 60
    end
    object tbClientesINTEGRA_DIVERGENTE: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'INTEGRA_DIVERGENTE'
      Origin = 'INTEGRA_DIVERGENTE'
      Size = 1
    end
    object tbClientesINTEGRACAO_HABILITADA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'INTEGRACAO_HABILITADA'
      Origin = 'INTEGRACAO_HABILITADA'
      Size = 1
    end
    object tbClientesINTEGRA_VENDAS: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'INTEGRA_VENDAS'
      Origin = 'INTEGRA_VENDAS'
      Size = 1
    end
    object tbClientesINTEGRA_RECEBIMENTOS: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'INTEGRA_RECEBIMENTOS'
      Origin = 'INTEGRA_RECEBIMENTOS'
      Size = 1
    end
    object tbClientesHORA_RETORNO_VENDA: TTimeField
      AutoGenerateValue = arDefault
      FieldName = 'HORA_RETORNO_VENDA'
      Origin = 'HORA_RETORNO_VENDA'
    end
    object tbClientesHORA_RETORNO_PAGAMENTO: TTimeField
      AutoGenerateValue = arDefault
      FieldName = 'HORA_RETORNO_PAGAMENTO'
      Origin = 'HORA_RETORNO_PAGAMENTO'
    end
    object tbClientesDIAS_RETORNO_BAIXA: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'DIAS_RETORNO_BAIXA'
      Origin = 'DIAS_RETORNO_BAIXA'
    end
    object tbClientesDIAS_RETORNO_VENDA: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'DIAS_RETORNO_VENDA'
      Origin = 'DIAS_RETORNO_VENDA'
    end
    object tbClientesARQUIVOS_PROCESSADOS: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'ARQUIVOS_PROCESSADOS'
      Origin = 'ARQUIVOS_PROCESSADOS'
      Size = 1
    end
    object tbClientesINTEGRACAO_GLOBAL: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'INTEGRACAO_GLOBAL'
      Origin = 'INTEGRACAO_GLOBAL'
      Size = 1
    end
    object tbClientesCODIGO: TFDAutoIncField
      FieldName = 'CODIGO'
      Origin = 'CODIGO'
      ProviderFlags = [pfInWhere, pfInKey]
      ReadOnly = True
    end
  end
  object DataClienteOperadora: TDataSource
    DataSet = tbClienteOperadora
    Left = 140
    Top = 16
  end
  object tbClienteOperadora: TFDQuery
    CachedUpdates = True
    Connection = Data1.Conexao
    SQL.Strings = (
      
        'select * from cliente_operadora where cliente_operadora.CODIGO i' +
        's null')
    Left = 140
    Top = 4
    object tbClienteOperadoraCODIGO: TFDAutoIncField
      FieldName = 'CODIGO'
      Origin = 'CODIGO'
      ProviderFlags = [pfInWhere, pfInKey]
      ReadOnly = True
    end
    object tbClienteOperadoraCOD_CLIENTE: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_CLIENTE'
      Origin = 'COD_CLIENTE'
    end
    object tbClienteOperadoraCOD_ADQUIRENTE: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_ADQUIRENTE'
      Origin = 'COD_ADQUIRENTE'
    end
    object tbClienteOperadoraCODIGO_ESTABELECIMENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_ESTABELECIMENTO'
      Origin = 'CODIGO_ESTABELECIMENTO'
      Size = 50
    end
    object tbClienteOperadoraCNPJ_ESTABELECIMENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CNPJ_ESTABELECIMENTO'
      Origin = 'CNPJ_ESTABELECIMENTO'
      Size = 45
    end
    object tbClienteOperadoraCOD_GRUPO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_GRUPO'
      Origin = 'COD_GRUPO'
    end
    object tbClienteOperadoraAFFILIATION_KEY: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'AFFILIATION_KEY'
      Origin = 'AFFILIATION_KEY'
      Size = 60
    end
    object tbClienteOperadoraINTEGRA_API_PAGSEGURO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'INTEGRA_API_PAGSEGURO'
      Origin = 'INTEGRA_API_PAGSEGURO'
      Size = 1
    end
    object tbClienteOperadoraRETORNO_VENDA_PGTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'RETORNO_VENDA_PGTO'
      Origin = 'RETORNO_VENDA_PGTO'
      Size = 1
    end
  end
  object DataVendasDuplicidade: TDataSource
    DataSet = tbVendasDuplicidade
    Left = 263
    Top = 16
  end
  object tbVendasDuplicidade: TFDQuery
    CachedUpdates = True
    Connection = Data1.Conexao
    SQL.Strings = (
      'select vendas.NSU, vendas.PARCELA, vendas.AUTORIZACAO,'
      ' vendas.DATA_VENDA, vendas.CNPJ, count(vendas.CODIGO) as total'
      'from vendas'
      'where vendas.CODIGO is null'
      'group by vendas.NSU, vendas.PARCELA, vendas.AUTORIZACAO, '
      'vendas.DATA_VENDA, vendas.CNPJ'
      'HAVING COUNT(vendas.CODIGO) > 1')
    Left = 263
    Top = 5
    object tbVendasDuplicidadeNSU: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NSU'
      Origin = 'NSU'
      Size = 90
    end
    object tbVendasDuplicidadePARCELA: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'PARCELA'
      Origin = 'PARCELA'
    end
    object tbVendasDuplicidadeAUTORIZACAO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'AUTORIZACAO'
      Origin = 'AUTORIZACAO'
      Size = 120
    end
    object tbVendasDuplicidadeDATA_VENDA: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_VENDA'
      Origin = 'DATA_VENDA'
    end
    object tbVendasDuplicidadetotal: TLargeintField
      AutoGenerateValue = arDefault
      FieldName = 'total'
      Origin = 'total'
      ProviderFlags = []
      ReadOnly = True
    end
    object tbVendasDuplicidadeCNPJ: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CNPJ'
      Origin = 'CNPJ'
      Size = 45
    end
  end
  object DataPagamentosDuplicidade: TDataSource
    DataSet = tbPagamentosDuplicidade
    Left = 63
    Top = 87
  end
  object tbPagamentosDuplicidade: TFDQuery
    CachedUpdates = True
    Connection = Data1.Conexao
    SQL.Strings = (
      'select pagamentos_operadoras.NSU, pagamentos_operadoras.PARCELA,'
      ' pagamentos_operadoras.DATA_PAGAMENTO,'
      
        ' pagamentos_operadoras.CNPJ, count(pagamentos_operadoras.CODIGO)' +
        ' as total'
      'from pagamentos_operadoras'
      'where pagamentos_operadoras.CODIGO is null'#11
      
        'group by pagamentos_operadoras.NSU, pagamentos_operadoras.PARCEL' +
        'A, pagamentos_operadoras.DATA_PAGAMENTO,'#11
      'pagamentos_operadoras.CNPJ'#11
      'HAVING COUNT(pagamentos_operadoras.CODIGO) > 1')
    Left = 63
    Top = 74
    object tbPagamentosDuplicidadeNSU: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NSU'
      Origin = 'NSU'
      Size = 50
    end
    object tbPagamentosDuplicidadePARCELA: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'PARCELA'
      Origin = 'PARCELA'
    end
    object tbPagamentosDuplicidadeDATA_PAGAMENTO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_PAGAMENTO'
      Origin = 'DATA_PAGAMENTO'
    end
    object tbPagamentosDuplicidadeCNPJ: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CNPJ'
      Origin = 'CNPJ'
      Size = 45
    end
    object tbPagamentosDuplicidadetotal: TLargeintField
      AutoGenerateValue = arDefault
      FieldName = 'total'
      Origin = 'total'
      ProviderFlags = []
      ReadOnly = True
    end
  end
  object DataPagamentosDuplicidade2: TDataSource
    DataSet = tbPagamentosDuplicidade2
    Left = 213
    Top = 86
  end
  object tbPagamentosDuplicidade2: TFDQuery
    CachedUpdates = True
    Connection = Data1.Conexao
    SQL.Strings = (
      'select pagamentos_operadoras.NSU, '
      'pagamentos_operadoras.CODIGO_AUTORIZACAO,'
      ' pagamentos_operadoras.PARCELA,'
      ' pagamentos_operadoras.DATA_PAGAMENTO,'
      ' pagamentos_operadoras.DATA_VENDA,'
      
        ' pagamentos_operadoras.CNPJ, count(pagamentos_operadoras.CODIGO)' +
        ' as total'
      'from pagamentos_operadoras'
      'where pagamentos_operadoras.CODIGO is null'
      'group by pagamentos_operadoras.NSU, '
      'pagamentos_operadoras.CODIGO_AUTORIZACAO,'
      'pagamentos_operadoras.PARCELA, '
      'pagamentos_operadoras.DATA_PAGAMENTO,'
      'pagamentos_operadoras.DATA_VENDA,'
      'pagamentos_operadoras.CNPJ'#11
      ''
      ''
      ''
      'HAVING COUNT(pagamentos_operadoras.CODIGO) > 1')
    Left = 213
    Top = 73
    object tbPagamentosDuplicidade2NSU: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NSU'
      Origin = 'NSU'
      Size = 50
    end
    object tbPagamentosDuplicidade2CODIGO_AUTORIZACAO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_AUTORIZACAO'
      Origin = 'CODIGO_AUTORIZACAO'
      Size = 50
    end
    object tbPagamentosDuplicidade2PARCELA: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'PARCELA'
      Origin = 'PARCELA'
    end
    object tbPagamentosDuplicidade2DATA_PAGAMENTO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_PAGAMENTO'
      Origin = 'DATA_PAGAMENTO'
    end
    object tbPagamentosDuplicidade2DATA_VENDA: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_VENDA'
      Origin = 'DATA_VENDA'
    end
    object tbPagamentosDuplicidade2CNPJ: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CNPJ'
      Origin = 'CNPJ'
      Size = 45
    end
    object tbPagamentosDuplicidade2total: TLargeintField
      AutoGenerateValue = arDefault
      FieldName = 'total'
      Origin = 'total'
      ProviderFlags = []
      ReadOnly = True
    end
  end
  object DataPagamentosDuplicidade3: TDataSource
    DataSet = tbPagamentosDuplicidade3
    Left = 365
    Top = 86
  end
  object tbPagamentosDuplicidade3: TFDQuery
    CachedUpdates = True
    Connection = Data1.Conexao
    SQL.Strings = (
      
        'select NSU, CODIGO_AUTORIZACAO, ID_LOJA, PARCELA, TOTAL_PARCELAS' +
        ', DATA_PAGAMENTO, count(pagamentos_operadoras.CODIGO) as total '
      'from pagamentos_operadoras'
      ' where CODIGO is null'
      
        'group by NSU, CODIGO_AUTORIZACAO, ID_LOJA, PARCELA, TOTAL_PARCEL' +
        'AS, DATA_PAGAMENTO'
      'HAVING COUNT(pagamentos_operadoras.CODIGO) > 1')
    Left = 365
    Top = 73
    object tbPagamentosDuplicidade3NSU: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NSU'
      Origin = 'NSU'
      Size = 50
    end
    object tbPagamentosDuplicidade3CODIGO_AUTORIZACAO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_AUTORIZACAO'
      Origin = 'CODIGO_AUTORIZACAO'
      Size = 50
    end
    object tbPagamentosDuplicidade3ID_LOJA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'ID_LOJA'
      Origin = 'ID_LOJA'
      Size = 25
    end
    object tbPagamentosDuplicidade3PARCELA: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'PARCELA'
      Origin = 'PARCELA'
    end
    object tbPagamentosDuplicidade3TOTAL_PARCELAS: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'TOTAL_PARCELAS'
      Origin = 'TOTAL_PARCELAS'
    end
    object tbPagamentosDuplicidade3DATA_PAGAMENTO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_PAGAMENTO'
      Origin = 'DATA_PAGAMENTO'
    end
    object tbPagamentosDuplicidade3total: TLargeintField
      AutoGenerateValue = arDefault
      FieldName = 'total'
      Origin = 'total'
      ProviderFlags = []
      ReadOnly = True
    end
  end
end
