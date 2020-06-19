#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 20 /* you can change value 20 */
#define FALSE 0
#define TRUE 1

short int visited[MAX_VERTEX];

typedef struct Vertex {
	int num; /* vertex number */
	struct Vertex* link; /* link to a next adjacent vertext */
} Vertex;

typedef struct VertexHead {
	Vertex* head; /* linked list of all adjacent vertices */
} VertexHead;

typedef struct Graph {
	VertexHead* vlist; /* list of all vertices: vlist[MAX_VERTEX] */
} Graph;



typedef struct node {
	int key;//노드의 데이터 저장
	struct node *left;//노드의 왼족 자식 저장
	struct node *right;//노드의 오른쪽 자식 저장
} Node;

#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];//큐 저장 공간
int front = -1;//큐의 front
int rear = -1;//큐의 rear

int deQueue();//큐에서 데이터 빼기
void enQueue(int key);//큐에 데이터 저장


int createGraph(Graph **head); /* empty graph creation */
int destroyGraph(Graph *g); /* deallocating all allocated memory */
int insertVertex(int key,Graph *g); /* vertex insertion */
int deleteVertex(int key,Graph *g); /* vertex deletion */
int insertEdge(int key1,int key2,Graph *head); /* new edge creation between two vertices */
int deleteEdge(int key1,int key2, Graph *head); /* edge removal */
int depthFS(int key,Graph *head); /* depth firt search using stack */
int breadthFS(int key,Graph *head); /* breadth first search using queue */
int printGraph(Graph *head); /* printing graph with vertices and edges */

