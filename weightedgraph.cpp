#include "weightedgraph.h"
#include <iostream>
#include <queue>

WeightedGraph::WeightedGraph(int size)
{
    m_numVertices = 0;
    m_maxVertices = size;
    m_vertices.resize(size);
    for (int i=0; i<size; i++){
        m_vertices[i] = NULL;
    }
    m_marks.resize(size);
    int rows = size;
    int columns = size;
    m_edges.resize(rows, vector<int>(columns, 0));
}

void WeightedGraph::addVertex(Vertex* aVertex)
{
    m_vertices[m_numVertices] = aVertex;
    for (int i=0; i<m_maxVertices; i++) {
        m_edges[m_numVertices][i] = NULL_EDGE;
        m_edges[i][m_numVertices] = NULL_EDGE;
    }
    m_numVertices++;
}

void WeightedGraph::addEdge(int fromVertex, int toVertex, int weight)
{
    int row;
    int column;
    row = indexIs(m_vertices[fromVertex]);
    column = indexIs(m_vertices[toVertex]);
    m_edges[row][column] = weight;
}

int WeightedGraph::indexIs(Vertex* aVertex)
{
     int i = 0;
     while (i < m_numVertices) {
        if (m_vertices[i] == aVertex) {
            return i;
        }
        i++;
     }
     return -1;
}

void WeightedGraph::clearMarks()
{
    for (int i=0; i<m_numVertices; i++) {
        m_marks[i] = false;
    }
}

void WeightedGraph::doDFS(Vertex* aVertex, int& cost)
{
    int ix, ix2;
    if (aVertex == NULL) return;
    cout << aVertex->getTitle() << " ";
    ix = indexIs(aVertex);
    m_marks[ix] = true;
    for (int i=0; i<m_numVertices; i++) {
        ix2 = indexIs(m_vertices[i]);
        if(m_edges[ix][ix2] != NULL_EDGE) {
            if (m_marks[i] == false) {
               cost += m_edges[ix][ix2];
               doDFS(m_vertices[i], cost);
            }
        }
    }
}

void WeightedGraph::DFS(Vertex* aVertex)
{
    clearMarks();
    int cost = 0;
    cout << "Path: ";
    doDFS(aVertex, cost);
    cout << "\nTotal cost: " << cost << endl;
}

void WeightedGraph::doBFS(Vertex* aVertex)
{
    int ix,ix2;
    int cost = 0;
    queue <Vertex*> que;
    ix = indexIs(aVertex);
    m_marks[ix] = true;
    que.push(aVertex);
    cout << "Path: ";
    while (!que.empty()) {
        Vertex* node = que.front();
        que.pop();
        ix = indexIs(node);
        cout << node->getTitle() << " ";
        for (int i=0; i<m_numVertices; i ++) {
            ix2 = indexIs(m_vertices[i]);
            if (m_edges[ix][ix2] != NULL_EDGE) {
                if (m_marks[ix2] == false) {
                    m_marks[i] = true;
                    que.push(m_vertices[i]);
                    cost += m_edges[ix][ix2];
                }
            }
        }
    }
    cout << "\nTotal cost: " << cost << endl;
}

void WeightedGraph::BFS(Vertex* aVertex)
{
    clearMarks();
    doBFS(aVertex);
}

void WeightedGraph::findPath(Vertex* start, Vertex* end)
{
    vector<int> dist(m_numVertices, 9999);
    vector<int> prev(m_numVertices, -1);
    vector<bool> visited(m_numVertices, false);
    int ix = indexIs(start);
    int endIx = indexIs(end);
    dist[ix] = 0;

    for(int i = 0; i < m_numVertices; i++) {
        int minDist = 9999;
        int current = -1;

        for(int j = 0; j < m_numVertices; j++) {
            if(!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                current = j;
            }
        }

        if(current == -1) break;
        visited[current] = true;

        for(int j = 0; j < m_numVertices; j++) {
            if(!visited[j] && m_edges[current][j] != NULL_EDGE) {
                if(dist[current] + m_edges[current][j] < dist[j]) {
                    dist[j] = dist[current] + m_edges[current][j];
                    prev[j] = current;
                }
            }
        }
    }

    if(dist[endIx] == 9999) {
        cout << "No path exists from " << start->getTitle()
             << " to " << end->getTitle() << endl;
        return;
    }

    vector<int> path;
    for(int at = endIx; at != -1; at = prev[at]) {
        path.push_back(at);
    }

    cout << "Path from " << start->getTitle() << " to " << end->getTitle() << ": ";
    for(int i = path.size() - 1; i >= 0; i--) {
        cout << m_vertices[path[i]]->getTitle();
        if(i > 0) cout << " -> ";
    }
    cout << "Path length: " << dist[endIx] << endl;
}
