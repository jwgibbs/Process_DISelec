import os
env = Environment(ENV = os.environ)
env.ParseConfig('root-config --cflags --glibs')
t = env.Program(target='Process_DISelec', source=['Process_DISelec.cc', 'HistManager.cc', 'ElecReader.cc', 'ElecCounter.cc'])
Default(t)
