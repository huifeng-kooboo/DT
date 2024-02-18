#include "dtimages.h"

bool DTImages::saveImageToFile(const QImage &qImage, const QString &qsFilePath,
                               E_IMAGE_TYPE image_type) {
  return qImage.save(qsFilePath);
}
