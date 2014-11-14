#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 2_autoWin32Resource.py
# Author: 底会雷

import os
from tools import win32Resource
from tools import fileTool
from crypto import AESEncode

# 原始资源目录
SOURCE_SRC      = ur'..\Resources'
# 加密后资源目录
SOURCE_WIN32    = ur'..\ResourcesWin32'

# 生成程序中需要的文件
def createWin32Resource():
    win32Resource.init()
    win32Resource.generate_h()
    win32Resource.generate_json()

def copy(src, target):
    fileTool.removeFileDir(target)
    fileTool.copyFiles(src, target)

# 加密文件
def encode(dir):
    myAES = AESEncode.MyGladmanAESObject()
    myAES.setkey(AESEncode.AES_KEY)
    AESEncode.AESEncode(dir, myAES)


if '__main__' == __name__:
    print(ur'是否生产程序所需h和json文件，若生产，程序会编译很长时间')
    print(ur'只有输入y/Y，才会生产h和json文件')
    type = raw_input()
    if 'y' == type.lower():
        # 生成程序中需要的文件
        createWin32Resource()
        print(ur'----------生成文件完成----------')
    # 复制
    copy(SOURCE_SRC, SOURCE_WIN32)
    print(ur'----------原始文件复制完成----------')
    # 加密文件
    print(ur'是否对资源进行加密')
    print(ur'只有输入不等于n/N时，才会进行加密')
    type = raw_input()
    if 'n' != type.lower():
        encode(SOURCE_WIN32)
        print(ur'----------加密完成----------')
    print(u'----------win32资源准备完毕----------')
    os.system('pause')
