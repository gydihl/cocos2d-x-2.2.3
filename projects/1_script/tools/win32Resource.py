#!/usr/bin/env python
# -*- coding: utf-8 -*-
# resources.py
# Author: leafsoar (一叶)

import os,sys
from xml.etree import ElementTree as ET
import json

## AssetLoader资源处理脚本

# resources path
rs_path = "../Resources"
# classes path
cs_path = "../Classes/Control"
# resource define
h_file = cs_path + "/ResourceInfo.h"
js_file = rs_path + "/file_list.json"

# json define
file_name_key = "file_name"
file_index_key = "file_index"
texture_name_key = "texture_name"
texture_plist_key = "texture_plist"
texture_image_key = "texture_image"

removeDirList = [r'resources\animation',
                 r'resources\config',
                 r'resources\uifile',
                 r'resources\ui\weaponsystem',
                 r'resources\scene',
                 r'resources\music']

dir_list = []
file_list = []
texture_list = []

# 检测列表中的字符串是否在指定字符串中
def check():
    parse

# 初始化方法
def init():
    # 填充所有目录和文件名称
    for dirpath, dirnames, filenames in os.walk(rs_path):
        bRemove = False
        for removeDir in removeDirList:
            if (dirpath.lower().find(removeDir) > -1):
                bRemove = True
                break
        dir_list.append(dirpath)
        if bRemove:
            continue
        for filename in filenames:
            file_list.append(dirpath + "/" + filename)
    # 填充 texture
    for filename in file_list:
        name, ext = os.path.splitext(filename)
        if ext == ".plist":
            texture_list.append(filename)
    

# 根据扩展名称返回缩写
def getPreByExt(ext):
    if ext.find('.') >= 0:
        ext = ext[1:]
    ext_dict = {
        "png": "i",
        "PNG": "i",
        "jpg": "i",
        "plist": "p",
        "ttf": "t",
        "gif": "i",
        "db": "d",
        "json": "js",
        "ExportJson": "ejs",
        "tmx": "tmx",
        "xml": "xml",
        "fnt": "f",
        'pvr.ccz': 'pc'
    }
    if len(ext) > 0:
        return ext_dict[ext]
    else:
        return ""

def generate_h():
    if os.path.isfile(h_file):
        os.remove(h_file)

    f = file(h_file, 'w')
    f.write("#ifndef _AUTO_RESOURCES_H_\n")
    f.write("#define _AUTO_RESOURCES_H_\n\n")

    # 生成目录定义
    f.write("// search paths\n")
    f.write("static const char* s_szSearchPath[] = {\n")
    for dirname in dir_list:
        name = dirname[len(rs_path) + 1:]
        if len(name) > 0:
            name = name.replace('\\', '/')
            f.write('\t"%s",\n' % name )
    f.write("};\n")
    ## 生成目录的个数
    pathCount = 'static const int sn_pathCount = %d;'
    f.write(pathCount % (len(dir_list)-1))
    f.write("\n\n")

    res_format = 'static const char s%s_%s[]\t\t = "%s";\n'

    # 生成资源定义
    f.write("// files\n")
    for filename in file_list:
        # 去路径
        filename = os.path.basename(filename)
        name, ext = os.path.splitext(filename)
        # 去空格
        name = name.replace(' ', '')
        # ext = 'ccz'
        if '.ccz' == ext:
            n, e = os.path.splitext(name)
            name = n
            ext = e + ext
        # 前缀
        ext_pre = getPreByExt(ext)
        f.write(res_format % (ext_pre, name, filename))

    # 生成打包资源定义
    f.write("\n\n////// texture //////\n")
    for filename in texture_list:
        print(filename)
        name, ext = os.path.splitext(filename)
        root = ET.parse(filename).getroot()
        if root[0][0].text == "texture":
            f.write("\n// %s\n" % os.path.basename(filename))
            # images = root[0][3].find("key")
            for elem in root[0][3]:
                if elem.tag == "key":
                    image = elem.text
                    name, ext = os.path.splitext(image)
                    # 去空格
                    name = name.replace(' ', '')
                    name = name.replace('/', '__')
                    # 前缀
                    ext_pre = getPreByExt(ext)
                    f.write(res_format % (ext_pre, name, image))
        else:
            f.write("\n// %s\n" % os.path.basename(filename))
            # images = root[0][1].find("key")
            for elem in root[0][1]:
                if elem.tag == "key":
                    image = elem.text
                    name, ext = os.path.splitext(image)
                    # 去空格
                    name = name.replace(' ', '')
                    name = name.replace('/', '__')
                    # 前缀
                    ext_pre = getPreByExt(ext)
                    f.write(res_format % (ext_pre, name, image))

    # 生成 json key 定义
    f.write("\n// json key\n")    
    write_key_define = lambda key: f.write('static const char %s[]\t\t = "%s"; \n' %  (key, key))
    write_key_define(file_name_key)
    write_key_define(file_index_key)
    write_key_define(texture_name_key)
    write_key_define(texture_plist_key)
    write_key_define(texture_image_key)
                    
    
    f.write("\n#endif // _AUTO_RESOURCES_H_\n")

# 生成配置文件，字典
def generate_json():
    file_name = []
    file_index = []
    texture_name = []
    texture_plist = []
    texture_image = []

    for idx, filename in enumerate(file_list):
        file_index.append(str(idx + 1))
        file_name.append(os.path.basename(filename))

        name, ext = os.path.splitext(filename)
        if ext == ".plist":
            root = ET.parse(filename).getroot()
            if root[0][0].text == "texture":                
                for elem in root[0][3]:
                    if elem.tag == "key":
                        image = elem.text
                        texture_plist.append(str(idx + 1))
                        texture_name.append(image)
                        texture_image.append(str(idx + 2))
            else:
                for elem in root[0][1]:
                    if elem.tag == "key":
                        image = elem.text
                        texture_plist.append(str(idx + 1))
                        texture_name.append(image)
                        texture_image.append(str(idx + 2))
                            
    json_file = {
        file_name_key: file_name,
        file_index_key: file_index,
        texture_name_key: texture_name,        
        texture_plist_key: texture_plist,
        texture_image_key: texture_image
    }
    
    if os.path.isfile(js_file):
        os.remove(js_file)

    f = file(js_file, 'w')
    f.write(json.dumps(json_file, indent = 2))
    f.close()

if '__main__' == __name__:
    init()
    generate_h()
    generate_json()

    print("leaf ~")
    os.system("pause")

