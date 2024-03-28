#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <QGraphicsProxyWidget>
#include <windows.h>
#include <unistd.h>

const int ROWS = 6;
const int COLS = 7;

const int cellSize = 50;

int tab[ROWS][COLS];

int idPlayer = 1;

int t1 = 21;
int t2 = 21;

int w1 = 0;
int w2 = 0;

int rnd = 1;

void reset() {
    t1 = 21;
    t2 = 21;
    idPlayer = 2;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            tab[i][j] = 0;
        }
    }
}

bool isVictory(int x, int y) {
    int count;

    count = 0;
    // Vérification horizontale
    for (int j = std::max(0, y - 3); j <= std::min(COLS - 1, y + 3); ++j) {
        if (tab[x][j] == idPlayer) {
            count++;
            if (count == 4) {
                //qDebug() << "Okakoro";
                return true;
            }
        } else {
            count = 0;
        }
    }

    count = 0;
    // Vérification verticale
    for (int i = std::max(0, x - 3); i <= std::min(ROWS - 1, x + 3); ++i) {
        if (tab[i][y] == idPlayer) {
            count++;
            if (count == 4) {
                //qDebug() << "Fubumio";
                return true;
            }
        } else {
            count = 0;
        }
    }

    count = 0;
    // Vérification diagonale (de haut gauche à bas droite)
    for (int i = std::max(0, x - 3), j = std::max(0, y - 3); i <= std::min(ROWS - 1, x + 3) && j <= std::min(COLS - 1, y + 3); ++i, ++j) {
        if (tab[i][j] == idPlayer) {
            count++;
            if (count == 4) {
                //qDebug() << "Korokayu";
                return true;
            }
        } else {
            count = 0;
        }
    }

    count = 0;
    // Vérification diagonale (de haut droite à bas gauche)
    for (int i = std::max(0, x - 3), j = std::min(COLS - 1, y + 3); i <= std::min(ROWS - 1, x + 3) && j >= std::max(0, y - 3); ++i, --j) {
        if (tab[i][j] == idPlayer) {
            count++;
            if (count == 4) {
                //qDebug() << "Miobuki";
                return true;
            }
        }
    }


    //qDebug() << "Sorazki";

    return false;
}

bool place(int column) {

    bool t = false;
    int i = 0;
    do {
        if (tab[ROWS - 1 - i][column] == 0) {
            tab[ROWS - 1 - i][column] = idPlayer;
            t = true;
        } else {
            ++i;
        }
    } while (!t);

    if (isVictory(ROWS - 1 - i, column)) {
        w1 = (idPlayer == 1) ? ++w1 : w1;
        w2 = (idPlayer == 2) ? ++w2 : w2;
        QMessageBox msgBox;
        msgBox.setWindowTitle(QString::number(rnd));
        msgBox.setText("Congratulation !");
        msgBox.resize(400, 200);
        msgBox.exec();
        reset();
    }
    else if (t2 == 0){
        QMessageBox msgBox;
        ++w1;
        ++w2;
        msgBox.setWindowTitle(QString::number(rnd));
        msgBox.setText("Equality");
        msgBox.resize(400, 200);
        msgBox.exec();
        reset();
    }
    else {
        t1 = (idPlayer == 1) ? --t1 : t1;
        t2 = (idPlayer == 2) ? --t2 : t2;

        idPlayer = (idPlayer == 1) ? 2 : 1;
    }

    return isVictory(ROWS - 1 - i, column);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);

    for (int i = 0; i < COLS; ++i) {
        for (int j = 0; j < ROWS; ++j) {
            scene->addRect(i * cellSize, j * cellSize, cellSize, cellSize, QPen(Qt::black));
        }
    }

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            tab[i][j] = 0;
        }
    }

    refreshScene(scene);

    QGraphicsProxyWidget *buttonProxies[COLS];
    for (int i = 0; i < COLS; ++i) {
        QPushButton *button = new QPushButton(QString::number(i + 1));
        button->setFixedSize(cellSize, cellSize);
        buttonProxies[i] = scene->addWidget(button);
        buttonProxies[i]->setPos(i * cellSize, -50);
        connect(button, &QPushButton::clicked, this, [=]() { onButtonClicked(scene); });
    }

    QGraphicsView *view = new QGraphicsView(scene);
    setCentralWidget(view);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onButtonClicked(QGraphicsScene *scene)
{
    QPushButton *senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton) {
        int column = senderButton->text().toInt() - 1;
        qDebug() << column;

        if (tab[0][column] == 0 ) {
            place(column);
            refreshScene(scene);
        }
    }
}

