# graph_project
This project takes as an input a .txt file, which contains an integer stating how many vertices there are, and an adjacency list, which informs us about the connections inside the graph. Provided that the graph is not directed, the program proceeds to draw the graph.
For it to work: graph.txt must be next to the .exe file (an example file which works with the program is added).

This project uses: 
CMake (>= 3.20)
SFML
vcpkg

To run this thing, likely this should work for Windows:
```In powershell, type:
cmake -S . -B build `
  -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake `
  -DVCPKG_TARGET_TRIPLET=x64-windows

cmake --build build --config Release
