cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DUSE_GL=TRUE -DCMAKE_EXPORT_COMPILE_COMMANDS=1
mv build/compile_commands.json compile_commands.json
cmake --build build