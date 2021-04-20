Attribute VB_Name = "readMaster"
Sub readMaster()

    Dim oFSO As New FileSystemObject
    Dim oFS
    Dim addressName(3) As String
    Dim fileName(4) As String
    Dim currentAddressName As Long
    Dim currentAddress As Long
    Dim nextRow As Long
    Dim startRow As Long

    'name of each eeprom block start address
    'must be in the same order as in XXXX_eeprom.h!
    
    addressName(0) = "EEPROM_HIGH_CLEARANCE_PARAMS"
    addressName(1) = "EEPROM_HIGH_CLEARANCE_CALS"
    addressName(2) = "EEPROM_HIGH_CLEARANCE_OPTIONS"
    'addressName(3) = "EEPROM_DANFOSS_PROPEL_OPTIONS"
    'addressName(4) = "EEPROM_WBZ_PARAMS"
    'addressName(5) = "EEPROM_WBZ_CALS"
    'addressName(6) = "EEPROM_WBZ_SETTINGS"
    'addressName(7) = "EEPROM_RG3_PARAMS"
    'addressName(8) = "EEPROM_RG3_CALS"
    'addressName(9) = "EEPROM_SBL_PARAMS"
    'addressName(10) = "EEPROM_RG3_OPTIONS"
        
    addressName(3) = ""  'Last must be empty to prevent out of range error
    
    
    'file that declares the Eeprom block structure
    fileName(0) = "\..\..\ExternalLinks\Parts_Store\Chassis\Chassis_Functions\Control_Logic\High_Clearance\Src\HighClearance_eeprom.h"
    fileName(1) = fileName(0)
    fileName(2) = fileName(0)
    'fileName(3) = "\..\..\ExternalLinks\Parts_Store\Chassis\Chassis_Functions\Control_Logic\Danfoss_Drive_Control\Src\danfoss_propel_eeprom.h"
    'fileName(4) = "\..\..\ExternalLinks\Parts_Store\Chassis\Chassis_Functions\Control_Logic\WBZ_Bridge\Src\Wbz_Eeprom.h"
    'fileName(5) = "\..\..\ExternalLinks\Parts_Store\Chassis\Chassis_Functions\Control_Logic\WBZ_Bridge\Src\Wbz_Eeprom.h"
    'fileName(6) = "\..\..\ExternalLinks\Parts_Store\Chassis\Chassis_Functions\Control_Logic\WBZ_Bridge\Src\Wbz_Eeprom.h"
    'fileName(7) = "\..\..\Application\Source\Modules\RG3_Specific\RG3_Specific_Eeprom.h"
    'fileName(8) = "\..\..\Application\Source\Modules\RG3_Specific\RG3_Specific_Eeprom.h"
    'fileName(9) = "\..\..\ExternalLinks\Parts_Store\Chassis\Chassis_Functions\Control_Logic\System_Brightness\Src\System_Brightness_Eeprom.c"
    'fileName(10) = "\..\..\Application\Source\Modules\RG3_Specific\RG3_Specific_Eeprom.h"
   
    currentAddressName = 0
    nextRow = 8
    
    Set oFS = oFSO.OpenTextFile(ThisWorkbook.Path & "\..\..\Application\Source\Eeprom.h")
    
    'delete all data
    Range("A8:A65536").EntireRow.Delete
    
    'format units column as text
    Cells(8, 4).EntireColumn.NumberFormat = "@"
    
    'disable screen updating and calculations
    Application.ScreenUpdating = False
    Application.Calculation = xlCalculationManual
    
    Do Until oFS.AtEndOfStream
        
        sText = oFS.ReadLine
        currentAddress = getEepromAddr(sText, addressName(currentAddressName))
        
        If Not (currentAddress = -1) Then
            Range(Cells(nextRow, 1), Cells(nextRow, 12)).Interior.ColorIndex = 15
            Cells(nextRow, 3).Value = addressName(currentAddressName)
            Cells(nextRow, 3).Font.Bold = True
            If Not (Left(addressName(currentAddressName), 18) = "EEP_WEATHERSTATION") Then
