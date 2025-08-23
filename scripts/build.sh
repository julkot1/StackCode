#!/bin/bash
./scripts/build_antrl.sh

set -e
mkdir -p build && cd build
cmake .. "$@"
make -j$(nproc)
pwd
mv src/stcc ..
#build runtime libraries
../stc/compile.sh
#run tests
../src/test/test.sh