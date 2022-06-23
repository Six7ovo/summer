#include <stdio.h>
#include "com.h"
 
int main(void)
{
	unsigned char tmp[15] = {0}; //用于存放读取出来的数据的缓冲区
	int rl; //读取数据的长度（单位：字节）
	int i;
 
	fd = openSerial("/dev/ttyUSB0"); //打开串口，ttyUSB0是串口文件
	
	if(fd < 0)
	{
		printf("open com fail!\n");
		return 0;
	}
	
	EpollInit(fd); //初始化终端事件触发函数epoll,设置要监听的事件及相关参数等
	unsigned char sno[14] = {0XAA, 0X55, 0X02, 0X00, 0X02, 0X00, 0X00, 0X08, 0X00, 0X04, 0X00, 0X02, 0X02, 0X06};
	unsigned char passwd[6] = {0XAA, 0X55};
	int n=0;
	unsigned s[100] = {0};
	const char* errstr = "error!";
	
	write(fd,sno,14);

	
	while(1)
	{
		//ero(tmp,sizeof(tmp)); //把tmp对应的内存块的前sizeof(tmp)个字节置零
		
		rl = ComRead(tmp,2);//读取1个字节放到缓存
         	
		//打印读到的数据
		
		//for(i = 0; i < rl; i++)
		//	printf(" %02x", tmp[i]);
		//printf("\n\n");
		
	        /*for(i = 0; i<rl; i++){
			if(tmp[i]==0xaa){
				int j;
				for(j=0; j<4; j++){
					passwd[2+j] = tmp[i+j];
				}
			}*/
		int j;
		s[n++] = tmp[0];
		if(tmp[0]==0xaa&&tmp[1]==0x55&&n>8){
			
			for(j=0;j<4;j++)
				passwd[5-j]=s[n-j-2];
			for(j=0; j<6; j++)
				printf(" %02x",passwd[j]);
			printf("\n\n");
			write(fd,passwd,6);
			n=0;
			for(j=0; j<6; j++)
				printf(" %02x",passwd[j]);
			printf("\n");
		}
		
		
	}
	close(epid);
	close(fd);
	
	return 0;
}