#include "ALL.h"

Node *Create_new_23_node()
{
	Node *temp = (Node*)malloc(sizeof(Node));

	temp->L_Next = NULL;
	temp->R_Next = NULL;
	temp->M_Next = NULL;
	temp->nData.Left = 0;//Left ���� ������
	temp->nData.Right = 0;//Right ū ������

	return temp;
}


//���ȿ��� ���ʰ� �������� ������ ���ʸ��� ä������.

//��忡 ����ִ� ������ ������ Ȯ���ϴ� �Լ�
int Count_node_data(Node *target_node)
{
	if (target_node->nData.Left == 0 && target_node->nData.Right == 0)
		return 0;
	else if (target_node->nData.Left != 0 && target_node->nData.Right == 0)
		return 1;
	else
		return 2;
}


//��� ������ �� ������ ��ġ�� �ٲ��ִ� �Լ�
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
	else//1���� ���
	{
		if (target_node->nData.Left > item)
			return LEFT;
		else if (target_node->nData.Left < item)
			return RIGHT;
	}
	
}

//��忡 ������ ���� �ִ� ���¿��� ���� �� ������ � ������ ���ϴ��� Ȯ������ �Լ�
/*
���� ���� ����: nData.Left�� �߾Ӱ�
���� ���� ������: nData.Right�� �߾Ӱ�
���� ���� �߾�: item��ü�� �߾Ӱ�
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
��� ������ 0��: ���� ����
��� ������ 1��: ũ�� ���� �޿�
��� ������ 2��: ���ʺ��� ������->���� ���, ������ ���� ū��->������ ���, else ���� ����� ������ �� á���� Ȯ����
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

void Insert_23_node(Node * top, int item)//�θ����� ��Ȳ
{
	if (Type_of_node(top) == NODE_2)//�ڽ� ��尡 2��
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
					//�̺κ� ����
					if (Count_node_data(top->R_Next) == 2)
					{
						switch (Range_checker(top->R_Next, item))
						{
						case LEFT://������� ���� �����Ͱ� �߾Ӱ�
							top->nData.Right = top->R_Next->nData.Left;
							top->R_Next->nData.Left = item;
							break;
						case RIGHT://������� ������ �����Ͱ� �߾Ӱ�
							top->nData.Right = top->R_Next->nData.Right;
							top->R_Next->nData.Right = item;
							break;
						case CENTER://���� �� ���ڰ� �߾Ӱ�
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
		case CENTER://�θ����� �����Ͱ� 2���� ��쿡�� ���� �� ����
			top->M_Next = Create_new_23_node();
			top->M_Next->nData.Left = item;

			break;
		}


	}
	else if (Type_of_node(top) == NODE_3)//�ڽ� ��尡 3��
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
					//�̺κ� ����
					if (Count_node_data(top->R_Next) == 2)
					{
						if (top->nData.Right == 0)
						{
							switch (Range_checker(top->R_Next, item))
							{
							case LEFT://������� ���� �����Ͱ� �߾Ӱ�
								top->nData.Right = top->R_Next->nData.Left;
								top->R_Next->nData.Left = item;
								break;
							case RIGHT://������� ������ �����Ͱ� �߾Ӱ�
								top->nData.Right = top->R_Next->nData.Right;
								top->R_Next->nData.Right = item;
								break;
							case CENTER://���� �� ���ڰ� �߾Ӱ�
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
		case CENTER://�θ����� �����Ͱ� 2���� ��쿡�� ���� �� ����
			Insert_23_node(top->M_Next, item);

			break;
		}
	}
	else//�ڽ� ��尡 0��, ���� ó�� �ʿ�X
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
		���� ���� ����: nData.Left�� �߾Ӱ�
		���� ���� ������: nData.Right�� �߾Ӱ�
		���� ���� �߾�: item��ü�� �߾Ӱ�
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

void Insert_23_node(Node * top, int item)//�θ����� ��Ȳ
{
	if (Type_of_node(top) == NODE_2)//�ڽ� ��尡 2��
	{
		if (Count_node_data(top) == 1)
		{
			top->nData.Right = item;
			if (top->nData.Left > top->nData.Right)
				top->nData = Swap_in(top->nData);
		}
		else//��ġ ó�� �ڽ��� �� ��ġ�� ã�ư���.
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
			case CENTER://�θ����� �����Ͱ� 2���� ��쿡�� ���� �� ����
				top->M_Next = Create_new_23_node();
				top->M_Next->nData.Left = item;

				break;
			}

		}
	}
	else if (Type_of_node(top) == NODE_3)//�ڽ� ��尡 3��
	{
		if (Count_node_data(top) == 1)
		{

		}
		else
		{

		}
	}
	else//�ڽ� ��尡 0��, ���� ó�� �ʿ�X
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
		���� ���� ����: nData.Left�� �߾Ӱ�
		���� ���� ������: nData.Right�� �߾Ӱ�
		���� ���� �߾�: item��ü�� �߾Ӱ�
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
