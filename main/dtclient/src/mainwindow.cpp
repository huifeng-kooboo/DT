#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../dtui/include/dtgraphicsview.h"
#include "../../common/include/dtlog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent, Qt::FramelessWindowHint), ui(new Ui::MainWindow) {
    this->setStyleSheet("QWidget { background-color: rgb(36, 33, 32); }");
    ui->setupUi(this);
    this->setMinimumSize(1100,700);
    init();
    qRegisterMetaType<PluginMetaData>("PluginMetaData");
}

MainWindow::~MainWindow() {

    // 卸载所有插件
    m_dtPluginsManager->freePlugins();
    m_dtPluginsManager = nullptr;
    delete m_dtPluginsManager;
    delete ui;

    /**
      * @brief: exit current thread;
    */
    std::string strExitCmd = "taskkill /f /PID "+ std::to_string(QApplication::applicationPid());
    system(strExitCmd.c_str());

}


void MainWindow::addWidgetToMainWindow(QWidget *pWidget)
{
    this->layout()->addWidget(pWidget);
}

void MainWindow::showStatusBarInfo(const QString &qsInfo)
{
    m_pStatusBarLabel->setText(qsInfo);
}


void MainWindow::init() {

    /************* 设置图标 *******************/
    setWindowIcon(QIcon(":/resources/icon.png"));

    // 1.标题栏设置
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

    // 2. 工具栏
    Logger->logMsg(QtMsgType::QtInfoMsg,QString(tr("工具栏初始化")));
    if(!m_bInitToolBar)
    {
        m_bInitToolBar = true;
        m_pToolBar = new DTToolBar(NULL);
        m_pToolBar->setObjectName("toolbar");
        m_pToolBar->setGeometry(0,0,this->width(),50); //设置大小
        m_pToolBar->setFixedHeight(50);
        m_pToolBar->setStyleSheet("background-color: rgb(57, 53, 51);");
    }

    Logger->logMsg(QtMsgType::QtInfoMsg,QString(tr("工具栏初始化结束")));
    // 3. 左侧ListWidget
    m_pFuncListWidget = new QListWidget(nullptr);
    m_pFuncListWidget->setObjectName("camera_func_listwidget");
    m_pFuncListWidget->setWindowFlag(Qt::FramelessWindowHint);
    m_pFuncListWidget->setAttribute(Qt::WA_StyledBackground, true);
    m_pFuncListWidget->setFixedWidth(180);
    //m_pCameraWidget->layout()->addWidget(m_pFuncListWidget);
    m_pFuncListWidget->setGeometry(0,50,180,this->height()-50);
    m_pFuncListWidget->setViewMode(QListView::ListMode);
    m_pFuncListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QString qsItemStyle = "QListWidget { border:0px; background-color: rgb(22, 20, 19);}  "
                          "QListWidget::item {margin:5px; padding-left:30px; color: rgba(255, 255, 255, 0.8); background-color: rgb(22, 20, 19); height: 40px; border-radius: 12px; }"
                          "QListWidget::item:hover { color: rgb(141, 153, 255); background-color: rgb(41, 36, 72); }"
                          "QListWidget::item:selected { color: rgb(141, 153, 255); background-color: rgb(41, 36, 72); }"
                          "QListWidget::item:pressed { color: rgb(141, 153, 255); background-color: rgb(41, 36, 72); }";
    m_pFuncListWidget->setStyleSheet(qsItemStyle);
    // 从上到下排列
    m_pFuncListWidget->setFlow(QListView::TopToBottom);
    addListItemToFuncListWidget("func_cameraconfig",tr("相机配置"),QIcon(":/resources/camera_config.png"));
    addListItemToFuncListWidget("func_tooltask",tr("工具任务"),QIcon(":/resources/tool_task.png"));
    addListItemToFuncListWidget("func_outset",tr("输出配置"),QIcon(":/resources/out_set.png"));
    addListItemToFuncListWidget("func_hmi",tr("人机交互"),QIcon(":/resources/hmi.png"));
    // 添加信号槽响应
    connect(m_pFuncListWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(slotFuncToolBtnSelected(QListWidgetItem*)));

    // 4. 右侧主窗体初始化
    Logger->logMsg(QtMsgType::QtInfoMsg,QString(tr("主窗体初始化")));
    m_pCurFuncWidget = new QWidget(nullptr);
    QVBoxLayout* pVLayout = new QVBoxLayout(this);
    pVLayout->setMargin(0);
    pVLayout->setSpacing(0);
    m_pCurFuncWidget->setObjectName("camera_main_func_widget");
    m_pCurFuncWidget->setWindowFlag(Qt::FramelessWindowHint);
    m_pCurFuncWidget->setAttribute(Qt::WA_StyledBackground, true);
    m_pCurFuncWidget->setStyleSheet("QWidget#camera_main_func_widget {background-color: rgb(32, 29, 29); }");

    // 5.加载所有插件
    Logger->logMsg(QtMsgType::QtInfoMsg,tr("加载所有插件开始"));
    m_dtPluginsManager = new DT_PluginsManager(this);
    m_dtPluginsManager->loadPlugins();
    m_dtPluginsManager->registerEventCallBacks();
    m_dtPluginsManager->initUI((QObject*)this);
    Logger->logMsg(QtMsgType::QtInfoMsg,tr("加载所有插件结束"));

    this->showNormal();

    //启动首页
    m_pTitleBar->homePageClick();
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

void MainWindow::slotPluginAddTitleBtn(QPushButton* plt)
{
    //
    m_pTitleBar->addToolButton(plt);
}

void MainWindow::slotPluginAddStatusBarControls(QWidget*pWidget,int strech)
{
    m_pStatusBar->addWidget(pWidget,strech);
}

void MainWindow::slotPluginShowStatusBarInfo(QString qsStatusBarInfo)
{
    showStatusBarInfo(qsStatusBarInfo);
}

void MainWindow::slotPluginAddToolBtn(QPushButton* plt, bool bNeedSplit ,Qt::Alignment align)
{
    if(m_bInitToolBar)
    {
        m_pToolBar->addTool(plt->text(),plt->icon(),plt,align);
        if(bNeedSplit)
        {
            m_pToolBar->addSplitLine();
        }
    }
}

void MainWindow::slotPluginAddTabWidget(QString qsName,QIcon qsIcon, QWidget* pTabWidget, bool bShowTabName)
{
    Q_UNUSED(qsName);
    Q_UNUSED(qsIcon);
    Q_UNUSED(pTabWidget);
    Q_UNUSED(bShowTabName);
    //todo
    if(!m_bInitTabWidget)
    {
        m_bInitTabWidget = true;
        // 初始化TabWidget
    }
    else{

    }
    return;
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


void MainWindow::slotSetMainWidget(QWidget* pWidget)
{
    setCurrentWidget(pWidget);
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
    if(m_bInitToolBar)
    {
        m_pToolBar->setGeometry(0,0,this->width(),50); //设置大小
        m_pToolBar->show();
    }
    if(m_pCurWidget)
    {
        m_pCurWidget->setGeometry(0,44,this->geometry().width(),this->geometry().height());
    }
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

void MainWindow::setCurrentWidget(QWidget *pWidget)
{
    if(!m_pCurWidget)
    {
        m_pCurWidget = pWidget;
        m_pCurWidget->setWindowFlag(Qt::FramelessWindowHint);
        this->layout()->addWidget(m_pCurWidget);
    }
    else{
        if(m_pCurWidget == pWidget)
        {
            return;
        }
        else{
            m_pCurWidget->setParent(NULL);
            this->layout()->removeWidget(m_pCurWidget);
            m_pCurWidget = pWidget;
            m_pCurWidget->setWindowFlag(Qt::FramelessWindowHint);
            this->layout()->addWidget(m_pCurWidget);
        }
    }

    if(m_pCurWidget)
    {
        m_pCurWidget->setGeometry(0,44,this->geometry().width(),this->geometry().height());
    }
}

QWidget* MainWindow::getCurrentWidget()
{
    return m_pCurWidget;
}

void MainWindow::slotPluginTitleBarAddTabBtn(DTButton* pBtn, bool bNeedClose)
{
    if(m_pTitleBar)
    {
        m_pTitleBar->addTabButton(pBtn,bNeedClose);
        pBtn->setIcon(QIcon(":/resources/camera.png"));
        connect(pBtn,SIGNAL(clicked()),this,SLOT(slotSetCameraWidget()));
    }
}

void MainWindow::addListItemToFuncListWidget(QString qsObjectName, QString qsText, QIcon qIcon)
{
    QListWidgetItem * pListWidgetItem = new QListWidgetItem();
    pListWidgetItem->setData(0,qsObjectName);
    pListWidgetItem->setText(qsText);
    pListWidgetItem->setIcon(qIcon);
    m_pFuncListWidget->addItem(pListWidgetItem);
}
