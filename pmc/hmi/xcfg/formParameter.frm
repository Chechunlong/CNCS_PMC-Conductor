VERSION 5.00
Begin VB.Form formParameter 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "通道参数"
   ClientHeight    =   4785
   ClientLeft      =   4620
   ClientTop       =   330
   ClientWidth     =   7425
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
   Icon            =   "formParameter.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4785
   ScaleWidth      =   7425
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'CenterOwner
   Begin VB.PictureBox picButtons 
      Align           =   2  'Align Bottom
      Appearance      =   0  'Flat
      BackColor       =   &H8000000C&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   570
      Left            =   0
      ScaleHeight     =   570
      ScaleWidth      =   7425
      TabIndex        =   26
      Top             =   3840
      Width           =   7425
      Begin VB.CommandButton cmdClear 
         Caption         =   "清除(&D)"
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
         Left            =   3384
         TabIndex        =   12
         Top             =   120
         Width           =   1032
      End
      Begin VB.CommandButton cmdClose 
         Caption         =   "关闭(&x)"
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
         Left            =   6240
         TabIndex        =   15
         Top             =   120
         Width           =   1035
      End
      Begin VB.CommandButton cmdCopy 
         Caption         =   "拷贝(&C)"
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
         Height          =   360
         Left            =   120
         TabIndex        =   10
         Top             =   120
         Width           =   975
      End
      Begin VB.CommandButton cmdPaste 
         Caption         =   "粘贴(&P)"
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
         Height          =   360
         Left            =   1170
         TabIndex        =   11
         Top             =   120
         Width           =   1035
      End
      Begin VB.CommandButton cmdCancel 
         Caption         =   "取消(&C)"
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
         Left            =   3384
         TabIndex        =   27
         Top             =   120
         Visible         =   0   'False
         Width           =   1032
      End
      Begin VB.CommandButton cmdUpdate 
         Caption         =   "更新(&U)"
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
         Left            =   2250
         TabIndex        =   13
         Top             =   120
         Visible         =   0   'False
         Width           =   1032
      End
      Begin VB.CommandButton cmdEdit 
         Caption         =   "编辑(&E)"
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
         Left            =   2268
         TabIndex        =   14
         Top             =   120
         Width           =   1032
      End
   End
   Begin VB.ComboBox cmbChannelType 
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
      ItemData        =   "formParameter.frx":000C
      Left            =   2175
      List            =   "formParameter.frx":0019
      Style           =   2  'Dropdown List
      TabIndex        =   0
      Top             =   120
      Width           =   1575
   End
   Begin VB.ComboBox cmbSensorType 
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
      ItemData        =   "formParameter.frx":0035
      Left            =   2175
      List            =   "formParameter.frx":0037
      Style           =   2  'Dropdown List
      TabIndex        =   1
      Top             =   480
      Width           =   1575
   End
   Begin VB.ComboBox cmbCompType 
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
      ItemData        =   "formParameter.frx":0039
      Left            =   2175
      List            =   "formParameter.frx":003B
      Style           =   2  'Dropdown List
      TabIndex        =   2
      Top             =   840
      Width           =   1575
   End
   Begin VB.TextBox txtCompParameter 
      DataField       =   "CompResistance"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   300
      Left            =   2175
      TabIndex        =   25
      Top             =   840
      Visible         =   0   'False
      Width           =   1575
   End
   Begin VB.ComboBox cmbCompChannel 
      DataField       =   "CompChannelNO"
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
      ItemData        =   "formParameter.frx":003D
      Left            =   5775
      List            =   "formParameter.frx":003F
      TabIndex        =   3
      Top             =   840
      Visible         =   0   'False
      Width           =   1095
   End
   Begin VB.ComboBox cmbCalculate2 
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
      ItemData        =   "formParameter.frx":0041
      Left            =   2175
      List            =   "formParameter.frx":0054
      Style           =   2  'Dropdown List
      TabIndex        =   9
      Top             =   3390
      Width           =   2280
   End
   Begin VB.Frame frmCalculate1 
      Caption         =   "Y=A*X+B"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1992
      Left            =   2175
      TabIndex        =   22
      Top             =   1320
      Width           =   4875
      Begin VB.TextBox txtMaxValue 
         DataField       =   "MaxValue"
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
         Height          =   324
         Left            =   2172
         TabIndex        =   8
         Top             =   1440
         Width           =   1575
      End
      Begin VB.TextBox txtMinValue 
         DataField       =   "MinValue"
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
         Height          =   324
         Left            =   2172
         TabIndex        =   7
         Top             =   1080
         Width           =   1575
      End
      Begin VB.TextBox txtA 
         DataField       =   "A"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   324
         Left            =   576
         TabIndex        =   4
         Top             =   330
         Width           =   1395
      End
      Begin VB.TextBox txtB 
         DataField       =   "B"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   324
         Left            =   2655
         TabIndex        =   5
         Top             =   330
         Width           =   1395
      End
      Begin VB.CheckBox chkDefault 
         Caption         =   "使用默认值"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   576
         TabIndex        =   6
         Top             =   780
         Width           =   1545
      End
      Begin VB.Label lblLabels 
         Alignment       =   1  'Right Justify
         Caption         =   "最大工程值"
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
         Height          =   255
         Index           =   5
         Left            =   630
         TabIndex        =   37
         Top             =   1560
         Width           =   1515
      End
      Begin VB.Label lblLabels 
         Alignment       =   1  'Right Justify
         Caption         =   "最小工程值"
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
         Height          =   255
         Index           =   4
         Left            =   630
         TabIndex        =   36
         Top             =   1170
         Width           =   1515
      End
      Begin VB.Label lblLabels 
         Alignment       =   1  'Right Justify
         Caption         =   "A="
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
         Index           =   17
         Left            =   135
         TabIndex        =   24
         Top             =   390
         Width           =   360
      End
      Begin VB.Label lblLabels 
         Alignment       =   1  'Right Justify
         Caption         =   "B="
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
         Index           =   18
         Left            =   2205
         TabIndex        =   23
         Top             =   390
         Width           =   360
      End
   End
   Begin VB.PictureBox picStatBox 
      Align           =   2  'Align Bottom
      Appearance      =   0  'Flat
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   375
      Left            =   0
      ScaleHeight     =   375
      ScaleWidth      =   7425
      TabIndex        =   16
      Top             =   4410
      Width           =   7425
      Begin VB.CommandButton cmdLast 
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
         Left            =   7080
         Picture         =   "formParameter.frx":0090
         Style           =   1  'Graphical
         TabIndex        =   20
         Top             =   0
         UseMaskColor    =   -1  'True
         Width           =   345
      End
      Begin VB.CommandButton cmdNext 
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
         Left            =   6720
         Picture         =   "formParameter.frx":03D2
         Style           =   1  'Graphical
         TabIndex        =   19
         Top             =   0
         UseMaskColor    =   -1  'True
         Width           =   345
      End
      Begin VB.CommandButton cmdPrevious 
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
         Left            =   345
         Picture         =   "formParameter.frx":0714
         Style           =   1  'Graphical
         TabIndex        =   18
         Top             =   0
         UseMaskColor    =   -1  'True
         Width           =   345
      End
      Begin VB.CommandButton cmdFirst 
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
         Left            =   0
         Picture         =   "formParameter.frx":0A56
         Style           =   1  'Graphical
         TabIndex        =   17
         Top             =   0
         UseMaskColor    =   -1  'True
         Width           =   345
      End
      Begin VB.Label lblStatus 
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   1  'Fixed Single
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
         Left            =   672
         TabIndex        =   21
         Top             =   0
         Width           =   6060
      End
   End
   Begin VB.Label lblLabels 
      Alignment       =   1  'Right Justify
      Caption         =   "通道类型"
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
      Index           =   12
      Left            =   210
      TabIndex        =   35
      Top             =   210
      Width           =   1935
   End
   Begin VB.Label lblLabels 
      Alignment       =   1  'Right Justify
      Caption         =   "传感器类型"
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
      Index           =   13
      Left            =   210
      TabIndex        =   34
      Top             =   570
      Width           =   1935
   End
   Begin VB.Label lblLabels 
      Alignment       =   1  'Right Justify
      Caption         =   "补偿方式"
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
      Index           =   14
      Left            =   210
      TabIndex        =   33
      Top             =   930
      Width           =   1935
   End
   Begin VB.Label lblLabels 
      Alignment       =   1  'Right Justify
      Caption         =   "线路修正电阻值"
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
      Index           =   15
      Left            =   210
      TabIndex        =   32
      Top             =   960
      Visible         =   0   'False
      Width           =   1935
   End
   Begin VB.Label lblLabels 
      Alignment       =   1  'Right Justify
      Caption         =   "一次计算"
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
      Index           =   16
      Left            =   210
      TabIndex        =   31
      Top             =   1320
      Width           =   1935
   End
   Begin VB.Label lblLabels 
      Alignment       =   1  'Right Justify
      Caption         =   "二次计算"
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
      Index           =   19
      Left            =   210
      TabIndex        =   30
      Top             =   3480
      Width           =   1935
   End
   Begin VB.Label lblLabels 
      Alignment       =   1  'Right Justify
      Caption         =   "冷端补偿通道"
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
      Index           =   20
      Left            =   4260
      TabIndex        =   29
      Top             =   930
      Visible         =   0   'False
      Width           =   1485
   End
   Begin VB.Label lblLabels 
      Alignment       =   1  'Right Justify
      Caption         =   "Ω"
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
      Index           =   22
      Left            =   3780
      TabIndex        =   28
      Top             =   915
      Visible         =   0   'False
      Width           =   270
   End
