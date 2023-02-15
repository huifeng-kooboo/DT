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

  /**
   * @brief: 同步的槽函数返回
   * 直接获取返回结果
   */
  QVariant slotSendMessage(const PluginMetaData&);

  // 与其他插件通信的槽
  void slotEventFromPlugins(const PluginMetaData& plt);
  void slotEventFromPluginsAsync(const PluginMetaData&);

  // 加载对应的样式表
  void loadStyleSheet(const QString& qsStyleFile);

  // 放大 缩小 关闭事件
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
  /********* 重绘界面框，可以实现拖动 *********/
  bool nativeEvent(const QByteArray &eventType, void *message,
                   long *result) override;
#endif


private:
  Ui::MainWindow *ui;

  QSharedPointer<QWidget> m_pMainWidget;  // 主窗体
  QSharedPointer<DT_PluginsManager> m_dtPluginsManager;  // 插件管理
  QSharedPointer<DTTitleBar> m_pTitleBar;       // 标题栏控件
  QSharedPointer<QVBoxLayout> m_pMainLayout;  // 总体布局

  // 程序拖动时候需要使用的变量
  QPoint m_PointMouse;
  int m_nCurrentWidth = 0;
  bool m_bShowMax = false;
};
#endif // MAINWINDOW_H
