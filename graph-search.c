#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 10 // 최대 Vertex 수 = 10
#define MAX_QUEUE 11 // 최대 Queue 수 = 11

typedef struct LIST { // (typedef를 사용하여) List 구조체 생성
   int vx;
   struct LIST* link;
}List;

typedef struct GRAPH { // (typedef를 사용하여) Graph 구조체 생성
   int n;
   List* adj_list[MAX_VERTEX];
}Graph;

// 함수 리스트
Graph* Init_Graph(void); // 구조체 포인터 초기화

void Add_Vertex(Graph* g); // 그래프에 정점 추가
void Add_Edge(Graph* g, int u, int v); // 간선 생성
void Check_Link(Graph* g, int u, int v); // 이어져 있는지 검사
void Delete_Vertex(Graph* g, int u); // 정점에 연결된 간선 삭제
void Delete_Edge(Graph* g, int u, int v); // 간선 삭제

void DFS(Graph *g, int n); // 깊이 우선 탐색 알고리즘
void Depth_First_Search(Graph* g, int n); // 깊이 우선 탐색 알고리즘에 대한 코드 저장

void BFS(Graph *g, int n); // 넓이 우선 탐색 알고리즘
void Breath_First_Search(Graph* g, int n); // 넓이 우선 탐색 알고리즘에 대한 코드 저장

void Add_Queue(int n);  // 넓이 우선 탐색을 위한 큐 (추가)
int Delete_Queue(void); // 넓이 우선 탐색을 위한 큐 (삭제)

int check[MAX_VERTEX];

// 큐
int front   = 0;
int rear    = 0;
int queue[MAX_QUEUE];

