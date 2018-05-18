// A C++ program to implement greedy algorithm for graph coloring
#include <iostream>
#include <list>
#include <vector>
#include <random>

using namespace std;

vector <float> runningTimes;

// A class that represents an undirected graph
class Graph
{
    int V;    // No. of vertices
    int E;
    list<int> *adj;    // A dynamic array of adjacency lists
    int threeColor = 0;
public:
    // Constructor and destructor
    Graph(int V)   { this->V = V; adj = new list<int>[V];}
    // function to add an edge to graph
    void addEdge(int v, int w);
    void populate();
    // Prints greedy coloring of the vertices
    void greedyColoring();
    bool isThreeColor = true;
    bool threeFound = false;
};

int getRandNum(int fromnum, int tonum){
    std::uniform_int_distribution<std::mt19937::result_type> dist6(fromnum,tonum); // distribution in range [1, 6]
	    std::mt19937 rng;
    rng.seed(std::random_device()());
    return dist6(rng);
}

void Graph::populate()
{
	E = getRandNum(1, V*(V-1)/2);
	int fromV = 0;
	int toV = 0;

	for (int i = 0; i < E; i++)
	{
		fromV = getRandNum(0,V-1);
		toV = getRandNum(0,V-1);

		while(fromV == toV)
		{
			toV = getRandNum(0,V-1);
		}
		
		addEdge(fromV, toV);
		addEdge(toV, fromV);
	}

}


void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);  // Note: the graph is undirected
}
 
// Assigns colors (starting from 0) to all vertices and prints
// the assignment of colors
void Graph::greedyColoring()
{
    double start_s3=clock();
    
    int result[V];
 
    // Assign the first color to first vertex
    result[0]  = 0;
 
    // Initialize remaining V-1 vertices as unassigned
    for (int u = 1; u < V; u++)
        result[u] = -1;  // no color is assigned to u
 
    // A temporary array to store the available colors. True
    // value of available[cr] would mean that the color cr is
    // assigned to one of its adjacent vertices
    bool available[V];
    for (int cr = 0; cr < V; cr++)
        available[cr] = false;
 
    // Assign colors to remaining V-1 vertices
    for (int u = 1; u < V; u++)
    {
        // Process all adjacent vertices and flag their colors
        // as unavailable
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (result[*i] != -1)
                available[result[*i]] = true;

        // Find the first available color
        int cr;
        for (cr = 0; cr < V; cr++)
            if (available[cr] == false)
                break;
 
        result[u] = cr; // Assign the found color
 
        // Reset the values back to false for the next iteration
        for (i = adj[u].begin(); i != adj[u].end(); ++i){
            if (result[*i] != -1)
                available[result[*i]] = false;
        }
        
    }
 
    
    for (int u = 0; u < V; u++){
       // cout << "Vertex " << u << " --->  Color " << result[u] << endl;
        if(result[u] == 3)
        {
          isThreeColor = false;
          break;
        }       
        
        if(result[u] == 2)
        {
          threeFound = true;
        }
        
    }
    
    if (!threeFound){
      isThreeColor = false;
    }
    
    
double stop_s3=clock();

runningTimes.push_back((stop_s3-start_s3)/double(CLOCKS_PER_SEC)*1000);

}

float calculateSD(vector<float> & data)
{
    float sum = 0.0, mean, standardDeviation = 0.0;
    for(int i = 0; i < data.size(); i++)
    { sum += data[i]; }
    
    mean = sum/data.size();
    
    for(int j = 0; j < data.size(); j++)
        standardDeviation += pow(data[j] - mean, 2);
    standardDeviation = sqrt(standardDeviation / data.size());
    return standardDeviation;
}

float calculateStandartError(float standartDeviation, int N)
{
  return standartDeviation/sqrt(N);
}

void getRunningTime(){
  float totalTime = 0.0;
  for (int i = 0; i < runningTimes.size(); i++){
    totalTime += runningTimes[i];
  }
  
  float standartDeviation = calculateSD(runningTimes);
  int N = runningTimes.size();
  float m = totalTime/N; // Sample Mean
  
  const float tval90 = 1.645;
  const float tval95 = 1.96;
  
  float sm = calculateStandartError(standartDeviation,N);
  
  float upperMean90 = m+tval90*sm;
  float lowerMean90 = m-tval90*sm;
  
  float upperMean95 = m+tval95*sm;
  float lowerMean95 = m-tval95*sm;
  
  cout << "Mean Time: " << m << " ms";
  
  cout << ", SD: " << standartDeviation << " Standart Error: " << sm << ", " << ", %90 " << upperMean90 << " - " << lowerMean90 << ", %95 " << upperMean95 << " - " << lowerMean95;
    runningTimes.clear();
}

void runGraph(int numberOfGraphs, int V)
{
    vector <Graph> graphVec;
    vector <bool> results;
    
    Graph * g1;
    
    for (int i = 0; i < numberOfGraphs; i++)
    {
      g1 = new Graph(V);
      g1->populate();
      g1->greedyColoring();
      graphVec.push_back(*g1);
      results.push_back(g1->isThreeColor);
      delete g1;
    }
  
    int successCount = 0;
    
    for (int j = 0; j <results.size(); j++)
    {
      if(results[j]){
        successCount++;
      }
    }
    
    cout << "Vertex: " << V << ", numberOfGraphs: " << numberOfGraphs << ", successRate: " << (float)successCount/results.size()*100 << "%" << endl;   
    getRunningTime();
    
}

// Driver program to test above function
int main()
{
  runGraph(100, 5);
  runGraph(100, 10);
  runGraph(100, 15);
  runGraph(100, 20);
  runGraph(100, 25);
  return 0;
}