# nanomeshview
Mesh viewer based on [libigl](https://github.com/libigl/libigl) and [nanogui](https://github.com/wjakob/nanogui)

The main motivation is to view Draco compressed mesh files which are not yet supported by popular mesh viewer. 

Currently based on a branch of libigl until this branch is clean enough to submit a proper pull request.

## How to build

**libigl uses submodules --recursive is mandatory**

Windows x64 example, update for your platform:

~~~~
git clone --recursive https://github.com/VLAM3D/libigl.git
git clone https://github.com/VLAM3D/nanomeshview
cd nanomeshview
mkdir build
cd build
cmake .. -G "Visual Studio 14 2015 Win64" -DLIBIGL_USE_STATIC_LIBRARY=ON -DLIBIGL_WITH_NANOGUI=ON -DLIBIGL_DIR=c:/dev/libigl
~~~~

The last command must be run 4x times, for some yet unknown reason the CC preprocessor variables from Draco ex: ENABLE\_MESH\_COMPRESSION are not defined on the first run. 

This is probably caused by using *add\_subdirectory* in libigl CMakeList.txt instead of using *find\_package*.

Open solution and build nanomeshviewer_bin. 

