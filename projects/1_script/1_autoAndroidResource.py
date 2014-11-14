#coding: utf-8
__author__ = 'dihl'

import os
from tools import autoCompression
from crypto import AESEncode

## 原文件目录
SOURCE_DIR = ur'..\Resources'
## android资源目录
SOURCE_ANDROID = ur'..\ResourcesAndroid'

# 复制原始文件到Android资源目录
def copy(src, dest):
    autoCompression.removeFileDir(dest)
    autoCompression.copyFiles(src, dest)
    print ur'共有%d个图片文件'%(autoCompression.pngFileCounts)

# 压缩Android资源目录下图片
def compression(dir):
    autoCompression.compression(dir)
    print ur'共压缩%d个图片文件'%(autoCompression.compressionCounts)

# 加密文件
def encode(dir):
    myAES = AESEncode.MyGladmanAESObject()
    myAES.setkey(AESEncode.AES_KEY)
    AESEncode.AESEncode(dir, myAES)

if '__main__' == __name__:
    # 复制
    copy(SOURCE_DIR, SOURCE_ANDROID)
    print(ur'----------原始文件复制完成----------')
    # 压缩
    compression(SOURCE_ANDROID)
    print(ur'----------图片压缩完成----------')
    # 加密
    print(ur'是否对资源进行加密')
    print(ur'只有输入不等于n/N时，才会进行加密')
    type = raw_input()
    if 'n' != type.lower():
        encode(SOURCE_ANDROID)
        print(ur'----------加密完成----------')
    print(u'----------Andord资源准备完毕----------')
    os.system('pause')


