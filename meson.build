# set the compiler to clang first
# export CC=/usr/bin/clang

project('improved-octo-waffle', 'cpp',
 default_options : ['-std=c++17'] )

inc = include_directories('src')
inc = include_directories('extern')

srcs = [ 'src/main.cpp'
       , 'src/input.cpp'
       ]

executable('improved-octo-waffle'
        , srcs
        , cpp_args : ['-Wall', '-Wextra', '-O2', '-g']
        , link_args : ['-lsfml-graphics', '-lsfml-window', '-lsfml-audio', '-lsfml-network', '-lsfml-system'] )


testsrcs = [ 'tests/main-tests.cpp'  
           , 'tests/packedvectortests.cpp'  
           ]
unittests = executable('unittests', testsrcs, cpp_args : ['-Wall', '-Wextra', '-O2', '-g'], link_args :[])
test('unittests', unittests )

