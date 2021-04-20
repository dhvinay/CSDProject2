Attribute VB_Name = "util"
'#If VBA7 Then
    Private Declare PtrSafe Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal Length As Long)
'#Else
'    Private Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal Length As Long)
'#End If

Private Const MIN_INT64 = -9.22337203685478E+18
Private Const MAX_INT64 = 9.22337203685478E+18
Private Const MIN_UINT64 = 0
Private Const SIZE_UINT64 = 1.84467440737096E+19

Private Const MIN_INT32 = -2147483647
Private Const MAX_INT32 = 2147483647
Private Const MIN_UINT32 = 0
Private Const SIZE_UINT32 = 4294967296#

Private Const MAX_INT16 = 32767
Private Const MIN_INT16 = -32768
Private Const MIN_UINT16 = 0
Private Const SIZE_UINT16 = 65536

Private Const MAX_INT8 = 127
Private Const MIN_INT8 = 128
Private Const MIN_UINT8 = 0
Private Const SIZE_UINT8 = 256
    
Public Function paramToBytes(ByVal val As Currency, ByVal paramType As String, ByRef byteArray() As Byte)
    
    Dim size As Long
    Dim isSigned As Boolean
    Dim isFloat As Boolean
    Dim isDouble As Boolean
    Dim valByte As Byte
    Dim valInt As Integer
    Dim valLong As Long
    Dim valFloat As Single
    Dim valDouble As Double
    
    'reset byteArray
    For i = 0 To 7
        Let byteArray(i) = 0
    Next i
    
    size = paramTypeLength(paramType)                           'get size

    'first check the type of data
    If Left(paramType, 4) = "sint" Or _
       Left(paramType, 3) = "int" Then                          'get signed/unsigned
        isSigned = True
        isFloat = False
        isDouble = False
    Else
        isSigned = False
        
        If paramType = "float" Then                             'get float
            isFloat = True                                      '4 bytes
            isDouble = False
        ElseIf paramType = "double" Then                        'get double
            isFloat = False
            isDouble = True                                     '8 bytes
        ElseIf Left(paramType, 4) = "real" Then                 'get float
            If size > 4 Then
                isFloat = False
                isDouble = True                                 '8 bytes
            Else
                isFloat = True                                  '4 bytes
                isDouble = False
            End If
        End If
    
    End If

    'start processing data
    If isDouble Then                                            'process as double
    
        valDouble = val
        
        CopyMemory byteArray(0), valDouble, size                'copy to bytes array
        On Error Resume Next
    
    ElseIf isFloat Then                                         'process as float
    
        valFloat = val
        
        CopyMemory byteArray(0), valFloat, size                 'copy to bytes array
        On Error Resume Next
    
    Else                                                        'process as integer
    
        If size = 1 Then
            
            If isSigned And _
               val < MIN_UINT8 Then
                val = val + SIZE_UINT8                          'convert signed to unsigned
            End If
            
            valByte = val
            
            CopyMemory byteArray(0), valByte, size              'copy to bytes array
            On Error Resume Next
        
        ElseIf size = 2 Then
            
            If Not isSigned And _
               val > MAX_INT16 Then
                val = val - SIZE_UINT16                         'convert unsigned to signed
            End If
            
            valInt = val
            
            CopyMemory byteArray(0), valInt, size               'copy to bytes array
            On Error Resume Next
        
        ElseIf size = 4 Then
            
            If Not isSigned And _
               val > MAX_INT32 Then
                val = val - SIZE_UINT32                         'convert unsigned to signed
            End If
            
            valLong = val
            
            CopyMemory byteArray(0), valLong, size              'copy to bytes array
            On Error Resume Next
        
        ElseIf size = 8 Then
        
            'TODO: Handle 64-bit values properly
            'this code only handles values up to 32 bits
            'negative signed values are handled incorrectly!
            
            'Show warning if value is larger then 32-bit
            If val >= SIZE_UINT32 Then
                If errorMessage("Handling values larger then 32-bit is not supported yet!") Then         'Non numeric value
                    Exit Function
                End If
            End If
            
            'Handle 32-bit value
            If Not isSigned And _
               val > MAX_INT32 Then
                val = val - SIZE_UINT32                         'convert unsigned to signed
            End If
            
            valLong = val
            
            CopyMemory byteArray(0), valLong, 4                 'copy to bytes array
            On Error Resume Next
        
        End If
    
    End If

