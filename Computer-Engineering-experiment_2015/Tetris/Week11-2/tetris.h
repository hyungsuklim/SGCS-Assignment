#ifndef _TETRIS_H_
#define _TETRIS_H_


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#define WIDTH	10
#define HEIGHT	22
#define NOTHING	0
#define QUIT	'q'
#define NUM_OF_SHAPE	7
#define NUM_OF_ROTATE	4
#define BLOCK_HEIGHT	4
#define BLOCK_WIDTH	4
#define BLOCK_NUM	3

// menu number
#define MENU_PLAY '1'
#define MENU_RANK '2'
#define MENU_AUTO '3'
#define MENU_EXIT '4'

// ����� �̸��� ����
#define NAMELEN 16
typedef struct Node* _Node;
typedef struct Node{
	int accumulatedScore;
	char recField[HEIGHT][WIDTH];
	_Node* child;

	int curBlockID;
	int recBlockX,recBlockY,recBlockRotate;
	int level;
	_Node parent;
}Node;
/* [blockShapeID][# of rotate][][]*/

const char block[NUM_OF_SHAPE][NUM_OF_ROTATE][BLOCK_HEIGHT][BLOCK_WIDTH] ={
	{/*[0][][][]					�̢̢̢�*/
		{/*[][0][][]*/
			{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}
		},
		{/*[][1][][]*/
			{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}			
		},
		{/*[][2][][]*/
			{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}			
		},
		{/*[][3][][]*/
			{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}
		}
	},
	{/*[1][][][];					  �̢̢�*/
		{/*[][0][][]				      ��*/
			{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 1, 1}, {0, 0, 0, 1}
		},
		{/*[][1][][]*/
			{0, 0, 0, 0}, {0, 0 ,1, 1}, {0, 0, 1, 0}, {0, 0, 1, 0}
		},
		{/*[][2][][]*/
			{0, 0, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 1}, {0, 0, 0, 0}
		},
		{/*[][3][][]*/
			{0, 0, 0, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}
		}
	},
	{/*[2][][][];					  �̢̢�*/
		{/*[][0][][]				  ��*/
			{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 1, 1}, {0, 1, 0, 0}
		},
		{/*[][1][][]*/
			{0, 0, 0, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 1}
		},
		{/*[][2][][]*/
			{0, 0, 0, 0}, {0, 0, 0, 1}, {0, 1, 1, 1}, {0, 0, 0, 0}
		},
		{/*[][3][][]*/
			{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}
		}
	},
	{/*[3][][][];					  �̢̢�*/
		{/*[][0][][]				    ��*/
			{0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}
		},
		{/*[][1][][]*/
			{0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}
		},
		{/*[][2][][]*/
			{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}
		},
		{/*[][3][][]*/
			{0, 0, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}
		}
	},
	{/*[4][][][];					  �̢�*/
		{/*[][0][][]				  �̢�*/
			{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}
		},
		{/*[][1][][]*/
			{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}
		},
		{/*[][2][][]*/
			{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}
		},
		{/*[][3][][]*/
			{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}
		}
	},
	{/*[5][][][];					  �̢�*/
		{/*[][0][][]				�̢�*/
			{0, 0, 0, 0}, {0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}
		},
		{/*[][1][][]*/
			{0, 0, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}			
		},
		{/*[][2][][]*/
			{0, 0, 0, 0}, {0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}			
		},
		{/*[][3][][]*/
			{0, 0, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}			
		}
	},
	{/*[6][][][];					�̢�*/
		{/*[][0][][]				  �̢�*/
			{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 1}
		},
		{/*[][1][][]*/
			{0, 0, 0, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}
		},
		{/*[][2][][]*/
			{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 1}
		},
		{/*[][3][][]*/
			{0, 0, 0, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}
		}
	}
};

char field[HEIGHT][WIDTH];	/* ��Ʈ������ ���� ���� ȭ�� */
int nextBlock[BLOCK_NUM];	/* ���� ������ ID�� ���� ������ ID���� ����; [0]: ���� ����; [1]: ���� ���� */
int blockRotate,blockY,blockX;	/* ���� ������ ȸ��, ������ Y ��ǥ, ������ X ��ǥ*/
int score;			/* ������ ����*/
int gameOver=0;			/* ������ ����Ǹ� 1�� setting�ȴ�.*/
int timed_out;
int rank_num;
int recommendR,recommendY,recommendX; // ��õ ���� ��ġ ����. ���ʴ�� ȸ��, Y ��ǥ, X ��ǥ
int Auto;

