from building import *
import rtconfig

# get current directory
cwd     = GetCurrentDir()
# The set of source files associated with this SConscript file.
src     = Glob('Arm-2D/Library/Source/*.c')
src    += Glob('Arm-2D/Helper/Source/*.c')
src    += Glob('Arm-2D/Lcdprintf/*.c')

if GetDepend('PKG_ARM_2D_USE_EXAMPLE_BASIC'):
	src    += Glob('example/example_basic.c')

if GetDepend('PKG_ARM_2D_USE_EXAMPLE_COMPLEX'):
	src    += Glob('example/example_complex.c')
	src    += Glob('example/array.c')

path    = [cwd + '/Arm-2D/Library/Include']
path   += [cwd + '/Arm-2D/Helper/Include']
path   += [cwd + '/Arm-2D/Lcdprintf']
path   += [cwd + '/example']

LOCAL_CCFLAGS = ''
CPPDEFINES = []

if GetDepend('PKG_ARM_2D_USE_INTERPOLATION_ROTATION'):
	CPPDEFINES += ['__ARM_2D_HAS_INTERPOLATION_ROTATION__=1']

if GetDepend('PKG_ARM_2D_HAS_HELIUM'):
	CPPDEFINES += ['__ARM_2D_HAS_HELIUM__=1']

if GetDepend('PKG_ARM_2D_HAS_CDE'):
	CPPDEFINES += ['__ARM_2D_HAS_CDE__=1']

if GetDepend('PKG_ARM_2D_HAS_ACC'):
	CPPDEFINES += ['__ARM_2D_HAS_HW_ACC__=1']

group = DefineGroup('Arm-2D', src, depend = ['PKG_USING_ARM_2D'], CPPPATH = path, CPPDEFINES = CPPDEFINES, LOCAL_CCFLAGS = LOCAL_CCFLAGS)

Return('group')
