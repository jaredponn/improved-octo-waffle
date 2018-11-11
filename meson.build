# set the compiler to clang first
# export CC=/usr/bin/clang

project('improved-octo-waffle', 'cpp',
 default_options : ['-std=c++17'] )

inc = include_directories('src')

srcs = ['src/main.cpp'
       ]

executable('improved-octo-waffle'
        , srcs
        , cpp_args : ['-Wall', '-Wextra', '-O2', '-g']
        , link_args : [] )

