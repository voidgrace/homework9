/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);                                                            // head�� ����

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */                 // ������ȸ
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */                // ������ȸ
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */               // ������ȸ
int insert(Node* head, int key);  /* insert a node to the tree */                       // ������, ���� ���� ���� ��� ����
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */        // key���� �ش��ϴ� ����� �ڽĳ�尡 ������ ����, �ƴҰ�� �������
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */           // ������ ������� key���� ������ data ���� �ִ� ��带 ã�� �ּҸ� ��ȯ
Node* searchIterative(Node* head, int key);  /* search the node for the key */          // �ݺ��� ������� key���� ������ data ���� �ִ� ��带 ã�� �ּҸ� ��ȯ
int freeBST(Node* head); /* free all memories allocated to the tree */                  // ��带 �����ϴ� �Լ�

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	printf("[---------------2022041047 ������-----------------]");
	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {               // head�� ����

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)                         // ���� ��尡 �������
		freeBST(*h);                        // ������ �ش�

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)            // ������ȸ
{
	if (ptr != NULL) {                      // NULL�� ��� ����
		inorderTraversal(ptr->left);        // inorder�̹Ƿ� ���� ������ Ž��
		printf("%d ", ptr->key);            // �ش� ����� data�� ���
		inorderTraversal(ptr->right);       // �� ���� ������ ��� Ž��
	}
}

void preorderTraversal(Node* ptr)           // ������ȸ
{
	if (ptr != NULL) {                      // NULL�� ��� ����
		printf("%d ", ptr->key);            // preorder�̹Ƿ� �ش� ����� data�� ���� ���
		preorderTraversal(ptr->left);       // ���� ��� Ž�� ��
		preorderTraversal(ptr->right);      // ������ ��� Ž��
	}
}

void postorderTraversal(Node* ptr)          // ������ȸ
{
	if (ptr != NULL) {                      // NULL�� ��� ����
		postorderTraversal(ptr->left);      // postorder�̹Ƿ� ���� ������ Ž��
		postorderTraversal(ptr->right);     // ������ ��� Ž��
		printf("%d ", ptr->key);            // �ش� ����� data�� ���
	}
}


int insert(Node* head, int key)             // ������, ���� ���� ���� ��� ����
{
	Node *node = head;
	Node *temp = NULL;
	if (head == NULL) {                     // head�� NULL�� ��� ���� �߻�
		printf("initializeBST first\n");
		return -1;
	}
	temp = (Node *)malloc(sizeof(Node));      // ��� ����

	temp->key = key;
	temp->left = NULL;
	temp->right = NULL;
	if (node->left == NULL) {
		node->left = temp;
	}
	else {
		node = node->left;                  // ó�� head->left�� Ʈ���� ��Ʈ�� �����Ƿ� �̵�
		while (1) {
			if (node->key == key) {         // ���� ���� ���� ��� ����
				return 0;
			}
			else if (node->key < key) {    // node-> key���� key���� Ŭ���
				if (node->right == NULL) {  // node->right�� ����ִٸ�
					node->right = temp;     // ��� ����
					return 0;
				}
				else
					node = node->right;     // �ƴҰ�� node->right�� �̵�
			}
			else {                         // node-> key���� key���� ���� ���
				if (node->left == NULL) {   // node->right�� ����ִٸ�
					node->left = temp;      // ��� ����
					return 0;
				}
				else
					node = node->left;      // �ƴҰ�� node->left�� �̵�
			}
		}
	}
	return 0;
}

int deleteLeafNode(Node* head, int key)     // key���� �ش��ϴ� ����� �ڽĳ�尡 ������ ����, �ƴҰ�� �������
{
	Node* node = head;
	Node* previous = NULL;

	while (1) {
		if (node == NULL || node->key == key) {  // node�� NULL Ȥ�� key���� node->key�� ���� ��� �ݺ� ����
			break;
		}
		previous = node;                         // ������ ������ ������ ���� ���� ���� ����� �ּ� ����
		if (node->key <= key && node != head) {  // key���� Ŭ��� right���� �̵� & head �� �ƴҰ��
			node = node->right;
		}
		else
			node = node->left;
	}

	if (node == NULL) {                          // key���� ���� ���� ���� ��尡 �������� �ʴ� ���
		printf("%d is not Found\n", key);
		return -1;
	}
	else if (node->left != node->right) {        // �� ������ �����ϴ� ���� �Ѵ� NULL�϶� �̹Ƿ�
		printf("%d is Not LeafNode\n", node->key); // left�� right�� ���� �ٸ� ��� �ڽ��� �����ϴ� ����̹Ƿ� ����
		return -1;
	}
	else {
		printf("Delet %d", node->key);           // key���� ������ data�� ����� Node�� ���������� ã���� ���
		if (previous->left == node) {            // ���� ������ ������ ��ü�ϴ� �κ�
			previous->left = NULL;
		}
		else {
			previous->right = NULL;
		}
		free(node);
		return 0;
	}
}

Node* searchRecursive(Node* ptr, int key)        // ������ ������� key���� ������ data ���� �ִ� ��带 ã�� �ּҸ� ��ȯ
{
	Node* temp = NULL;
	if (ptr == NULL || ptr->key == key) {        // NULL or node�� data���� key���� ���� ���
		return ptr;                              // ���� ����
	}
	if (ptr->key > key)                          // node�� data�� key ���� ���� �̵��� ��ġ ����
		temp = searchRecursive(ptr->left, key);  // �����Լ� ȣ��
	else
		temp = searchRecursive(ptr->right, key); // �����Լ� ȣ��

	if (temp != NULL) {                          // ����� ��ġ�� ã�Ҵٸ� ���� ��ȯ
		return temp;
	}

	return NULL;
}

Node* searchIterative(Node* head, int key)       // �ݺ��� ������� key���� ������ data ���� �ִ� ��带 ã�� �ּҸ� ��ȯ
{
	Node* node = head->left;
	while (1) {
		if (node == NULL || node->key == key) {  // NULL or node�� data���� key���� ���� ���
			return node;                         // �ݺ�����
		}
		if (node->key <= key) {                  // node�� ������ ��ġ ����
			node = node->right;
		}
		else
			node = node->left;
	}
}


int freeBST(Node* head)                          // ��带 �����ϴ� �Լ�
{
	if (head != NULL) {                          // head�� NULL�� �ƴ� ���
		freeBST(head->left);                     // ���� left�� �̵�
		if (head->right != head)                  // head�� �ƴҰ��
			freeBST(head->right);                // right�� �̵�
		free(head);                              // head ��ü
	}
	head = NULL;
	return 0;
}
