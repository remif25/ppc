//QString LinkedList::createGraph() {

//    std::vector<int>::iterator it_sizeGammes = sizeGammes().begin(); // Itérateur pour récupérer la taille des gammes
//    std::vector<int>::const_iterator it_bestPath;
//    std::list<Node*>::iterator it_nextNode;
//    std::list<Node*>::iterator it_OptimizedgraphTemp;
//    QString result= "";
//    float weight = 1/NodesHeads().size(); //Poids moyen de chaque gamme
//    float tempWeight;
//    int numberOfOptimizedgraph; //Nombre de graphe optimisé trouvé pour une gamme : permet de pouvoir calculer le poids à incrémenter à optimizedGraph
//    std::vector<Node*> listBestPath; // les meilleures chemin de chaque gammes
//    std::vector<int> bestPathByOp; // Taille des meilleurs chemin par opération
//    std::list<Node*> tempGragh; //Premier Graph temporaire pour stocker temporairement les données lors des recherches des meilleures chemins
//    std::list<Node*> tempGamme2;
//    unsigned int bestPath; // longueur du chemin meilleur la gamme
//    int path;
//    int tempPath;
//    int branch; // Numéro de la branche actuel
//    bool checkNode; //Vérifie si le noeud du graph optimisé de la gamme existe dans le Graph optimisé. S'il n'existe pas, on ajoute ce Node comme NodeHead du Graph
//    bool checkIncrement;  // Vérifie que Optimizedgraph n'est pas imcrémenté n-fois par le même graphe optimisé
//    bool checkAdvance; // Vérifie si lors de l'incrémentation de l'OptimizedGraph si l'on a déjà parcouru des Nodes


//    m_optimizedGraphHead.push_back(copieWithoutNext(NodesHeads().front())); // On met arbitrairement un premier élément dans le Graph
//    m_listNodeValueOptimizedGraph.push_back(m_optimizedGraphHead.back()->value);

//    for (auto &gamme : NodesHeads()) {
//        bestPath = std::numeric_limits<int>::max(); // Reset bestPath
//        float tempWeight = 0; // Initialisation pour chaque gamme
//        int numberOfOptimizedgraph = 0; // Initialisation pour chaque gamme
//        bestPathByOp.clear(); // Reset pour chaque gamme

//        it_OptimizedgraphTemp = m_optimizedGraphHead.begin();

//        while (it_OptimizedgraphTemp != m_optimizedGraphHead.end()) {
//            path = 0;
//            while (!gamme->next.empty()) {


//                it_Optimizedgraph = it_OptimizedgraphTemp;
//                algo_rec(gamme,gamme->next, gamme->next, 0, 0, 0);
//                m_optimizedGraphHeadbyGamme.push_back(m_tempGamme.back());
//                m_tempGamme.clear(); // Reset pour chaque gamme

//                bestPathByOp.push_back(tempPath);
//                path++;

//                if (tempGamme2.empty())
//                    tempGamme2.push_back(copieWithoutNext(gamme));
//                else
//                    (*getLast(&tempGamme2.back()))->next.push_back(copieWithoutNext(gamme));

//                m_tempGamme.push_back(tempGamme2.back());
//                gamme = gamme->next.back();


//                if (tempPath > 0 && tempPath <= bestPath)
//                    bestPath = tempPath;
//            }
//            it_OptimizedgraphTemp++;
//        }
//        it_bestPath = bestPathByOp.begin();

//        for (auto j : bestPathByOp) {
//            if (j >0 && j == bestPath)
//                numberOfOptimizedgraph++;
//        }

//        tempWeight = weight/ static_cast< float > (numberOfOptimizedgraph); // Poids de graphe optimisé
//        tempGragh =optimizedGraphH(); // a supprimer

//        while(it_bestPath != bestPathByOp.end()) {
//            for (auto nodeHeadGamme : optimizedGraphHbyG()) {
//                if (*it_bestPath <= bestPath && *it_bestPath > 0) {
//                    m_tempGamme = listedGamme(nodeHeadGamme);
//                    checkAdvance = false;
//                    for (auto nodeGamme : m_tempGamme) {
//                        checkIncrement = false;
//                        for (auto &nodeHeadGraph : optimizedGraphH()) {
//                            if (nodeGamme->value == nodeHeadGraph->value && !checkIncrement) {

//                                *it_Optimizedgraph = nodeHeadGraph;
//                                (*it_Optimizedgraph)->gamme = nodeGamme->gamme;
//                                (*it_Optimizedgraph)->weight += tempWeight;
//                                (*it_Optimizedgraph)->branchs.push_back(branch);
//                                checkIncrement = true;
//                            } else {
//                                if (!checkIncrement) {
//                                    if (!checkAdvance) // Si on a n'a pas encore parcourue optimizedGraph
//                                        it_nextNode = nodeHeadGraph->next.begin();
//                                    else // Si on est avancé dans le pacours de optimizedGraph
//                                        *it_nextNode = *it_Optimizedgraph;

//                                    while (it_nextNode != nodeHeadGraph->next.end()) {
//                                        if ((*it_nextNode)->value == nodeGamme->value && !checkAdvance){
//                                            (*it_nextNode)->gamme = nodeGamme->gamme;
//                                            (*it_nextNode)->weight += tempWeight;
//                                            (*it_nextNode)->branchs.push_back(branch);
//                                            *it_Optimizedgraph = *it_nextNode;
//                                            checkAdvance = true;
//                                            checkIncrement = true;
//                                        }

//                                        /*
//                                         *
//                                         * Manque l'ajout des nodes lorsqu'ils ne sont pas dans OptimizedGraph
//                                         *
//                                         * */

//                                        it_nextNode++;

//                                        if (it_nextNode == nodeHeadGraph->next.end()) {
//                                            it_nextNode--;
//                                            if(!(*it_nextNode)->next.empty())
//                                                it_nextNode = (*it_nextNode)->next.begin();
//                                            else
//                                                it_nextNode++;
//                                        }

//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//                it_bestPath++;
//            }
//        }
//    }

//    return result;
//}
