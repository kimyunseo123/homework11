#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 10
#define MAX_QUEUE 11

int main(void) {
  char command; // 변수 command
	int key; // 변수 key

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
			break;
		case 'v': case 'V': // command 값이 v 또는 V 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값 받기
			break;
		case 'd': case 'D': // command 값이 d 또는 D 일 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값 받기
			break;
    case 'p': case 'P': // command 값이 p 또는 P 일 경우
			break;
		case 'e': case 'E': // command 값이 e 또는 E 일 경우
			break;
		case 't': case 'T': // command 값이 t 또는 T 일 경우
			break;
		case 'q': case 'Q': // command 값이 q 또는 Q 일 경우
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // 입력받은 command 값이 q 또는 Q 이 아닐 경우 동안 진행
	return 1;
}
