#!/bin/bash

LIBRARY="bcm2835-1.46"
LIBRARY_BASE_DIR="http://www.airspayce.com/mikem/bcm2835/"
PWD="$(pwd)"
BASE_DIR="$PWD"
BCM_DIR="$PWD/$LIBRARY"

echo ""
echo "Checking system..."

if [ -d "$BCM_DIR" ]; then
    echo "bcm2835 directory ($LIBRARY) already exists, using it"
else
    echo "downloading $LIBRARY library"
    wget $LIBRARY_BASE_DIR/$LIBRARY.tar.gz
    echo "untarring $LIBRARY library"
    tar -xvf $LIBRARY.tar.gz
    echo "untarred $LIBRARY library"
fi

sleep 1

echo "Checking required packages..."

sudo apt-get update

dpkg -s g++ 2>/dev/null >/dev/null || sudo apt-get -y install g++
dpkg -s zip 2>/dev/null >/dev/null || sudo apt-get -y install zip
dpkg -s unzip 2>/dev/null >/dev/null || sudo apt-get -y install unzip

echo "Pacakes installed..."
echo "Unzipping libraries, this will take a while..."

cd "$LIBRARY" && chmod +x configure && ./configure && sudo make && sudo make install && cd .. 

sleep 1

echo ""
echo "Libraries compiled and installed successfully!!! You can now use Broadcom BCM 2835 in your Raspberry Pi projects"
echo "Library sourced from $LIBRARY_BASE_DIR"
echo ""

exit 0

