#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../../dtui/include/dttabwidget.h"
#include "../../dtui/include/dttitlebar.h"
#include "../../dtui/include/dttoolbar.h"
#include "globaldefine.h"
#include "pluginsmanager.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  // 初始化
  void init();
  void addWidgetToMainWindow(QWidget *);
  void showStatusBarInfo(const QString &qsInfo);


  /**
   * @brief: 设置当前的Widget
   */
  void setCurrentWidget(QWidget* pWidget);
  QWidget* getCurrentWidget();

signals:
  // 发送信号给对应的插件
  void sendSignalToPlugins(PluginMetaData);

  /**
   * @brief: 异步调用
   */
  void sendSignalToPluginsAsync(PluginMetaData);


public slots:

  /**
   * @brief: 同步的槽函数返回
   * 直接获取返回结果
   */
  QVariant slotSendMessage(const PluginMetaData&);

  // 与其他插件通信的槽
  void slotEventFromPlugins(const PluginMetaData& plt);

  void slotEventFromPluginsAsync(const PluginMetaData&);

  /**
    * @brief: 标题栏增加按钮 (1.0版本暂时没有该需求预留)
  */
  void slotPluginAddTitleBtn(QPushButton *pBtn);

  /**
   * @brief: tab页窗体添加控件
  */
  void slotPluginAddTabWidget(QString qsName, QIcon qsIcon, QWidget *pTabWidget,
                              bool bShowTabName);

  /**
    * @brief: Tab标题栏添加新相机
    * @param: pBtn: 按钮
    * @param: bNeedClose: 是否需要有关闭按钮
   */
  void slotPluginTitleBarAddTabBtn(DTButton* pBtn, bool bNeedClose);

  /**
   * @brief: 工具栏增加工具
   */
  void slotPluginAddToolBtn(QPushButton *pBtn, bool bNeedSplit,
                           Qt::Alignment align); //工具栏增加工具接口

  /**
   * @brief: 底部状态栏信息添加控件
   */
  void slotPluginAddStatusBarControls(QWidget *pWidget,
                                      int strech); // 底部状态栏增加控件接口

  /**
   * @brief: 底部状态栏信息展示
   * @param qsTabInfo: 需要展示的信息text
   */
  void slotPluginShowStatusBarInfo(QString qsTabInfo);

  // 主程序用到的槽
  void slotCloseEvent();
  void slotMinEvent();
  void slotMaxEvent();

  // 设置主界面Widget窗体
  void slotSetMainWidget(QWidget* pWidget);

  // override
  void mouseMoveEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mouseDoubleClickEvent(QMouseEvent *event) override;
  void resizeEvent(QResizeEvent *event) override;


#ifdef Q_OS_WIN
protected:
  /********* 重绘界面框，可以拖动 *********/
  bool nativeEvent(const QByteArray &eventType, void *message,
                   long *result) override;
#endif

private:
  void addListItemToFuncListWidget(QString qsObjectName, QString qsText, QIcon qIcon);

private:

  QPoint m_PointMouse;
  bool m_bShowMax = false;
  bool m_bInitToolBar = false;  // 初始化工具栏
  bool m_bInitTabWidget = false;

private:
  Ui::MainWindow *ui;
  DT_PluginsManager *m_dtPluginsManager;  // 插件管理


  QWidget * m_pCurWidget = nullptr;      // 当前Widget
  QWidget * m_pCurFuncWidget = nullptr;   // 功能窗体
  QListWidget * m_pFuncListWidget = nullptr; // 左侧功能列表菜单栏
  DTTitleBar *m_pTitleBar;       // 标题控件
  DTToolBar *m_pToolBar;         // 工具栏控件

  // 底部状态栏
  QStatusBar *m_pStatusBar;
  QLabel *m_pStatusBarLabel;

  int m_nCurrentWidth = 0;
};
#endif // MAINWINDOW_H
