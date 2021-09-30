## Compilation
This contract is built with eden `clsdk` compiler, to have the local environment configured to compile this contract is needed to [take a look at this link](https://github.com/eoscommunity/demo-clsdk) to learn more or follow these steps to continue forward.

## Get Started
### Ubuntu 20.04
Run the following commands to set local environment.
```
sudo apt-get update
sudo apt-get install -yq    \
    binaryen                \
    build-essential         \
    cmake                   \
    gdb                     \
    git                     \
    libboost-all-dev        \
    libcurl4-openssl-dev    \
    libgmp-dev              \
    libssl-dev              \
    libusb-1.0-0-dev        \
    pkg-config              \
    wget


mkdir ~/work

cd ~/work
wget https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-12/wasi-sdk-12.0-linux.tar.gz
tar xf wasi-sdk-12.0-linux.tar.gz

cd ~/work
wget https://github.com/eoscommunity/Eden/releases/download/sdk-v0.1.0-alpha/clsdk-ubuntu-20-04.tar.gz
tar xf clsdk-ubuntu-20-04.tar.gz
```

Make sure to have the following variables to compile the `rateproducer` contract:
```
export WASI_SDK_PREFIX=~/work/wasi-sdk-12.0
export CLSDK_PREFIX=~/work/clsdk

export PATH=$CLSDK_PREFIX/bin:$PATH
```

Once the previous step is completed, inside of `rateproducer` folder:
```
mkdir build
cd build
cmake `clsdk-cmake-args` ..
make -j
```