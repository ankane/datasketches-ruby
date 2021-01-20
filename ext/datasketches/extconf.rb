require "mkmf-rice"

$CXXFLAGS += " -std=c++11"

ext = File.expand_path(".", __dir__)
datasketches = File.expand_path("../../vendor/datasketches-cpp", __dir__)

$srcs = Dir["#{ext}/*.cpp"]
$INCFLAGS += " -I#{datasketches}/common/include -I#{datasketches}/cpc/include -I#{datasketches}/hll/include -I#{datasketches}/kll/include"

create_makefile("datasketches/ext")
