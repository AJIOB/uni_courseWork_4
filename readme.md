# Project "Library"

This is project, which can help persons to structure & store information about books and its' readers.

## What do you need to build that project

To develop and build this project I'm using:  
* Microsoft Visual Studio 2015 Update 3, Enterprise Edition  
* Qt OpenSource v5.7.1 for msvc2015  
* External libraries:  

| Library   |      Version     |  Dependent from |  
|----------|:-------------:|:-----------:|  
| bzip2 |  1.0.6 |  |  
| zlib | 1.2.11 |  |  
| boost | 1.63-4 | bzip2, zlib |  
| libbson | 1.6.2 |  |  
| mongo-c-driver | 1.6.2 | libbson |  
| mongo-cxx-driver | 3.1.1 | mongo-c-driver, boost, libbson |  
| gtest | 1.8 |  |  

If you want to run this app, you may need to build `GUI.QT` project and it's dependencies in solution.  
If you want to run tests, you may need to build `tests` progect and it's dependencies in solution.  

## Author

Made by AJIOB (Alex).
