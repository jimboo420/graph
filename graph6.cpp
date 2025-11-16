#include <iostream>
#include <vector>
#include <climits>
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
    char graphType;
    bool isDirected;
    
    cout << "Enter number of vertices: ";
    cin >> v;
    cout << "Enter number of edges: ";
    cin >> e;
    cout << "Is the graph directed? (y/n): ";
    cin >> graphType;
    
    isDirected = (graphType == 'y' || graphType == 'Y');
    
    if (isDirected) {
        cout << "Creating a DIRECTED graph...\n";
    } else {
        cout << "Creating an UNDIRECTED graph...\n";
    }

  
    // Initialize with 0 (0 means no edge)
    vector<vector<int>> adjMatrix(v, vector<int>(v, 0));

    // Variables to track statistics
    int totalWeight = 0;
    int minWeight = INT_MAX;
    int maxWeight = INT_MIN;
    int minU = -1, minV = -1;
    int maxU = -1, maxV = -1;

    cout << "Enter edges (u v weight) where u and v are vertex indices:\n";
    if (isDirected) {
        cout << "(Edge direction: u -> v)\n";
    }
    cout << "(Note: Self-loops are allowed, e.g., 2 2 5)\n";
    
    for (int i = 0; i < e; i++) {
        int u, w, weight;
        cin >> u >> w >> weight;
        
        // Validate vertex indices
        if (u < 0 || u >= v || w < 0 || w >= v) {
            cout << "Invalid edge (" << u << " " << w << "). Vertices must be between 0 and " << v-1 << ".\n";
            i--;  // Don't count this as a valid edge
            continue;
        }
        
        // Validate weight
        if (weight <= 0) {
            cout << "Invalid weight. Weight must be positive.\n";
            i--;
            continue;
        }
        
        // Update statistics
        totalWeight += weight;
        if (weight < minWeight) {
            minWeight = weight;
            minU = u;
            minV = w;
        }
        if (weight > maxWeight) {
            maxWeight = weight;
            maxU = u;
            maxV = w;
        }
        
        // Handle self-loop
        if (u == w) {
            cout << "Self-loop detected at vertex " << u << " with weight " << weight << "\n";
            adjMatrix[u][w] = weight;
        } else {
            // Add edge u -> w
            adjMatrix[u][w] = weight;
            
            // If undirected, also add edge w -> u
            if (!isDirected) {
                adjMatrix[w][u] = weight;
            }
        }
    }

    cout << "\nAdjacency Matrix (0 means no edge):\n";
    cout << "   ";
    for (int i = 0; i < v; i++) {
        cout << i << " ";
    }
    cout << "\n";
    
    for (int i = 0; i < v; i++) {
        cout << i << ": ";
        for (int j = 0; j < v; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
    
    // Show interpretation for directed graphs
    if (isDirected) {
        cout << "\n(Row i, Column j represents edge from vertex i to vertex j)\n";
    }
    
    // Display statistics
    cout << "\n=== Graph Statistics ===\n";
    cout << "Total number of edges: " << e << "\n";
    cout << "Total weight of all edges: " << totalWeight << "\n";
    
    if (e > 0) {
        cout << "Average edge weight: " << (double)totalWeight / e << "\n";
        cout << "Minimum weight edge: " << minWeight << " (from vertex " << minU << " to vertex " << minV << ")\n";
        cout << "Maximum weight edge: " << maxWeight << " (from vertex " << maxU << " to vertex " << maxV << ")\n";
    }
    
   
}

void createAdjacencyList() {
    int v, e;
    char graphType;
    bool isDirected;
    
    cout << "Enter number of vertices: ";
    cin >> v;
    cout << "Enter number of edges: ";
    cin >> e;
    cout << "Is the graph directed? (y/n): ";
    cin >> graphType;
    
    isDirected = (graphType == 'y' || graphType == 'Y');
    
    if (isDirected) {
        cout << "Creating a DIRECTED graph...\n";
    } else {
        cout << "Creating an UNDIRECTED graph...\n";
    }

    struct Node {
        int vertex;
        int weight;  // Added weight field
        Node* next;
    };


    vector<Node*> adjList(v, nullptr);

    // Variables to track statistics
    int totalWeight = 0;
    int minWeight = INT_MAX;
    int maxWeight = INT_MIN;
    int minU = -1, minV = -1;
    int maxU = -1, maxV = -1;

    cout << "Enter edges (u v weight) where u and v are vertex indices:\n";
    if (isDirected) {
        cout << "(Edge direction: u -> v)\n";
    }
    cout << "(Note: Self-loops are allowed, e.g., 2 2 5)\n";
    
    for (int i = 0; i < e; i++) {
        int u, w, weight;
        cin >> u >> w >> weight;
        
        // Validate vertex indices
        if (u < 0 || u >= v || w < 0 || w >= v) {
            cout << "Invalid edge (" << u << " " << w << "). Vertices must be between 0 and " << v-1 << ".\n";
            i--;  // Don't count this as a valid edge
            continue;
        }
        
        // Validate weight
        if (weight <= 0) {
            cout << "Invalid weight. Weight must be positive.\n";
            i--;
            continue;
        }
        
        // Update statistics
        totalWeight += weight;
        if (weight < minWeight) {
            minWeight = weight;
            minU = u;
            minV = w;
        }
        if (weight > maxWeight) {
            maxWeight = weight;
            maxU = u;
            maxV = w;
        }
        
        // Handle self-loop
        if (u == w) {
            cout << "Self-loop detected at vertex " << u << " with weight " << weight << "\n";
            Node* newNode = new Node();
            newNode->vertex = u;
            newNode->weight = weight;
            newNode->next = adjList[u];
            adjList[u] = newNode;
        } else {
            // Add edge u -> w
            Node* newNode = new Node();
            newNode->vertex = w;
            newNode->weight = weight;
            newNode->next = adjList[u];
            adjList[u] = newNode;

            // If undirected, also add edge w -> u
            if (!isDirected) {
                newNode = new Node();
                newNode->vertex = u;
                newNode->weight = weight;
                newNode->next = adjList[w];
                adjList[w] = newNode;
            }
        }
    }

    cout << "\nAdjacency List:\n";
    for (int i = 0; i < v; i++) {
        cout << i << ": ";
        Node* temp = adjList[i];
        while (temp) {
            cout << "(" << temp->vertex << ", w:" << temp->weight << ") -> ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }
    
    if (isDirected) {
        cout << "\n(Vertex i's list shows all vertices reachable FROM vertex i)\n";
    }
    
    // Display statistics
    cout << "\n=== Graph Statistics ===\n";
    cout << "Total number of edges: " << e << "\n";
    cout << "Total weight of all edges: " << totalWeight << "\n";
    
    if (e > 0) {
        cout << "Average edge weight: " << (double)totalWeight / e << "\n";
        cout << "Minimum weight edge: " << minWeight << " (from vertex " << minU << " to vertex " << minV << ")\n";
        cout << "Maximum weight edge: " << maxWeight << " (from vertex " << maxU << " to vertex " << maxV << ")\n";
    }
    
    // Clean up dynamically allocated memory
    cout << "\nCleaning up memory...\n";
    for (int i = 0; i < v; i++) {
        Node* current = adjList[i];
        while (current) {
            Node* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        adjList[i] = nullptr;  // Good practice
    }
    cout << "Memory cleaned up successfully.\n";
}
