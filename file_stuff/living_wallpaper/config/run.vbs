DIM objShell 
set objShell = wscript.createObject("wscript.shell") 
Set Ws = CreateObject("Scripting.FileSystemObject")
iReturn = objShell.Run("cmd.exe /C " + Ws.GetFile(Wscript.ScriptFullName).ParentFolder.Path + "\run.bat", 0, TRUE)