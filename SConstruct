import os

env = Environment()

env['ENV']['TERM'] = os.environ['TERM']

env['CPPFLAGS'] = ['-stdlib=libc++', '-ansi', '-std=c++11', '-O0', '-g', '-fcaret-diagnostics', '-march=native', #'-flto',
'-W', '-Wall', '-Wextra', '-Wpedantic', '-Werror', #'g',
'-Winit-self', '-Wold-style-cast', '-Woverloaded-virtual', '-Wuninitialized', '-Wmissing-declarations']
#env['LINKFLAGS'] = ['-flto']
env['CXX'] = 'clang++'

conf = Configure(env)
env = conf.Finish()

env.Program(target = 'pi', source = ["main.cpp", "pi.cpp", "tsio.cpp", "util.cpp"], LIBS = ['c++', 'supc++', 'pthread', 'gmpxx', 'gmp'])
