set -ex

cd deps/lfi-runtime
meson setup build --libdir=lib --prefix=$PWD/install
cd build
ninja install
