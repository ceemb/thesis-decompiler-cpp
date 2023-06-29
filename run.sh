#!/bin/bash

if [ -z ${MY_GIT_TOP} ]; then
    echo "MY_GIT_TOP is not set!"
    echo "Source gitenv.sh in repo root and try again"
    exit 1
fi

while getopts "i:d:" opt; do
  case $opt in
    i)
      arg_i=$OPTARG
      ;;
    d)
      arg_d=$OPTARG
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      exit 1
      ;;
    :)
      echo "Option -$OPTARG requires an argument." >&2
      exit 1
      ;;
  esac
done

if [[ -z $arg_i || -z $arg_d ]]; then
  echo "Usage: $0 -i <int> -d <int>"
  exit 1
fi

echo "arg_i: $arg_i"
echo "arg_d: $arg_d"
# Compile & run if succesful
make -f makefile_no_fpic && sdk_run.sh --toolchain= <redacted> -i $arg_i -d $arg_d
