#pragma once

#include "SLList.h"
#include "DynArray.h"
#include <queue>
#include <list>
using namespace std;

template<typename Type>
class Graph
{

public:

	struct Edge
	{
		unsigned int toVertex;
		//float weight = INT_MAX;
	};

	struct Vertex
	{
		Type element;
		SLList<Edge> edges;

		void addEdge(const unsigned int& _toVertex)
		{
			Edge e;
			e.toVertex = _toVertex;
			edges.addHead(e);
		}
	};

	Graph() = default;
	~Graph() = default;

	unsigned int addVertex(const Type& value);
	Vertex& operator[](const unsigned int& index){ return arr[index]; }
	Vertex& operator[](const unsigned int& index) const { return arr[index]; }

	const Type GetVertexElement(const unsigned int& index) const { return arr[index].element; }

	unsigned int size() const { return arr.size(); }
	void clear() { arr.clear(); }
	void FindPath(const unsigned int& startVertex, const unsigned int& endVertex, vector<unsigned int>& finalPath);
	void printBreadthFirst(const unsigned int& startVertex);

private:
	DynArray<Vertex> arr;

};

template<typename Type>
unsigned int Graph<Type>::addVertex(const Type& value)
{
	Vertex v;
	v.element = value;
	arr.append(v);

	return (arr.size() - 1);
}



template<typename Type>
void Graph<Type>::printBreadthFirst(const unsigned int& startVertex)
{
	queue<unsigned int> q;
	int* stuffs = new int[arr.size()]; // MAY ARRAY OF DEPTH VALUES

	for (size_t i = 0; i < arr.size(); i++) // SETTING THEM TO -1 SO I KNOW THEY HAVENT BEEN SEEN
		stuffs[i] = -1;

	q.push(startVertex); // PUSH YOUR START VERTEX TO THE QUEUE
	stuffs[startVertex] = 0; //SET THE FIRST INDEX IN THE DEPTH ARRAY TO 0 SINCE THATS THE START VERTEX

	while (!q.empty()) // WHILE YOUR QUEUE ISNT EMPTY
	{
		unsigned int index = q.front(); //STORE YOUR FIRST ITEM IN THE QUEUE FOR LATER USE
		q.pop(); //THEN POP IT FROM THE QUEUE

		SLLIter<Edge> iter(arr[index].edges); // ITERATOR

		for (iter.begin(); !iter.end(); ++iter) //ITERATE
		{
			if (stuffs[iter.current().toVertex] == -1) // IF THE CURRENT ITEM HASNT BEEN HIT YET
			{
				q.push(iter.current().toVertex); //PUSH THAT ITEM TO THE QUEUE
				stuffs[iter.current().toVertex] = stuffs[index] + 1; //MAKES IT DEPTH WHATEVER THE PREVIOUSLY ADDED ITEMS DEPTH IS + 1
			}
		}
		cout << arr[index].element << " : " << stuffs[index] << '\n'; //THEN DO YOUR OUTPUT AT THE END OF EACH CYCLE
	}

	delete[] stuffs; // MAKE SURE TO DELETE YOUR DEPTH ARRAY

}



	template<typename Type>
	void Graph<Type>::FindPath(const unsigned int& startVertex, const unsigned int& endVertex, vector<unsigned int>& finalPath)
	{

		finalPath.clear();


		queue<list<unsigned int>> q;
		int* stuffs = new int[arr.size()]; // MAY ARRAY OF visited VALUES

		for (size_t i = 0; i < arr.size(); i++) // SETTING THEM TO -1 SO I KNOW THEY HAVENT BEEN SEEN
			stuffs[i] = -1;

		list<unsigned int> path;
		path.push_front(startVertex);
		q.push(path); // PUSH YOUR START VERTEX TO THE QUEUE
		stuffs[startVertex] = 0; //SET THE FIRST INDEX IN THE DEPTH ARRAY TO 0 SINCE THATS THE START VERTEX

		while (!q.empty()) // WHILE YOUR QUEUE ISNT EMPTY
		{
			list<unsigned int> currPath = q.front(); //STORE YOUR FIRST ITEM IN THE QUEUE FOR LATER USE
			q.pop(); //THEN POP IT FROM THE QUEUE

			list<unsigned int>::iterator pathIter = currPath.begin();

			// ITERATOR

			for (; pathIter != currPath.end(); ++pathIter) //ITERATE
			{
				if (*pathIter == endVertex)
				{
					pathIter = currPath.begin();

					for (; pathIter != currPath.end(); ++pathIter)
						finalPath.push_back(*pathIter);


					delete[] stuffs; // MAKE SURE TO DELETE YOUR DEPTH ARRAY

					return;
				}
				SLLIter<Edge> edgeIter(arr[*pathIter].edges);
				for (edgeIter.begin(); !edgeIter.end(); ++edgeIter) //ITERATE
				{
					if (stuffs[edgeIter.current().toVertex] == -1) // IF THE CURRENT ITEM HASNT BEEN HIT YET
					{
						//currPath.push_back(edgeIter.current().toVertex);


						list<unsigned int> newPath = currPath;
						newPath.push_back(edgeIter.current().toVertex);
						q.push(newPath); //PUSH THAT ITEM TO THE QUEUE
						stuffs[edgeIter.current().toVertex] = 0; //MAKES IT DEPTH WHATEVER THE PREVIOUSLY ADDED ITEMS DEPTH IS + 1
					}
					else
						continue;
				}
			}
			//	cout << arr[index].element << " : " << stuffs[index] << '\n'; //THEN DO YOUR OUTPUT AT THE END OF EACH CYCLE
		}

		delete[] stuffs; // MAKE SURE TO DELETE YOUR DEPTH ARRAY


	}




