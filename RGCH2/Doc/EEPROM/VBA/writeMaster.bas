Attribute VB_Name = "writeMaster"
Sub writeMaster()

    Dim fileName As String
    Dim i As Long
    
    fileName = ThisWorkbook.Path & "\" & ThisWorkbook.Name
    fileName = Replace(fileName, ".xlsm", ".csv")
    
    i = 8

    fnum = FreeFile()
    Open fileName For Output As fnum
        
        'insert header
        Print #fnum, Cells(7, 3).Value & ";" & _
                     Cells(7, 5).Value & ";" & _
                     Cells(7, 6).Value & ";" & _
                     Cells(7, 7).Value & ";" & _
                     Cells(7, 8).Value & ";" & _
                     Cells(7, 9).Value
        
        While Not IsEmpty(Cells(i, 3))
        
            'Insert extra line before each eeprom block
            If IsEmpty(Cells(i, 1)) Then
                
                If Not (Cells(i, 3).Value = "checksum") Then            'start of new eeprom block
                    Print #fnum, Cells(i, 3).Value
                End If
            
            Else                                                        'normal parameter row
        
                Print #fnum, Cells(i, 3).Value & ";" & _
                             Cells(i, 5).Value & ";" & _
                             Cells(i, 6).Value & ";" & _
                             Cells(i, 7).Value & ";" & _
                             Cells(i, 8).Value & ";" & _
                             Cells(i, 9).Value
            
            End If
            
            i = i + 1
            
        Wend
    
        'blank line at end of file
        Print #fnum,
    
    Close #fnum
 
End Sub
