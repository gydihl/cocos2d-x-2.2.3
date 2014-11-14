#coding: utf-8
#__author__ = 'gydihl'

# 警告：原文件目录不要和加密后文件目录一样，否则文件将丢失

# 工作原理：
# 删除目的文件目录下的文件
# 复制原文件目录至目的文件目录
# 加密目的文件目录下的文件

import os
import time
import os.path
import shutil
#from MyAESObject import *
from MyGladmanAESObject import *

# 原文件目录
SOURCE_DIR = ur'../../ResourcesCompression'
# SOURCE_DIR = ur'../../Resources'
# 目的文件目录
PURPOSE_DIR = ur'../../ResourcesEncode'

EXCLUDE_DIR = ['music']

AES_KEY     = r'6bead6bf16b9d120fde23bc36e8fbc046bead6bf16b9d120fde23bc36e8fbc04'

ENCODE_COUNT    = 0

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

def AESEncode(dir, aes):
    global ENCODE_COUNT
    if not os.path.isdir(dir):
        return
    for file in os.listdir(dir):
        fileName = os.path.join(dir, file)
        if os.path.isfile(fileName):
            f = open(fileName, 'rb')
            try:
                buff = f.read()
                encode = aes.encode(buff)
            finally:
                f.close()
            f = open(fileName, 'wb')
            try:
                f.write(encode)
            finally:
                f.close()
            ENCODE_COUNT += 1
            print(u'%s: %s\t加密完成'%(curTime(), fileName))
        elif os.path.isdir(fileName):
            if strInList(EXCLUDE_DIR, file):
                continue
            AESEncode(fileName, aes)

def AESDecode(dir, aes):
    if not os.path.isdir(dir):
        return
    for file in os.listdir(dir):
        fileName = os.path.join(dir, file)
        if os.path.isfile(fileName):
            f = open(fileName, 'rb')
            try:
                buff = f.read()
                decode = aes.decode(buff)
            finally:
                f.close()
            f = open(fileName, 'wb')
            try:
                f.write(decode)
            finally:
                f.close()
        elif os.path.isdir(fileName):
            AESDecode(fileName, aes)

def strInList(list, key):
    l = [i for i in list if isinstance(i, str) and i == key]
    if len(l) > 0:
        return True
    return False

if '__main__' == __name__:
    # 删除目的目录下的文件
    removeFileDir(PURPOSE_DIR)
    # 复制文件
    copyFiles(SOURCE_DIR, PURPOSE_DIR)
    # 加密文件
    myAES = MyGladmanAESObject()
    myAES.setkey(AES_KEY)
    AESEncode(PURPOSE_DIR, myAES)
    print(ur'加密完成')
#    AESDecode(PURPOSE_DIR, myAES)
#    print(ur'解密完成')
    os.system('pause')


