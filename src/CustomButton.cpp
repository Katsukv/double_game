#include "../hdr/CustomButton.h"
#include <QPainter>

CustomButton::CustomButton(QWidget* parent) : QPushButton(parent)
{
    setFlat(true); // Убираем стандартные стили кнопки
    setCursor(Qt::PointingHandCursor);
}

void CustomButton::setImages(const QString& normal, const QString& pressed,
                           const QString& hover)
{
    m_normal.load(normal);
    // m_normal = m_normal.scaled(m_normal.width()/2, m_normal.height()/2,
    //                                  Qt::IgnoreAspectRatio,
    //                                  Qt::SmoothTransformation);
    m_pressed.load(pressed);
    if (!hover.isEmpty()) {
        m_hover.load(hover);
    }

    // Устанавливаем размер кнопки по размеру изображения
    if (!m_normal.isNull()) {
        setFixedSize(m_normal.size().width()/2, m_normal.size().height()/2);
    }
}

void CustomButton::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    if (m_isPressed && !m_pressed.isNull()) {
        painter.drawPixmap(rect(), m_pressed);
    }
    else if (m_isHovered && !m_hover.isNull()) {
        painter.drawPixmap(rect(), m_hover);
    }
    else if (!m_normal.isNull()) {
        painter.drawPixmap(rect(), m_normal);
    }
    else {
        QPushButton::paintEvent(event);
    }
}

void CustomButton::mousePressEvent(QMouseEvent* event)
{
    m_isPressed = true;
    update();
    QPushButton::mousePressEvent(event);
}

void CustomButton::mouseReleaseEvent(QMouseEvent* event)
{
    m_isPressed = false;
    update();
    QPushButton::mouseReleaseEvent(event);
}

void CustomButton::enterEvent(QEnterEvent* event)
{
    m_isHovered = true;
    update();
    QPushButton::enterEvent(event);
}

void CustomButton::leaveEvent(QEvent* event)
{
    m_isHovered = false;
    update();
    QPushButton::leaveEvent(event);
}