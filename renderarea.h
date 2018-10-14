#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>
#include <QColor>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr);

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    enum ShapeType {Astroid, Cycloid, HuygensCycloid, HypoCycloid/*, FutureCurve*/};

    inline void setBackgroundColor (QColor color){mBackgroundColor = color;}
    QColor backgroundColor () const {return mBackgroundColor;}

    void setShape (ShapeType shape) {mShape = shape; on_shape_changed();}
    ShapeType getShape () const {return mShape;}

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:

private:

    QColor mBackgroundColor;
    QColor mShapeColor;
    ShapeType mShape;

    QPointF compute_astroid(float t);
    QPointF compute_cycloid(float t);
    QPointF compute_huygenscycloid(float t);
    QPointF compute_hypocycloid(float t);
    QPointF compute_futurecurve(float t);

    void on_shape_changed();
    QPointF compute (float t);

    float mIntervalLegth;
    float mScale;
    int mStepCount;


};

#endif // RENDERAREA_H