/***********************************************************
 *	��Ʈ������ ���  global ������ �ʱ�ȭ ���ش�.
 *	input	: none
 *	return	: none
 ***********************************************************/
void InitTetris();

/***********************************************************
 *	��Ʈ������ ���  interface�� �׷��ش�.
 *	input	: none
 *	return	: none
 ***********************************************************/
void DrawOutline();

/***********************************************************
 *	��Ʈ������ ���õ� Ű�Է��� �޴´�.
 *	input	: none
 *	return	: (int) �Է¹��� command
 *		  KEY_DOWN : ����Ű �Ʒ�
 *		  KEY_UP   : ����Ű ��
 *		  KEY_RIGHT: ����Ű ������
 *		  KEY_LEFT : ����Ű ����
 *		  ' '	   : Space bar
 *		  'q'/'Q'  : quit
 ***********************************************************/
int GetCommand();

/***********************************************************
 *	GetCommand�� �Է¹��� command�� ���� ������ �����Ѵ�.
 *	input	: (int) GetCommand�� ���� command
 *	return	: (int) quit�� ���� �Է��� ���� ��� 0,
 * 		  �׿��� ��� 1�� return�Ѵ�.
 ***********************************************************/
int ProcessCommand(int command);

/***********************************************************
 *	������ ���� �ð�(1��)���� ���������� ȣ��Ǵ� �Լ�
 *	���̻� ������ ���� ���,
 *		������ field�� ��ģ��.
 *		������ ä���� line�� �����.
 *		next block�� current block���� �ٲ��ְ�
 *		block�� ��ǥ�� �ʱ�ȭ �Ѵ�.
 *		���� ������ ȭ�鿡 �׸��� ���ŵ� score�� 
 *		ȭ�鿡 display�Ѵ�.
 *	input	: (int) sig
 *	return	: none
 ***********************************************************/
void BlockDown(int sig);

/***********************************************************
 *	�Էµ� �������� ���������� �Ǵ����ִ� �Լ�.
 *	input	: (char[][]) ������ �������� Ȯ���� �ʵ�
 *		  (int) ���� ������ ��� ID
 *		  (int) ������ ȸ�� Ƚ��
 *		  (int) ������ Y��ǥ
 *		  (int) ������ X��ǥ
 *	return	: (int) �Է¿� ���� ���� �������� �����ϸ� 1
 *		  �������� ������ 0�� return �Ѵ�.
 ***********************************************************/
int CheckToMove(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX);

/***********************************************************
 *	��Ʈ�������� command�� ���� �ٲ� �κи� �ٽ� �׷��ش�.
 *	input	: (char[][]) command���� �ٲ� ������ Ȯ���� �ʵ�
 *		  (int) �ٲ�� �� ����� �˱� ���� command�� �Է����� �޴´�.
 *		  (int) ���� ������ ��� ID
 *		  (int) ������ ȸ�� Ƚ��
 *		  (int) ������ Y��ǥ
 *		  (int) ������ X��ǥ
 *	return	: none
 ***********************************************************/
void DrawChange(char f[HEIGHT][WIDTH],int command,int currentBlock,int blockRotate, int blockY, int blockX);

/***********************************************************
 *	��Ʈ������ ������ ���̴� field�� �׷��ش�.
 *	input	: none
 *	return	: none
 ***********************************************************/
void DrawField();

/***********************************************************
 *	�������� ������ field�� �����ش�.
 *	input	: (char[][]) ������ ���� �ʵ�
 *		  (int) ���� ������ ��� ID
 *		  (int) ������ ȸ�� Ƚ��
 *		  (int) ������ Y��ǥ
 *		  (int) ������ X��ǥ
 *	return	: none
 ***********************************************************/
void AddBlockToField(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX);

/***********************************************************
 *	������ ä���� Line�� �����ϰ� ������ �Ű��ش�.
 *	input	: (char[][]) ������ ä���� line�� Ȯ���� �ʵ�
 *	return	: (int) ������ ������ ������ ���� ����
 ***********************************************************/
int DeleteLine(char f[HEIGHT][WIDTH], int mode);

