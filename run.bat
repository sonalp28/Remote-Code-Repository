@echo off
cd "Debug"
start ServerPrototype.exe
cd "../GUI/bin/Debug"
start GUI.exe 8084 1
