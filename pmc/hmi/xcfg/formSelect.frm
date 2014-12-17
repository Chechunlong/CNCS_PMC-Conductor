VERSION 5.00
Begin VB.Form formSelect 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "选择巡测设备"
   ClientHeight    =   1770
   ClientLeft      =   30
   ClientTop       =   315
   ClientWidth     =   3105
   ControlBox      =   0   'False
   BeginProperty Font 
      Name            =   "System"
      Size            =   12
      Charset         =   134
      Weight          =   700
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1770
   ScaleWidth      =   3105
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
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
      ItemData        =   "formSelect.frx":0000
      Left            =   1428
      List            =   "formSelect.frx":0010
      Style           =   2  'Dropdown List
      TabIndex        =   1
      Top             =   480
      Width           =   1320
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
      Left            =   1428
      Style           =   2  'Dropdown List
      TabIndex        =   2
      Top             =   840
      Width           =   1320
   End
   Begin VB.ComboBox cmbPort 
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
      Left            =   1428
      Style           =   2  'Dropdown List
      TabIndex        =   0
      Top             =   120
      Width           =   1320
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
      Left            =   1668
      TabIndex        =   4
      Top             =   1320
      Width           =   852
   End
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
      Left            =   528
      TabIndex        =   3
      Top             =   1320
      Width           =   852
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
      Height          =   252
      Left            =   108
      TabIndex        =   7
      Top             =   540
      Width           =   1212
   End
   Begin VB.Label LabelChooseEquip 
      Alignment       =   1  'Right Justify
      Caption         =   "选择巡测"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   252
      Left            =   108
      TabIndex        =   6
      Top             =   900
      Width           =   1212
   End
   Begin VB.Label LabelChooseInterface 
      Alignment       =   1  'Right Justify
      Caption         =   "选择端口"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   252
      Left            =   108
      TabIndex        =   5
      Top             =   180
      Width           =   1212
   End
End
Attribute VB_Name = "formSelect"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public Cancel As Boolean
Public PortNo As Long
Public Bt As Long
Public StaNo As Long

Private Sub cmdCancel_Click()
    Cancel = True
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
    If Me.cmbXC.Text = Empty Then
        MsgBox "未指定巡测站号", vbOKOnly + vbExclamation
        Exit Sub
    Else
        StaNo = Val(Me.cmbXC.Text)
    End If
    
    Cancel = False
    Unload Me
End Sub

Private Sub Form_Load()
    Dim i As Long
    For i = 1 To 16
        Me.cmbPort.AddItem CStr(i)
    Next i
    For i = 1 To 99
        Me.cmbXC.AddItem CStr(i)
    Next i
    
    Me.cmbBt.ListIndex = 3
End Sub

