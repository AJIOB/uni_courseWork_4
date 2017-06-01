# Project "Library"

This is project, which can help persons to structure & store information about books and its' readers.

## What do you need to build that project

To develop and build this project I'm using:  
* Microsoft Visual Studio 2015 Update 3, Enterprise Edition  
* Qt VS Tools (plug-in for Visual Studio, you can download it from [this page](http://download.qt.io/development_releases/vsaddin/) or from [this manual link](http://download.qt.io/development_releases/vsaddin/qt-vs-addin-msvc2015-2.0.0-beta.vsix) for msvc 2015)  
* Qt OpenSource v5.7.1 for msvc2015  
* InstallShield 2015 Limited Edition for Visual Studio 2015  
* External libraries (were builded by [vcpkg tool](https://github.com/Microsoft/vcpkg)):  

| Library   |      Version     |  Dependent from |  
|----------|:-------------:|:-----------:|  
| bzip2 |  1.0.6 |  |  
| zlib | 1.2.11 |  |  
| boost | 1.63-4 | bzip2, zlib |  
| libbson | 1.6.2 |  |  
| mongo-c-driver | 1.6.2 | libbson |  
| mongo-cxx-driver | 3.1.1 | mongo-c-driver, boost, libbson |  
| gtest | 1.8 |  |  

## Build & run instructions

First of all you need to add `$(QTDIR)` variable to `GUI.QT` and `Controller.QT` projects. This variable must be a way to your installed Qt, for example `D:\Qt\Qt5.7.1\5.7\msvc2015`.   
If you want to run this app, you may need to build `GUI.QT` project and it's dependencies in solution.  
If you want to run tests, you may need to build `tests` project and it's dependencies in solution.  

## Author

Made by AJIOB (Alex).
