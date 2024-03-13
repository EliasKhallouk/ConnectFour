#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Création du titre
    QLabel titleLabel("Choisissez votre pseudo");
    QFont titleFont = titleLabel.font();
    titleFont.setPointSize(24);
    titleLabel.setFont(titleFont);

    // Création du champ d'entrée
    QLineEdit inputPseudo;
    inputPseudo.setFixedWidth(200);
    inputPseudo.setStyleSheet("border: 1px solid white; border-radius: 50px;");

    // Création du bouton
    QPushButton suivantPseudo("Suivant");
    suivantPseudo.setFixedWidth(200);
    suivantPseudo.setStyleSheet("border: 1px solid white; border-radius: 50px;");

    // Mise en page principale
    QVBoxLayout mainLayout;

    // Ajout du titre centré verticalement
    titleLabel.setStyleSheet("color: #FFFFFF;");  // Définir la couleur du texte
    mainLayout.addWidget(&titleLabel, 0, Qt::AlignVCenter | Qt::AlignHCenter);

    // Création de la mise en page horizontale pour centrer les éléments
    QHBoxLayout centerLayout;
    centerLayout.addWidget(&inputPseudo, 0, Qt::AlignHCenter | Qt::AlignVCenter);

    // Définir la couleur de fond du bouton
    suivantPseudo.setStyleSheet("background-color: #FCA311");  // Définir la couleur du fond et du texte
    centerLayout.addWidget(&suivantPseudo, 0, Qt::AlignHCenter | Qt::AlignVCenter);

    // Ajout de la mise en page horizontale à la mise en page principale
    mainLayout.addLayout(&centerLayout);

    // Définir la taille de la fenêtre principale à 700x700
    QWidget mainWidget;
    mainWidget.setLayout(&mainLayout);

    // Définir la couleur de fond de la fenêtre principale
    mainWidget.setStyleSheet("background-color: #14213D;");

    mainWidget.resize(700, 700);
    mainWidget.setWindowTitle("Connect Four");

    // Centrer la fenêtre sur l'écran
    QRect mainScreenSize = QApplication::desktop()->screenGeometry();
    int x = (mainScreenSize.width() - mainWidget.width()) / 2;
    int y = (mainScreenSize.height() - mainWidget.height()) / 2;
    mainWidget.move(x, y);

    // Affichage du widget principal
    mainWidget.show();

    return app.exec();
}
