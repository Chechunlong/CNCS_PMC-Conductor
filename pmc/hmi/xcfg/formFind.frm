VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form formFind 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "扫描当前连接"
   ClientHeight    =   4080
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   6840
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4080
   ScaleWidth      =   6840
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton cmdConnect 
      Caption         =   "连接(&L)"
      Enabled         =   0   'False
      Height          =   315
      Left            =   5370
      TabIndex        =   4
      Top             =   2640
      Width           =   1305
   End
   Begin VB.CommandButton cmdStop 
      Caption         =   "停止(&T)"
      Enabled         =   0   'False
      Height          =   315
      Left            =   5370
      TabIndex        =   3
      Top             =   2220
      Width           =   1305
   End
   Begin MSComctlLib.ListView lvFind 
      Height          =   3615
      Left            =   60
      TabIndex        =   6
      Top             =   60
      Width           =   5115
      _ExtentX        =   9022
      _ExtentY        =   6376
      View            =   3
      LabelEdit       =   1
      LabelWrap       =   0   'False
      HideSelection   =   0   'False
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   4
      BeginProperty ColumnHeader(1) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         Text            =   "端口"
         Object.Width           =   1235
      EndProperty
      BeginProperty ColumnHeader(2) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   1
         Text            =   "站号"
         Object.Width           =   1235
      EndProperty
      BeginProperty ColumnHeader(3) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   2
         Text            =   "波特率"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(4) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   3
         Text            =   "状态"
         Object.Width           =   2540
      EndProperty
   End
   Begin MSComctlLib.StatusBar sbStatus 
      Align           =   2  'Align Bottom
      Height          =   345
      Left            =   0
      TabIndex        =   9
      Top             =   3735
      Width           =   6840
      _ExtentX        =   12065
      _ExtentY        =   609
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   1
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   1
            Object.Width           =   12012
         EndProperty
      EndProperty
   End
   Begin VB.ComboBox cmbPort 
      Height          =   315
      ItemData        =   "formFind.frx":0000
      Left            =   5370
      List            =   "formFind.frx":0034
      Style           =   2  'Dropdown List
      TabIndex        =   0
      Top             =   450
      Width           =   1305
   End
   Begin VB.ComboBox cmbBt 
      Enabled         =   0   'False
      Height          =   315
      ItemData        =   "formFind.frx":006F
      Left            =   5370
      List            =   "formFind.frx":0082
      Style           =   2  'Dropdown List
      TabIndex        =   1
      Top             =   1260
      Width           =   1305
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "关闭(&C)"
      Height          =   315
      Left            =   5370
      TabIndex        =   5
      Top             =   3240
      Width           =   1305
   End
   Begin VB.CommandButton cmdScan 
      Caption         =   "扫描(&S)"
      Height          =   315
      Left            =   5370
      TabIndex        =   2
      Top             =   1800
      Width           =   1305
   End
   Begin VB.Label LabelChooseInterface 
      Caption         =   "选择端口"
      Height          =   315
      Left            =   5370
      TabIndex        =   8
      Top             =   180
      Width           =   1305
   End
   Begin VB.Label Label2 
      Caption         =   "波特率"
      Enabled         =   0   'False
      Height          =   315
      Left            =   5370
      TabIndex        =   7
      Top             =   990
      Width           =   1305
   End
End
Attribute VB_Name = "formFind"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim bStop As Boolean
Public Cancel As Boolean
Public PortNo As Long
Public Bt As Long
Public StaNo As Long

Private Sub cmdConnect_Click()
    Cancel = False
    Unload Me
End Sub

Private Sub cmdExit_Click()
    Cancel = True
    Unload Me
End Sub

Private Sub cmdScan_Click()
    bStop = False
    Me.cmdScan.Enabled = False
    Me.cmdStop.Enabled = True
    Me.cmdExit.Enabled = False
    Me.cmdConnect.Enabled = False
    
    Me.lvFind.ListItems.Clear
    
    Dim lPort As Long
    lPort = Val(Me.cmbPort.Text)
    
    Dim i As Long
    Dim itmX As ListItem
    
    For i = 1 To 99
        Select Case GetXCStatus(lPort, i)
        Case 0
        Case 1
            Set itmX = Me.lvFind.ListItems.Add(, , CStr(lPort))
            itmX.SubItems(1) = CStr(i)
            itmX.SubItems(2) = Me.cmbBt.Text
            itmX.SubItems(3) = "运行"
        Case 2
            Set itmX = Me.lvFind.ListItems.Add(, , CStr(lPort))
            itmX.SubItems(1) = CStr(i)
            itmX.SubItems(2) = Me.cmbBt.Text
            itmX.SubItems(3) = "监控"
        End Select
        Me.sbStatus.Panels(1).Text = "波特率:" & Me.cmbBt.Text & "    " & "站号:" & i
        DoEvents
        If bStop Then GoTo StopFind
    Next i
    
StopFind:
    Me.sbStatus.Panels(1).Text = ""
    Me.cmdScan.Enabled = True
    Me.cmdStop.Enabled = False
    Me.cmdExit.Enabled = True
End Sub

Private Sub cmdStop_Click()
    bStop = True
    Me.cmdExit.Enabled = True
End Sub

Private Sub Form_Load()
    Me.cmbBt.ListIndex = 4
    Me.cmbPort.ListIndex = 0
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
        
            Sleep 50
            
            Dim lRetVal As Long
            lRetVal = 1024 * 8
            read_port PortNo, gabRevBuffer(0), lRetVal, 100
            If lRetVal > 0 Then
                If CheckMessage(lRetVal) Then
                    If gabRevBuffer(6) = Asc("0") Then
                        GetXCStatus = 1
                    Else
                        GetXCStatus = 2
                    End If
                End If
            End If
        End If
        
        unlock_port PortNo
    End If
End Function

Private Sub lvFind_ItemClick(ByVal Item As MSComctlLib.ListItem)
    If Not Me.lvFind.SelectedItem Is Nothing Then
        PortNo = Val((Me.lvFind.SelectedItem.Text))
        StaNo = Val(Me.lvFind.SelectedItem.SubItems(1))
        Bt = Val(Me.lvFind.SelectedItem.SubItems(2))
        Me.cmdConnect.Enabled = True
    Else
        Me.cmdConnect.Enabled = False
    End If
End Sub