End
Attribute VB_Name = "formParameter"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public IniID  As Long

Private WithEvents adoPrimaryRS As ADODB.Recordset
Attribute adoPrimaryRS.VB_VarHelpID = -1
Private mbChangedByCode As Boolean
Private mvBookMark As Variant
Private mbEditFlag As Boolean
Private mbAddNewFlag As Boolean
Private mbDataChanged As Boolean

'参数
Private bCopyed As Boolean
'section 1
Private fMinValue As Single
Private fMaxValue As Single
Private bUsed As Boolean
'section 2
Private iChannelType As Integer
Private iSensorType As Integer
Private iCompType As Integer
Private fCompResistance As Single
Private iCompChannel As Integer
Private bUseDefault As Boolean
Private fA As Single
Private fB As Single
Private iCalculate2 As Integer

'拷贝用参数
'section 1
Private fcMinValue As Single
Private fcMaxValue As Single
'section 2
Private icChannelType As Integer
Private icSensorType As Integer
Private icCompType As Integer
Private fcCompResistance As Single
Private icCompChannel As Integer
Private bcUseDefault As Boolean
Private fcA As Single
Private fcB As Single
Private icCalculate2 As Integer

Private Sub adoPrimaryRS_MoveComplete(ByVal adReason As ADODB.EventReasonEnum, ByVal pError As ADODB.Error, adStatus As ADODB.EventStatusEnum, ByVal pRecordset As ADODB.Recordset)
'    This will display the current record position for this recordset
    If (adReason <> adRsnMove) And (adReason < adRsnMoveFirst Or adReason > adRsnMoveLast) Then Exit Sub
    If pRecordset.BOF Or pRecordset.EOF Then
        lblStatus.Caption = Empty
        RefreshContrl False
        LockContrl True
    Else
        If pRecordset.EditMode <> adEditAdd Then
            GetValFromDB
            Me.cmdCopy.Enabled = True
            RefreshContrl bUsed
            lblStatus.Caption = "当前通道:" & adoPrimaryRS.Fields("ChannelNo")
        End If
        If mbAddNewFlag Then
            LockContrl False
        Else
            LockContrl True
        End If
    End If
