#ifndef Images_H
#define Images_H

#include "pluginsmanager_base.h"
#include "images_global.h"



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
    QSharedPointer<QPushButton> m_pTestBtn; // 测试按钮
};

#endif // Images_H
