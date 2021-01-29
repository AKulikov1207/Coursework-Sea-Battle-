object Form1: TForm1
  Left = 0
  Top = 0
  Caption = #1052#1086#1088#1089#1082#1086#1081' '#1073#1086#1081
  ClientHeight = 398
  ClientWidth = 493
  Color = clSkyBlue
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Fild1: TImage
    Left = 16
    Top = 64
    Width = 201
    Height = 201
    OnMouseDown = Fild1MouseDown
  end
  object Fild2: TImage
    Left = 272
    Top = 64
    Width = 201
    Height = 201
    OnMouseDown = Fild2MouseDown
  end
  object Panel2: TPanel
    Left = 56
    Top = 8
    Width = 377
    Height = 41
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
  end
  object BitBtn3: TBitBtn
    Left = 176
    Top = 280
    Width = 137
    Height = 48
    Caption = #1053#1072#1095#1072#1090#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    OnClick = BitBtn3Click
  end
  object RadioGroup1: TRadioGroup
    Left = 16
    Top = 280
    Width = 97
    Height = 105
    Caption = #1057#1083#1086#1078#1085#1086#1089#1090#1100
    Items.Strings = (
      '1 '#1091#1088#1086#1074#1077#1085#1100
      '2 '#1091#1088#1086#1074#1077#1085#1100
      '3 '#1091#1088#1086#1074#1077#1085#1100)
    TabOrder = 2
    OnClick = RadioGroup1Click
  end
end
