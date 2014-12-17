VERSION 5.00
Begin VB.Form formRefresh 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "自动刷新数据"
   ClientHeight    =   1515
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   2385
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1515
   ScaleWidth      =   2385
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdStop 
      Caption         =   "停止"
      Height          =   345
      Left            =   90
      TabIndex        =   2
      Top             =   1110
      Width           =   2205
   End
   Begin VB.Frame Frame1 
      Caption         =   "读取数据类型"
      Height          =   915
      Left            =   90
      TabIndex        =   3
      Top             =   60
      Width           =   2205
      Begin VB.OptionButton optRaw 
         Caption         =   "A/D值"
         Height          =   315
         Left            =   180
         TabIndex        =   1
         Top             =   570
         Width           =   1095
      End
      Begin VB.OptionButton optValue 
         Caption         =   "工程值"
         Height          =   255
         Left            =   180
         TabIndex        =   0
         Top             =   300
         Value           =   -1  'True
         Width           =   1065
      End
   End
End
Attribute VB_Name = "formRefresh"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub cmdStop_Click()
    Unload Me
End Sub

Private Sub Form_Load()
    'Me.Left = formMain.Left + formMain.Width - 2500
    'Me.Top = formMain.Top - 2000
    If optRaw.Value Then
        glRefresh = 1
    Else
        glRefresh = 0
    End If
    formMain.timerRefresh.Enabled = True
End Sub

Private Sub Form_Unload(Cancel As Integer)
    formMain.timerRefresh.Enabled = False
End Sub

Private Sub optRaw_Click()
    glRefresh = 1
End Sub

Private Sub optValue_Click()
    glRefresh = 0
End Sub

