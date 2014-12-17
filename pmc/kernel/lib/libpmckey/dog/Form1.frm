VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "get pair"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command1 
      Caption         =   "do it now!"
      Height          =   1155
      Left            =   660
      TabIndex        =   0
      Top             =   840
      Width           =   3435
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Function getBegin(strNow As String) As Boolean
    
    'Query -----> Response            Query -----> Response
    'Query -----> Response            Query -----> Response
    
    If strNow = "Query -----> Response            Query -----> Response" Then
        getBegin = True
    Else
        getBegin = False
    End If
    
'    Static strPrv As String
'    Static nBegin As Long
'
'    If strNow = "Query" Then
'        If strPrv = "Response" Then
'            nBegin = nBegin + 1
'        Else
'            nBegin = 0
'        End If
'    ElseIf strNow = "----->" Then
'        If strPrv = "Query" Then
'            nBegin = nBegin + 1
'        Else
'            nBegin = 0
'        End If
'    ElseIf strNow = "Response" Then
'        If strPrv = "----->" Then
'            nBegin = nBegin + 1
'        Else
'            nBegin = 0
'        End If
'    Else
'        nBegin = 0
'    End If
'
'    strPrv = strNow
'
'    If nBegin > 4 Then
'        nBegin = 0
'        getBegin = True
'    Else
'        getBegin = False
'    End If

End Function

Private Function GetHexString(str As String, last As Boolean) As String
    '0x01,0x0B,0x38,0xA7,
    
    If Not last Then
        GetHexString = "0x" & Mid(str, 1, 2) & "," & _
                       "0x" & Mid(str, 3, 2) & "," & _
                       "0x" & Mid(str, 5, 2) & "," & _
                       "0x" & Mid(str, 7, 2) & ","
    Else
        GetHexString = "0x" & Mid(str, 1, 2) & "," & _
                       "0x" & Mid(str, 3, 2) & "," & _
                       "0x" & Mid(str, 5, 2) & "," & _
                       "0x" & Mid(str, 7, 2)
    End If
End Function

Private Sub Command1_Click()
    
    Dim strTmp As String
    Dim i As Long
    Dim j As Long
    Dim nCell As Long
    Dim strArray(0 To 14 * 200 - 1) As String
    
    nCell = 0
    
    Dim strFile As String
    strFile = App.Path & "\input.txt"
    
    Open strFile For Input As #1
    
    Do
        Input #1, strTmp
        
        If getBegin(strTmp) Then
        
            For i = 0 To 199
                Input #1, strArray(nCell * 200 + i)
            Next
            
            Debug.Print "Cell" & (nCell + 1), strArray(nCell * 200)
            nCell = nCell + 1
        
        End If
        
    Loop Until (EOF(1))
    
    Close #1
    
    
    Dim strHeadFile As String
    strHeadFile = App.Path & "\pair.h"
    Open strHeadFile For Output As #2
    
    Print #2, "#ifndef pair_h"
    Print #2, "#define pair_h"
    Print #2, ""
    
    Print #2, "//欲查询数据"
    Print #2, "unsigned char queryData[]="
    Print #2, "{"
    For i = 0 To 13
        Print #2, vbTab & "// cell - " & 8 + 4 * i
        For j = 0 To 99
            If j = 99 And i = 13 Then
                Print #2, vbTab & GetHexString(strArray(i * 200 + j * 2), True)
            Else
                Print #2, vbTab & GetHexString(strArray(i * 200 + j * 2), False)
            End If
        Next j
    Next i
    Print #2, "};"
    Print #2, ""
    
    Print #2, "//响应数据"
    Print #2, "unsigned char cmpqueryData[]="
    Print #2, "{"
    For i = 0 To 13
        Print #2, vbTab & "// cell - " & 8 + 4 * i
        For j = 0 To 99
            If j = 99 And i = 13 Then
                Print #2, vbTab & GetHexString(strArray(i * 200 + j * 2 + 1), True)
            Else
                Print #2, vbTab & GetHexString(strArray(i * 200 + j * 2 + 1), False)
            End If
        Next j
    Next i
    Print #2, "};"
    Print #2, ""
    
    Print #2, "#endif"
    Close #2

    'ok! we can create "pair.h" now
End Sub
