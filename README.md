# DT  
## 1. 为什么开源DT框架

* DT框架，本身就是基于QT为基础搭建的开发框架，其中用到了一些许多常用的设计模式，可以助于开发者快速开发客户端系统，参考了组件化的设计思想，所以尝试开源DT框架，之前在互联网上也接触很多的开源框架，所以打算回馈于开源，为开源软件业贡献自己的一份小小力量
* 就目前所有开源的客户端开发框架来看，个人认为DT框架最大的优势在于：
  1. 借助于QT丰富的API文档，可以极其方便用户进行掌握，使用该框架
  2. 组件化的设计思想，可以很方便的复用各类的组件，all function is a tool
  3. UI+业务的绑定，不需要用户去写完UI再去写业务，设计思想承接自Vue

​    当然，目前该框架肯定还存在很多的缺陷，因为目前主要是我一个人在开发和维护这套框架，也希望其他的对开源感兴趣的用户能一起贡献代码，提高DT框架的健壮性！

  `DT`是一套基于商业化标准的开源UI组件业务框架，不仅能提供完善的代码设计、详细的业务实现框架，框架的稳定性已在多个大型商化项目中通过验证，其中不仅限AI智能相机客户端项目

* DM库有在大型项目中使用，可以稳定放心，[AI智能相机](https://baijiahao.baidu.com/s?id=1750463100165117672&wfr=spider&for=pc), [演示视频](https://www.notion.so/Resume-0794b3ec26bb4f8181c0f96729f58b9f#ddb91895b2f44fd5a46aa868916dde08)

* DM库的代码统一规范，方便阅读

* DT库拥有拥有扩展性：基于基类，可以扩展各个插件通信

* DT框架完全开源
  
  

## 2. 开源协议

* 可以随意使用修改源码
* 您在使用过程中觉得好的话可以加个star！



## 3. 关于  
* 技术支持： 

    邮箱： gisdoing@gmail.com

    微信：ytouching

    QQ: 942840260

    

* DT框架的git路径：
    https://github.com/huifeng-kooboo/DT


​     

# 4. 帮助文档

### （1）开发环境安装

##### 依赖安装：

* [Qt 5.14.2](https://download.qt.io/archive/qt/5.14/5.14.2/)  ：只需要安装Qt5.14.2即可
* 需要配置VS2017的MSVC编译 参考[此处](https://blog.csdn.net/baiyi_2014/article/details/125424534) 进行配置环境 【假如有调用到Win相关的API的环境，需要下载】
* Qt Creator 配置： 工具->选项->文本编辑器->行为->UTF-8 BOM设置成“如果编码是UTF-8则添加”

##### 编译：

* Qt安装好后，启动QtCreator

  <img src="D:\Own\sensetime\sensetime\senseinsight-client\images\qt.png">


* 文件----打开文件或项目

  <img src="D:\Own\sensetime\sensetime\senseinsight-client\images\open.jpg">

* 依次打开main.pro以及plugins.pro  （选择 MSVC2017 64bit 编译： 因为需要调用到sdk的头文件和lib文件，所以用MSVC2017编译）

  <img src="D:\Own\sensetime\sensetime\senseinsight-client\images\plugins.jpg">

* 编译main.pro以及plugins.pro ,编译成功后，会在bin目录下生成相关的文件

  <img src="D:\Own\sensetime\sensetime\senseinsight-client\images\success.jpg">



* dtdt.exe为编译成功的文件



### （2）如何在DT框架下进行开发程序

* TODO



----

#### 打包部署【win】

* 打包需要本地先安装python3，进入```scripts```文件下

* 执行 ```pip install -r requirements.txt```  安装相关依赖

* 执行scripts的pack.py脚本 ```python3 pack.py```

* 脚本执行成功后，会在代码目录下package文件夹生成时间命名的压缩包，并且发送文件下载地址到对应的邮箱

  

----

#### 程序运行

* 正常启动

  直接双击```dtdt.exe```即可启动

* 调试模式

  命令行中执行```dtdt.exe -debug```，则使用调试模式启动窗体（带有输出窗口的形式启动软件）



# 5. Q&A

* TODO