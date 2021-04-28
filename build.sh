BUILD_DIR=./build
echo "Building stock-trading Application ....."
if [[ ! -d "$BUILD_DIR" ]]; then
  mkdir build
fi
cd build; cmake ..
cmake --build .
cd -
