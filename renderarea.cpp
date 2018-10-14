#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    mBackgroundColor(QColor(0,0,255)),
    mShapeColor(QColor(255,255,255)),
    mShape(Astroid)
{
    on_shape_changed();
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize RenderArea::sizeHint() const
{
       return QSize(400, 200);
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
//        case FutureCurve:

//            break;
    }
}

QPointF RenderArea::compute (float t)
{
    switch (mShape)
    {
        case Astroid:
            compute_astroid(t);
            break;
        case Cycloid:
            compute_cycloid(t);
            break;
        case HuygensCycloid:
            compute_huygenscycloid(t);
            break;
        case HypoCycloid:
            compute_hypocycloid(t);
            break;
//        case FutureCurve:
//            compute_futurecurve(t);
//            break;
        default:
            break;
    }
    return QPointF (0, 0);
}

QPointF RenderArea::compute_astroid(float t)
{
    float cos_t = cos (t);
    float sin_t = sin (t);
    float x = 2 * cos_t * cos_t * cos_t;
    float y = 2 * sin_t * sin_t * sin_t;
    return QPointF(x, y);
}

QPointF RenderArea::compute_cycloid(float t)
{
    return QPointF (
            1.5 * ( 1 - cos(t)), // x
            1.5 * ( 1 - sin(t))  // y
                );
}

QPointF RenderArea::compute_huygenscycloid(float t)
{
    return QPointF (
            4 * ( 3 * cos(t) - cos (3 * t)), // x
            4 * (3 * sin (t) - sin (3 * t))  // y
                );
}

QPointF RenderArea::compute_hypocycloid(float t)
{
    return QPointF (
            1.5 * ( 2 * cos(t) + cos (2 * t)), // x
            1.5 * ( 2 * sin(t) - sin (2 * t))  // y
                );
}

QPointF RenderArea::compute_futurecurve(float t)
{

}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setBrush(mBackgroundColor);
    painter.setPen(mShapeColor);

    //drawing area
    painter.drawRect(this->rect());

    QPoint center = this->rect().center();

    float step = mIntervalLegth / mStepCount;

    for (float t = 0; t < mIntervalLegth; t += step)
    {
        QPointF point = compute (t);
        QPoint pixel;
        pixel.setX(point.x() * mScale + center.x());
        pixel.setY(point.y() * mScale + center.y());

        painter.drawPoint(pixel);
    }


}
