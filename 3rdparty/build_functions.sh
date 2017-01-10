#!/bin/bash

deps_rootdir=`readlink -f $(dirname $BASH_SOURCE)`
deps_builddir="${deps_rootdir}/.build"
install_prefix="${deps_rootdir}/.deploy"

zbar_srcdir="${deps_rootdir}/ZBar"
zbar_builddir="${deps_builddir}/ZBar"
zbar_config_opts=(
  --prefix=${install_prefix}
  --disable-video
  --without-x
  --without-python
  --without-gtk
  --without-qt
)

# TODO generalize this to "dep_configure"
zbar_configure() {
  local dep='zbar'
  local builddir=$zbar_builddir
  local srcdir=$zbar_srcdir
  local opts=( ${zbar_config_opts[@]} )
  local rundir=$(pwd)
  local config="${srcdir}/configure"

  if (( RECONF )); then
    cd $srcdir
    echo "## [$dep] Generating 'configure' script'"
    autoreconf -i
  fi

  test -d $builddir || mkdir -pv $builddir
  cd $builddir
  echo "## [$dep] Running 'configure' script'"
  $config "${opts[@]}"
  cd $rundir
}

zbar_build() {
  local rundir=$(pwd)
  cd $zbar_builddir
  make all -j4
  cd $rundir
}

zbar_deploy() {
  local dep=zbar
  local rundir=$(pwd)
  local prefix=$install_prefix

  if [[ -d ${prefix} ]]; then
    rm -rfv ${prefix}/*
  else
    mkdir -pv $prefix
  fi
  cd $zbar_builddir
  echo "## [$dep] Installing..."
  make install
  cd $rundir
}
