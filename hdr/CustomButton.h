#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>
#include <QPixmap>

class CustomButton : public QPushButton
{
     Q_OBJECT
public:
    explicit CustomButton(QWidget* parent = nullptr);

    void setImages(const QString& normal, const QString& pressed,
                  const QString& hover = "");

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;

private:
    QPixmap m_normal;
    QPixmap m_pressed;
    QPixmap m_hover;
    bool m_isPressed = false;
    bool m_isHovered = false;
};

#endif // CUSTOMBUTTON_H