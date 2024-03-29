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

//#include "mainwindow.h"
struct PlayerInfo {
    QColor color;
    int gamesWon;
    int gamesLost;
    int totalPoints;

    // Méthode pour définir la couleur
    void setColor(const QColor &newColor) {
        color = newColor;
    }
};

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

void refreshScene(QGraphicsScene *scene) {
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

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QStringList pseudoList;
    QMap<QString, PlayerInfo> playerInfoMap;

    // MISE EN PAGE NOMBRE JOUEUR
    QVBoxLayout layoutNumberJoueur;
    // Création du titre
    QLabel titleNumberJoueur("Choisissez le nombre de joueur");
    QFont titleFont = titleNumberJoueur.font();
    titleFont.setPointSize(24);
    titleNumberJoueur.setFont(titleFont);
    titleNumberJoueur.setStyleSheet("color: #14213D;");

    // Création du champ d'entrée
    QLineEdit inputNumberJoueur;
    inputNumberJoueur.setFixedWidth(200);
    inputNumberJoueur.setStyleSheet("border: 1px solid white; border-radius: 50px; color: #14213D");

    // Ajouter un validateur pour n'accepter que les entiers
    QIntValidator *validator = new QIntValidator(&inputNumberJoueur);
    inputNumberJoueur.setValidator(validator);

    // Création du bouton
    QPushButton suivantNumberJoueur("Suivant");
    suivantNumberJoueur.setFixedWidth(200);
    suivantNumberJoueur.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #E5E5E5; color: #000000;");
    suivantNumberJoueur.setEnabled(false);

    layoutNumberJoueur.addWidget(&titleNumberJoueur, 0, Qt::AlignVCenter | Qt::AlignHCenter);
    QHBoxLayout centerLayoutNumberJoueur;
    centerLayoutNumberJoueur.addWidget(&inputNumberJoueur, 0, Qt::AlignHCenter | Qt::AlignVCenter);
    centerLayoutNumberJoueur.addWidget(&suivantNumberJoueur, 0, Qt::AlignHCenter | Qt::AlignVCenter);
    layoutNumberJoueur.addLayout(&centerLayoutNumberJoueur);

    // Création du widget principal pour la page de choix du nombre de joueurs
    QWidget pageNumberJoueur;
    pageNumberJoueur.setLayout(&layoutNumberJoueur);
    pageNumberJoueur.setStyleSheet("background-color: #A6B9E2;");


    // MISE EN PAGE TEMPS DE PARTIE
    QVBoxLayout layoutTempPartie;
    // Création du titre
    QLabel titleTempPartie("Choisissez le temps de partie");
    titleFont = titleTempPartie.font();
    titleFont.setPointSize(24);
    titleTempPartie.setFont(titleFont);
    titleTempPartie.setStyleSheet("color: #14213D;");

    // Création du champ d'entrée
    QComboBox comboBoxTempPartie;
    comboBoxTempPartie.setFixedWidth(200);
    comboBoxTempPartie.addItem("3 minutes");
    comboBoxTempPartie.addItem("5 minutes");
    comboBoxTempPartie.addItem("10 minutes");
    comboBoxTempPartie.setStyleSheet("border: 1px solid white; border-radius: 50px; color: #14213D");

    // Création du bouton
    QPushButton suivantTempPartie("Suivant");
    suivantTempPartie.setFixedWidth(200);
    suivantTempPartie.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #FCA311");

    layoutTempPartie.addWidget(&titleTempPartie, 0, Qt::AlignVCenter | Qt::AlignHCenter);
    QHBoxLayout centerLayoutTempPartie;
    centerLayoutTempPartie.addWidget(&comboBoxTempPartie, 0, Qt::AlignHCenter | Qt::AlignVCenter);
    centerLayoutTempPartie.addWidget(&suivantTempPartie, 0, Qt::AlignHCenter | Qt::AlignVCenter);
    layoutTempPartie.addLayout(&centerLayoutTempPartie);

    // Création du widget principal pour la page de choix du temps de partie
    QWidget pageTempPartie;
    pageTempPartie.setLayout(&layoutTempPartie);
    pageTempPartie.setStyleSheet("background-color: #A6B9E2;");


    // MISE EN PAGE PSEUDO
    QVBoxLayout layoutPseudo;
    // Création du titre
    QLabel titlePseudo("Choisissez le pseudo et la couleur");
    titleFont = titlePseudo.font();
    titleFont.setPointSize(24);
    titlePseudo.setFont(titleFont);
    titlePseudo.setStyleSheet("color: #14213D;");

    // Création du champ d'entrée pour le pseudo
    QLineEdit inputPseudo;
    inputPseudo.setFixedWidth(200);
    inputPseudo.setStyleSheet("border: 1px solid white; border-radius: 50px; color: #14213D");

    // Création du bouton pour choisir la couleur
    QPushButton chooseColorButton("Choisir une couleur");
    chooseColorButton.setFixedWidth(200);
    chooseColorButton.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #FCA311");

    // Création du bouton "Enregistrer"
    QPushButton enregistrerPseudo("Enregistrer Pseudo");
    enregistrerPseudo.setFixedWidth(200);
    enregistrerPseudo.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #FCA311; color: #000000;");

    // Création du bouton "Suivant"
    QPushButton suivantPseudo("Suivant");
    suivantPseudo.setFixedWidth(200);
    suivantPseudo.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #FCA311");

    layoutPseudo.addWidget(&titlePseudo, 0, Qt::AlignVCenter | Qt::AlignHCenter);
    QHBoxLayout centerLayoutPseudo;
    centerLayoutPseudo.addWidget(&inputPseudo, 0, Qt::AlignHCenter | Qt::AlignVCenter);
    centerLayoutPseudo.addWidget(&chooseColorButton, 0, Qt::AlignHCenter | Qt::AlignVCenter); // Ajout du bouton pour choisir la couleur
    centerLayoutPseudo.addWidget(&enregistrerPseudo, 0, Qt::AlignHCenter | Qt::AlignVCenter);
    centerLayoutPseudo.addWidget(&suivantPseudo, 0, Qt::AlignHCenter | Qt::AlignVCenter);
    layoutPseudo.addLayout(&centerLayoutPseudo);

    // Création du widget principal pour la page de choix du nombre de joueurs
    QWidget pagePseudo;
    pagePseudo.setLayout(&layoutPseudo);
    pagePseudo.setStyleSheet("background-color: #A6B9E2;");


    // MISE EN PAGE JOUER DE PARTIE
    QVBoxLayout layoutTableau;
    // Création du titre
    QLabel titleTableau("Jouer la partie");
    titleFont = titleTableau.font();
    titleFont.setPointSize(24);
    titleTableau.setFont(titleFont);
    titleTableau.setStyleSheet("color: #14213D;");

    // Création du tableau pour afficher les données
    QTableWidget tableauScore(0, 4); // 4 colonnes
    tableauScore.setHorizontalHeaderLabels(QStringList() << "PSEUDO" << "PARTIE GAGNER" << "PARTIE PERDU" << "TOTAL POINT");

    // Création du bouton
    QPushButton suivantTableau("Suivant");
    suivantTableau.setFixedWidth(200);
    suivantTableau.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #FCA311");

    layoutTableau.addWidget(&titleTableau, 0, Qt::AlignVCenter | Qt::AlignHCenter);
    layoutTableau.addWidget(&tableauScore, Qt::AlignVCenter | Qt::AlignHCenter);
    layoutTableau.addWidget(&suivantTableau, 0, Qt::AlignVCenter | Qt::AlignHCenter);



    // Création du widget principal pour la page de choix du temps de partie
    QWidget pageTableau;
    pageTableau.setLayout(&layoutTableau);
    pageTableau.setStyleSheet("background-color: #A6B9E2;");

    QGraphicsScene *scene = new QGraphicsScene();

    //TSTTR
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

        QObject::connect(button, &QPushButton::clicked, [i, scene]() {
            qDebug() << (i+1);

            if (tab[0][i] == 0) {
                place(i);
                refreshScene(scene);
            }
        });
    }


    // Création d'un QStackedWidget pour gérer les pages
    QStackedWidget stackedWidget;
    stackedWidget.addWidget(&pageNumberJoueur);  // Ajout de la page principale
    stackedWidget.addWidget(&pageTempPartie);    // Ajout de la deuxième page
    stackedWidget.addWidget(&pagePseudo);        // Ajout de la troisième page
    stackedWidget.addWidget(&pageTableau);  // Ajout de la quatrième page

    //TSTTR
    stackedWidget.addWidget(&pageGame);

    stackedWidget.setCurrentWidget(&pageNumberJoueur);  // Définir la page principale comme étant celle affichée initialement
    stackedWidget.resize(700, 700);
    stackedWidget.setWindowTitle("Connect Four");

    // Définir le style des boutons "Suivant" et "Enregistrer Pseudo" lorsque désactivés
    suivantPseudo.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #E5E5E5; color: #000000;");
    suivantPseudo.setEnabled(false);

    enregistrerPseudo.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #FCA311; color: #000000;");
    enregistrerPseudo.setEnabled(true);
    int nextPlayerIndex = 0; // Variable pour suivre le numéro du prochain joueur

    QObject::connect(&inputNumberJoueur, &QLineEdit::textChanged, [&suivantNumberJoueur](const QString &text) {
        if (text.isEmpty()) {
            suivantNumberJoueur.setEnabled(false);
            suivantNumberJoueur.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #E5E5E5; color: #000000;");
        } else {
            suivantNumberJoueur.setEnabled(true);
            suivantNumberJoueur.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #FCA311;");
        }
    });

    // Connecter le clic sur le bouton "Suivant" pour passer à la nouvelle page
    QObject::connect(&suivantNumberJoueur, &QPushButton::clicked, [&stackedWidget]() {
        stackedWidget.setCurrentIndex(1);  // Passer à la deuxième page
    });

    // Connecter le clic sur le bouton "Suivant" pour passer à la pagePseudo
    QObject::connect(&suivantTempPartie, &QPushButton::clicked, [&stackedWidget]() {
        stackedWidget.setCurrentIndex(2);  // Passer à la troisième page (index 2)
    });

    // Connecter le clic sur le bouton "Suivant" pour passer à la page suivante
    QObject::connect(&suivantPseudo, &QPushButton::clicked, [&stackedWidget]() {
        stackedWidget.setCurrentIndex(3);  // Passer à la page suivante
    });

    QObject::connect(&suivantTableau, &QPushButton::clicked, [&stackedWidget]() {
        stackedWidget.setCurrentIndex(4);
    });

    // Connecter le clic sur le bouton pour choisir la couleur
    QObject::connect(&chooseColorButton, &QPushButton::clicked, [&inputPseudo, &pagePseudo, &playerInfoMap]() {
        QString pseudo = inputPseudo.text();
        QColor color = QColorDialog::getColor(Qt::white, &pagePseudo, "Choisissez une couleur");

        if (color.isValid()) {
            // Mettre à jour la couleur du champ d'entrée du pseudo
            QString styleSheet = QString("border: 1px solid white; border-radius: 50px; color: %1").arg(color.name());
            inputPseudo.setStyleSheet(styleSheet);

            // Enregistrer la couleur choisie pour ce pseudo dans la structure PlayerInfo
            PlayerInfo &playerInfo = playerInfoMap[pseudo];
            playerInfo.setColor(color);
        }
    });
    int totalPlayers = 0;

    // Connecter le champ d'entrée du nombre de joueurs pour mettre à jour totalPlayers
    QObject::connect(&inputNumberJoueur, &QLineEdit::textChanged, [&totalPlayers, &suivantPseudo](const QString &text) {
        bool ok;
        int numPlayers = text.toInt(&ok);
        if (ok && numPlayers > 0) {
            totalPlayers = numPlayers;
            suivantPseudo.setEnabled(false); // Désactiver le bouton "Suivant" jusqu'à ce que tous les pseudos soient enregistrés
        }
    });
    // Connecter le clic sur le bouton "Suivant" pour passer à la pagePseudo
    QObject::connect(&suivantTempPartie, &QPushButton::clicked, [&stackedWidget]() {
        stackedWidget.setCurrentIndex(2);  // Passer à la troisième page (index 2)
    });

    // Ajoutez une variable pour suivre le nombre de joueurs déjà ajoutés
    //int playersAdded = 0;

    // Connecter le clic sur le bouton "Enregistrer Pseudo"
    // Connecter le clic sur le bouton "Enregistrer Pseudo"
    QObject::connect(&enregistrerPseudo, &QPushButton::clicked, [&layoutPseudo,&pseudoList, &inputPseudo, &nextPlayerIndex, &totalPlayers, &suivantPseudo, &enregistrerPseudo, &tableauScore, &playerInfoMap]() {
        if (pseudoList.size() >= totalPlayers) {
            return; // Ne rien faire si le nombre maximal de pseudos est atteint
        }

        QString pseudo = inputPseudo.text(); // Récupérer le pseudo entré

        // Vérifier si le pseudo est vide ou s'il y a déjà suffisamment de pseudos
        if (pseudo.isEmpty() || pseudoList.size() >= totalPlayers) {
            return;
        }

        // Création d'une instance de PlayerInfo et initialisation à zéro
        PlayerInfo playerInfo;
        playerInfo.color = Qt::white; // Couleur par défaut
        playerInfo.gamesWon = 0;
        playerInfo.gamesLost = 0;
        playerInfo.totalPoints = 0;

        // Enregistrer la couleur choisie pour ce pseudo dans la structure PlayerInfo
        QColor pseudoColor = playerInfoMap[pseudo].color;

        // Ajouter le pseudo à la liste
        pseudoList << pseudo;

        // Ajouter le pseudo et ses informations à la QMap
        playerInfoMap.insert(pseudo, playerInfo);

        // Créer une étiquette pour le pseudo avec la couleur correspondante
        QLabel *labelPlayerPseudo = new QLabel(QString("Joueur %1 : %2").arg(nextPlayerIndex + 1).arg(pseudo));
        labelPlayerPseudo->setStyleSheet(QString("QLabel { color: %1; padding: 5px 0; }").arg(pseudoColor.name())); // Ajuster l'espacement entre les lignes
        layoutPseudo.addWidget(labelPlayerPseudo, 0, Qt::AlignHCenter | Qt::AlignVCenter);

        // Incrémenter le numéro du prochain joueur
        nextPlayerIndex++;

        // Ajouter une ligne pour ce pseudo dans le tableau
        int row = tableauScore.rowCount();
        tableauScore.insertRow(row);
        tableauScore.setItem(row, 0, new QTableWidgetItem(pseudo));

        // Remplir les autres cellules avec les informations du joueur
        QTableWidgetItem *gamesWonItem = new QTableWidgetItem(QString::number(playerInfo.gamesWon));
        QTableWidgetItem *gamesLostItem = new QTableWidgetItem(QString::number(playerInfo.gamesLost));
        QTableWidgetItem *totalPointsItem = new QTableWidgetItem(QString::number(playerInfo.totalPoints));

        // Rendre les cellules non éditables
        gamesWonItem->setFlags(gamesWonItem->flags() ^ Qt::ItemIsEditable);
        gamesLostItem->setFlags(gamesLostItem->flags() ^ Qt::ItemIsEditable);
        totalPointsItem->setFlags(totalPointsItem->flags() ^ Qt::ItemIsEditable);

        tableauScore.setItem(row, 1, gamesWonItem);
        tableauScore.setItem(row, 2, gamesLostItem);
        tableauScore.setItem(row, 3, totalPointsItem);

        // Définir la couleur de fond de toute la ligne avec la couleur du pseudo
        for (int col = 0; col < 4; ++col) {
            QTableWidgetItem *item = tableauScore.item(row, col);
            if (item) {
                item->setBackground(pseudoColor);
            }
        }

        // Vérifier si tous les pseudos ont été enregistrés
        if (pseudoList.size() == totalPlayers) {
            suivantPseudo.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #FCA311; color: #000000;");
            suivantPseudo.setEnabled(true); // Activer le bouton "Suivant" une fois que tous les pseudos sont enregistrés

            // Modifier le style du bouton "Enregistrer Pseudo" car tous les pseudos sont enregistrés
            enregistrerPseudo.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #E5E5E5; color: #000000;");
            enregistrerPseudo.setEnabled(false); // Désactiver le bouton "Enregistrer Pseudo"
        }

        // Effacer le texte dans le champ inputPseudo pour permettre à l'utilisateur d'entrer un nouveau pseudo
        inputPseudo.clear();
    });

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect mainScreenSize = screen->geometry();

    int x = (mainScreenSize.width() - stackedWidget.width()) / 2;
    int y = (mainScreenSize.height() - stackedWidget.height()) / 2;
    stackedWidget.move(x, y);

    // Afficher le widget principal
    stackedWidget.show();

    return app.exec();
}
