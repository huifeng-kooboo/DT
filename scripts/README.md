#### 说明

----

* 自动化部署脚本 ```pack.py```
* 执行的操作如下：
  1. 自动删除安装包多余文件
  2. 打包发送到云服务器中
  3. 抄送给对应的邮箱
* 运行方式：
  1. 添加Python3环境
  2. 运行```pip install virtualenv```
  3. 执行```virtualenv venv```
  4. 执行```source venv/bin/activate``` 进入到虚拟环境
  5. 执行```pip install -r requirements.txt```安装相关依赖
  6. 执行```python pack.py```自动编译打包