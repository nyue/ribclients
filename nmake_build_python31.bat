REM Example of how to build the python module for Python3.x so that it is usable with Blender3D on Windows

del /f CMakeCache.txt
cmake -DPYTHON_EXECUTABLE="C:/Python31/python.exe" -DPYTHON_INCLUDE_DIR="C:/Python31/include" -DPYTHON_LIBRARY="C:/Python31/libs/python31.lib" -DPYTHON_DEBUG_LIBRARY="C:/Python31/libs/python31.lib" -DCMAKE_BUILD_TYPE=Release -DRENDERER="3Delight" -G "NMake Makefiles" ..
