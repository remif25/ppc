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

struct Node {
    std::list<Node*> next;
    QString value;
    QString gamme;
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
    int algo_rec(std::list<Node>::iterator* it,Node* t_nodeGamme, Node* t_nodeGraph, int t_path);
    static bool deleteAll( Node * theElement ) { delete theElement; return true; }
    void incrementPath(std::list<Node*>::iterator *it_OptimizedGraph , std::list<Node*>::iterator* t_it_tempPath, double t_weight);

private:
    std::vector<Node*> m_NodesHeads;
    std::vector<int> m_sizeGammes;
    std::list<Node*> m_optimizedGraph_head;
    int m_nbElements;
    int m_nbGammes;
    float m_defaultWeight;
    std::list<Node*> m_bestPath;
    std::vector<QString> m_listNodeValue;
    std::vector<QString> m_listGammes;

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

    std::list<Node*> optimizedGraphH() const { return m_optimizedGraph_head; }
    void optimizedGraphH(std::list<Node*> t_optimizedGraph) { m_optimizedGraph_head = std::move(t_optimizedGraph); }

    int push_back_node(Node &node);
    int add_node(struct Node *node, struct Node *previous);
};

#endif // LINKEDLIST_H