End Sub

Private Sub adoPrimaryRS_WillChangeRecord(ByVal adReason As ADODB.EventReasonEnum, ByVal cRecords As Long, adStatus As ADODB.EventStatusEnum, ByVal pRecordset As ADODB.Recordset)
    'This is where you put validation code
    'This event gets called when the following actions occur
    Dim bCancel As Boolean
    
    Select Case adReason
    Case adRsnAddNew
    Case adRsnClose
    Case adRsnDelete
    Case adRsnFirstChange
    Case adRsnMove
    Case adRsnRequery
    Case adRsnResynch
    Case adRsnUndoAddNew
    Case adRsnUndoDelete
    Case adRsnUndoUpdate
    Case adRsnUpdate
    End Select
    
    If bCancel Then adStatus = adStatusCancel
End Sub


Private Sub chkDefault_Click()
    If Me.chkDefault.Value = vbChecked Then
        Me.lblLabels(17).Enabled = False
        Me.lblLabels(18).Enabled = False
        Me.lblLabels(4).Enabled = True
        Me.lblLabels(5).Enabled = True
        Me.txtA = Empty
        Me.txtB = Empty
        Me.txtA.Enabled = False
        Me.txtB.Enabled = False
        Me.txtMinValue.Enabled = True
        Me.txtMaxValue.Enabled = True
    Else
        Me.lblLabels(17).Enabled = True
        Me.lblLabels(18).Enabled = True
        Me.lblLabels(4).Enabled = False
        Me.lblLabels(5).Enabled = False
        Me.txtA.Enabled = True
        Me.txtB.Enabled = True
        Me.txtMinValue = Empty
        Me.txtMaxValue = Empty
        Me.txtMinValue.Enabled = False
        Me.txtMaxValue.Enabled = False
    End If