/***********************************************************
 *	Ŀ���� ��ġ�� �Էµ� x, y�� ��ġ�� �Ű��ִ� ������ �Ѵ�.
 *	input	: (int) Ŀ���� �̵��� y ��ǥ
 *		  (int) Ŀ���� �̵��� x ��ǥ
 *	return	: none
 ***********************************************************/
void gotoyx(int y, int x);

/***********************************************************
 *	��Ʈ������ ȭ�� �����ʻ�ܿ� ���� ���� ������ �׷��ش�..
 *	input	: (int*) ������ ��翡 ���� ID �迭
 *	return	: none
 ***********************************************************/
void DrawNextBlock(int *nextBlock);

/***********************************************************
 *	��Ʈ������ ȭ�� ������ �ϴܿ� Score�� ����Ѵ�.
 *	input	: (int) ����� ����
 *	return	: none
 ***********************************************************/
void PrintScore(int score);

/***********************************************************
 *	�ش� ��ǥ(y,x)�� ���ϴ� ũ��(height,width)�� box�� �׸���.
 *	input	: (int) �׸����� �ϴ� �ڽ��� ���� ��ܸ𼭸��� y ��ǥ
 *		  (int) ���� ��� �𼭸��� x ��ǥ
 *		  (int) �ڽ��� ����
 *		  (int) �ڽ��� ����
 *	return	: none
 ***********************************************************/
void DrawBox(int y,int x, int height, int width);

/***********************************************************
 *	�ش� ��ǥ(y,x)�� ���ϴ� ����� ������ �׸���.
 *	input	: (int) �׸����� �ϴ� �ڽ��� ���� ��ܸ𼭸��� y ��ǥ
 *		  (int) ���� ��� �𼭸��� x ��ǥ
 *		  (int) ������ ���
 *		  (int) ������ ȸ�� Ƚ��
 *		  (char) ������ �׸� ���� ���
 *	return	: none
 ***********************************************************/
void DrawBlock(int y, int x, int blockID,int blockRotate,char tile);

/***********************************************************
 *	������ ������ ��ġ�� �̸� �����ش�.
 *	input	: (int) �׸��ڸ� ������ ������ ���� ��ܸ𼭸��� y ��ǥ
 *		  (int) ���� ��� �𼭸��� x ��ǥ
 *		  (int) ������ ���
 *		  (int) ������ ȸ�� Ƚ��
 *	return	: none
 ***********************************************************/
void DrawShadow(int y, int x, int blockID,int blockRotate);

/***********************************************************
 *	��Ʈ���� ������ �����Ѵ�.
 *	input	: none
 *	return	: none
 ***********************************************************/
void play();

/***********************************************************
 *	�޴��� �����ش�.
 *	input	: none
 *	return	: ����ڰ� �Է��� �޴� ��ȣ
 ***********************************************************/
char menu();

/***********************************************************
 *	rank file�κ��� ��ŷ ������ �о�� ��ŷ ����� �����Ѵ�.
 *	input	: none
 *	return	: none
 ***********************************************************/
void createRankList();

/***********************************************************
 *	ȭ�鿡 ��ŷ ��ϵ��� �����ش�.
 *	input	: none
 *	return	: none
 ***********************************************************/
void rank();

/***********************************************************
 *	rank file�� �����Ѵ�.
 *	input	: none
 *	return	: none
 ***********************************************************/
void writeRankFile();

/***********************************************************
 *	���ο� ��ŷ ������ �߰��Ѵ�.
 *	input	: (int) ���ο� ��ŷ�� ����
 *	return	: none
 ***********************************************************/
void newRank(int score);

/***********************************************************
 *	��õ ���� ��ġ�� ���Ѵ�.
 *	input	: (char[][]) ��õ ���� ��ġ�� ���� �ʵ�
 *		  (int) ���� ������ ���� ������ �߿��� � ������ ���� ��õ���� ����
 *	return	: (int) ��õ ���� ��ġ�� ���� �� ������� ���� ���ھ�
 ***********************************************************/
int recommend(Node *root);

/***********************************************************
 *	��õ ��ɿ� ���� ������ ��ġ�Ͽ� �����ϴ� ������ �����Ѵ�.
 *	input	: none
 *	return	: none
 ***********************************************************/
void recommendedPlay();
void DrawBlockWithFeatures(int y, int x, int blockID, int blockRotate);
int modified_recommend(Node *root);
#endif