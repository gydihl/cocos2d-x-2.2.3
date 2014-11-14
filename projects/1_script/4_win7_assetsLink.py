#coding: utf-8
__author__ = 'dihl'

import os

androidAsset = r'../proj.android/assets'
## 平常开发过程中使用原始资源
print(ur'平常开发过程中使用原始资源')
linkAsset = r'../Resources'
## 最后测试压缩资源效果时使用的压缩资源
## print(ur'平常开发过程中使用原始资源')
##linkAsset = r'../ResourcesCompression'

strCmd = ur'mklink /J "%s" "%s"'%(androidAsset, linkAsset)
os.system(strCmd)
os.system('pause')
