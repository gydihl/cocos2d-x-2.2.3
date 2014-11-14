#coding: utf-8
__author__ = 'dihl'

import os
import os.path

cppPath = '../Classes'
mkPath = '../proj.android/jni/Android.mk'

# exclude
excludeDir = ['Pay']
excludeFile = ['']
# create cpp list
find_files = []


# mk define
FIND_CPP_FILES = 'FIND_CPP_FILES'
wordWrap = "\n\n"
localPath = r'LOCAL_PATH := $(call my-dir)'
CLEAR_VARS = r'include $(CLEAR_VARS)'
localModule = r'LOCAL_MODULE := gulu_shared'
localModuleFile = r'LOCAL_MODULE_FILENAME := libgulu'
maincpp = 'LOCAL_SRC_FILES := hellocpp/main.cpp'
localCInclude = r'LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes'
BUILD_SHARED_LIBRARY = r'include $(BUILD_SHARED_LIBRARY)'

LOCAL_WHOLE_STATIC_LIBRARIES = ['cocos2dx_static',
                                'mobclickcpp_static',
                                'cocosdenshion_static',
                                'box2d_static',
                                'chipmunk_static',
                                'cocos_extension_static',
                                'libJson_static']

import_module = [r'cocos2dx',
                 r'libMobClickCpp',
                 r'cocos2dx/platform/third_party/android/prebuilt/libcurl',
                 r'CocosDenshion/android',
                 r'extensions',
                 r'external/Box2D',
                 r'external/chipmunk',
                 r'libJson']


def make():
    f = file(mkPath, 'w')
    f.write(localPath)
    f.write(wordWrap)
    f.write(CLEAR_VARS)
    f.write(wordWrap)
    f.write(localModule)
    f.write(wordWrap)
    f.write(localModuleFile)
    f.write(wordWrap)
    # cpp list
    createFindCppList(cppPath)
    for find in find_files:
        f.write('%s\n'%find)
    f.write('$(warning $(%s))'%FIND_CPP_FILES)
    f.write(wordWrap)

    f.write(maincpp)
    f.write('\nLOCAL_SRC_FILES += $(%s:$(LOCAL_PATH)/%%=%%)'%FIND_CPP_FILES)
    f.write('\n$(warning $(LOCAL_SRC_FILES))')
    f.write(wordWrap)

    f.write(localCInclude)
    f.write(wordWrap)
    # LOCAL_WHOLE_STATIC_LIBRARIES
    libList = createLOCAL_WHOLE_STATIC_LIBRARIES()
    for lib in libList:
        f.write(lib)
    f.write(wordWrap)
    f.write(BUILD_SHARED_LIBRARY)
    f.write(wordWrap)
    # import_module
    moduleList = createImportModule()
    for module in moduleList:
        f.write(module)
    f.write(wordWrap)

def createLOCAL_WHOLE_STATIC_LIBRARIES():
    return ['LOCAL_WHOLE_STATIC_LIBRARIES += %s\n'%(lib) for lib in LOCAL_WHOLE_STATIC_LIBRARIES]

def createImportModule():
    return ['$(call import-module,%s)\n'%(module) for module in import_module]

def createFindCppList(folder):
    if os.path.isdir(folder):
        if strInList(excludeDir, folder):
            return
        find_files.append('%s += $(wildcard find $(LOCAL_PATH)/../%s/*.cpp)'%(FIND_CPP_FILES, folder))
        for file in os.listdir(folder):
            sourceFile = os.path.join(folder, file)
            if os.path.isdir(sourceFile):
                createFindCppList(sourceFile)

def strInList(list, key):
    l = [i for i in list if isinstance(i, str) and key.find(i) > -1]
    if len(l) > 0:
        return True
    return False

if '__main__' == __name__:
    make()
    print('create Android.mk finished!!')
    os.system('pause')
