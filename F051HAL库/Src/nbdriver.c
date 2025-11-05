#include "nbdriver.h"
#include "usart.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern Usart2Type Usart2type;
//extern uint32_t AdcValue;

ATCMD_index currentATIndex;//当前的索引，表示当前发到哪一个了

NB_TaskStatus NB_TaskStat;//当前状态

uint8_t retrytime;

uint32_t NBsendTime;//NB的发送时间
uint32_t NBRecvTime;//接收时间

uint8_t serverAddr[] = "142.171.158.200";
//uint8_t serverAddr[] = "64.69.43.237";

uint16_t serverPort = 10234;

uint8_t senddata[4] = {0x11,0x22,0x33,0x44};
uint16_t sendlen = 4;

ATCMD_str AT_cmds[] = 
{
	//复位NB模块期望的字符串,如果超过10000毫秒没收到就是失败,重试1次
	{"AT+NRB\r\n","OK",3000,NO_REC,1},
	//获取信号强度
	{"AT+CSQ\r\n","OK",3000,NO_REC,3},
	//获取IP地址 
	{"AT+CGPADDR\r\n","OK",3000,NO_REC,3},
	//创建TCP socket
	{"AT+NSOCR=STREAM,6,10000\r\n","OK",1000,NO_REC,0},
	//连接服务器
	{"AT+NSOCO=2,","OK",3000,NO_REC,2},
	//发送数据
	{"AT+NNMI=1\r\n","OK",2000,NO_REC,0}, //设置接收数据提示
	{"AT+NSORF=2,10\r\n","OK",2000,NO_REC,0},	//接收数据命令
	{"AT+NSOSD=2,","OK",2000,NO_REC,0},
	//关闭连接
	{"AT+NSOCL=2\r\n","OK",1000,NO_REC,0},

};


//串口发送程序,送indx
void ATSend(ATCMD_index indx){//按照顺序进行发送
	
	uint8_t sendStr[100] = {0};
	//先吧buff里面的东西清除一下
	memset(Usart2type.Usart2DMARecBuff,0,USART2_DMA_REC_SIZE);
	AT_cmds[indx].AtStat = NO_REC;//发送AT指令之后的状态，没有读
	
	currentATIndex = indx;//当前发送的数据记录下来
	//连接服务器是这个字符串
	if(currentATIndex == AT_NSOCO){
		sprintf(sendStr,"%s%s,%d\r\n",AT_cmds[indx].ATSendStr,\
		serverAddr,serverPort);
		
		//连接
	}else if(currentATIndex == AT_NSOSD){
		//%02x%02x一个是高位一个是低位
//		sprintf(sendStr,"%s%d,AA02%02x%02x\r\n",AT_cmds[indx].ATSendStr,\
//		sendlen,(AdcValue>>8) &0xFF,AdcValue&0xFF);
	}else{
		//把字符串拷贝到sendStr
		strcpy(sendStr,AT_cmds[indx].ATSendStr);

		
	}
	//发送指令到huart2中
	HAL_UART_Transmit(&huart2,sendStr,\
	strlen(sendStr),100);
	//串口1也发送一次
	HAL_UART_Transmit(&huart1,sendStr,\
	strlen(sendStr),100);
	
	
	NBsendTime = HAL_GetTick();//获取一个当前时间
	
}
/*
代码功能说明：
asc码转数据的函数
输入：ASCII字符序列（数字0-9、大写字母A-F、小写字母a-f）
处理逻辑：
将每个字符转换为对应的4位十六进制值（0-15）
根据字符位置进行位左移（<<），实现十六进制位的权重计算
输出：合并所有字符值后的32位无符号整数

*/
uint32_t asciiToNumber(uint8_t* p,uint8_t len){
    
    uint32_t ren=0;
    uint8_t i;
    for(i=0;i<len;i++){
        
         if(*p>=0x30 && *p<=0x39){
            ren+= (uint32_t)(*p-'0')<<((len-i-1)*4);
        }else if(*p>=0x41 && *p<=0x46){
            ren+= (uint32_t)(*p-'A'+10)<<((len-i-1)*4);
        }
        else if(*p>=0x61 && *p<=0x66){
            ren+= (uint32_t)(*p-'a'+10)<<((len-i-1)*4);
        }          
        p++;
    }
    return ren;
  
    
};



