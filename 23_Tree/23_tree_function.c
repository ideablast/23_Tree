#include "ALL.h"

Node *Create_new_23_node()
{
	Node *temp = (Node*)malloc(sizeof(Node));

	temp->L_Next = NULL;
	temp->R_Next = NULL;
	temp->M_Next = NULL;
	temp->nData.Left = 0;//Left 작은 데이터
	temp->nData.Right = 0;//Right 큰 데이터

	return temp;
}


//노드안에서 왼쪽과 오른쪽이 있으면 왼쪽먼저 채워진다.

//노드에 들어있는 정수의 갯수를 확인하는 함수
int Count_node_data(Node *target_node)
{
	if (target_node->nData.Left == 0 && target_node->nData.Right == 0)
		return 0;
	else if (target_node->nData.Left != 0 && target_node->nData.Right == 0)
		return 1;
	else
		return 2;
}


//노드 내에서 두 정수의 위치를 바꿔주는 함수
nData Swap_in(nData target_nData)
{
	int temp;

	temp = target_nData.Left;
	target_nData.Left = target_nData.Right;
	target_nData.Right = temp;

	return target_nData;
}

int Range_checker(Node *target_node, int item)
{
	if (Count_node_data(target_node) == 2)
	{
		if (target_node->nData.Left > item)
			return LEFT;
		else if (target_node->nData.Right < item)
			return RIGHT;
		else
			return CENTER;
	}
	else//1개인 경우
	{
		if (target_node->nData.Left > item)
			return LEFT;
		else if (target_node->nData.Left < item)
			return RIGHT;
	}
	
}

//노드에 정수가 꽉차 있는 상태에서 들어갈때 들어갈 정수가 어떤 범위에 속하는지 확인해줄 함수
/*
리턴 값이 왼쪽: nData.Left가 중앙값
리턴 값이 오른쪽: nData.Right가 중앙값
리턴 값이 중앙: item자체가 중앙값
*/



int Type_of_node(Node *cur_node)
{
	if (cur_node->L_Next == NULL && cur_node->R_Next == NULL && cur_node->M_Next == NULL)
		return NODE_0;
	else if (cur_node->L_Next != NULL && cur_node->R_Next != NULL && cur_node->M_Next == NULL)
		return NODE_2;
	else
		return NODE_3;
}


/*
노드 데이터 0개: 왼쪽 대입
노드 데이터 1개: 크기 비교후 왼오
노드 데이터 2개: 왼쪽보다 작은지->왼쪽 노드, 오른쪽 보다 큰지->오른쪽 노드, else 현재 노드의 양쪽이 꽉 찼는지 확인후
*/


int Exception_check(Node *cur_node)
{
	if (cur_node->nData.Left < cur_node->L_Next->nData.Right)
		return LEFT;
	else if (cur_node->nData.Right > cur_node->R_Next->nData.Left)
		return RIGHT;
	else
		return TRUE;
}

