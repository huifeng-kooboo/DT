#ifndef DTGRAPHICSVIEW_H
#define DTGRAPHICSVIEW_H
/*
 * 重写QGraphicsView
 */
#include <QGraphicsView>



class DTGraphicsView : public QGraphicsView {
  Q_OBJECT
public:
  // 图形类型
  enum E_GRAPHICS_TYPE {
    TYPE_RECTANGLE,  // 矩形
    TYPE_ROTATE_RECTANGLE, // 旋转矩形
    TYPE_DISTANCE, // 距离描绘
    TYPE_CIRCLE,  // 绘制圆
    TYPE_RING, //圆环
    TYPE_SECTOR,  // 扇形
    TYPE_IRREGULAR, //不规则图形
  };
  //
  Q_ENUMS(E_GRAPHICS_TYPE)

  DTGraphicsView(QGraphicsScene* pScene,QWidget* pWidget = nullptr);

  DTGraphicsView(QWidget *parent = nullptr);

  /**
    * @brief: 加载画布
    *
   */
  bool loadCanvas(QPixmap& qPixmap);

  // 设置显示图像的类型
  void setGraphicType(E_GRAPHICS_TYPE graphic_type);
  bool getGraphicType(E_GRAPHICS_TYPE& graphic_type);

  /**
    * 设置当前的图片
  */
  void setCurrentImage(const QImage&image)
  {
      m_currentImage = image;
  }

  const QImage& getCurrentImage()
  {
      return  m_currentImage;
  }

  void setCanDrag(bool bCan)
  {
      m_bDrag = bCan;
  }

  bool getCanDrag()
  {
      return m_bDrag;
  }

  //Tool
  //放大
  void tool_ZoomIn();
  //缩小
  void tool_ZoomOut();
  //适应画布
  void tool_AdapterToCanvas();
  //旋转
  void tool_Rotate();


  /**
   * @brief 设置是否允许修改
  */
  void setModified(bool bModified)
  {
      m_bModified = bModified;
  }

  bool isModified()
  {
      return m_bModified;
  }

protected:
  // overide
  void paintEvent(QPaintEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void dropEvent(QDropEvent *event) override;
  void focusInEvent(QFocusEvent *event) override;
  void focusOutEvent(QFocusEvent *event) override;
  void showEvent(QShowEvent *event) override;

signals:
    void positionChanged(int x , int y );

    void signalCurrentPos(double x, double y);

private:
  E_GRAPHICS_TYPE m_eGraphicsType;  // 绘图类型
  bool  m_bSetGraphicsType = false; // 默认为False
  QImage m_currentImage; // 当前的图片
  QImage m_canvasImage; // 画布图片
  bool m_bDrag = false; // 设置是否可拖动
  bool m_bModified = false; //是否允许修改
  bool m_bInitCanvas = false; // 是否加载画布
};

#endif // DTGRAPHICSVIEW_H
