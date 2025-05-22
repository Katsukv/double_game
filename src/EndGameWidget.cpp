//
// Created by katsu on 22.05.2025.
//

#include "../hdr/EndGameWidget.h"
#include "../hdr/Globals.h"

EndGameWidget::EndGameWidget(float score, float hight_score, QWidget* parent) :
    QWidget(parent), m_score(score), m_hight_score(hight_score) {

    int fontId = QFontDatabase::addApplicationFont("../sprites/Doodle Jump/options/DoodleJump.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    m_customFont = QFont(fontFamily, 22);
    m_customFont.setBold(true);

    playAgainButton = new CustomButton(this);
    playAgainButton->setImages(
        "../sprites/Doodle Jump/options/play-again.png",
        "../sprites/Doodle Jump/options/play-again-on.png",
        "../sprites/Doodle Jump/options/play-again-on.png"
    );
    playAgainButton->move(25, SCREEN_SIZE_Y - 130);
    connect(playAgainButton, &QPushButton::clicked, this, [this]() {
        SaveResult();
        emit playAgainButtonClicked();
    });


    menuButton = new CustomButton(this);
    menuButton->setImages(
        "../usefullSprites/menu@2x.png",
        "../usefullSprites/menu-on@2x.png",
        "../usefullSprites/menu-on@2x.png"
    );
    menuButton->move(SCREEN_SIZE_X - menuButton->width()-25, SCREEN_SIZE_Y - 130);
    connect(menuButton, &QPushButton::clicked, this, [this]() {
        SaveResult();
        emit menuButtonClicked();
    });

    YouLose = new QPixmap("../sprites/Doodle Jump/options/you-lose.png");
    *YouLose = (YouLose->scaled(250, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    nameInput = new QLineEdit(this);
    nameInput->setFont(m_customFont);
    nameInput->setStyleSheet(
        "QLineEdit {"
        "   background: transparent;"
        "   border: 0px;"
        "   color: black;"
        "}"
        "QLineEdit:focus {"
        "   border: 0px;"
        "}"
    );
    nameInput->setGeometry(SCREEN_SIZE_X/2 - 20, 250, 200, 50);
    nameInput->setMaxLength(15);

    connect(nameInput, &QLineEdit::textChanged, this, [this](const QString& text) {
       displayedName = text;
   });
}

void EndGameWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPixmap background;
    background.load(QString::fromStdString(path_to_background));
    painter.drawPixmap(0, 0, width(), height(), background);

    painter.drawPixmap((SCREEN_SIZE_X - YouLose->width()) / 2, 10, *YouLose);

    painter.setPen(Qt::black);
    painter.setFont(m_customFont);
    painter.drawText(0,150, SCREEN_SIZE_X, 50, Qt::AlignCenter,
                    QString("your score: %1").arg(m_score));
    painter.drawText(0,200, SCREEN_SIZE_X, 50, Qt::AlignCenter,
                    QString("your hight score: %1").arg(m_hight_score));

    painter.drawText(SCREEN_SIZE_X/2 - 150, 250, 200, 50,
                    Qt::AlignLeft | Qt::AlignVCenter, "your name:");
}

void EndGameWidget::update(double deltaTime) {}

void EndGameWidget::SaveResult() {
    if (displayedName == "") return;

    QDateTime currentTime = QDateTime::currentDateTime();
    QString timeString = currentTime.toString("yyyy-MM-dd HH:mm");

    QFile file("scores.csv");

    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);
        QString csvLine = QString("\"%1\",%2,\"%3\"\n")
                            .arg(displayedName)
                            .arg(m_score)
                            .arg(timeString);

        stream << csvLine;
        file.close();

        qDebug() << "Result save:\n";
    }
    else {
        qWarning() << "not such file";
    }
}