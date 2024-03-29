#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScreen>
#include <QStackedWidget>
#include <QComboBox>
#include <QColorDialog>
#include <QPair>
#include <QList>
#include <QMap>
#include <QTableWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsProxyWidget>
#include <QBrush>
#include <QPen>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <vector>
#include <utility>
#include <algorithm>
#include <random>
using namespace std;

//#include "mainwindow.h"
struct PlayerInfo {
    QString pseudo;
    QColor color;
    int gamesWon;
    int gamesLost;
    int gamesEqualities;
    int totalPoints;

    void setColor(const QColor &newColor) {
        color = newColor;
    }
};

const int ROWS = 6;
const int COLS = 7;

const int cellSize = 50;

int tab[ROWS][COLS];

PlayerInfo player1;
PlayerInfo player2;

int idPlayer = 1;

int t1 = 21;
int t2 = 21;

int w1 = 0;
int w2 = 0;

int rnd = 1;

int nMatch = 0;

QTimer timer;

int minutes;

vector<pair<int, int>> matchPlanning;

QColor colorJ1 = (Qt::blue);
QColor colorJ2 = (Qt::red);

//QLabel *labelTimer;

std::vector<PlayerInfo> playersList;

vector<pair<int, int>> generatePlanning(int n) {
    vector<pair<int, int>> pairs;
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            if (j > i) {
                pairs.push_back(make_pair(j, i));
            }
            else {
                pairs.push_back(make_pair(i, j));
            }
        }
    }
    random_device rd;
    mt19937 g(rd());
    shuffle(pairs.begin(), pairs.end(), g);
    return pairs;
}

void initGame(PlayerInfo p1, PlayerInfo p2) {
    colorJ1 = p1.color;
    colorJ2 = p2.color;
}

void reset() {
    t1 = 21;
    t2 = 21;
    idPlayer = (idPlayer == 1) ? 2 : 1;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            tab[i][j] = 0;
        }
    }
}

void resetGame() {
    rnd = 1;
    idPlayer = 1;
    w1 = 0;
    w2 = 0;
    reset();
}

