#include "ALL.h"

Node *Create_new_23_node()
{
	Node *temp = (Node*)malloc(sizeof(Node));

	temp->Link[0] = NULL;
	temp->Link[1] = NULL;
	temp->Link[2] = NULL;
	temp->nData.Left = 0;//Left 작은 데이터
	temp->nData.Right = 0;//Right 큰 데이터

	return temp;
}

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
//노드에 정수가 꽉차 있는 상태에서 들어갈때 들어갈 정수가 어떤 범위에 속하는지 확인해줄 함수
/*
리턴 값이 왼쪽: nData.Left가 중앙값
리턴 값이 오른쪽: nData.Right가 중앙값
리턴 값이 중앙: item자체가 중앙값
*/

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

int Type_of_node(Node *cur_node) //현재 노드에서 밑에 자식 노드의 상황을 알려주는 함수
{
	if (cur_node->Link[0] == NULL && cur_node->Link[2] == NULL && cur_node->Link[1] == NULL)
		return NODE_0;
	else if (cur_node->Link[0] != NULL && cur_node->Link[2] != NULL && cur_node->Link[1] == NULL)
		return NODE_2;
	else
		return NODE_3;
}


int Exception_check(Node *cur_node)//예외 상황에 해당하는지 알려주는 함수
{
	if (cur_node->nData.Left < cur_node->Link[0]->nData.Right)
		return LEFT;
	else if (cur_node->nData.Right > cur_node->Link[2]->nData.Left)
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
			//이부분 수정
			if (Count_node_data(top) == 1)
			{
				
				if (Count_node_data(top->Link[0]) == 2)
				{
					top->nData.Right = top->nData.Left;
					top->nData.Left = 0;
					switch (Range_checker(top->Link[0], item))
					{
					case LEFT://들어갈노드의 왼쪽 데이터가 중앙값
						top->nData.Left = top->Link[0]->nData.Left;
						top->Link[0]->nData.Left = item;
						break;
					case RIGHT://들어갈노드의 오른쪽 데이터가 중앙값
						top->nData.Left = top->Link[0]->nData.Right;
						top->Link[0]->nData.Right = item;
						break;
					case CENTER://새로 들어갈 숫자가 중앙값
						top->nData.Left = item;
						break;
					}
				}
				else
					Insert_23_node(top->Link[0], item);

				if (Exception_check(top) == LEFT)
				{
					int temp = 0;
					temp = top->nData.Left;
					top->nData.Left = top->Link[0]->nData.Right;
					top->Link[0]->nData.Right = temp;
				}
			}
			else
				Insert_23_node(top->Link[0], item);

			if (Exception_check(top) == LEFT)
			{
				int temp = 0;
				temp = top->nData.Left;
				top->nData.Left = top->Link[0]->nData.Right;
				top->Link[0]->nData.Right = temp;
			}
			/*기존 코드*/
			/*
			Insert_23_node(top->Link[0], item);
			if (Exception_check(top) == LEFT)
			{
			int temp = 0;
			temp = top->nData.Left;
			top->nData.Left = top->Link[0]->nData.Right;
			top->Link[0]->nData.Right = temp;
			}
			*/
			break;
		case RIGHT:
			if (Count_node_data(top) == 1)
			{
				if (top->nData.Left<item&&top->Link[2]->nData.Left>item)
					top->nData.Right = item;
				else
				{
					//이부분 수정
					if (Count_node_data(top->Link[2]) == 2)
					{
						switch (Range_checker(top->Link[2], item))
						{
						case LEFT://들어갈노드의 왼쪽 데이터가 중앙값
							top->nData.Right = top->Link[2]->nData.Left;
							top->Link[2]->nData.Left = item;
							break;
						case RIGHT://들어갈노드의 오른쪽 데이터가 중앙값
							top->nData.Right = top->Link[2]->nData.Right;
							top->Link[2]->nData.Right = item;
							break;
						case CENTER://새로 들어갈 숫자가 중앙값
							top->nData.Right = item;
							break;
						}
					}
					else
						Insert_23_node(top->Link[2], item);

					if (Exception_check(top) == RIGHT)
					{
						int temp = 0;
						temp = top->nData.Right;
						top->nData.Right = top->Link[2]->nData.Left;
						top->Link[2]->nData.Left = temp;
					}
				}
			}
			else
			{
				Insert_23_node(top->Link[2], item);
				if (Exception_check(top) == RIGHT)
				{
					int temp = 0;
					temp = top->nData.Right;
					top->nData.Right = top->Link[2]->nData.Left;
					top->Link[2]->nData.Left = temp;
				}
			}

			break;
		case CENTER://부모노드의 데이터가 2개인 경우에만 나올 수 있음
			top->Link[1] = Create_new_23_node();
			top->Link[1]->nData.Left = item;

			break;
		}


	}
	else if (Type_of_node(top) == NODE_3)//자식 노드가 3개
	{
		switch (Range_checker(top, item))
		{
		case LEFT:
			/*변경된 코트*/
			if (Count_node_data(top) == 1)
			{
				//이부분 수정
				if (Count_node_data(top->Link[0]) == 2)
				{
					top->nData.Right = top->nData.Left;
					top->nData.Left = 0;
					switch (Range_checker(top->Link[0], item))
					{
					case LEFT://들어갈노드의 왼쪽 데이터가 중앙값
						top->nData.Left = top->Link[0]->nData.Left;
						top->Link[0]->nData.Left = item;
						break;
					case RIGHT://들어갈노드의 오른쪽 데이터가 중앙값
						top->nData.Left = top->Link[0]->nData.Right;
						top->Link[0]->nData.Right = item;
						break;
					case CENTER://새로 들어갈 숫자가 중앙값
						top->nData.Left = item;
						break;
					}
				}
				else
					Insert_23_node(top->Link[0], item);

				if (Exception_check(top) == LEFT)
				{
					int temp = 0;
					temp = top->nData.Left;
					top->nData.Left = top->Link[0]->nData.Right;
					top->Link[0]->nData.Right = temp;
				}

			}
			else
				Insert_23_node(top->Link[0], item);

			if (Exception_check(top) == LEFT)
			{
				int temp = 0;
				temp = top->nData.Left;
				top->nData.Left = top->Link[0]->nData.Right;
				top->Link[0]->nData.Right = temp;
			}

		
			/*변경된 코트*/

			/*기존 코드*/
			/*
			Insert_23_node(top->Link[0], item);
			if (Exception_check(top) == LEFT)
			{
			int temp = 0;
			temp = top->nData.Left;
			top->nData.Left = top->Link[0]->nData.Right;
			top->Link[0]->nData.Right = temp;
			}
			*/
			break;
		case RIGHT:
			if (Count_node_data(top) == 1)
			{
				if (top->nData.Left<item&&top->Link[2]->nData.Left>item)
					top->nData.Right = item;
				else
				{
					//이부분 수정
					if (Count_node_data(top->Link[2]) == 2)
					{
						switch (Range_checker(top->Link[2], item))
						{
						case LEFT://들어갈노드의 왼쪽 데이터가 중앙값
							top->nData.Right = top->Link[2]->nData.Left;
							top->Link[2]->nData.Left = item;
							break;
						case RIGHT://들어갈노드의 오른쪽 데이터가 중앙값
							top->nData.Right = top->Link[2]->nData.Right;
							top->Link[2]->nData.Right = item;
							break;
						case CENTER://새로 들어갈 숫자가 중앙값
							top->nData.Right = item;
							break;
						}
					}
					else
						Insert_23_node(top->Link[2], item);

					if (Exception_check(top) == RIGHT)
					{
						int temp = 0;
						temp = top->nData.Right;
						top->nData.Right = top->Link[2]->nData.Left;
						top->Link[2]->nData.Left = temp;
					}
				}
			}
			else
			{
				Insert_23_node(top->Link[2], item);
				if (Exception_check(top) == RIGHT)
				{
					int temp = 0;
					temp = top->nData.Right;
					top->nData.Right = top->Link[2]->nData.Left;
					top->Link[2]->nData.Left = temp;
				}
			}

			break;
		case CENTER:
			Insert_23_node(top->Link[1], item);

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
		else
		{
			top->Link[0] = Create_new_23_node();
			top->Link[2] = Create_new_23_node();

			switch (Range_checker(top, item))
			{
			case LEFT:
				top->Link[0]->nData.Left = item;
				top->Link[2]->nData.Left = top->nData.Right;
				top->nData.Right = 0;

				break;
			case RIGHT:
				top->Link[0]->nData.Left = top->nData.Left;
				top->nData.Left = top->nData.Right;
				top->nData.Right = 0;
				top->Link[2]->nData.Left = item;

				break;
				/*변경된 코트*/
			case CENTER:
				top->Link[0]->nData.Left = top->nData.Left;
				top->Link[2]->nData.Left = top->nData.Right;
				top->nData.Left = item;
				top->nData.Right = 0;
				/*변경된 코트*/
				break;
			}
		}
	}
}


