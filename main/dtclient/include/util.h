#ifndef UTIL_H
#define UTIL_H

class Util {
public:
    /**
     * @brief: 处理命令行
     */
    static void processCmd(int argc, char *argv[]);
    /**
     * @brief: 设置编码格式
     */
    static void setDefaultCodec(QString qsFormat="utf-8");
};

#endif // UTIL_H
