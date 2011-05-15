require "mkmf"
dir_config('rman')
dir_config('utils')
# dir_config('vecmath')
have_header('ri.h')


puts "NICHOLAS ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
puts CONFIG["CFLAGS"]
puts CONFIG["LDSHARED"]
puts "NICHOLAS ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"


if (RUBY_PLATFORM.include? "mswin")
  have_library('utils')
  if (ENV["USE_PRMAN"])
    have_library('librib')
    have_library('libtarget')
    have_library('libzip')
    have_library('libprmutil')
    have_library('ws2_32')
    have_library('netapi32')
    $CFLAGS << ' -DPRMAN_RIBCLIENT' #
  elsif (ENV["USE_DELIGHT"])
    have_library('3delight')
    $CFLAGS << ' -DDELIGHT_RIBCLIENT -GX' #
  elsif (ENV["USE_AQSIS"])
    have_library('ri2rib')
    $CFLAGS << ' -DAQSIS_RIBCLIENT' #
  elsif (ENV["USE_RDC"])
    have_library('ribdc')
    $CFLAGS << ' -DRDC_RIBCLIENT' #
  elsif (ENV["USE_PIXIE"])
    have_library('ri')
    $CFLAGS << ' -DPIXIE_RIBCLIENT' #
  end
else # Linux and Darwin are classify as poxi platform
  have_library('utils')
  if (ENV["USE_PRMAN"])
    # The ordering of this libraries are extremely important, ask PIXAR!
    have_library('prmutil')
    have_library('zip')
    have_library('target')
    have_library('rib')
    $CFLAGS << ' -DPRMAN_RIBCLIENT' #
  elsif (ENV["USE_DELIGHT"])
    have_library('3delight')
    $CFLAGS << ' -DDELIGHT_RIBCLIENT' #
  elsif (ENV["USE_AQSIS"])
    have_library('ri2rib')
    $CFLAGS << ' -DAQSIS_RIBCLIENT' #
  elsif (ENV["USE_RDC"])
    have_library('ri2rib')
    $CFLAGS << ' -DRDC_RIBCLIENT' #
  elsif (ENV["USE_PIXIE"])
    have_library('ri')
    $CFLAGS << ' -DPIXIE_RIBCLIENT' #
  end
  # Linux and Darwin requires different flags
  if (RUBY_PLATFORM.include? "darwin")
    CONFIG["CC"] = "g++"
    CONFIG["LDSHARED"].gsub!("cc","g++") # use c++
  else
    CONFIG["CC"] = "g++"
    CONFIG["CXX"] = "g++"
  end
end

if ( Integer(ENV["RUBY_VERSION"]) >= 190 )
  $CFLAGS << ' -DRUBY_VERSION_POST_180'
end

if (RUBY_PLATFORM.include? "mswin")
  CONFIG["DLDFLAGS"].gsub!("-debug","") # disable debug build
  CONFIG["DLDFLAGS"].gsub!("-incremental:no",
                           "-incremental:no -nodefaultlib:msvcrtd") # 
#  $LDFLAGS << ' -link -nodefaultlib:msvcrtd '
#  puts $LDFLAGS
else
  $LDFLAGS << ' -headerpad_max_install_names '
end

#puts "NICHOLAS ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
#puts CONFIG["LDSHARED"]
#puts CONFIG["CFLAGS"]
#puts CONFIG["DLDFLAGS"]
puts CONFIG["LDFLAGS"]
#puts "NICHOLAS ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"

create_makefile("ribclient")
