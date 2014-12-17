VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form formShowParameter 
   Caption         =   "通道参数"
   ClientHeight    =   6048
   ClientLeft      =   132
   ClientTop       =   708
   ClientWidth     =   9360
   Icon            =   "formShowParameter.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   6048
   ScaleWidth      =   9360
   StartUpPosition =   3  'Windows Default
   Begin MSComctlLib.ListView lvChannels 
      Height          =   4572
      Left            =   0
      TabIndex        =   0
      Top             =   -120
      Width           =   6252
      _ExtentX        =   11028
      _ExtentY        =   8065
      View            =   3
      LabelEdit       =   1
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   0
   End
   Begin VB.Menu mnuFile 
      Caption         =   "文件(&F)"
      Begin VB.Menu mnuExit 
         Caption         =   "退出(&x)"
      End
   End
   Begin VB.Menu mnuView 
      Caption         =   "显示(&V)"
      Begin VB.Menu mnuTranslate 
         Caption         =   "翻译值(&T)"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuOrigin 
         Caption         =   "原始值(&O)"
      End
   End
End
Attribute VB_Name = "formShowParameter"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private mxc As LYXC

Private Sub Form_Load()
    GetXCInfoFromBuffer
End Sub

Private Sub Form_Resize()
    On Error Resume Next
    Me.lvChannels.Left = 0
    Me.lvChannels.Top = 0
    Me.lvChannels.Width = Me.ScaleWidth
    Me.lvChannels.Height = Me.ScaleHeight
    ShowParameter
End Sub

Private Sub mnuExit_Click()
    Unload Me
End Sub

Private Sub mnuOrigin_Click()
    Me.mnuTranslate.Checked = False
    Me.mnuOrigin.Checked = True
    ShowParameter
End Sub

Private Sub mnuTranslate_Click()
    Me.mnuTranslate.Checked = True
    Me.mnuOrigin.Checked = False
    ShowParameter
End Sub

Private Sub ShowParameter()
    Me.lvChannels.ListItems.Clear
    Me.lvChannels.ColumnHeaders.Clear
    Dim itmX As ListItem
    Dim i As Long
        
    If Me.mnuTranslate.Checked Then
        With Me.lvChannels.ColumnHeaders
            .Add , , "通道", 800
            .Add , , "通道类型"
            .Add , , "传感器类型"
            .Add , , "补偿方式"
            .Add , , "补偿通道"
            .Add , , "线路修正电阻"
            .Add , , "A", 1000
            .Add , , "B", 1000
            .Add , , "二次计算"
        End With
        Select Case gXC.XCType
        Case gd99LYXC30
            For i = 1 To 30
                Set itmX = Me.lvChannels.ListItems.Add(, , "Ch:" & Format(i, "00"))
                itmX.SubItems(1) = mxc.ParaInfo(i).ChannelType
                itmX.SubItems(2) = mxc.ParaInfo(i).SensorType
                itmX.SubItems(3) = mxc.ParaInfo(i).CompType
                itmX.SubItems(4) = mxc.ParaInfo(i).CompNo
                itmX.SubItems(5) = mxc.ParaInfo(i).CompResistance
                itmX.SubItems(6) = mxc.ParaInfo(i).A
                itmX.SubItems(7) = mxc.ParaInfo(i).B
                itmX.SubItems(8) = mxc.ParaInfo(i).Calculate2
            Next i
        Case gd99LYXC60
            For i = 1 To 60
                Set itmX = Me.lvChannels.ListItems.Add(, , "Ch:" & Format(i, "00"))
                itmX.SubItems(1) = mxc.ParaInfo(i).ChannelType
                itmX.SubItems(2) = mxc.ParaInfo(i).SensorType
                itmX.SubItems(3) = mxc.ParaInfo(i).CompType
                itmX.SubItems(4) = mxc.ParaInfo(i).CompNo
                itmX.SubItems(5) = mxc.ParaInfo(i).CompResistance
                itmX.SubItems(6) = mxc.ParaInfo(i).A
                itmX.SubItems(7) = mxc.ParaInfo(i).B
                itmX.SubItems(8) = mxc.ParaInfo(i).Calculate2
            Next i
        End Select
    Else
        With Me.lvChannels.ColumnHeaders
            .Add , , "通道", 800
            For i = 0 To 9
                .Add , , Format(Hex(i), "00"), 500
            Next i
            .Add , , "0A", 500
            .Add , , "0B", 500
            .Add , , "0C", 500
            .Add , , "0D", 500
            .Add , , "0E", 500
            .Add , , "0F", 500
        End With
        Dim j As Long
        Dim strTemp As String
        Select Case gXC.XCType
        Case gd99LYXC30
            For i = 1 To 30
                Set itmX = Me.lvChannels.ListItems.Add(, , "Ch:" & Format(i, "00"))
                strTemp = mxc.Para(i)
                For j = 0 To 15
                    itmX.SubItems(1 + j) = Mid(strTemp, 1 + j * 2, 2)
                Next j
            Next i
        Case gd99LYXC60
            For i = 1 To 60
                Set itmX = Me.lvChannels.ListItems.Add(, , "Ch:" & Format(i, "00"))
                strTemp = mxc.Para(i)
                For j = 0 To 15
                    itmX.SubItems(1 + j) = Mid(strTemp, 1 + j * 2, 2)
                Next j
            Next i
        End Select
    End If
End Sub

