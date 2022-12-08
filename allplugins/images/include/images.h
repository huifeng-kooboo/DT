#ifndef Images_H
#define Images_H

#include "pluginsmanager_base.h"
#include "images_global.h"

#include <QListWidget>
#include <QImage>

#define PLUGIN_Images_IID "Plugin.Images"
class Images_EXPORT Images : public DTPluginBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PLUGIN_Images_IID)
public:
    Images(QObject* qobj=nullptr);

    void loadUI() override;


    /*
     * 测试UI功能
    */
    void testUiFunc();

public :

    /**
     * @brief:保存图片到列表中
     * @param: qIcon: 图片Icon
     * @param: objName: 属性名称
     * @return: null
    */
    void saveImageToWidgetList(const QIcon& qIcon,const QString&objName);

    /**
     * @brief:设置底部ImageList的IconSize大小
     * @param
    */
    void setImageWidgetIconSize(const int& width,const int& height);

public:
    void slotEventFromPlugins(PluginMetaData plt) override;
    QVariant slotHandleMessage(const PluginMetaData &plt) override;


private:
    QListWidget* m_pImageListWidget; //图片控件
    QVector<QImage> m_vecImages; //存放图片的列表
};

#endif // Images_H
