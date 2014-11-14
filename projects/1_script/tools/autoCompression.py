#coding: utf-8
__author__ = 'dihl'

## 自动压缩图片

import os
import time
import os.path
import shutil

##str = r'pngquant -f --ext .png --quality=50-50 "D:\Program Files\beijing2.png"'
##print str
##os.system(str)
## os.system("pngquant -f --ext .png --quality=50-50 beijing2.png")

## 1单位是秒，表示暂停1秒再运行程序
## time.sleep(1)

##os.system('pause')

## 原文件目录
SOURCE_DIR = ur'..\Resources'
## 复制原文件目录下的文件到的目的目录
## 压缩目的目录下的图片
COMPRESSION_DIR = ur'..\ResourcesCompression'
## 在android工程目录下执行下面的bat语句
## mklink /J "assets" "..\ResourcesCompression"
## pause
## 此时编译android工程，即是图片压缩后的apk安装包

## 压缩质量
quality = 30

copyFileCounts = 0
pngFileCounts = 0
compressionCounts = 0

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
    global copyFileCounts
    global pngFileCounts
    if sourceDir.find('.svn') > 0:
        return
    print ur'%s: 当前处理文件夹%s已处理%d个文件'%(curTime(), sourceDir, copyFileCounts)
    for file in os.listdir(sourceDir):
        sourceFile = os.path.join(sourceDir, file)
        targetFile = os.path.join(targetDir, file)
        if os.path.isfile(sourceFile):
            ## 创建目录
            if not os.path.exists(targetDir):
                os.makedirs(targetDir)
            copyFileCounts += 1
            ## 计算png文件个数
            name, ext = os.path.splitext(sourceFile)
            if ext.lower() == '.png':
                pngFileCounts += 1
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

## 压缩文件夹内的图片
def compression(sourceDir):
    if os.path.isdir(sourceDir):
        for file in os.listdir(sourceDir):
            sourceFile = os.path.join(sourceDir, file)
            if os.path.isdir(sourceFile):
                compression(sourceFile)
            elif os.path.isfile(sourceFile):
                ## 判断后缀是不是png
                name, ext = os.path.splitext(file)
                if ext.lower() == '.png':
                    compressionFile(sourceFile)
    elif os.path.isfile(sourceDir):
       compressionFile(sourceDir)

def compressionFile(sourceFile):
    global compressionCounts
    if not os.path.isfile(sourceFile):
        return
    str = ur'pngquant -f --ext .png --quality=%d-%d "%s"'%(quality, quality, sourceFile)
    os.system(r'@echo off')
    os.system(str)
    print ur'%s: 完成压缩文件：%s'%(curTime(), sourceFile)
    compressionCounts += 1
    print ur'压缩完成百分比: %.3f%%'%(compressionCounts*100.0/pngFileCounts)

if '__main__' == __name__:
    removeFileDir(COMPRESSION_DIR)
    copyFiles(SOURCE_DIR, COMPRESSION_DIR)
    print ur'共有%d个图片文件'%(pngFileCounts)
    compression(COMPRESSION_DIR)
    print ur'共压缩%d个图片文件'%(compressionCounts)
    os.system('pause')



