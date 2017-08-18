//
//  main.cpp
//  18.5 Clone a graph
//
//  Created by Andy Lin on 2017/8/18.
//  Copyright © 2017年 Andy Lin. All rights reserved.
//

/*
!!Question!!:
//Question: does returning reference relates to auto?
//Question: does struct has default constructor?
 

!!Repertoire!!:
 
poiter:
 1. always think of both the pointer and the pointed one
 2. from my C experience, manipulate struct elt usually leading to pointer usuage
 
vector
 1. for( T var_name_elt : vecotor<T> var_name_container)
 2. emplace_back
 
queue
 1. constructor: queue<T> var_name (dequeue<T>(size_t size, T var name))
 2. queue.front() returns the reference to the first elt, usually with auto keyword
 3. for BFS, usually start with one elt in the queue. use while(!queue) to do BFS task
 4. emplace: when you wanna put something
 
unorederd_map
 1. [] operator, access the reference to the mapped value
 2. emplace(): put both your key, and mapped value at the same time. Make both exisit
 3. find() and end(): test whether the key is exist
 
 
 
layer by layer:
vertex_map[pivot]->neighbors.emplace_back(vertex_map[neighbor]);

vertex_map[pivot]: pointer to GraphVertex
 vertex_map[pivot]->: GraphVertex
  vertex_map[pivot]->neighbors.: vector container
   vertex_map[pivot]->neighbors.emplace_back(vertex_map[neighbor]): elt is pointer to GraphVertex

*/


#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;


struct GraphVertex {

    int label;
    vector<GraphVertex*> neighbors;
};


int main(int argc, const char * argv[]) {

    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}


GraphVertex* CloneGraph(GraphVertex* G){
    //corner case
    // if a pointer is NULL, its value is 0
    if(!G){
        return nullptr;
    }
    
    unordered_map<GraphVertex*, GraphVertex*> vertex_map;
    // feel like every BFS_queue start with one elt
    queue<GraphVertex*> BFS_queue (deque<GraphVertex*>(1,G));
    
    while(! BFS_queue.empty()){
        
        //Question: does returning reference relates to auto?
        auto pivot = BFS_queue.front();
        BFS_queue.pop();
        
        for(GraphVertex* neighbor : pivot->neighbors){
            
            //if the neighbor not exisit in the map, which means we havn't visit it yet, put it in the map. Otherwise don't do anything!
            if(vertex_map.find(neighbor) == vertex_map.end()){
                
                //Question: does struct has default constructor?
                vertex_map.emplace(neighbor, new GraphVertex({neighbor->label}));
                BFS_queue.emplace(neighbor);
            }
            //[] operator: reference to its mapped value, which is a pointer to GraphVertex
            vertex_map[pivot]->neighbors.emplace_back(vertex_map[neighbor]);
        }//for
    }//while
    return vertex_map[G];
}
