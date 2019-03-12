#include "linkedlist.h"
#include <limits>

LinkedList::LinkedList()
{
    m_nbElements = 0;
    m_nbGammes = 0;
}

void LinkedList::initData(QFile *file) {
    int sizeGamme = 0;
    QTextStream in(file);
    QString result;
    QString gamme;
    std::list<Node*> gammeActuel;
    Node* before = new Node(); // Permet d'enregistrer pendant une itération le node précédent pour l'intéroger

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
            node->weight = 0;
            node->increment = 1;

            // Incrémentation de la liste de la taille des gammes pour calculer le poids.

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

            if (m_listGammes.size() < 0) { // On ajoute un premier élément si les liste sont vides
                m_listGammes.push_back(list.first());
                m_listNodeValue.push_back(list[1] + list[2]);
                gammeAlreadyExist = false;
            }

            if (gammeActuel.size() > 0) { // On fait pointer "next" vers le node qui le succède (1er chainage du graph)
                if (gammeActuel.back()->gamme == node->gamme)
                    gammeActuel.back()->next.push_back(node);
                else {
                    gammeActuel.back()->next.push_back(new Node());
                }
            }

            if(!gammeAlreadyExist) {// Si elle n'existe pas déjà on l'ajoute à la liste
                m_listGammes.push_back(list.first());
                if (before->next.empty() || before->next.back()->value.isEmpty()) { // Si le next du node précédent est vide, alors on ajoute le node actuel à la liste des Node de tête
                    std::vector<Node*> tempNodeHeads = NodesHeads();
                    tempNodeHeads.push_back(node);
                    NodesHeads(tempNodeHeads);
                    m_sizeGammes.push_back(0);
                    sizeGamme = 0;
                    m_defaultWeight++;
                }

                gammeActuel.clear();
            }

            sizeGamme++;
            m_sizeGammes.back() = sizeGamme;

            gammeActuel.push_back(node);
            before = node;
        }
        m_nbElements++;

    }
    gammeActuel.clear();
}

