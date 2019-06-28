# Boggle Sample

#### Omar Gonzalez
Hi! My name is Omar Gonzalez and I am applying for the open position of Network Engineer listed here: https://www.guerrilla-games.com/join/network-engineer
This is the git repo of a my code sample. It is a simple solver for a game called Boggle(https://en.wikipedia.org/wiki/Boggle).


# Instructions

To build project files you will need to have cmake installed. I've tested against MSVC 15.9.13 and GCC 7

## Windows
```
git clone https://github.com/Tenbatsu589/guerilla-games.git
cmake -B build -G "Visual Studio 15 2017 Win64"
cd build
MSBuild Boggle.sln -t:BoggleTest -p:Configuration=Release
cd ..\bin
BoggleTest.exe dictionary.txt board_1.txt board_1_solution.txt
```
## Linux
```
git clone https://github.com/Tenbatsu589/guerilla-games.git
cmake -B build_linux  -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc-7 -DCMAKE_CXX_COMPILER=g++-7
cd build_linux
make BoggleTest
cd ..\bin
./BoggleTest dictionary.txt board_1.txt board_1_solution.txt
```

