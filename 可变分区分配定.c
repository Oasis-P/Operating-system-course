#include <stdio.h> 
#include <stdlib.h> 
int	 total;	//�ڴ�����
int	 beginaddress;//���η�����ʼ��ַ

struct	Block
{
	int	addr;	//�����ʼ��ַ
	int	size;	// ��Ĵ�С
	int	flag;//��ķ���״̬	1�������ѷ��� 0������δ���䣻
	int sign;//��Ƿ��ϵ����ڴ������С�Ĳ�ֵ(����㷨ƥ���ʶ)
}block[100];
int	count=0;	//��ĸ�������ֵΪ 0������һ����� 1������һ����� 1

//��ʾ����ģ��
void display()	//��ʾ���п��ģ��
{
	int i;
	printf("	Ŀǰ�ڴ����\n");
	printf("-----------------------------------------------------------\n");
	printf("   ���	  ��ʼ��ַ   ��С  ����״̬\n");
	for(i=1;i<=count;i++)				
	{				
		printf("    %2d      %3d      %3d    ",i,block[i].addr,block[i].size);
		if (block[i].flag==0)
			printf("δ����\n");
 
		else 
			printf("�ѷ���\n");

	}
	printf("-----------------------------------------------------------\n");
}
 
//���̽��뺯���������״���Ӧ�㷨

/*�����״���Ӧ�㷨
��������Ҫ�����ڴ�Ľ��̵Ĵ�С��Ȼ���� block ��������δ�����ұȸý��̴�Ŀ飬 
���ҵ��Ŀ�ͽ���һ����ֱ�ӽ��ÿ���Ϊ�ѷ��䣬��Ƚ��̴󣬸ÿ�Ҫ��Ϊ���飬
һ���ѷ��䣬һ����У����Һ���Ŀ����κ���һλ��*/

void shoucishiying()
{
	int size;
	int i=1,a=0;
	int j;
	printf("������Ҫ�����ڴ�Ľ��̴�С:"); 
	scanf("%d",&size);
	for(i=1;i<=count;i++) 
		if(block[i].flag==0&&block[i].size>=size)
		{
			if(block[i].size==size) 
				block[i].flag=1;	
			else
			{//���Ų 
				count++;
				for(j=count;j>i+1;j--)
				{
					block[j]=block[j-1];
				}  
				//�зֳ�����i+1���ʼ�� 
				block[i+1].addr=block[i].addr+size;		
				block[i+1].size=block[i].size-size;
				block[i+1].flag=0; 
				//�����i��ĳ�ʼ�� 
				block[i].size=size;	
				block[i].flag=1;
			}
			break;
		}
		else
			a++;//Ѱ��ʧ�ܴ��� 
	if(a==count)//Ѱ��ʧ�ܴ�����count��ȣ������ 
		printf("\n\nError:�����ڴ�����û�п��з���,�޷����롣\n\n");	
	display();
}
/*���������Ӧ
	���Ƚ����з�����������С������˳���γ�һ�����з�����
	������Ҫ������ڴ�ʱ����һ���ҵ�������Ҫ��Ŀ�������Ȼ�����ŵ�*/
void zuijiashiying()
{
	struct Block min;
	int size;
	int i=1;
	int j,n,m=0,a=0;
	for(i=1;i<=count;i++)//sign��Ϊ��Ҫ��������п��з����Ĳ�ֵ����ʼ��Ϊ0 
		block[i].sign=0;
	printf("������Ҫ�����ڴ�Ľ��̴�С:"); 
	scanf("%d",&size);
	//�ҵ�����Ҫ�����ڴ�Ľ��̴�С��ȵĿ��з���ֱ�Ӵ���
	for(i=1;i<=count;i++) 
		if(block[i].flag==0&&block[i].size>=size)			
			if(block[i].size==size)
			{
				block[i].flag=1;
				m=1;//��Ϊ�ҵ��ı�־ 
			}
			else//���û���ҵ��ͽ�"size�Ϳ��з����Ĳ�ֵ"�����ṹ����signֵ
				block[i].sign=block[i].size-size;
		else
			a++;//Ѱ��ʧ�ܴ��� 
	//û����������ڴ��С��ȵĿ��з���			
	if(m==0&&a!=count)//ֻ��m=0��û��ƥ��Ŀ��з���ʱ�Ի�ִ�� 
	{	
		min.sign=total;	
		for(i=1;i<=count;i++)//ȡ��С��ֵ���sign��С�� 
			if(block[i].sign!=0&&min.sign>=block[i].sign)//�ѱ������sign=0�� 
			{
				min=block[i];//��size��С���min 
				n=i;         //��¼��С���λ�� 
			}
		//��λ�ڵ�ǰ������ڴ�֮��������Ų	
		count++;
		for(j=count;j>n+1;j--)
		{
			block[j]=block[j-1];
		}  
		//�зֺ�n+1���ʼ�� 
		block[n+1].addr=block[n].addr+size;		
		block[n+1].size=block[n].size-size;
		block[n+1].flag=0; 
		//�����n�� �ĳ�ʼ�� 
		block[n].size=size;	
		block[n].flag=1;
	}	
	if(a==count)//Ѱ��ʧ�ܴ�����count��ȣ������ 
		printf("\n\nError:�����ڴ�����û�п��з���,�޷����롣\n\n");	
	display();
}
/*�´���Ӧ 
	����״���Ӧ��ȱ��:����ʹ���е׵�ַ���ߵ�ַ���ֺ��ٱ�ʹ�á�
	�´���Ӧ����Ѱ�ҿ��з��������Ϊ:�ϴ������´���Ӧ�����ڴ�ĵ�ַ
	�������δ�ҵ��ʺϵĿ��з������ͷ�ٿ�ʼ����*/
