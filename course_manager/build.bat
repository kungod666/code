@echo off
chcp 65001 > nul
if not exist output mkdir output

g++ main.cpp -Wall -Wextra -g3 -I"C:/Program Files/MariaDB/MariaDB Connector C 64-bit/include" -I"third_party/libsodium/include" "C:/Program Files/MariaDB/MariaDB Connector C 64-bit/lib/libmariadb.lib" -L"third_party/libsodium/lib" -lsodium -o output/main.exe
if errorlevel 1 (
    echo Build failed
    exit /b 1
)

copy /Y "third_party\libsodium\bin\libsodium-26.dll" output\ > nul
echo Build completed: output\main.exe