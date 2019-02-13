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
    struct Node* before;
    QString value;
    QString gamme;
    double weight;
    std::vector<int> branchs;
    std::vector<QString> gammes;
};

class LinkedList
{
public:
    LinkedList();
    LinkedList(QFile* file);
    QString displayData(QFile *file);

private:
    std::vector<Node*> m_listNodes;
    std::list<Node> m_optimizedGraph;
    int m_nbElements;
    int m_nbGammes;
    float m_defaultWeight;
    std::list<Node> m_bestPath;
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

    std::vector<Node*> listNodes() const { return m_listNodes; }
    void listNodes(std::vector<Node*> t_listNodes) { m_listNodes = std::move(t_listNodes); }

    std::list<Node> optimizedGraph() const { return m_optimizedGraph; }
    void optimizedGraph(std::list<Node> t_optimizedGraph) { m_optimizedGraph = std::move(t_optimizedGraph); }

    int push_back_node(Node &node);
    int add_node(struct Node *node, struct Node *previous);
};

#endif // LINKEDLIST_H