End Function


Public Function bytesToParam(ByVal paramType As String, ByRef byteArray() As Byte, ByRef isFloat As Boolean, ByRef isDouble As Boolean) As Currency
    
    Dim size As Long
    Dim isSigned As Boolean
    Dim valByte As Byte
    Dim valInt As Integer
    Dim valLong As Long
    Dim valFloat As Single
    Dim valDouble As Double
    
    size = paramTypeLength(paramType)                           'get size

    'first check the type of data
    If Left(paramType, 4) = "sint" Or _
       Left(paramType, 3) = "int" Then                          'get signed/unsigned
        isSigned = True
        isFloat = False
        isDouble = False
    Else
        isSigned = False
        
        If paramType = "float" Then                             'get float
            isFloat = True                                      '4 bytes
            isDouble = False
        ElseIf paramType = "double" Then                        'get double
            isFloat = False
            isDouble = True                                     '8 bytes
        ElseIf Left(paramType, 4) = "real" Then                 'get float
            If size > 4 Then
                isFloat = False
                isDouble = True                                 '8 bytes
            Else
                isFloat = True                                  '4 bytes
                isDouble = False
            End If
        Else
            isFloat = False
            isDouble = False
        End If
    
    End If

    'start processing data
    If isDouble Then                                            'process as double
    
        CopyMemory valDouble, byteArray(0), size                'copy from bytes array
        
        bytesToParam = valDouble
        
        On Error Resume Next
    
    ElseIf isFloat Then                                         'process as float
        
        CopyMemory valFloat, byteArray(0), size                 'copy from bytes array
        On Error Resume Next
    
        bytesToParam = valFloat
    
    Else                                                        'process as integer
    
        If size = 1 Then
            
            CopyMemory valByte, byteArray(0), size              'copy from bytes array
            On Error Resume Next
            
            If isSigned And _
               valByte > MAX_INT8 Then
                bytesToParam = valByte - SIZE_UINT8             'convert signed to unsigned
            Else
                bytesToParam = valByte
            End If
        
        ElseIf size = 2 Then
            
            CopyMemory valInt, byteArray(0), size               'copy from bytes array
            On Error Resume Next
            
            If Not isSigned And _
               valInt < MIN_UINT16 Then
                bytesToParam = valInt + SIZE_UINT16             'convert signed to unsigned
            Else
                bytesToParam = valInt
            End If
        
        ElseIf size = 4 Then
            
            CopyMemory valLong, byteArray(0), size              'copy from bytes array
            On Error Resume Next
            
            If Not isSigned And _
               valLong < MIN_UINT32 Then
                bytesToParam = valLong + SIZE_UINT32            'convert signed to unsigned
            Else
                bytesToParam = valLong
            End If
        
        ElseIf size = 8 Then
        
            'TODO: Handle 64-bit values properly
            'this code only handles values up to 32 bits
            'negative signed values are handled incorrectly!
        
            'Show warning if bits above 32nd bit are set
            CopyMemory valLong, byteArray(4), 4                 'copy from bytes array
            On Error Resume Next
            
            If Not valLong = 0 Then
                If errorMessage("Handling values larger then 32-bit is not supported yet!") Then         'Non numeric value
                    Exit Function
                End If
            End If
            
            'Handle 32-bit value
            CopyMemory valLong, byteArray(0), 4                 'copy from bytes array
            On Error Resume Next
            
            If Not isSigned And _
               valLong < MIN_UINT32 Then
                bytesToParam = valLong + SIZE_UINT32            'convert signed to unsigned
            Else
                bytesToParam = valLong
            End If
        
        End If
    
    End If

End Function



