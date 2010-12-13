REM This assumes that libutil.a has been previously build with cmake and is
REM available in ..\build

del /f RIBClientRUBY_wrap.cxx *.def *.pdb *.obj

swig -ruby -includeall -c++ -I..\utils -o RIBClientRUBY_wrap.cxx RIBClient.i 

REM set USE_PRMAN=1
REM ruby extconf.rb --with-rman-dir=$RMANTREE --with-utils-include=..\utils\ --with-utils-lib=..\build_nmake\utils

set USE_DELIGHT=1
set RUBY_VERSION=180
ruby extconf.rb --with-rman-dir=%DELIGHT% --with-utils-include=..\utils\ --with-utils-lib=..\build_nmake\utils

nmake all
