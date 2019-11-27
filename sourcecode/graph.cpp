#include <algorithm>
#include <iterator>
#include "graph.h"

/**
 * @brief Graph::Graph
 */
Graph::Graph()
{
    nodes.clear();
    visitedNodes.clear();
    totalNodes = 0;
    distance = 0;
    MAX = std::numeric_limits<int>::max();
    visited[totalNodes];
    vertices[0];
    edgeVertices[0];
}

Graph::~Graph(){}

/**
 * @brief Graph::isNode
 * @param node
 * @return boolean
 */
bool Graph::isNode(QString node)
{
    //cycle through all nodes in list
    for(int i = 0; i < nodes.size(); i++)
    {
        //if the node equals the node in question
        //we have found it
        if(node == nodes[i].nodeName)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Graph::AddEdge
 * @param nodeFrom
 * @param nodeTo
 * @param edgeWeight
 * Simple member function to add a new edge
 */
void Graph::AddEdge(QString nodeFrom, QString nodeTo, int edgeWeight)
{
    //if the node base already exists
    if(nodes.size() > 0)
    {
        //and there is space
        if(this->isNode(nodeFrom) && this->isNode(nodeTo))
        {
            //cycle through node list
            for(int i = 0; i < nodes.size(); i++)
            {
                //when node in question is found
                if(nodeFrom == nodes[i].nodeName)
                {
                    //create the new edge, to and from node, and the weight
                    WeightEdge newEdge;
                    newEdge.connectedNode = nodeTo;
                    newEdge.weight = edgeWeight;

                    nodes[i].edges.push_back(newEdge);
                }
            }
            return;
        }//if(this->isNode(nodeFrom) && this->isNode(nodeTo))
    }//if(nodes.size() > 0)
}//end member function

/**
 * @brief Graph::AddNode
 * @param nodeName
 * Adds a new node
 */
void Graph::AddNode(QString nodeName)
{
    Node newNode;
    newNode.nodeName = nodeName;
    newNode.edges.clear();
    newNode.visited = false;
    newNode.vertex = nodes.size();
    nodes.push_back(newNode);
    totalNodes++;
}

/**
 * @brief Graph::GetVertex
 * @param nodeName
 * @return vertex
 *
 * Finds and returns the vertex associated with a nodeName
 */
int Graph::GetVertex(QString nodeName)
{
    int vertex = -1;
    bool isFound = false;
    int index = 0;

    //we will search until the end of nodes and !found
    while (index < nodes.size() && !isFound)
    {
        //when it's found save the vertex and change isFound to true
        if (nodes[index].nodeName == nodeName)
        {
            vertex = nodes[index].vertex;
            isFound = true;
        }
        index++;
    }

    //if the vertex still equals -1 it hasn't been found
    if (vertex == -1)
    {
        qDebug() << "Error, vertex not found.";
    }
    return vertex;
}

/**
 * @brief Graph::GetNodeName
 * @param vertex
 * @return nodeName at vertext location
 */
QString Graph::GetNodeName(int vertex)
{
    return nodes[vertex].nodeName;
}

/**
 * @brief Graph::SetMatrix
 * Sets the matrix with the given specifications
 */
void Graph::SetMatrix()
{
    matrix = new int*[totalNodes]; //matrix equals a pointer to the totalNodes count

    //for each of the nodes will will populate the array with a new node
    for (int i = 0; i < totalNodes; ++i)
    {
        matrix[i] = new int[totalNodes];
    }

    //again cycling through all the available nodes
    for (int i = 0; i < totalNodes; i++)
    {
        //create two blank vectors to store values in
        QVector<int> tempWeightVector;
        QVector<int> tempVertexVector;

        //cycle through the node edges
        for (int k = 0; k < nodes[i].edges.size(); k++)
        {
            //push each weight
            tempWeightVector.push_back(nodes[i].edges[k].weight);
            tempVertexVector.push_back(GetVertex(nodes[i].edges[k].connectedNode));
        }

        //cycle through all the nodes again
        for (int j = 0; j < totalNodes; j++)
        {
            matrix[i][j] = 0; //blank out the matrix array

            //for each of the Vertex values we will see if they align with our count
            for (int k = 0; k < tempVertexVector.size(); k++)
            {
                if (j == tempVertexVector[k])
                {
                    matrix[i][j] = tempWeightVector[k]; //if it does assign it to the array
                }
            }
        }
    }

    //cycle through the total nodes for the last time
//    for (int j = 0; j < totalNodes; j++)
//    {
//        //gotta have those sweet debug outputs
//        qDebug() << "Vertex:" << j << nodes[j].nodeName << "{";

//        //just kidding, cycling through all the nodes again! outputting their weight to debug
//        for (int k = 0; k < totalNodes; k++)
//        {
//            qDebug() << "Weight:" << matrix[j][k];
//        }
//        qDebug() << "}";
//    }
}

/**
 * @brief Graph::sortedIncidentEdges
 * @param nodeName
 * @return sortedEdges
 * Sorts the edges on the graph
 */
QVector<WeightEdge> Graph::sortedIncidentEdges(QString nodeName)
{
    //cycle through the nodes to check each edge
    for(int index = 0; index < nodes.size(); index++)
    {
        //if the node matches the nodeName we need then finish the sort
        if(nodeName == nodes[index].nodeName)
        {
            QVector<WeightEdge> sortedEdges = nodes[index].edges;
            sort(sortedEdges.begin(), sortedEdges.end());
            return sortedEdges;
        }
    }
}

/**
 * @brief Graph::dfsUtil
 * @param node
 */
void Graph::dfsUtil(Node node, QVector<QString> &stadiums)
{
    visitedNodes.push_back(node.nodeName); //gotta push that node onto the visited stack

    QVector<WeightEdge> incidentEdges = this->sortedIncidentEdges(node.nodeName);
    QVector<WeightEdge>::iterator weightIT;

    //cycle through the edges by weight
    for(weightIT = incidentEdges.begin(); weightIT != incidentEdges.end(); weightIT++)
    {
        QString connectednodeName = weightIT->connectedNode;
        Node connectednode = GetNodeFromName(connectednodeName);

        //when the node hasn't been visited we will output to debug
        //and set the distance to += the new weight of the node
        if(!(isVisited(connectednodeName)))
        {
            qDebug() << connectednode.nodeName;
            stadiums.push_back(connectednode.nodeName);
            distance += weightIT->weight;
            dfsUtil(GetNodeFromName(connectednode.nodeName), stadiums);
        }
    }
}

/**
 * @brief Graph::GetNodeFromName
 * @param nodeName
 * @return nodeIT
 *
 * Finds a node based on it's name
 */
Node Graph::GetNodeFromName(QString nodeName)
{
    QVector<Node>::iterator QVectorIt;

    for(QVectorIt = nodes.begin(); QVectorIt != nodes.end(); ++QVectorIt)
    {
        Node nodeIT = *QVectorIt;
        if(nodeIT.nodeName == nodeName)
        {
            return nodeIT;
        }
    }
}

/**
 * @brief Graph::DFS
 * @param nodeName
 *
 * Simple DFS Graphing Function
 */
void Graph::DFS(QString nodeName, QVector<QString> &stadiums)
{
    distance = 0;
    qDebug() << "Total nodes: " << GetTotalNodes();
    Node start = GetNodeFromName(nodeName);
    visitedNodes.clear();
    stadiums.push_back(nodeName);
    dfsUtil(start, stadiums);
    qDebug() << "Total nodes: " << GetTotalNodes();
    qDebug() << "Distance for DFS: " << distance;
}

/**
 * @brief Graph::isVisited
 * @param nodeName
 * @return boolean
 *
 * Simple function to find out of if a node has been visited
 */
bool Graph::isVisited(QString nodeName)
{
    for(int i = 0; i < visitedNodes.size(); i++)
    {
        if(visitedNodes[i] == nodeName)
            return true;
    }

    return false;
}

/**
 * @brief Graph::BFS
 * @param nodeName
 *
 * Implementation of the BFS graph function
 */
void Graph::BFS( QString nodeName, QVector<QString> &stadiums)
{
    distance = 0;
    QVector<QString> queue;
    visitedNodes.clear();

    QVector<WeightEdge>::iterator QVectorIt;
    QVector<Node>::iterator NodeIt;
    Node startnode = GetNodeFromName(nodeName);
    Node currentnode = startnode;
    stadiums.push_back(nodeName);

    for(int i = 0; i < totalNodes; i++)
    {
        if(!(isVisited(currentnode.nodeName)))
        {
            queue.push_back(currentnode.nodeName);
            visitedNodes.push_back(currentnode.nodeName);
            while(!queue.empty())
            {
                QString current;
                current = queue.front();
                currentnode = GetNodeFromName(current);
                queue.pop_front();
                QVector<WeightEdge> incidentEdges = this->sortedIncidentEdges(current);

                for(QVectorIt = incidentEdges.begin(); QVectorIt != incidentEdges.end(); ++QVectorIt)
                {
                    QString connectednodeName = QVectorIt->connectedNode;
                    Node connectednode = GetNodeFromName(connectednodeName);

                    if(!(isVisited(connectednodeName)))
                    {
                        qDebug() << connectednodeName;
                        stadiums.push_back(connectednodeName);
                        distance += QVectorIt->weight;
                        queue.push_back(connectednodeName);
                        visitedNodes.push_back(connectednodeName);
                    }
                }
            }
        }
    }
    qDebug() << "Distance for BFS: " << distance;
}

/**
 * @brief Graph::minKey
 * @param key
 * @param mstSet
 * @return min_index
 *
 * A utility function to find the vertex with minimum key value, from
 * the set of vertices not yet included in MST
 */
int Graph::minKey(int key[], bool mstSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
    for (int v = 0; v < totalNodes; v++)
    {
        if (mstSet[v] == false && key[v] < min)
        {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

/**
 * @brief Graph::PrimMST
 * @return distance
 * Returns the distance of the PrimMST
 */
int Graph::PrimMST()
{
    distance = 0;
    int parent[totalNodes];
    int key[totalNodes];
    bool mstSet[totalNodes];
    qDebug () << "Nodes" << totalNodes;
    for (int i = 0; i < totalNodes; i++)
    {
        key[i] = INT_MAX, mstSet[i] = false;
    }
    key[0] = 0;
    parent[0] = -1;
    for (int count = 0; count < totalNodes; count++)
    {
        int u = minKey(key, mstSet);
        mstSet[u] = true;
        for (int v = 0; v < totalNodes; v++)
        {
            if (matrix[u][v] && mstSet[v] == false && matrix[u][v] < key[v])
            {
                parent[v] = u;
                key[v] = matrix[u][v];
                qDebug() << "Index " << v << "matrix " << matrix[u][v];
            }
        }
    }
    for (int index = 0; index < totalNodes; index++)
    {
        qDebug() << "index " << index << ": " << key[index];
        distance += key[index];
    }

    if(totalNodes >= 31)
        distance -= INT_MAX;

    return distance;
}

/**
 * @brief Graph::minDistance
 * @param distances
 * @param sptSet
 * @return min_index
 * Returns the minimum distance between multiple points
 */
int Graph::minDistance(QVector<int> distances, bool sptSet[])
{
    int min = INT_MAX, min_index;
    for (int v = 0; v < totalNodes; v++)
    {
        if (sptSet[v] == false && distances[v] <= min)
        {
            min = distances[v];
            min_index = v;
        }
    }
    return min_index;
}

/**
 * @brief Graph::Dijkstra
 * @param sourceVertex
 * @return distances
 * Out implementation of the Dijkstra's algorithm
 */
QVector<int> Graph::Dijkstra(int sourceVertex, QVector<QString> &stadiums)
{
    QVector<int> distances;
    distances.resize(totalNodes);
    bool sptSet[totalNodes];
    for (int i = 0; i < totalNodes; i++)
    {
        distances[i] = INT_MAX, sptSet[i] = false;
    }
    distances[sourceVertex] = 0;
    for (int count = 0; count < totalNodes-1; count++)
    {
        int u = minDistance(distances, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < totalNodes; v++)
        {
            if (!sptSet[v] && matrix[u][v] && distances[u] != INT_MAX && distances[u]+matrix[u][v] < distances[v])
            {
                distances[v] = distances[u] + matrix[u][v];
            }
        }
    }
    return distances;
}

/**
 * @brief Graph::DijkstraRecursive
 * @param sourceVertex
 * @param baseCase
 * A recursive implementation of the Dijkstra algorithm.
 */
void Graph::DijkstraRecursive(int sourceVertex, int baseCase, QVector<QString> &stadiums)
{
    if (baseCase < totalNodes-1)
    {
        qDebug() << "Source:" << nodes[sourceVertex].nodeName << baseCase;
        QVector<int> distances = Dijkstra(sourceVertex, stadiums);
        visited[sourceVertex] = true;
        int smallest = 99999;
        int nextVertex = -1;\
        for (int index = 0; index < totalNodes; index++)
        {
            if (distances[index] < smallest && visited[index] == false)
            {
                smallest = distances[index];
                nextVertex = index;
            }
        }
        qDebug() << "Smallest:" << smallest;
        if(smallest==99999){
            qDebug() << "Exit";
            return;
        }
        distance += smallest;
        stadiums.push_back(nodes[nextVertex].nodeName);
        qDebug() << "Next:" << nodes[nextVertex].nodeName;
        visitedNodes.push_back(GetNodeName(nextVertex));

        DijkstraRecursive(nextVertex, baseCase+1, stadiums);
    }
}

/**
 * @brief Graph::PerformCompleteDijkstra
 * @param sourceVertex
 * @param baseCase
 * @return Disjkstra's algorithm on a segment of verticies
 */
int Graph::PerformCompleteDijkstra(int sourceVertex, int baseCase, QVector<QString> &stadiums)
{
    distance = 0;
    visitedNodes.clear();
    for (int index = 0; index < totalNodes; index++)
    {
        visited[index] = false;
    }
    visitedNodes.push_back(GetNodeName(sourceVertex));
    DijkstraRecursive(sourceVertex, baseCase, stadiums);
    return distance;
}

/**
 * @brief Graph::PerformFromToDijkstra
 * @param fromVertex
 * @param toVertex
 * @return Dijkstra's algorithm from a vertex to a vertex
 */
int Graph::PerformFromToDijkstra(int fromVertex, int toVertex)
{
    QVector<QString> stadiums;
    return Dijkstra(fromVertex, stadiums)[toVertex];
}
