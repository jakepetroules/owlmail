set QT=C:\Qt\2010.02.1\qt
set QTDIR=%QT%\bin
set QTPLUGINSDIR=%QT%\plugins
set RELEASEDIR=%CD%\win
set PLUGINSRELEASEDIR=%CD%\win\imageformats

REM Remove and recreate release directory
IF EXIST "%RELEASEDIR%" rmdir /s "%RELEASEDIR%"
mkdir "%RELEASEDIR%"
mkdir "%PLUGINSRELEASEDIR%"

@REM Copy main executable
xcopy "..\release\KscEmailTracker.exe" "%RELEASEDIR%"

@REM Copy core DLLs
xcopy "%QTDIR%\libgcc_s_dw2-1.dll" "%RELEASEDIR%"
xcopy "%QTDIR%\mingwm10.dll" "%RELEASEDIR%"
xcopy "%QTDIR%\phonon4.dll" "%RELEASEDIR%"

@REM Copy required Qt DLLs
xcopy "%QTDIR%\QtCore4.dll" "%RELEASEDIR%"
xcopy "%QTDIR%\QtGui4.dll" "%RELEASEDIR%"
xcopy "%QTDIR%\QtNetwork4.dll" "%RELEASEDIR%"
xcopy "%QTDIR%\QtWebKit4.dll" "%RELEASEDIR%"
xcopy "%QTDIR%\QtXmlPatterns4.dll" "%RELEASEDIR%"

@REM Copy image plugins
xcopy "%QTPLUGINSDIR%\imageformats\qgif4.dll" "%PLUGINSRELEASEDIR%"
xcopy "%QTPLUGINSDIR%\imageformats\qico4.dll" "%PLUGINSRELEASEDIR%"
xcopy "%QTPLUGINSDIR%\imageformats\qjpeg4.dll" "%PLUGINSRELEASEDIR%"

@echo The deployment operation has completed.
pause