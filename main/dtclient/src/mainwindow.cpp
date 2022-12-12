#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../dtui/include/dtgraphicsview.h"
#include "../../common/include/dtlog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent, Qt::FramelessWindowHint), ui(new Ui::MainWindow) {
    // 设置背景颜色[可动态调整]
    this->setStyleSheet("QWidget { background-color: rgb(36, 33, 32); }");
    ui->setupUi(this);
    this->setMinimumSize(1100,700);
    init();
    qRegisterMetaType<PluginMetaData>("PluginMetaData");
}

MainWindow::~MainWindow() {

    // 卸载所有插件
    m_dtPluginsManager->freePlugins();
    delete ui;

    /**
      * @brief: exit current thread;
    */
#ifdef Q_OS_WIN
    std::string strExitCmd = "taskkill /f /PID "+ std::to_string(QApplication::applicationPid());
    system(strExitCmd.c_str());
#endif
}



void MainWindow::init() {

    /************* 设置图标 *******************/
    setWindowIcon(QIcon(":/resources/icon.png"));

    // 1.标题栏控件
    m_pTitleBar = new DTTitleBar(this);
    m_pTitleBar->setGeometry(0,0,this->geometry().width(),44); //设置大小
    m_pTitleBar->setCurrentWindowTitle(APP_NAME);  // 设置标题文字
    m_pTitleBar->setLogo(QIcon(":/resources/icon.png")); // 设置左上角Logo
    QIcon qHomePageIcon = QIcon(":/resources/homepage.png");
    m_pTitleBar->setHomePageIcon(qHomePageIcon,QIcon(":/resources/homepage_hover.png"),QIcon(":/resources/homepage_press.png"),QSize(17,17));
    QIcon qMinIcon = QIcon(":/resources/min.png");
    QIcon qMaxIcon = QIcon(":/resources/max.png");
    QIcon qCloseIcon = QIcon(":/resources/close.png");
    QIcon qMinHoverIcon = QIcon(":/resources/min_hover.png");
    QIcon qMaxHoverIcon = QIcon(":/resources/maxPress.png");
    QIcon qCloseHoverIcon = QIcon(":/resources/closePress.png");
    QIcon qMinPressIcon = QIcon(":/resources/min_press.png");
    QIcon qMaxPressIcon = QIcon(":/resources/max_press.png");
    QIcon qClosePressIcon = QIcon(":/resources/close_press.png");
    m_pTitleBar->setButtonsIcon(qMinIcon,qMaxIcon,qCloseIcon,qMinHoverIcon,qMaxHoverIcon,qCloseHoverIcon,
                                qMinPressIcon,qMaxPressIcon,qClosePressIcon);
    this->layout()->addWidget(m_pTitleBar);

    // 2. 加载插件
    loadPlugins();

    // 3. 显示界面
    this->showNormal();
}


void MainWindow::loadPlugins()
{
    Logger->logMsg(QtMsgType::QtInfoMsg,tr("加载所有插件开始"));
    m_dtPluginsManager = QSharedPointer<DT_PluginsManager>(new DT_PluginsManager(this), &QObject::deleteLater);
    m_dtPluginsManager->loadPlugins();
    m_dtPluginsManager->registerEventCallBacks();
    m_dtPluginsManager->initUI((QObject*)this);
    Logger->logMsg(QtMsgType::QtInfoMsg,tr("加载所有插件结束"));
}

void MainWindow::slotEventFromPluginsAsync(const PluginMetaData& plt)
{
    emit sendSignalToPluginsAsync(plt);
}

QVariant MainWindow::slotSendMessage(const PluginMetaData& plt)
{
    for(auto& plugin: m_dtPluginsManager->getLoadedObject())
    {
        if(plugin->property("dllType") == plt.enumMsg)
        {
            QVariant retVal;
            QMetaObject::invokeMethod(plugin, "slotHandleMessage", Qt::DirectConnection,
                                      Q_RETURN_ARG(QVariant, retVal),
                                      Q_ARG(const PluginMetaData&, plt));
            return retVal;
        }
    }
    return QVariant("");
}

