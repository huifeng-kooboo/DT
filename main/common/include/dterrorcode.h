#ifndef DTERRORCODE_H
#define DTERRORCODE_H

// 错误码模块

enum DTErrorCode{
    SUCCESS = 0, //成功
    ERR_NETWORK , // 网络错误
    ERR_SERVER,  // 服务端错误
    ERR_CLIENT,  // 客户端错误
    ERR_OTHERS ,// 其他错误

    //  业务相关的错误码定义
    ERR_LOGIN_PASSWORD = 100, // 登录相关的错误码
    ERR_REGISTER_PASSWORD = 101, //注册错误

};

#endif // DTERRORCODE_H