Public Sub generateEeprom(ByVal fileName As String, ByVal columnNum As Long)

    Dim fnum As Long
    Dim data(0 To &H67FF) As Byte
    Dim address As Variant
    Dim size As Long
    Dim val As Currency
    Dim valLong As Long
    Dim valFloat As Single
    Dim valDouble As Double
    Dim tmpVal As Currency
    Dim i As Long
    Dim paramType As Variant
    Dim J As Long
    Dim byteArray(8) As Byte
    
    'initialize Eeprom data
    For i = 0 To &H67FF
        Let data(i) = &HFF
    Next i

    i = 8
    Do While Not IsEmpty(Cells(i, 3))
        If Not IsEmpty(Cells(i, 1)) Then                                'check if there is an address
        
            address = Cells(i, 1).Value                                 'get address
            Mid(address, 1, 2) = "&H"                                   'prefix for hex value
        
            val = 0
            
            If IsNumeric(Cells(i, columnNum).Value) Then
                val = Cells(i, columnNum).Value                         'get value
            Else
                If errorMessage("0x" & VBA.Strings.Right(address, 4) & ", " & _
                                "column " & Cells(7, columnNum).Value) Then         'Non numeric value
                    Exit Sub
                End If
            End If
                
            paramType = Cells(i, 2).Value                           'get parameter type
            size = paramTypeLength(paramType)                       'get number of bytes
            
            Call paramToBytes(val, paramType, byteArray)
            
            J = 0
            While J < size
                
                data(address + J) = byteArray(J)                    'write data
                
                J = J + 1
            Wend
            
        
        End If
        
        i = i + 1
    Loop
    
    'open file
    fnum = FreeFile()
    Open fileName For Binary Access Write As #fnum
    
    'write Eeprom data to file
    For i = 0 To &H67FF
        Put #fnum, , data(i)
    Next i
    
    Close #fnum

End Sub


Sub exportBytes()

    Dim address As Variant
    Dim size As Long
    Dim val As Currency
    Dim tmpVal As Currency
    Dim rowNum As Long
    Dim columnNum As Long
    Dim i As Long
    Dim paramType As Variant
    Dim J As Long
    Dim byteArray(8) As Byte
     
    'delete all data
    Sheets("Bytes").Range("A8:A65536").EntireRow.Delete
    
    'disable screen updating and calculations
    Application.ScreenUpdating = False
    Application.Calculation = xlCalculationManual
    
    'format units column as text
    Sheets("Bytes").Cells(8, 4).EntireColumn.NumberFormat = "@"
    
    'Set columns
    With Range(Sheets("Bytes").Cells(8, 5), Sheets("Bytes").Cells(65535, 10))
        .NumberFormat = "@"
        .FormatConditions.Delete
        .HorizontalAlignment = xlCenter
    End With
    
    i = 8
    rowNum = 8
    Do While Not IsEmpty(Cells(i, 3))
        If Not IsEmpty(Cells(i, 1)) Then                                'check if there is an address
        
            address = Cells(i, 1).Value                                 'get address
            Mid(address, 1, 2) = "&H"                                   'prefix for hex value
        
            paramType = Cells(i, 2).Value                               'get parameter type
            size = paramTypeLength(paramType)                           'get number of bytes
            