int xiacishiying(int i)//�����ϴ������´���Ӧ�����ڴ�ĵ�ַ 
{
	int size;
	int n=i,m=0,a=0;
	int j;
	printf("������Ҫ�����ڴ�Ľ��̴�С:"); 
	scanf("%d",&size);
	//�����´���Ӧ�����ڴ�ĵ�ַ 
	for(i;i<=count;i++) 
		if(block[i].flag==0&&block[i].size>=size)
		{	//�ҵ���size��ȵĿ��з���ֱ�Ӵ��� 
			if(block[i].size==size) 
				block[i].flag=1;
			else
			{	//���Ųλ 
				count++;
				for(j=count;j>i+1;j--)
				{
					block[j]=block[j-1];
				}  
				 //�зֳ�����i+1���ʼ��
				block[i+1].addr=block[i].addr+size;		
				block[i+1].size=block[i].size-size;
				block[i+1].flag=0; 
				//�����i��ĳ�ʼ��
				block[i].size=size;	
				block[i].flag=1;
			}
			m=1;
			break;
		}
		else
		a++;//Ѱ��ʧ�ܴ��� 
	if(m!=1)
	for(i=1;i<n;i++) 
		if(block[i].flag==0&&block[i].size>=size)
		{	//�ҵ���size��ȵĿ��з���ֱ�Ӵ��� 
			if(block[i].size==size) 
				block[i].flag=1;
			else
			{	//���Ų 
				count++;
				for(j=count;j>i+1;j--)
				{
					block[j]=block[j-1];
				}  
				//�зֳ�����i+1���ʼ��
				block[i+1].addr=block[i].addr+size;		
				block[i+1].size=block[i].size-size;
				block[i+1].flag=0; 
				//�����i��ĳ�ʼ��
				block[i].size=size;	
				block[i].flag=1;
			}
			m=1;
			break;
		}
		else
		a++;//Ѱ��ʧ�ܴ��� 
	if(a==count)//Ѱ��ʧ�ܴ�����count��ȣ������ 
		printf("\n\nError:�����ڴ�����û�п��з���,�޷����롣\n\n");	
	display();
	return i;
}
//�����˳�����,�ͷ��ڴ�
void jinchengExit()	//��ҵ�����ڴ�ģ��
{	
	int	kuaihao;
	int	i;
	printf("������Ҫ�����ڴ�Ŀ��:");
	scanf("%d",&kuaihao);
	//�������ĵ�����Ų��������� 
	if(kuaihao>count)
	{
		printf("\n�������Ų��ڵ�ǰ������\n\n");
		jinchengExit();
	}
	else
	{   //�������ڴ��Ϊ������������� 
		if(block[kuaihao].flag==0)
			printf("\n�ÿ��ڴ��ǿ��е�,�������\n\n");
		else
		{	
			//���ÿ���Ϊ���У����ǽ��ÿ�� flag ��Ϊ 0��
			//�������˸ÿ����һ������ǿ��еģ���������ϲ�Ϊһ�飬�ܿ����� 1
			//���Ҫ���Ǹÿ��ǰһ���ǿ��У���������ϲ�Ϊһ�飬�ܿ����� 1����θĴ��룿
			//if()
			block[kuaihao].flag=0; 
			//�ÿ���һ��Ϊ����������ϲ�,���������Ϊ���һ�������迼����һ��         �� 
			if(kuaihao<count&&block[kuaihao+1].flag==0)
			{
 
				block[kuaihao].size=block[kuaihao].size+block[kuaihao+1].size; 
				for(i=kuaihao+2;i<=count;i++)
					block[i-1]=block[i]; 
				count--;
			}
			//�ÿ���һ��Ϊ����������ϲ��������������Ϊ��һ�������迼����һ��        �� 
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
	printf("\n�����뱾��ģ���ڴ��������ʼ��ַ����ֹ��ַ:");
	scanf("%d %d",&beginaddress,&total);
	//��һ���ʼ��
	block[1].addr=beginaddress; 
	block[1].flag=0;
	block[1].size=total-beginaddress; 
	count=1;
	display(); 
	while(exit_flag==0) 
	{
		printf("    ��������Ӧ����\n");
		printf("    1.  ���̽����ڴ� \n");											   
		printf("    2.  �����˳��ڴ�\n");
		printf("    3.  ��ʾ��ǰ״̬\n");
		printf("    4.  �˳�\n");	
		printf("\n  ��ѡ��: ");
		scanf("%d",&select1);
 
		if(select1==1)
		{
			printf("    ��ѡ��洢�㷨:\n");
			printf("    1.  �״���Ӧ(�ӿ��з����͵�ַ��ʼ���ң��ҵ�����λ�ü�����)\n");											   
			printf("    2.  �����Ӧ(�ڿ��з������ҵ���Ѵ洢λ�ú����)\n");
			printf("    3.  �´���Ӧ(���ϴ�ʹ�ø��㷨λ�ÿ�ʼ���ң��ҵ�����Ϊֹ�����)\n");
			printf("\n  ��ѡ��: ");
			scanf("%d",&select2);
			if(select2==1) 
			shoucishiying();
			if(select2==2)
			zuijiashiying();
			if(select2==3)
			n=xiacishiying(n);//��¼�ϴ������´���Ӧ�����ڴ�ĵ�ַ
		}
		if(select1==2)
			jinchengExit();
		if(select1==3)
			display();
		if(select1==4)
			break;
	}
}
