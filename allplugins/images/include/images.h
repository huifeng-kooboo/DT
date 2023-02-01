#ifndef Images_H
#define Images_H

#include "pluginsmanager_base.h"
#include "images_global.h"
#include "../../main/dtui/include/dtbutton.h"
#include "widgets/sidebar_widget.h"
#include "widgets/account_widget.h"

#define PLUGIN_Images_IID "Plugin.Images"
class Images_EXPORT Images : public DTPluginBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PLUGIN_Images_IID)
public:
    Images(QObject* qobj=nullptr);

    void loadUI() override;

public:
    void slotEventFromPlugins(const PluginMetaData& plt) override;
    QVariant slotHandleMessage(const PluginMetaData &plt) override;

private:
    QSharedPointer<DTButton> m_pTestBtn; // 测试按钮
    QSharedPointer<SideBarWidget> m_pSideBar; // 侧边栏
    QSharedPointer<AccountWidget> m_pAccountWidget; // 账户登录窗体
    QHBoxLayout * m_pHboxLayout;

    /**
      * 本地草稿、我的云空间、热门活动
      */
    QSharedPointer<DTButton> m_pLocalBtn; // 本地按钮
    QSharedPointer<DTButton> m_pCloudBtn; // 云空间
    QSharedPointer<DTButton> m_pHotBtn; // 热门活动
};

#endif // Images_H
