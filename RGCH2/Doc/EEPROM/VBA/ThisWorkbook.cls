VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "ThisWorkbook"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = True
Private Sub Workbook_Open()
    ' Read VBA modules from files
    ' Existing modules will be replaced!

    ImportAndReplaceModule ("custom")
    ImportAndReplaceModule ("generateMaster")
    ImportAndReplaceModule ("readMaster")
    ImportAndReplaceModule ("util")
    ImportAndReplaceModule ("writeMaster")
    'ImportAndReplaceModule ("CRC16")

    ' These modules can not be imported:
    ' Utils             Currently in use for ImportAndReplaceModule
    ' ThisWorkbook      This type can not be imported

End Sub

Private Sub Workbook_AfterSave(ByVal Success As Boolean)
    ' Export VBA modules to files
    ' Existing files will be replaced!
    
    If Success Then
        
        ExportModule ("custom")
        ExportModule ("generateMaster")
        ExportModule ("readMaster")
        ExportModule ("util")
        ExportModule ("writeMaster")
        'ExportModule ("CRC16")
        ExportModule ("Utils")
        ExportModule ("ThisWorkbook")
    
    End If

End Sub



