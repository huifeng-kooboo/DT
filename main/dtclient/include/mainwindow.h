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

private:

  /**
    * @brief: 程序初始化
    */
  void init();

  // 注册自定义的数据类型
  void registerMetaTypes();

  /**
    * @brief: 插件加载
    * 1. 加载All Plugins
    * 2. RegisterSignal
    * 3. Invoke LoadUi
   */
  void loadPlugins();


signals:

  /**
    * @brief: 同步调用
    */
  void sendSignalToPlugins(PluginMetaData);

  /**
   * @brief: 异步调用
   */
  void sendSignalToPluginsAsync(PluginMetaData);


public slots:

  // 插件通信部分
  QVariant slotSendMessage(const PluginMetaData&);
  void slotEventFromPlugins(const PluginMetaData& plt);
  void slotEventFromPluginsAsync(const PluginMetaData&);

  // 加载对应的样式表
  void loadStyleSheet(const QString& qsStyleFile);

  // 最大化、最小化、关闭事件
  void slotCloseEvent();
  void slotMinEvent();
  void slotMaxEvent();

  // override
  void mouseMoveEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mouseDoubleClickEvent(QMouseEvent *event) override;
  void resizeEvent(QResizeEvent *event) override;


#ifdef Q_OS_WIN
protected:
  /********* 重绘界面框，可以实现拖动【基于Windows平台适配】 *********/
  bool nativeEvent(const QByteArray &eventType, void *message,
                   long *result) override;
#endif


private:
  Ui::MainWindow *ui;

  // 插件管理
  QSharedPointer<DT_PluginsManager> m_dtPluginsManager;  // 插件管理

  // 界面相关
  QSharedPointer<QWidget> m_pMainWidget;  // 主窗体
  QSharedPointer<DTTitleBar> m_pTitleBar;       // 标题栏控件
  QSharedPointer<QVBoxLayout> m_pMainLayout;  // 总体布局

  // FrameLess Window Need
  QPoint m_PointMouse;
  int m_nDesktopWidth = 0;  // The Default Normal Width
  bool m_bShowMax = false;  // The State Show whether is Max State
};
#endif // MAINWINDOW_H
