# 创建插件的脚本
import os
import os.path



def create_plugin(plugin_name: str, save_folder: str, plugins_json: str = ""):
    """
    创建插件
    plugin_name: 插件名称
    save_folder: 保存插件路径
    plugins_json: 插件json文件的路径
    """
    if plugin_name == "":
        return False, "插件名称不允许为空"
    
    if not os.path.exists(save_folder):
        return False, "保存的插件路径不存在"

    # 需要执行的步骤
    '''
    1. 把文件名调整 plugins_name: xxxx
    2.
    '''
    file_list = os.listdir("../scripts/")
    print(f"{file_list}")
    for file_path in file_list:
        if os.path.isdir(file_path):
            print(file_path)
            os.rename(file_path,"test_demo")

create_plugin("sada","../scripts/")
