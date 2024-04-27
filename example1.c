/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/
#include <stdlib.h>
#include <stdio.h>



typedef struct Node{
    int dest;
    struct Node *next;
}NODE;

// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
// ex: 1 - restaurantul 1 si tot asa    

typedef struct GRAPH{
    int n;
    int *nodeList;
    struct Node **head;
}GRAPH;

typedef struct Stack{
    int top;
    int size;
    int *array;
} STACK;

NODE *createNode(int dest){

    NODE *node=(NODE*)malloc(sizeof(NODE));
    node->dest=dest;
    node->next=NULL;

    return node;
}

/**
 * Adds an edge between two vertices in a graph.
 * 
 * @param graph The graph to add the edge to.
 * @param src The source vertex.
 * @param dest The destination vertex.
 */
void addEdge(GRAPH *graph, int src, int dest){

    NODE *node=createNode(dest);
    node->next=graph->head[src];
    graph->head[src]=node;

    node=createNode(src);
    node->next=graph->head[dest];
    graph->head[dest]=node;

}

/**
 * Creates a graph with the specified number of vertices.
 * 
 * @param n The number of vertices in the graph.
 * @return A pointer to the created graph.
 */
GRAPH *createGraph(int n){
    GRAPH *graph=malloc(sizeof(GRAPH));

    graph->n=n;
    graph->head=malloc(sizeof(NODE *) * n+1);
    graph->nodeList=malloc(sizeof(int) *n+1);

    for (int i=0;i<=n;i++){
        graph->head[i]=NULL;
        graph->nodeList[i]=0;
    }   

    return graph;
}

/**
 * Creates a stack with the specified size.
 * 
 * @param size The size of the stack.
 * @return A pointer to the created stack.
 */
STACK *createStack(int size){
    STACK *stack=malloc(sizeof(STACK));
    stack->array=malloc(size*sizeof(int));
    stack->top = -1;
    stack->size=size;

    return stack;
}

/**
 * Prints the adjacency list representation of a graph.
 * 
 * @param graph The graph to print.
 */
void print_graph(GRAPH *graph)
{
    int i; 
    for (i = 0; i <= graph->n; i++){
        NODE *temp = graph->head[i];
        printf("vertex %d: ", i);
        while (temp) {
            printf("%d ", temp->dest);
            temp =temp->next;
        }
        printf("\n");
    }
}

/**
 * Pushes an element onto the stack.
 * 
 * @param data The data to push onto the stack.
 * @param stack The stack to push the data onto.
 */
void push(int data,STACK *stack)
{
    stack->top=stack->top+1;
    stack->array[stack->top]=data;
}

/**
 * Performs a depth-first search (DFS) traversal of a graph starting from a given vertex.
 * 
 * @param graph The graph to perform the DFS on.
 * @param stack The stack used for DFS.
 * @param vertex The starting vertex for DFS.
 */
void DFS(GRAPH *graph,STACK *stack, int vertex)
{
    if(graph->head[vertex]!=NULL){

        NODE *adjacencyList=graph->head[vertex];
        graph->nodeList[vertex]=1;
        push(vertex,stack);

        while (adjacencyList != NULL){
            int next=adjacencyList->dest;

            if (graph->nodeList[next]==0)
                DFS(graph, stack, next);

            adjacencyList = adjacencyList->next;
        }

        free(adjacencyList);
    }
}

/**
 * Inserts edges into a graph from a file.
 * 
 * @param graph The graph to insert the edges into.
 * @param edgeNumber The number of edges to insert.
 * @param vertexNumber The number of vertices in the graph.
 * @param fin The file pointer to read the edges from.
 */
void insertEdges(GRAPH *graph,int edgeNumber,int vertexNumber, FILE *fin)
{
    int src,dest;
    printf("adauga %d munchii (de la 1 la %d)\n", edgeNumber, vertexNumber);

    for (int i = 0; i < edgeNumber; i++){
        fscanf(fin ,"%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }
}

/**
 * Clears the node list of a graph.
 * 
 * @param graph The graph to clear the node list of.
 * @param vertexNumber The number of vertices in the graph.
 */
void clearNodeList(GRAPH *graph, int vertexNumber)
{
    for (int i = 1; i <= vertexNumber;i++){
        graph->nodeList[i] = 0;
    }
}  

/**
 * Determines if each vertex in a graph can be reached from any other vertex.
 * 
 * @param graph The graph to check.
 * @param vertexNumber The number of vertices in the graph.
 * @return An array indicating if each vertex can be reached (1) or not (0).
 */
int *canBeReached(GRAPH *graph, int vertexNumber)// 0 sau 1 daca poate fi sau nu ajuns
{
    int *canBeReached = calloc(vertexNumber, sizeof(int)); 

    for (int i = 1; i <= vertexNumber; i++) // aici i tine loc de numar adica de restaurant{for (int j = 0; j < 5; j++)
    {
        STACK *stack = createStack(2*vertexNumber);

        DFS(graph, stack, i);
        clearNodeList(graph, vertexNumber);

        if (stack->top >= 0)
            canBeReached[i] = 1;
    
    }

    return canBeReached; 
}

int main(){

    FILE *fin=fopen("input.txt","r");

    int vertexNumber, edgeNumber;

    printf("cate noduri are graful?");
    fscanf(fin,"%d", &vertexNumber);

    printf("cate muchii are graful?");
    fscanf(fin,"%d", &edgeNumber);

    GRAPH *graph = createGraph(vertexNumber);
    insertEdges(graph, edgeNumber, vertexNumber, fin);
    printf("graf:\n");
    print_graph(graph);

    int *reachArray = canBeReached(graph, vertexNumber);


    for(int i=0; i<=vertexNumber; i++)
        printf("%d ", reachArray[i]);

    return 0;
}