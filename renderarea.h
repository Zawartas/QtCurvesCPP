#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>
#include <QColor>
#include <QPen>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr);

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    enum ShapeType {Astroid, Cycloid, HuygensCycloid, HypoCycloid, Line, Circle};

    inline void setBackgroundColor (QColor color){mBackgroundColor = color;}
    QColor backgroundColor () const {return mBackgroundColor;}

    void setShape (ShapeType shape) {mShape = shape; on_shape_changed();}
    ShapeType getShape () const {return mShape;}

    void setScale (float scale) {mScale = scale; repaint();}
    float scale() {return mScale;}

    void setInterval (float interval) {mIntervalLegth = interval; repaint();}
    float interval(){return mIntervalLegth;}

    void setStep(int stepCount);
    int getStep() const;

    QColor getShapeColor() const;
    void setShapeColor(const QColor &shapeColor);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:

private:

    QColor mBackgroundColor;
    ShapeType mShape;
    QPen mPen;

    QPointF compute (float t);
    QPointF compute_astroid(float t);
    QPointF compute_cycloid(float t);
    QPointF compute_huygenscycloid(float t);
    QPointF compute_hypocycloid(float t);
    QPointF compute_line(float t);
    QPointF compute_circle(float t);

    void on_shape_changed();

    float mIntervalLegth;
    float mScale;
    int mStepCount;


};

#endif // RENDERAREA_H
