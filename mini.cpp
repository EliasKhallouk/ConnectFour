#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QStackedWidget>
#include <QComboBox>
#include <QColorDialog>
#include <QPair>
#include <QList>
#include <QMap>
#include <QTableWidget>

#include "NombreJoueurPage.h"

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
            titleNumberJoueur.setStyleSheet("color: #FFFFFF;");

            // Création du champ d'entrée
            QLineEdit inputNumberJoueur;
            inputNumberJoueur.setFixedWidth(200);
            inputNumberJoueur.setStyleSheet("border: 1px solid white; border-radius: 50px; color: #FFFFFF");

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
            pageNumberJoueur.setStyleSheet("background-color: #14213D;");


    // MISE EN PAGE TEMPS DE PARTIE
    QVBoxLayout layoutTempPartie;
            // Création du titre
            QLabel titleTempPartie("Choisissez le temps de partie");
            titleFont = titleTempPartie.font();
            titleFont.setPointSize(24);
            titleTempPartie.setFont(titleFont);
            titleTempPartie.setStyleSheet("color: #FFFFFF;");

            // Création du champ d'entrée
            QComboBox comboBoxTempPartie;
            comboBoxTempPartie.setFixedWidth(200);
            comboBoxTempPartie.addItem("3 minutes");
            comboBoxTempPartie.addItem("5 minutes");
            comboBoxTempPartie.addItem("10 minutes");
            comboBoxTempPartie.setStyleSheet("border: 1px solid white; border-radius: 50px; color: #FFFFFF");

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
            pageTempPartie.setStyleSheet("background-color: #14213D;");


    // MISE EN PAGE PSEUDO
    QVBoxLayout layoutPseudo;
            // Création du titre
            QLabel titlePseudo("Choisissez le pseudo et la couleur");
            titleFont = titlePseudo.font();
            titleFont.setPointSize(24);
            titlePseudo.setFont(titleFont);
            titlePseudo.setStyleSheet("color: #FFFFFF;");

            // Création du champ d'entrée pour le pseudo
            QLineEdit inputPseudo;
            inputPseudo.setFixedWidth(200);
            inputPseudo.setStyleSheet("border: 1px solid white; border-radius: 50px; color: #FFFFFF");

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
            pagePseudo.setStyleSheet("background-color: #14213D;");


    // MISE EN PAGE JOUER DE PARTIE
    QVBoxLayout layoutJouerPartie;
            // Création du titre
            QLabel titleJouerPartie("Jouer la partie");
            titleFont = titleJouerPartie.font();
            titleFont.setPointSize(24);
            titleJouerPartie.setFont(titleFont);
            titleJouerPartie.setStyleSheet("color: #FFFFFF;");

            // Création du tableau pour afficher les données
            QTableWidget tableauJouerPartie(0, 4); // 4 colonnes
            tableauJouerPartie.setHorizontalHeaderLabels(QStringList() << "PSEUDO" << "PARTIE GAGNER" << "PARTIE PERDU" << "TOTAL POINT");

            // Ajoutez les pseudos dans la première colonne
            for (int i = 0; i < pseudoList.size(); ++i) {
                tableauJouerPartie.insertRow(i);
                tableauJouerPartie.setItem(i, 0, new QTableWidgetItem(pseudoList[i]));
                // Remplissez les autres cellules avec des zéros
                for (int j = 1; j < 4; ++j) {
                    tableauJouerPartie.setItem(i, j, new QTableWidgetItem("0"));
                }
            }

            // Redimensionner les colonnes pour s'adapter au contenu
            //tableauJouerPartie.resizeColumnsToContents();
            for (int col = 0; col < 4; ++col) {
                tableauJouerPartie.setColumnWidth(col, 600 / 4); // Divisez la largeur fixe par le nombre de colonnes pour obtenir la largeur de chaque colonne
            }
            // Rendre les cellules du tableau non éditables
            for (int row = 0; row < tableauJouerPartie.rowCount(); ++row) {
                for (int col = 0; col < tableauJouerPartie.columnCount(); ++col) {
                    QTableWidgetItem *item = tableauJouerPartie.item(row, col);
                    if (item) {
                        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                    }
                }
            }
            layoutJouerPartie.addWidget(&titleJouerPartie, 0, Qt::AlignVCenter | Qt::AlignHCenter);
            layoutJouerPartie.addWidget(&tableauJouerPartie, Qt::AlignVCenter | Qt::AlignHCenter);

            // Création du widget principal pour la page de choix du temps de partie
            QWidget pageJouerPartie;
            pageJouerPartie.setLayout(&layoutJouerPartie);
            pageJouerPartie.setStyleSheet("background-color: #14213D;");




    // Création d'un QStackedWidget pour gérer les pages
    QStackedWidget stackedWidget;
    stackedWidget.addWidget(&pageNumberJoueur);  // Ajout de la page principale
    stackedWidget.addWidget(&pageTempPartie);    // Ajout de la deuxième page
    stackedWidget.addWidget(&pagePseudo);        // Ajout de la troisième page
    stackedWidget.addWidget(&pageJouerPartie);  // Ajout de la quatrième page
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
    int playersAdded = 0;

    // Connecter le clic sur le bouton "Enregistrer Pseudo"
   // Connecter le clic sur le bouton "Enregistrer Pseudo"
   QObject::connect(&enregistrerPseudo, &QPushButton::clicked, [&layoutPseudo,&pseudoList, &inputPseudo, &nextPlayerIndex, &totalPlayers, &suivantPseudo, &enregistrerPseudo, &tableauJouerPartie, &playerInfoMap, &chooseColorButton]() {
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
       int row = tableauJouerPartie.rowCount();
       tableauJouerPartie.insertRow(row);
       tableauJouerPartie.setItem(row, 0, new QTableWidgetItem(pseudo));

       // Remplir les autres cellules avec les informations du joueur
       QTableWidgetItem *gamesWonItem = new QTableWidgetItem(QString::number(playerInfo.gamesWon));
       QTableWidgetItem *gamesLostItem = new QTableWidgetItem(QString::number(playerInfo.gamesLost));
       QTableWidgetItem *totalPointsItem = new QTableWidgetItem(QString::number(playerInfo.totalPoints));

       // Rendre les cellules non éditables
       gamesWonItem->setFlags(gamesWonItem->flags() ^ Qt::ItemIsEditable);
       gamesLostItem->setFlags(gamesLostItem->flags() ^ Qt::ItemIsEditable);
       totalPointsItem->setFlags(totalPointsItem->flags() ^ Qt::ItemIsEditable);

       tableauJouerPartie.setItem(row, 1, gamesWonItem);
       tableauJouerPartie.setItem(row, 2, gamesLostItem);
       tableauJouerPartie.setItem(row, 3, totalPointsItem);

       // Définir la couleur de fond de toute la ligne avec la couleur du pseudo
       for (int col = 0; col < 4; ++col) {
           QTableWidgetItem *item = tableauJouerPartie.item(row, col);
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





    // Connecter le clic sur le bouton "Suivant" pour passer à la page suivante
    QObject::connect(&suivantPseudo, &QPushButton::clicked, [&stackedWidget]() {
        stackedWidget.setCurrentIndex(3);  // Passer à la page suivante
    });


    // Centrer la fenêtre sur l'écran
    QRect mainScreenSize = QApplication::desktop()->screenGeometry();
    int x = (mainScreenSize.width() - stackedWidget.width()) / 2;
    int y = (mainScreenSize.height() - stackedWidget.height()) / 2;
    stackedWidget.move(x, y);

    // Afficher le widget principal
    stackedWidget.show();

    return app.exec();
}
