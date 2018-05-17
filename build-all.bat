@echo off 

SET BUILD_TYPE=Debug
SET BUILD_DIR=build
SET SHARED_LIB=OFF
echo *** Buiding OpenML Static Library x86 in Debug Mode ***

if exist %BUILD_DIR% ( rmdir /s/q %BUILD_DIR% )
mkdir %BUILD_DIR%
cd %BUILD_DIR%

call cmake ..                                          ^
	-DMAJOR_COLUMN_ORDER:BOOL=ON                       ^
	-DBUILD_SHARED_LIBS:BOOL=%SHARED_LIB%              ^
	-DWIN32:BOOL=ON                                    ^
	-DWINDOWS:BOOL=ON                                  ^
	-G "Visual Studio 15 2017"
	
cmake --build . --config %BUILD_TYPE%

copy ".\%BUILD_TYPE%\OpenML.lib" ".\..\bin\x86\%BUILD_TYPE%-COLUMN_ORDER"
copy ".\%BUILD_TYPE%\OpenML.pdb" ".\..\bin\x86\%BUILD_TYPE%-COLUMN_ORDER"
if %SHARED_LIB%==ON ( copy ".\%BUILD_TYPE%\OpenML.dll" ".\..\bin\x86\%BUILD_TYPE%-COLUMN_ORDER" )

SET BUILD_TYPE=Release
echo *** Buiding OpenML Static Library x86 in Release Mode ***

cmake --build . --config %BUILD_TYPE%

copy ".\%BUILD_TYPE%\OpenML.lib" ".\..\bin\x86\%BUILD_TYPE%-COLUMN_ORDER"
if %SHARED_LIB%==ON ( copy ".\%BUILD_TYPE%\OpenML.dll" ".\..\bin\x86\%BUILD_TYPE%-COLUMN_ORDER" )

cd ..

SET BUILD_TYPE=Debug
echo *** Buiding OpenML Static Library x64 in Debug Mode ***

if exist %BUILD_DIR% ( rmdir /s/q %BUILD_DIR% )
mkdir %BUILD_DIR%
cd %BUILD_DIR%

call cmake ..                                          ^
	-DMAJOR_COLUMN_ORDER:BOOL=ON                       ^
	-DBUILD_SHARED_LIBS:BOOL=%SHARED_LIB%              ^
	-DWIN32:BOOL=ON                                    ^
	-DWINDOWS:BOOL=ON                                  ^
	-G "Visual Studio 15 2017 Win64"
	
cmake --build . --config %BUILD_TYPE%

copy ".\%BUILD_TYPE%\OpenML.lib" ".\..\bin\x64\%BUILD_TYPE%-COLUMN_ORDER"
copy ".\%BUILD_TYPE%\OpenML.pdb" ".\..\bin\x64\%BUILD_TYPE%-COLUMN_ORDER"
if %SHARED_LIB%==ON ( copy ".\%BUILD_TYPE%\OpenML.dll" ".\..\bin\x64\%BUILD_TYPE%-COLUMN_ORDER" )

SET BUILD_TYPE=Release
echo *** Buiding OpenML Static Library x64 in Release Mode ***

cmake --build . --config %BUILD_TYPE%

copy ".\%BUILD_TYPE%\OpenML.lib" ".\..\bin\x64\%BUILD_TYPE%-COLUMN_ORDER"
if %SHARED_LIB%==ON ( copy ".\%BUILD_TYPE%\OpenML.dll" ".\..\bin\x64\%BUILD_TYPE%-COLUMN_ORDER" )

cd ..
if exist %BUILD_DIR% ( rmdir /s/q %BUILD_DIR% )