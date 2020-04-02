#include "ALL.h"

int main()
{
	Node *top = Create_new_23_node();
	Insert_23_node(top, 10);
	Insert_23_node(top, 5);
	Insert_23_node(top, 4);
	Insert_23_node(top, 15);
	Insert_23_node(top, 8);
	Insert_23_node(top, 9);
	Insert_23_node(top, 6);
	Insert_23_node(top, 7);
	Insert_23_node(top, 3);
	Insert_23_node(top, 2);
	Insert_23_node(top, 1);
	Insert_23_node(top, 12);
	Insert_23_node(top, 11);

	Print_pre_order(top); puts("");
	printf("%d\n", Search_depth(top));
}

#ifdef EXAMPLE
Insert_23_node(top, 10);
Insert_23_node(top, 5);
Insert_23_node(top, 15);
Insert_23_node(top, 4);
Insert_23_node(top, 8);
Insert_23_node(top, 16);
Insert_23_node(top, 20);
Insert_23_node(top, 12);
Insert_23_node(top, 9);
Insert_23_node(top, 25);
Insert_23_node(top, 18);
Insert_23_node(top, 7);
Insert_23_node(top, 30);
Insert_23_node(top, 11);
Insert_23_node(top, 13);


Insert_23_node(top, 37);
Insert_23_node(top, 33);
Insert_23_node(top, 50);
Insert_23_node(top, 30);
Insert_23_node(top, 35);
Insert_23_node(top, 39);
Insert_23_node(top, 70);
Insert_23_node(top, 90);
Insert_23_node(top, 10);
Insert_23_node(top, 20);
Insert_23_node(top, 32);
Insert_23_node(top, 34);
Insert_23_node(top, 26);
Insert_23_node(top, 38);
Insert_23_node(top, 40);
Insert_23_node(top, 60);
Insert_23_node(top, 80);
Insert_23_node(top, 100);

#endif