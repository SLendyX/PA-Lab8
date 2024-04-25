/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/
#include <stdlib.h>
#include <stdio.h>



typedef struct Node{
    int dest;
    struct Node *next;
}NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa    

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

void addEdge(GRAPH *graph, int src, int dest){

    NODE *node=createNode(dest);
    node->next=graph->head[src];
    graph->head[src]=node;

    node=createNode(src);
    node->next=graph->head[dest];
    graph->head[dest]=node;

}

GRAPH *createGraph(int n){
    GRAPH *graph=malloc(sizeof(GRAPH));

    graph->n=n;
    graph->head=malloc(sizeof(NODE *));
    graph->nodeList=malloc(sizeof(int) *n);

    for (int i=0;i<n;i++){
        graph->head[i]=NULL;
        graph->nodeList[i]=0;
    }   

    return graph;
}

STACK *createStack(int size){
    STACK *stack=malloc(sizeof(STACK));
    stack->array=malloc(size*sizeof(int));
    stack->top = -1;
    stack->size=size;
    return stack;
}

void push(int data,STACK *stack)
{
    stack->top=stack->top+1;
    stack->array[stack->top]=data;
}

void DFS(GRAPH *graph,STACK *stack, int vertex)
{
    NODE *adjacencyList=graph->head[vertex];
    
    graph->nodeList[vertex]=1;
    printf("%d ",vertex);

    push(vertex,stack);

    while (adjacencyList != NULL){
        int next=adjacencyList->dest;

        if (graph->nodeList[next]==0)
            DFS(graph, stack, next);

        adjacencyList = adjacencyList->next;
    }
}


void insertEdges(GRAPH *graph,int edgeNumber,int vertexNumber)
{
    int src,dest;
    printf("adauga %d munchii (de la 1 la %d)\n", edgeNumber, vertexNumber);

    for (int i = 0; i < edgeNumber; i++){
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }
}


void wipe(GRAPH *graph, int vertexNumber)
{
    for (int i = 0; i < vertexNumber;i++){
        graph->nodeList[i] = 0;
    }
}  


int canBeReached(GRAPH *graph, int vertexNumber, STACK *stack1, STACK *stack2)// 0 sau 1 daca poate fi sau nu ajuns
{
    int *canBeReached = calloc(5, sizeof(int)); 
    for (int i = 0; i < vertexNumber; i++) // aici i tine loc de numar adica de restaurant{for (int j = 0; j < 5; j++)
    {
        DFS(graph, stack1, i);
        printf("\n");
        wipe(graph, vertexNumber);
        for (int j = 0; j < vertexNumber; j++){
            if ((stack1->array[i] == j) && (stack2->array[j] == i)){
                canBeReached[i] = 1;
                break;
            }
        }
    }

}

int main()
{
    int vertexNumber, edgeNumber;
    printf("cate noduri are graful?");
    scanf("%d", &vertexNumber);
    printf("cate muchii are graful?");
    scanf("%d", &edgeNumber);

    GRAPH *graph = createGraph(vertexNumber);
    STACK *stack1 = createStack(2 * vertexNumber);
    STACK *stack2 = createStack(2 * vertexNumber);

    insertEdges(graph, edgeNumber, vertexNumber);
    canBeReached(graph, vertexNumber, stack1, stack2);

    return 0;
}
