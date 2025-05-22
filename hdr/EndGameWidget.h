#ifndef ENDGAMEWIDGET_H
#define ENDGAMEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTime>
#include <QFontDatabase>
#include <QFile>
#include <QTextStream>

#include "../hdr/Doodle.h"
#include "../hdr/Platform.h"
#include "../hdr/CustomButton.h"
#include "../hdr/Globals.h"

class EndGameWidget : public QWidget
{
     Q_OBJECT
public:
    explicit EndGameWidget(float score, float hight_score, QWidget* parent = nullptr);
     void update(double deltaTime);
     signals:
         void playAgainButtonClicked();
         void menuButtonClicked();
protected:
    void paintEvent(QPaintEvent *event) override;
    void SaveResult();
private:
    QFont m_customFont;
    QLineEdit* nameInput;
    QString displayedName;
    void setupUI();

    CustomButton *playAgainButton;
    CustomButton *menuButton;
    CustomButton *saveResultButton;
    QPixmap *YouLose;

    int m_score;
    int m_hight_score;
};

#endif // ENDGAMEWIDGET_H