/***************************************************************
 * The Graph Class
 * *************************************************************
 * This class is meant to provide the needed functions and
 * methods to be able to efficiently and effectively solve
 * multiple graphing and mapping problems. The main algorithm
 * implemented in this class is Dijkstra's which has both a
 * standard and a recursive implementation.
 * *************************************************************/

#ifndef GRAPH_H_
#define GRAPH_H_

#include <algorithm>
#include <iterator>
#include <QString>
#include <QVector>
#include <QDebug>
#include <stdio.h>
#include <limits.h>
#include <utility>

using namespace std;

/**
 * @brief The WeightEdge struct
 * Holds the details of one weighted edge
 */
struct WeightEdge
{
    QString connectedNode;
    int weight;

    bool operator < (const WeightEdge &node)
    {
        return (weight < node.weight);
    }
};

/**
 * @brief The Node struct
 * Holds the details of a single Node
 */
struct Node
{
    QString nodeName;
    int vertex;
    bool visited;
    QVector<WeightEdge> edges;
};

/**
 * @brief The DepthHolder struct
 */
struct DepthHolder {
    int discoveryTotal;
    QVector<QString> depthList;
};

/**
 * @brief The Graph class
 *
 * The graph class handles all of the functions and data related
 * to the graphing function (finding shortest routes, most efficient, etc) for
 * the NFL program
 */
class Graph {
public:

    Graph();
    ~Graph();

    // Mutators
    void AddEdge(QString nodeFrom, QString nodeTo, int edgeWeight);
    void AddNode(QString nodeName);
    void SetMatrix();

    // Accessors
    bool isConnected(QString nodeFrom, QString nodeTo);
    bool isNode(QString nodeName);
    int GetWeight(QString nodeFrom, QString nodeTo);
    int GetDistance(){return distance;}
    int GetTotalNodes(){return totalNodes;}
    int GetVertex(QString nodeName);
    QString GetNodeName(int vertex);
    int* GetVertices();
    QVector<Node> GetNodes(){return nodes;}
    QVector<QString> GetVisitedNodes(){return visitedNodes;}

    // Traversals
    void DFS(QString nodeName, QVector<QString> &stadiums);
    void BFS(QString nodeName, QVector<QString> &stadiums);
    int PrimMST();
    QVector<int> Dijkstra(int sourceVertex, QVector<QString> &stadiums);
    int PerformCompleteDijkstra(int sourceVertex, int baseCase, QVector<QString> &stadiums);
    int PerformFromToDijkstra(int fromVertex, int toVertex);

private:

    int totalNodes; //total number of nodes
    int distance;   //distances between two nodes
    int MAX;        //capitilized even though it's not a constant
    int vertices[]; //array to store verticies during BFS
    int edgeVertices[]; //the edge verticies calculated store in this array
    int **matrix;       //matrix pointer
    QVector<QString> visitedNodes;
    QVector<Node> nodes;
    QVector<WeightEdge> sortedIncidentEdges(QString nodeName);
    bool visited[]; //the nodes that will have been visited during calculations

    // Helper Functions
    Node GetNodeFromName(QString nodeName);
    bool isVisited(QString nodeName);
    void dfsUtil(Node node, QVector<QString> &stadiums);
    int minKey(int key[], bool mstSet[]);
    int minDistance(QVector<int> distances, bool sptSet[]);
    void DijkstraRecursive(int sourceVertex, int baseCase, QVector<QString> &stadiums);
};



#endif /* GRAPH_H_ */
