#### 说明

----

该文件夹主要存放插件的代码库，统一通过```plugins.pro```来管理所有的插件，是否加载插件，通过```plugins.json```来配置，配置中包含四个参数

```json
{
    "plugins":[{
            "plugins_name":"service.dll",  //插件名
            "plugins_version":"1.0", // 插件版本
            "plugins_desc":"test-desc", //插件描述
            "plugins_state":"0"  //插件状态 0:默认启动加载 1:动态加载
        }]
}
```

-----

所有插件均需要引入plugins_base的头文件，通过继承plugins_base的类，各自实现```loadUI```方法以及```slotEventFromPlugins```方法，其中```loadUI()```方法主要是用于绘制各自插件的ui界面，```slotEventFromPlugins```方法主要是用于处理插件接收主程序的消息，以及插件处理其他插件的透传消息等，实现插件之间的通信等。

##### 编译方式：

* 点击plugins.pro 即可进行编译，编译生成目录在```bin/plugins```目录下