#ifndef IMAGES_H
#define IMAGES_H
#include <QImage>

enum E_IMAGE_TYPE {
  IMAGE_BMP,
  IMAGE_JPG
};

/*
 * @brief: 图片相关的处理
*/
class DTImages{
    /*
     * 保存图片到文件接口
    */
    static bool saveImageToFile(const QImage& qImage,const QString&qsFilePath,E_IMAGE_TYPE image_type);
};

#endif // IMAGES_H