'Chassis EEPROM
                nextRow = nextRow + 1
                startRow = nextRow
                
                nextRow = writeEepromBlock(currentAddress, addressName(currentAddressName), fileName(currentAddressName), nextRow)
                
                If InStr(sText, "CEAG") Then
                    For i = 5 To 11
                        Cells(nextRow - 1, i).Value = "=SummeCRC16(R" & startRow & "C:R" & nextRow - 2 & "C)"
                    Next i
                Else
                    For i = 5 To 11
                        Cells(nextRow - 1, i).Value = "=checksum(R" & startRow & "C:R" & nextRow - 2 & "C)"
                    Next i
                End If
                
                Cells(nextRow, 3).Value = "checksum"
                Cells(nextRow, 12).Value = "Original checksum (from read)"
    
                nextRow = nextRow + 1
                
                currentAddressName = currentAddressName + 1
'End Chassis EEPROM
            Else
'Implement EEPROM
                nextRow = nextRow + 1
                startRow = nextRow
                
                nextRow = writeEepromBlock(currentAddress, addressName(currentAddressName), fileName(currentAddressName), nextRow)
                
                For i = 5 To 11
                    Cells(startRow + 1, i).Value = "=calcCRC(R" & (startRow + 2) & "C:R" & (nextRow - 1) & "C)"
                Next i
                
                Cells(nextRow, 3).Value = "checksum"
                
                nextRow = nextRow + 1
                currentAddressName = currentAddressName + 1
'End Implement EEPROM
            End If
        End If
    
    Loop

    'enable screen updating
    Application.ScreenUpdating = True

    'disable screen updating
    Application.ScreenUpdating = False

    Call readMasterValues

    'enable screen updating and calculations
    Application.ScreenUpdating = True
    Application.Calculation = xlCalculationAutomatic
    Call MsgBox("Master structure successfully read!", vbOKOnly + vbInformation, "Master Structure Read")

End Sub


Function getEepromAddr(ByVal sText As String, addrName As String) As Long

    getEepromAddr = -1
    
    If addrName = "" Then
        Exit Function
    End If
    
    If InStr(1, sText, "//") Then
        sText = Left(sText, InStr(1, sText, "//") - 1)                          'remove comments
    End If
    
    sText = TrimAll(sText)                                                      'remove leading and trailing white space
    
    If InStr(1, sText, "#define " & addrName) = 1 Then                          'check if it is the correct line
    
        If InStr(1, sText, "0x") Then
            sText = Right(sText, Len(sText) - InStr(1, sText, "0x") - 1)        'remove hex sign to be able to get the value
            getEepromAddr = val("&H" & sText)                                   'get hex value
        End If
        
    End If

End Function


