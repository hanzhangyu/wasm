#! /usr/bin/env bash

function echoHelp {
cat << EOL
Build For WebAssembly

usage: ./make [arguments]		build wasm by your order
   or: ./make -h | --help			see help

Arguments:
    all             build wasm in all folder
    *               match the folder by you order

EOL
}

if [[ -z $1 ]]; then
	echo "No such command for build script. Use ./make -h to see help."
	exit 1
fi

case $1 in
	-h | --help )
		echoHelp;;
	all )
	    echo "TODO";;
    * )
        if ! grep -qE "(Microsoft|WSL)" /proc/version &> /dev/null ; then
            echo "Use wsl plz!"
            exit 1
        fi
        echo "Checking files"
        curPath=`pwd`/$1
        curPathWin=`wslpath -m ${curPath}`
        if [[ ! -d ${curPath} ]]; then
            echo "$curPath is not a directory"
            exit 1;
        fi

        curCFile=${curPath}/$1.c
        if [[ ! -f ${curCFile} ]]; then
            echo "$curCFile is not exist"
            exit 1;
        fi
        echo "file captured: $curCFile"
        time docker.exe run --rm -v ${curPathWin}:/src trzeci/emscripten emcc $1.c
        echo "open: http://localhost:8080/$1"
        ;;
esac