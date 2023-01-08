#ifndef NETWORKMANAGER_GRAPH_H
#define NETWORKMANAGER_GRAPH_H


#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include "Airline.h"
#include "Airport.h"

/**
 * \brief Classe Graph
 *
 * Classe usada para representar os voos
 */
class Graph {
private:
    /**
     * \brief Struct utilizada para representar uma aresta do grafo.
     *
     * Uma aresta do grafo é um voo com um determinado destino e companhia aérea.
     */
    struct Edge{
        int dest;
        const Airline* airline;
    };

    /**
     * \brief Struct utilizado para representar um vértice do grafo.
     *
     * Um vértice do grafo é um aeroporto.
     */
    struct Node{
        list<Edge> adj;
        bool visited;

        int dist;
        vector<int> path;


        int num;
        int low;
        bool inStack;
        bool isAP;
    };

    int n;
    vector<Node> nodes;

public:
    /**
     * Construtor default da classe Graph
     */
    Graph();
    /**
     * Construtor da classe Graph
     * @param num Número de nodes/vértices do grafo
     */
    Graph(int num);

    /**
     * Caso seja fornecido um voo válido, este é adicionado ao grafo
     * @param src Aeroporto de origem
     * @param dest Aeroporto de Destino
     * @param airline Companhia Aérea
     */
    void addFlight(int src, int dest, const Airline* airline);

    /**
     * \brief Realiza uma pesquisa em largura (Breadth-first search) respeitando as preferências do utilizador.
     * Para cada node visitado regista a distância (número de nodes percorridos até lá chegar) e o path (node(s) a partir dos quais se atingiu o node atual)
     *
     * Complexidade: O(|V|+|E|)
     * @param q Nodes a partir dos quais se inicia o bfs
     * @param preferences Preferências do utilizador relativas às Airlines
     */

    void bfs(queue<int> q, unordered_set<string> preferences);

    /**
     * \brief Realiza uma pesquisa em profundidade (Depth-first search) para encontrar os pontos de articulação do grafo.
     *
     * Complexidade: O(|V|+|E|)
     * @param v Node a partir do qual se inicia a pesquisa
     * @param S Stack para guardar quais os elementos que estão a ser pesquisados
     * @param index número da visita atual
     */
    void dfs_art(int v, stack<int> *S, int index);

    void dfs_cc(int v);

    /**
     * Define os campos dos Nodes do grafo adequadamente, de modo a que seja realizada uma pesquisa por pontos de articulação em todos os Nodes.
     * @return Vetor contendo pontos de articulação
     */
    vector<int> getGlobalArticulationPoints();

    /**
     * Define os campos dos Nodes do grafo adequadamente, de modo a que seja realizada uma pesquisa por pontos de articulação nos Nodes de um determinado continente.
     * @param map Map em que a chave é o número do node e o valor o aeroporto correspondente
     * @param countries Unordered set dos países do continente
     * @return Vetor contendo pontos de articulação no continente
     */
    vector<int> getContinentalArticulationPoints(unordered_map<int, const Airport*> map, unordered_set<string> countries);

    /**
     * Define os campos dos Nodes do grafo adequadamente, de modo a que seja realizada uma pesquisa por pontos de articulação nos Nodes de um determinado país.
     * @param map Map em que a chave é o número do node e o valor o aeroporto correspondente
     * @param countries País a fazer a pesquisa
     * @return Vetor contendo pontos de articulação no país
     */
    vector<int> getCountryArticulationPoints(unordered_map<int, const Airport*> map, string country);

    /**
     * \brief Determina qual a distância de um nó inicial até ao nó mais disntante de si
     *
     * Complexidade: O(|V|+|E|)
     * @param u Nó inicial
     * @return Valor da distância de u até o nó mais distante de si
     */
    int getMaxDistance(int u, unordered_map<int, const Airport *> map = {}, unordered_set<std::string> countries = {});

    /**
     * \brief Determina o diâmetro do grafo, isto é, a maior distância entre dois nós
     *
     * Complexidade O(|V|*(|V|+|E|))
     * @return Diâmetro do grafo
     */
    int getGlobalDiameter();

    int getContinentalDiameter(unordered_map<int, const Airport*> map, unordered_set<string> countries);

    int getCountryDiameter(unordered_map<int, const Airport*> map, string country);


    int getGlobalConnectedComponents();

    int getContinentalConnectedComponents(unordered_map<int, const Airport*> map, unordered_set<string> countries);

    int getCountryConnectedComponents(unordered_map<int, const Airport*> map, string country);

    /**
     * Getter dos nodes do grafo
     * @return Nodes do grafo
     */
    vector<Node> getNodes();
};



#endif //NETWORKMANAGER_GRAPH_H