End Sub

Private Sub cmbChannelType_Click()
    Me.cmbSensorType.Clear
    Me.cmbCompType.Clear
        
    Select Case Me.cmbChannelType.Text
    Case "热电阻"
        With Me.cmbSensorType
            .AddItem "Pt100"
            .AddItem "Cu50"
            .AddItem "Cu100"
            .AddItem "BA1"
            .AddItem "BA2"
            .AddItem "G53"
            .ItemData(0) = 4
            .ItemData(1) = 0
            .ItemData(2) = 1
            .ItemData(3) = 2
            .ItemData(4) = 3
            .ItemData(5) = 7
        End With
        Me.lblLabels(14).Visible = False
        Me.cmbCompType.Visible = False
        Me.lblLabels(15).Visible = True
        Me.lblLabels(22).Visible = True
        Me.txtCompParameter.Visible = True
        Me.lblLabels(20).Visible = False
        Me.cmbCompChannel.Visible = False
    Case "热电偶"
        With Me.cmbSensorType
            .AddItem "K"
            .AddItem "E"
            .AddItem "EA2"
            .ItemData(0) = 5
            .ItemData(1) = 6
            .ItemData(2) = 8
        End With
        With Me.cmbCompType
            .AddItem "恒温箱补偿"
            .AddItem "冷端补偿"
            .ItemData(0) = 1
            .ItemData(1) = 2
        End With
        Me.lblLabels(14).Visible = True
        Me.cmbCompType.Visible = True
        Me.lblLabels(15).Visible = False
        Me.lblLabels(22).Visible = False
        Me.txtCompParameter.Visible = False
        Me.lblLabels(14).Enabled = True
        Me.cmbCompType.Enabled = True
        Me.cmbCompType.ListIndex = 0
    Case "传感器"
        With Me.cmbSensorType
            .AddItem "4-20mA"
            .AddItem "0-10mA"
            .AddItem "1-5V"
            .AddItem "0-5V"
            .AddItem "0-10V"
            .ItemData(0) = 12
            .ItemData(1) = 11
            .ItemData(2) = 10
            .ItemData(3) = 9
            .ItemData(4) = 13
        End With
        Me.lblLabels(14).Visible = True
        Me.cmbCompType.Visible = True
        Me.lblLabels(14).Enabled = False
        Me.cmbCompType.Enabled = False
        Me.lblLabels(15).Visible = False
        Me.lblLabels(22).Visible = False
        Me.txtCompParameter.Visible = False
        Me.lblLabels(20).Visible = False
        Me.cmbCompChannel.Visible = False
    End Select
End Sub

Private Sub cmbCompType_Click()
    If Me.cmbCompType.ListIndex < 0 Then
        Me.lblLabels(15).Visible = False
        Me.txtCompParameter.Visible = False
        Me.lblLabels(20).Visible = False
        Me.cmbCompChannel.Visible = False
        Exit Sub
    End If
    
    Select Case Me.cmbCompType.ItemData(Me.cmbCompType.ListIndex)
    Case 1
        Me.lblLabels(20).Visible = False
        Me.cmbCompChannel.Visible = False
    Case 2
        Me.lblLabels(20).Visible = True
        Me.cmbCompChannel.Visible = True
    Case Else
        Me.lblLabels(20).Visible = False
        Me.cmbCompChannel.Visible = False
    End Select
    
End Sub



