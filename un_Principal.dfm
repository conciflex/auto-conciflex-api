object Principal: TPrincipal
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = 'Auto Conciflex API'
  ClientHeight = 429
  ClientWidth = 904
  Color = clGray
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object TPageControl: TPageControl
    Left = 2
    Top = 4
    Width = 675
    Height = 413
    ActivePage = TabSheet1
    DockSite = True
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Principal'
      object Label8: TLabel
        Left = 176
        Top = 16
        Width = 109
        Height = 13
        Caption = 'DATA '#218'LT. PROCESSO'
      end
      object Label9: TLabel
        Left = 317
        Top = 16
        Width = 111
        Height = 13
        Caption = 'HORA '#218'LT. PROCESSO'
      end
      object Label24: TLabel
        Left = 8
        Top = 77
        Width = 124
        Height = 13
        Caption = 'ARQUIVO SENDO LIDO:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label78: TLabel
        Left = 578
        Top = 38
        Width = 27
        Height = 13
        Caption = 'Loop:'
      end
      object Label79: TLabel
        Left = 610
        Top = 38
        Width = 6
        Height = 13
        Caption = '0'
      end
      object Edit2: TEdit
        Left = 176
        Top = 35
        Width = 115
        Height = 21
        CharCase = ecUpperCase
        Enabled = False
        ReadOnly = True
        TabOrder = 0
      end
      object Edit3: TEdit
        Left = 317
        Top = 35
        Width = 115
        Height = 21
        CharCase = ecUpperCase
        Enabled = False
        ReadOnly = True
        TabOrder = 1
      end
      object RadioGroup1: TRadioGroup
        Left = 8
        Top = 8
        Width = 148
        Height = 53
        Caption = 'PROCESSO ATIVO'
        Columns = 2
        ItemIndex = 1
        Items.Strings = (
          'SIM'
          'N'#195'O')
        TabOrder = 2
      end
      object GroupBox1: TGroupBox
        Left = 8
        Top = 204
        Width = 652
        Height = 176
        Caption = 'PROCESSO ATUAL'
        TabOrder = 3
        object Label1: TLabel
          Left = 12
          Top = 45
          Width = 61
          Height = 13
          Caption = 'PROCESSO:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label2: TLabel
          Left = 12
          Top = 62
          Width = 43
          Height = 13
          Caption = 'Processo'
        end
        object Label4: TLabel
          Left = 12
          Top = 79
          Width = 64
          Height = 13
          Caption = 'CONTADOR:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label5: TLabel
          Left = 12
          Top = 98
          Width = 38
          Height = 13
          Caption = 'FINAL: '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label6: TLabel
          Left = 79
          Top = 79
          Width = 6
          Height = 13
          Caption = '0'
        end
        object Label7: TLabel
          Left = 79
          Top = 98
          Width = 6
          Height = 13
          Caption = '0'
        end
        object Label3: TLabel
          Left = 12
          Top = 117
          Width = 102
          Height = 13
          Caption = 'ARQUIVOS LIDOS: '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label10: TLabel
          Left = 119
          Top = 117
          Width = 6
          Height = 13
          Caption = '0'
        end
        object Label11: TLabel
          Left = 13
          Top = 14
          Width = 61
          Height = 13
          Caption = 'PROCESSO:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label21: TLabel
          Left = 12
          Top = 30
          Width = 43
          Height = 13
          Caption = 'Processo'
        end
        object ProgressBar1: TProgressBar
          Left = 12
          Top = 136
          Width = 293
          Height = 17
          TabOrder = 0
        end
      end
      object Memo3: TMemo
        Left = 8
        Top = 100
        Width = 5000
        Height = 98
        ScrollBars = ssVertical
        TabOrder = 4
      end
      object Edit1: TEdit
        Left = 467
        Top = 3
        Width = 60
        Height = 21
        TabOrder = 5
        Visible = False
      end
      object Edit4: TEdit
        Left = 138
        Top = 73
        Width = 434
        Height = 21
        TabOrder = 6
      end
      object Button6: TButton
        Left = 467
        Top = 33
        Width = 105
        Height = 25
        Caption = 'Liberar Mem'#243'ria'
        TabOrder = 7
        Visible = False
        OnClick = Button6Click
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Stone'
      ImageIndex = 1
      object GroupBox4: TGroupBox
        Left = 3
        Top = 3
        Width = 650
        Height = 381
        Caption = 'Stone'
        Color = clWhite
        ParentBackground = False
        ParentColor = False
        TabOrder = 0
        object Label12: TLabel
          Left = 21
          Top = 16
          Width = 64
          Height = 13
          Caption = 'Data Inicial'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label13: TLabel
          Left = 168
          Top = 16
          Width = 56
          Height = 13
          Caption = 'Data Final'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label14: TLabel
          Left = 21
          Top = 102
          Width = 117
          Height = 13
          Caption = 'Progresso de Leitura'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label15: TLabel
          Left = 21
          Top = 146
          Width = 23
          Height = 13
          Caption = 'Data'
        end
        object Label16: TLabel
          Left = 21
          Top = 182
          Width = 72
          Height = 13
          Caption = 'Erro na leitura:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsItalic]
          ParentFont = False
        end
        object Label17: TLabel
          Left = 99
          Top = 182
          Width = 72
          Height = 13
          AutoSize = False
          Caption = '0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsItalic]
          ParentFont = False
        end
        object Label20: TLabel
          Left = 21
          Top = 117
          Width = 85
          Height = 13
          Caption = 'Estabelecimento: '
        end
        object Label22: TLabel
          Left = 107
          Top = 117
          Width = 78
          Height = 13
          Caption = 'Estabelecimento'
        end
        object Label23: TLabel
          Left = 517
          Top = 114
          Width = 6
          Height = 13
          Caption = '0'
        end
        object Label25: TLabel
          Left = 582
          Top = 114
          Width = 6
          Height = 13
          Caption = '0'
        end
        object Label26: TLabel
          Left = 550
          Top = 114
          Width = 4
          Height = 13
          Caption = '-'
        end
        object TLabel
          Left = 155
          Top = 102
          Width = 3
          Height = 13
        end
        object Label27: TLabel
          Left = 21
          Top = 213
          Width = 54
          Height = 13
          Caption = 'PROCESSO'
        end
        object Label28: TLabel
          Left = 21
          Top = 232
          Width = 49
          Height = 13
          Caption = 'Contador:'
        end
        object Label29: TLabel
          Left = 21
          Top = 251
          Width = 26
          Height = 13
          Caption = 'Final:'
        end
        object Label30: TLabel
          Left = 76
          Top = 232
          Width = 6
          Height = 13
          Caption = '0'
        end
        object Label31: TLabel
          Left = 76
          Top = 251
          Width = 6
          Height = 13
          Caption = '0'
        end
        object Label32: TLabel
          Left = 21
          Top = 62
          Width = 39
          Height = 13
          Caption = 'Cliente'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label33: TLabel
          Left = 341
          Top = 62
          Width = 31
          Height = 13
          Cursor = crHandPoint
          Caption = 'Limpar'
          OnClick = Label33Click
        end
        object Label34: TLabel
          Left = 21
          Top = 270
          Width = 22
          Height = 13
          Caption = 'LOG'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label35: TLabel
          Left = 596
          Top = 270
          Width = 31
          Height = 13
          Cursor = crHandPoint
          Caption = 'Limpar'
          OnClick = Label35Click
        end
        object DateTimePicker1: TDateTimePicker
          Left = 21
          Top = 35
          Width = 128
          Height = 21
          Date = 44097.000000000000000000
          Time = 44097.000000000000000000
          TabOrder = 0
        end
        object DateTimePicker2: TDateTimePicker
          Left = 168
          Top = 35
          Width = 128
          Height = 21
          Date = 44097.000000000000000000
          Time = 44097.000000000000000000
          TabOrder = 1
        end
        object Button17: TButton
          Left = 316
          Top = 24
          Width = 113
          Height = 32
          Cursor = crHandPoint
          Cancel = True
          Caption = 'Iniciar Processo'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
          OnClick = Button17Click
        end
        object ProgressBar2: TProgressBar
          Left = 21
          Top = 165
          Width = 620
          Height = 11
          TabOrder = 3
        end
        object ProgressBar3: TProgressBar
          Left = 21
          Top = 133
          Width = 620
          Height = 11
          TabOrder = 4
        end
        object DBLookupComboBox1: TDBLookupComboBox
          Left = 21
          Top = 79
          Width = 351
          Height = 21
          KeyField = 'CODIGO'
          ListField = 'NOME'
          ListSource = DataProcessamento.DataClientes
          TabOrder = 5
        end
        object Memo2: TMemo
          Left = 21
          Top = 289
          Width = 612
          Height = 88
          ScrollBars = ssVertical
          TabOrder = 6
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'PagSeguro'
      ImageIndex = 2
      object GroupBox5: TGroupBox
        Left = 3
        Top = 0
        Width = 650
        Height = 383
        Caption = 'PagSeguro'
        Color = clWhite
        ParentBackground = False
        ParentColor = False
        TabOrder = 0
        object Label36: TLabel
          Left = 21
          Top = 16
          Width = 64
          Height = 13
          Caption = 'Data Inicial'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label37: TLabel
          Left = 168
          Top = 16
          Width = 56
          Height = 13
          Caption = 'Data Final'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label38: TLabel
          Left = 21
          Top = 102
          Width = 117
          Height = 13
          Caption = 'Progresso de Leitura'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label39: TLabel
          Left = 21
          Top = 146
          Width = 23
          Height = 13
          Caption = 'Data'
        end
        object Label40: TLabel
          Left = 21
          Top = 182
          Width = 72
          Height = 13
          Caption = 'Erro na leitura:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsItalic]
          ParentFont = False
        end
        object Label41: TLabel
          Left = 99
          Top = 182
          Width = 72
          Height = 13
          AutoSize = False
          Caption = '0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsItalic]
          ParentFont = False
        end
        object Label44: TLabel
          Left = 21
          Top = 117
          Width = 85
          Height = 13
          Caption = 'Estabelecimento: '
        end
        object Label45: TLabel
          Left = 107
          Top = 117
          Width = 78
          Height = 13
          Caption = 'Estabelecimento'
        end
        object Label46: TLabel
          Left = 517
          Top = 114
          Width = 6
          Height = 13
          Caption = '0'
        end
        object Label47: TLabel
          Left = 582
          Top = 114
          Width = 6
          Height = 13
          Caption = '0'
        end
        object Label48: TLabel
          Left = 550
          Top = 114
          Width = 4
          Height = 13
          Caption = '-'
        end
        object TLabel
          Left = 155
          Top = 102
          Width = 3
          Height = 13
        end
        object Label49: TLabel
          Left = 21
          Top = 213
          Width = 54
          Height = 13
          Caption = 'PROCESSO'
        end
        object Label50: TLabel
          Left = 21
          Top = 232
          Width = 49
          Height = 13
          Caption = 'Contador:'
        end
        object Label51: TLabel
          Left = 21
          Top = 251
          Width = 26
          Height = 13
          Caption = 'Final:'
        end
        object Label52: TLabel
          Left = 76
          Top = 232
          Width = 6
          Height = 13
          Caption = '0'
        end
        object Label53: TLabel
          Left = 76
          Top = 251
          Width = 6
          Height = 13
          Caption = '0'
        end
        object Label54: TLabel
          Left = 21
          Top = 62
          Width = 39
          Height = 13
          Caption = 'Cliente'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label55: TLabel
          Left = 341
          Top = 62
          Width = 31
          Height = 13
          Cursor = crHandPoint
          Caption = 'Limpar'
          OnClick = Label55Click
        end
        object Label56: TLabel
          Left = 21
          Top = 270
          Width = 22
          Height = 13
          Caption = 'LOG'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label57: TLabel
          Left = 596
          Top = 270
          Width = 31
          Height = 13
          Cursor = crHandPoint
          Caption = 'Limpar'
          OnClick = Label57Click
        end
        object Label58: TLabel
          Left = 259
          Top = 232
          Width = 36
          Height = 13
          Caption = 'P'#225'gina:'
        end
        object Label59: TLabel
          Left = 301
          Top = 232
          Width = 6
          Height = 13
          Caption = '0'
        end
        object Label60: TLabel
          Left = 259
          Top = 251
          Width = 28
          Height = 13
          Caption = 'Total:'
        end
        object Label61: TLabel
          Left = 301
          Top = 251
          Width = 6
          Height = 13
          Caption = '0'
        end
        object DateTimePicker3: TDateTimePicker
          Left = 21
          Top = 35
          Width = 128
          Height = 21
          Date = 44097.000000000000000000
          Time = 44097.000000000000000000
          TabOrder = 0
        end
        object DateTimePicker4: TDateTimePicker
          Left = 168
          Top = 35
          Width = 128
          Height = 21
          Date = 44097.000000000000000000
          Time = 44097.000000000000000000
          TabOrder = 1
        end
        object Button2: TButton
          Left = 316
          Top = 24
          Width = 113
          Height = 32
          Cursor = crHandPoint
          Cancel = True
          Caption = 'Iniciar Processo'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
          OnClick = Button2Click
        end
        object ProgressBar4: TProgressBar
          Left = 21
          Top = 165
          Width = 620
          Height = 11
          TabOrder = 3
        end
        object ProgressBar5: TProgressBar
          Left = 21
          Top = 133
          Width = 620
          Height = 11
          TabOrder = 4
        end
        object DBLookupComboBox2: TDBLookupComboBox
          Left = 21
          Top = 79
          Width = 351
          Height = 21
          KeyField = 'CODIGO'
          ListField = 'NOME'
          ListSource = DataProcessamento.DataClientes
          TabOrder = 5
        end
        object Memo4: TMemo
          Left = 21
          Top = 289
          Width = 612
          Height = 88
          ScrollBars = ssVertical
          TabOrder = 6
        end
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'B'#244'nusCred'
      ImageIndex = 3
      object GroupBox2: TGroupBox
        Left = 3
        Top = 1
        Width = 650
        Height = 381
        Caption = 'B'#244'nusCred'
        Color = clWhite
        ParentBackground = False
        ParentColor = False
        TabOrder = 0
        object Label18: TLabel
          Left = 21
          Top = 16
          Width = 64
          Height = 13
          Caption = 'Data Inicial'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label19: TLabel
          Left = 168
          Top = 16
          Width = 56
          Height = 13
          Caption = 'Data Final'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label42: TLabel
          Left = 21
          Top = 102
          Width = 117
          Height = 13
          Caption = 'Progresso de Leitura'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label43: TLabel
          Left = 21
          Top = 146
          Width = 23
          Height = 13
          Caption = 'Data'
        end
        object Label62: TLabel
          Left = 21
          Top = 182
          Width = 72
          Height = 13
          Caption = 'Erro na leitura:'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsItalic]
          ParentFont = False
        end
        object Label63: TLabel
          Left = 99
          Top = 182
          Width = 72
          Height = 13
          AutoSize = False
          Caption = '0'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsItalic]
          ParentFont = False
        end
        object Label64: TLabel
          Left = 21
          Top = 117
          Width = 85
          Height = 13
          Caption = 'Estabelecimento: '
        end
        object Label65: TLabel
          Left = 112
          Top = 117
          Width = 78
          Height = 13
          Caption = 'Estabelecimento'
        end
        object Label66: TLabel
          Left = 517
          Top = 114
          Width = 6
          Height = 13
          Caption = '0'
        end
        object Label67: TLabel
          Left = 582
          Top = 114
          Width = 6
          Height = 13
          Caption = '0'
        end
        object Label68: TLabel
          Left = 550
          Top = 114
          Width = 4
          Height = 13
          Caption = '-'
        end
        object TLabel
          Left = 155
          Top = 102
          Width = 3
          Height = 13
        end
        object Label69: TLabel
          Left = 21
          Top = 213
          Width = 54
          Height = 13
          Caption = 'PROCESSO'
        end
        object Label70: TLabel
          Left = 21
          Top = 232
          Width = 49
          Height = 13
          Caption = 'Contador:'
        end
        object Label71: TLabel
          Left = 21
          Top = 251
          Width = 26
          Height = 13
          Caption = 'Final:'
        end
        object Label72: TLabel
          Left = 76
          Top = 232
          Width = 6
          Height = 13
          Caption = '0'
        end
        object Label73: TLabel
          Left = 76
          Top = 251
          Width = 6
          Height = 13
          Caption = '0'
        end
        object Label74: TLabel
          Left = 21
          Top = 62
          Width = 39
          Height = 13
          Caption = 'Cliente'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label75: TLabel
          Left = 341
          Top = 62
          Width = 31
          Height = 13
          Cursor = crHandPoint
          Caption = 'Limpar'
          OnClick = Label33Click
        end
        object Label76: TLabel
          Left = 21
          Top = 270
          Width = 22
          Height = 13
          Caption = 'LOG'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label77: TLabel
          Left = 602
          Top = 270
          Width = 31
          Height = 13
          Cursor = crHandPoint
          Caption = 'Limpar'
          OnClick = Label77Click
        end
        object DateTimePicker5: TDateTimePicker
          Left = 21
          Top = 35
          Width = 128
          Height = 21
          Date = 44097.000000000000000000
          Time = 44097.000000000000000000
          TabOrder = 0
        end
        object DateTimePicker6: TDateTimePicker
          Left = 168
          Top = 35
          Width = 128
          Height = 21
          Date = 44097.000000000000000000
          Time = 44097.000000000000000000
          TabOrder = 1
        end
        object Button1: TButton
          Left = 316
          Top = 24
          Width = 113
          Height = 32
          Cursor = crHandPoint
          Cancel = True
          Caption = 'Iniciar Processo'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
          OnClick = Button1Click
        end
        object ProgressBar6: TProgressBar
          Left = 21
          Top = 165
          Width = 620
          Height = 11
          TabOrder = 3
        end
        object ProgressBar7: TProgressBar
          Left = 21
          Top = 133
          Width = 620
          Height = 11
          TabOrder = 4
        end
        object DBLookupComboBox3: TDBLookupComboBox
          Left = 21
          Top = 79
          Width = 351
          Height = 21
          KeyField = 'CODIGO'
          ListField = 'NOME'
          ListSource = DataProcessamento.DataClientes
          TabOrder = 5
        end
        object Memo1: TMemo
          Left = 21
          Top = 289
          Width = 612
          Height = 88
          ScrollBars = ssVertical
          TabOrder = 6
        end
      end
    end
  end
  object Timer1: TTimer
    Interval = 300000
    OnTimer = Timer1Timer
    Left = 728
    Top = 232
  end
  object MainMenu1: TMainMenu
    Left = 720
    Top = 71
    object Arquivo1: TMenuItem
      Caption = 'Arquivo'
      object Fechar1: TMenuItem
        Caption = 'Fechar'
      end
    end
    object Automaticva1: TMenuItem
      Caption = 'Autom'#225'tico'
      object AutomaticoBonuscred: TMenuItem
        Caption = 'B'#244'nusCred'
        OnClick = AutomaticoBonuscredClick
      end
      object AutomaticoPagSeguro: TMenuItem
        Caption = 'PagSeguro'
        OnClick = AutomaticoPagSeguroClick
      end
      object Stone5: TMenuItem
        Caption = 'Stone'
        OnClick = Stone5Click
      end
    end
    object Atualizaes1: TMenuItem
      Caption = 'Atualiza'#231#245'es'
      object Stone3: TMenuItem
        Caption = 'Stone'
        object MarcarDadosBrutosparaTRATADON2: TMenuItem
          Caption = 'Marcar Dados Brutos para TRATADO = '#39'N'#39
          OnClick = MarcarDadosBrutosparaTRATADON2Click
        end
      end
      object Bnuscred3: TMenuItem
        Caption = 'B'#244'nuscred'
        object Marcardadosbrutospa1: TMenuItem
          Caption = 'Marcar dados brutos para TRATADO = '#39'N'#39
          OnClick = Marcardadosbrutospa1Click
        end
      end
    end
    object Funcoes1: TMenuItem
      Caption = 'Fun'#231#245'es'
      object BnusCred1: TMenuItem
        Caption = 'B'#244'nusCred'
        object VendasBonuscred: TMenuItem
          Caption = 'Tratar Vendas'
          OnClick = VendasBonuscredClick
        end
        object PagamentosBonuscred: TMenuItem
          Caption = 'Tratar Pagamentos'
          OnClick = PagamentosBonuscredClick
        end
        object AjustesBonuscred: TMenuItem
          Caption = 'Tratar Ajustes'
          OnClick = AjustesBonuscredClick
        end
      end
      object PagSeguro1: TMenuItem
        Caption = 'PagSeguro'
        object TratarVendasPagSeguro: TMenuItem
          Caption = 'Tratar Vendas'
          OnClick = TratarVendasPagSeguroClick
        end
        object TratarPagamentosPagSeguro: TMenuItem
          Caption = 'Tratar Pagamentos'
          OnClick = TratarPagamentosPagSeguroClick
        end
        object TratarAntecipacoesPagSeguro: TMenuItem
          Caption = 'Tratar Antecipa'#231#245'es'
          OnClick = TratarAntecipacoesPagSeguroClick
        end
      end
      object Stone2: TMenuItem
        Caption = 'Stone'
        object TratarVendasStone: TMenuItem
          Caption = 'Tratar Vendas'
          OnClick = TratarVendasStoneClick
        end
        object TratarAntecipacoesStone: TMenuItem
          Caption = 'Tratar Antecipa'#231#245'es'
          OnClick = TratarAntecipacoesStoneClick
        end
        object TratarPagamentosStone: TMenuItem
          Caption = 'Tratar Pagamentos'
          OnClick = TratarPagamentosStoneClick
        end
        object TratarAjustesStone: TMenuItem
          Caption = 'Tratar Ajustes'
          OnClick = TratarAjustesStoneClick
        end
      end
    end
    object Excluses1: TMenuItem
      Caption = 'Exclus'#245'es'
      object Bnuscred2: TMenuItem
        Caption = 'B'#244'nuscred'
        object ExcluirVendas1: TMenuItem
          Caption = 'Excluir Vendas'
          OnClick = ExcluirVendas1Click
        end
        object ExcluirPagamentos1: TMenuItem
          Caption = 'Excluir Pagamentos'
          OnClick = ExcluirPagamentos1Click
        end
      end
      object PagSeguro3: TMenuItem
        Caption = 'PagSeguro'
        object ExcluirDuplicidadedeVendas2: TMenuItem
          Caption = 'Excluir Duplicidade de Vendas'
          OnClick = ExcluirDuplicidadedeVendas2Click
        end
        object ExcluirDuplicidadedePagamento6: TMenuItem
          Caption = 'Excluir Duplicidade de Pagamento'
          OnClick = ExcluirDuplicidadedePagamento6Click
        end
      end
      object Stone1: TMenuItem
        Caption = 'Stone'
        object ExcluirDadosBrutos9: TMenuItem
          Caption = 'Excluir Dados Brutos'
          OnClick = ExcluirDadosBrutos9Click
        end
        object ExcluirVendas10: TMenuItem
          Caption = 'Excluir Vendas'
          OnClick = ExcluirVendas10Click
        end
        object ExcluirPagamentos10: TMenuItem
          Caption = 'Excluir Pagamentos'
          OnClick = ExcluirPagamentos10Click
        end
        object Excluirduplicidadedevendas1: TMenuItem
          Caption = 'Excluir duplicidade de vendas'
          OnClick = Excluirduplicidadedevendas1Click
        end
        object Excluirduplicidadedepagamentos1: TMenuItem
          Caption = 'Excluir duplicidade de pagamentos'
          OnClick = Excluirduplicidadedepagamentos1Click
        end
      end
    end
    object Manual1: TMenuItem
      Caption = 'Manual'
      object PagSeguro2: TMenuItem
        Caption = 'PagSeguro'
        object DeletardadosDalgaloPneus1: TMenuItem
          Caption = 'Deletar dados - Dalgalo Pneus'
          Visible = False
          OnClick = DeletardadosDalgaloPneus1Click
        end
        object Vincularvendasepagamentosoperadora1: TMenuItem
          Caption = 'Vincular vendas e pagamentos operadora'
          OnClick = Vincularvendasepagamentosoperadora1Click
        end
      end
      object Stone4: TMenuItem
        Caption = 'Stone'
        object Atualizardadosbancriosvenda1: TMenuItem
          Caption = 'Atualizar dados banc'#225'rios - venda'
          OnClick = Atualizardadosbancriosvenda1Click
        end
        object Atualizardadosbancriospagamento1: TMenuItem
          Caption = 'Atualizar dados banc'#225'rios - pagamento'
          OnClick = Atualizardadosbancriospagamento1Click
        end
        object ResetarVendas1: TMenuItem
          Caption = 'Vincular vendas e pagamentos operadoras'
          OnClick = ResetarVendas1Click
        end
        object Preencherbandeiranospagamentos1: TMenuItem
          Caption = 'Preencher bandeira nos pagamentos'
          OnClick = Preencherbandeiranospagamentos1Click
        end
        object Preencherdadosbancriosnospagamentos1: TMenuItem
          Caption = 'Preencher dados banc'#225'rios nos pagamentos'
          OnClick = Preencherdadosbancriosnospagamentos1Click
        end
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = '.txt|.txt|.csv|.csv'
    FilterIndex = 2
    Left = 796
    Top = 71
  end
  object IdHTTP2: TIdHTTP
    IOHandler = IdSSLIOHandlerSocketOpenSSL2
    MaxAuthRetries = 10
    AllowCookies = True
    HandleRedirects = True
    ProxyParams.BasicAuthentication = False
    ProxyParams.ProxyPort = 0
    Request.ContentLength = -1
    Request.ContentRangeEnd = -1
    Request.ContentRangeStart = -1
    Request.ContentRangeInstanceLength = -1
    Request.Accept = 
      'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp' +
      ',image/apng,*/*;q=0.8'
    Request.BasicAuthentication = False
    Request.UserAgent = 
      'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like ' +
      'Gecko) Chrome/59.0.3071.104 Safari/537.36'
    Request.Ranges.Units = 'bytes'
    Request.Ranges = <>
    HTTPOptions = [hoForceEncodeParams]
    CookieManager = IdCookieManager2
    Compressor = IdCompressorZLib2
    Left = 716
    Top = 124
  end
  object IdSSLIOHandlerSocketOpenSSL1: TIdSSLIOHandlerSocketOpenSSL
    MaxLineAction = maException
    Port = 0
    DefaultPort = 0
    SSLOptions.Method = sslvTLSv1_2
    SSLOptions.SSLVersions = [sslvTLSv1_2]
    SSLOptions.Mode = sslmUnassigned
    SSLOptions.VerifyMode = []
    SSLOptions.VerifyDepth = 0
    Left = 908
    Top = 341
  end
  object XMLDocument1: TXMLDocument
    Left = 808
    Top = 227
  end
  object IdCookieManager1: TIdCookieManager
    Left = 804
    Top = 288
  end
  object IdCompressorZLib1: TIdCompressorZLib
    Left = 763
    Top = 343
  end
  object IdHTTP1: TIdHTTP
    IOHandler = IdSSLIOHandlerSocketOpenSSL1
    MaxAuthRetries = 10
    AllowCookies = True
    HandleRedirects = True
    ProxyParams.BasicAuthentication = False
    ProxyParams.ProxyPort = 0
    Request.ContentLength = -1
    Request.ContentRangeEnd = -1
    Request.ContentRangeStart = -1
    Request.ContentRangeInstanceLength = -1
    Request.Accept = 
      'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp' +
      ',image/apng,*/*;q=0.8'
    Request.BasicAuthentication = False
    Request.UserAgent = 
      'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like ' +
      'Gecko) Chrome/59.0.3071.104 Safari/537.36'
    Request.Ranges.Units = 'bytes'
    Request.Ranges = <>
    HTTPOptions = [hoForceEncodeParams]
    CookieManager = IdCookieManager1
    Compressor = IdCompressorZLib1
    Left = 716
    Top = 292
  end
  object IdCookieManager2: TIdCookieManager
    Left = 796
    Top = 122
  end
  object IdCompressorZLib2: TIdCompressorZLib
    Left = 763
    Top = 175
  end
  object IdSSLIOHandlerSocketOpenSSL2: TIdSSLIOHandlerSocketOpenSSL
    MaxLineAction = maException
    Port = 0
    DefaultPort = 0
    SSLOptions.Method = sslvTLSv1_2
    SSLOptions.SSLVersions = [sslvTLSv1_2]
    SSLOptions.Mode = sslmUnassigned
    SSLOptions.VerifyMode = []
    SSLOptions.VerifyDepth = 0
    Left = 908
    Top = 176
  end
end
