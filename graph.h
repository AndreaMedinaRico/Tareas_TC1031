/*
* graph.h
* By: Andrea Medina Rico
* 14.11.23
*/

#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;

class Graph {
    private:
        int edgesList;
        int edgesMat;
        int nodes;
        vector<int> *adjList;
        int *adjMatrix;

    public:
        Graph();
        Graph(int n);
        void addEdgeAdjList(int, int);
		void addEdgeAdjMatrix(int, int);
        string printAdjList();
		string printAdjMat();
		string printAdjMat_clean();
        bool contains(list<int> ls, int node);
		void sortAdjList();

        string print_visited(list<int> q);
		string print_path(vector<vector<int>> &paths, int , int); 

        void loadGraphList(string name, int n);
        void loadGraphMat(string name, int n, int m);

        string DFS(int start, int goal);
        string depthHelper(int start, int goal, stack<int> &st, list<int> &visited, vector<vector<int>> &paths);

        string BFS(int start, int goal);
        string breadthHelper(int start, int goal, queue<int> &qu, list<int> &visited, vector<vector<int>> &paths);
};

Graph::Graph() {
    edgesList = edgesMat = 0;
}

Graph::Graph(int n) {
    nodes = n;
    adjList = new vector<int>[nodes];
    adjMatrix = new int [nodes * nodes];
    for (int i = 0; i < nodes * nodes; i++)
        adjMatrix[i] = 0;      // Every matrix node = 0
    edgesList = edgesMat = 0;
}

void Graph::addEdgeAdjList(int u, int v){
	adjList[u].push_back(v);
	adjList[v].push_back(u);
	edgesList++;
}

void Graph::addEdgeAdjMatrix(int u, int v){
	adjMatrix[u * nodes + v] = 1;
	adjMatrix[v * nodes + u] = 1;
	edgesMat++;
}

string Graph::printAdjList(){
	  stringstream aux;
		for (int i = 0; i < nodes; i++){
	        aux << "vertex "
	             << i << " :";
	        for (int j = 0; j < adjList[i].size(); j ++){
							 aux << " " << adjList[i][j];
					}
	        aux << " ";
    }
		return aux.str();

}

void Graph::sortAdjList(){
	for (int i = 0; i < nodes; i++)
		sort(adjList[i].begin(), adjList[i].end());
}

string Graph::printAdjMat(){
	stringstream aux;
	for (int i = 0; i < nodes; i++){
	   for (int j = 0; j < nodes; j++){
			 aux << adjMatrix[i*nodes+j] << " ";
		 }
  }
	return aux.str();
}

bool Graph::contains(list<int> ls, int node){
		list<int>::iterator it;

		it = find(ls.begin(), ls.end(), node);
		if(it != ls.end())
			return true;
		else
			return false;
}

string Graph::print_visited(list<int> q){
	stringstream aux;
	aux << "visited: ";
	while (!q.empty()) {
    	aux << q.front() << " ";
    	q.pop_front();
    }
	return aux.str();
}

string Graph::print_path(vector<vector <int>> &path, int start, int goal){
	int node =  path[goal][0];
	stack<int> reverse;
	reverse.push(goal);
	stringstream aux;
	aux  << "path:";

	while (node != start) {
		reverse.push(node);
    	node = path[node][0];
  	}

	reverse.push(start);
	while (!reverse.empty()) {
		aux << " " << reverse.top() ;
		reverse.pop();
  	}
	return aux.str();
}

void Graph::loadGraphList(string data, int a){
	adjList = new vector<int>[a];
	nodes = a;
	int u, v, i = 0;
	while ( i < data.size()) {
			u = (int)data[i+1] - 48;
			v = (int)data[i+3] - 48;
			i = i + 6;
			addEdgeAdjList(u,v);
//			cout << "u  "  << u << " v " << v << endl;
	}
	sortAdjList();
}

void Graph::loadGraphMat(string data, int a, int b){
	adjMatrix = new int [a*b];
	nodes = a;
	for (int i = 0; i < a*b; i++)
		adjMatrix[i] = 0;
	int u, v, i = 0;
	while (i < data.size()) {
		u = (int)data[i+1] - 48;
		v = (int)data[i+3] - 48;
		i = i + 6;
		addEdgeAdjMatrix(u,v);
	}
}

string Graph::DFS(int start, int goal){
	stack<int> st;
	list<int> visited;		// List VISITED nodes
	// 2, -1
	vector< vector<int> >  paths(nodes, vector<int>(1, -1));

	st.push(start);
	string ans = depthHelper(start, goal, st, visited, paths);
	ans = ans + print_path(paths, start, goal);
	// ans    includes VISITED list and PATH
	return ans;
}

// Uses STACK
string Graph::depthHelper(int current,
						int goal,
						stack<int> &st,
						list<int> &visited,
						vector<vector<int>> &paths){

	// CASE 1: Goal found
	if (current == goal) {
		return print_visited(visited);
	
	// CASE 2: Not found -> stack empty
	} else if (st.empty()) {
		return ("node not found");
	
	// CASE 3: Not found YET 
	} else {
		current = st.top();				// Get TOP node
		st.pop();
		visited.push_back(current);		// Add CURRENT as already visited 

		// Check SIZE of current in ADJLIST --> runs for every CONNECTION current has
		for (int i = 0; i < adjList[current].size(); i++) {

			// If CONNECTION with current IS NOT in VISITED list
			if (!contains(visited, adjList[current][i])) {
				st.push(adjList[current][i]);		// Add to STACK
				paths[adjList[current][i]][0] = current;	// Add to PATH
			}
		}
		return depthHelper(current, goal, st, visited, paths);
	}
	return " node not found";
}

// Uses QUEUE
string Graph::BFS(int start, int goal) {
	queue<int> qu;
	list<int> visited;
	// Initializes vector of vectors --> NOT empty
	vector< vector<int> > paths(nodes, vector<int>(1, -1)); // 2D vector of size nodes x 1{
	
	qu.push(start);		// Add START to end of QUEUE (First)	--> Queue ISNT EMPTY when function is called
	string ans = breadthHelper(start, goal, qu, visited, paths);
	ans = ans + print_path(paths, start, goal);

	return ans;
}

string Graph::breadthHelper(int current,
							int goal,
							queue<int> &qu,
							list<int> &visited,
							vector<vector<int>> &paths) {

    if (current == goal) {
		return print_visited(visited);
	} else if (qu.empty()) {
		return ("node not found");
	} else {
		current = qu.front();
		qu.pop();
		visited.push_back(current);

		// Check SIZE of current in ADJLIST --> runs for every CONNECTION current has
		for (int i = 0; i < adjList[current].size(); i++) {

			// If CONNECTION with current IS NOT in VISITED list
			if (!contains(visited, adjList[current][i])) {
				qu.push(adjList[current][i]);		// Add to QUEUE

				if (paths[adjList[current][i]][0] == -1) 		// If it hasnt been reached
					paths[adjList[current][i]][0] = current;	// Add to PATH
			}
			
		}
		return breadthHelper(current, goal, qu, visited, paths);
	}
	return "node not found";

}

#endif