/*
가운데 노드의 유무가 최우선 순위
부모노드의 왼쪽을 지웠을떄 가운데 노드가 꽉 차있으면 가운데 노드의 왼쪽을 들고 오는게 제일 빠르다.
부모노드의 오른쪽을 지웠을때 가운데 노드가 꽉 차있으면
*/

/*
나머지는 이진트리 처럼
오른쪽에 있는것중 제일 작은것
왼쪽에 있는 것중 제일 큰것
*/

/*
최대한 자리 이동이 적은 경우
같은 우선 순위라면 깊이가 깊은거
*/
int Search_depth(Node *top)
{
	int cnt = 0;

	if (top)
	{
		cnt = Search_depth(top->Link[0]) > Search_depth(top->Link[2]) ? Search_depth(top->Link[0]) : Search_depth(top->Link[2]);
		cnt += 1;
	}
	return cnt;
}

int Node_shape(Node* top)
{
	
}

int Find_perfect_number(Node* top, int item)//지울 숫자를 찾았을때 그 자리를 대체할 숫자를 찾아줄 함수
{
	if (top->Link[1])//중간 자식 노드가 있을때
	{
		if (top->nData.Left == item)//링크: 왼-중-오, 데이터: 왼-오
		{
			int i = 0;
			top->Link[i]
		}
		else
		{

		}
	}
	else// 중간 자식노드가 없을때
	{
		if (top->nData.Left == item)//링크: 오-중-왼, 데이터: 오-왼
		{

		}
		else
		{

		}
	}
}

