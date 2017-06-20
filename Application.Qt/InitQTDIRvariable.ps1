param (
    [string]$qtdir = "C:\Qt\Qt5.7.1\5.7\msvc2015"
 )

$guiqtFile = "GUI.QT\GUI.QT.vcxproj.user"
$controllerqtFile = "Controller.QT\Controller.QT.vcxproj.user"

$PSDefaultParameterValues['Out-File:Encoding'] = 'utf8'

$guiqtTextToFile = '<?xml version="1.0" encoding="utf-8"?>
<Project ToolsVersion="14.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <PropertyGroup />
  <PropertyGroup Condition="''$(Configuration)|$(Platform)''==''Debug|Win32''">
    <QTDIR>' + $qtdir + '</QTDIR>
    <LocalDebuggerEnvironment>PATH=$(QTDIR)\bin%3b$(PATH)</LocalDebuggerEnvironment>
    <LocalDebuggerWorkingDirectory>$(SolutionDir)deps</LocalDebuggerWorkingDirectory>
    <DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
  </PropertyGroup>
  <PropertyGroup Condition="''$(Configuration)|$(Platform)''==''Release|Win32''">
    <QTDIR>' + $qtdir + '</QTDIR>
    <LocalDebuggerEnvironment>PATH=$(QTDIR)\bin%3b$(PATH)</LocalDebuggerEnvironment>
    <LocalDebuggerWorkingDirectory>$(SolutionDir)deps</LocalDebuggerWorkingDirectory>
    <DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
  </PropertyGroup>
</Project>'

$guiqtTextToFile > $guiqtFile

$controllerqtTextToFile = '<?xml version="1.0" encoding="utf-8"?>
<Project ToolsVersion="14.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <PropertyGroup />
  <PropertyGroup Condition="''$(Configuration)|$(Platform)''==''Debug|Win32''">
    <QTDIR>' + $qtdir + '</QTDIR>
    <LocalDebuggerEnvironment>PATH=$(QTDIR)\bin%3b$(PATH)</LocalDebuggerEnvironment>
  </PropertyGroup>
  <PropertyGroup Condition="''$(Configuration)|$(Platform)''==''Release|Win32''">
    <QTDIR>' + $qtdir + '</QTDIR>
    <LocalDebuggerEnvironment>PATH=$(QTDIR)\bin%3b$(PATH)</LocalDebuggerEnvironment>
  </PropertyGroup>
</Project>'

$controllerqtTextToFile > $controllerqtFile

