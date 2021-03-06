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
cppList = []

# mk define
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
    f.write(maincpp)
    createCppList(cppPath)
    for cpp in cppList:
        f.write(' \\\n\t\t../%s'%cpp)
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

def createCppList(cpp):
    if os.path.isfile(cpp):
        name, ext = os.path.splitext(cpp)
        if '.cpp' == ext.lower():
            cppList.append(cpp)
    elif os.path.isdir(cpp):
        for file in os.listdir(cpp):
            sourceFile = os.path.join(cpp, file)
            if os.path.isdir(sourceFile):
                if strInList(excludeDir, file):
                    continue
                createCppList(sourceFile)
            elif os.path.isfile(sourceFile):
                if strInList(excludeFile, file):
                    continue
                createCppList(sourceFile)

def strInList(list, key):
    l = [i for i in list if isinstance(i, str) and i == key]
    if len(l) > 0:
        return True
    return False

if '__main__' == __name__:
    make()
    print('create Android.mk finished!!')
    os.system('pause')
