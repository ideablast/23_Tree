#include "ALL.h"

Node *Create_new_23_node()
{
	Node *temp = (Node*)malloc(sizeof(Node));

	temp->Link[0] = NULL;
	temp->Link[1] = NULL;
	temp->Link[2] = NULL;
	temp->nData.Left = 0;//Left ���� ������
	temp->nData.Right = 0;//Right ū ������

	return temp;
}

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
//��忡 ������ ���� �ִ� ���¿��� ���� �� ������ � ������ ���ϴ��� Ȯ������ �Լ�
/*
���� ���� ����: nData.Left�� �߾Ӱ�
���� ���� ������: nData.Right�� �߾Ӱ�
���� ���� �߾�: item��ü�� �߾Ӱ�
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
	else//1���� ���
	{
		if (target_node->nData.Left > item)
			return LEFT;
		else if (target_node->nData.Left < item)
			return RIGHT;
	}
	
}

int Type_of_node(Node *cur_node) //���� ��忡�� �ؿ� �ڽ� ����� ��Ȳ�� �˷��ִ� �Լ�
{
	if (cur_node->Link[0] == NULL && cur_node->Link[2] == NULL && cur_node->Link[1] == NULL)
		return NODE_0;
	else if (cur_node->Link[0] != NULL && cur_node->Link[2] != NULL && cur_node->Link[1] == NULL)
		return NODE_2;
	else
		return NODE_3;
}


int Exception_check(Node *cur_node)//���� ��Ȳ�� �ش��ϴ��� �˷��ִ� �Լ�
{
	if (cur_node->nData.Left < cur_node->Link[0]->nData.Right)
		return LEFT;
	else if (cur_node->nData.Right > cur_node->Link[2]->nData.Left)
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
			//�̺κ� ����
			if (Count_node_data(top) == 1)
			{
				
				if (Count_node_data(top->Link[0]) == 2)
				{
					top->nData.Right = top->nData.Left;
					top->nData.Left = 0;
					switch (Range_checker(top->Link[0], item))
					{
					case LEFT://������� ���� �����Ͱ� �߾Ӱ�
						top->nData.Left = top->Link[0]->nData.Left;
						top->Link[0]->nData.Left = item;
						break;
					case RIGHT://������� ������ �����Ͱ� �߾Ӱ�
						top->nData.Left = top->Link[0]->nData.Right;
						top->Link[0]->nData.Right = item;
						break;
					case CENTER://���� �� ���ڰ� �߾Ӱ�
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
			/*���� �ڵ�*/
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
					//�̺κ� ����
					if (Count_node_data(top->Link[2]) == 2)
					{
						switch (Range_checker(top->Link[2], item))
						{
						case LEFT://������� ���� �����Ͱ� �߾Ӱ�
							top->nData.Right = top->Link[2]->nData.Left;
							top->Link[2]->nData.Left = item;
							break;
						case RIGHT://������� ������ �����Ͱ� �߾Ӱ�
							top->nData.Right = top->Link[2]->nData.Right;
							top->Link[2]->nData.Right = item;
							break;
						case CENTER://���� �� ���ڰ� �߾Ӱ�
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
		case CENTER://�θ����� �����Ͱ� 2���� ��쿡�� ���� �� ����
			top->Link[1] = Create_new_23_node();
			top->Link[1]->nData.Left = item;

			break;
		}


	}
	else if (Type_of_node(top) == NODE_3)//�ڽ� ��尡 3��
	{
		switch (Range_checker(top, item))
		{
		case LEFT:
			/*����� ��Ʈ*/
			if (Count_node_data(top) == 1)
			{
				//�̺κ� ����
				if (Count_node_data(top->Link[0]) == 2)
				{
					top->nData.Right = top->nData.Left;
					top->nData.Left = 0;
					switch (Range_checker(top->Link[0], item))
					{
					case LEFT://������� ���� �����Ͱ� �߾Ӱ�
						top->nData.Left = top->Link[0]->nData.Left;
						top->Link[0]->nData.Left = item;
						break;
					case RIGHT://������� ������ �����Ͱ� �߾Ӱ�
						top->nData.Left = top->Link[0]->nData.Right;
						top->Link[0]->nData.Right = item;
						break;
					case CENTER://���� �� ���ڰ� �߾Ӱ�
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

		
			/*����� ��Ʈ*/

			/*���� �ڵ�*/
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
					//�̺κ� ����
					if (Count_node_data(top->Link[2]) == 2)
					{
						switch (Range_checker(top->Link[2], item))
						{
						case LEFT://������� ���� �����Ͱ� �߾Ӱ�
							top->nData.Right = top->Link[2]->nData.Left;
							top->Link[2]->nData.Left = item;
							break;
						case RIGHT://������� ������ �����Ͱ� �߾Ӱ�
							top->nData.Right = top->Link[2]->nData.Right;
							top->Link[2]->nData.Right = item;
							break;
						case CENTER://���� �� ���ڰ� �߾Ӱ�
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
				/*����� ��Ʈ*/
			case CENTER:
				top->Link[0]->nData.Left = top->nData.Left;
				top->Link[2]->nData.Left = top->nData.Right;
				top->nData.Left = item;
				top->nData.Right = 0;
				/*����� ��Ʈ*/
				break;
			}
		}
	}
}


/*
��� ����� ������ �ֿ켱 ����
�θ����� ������ �������� ��� ��尡 �� �������� ��� ����� ������ ��� ���°� ���� ������.
�θ����� �������� �������� ��� ��尡 �� ��������
*/

/*
�������� ����Ʈ�� ó��
�����ʿ� �ִ°��� ���� ������
���ʿ� �ִ� ���� ���� ū��
*/

/*
�ִ��� �ڸ� �̵��� ���� ���
���� �켱 ������� ���̰� ������
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

int Find_perfect_number(Node* top, int item)//���� ���ڸ� ã������ �� �ڸ��� ��ü�� ���ڸ� ã���� �Լ�
{
	if (top->Link[1])//�߰� �ڽ� ��尡 ������
	{
		if (top->nData.Left == item)//��ũ: ��-��-��, ������: ��-��
		{
			int i = 0;
			top->Link[i]
		}
		else
		{

		}
	}
	else// �߰� �ڽĳ�尡 ������
	{
		if (top->nData.Left == item)//��ũ: ��-��-��, ������: ��-��
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
			if (Type_of_node(top) == NODE_3)//�ڽ� ��尡 3��, ��� ��忡�� �������� ���� ���� �����Ƿ� �װ� �ֿ켱
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
				//�������� �θ��尡 ����Ű�� ��ũ�� ��� �������� 
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


if (top->nData.Left == item || top->nData.Right == item)//���� ã������
{//��尡 3���ϋ��� �ؿ� �ڽ��� �ִ� ��츦 ����ؼ� ���� ������ ���� ū�Ÿ� �������Ѵ�.
	if (Type_of_node(top) == NODE_3)//�ڽ� ��尡 3��, ��� ��忡�� �������� ���� ���� �����Ƿ� �װ� �ֿ켱
	{
		if (Count_node_data(top->Link[1]) == 2)
		{
			if (item == top->nData.Left)
			{
				top->nData.Left = top->Link[1]->nData.Left;
				Delete_23_node(top->Link[1], top->Link[1]->nData.Left);
				//���� �ʿ�
				top->Link[1]->nData.Left = top->Link[1]->nData.Right;
				top->Link[1]->nData.Right = 0;
				//���� �ʿ�
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
			{//�ӽ� ��带 ���� �ؼ� �� ���� �˾ƾ� �Ѵ�.
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
	else if (Type_of_node(top) == NODE_2)//�ڽ� ��尡 2��, ����Ʈ�� ó�� ����
	{
		if (Count_node_data(top) == 2)//���� ���� ���� �θ��尡 ���� �ΰ� ������ ������
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
		else //���� 1�� ������ ������ 2��Ʈ�� ó�� ������ ����� ���� ���� ���� ������ ����
		{
			if (top->nData.Left == item)
			{

			}

		}
	}
	/*
	else//�ڽ� ��尡 0��, ���� ó�� �ʿ�X
	{
		//����������� ���Դ��� Ȯ���ؼ� ��ũ�� NULL�� �ʱ�ȭ �������
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
else//���� ��ã������
{
	if (Type_of_node(top) == NODE_3)//�ڽ� ��尡 3��, ��� ��忡�� �������� ���� ���� �����Ƿ� �װ� �ֿ켱
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
	else if (Type_of_node(top) == NODE_2)//�ڽ� ��尡 2��, ����Ʈ�� ó�� ����
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
			case CENTER://�θ����� �����Ͱ� 2���� ��쿡�� ���� �� ����
				top->Link[1] = Create_new_23_node();
				top->Link[1]->nData.Left = item;

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
