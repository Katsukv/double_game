#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

#include "../hdr/Doodle.h"
#include "../hdr/Platform.h"
#include "../hdr/CustomButton.h"
#include "../hdr/Globals.h"

class MenuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MenuWidget(QWidget* parent = nullptr);
    void update(double deltaTime);
signals:
    void playButtonClicked();
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    void setupUI();

    CustomButton *playButton;
    QPushButton *settingsButton;
    QPushButton *exitButton;
    QLabel *titleLabel;
    QLabel *versionLabel;
    Doodle m_doodle = Doodle(90, 420, "..//sprites//Doodle Jump//blue-lik-right-odskok@2x.png",
            "..//sprites//Doodle Jump//blue-lik-left-odskok@2x.png");
    std::vector<Platform> m_platforms;
};

#endif // MENUWIDGET_H