void Delete_23_node(Node * top, int item)
{
	Node* cur_top_node = top;
	Node* link_backup_node;

	while (1)
	{
		if (top->nData.Left == item || top->nData.Right == item)
		{
			//case 1
			if (Type_of_node(top) == NODE_3)//자식 노드가 3개, 가운데 노드에서 가져오는 것이 가장 빠르므로 그게 최우선
			{
				if (top->nData.Left == item)
				{

				}
				else
				{

				}
			}
			//case 2
			else if (Type_of_node(top) == NODE_2)
			{
				if (top->nData.Left == item)
				{

				}
				else
				{

				}
			}
			//case 3
			else
			{
				//지울노드의 부모노드가 가리키는 링크를 어떻게 수정할지 
				if (top->nData.Left)
				{
					free(top);
					break;
				}
				else
				{
					top->nData.Left = top->nData.Right;
					top->nData.Right = 0;
				}
			}
		}
		else
		{
			switch (Range_checker(cur_top_node, item))
			{
			case LEFT:
				cur_top_node = cur_top_node->Link[0];
				break;
			case RIGHT:
				cur_top_node = cur_top_node->Link[2];
				break;
			case CENTER:
				cur_top_node = cur_top_node->Link[1];
				break;
			}
		}
	}
	
}


void Print_pre_order(Node *top)
{
	if (top)
	{
		printf("(%d,%d) ", top->nData.Left, top->nData.Right);
		Print_pre_order(top->Link[0]);
		Print_pre_order(top->Link[1]);
		Print_pre_order(top->Link[2]);
	}
}
#ifdef NOTYET


