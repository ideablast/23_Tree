#ifndef __Data_H__
#define __Data_H__
typedef struct _nData {
	int Left;
	int Right;
}nData;

typedef struct _Node {
	nData nData;
	struct _Node *L_Next;
	struct _Node *M_Next;
	struct _Node *R_Next;
}Node;



#endif


#define LEFT 100
#define CENTER 150
#define RIGHT 200

#define NODE_0 250
#define NODE_2 300
#define NODE_3 400


#define TRUE 1
#define FALSE 0
#define FAIL -1
