VERSION 5.00
Begin VB.Form formNew 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "�½���̬�ļ�"
   ClientHeight    =   2220
   ClientLeft      =   30
   ClientTop       =   330
   ClientWidth     =   3285
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
   Icon            =   "formNew.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2220
   ScaleWidth      =   3285
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox txtChNum 
      Enabled         =   0   'False
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   10.5
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   300
      Left            =   1560
      MaxLength       =   2
      TabIndex        =   9
      Text            =   "60"
      Top             =   -30
      Visible         =   0   'False
      Width           =   1332
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "ȡ��"
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
      Top             =   1770
      Width           =   852
   End
   Begin VB.Frame frmComPar 
      Caption         =   "ָ����������"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1515
      Left            =   150
      TabIndex        =   5
      Top             =   120
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
         ItemData        =   "formNew.frx":000C
         Left            =   1500
         List            =   "formNew.frx":0016
         Style           =   2  'Dropdown List
         TabIndex        =   2
         Top             =   990
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
         Height          =   288
         Left            =   1500
         MaxLength       =   2
         TabIndex        =   0
         Top             =   300
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
         ItemData        =   "formNew.frx":0026
         Left            =   1500
         List            =   "formNew.frx":0036
         Style           =   2  'Dropdown List
         TabIndex        =   1
         Top             =   600
         Width           =   1332
      End
      Begin VB.Label Label4 
         Alignment       =   1  'Right Justify
         Caption         =   "�ɼ��ٶ�"
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
         Left            =   180
         TabIndex        =   8
         Top             =   1020
         Width           =   1215
      End
      Begin VB.Label Label2 
         Alignment       =   1  'Right Justify
         Caption         =   "������"
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
         Left            =   180
         TabIndex        =   7
         Top             =   660
         Width           =   1215
      End
      Begin VB.Label Label3 
         Alignment       =   1  'Right Justify
         Caption         =   "�������¶�"
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
         Left            =   180
         TabIndex        =   6
         Top             =   360
         Width           =   1215
      End
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "ȷ��"
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
      Top             =   1770
      Width           =   852
   End
   Begin VB.Label Label1 
      Alignment       =   1  'Right Justify
      Caption         =   "ͨ������"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   10.5
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   300
      TabIndex        =   10
      Top             =   240
      Visible         =   0   'False
      Width           =   1215
   End
End
Attribute VB_Name = "formNew"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public bCancel As Boolean

Public lChNum As Long
Public lBt As Long
Public lTemp As Long
Public lSpeed As Long

Private Sub cmdCancel_Click()
    bCancel = True
    Unload Me
End Sub

Private Sub cmdOK_Click()
    lBt = Val(Me.cmbBt.Text)
    
    If IsEmpty(Me.txtTemperature) Then
        MsgBox "δָ���������¶�", vbOKOnly + vbExclamation
        Exit Sub
    End If
    If IsNumeric(Me.txtTemperature) Then
        lTemp = Val(Me.txtTemperature)
    Else
        MsgBox "�������󣬺������¶ȴ���", vbOKOnly + vbCritical
        Exit Sub
    End If

    'If IsEmpty(Me.txtChNum) Then
    '    MsgBox "δָ��ͨ������", vbOKOnly + vbExclamation
    '    Exit Sub
    'End If
    'lChNum = Val(Me.txtChNum)
    'If lChNum < 1 Then
    '    MsgBox "��������,ͨ�������������0", vbOKOnly + vbCritical
    '    Exit Sub
    'End If
    If (Me.cmbSpeed.Text = "����") Then
        lSpeed = 0
    Else
        lSpeed = 1
    End If
    
    bCancel = False
    Unload Me
End Sub

Private Sub Form_Load()
    Me.cmbBt.ListIndex = 3
    Me.cmbSpeed.ListIndex = 0
End Sub

Private Sub txtChNum_KeyPress(KeyAscii As Integer)
    '�˸�
    If KeyAscii = vbKeyBack Then
    '�»���
    'ElseIf KeyAscii = 95 Then
    '����
    ElseIf KeyAscii >= vbKey0 And KeyAscii <= vbKey9 Then
    'Ӣ���ַ�
    'ElseIf KeyAscii >= vbKeyA And KeyAscii <= vbKeyZ Then   '��д
    'ElseIf KeyAscii >= 97 And KeyAscii <= 122 Then          'Сд
    Else
        KeyAscii = 0
    End If
End Sub

Private Sub txtTemperature_KeyPress(KeyAscii As Integer)
    '�˸�
    If KeyAscii = vbKeyBack Then
    '�»���
    'ElseIf KeyAscii = 95 Then
    '����
    ElseIf KeyAscii >= vbKey0 And KeyAscii <= vbKey9 Then
    'Ӣ���ַ�
    'ElseIf KeyAscii >= vbKeyA And KeyAscii <= vbKeyZ Then   '��д
    'ElseIf KeyAscii >= 97 And KeyAscii <= 122 Then          'Сд
    Else
        KeyAscii = 0
    End If
End Sub
