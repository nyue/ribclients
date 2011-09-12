#!/bin/sh
# This assumes that libutil.a has been previously build with cmake and is
# available in ../build/utils

RUBY=/opt/ruby/v1.8.5p231/bin/ruby

swig -ruby -includeall -c++ -I../utils -o RIBClientRUBY_wrap.cxx RIBClient.i 

env USE_DELIGHT=1 RUBY_VERSION=180 $RUBY extconf.rb --with-rman-dir=$DELIGHT --with-utils-include=../utils/ --with-utils-lib=../build/utils

make clean all
