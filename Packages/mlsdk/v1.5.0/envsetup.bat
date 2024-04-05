@echo off

call :set_mlsdk
call :set_android_home
call :set_android_ndk_root
goto :exit


:set_mlsdk

	call :realpath_noslash "%~dp0" _ROOT
	call :realpath_noslash "%MLSDK%" _MLSDK
	if defined MLSDK (
		if "%_MLSDK%" NEQ "" (
			if /I NOT "%_ROOT%" == "%_MLSDK%" (
				echo *** Replacing MLSDK=%MLSDK%...
			)
		)
	)

	echo *** Setting MLSDK=%_ROOT% and updating PATH
	set "MLSDK=%_ROOT%"
	set "PATH=%_ROOT%;%PATH%"
	exit /b


:set_android_home
	if not defined ANDROID_HOME if defined ANDROID_SDK_ROOT (
		set "ANDROID_HOME=%ANDROID_SDK_ROOT%"
		echo *** Setting ANDROID_HOME to ANDROID_SDK_ROOT=%ANDROID_SDK_ROOT%
	)

	if not defined ANDROID_HOME (
		echo *** ANDROID_HOME is not set, checking default paths...
		if exist "%LOCALAPPDATA%\Android\sdk" (
			set "ANDROID_HOME=%LOCALAPPDATA%\Android\sdk"
			echo *** Setting ANDROID_HOME=%LOCALAPPDATA%\Android\sdk
		)
	)

	if defined ANDROID_HOME (
		set "PATH=%ANDROID_HOME%\platform-tools;%PATH%"
	) else (
		goto :exit
	)
	exit /b


:set_android_ndk_root

	if not defined ANDROID_NDK_ROOT (
		echo *** ANDROID_NDK_ROOT is not set, checking default paths...
		for /f "delims=" %%i in ('dir "%ANDROID_HOME%\ndk" /b/ad-h/on') do set "_NDK_VERSION=%%i"
	)

	if defined _NDK_VERSION if "%_NDK_VERSION%" NEQ "" (
		set "_NDK_PATH=%ANDROID_HOME%\ndk\%_NDK_VERSION%"
	)

	if defined _NDK_PATH if exist "%_NDK_PATH%" (
		set "ANDROID_NDK_ROOT=%_NDK_PATH%"
		echo *** Setting ANDROID_NDK_ROOT=%_NDK_PATH%
	)

	if defined ANDROID_NDK_ROOT (
		set "PATH=%ANDROID_NDK_ROOT%;%PATH%"
	) else (
		goto :exit
	)
	exit /b


:realpath_noslash
  @rem get canonical path of argument 1, without a trailing "\", and write to variable named in argument 2
  set "_T=%~df1"
  if [%_T:~-1%] == [\] (
    set "%~2=%_T:~0,-1%"
  ) else (
    set "%~2=%_T%"
  )
  exit /b


:exit

set "_MLSDK="
set "_T="
set "_ROOT="
set "_NDK_VERSION="
set "_NDK_PATH="
