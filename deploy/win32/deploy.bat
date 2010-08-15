@REM Build the installer
"C:\Program Files\NSIS\makensisw.exe" "kscemailtracker.nsi"

@REM Move the compiled installer to the output directory
move "kscemailtracker-2.0.3-windows.exe" "%CD%\..\..\..\kscemailtracker-build-desktop\bin\kscemailtracker-2.0.3-windows.exe"

pause
