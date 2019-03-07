/*
 *
 *
 *
 *
 *
 *
 *
 *
 * */



#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <QString>
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <QTextStream>
#include <QFile>
#include <string>
#include <array>
#include <map>

struct Node {
    std::list<Node*> next;
    QString value;
    QString gamme;
    int increment;
    double weight;
    std::vector<int> branchs;
    std::vector<QString> gammes;
};

template <typename Iter>
Iter nextIter(Iter iter)
{
    return ++iter;
}

class LinkedList
{
public:
    LinkedList();
    void initData(QFile *file);
    QString displayInitData();
    QString createGraph();
    std::list<Node*> listedGamme(Node* t_nodeHead); //Uniquement pour les gammes
    Node* getLast(Node* t_node); //Uniquement pour les gammes
    Node* copieWithoutNext(Node* t_nodeGamme);
    Node* copieWithoutNextAndIncrement(Node* t_nodeGamme);

    /*
     *
     * La fonction renvoie une valeur négative s'il n'existe aucun élément en commun entre le Graph et la Gamme
     * t_check : Vérifie s'il y a au moins un élément en commun entre la gamme et le graph
     * t_test : Vérifie si l'on parcours l'algo_rec pour trouver le chemin le plus court ou s'il a été trouvé.
     *
     *
     * */
    int buildGraph(Node* t_previousNode, Node* t_node);
    void buildGraph2(Node* t_node);
    Node* getNodeByValue(QString t_value, Node* t_node); // cherche à partir du noeud indiqué dans le graphOptimized et renvoie le noeud avec la même valeur
    int algo_rec(Node* t_nodeGamme, std::list<Node*> t_listPreviousNextNode, std::list<Node*> t_listNextNode, int t_occurence, int t_check, int t_try);
    static bool deleteAll( Node * theElement ) { delete theElement; return true; }
    int addgamme(Node* t_gamme, Node* t_previousNode, std::list<Node*> t_graph, float t_tempWeight);
    void incrementPath(std::list<Node*>::iterator *it_OptimizedGraph , std::list<Node*>::iterator* t_it_tempPath, double t_weight);

private:
    std::vector<Node*> m_NodesHeads;
    std::vector<int> m_sizeGammes;
    std::list<Node*> m_optimizedGraphHead;
    std::list<Node*>::iterator it_Optimizedgraph;
    std::list<Node*> m_optimizedGraphHeadbyGamme;
    int m_nbElements = 0;
    int m_nbGammes = 0;
    float m_defaultWeight = 0;
    std::list<Node*> m_bestPath;
    std::vector<QString> m_listNodeValue;
    std::vector<QString> m_listNodeValueOptimizedGraph;
    std::vector<int> m_listNodeIncrementOptimizedGraph;
    std::vector<QString> m_listGammes;
    std::list<Node*> m_listTempGamme;
    std::list<Node*> m_tempGamme;
    std::list<int> m_occurence;
    std::map<QString, int> m_listProcess;

    int nbElements() const { return m_nbElements; }
    void nbElements(int nb_element) {m_nbElements = std::move(nb_element);}
    void add_elements(int nb_element);

    int nbGammes() const { return m_nbGammes;}
    void nbGammes(int t_nbGammes) {m_nbGammes = std::move(t_nbGammes);}
    void add_gammes(int t_nbGammes);

    std::vector<QString> listNodeValue() const { return m_listNodeValue;}
    void listNodevalues(std::vector<QString> t_listNodeValues) {m_listNodeValue = std::move(t_listNodeValues);}

    std::vector<QString> listGammes() const { return m_listGammes;}
    void listGammes(std::vector<QString> t_listGammes) {m_listGammes = std::move(t_listGammes);}

    std::vector<Node*> NodesHeads() const { return m_NodesHeads; }
    void NodesHeads(std::vector<Node*> t_NodesHeads) { m_NodesHeads = std::move(t_NodesHeads); }

    std::list<Node*> optimizedGraphH() const { return m_optimizedGraphHead; }
    void optimizedGraphH(std::list<Node*> t_optimizedGraph) { m_optimizedGraphHead = std::move(t_optimizedGraph); }

    std::list<Node*> optimizedGraphHbyG() const { return m_optimizedGraphHeadbyGamme; }
    void optimizedGraphHbyG(std::list<Node*> t_optimizedGraph) { m_optimizedGraphHeadbyGamme = std::move(t_optimizedGraph); }

    std::vector<int> sizeGammes() const { return m_sizeGammes; }
    void sizeGammes(std::vector<int> t_sizeGammes) { m_sizeGammes = std::move(t_sizeGammes); }

    int push_back_node(Node &node);
    int add_node(struct Node *node, struct Node *previous);
};

#endif // LINKEDLIST_H
