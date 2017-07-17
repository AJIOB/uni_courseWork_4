IF EXIST external (
echo Cache was found 
) ELSE (

mkdir external
cd external

REM # building mongo-c-driver
git clone https://github.com/mongodb/mongo-c-driver.git
cd mongo-c-driver
git checkout 1.6.2
git submodule init
git submodule update
cd src\libbson
cmake -DCMAKE_INSTALL_PREFIX=C:\libmongoc -G "Visual Studio 14 Win64" .
msbuild.exe ALL_BUILD.vcxproj
msbuild.exe INSTALL.vcxproj
cd ..\..
cmake -DCMAKE_INSTALL_PREFIX=C:\libmongoc -DENABLE_SSL=WINDOWS -DBSON_ROOT_DIR=C:\libmongoc -G "Visual Studio 14 Win64" .
msbuild.exe ALL_BUILD.vcxproj
msbuild.exe INSTALL.vcxproj

cd ..

REM # building mongo-cxx-driver
git clone https://github.com/mongodb/mongo-cxx-driver.git --branch releases/stable --depth 1
cd mongo-cxx-driver/build

cmake.exe -G "Visual Studio 14 Win64" -DCMAKE_INSTALL_PREFIX=C:\mongo-cxx-driver -DCMAKE_PREFIX_PATH=c:\mongo-c-driver -DBOOST_ROOT=C:\Libraries\boost_1_63_0

REM # going back

cd ../..

cd ..

)
