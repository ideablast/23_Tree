#ifndef __Data_H__
#define __Data_H__
typedef struct _nData {
	int Left;
	int Right;
}nData;

typedef struct _Node {
	nData nData;
	struct _Node *Link[3];//0:Left, 1:Middle, 2:Right
}Node;



#endif


#define LEFT 100
#define CENTER 150
#define RIGHT 200

#define NODE_0 250
#define NODE_2 350
#define NODE_3 400

#define NODE_LMR 450
#define NODE_LR


#define TRUE 1
#define FALSE 0
#define FAIL -1