Private Sub cmdCancel_Click()
     On Error Resume Next
    
     SetButtons True
     mbEditFlag = False
     mbAddNewFlag = False
     adoPrimaryRS.CancelUpdate
     
     If mvBookMark > 0 Then
        adoPrimaryRS.Bookmark = mvBookMark
     Else
        adoPrimaryRS.MoveFirst
     End If
     
     mbDataChanged = False
End Sub

Private Sub cmdClear_Click()
    If adoPrimaryRS.BOF Or adoPrimaryRS.EOF Then Exit Sub
    mvBookMark = adoPrimaryRS.Bookmark
    adoPrimaryRS.Fields("Used") = False
    adoPrimaryRS.Update
    bUsed = False
    RefreshContrl bUsed
    Exit Sub

EditErr:
  MsgBox Err.Description
End Sub

 Sub cmdCopy_Click()
    bCopyed = True
    'section 1
    fcMinValue = fMinValue
    fcMaxValue = fMaxValue
    'section2
    icChannelType = iChannelType
    icSensorType = iSensorType
    icCompType = iCompType
    fcCompResistance = fCompResistance
    icCompChannel = iCompChannel
    bcUseDefault = bUseDefault
    fcA = fA
    fcB = fB
    icCalculate2 = iCalculate2
End Sub

Private Sub cmdEdit_Click()
    If adoPrimaryRS.BOF Or adoPrimaryRS.EOF Then Exit Sub
    mvBookMark = adoPrimaryRS.Bookmark
    Me.cmdCopy.Enabled = False
    mbEditFlag = True
    SetButtons False
    
    LockContrl False
    Exit Sub

EditErr:
  MsgBox Err.Description
End Sub

Private Sub cmdFirst_Click()
    On Error GoTo GoFirstError
    
    adoPrimaryRS.MoveFirst
    mbDataChanged = False
    
    Exit Sub
    
GoFirstError:
    MsgBox Err.Description
End Sub

Private Sub cmdLast_Click()
  On Error GoTo GoLastError

  adoPrimaryRS.MoveLast
  mbDataChanged = False

  Exit Sub

GoLastError:
  MsgBox Err.Description
End Sub

Private Sub cmdNext_Click()
    On Error GoTo GoNextError
    
    If Not adoPrimaryRS.EOF Then adoPrimaryRS.MoveNext
    If adoPrimaryRS.EOF And adoPrimaryRS.RecordCount > 0 Then
        Beep
         'moved off the end so go back
        adoPrimaryRS.MoveLast
    End If
    'show the current record
    mbDataChanged = False
    
    Exit Sub
GoNextError:
    MsgBox Err.Description
End Sub

Private Sub cmdPaste_Click()
    Dim i As Long
    'section 1
    Me.txtMinValue = CStr(fcMinValue)
    Me.txtMaxValue = CStr(fcMaxValue)
    'section 2
    Select Case icChannelType
    Case 1  '热电阻
        Me.cmbChannelType.ListIndex = 0
        Me.txtCompParameter = CStr(fcCompResistance)
    Case 2  '热电偶
        Me.cmbChannelType.ListIndex = 1
        If icCompType = 1 Then       '恒温箱补偿
            Me.cmbCompType.ListIndex = 0
        ElseIf icCompType = 2 Then   '冷端补偿
            Me.cmbCompType.ListIndex = 1
            Me.cmbCompChannel.ListIndex = icCompChannel - 1
        End If
    Case 3  '传感器
        Me.cmbChannelType.ListIndex = 2
    End Select
    Me.cmbSensorType.ListIndex = -1
    For i = 0 To Me.cmbSensorType.ListCount - 1
        If Me.cmbSensorType.ItemData(i) = icSensorType Then
            Me.cmbSensorType.ListIndex = i
            Exit For
        End If
    Next i
    If bcUseDefault Then
        Me.chkDefault.Value = vbChecked
        Me.txtA = Empty
        Me.txtB = Empty
    Else
        Me.chkDefault.Value = vbUnchecked
        Me.txtA = CStr(fcA)
        Me.txtB = CStr(fcB)
    End If
    Me.cmbCalculate2.ListIndex = -1
    For i = 0 To Me.cmbCalculate2.ListCount - 1
        If Me.cmbCalculate2.ItemData(i) = icCalculate2 Then
            Me.cmbCalculate2.ListIndex = i
            Exit For
        End If
    Next i
End Sub

