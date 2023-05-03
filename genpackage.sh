#!/bin/bash

mkdir package
g++ genmeta.cpp
./a.out < tests/mapping > package/meta.json
cp statement/description.md package/prob.md
mkdir package/testdata
cp tests/*.in package/testdata/
cp tests/*.out package/testdata/
tar zcvf package.tar.gz package
rm -r package
