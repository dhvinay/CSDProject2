Attribute VB_Name = "custom"
'#If VBA7 Then
    Private Declare PtrSafe Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal Length As Long)
'#Else
'    Private Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal Length As Long)
'#End If
 
Sub readCustom1()
    
    Dim fileName As String
    fileName = Application.GetOpenFilename("EEPROM file (*.eep),*.eep", , "Open EEPROM file")
    If fileName = "False" Then Exit Sub
    
    Call readEeprom(fileName, 10)
    Call EepromToVIN("VIN custom 1", 10, 114)

End Sub


Sub readCustom2()
    
    Dim fileName As String
    fileName = Application.GetOpenFilename("EEPROM file (*.eep),*.eep", , "Open EEPROM file")
    If fileName = "False" Then Exit Sub
    
    Call readEeprom(fileName, 11)
    Call EepromToVIN("VIN custom 2", 11, 15)

End Sub


Sub generateCustom1()
    
    Dim fileName As String
    fileName = Application.GetSaveAsFilename("RGCH2_eeprom_custom1.eep", "EEPROM file (*.eep),*.eep", , "Save EEPROM file")
    If fileName = "False" Then Exit Sub
    
    Call generateEeprom(fileName, 10)
    
    Call MsgBox("EEP-file successfully generated!", vbOKOnly + vbInformation, "EEP-file Generation")

End Sub


Sub generateCustom2()
    
    Dim fileName As String
    fileName = Application.GetSaveAsFilename("RGCH2_eeprom_custom2.eep", "EEPROM file (*.eep),*.eep", , "Save EEPROM file")
    If fileName = "False" Then Exit Sub
    
    Call generateEeprom(fileName, 11)

    Call MsgBox("EEP-file successfully generated!", vbOKOnly + vbInformation, "EEP-file Generation")

End Sub


Sub readEeprom(ByVal fileName As String, ByVal columnNum As Long)

    Dim fnum As Long
    Dim data(0 To 32767) As Byte
    Dim address As Variant
    Dim size As Long
    Dim signed As Boolean
    Dim single_float As Boolean
    Dim double_float As Boolean
    Dim val As Currency
    Dim i As Long
    Dim paramType As Variant
    Dim J As Long
    Dim byteArray(8) As Byte
    Dim isFloat As Boolean
    Dim isDouble As Boolean
    Dim valFloat As Single
    Dim valDouble As Double
    Dim localFormula As String
    Dim oldFormula As String
    Dim k As Long
    
    'initialize Eeprom data
    For i = 0 To &H67FF
        Let data(i) = &HFF
    Next i
    
    'open file
    fnum = FreeFile()
    Open fileName For Binary Access Read As #fnum

    'write Eeprom data to file
    For i = 0 To 32767
        If Not EOF(fnum) Then
            Get #fnum, , data(i)
        End If
    Next i
    
    Close #fnum

    'disable screen updating and calculations
    Application.ScreenUpdating = False
    Application.Calculation = xlCalculationManual
    
    i = 8
    Do While Not IsEmpty(Cells(i, 3))
        If Not IsEmpty(Cells(i, 1)) Then                                'check if there is an address
        
            address = Cells(i, 1).Value                                 'get address
            Mid(address, 1, 2) = "&H"                                   'prefix for hex value
            
            paramType = Cells(i, 2).Value                               'get parameter type
            size = paramTypeLength(paramType)                           'get number of bytes
            
            val = 0
            
            'reset byteArray
            For k = 0 To 7
                Let byteArray(k) = 0
            Next k
            
            J = 0
            While J < size
                
                byteArray(J) = data(address + J)
                
                J = J + 1
            Wend
            
            val = bytesToParam(paramType, byteArray, isFloat, isDouble)
            
            With Cells(i, columnNum)
                If Not Cells(i, 3).Value = "checksum" Then                    'parameter was found, not crc or fileLength
                    If isFloat Then
                        'have to convert back to float to avoid losing decimals
                        valFloat = val
                        .Value = valFloat
                    ElseIf isDouble Then
                        'have to convert back to double to avoid losing decimals
                        valDouble = val
                        .Value = valDouble
                    Else
                        .Value = val
                    End If
                Else
                    'Set base formula in this cell, to get localized formula needed for FormatConditions
                    oldFormula = Cells(i + 1, columnNum).Formula
                    Cells(i + 1, columnNum).FormulaR1C1 = "=R" & i & "C"
                    localFormula = Cells(i + 1, columnNum).FormulaLocal
                    Cells(i + 1, columnNum).Formula = oldFormula

                    Cells(i + 1, columnNum).Value = val
                    Cells(i + 1, columnNum).NumberFormat = "General"
                    Cells(i + 1, columnNum).FormatConditions.Delete
                    Cells(i + 1, columnNum).FormatConditions.Add xlCellValue, xlNotEqual, localFormula

                    Cells(i + 1, columnNum).FormatConditions(1).Interior.PatternColorIndex = 3
                    Cells(i + 1, columnNum).FormatConditions(1).Interior.Pattern = xlLightUp
                End If
                'Set base formula in this cell, to get localized formula needed for FormatConditions
                oldFormula = .Formula
                .FormulaR1C1 = "=LOOKUP(R6C,R7C5:R7C10,RC5:RC10)"
                localFormula = .FormulaLocal
                .Formula = oldFormula
                
                .NumberFormat = "General"
                .FormatConditions.Delete
                .FormatConditions.Add xlCellValue, xlNotEqual, localFormula
                .FormatConditions(1).Interior.PatternColorIndex = 3
                .FormatConditions(1).Interior.Pattern = xlLightUp
            End With
        End If
        
        i = i + 1
    Loop

    'enable screen updating and calculations
    Application.ScreenUpdating = True
    Application.Calculation = xlCalculationAutomatic

    Call MsgBox("EEP-file successfully read!", vbOKOnly + vbInformation, "EEP-file Read")
    
End Sub

Sub EepromToVIN(ByVal Name As String, ByVal ColInput As Byte, ByVal ColOutput As Byte)

Dim VinRowNr As Double

VinRowNr = Application.Match("EEPROM_MACHINE_INFO_VIN", Range("C:C"), 0)
Cells(VinRowNr, ColOutput).Value = Name

    For i = 1 To 17
        Cells(VinRowNr + i, ColOutput).Value = Chr(Cells(VinRowNr + i, ColInput).Value)
    Next i

End Sub
