
mode = ARGUMENTS.get('mode', 'debug')
print '##################'
print '## ' + mode
print '##################'

env = Environment(

    #add cpp path here
    CPPPATH=[
        '.'
    ],

    #add flags here
    CPPFLAGS=[
        '-Wno-deprecated',
    ],

    #add libs here
    LIBS=[
        'sampler',
        'model',
        'tools',
    ], 

    #add libpath here
    LIBPATH=[
        'lib/'+mode
    ],

)

if mode == 'debug':
    env.Append(CPPFLAGS=['-g'])
    env.Replace(OBJSUFFIX=['.o'])
    env.Replace(PROGSUFFIX=['.debug'])
elif mode == 'release':
    env.Append(CPPFLAGS=['-O2'])
    env.Replace(OBJSUFFIX=['.os'])
    env.Replace(PROGSUFFIX=['.release'])
else:
    print "What?"

env.Program('bin/demo','apps/demo.cc')
env.Program('bin/rand','apps/rand.cc')
env.Program('bin/is_can','apps/is_can.cc')
env.Program('bin/sc_can','apps/sc_can.cc')

env.Library('lib/'+mode+'/sampler', [ 
    'sampler/sampler.cc',   #basic class
    'sampler/simple.cc',    #demo  
    #add user model
    #'sampler/user.cc',
    'sampler/canonical.cc',
   ], 
)

env.Library(
    'lib/'+mode+'/model', [ 
        'model/model.cc',     #basic class
        'model/simple.cc',    #demo  
        #add user model
        #'model/user.cc',
        'model/ising.cc',
        'model/singlechain.cc',
        'model/link.cc',
    ], 
)

env.Library(
    'lib/'+mode+'/tools', [ 
        #add user file 
        #'tools/user.cc',
        'tools/CReader.cc', 
        'tools/ext_math.cc',
    ], 
)

