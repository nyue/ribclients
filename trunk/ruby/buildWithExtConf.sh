#!/bin/sh
# This assumes that libutil.a has been previously build with cmake and is
# available in ../build

swig -ruby -includeall -c++ -I../utils -o RIBClientRUBY_wrap.cxx RIBClient.i 

# env USE_PRMAN=1 ruby extconf.rb --with-rman-dir=$RMANTREE --with-utils-include=../utils/ --with-utils-lib=../build/

env USE_DELIGHT=1 RUBY_VERSION=180 ruby1.8 extconf.rb --with-rman-dir=$DELIGHT --with-utils-include=../utils/ --with-utils-lib=../build/
# env USE_DELIGHT=1 RUBY_VERSION=190 ruby1.9 extconf.rb --with-rman-dir=$DELIGHT --with-utils-include=../utils/ --with-utils-lib=../build/

make clean all
