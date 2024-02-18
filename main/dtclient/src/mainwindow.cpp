#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../dtui/include/dtgraphicsview.h"
#include "../../dtui/include/dtgroupbox.h"
#include "../../common/include/dtlog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent, Qt::FramelessWindowHint), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    init();
    registerMetaTypes();
}

MainWindow::~MainWindow() {
    // 卸载所有插件
    m_dtPluginsManager->freePlugins();
    delete ui;
    // todo: 防止内存泄露，之后修复
#ifdef Q_OS_WIN
    std::string strExitCmd = "taskkill /f /PID "+ std::to_string(QApplication::applicationPid());
    system(strExitCmd.c_str());
#endif
}



void MainWindow::init() {

    /**************************************/
    m_pMainWidget = QSharedPointer<QWidget>(new QWidget(this), &QObject::deleteLater);
    setCentralWidget(m_pMainWidget.data());

    /************* 设置图标 *******************/
    setWindowIcon(QIcon(":/resources/icon.png"));

    // 1.标题栏控件
    m_pTitleBar =  QSharedPointer<DTTitleBar>(new DTTitleBar(this), &QObject::deleteLater);
    m_pTitleBar->setObjectName("window_title_bar");
    m_pTitleBar->setGeometry(0,0,this->geometry().width(),m_nDefaultTitleBarHeight); //设置大小
    m_pTitleBar->setTitle("数学研究院系统");
    m_pTitleBar->setRegion("华东地区");

    // 添加文本按钮
    for (int i = 0; i < 6; i++)
    {
        QLabel* label = new QLabel();
        label->setObjectName("title_info");
        label->setFixedSize(160,30);
        label->setText(QString("文本%1").arg(i));
        if(i % 2 ==0)
        {
            m_pTitleBar->addTextLabel(label,1);
        }
        else{
            m_pTitleBar->addTextLabel(label,0);
        }
    }


    m_pMainLayout = QSharedPointer<QVBoxLayout>(new QVBoxLayout(this), &QObject::deleteLater);
    m_pMainLayout->setSpacing(0);
    m_pMainLayout->setMargin(0);
    m_pMainWidget->setLayout(m_pMainLayout.data());

    // Tab工具栏
    m_pTabWidget = new DTTabWidget(this);
    m_pTabWidget->setObjectName("window_tab_widget");
    m_pMainLayout->addStretch();
    m_pMainLayout->addWidget(m_pTabWidget); // 放置最下层
    QIcon myIcon(":/resources/icon.png");
    for(int i =0; i < 6; i++)
    {
        m_pTabWidget->addTabByName(QString("功能按钮%1").arg(i+1),myIcon,QString("test").arg(i+1));
    }

    auto vecButtons = m_pTabWidget->getToolButtonVec();
    for (auto btn: vecButtons)
    {
        connect(btn,SIGNAL(clicked()),this,SLOT(showGroupBox()));
    }
    // 2. 加载插件
    loadPlugins();

    // 3.UI样式设置
    loadStyle();

    // 4. 显示界面
    this->showNormal();

}

void MainWindow::loadStyle()
{
    this->loadStyleSheet(":/resources/css/common.css");
}

// 需要设置该类型，使得能被其他的插件正确引用
void MainWindow::registerMetaTypes()
{
    qRegisterMetaType<PluginMetaData>("PluginMetaData");
}


void MainWindow::loadPlugins()
{
    Logger->logMsg(QtMsgType::QtInfoMsg,tr("加载所有插件开始"));
    m_dtPluginsManager = QSharedPointer<DT_PluginsManager>(new DT_PluginsManager(this), &QObject::deleteLater);
    m_dtPluginsManager->loadPlugins();
    m_dtPluginsManager->registerEventCallBacks();
    m_dtPluginsManager->loadPluginUi(m_pMainWidget.data());
    Logger->logMsg(QtMsgType::QtInfoMsg,tr("加载所有插件结束"));
}

void MainWindow::slotEventFromPluginsAsync(const PluginMetaData& plt)
{
    switch (plt.enumUiMsg) {
    case E_UI_MSG_TYPE::MSG_UI_MAIN_CLOSE:
    {
        Logger->logMsg(QtMsgType::QtSystemMsg,"Close Window");
        this->close();
    }
        break;
    case E_UI_MSG_TYPE::MSG_UI_IMAGE_HOT_PINK:
    {
        QMessageBox::information(NULL,"HotPink","HotPink");
    }
        break;
    default:
        break;
    }
    emit sendSignalToPluginsAsync(plt);
}

void MainWindow::loadStyleSheet(const QString& qsStyleFile)
{
    if (!QFile::exists(qsStyleFile))
        return ;
    QFile qss(qsStyleFile);
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qApp->styleSheet() + qss.readAll());
    qss.close();
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
    case MSG_UI_MAIN_CLOSE:
        this->close();
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
        m_nDesktopWidth = this->geometry().width();
        this->showMaximized();
        m_pTitleBar->setGeometry(0,0,this->geometry().width(),m_nDefaultTitleBarHeight); //设置大小
        m_pTitleBar->show();
        this->setGeometry(this->x(),this->y(),this->geometry().width(),this->geometry().height());
        m_bShowMax = true;
    }
    else{
        m_pTitleBar->setGeometry(0,0,m_nDesktopWidth,m_nDefaultTitleBarHeight); //设置大小
        m_pTitleBar->show();
        this->showNormal();
        this->setGeometry(this->x(),this->y(),m_nDesktopWidth,this->geometry().height());
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
    m_pTitleBar->setGeometry(0,0,this->geometry().width(),m_nDefaultTitleBarHeight); //设置大小
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

void MainWindow::showGroupBox()
{
    if(m_pTestBox == nullptr)
    {
        m_pTestBox = new DTGroupBox();
    }
    QString title = "采购合同";
    m_pTestBox->setTitle(title);
    m_pTestBox->setGeometry(70,300,390,364);
    //
    QWidget* pWidget = new QWidget();
    QVBoxLayout* pLayout = new QVBoxLayout();
    pWidget->setLayout(pLayout);
    QHBoxLayout* pHLayout = new QHBoxLayout();
    pLayout->addLayout(pHLayout);
    pLayout->addStretch();
    for (auto i = 0; i <3; i++)
    {
        DTButton * dtButton = new DTButton();
        dtButton->setText(QString("text_ok_%1").arg(i));
        dtButton->setObjectName("dt_info");
        pHLayout->addWidget(dtButton);
    }
    //
    m_pTestBox->setContentWidget(pWidget);
    m_pTestBox->show();
    // QMessageBox::warning(NULL,"ShowNone","Show Text");
}