Private Sub GetXCInfoFromBuffer()
    Dim lChannelCount As Long
    Select Case gXC.XCType
    Case gd99LYXC30
        lChannelCount = 30
    Case gd99LYXC60
        lChannelCount = 60
    End Select
    
    Dim iChannelNo As Integer
    Dim iChannelType As Integer
    Dim iSensorType As Integer
    Dim iCompNo As Integer
    Dim iCompType As Integer
    Dim fCompResistance As Single
    Dim iCalculate2 As Integer
    Dim bUseDefault As Boolean
    Dim fA As Single
    Dim fB As Single
    
    Dim abTemp(0 To 31) As Byte
    For iChannelNo = 1 To lChannelCount
        If Mid(gXC.Para(iChannelNo), 1, 1) = "8" Then
            mxc.ParaInfo(iChannelNo).Used = False
        Else
            mxc.ParaInfo(iChannelNo).Used = True
            CopyMemory abTemp(0), gabRevBuffer(5 + (iChannelNo - 1) * 32), 32
            mxc.Para(iChannelNo) = StrConv(abTemp, vbUnicode)
            iSensorType = Val(Mid(mxc.Para(iChannelNo), 1, 2))
            Select Case iSensorType
            Case 0 To 4, 7
                iChannelType = 1
            Case 5, 6, 8
                iChannelType = 2
            Case 9 To 13
                iChannelType = 3
            End Select
            Select Case iChannelType
            Case 1  '热电阻
                fCompResistance = Val(Mid(mxc.Para(iChannelNo), 11, 2)) / 10#
            Case 2  '热电偶
                iCompNo = Val(Mid(mxc.Para(iChannelNo), 11, 2))
                If iCompNo = 0 Then
                    iCompType = 1   '恒温箱
                Else
                    iCompType = 2   '冷端补偿
                End If
            Case 3  '传感器
            End Select
            iCalculate2 = Val(Mid(mxc.Para(iChannelNo), 13, 2))
            If Mid(mxc.Para(iChannelNo), 9, 2) = "00" Then
                bUseDefault = True
            Else
                bUseDefault = False
            End If
            fA = YTStringtoSingle(Mid(mxc.Para(iChannelNo), 15, 6))
            fB = YTStringtoSingle(Mid(mxc.Para(iChannelNo), 21, 6))
            
            mxc.ParaInfo(iChannelNo).A = CStr(fA)
            mxc.ParaInfo(iChannelNo).B = CStr(fB)
            Select Case iChannelType
            Case 1
                mxc.ParaInfo(iChannelNo).ChannelType = "热电阻"
                mxc.ParaInfo(iChannelNo).CompResistance = Format(fCompResistance, "0.0") & "Ω"
                mxc.ParaInfo(iChannelNo).CompNo = ""
            Case 2
                mxc.ParaInfo(iChannelNo).ChannelType = "热电偶"
                Select Case iCompType
                Case 1
                    mxc.ParaInfo(iChannelNo).CompType = "恒温箱补偿"
                    mxc.ParaInfo(iChannelNo).CompNo = ""
                Case 2
                    mxc.ParaInfo(iChannelNo).CompType = "冷端补偿"
                    mxc.ParaInfo(iChannelNo).CompNo = CStr(iCompNo)
                Case Else
                    mxc.ParaInfo(iChannelNo).CompType = ""
                    mxc.ParaInfo(iChannelNo).CompNo = ""
                End Select
                mxc.ParaInfo(iChannelNo).CompResistance = ""
            Case 3
                mxc.ParaInfo(iChannelNo).ChannelType = "传感器"
                mxc.ParaInfo(iChannelNo).CompResistance = ""
                mxc.ParaInfo(iChannelNo).CompNo = ""
            Case Else
                mxc.ParaInfo(iChannelNo).ChannelType = ""
                mxc.ParaInfo(iChannelNo).CompResistance = ""
                mxc.ParaInfo(iChannelNo).CompNo = ""
            End Select
            Select Case iSensorType
            Case 0
                mxc.ParaInfo(iChannelNo).SensorType = "Cu50"
            Case 1
                mxc.ParaInfo(iChannelNo).SensorType = "Cu100"
            Case 2
                mxc.ParaInfo(iChannelNo).SensorType = "BA1"
            Case 3
                mxc.ParaInfo(iChannelNo).SensorType = "BA2"
            Case 4
                mxc.ParaInfo(iChannelNo).SensorType = "Pt100"
            Case 5
                mxc.ParaInfo(iChannelNo).SensorType = "K"
            Case 6
                mxc.ParaInfo(iChannelNo).SensorType = "E"
            Case 7
                mxc.ParaInfo(iChannelNo).SensorType = "G53"
            Case 8
                mxc.ParaInfo(iChannelNo).SensorType = "EA2"
            Case 9
                mxc.ParaInfo(iChannelNo).SensorType = "0-5V"
            Case 10
                mxc.ParaInfo(iChannelNo).SensorType = "1-5V"
            Case 11
                mxc.ParaInfo(iChannelNo).SensorType = "0-10mA"
            Case 12
                mxc.ParaInfo(iChannelNo).SensorType = "0-20mA"
            Case 13
                mxc.ParaInfo(iChannelNo).SensorType = "0-10V"
            Case Else
                mxc.ParaInfo(iChannelNo).SensorType = ""
            End Select
            Select Case iCalculate2
            Case 0
                mxc.ParaInfo(iChannelNo).Calculate2 = "y=x"
            Case 3
                mxc.ParaInfo(iChannelNo).Calculate2 = "y=sqrt(x)"
            Case 4
                mxc.ParaInfo(iChannelNo).Calculate2 = "y=x/2+z0/2"
            Case 5
                mxc.ParaInfo(iChannelNo).Calculate2 = "y=x/4+3*z0/4"
            Case 6
                mxc.ParaInfo(iChannelNo).Calculate2 = "y=x/8+7z0/8"
            Case Else
                mxc.ParaInfo(iChannelNo).Calculate2 = ""
            End Select
            'Debug.Print mxc.Para(iChannelNo)
        End If
    Next iChannelNo
End Sub
