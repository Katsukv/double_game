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

class OptionsDialog : public QDialog {
    Q_OBJECT
public:
    explicit OptionsDialog(QWidget* parent = nullptr) : QDialog(parent) {
        setWindowTitle("Choose Theme");
        setFixedSize(200, 150);

        QVBoxLayout* layout = new QVBoxLayout(this);

        QPushButton* defaultButton = new QPushButton("Default", this);
        QPushButton* spaceButton = new QPushButton("Space", this);
        QPushButton* halloweenButton = new QPushButton("Halloween", this);

        layout->addWidget(defaultButton);
        layout->addWidget(spaceButton);
        layout->addWidget(halloweenButton);

        connect(defaultButton, &QPushButton::clicked, this, &OptionsDialog::setDefaultTheme);
        connect(spaceButton, &QPushButton::clicked, this, &OptionsDialog::setSpaceTheme);
        connect(halloweenButton, &QPushButton::clicked, this, &OptionsDialog::setHalloweenTheme);
    }

    signals:
        void setDefaultTheme();
    void setSpaceTheme();
    void setHalloweenTheme();
};

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
    void showOptions();
private:
    void setupUI();
    CustomButton *playButton;
    CustomButton *optionsButton;
    QPushButton *exitButton;
    CustomButton* highScoresButton;
    QLabel *titleLabel;
    QLabel *versionLabel;
    Doodle m_doodle = Doodle(90, 400);
    std::vector<Platform> m_platforms;
};

void SetOptionToDefolt();
void SetOptionToSpace();
void SetOptionToHalloween();

#endif // MENUWIDGET_H