'            With Range(Sheets("Bytes").Cells(rowNum, 5), Sheets("Bytes").Cells(rowNum + size - 1, 9))
'                .FormatConditions.Add xlExpression, , "=COUNTIF(RC5:RC12;RC)<3"
'                .FormatConditions(1).Interior.PatternColorIndex = 6
'                .FormatConditions(1).Interior.Pattern = xlLightUp
'            End With
            
            With Range(Sheets("Bytes").Cells(rowNum, 6), Sheets("Bytes").Cells(rowNum + size - 1, 10))
                .FormatConditions.Add xlCellValue, xlNotEqual, "=LOOKUP(R6C;R7C5:R7C10;RC5:RC10)"
                .FormatConditions(1).Interior.PatternColorIndex = 3
                .FormatConditions(1).Interior.Pattern = xlLightUp
            End With
            
            With Sheets("Bytes")
                With Range(.Cells(rowNum, 2), .Cells(rowNum + size - 1, 2))
                    .Merge
                    .VerticalAlignment = xlCenter
                End With
                With Range(.Cells(rowNum, 3), .Cells(rowNum + size - 1, 3))
                    .Merge
                    .VerticalAlignment = xlCenter
                End With
                With Range(.Cells(rowNum, 4), .Cells(rowNum + size - 1, 4))
                    .Merge
                    .VerticalAlignment = xlCenter
                End With
                With Range(.Cells(rowNum, 12), .Cells(rowNum + size - 1, 11))
                    .Merge
                    .VerticalAlignment = xlCenter
                End With
                .Cells(rowNum, 2).Value = Cells(i, 2).Value
                .Cells(rowNum, 3).Value = Cells(i, 3).Value
                .Cells(rowNum, 4).Value = Cells(i, 4).Value
                .Cells(rowNum, 12).Value = Cells(i, 12).Value
                Range(.Cells(rowNum, 1), .Cells(rowNum, 12)).Borders(xlEdgeTop).Weight = xlMedium
            End With
            
            For columnNum = 5 To 11
                If IsNumeric(Cells(i, columnNum).Value) Then
                    If Not IsEmpty(Cells(i, columnNum).Value) Then
                    
                        val = Cells(i, columnNum).Value                         'get value
                        
                        Call paramToBytes(val, paramType, byteArray)
                        
                        J = 0
                        While J < size
                            
                            Sheets("Bytes").Cells(rowNum + J, 1).Value = "0x" & VBA.Strings.Right("0000" & VBA.Hex(address + J), 4)
                            With Sheets("Bytes").Cells(rowNum + J, columnNum)
                                .Value = VBA.Strings.Right("00" & VBA.Hex(byteArray(J)), 2)
                                .Errors(xlNumberAsText).Ignore = True
                            End With
 
                            J = J + 1
                        
                        Wend
                
                    End If
                Else
                    If errorMessage("0x" & VBA.Strings.Right(address, 4) & ", " & _
                                    "column " & Cells(7, columnNum).Value) Then         'Non numeric value
                        Exit Sub
                    End If
                End If
            Next columnNum
            
            rowNum = rowNum + size
        
        Else
        
            If Not Cells(i, 3).Value = "checksum" Then
                Range(Sheets("Bytes").Cells(rowNum, 1), Sheets("Bytes").Cells(rowNum, 11)).Interior.ColorIndex = 15
                Sheets("Bytes").Cells(rowNum, 3).Value = Cells(i, 3)
                Sheets("Bytes").Cells(rowNum, 3).Font.Bold = True
                rowNum = rowNum + 1
            End If
        
        End If
        
        i = i + 1
    Loop

    'enable screen updating and calculations
    Application.ScreenUpdating = True
    Application.Calculation = xlCalculationAutomatic
    
    Sheets("Bytes").Select
    
    Call MsgBox("Eeprom values successfully exported to bytes!", vbOKOnly + vbInformation, "Export to bytes")
    

End Sub


Public Function paramTypeLength(ByVal paramType As String) As Long

    If paramType = "bool" Or _
       paramType = "uint8" Or _
       paramType = "sint8" Or _
       paramType = "int8_T" Or _
       paramType = "uint8_T" Or _
       paramType = "char_T" Or _
       paramType = "uchar_T" Or _
       paramType = "byte_T" Or _
       paramType = "boolean_T" Or _
       paramType = "enum" Then
        paramTypeLength = 1
    ElseIf paramType = "uint16" Or _
           paramType = "int16_T" Or _
           paramType = "uint16_T" Or _
           paramType = "sint16" Then
        paramTypeLength = 2
    ElseIf paramType = "uint32" Or _
           paramType = "sint32" Or _
           paramType = "int32_T" Or _
           paramType = "uint32_T" Or _
           paramType = "real32_T" Or _
           paramType = "int_T" Or _
           paramType = "uint_T" Or _
           paramType = "ulong_T" Or _
           paramType = "float" Or _
           paramType = "real32" Then
        paramTypeLength = 4
    ElseIf paramType = "uint64" Or _
           paramType = "sint64" Or _
           paramType = "real64" Or _
           paramType = "real_T" Or _
           paramType = "real64_T" Or _
           paramType = "time_T" Or _
           paramType = "double" Then
        paramTypeLength = 8
    Else
        paramTypeLength = 1                                         'should not come here
    End If

