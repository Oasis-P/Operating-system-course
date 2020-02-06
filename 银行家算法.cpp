#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <conio.h> 
#include <iostream>
using namespace std;
struct Banker
{	
	int **need2D;   //��������ָ��
	int **allo2D;	//��ǰ�����������ָ��
	int *avai1D;	//ʣ����Դ����ָ��
	int *resource1D;//��������ָ��
	int *queue1D;   //��ȫ����ָ��
	int *count1D;	//������ָ��
};
struct Banker banker;

void TestFunc_pointer2D(unsigned int height, unsigned int width)  /*��ά��̬���鴴������*/
{  
    unsigned int i;						/*  �����Ԫ������Ϊ��int *�����ɸ�ֵ��ָ��int *����ָ��.  */
     banker.need2D= new int *[height];  /*Ϊ�������鿪��һ��ָ�����飬ָ�������ڱ�ʾ������           */
	 banker.allo2D= new int *[height];  /*Ϊ��ǰ����������鿪��һ��ָ�����飬ָ�������ڱ�ʾ������   */

    for(i=0; i<height; ++i)  
    {   
        banker.need2D[i] = new int [width];  /*Ϊ֮ǰ���ٵ����������ÿһ���һ������        */
		banker.allo2D[i] = new int [width];	 /*Ϊ֮ǰ���ٵĵ�ǰ������������ÿһ���һ������*/
	}
} 
void TestFunc_pointer1D(unsigned int height)/*һά��̬���鴴������*/
{
	banker.avai1D=new int[height];		/*Ϊʣ����Դ���鿪�ٿռ�*/
	banker.queue1D=new int[height];		/*Ϊ��ȫ�������鿪�ٿռ�*/
	banker.count1D=new int[height];		/*Ϊ���������鿪�ٿռ�  */
}
int main()
{
	int i,j,l=0,*t;								/*lΪѭ���˳���������l=���̸�����˵�����ڰ�ȫ����*/
	unsigned int height,width;					/*heightΪ��������widthΪ��Դ������*/
	printf("��������̵ĸ�������Դ��������");
	scanf("%d%d",&height,&width);
	TestFunc_pointer2D(height,width);			/*��ά��̬���鴴����������*/
	TestFunc_pointer1D(height);					/*һά��̬���鴴����������*/
	printf("��������Դ��������\n");
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			//scanf("%d",&banker.need2D[i][j]);
			cin>>banker.need2D[i][j];
			printf("%d  ",banker.allo2D[i][j]);
		}
	}
	printf("�����뵱ǰ�����������\n");
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		scanf("%d",&banker.allo2D[i][j]);
		printf("%d  ",banker.allo2D[i][j]);
	}	
	printf("������ʣ����Դ����\n");
	for(j=0;j<width;j++)
	{
		scanf("%d",&banker.avai1D[j]);
		printf("%  ",banker.avai1D[j]);
	}
	for(i=0;i<height;i++)
	{
		banker.count1D[i]=0;	
	}
	do
	{
		
		for(i=0;i<height;i++)/*��һ�е��������ִ����һ��������Ҫ�����ֲ�ͬ��Դ*/
		{	
			for(j=0;j<width;j++)
			{
				if(banker.allo2D[i][j]==0)
					banker.count1D[i]++;		/*�жϽ���ÿ����Դ���ѷ������Ƿ���0�������ǣ�˵��֮ǰ�Ѿ���ɷ��䣬��Դ������*/
			//printf("banker.count1D[%d]=%d\n",i,banker.count1D[i]);
			}
			if(banker.count1D[i]==width)
					break;		/*���ý���ÿ����Դ������Ϊ0��������ѭ��ɨ����һ������*/
			banker.count1D[i]=0;
			for(j=0;j<width;j++)/*ɨ��ý��̵�ÿ����Դ	*/
			{					
				if(banker.need2D[i][j]<=banker.avai1D[j]+banker.allo2D[i][j])
						banker.count1D[i]++;		/* �������������������banker.count1D[i]++ */	
			}	

			//printf("banker.count1D[%d]=%d\n",i,banker.count1D[i]);

			if(banker.count1D[i]==width)/*banker.count1D[i]=����ʱ������ʾÿ����Դ���������Ҫ����з���*/
			{	
				printf("��һ�������ǽ���Դ�����%d���̣����ң���ʹ����Ϻ��ͷŸý�����Դ,��ӵ�ʣ����Դ��\n",i);
				for(j=0;j<width;j++)
				{
					banker.avai1D[j]=banker.allo2D[i][j]+banker.avai1D[j];/*���ý��̵�ÿ����Դ�÷���ɷ�����Դ*/
					//printf("��ǰ�ɷ�����ԴΪ%d=%d\n",j,banker.avai1D[j]);
					banker.allo2D[i][j]=0;/*�ͷŸý�����Դ���ý��̵�ÿ����Դ��Ϊ0*/
				}

				//printf("banker.avai1D[%d]=%d\n",j,banker.avai1D[j]);

				banker.queue1D[l]=i;				/*��ȫ��������  */
				l++;
				banker.count1D[i]=0;					   
			}
			else
				banker.count1D[i]=0;			/*����֮ǰbanker.count1D[i]��ֵ�Ƕ��٣�����Ҫ����*/			
			if(i==height-1 && l!=height)
				i=-1;
		}

		if(l==height)/*ȫ����������ڰ�ȫ���У����򲻴���*/
		{
			printf("���ڰ�ȫ����Ϊ��");
			for(i=0;i<height;i++)/*�����ȫ����*/
			{
				printf("%d  ",banker.queue1D[i]);
			}
			printf("\n");
		}
		else
		{
			printf("�����ڰ�ȫ����\n");
			printf("\n��������ֵ�Ըı䵱ǰ�����ɷ�����Դ��:\n");
			for(j=0;j<width;j++)
			{
				scanf("%d",&banker.avai1D[j]);
				//printf("banker.avai1D[%d]=%d\n",j,banker.avai1D[j]);
			}
		}


	}while(l!=height);
	return 0;
}