Private Sub cmdPrevious_Click()
    On Error GoTo GoPrevError
    
    If Not adoPrimaryRS.BOF Then adoPrimaryRS.MovePrevious
    If adoPrimaryRS.BOF And adoPrimaryRS.RecordCount > 0 Then
        Beep
        'moved off the end so go back
        adoPrimaryRS.MoveFirst
    End If
    'show the current record
    mbDataChanged = False
    
    Exit Sub

GoPrevError:
    MsgBox Err.Description
End Sub

Private Sub cmdUpdate_Click()
    On Error GoTo UpdateErr
    
    If Not CheckParameter Then Exit Sub
        
    SetValToDB
    adoPrimaryRS.Update
            
    If mbEditFlag Or mbAddNewFlag Then LockContrl True
    If mbEditFlag Then Me.cmdCopy.Enabled = True
    
    mbEditFlag = False
    mbAddNewFlag = False
    SetButtons True
    mbDataChanged = False
    
    Exit Sub
UpdateErr:
    MsgBox "Data error event hit err:" & Err.Description
End Sub

Private Sub Form_Initialize()
    IniID = 0
End Sub

Private Sub Form_KeyDown(KeyCode As Integer, Shift As Integer)
  If mbEditFlag Or mbAddNewFlag Then Exit Sub

  Select Case KeyCode
    Case vbKeyEscape
      cmdClose_Click
    Case vbKeyEnd
      cmdLast_Click
    Case vbKeyHome
      cmdFirst_Click
    Case vbKeyUp, vbKeyPageUp
      If Shift = vbCtrlMask Then
        cmdFirst_Click
      Else
        cmdPrevious_Click
      End If
    Case vbKeyDown, vbKeyPageDown
      If Shift = vbCtrlMask Then
        cmdLast_Click
      Else
        cmdNext_Click
      End If
  End Select
End Sub

Private Sub Form_Load()
    Me.Caption = "通道参数 - " & glChNum & "点"
    Dim i As Integer
    For i = 1 To glChNum
        Me.cmbCompChannel.AddItem CStr(i)
    Next i
        
    Set adoPrimaryRS = grdPara
    adoPrimaryRS.Filter = "ChannelNo<=" & glChNum
    If IniID > 0 Then
        adoPrimaryRS.Find "ChannelNo = " & IniID
    ElseIf adoPrimaryRS.RecordCount > 0 Then
        adoPrimaryRS.MoveFirst
    End If
           
    mbDataChanged = False
    Screen.MousePointer = vbDefault
End Sub

Private Sub cmdClose_Click()
  Unload Me
End Sub



