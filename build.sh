#! /bin/bash

# Maybe it's necessary to downgrade harfbuzz package to
# avoid linking erros "FT_Get_Var_Blend_Coordinates" if using freetype-infinality
#
# run:
#  $ sudo pacman -U http://archive.archlinux.org/packages/h/harfbuzz/harfbuzz-1.3.4-1-x86_64.pkg.tar.xz
# see:
#  - http://archlinux.org.ru/forum/topic/16942
#  - https://bugzilla.redhat.com/show_bug.cgi?id=1410528

builddir=.build/linux
srcdir=$(pwd) # assuming it's always exec from source dir
libpath='3rdparty/zint-2.5.1/build/lib'
exe="${builddir}/ScanCode"

while (( $# )); do
  case $1 in
    --run) RUN=1;;
    --clean) CLEAN=1;;
  esac
  shift
done

[ -d $builddir ] || mkdir -pv $builddir

cd $builddir
qmake $srcdir
if (( CLEAN )); then
    make clean
fi
make -j4
cd $srcdir

if (( RUN )); then
  LD_LIBRARY_PATH=$libpath $exe
fi
