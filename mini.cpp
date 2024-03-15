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

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

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

        // Création du bouton
        QPushButton suivantNumberJoueur("Suivant");
        suivantNumberJoueur.setFixedWidth(200);
        suivantNumberJoueur.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #FCA311");

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

        // Création du bouton "Suivant"
        QPushButton suivantPseudo("Suivant");
        suivantPseudo.setFixedWidth(200);
        suivantPseudo.setStyleSheet("border: 1px solid white; border-radius: 50px; background-color: #FCA311");

        layoutPseudo.addWidget(&titlePseudo, 0, Qt::AlignVCenter | Qt::AlignHCenter);
        QHBoxLayout centerLayoutPseudo;
        centerLayoutPseudo.addWidget(&inputPseudo, 0, Qt::AlignHCenter | Qt::AlignVCenter);
        centerLayoutPseudo.addWidget(&chooseColorButton, 0, Qt::AlignHCenter | Qt::AlignVCenter); // Ajout du bouton pour choisir la couleur
        centerLayoutPseudo.addWidget(&suivantPseudo, 0, Qt::AlignHCenter | Qt::AlignVCenter);
        layoutPseudo.addLayout(&centerLayoutPseudo);

        // Création du widget principal pour la page de choix du nombre de joueurs
        QWidget pagePseudo;
        pagePseudo.setLayout(&layoutPseudo);
        pagePseudo.setStyleSheet("background-color: #14213D;");

    // Création d'un QStackedWidget pour gérer les pages
    QStackedWidget stackedWidget;
    stackedWidget.addWidget(&pageNumberJoueur);  // Ajout de la page principale
    stackedWidget.addWidget(&pageTempPartie);    // Ajout de la deuxième page
    stackedWidget.addWidget(&pagePseudo);        // Ajout de la troisieme page
    stackedWidget.setCurrentWidget(&pageNumberJoueur);  // Définir la page principale comme étant celle affichée initialement
    stackedWidget.resize(700, 700);
    stackedWidget.setWindowTitle("Connect Four");

    // Connecter le clic sur le bouton "Suivant" pour passer à la nouvelle page
    QObject::connect(&suivantNumberJoueur, &QPushButton::clicked, [&stackedWidget]() {
        stackedWidget.setCurrentIndex(1);  // Passer à la deuxième page
    });

    // Connecter le clic sur le bouton "Suivant" pour passer à la pagePseudo
    QObject::connect(&suivantTempPartie, &QPushButton::clicked, [&stackedWidget]() {
        stackedWidget.setCurrentIndex(2);  // Passer à la troisième page (index 2)
    });

    // Connecter le clic sur le bouton pour choisir la couleur
    QObject::connect(&chooseColorButton, &QPushButton::clicked, [&inputPseudo, &pagePseudo]() {
        QColor color = QColorDialog::getColor(Qt::white, &pagePseudo, "Choisissez une couleur");
        if (color.isValid()) {
            // Mettre à jour la couleur du champ d'entrée du pseudo
            QString styleSheet = QString("border: 1px solid white; border-radius: 50px; color: %1").arg(color.name());
            inputPseudo.setStyleSheet(styleSheet);
        }
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