End Function


Public Function errorMessage(address As Variant) As Boolean
    
    Dim message
    Dim response

    message = "Invalid value for address " & address & Chr(13) & Chr(10) & "Continue?"
    
    response = MsgBox(message, vbYesNo + vbCritical, "Error Message")
    
    If response = vbYes Then
        errorMessage = False
    Else
        errorMessage = True
    End If

End Function


Public Function checksum(ParamArray args() As Variant) As Variant

    Dim s As Long                                                   ' Sum
    Dim i As Long                                                   ' Increment
    Dim v As Variant
    Dim val As Currency
    Dim byteArray(8) As Byte

    
    s = 45
    i = 0
    
    Dim arg As Variant
    Dim b As Range
    Dim z As Range

    For Each arg In args()
    For Each b In arg.Areas
    For Each z In b.Cells                                           ' for every cell
        
        If Not IsEmpty(z.Value) Then
        
            v = z.Value                                             ' cell contents
        
            If IsNumeric(v) Then
            
                val = v                                             ' cell value
                paramType = Cells(z.Row, 2).Value                   'get parameter type
                size = paramTypeLength(paramType)                   'get number of bytes
               
                Call paramToBytes(val, paramType, byteArray)
                
                J = 0
                While J < size
                
                   
                    s = s + (byteArray(J) * ((i And &H7F&) + 1))
                        
                    i = i + 1
                    J = J + 1
                Wend
                
            Else
        
                Let checksum = CVErr(xlErrNum)
                Exit Function                                       ' #VALUE! - no numeric value
            
            End If
        
        End If
        
    Next z
    Next b
    Next arg
    
    Let checksum = s And &HFFFF&

End Function


Public Function CheckLetter(ParamArray args() As Variant) As Variant

    Dim s As Long                       ' Sum
    Let s = 0
    Dim i As Long                       ' Increment
    Let i = 0
    Dim J As Long
    Let J = 1
    
    Dim arg As Variant
    Dim b As Range
    Dim z As Range

    For Each arg In args()
    For Each b In arg.Areas
    For Each z In b.Cells               ' for every cell
        
        If (Not IsEmpty(z.Value) And Not z.Value = 255) Then
        
            Dim v As Variant
            Dim x As Long
            Let v = z.Value             ' cell contents
        
            If v = "A" Then
                x = 1
            ElseIf v = "B" Then
                x = 2
            ElseIf v = "C" Then
                x = 3
            ElseIf v = "D" Then
                x = 4
            ElseIf v = "E" Then
                x = 5
            ElseIf v = "F" Then
                x = 6
            ElseIf v = "G" Then
                x = 7
            ElseIf v = "H" Then
                x = 8
            ElseIf v = "I" Then
                x = 0
            ElseIf v = "J" Then
                x = 1
            ElseIf v = "K" Then
                x = 2
            ElseIf v = "L" Then
                x = 3
            ElseIf v = "M" Then
                x = 4
            ElseIf v = "N" Then
                x = 5
            ElseIf v = "O" Then
                x = 0
            ElseIf v = "P" Then
                x = 7
            ElseIf v = "Q" Then
                x = 0
            ElseIf v = "R" Then
                x = 9
            ElseIf v = "S" Then
                x = 2
            ElseIf v = "T" Then
                x = 3
            ElseIf v = "U" Then
                x = 4
            ElseIf v = "V" Then
                x = 5
            ElseIf v = "W" Then
                x = 6
            ElseIf v = "X" Then
                x = 7
            ElseIf v = "Y" Then
                x = 8
            ElseIf v = "Z" Then
                x = 9
            ElseIf IsNumeric(v) And v >= 0 And v <= 9 Then
                x = v
            Else
                Let s = 0
                GoTo After_For
            End If
            
            If J = 1 Then
                i = 8
            ElseIf J = 2 Then
                i = 7
            ElseIf J = 3 Then
                i = 6
            ElseIf J = 4 Then
                i = 5
            ElseIf J = 5 Then
                i = 4
            ElseIf J = 6 Then
                i = 3
            ElseIf J = 7 Then
                i = 2
            ElseIf J = 8 Then
                i = 10
            ElseIf J = 9 Then
                i = 0
            ElseIf J = 10 Then
                i = 9
            ElseIf J = 11 Then
                i = 8
            ElseIf J = 12 Then
                i = 7
            ElseIf J = 13 Then
                i = 6
            ElseIf J = 14 Then
                i = 5
            ElseIf J = 15 Then
                i = 4
            ElseIf J = 16 Then
                i = 3
            ElseIf J = 17 Then
                i = 2
            Else
                Let s = 0
                GoTo After_For
            End If
            
            ' CheckLetter calculation
            Let s = s + (x * i)
            Let J = J + 1
            
            If J = 9 Then
                Let J = 10
            End If
                   
        Else
            Let s = 0
            GoTo After_For
        End If
        
    Next z
    Next b
    Next arg
    