Function writeEepromBlock(ByRef startAddress As Long, addrName As String, fileName As String, ByVal nextRow, Optional ByVal baseName As String = "") As Long

    Dim oFSO As New FileSystemObject
    Dim oFS
    
    Dim blockStart As Boolean
    Dim blockEnd As Boolean
    
    Dim paramType As String
    Dim paramName As String
    Dim paramUnit As String
    Dim paramComment As String
    
    Dim wordEnd As Long
    
    Const numBlocks As Long = 11
    Dim blockName(numBlocks) As String
    Dim blockFile(numBlocks) As String
    Dim i As Long
    
    blockName(0) = "T_DRCE_DRIVE_MODE"
    blockName(1) = "T_PB_PARA"
    blockName(2) = "T_ASC_PARA"
    blockName(3) = "T_ABS_PARA"
    blockName(4) = "T_LLC_PARA"
    blockName(5) = "T_DA_HA_PARA"
    blockName(6) = "T_FAN_PARA"
    blockName(7) = "T_FAN_SENSOR_PARA"
    blockName(8) = "T_ECO_PARA"
    blockName(9) = "BrakeVariables_ts"
    blockName(10) = "CurrentOutEepromPara_ts"
    
    blockFile(0) = "\..\..\ExternalLinks\Parts_Store\Chassis\Libraries\Bosch\Lib_AGCH001\include\AGCH001.h"
    blockFile(1) = "\..\..\ExternalLinks\Parts_Store\Chassis\Libraries\Bosch\Lib_AGCH001\include\dom_pb_para.h"
    blockFile(2) = "\..\..\ExternalLinks\Parts_Store\Chassis\Libraries\Bosch\Lib_AGCH001\include\dom_asc_para.h"
    blockFile(3) = "\..\..\ExternalLinks\Parts_Store\Chassis\Libraries\Bosch\Lib_AGCH001\include\dom_abs_para.h"
    blockFile(4) = "\..\..\ExternalLinks\Parts_Store\Chassis\Libraries\Bosch\Lib_AGCH001\include\dom_llc_para.h"
    blockFile(5) = "\..\..\ExternalLinks\Parts_Store\Chassis\Libraries\Bosch\Lib_AGCH001\include\dom_da_ha_para.h"
    blockFile(6) = "\..\..\ExternalLinks\Parts_Store\Chassis\Libraries\Bosch\Lib_AGCH001\include\dom_fan_para.h"
    blockFile(7) = "\..\..\ExternalLinks\Parts_Store\Chassis\Libraries\Bosch\Lib_AGCH001\include\dom_fan_para.h"
    blockFile(8) = "\..\..\ExternalLinks\Parts_Store\Chassis\Libraries\Bosch\Lib_AGCH001\include\dom_eco_para.h"
    blockFile(9) = "\..\..\ExternalLinks\Parts_Store\Chassis\Chassis_Functions\Control_Logic\Trailer_Brake\Src\Trailerbrake_Eeprom.h"
    blockFile(10) = "\..\..\ExternalLinks\Parts_Store\Chassis\Chassis_Functions\Outputs\Basic\Current_Control\Src\Current_Control.h"

    blockStart = False
    blockEnd = False
    
    Set oFS = oFSO.OpenTextFile(ThisWorkbook.Path & fileName)
    Do Until oFS.AtEndOfStream
        
        sText = oFS.ReadLine
        
        'reset variables
        paramType = ""
        paramName = ""
        paramUnit = ""
        paramComment = ""

        If Not blockStart Then
            If InStr(1, sText, "//" & addrName & "_START") = 1 Then             'find the starting point
                blockStart = True
            End If
        End If
        
        If blockStart And Not blockEnd Then
            
            sText = TrimAll(sText)                                              'remove leading and trailing white space
            If Not (InStr(1, sText, "//") = 1) And Not sText = "" Then          'skip comment and empty line
            
                wordEnd = nextCut(sText)                                        'find end of parameter type
                paramType = Left(sText, wordEnd)                                'extract parameter type
                sText = Right(sText, Len(sText) - wordEnd)                      'remove parameter type
            
                sText = TrimAll(sText)                                          'remove leading and trailing white space
                
                wordEnd = InStr(1, sText, ";")                                  'find end of parameter name
                paramName = Left(sText, wordEnd - 1)                            'extract parameter name
                sText = Right(sText, Len(sText) - wordEnd)                      'remove parameter name
            
                sText = Replace(sText, "//", "")                                'remove comment trigger
                sText = TrimAll(sText)                                          'remove leading and trailing white space
            
                If Not sText = "" Then                                          'look if more information is on this line
                    
                    If InStr(1, sText, "[") Then                                'check if start of parameter unit exists
                        sText = Right(sText, Len(sText) - InStr(1, sText, "[")) 'remove everything before parameter unit
                        wordEnd = InStr(1, sText, "]")                          'find end of parameter unit
                        paramUnit = Left(sText, wordEnd - 1)                    'extract parameter unit
                        sText = Right(sText, Len(sText) - wordEnd)              'remove parameter unit
                    End If
            
                    sText = TrimAll(sText)                                      'remove leading and trailing white space
                
                    paramComment = sText                                        'everything that is left is comments
                    
                End If
                
                If InStr(1, paramName, "[") Then                                'parameter is an array
                    nextRow = writeArray(paramName, paramType, paramUnit, paramComment, nextRow, startAddress, baseName)
                Else
                    i = 0
                    Do While i < numBlocks
                        If paramType = blockName(i) Then
                            nextRow = writeEepromBlock(startAddress, blockName(i), blockFile(i), nextRow, baseName & paramName & ".")
                            Exit Do
                        End If
                        i = i + 1
                    Loop
                    
                    If i = numBlocks Then                                       'parameter should be written
                    
                        'write data
                        Cells(nextRow, 1).Value = "0x" & Right("0000" & Hex(startAddress), 4)
                        Cells(nextRow, 2).Value = paramType
                        Cells(nextRow, 3).Value = baseName & paramName
                        Cells(nextRow, 4).Value = paramUnit
                        Cells(nextRow, 12).Value = paramComment
                        
                        nextRow = nextRow + 1
                        startAddress = startAddress + paramTypeLength(paramType)
                    
                    End If
                End If
            
            End If

        End If

        If Not blockEnd Then
            If InStr(1, sText, "//" & addrName & "_END") = 1 Then               'check if the end point is reached
                blockEnd = True
            End If
        End If

    Loop
    
    writeEepromBlock = nextRow

End Function


