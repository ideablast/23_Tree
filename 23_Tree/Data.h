#ifndef __Data_H__
#define __Data_H__

typedef struct _Node {
	int L_nData;
	int R_nData;
	struct _Node *L_Next;
	struct _Node *M_Next;
	struct _Node *R_Next;
}Node;



#endif


#define LEFT 100
#define RIGHT 200
#define END 300

#define TRUE 1
#define FALSE 0
#define FAIL -1