void MainWindow::slotEventFromPlugins(const PluginMetaData& plt)
{
    switch (plt.enumUiMsg) {
    case MSG_UI_NONE:
        break;
    default:
         emit sendSignalToPlugins(plt);
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e){
    if(m_pTitleBar->geometry().contains(this->mapFromGlobal(QCursor::pos())))
    {
        int dx = e->globalX() - m_PointMouse.x();
        int dy = e->globalY() - m_PointMouse.y();
        m_PointMouse = e->globalPos();
        this->move(x()+dx, y()+dy);
    }
}
void MainWindow::mousePressEvent(QMouseEvent *event){
    if(m_pTitleBar->geometry().contains(this->mapFromGlobal(QCursor::pos())))
    {
        m_PointMouse =event->globalPos();
    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if(m_pTitleBar->geometry().contains(this->mapFromGlobal(QCursor::pos())))
    {
        int dx =  event ->globalX() -  m_PointMouse .x();
        int dy = event->globalY() -  m_PointMouse .y();
        this->move(x()+dx, y()+dy);
    }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(m_pTitleBar->geometry().contains(this->mapFromGlobal(QCursor::pos())))
    {
        slotMaxEvent();
    }
}

//
void MainWindow::slotMaxEvent()
{
    if(m_bShowMax == false)
    {
        m_nCurrentWidth = this->geometry().width();
        this->showMaximized();
        m_pTitleBar->setGeometry(0,0,qApp->primaryScreen()->size().width(),44); //设置大小
        m_pTitleBar->show();
        m_bShowMax = true;
    }
    else{
        this->showNormal();
        m_pTitleBar->setGeometry(0,0,m_nCurrentWidth,44); //设置大小
        m_pTitleBar->show();
        m_bShowMax = false;
    }
}

void MainWindow::slotMinEvent()
{
    this->showMinimized();
}

void MainWindow::slotCloseEvent()
{
    // 退出
    this->close();
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    m_pTitleBar->setGeometry(0,0,this->geometry().width(),44); //设置大小
    m_pTitleBar->show();
    QMainWindow::resizeEvent(event);
}

#ifdef Q_OS_WIN
#include <qt_windows.h>
#include <windowsx.h>
bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType);
    const int captionHeight = 0;
    const int frameWidth = 6;

    if (static_cast<MSG *>(message)->message != WM_NCHITTEST) return false;

    QPoint pos = mapFromGlobal(QCursor::pos());
    int w = width();
    int h = height();

    if (QRect(frameWidth, captionHeight, w-frameWidth-frameWidth, h-captionHeight-frameWidth).contains(pos))
    {
        *result = HTCLIENT;
    }
    else if (QRect(0, 0, w, captionHeight).contains(pos))
    {
        *result = HTCAPTION;
    }
    else if (QRect(0, captionHeight, frameWidth, h-captionHeight-frameWidth).contains(pos))
    {
        *result = HTLEFT;
    }
    else if (QRect(w-frameWidth, captionHeight, frameWidth, h-captionHeight-frameWidth).contains(pos))
    {
        *result = HTRIGHT;
    }
    else if  (QRect(frameWidth, h-frameWidth, w-frameWidth-frameWidth, frameWidth).contains(pos))
    {
        *result = HTBOTTOM;
    }
    else if (QRect(0, h-frameWidth, frameWidth, frameWidth).contains(pos))
    {
        *result = HTBOTTOMLEFT;
    }
    else if (QRect(w-frameWidth, h-frameWidth, frameWidth, frameWidth).contains(pos))
    {
        *result = HTBOTTOMRIGHT;
    }
    /******************** Top TopLeft Top Right**************************/
    if (QRect(frameWidth, frameWidth, w-frameWidth-frameWidth, frameWidth).contains(pos))
    {
        *result = HTTOP;
    }
    else if (QRect(0, frameWidth, frameWidth, frameWidth).contains(pos))
    {
        *result = HTTOPLEFT;
    }
    else if (QRect(w-frameWidth, frameWidth, frameWidth, frameWidth).contains(pos))
    {
        *result = HTTOPRIGHT;
    }
    return true;
}
#endif
