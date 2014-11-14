__author__ = 'dihl'

import os

androidAsset = r'../proj.android/assets'
#linkAsset = r'../ResourcesCompression'
linkAsset = r'../ResourcesAndroid'

strCmd = ur'mklink /J "%s" "%s"'%(androidAsset, linkAsset)
os.system(strCmd)
os.system('pause')
