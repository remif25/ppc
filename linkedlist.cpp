#include "linkedlist.h"

LinkedList::LinkedList()
{

}



LinkedList::LinkedList(QFile* file)
{
    QTextStream in(file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList list = line.split(';');
        QString *gamme;


        if(list.count() == 3) {
            if (gamme->isEmpty()) {
                gamme->append(&list.first());
            }

            QChar *data = gamme->data();

            //std::cout << data;
        }
    }
}

QString LinkedList::displayData(QFile *file) {
    QTextStream in(file);
    QString result;
    QString gamme;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList list = line.split(';');
        bool nodeValueAlreadyExist = false;
        bool gammeAlreadyExist = false;


        // On vérifie de manière arbitraire si on a au mojns 3 éléments dans la liste (1er : Gamme - 2ème : PDT - 3ème : Clé de réf)
        if(list.count() == 3) {
            if (gamme.isEmpty()) {
                gamme.append(list.first());
                m_listNodeValue.push_back(list[1] + list[2]);
            }

            for (auto &node : m_listNodeValue) { //On vérifie si la combinaison PDT + CLé existe déjà (Elimination des doublons)
                if(node == (list[1] + list[2]))
                    nodeValueAlreadyExist = true;
            }

            if(!nodeValueAlreadyExist) // Si elle n'existe pas déjà on l'ajoute à la liste
                m_listNodeValue.push_back(list[1] + list[2]);


            for (auto &gammesListed : m_listGammes) { //On vérifie si la gamme existe déjà (Elimination des doublons)
                if (gamme == gammesListed)
                    gammeAlreadyExist = true;
            }

            if(!gammeAlreadyExist) // Si elle n'existe pas déjà on l'ajoute à la liste
                m_listGammes.push_back(list.first());

            // Define the node before attach it to the list "listNodes"
            Node *node = new Node;
            //node->before = (struct Node*)malloc(sizeof(struct Node));
            node->value = list[1] + list[2];
            node->gammes.push_back(list.first());
            node->gamme = list.first();
            if (listNodes().size() > 0) { // On fait pointer "before" vers le node qui le succède (1er chainage du graph)
                if(listNodes().back()->gamme == node->gamme){
                    node->before = listNodes().back();
                } else {
                    node->before = NULL;
                }
            } else {
                node->before = NULL;
            }

            std::vector<Node*> a_listNodes = listNodes(); // Ajout du node dans la collection (list)
            a_listNodes.push_back(node);
            listNodes(a_listNodes);



            if (node->before) {
                if (!node->before->gammes.empty()){

                    result += QString("value : ") + node->value.toUtf8().constData()
                            + QString(" / gamme : ") + node->gammes.back().toUtf8().constData()
                            + QString(" // previous->value : ") + node->before->value.toUtf8().constData()
                            + QString(" previous->gamme : ")  + node->before->gammes.front().toUtf8().constData() + QString("\n");
                }
            } else {
                result += QString("value : ") + node->value.toUtf8().constData()
                        + QString(" / gamme : ") + node->gammes.back().toUtf8().constData() + QString("\n");
            }

        }
    }
    return result;
}

void LinkedList::add_elements(int t_nbElements)
{
    nbElements(t_nbElements + nbElements());
}

void LinkedList::add_gammes(int t_nbGammes)
{
    nbGammes(t_nbGammes + nbGammes());
}
