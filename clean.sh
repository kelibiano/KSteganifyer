
clean() {
    rm Makefile
    rm -rf CMakeFiles
    rm cmake_install.cmake
}

rm Steganifyer
rm CMakeCache.txt
clean

cd modules
clean

cd mSteganifyer
clean

cd ../mBMPIO
clean

cd ../../test
clean