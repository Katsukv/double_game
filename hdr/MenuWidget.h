#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QFontDatabase>


#include "../hdr/Doodle.h"
#include "../hdr/Platform.h"
#include "../hdr/CustomButton.h"
#include "../hdr/Globals.h"

class HighScoresDialog : public QDialog {
    Q_OBJECT
public:
    explicit HighScoresDialog(QWidget* parent = nullptr);
    void loadScores();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QScrollArea* scrollArea;
    QWidget* scrollContent;
    QWidget* mainContainer;
    QVBoxLayout* mainLayout;
    QFont customFont;
};

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

private slots:
    void showHighScores();
private:
    void setupUI();
    CustomButton *playButton;
    QPushButton *settingsButton;
    QPushButton *exitButton;
    CustomButton* highScoresButton;
    QLabel *titleLabel;
    QLabel *versionLabel;
    Doodle m_doodle = Doodle(90, 400);
    std::vector<Platform> m_platforms;
};

#endif // MENUWIDGET_H