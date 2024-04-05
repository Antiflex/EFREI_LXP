# Note: This script should not be run, just sourced into an
# shell ("source ./envsetup.sh" or ". ./envsetup.sh").
# it has no effect when running it ("./envsetup.sh").

if [ -n "$BASH" ]; then
  [[ "${BASH_SOURCE[0]}" == "${0}" ]] && echo "This script should only be sourced, not executed!"

  _ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
else
  # Handle other bourne (sh) compatible shells. E.g. dash, posh, zsh
  # and others.
  # Note: This script does not support csh/tcsh and other types of shells.
  _ROOT="$( cd "$( dirname "${0}" )" && pwd )"
fi


if [ ! -z "$MLSDK" ]; then
    # compare any existing MLSDK value
    if [ ! "$MLSDK" -ef "$_ROOT" ]; then
        echo "*** Replacing MLSDK=$MLSDK..."
    fi
fi

echo "*** Setting MLSDK=$_ROOT and updating PATH"
export MLSDK=$_ROOT
export PATH=$_ROOT:$PATH


if [ -z "$ANDROID_HOME" ] && [ ! -z "$ANDROID_SDK_ROOT" ]; then
	export ANDROID_HOME="$ANDROID_SDK_ROOT"
	echo "*** Setting ANDROID_HOME to ANDROID_SDK_ROOT=$ANDROID_HOME"
fi

if [ -z "$ANDROID_HOME" ]; then
    # check if sdk is in default path
	echo "*** ANDROID_HOME is not set, checking default paths..."
	path_to_check=""
	if [ "$(uname)" == "Darwin" ]; then
		path_to_check="$HOME/Library/Android/sdk"
	elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
		path_to_check="$HOME/Android/Sdk"
	fi
	
	if [ -d "$path_to_check" ]; then
		export ANDROID_HOME="$path_to_check"
		echo "*** Setting ANDROID_HOME=$ANDROID_HOME"
	fi
fi

if [ ! -z "$ANDROID_HOME" ]; then
	export PATH="$ANDROID_HOME/platform-tools:$PATH"
fi


if [ -z "$ANDROID_NDK_ROOT" ]; then
	echo "*** ANDROID_NDK_ROOT is not set, checking newest NDK in $ANDROID_HOME..."
	newest_ndk="$( ls -1r "$ANDROID_HOME/ndk" | head -n1 )"
	if [ ! -z "$newest_ndk" ]; then
		export ANDROID_NDK_ROOT="$ANDROID_HOME/ndk/$newest_ndk"
		echo "*** Setting ANDROID_NDK_ROOT=$ANDROID_NDK_ROOT"
	fi
fi

if [ ! -z "$ANDROID_NDK_ROOT" ]; then
	export PATH="$ANDROID_NDK_ROOT:$PATH"
fi
	
