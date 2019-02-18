#include "linkedlist.h"
#include <limits>

LinkedList::LinkedList()
{
    m_nbElements = 0;
    m_nbGammes = 0;
}

void LinkedList::initData(QFile *file) {
    QTextStream in(file);
    QString result;
    QString gamme;
    std::list<Node*> gammeActuel;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList list = line.split(';');
        bool nodeValueAlreadyExist = false;
        bool gammeAlreadyExist = false;


        // On vérifie de manière arbitraire si on a au mojns 3 éléments dans la liste (1er : Gamme - 2ème : PDT - 3ème : Clé de réf)
        if(list.count() == 3) {
            // Define the node before attach it to the list "listNodes"
            Node *node = new Node;
            node->value = list[1] + list[2];
            node->gammes.push_back(list.first());
            node->gamme = list.first();

            if (m_listGammes.size() < 1) { // On ajoute un premier élément si les liste sont vides
                m_listGammes.push_back(list.first());
                m_listNodeValue.push_back(list[1] + list[2]);
            }

            for (auto &node : m_listNodeValue) { //On vérifie si la combinaison PDT + CLé existe déjà (Elimination des doublons)
                if(node == (list[1] + list[2]))
                    nodeValueAlreadyExist = true;
            }

            if(!nodeValueAlreadyExist) // Si elle n'existe pas déjà on l'ajoute à la liste
                m_listNodeValue.push_back(list[1] + list[2]);


            for (auto &gammesListed : m_listGammes) { //On vérifie si la gamme existe déjà (Elimination des doublons)
                if (list.first() == gammesListed) {
                    gammeAlreadyExist = true;
                }
            }

            if(!gammeAlreadyExist) {// Si elle n'existe pas déjà on l'ajoute à la liste
                m_listGammes.push_back(list.first());
                std::vector<std::list<Node*>> a_listNodes = listNodes();
                a_listNodes.push_back(gammeActuel);
                listNodes(a_listNodes);
                gammeActuel.clear();
            }


            if (gammeActuel.size() > 0) { // On fait pointer "before" vers le node qui le succède (1er chainage du graph)
                if (gammeActuel.back()->gamme == node->gamme)
                    gammeActuel.back()->next.push_back(node);
            }

            gammeActuel.push_back(node);
        }
        m_nbElements++;
    }
    std::vector<std::list<Node*>> a_listNodes = listNodes();
    a_listNodes.push_back(gammeActuel);
    listNodes(a_listNodes);
    gammeActuel.clear();
}

QString LinkedList::displayInitData() {
    QString result;

    result += "ListNodes size : " + QString::number(listNodes().size()) + "\n";
    for(auto &array : listNodes()) {
        result += "array : " + QString::number(array.size()) + "\n";
        for (auto &node : array) {
            if (!node->next.empty()) {
                for (auto &nextNode : node->next) {
                    if (!nextNode->gammes.empty()){

                        result += QString("value : ") + node->value.toUtf8().constData()
                                + QString(" / gamme : ") + node->gammes.back().toUtf8().constData()
                                + QString(" // next->value : ") + nextNode->value.toUtf8().constData()
                                + QString(" next->gamme : ")  + nextNode->gammes.front().toUtf8().constData() + QString("\n");

                    } else {
                        result += QString("value : ") + node->value.toUtf8().constData()
                                + QString(" / gamme : ") + node->gammes.back().toUtf8().constData() + QString("\n");
                    }
                }
            }
        }
    }

    result += "Nombre de gammes :  " + QString::number(m_listGammes.size()) + "\n";
    result += "Nombre d'opérations : " + QString::number(m_nbElements) + "\n";
    result += "Nombre d'opérations (sans doublon) : " + QString::number(m_listNodeValue.size()) + "\n";
    return result;
}

