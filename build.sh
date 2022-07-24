#!/usr/bin/bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DUSE_GL=TRUE -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cp build/compile_commands.json compile_commands.json
cmake --build build