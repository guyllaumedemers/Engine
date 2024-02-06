@ECHO OFF

SETLOCAL enabledelayedexpansion

SET cppFilenames=
FOR /f usebackq %%i in (`DIR /ad /b %~dp0`) do (
	ECHO "Fetching all translation units to be compiled..."
	:: update current directory as FOR /r [drive:path] doesnt support %VAR%
	PUSHD "%%i"
	FOR /r %%k in (*.cpp) do (
		SET cppFilenames=!cppFilenames! %%k
		ECHO %%k
	)
	POPD
)

:: windows environment variables https://pureinfotech.com/list-environment-variables-windows-10/
SET engineDir="..\\..\\out"
SET msvcDir="C:\\Program Files\\Microsoft Visual Studio\\2022\\Enterprise\\VC\\Tools\\MSVC\\14.38.33130\\lib\\x64"
SET windowKitDir="C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.22621.0\\um\\x64"
SET windowCrt="C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.22621.0\\ucrt\\x64"

SET assembly=Sandbox
SET compilerFlags=/std:c++17 /Ob1 /Y- /Zi /Wall /showFilenames /MDd --target=x86_64-pc-windows-msvc
SET includeFlags=/I..\\..\\Engine\\Source\\Runtime
SET linkerLibs=Engine.lib msvcrtd.lib vcruntimed.lib ucrtd.lib kernel32.lib msvcprtd.lib
SET linkerFlags=/MACHINE:X64 /SUBSYSTEM:WINDOWS /NODEFAULTLIB /DEBUG /VERBOSE
SET linkerPaths=/LIBPATH:%engineDir% /LIBPATH:%msvcDir% /LIBPATH:%windowKitDir% /LIBPATH:%windowCrt%
SET defines=/D_DEBUG /D_CRT_SECURE_NO_WARNINGS

:: print console you env LIB paths
:: ECHO %LIB%

ECHO "Building %assembly%..."
clang-cl %defines% %includeFlags% %compilerFlags% %cppFilenames% -o ..\\..\\out\\%assembly%.exe /link %linkerLibs% %linkerPaths% %linkerFlags%