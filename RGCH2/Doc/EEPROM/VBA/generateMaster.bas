Attribute VB_Name = "generateMaster"
Sub generateMaster()

    Dim fileName As String
    Dim columnNum As Long
        
    For columnNum = 5 To 9
        
        'set file name
        fileName = ThisWorkbook.Path & "\" & ThisWorkbook.Name
        fileName = Replace(fileName, ".xlsm", "")
        fileName = fileName & "_" & Cells(7, columnNum).Value & ".eep"
        
        Call generateEeprom(fileName, columnNum)
    
    Next columnNum

    Call MsgBox("EEP-files successfully generated!", vbOKOnly + vbInformation, "Generate EEP-files")

End Sub
