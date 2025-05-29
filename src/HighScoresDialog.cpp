//
// Created by katsu on 22.05.2025.
//

#include "../hdr/MenuWidget.h"

HighScoresDialog::HighScoresDialog(QWidget* parent) : QDialog(parent) {
    setModal(true);
    setFixedSize(320, 320);

    int fontId = QFontDatabase::addApplicationFont("../sprites/Doodle Jump/options/DoodleJump.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    customFont = QFont(fontFamily, 16);
    customFont.setBold(true);

    mainContainer = new QWidget(this);
    mainContainer->setGeometry(0, 0, width(), height());

    scrollArea = new QScrollArea(mainContainer);
    scrollArea->setGeometry(45, 110, 320-45, 320-110);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("background: transparent; border: none;");

    scrollContent = new QWidget();
    scrollArea->setWidget(scrollContent);

    mainLayout = new QVBoxLayout(scrollContent);
    mainLayout->setAlignment(Qt::AlignTop);
}

void HighScoresDialog::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    QPixmap bg(QString::fromStdString(path_to_background));
    painter.drawPixmap(0, 0, width(), height(), bg);

    QPixmap Name("../sprites/Doodle Jump/options/high-scores-top.png");
    painter.drawPixmap(0, 0, Name);

}

void HighScoresDialog::loadScores() {
    QVector<QStringList> scores;

    QFile file("scores.csv");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if (parts.size() >= 3) {
                scores.append({
                    parts[0].replace("\"", ""),
                    parts[1],
                    parts[2].replace("\"", "")
                });
            }
        }
        file.close();
    }

    std::sort(scores.begin(), scores.end(), [](const QStringList& a, const QStringList& b) {
        return a[1].toInt() > b[1].toInt();
    });

    const int maxScores = 15;
    if (scores.size() > maxScores) {
        scores.resize(maxScores);
    }

    for (int i = 0; i < scores.size(); ++i) {
        const auto& score = scores[i];

        QWidget* entry = new QWidget(scrollContent);
        entry->setFixedHeight(70);

        QVBoxLayout* vLayout = new QVBoxLayout(entry);
        vLayout->setContentsMargins(15, 5, 15, 5);
        vLayout->setSpacing(0);

        QWidget* topRow = new QWidget();
        QHBoxLayout* hLayout = new QHBoxLayout(topRow);
        hLayout->setContentsMargins(0, 0, 0, 0);

        QLabel* place = new QLabel(QString("%1.").arg(i+1), topRow);
        place->setFont(customFont);
        place->setStyleSheet("color: red");

        QLabel* name = new QLabel(score[0], topRow);
        name->setFont(customFont);
        name->setStyleSheet("color: black;");

        QLabel* points = new QLabel(score[1], topRow);
        points->setFont(customFont);
        points->setStyleSheet("color: black;");

        hLayout->addWidget(place);
        hLayout->addWidget(name);
        hLayout->addWidget(points);

        QLabel* timeLabel = new QLabel(score[2], entry);
        customFont.setPointSize(14);
        timeLabel->setFont(customFont);
        timeLabel->setStyleSheet("color: black;");
        customFont.setPointSize(20);

        vLayout->addWidget(topRow);
        vLayout->addWidget(timeLabel);
        mainLayout->addWidget(entry);
    }

    if (scores.isEmpty()) {
        QLabel* noScores = new QLabel("No scores yet!", scrollContent);
        noScores->setFont(customFont);
        noScores->setStyleSheet("color: #777777;");
        noScores->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(noScores);
    }
}