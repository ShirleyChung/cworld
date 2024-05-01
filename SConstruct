import os
env = Environment(CXX='g++', CPPPATH=['third_party/rapidjson/include'])

VariantDir('build_scons', '.', duplicate = 0)
 
cworld = env.Program(target = 'build_scons/cworld', source = [Glob('build_scons/*.cpp')], LIBS=['rapidjson'])

env.Install( '#out', cworld )
env.Alias( 'install', '#out' )
