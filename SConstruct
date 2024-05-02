import os
env = Environment(CXX='g++', CPPPATH=['third_party/rapidjson/include'],CXXFLAGS=["-std=c++11"])

VariantDir('build_scons', '.', duplicate = 0)
 
cworld = env.Program(target = 'build_scons/cworld', source = [Glob('build_scons/*.cpp')])

env.Install( '#out', cworld )
env.Alias( 'install', '#out' )
dataDir = 'data'
env.Install( '#out', source=dataDir )
