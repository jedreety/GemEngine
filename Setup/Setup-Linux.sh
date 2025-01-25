#!/bin/bash

pushd ..
Setup/Vendor/Binaries/Premake/Linux/premake5 --cc=clang --file=Build.lua gmake2
popd
