#include <stdio.h> 
#include <stdlib.h> 
int	 total;	//内存总数
int	 beginaddress;//初次分配起始地址

struct	Block
{
	int	addr;	//块的起始地址
	int	size;	// 块的大小
	int	flag;//块的分配状态	1：代表已分配 0：代表未分配；
	int sign;//标记符合调入内存需求大小的差值(最佳算法匹配标识)
}block[100];
int	count=0;	//块的个数，初值为 0，分配一个则加 1，减少一个则减 1

//显示函数模块
void display()	//显示所有块的模块
{
	int i;
	printf("	目前内存情况\n");
	printf("-----------------------------------------------------------\n");
	printf("   块号	  起始地址   大小  分配状态\n");
	for(i=1;i<=count;i++)				
	{				
		printf("    %2d      %3d      %3d    ",i,block[i].addr,block[i].size);
		if (block[i].flag==0)
			printf("未分配\n");
 
		else 
			printf("已分配\n");

	}
	printf("-----------------------------------------------------------\n");
}
 
//进程进入函数，采用首次适应算法

/*采用首次适应算法
首先输入要调入内存的进程的大小。然后在 block 数组中找未分配且比该进程大的块， 
如找到的块和进程一样大，直接将该块设为已分配，如比进程大，该块要分为两块，
一块已分配，一块空闲，并且后面的块依次后移一位。*/

void shoucishiying()
{
	int size;
	int i=1,a=0;
	int j;
	printf("请输入要调入内存的进程大小:"); 
	scanf("%d",&size);
	for(i=1;i<=count;i++) 
		if(block[i].flag==0&&block[i].size>=size)
		{
			if(block[i].size==size) 
				block[i].flag=1;	
			else
			{//向后挪 
				count++;
				for(j=count;j>i+1;j--)
				{
					block[j]=block[j-1];
				}  
				//切分出来的i+1项初始化 
				block[i+1].addr=block[i].addr+size;		
				block[i+1].size=block[i].size-size;
				block[i+1].flag=0; 
				//调入第i项的初始化 
				block[i].size=size;	
				block[i].flag=1;
			}
			break;
		}
		else
			a++;//寻找失败次数 
	if(a==count)//寻找失败次数与count相等，则输出 
		printf("\n\nError:调入内存过大或没有空闲分区,无法调入。\n\n");	
	display();
}
/*采用最佳适应
	首先将空闲分区按分区大小递增的顺序形成一个空闲分区链
	当进程要求分配内存时，第一次找到的满足要求的空闲区必然是最优的*/
void zuijiashiying()
{
	struct Block min;
	int size;
	int i=1;
	int j,n,m=0,a=0;
	for(i=1;i<=count;i++)//sign作为需要调入和所有空闲分区的差值，初始化为0 
		block[i].sign=0;
	printf("请输入要调入内存的进程大小:"); 
	scanf("%d",&size);
	//找到和需要调入内存的进程大小相等的空闲分区直接存入
	for(i=1;i<=count;i++) 
		if(block[i].flag==0&&block[i].size>=size)			
			if(block[i].size==size)
			{
				block[i].flag=1;
				m=1;//作为找到的标志 
			}
			else//如果没有找到就将"size和空闲分区的差值"赋给结构体中sign值
				block[i].sign=block[i].size-size;
		else
			a++;//寻找失败次数 
	//没有与需调入内存大小相等的空闲分区			
	if(m==0&&a!=count)//只有m=0则当没有匹配的空闲分区时仍会执行 
	{	
		min.sign=total;	
		for(i=1;i<=count;i++)//取最小差值项，即sign最小项 
			if(block[i].sign!=0&&min.sign>=block[i].sign)//已被分配的sign=0； 
			{
				min=block[i];//将size最小项赋给min 
				n=i;         //记录最小项的位置 
			}
		//将位于当前存入的内存之后的项向后挪	
		count++;
		for(j=count;j>n+1;j--)
		{
			block[j]=block[j-1];
		}  
		//切分后n+1项初始化 
		block[n+1].addr=block[n].addr+size;		
		block[n+1].size=block[n].size-size;
		block[n+1].flag=0; 
		//调入第n项 的初始化 
		block[n].size=size;	
		block[n].flag=1;
	}	
	if(a==count)//寻找失败次数与count相等，则输出 
		printf("\n\nError:调入内存过大或没有空闲分区,无法调入。\n\n");	
	display();
}
/*下次适应 
	针对首次适应的缺点:优先使用中底地址，高地址部分很少被使用。
	下次适应更改寻找空闲分区的起点为:上次利用下次适应调入内存的地址
	若最后仍未找到适合的空闲分区则从头再开始查找*/
