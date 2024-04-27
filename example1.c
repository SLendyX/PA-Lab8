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
    graph->head=malloc(sizeof(NODE *) * n+1);
    graph->nodeList=malloc(sizeof(int) *n+1);

    for (int i=0;i<=n;i++){
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


void push(int data,STACK *stack)
{
    stack->top=stack->top+1;
    stack->array[stack->top]=data;
}

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


void insertEdges(GRAPH *graph,int edgeNumber,int vertexNumber, FILE *fin)
{
    int src,dest;
    printf("adauga %d munchii (de la 1 la %d)\n", edgeNumber, vertexNumber);

    for (int i = 0; i < edgeNumber; i++){
        fscanf(fin ,"%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }
}


void clearNodeList(GRAPH *graph, int vertexNumber)
{
    for (int i = 1; i <= vertexNumber;i++){
        graph->nodeList[i] = 0;
    }
}  


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