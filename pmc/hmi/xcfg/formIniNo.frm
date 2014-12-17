VERSION 5.00
Begin VB.Form formIniNo 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "初始化站号"
   ClientHeight    =   2145
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   2955
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2145
   ScaleWidth      =   2955
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.ComboBox cmbBt 
      Enabled         =   0   'False
      Height          =   315
      ItemData        =   "formIniNo.frx":0000
      Left            =   1290
      List            =   "formIniNo.frx":0010
      Style           =   2  'Dropdown List
      TabIndex        =   1
      Top             =   450
      Width           =   1320
   End
   Begin VB.ComboBox cmbPort 
      Height          =   315
      Left            =   1290
      Style           =   2  'Dropdown List
      TabIndex        =   0
      Top             =   120
      Width           =   1320
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "取消"
      Height          =   312
      Left            =   1740
      TabIndex        =   5
      Top             =   1650
      Width           =   852
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "确定"
      Default         =   -1  'True
      Height          =   312
      Left            =   540
      TabIndex        =   4
      Top             =   1650
      Width           =   852
   End
   Begin VB.TextBox txtWsNo 
      Height          =   330
      Left            =   1290
      MaxLength       =   2
      TabIndex        =   3
      Top             =   1140
      Width           =   1320
   End
   Begin VB.TextBox txtSrNo 
      Height          =   330
      Left            =   1290
      MaxLength       =   4
      TabIndex        =   2
      Top             =   810
      Width           =   1320
   End
   Begin VB.Label Label2 
      Alignment       =   1  'Right Justify
      Caption         =   "波特率"
      Height          =   255
      Left            =   30
      TabIndex        =   9
      Top             =   510
      Width           =   1215
   End
   Begin VB.Label LabelChooseInterface 
      Alignment       =   1  'Right Justify
      Caption         =   "选择端口"
      Height          =   255
      Left            =   240
      TabIndex        =   8
      Top             =   180
      Width           =   1005
   End
   Begin VB.Label labWsNo 
      Alignment       =   1  'Right Justify
      Caption         =   "站号"
      Height          =   225
      Left            =   540
      TabIndex        =   7
      Top             =   1230
      Width           =   705
   End
   Begin VB.Label labSrNo 
      Alignment       =   1  'Right Justify
      Caption         =   "序列号"
      Height          =   225
      Left            =   570
      TabIndex        =   6
      Top             =   870
      Width           =   675
   End
End
Attribute VB_Name = "formIniNo"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public PortNo As Long
Public bCancel As Boolean
Public sSrNo As String
Public sWsNo As String
Public Bt As Long

Private Sub cmdCancel_Click()
    bCancel = True
    Unload Me
End Sub

Private Sub cmdOK_Click()
    If Me.cmbPort.Text = Empty Then
        MsgBox "未指定端口号", vbOKOnly + vbExclamation
        Exit Sub
    Else
        PortNo = Val(Me.cmbPort.Text)
    End If
    If Me.cmbBt.Text = Empty Then
        MsgBox "未指定波特率", vbOKOnly + vbExclamation
        Exit Sub
    Else
        Bt = Val(Me.cmbBt.Text)
    End If
    If Len(Me.txtSrNo) = 4 Then
        sSrNo = Me.txtSrNo
    Else
        MsgBox "参数错误，序列号不足4位", vbOKOnly + vbCritical
        Exit Sub
    End If
    If Len(Me.txtWsNo) = Empty Then
        MsgBox "参数错误，未指定站号", vbOKOnly + vbCritical
        Exit Sub
    ElseIf Val(Me.txtWsNo) = 0 Then
        MsgBox "参数错误，站号必须为1-99", vbOKOnly + vbCritical
        Exit Sub
    End If
    sWsNo = Format(Val(Me.txtWsNo), "00")
    
    bCancel = False
    Unload Me
End Sub

Private Sub Form_Load()
    Dim i As Long
    For i = 1 To 16
        Me.cmbPort.AddItem CStr(i)
    Next i
    
    Me.cmbBt.ListIndex = 3
End Sub

Private Sub txtSrNo_KeyPress(KeyAscii As Integer)
    '退格
    If KeyAscii = vbKeyBack Then
    '下划线
    'ElseIf KeyAscii = 95 Then
    '数字
    ElseIf KeyAscii >= vbKey0 And KeyAscii <= vbKey9 Then
    '英文字符
    'ElseIf KeyAscii >= vbKeyA And KeyAscii <= vbKeyZ Then   '大写
    'ElseIf KeyAscii >= 97 And KeyAscii <= 122 Then          '小写
    Else
        KeyAscii = 0
    End If
End Sub

Private Sub txtWsNo_KeyPress(KeyAscii As Integer)
    '退格
    If KeyAscii = vbKeyBack Then
    '下划线
    'ElseIf KeyAscii = 95 Then
    '数字
    ElseIf KeyAscii >= vbKey0 And KeyAscii <= vbKey9 Then
    '英文字符
    'ElseIf KeyAscii >= vbKeyA And KeyAscii <= vbKeyZ Then   '大写
    'ElseIf KeyAscii >= 97 And KeyAscii <= 122 Then          '小写
    Else
        KeyAscii = 0
    End If
End Sub
