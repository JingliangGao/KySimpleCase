#!/bin/bash

CURRENT_DIR=$(pwd)
BUILD_DIR=build


# install system dependencies
sudo apt install -y build-essential cmake python3-pip

# check kytensor-llm is installed
cd ${CURRENT_DIR}
if ! dpkg -s kytensor-llm >/dev/null 2>&1; then
    echo "[INFO] kytensor-llm not found, installing ..."


    ARCH=$(uname -m)   # 或 uname -m
    if [ "$ARCH" = "arm64" ]; then
        echo "[INFO] install kytensor-llm for arm64 ..."
        cd debian/arm64
        sudo dpkg -i kytensor-llm*.deb        
    else
        echo "[INFO] install kytensor-llm for x86_64 ..."
        cd debian/x86_64
        sudo dpkg -i kytensor-llm*.deb
    fi
    
fi


# refresh build directory
cd ${CURRENT_DIR}
if [ -d ${BUILD_DIR} ]; then
    rm -rf ${BUILD_DIR}
fi
mkdir ${BUILD_DIR}

# build for debug
cd ${CURRENT_DIR}
echo "[INFO] Start building for debug ..."
cd ${BUILD_DIR}
cmake ../

make -j16