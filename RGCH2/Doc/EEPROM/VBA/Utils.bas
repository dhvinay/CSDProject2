Attribute VB_Name = "Utils"
Public Function ImportAndReplaceModule(Module As String)

    Dim VBComp As VBComponent
    Dim FName As String
    
    ' Remove existing module first
    RemoveModule (Module)
    
    ' Import Export_IO_header module
    FName = ThisWorkbook.Path & "\VBA\" & Module & ".bas"
    ThisWorkbook.VBProject.VBComponents.Import FName

End Function

Public Function RemoveModule(Module As String)

    ' Remove module if it exists
    If VBComponentExists(Module) Then
        Set VBComp = ThisWorkbook.VBProject.VBComponents(Module)
        ThisWorkbook.VBProject.VBComponents.Remove VBComp
    End If

End Function

Public Function ExportModule(Module As String)

    Dim VBComp As VBComponent
    Dim FPath As String
    
    If VBComponentExists(Module) Then
        ' Module found, export it
        FPath = ThisWorkbook.Path & "\VBA\"
        Set VBComp = ThisWorkbook.VBProject.VBComponents(Module)
        Call ExportVBComponent(VBComp, FPath, Module, True)
    Else
        ' Module missing, show warning
        Call MsgBox("Could not export " & Module & "!" & vbNewLine & _
                    "Module not found.", _
                    vbOKOnly + vbExclamation, _
                    "Warning " & Module)
    End If

End Function
    
    Public Function VBComponentExists(VBCompName As String, Optional VBProj As VBIDE.VBProject = Nothing) As Boolean
    ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    ' This returns True or False indicating whether a VBComponent named
    ' VBCompName exists in the VBProject referenced by VBProj. If VBProj
    ' is omitted, the VBProject of the ActiveWorkbook is used.
    ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
        Dim VBP As VBIDE.VBProject
        If VBProj Is Nothing Then
            Set VBP = ActiveWorkbook.VBProject
        Else
            Set VBP = VBProj
        End If
        On Error Resume Next
        VBComponentExists = CBool(Len(VBP.VBComponents(VBCompName).Name))
    
    End Function

    Public Function ExportVBComponent(VBComp As VBIDE.VBComponent, _
                FolderName As String, _
                Optional fileName As String, _
                Optional OverwriteExisting As Boolean = True) As Boolean
    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    ' This function exports the code module of a VBComponent to a text
    ' file. If FileName is missing, the code will be exported to
    ' a file with the same name as the VBComponent followed by the
    ' appropriate extension.
    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    Dim Extension As String
    Dim FName As String
    Extension = GetFileExtension(VBComp:=VBComp)
    If Trim(fileName) = vbNullString Then
        FName = VBComp.Name & Extension
    Else
        FName = fileName
        If InStr(1, FName, ".", vbBinaryCompare) = 0 Then
            FName = FName & Extension
        End If
    End If
    
    If StrComp(Right(FolderName, 1), "\", vbBinaryCompare) = 0 Then
        FName = FolderName & FName
    Else
        FName = FolderName & "\" & FName
    End If
    
    If Dir(FName, vbNormal + vbHidden + vbSystem) <> vbNullString Then
        If OverwriteExisting = True Then
            Kill FName
        Else
            ExportVBComponent = False
            Exit Function
        End If
    End If
    
    VBComp.Export fileName:=FName
    ExportVBComponent = True
    
    End Function
    
    Public Function GetFileExtension(VBComp As VBIDE.VBComponent) As String
    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    ' This returns the appropriate file extension based on the Type of
    ' the VBComponent.
    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
        Select Case VBComp.Type
            Case vbext_ct_ClassModule
                GetFileExtension = ".cls"
            Case vbext_ct_Document
                GetFileExtension = ".cls"
            Case vbext_ct_MSForm
                GetFileExtension = ".frm"
            Case vbext_ct_StdModule
                GetFileExtension = ".bas"
            Case Else
                GetFileExtension = ".bas"
        End Select
        
    End Function




