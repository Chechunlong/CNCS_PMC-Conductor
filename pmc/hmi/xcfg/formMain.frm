VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "MSFLXGRD.OCX"
Begin VB.Form formMain 
   Caption         =   "LY30Q/LY60E组态及调试工具"
   ClientHeight    =   5460
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   10395
   Icon            =   "formMain.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   ScaleHeight     =   5460
   ScaleWidth      =   10395
   StartUpPosition =   3  'Windows Default
   WindowState     =   2  'Maximized
   Begin MSFlexGridLib.MSFlexGrid fgData 
      Height          =   1515
      Left            =   90
      TabIndex        =   4
      Top             =   3300
      Visible         =   0   'False
      Width           =   7995
      _ExtentX        =   14102
      _ExtentY        =   2672
      _Version        =   393216
      Rows            =   16
      Cols            =   8
      FixedCols       =   0
      FocusRect       =   0
      HighLight       =   0
      GridLines       =   0
      AllowUserResizing=   1
      FormatString    =   """      ""<|""          ""<|""      ""<|""          ""<|""      ""<|""          ""<|""      ""<|""          ""<"
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Courier"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin MSComctlLib.Toolbar tbToolBar 
      Align           =   1  'Align Top
      Height          =   360
      Left            =   0
      TabIndex        =   3
      Top             =   0
      Width           =   10395
      _ExtentX        =   18336
      _ExtentY        =   635
      ButtonWidth     =   609
      ButtonHeight    =   582
      Wrappable       =   0   'False
      Appearance      =   1
      Style           =   1
      ImageList       =   "ImgListTb"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   21
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "New"
            Object.ToolTipText     =   "新建"
            ImageIndex      =   1
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Open"
            Object.ToolTipText     =   "打开"
            ImageIndex      =   2
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Save"
            Object.ToolTipText     =   "保存"
            ImageIndex      =   3
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button5 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "EdCom"
            Object.ToolTipText     =   "编辑公共参数"
            ImageIndex      =   4
         EndProperty
         BeginProperty Button6 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "EdCh"
            Object.ToolTipText     =   "编辑通道参数"
            ImageIndex      =   5
         EndProperty
         BeginProperty Button7 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button8 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Connect"
            Object.ToolTipText     =   "连接"
            ImageIndex      =   6
         EndProperty
         BeginProperty Button9 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Discon"
            Object.ToolTipText     =   "断开"
            ImageIndex      =   7
         EndProperty
         BeginProperty Button10 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button11 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Monitor"
            Object.ToolTipText     =   "切换至监控态"
            ImageIndex      =   8
         EndProperty
         BeginProperty Button12 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Run"
            Object.ToolTipText     =   "切换至运行态"
            ImageIndex      =   9
         EndProperty
         BeginProperty Button13 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button14 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "DlCom"
            Object.ToolTipText     =   "下装公共参数"
            ImageIndex      =   10
         EndProperty
         BeginProperty Button15 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "UlCom"
            Object.ToolTipText     =   "上载公共参数"
            ImageIndex      =   11
         EndProperty
         BeginProperty Button16 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "DlCh"
            Object.ToolTipText     =   "下装通道参数"
            ImageIndex      =   12
         EndProperty
         BeginProperty Button17 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "UlCh"
            Object.ToolTipText     =   "上载通道参数"
            ImageIndex      =   13
         EndProperty
         BeginProperty Button18 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button19 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "AD"
            Object.ToolTipText     =   "读A/D值"
            ImageIndex      =   14
         EndProperty
         BeginProperty Button20 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "EV"
            Object.ToolTipText     =   "读工程值"
            ImageIndex      =   15
         EndProperty
         BeginProperty Button21 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Refresh"
            Object.ToolTipText     =   "自动刷新"
            ImageIndex      =   16
            Style           =   1
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.ImageList ImgListTb 
      Left            =   7470
      Top             =   1290
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   16
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "formMain.frx":0442
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "formMain.frx":0984
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "formMain.frx":0EC6
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "formMain.frx":1408
            Key             =   ""
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "formMain.frx":1562
            Key             =   ""
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "formMain.frx":16BC
            Key             =   ""
         EndProperty
         BeginProperty ListImage7 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "formMain.frx":1B0E
            Key             =   ""
         EndProperty
         BeginProperty ListImage8 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "formMain.frx":1F60
            Key             =   ""
         EndProperty
         BeginProperty ListImage9 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "formMain.frx":23B2
            Key             =   ""
         EndProperty
         BeginProperty ListImage10 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "formMain.frx":2804
            Key             =   ""
         EndProperty
         BeginProperty ListImage11 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "formMain.frx":2C56
            Key             =   ""
         EndProperty
         BeginProperty ListImage12 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "formMain.frx":2DB0
            Key             =   ""
         EndProperty
         BeginProperty ListImage13 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "formMain.frx":2F0A
            Key             =   ""
         EndProperty
         BeginProperty ListImage14 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "formMain.frx":3064
            Key             =   ""
         EndProperty
         BeginProperty ListImage15 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "formMain.frx":31BE
            Key             =   ""
         EndProperty
         BeginProperty ListImage16 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "formMain.frx":3318
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.Timer timerRefresh 
      Enabled         =   0   'False
      Interval        =   2000
      Left            =   6690
      Top             =   480
   End
   Begin MSComDlg.CommonDialog cdlgFile 
      Left            =   6990
      Top             =   2490
      _ExtentX        =   688
      _ExtentY        =   688
      _Version        =   393216
      CancelError     =   -1  'True
      DefaultExt      =   "xcf"
      Filter          =   "巡测组态文件(*.xcf)|*.xcf"
      FilterIndex     =   1
   End
   Begin MSComctlLib.ListView lvChannels 
      Height          =   1515
      Left            =   60
      TabIndex        =   0
      Top             =   1320
      Width           =   6255
      _ExtentX        =   11033
      _ExtentY        =   2672
      View            =   3
      LabelEdit       =   1
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      NumItems        =   0
   End
   Begin VB.Label labComPara 
      BackColor       =   &H8000000A&
      Height          =   255
      Left            =   960
      TabIndex        =   2
      Top             =   870
      Width           =   2175
   End
   Begin VB.Label labCurXC 
      BackColor       =   &H8000000B&
      Caption         =   "无连接"
      Height          =   255
      Left            =   960
      TabIndex        =   1
      Top             =   420
      Width           =   2175
   End
   Begin VB.Menu mnuFile 
      Caption         =   "文件(&F)"
      Begin VB.Menu mnuNew 
         Caption         =   "新建(&N)"
      End
      Begin VB.Menu mnuOpen 
         Caption         =   "打开(&O)"
      End
      Begin VB.Menu mnuSave 
         Caption         =   "保存(&S)"
      End
      Begin VB.Menu mnuSpaceBar 
         Caption         =   "-"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuPrint 
         Caption         =   "打印(&P)"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuSpaceBar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuExit 
         Caption         =   "退出(&x)"
      End
   End
   Begin VB.Menu mnuEdit 
      Caption         =   "编辑(&E)"
      Begin VB.Menu mnuECom 
         Caption         =   "公共参数"
      End
      Begin VB.Menu mnuEChl 
         Caption         =   "通道参数"
      End
   End
   Begin VB.Menu mnuOperation 
      Caption         =   "操作(&O)"
      Begin VB.Menu mnuConnect 
         Caption         =   "连接(&C)"
      End
      Begin VB.Menu mnuDisConnect 
         Caption         =   "断开连接(&D)"
      End
      Begin VB.Menu mnuSaperate3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuMonitor 
         Caption         =   "监控状态(&M)"
      End
      Begin VB.Menu mnuRun 
         Caption         =   "运行状态(&R)"
      End
      Begin VB.Menu mnuSeperate4 
         Caption         =   "-"
      End
      Begin VB.Menu mnuDLCom 
         Caption         =   "下装公共参数"
      End
      Begin VB.Menu mnuULCom 
         Caption         =   "上载公共参数"
      End
      Begin VB.Menu mnuSpaceBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuDLChn 
         Caption         =   "下装通道参数"
      End
      Begin VB.Menu mnuULChn 
         Caption         =   "上载通道参数"
      End
   End
   Begin VB.Menu mnuDebug 
      Caption         =   "调试(&D)"
      Begin VB.Menu mnuReadRAW 
         Caption         =   "读取A/D值"
         Shortcut        =   ^H
      End
      Begin VB.Menu mnuReadValue 
         Caption         =   "读取工程值"
         Shortcut        =   ^E
      End
      Begin VB.Menu mnuSeparate6 
         Caption         =   "-"
      End
      Begin VB.Menu mnuAutoRefresh 
         Caption         =   "自动刷新"
      End
   End
   Begin VB.Menu mnuSpecial 
      Caption         =   "特别(&S)"
      Begin VB.Menu mnuInitial 
         Caption         =   "初始化站号(&I)"
      End
      Begin VB.Menu mnuSpecitalSapceBar 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFine 
         Caption         =   "扫描当前连接"
         Shortcut        =   ^F
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "帮助(&H)"
      Begin VB.Menu mnuDefine 
         Caption         =   "数据定义(&D)"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuSapceBar2 
         Caption         =   "-"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuAbout 
         Caption         =   "关于(&A)"
      End
   End
End
Attribute VB_Name = "formMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private lXCHandle As Long
Private lChnHandle As Long
Private PortIsOpen As Boolean
Private OldPort As Long

Private Sub Form_Load()
    Me.mnuDisConnect.Enabled = False
    Me.tbToolBar.Buttons("Discon").Enabled = False
    Me.mnuMonitor.Enabled = False
    Me.tbToolBar.Buttons("Monitor").Enabled = False
    Me.mnuRun.Enabled = False
    Me.tbToolBar.Buttons("Run").Enabled = False
    Me.mnuDLCom.Enabled = False
    Me.tbToolBar.Buttons("DlCom").Enabled = False
    Me.mnuULCom.Enabled = False
    Me.tbToolBar.Buttons("UlCom").Enabled = False
    Me.mnuDLChn.Enabled = False
    Me.tbToolBar.Buttons("DlCh").Enabled = False
    Me.mnuULChn.Enabled = False
    Me.tbToolBar.Buttons("UlCh").Enabled = False
    
    Me.mnuDebug.Enabled = False
    Me.tbToolBar.Buttons("AD").Enabled = False
    Me.tbToolBar.Buttons("EV").Enabled = False
    Me.tbToolBar.Buttons("Refresh").Enabled = False
    
    
    glChNum = 60
    glBt = 57600
    glTemperature = 0
    
    Set grdPara = New ADODB.Recordset
    With grdPara
        .Fields.Append "ChannelNO", adInteger
        .Fields.Append "Used", adBoolean
        .Fields.Append "ChannelType", adInteger
        .Fields.Append "SensorType", adInteger
        .Fields.Append "CompType", adInteger
        .Fields.Append "CompChannel", adInteger
        .Fields.Append "Compresistance", adSingle
        .Fields.Append "A", adSingle
        .Fields.Append "B", adSingle
        .Fields.Append "Calculate2", adInteger
        .Fields.Append "UseDefault", adBoolean
        .Fields.Append "MinValue", adSingle
        .Fields.Append "MaxValue", adSingle
        .CursorType = adOpenKeyset
        .LockType = adLockOptimistic
        .Open
    End With
    
    Dim i As Long
    For i = 1 To 99
        '表示此通道关闭
        With grdPara
            .AddNew
            .Fields("ChannelNO") = i
            .Fields("Used") = False
            .Update
        End With
        'gaPara(i) = String(32, "0")
        'Mid(gaPara(i), 1, 1) = "8"
        'gParaInfo(i).Used = False
    Next i
    
    ShowComPara
    ShowChPara
End Sub

Private Sub Form_Resize()
    On Error Resume Next
    
    Me.labCurXC.Left = 0
    Me.labCurXC.Top = Me.tbToolBar.Height + 50
    Me.labCurXC.Width = Me.ScaleWidth
    
    Me.labComPara.Left = 0
    Me.labComPara.Top = Me.tbToolBar.Height + Me.labCurXC.Height + 50
    Me.labComPara.Width = Me.ScaleWidth
    
    Me.lvChannels.Left = 0
    Me.lvChannels.Top = Me.labCurXC.Height + Me.tbToolBar.Height + Me.labComPara.Height + 50
    Me.lvChannels.Width = Me.ScaleWidth
    Me.lvChannels.Height = Me.ScaleHeight - Me.labCurXC.Height - Me.tbToolBar.Height - Me.labComPara.Height - 50

    Me.fgData.Left = 0
    Me.fgData.Top = Me.labCurXC.Height + Me.tbToolBar.Height + Me.labComPara.Height + 50
    Me.fgData.Width = Me.ScaleWidth
    Me.fgData.Height = Me.ScaleHeight - Me.labCurXC.Height - Me.tbToolBar.Height - Me.labComPara.Height - 50
End Sub

Private Sub Form_Unload(Cancel As Integer)
    uninit_spac
End Sub

Private Sub labComPara_DblClick()
    mnuECom_Click
End Sub

Private Sub lvChannels_DblClick()
    mnuEChl_Click
End Sub

Private Sub mnuAbout_Click()
    frmAbout.Show vbModal, Me
End Sub

Private Sub mnuAutoRefresh_Click()
    Me.timerRefresh.Interval = 1000 + 200 * (57600 \ glRealBt)
    Me.timerRefresh.Enabled = Not Me.timerRefresh.Enabled
    If Me.timerRefresh.Enabled Then
    End If
    'formRefresh.Show vbModal
End Sub

Private Sub mnuConnect_Click()
    formSelect.Show vbModal, Me
    If formSelect.Cancel Then Exit Sub
                
    glPort = formSelect.PortNo
    glStaNo = formSelect.StaNo
    glRealBt = formSelect.Bt

    Me.MousePointer = vbHourglass
    Select Case GetXCStatus(glPort, glStaNo)
    Case 1
        Me.mnuSpecial.Enabled = False
        Me.mnuConnect.Enabled = False
        Me.tbToolBar.Buttons("Connect").Enabled = False
        Me.mnuSpecial.Enabled = False
        Me.mnuDisConnect.Enabled = True
        Me.tbToolBar.Buttons("Discon").Enabled = True
        Me.mnuRun.Enabled = True
        Me.tbToolBar.Buttons("Run").Enabled = True
        Me.mnuDLChn.Enabled = True
        Me.tbToolBar.Buttons("DlCh").Enabled = True
        Me.mnuDLCom.Enabled = True
        Me.tbToolBar.Buttons("DlCom").Enabled = True
        Me.mnuULChn.Enabled = True
        Me.tbToolBar.Buttons("UlCh").Enabled = True
        Me.mnuULCom.Enabled = True
        Me.tbToolBar.Buttons("UlCom").Enabled = True
        Me.labCurXC = "当前连接：" & "端口=" & glPort & " / " & "波特率=" & glRealBt & " / " & _
                    "站号=" & glStaNo & " / " & "状态=" & "监控"
        Me.lvChannels.Visible = True
        Me.fgData.Visible = False
        Me.mnuNew.Enabled = True
        Me.mnuOpen.Enabled = True
        Me.mnuSave.Enabled = True
        Me.mnuEChl.Enabled = True
        Me.tbToolBar.Buttons("New").Enabled = True
        Me.tbToolBar.Buttons("Open").Enabled = True
        Me.tbToolBar.Buttons("Save").Enabled = True
        Me.tbToolBar.Buttons("EdCh").Enabled = True
    Case 2
        Me.mnuSpecial.Enabled = False
        Me.mnuConnect.Enabled = False
        Me.tbToolBar.Buttons("Connect").Enabled = False
        Me.mnuDisConnect.Enabled = True
        Me.tbToolBar.Buttons("Discon").Enabled = True
        Me.mnuMonitor.Enabled = True
        Me.tbToolBar.Buttons("Monitor").Enabled = True
        Me.mnuDebug = True
        Me.tbToolBar.Buttons("AD").Enabled = True
        Me.tbToolBar.Buttons("EV").Enabled = True
        Me.tbToolBar.Buttons("Refresh").Enabled = True
        Me.labCurXC = "当前连接：" & "端口=" & glPort & " / " & "波特率=" & glRealBt & " / " & _
                    "站号=" & glStaNo & " / " & "状态=" & "运行"
        Me.lvChannels.Visible = False
        Me.fgData.Visible = True
        Me.fgData.Clear
        Me.mnuNew.Enabled = False
        Me.mnuOpen.Enabled = False
        Me.mnuSave.Enabled = False
        Me.mnuEChl.Enabled = False
        Me.tbToolBar.Buttons("New").Enabled = False
        Me.tbToolBar.Buttons("Open").Enabled = False
        Me.tbToolBar.Buttons("Save").Enabled = False
        Me.tbToolBar.Buttons("EdCh").Enabled = False
    Case Else
        MsgBox "无法连接选定设备", vbOKOnly + vbCritical
    End Select
    Me.MousePointer = vbDefault
End Sub

Private Sub mnuDisConnect_Click()
    Me.labCurXC = "无连接"
    
    Me.mnuConnect.Enabled = True
    Me.tbToolBar.Buttons("Connect").Enabled = True
    
    Me.mnuSpecial.Enabled = True
    Me.mnuDisConnect.Enabled = False
    Me.tbToolBar.Buttons("Discon").Enabled = False
    Me.mnuMonitor.Enabled = False
    Me.tbToolBar.Buttons("Monitor").Enabled = False
    Me.mnuRun.Enabled = False
    Me.tbToolBar.Buttons("Run").Enabled = False
    Me.mnuDLCom.Enabled = False
    Me.tbToolBar.Buttons("DlCom").Enabled = False
    Me.mnuULCom.Enabled = False
    Me.tbToolBar.Buttons("UlCom").Enabled = False
    Me.mnuDLChn.Enabled = False
    Me.tbToolBar.Buttons("DlCh").Enabled = False
    Me.mnuULChn.Enabled = False
    Me.tbToolBar.Buttons("UlCh").Enabled = False
    Me.mnuDebug.Enabled = False
    Me.tbToolBar.Buttons("AD").Enabled = False
    Me.tbToolBar.Buttons("EV").Enabled = False
    Me.tbToolBar.Buttons("Refresh").Enabled = False
    
    Me.lvChannels.Visible = True
    Me.fgData.Visible = False
    Me.mnuNew.Enabled = True
    Me.mnuOpen.Enabled = True
    Me.mnuSave.Enabled = True
    Me.mnuEChl.Enabled = True
    Me.tbToolBar.Buttons("New").Enabled = True
    Me.tbToolBar.Buttons("Open").Enabled = True
    Me.tbToolBar.Buttons("Save").Enabled = True
    Me.tbToolBar.Buttons("EdCh").Enabled = True
End Sub

Private Sub mnuDLChn_Click()
    Dim retVal As VbMsgBoxResult
    retVal = MsgBox("下装通道参数将清除原有设置，是否继续", vbYesNo + vbQuestion)
    If retVal = vbNo Then Exit Sub
    
    '生成下装命令
    Dim j As Long
    Dim strCommand As String
    If glChNum < 16 Then
        strCommand = ":" & Format(glStaNo, "00") & "44" & "010" & Hex(glChNum)
    Else
        strCommand = ":" & Format(glStaNo, "00") & "44" & "01" & Hex(glChNum)
    End If
    For j = 1 To glChNum
        strCommand = strCommand & gaPara(j)
    Next j
    '给字符串加上LRC校验码和回车符
    AddLRCandCR strCommand
    gabCommand = StrConv(strCommand, vbFromUnicode)
    
    Dim lRetVal As Long
    lRetVal = 0
    
    If 1 = lock_port(glPort, 500) Then
        Dim retcode As Long
        retcode = write_port(glPort, gabCommand(0), UBound(gabCommand) - LBound(gabCommand) + 1, 1000)
        If retcode = 1 Then
            Me.Enabled = False
            Me.MousePointer = vbHourglass
            
            Sleep 2000  '等2秒
            lRetVal = 1024 * 8
            read_port glPort, gabRevBuffer(0), lRetVal, 100
            
            If lRetVal > 0 Then
                CheckMessage lRetVal
            End If
            
            Me.Enabled = True
            Me.MousePointer = vbDefault
        End If
        
        unlock_port glPort
    End If
        
errHandle:
    If lRetVal > 0 Then
        MsgBox "下装" & glStaNo & "成功", vbOKOnly + vbExclamation
    Else
        MsgBox "下装" & glStaNo & "失败，错误代码：" & lRetVal, vbOKOnly + vbCritical
    End If
End Sub

Private Sub mnuDLCom_Click()
    Dim retVal As VbMsgBoxResult
    retVal = MsgBox("下装公共参数将清除原有设置，是否继续", vbYesNo + vbQuestion)
    If retVal = vbNo Then Exit Sub
    
    Dim strSpeed As String
    If glSpeed = 1 Then
        strSpeed = "01"
    Else
        strSpeed = "00"
    End If
    Dim strBt As String
    Select Case glBt
    Case 4800
        strBt = "00"
    Case 9600
        strBt = "01"
    Case 19200
        strBt = "02"
    Case 57600
        strBt = "03"
    Case Else
        strBt = "00"
    End Select
    Dim strWsNo As String
    If glWsNo = 0 Then
        strWsNo = Format(glStaNo, "00")
    Else
        strWsNo = Format(glWsNo, "00")
    End If
    
    Dim strCommand As String
    strCommand = ":" & Trim(Format(glStaNo, "00")) & "46" & strSpeed & "000000000000" & Trim(Format(glTemperature, "00")) & strBt & strWsNo & "000000000000"
    AddLRCandCR strCommand
    
    gabCommand = StrConv(strCommand, vbFromUnicode)
    
    Dim lRetVal As Long
    lRetVal = 0
    
    If 1 = lock_port(glPort, 500) Then
        If 1 = write_port(glPort, gabCommand(0), UBound(gabCommand) - LBound(gabCommand) + 1, 500) Then
            Me.Enabled = False
            Me.MousePointer = vbHourglass
            
            Sleep 1000
            lRetVal = 1024 * 8
            read_port glPort, gabRevBuffer(0), lRetVal, 100
            
            If lRetVal > 0 Then
                CheckMessage lRetVal
            End If
            Me.Enabled = True
            Me.MousePointer = vbDefault
        End If
        
        unlock_port glPort
    End If
    
    If lRetVal > 0 Then
        MsgBox "下装" & glStaNo & "成功", vbOKOnly + vbExclamation
    Else
        MsgBox "下装" & glStaNo & "失败，错误代码：" & lRetVal, vbOKOnly + vbCritical
    End If
End Sub

Private Sub mnuEChl_Click()
    If Not Me.lvChannels.Visible Then Exit Sub
    
    If Not (Me.lvChannels.SelectedItem Is Nothing) Then
        formParameter.IniID = Me.lvChannels.SelectedItem.Index
    End If
    formParameter.Show vbModal
    ShowChPara
End Sub

Private Sub mnuECom_Click()
    formComPara.Show vbModal
    If formComPara.bCancel Then Exit Sub
    
    glBt = formComPara.lBt
    glTemperature = formComPara.lTemp
    glSpeed = formComPara.lSpeed
    glWsNo = formComPara.lStaNo
    ShowComPara
End Sub

Private Sub mnuExit_Click()
    Unload Me
End Sub

Private Sub mnuFine_Click()
    formFind.Show vbModal
    If formFind.Cancel Then Exit Sub
    
    glPort = formFind.PortNo
    glStaNo = formFind.StaNo
    glRealBt = formFind.Bt

    Me.MousePointer = vbHourglass
    Select Case GetXCStatus(glPort, glStaNo)
    Case 1
        Me.mnuSpecial.Enabled = False
        Me.mnuConnect.Enabled = False
        Me.tbToolBar.Buttons("Connect").Enabled = False
        Me.mnuSpecial.Enabled = False
        Me.mnuDisConnect.Enabled = True
        Me.tbToolBar.Buttons("Discon").Enabled = True
        Me.mnuRun.Enabled = True
        Me.tbToolBar.Buttons("Run").Enabled = True
        Me.mnuDLChn.Enabled = True
        Me.tbToolBar.Buttons("DlCh").Enabled = True
        Me.mnuDLCom.Enabled = True
        Me.tbToolBar.Buttons("DlCom").Enabled = True
        Me.mnuULChn.Enabled = True
        Me.tbToolBar.Buttons("UlCh").Enabled = True
        Me.mnuULCom.Enabled = True
        Me.tbToolBar.Buttons("UlCom").Enabled = True
        Me.labCurXC = "当前连接：" & "端口=" & glPort & " / " & "波特率=" & glRealBt & " / " & _
                    "站号=" & glStaNo & " / " & "状态=" & "监控"
        Me.lvChannels.Visible = True
        Me.fgData.Visible = False
        Me.mnuNew.Enabled = True
        Me.mnuOpen.Enabled = True
        Me.mnuSave.Enabled = True
        Me.mnuEChl.Enabled = True
        Me.tbToolBar.Buttons("New").Enabled = True
        Me.tbToolBar.Buttons("Open").Enabled = True
        Me.tbToolBar.Buttons("Save").Enabled = True
        Me.tbToolBar.Buttons("EdCh").Enabled = True
    Case 2
        Me.mnuSpecial.Enabled = False
        Me.mnuConnect.Enabled = False
        Me.tbToolBar.Buttons("Connect").Enabled = False
        Me.mnuDisConnect.Enabled = True
        Me.tbToolBar.Buttons("Discon").Enabled = True
        Me.mnuMonitor.Enabled = True
        Me.tbToolBar.Buttons("Monitor").Enabled = True
        Me.mnuDebug = True
        Me.tbToolBar.Buttons("AD").Enabled = True
        Me.tbToolBar.Buttons("EV").Enabled = True
        Me.tbToolBar.Buttons("Refresh").Enabled = True
        Me.labCurXC = "当前连接：" & "端口=" & glPort & " / " & "波特率=" & glRealBt & " / " & _
                    "站号=" & glStaNo & " / " & "状态=" & "运行"
        Me.lvChannels.Visible = False
        Me.fgData.Visible = True
        Me.fgData.Clear
        Me.mnuNew.Enabled = False
        Me.mnuOpen.Enabled = False
        Me.mnuSave.Enabled = False
        Me.mnuEChl.Enabled = False
        Me.tbToolBar.Buttons("New").Enabled = False
        Me.tbToolBar.Buttons("Open").Enabled = False
        Me.tbToolBar.Buttons("Save").Enabled = False
        Me.tbToolBar.Buttons("EdCh").Enabled = False
    Case Else
        MsgBox "无法连接选定设备", vbOKOnly + vbCritical
    End Select
    Me.MousePointer = vbDefault
End Sub

Private Sub mnuInitial_Click()
    formIniNo.Show vbModal
    
    If formIniNo.bCancel Then Exit Sub

    Dim strCommand As String
    strCommand = ":0047" & formIniNo.sSrNo & formIniNo.sWsNo
    '给字符串加上LRC校验码和回车符
    AddLRCandCR strCommand
    gabCommand = StrConv(strCommand, vbFromUnicode)
    
    If 1 = lock_port(glPort, 500) Then
        write_port glPort, gabCommand(0), UBound(gabCommand) - LBound(gabCommand) + 1, 200
        unlock_port glPort
    End If
    
End Sub

Private Sub mnuMonitor_Click()
    Dim strCommand As String
    strCommand = ":" & Format(glStaNo, "00") & "4001"
    
    '给字符串加上LRC校验码和回车符
    AddLRCandCR strCommand
    gabCommand = StrConv(strCommand, vbFromUnicode)
    
    Dim lRetVal As Long
    lRetVal = 0
    If 1 = lock_port(glPort, 500) Then
        If 1 = write_port(glPort, gabCommand(0), UBound(gabCommand) - LBound(gabCommand) + 1, 200) Then
            Me.Enabled = False
            Me.MousePointer = vbHourglass
            
            Sleep 500
            lRetVal = 1024 * 8
            read_port glPort, gabRevBuffer(0), lRetVal, 100
            
            If lRetVal > 0 Then
                CheckMessage lRetVal
            End If
            Me.Enabled = True
            Me.MousePointer = vbDefault
        End If
        
        unlock_port glPort
    End If
    
    If lRetVal <= 0 Then GoTo errHandle
    
    Me.mnuMonitor.Enabled = False
    Me.tbToolBar.Buttons("Monitor").Enabled = False
    Me.mnuRun.Enabled = True
    Me.tbToolBar.Buttons("Run").Enabled = True
    Me.mnuDebug.Enabled = False
    Me.tbToolBar.Buttons("AD").Enabled = False
    Me.tbToolBar.Buttons("EV").Enabled = False
    Me.tbToolBar.Buttons("Refresh").Enabled = False
    Me.mnuDLChn.Enabled = True
    Me.tbToolBar.Buttons("DlCh").Enabled = True
    Me.mnuDLCom.Enabled = True
    Me.tbToolBar.Buttons("DlCom").Enabled = True
    Me.mnuULChn.Enabled = True
    Me.tbToolBar.Buttons("UlCh").Enabled = True
    Me.mnuULCom.Enabled = True
    Me.tbToolBar.Buttons("UlCom").Enabled = True
errHandle:
    If lRetVal > 0 Then
        MsgBox "设备" & glStaNo & "已进入监控状态", vbOKOnly + vbExclamation
        Me.labCurXC = "当前连接：" & "端口=" & glPort & " / " & "波特率=" & glRealBt & " / " & _
                    "站号=" & glStaNo & " / " & "状态=" & "监控"
        Me.lvChannels.Visible = True
        Me.fgData.Visible = False
        Me.mnuNew.Enabled = True
        Me.mnuOpen.Enabled = True
        Me.mnuSave.Enabled = True
        Me.mnuEChl.Enabled = True
        Me.tbToolBar.Buttons("New").Enabled = True
        Me.tbToolBar.Buttons("Open").Enabled = True
        Me.tbToolBar.Buttons("Save").Enabled = True
        Me.tbToolBar.Buttons("EdCh").Enabled = True
    Else
        MsgBox "网络命令失败，错误代码：" & lRetVal, vbOKOnly + vbCritical
    End If
End Sub


Private Sub mnuNew_Click()
    'formNew.Show vbModal
    'If formNew.bCancel Then Exit Sub
    
    'Me.mnuEdit.Enabled = True
    
    'glBt = formNew.lBt
    'glTemperature = formNew.lTemp
    'glSpeed = formNew.lSpeed
    
    grdPara.MoveFirst
    Dim i As Long
    For i = 1 To glChNum
        '表示此通道关闭
        With grdPara
            .Fields("Used") = False
            '.Update
        End With
        grdPara.MoveNext
        'gaPara(i) = String(32, "0")
        'Mid(gaPara(i), 1, 1) = "8"
        'gParaInfo(i).Used = False
    Next i
    
    'ShowComPara
    ShowChPara
End Sub

Private Sub mnuOpen_Click()
    On Error GoTo errHandle
    Me.cdlgFile.ShowOpen
    Open Me.cdlgFile.FileName For Input As #1
    Dim strTemp As String
    '读公共参数
    Input #1, strTemp
    'If strTemp <> "[common]" Then
    'End If
    Input #1, glBt, glTemperature, glSpeed
    '读通道参数
    Input #1, strTemp
    'If strTemp <> "[channel]" Then
    'End If
    Dim bUsed As Boolean
    Dim iChannelType As Integer
    Dim iSensorType As Integer
    Dim iCompType As Integer
    Dim fCompResistance As Single
    Dim iCompChannel As Integer
    Dim bUseDefault As Boolean
    Dim fA As Single
    Dim fB As Single
    Dim fMinValue As Single
    Dim fMaxValue As Single
    Dim iCalculate2 As Integer
    Dim i As Long
    grdPara.MoveFirst
    For i = 1 To glChNum
        Input #1, bUsed, iChannelType, iSensorType, iCompType, _
                fCompResistance, iCompChannel, bUseDefault, _
                fA, fB, fMinValue, fMaxValue, iCalculate2
        With grdPara
            .Fields("Used") = bUsed
            'section 2
            .Fields("ChannelType") = iChannelType
            Select Case iChannelType
            Case 1  '热电阻
                .Fields("CompResistance") = fCompResistance
            Case 2  '热电偶
                .Fields("CompType") = iCompType
                If iCompType = 1 Then       '恒温箱补偿
                ElseIf iCompType = 2 Then   '冷端补偿
                    .Fields("CompChannel") = iCompChannel
                End If
            Case 3  '传感器
            End Select
            .Fields("SensorType") = iSensorType
            .Fields("UseDefault") = bUseDefault
            If bUseDefault Then
                'section 1
                .Fields("MinValue") = fMinValue
                .Fields("MaxValue") = fMaxValue
            End If
            .Fields("A") = fA
            .Fields("B") = fB
            .Fields("Calculate2") = iCalculate2
            .Update
            .MoveNext
        End With
    Next i
    Close #1
    ShowComPara
    ShowChPara
    Me.mnuEdit.Enabled = True
errHandle:
End Sub

Private Sub mnuReadRAW_Click()
    glRefresh = 1
    
    Dim strCommand As String
    strCommand = ":" & Format(glStaNo, "00") & "41" & "01" & "3C"
    
    '给字符串加上LRC校验码和回车符
    AddLRCandCR strCommand
    gabCommand = StrConv(strCommand, vbFromUnicode)
        
    Dim lRetVal As Long
    lRetVal = 0
    
    If 1 = lock_port(glPort, 500) Then
        If 1 = write_port(glPort, gabCommand(0), UBound(gabCommand) - LBound(gabCommand) + 1, 200) Then
            Me.Enabled = False
            Me.MousePointer = vbHourglass
            
            'Sleep 200 * (57600 \ glRealBt)
            Sleep 200
            lRetVal = 1024 * 8
            read_port glPort, gabRevBuffer(0), lRetVal, 100
            
            If lRetVal > 0 Then
                CheckMessage lRetVal
            End If
            Me.Enabled = True
            Me.MousePointer = vbDefault
        End If
        
        unlock_port glPort
    End If
    
errHandle:
    If lRetVal <= 0 Then
        MsgBox "通讯失败,无法获取通道数据", vbOKOnly + vbExclamation
    Else
        ShowRaw
    End If
End Sub

Private Sub mnuReadValue_Click()
    glRefresh = 0
    
    Dim strCommand As String
    strCommand = ":" & Format(glStaNo, "00") & "42" & "01" & "3C"
    
    '给字符串加上LRC校验码和回车符
    AddLRCandCR strCommand
    gabCommand = StrConv(strCommand, vbFromUnicode)
        
    Dim lRetVal As Long
    lRetVal = 0
    
    If 1 = lock_port(glPort, 500) Then
        If 1 = write_port(glPort, gabCommand(0), UBound(gabCommand) - LBound(gabCommand) + 1, 200) Then
            Me.Enabled = False
            Me.MousePointer = vbHourglass
            
            'Sleep 200 * (57600 \ glRealBt)
            Sleep 200
            lRetVal = 1024 * 8
            read_port glPort, gabRevBuffer(0), lRetVal, 100
            
            If lRetVal > 0 Then
                CheckMessage lRetVal
            End If
            Me.Enabled = True
            Me.MousePointer = vbDefault
        End If
        
        unlock_port glPort
    End If
    
errHandle:
    If lRetVal <= 0 Then
        MsgBox "通讯失败,无法获取通道数据", vbOKOnly + vbCritical
    Else
        ShowValue
    End If
End Sub

Private Sub mnuRun_Click()
    Dim strCommand As String
    strCommand = ":" & Format(glStaNo, "00") & "4000"
    
    '给字符串加上LRC校验码和回车符
    AddLRCandCR strCommand
    gabCommand = StrConv(strCommand, vbFromUnicode)
    
    Dim lRetVal As Long
    lRetVal = 0
    If 1 = lock_port(glPort, 500) Then
        If 1 = write_port(glPort, gabCommand(0), UBound(gabCommand) - LBound(gabCommand) + 1, 200) Then
            Me.Enabled = False
            Me.MousePointer = vbHourglass
            
            Sleep 1000
            lRetVal = 1024 * 8
            read_port glPort, gabRevBuffer(0), lRetVal, 100
            
            If lRetVal > 0 Then
                CheckMessage lRetVal
            End If
            Me.Enabled = True
            Me.MousePointer = vbDefault
        End If
        
        unlock_port glPort
    End If
    
    If lRetVal <= 0 Then GoTo errHandle
    
    Me.mnuMonitor.Enabled = True
    Me.tbToolBar.Buttons("Monitor").Enabled = True
    Me.mnuRun.Enabled = False
    Me.tbToolBar.Buttons("Run").Enabled = False
    Me.mnuDebug.Enabled = True
    Me.tbToolBar.Buttons("AD").Enabled = True
    Me.tbToolBar.Buttons("EV").Enabled = True
    Me.tbToolBar.Buttons("Refresh").Enabled = True
    Me.mnuDLChn.Enabled = False
    Me.tbToolBar.Buttons("DlCh").Enabled = False
    Me.mnuDLCom.Enabled = False
    Me.tbToolBar.Buttons("DlCom").Enabled = False
    Me.mnuULChn.Enabled = False
    Me.tbToolBar.Buttons("UlCh").Enabled = False
    Me.mnuULCom.Enabled = False
    Me.tbToolBar.Buttons("UlCom").Enabled = False
errHandle:
    If lRetVal > 0 Then
        MsgBox "设备" & glStaNo & "已进入运行状态", vbOKOnly + vbExclamation
        Me.labCurXC = "当前连接：" & "端口=" & glPort & " / " & "波特率=" & glRealBt & " / " & _
                    "站号=" & glStaNo & " / " & "状态=" & "运行"
        Me.lvChannels.Visible = False
        Me.fgData.Visible = True
        Me.fgData.Clear
        Me.mnuNew.Enabled = False
        Me.mnuOpen.Enabled = False
        Me.mnuSave.Enabled = False
        Me.mnuEChl.Enabled = False
        Me.tbToolBar.Buttons("New").Enabled = False
        Me.tbToolBar.Buttons("Open").Enabled = False
        Me.tbToolBar.Buttons("Save").Enabled = False
        Me.tbToolBar.Buttons("EdCh").Enabled = False
    Else
        MsgBox "网络命令失败，错误代码：" & lRetVal, vbOKOnly + vbCritical
    End If
End Sub

Private Sub mnuSave_Click()
    On Error GoTo errHandle
    Me.cdlgFile.ShowSave
    If Dir(Me.cdlgFile.FileName) <> "" Then
        Dim retVal As VbMsgBoxResult
        retVal = MsgBox("是否覆盖已有文件<" & Me.cdlgFile.FileName & ">", vbYesNo + vbQuestion)
        If retVal = vbNo Then
            Exit Sub
        End If
    End If
    Open Me.cdlgFile.FileName For Output As #1
    '写公共参数
    Write #1, "[common]"
    Write #1, glBt, glTemperature, glSpeed
    '写通道参数
    Write #1, "[channel]"
    Dim bUsed As Boolean
    Dim iChannelType As Integer
    Dim iSensorType As Integer
    Dim iCompType As Integer
    Dim fCompResistance As Single
    Dim iCompChannel As Integer
    Dim bUseDefault As Boolean
    Dim fA As Single
    Dim fB As Single
    Dim fMinValue As Single
    Dim fMaxValue As Single
    Dim iCalculate2 As Integer
    Dim i As Long
    grdPara.MoveFirst
    For i = 1 To glChNum
        With grdPara
            bUsed = .Fields("Used")
            If bUsed Then
                'section 2
                iChannelType = .Fields("ChannelType")
                Select Case iChannelType
                Case 1  '热电阻
                    fCompResistance = .Fields("CompResistance")
                Case 2  '热电偶
                    iCompType = .Fields("CompType")
                    If iCompType = 1 Then       '恒温箱补偿
                    ElseIf iCompType = 2 Then   '冷端补偿
                        iCompChannel = .Fields("CompChannel")
                    End If
                Case 3  '传感器
                End Select
                iSensorType = .Fields("SensorType")
                bUseDefault = .Fields("UseDefault")
                If bUseDefault Then
                    'section 1
                    fMinValue = .Fields("MinValue")
                    fMaxValue = .Fields("MaxValue")
                End If
                fA = .Fields("A")
                fB = .Fields("B")
                iCalculate2 = .Fields("Calculate2")
            End If
            .MoveNext
        End With
        Write #1, bUsed, iChannelType, iSensorType, iCompType, _
                fCompResistance, iCompChannel, bUseDefault, _
                fA, fB, fMinValue, fMaxValue, iCalculate2
    Next i
    Close #1
errHandle:
End Sub

'获取巡测状态
'0-出错 1-监控 2-运行
Private Function GetXCStatus(PortNo, XCNo) As Integer
    Dim strCommand As String
    strCommand = ":" & Format(XCNo, "00") & "3F"
    
    '给字符串加上LRC校验码和回车符
    AddLRCandCR strCommand
    gabCommand = StrConv(strCommand, vbFromUnicode)

    GetXCStatus = 0
    
    If lock_port(PortNo, 500) = 1 Then
        If 1 = write_port(PortNo, gabCommand(0), UBound(gabCommand) - LBound(gabCommand) + 1, 200) Then
        
            Sleep 500
            
            Dim lRetVal As Long
            lRetVal = 1024 * 8
            read_port PortNo, gabRevBuffer(0), lRetVal, 100
            If lRetVal > 0 Then
                If CheckMessage(lRetVal) Then
                    If gabRevBuffer(6) = Asc("0") Then
                        GetXCStatus = 2
                    Else
                        GetXCStatus = 1
                    End If
                End If
            End If
        End If
        
        unlock_port PortNo
    End If
End Function

Private Sub ShowChPara()
    glShowMode = xcfgConfig
    
    Me.lvChannels.ListItems.Clear
    Me.lvChannels.ColumnHeaders.Clear
    Dim itmX As ListItem
    Dim i As Long
        
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
        
    grdPara.MoveFirst
    Do Until grdPara.EOF
        SetChPara
        grdPara.MoveNext
    Loop
    
    For i = 1 To glChNum
        Set itmX = Me.lvChannels.ListItems.Add(, , "Ch:" & Format(i, "00"))
        If gParaInfo(i).Used Then
            itmX.SubItems(1) = gParaInfo(i).ChannelType
            itmX.SubItems(2) = gParaInfo(i).SensorType
            itmX.SubItems(3) = gParaInfo(i).CompType
            itmX.SubItems(4) = gParaInfo(i).CompNo
            itmX.SubItems(5) = gParaInfo(i).CompResistance
            itmX.SubItems(6) = gParaInfo(i).A
            itmX.SubItems(7) = gParaInfo(i).B
            itmX.SubItems(8) = gParaInfo(i).Calculate2
        End If
    Next i
End Sub

Private Sub ShowComPara()
    If glWsNo > 0 And glWsNo < 100 Then
        If glSpeed = 1 Then
            Me.labComPara = "公共参数：" & "站号=" & glWsNo & " / " & "波特率=" & glBt & " / " & "恒温箱温度=" & glTemperature & " / " & "降速运行"
        Else
            Me.labComPara = "公共参数：" & "站号=" & glWsNo & " / " & "波特率=" & glBt & " / " & "恒温箱温度=" & glTemperature & " / " & "正常速运行"
        End If
    Else
        If glSpeed = 1 Then
            Me.labComPara = "公共参数：" & "站号=未指定" & " / " & "波特率=" & glBt & " / " & "恒温箱温度=" & glTemperature & " / " & "降速运行"
        Else
            Me.labComPara = "公共参数：" & "站号=未指定" & " / " & "波特率=" & glBt & " / " & "恒温箱温度=" & glTemperature & " / " & "正常速运行"
        End If
    End If
End Sub

Private Sub mnuULChn_Click()
    Dim strCommand As String
    'strCommand = ":" & Format(glStaNo, "00") & "43" & "01" & "1D"
    strCommand = ":" & Format(glStaNo, "00") & "43" & "01" & "3C"
    
    '给字符串加上LRC校验码和回车符
    AddLRCandCR strCommand
    gabCommand = StrConv(strCommand, vbFromUnicode)
        
    Dim lRetVal As Long
    lRetVal = 0
    
    If 1 = lock_port(glPort, 500) Then
        If 1 = write_port(glPort, gabCommand(0), UBound(gabCommand) - LBound(gabCommand) + 1, 200) Then
            Me.Enabled = False
            Me.MousePointer = vbHourglass
            
            Sleep 1000 * (57600 \ glRealBt)
            lRetVal = 1024 * 8
            read_port glPort, gabRevBuffer(0), lRetVal, 100
            If lRetVal > 0 Then
                CheckMessage lRetVal
            End If
            Me.Enabled = True
            Me.MousePointer = vbDefault
        End If
        
        unlock_port glPort
    End If
    
    If lRetVal <= 0 Then
        MsgBox "无法获取通道参数", vbOKOnly + vbExclamation, "通讯失败"
    Else
        GetXCInfoFromBuffer
        ShowChPara
    End If
End Sub

Private Sub GetXCInfoFromBuffer()
    Dim bUsed As Boolean
    Dim iChannelNo As Integer
    Dim iChannelType As Integer
    Dim iSensorType As Integer
    Dim iCompChannel As Integer
    Dim iCompType As Integer
    Dim fCompResistance As Single
    Dim iCalculate2 As Integer
    Dim bUseDefault As Boolean
    Dim fA As Single
    Dim fB As Single
    
    grdPara.MoveFirst
    Dim abTemp(0 To 31) As Byte
    For iChannelNo = 1 To 60
        CopyMemory abTemp(0), gabRevBuffer(5 + (iChannelNo - 1) * 32), 32
        gaPara(iChannelNo) = StrConv(abTemp, vbUnicode)
        If Mid(gaPara(iChannelNo), 1, 1) = "8" Then
            bUsed = False
        Else
            bUsed = True
        End If
        iSensorType = Val(Mid(gaPara(iChannelNo), 1, 2))
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
            fCompResistance = Val(Mid(gaPara(iChannelNo), 11, 2)) / 10#
        Case 2  '热电偶
            iCompChannel = Val(Mid(gaPara(iChannelNo), 11, 2))
            If iCompChannel = 0 Then
                iCompType = 1   '恒温箱
            Else
                iCompType = 2   '冷端补偿
            End If
        Case 3  '传感器
        End Select
        iCalculate2 = Val(Mid(gaPara(iChannelNo), 13, 2))
        If Mid(gaPara(iChannelNo), 9, 2) = "00" Then
            bUseDefault = True
        Else
            bUseDefault = False
        End If
        fA = YTStringtoSingle(Mid(gaPara(iChannelNo), 15, 6))
        fB = YTStringtoSingle(Mid(gaPara(iChannelNo), 21, 6))
        With grdPara
            .Fields("Used") = bUsed
            .Fields("ChannelType") = iChannelType
            .Fields("SensorType") = iSensorType
            .Fields("CompType") = iCompType
            .Fields("CompChannel") = iCompChannel
            .Fields("Compresistance") = fCompResistance
            .Fields("A") = fA
            .Fields("B") = fB
            .Fields("Calculate2") = iCalculate2
            .Fields("UseDefault") = bUseDefault
            If bUseDefault And iChannelType = 3 Then
                Dim fMinRaw As Single
                Dim fMaxRaw As Single
                Select Case iSensorType
                Case 9
                    fMinRaw = 0#
                    fMaxRaw = 5000#
                Case 10
                    fMinRaw = 1000#
                    fMaxRaw = 5000#
                Case 11
                    fMinRaw = 0#
                    fMaxRaw = 5000#
                Case 12
                    fMinRaw = 1000#
                    fMaxRaw = 5000#
                Case 13
                    fMinRaw = 0#
                    fMaxRaw = 10000#
                End Select
                .Fields("MinValue") = fA * fMinRaw + fB
                .Fields("MaxValue") = fA * fMaxRaw + fB
            End If
            .MoveNext
        End With
        Debug.Print iChannelNo, gaPara(iChannelNo)
    Next iChannelNo
End Sub

Private Sub mnuULCom_Click()
    Dim strCommand As String
    strCommand = ":" & Trim(Format(glStaNo, "00")) & "45"
    
    '给字符串加上LRC校验码和回车符
    AddLRCandCR strCommand
    gabCommand = StrConv(strCommand, vbFromUnicode)
        
    Dim lRetVal As Long
    lRetVal = 0
    If 1 = lock_port(glPort, 500) Then
        If 1 = write_port(glPort, gabCommand(0), UBound(gabCommand) - LBound(gabCommand) + 1, 200) Then
            Me.Enabled = False
            Me.MousePointer = vbHourglass
            
            Sleep 1000
            lRetVal = 1024 * 8
            read_port glPort, gabRevBuffer(0), lRetVal, 100
            
            If lRetVal > 0 Then
                CheckMessage lRetVal
            End If
            Me.Enabled = True
            Me.MousePointer = vbDefault
        End If
        
        unlock_port glPort
    End If
    
errHandle:
    If lRetVal <= 0 Then
        MsgBox "无法获取通道参数", vbOKOnly + vbExclamation, "通讯失败"
    Else
        
    Dim abTemp(0 To 31) As Byte
    Dim strComPara As String
    CopyMemory abTemp(0), gabRevBuffer(5), 32
    strComPara = StrConv(abTemp, vbUnicode)
    glSpeed = Val(Mid(strComPara, 1, 2))
    glTemperature = Val(Mid(strComPara, 15, 2))
    Select Case Mid(strComPara, 17, 2)
    Case "01"
        glBt = 9600
    Case "02"
        glBt = 19200
    Case "03"
        glBt = 57600
    Case Else
        glBt = 4800
    End Select
    glWsNo = Val(Mid(strComPara, 19, 2))
    ShowComPara
    End If
End Sub

Public Sub ShowValue()
    glShowMode = xcfgRun
    
    Dim fValue(1 To 60) As Single
    
    Dim strValue As String * 6
    Dim abTemp(0 To 5) As Byte
    Dim i As Long, j As Long
    For i = 1 To 60
        CopyMemory abTemp(0), gabRevBuffer(5 + (i - 1) * 6), 6
        strValue = StrConv(abTemp, vbUnicode)
        fValue(i) = YTStringtoSingle(strValue)
    Next i

    For i = 0 To 7
        If i Mod 2 = 0 Then
            Me.fgData.TextMatrix(0, i) = "通道"
        Else
            Me.fgData.TextMatrix(0, i) = "工程值"
        End If
        For j = 1 To 15
            If i Mod 2 = 0 Then
                Me.fgData.TextMatrix(j, i) = "CH:" & Format(j + (i \ 2) * 15, "00")
            Else
                If fValue(j + (i \ 2) * 15) < -999998 Then
                    Me.fgData.TextMatrix(j, i) = "N/A"
                Else
                    Me.fgData.TextMatrix(j, i) = fValue(j + (i \ 2) * 15)
                End If
                Debug.Print j + (i \ 2) * 15, fValue(j + (i \ 2) * 15)
            End If
        Next j
    Next i
    
End Sub

Private Sub ShowRaw()
    glShowMode = xcfgRun

    Dim sRaw(1 To 60) As String * 4

    Dim abTemp(0 To 3) As Byte
    Dim i As Long, j As Long
    For i = 1 To 60
        CopyMemory abTemp(0), gabRevBuffer(5 + (i - 1) * 4), 4
        sRaw(i) = StrConv(abTemp, vbUnicode)
    Next i

    'Me.fgData.Clear
    For i = 0 To 7
        If i Mod 2 = 0 Then
            Me.fgData.TextMatrix(0, i) = "通道"
        Else
            Me.fgData.TextMatrix(0, i) = "A/D值"
        End If
        For j = 1 To 15
            If i Mod 2 = 0 Then
                Me.fgData.TextMatrix(j, i) = "CH:" & Format(j + (i \ 2) * 15, "00")
            Else
                Me.fgData.TextMatrix(j, i) = sRaw(j + (i \ 2) * 15) & "H"
            End If
        Next j
    Next i
End Sub

Private Sub tbToolBar_ButtonClick(ByVal Button As MSComctlLib.Button)
    Select Case Button.Key
    Case "New"
        mnuNew_Click
    Case "Open"
        mnuOpen_Click
    Case "Save"
        mnuSave_Click
    Case "EdCom"
        mnuECom_Click
    Case "EdCh"
        mnuEChl_Click
    Case "Connect"
        mnuConnect_Click
    Case "Discon"
        mnuDisConnect_Click
    Case "Monitor"
        mnuMonitor_Click
    Case "Run"
        mnuRun_Click
    Case "DlCom"
        mnuDLCom_Click
    Case "UlCom"
        mnuULCom_Click
    Case "DlCh"
        mnuDLChn_Click
    Case "UlCh"
        mnuULChn_Click
    Case "AD"
        mnuReadRAW_Click
    Case "EV"
        mnuReadValue_Click
    Case "Refresh"
        mnuAutoRefresh_Click
    End Select
End Sub

Private Sub timerRefresh_Timer()
    If glRefresh = 1 Then
        mnuReadRAW_Click
    Else
        mnuReadValue_Click
    End If
End Sub