void Insert_23_node(Node * top, int item)//부모노드인 상황
{
	if (Type_of_node(top) == NODE_2)//자식 노드가 2개
	{
		switch (Range_checker(top, item))
		{
		case LEFT:
			Insert_23_node(top->L_Next, item);
			if (Exception_check(top) == LEFT)
			{
				int temp = 0;
				temp = top->nData.Left;
				top->nData.Left = top->L_Next->nData.Right;
				top->L_Next->nData.Right = temp;
			}

			break;
		case RIGHT:
			if (Count_node_data(top) == 1)
			{
				if (top->nData.Left<item&&top->R_Next->nData.Left>item)
					top->nData.Right = item;
				else
				{
					//이부분 수정
					if (Count_node_data(top->R_Next) == 2)
					{
						switch (Range_checker(top->R_Next, item))
						{
						case LEFT://들어갈노드의 왼쪽 데이터가 중앙값
							top->nData.Right = top->R_Next->nData.Left;
							top->R_Next->nData.Left = item;
							break;
						case RIGHT://들어갈노드의 오른쪽 데이터가 중앙값
							top->nData.Right = top->R_Next->nData.Right;
							top->R_Next->nData.Right = item;
							break;
						case CENTER://새로 들어갈 숫자가 중앙값
							top->nData.Right = item;
							break;
						}
					}
					else
						Insert_23_node(top->R_Next, item);

					if (Exception_check(top) == RIGHT)
					{
						int temp = 0;
						temp = top->nData.Right;
						top->nData.Right = top->R_Next->nData.Left;
						top->R_Next->nData.Left = temp;
					}
				}
			}
			else
			{
				Insert_23_node(top->R_Next, item);
				if (Exception_check(top) == RIGHT)
				{
					int temp = 0;
					temp = top->nData.Right;
					top->nData.Right = top->R_Next->nData.Left;
					top->R_Next->nData.Left = temp;
				}
			}

			break;
		case CENTER://부모노드의 데이터가 2개인 경우에만 나올 수 있음
			top->M_Next = Create_new_23_node();
			top->M_Next->nData.Left = item;

			break;
		}


	}
	else if (Type_of_node(top) == NODE_3)//자식 노드가 3개
	{
		switch (Range_checker(top, item))
		{
		case LEFT:
			Insert_23_node(top->L_Next, item);
			if (Exception_check(top) == LEFT)
			{
				int temp = 0;
				temp = top->nData.Left;
				top->nData.Left = top->L_Next->nData.Right;
				top->L_Next->nData.Right = temp;
			}

			break;
		case RIGHT:
			if (Count_node_data(top) == 1)
			{
				if (top->nData.Left<item&&top->R_Next->nData.Left>item)
					top->nData.Right = item;
				else
				{
					//이부분 수정
					if (Count_node_data(top->R_Next) == 2)
					{
						if (top->nData.Right == 0)
						{
							switch (Range_checker(top->R_Next, item))
							{
							case LEFT://들어갈노드의 왼쪽 데이터가 중앙값
								top->nData.Right = top->R_Next->nData.Left;
								top->R_Next->nData.Left = item;
								break;
							case RIGHT://들어갈노드의 오른쪽 데이터가 중앙값
								top->nData.Right = top->R_Next->nData.Right;
								top->R_Next->nData.Right = item;
								break;
							case CENTER://새로 들어갈 숫자가 중앙값
								top->nData.Right = item;
								break;
							}
						}
						else
							Insert_23_node(top->R_Next, item);
					}
					else
						Insert_23_node(top->R_Next, item);

					if (Exception_check(top) == RIGHT)
					{
						int temp = 0;
						temp = top->nData.Right;
						top->nData.Right = top->R_Next->nData.Left;
						top->R_Next->nData.Left = temp;
					}
				}
			}
			else
			{
				Insert_23_node(top->R_Next, item);
				if (Exception_check(top) == RIGHT)
				{
					int temp = 0;
					temp = top->nData.Right;
					top->nData.Right = top->R_Next->nData.Left;
					top->R_Next->nData.Left = temp;
				}
			}

			break;
		case CENTER://부모노드의 데이터가 2개인 경우에만 나올 수 있음
			Insert_23_node(top->M_Next, item);

			break;
		}
	}
	else//자식 노드가 0개, 예외 처리 필요X
	{
		if (Count_node_data(top) == 0)
		{
			top->nData.Left = item;

			return;
		}
		else if (Count_node_data(top) == 1)
		{
			top->nData.Right = item;
			if (top->nData.Left > top->nData.Right)
				top->nData = Swap_in(top->nData);

			return;
		}
		/*
		리턴 값이 왼쪽: nData.Left가 중앙값
		리턴 값이 오른쪽: nData.Right가 중앙값
		리턴 값이 중앙: item자체가 중앙값
		*/
		else
		{
			top->L_Next = Create_new_23_node();
			top->R_Next = Create_new_23_node();

			switch (Range_checker(top, item))
			{
			case LEFT:
				top->L_Next->nData.Left = item;
				top->R_Next->nData.Left = top->nData.Right;
				top->nData.Right = 0;

				break;
			case RIGHT:
				top->L_Next->nData.Left = top->nData.Left;
				top->nData.Left = top->nData.Right;
				top->nData.Right = 0;
				top->R_Next->nData.Left = item;

				break;
			}
		}
	}
}


