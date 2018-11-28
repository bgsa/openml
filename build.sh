rm -rf build
mkdir build
cd build
cmake .. -DMAJOR_COLUMN_ORDER:BOOL=ON
cmake --build .
cd ..
cp -R ./resources ./build/
