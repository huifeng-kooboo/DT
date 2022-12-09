# 打包安装脚本
import os
from time import time
from traceback import format_exception_only
import zipfile
import datetime
import yagmail
from upload import cos_upload_file

# 需要配置本地windeployqt.exe 以及生成文件路径
install_path = '''C:\\Qt\\Qt5.14.2\\5.14.2\\msvc2017_64\\bin\\windeployqt.exe ..\\bin\\dtdt.exe'''


def send_email(file_path, email_address,cc_email, str_content,str_title):
    # 需要自己配置user和password
    yag = yagmail.SMTP( user='xxxx@qq.com', password='xxxxxxx', host='smtp.partner.outlook.cn',port=587, smtp_starttls=True, smtp_ssl=False)
    if file_path != "":
        yag.send(to = email_address, cc=cc_email ,subject = str_title ,contents=str_content, attachments=file_path)
    else:
        yag.send(to = email_address, cc=cc_email ,subject = str_title ,contents=str_content)
    

def get_file_path(root_path, file_list, dir_list):
    # 获取该目录下所有的文件名称和目录名称
    dir_or_files = os.listdir(root_path)
    for dir_file in dir_or_files:
        # 获取目录或者文件的路径
        dir_file_path = os.path.join(root_path, dir_file)
        # 判断该路径为文件还是路径
        if os.path.isdir(dir_file_path):
            dir_list.append(dir_file_path)
            # 递归获取所有文件和目录的路径
            get_file_path(dir_file_path, file_list, dir_list)
        else:
            file_list.append(dir_file_path)


def delete_file(file_list):
    for file_name in file_list:
        if file_name.endswith(".ilk") or file_name.endswith(".exp") or file_name.endswith(".pdb") or file_name.endswith(".bmp") or file_name.endswith(".log") or file_name.endswith(".lib") or file_name.endswith(".txt"):
            print(file_name)
            os.remove(file_name)


def get_zip(dirpath, outFullName):
    """
    压缩指定文件夹
    :param dirpath: 目标文件夹路径
    :param outFullName: 压缩文件保存路径+xxxx.zip
    :return: 无
    """
    zip = zipfile.ZipFile(outFullName, "w", zipfile.ZIP_DEFLATED)
    for path, dirnames, filenames in os.walk(dirpath):
        # 去掉目标跟路径，只对目标文件夹下边的文件及文件夹进行压缩
        fpath = path.replace(dirpath, '')

        for filename in filenames:
            zip.write(os.path.join(path, filename),
                      os.path.join(fpath, filename))
    zip.close()


if __name__ == "__main__":
    # 1. Qt依赖环境放在里面
    os.system(install_path)
    # 2. 删除debug文件
    root_path = r"..\bin"
    file_list = []
    dir_list = []
    get_file_path(root_path, file_list, dir_list)
    delete_file(file_list)
    # 3.Log文件夹删除
    if os.path.exists("..\\bin\\Logs"):
        os.removedirs("..\\bin\\Logs")
    # 4.压缩文件夹
    if not os.path.exists("..\\package"):
        os.mkdir("..\\package")
    times= datetime.datetime.now().strftime('%Y-%m-%d-%H-%M-%S')
    get_zip("..\\bin",f"..\\package\\{times}.zip")
    print(f"《----当前安装包..\\package\\{times}.zip打包成功----》")
    email_ = ["xxx@qq.com"] # 需要发送的邮箱地址
    cc_email = ["xxxx@qq.com"] # 需要抄送的邮箱地址
    res_url  = cos_upload_file(f"..\\package\\{times}.zip")
    # 安装包下载链接:{res_url}
    send_email("",email_, cc_email, f"dtdt安装包 \n 打包时间:{times}\n 安装包下载链接: {res_url}","dtdt安装包")
    print(f"发送安装包到{email_}成功")