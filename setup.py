#!/usr/bin/env python2.7
from distutils.core import setup, Extension

boundaries_ext_mod = Extension('boundaries',
  sources=['boundaries_python.cpp'],
  include_dirs=['.'],
  libraries=['boost_python'],
  extra_compile_args=["-std=c++11"],
  language='c++',
)

setup(name='Boundaries', ext_modules=[boundaries_ext_mod])