Private Function CheckParameter() As Boolean
    'section 2
    If Me.cmbChannelType.ListIndex < 0 Then
        MsgBox "未指定通道类型", vbOKOnly + vbExclamation, "参数错误"
        CheckParameter = False
        Exit Function
    Else
        iChannelType = Me.cmbChannelType.ItemData(Me.cmbChannelType.ListIndex)
    End If
    Select Case iChannelType
    Case 1  '热电阻
        If Not IsNumeric(Me.txtCompParameter) Then
            MsgBox "补偿电阻错误", vbOKOnly + vbExclamation, "参数错误"
            CheckParameter = False
            Exit Function
        Else
            fCompResistance = Val(Me.txtCompParameter)
        End If
    Case 2  '热电偶
        If Me.cmbCompType.ListIndex < 0 Then
            MsgBox "未指定补偿类型", vbOKOnly + vbExclamation, "参数错误"
            CheckParameter = False
            Exit Function
        Else
            iCompType = Me.cmbCompType.ItemData(Me.cmbCompType.ListIndex)
        End If
        If iCompType = 1 Then       '恒温箱补偿
        ElseIf iCompType = 2 Then   '冷端补偿
            If Me.cmbCompChannel.ListIndex < 0 Then
                MsgBox "未指定补偿通道号", vbOKOnly + vbExclamation, "参数错误"
                CheckParameter = False
                Exit Function
            Else
                iCompChannel = Me.cmbCompChannel.ListIndex + 1
            End If
        End If
    Case 3  '传感器
    End Select
    If Me.cmbSensorType.ListIndex < 0 Then
        MsgBox "未指定传感器类型", vbOKOnly + vbExclamation, "参数错误"
        CheckParameter = False
        Exit Function
    Else
        iSensorType = Me.cmbSensorType.ItemData(Me.cmbSensorType.ListIndex)
    End If
    If Me.chkDefault.Value = vbChecked Then
        bUseDefault = True
        If Me.cmbSensorType.ItemData(Me.cmbSensorType.ListIndex) > 8 Then
            'section 1
            If Not IsNumeric(Me.txtMinValue) Then
                MsgBox "最小工程值错误", vbOKOnly + vbExclamation, "参数错误"
                CheckParameter = False
                Exit Function
            End If
            If Not IsNumeric(Me.txtMaxValue) Then
                MsgBox "最大工程值错误", vbOKOnly + vbExclamation, "参数错误"
                CheckParameter = False
                Exit Function
            End If
            If Abs(Val(Me.txtMaxValue) - Val(Me.txtMinValue)) < 0.1 Then
                MsgBox "最大工程值与最小工程值差应大于" & 0.1, vbOKOnly + vbExclamation, "参数错误"
                CheckParameter = False
                Exit Function
            Else
                fMinValue = Val(Me.txtMinValue)
                fMaxValue = Val(Me.txtMaxValue)
            End If
            Dim fMinRaw As Single
            Dim fMaxRaw As Single
            Select Case Me.cmbSensorType.ItemData(Me.cmbSensorType.ListIndex)
            Case 9
                fMinRaw = 0#
                fMaxRaw = 5000#
            Case 10
                fMinRaw = 0#
                fMaxRaw = 4000#
            Case 11
                fMinRaw = 0#
                fMaxRaw = 5000#
            Case 12
                fMinRaw = 0#
                fMaxRaw = 4000#
            Case 13
                fMinRaw = 0#
                fMaxRaw = 10000#
            End Select
            fA = (fMaxValue - fMinValue) / (fMaxRaw - fMinRaw)
            fB = -fMinRaw * (fMaxValue - fMinValue) / (fMaxRaw - fMinRaw) + fMinValue
        Else
            fA = 1#
            fB = 0#
        End If
    Else
        bUseDefault = False
        If Not IsNumeric(Me.txtA) Then
            MsgBox "参数A错误", vbOKOnly + vbExclamation, "参数错误"
            CheckParameter = False
            Exit Function
        Else
            fA = Val(Me.txtA)
        End If
        If Not IsNumeric(Me.txtB) Then
            MsgBox "参数B错误", vbOKOnly + vbExclamation, "参数错误"
            CheckParameter = False
            Exit Function
        Else
            fB = Val(Me.txtB)
        End If
    End If
    If Me.cmbCalculate2.ListIndex < 0 Then
        MsgBox "未指定二次计算类型", vbOKOnly + vbExclamation, "参数错误"
        CheckParameter = False
        Exit Function
    Else
        iCalculate2 = Me.cmbCalculate2.ItemData(Me.cmbCalculate2.ListIndex)
    End If
    
    CheckParameter = True
End Function

Private Sub SetButtons(bVal As Boolean)
    cmdEdit.Visible = bVal
    cmdClear.Visible = bVal
    cmdUpdate.Visible = Not bVal
    cmdCancel.Visible = Not bVal
    cmdClose.Visible = bVal
    cmdNext.Enabled = bVal
    cmdFirst.Enabled = bVal
    cmdLast.Enabled = bVal
    cmdPrevious.Enabled = bVal
End Sub

