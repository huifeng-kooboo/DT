# 所有的动态库都需要包含该.pri
DEFINES += DEBUG  # debug模式下开启(默认开启)

# 处理编译器无法识别M_PI的问题
DEFINES += _USE_MATH_DEFINES

# 设置Release版本可以调试
QMAKE_CXXFLAGS_RELEASE = -Od -ZI -MD
QMAKE_LFLAGS_RELEASE = /DEBUG /INCREMENTAL:NO