int main(void) {
    char command; // 변수 command
	int key; // 변수 key
    Graph* g = Init_Graph();

    printf("\n[----- [Kim Yun Seo]  [2020021016] -----]");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Graph Searches                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph       = z                                     \n");
		printf(" Insert Vertex          = v     Insert Edge            = e \n");
		printf(" Depth First Search     = d     Breath First Search    = t \n");
		printf(" Print Graph            = p     Quit                   = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // command 값 받기

		switch(command) {
		case 'z': case 'Z': // command 값이 z 또는  일 경우
			Init_Graph();
			break;
		case 'v': case 'V': // command 값이 v 또는 V 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값 받기
			Add_Vertex(g);
			break;
		case 'd': case 'D': // command 값이 d 또는 D 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값 받기
            DFS(g, key);
			break;
        case 'p': case 'P': // command 값이 p 또는 P 일 경우
            Add_Edge(g, 0, 1);
            Add_Edge(g, 0, 2);
            Add_Edge(g, 0, 3);
            Add_Edge(g, 1, 2);
            Add_Edge(g, 1, 3);
            Add_Edge(g, 1, 4);

            Check_Link(g, 1, 3);

            DFS(g, 0);
            BFS(g, 0);
			break;
		case 'e': case 'E': // command 값이 e 또는 E 일 경우
            printf("Your Key = ");
			scanf("%d", &key); // key 값 받기
            Add_Edge(g,key,key);
			break;
		case 't': case 'T': // command 값이 t 또는 T 일 경우
            printf("Your Key = ");
			scanf("%d", &key); // key 값 받기
            BFS(g, key);
			break;
		case 'q': case 'Q': // command 값이 q 또는 Q 일 경우
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // 입력받은 command 값이 q 또는 Q 이 아닐 경우 동안 진행

    for(int i = 0; i < 5; i++){
        Add_Vertex(g);
    }

    return 0;
}

 // 구조체 포인터 초기화
Graph* Init_Graph(void){
    Graph* g = (Graph*)malloc(sizeof(Graph)); // *g에 'Graph' 타입으로 주소 받기
    g->n = 0;

    for(int i = 0; i < MAX_VERTEX; i++)
        g->adj_list[i] = NULL;

    return g;
}

// 그래프에 정점 추가
void Add_Vertex(Graph* g){
    g->adj_list[g->n] = (List*)malloc(sizeof(List));
    g->adj_list[g->n]->vx = -1;
    g->adj_list[g->n]->link = NULL;

    g->n++;
}

// 추가된 정점을 이어주는 간선 생성
void Add_Edge(Graph* g, int u, int v){
    if(u >= g->n || v >= g->n){
        printf("Out of Graph.\n\n");
    }

    else{
        List* tmp_u = (List*)malloc(sizeof(List)); // u에 대한 정보를 저장하는 List 구조체 포인터 형성
        List* tmp_v = (List*)malloc(sizeof(List)); // v에 대한 정보를 저장하는 List 구조체 포인터 형성

        tmp_u->vx = u;
        tmp_v->vx = v;

        // u
        tmp_v->link = g->adj_list[u]->link; // 기존 정점의 정보 저장
        g->adj_list[u]->link = tmp_v; // 기존에 연결된 정잠 자리로 연결
        // v
        tmp_u->link = g->adj_list[v]->link;
        g->adj_list[v]->link = tmp_u;
    }
}

// 두 정점이 간선으로 이어져 있는가 확인
void Check_Link(Graph* g, int u, int v){
    if(u >= g->n || v >= g->n){
        printf("Out of Graph.\n\n");
    }

    else{
        List* cur;
        List* tmp;

        cur = g->adj_list[u]->link; // link에 맨 앞에 연결된 노드의 정보 포함

        while(cur != NULL){ // cur이 NULL이 아닐 경우
            tmp = cur->link; // 마지막에 연결된 정점은 NULL과 Link로 연결

            if(cur->vx == v){
                printf("Connected!! [%d]--[%d]\n", u, v);
                return;
            }

            cur = tmp;
        }

        printf("Disconnected!! [%d]\\[%d]\n", u, v);
    }
}

// 정점에 연결된 간선 삭제
void Delete_Vertex(Graph* g, int u){
    if(u >= g->n){
        printf("Out of Graph.\n\n");
    }

    else{
        List* cur;
        List* pre;
        List* tmp;

        // 모든 정점의 연결 리스트에서 u의 정보 삭제
        for(int i = 0; i < g->n && i != u; i++){
            pre = g->adj_list[i]; // 삭제하고자하는 정점의 앞 부분에 노드 정보 저장
            cur = pre->link; // 삭제하고자 하는 정점의 정보 저장

            while(cur != NULL){ // cur가 NULL이 아닐 경우
                tmp = cur->link;

                 if(cur->vx == u){ // 현재 노드 cur이 삭제하고자 하는 정점일 경우
                    pre->link = cur->link; // 앞 부분의 노드를 cur 뒷 부분 노드와 연결
                    free(cur); // 메모리 해제
                    break;
                }

                pre = cur;
                cur = tmp;
            }
        }
        
        // u의 인접 리스트에 연결된 모든 정점의 정보 삭제
        pre = g->adj_list[u]; // 지울 정점의 인접 리스트
        cur = g->adj_list[u]->link; 

        while(cur != NULL){ // 마지막 정점까지 이동하면서 할당된 메모리 해제
            tmp = cur->link;
            free(cur); // 메모리 해제
            cur = tmp;
        }

        pre->link = NULL;
    }
}

// 두 정점 사이를 잇는 간선 삭제
void Delete_Edge(Graph* g, int u, int v){
    if(u >= g->n){
        printf("Out of Graph.\n\n");
    }

    else{
        List* cur;
        List* pre;
        List* tmp;

        pre = g->adj_list[u];
        cur = g->adj_list[u]->link;

        while(cur != NULL){ // cur가 NULL이 아닐 경우
            tmp = cur->link;

            if(cur->vx == v){
                pre->link = cur->link;
                free(cur); // 메로리 해제
                break;
            }

            pre = cur;
            cur = tmp;
        }

        pre = g->adj_list[v];
        cur = g->adj_list[v]->link;

        while(cur != NULL){ // cur가 NULL이 아닐 경우
            tmp = cur->link;

            if(cur->vx == u){
                pre->link = cur->link;
                free(cur); // 메모리 해제
                break;
            }

            pre = cur;
            cur = tmp;
        }
    }
}

// 깊이 우선 탐색 알고리즘
void DFS(Graph *g, int n){
    for(int i = 0; i < MAX_VERTEX; i++){
        check[i] = 0; // 행렬 초기화
    }

    Depth_First_Search(g, n); // 깊이 우선 탐색 알고리즘에 대한 코드 저장
    printf("\n");
}

// 깊이 우선 탐색 알고리즘에 대한 코드 저장
void Depth_First_Search(Graph* g, int n){
    if(check[n] == 0){
        List* cur;
        List* tmp;

        cur =  g->adj_list[n]->link; // n번 정점 방문
        printf("%2d  ", n);
        check[n] = 1; // 정점 방문 여부

        while(cur != NULL){ // cur가 NULL이 아닐 경우
            tmp = cur->link;

            if(check[cur->vx] == 0)
                Depth_First_Search(g, cur->vx); // 연결된 정점에 방문하여 과정 반복

            cur = tmp;
        }
    }
}

// 넓이 우선 탐색 알고리즘
void BFS(Graph *g, int n){
    for(int i = 0; i < MAX_VERTEX; i++){
        check[i] = 0; // 행렬 초기화
    }

    front   = 0; // 큐 사용을 위해 변수 초기화
    rear    = 0;

    Breath_First_Search(g, n); // 넓이 우선 탐색 알고리즘에 대한 코드 저장

    printf("\n");
}

// 넓이 우선 탐색 알고리즘에 대한 코드 저장
void Breath_First_Search(Graph* g, int n){
    List* cur;
    List* tmp;

    int queue_out;
    cur = g->adj_list[n]->link;

    if(check[n] == 0){ // check[0]이 0일 경우
        printf("%2d  ", n);
        check[n] = 1;
    }

    while(cur != NULL){ // cur가 NULL이 아닐 경우
        tmp = cur->link; // n번 정점과 연결된 cur 확인

        if(check[cur->vx] == 0){ // 방문하지 않았을 경우
            printf("%2d  ", cur->vx);
            check[cur->vx] = 1;
            Add_Queue(cur->vx); // 넓이 우선 탐색을 위한 큐 (추가)
        }

        cur = tmp;
    }
    queue_out = Delete_Queue(); // 넓이 우선 탐색을 위한 큐 (삭제)

    while(queue_out != -1){ // 정점이 없을 경우
        Breath_First_Search(g, queue_out);
        queue_out = Delete_Queue();
    }
}

// 넓이 우선 탐색을 위한 큐 (추가)
void Add_Queue(int n){
    if((rear+1)%MAX_QUEUE == front){
        puts("Queue is full.");
    }

    else{
        rear = (rear+1)%MAX_QUEUE;
        queue[rear] = n; // 1번부터 채우기
    }

}

// 넓이 우선 탐색을 위한 큐 (삭제)
int Delete_Queue(void){
    int tmp = -1;

    if(front == rear){ // 큐의 앞과 뒤가 같을 경우
        puts("Queue is empty.");
    }

    else{ // 같지 않을 경우
        front = (front+1)%MAX_QUEUE;
        tmp = queue[front];
    }

    return tmp;
}
