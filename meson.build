# set the compiler to clang first
# export CC=/usr/bin/clang

project('improved-octo-waffle', 'cpp',
 default_options : ['cpp_std=c++17'] )

inc = include_directories('src')
inc = include_directories('extern')

srcs = [ 'src/main.cpp'
       , 'src/graphics.cpp'
       , 'src/input.cpp'
       , 'src/resourcemanager.cpp'
       , 'src/texturemanager.cpp'
       , 'src/ecs.cpp'
       , 'src/components.cpp'
       , 'src/parsegamekeys.cpp'
       , 'src/parseinternalgameevents.cpp'
       #, 'src/tilemappathfinding.cpp'
       , 'src/extrastate.cpp'
       , 'src/collision.cpp'
       , 'src/gameconfig.cpp'
       , 'src/tilemap.cpp'
       ]

executable('improved-octo-waffle'
        , srcs
        , cpp_args : ['-Wall', '-Wextra', '-O2', '-g']
        , link_args : ['-lsfml-graphics', '-lsfml-window', '-lsfml-audio', '-lsfml-network', '-lsfml-system'] )


testsrcs = [ 'tests/main-tests.cpp'  
           , 'tests/packedvectortests.cpp'  
           , 'tests/tilemaptests.cpp'  
           , 'tests/graphtests.cpp'  
           , 'src/tilemap.cpp'  
           ]
unittests = executable('unittests', testsrcs, cpp_args : ['-Wall', '-Wextra', '-O2', '-g'], link_args :['-lsfml-graphics', '-lsfml-window', '-lsfml-audio', '-lsfml-network', '-lsfml-system'])
test('unittests', unittests )

smallmainsrcs = [ 'tests/smallmain.cpp' ]
smallmain = executable('smallmain', smallmainsrcs, cpp_args : ['-Wall', '-Wextra', '-g'], link_args :['-lsfml-graphics', '-lsfml-window', '-lsfml-audio', '-lsfml-network', '-lsfml-system'])