QString LinkedList::createGraph() {

    QString result= "";
    int i = 0;
    float weight = 1/listNodes().size();
    float tempWeight;
    std::vector<std::list<Node>> listBestPathByOp; // les meilleures chemin de chaque gammes trouvé à partir de chaque opération
    std::vector<std::list<Node*>> listBestPath; // les meilleures chemin de chaque gammes

    std::list<Node*> tempGragh1; //Premier Graph temporaire pour stocker temporairement les données lors des recherches des meilleures chemins
    std::list<Node*> tempGragh2; //Deuxième Graph temporaire pour stocker temporairement les données lors des recherches des meilleures chemins (peut-être possible de ne pas l'utiliser)

    std::list<Node*> tempGamme;

    unsigned int bestPath; // longueur du chemin meilleur la gamme
    std::vector<int> bestPathByOp; // Taille des meilleurs chemin par opération
    unsigned int tempPath; // Chemin temporaire pour manipulation des données
    unsigned int tempPath2;

    for (auto &gamme : listNodes()) {
        std::list<Node*> Gamme(gamme.begin(), gamme.end());
        bestPath = std::numeric_limits<int>::max(); // Reset bestPath
        tempPath = 0;
        tempWeight = weight/gamme.size();

        //Reset & Initialize listBestPathByOp
        listBestPathByOp.clear();
        Node emptyNode;
        std::list<Node> emptyList;
        emptyList.push_back(emptyNode);
        listBestPathByOp.push_back(emptyList);

        tempGragh1 = optimizedGraph(); // Copy du graph Optimisé dans la graph Temporaire;
        bestPathByOp.clear(); // Reset

        for (auto &op : gamme) {
            if (tempGragh1.empty())
                tempGragh1.push_back(op);

            tempGamme.push_back(op);

            tempPath2 = tempPath;

            result += QString::number(i) + "/ Create graph - OP : valeur : " + op->value.toUtf8().constData() + " | gamme : " + op->gammes.back().toUtf8().constData() + QString("\n");
            result += QString::number(i) + "/ algo_rec(&listBestPathByOp.back(), tempGamme(" + tempGamme.back()->value.toUtf8() + ", " + tempGamme.back()->gammes.back().toUtf8() +
                    "), tempGraph(" + tempGragh1.back()->value.toUtf8() + ", " + tempGragh1.back()->gammes.back().toUtf8()  + QString("\n");

            tempPath = algo_rec(&listBestPathByOp.back(), tempGamme, tempGragh1, tempPath);

            if(gamme.size() == tempPath) {
                listBestPathByOp.pop_back();
                for (auto &tempOP : gamme) {
                    std::list<Node> opList;
                    opList.push_back(*tempOP);
                    listBestPathByOp.push_back(opList);
                }
            }

            result += QString::number(i) + "/ taille du chemin : " + QString::number(tempPath);
            if (tempPath < bestPath) {
                bestPath = tempPath;
            }
            tempGamme.pop_back();
            tempPath = tempPath2;
            tempPath++;
        }

        // Initialiser arbitrairement l'optimizedGraph avec la première gamme. Car nécessairement cette gamme réprésentera un des chemins du Graph.
        // Faire fonction récursives pour parcourir tous les élements de tous les meilleures chemins trouvés en incrément temps le chemin à chaque fois si les "next" correspondent
        // et sinon ajouter l'élément n'existant pas .

        for (auto &tempOptimized : listBestPathByOp) {
            if (bestPath == tempOptimized.size())
                for (auto &tempNode : tempOptimized) {
                    if (optimizedGraph().size() > 0)
                        optimizedGraph().push_back(&tempNode);

                    for (auto &tempNode2 : optimizedGraph()) {
                        if (tempNode.value == tempNode2->value) {

                        }

                    }
                }

        }

    }

    return result;
}

int LinkedList::algo_rec(std::list<Node>* t_optimzed, std::list<Node*> t_gamme, std::list<Node*> t_graph, int t_path) {
    int graphPath = t_path;
    int gammePath = t_path;
    std::list<Node*> tempGamme = t_gamme;
    std::list<Node*> tempGragh2 = t_graph;
    for (auto &op : t_gamme) {
        for (auto &opGraph : t_graph) {
            if(op->value == opGraph->value) {
                t_path++;
//                std::list<Node*> delete1, delete2;

                if(opGraph->next.size() > 0)
                    graphPath = algo_rec(t_optimzed, opGraph->next, op->next, t_path);
//                    graphPath = algo_rec(&delete1, opGraph->next, op->next, t_path);

                if(op->next.size() > 0)
                    gammePath = algo_rec(t_optimzed, op->next, opGraph->next, t_path);
//                    gammePath = algo_rec(&delete2, op->next, opGraph->next, t_path);

//                delete1 . remove_if ( deleteAll );
//                delete2 . remove_if ( deleteAll );

                if(op->next.size() > 0 && opGraph->next.size() > 0)
                    return (gammePath <= graphPath) ? algo_rec(t_optimzed, op->next, opGraph->next, t_path) : algo_rec(t_optimzed, opGraph->next, op->next, t_path);
                else {
                    return t_path;
                }
            } else {
                if (t_optimzed->size() > 0)
                    t_optimzed->front().next.push_back(opGraph);

                t_optimzed->push_front(*opGraph);
                return algo_rec(t_optimzed, t_gamme, opGraph->next, t_path);
            }
        }
        if (t_optimzed->size() > 0)
            t_optimzed->front().next.push_back(op);

        t_optimzed->push_front(*op);
    }

    return t_path;
}






void LinkedList::add_elements(int t_nbElements)
{
    nbElements(t_nbElements + nbElements());
}

void LinkedList::add_gammes(int t_nbGammes)
{
    nbGammes(t_nbGammes + nbGammes());
}
