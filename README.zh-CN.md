# study-facsimile-backend
**CVL-Study学习平台，用c++完成的web后端**

[English](README.md)

# 依赖
- c++ 版本大于等于 c++17
- cmake 版本大于等于 3.20
- drogon: 使用到的web服务库
- vcpkg:  包管理器
    - mongo-c-driver  mongodb对c语言的支持
    - mongo-cxx-driver mongodb对c++的支持
    - sqlite3  一个轻数据库
    - loguru  日志库
    - [drogon] web服务库，如果没有直接安装，通过vcpkg也可以安装

# Directory
- controller: 存放控制器的目录
- filter: 存放过滤器的目录
- models: 连接数据库和交互数据使用到的结构体和类
    - model.json: drogon提供的配置文件，尚未使用
- services: 基本的底层服务器，例如CRUD
- CmakeLists.txt: c++ cmake工程的配置文件
- config.json: 网页服务器的配置，由drogon提供，尚未使用
- vcpkg.json: vcpkg包管理器依赖包裹清单
- main.cc: 程序主要入口