#!/bin/bash

#for example, if you want to download 3.15.3 install packets
majorVersion=3.15
minorVersion=3
fullVersion=$majorVersion.$minorVersion
TARGET=/home/elmpprv/projs
INSTALLPACKET=cmake-$fullVersion.tar.gz

#echo $majorVersion
#echo $minorVersion
#echo $fullVersion
#echo $INSTALLPACKET

if [ ! -f $INSTALLPACKET ]
then
    echo "download '$INSTALLPACKET'"
    wget https://cmake.org/files/v$majorVersion/$INSTALLPACKET
fi

if [ ! -d cmake-$fullVersion ]
then
    tar -zxvf cmake-$fullVersion.tar.gz
fi

cd cmake-$fullVersion
./bootstrap --prefix=$TARGET
make;make install