QString LinkedList::displayInitData() {
    QString result;
    std::list<Node*> tempList;

    result += "ListNodes size : " + QString::number(NodesHeads().size()) + "\n";
    for(auto heaNode : NodesHeads()) {
        if (tempList.size() > 0)
            tempList.pop_back();

        tempList.push_back(heaNode);
        //        result += "array : " + QString::number(array.size()) + "\n"
        while (tempList.back()->value != "") {
            if (tempList.back()->next.size() < 1)
                tempList.back()->value = "";
            for (auto node : tempList) {
                for (std::list<Node*>::iterator it = node->next.begin(); it != node->next.end(); ++it) {
                    if (!(*it)->gamme.isEmpty()){
                        result += QString("value : ") + node->value.toUtf8().constData()
                                + QString(" / gamme : ") + node->gammes.back().toUtf8().constData()
                                + QString(" // next->value : ") + (*it)->value.toUtf8().constData()
                                + QString(" next->gamme : ")  +(*it)->gammes.front().toUtf8().constData() + QString("\n");

                    } else {
                        result += QString("value : ") + node->value.toUtf8().constData()
                                + QString(" / gamme : ") + node->gammes.back().toUtf8().constData() + QString("\n");
                    }

                    if ((it != node->next.end()) && (nextIter(it) == node->next.end()))
                    {
                        tempList = node->next;
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
    std::list<int>::iterator mostOccurence;
    Node TempGamme;
    Node TempGamme2;
    int i;
    int j = 0;
    int numberOfGammeToIncrement;
    float tempWeight;

    m_optimizedGraphHead.push_back(copieWithoutNextAndIncrement( NodesHeads().front()));
    for (auto &gamme : NodesHeads()) {
        while (!gamme->next.empty()) {


            algo_rec(gamme, m_optimizedGraphHead, m_optimizedGraphHead, 0, 0, 0);

            mostOccurence = std::max_element(m_occurence.begin(), m_occurence.end());
            numberOfGammeToIncrement= 0;

            // On compte le nombre gamme à incrémenter dans optimized grah pour déterminer le poids de l'incrément
            for (std::list<int>::iterator it=m_occurence.begin(); it != m_occurence.end(); ++it) {
                if (it == mostOccurence)
                    numberOfGammeToIncrement++;
            }


            tempWeight = 1/ (m_defaultWeight * static_cast< float >(numberOfGammeToIncrement) * static_cast< float >(m_sizeGammes[j]));
            i = 0;
            for (std::list<int>::iterator it=m_occurence.begin(); it != m_occurence.end(); ++it) {
                if ((*it) == (*mostOccurence))  {
                    std::list<Node*>::iterator it_gamme = m_listTempGamme.begin();
                    std::advance(it_gamme, i);

                    if(TempGamme.value == "") {
                        addgamme(*it_gamme, new Node(), m_optimizedGraphHead, tempWeight);
                        TempGamme = *copieWithoutNext(gamme);
                    }
                    else {
                        TempGamme2 = TempGamme;

                        /*
                         *
                         *
                         * Lors de la copie de TempGamme dans TempGamme2 le premier Node contenu dans TempGamme va
                         * bien créer un nouveau Node avec les mêmes attributs mais considéré comme un Node différent.
                         * Par contre si TempGamme à des nexts, TempGamme2 aura les mêmes nexts copiés.
                         * Donc si l'on rajoute ensuite des nexts au next de TempGamme2, ceux-ci vont aussi être ajouté pour
                         * TempGamme. Il font don ccréer un fonction de copy pour chaque next de TempGamme, créer une copie.
                         *
                         *
                         *
                         *
                         *
                         *
                         * */
                        getLast(&TempGamme2)->next.push_back((*it_gamme));
                        addgamme(&TempGamme2, new Node(), m_optimizedGraphHead, tempWeight);
                        getLast(&TempGamme)->next.push_back(copieWithoutNext(gamme));

                    }

                }
                i++;
            }


            m_listTempGamme.clear();
            m_occurence.clear();


            gamme = gamme->next.back();
        }
        j++;
    }
    return "ok";
}

int LinkedList::addgamme(Node* t_gamme, Node* t_previousNode, std::list<Node*> t_graph, float t_tempWeight)
{
    Node* previousNode;
    t_gamme->weight = static_cast<double>(t_tempWeight);

    while (t_gamme->value != "") {
        if (m_listProcess.find(t_gamme->value) != m_listProcess.end() && m_listProcess.at(t_gamme->value) >= t_gamme->increment){ //On Vérifie si le Proces existe déjà (Valeur + incrément)
            for (auto node : t_graph) {
                if (node->value == t_gamme->value && node->increment == t_gamme->increment) {
                    node->weight += static_cast<double>(t_tempWeight);
                    previousNode = node;
                    if (!t_gamme->next.empty())
                        return addgamme(t_gamme->next.back(), node, node->next, t_tempWeight);
                    else {
                        return 1;
                    }
                } else {
                    if (!node->next.empty())
                        return LinkedList::addgamme(t_gamme, node, node->next, t_tempWeight);
                    else {
                        return 1;
                    }
                }
            }
        } else {
            if (t_previousNode->value == "") {
                m_optimizedGraphHead.push_back(copieWithoutNextAndIncrement(t_gamme));
                previousNode = m_optimizedGraphHead.back();

            } else {
                t_previousNode->next.push_back(copieWithoutNextAndIncrement(t_gamme));
                previousNode = t_previousNode->next.back();
            }
        }
        if (!t_gamme->next.empty())
            return addgamme(t_gamme->next.back(), previousNode, m_optimizedGraphHead, t_tempWeight);
        else
            return 1;
    }

    return 1;
}


int LinkedList::algo_rec(Node *t_nodeGamme, std::list<Node *> t_listPreviousNextNode, std::list<Node *> t_listNextNode, unsigned int t_occurence, int t_check, unsigned int t_try)
{
    bool checkExist;

    while (!t_nodeGamme->next.empty()) { // Vérifie si l'élément de la gamme à une suite
        checkExist = false;

        for (auto nextNode : t_listNextNode) // Pour tous les éléments suivants de l'élément en cours du Graph
        {
            if (nextNode->value == t_nodeGamme->value) { //Si le graph et la gamme correspondent
                if (!m_occurence.size() > t_try) { // t_try correspond au nombre de chemin rencontre
                    m_listTempGamme.push_back(copieWithoutNext(nextNode)); // On ajout à la Tempgamme l'élement de la gamme sans suite pour le moment
                    m_occurence.push_back(t_occurence +1);
                } else {
                    std::list<Node*>::iterator it_nextNode = std::next(m_listTempGamme.begin(), t_try);
                    getLast(*it_nextNode)->next.push_back(copieWithoutNext(nextNode));
                    std::list<int>::iterator it_occurrence = std::next(m_occurence.begin() , t_try);
                    (*it_occurrence)++;
                    t_occurence = *it_occurrence;
                }

                return algo_rec(t_nodeGamme->next.back(), nextNode->next, nextNode->next, t_occurence, true, t_try); // On renvoie le prochain élément de la gamme, et les prochains éléments.

            } else if (!nextNode->next.empty() && nextNode->value != t_nodeGamme->value) {
                return algo_rec(t_nodeGamme, t_listPreviousNextNode, nextNode->next, t_occurence, t_check, t_try);
            } else {
                if (t_check) {
                    if (m_occurence.size() > t_try) {
                        std::list<Node*>::iterator it_nextNode = std::next(m_listTempGamme.begin(), t_try);
                        getLast(*it_nextNode)->next.push_back(copieWithoutNextAddIncrement(t_nodeGamme));
                    } else {
                        std::list<Node*>::iterator it_nextNode = std::next(m_listTempGamme.begin(), t_try);
                        getLast(*it_nextNode)->next.push_back(copieWithoutNext(nextNode));
                        std::list<int>::iterator it_occurrence = std::next(m_occurence.begin() , t_try);
                        (*it_occurrence)++;
                        t_occurence = *it_occurrence;
                    }

                    return algo_rec(t_nodeGamme->next.back(), t_listPreviousNextNode, t_listPreviousNextNode, t_occurence, t_check, t_try);
                }
            }
            m_listTempGamme.push_back(copieWithoutNext(nextNode));
            m_occurence.push_back(t_occurence);
            t_try++;

        }


        if(checkExist && t_nodeGamme->next.empty())
            return t_occurence;
        else {
            std::list<Node*>::iterator it_nextNode = std::next(m_listTempGamme.begin(), t_try);
            getLast(*it_nextNode)->next.push_back(copieWithoutNext(t_nodeGamme));

            return algo_rec(t_nodeGamme->next.back(), t_listPreviousNextNode, t_listPreviousNextNode, t_occurence, t_check, t_try);
        }
    }
    return 1;
}

void LinkedList::add_elements(int t_nbElements)
{
    nbElements(t_nbElements + nbElements());
}

void LinkedList::add_gammes(int t_nbGammes)
{
    nbGammes(t_nbGammes + nbGammes());
}

Node* LinkedList::getLast(Node* t_node) {
    if (!t_node->next.empty())
        t_node = getLast(t_node->next.back());

    return t_node;
}

Node* LinkedList::copieWithoutNext(Node *t_node) {
    Node* node = new Node();
    node->gamme = t_node->gamme;
    node->value = t_node->value;
    node->weight = t_node->weight;
    node->branchs = t_node->branchs;
    node->increment = t_node->increment;

    return node;
}

Node* LinkedList::copieWithoutNextAndIncrement(Node *t_node) {
    Node* node = new Node();
    node->gamme = t_node->gamme;
    node->value = t_node->value;
    node->weight = t_node->weight;
    node->branchs = t_node->branchs;

    if (m_listProcess.find(node->value) == m_listProcess.end() ) {
        m_listProcess.insert(std::pair<QString, int>(node->value, 1));
        node->increment = 1;
    } else {
        m_listProcess[node->value] = m_listProcess[node->value] + 1;
        node->increment = m_listProcess[node->value];
    }

    return node;
}

Node* LinkedList::copieWithoutNextAddIncrement(Node *t_node) {
    Node* node = new Node();
    node->gamme = t_node->gamme;
    node->value = t_node->value;
    node->weight = t_node->weight;
    node->branchs = t_node->branchs;

    if ( m_listProcess.find(node->value) == m_listProcess.end() ) {
        node->increment = 1;
    } else {
        node->increment = m_listProcess[node->value] + 1;
    }

    return node;
}

std::list<Node*> LinkedList::listedGamme(Node *t_nodeHead) {
    std::list<Node*> list_node;

    if (!t_nodeHead->next.empty())
        list_node =  listedGamme(t_nodeHead->next.back());

    list_node.push_back(copieWithoutNext(t_nodeHead));

    return list_node;

}