void refreshScene(QGraphicsScene *scene) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if(tab[i][j] == 1) {
                QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(j * cellSize, i * cellSize, cellSize, cellSize);
                circle->setBrush(QBrush(colorJ1));
                scene->addItem(circle);
            } else if (tab[i][j] == 2) {
                QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(j * cellSize, i * cellSize, cellSize, cellSize);
                circle->setBrush(QBrush(colorJ2));
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
    leftCircle->setBrush(QBrush(colorJ1));
    scene->addItem(leftCircle);

    QGraphicsEllipseItem *rightCircle = new QGraphicsEllipseItem(COLS * cellSize + circleSpacing, ROWS * cellSize / 2 - cellSize / 2, cellSize, cellSize);
    rightCircle->setBrush(QBrush(colorJ2));
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
    topLeftCircle1->setBrush(QBrush(colorJ1));
    scene->addItem(topLeftCircle1);

    QGraphicsEllipseItem *topLeftCircle2 = new QGraphicsEllipseItem(cellSize, -2*cellSize - circleSpacing, cellSize - 2, cellSize - 2);
    topLeftCircle2->setBrush(QBrush(colorJ1));
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
        qDebug() << "1 wins";
        break;

    default:
        qDebug() << "Inosumi";
        break;
    }

    QGraphicsEllipseItem *topRightCircle1 = new QGraphicsEllipseItem((COLS-1) * cellSize, -2*cellSize - circleSpacing, cellSize - 2, cellSize - 2);
    topRightCircle1->setBrush(QBrush(colorJ2));
    scene->addItem(topRightCircle1);

    QGraphicsEllipseItem *topRightCircle2 = new QGraphicsEllipseItem((COLS-2) * cellSize, -2*cellSize - circleSpacing, cellSize - 2, cellSize - 2);
    topRightCircle2->setBrush(QBrush(colorJ2));
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
        qDebug() << "2 wins";
        break;

    default:
        qDebug() << "Miku";
        break;
    }
    
    QLabel *label = new QLabel("Hello, World!");
    
    // Création du proxy widget pour le label
    QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget;
    proxy->setWidget(label);
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
        rnd++;
        if (w1 == 2 || w2 == 2) {
            return true;
        }
        else {
            reset();
        }
    }
    else if (t2 == 0){
        QMessageBox msgBox;
        ++w1;
        ++w2;
        msgBox.setWindowTitle(QString::number(rnd));
        msgBox.setText("Equality");
        msgBox.resize(400, 200);
        msgBox.exec();
        rnd++;
        if (w1 == 2 || w2 == 2) {
            return true;
        }
        else {
            reset();
        }
    }
    else {
        t1 = (idPlayer == 1) ? --t1 : t1;
        t2 = (idPlayer == 2) ? --t2 : t2;

        idPlayer = (idPlayer == 1) ? 2 : 1;
    }

    return false;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QStringList pseudoList;
    QMap<QString, PlayerInfo> playerInfoMap;

    QVBoxLayout layoutNumberJoueur;
    QLabel titleNumberJoueur("Choisissez le nombre de joueur");
    QFont titleFont = titleNumberJoueur.font();
    titleFont.setPointSize(24);
    titleNumberJoueur.setFont(titleFont);
    titleNumberJoueur.setStyleSheet("color: #14213D;");

    QLineEdit inputNumberJoueur;
    inputNumberJoueur.setFixedWidth(200);
    inputNumberJoueur.setStyleSheet("border: 1px solid white; border-radius: 50px; color: #14213D");

    QIntValidator *validator = new QIntValidator(&inputNumberJoueur);
    inputNumberJoueur.setValidator(validator);

    QPushButton suivantNumberJoueur("Suivant");
    suivantNumberJoueur.setFixedWidth(200);
    suivantNumberJoueur.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #E5E5E5; color: #000000;");
    suivantNumberJoueur.setEnabled(false);

    layoutNumberJoueur.addWidget(&titleNumberJoueur, 0, Qt::AlignVCenter | Qt::AlignHCenter);
    QHBoxLayout centerLayoutNumberJoueur;
    centerLayoutNumberJoueur.addWidget(&inputNumberJoueur, 0, Qt::AlignHCenter | Qt::AlignVCenter);
    centerLayoutNumberJoueur.addWidget(&suivantNumberJoueur, 0, Qt::AlignHCenter | Qt::AlignVCenter);
    layoutNumberJoueur.addLayout(&centerLayoutNumberJoueur);

    QWidget pageNumberJoueur;
    pageNumberJoueur.setLayout(&layoutNumberJoueur);
    pageNumberJoueur.setStyleSheet("background-color: #A6B9E2;");


    QVBoxLayout layoutTempPartie;
    QLabel titleTempPartie("Choisissez le temps de partie");
    titleFont = titleTempPartie.font();
    titleFont.setPointSize(24);
    titleTempPartie.setFont(titleFont);
    titleTempPartie.setStyleSheet("color: #14213D;");

    QComboBox comboBoxTempPartie;
    comboBoxTempPartie.setFixedWidth(200);
    comboBoxTempPartie.addItem("3 minutes");
    comboBoxTempPartie.addItem("5 minutes");
    comboBoxTempPartie.addItem("10 minutes");
    comboBoxTempPartie.setStyleSheet("border: 1px solid white; border-radius: 50px; color: #14213D");

    QPushButton suivantTempPartie("Suivant");
    suivantTempPartie.setFixedWidth(200);
    suivantTempPartie.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #FCA311");

    layoutTempPartie.addWidget(&titleTempPartie, 0, Qt::AlignVCenter | Qt::AlignHCenter);
    QHBoxLayout centerLayoutTempPartie;
    centerLayoutTempPartie.addWidget(&comboBoxTempPartie, 0, Qt::AlignHCenter | Qt::AlignVCenter);
    centerLayoutTempPartie.addWidget(&suivantTempPartie, 0, Qt::AlignHCenter | Qt::AlignVCenter);
    layoutTempPartie.addLayout(&centerLayoutTempPartie);

    QWidget pageTempPartie;
    pageTempPartie.setLayout(&layoutTempPartie);
    pageTempPartie.setStyleSheet("background-color: #A6B9E2;");

    QVBoxLayout layoutPseudo;
    QLabel titlePseudo("Choisissez le pseudo et la couleur");
    titleFont = titlePseudo.font();
    titleFont.setPointSize(24);
    titlePseudo.setFont(titleFont);
    titlePseudo.setStyleSheet("color: #14213D;");

    QLineEdit inputPseudo;
    inputPseudo.setFixedWidth(200);
    inputPseudo.setStyleSheet("border: 1px solid white; border-radius: 50px; color: #14213D");

    QPushButton chooseColorButton("Choisir une couleur");
    chooseColorButton.setFixedWidth(200);
    chooseColorButton.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #FCA311");

    QPushButton enregistrerPseudo("Enregistrer Pseudo");
    enregistrerPseudo.setFixedWidth(200);
    enregistrerPseudo.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #FCA311; color: #000000;");

    QPushButton suivantPseudo("Suivant");
    suivantPseudo.setFixedWidth(200);
    suivantPseudo.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #FCA311");

    layoutPseudo.addWidget(&titlePseudo, 0, Qt::AlignVCenter | Qt::AlignHCenter);
    QHBoxLayout centerLayoutPseudo;
    centerLayoutPseudo.addWidget(&inputPseudo, 0, Qt::AlignHCenter | Qt::AlignVCenter);
    centerLayoutPseudo.addWidget(&chooseColorButton, 0, Qt::AlignHCenter | Qt::AlignVCenter);
    centerLayoutPseudo.addWidget(&enregistrerPseudo, 0, Qt::AlignHCenter | Qt::AlignVCenter);
    centerLayoutPseudo.addWidget(&suivantPseudo, 0, Qt::AlignHCenter | Qt::AlignVCenter);
    layoutPseudo.addLayout(&centerLayoutPseudo);

    QWidget pagePseudo;
    pagePseudo.setLayout(&layoutPseudo);
    pagePseudo.setStyleSheet("background-color: #A6B9E2;");

    QVBoxLayout layoutTableau;
    QLabel titleTableau("Jouer la partie");
    titleFont = titleTableau.font();
    titleFont.setPointSize(24);
    titleTableau.setFont(titleFont);
    titleTableau.setStyleSheet("color: #14213D;");

    QTableWidget tableauScore(0, 5);
    tableauScore.setHorizontalHeaderLabels(QStringList() << "PSEUDO" << "PARTIES GAGNEES" << "PARTIES PERDUES" << "EGALITES" << "TOTAL POINT");

    QPushButton suivantTableau("Suivant");
    suivantTableau.setFixedWidth(200);
    suivantTableau.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #FCA311");

    layoutTableau.addWidget(&titleTableau, 0, Qt::AlignVCenter | Qt::AlignHCenter);
    layoutTableau.addWidget(&tableauScore, Qt::AlignVCenter | Qt::AlignHCenter);
    layoutTableau.addWidget(&suivantTableau, 0, Qt::AlignVCenter | Qt::AlignHCenter);

    QStackedWidget stackedWidget;

    QWidget pageTableau;
    pageTableau.setLayout(&layoutTableau);
    pageTableau.setStyleSheet("background-color: #A6B9E2;");

    QGraphicsScene *scene = new QGraphicsScene();

    QVBoxLayout layoutGame;
    for (int i = 0; i < COLS; ++i) {
        for (int j = 0; j < ROWS; ++j) {
            scene->addRect(i * cellSize, j * cellSize, cellSize, cellSize, QPen(Qt::black));

        }
    }
    QGraphicsView *view = new QGraphicsView(scene);
    layoutGame.addWidget(view);
    QWidget pageGame;
    pageGame.setLayout(&layoutGame);
    pageGame.setStyleSheet("background-color: #A6B9E2;");
    QGraphicsProxyWidget *buttonProxies[COLS];
    for (int i = 0; i < COLS; ++i) {
        QPushButton *button = new QPushButton(QString::number(i + 1));
        button->setFixedSize(cellSize, cellSize);
        buttonProxies[i] = scene->addWidget(button);
        buttonProxies[i]->setPos(i * cellSize, -50);
        /*connect(button, &QPushButton::clicked, this, [=]() { onButtonClicked(scene); });
        connect(button, &QPushButton::clicked, [&, i]() {
            stackedWidget.setCurrentIndex(2);
        });*/
        /*QObject::connect(&button, &QPushButton::clicked, []() {
        });*/

        QObject::connect(button, &QPushButton::clicked, [i, scene, &stackedWidget, &tableauScore]() {
            qDebug() << (i+1);

            player1 = playersList[matchPlanning.at(nMatch).first];
            player2 = playersList[matchPlanning.at(nMatch).second];

            if (tab[0][i] == 0) {
                if (place(i)) {
                    player1.totalPoints += (w1 - w2);
                    player2.totalPoints += (w2 - w1);
                    if (w1 == 2 && w2 == 2) {
                        player1.gamesEqualities += 1;
                        player2.gamesEqualities += 1;
                    }
                    else if (w1 == 2) {
                        player1.gamesWon += 1;
                        player2.gamesLost += 1;
                    }
                    else if (w2 == 2){
                        player1.gamesLost += 1;
                        player2.gamesWon += 1;
                    }

                    tableauScore.setItem(matchPlanning.at(nMatch).first, 1, new QTableWidgetItem(QString::number(player1.gamesWon)));
                    tableauScore.setItem(matchPlanning.at(nMatch).first, 2, new QTableWidgetItem(QString::number(player1.gamesLost)));
                    tableauScore.setItem(matchPlanning.at(nMatch).first, 3, new QTableWidgetItem(QString::number(player1.gamesEqualities)));
                    tableauScore.setItem(matchPlanning.at(nMatch).first, 4, new QTableWidgetItem(QString::number(player1.totalPoints)));

                    for (int col = 1; col <= 4; ++col) {
                        tableauScore.item(matchPlanning.at(nMatch).first, col)->setBackground(QBrush(player1.color));
                    }

                    tableauScore.setItem(matchPlanning.at(nMatch).second, 1, new QTableWidgetItem(QString::number(player2.gamesWon)));
                    tableauScore.setItem(matchPlanning.at(nMatch).second, 2, new QTableWidgetItem(QString::number(player2.gamesLost)));
                    tableauScore.setItem(matchPlanning.at(nMatch).second, 3, new QTableWidgetItem(QString::number(player2.gamesEqualities)));
                    tableauScore.setItem(matchPlanning.at(nMatch).second, 4, new QTableWidgetItem(QString::number(player2.totalPoints)));

                    for (int col = 1; col <= 4; ++col) {
                        tableauScore.item(matchPlanning.at(nMatch).second, col)->setBackground(QBrush(player2.color));
                    }

                    //tableauScore.sortItems(4, Qt::AscendingOrder);

                    nMatch += 1;

                    resetGame();
                    stackedWidget.setCurrentIndex(3);
                }
                else {
                    refreshScene(scene);
                }
            }
        });
    }

    stackedWidget.addWidget(&pageNumberJoueur);
    stackedWidget.addWidget(&pageTempPartie);
    stackedWidget.addWidget(&pagePseudo);
    stackedWidget.addWidget(&pageTableau);

    stackedWidget.addWidget(&pageGame);

    stackedWidget.setCurrentWidget(&pageNumberJoueur);
    stackedWidget.resize(700, 700);
    stackedWidget.setWindowTitle("Connect Four");

    suivantPseudo.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #E5E5E5; color: #000000;");
    suivantPseudo.setEnabled(false);

    enregistrerPseudo.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #FCA311; color: #000000;");
    enregistrerPseudo.setEnabled(true);
    int nextPlayerIndex = 0;

    /*QObject::connect(&timer, &QTimer::timeout, [&]() {
        // Mettre à jour l'affichage du temps restant
        labelTimer.setText(QString("Temps restant : %1:%2")
                          .arg(minutes / 60, 2, 10, QLatin1Char('0'))
                          .arg(minutes % 60, 2, 10, QLatin1Char('0')));
        minutes--;

        // Si le temps est écoulé
        if (minutes < 0) {
            // Arrêter le timer
            timer.stop();
            // Effectuer quelque chose ici lorsque le temps est écoulé
            labelTimer.setText("Temps écoulé !");
        }
    });*/

    QObject::connect(&comboBoxTempPartie, QOverload<int>::of(&QComboBox::currentIndexChanged), [&](int index) {
        // Mettre à jour la valeur des minutes en fonction de la sélection
        switch(index) {
        case 0:
            minutes = 3 * 60;
            break;
        case 1:
            minutes = 5 * 60;
            break;
        case 2:
            minutes = 10 * 60;
            break;
        default:
            break;
        }
    });

    QObject::connect(&inputNumberJoueur, &QLineEdit::textChanged, [&suivantNumberJoueur](const QString &text) {
        if (text.isEmpty()) {
            suivantNumberJoueur.setEnabled(false);
            suivantNumberJoueur.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #E5E5E5; color: #000000;");
        } else {
            suivantNumberJoueur.setEnabled(true);
            suivantNumberJoueur.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #FCA311;");
        }
    });

    QObject::connect(&suivantNumberJoueur, &QPushButton::clicked, [&stackedWidget]() {
        stackedWidget.setCurrentIndex(1);
    });

    QObject::connect(&suivantTempPartie, &QPushButton::clicked, [&stackedWidget]() {
        stackedWidget.setCurrentIndex(2);
    });

    QObject::connect(&suivantPseudo, &QPushButton::clicked, [&stackedWidget]() {
        stackedWidget.setCurrentIndex(3);
    });

    QObject::connect(&suivantTableau, &QPushButton::clicked, [&stackedWidget, scene]() {
        stackedWidget.setCurrentIndex(4);
        initGame(playersList[matchPlanning.at(nMatch).first], playersList[matchPlanning.at(nMatch).second]);
        refreshScene(scene);
    });

    QObject::connect(&chooseColorButton, &QPushButton::clicked, [&inputPseudo, &pagePseudo, &playerInfoMap]() {
        QString pseudo = inputPseudo.text();
        QColor color = QColorDialog::getColor(Qt::white, &pagePseudo, "Choisissez une couleur");

        if (color.isValid()) {
            QString styleSheet = QString("border: 1px solid white; border-radius: 50px; color: %1").arg(color.name());
            inputPseudo.setStyleSheet(styleSheet);

            PlayerInfo &playerInfo = playerInfoMap[pseudo];
            playerInfo.setColor(color);
        }
    });
    int totalPlayers = 0;

    QObject::connect(&inputNumberJoueur, &QLineEdit::textChanged, [&totalPlayers, &suivantPseudo](const QString &text) {
        bool ok;
        int numPlayers = text.toInt(&ok);
        if (ok && numPlayers > 1) {
            totalPlayers = numPlayers;
            suivantPseudo.setEnabled(false);
        }
    });

    QObject::connect(&suivantTempPartie, &QPushButton::clicked, [&stackedWidget]() {
        stackedWidget.setCurrentIndex(2);
    });

    QObject::connect(&enregistrerPseudo, &QPushButton::clicked, [&layoutPseudo,&pseudoList, &inputPseudo, &nextPlayerIndex, &totalPlayers, &suivantPseudo, &enregistrerPseudo, &tableauScore, &playerInfoMap]() {

        if (pseudoList.size() >= totalPlayers) {
            return;
        }

        QString pseudo = inputPseudo.text();

        if (pseudo.isEmpty() || pseudoList.size() >= totalPlayers) {
            return;
        }

        PlayerInfo playerInfo;
        playerInfo.color = Qt::white;
        playerInfo.gamesWon = 0;
        playerInfo.gamesLost = 0;
        playerInfo.gamesEqualities = 0;
        playerInfo.totalPoints = 0;

        QColor pseudoColor = playerInfoMap[pseudo].color;

        pseudoList << pseudo;

        playerInfo.pseudo = pseudo;

        playerInfoMap.insert(pseudo, playerInfo);

        QLabel *labelPlayerPseudo = new QLabel(QString("Joueur %1 : %2").arg(nextPlayerIndex + 1).arg(pseudo));
        labelPlayerPseudo->setStyleSheet(QString("QLabel { color: %1; padding: 5px 0; }").arg(pseudoColor.name()));
        layoutPseudo.addWidget(labelPlayerPseudo, 0, Qt::AlignHCenter | Qt::AlignVCenter);

        QString styleSheet = labelPlayerPseudo->styleSheet();
        QRegularExpression regex("color:\\s*(.*?);");
        QRegularExpressionMatch match = regex.match(styleSheet);
        if (match.hasMatch()) {
            QString textColorString = match.captured(1);
            QColor textColor(textColorString);
            playerInfo.color = textColor;
        } else {
            playerInfo.color = Qt::blue;
        }

        matchPlanning = generatePlanning(totalPlayers);

        playersList.push_back(playerInfo);

        nextPlayerIndex++;

        int row = tableauScore.rowCount();
        tableauScore.insertRow(row);

        QTableWidgetItem *pseudoItem = new QTableWidgetItem(pseudo);
        QTableWidgetItem *gamesWonItem = new QTableWidgetItem(QString::number(playerInfo.gamesWon));
        QTableWidgetItem *gamesLostItem = new QTableWidgetItem(QString::number(playerInfo.gamesLost));
        QTableWidgetItem *gamesEqualitiesItem = new QTableWidgetItem(QString::number(playerInfo.gamesEqualities));
        QTableWidgetItem *totalPointsItem = new QTableWidgetItem(QString::number(playerInfo.totalPoints));

        pseudoItem->setFlags(pseudoItem->flags() ^ Qt::ItemIsEditable);
        gamesWonItem->setFlags(gamesWonItem->flags() ^ Qt::ItemIsEditable);
        gamesLostItem->setFlags(gamesLostItem->flags() ^ Qt::ItemIsEditable);
        gamesLostItem->setFlags(gamesEqualitiesItem->flags() ^ Qt::ItemIsEditable);
        totalPointsItem->setFlags(totalPointsItem->flags() ^ Qt::ItemIsEditable);

        tableauScore.setItem(row, 0, pseudoItem);
        tableauScore.setItem(row, 1, gamesWonItem);
        tableauScore.setItem(row, 2, gamesLostItem);
        tableauScore.setItem(row, 3, gamesEqualitiesItem);
        tableauScore.setItem(row, 4, totalPointsItem);

        for (int col = 0; col < 5; ++col) {
            QTableWidgetItem *item = tableauScore.item(row, col);
            if (item) {
                item->setBackground(pseudoColor);
            }
        }

        if (pseudoList.size() == totalPlayers) {
            suivantPseudo.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #FCA311; color: #000000;");
            suivantPseudo.setEnabled(true);

            enregistrerPseudo.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #E5E5E5; color: #000000;");
            enregistrerPseudo.setEnabled(false);
        }

        inputPseudo.clear();
    });

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect mainScreenSize = screen->geometry();

    int x = (mainScreenSize.width() - stackedWidget.width()) / 2;
    int y = (mainScreenSize.height() - stackedWidget.height()) / 2;
    stackedWidget.move(x, y);

    stackedWidget.show();

    return app.exec();
}