Function writeArray(paramName As String, paramType, paramUnit, paramComment, ByVal nextRow As Long, ByRef paramAddress As Long, Optional ByVal baseName As String = "") As Long

    Dim arrayLength As Long
    Dim i As Long
    
    i = 0

    arrayLength = val(Right(paramName, Len(paramName) - InStr(1, paramName, "[")))  'get array length
    paramName = Left(paramName, InStr(1, paramName, "["))                           'remove array size
    
    While i < arrayLength
        'write data
        Cells(nextRow, 1).Value = "0x" & Right("0000" & Hex(paramAddress), 4)
        Cells(nextRow, 2).Value = paramType
        Cells(nextRow, 3).Value = baseName & paramName & i & "]"
        Cells(nextRow, 4).Value = paramUnit
        Cells(nextRow, 12).Value = paramComment
        
        nextRow = nextRow + 1
        paramAddress = paramAddress + paramTypeLength(paramType)
        i = i + 1
    Wend
    
    writeArray = nextRow

End Function


Function nextCut(ByVal text As String) As Long
'return position of first cut in text string (space or tab)

    Dim posSpace
    Dim posTab
    
    posSpace = InStr(1, text, " ")
    posTab = InStr(1, text, vbTab)
    
    If posSpace = 0 And Not posTab = 0 Then
        nextCut = posTab
    ElseIf Not posSpace = 0 And posTab = 0 Then
        nextCut = posSpace
    Else
        nextCut = Min(posSpace, posTab)
    End If

    nextCut = nextCut - 1

End Function


Sub readMasterValues()

    Dim oFSO As New FileSystemObject
    Dim oFS
    Dim fileName As String
    Dim rowNum As Long
    Dim paramName As String
    Dim i As Long
    Dim separator As Long
    
    fileName = ThisWorkbook.Path & "\" & ThisWorkbook.Name
    fileName = Replace(fileName, ".xlsm", ".csv")
    
    rowNum = 8
    
    Set oFS = oFSO.OpenTextFile(fileName)
    
    sText = oFS.ReadLine                                                'read header line before loop
    
    If sText = "parameter name;aHC;bNoHC;cFtDev;dFtDev;eFtDev" Then         'check header is correct
        Do Until oFS.AtEndOfStream
                        
            i = 8
            sText = oFS.ReadLine
                
            If InStr(1, sText, ";") Then                                'skip block start line
                
                separator = InStr(1, sText, ";")
                paramName = Left(sText, separator - 1)                  'extract parameter name
                sText = Right(sText, Len(sText) - separator)            'remove parameter name
                
                If Not paramName = Cells(rowNum, 3).Value Then
                    While Not IsEmpty(Cells(i, 3))
                    
                        If paramName = Cells(i, 3).Value Then
                            rowNum = i
                            i = 65535
                        End If
                    
                        i = i + 1
                    Wend
                End If
            
                If (i = 8 Or i = 65536) And _
                   Not ((paramName = "checksum") Or (paramName = "FileCrc")) Then                        'parameter was found and it is not the checksum line
                    
                    separator = InStr(1, sText, ";")
                    Cells(rowNum, 5).Value = Left(sText, separator - 1) 'extract value
                    sText = Right(sText, Len(sText) - separator)        'remove value
                    
                    separator = InStr(1, sText, ";")
                    Cells(rowNum, 6).Value = Left(sText, separator - 1) 'extract value
                    sText = Right(sText, Len(sText) - separator)        'remove value
                    
                    separator = InStr(1, sText, ";")
                    Cells(rowNum, 7).Value = Left(sText, separator - 1) 'extract value
                    sText = Right(sText, Len(sText) - separator)        'remove value
                    
                    separator = InStr(1, sText, ";")
                    Cells(rowNum, 8).Value = Left(sText, separator - 1) 'extract value
                    sText = Right(sText, Len(sText) - separator)        'remove value
                                       
                    Cells(rowNum, 9).Value = sText                      'extract value
                    
                End If
                
                For i = 5 To 9
                    With Cells(rowNum, i)
                        .NumberFormat = "General"
                        .FormatConditions.Delete
                        .FormatConditions.Add xlCellValue, xlNotEqual, "=MODE(RC5:RC9)"
                        .FormatConditions(1).Interior.PatternColorIndex = 6
                        .FormatConditions(1).Interior.Pattern = xlLightUp
                    End With
                Next i

                
            End If
        
            rowNum = rowNum + 1
                    
        Loop
    End If

End Sub