Private Sub RefreshContrl(Optional bSet As Boolean = False)
    Dim i As Long
    
    If Not bSet Then
        'section 1
        Me.txtMinValue = Empty
        Me.txtMaxValue = Empty
        'section 2
        Me.cmbChannelType.ListIndex = -1
        Me.cmbSensorType.ListIndex = -1
        Me.cmbCompType.ListIndex = -1
        Me.cmbCompChannel.ListIndex = -1
        Me.txtCompParameter = Empty
        Me.txtA = Empty
        Me.txtB = Empty
        Me.chkDefault.Value = vbUnchecked
        Me.chkDefault.Value = vbChecked
        Me.cmbCalculate2.ListIndex = 0
    Else
        'section 2
        Select Case iChannelType
        Case 1  '热电阻
            Me.cmbChannelType.ListIndex = 0
            Me.txtCompParameter = CStr(fCompResistance)
        Case 2  '热电偶
            Me.cmbChannelType.ListIndex = 1
            If iCompType = 1 Then       '恒温箱补偿
                Me.cmbCompType.ListIndex = 0
            ElseIf iCompType = 2 Then   '冷端补偿
                Me.cmbCompType.ListIndex = 1
                Me.cmbCompChannel.ListIndex = iCompChannel - 1
            End If
        Case 3  '传感器
            Me.cmbChannelType.ListIndex = 2
        End Select
        Me.cmbSensorType.ListIndex = -1
        For i = 0 To Me.cmbSensorType.ListCount - 1
            If Me.cmbSensorType.ItemData(i) = iSensorType Then
                Me.cmbSensorType.ListIndex = i
                Exit For
            End If
        Next i
        If bUseDefault Then
            Me.chkDefault.Value = vbChecked
            Me.txtA = Empty
            Me.txtB = Empty
            'section 1
            If iChannelType = 3 Then
                Me.txtMinValue = CStr(fMinValue)
                Me.txtMaxValue = CStr(fMaxValue)
            End If
        Else
            Me.chkDefault.Value = vbUnchecked
            Me.txtA = CStr(fA)
            Me.txtB = CStr(fB)
            'section 1
            Me.txtMinValue = Empty
            Me.txtMaxValue = Empty
        End If
        Me.cmbCalculate2.ListIndex = -1
        For i = 0 To Me.cmbCalculate2.ListCount - 1
            If Me.cmbCalculate2.ItemData(i) = iCalculate2 Then
                Me.cmbCalculate2.ListIndex = i
                Exit For
            End If
        Next i
    End If
End Sub

Private Sub GetValFromDB()
    If adoPrimaryRS.BOF Or adoPrimaryRS.EOF Then Exit Sub
    With adoPrimaryRS
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
    End With
End Sub

Private Sub SetValToDB()
    'If adoPrimaryRS.BOF Or adoPrimaryRS.EOF Then Exit Sub
    
    With adoPrimaryRS
        .Fields("Used") = True
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
    End With
End Sub

Private Sub LockContrl(Optional bLock As Boolean = True)
    Dim i As Long
    
    If bLock Then
        Me.cmdPaste.Enabled = False
        'section 1
        Me.txtMinValue.Enabled = False
        Me.txtMaxValue.Enabled = False
        'section 2
        Me.cmbChannelType.Enabled = False
        Select Case iChannelType
        Case 1  '热电阻
            Me.txtCompParameter.Enabled = False
        Case 2  '热电偶
            If iCompType = 1 Then       '恒温箱补偿
            ElseIf iCompType = 2 Then   '冷端补偿
                Me.cmbCompType.Enabled = False
                Me.cmbCompChannel.Enabled = False
            End If
        Case 3  '传感器
        End Select
        Me.cmbCompType.Enabled = False
        Me.cmbSensorType.Enabled = False
        Me.chkDefault.Enabled = False
        Me.txtA.Enabled = False
        Me.txtB.Enabled = False
        Me.cmbCalculate2.Enabled = False
    Else
        Me.cmdPaste.Enabled = bCopyed
        'section 2
        Me.cmbChannelType.Enabled = True
        Select Case iChannelType
        Case 1  '热电阻
            Me.txtCompParameter.Enabled = True
        Case 2  '热电偶
            If iCompType = 1 Then       '恒温箱补偿
                Me.cmbCompType.Enabled = True
            ElseIf iCompType = 2 Then   '冷端补偿
                Me.cmbCompType.Enabled = True
                Me.cmbCompChannel.Enabled = True
            End If
        Case 3  '传感器
        End Select
        Me.cmbSensorType.Enabled = True
        Me.chkDefault.Enabled = True
        If bUseDefault Then
            Me.chkDefault.Value = vbChecked
            Me.txtA.Enabled = False
            Me.txtB.Enabled = False
            'section 1
            Me.txtMinValue.Enabled = True
            Me.txtMaxValue.Enabled = True
        Else
            Me.chkDefault.Value = vbUnchecked
            Me.txtA.Enabled = True
            Me.txtB.Enabled = True
            'section 1
            Me.txtMinValue.Enabled = False
            Me.txtMaxValue.Enabled = False
        End If
        Me.cmbCalculate2.Enabled = True
    End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
    'adoPrimaryRS.Filter = ""
    Set adoPrimaryRS = Nothing
End Sub