int main(void)
{
	char command;//메뉴 선택

	int key;//키값

	int key1, key2;//키값 받음

	Graph *head = NULL;

	
	do {

		printf("\n\n");

		printf("[---- - [한서영][2019038038] ---- - ]\n");

		printf("----------------------------------------------------------------\n");
		 
		printf("                            Graph                               \n");

		printf("----------------------------------------------------------------\n");

		printf(" Create Graph      = C                                          \n");

		printf(" Destroy Graph     = D         Insert Vertex                = I \n");

		printf(" Delete Vertex     = B         Insert Edge                  = E \n");

		printf(" Delete Edge       = G         Depth First Search           = F \n");

		printf(" Print Graph       = P         Breath First Search          = H \n");

		printf(" Quit              = Q\n");

		printf("----------------------------------------------------------------\n");



		printf("Command = ");

		scanf(" %c", &command);



		switch (command) {

		case 'c': case 'C':

			createGraph(&head);

			break;

		case 'd': case 'D':

			destroyGraph(head);

			break;

		case 'i': case 'I':

			printf("KEY:");

			scanf("%d", &key);

			insertVertex(key,head);

			break;

		case 'b': case 'B':

			printf("KEY:");

			scanf("%d", &key);

			deleteVertex(key,head);

			break;

		case 'e': case 'E':

			printf("KEY1 KEY2:");

			scanf("%d %d", &key1,&key2);

			insertEdge(key1,key2,head);

			break;

		case 'g': case 'G':

			printf("KEY1 KEY2:");

			scanf("%d %d", &key1, &key2);

			deleteEdge(key1,key2,head);

			break;

		case 'f': case 'F':

			printf("KEY:");

			scanf("%d", &key);

			depthFS(key,head);

			break;

		case 'p': case 'P':

			printGraph(head);

			break;

		case 'h': case 'H':

			printf("KEY:");

			scanf("%d", &key);

			breadthFS(key,head);

			break;


		default:

			printf("\n       >>>>>   Concentration!!   <<<<<     \n");

			break;

		}



	} while (command != 'q' && command != 'Q');



	return 1;

}
int createGraph(Graph **head) /* empty graph creation */
{
	Vertex * temp;
	if (*head != NULL)//예외
	{
		destroyGraph(*head);
	}
	
	*head = (Graph*)malloc(sizeof(Graph));//head생성
	
	(*head)->vlist = (VertexHead*)malloc(sizeof(VertexHead)*MAX_VERTEX);//head의 vlist 리스트
	
	//(*head)->vlist = (VertexHead*)malloc(sizeof(VertexHead)*MAX_VERTEX);
	//temp = (Vertex*)malloc(sizeof(Vertex));

	for (int i = 0; i < MAX_VERTEX; i++)//리스트 안에 있는 vertex의 link와 number지정
	{
		temp = (Vertex*)malloc(sizeof(Vertex));
		temp->link = NULL;
		temp->num = i;
		(*head)->vlist[i].head=temp;
	}

}
int destroyGraph(Graph *g) /* deallocating all allocated memory */
{
	int i=0;
	if (g == NULL)//예외 설정
		return -1;
	VertexHead *temph = g->vlist;
	//Vertex *tempv = temph->head;
	while (i<MAX_VERTEX)//vertex크기만큼 반복
	{
		if (temph[i].head == NULL)
		{
			return -1;
		}
		while (temph[i].head != NULL)
		{
			free(temph[i].head);
			temph[i].head = NULL;
		}
		i++;
	}//그래프 안에 있는 것들을 우선 동적 할당 해제해준다.

	free(g);
	g = NULL;//그래프 해제
}
int insertVertex(int key,Graph *head) /* vertex insertion */
{
	if (head == NULL)//예외 설정
	{
		return -1;
	}
	//Vertex *temp = &(head->vlist[key]).head;
	Vertex *temp = (Vertex*)malloc(sizeof(Vertex));
	if (head->vlist[key].head->link==NULL)//head 수정
	{
		temp->link = NULL;
		temp->num = key;
		head->vlist[key].head->link = temp;
	}//temp 에 값을 입력한 후에 새로 입력하는 자리에 입력
	
}
int deleteVertex(int key,Graph *head) /* vertex deletion */
{
	if (head == NULL)//예외 설정
	{
		return -1;
	}
	Vertex *temp = &(head->vlist[key]).head;//사용할 변수 지정
	temp->link = NULL;
	temp->num = 0;

	for (int i = 0; i < MAX_VERTEX; i++)//해당vertex를 찾아 해제 해줌
	{
		VertexHead *next = &(head->vlist[i]);
		Vertex *pre = next->head;
		temp = next->head;
		deleteEdge(i, key, head);
	}
	

	//free(&(head->vlist[key]));
	
}
int insertEdge(int key1,int key2, Graph *head ) /* new edge creation between two vertices */
{
	VertexHead *temp = &(head->vlist[key1]);

	Vertex *node = (Vertex*)malloc(sizeof(Vertex));
	node->link = NULL;
	node->num = key2;

	Vertex *tempv = temp->head;

	if (tempv == NULL)//예외 설정
	{
		return -1;
	}

	while (tempv->link != NULL)//link를 이용한 간선 추가
	{
		tempv = tempv->link;
	}//해당 vertex에 마지막 부분까지 간 후에 연결
	tempv->link = node;

	
}
int deleteEdge(int key1,int key2,Graph *g) /* edge removal */
{
	int i = 0;
	VertexHead *next = &(g->vlist[key1]);
	Vertex *pre = next->head;
	Vertex *temp = next->head;//임시 변수 설정

	while (temp != NULL)//그래프에 값이 있는 경우
	{
		if (temp->num == key2)//vetex의 값이 같으면
		{
			if (temp->link != NULL)
			{
				pre->link = temp->link;//중간인 경우
			}
			else
			{
				pre->link = NULL;//마지막에 위치한 경우
			}
		}
		pre = temp;
		temp = temp->link;//다음값
	}
}
int depthFS(int key,Graph *head) /* depth firt search using stack */
{
	VertexHead *w=head->vlist;
	Vertex *temp = w[key].head;
	visited[key] = TRUE;
	printf("%5d",key);
	for (; &temp != NULL; temp = temp->link)
		if (!visited[temp->num])
			depthFS(temp->num,head);
	//인접리스트 중 프린팅 하지 않은 것 선택
	//visit 스택에 넣어 기억시킨 후 모두 프린팅 하는 방식
		
}
int breadthFS(int key,Graph *g ) /* breadth first search using queue */
{//너비 우선 탐색
	//각 정점을 방문할 때마다 큐에 넣어 조사
	//이미 방문된 정점은 무시
	VertexHead* w = g->vlist;
	front = rear = NULL;
	printf("%5d", key);
	visited[key] = TRUE;
	enQueue(key);
	while (front)
	{
		key = deQueue();
		for(w=g->vlist[key].head;w;w=w->head->link)
			if (!visited[w->head->num])
			{
				printf("%5d", w->head->num);
				enQueue(w->head->num);
				visited[w->head->num] = TRUE;
			}
	}
}
int printGraph(Graph *head) /* printing graph with vertices and edges */
{
	VertexHead* h = head->vlist;
	Vertex *v=(&h[0])->head;
	if (head == NULL)
		return -1;
	for (int i = 0; i < MAX_VERTEX; i++)
		{
			printf("[%2d]->", i);
			if (v!=NULL)
				v = h[i].head;//vetexhead값 표시
			while (v != NULL)
			{
				printf("[v:%d]->", v->num);
				v = v->link;//각vertex출력 후 다음으로 넘겨줌
			}
			printf("NULL\n");
		}
		
	


}
int deQueue()//큐에서 데이터 삭제
{
	int temp;
	front = (front + 1) % (MAX_QUEUE_SIZE);
	temp = queue[front];
	queue[front] = NULL;
	//front값 늘려준 후 전의 값은 NULL로 바꿔줌
	return temp;//front큐 값 반환
}

void enQueue(int key)//큐 추가
{
	rear = (rear + 1) % (MAX_QUEUE_SIZE);
	queue[rear] = key;

}//큐의 rear에 노드를 추가해준 후 rear는 증가시킴

