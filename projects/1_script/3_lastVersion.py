#coding: utf-8
__author__ = 'dihl'

import os
import os.path
import shutil
import zipfile
import time

## 变量设置
apkPath = r'..\proj.android\bin\TaijiMan.apk'
soPath = r'..\proj.android\obj\local\armeabi\libgulu.so'

exePath = r'..\proj.win32\Debug.win32\TaijiMan.win32.exe'
dllPath = r'..\..\dll'
resourcePath = r'..\Resources'

## 版本存放目录
versionPath = r'../../version'

## 文件夹下的文件夹数量
def dirInDirCount(dir):
    if not os.path.exists(dir):
        return 0
    dirCount = 0
    for file in os.listdir(dir):
        path = os.path.join(dir, file)
        if  os.path.isdir(path):
            dirCount += 1
    return dirCount

## 确定版本号
def version():
    dirPath = versionPath
    if not os.path.exists(dirPath):
        os.makedirs(dirPath)
    if os.path.isdir(dirPath):
        ver = dirInDirCount(dirPath)
        print(ur'新版本号：%d'%(ver))
        return ver
    else:
        return 0

## 创建版本目录
def createVersionDir(version):
    ## 根据版本号，生成版本目录
    dirVer = ur'v%d'%(version)
    path = os.path.join(versionPath, dirVer)
    print(ur'新版本存放目录: %s'%(path))
    ## 如果已经存在此目录，则删除，再创建
    if os.path.exists(path):
        return ''
#        print(ur'删除现有目录: %s'%(path))
#        shutil.rmtree(path, True)
    ## 创建新目录
    os.makedirs(path)
    print(ur'创建新版本目录成功')
    return path

## android版本
## 拷贝apk和so文件，so文件进行zi压缩
def android(newVerPath):
    print(ur'拷贝android版本')
    ## 创建android版本目录
    androidPath = os.path.join(newVerPath, r'android');
    print(ur'创建androi版本目录: %s'%(androidPath))
    os.makedirs(androidPath)
    ## pak
    androidApk(androidPath)
    ## so
    androidSo(androidPath)
    print(ur'android版本备份成功')

## 拷贝apk
def androidApk(path):
    shutil.copy(apkPath, path)
    print(ur'android版本apk备份完成')

## 拷贝so文件，并进行zip压缩
def androidSo(path):
    shutil.copy(soPath, path)
    print(ur'android版本so备份完成')
    orgSoPath, fileName = os.path.split(soPath)
    file, ext = os.path.splitext(fileName)
    ## zip路径
    zipPath = os.path.join(path, ur'%s.zip'%(file))
    ## 进行压缩
    zip = zipfile.ZipFile(zipPath, 'w', compression=zipfile.ZIP_DEFLATED)
    zip.write(soPath, arcname=fileName)
    zip.close()
    print(ur'android版本so压缩完成')

## win32版本
def win32(newVerPath):
    print(ur'拷贝win32版本')
    ## 创建win32版本目录
    win32Path = os.path.join(newVerPath, r'win32')
    print(ur'创建win32版本目录: %s'%(win32Path))
    os.makedirs(win32Path)
    ## win32版本exe
    win32Exe(win32Path)
    ## win32版本dll
    win32Dll(win32Path)
    ## win32版本resource
    win32Resource(win32Path)
    print(ur'win32版本备份成功')

## 拷贝win32版exe
def win32Exe(path):
    shutil.copy(exePath, path)
    print(ur'win32版本exe备份完成')

def win32Dll(path):
    copyFiles(dllPath, path)
    print(ur'win32版本dll备份完成')

def win32Resource(path):
    copyFiles(resourcePath, path)
    print(ur'win32版本resource备份完成')


## 当前时间字符串
def curTime():
    return time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time()))


def copyFiles(sourceDir, targetDir):
    global copyFileCounts
    global pngFileCounts
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
                ## print ur'%s: %s复制完毕'%(curTime(), targetFile)
            else:
                print ur'%s: %s已存在，不重复复制'%(curTime(), targetFile)
        elif os.path.isdir(sourceFile):
            copyFiles(sourceFile, targetFile)

if '__main__' == __name__:
    verNum = version()
    newVerPath = createVersionDir(verNum);
    if len(newVerPath) == 0:
        print(ur'新版本目录已经存在，请自行备份')
    else:
        print(ur'新版本目录: %s'%(newVerPath))
        android(newVerPath)
        win32(newVerPath)
        print(u'版本:%d\t备份完成'%(verNum))
    os.system('pause')
