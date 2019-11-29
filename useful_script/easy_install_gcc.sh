gcc_version=9.2.0
wget https://ftp.gnu.org/gnu/gcc/gcc-${gcc_version}/gcc-${gcc_version}.tar.xz
wget https://ftp.gnu.org/gnu/gcc/gcc-${gcc_version}/gcc-${gcc_version}.tar.xz.sig
wget https://ftp.gnu.org/gnu/gnu-keyring.gpg
signature_invalid=`gpg --verify --no-default-keyring --keyring ./gnu-keyring.gpg gcc-${gcc_version}.tar.xz.sig`
#if [ $signature_invalid ]; then echo "Invalid signature" ; exit 1 ; fi
tar xf gcc-${gcc_version}.tar.xz
cd gcc-${gcc_version}
./contrib/download_prerequisites
cd ..
mkdir gcc-${gcc_version}-build
cd gcc-${gcc_version}-build
$PWD/../gcc-${gcc_version}/configure --prefix=$HOME/projs --enable-languages=c,c++
make -j$(nproc)
make install
