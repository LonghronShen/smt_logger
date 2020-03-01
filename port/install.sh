#!/bin/bash

cp -r smt-logger $VCPKG_ROOT/ports/

cd $VCPKG_ROOT
actual_hash=$(./vcpkg install smt-logger | grep -oP "(?<=Actual hash: \[ ).+ "))

cd $VCPKG_ROOT/ports/smt-logger
sed -i "s/SOURCE_SHA512/$actual_hash/g" portfile.cmake

cd $VCPKG_ROOT
./vcpkg install smt-logger "$@"