// CLASS: CS 340
// ASSIGNMENT: 4
// SID: 200 333 074
// NAME: ROXANNE HARRISON

// QUESTION: PART II IMPLEMENT DIJKSTRA'S ALGORITHM

#include<iostream>
#include<fstream>
#include<list>
#include<vector>
#include<limits>
#include<set>

using namespace std;

int E = 14; // NUMBER OF EDGES IN THE GRAPH
int V = 9; // NUMBER OF VERTICES IN THE GRAPH
// SETTING INFINITY VARIABLE
int INF = numeric_limits<int>::max();

// CLASS FOR THE GRAPH
class Graph
{
    int V; // VERTICES
  
    // STORE VERTIX AND EDGE WEIGHT PAIRS
    list< pair<int, int> > *adj;
  
public:
    Graph(int V);  // GRAPH CONSTRUCTOR
  
    // ADD EDGE FUNCTION
    void addEdge(int u, int v, int w);
  
    // FIND SHORTEST PATH FUNCTION
    void shortestPath(int s);
};

// CREATE MEMORY FOR LIST
Graph::Graph(int V)
{
    this->V = V; // VERTIX
    adj = new list< pair<int, int> >[V]; // PAIRS
}

// ADD EDGE FUNCTION
void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

// SHORTEST PATH FUNCTION
void Graph::shortestPath(int src)
{
    // SET TO STORE VERTICES
    set< pair<int, int> > setds;

    // START ALL DISTANCES AS INFINITY
    vector<int> dist(V, INF);

    // INSERT THE SOURCE VERTEX AND DISTANCE TO ITSELF
    setds.insert(make_pair(0, src));
    dist[src] = 0;

    // LOOP TO FIND SHORTEST DISTANCE TO EACH VERTEX
    while (!setds.empty())
    {
        // GET THE SHORTEST DISTANCE
        pair<int, int> tmp = *(setds.begin());
        setds.erase(setds.begin());

        // KEEP VERTICES SORTED
        int u = tmp.second;

        // GET ADJACENT VERTICES
        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            // GET VERTIX LABEL AND WEIGHT
            int v = (*i).first;
            int weight = (*i).second;

            // CHECK IF THERE IS A SHORTER PATH
            if (dist[v] > dist[u] + weight)
            {
               // CHECK IF DISTANCE IS INFINITY AND REPLACE
                if (dist[v] != INF)
                    setds.erase(setds.find(make_pair(dist[v], v)));

                // Updating distance of v
                dist[v] = dist[u] + weight;
                setds.insert(make_pair(dist[v], v));
            }
        }
    }
    // PRINT THE LIST OF VERTICES AND SHORTEST DISTANCE
    printf("VERTEX  DISTANCE FROM INITIAL VERTEX\n");
    for (int i = 0; i < V; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

int main()
{

    // CREATE A GRAPH WITH V VERTICES
    Graph graph(V);
    int tempData[E*3];
    
    cout<<"* DIJSKSTRA'S ALGORITHM *"<< endl << endl;
    cout << "IMPORTING LIST OF EDGES: " << endl << endl;
        ifstream file("input.txt");
        if(file.is_open())
        {
            for(int i=0;i<E*3;i++){
                
            file >> tempData[i];
           
            }
            // PRINTING THE INPUT FOR THE GRAPH
            cout << "START VERTEX    END VERTEX    WEIGHT" << endl;
            for(int j=0;j<E*3;j++){
                cout << '\t' << tempData[j];
                cout << '\t' <<'\t'<<'\t'<< '\t'<< tempData[j+1] << '\t'<<'\t';
                cout << '\t' << tempData[j+2] << endl;
                
                // ADD EDGES TO THE GRAPH
                 graph.addEdge(tempData[j], tempData[j+1], tempData[j+2]);
                j = j+2;
            }
            
        }
    cout << endl;
    cout << "PRINTING LIST OF SHORTEST DISTANCE: " << endl << endl;
    // RUN SHORTEST PATH FUNCTION
    graph.shortestPath(0);
    return 0;
}
