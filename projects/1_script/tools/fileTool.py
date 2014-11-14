#coding: utf-8
__author__ = 'dihl'

import os
import time
import os.path
import shutil

## 当前时间
def curTime():
    return time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time()))

## 删除目录下的文件以及文件夹
def removeFileDir(targetDir):
    if os.path.isdir(targetDir):
        for file in os.listdir(targetDir):
            filePath = os.path.join(targetDir, file)
            if os.path.isfile(filePath):
                os.remove(filePath)
                print(filePath+'removed!')
            elif os.path.isdir(filePath):
                shutil.rmtree(filePath, True)
                print('dir: '+filePath+'removed!')

def copyFiles(sourceDir, targetDir):
    if sourceDir.find('.svn') > 0:
        return
    print ur'%s: 当前处理文件夹%s'%(curTime(), sourceDir)
    for file in os.listdir(sourceDir):
        sourceFile = os.path.join(sourceDir, file)
        targetFile = os.path.join(targetDir, file)
        if os.path.isfile(sourceFile):
            ## 创建目录
            if not os.path.exists(targetDir):
                os.makedirs(targetDir)
            ## 文件不存在，或者大小不同则覆盖
            if not os.path.exists(targetFile) or \
                (os.path.getsize(targetFile) != os.path.getsize(sourceFile)):
                ## open(targetFile, 'wb').write(open(sourceFile, 'rb').read())
                shutil.copy(sourceFile, targetFile)
                print u'%s: %s\t复制完毕'%(curTime(), targetFile)
            else:
                print u'%s: %s已存在，不重复复制'%(curTime(), targetFile)
        elif os.path.isdir(sourceFile):
            copyFiles(sourceFile, targetFile)

if '__main__' == __name__:
    SOURCE_DIR = ur'..\..\Resources'
    COMPRESSION_DIR = ur'..\..\ResourcesCompression'
    removeFileDir(COMPRESSION_DIR)
    copyFiles(SOURCE_DIR, COMPRESSION_DIR)
    print(ur'复制文件完成')
    os.system('pause')