void MainWindow::refreshScene(QGraphicsScene *scene) {

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if(tab[i][j] == 1) {
                QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(j * cellSize, i * cellSize, cellSize, cellSize);
                circle->setBrush(QBrush(Qt::blue));
                scene->addItem(circle);
            } else if (tab[i][j] == 2) {
                QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(j * cellSize, i * cellSize, cellSize, cellSize);
                circle->setBrush(QBrush(Qt::red));
                scene->addItem(circle);
            }
            else {
                QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(j * cellSize, i * cellSize, cellSize, cellSize);
                circle->setBrush(QBrush(Qt::white));
                scene->addItem(circle);
            }
        }
    }

    int circleSpacing = 20;

    QGraphicsEllipseItem *leftCircle = new QGraphicsEllipseItem(-cellSize - circleSpacing, ROWS * cellSize / 2 - cellSize / 2, cellSize, cellSize);
    leftCircle->setBrush(QBrush(Qt::blue));
    scene->addItem(leftCircle);

    QGraphicsEllipseItem *rightCircle = new QGraphicsEllipseItem(COLS * cellSize + circleSpacing, ROWS * cellSize / 2 - cellSize / 2, cellSize, cellSize);
    rightCircle->setBrush(QBrush(Qt::red));
    scene->addItem(rightCircle);

    QFont boldFont("Arial", 12, QFont::Bold);

    QGraphicsTextItem *textLeftCircle = new QGraphicsTextItem(QString::number(t1));
    textLeftCircle->setDefaultTextColor(Qt::white);
    textLeftCircle->setFont(boldFont);
    textLeftCircle->setPos(leftCircle->boundingRect().center() - QPointF(textLeftCircle->boundingRect().width() / 2, textLeftCircle->boundingRect().height() / 2));
    scene->addItem(textLeftCircle);

    QGraphicsTextItem *textRightCircle = new QGraphicsTextItem(QString::number(t2));
    textRightCircle->setDefaultTextColor(Qt::white);
    textRightCircle->setFont(boldFont);
    textRightCircle->setPos(rightCircle->boundingRect().center() - QPointF(textRightCircle->boundingRect().width() / 2, textRightCircle->boundingRect().height() / 2));
    scene->addItem(textRightCircle);

    QGraphicsEllipseItem *topLeftCircle1 = new QGraphicsEllipseItem(0, -2*cellSize - circleSpacing, cellSize - 2, cellSize - 2);
    topLeftCircle1->setBrush(QBrush(Qt::blue));
    scene->addItem(topLeftCircle1);

    QGraphicsEllipseItem *topLeftCircle2 = new QGraphicsEllipseItem(cellSize, -2*cellSize - circleSpacing, cellSize - 2, cellSize - 2);
    topLeftCircle2->setBrush(QBrush(Qt::blue));
    scene->addItem(topLeftCircle2);

    QGraphicsEllipseItem *topLeftCircle1bis = nullptr;
    QGraphicsEllipseItem *topLeftCircle2bis = nullptr;

    switch (w1) {
    case 0:
        topLeftCircle1bis = new QGraphicsEllipseItem(0 + 2, -2*cellSize - circleSpacing + 2, cellSize - 6, cellSize - 6);
        topLeftCircle1bis->setBrush(QBrush(Qt::white));
        scene->addItem(topLeftCircle1bis);
        topLeftCircle2bis = new QGraphicsEllipseItem(cellSize + 2, -2*cellSize - circleSpacing + 2, cellSize - 6, cellSize - 6);
        topLeftCircle2bis->setBrush(QBrush(Qt::white));
        scene->addItem(topLeftCircle2bis);
        break;

    case 1:
        topLeftCircle2bis = new QGraphicsEllipseItem(cellSize + 2, -2*cellSize - circleSpacing + 2, cellSize - 6, cellSize - 6);
        topLeftCircle2bis->setBrush(QBrush(Qt::white));
        scene->addItem(topLeftCircle2bis);
        break;

    case 3:
        qDebug() << "Blue wins";
        break;

    default:
        qDebug() << "Inosumi";
        break;
    }

    QGraphicsEllipseItem *topRightCircle1 = new QGraphicsEllipseItem((COLS-1) * cellSize, -2*cellSize - circleSpacing, cellSize - 2, cellSize - 2);
    topRightCircle1->setBrush(QBrush(Qt::red));
    scene->addItem(topRightCircle1);

    QGraphicsEllipseItem *topRightCircle2 = new QGraphicsEllipseItem((COLS-2) * cellSize, -2*cellSize - circleSpacing, cellSize - 2, cellSize - 2);
    topRightCircle2->setBrush(QBrush(Qt::red));
    scene->addItem(topRightCircle2);

    QGraphicsEllipseItem *topRightCircle1bis = nullptr;
    QGraphicsEllipseItem *topRightCircle2bis = nullptr;

    switch (w2) {
    case 0:
        topRightCircle1bis = new QGraphicsEllipseItem((COLS-1) * cellSize + 2, -2*cellSize - circleSpacing + 2, cellSize - 6, cellSize - 6);
        topRightCircle1bis->setBrush(QBrush(Qt::white));
        scene->addItem(topRightCircle1bis);
        topRightCircle2bis = new QGraphicsEllipseItem((COLS-2) * cellSize + 2, -2*cellSize - circleSpacing + 2, cellSize - 6, cellSize - 6);
        topRightCircle2bis->setBrush(QBrush(Qt::white));
        scene->addItem(topRightCircle2bis);
        break;

    case 1:
        topRightCircle2bis = new QGraphicsEllipseItem((COLS-2) * cellSize + 2, -2*cellSize - circleSpacing + 2, cellSize - 6, cellSize - 6);
        topRightCircle2bis->setBrush(QBrush(Qt::white));
        scene->addItem(topRightCircle2bis);

    case 3:
        qDebug() << "Red wins";
        break;

    default:
        qDebug() << "Miku";
        break;
    }
}
