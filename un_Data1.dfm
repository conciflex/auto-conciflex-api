object Data1: TData1
  OldCreateOrder = False
  Height = 333
  Width = 487
  object Conexao: TFDConnection
    Params.Strings = (
      'Database=conciflex'
      'User_Name=admin'
      'Password=Conc!flex5'
      'Server=129.159.54.96'
      'Compress=False'
      'DriverID=MySQL')
    FetchOptions.AssignedValues = [evMode, evRowsetSize]
    FetchOptions.Mode = fmAll
    FetchOptions.RowsetSize = -1
    ResourceOptions.AssignedValues = [rvAutoReconnect]
    ResourceOptions.AutoReconnect = True
    UpdateOptions.AssignedValues = [uvLockWait, uvAutoCommitUpdates]
    UpdateOptions.AutoCommitUpdates = True
    Connected = True
    LoginPrompt = False
    Transaction = FDTransaction1
    UpdateTransaction = FDTransaction1
    Left = 32
    Top = 8
  end
  object FDPhysMySQLDriverLink1: TFDPhysMySQLDriverLink
    VendorHome = 'C:\Auto Conciflex API'
    VendorLib = 'libmysql.dll'
    Left = 132
    Top = 8
  end
  object FDGUIxWaitCursor1: TFDGUIxWaitCursor
    Provider = 'Forms'
    Left = 248
    Top = 8
  end
  object FDTransaction1: TFDTransaction
    Connection = Conexao
    Left = 350
    Top = 7
  end
  object DataExcluir: TDataSource
    DataSet = tbExcluir
    Left = 34
    Top = 84
  end
  object tbExcluir: TFDQuery
    CachedUpdates = True
    Connection = Conexao
    Left = 34
    Top = 72
  end
  object DataControleArquivos: TDataSource
    DataSet = tbControleArquivos
    Left = 124
    Top = 84
  end
  object tbControleArquivos: TFDQuery
    CachedUpdates = True
    Connection = Conexao
    SQL.Strings = (
      'Select * from controle_arquivos_processados')
    Left = 124
    Top = 72
    object tbControleArquivosCODIGO: TFDAutoIncField
      FieldName = 'CODIGO'
      Origin = 'CODIGO'
      ProviderFlags = [pfInUpdate, pfInWhere, pfInKey]
      IdentityInsert = True
    end
    object tbControleArquivosNOME_ARQUIVO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NOME_ARQUIVO'
      Origin = 'NOME_ARQUIVO'
      ProviderFlags = [pfInUpdate]
      Size = 120
    end
    object tbControleArquivosLOCALIZACAO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'LOCALIZACAO'
      Origin = 'LOCALIZACAO'
      ProviderFlags = [pfInUpdate]
      Size = 255
    end
    object tbControleArquivosDATA_PROCESSAMENTO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_PROCESSAMENTO'
      Origin = 'DATA_PROCESSAMENTO'
      ProviderFlags = [pfInUpdate]
    end
    object tbControleArquivosHORA_PROCESSAMENTO: TTimeField
      AutoGenerateValue = arDefault
      FieldName = 'HORA_PROCESSAMENTO'
      Origin = 'HORA_PROCESSAMENTO'
      ProviderFlags = [pfInUpdate]
    end
    object tbControleArquivosCOD_ADIQUIRENTE: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_ADIQUIRENTE'
      Origin = 'COD_ADIQUIRENTE'
      ProviderFlags = [pfInUpdate]
    end
    object tbControleArquivosCNPJ_CLIENTE: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CNPJ_CLIENTE'
      Origin = 'CNPJ_CLIENTE'
      ProviderFlags = [pfInUpdate]
      Size = 45
    end
    object tbControleArquivosDATA_ARQUIVO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_ARQUIVO'
      Origin = 'DATA_ARQUIVO'
      ProviderFlags = [pfInUpdate]
    end
    object tbControleArquivosDATA_MENOR_VENDA: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_MENOR_VENDA'
      Origin = 'DATA_MENOR_VENDA'
      ProviderFlags = [pfInUpdate]
    end
    object tbControleArquivosDATA_MAIOR_VENDA: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_MAIOR_VENDA'
      Origin = 'DATA_MAIOR_VENDA'
      ProviderFlags = [pfInUpdate]
    end
    object tbControleArquivosDATA_MENOR_PAGAMENTO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_MENOR_PAGAMENTO'
      Origin = 'DATA_MENOR_PAGAMENTO'
      ProviderFlags = [pfInUpdate]
    end
    object tbControleArquivosDATA_MAIOR_PAGAMENTO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_MAIOR_PAGAMENTO'
      Origin = 'DATA_MAIOR_PAGAMENTO'
      ProviderFlags = [pfInUpdate]
    end
    object tbControleArquivosESTABELECIMENTO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'ESTABELECIMENTO'
      Origin = 'ESTABELECIMENTO'
      ProviderFlags = [pfInUpdate]
      Size = 60
    end
    object tbControleArquivosARQUIVO_COM_FALHA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'ARQUIVO_COM_FALHA'
      Origin = 'ARQUIVO_COM_FALHA'
      ProviderFlags = [pfInUpdate]
      Size = 1
    end
    object tbControleArquivosCONFIRMADO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CONFIRMADO'
      Origin = 'CONFIRMADO'
      Size = 1
    end
  end
  object DataClientes: TDataSource
    DataSet = tbClientes
    Left = 230
    Top = 84
  end
  object tbClientes: TFDQuery
    CachedUpdates = True
    Connection = Conexao
    SQL.Strings = (
      'select * from clientes where clientes.CODIGO is null')
    Left = 230
    Top = 72
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
  object DataFeriados: TDataSource
    DataSet = tbFeriados
    Left = 322
    Top = 83
  end
  object tbFeriados: TFDQuery
    CachedUpdates = True
    Connection = Conexao
    SQL.Strings = (
      'select * from feriados where feriados.DIA_SEMANA is null')
    Left = 322
    Top = 71
    object tbFeriadosDATA: TDateTimeField
      AutoGenerateValue = arDefault
      FieldName = 'DATA'
      Origin = '`DATA`'
    end
    object tbFeriadosDIA_SEMANA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'DIA_SEMANA'
      Origin = 'DIA_SEMANA'
      Size = 255
    end
    object tbFeriadosDESCRICAO_FERIADO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'DESCRICAO_FERIADO'
      Origin = 'DESCRICAO_FERIADO'
      Size = 255
    end
    object tbFeriadosDATA_FERIADO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_FERIADO'
      Origin = 'DATA_FERIADO'
    end
  end
  object DataGrupos: TDataSource
    DataSet = tbGrupos
    Left = 418
    Top = 81
  end
  object tbGrupos: TFDQuery
    CachedUpdates = True
    Connection = Conexao
    SQL.Strings = (
      
        'select * from grupos_clientes where grupos_clientes.CODIGO is nu' +
        'll')
    Left = 418
    Top = 69
    object tbGruposCODIGO: TFDAutoIncField
      FieldName = 'CODIGO'
      Origin = 'CODIGO'
      ProviderFlags = [pfInWhere, pfInKey]
      ReadOnly = True
    end
    object tbGruposCOD_CLIENTE: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_CLIENTE'
      Origin = 'COD_CLIENTE'
    end
    object tbGruposNOME_EMPRESA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'NOME_EMPRESA'
      Origin = 'NOME_EMPRESA'
      Size = 90
    end
    object tbGruposCNPJ: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CNPJ'
      Origin = 'CNPJ'
      Size = 25
    end
    object tbGruposCOD_FUNCIONARIO_RESP: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_FUNCIONARIO_RESP'
      Origin = 'COD_FUNCIONARIO_RESP'
    end
    object tbGruposDATA_CADASTRO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_CADASTRO'
      Origin = 'DATA_CADASTRO'
    end
    object tbGruposHORA_CADASTRO: TTimeField
      AutoGenerateValue = arDefault
      FieldName = 'HORA_CADASTRO'
      Origin = 'HORA_CADASTRO'
    end
    object tbGruposID_ERP: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'ID_ERP'
      Origin = 'ID_ERP'
      Size = 50
    end
    object tbGruposID_ERP_EXT: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'ID_ERP_EXT'
      Origin = 'ID_ERP_EXT'
      Size = 25
    end
    object tbGruposVINCULO_API_PAG_SEGURO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'VINCULO_API_PAG_SEGURO'
      Origin = 'VINCULO_API_PAG_SEGURO'
      Size = 1
    end
    object tbGruposQUANTIDADE_VINCULOS_API: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'QUANTIDADE_VINCULOS_API'
      Origin = 'QUANTIDADE_VINCULOS_API'
    end
  end
  object DataDomicilioCliente: TDataSource
    DataSet = tbDomicilioCliente
    Left = 42
    Top = 156
  end
  object tbDomicilioCliente: TFDQuery
    CachedUpdates = True
    Connection = Conexao
    SQL.Strings = (
      
        'select * from domicilio_cliente where domicilio_cliente.CODIGO i' +
        's null')
    Left = 42
    Top = 144
    object tbDomicilioClienteCODIGO: TFDAutoIncField
      FieldName = 'CODIGO'
      Origin = 'CODIGO'
      ProviderFlags = [pfInWhere, pfInKey]
      ReadOnly = True
    end
    object tbDomicilioClienteCOD_CLIENTE: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_CLIENTE'
      Origin = 'COD_CLIENTE'
    end
    object tbDomicilioClienteCOD_GRUPO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_GRUPO'
      Origin = 'COD_GRUPO'
    end
    object tbDomicilioClienteCNPJ: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CNPJ'
      Origin = 'CNPJ'
      Size = 45
    end
    object tbDomicilioClienteBANCO: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'BANCO'
      Origin = 'BANCO'
      Size = 10
    end
    object tbDomicilioClienteCOD_BANCO: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_BANCO'
      Origin = 'COD_BANCO'
    end
    object tbDomicilioClienteAGENCIA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'AGENCIA'
      Origin = 'AGENCIA'
      Size = 10
    end
    object tbDomicilioClienteCONTA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CONTA'
      Origin = 'CONTA'
      Size = 10
    end
    object tbDomicilioClienteCOD_ADQUIRENTE: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_ADQUIRENTE'
      Origin = 'COD_ADQUIRENTE'
    end
    object tbDomicilioClienteCOD_ESTABELECIMENTO: TIntegerField
      AutoGenerateValue = arDefault
      FieldName = 'COD_ESTABELECIMENTO'
      Origin = 'COD_ESTABELECIMENTO'
    end
  end
  object DataControleAjustes: TDataSource
    DataSet = tbControleAjustes
    Left = 170
    Top = 155
  end
  object tbControleAjustes: TFDQuery
    CachedUpdates = True
    Connection = Conexao
    SQL.Strings = (
      
        'select * from controle_ajustes where controle_ajustes.CODIGO is ' +
        'null')
    Left = 170
    Top = 143
    object tbControleAjustesCODIGO: TFDAutoIncField
      FieldName = 'CODIGO'
      Origin = 'CODIGO'
      ProviderFlags = [pfInWhere, pfInKey]
      ReadOnly = True
    end
    object tbControleAjustesCOD_ADQUIRENTE: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_ADQUIRENTE'
      Origin = 'COD_ADQUIRENTE'
    end
    object tbControleAjustesCODIGO_OPERADORA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'CODIGO_OPERADORA'
      Origin = 'CODIGO_OPERADORA'
      Size = 10
    end
    object tbControleAjustesDESCRICAO_OPERADORA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'DESCRICAO_OPERADORA'
      Origin = 'DESCRICAO_OPERADORA'
      Size = 90
    end
    object tbControleAjustesCOD_TIPO_AJUSTE_SISTEMA: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_TIPO_AJUSTE_SISTEMA'
      Origin = 'COD_TIPO_AJUSTE_SISTEMA'
    end
    object tbControleAjustesDATA_CADASTRO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_CADASTRO'
      Origin = 'DATA_CADASTRO'
    end
    object tbControleAjustesDATA_ALTERACAO: TDateField
      AutoGenerateValue = arDefault
      FieldName = 'DATA_ALTERACAO'
      Origin = 'DATA_ALTERACAO'
    end
    object tbControleAjustesCOD_FUNCIONARIO_RESP: TSingleField
      AutoGenerateValue = arDefault
      FieldName = 'COD_FUNCIONARIO_RESP'
      Origin = 'COD_FUNCIONARIO_RESP'
    end
    object tbControleAjustesDESCRICAO_TIPO_AJUSTE_SISTEMA: TStringField
      AutoGenerateValue = arDefault
      FieldName = 'DESCRICAO_TIPO_AJUSTE_SISTEMA'
      Origin = 'DESCRICAO_TIPO_AJUSTE_SISTEMA'
      Size = 180
    end
  end
  object DataPagamentosOperadoras: TDataSource
    DataSet = tbPagamentosOperadoras
    Left = 312
    Top = 154
  end
  object tbPagamentosOperadoras: TFDQuery
    CachedUpdates = True
    Connection = Conexao
    SQL.Strings = (
      
        'Select * from pagamentos_operadoras where pagamentos_operadoras.' +
        'CODIGO is null')
    Left = 312
    Top = 142
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
  end
end
