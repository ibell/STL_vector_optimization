
REM ******** set the variables ************
call "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" amd64
call "C:\Program Files\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" amd64

cl /O2 stl_vector_optimizations.cpp

stl_vector_optimizations.exe