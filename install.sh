#!/bin/bash

set -x

rm -rf install/

cd build/

cmake --install . --prefix=../install/