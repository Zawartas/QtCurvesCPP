#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    mBackgroundColor(QColor(0,0,255)),
    mPen(Qt::white),
    mShape(Astroid)
{
    mPen.setWidth(2);

    on_shape_changed();
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(400, 400);
}

QSize RenderArea::sizeHint() const
{
       return QSize(400, 400);
}

void RenderArea::on_shape_changed()
{
    switch (mShape)
    {
        case Astroid:
            mScale = 40;
            mIntervalLegth = static_cast<float>(2 * M_PI);
            mStepCount = 256;
            break;
        case Cycloid:
            mScale = 4;
            mIntervalLegth = static_cast<float>(6 * M_PI);
            mStepCount = 128;
            break;
        case HuygensCycloid:
            mScale = 4;
            mIntervalLegth = static_cast<float>(4 * M_PI);
            mStepCount = 256;
            break;
        case HypoCycloid:
            mScale = 15;
            mIntervalLegth = static_cast<float>(2 * M_PI);
            mStepCount = 256;
            break;
        case Line:
            mScale = 50;
            mIntervalLegth = 1;
            mStepCount = 128;
            break;
        case Circle:
            mScale = 100;
            mIntervalLegth = static_cast<float>(2 * M_PI);
            mStepCount = 128;
            break;
    }
}

int RenderArea::getStep() const
{
    return mStepCount;
}

void RenderArea::setStep(int stepCount)
{
    mStepCount = stepCount;
    repaint();
}

QPointF RenderArea::compute (float t)
{
    switch (mShape)
    {
        case Astroid:
            return compute_astroid(t);
        case Cycloid:
            return compute_cycloid(t);
        case HuygensCycloid:
            return compute_huygenscycloid(t);
        case HypoCycloid:
            return compute_hypocycloid(t);
        case Line:
            return compute_line(t);
        case Circle:
        return compute_circle(t);
        default:
            break;
    }
    return QPointF (0, 0);
}

QPointF RenderArea::compute_astroid(float t)
{
    float cos_t = static_cast<float>(cos (static_cast<double>(t)));
    float sin_t = static_cast<float>(sin (static_cast<double>(t)));
    float x = 2 * cos_t * cos_t * cos_t;
    float y = 2 * sin_t * sin_t * sin_t;
    return QPointF(static_cast<double>(x), static_cast<double>(y));
}

QPointF RenderArea::compute_cycloid(float t)
{
    return QPointF (
            1.5 * ( 1 - cos(static_cast<double>(t))), // x
            1.5 * ( static_cast<double>(t) - sin(static_cast<double>(t)))  // y
                );
}

QPointF RenderArea::compute_huygenscycloid(float t)
{
    return QPointF (
            4 * ( 3 * cos(static_cast<double>(t)) - cos (3 * static_cast<double>(t))), // x
            4 * (3 * sin (static_cast<double>(t)) - sin (3 * static_cast<double>(t)))  // y
                );
}

QPointF RenderArea::compute_hypocycloid(float t)
{
    return QPointF (
            1.5 * ( 2 * cos(static_cast<double>(t)) + cos (2 * static_cast<double>(t))), // x
            1.5 * ( 2 * sin(static_cast<double>(t)) - sin (2 * static_cast<double>(t)))  // y
                );
}

QPointF RenderArea::compute_line(float t)
{
    return QPointF (1 - t, 1 - t);
}

QPointF RenderArea::compute_circle(float t)
{
    return QPointF (
            cos(static_cast<double>(t)), // x
            sin(static_cast<double>(t))  // y
                );
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setBrush(mBackgroundColor);
    painter.setPen(mPen);

    //drawing area
    painter.drawRect(this->rect());

    QPoint center = this->rect().center();
    QPointF prevPoint = compute(0);
    QPoint prevPixel;

    prevPixel.setX(prevPoint.x() * mScale + center.x());
    prevPixel.setY(prevPoint.y() * mScale + center.y());

    float step = mIntervalLegth / mStepCount;

    for (float t = 0; t < mIntervalLegth; t += step)
    {
        QPointF point = compute(t);
        QPoint pixel;
        pixel.setX(point.x() * mScale + center.x());
        pixel.setY(point.y() * mScale + center.y());

        //painter.drawPoint(pixel);
        painter.drawLine(pixel, prevPixel);
        prevPixel = pixel;
    }


}

QColor RenderArea::getShapeColor() const
{
    return mPen.color();
}

void RenderArea::setShapeColor(const QColor &shapeColor)
{
    mPen.setColor(shapeColor);
}
