#ifndef NODE_H
#define NODE_H

#include <QString>
#include <vector>


class node
{

private:
    node* m_before;
    QString m_value;
    double m_weight;
    std::vector<int> m_branchs;
    std::vector<QString> m_gammes;
public:
    node();

    node* before() const { return m_before; }
    void optimizedGraph(std::list<node> t_optimizedGraph) { m_optimizedGraph = std::move(t_optimizedGraph); }
};

#endif // NODE_H