if (top->nData.Left == item || top->nData.Right == item)//값을 찾았을떄
{//노드가 3개일떄도 밑에 자식이 있는 경우를 고려해서 제일 작은거 제일 큰거를 당겨줘야한다.
	if (Type_of_node(top) == NODE_3)//자식 노드가 3개, 가운데 노드에서 가져오는 것이 가장 빠르므로 그게 최우선
	{
		if (Count_node_data(top->Link[1]) == 2)
		{
			if (item == top->nData.Left)
			{
				top->nData.Left = top->Link[1]->nData.Left;
				Delete_23_node(top->Link[1], top->Link[1]->nData.Left);
				//검증 필요
				top->Link[1]->nData.Left = top->Link[1]->nData.Right;
				top->Link[1]->nData.Right = 0;
				//검증 필요
				return;
			}
			else if (item == top->nData.Right)
			{
				top->nData.Right = top->Link[1]->nData.Right;
				Delete_23_node(top->Link[1], top->Link[1]->nData.Right);
				top->Link[1]->nData.Right = 0;
				return;
			}
		}
		else
		{
			if (item == top->nData.Left)
			{//임시 노드를 선언 해서 들어간 곳을 알아야 한다.
				top->nData.Left = top->Link[1]->nData.Left;
				Delete_23_node(top->Link[1], top->Link[1]->nData.Left);
				top->Link[1]->nData.Left = top->Link[1]->nData.Right;
				top->Link[1]->nData.Right = 0;
			}
			else if (item == top->nData.Right)
			{
				top->nData.Right = top->Link[1]->nData.Left;
				top->Link[1]->nData.Right = 0;
			}

			return;
		}

	}
	else if (Type_of_node(top) == NODE_2)//자식 노드가 2개, 이진트리 처럼 동작
	{
		if (Count_node_data(top) == 2)//현재 참조 중인 부모노드가 값을 두개 가지고 있을때
		{
			if (top->nData.Left == item)
			{
				if (Type_of_node(top->Link[0]) == NODE_2)
				{
					Node* parent_node = top;
					Node* candidate_node = top->Link[0];

					while (candidate_node->Link[2])
					{
						parent_node = candidate_node;
						candidate_node = candidate_node->Link[2];
					}
					if (Count_node_data(candidate_node) == 2)
					{
						top->nData.Left = candidate_node->nData.Right;
					}
					else
					{

					}
				}
				else if (Type_of_node(top->Link[0]) == NODE_3)
				{

				}

			}
			else if (top->nData.Right == item)
			{
				if (Type_of_node(top->Link[2]) == NODE_2)
				{

				}
				else if (Type_of_node(top->Link[2]) == NODE_3)
				{

				}
			}
		}
		else //값을 1개 가지고 있을때 2진트리 처럼 오른쪽 노드중 가장 작은 값을 가져올 생각
		{
			if (top->nData.Left == item)
			{

			}

		}
	}
	/*
	else//자식 노드가 0개, 예외 처리 필요X
	{
		//어느방향으로 들어왔는지 확인해서 링크를 NULL로 초기화 해줘야함
		if (Count_node_data(top) == 2)
		{


		}
		else
		{
			free(top);
			return;
		}

	}

	*/

}
else//값을 못찾았을때
{
	if (Type_of_node(top) == NODE_3)//자식 노드가 3개, 가운데 노드에서 가져오는 것이 가장 빠르므로 그게 최우선
	{
		switch (Range_checker(top, item))
		{
		case LEFT:
			Delete_23_node(top->Link[0], item);
			break;
		case RIGHT:
			Delete_23_node(top->Link[2], item);
			break;
		case CENTER:
			Delete_23_node(top->Link[1], item);
			break;
		}
	}
	else if (Type_of_node(top) == NODE_2)//자식 노드가 2개, 이진트리 처럼 동작
	{
		switch (Range_checker(top, item))
		{
		case LEFT:
			Delete_23_node(top->Link[0], item);
			break;
		case RIGHT:
			Delete_23_node(top->Link[2], item);
			break;
		}
	}
	else
	{
		return;
	}

}


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
				Insert_23_node(top->Link[0], item);
				if (Exception_check(top) == LEFT)
				{
					int temp = 0;
					temp = top->nData.Left;
					top->nData.Left = top->Link[0]->nData.Right;
					top->Link[0]->nData.Right = temp;
				}

				break;
			case RIGHT:
				if (Count_node_data(top) == 1)
				{
					if (top->nData.Left<item&&top->Link[2]->nData.Left>item)
						top->nData.Right = item;
					else
					{
						Insert_23_node(top->Link[2], item);
						if (Exception_check(top) == RIGHT)
						{
							int temp = 0;
							temp = top->nData.Right;
							top->nData.Right = top->Link[2]->nData.Left;
							top->Link[2]->nData.Left = temp;
						}

					}
				}
				else
				{
					Insert_23_node(top->Link[2], item);
					if (Exception_check(top) == RIGHT)
					{
						int temp = 0;
						temp = top->nData.Right;
						top->nData.Right = top->Link[2]->nData.Left;
						top->Link[2]->nData.Left = temp;
					}
				}

				break;
			case CENTER://부모노드의 데이터가 2개인 경우에만 나올 수 있음
				top->Link[1] = Create_new_23_node();
				top->Link[1]->nData.Left = item;

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
			top->Link[0] = Create_new_23_node();
			top->Link[2] = Create_new_23_node();

			switch (Range_checker(top, item))
			{
			case LEFT:
				top->Link[0]->nData.Left = item;
				top->Link[2]->nData.Left = top->nData.Right;
				top->nData.Right = 0;

				break;
			case RIGHT:
				top->Link[0]->nData.Left = top->nData.Left;
				top->nData.Left = top->nData.Right;
				top->nData.Right = 0;
				top->Link[2]->nData.Left = item;

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
		if (search_node->Link[0] == NULL && search_node->Link[2] == NULL)
			break;

		switch (Range_checker(search_node, item))
		{
		case LEFT:
			search_node = search_node->Link[0];
			break;
		case RIGHT:
			search_node = search_node->Link[2];
			break;
		case CENTER:
			search_node = search_node->Link[1];
			break;
		}
	}
	return search_node;
}

#endif
