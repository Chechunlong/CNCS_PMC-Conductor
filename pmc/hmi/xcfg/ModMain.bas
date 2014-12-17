Attribute VB_Name = "ModMain"
Option Explicit

Public Const xcfgRun = 1
Public Const xcfgConfig = 2

'通道参数
Public Type ChannelInfo
    Used As Boolean
    ChannelType As String
    SensorType As String
    CompNo As String
    CompType As String
    CompResistance As String
    Calculate2 As String
    A As String
    B As String
End Type

'=======================================================================
'全局变量
'串口
Public glPort As Long
Public glStatus As Long
Public glStaNo As Long
Public glRealBt As Long
'接收缓冲区
Public gabRevBuffer(30000) As Byte
'发送命令
Public gabCommand() As Byte
'公共参数
Public glWsNo As Long
Public glSpeed As Long
Public glBt As Long
Public glTemperature As Long
Public glChNum As Long
'通道参数
Public grdPara As ADODB.Recordset
Public gaPara(1 To 99) As String * 32
Public gParaInfo(1 To 99) As ChannelInfo
'自动刷新模式
Public glRefresh As Long
'显示状态
Public glShowMode As Long

Public Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)
Public Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal length As Long)
Public Const HWND_TOPMOST = -1
Public Const SWP_NOMOVE = &H2
Public Const SWP_NOSIZE = &H1
Public Declare Function SetWindowPos Lib "user32" (ByVal hwnd As Long, ByVal hWndInsertAfter As Long, ByVal x As Long, ByVal y As Long, ByVal cx As Long, ByVal cy As Long, ByVal wFlags As Long) As Long

'检查通讯返回的信息
Public Function CheckMessage(length As Long) As Boolean
    'too short
    If length < 8 Then
        length = -100
        GoTo MessageError
    End If
        
    'Check LRC
    Dim baLRC(2) As Byte
    GetLRC gabRevBuffer, length - 3, baLRC
    If gabRevBuffer(length - 3) = baLRC(0) And gabRevBuffer(length - 2) = baLRC(1) Then
    Else
        GetLRC gabRevBuffer, length - 3, baLRC
        length = -103
        GoTo MessageError
    End If
            
    'Chech Function Code
    If gabRevBuffer(3) And &H8 Then
        length = -200 - gabRevBuffer(4) * &H10 - gabRevBuffer(5)
        GoTo MessageError
    End If
                
    CheckMessage = True
    Exit Function

MessageError:
    CheckMessage = False
End Function

Sub GetLRC(SrcBuf() As Byte, length, lrc() As Byte)
    Dim bytTemp As Byte
    bytTemp = SrcBuf(LBound(SrcBuf) + 1)
    
    Dim i As Long
    For i = LBound(SrcBuf) + 2 To LBound(SrcBuf) + length - 1
        bytTemp = bytTemp Xor SrcBuf(i)
    Next i
    
    lrc(LBound(lrc)) = Asc(Hex((bytTemp And &HF0) \ 16))
    lrc(LBound(lrc) + 1) = Asc(Hex(bytTemp And &HF))
End Sub