After_For:
    If s = 0 Then
        Let CheckLetter = 255
    Else
        Dim r As Double
        Let r = s / 11
        Let s = Int(r * 10) Mod 10
        
        If s = 1 Then
            Let CheckLetter = "V"
        ElseIf s = 2 Then
            Let CheckLetter = "T"
        ElseIf s = 3 Then
            Let CheckLetter = "A"
        ElseIf s = 4 Then
            Let CheckLetter = "P"
        ElseIf s = 5 Then
            Let CheckLetter = "L"
        ElseIf s = 6 Then
            Let CheckLetter = "K"
        ElseIf s = 7 Then
            Let CheckLetter = "H"
        ElseIf s = 8 Then
            Let CheckLetter = "J"
        ElseIf s = 9 Then
            Let CheckLetter = "E"
        ElseIf s = 0 Then
            Let CheckLetter = "C"
        Else
            Let CheckLetter = 255
        End If
    End If

End Function


Public Function TrimAll(ByVal ToTrim As String) As String

    Dim Start, Finish As Long
    Dim ToEliminate As String

    ' Base condition test
    If Len(ToTrim) = 0 Then
        TrimAll = ""
        Exit Function
    End If

    ' Define the characters that we want to trim off
    ToEliminate = Chr(0) & Chr(8) & Chr(9) & Chr(10) & _
                  Chr(13) & Chr(32)

    ' Find the beginning of non-blank string
    Start = 1
    While InStr(1, ToEliminate, Mid$(ToTrim, Start, 1), _
                vbTextCompare) <> 0 And Start <= Len(ToTrim)
        Start = Start + 1
    Wend

    ' Find the end of non-blank string
    Finish = Len(ToTrim)
    While InStr(1, ToEliminate, Mid$(ToTrim, Finish, 1), _
                vbTextCompare) <> 0 And Finish > 1
        Finish = Finish - 1
    Wend
    '
    ' If the string is completely blank, Start is going to be greater
    ' than Finish
    '
    If Start > Finish Then
        TrimAll = ""
        Exit Function
    End If

    ' Trim out the real contents
    TrimAll = Mid$(ToTrim, Start, Finish - Start + 1)

End Function


Public Function Min(ByVal v1 As Long, ByVal v2 As Long) As Long

    Min = v1

    If v2 < v1 Then
        Min = v2
    End If

End Function


Public Function Max(ByVal v1 As Long, ByVal v2 As Long) As Long

    Max = v1

    If v2 > v1 Then
        Max = v2
    End If

End Function

