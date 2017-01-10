#! /bin/bash

# Maybe it's necessary to downgrade harfbuzz package to
# avoid linking erros "FT_Get_Var_Blend_Coordinates" if using freetype-infinality
#
# run:
#  $ sudo pacman -U http://archive.archlinux.org/packages/h/harfbuzz/harfbuzz-1.3.4-1-x86_64.pkg.tar.xz
# see:
#  - http://archlinux.org.ru/forum/topic/16942
#  - https://bugzilla.redhat.com/show_bug.cgi?id=1410528

builddir=build
runcwd=$(pwd)
libpath='3rdparty/zint-2.5.1/build/lib'
exe="${builddir}/ScanCode"

cd $builddir
qmake .. && make -j4
cd $runcwd

if [[ ${1:-} = '-r' ]]; then
  LD_LIBRARY_PATH=$libpath $exe
fi