Public Sub SetChPara()
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
    If grdPara.Fields("Used") = True Then
        With grdPara
            iChannelNo = .Fields("ChannelNo")
            iChannelType = .Fields("ChannelType")
            
            Mid(gaPara(iChannelNo), 1, 2) = Format(iChannelType, "00")
            Select Case iChannelType
            Case 1  '热电阻
                fCompResistance = .Fields("CompResistance")
                If fCompResistance > 9.9 Then fCompResistance = 9.9
                If fCompResistance < 0 Then fCompResistance = 0
                Mid(gaPara(iChannelNo), 11, 2) = Format(fCompResistance * 10, "00")
            Case 2  '热电偶
                iCompType = .Fields("CompType")
                Select Case iCompType
                Case 1
                    Mid(gaPara(iChannelNo), 11, 2) = "00" '恒温箱
                Case 2
                    iCompNo = .Fields("CompChannel")
                    Mid(gaPara(iChannelNo), 11, 2) = Format(iCompNo, "00")  '冷端补偿
                End Select
            Case 3  '传感器
            End Select
            iSensorType = .Fields("SensorType")
            Mid(gaPara(iChannelNo), 1, 2) = Format(iSensorType, "00")
            iCalculate2 = .Fields("Calculate2")
            Mid(gaPara(iChannelNo), 13, 2) = Format(iCalculate2, "00")
            bUseDefault = .Fields("UseDefault")
            If bUseDefault And (iChannelType <> 3) Then
                Mid(gaPara(iChannelNo), 9, 2) = "00"
            Else
                Mid(gaPara(iChannelNo), 9, 2) = "01"
            End If
            fA = .Fields("A")
            fB = .Fields("B")
            Mid(gaPara(iChannelNo), 15, 6) = YTSingletoString(fA)
            Mid(gaPara(iChannelNo), 21, 6) = YTSingletoString(fB)
        End With
    
        gParaInfo(iChannelNo).Used = True
        gParaInfo(iChannelNo).A = CStr(fA)
        gParaInfo(iChannelNo).B = CStr(fB)
        Select Case iChannelType
        Case 1
            gParaInfo(iChannelNo).ChannelType = "热电阻"
            gParaInfo(iChannelNo).CompResistance = Format(fCompResistance, "0.0") & "Ω"
            gParaInfo(iChannelNo).CompType = ""
            gParaInfo(iChannelNo).CompNo = ""
        Case 2
            gParaInfo(iChannelNo).ChannelType = "热电偶"
            Select Case iCompType
            Case 1
                gParaInfo(iChannelNo).CompType = "恒温箱补偿"
                gParaInfo(iChannelNo).CompNo = ""
            Case 2
                gParaInfo(iChannelNo).CompType = "冷端补偿"
                gParaInfo(iChannelNo).CompNo = CStr(iCompNo)
            Case Else
                gParaInfo(iChannelNo).CompType = ""
                gParaInfo(iChannelNo).CompNo = ""
            End Select
            gParaInfo(iChannelNo).CompResistance = ""
        Case 3
            gParaInfo(iChannelNo).ChannelType = "传感器"
            gParaInfo(iChannelNo).CompResistance = ""
            gParaInfo(iChannelNo).CompType = ""
            gParaInfo(iChannelNo).CompNo = ""
        Case Else
            gParaInfo(iChannelNo).ChannelType = ""
            gParaInfo(iChannelNo).CompResistance = ""
            gParaInfo(iChannelNo).CompNo = ""
            gParaInfo(iChannelNo).CompType = ""
        End Select
        Select Case iSensorType
        Case 0
            gParaInfo(iChannelNo).SensorType = "Cu50"
        Case 1
            gParaInfo(iChannelNo).SensorType = "Cu100"
        Case 2
            gParaInfo(iChannelNo).SensorType = "BA1"
        Case 3
            gParaInfo(iChannelNo).SensorType = "BA2"
        Case 4
            gParaInfo(iChannelNo).SensorType = "Pt100"
        Case 5
            gParaInfo(iChannelNo).SensorType = "K"
        Case 6
            gParaInfo(iChannelNo).SensorType = "E"
        Case 7
            gParaInfo(iChannelNo).SensorType = "G53"
        Case 8
            gParaInfo(iChannelNo).SensorType = "EA2"
        Case 9
            gParaInfo(iChannelNo).SensorType = "0-5V"
        Case 10
            gParaInfo(iChannelNo).SensorType = "1-5V"
        Case 11
            gParaInfo(iChannelNo).SensorType = "0-10mA"
        Case 12
            gParaInfo(iChannelNo).SensorType = "4-20mA"
        Case 13
            gParaInfo(iChannelNo).SensorType = "0-10V"
        Case Else
            gParaInfo(iChannelNo).SensorType = ""
        End Select
        Select Case iCalculate2
        Case 0
            gParaInfo(iChannelNo).Calculate2 = "y=x"
        Case 3
            gParaInfo(iChannelNo).Calculate2 = "y=sqrt(x)"
        Case 4
            gParaInfo(iChannelNo).Calculate2 = "y=x/2+z0/2"
        Case 5
            gParaInfo(iChannelNo).Calculate2 = "y=x/4+3*z0/4"
        Case 6
            gParaInfo(iChannelNo).Calculate2 = "y=x/8+7z0/8"
        Case Else
            gParaInfo(iChannelNo).Calculate2 = ""
        End Select
    Else
        iChannelNo = grdPara.Fields("ChannelNo")
        gaPara(iChannelNo) = String(32, "0")
        Mid(gaPara(iChannelNo), 1, 1) = "8"
        gParaInfo(iChannelNo).Used = False
    End If
End Sub

Public Sub Main()
    Dim lRet As Long
    lRet = init_spac()
    If 1 <> lRet Then
        MsgBox "初始化串口失败，错误码：" & lRet, vbOKOnly + vbCritical, "错误"
    Else
        Dim fMainForm As formMain
        Set fMainForm = New formMain
        fMainForm.Show
        
        Dim strCmd As String
        strCmd = Command()
                
        If ("/st" = strCmd Or "-st" = strCmd) Then
            Debug.Print SetWindowPos(fMainForm.hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE Or SWP_NOSIZE)
        End If
    End If
End Sub
