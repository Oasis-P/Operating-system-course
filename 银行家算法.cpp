#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <conio.h> 
#include <iostream>
using namespace std;
struct Banker
{	
	int **need2D;   //需求数组指针
	int **allo2D;	//当前分配情况数组指针
	int *avai1D;	//剩余资源数组指针
	int *resource1D;//总量数组指针
	int *queue1D;   //安全序列指针
	int *count1D;	//计数器指针
};
struct Banker banker;

void TestFunc_pointer2D(unsigned int height, unsigned int width)  /*二维动态数组创建函数*/
{  
    unsigned int i;						/*  数组的元素类型为‘int *’，可赋值给指向‘int *’的指针.  */
     banker.need2D= new int *[height];  /*为需求数组开辟一个指针数组，指针数用于表示进程数           */
	 banker.allo2D= new int *[height];  /*为当前分配情况数组开辟一个指针数组，指针数用于表示进程数   */

    for(i=0; i<height; ++i)  
    {   
        banker.need2D[i] = new int [width];  /*为之前开辟的需求数组的每一项开辟一个数组        */
		banker.allo2D[i] = new int [width];	 /*为之前开辟的当前分配情况数组的每一项开辟一个数组*/
	}
} 
void TestFunc_pointer1D(unsigned int height)/*一维动态数组创建函数*/
{
	banker.avai1D=new int[height];		/*为剩余资源数组开辟空间*/
	banker.queue1D=new int[height];		/*为安全队列数组开辟空间*/
	banker.count1D=new int[height];		/*为计数器数组开辟空间  */
}
int main()
{
	int i,j,l=0,*t;								/*l为循环退出条件，若l=进程个数，说明存在安全序列*/
	unsigned int height,width;					/*height为进程数，width为资源种类数*/
	printf("请输入进程的个数和资源种类数：");
	scanf("%d%d",&height,&width);
	TestFunc_pointer2D(height,width);			/*二维动态数组创建函数调用*/
	TestFunc_pointer1D(height);					/*一维动态数组创建函数调用*/
	printf("请输入资源需求数组\n");
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			//scanf("%d",&banker.need2D[i][j]);
			cin>>banker.need2D[i][j];
			printf("%d  ",banker.allo2D[i][j]);
		}
	}
	printf("请输入当前分配情况数组\n");
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		scanf("%d",&banker.allo2D[i][j]);
		printf("%d  ",banker.allo2D[i][j]);
	}	
	printf("请输入剩余资源数组\n");
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
		
		for(i=0;i<height;i++)/*第一行的三个数字代表第一个进程需要的三种不同资源*/
		{	
			for(j=0;j<width;j++)
			{
				if(banker.allo2D[i][j]==0)
					banker.count1D[i]++;		/*判断进程每种资源的已分配量是否都是0，若都是，说明之前已经完成分配，资源被剥夺*/
			//printf("banker.count1D[%d]=%d\n",i,banker.count1D[i]);
			}
			if(banker.count1D[i]==width)
					break;		/*若该进程每个资源需求量为0，则跳出循环扫描下一个进程*/
			banker.count1D[i]=0;
			for(j=0;j<width;j++)/*扫描该进程的每种资源	*/
			{					
				if(banker.need2D[i][j]<=banker.avai1D[j]+banker.allo2D[i][j])
						banker.count1D[i]++;		/* 若符合条件则计数器啊banker.count1D[i]++ */	
			}	

			//printf("banker.count1D[%d]=%d\n",i,banker.count1D[i]);

			if(banker.count1D[i]==width)/*banker.count1D[i]=列数时，即表示每个资源都满足分配要求进行分配*/
			{	
				printf("这一步操作是将资源分配给%d进程，并且，在使用完毕后释放该进程资源,添加到剩余资源中\n",i);
				for(j=0;j<width;j++)
				{
					banker.avai1D[j]=banker.allo2D[i][j]+banker.avai1D[j];/*将该进程的每个资源置放入可分配资源*/
					//printf("当前可分配资源为%d=%d\n",j,banker.avai1D[j]);
					banker.allo2D[i][j]=0;/*释放该进程资源将该进程的每个资源置为0*/
				}

				//printf("banker.avai1D[%d]=%d\n",j,banker.avai1D[j]);

				banker.queue1D[l]=i;				/*安全序列数组  */
				l++;
				banker.count1D[i]=0;					   
			}
			else
				banker.count1D[i]=0;			/*无论之前banker.count1D[i]的值是多少，都需要置零*/			
			if(i==height-1 && l!=height)
				i=-1;
		}

		if(l==height)/*全部进入则存在安全序列，否则不存在*/
		{
			printf("存在安全序列为：");
			for(i=0;i<height;i++)/*输出安全序列*/
			{
				printf("%d  ",banker.queue1D[i]);
			}
			printf("\n");
		}
		else
		{
			printf("不存在安全序列\n");
			printf("\n请输入数值以改变当前各个可分配资源数:\n");
			for(j=0;j<width;j++)
			{
				scanf("%d",&banker.avai1D[j]);
				//printf("banker.avai1D[%d]=%d\n",j,banker.avai1D[j]);
			}
		}


	}while(l!=height);
	return 0;
}

