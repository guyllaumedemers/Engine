:: Build script for engine

:: online resource - https://www.tutorialspoint.com/batch_script/batch_script_commands.htm

:: turn off command display. '@' apply command to itself
@ECHO OFF

:: cmd-args can be provided through '%<n>', where <n> is the arg index and forwarded during invocation of the .bat file
:: or through 'set /A variable-name=value'

:: variable-name			- is the name of the variable you want to set.
:: value					- is the value which needs to be set against the variable.
:: /A						- is used if the value needs to be numeric in nature. *All of the Arithmetic operations work in batch*

:: SETLOCAL / ENDLOCAL		- Starts localization of environment variables in a batch file
:: online resouce			- https://learn.microsoft.com/en-us/windows-server/administration/windows-commands/setlocal

:: CALL						- Calls one batch program from another without stopping the parent batch program.			
:: online resouce			- https://learn.microsoft.com/en-us/windows-server/administration/windows-commands/call

:: enabledelayeexpansion	- instructs cmd to recognise the syntax !var! which accesses the current value of var.
:: online resouce			- https://stackoverflow.com/questions/22278456/enable-and-disable-delayed-expansion-what-does-it-do
SETLOCAL enabledelayedexpansion

:: get list of all *.cpp	- https://learn.microsoft.com/en-us/windows-server/administration/windows-commands/for
SET cppFilenames=
FOR /f usebackq %%i in (`DIR /ad /b %~dp0 ^| FINDSTR /v /i ThirdParty`) do (
	ECHO "Fetching all translation units to be compiled..."
	:: update current directory as FOR /r [drive:path] doesnt support %VAR%
	PUSHD "%%i"
	FOR /r %%k in (*.cpp) do (
		SET cppFilenames=!cppFilenames! %%k
		ECHO %%k
	)
	POPD
)

SET assembly=Engine
SET compilerFlags=/std:c++17 /Ob1 /Y- /Zi /Wall /showFilenames
SET includeFlags=/IRuntime
SET linkerFlags=/MACHINE:X64 /DEBUG /DLL /NOENTRY /VERBOSE:LIB
SET defines=/D_DEBUG /DDCLSPEC_EXPORT /D_CRT_SECURE_NO_WARNINGS

ECHO "Building %assembly%..."
clang-cl %defines% %includeFlags% %compilerFlags% %cppFilenames% -o ..\\..\\out\\%assembly%.dll /link %linkerFlags%