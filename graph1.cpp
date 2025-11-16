#include <iostream>
using namespace std;

void createAdjacencyMatrix();
void createAdjacencyList();


int main() {
    int choice;
    cout << "Choose graph representation:\n";
    cout << "1. Adjacency Matrix\n";
    cout << "2. Adjacency List\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    if (choice == 1) {
        createAdjacencyMatrix();
    } else if (choice == 2) {
        createAdjacencyList();
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}


void createAdjacencyMatrix() {
    int v, e;
    cout << "Enter number of vertices: ";
    cin >> v;
    cout << "Enter number of edges: ";
    cin >> e;

    int adjMatrix[v][v];
    for (int i = 0; i < v; i++)
        for (int j = 0; j < v; j++)
            adjMatrix[i][j] = 0;

    cout << "Enter edges (u v) where u and v are vertex indices:\n";
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1; // For undirected graph
    }

    cout << "Adjacency Matrix:\n";
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Adjacenct list is an array of pointers to the head nodes of linked lists.
// Each linked list represents the vertices that are adjacent to a particular vertex.
void createAdjacencyList() {
    int v, e;
    cout << "Enter number of vertices: ";
    cin >> v;
    cout << "Enter number of edges: ";
    cin >> e;

    struct Node {
        int vertex;
        Node* next;
    };

    Node* adjList[v];
    for (int i = 0; i < v; i++)
        adjList[i] = nullptr;

    cout << "Enter edges (u v) where u and v are vertex indices:\n";
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;

        Node* newNode = new Node();
        newNode->vertex = v;
        newNode->next = adjList[u];
        adjList[u] = newNode;

        newNode = new Node();
        newNode->vertex = u;
        newNode->next = adjList[v];
        adjList[v] = newNode; // For undirected graph
    }

    cout << "Adjacency List:\n";
    for (int i = 0; i < v; i++) {
        cout << i << ": ";
        Node* temp = adjList[i];
        while (temp) {
            cout << temp->vertex << " -> ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }  
}