#ifdef NOTYET

void Insert_23_node(Node * top, int item)//부모노드인 상황
{
	if (Type_of_node(top) == NODE_2)//자식 노드가 2개
	{
		if (Count_node_data(top) == 1)
		{
			top->nData.Right = item;
			if (top->nData.Left > top->nData.Right)
				top->nData = Swap_in(top->nData);
		}
		else//서치 처럼 자신이 들어갈 위치를 찾아간다.
		{
			switch (Range_checker(top, item))
			{
			case LEFT:
				Insert_23_node(top->L_Next, item);
				if (Exception_check(top) == LEFT)
				{
					int temp = 0;
					temp = top->nData.Left;
					top->nData.Left = top->L_Next->nData.Right;
					top->L_Next->nData.Right = temp;
				}

				break;
			case RIGHT:
				if (Count_node_data(top) == 1)
				{
					if (top->nData.Left<item&&top->R_Next->nData.Left>item)
						top->nData.Right = item;
					else
					{
						Insert_23_node(top->R_Next, item);
						if (Exception_check(top) == RIGHT)
						{
							int temp = 0;
							temp = top->nData.Right;
							top->nData.Right = top->R_Next->nData.Left;
							top->R_Next->nData.Left = temp;
						}

					}
				}
				else
				{
					Insert_23_node(top->R_Next, item);
					if (Exception_check(top) == RIGHT)
					{
						int temp = 0;
						temp = top->nData.Right;
						top->nData.Right = top->R_Next->nData.Left;
						top->R_Next->nData.Left = temp;
					}
				}

				break;
			case CENTER://부모노드의 데이터가 2개인 경우에만 나올 수 있음
				top->M_Next = Create_new_23_node();
				top->M_Next->nData.Left = item;

				break;
			}

		}
	}
	else if (Type_of_node(top) == NODE_3)//자식 노드가 3개
	{
		if (Count_node_data(top) == 1)
		{

		}
		else
		{

		}
	}
	else//자식 노드가 0개, 예외 처리 필요X
	{
		if (Count_node_data(top) == 0)
		{
			top->nData.Left = item;

			return;
		}
		else if (Count_node_data(top) == 1)
		{
			top->nData.Right = item;
			if (top->nData.Left > top->nData.Right)
				top->nData = Swap_in(top->nData);

			return;
		}
		/*
		리턴 값이 왼쪽: nData.Left가 중앙값
		리턴 값이 오른쪽: nData.Right가 중앙값
		리턴 값이 중앙: item자체가 중앙값
		*/
		else
		{
			top->L_Next = Create_new_23_node();
			top->R_Next = Create_new_23_node();

			switch (Range_checker(top, item))
			{
			case LEFT:
				top->L_Next->nData.Left = item;
				top->R_Next->nData.Left = top->nData.Right;
				top->nData.Right = 0;

				break;
			case RIGHT:
				top->L_Next->nData.Left = top->nData.Left;
				top->nData.Left = top->nData.Right;
				top->nData.Right = 0;
				top->R_Next->nData.Left = item;

				break;
			}
		}
	}
}
Node* Search_node(Node *top, int item)
{
	Node *search_node = top;

	while (1)
	{
		if (search_node->L_Next == NULL && search_node->R_Next == NULL)
			break;

		switch (Range_checker(search_node, item))
		{
		case LEFT:
			search_node = search_node->L_Next;
			break;
		case RIGHT:
			search_node = search_node->R_Next;
			break;
		case CENTER:
			search_node = search_node->M_Next;
			break;
		}
	}
	return search_node;
}

#endif
