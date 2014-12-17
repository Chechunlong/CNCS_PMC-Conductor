VERSION 5.00
Begin VB.Form formComPara 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "公共参数"
   ClientHeight    =   2490
   ClientLeft      =   30
   ClientTop       =   330
   ClientWidth     =   3285
   ControlBox      =   0   'False
   BeginProperty Font 
      Name            =   "Arial"
      Size            =   10.5
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "formComPara.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2490
   ScaleWidth      =   3285
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton cmdOK 
      Caption         =   "确定"
      Default         =   -1  'True
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   312
      Left            =   570
      TabIndex        =   3
      Top             =   2070
      Width           =   852
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "取消"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   312
      Left            =   1770
      TabIndex        =   4
      Top             =   2070
      Width           =   852
   End
   Begin VB.Frame frmComPar 
      Caption         =   "指定公共参数"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1875
      Left            =   120
      TabIndex        =   5
      Top             =   60
      Width           =   3012
      Begin VB.ComboBox cmbSpeed 
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   315
         ItemData        =   "formComPara.frx":000C
         Left            =   1380
         List            =   "formComPara.frx":0016
         Style           =   2  'Dropdown List
         TabIndex        =   10
         Top             =   1320
         Width           =   1332
      End
      Begin VB.ComboBox cmbXC 
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   315
         Left            =   1380
         Style           =   2  'Dropdown List
         TabIndex        =   2
         Top             =   210
         Width           =   1332
      End
      Begin VB.ComboBox cmbBt 
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   315
         ItemData        =   "formComPara.frx":0026
         Left            =   1380
         List            =   "formComPara.frx":0036
         Style           =   2  'Dropdown List
         TabIndex        =   1
         Top             =   960
         Width           =   1332
      End
      Begin VB.TextBox txtTemperature 
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   360
         Left            =   1380
         MaxLength       =   2
         TabIndex        =   0
         Top             =   570
         Width           =   1332
      End
      Begin VB.Label Label4 
         Alignment       =   1  'Right Justify
         Caption         =   "采集速度"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   120
         TabIndex        =   9
         Top             =   1410
         Width           =   1215
      End
      Begin VB.Label Label1 
         Alignment       =   1  'Right Justify
         Caption         =   "站号"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   120
         TabIndex        =   8
         Top             =   300
         Width           =   1215
      End
      Begin VB.Label Label3 
         Alignment       =   1  'Right Justify
         Caption         =   "恒温箱温度"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   120
         TabIndex        =   7
         Top             =   690
         Width           =   1215
      End
      Begin VB.Label Label2 
         Alignment       =   1  'Right Justify
         Caption         =   "波特率"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   120
         TabIndex        =   6
         Top             =   1050
         Width           =   1215
      End
   End
End
Attribute VB_Name = "formComPara"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public bCancel As Boolean

Public lStaNo As Long
Public lSpeed As Long
Public lBt As Long
Public lTemp As Single

Private Sub cmdCancel_Click()
    bCancel = True
    Unload Me
End Sub

Private Sub cmdOK_Click()
    lBt = Val(Me.cmbBt.Text)
    
    If IsEmpty(Me.txtTemperature) Then
        MsgBox "未指定恒温箱温度", vbOKOnly + vbExclamation
        Exit Sub
    End If
    If IsNumeric(Me.txtTemperature) Then
        lTemp = Val(Me.txtTemperature)
    Else
        MsgBox "参数错误，恒温箱温度错误", vbOKOnly + vbCritical
        Exit Sub
    End If
    
    lStaNo = Val(Me.cmbXC.ListIndex)
    If (Me.cmbSpeed.Text = "正常") Then
        lSpeed = 0
    Else
        lSpeed = 1
    End If
    
    bCancel = False
    Unload Me
End Sub

Private Sub Form_Load()
    Me.cmbXC.Clear
    Me.cmbXC.AddItem "未指定"
    Dim i As Long
    For i = 1 To 99
        Me.cmbXC.AddItem i
    Next i
    Me.cmbXC.ListIndex = 0
    Me.cmbBt.Text = glBt
    Me.txtTemperature = glTemperature
    If glSpeed = 1 Then
        Me.cmbSpeed = "降速"
    Else
        Me.cmbSpeed = "正常"
    End If
End Sub

Private Sub txtTemperature_KeyPress(KeyAscii As Integer)
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
