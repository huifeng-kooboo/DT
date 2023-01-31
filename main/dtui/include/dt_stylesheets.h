#ifndef DT_STYLESHEETS_H
#define DT_STYLESHEETS_H

// 默认基础控件样式表
// title-bar 基础样式
#define TITLE_BAR_STYLE "QWidget { background-color: rgba(0, 0, 0, 1); color: #EAEAEA; font: 18px; }"
#define TITLE_BAR_BUTTON_STYLE "QPushButton { font: 14px; border-radius: 0px; background-color:rgba(0, 0, 0, 1); color: #EAEAEA;}  QPushButton:hover {font: 14px; background-color:rgba(54, 52, 51, 1); color: #EAEAEA;} QPushButton:pressed {font: 14px; background-color:rgba(54, 52, 51, 1); color: #EAEAEA;}  QPushButton:checked {font: 14px; background-color:rgba(54, 52, 51, 1); color: #EAEAEA;}"

// 工具按钮样式 (标题栏下方)
#define TOOL_BUTTON_STYLE  "QPushButton {background-color: rgb(57, 53, 51);} QPushButton:hover { background-color: #292448;} QPushButton:pressed { background-color: #292448; } QPushButton:checked { background-color: #292448; }"

// 正常按钮样式
#define NORMAL_BUTTON_STYLE  "QPushButton { font: 14px;font-family:'Microsoft YaHei'; border-radius: 10px; background-color:rgba(115, 129, 255, 1); color: #EAEAEA;}  QPushButton:hover {font: 14px; background-color:rgba(141, 153, 255, 1); color: #EAEAEA;} QPushButton:pressed {font: 14px; background-color:rgba(79, 92, 203, 1); color: #EAEAEA;} QPushButton:checked {font: 14px; background-color:rgba(79, 92, 203, 1); color: #EAEAEA;}"

// 小一号字体按钮样式
#define SMALL_BUTTON_STYLE  "QPushButton { font: 12px; padding:5px; border-radius: 5px; background-color:rgba(115, 129, 255, 1); color: #EAEAEA;}  QPushButton:hover {font: 12px; background-color:rgba(141, 153, 255, 1); color: #EAEAEA;} QPushButton:pressed {font: 12px; background-color:rgba(79, 92, 203, 1); color: #EAEAEA;} QPushButton:checked {font: 12px; background-color:rgba(79, 92, 203, 1); color: #EAEAEA;}"

//todo: checkbox基础样式
#define CHECK_BOX_STYLE "111"

#endif // DT_STYLESHEETS_H