//一个串口的接收，接收串口指令
void ATRec(void){
	
	uint8_t *strp;
	uint8_t rssi,ber,cid,a = 255,b = 255,c = 255,d = 255;
	uint8_t len = 0;//字节长度
	uint8_t cmd[2];//两个
	uint8_t count = 0;
	char ** result;
	
	//判断是否有数据来了做处理
	if(Usart2type.Usart2RecFlag){
		//判断里面是否包含了对应的字符串
		if(currentATIndex == AT_CSQ){
			
				strp = (uint8_t *)strstr((char *)(Usart2type.Usart2DMARecBuff),"+CSQ");//获取相比与+CSQ中
			if(strp){//就是接收失败的
				sscanf(strp,"+CSQ:%d,%d",&rssi,&ber);//
				if(rssi >0 && rssi<32)
					{
						AT_cmds[currentATIndex].AtStat = SUCCESS_REC;
				}else
					{
						AT_cmds[currentATIndex].AtStat = ERROR_REC;
					}
				}
			}else if(currentATIndex == AT_CGPADDR)
					{//
					strp = strstr(Usart2type.Usart2DMARecBuff,"+CGPADDR");
					if(strp)
						{
							//把IP地址的数值取出来了
							sscanf(strp,"+CGPADDR:%d,%d.%d.%d.%d",&cid,&a,&b,&c,&d);
						//判断IP是否合法
					if(a>0 && a<255 && b>0 && b<255 && c>0 && c<255 && d>0 && d<255 )
						{
							AT_cmds[currentATIndex].AtStat = SUCCESS_REC;
					}else
						{
							AT_cmds[currentATIndex].AtStat = ERROR_REC;
						}
				}
				}
				else if(currentATIndex == AT_NSORF && NB_TaskStat == NB_IDILE)
					{
						//判断数据的字符串和我们接收的字符串是否一致
						//解析字符串
						strp = strstr(Usart2type.Usart2DMARecBuff,"+NSONMI");
						//当你收到了+NSONMI这个字符串你就要进行发送指令
						if(strp)
						{
							NB_TaskStat = NB_SEND;//继续进入发送状态							
						}
					}
					//等待状态的NSORF是
				else if(currentATIndex == AT_NSORF && NB_TaskStat == NB_WAIT)
				{
					//解析服务器下发生的命令
					//l,64.69.43.237,10245,2,BB02,0从这里开始
					strp = &Usart2type.Usart2DMARecBuff[2];
					
					
//					result = split(strp, ',', &count);
					//l,142.171.158.200,10245,2,BB02,0从这里de 2,开始，但是是ask码
					printf("Raw data at strp[21]: %0x\n", strp[24]);  // 应该输出 '2'
					//所以需要进行转换
					len = strp[24] - '0';
					//这里吧BB和0x分别取出来
					cmd[0] = asciiToNumber(&strp[26],2);
					cmd[1] = asciiToNumber(&strp[28],2);
					
					
					printf("len=%d,cmd0=%02x,cmd1=%02x\n",len,cmd[0],cmd[1]);
					
					printf("strp = %s\n",strp);
					if(len == 2)
					{
						if(cmd[0]==0xBB && cmd[1] == 0x01)//01代表关继电器
						{
							HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET);
						}else if (cmd[0]==0xBB && cmd[1] == 0x02)//02代表开继电器
						{
							HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET);
						}
					}
					AT_cmds[currentATIndex].AtStat = SUCCESS_REC;

				}
				
				else
					{
					//判断数据的字符串和我们接收的字符串是否一致
					strp = strstr(Usart2type.Usart2DMARecBuff,AT_cmds[currentATIndex].ATRecStr);
							
					if(strp)
						{//只要不是NULL就是接收成功了
						AT_cmds[currentATIndex].AtStat = SUCCESS_REC;
					}else
						{
						AT_cmds[currentATIndex].AtStat = ERROR_REC;
				}
		}
		HAL_UART_Transmit(&huart1,Usart2type.Usart2DMARecBuff,\
		Usart2type.Usart2DMArecLen,100);
		Usart2type.Usart2RecFlag = 0;
		Usart2type.Usart2DMArecLen = 0;	

		}
	}

//NB初始化函数
void NB_init(){
	NB_TaskStat = NB_SEND;//发送状态
	currentATIndex = AT_NRB;//先是0状态AT_NRB
}
	
	
	//写状态机，把串口接收和发送串在一起,不断的对NB的数据做监控
void NB_Task(void){
	//死循环不断的去检测NB的状态
	while(1){
		switch(NB_TaskStat){
			case NB_IDILE://休息状态,在这里主动接收数据
				if(HAL_GetTick()-NBRecvTime > RECVTIMEOUT)
				{
						ATRec();//接收数据
						NBRecvTime = HAL_GetTick();
				}
					return;
				
			//设置发送状态
			case NB_SEND:
				
					ATSend(currentATIndex);
				
					
			//发送完的状态等待状态
					NB_TaskStat = NB_WAIT;
			
					return;
				case NB_WAIT:
					
				//超时时间
					if(HAL_GetTick() - NBsendTime > AT_cmds[currentATIndex].TimeOut){
						//串口进行接收
						ATRec();
						//如果返回值是成功的
						if(AT_cmds[currentATIndex].AtStat == SUCCESS_REC){
							//现在是接收状态的话发送成功了
							if(currentATIndex == AT_NSORF)
							{
								NB_TaskStat = NB_IDILE;//继续进入等待状态,下次来了就不会进行其他指令了
								return;
							}else
							{
								currentATIndex++;
								retrytime=0;//发送成功清零

								NB_TaskStat = NB_SEND;//继续进入发送状态
							}
						}else{
							if(retrytime<AT_cmds[currentATIndex].retryNum){
								//如果出现接收失败的情况
								NB_TaskStat = NB_SEND;//重新发送一次
								retrytime++;
						}else{
							retrytime = 0;
							NB_TaskStat = NB_IDILE;//继续进入等待状态
							return;
						}
				}
			}
		
		}
	}
}