int xiacishiying(int i)//调入上次利用下次适应调入内存的地址 
{
	int size;
	int n=i,m=0,a=0;
	int j;
	printf("请输入要调入内存的进程大小:"); 
	scanf("%d",&size);
	//利用下次适应调入内存的地址 
	for(i;i<=count;i++) 
		if(block[i].flag==0&&block[i].size>=size)
		{	//找到和size相等的空闲分区直接存入 
			if(block[i].size==size) 
				block[i].flag=1;
			else
			{	//向后挪位 
				count++;
				for(j=count;j>i+1;j--)
				{
					block[j]=block[j-1];
				}  
				 //切分出来的i+1项初始化
				block[i+1].addr=block[i].addr+size;		
				block[i+1].size=block[i].size-size;
				block[i+1].flag=0; 
				//调入第i项的初始化
				block[i].size=size;	
				block[i].flag=1;
			}
			m=1;
			break;
		}
		else
		a++;//寻找失败次数 
	if(m!=1)
	for(i=1;i<n;i++) 
		if(block[i].flag==0&&block[i].size>=size)
		{	//找到和size相等的空闲分区直接存入 
			if(block[i].size==size) 
				block[i].flag=1;
			else
			{	//向后挪 
				count++;
				for(j=count;j>i+1;j--)
				{
					block[j]=block[j-1];
				}  
				//切分出来的i+1项初始化
				block[i+1].addr=block[i].addr+size;		
				block[i+1].size=block[i].size-size;
				block[i+1].flag=0; 
				//调入第i项的初始化
				block[i].size=size;	
				block[i].flag=1;
			}
			m=1;
			break;
		}
		else
		a++;//寻找失败次数 
	if(a==count)//寻找失败次数与count相等，则输出 
		printf("\n\nError:调入内存过大或没有空闲分区,无法调入。\n\n");	
	display();
	return i;
}
//进程退出函数,释放内存
void jinchengExit()	//作业调出内存模块
{	
	int	kuaihao;
	int	i;
	printf("请输入要调出内存的块号:");
	scanf("%d",&kuaihao);
	//如果输入的调出块号不在序列中 
	if(kuaihao>count)
	{
		printf("\n所输入块号不在当前序列中\n\n");
		jinchengExit();
	}
	else
	{   //调出的内存块为空闲则无需调出 
		if(block[kuaihao].flag==0)
			printf("\n该块内存是空闲的,无需调出\n\n");
		else
		{	
			//将该块设为空闲，就是将该块的 flag 设为 0，
			//还考虑了该块的下一块如果是空闲的，则将这两块合并为一块，总块数减 1
			//如果要考虑该块的前一块是空闲，则将这两块合并为一块，总块数减 1，如何改代码？
			//if()
			block[kuaihao].flag=0; 
			//该块下一块为空闲则两块合并,如果调出的为最后一块则无需考虑下一块         二 
			if(kuaihao<count&&block[kuaihao+1].flag==0)
			{
 
				block[kuaihao].size=block[kuaihao].size+block[kuaihao+1].size; 
				for(i=kuaihao+2;i<=count;i++)
					block[i-1]=block[i]; 
				count--;
			}
			//该块上一块为空闲则两块合并，但如果调出的为第一块则无需考虑上一块        三 
			if(kuaihao!=1&&block[kuaihao-1].flag==0)
			{	
				block[kuaihao-1].size=block[kuaihao-1].size+block[kuaihao].size;
		  		for(i=kuaihao+1;i<=count;i++)
					block[i-1]=block[i];
				count--; 
			}
		}
		display();
	}
}

void main()
{
	int exit_flag=0,select1,select2,n=1;
	//int total,beginaddress;
	printf("\n请输入本次模拟内存分区的起始地址和终止地址:");
	scanf("%d %d",&beginaddress,&total);
	//第一块初始化
	block[1].addr=beginaddress; 
	block[1].flag=0;
	block[1].size=total-beginaddress; 
	count=1;
	display(); 
	while(exit_flag==0) 
	{
		printf("    请输入相应操作\n");
		printf("    1.  进程进入内存 \n");											   
		printf("    2.  进程退出内存\n");
		printf("    3.  显示当前状态\n");
		printf("    4.  退出\n");	
		printf("\n  请选择: ");
		scanf("%d",&select1);
 
		if(select1==1)
		{
			printf("    请选择存储算法:\n");
			printf("    1.  首次适应(从空闲分区低地址开始查找，找到合适位置即存入)\n");											   
			printf("    2.  最佳适应(在空闲分区内找到最佳存储位置后存入)\n");
			printf("    3.  下次适应(从上次使用该算法位置开始查找，找到合适为止后存入)\n");
			printf("\n  请选择: ");
			scanf("%d",&select2);
			if(select2==1) 
			shoucishiying();
			if(select2==2)
			zuijiashiying();
			if(select2==3)
			n=xiacishiying(n);//记录上次利用下次适应调入内存的地址
		}
		if(select1==2)
			jinchengExit();
		if(select1==3)
			display();
		if(select1==4)
			break;
	}
}
