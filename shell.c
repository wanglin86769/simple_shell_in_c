/** 
 * shell.c - Shell utility demo which is very useful for testing of hardware register access 
 * 
 * Author: Lin Wang
 * Email: wanglin@ihep.ac.cn
 * Create date: November 8th, 2022
 */
 

/* Includes */ 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/* Type definitions */
typedef int STATUS;
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;


/* Return values */
#define OK 0
#define ERROR -1


/* Register buffer size */
#define REG_BUF_SIZE 0x100000 /* 1MB */


/* Commands index */
#define CMD_HELP                    0
#define CMD_MULTI_REG_READ          1
#define CMD_MULTI_REG_WRITE         2
#define CMD_REG_READ                3
#define CMD_REG_WRITE               4
#define CMD_UINT8_REG_READ          5
#define CMD_UINT8_REG_WRITE         6
#define CMD_UINT16_REG_READ         7
#define CMD_UINT16_REG_WRITE        8
#define CMD_UINT32_REG_READ         9
#define CMD_UINT32_REG_WRITE        10
#define CMD_EXIT                    11
#define CMD_NUM                     12


/* Buffer to emulate the hareware registers */
UINT8 regBuffer[REG_BUF_SIZE] = {0};


/* List valid commands */
const char * cmdList[] = { "help", "mread", "mwrite", "read", "write", \
                           "read8", "write8", "read16", "write16", \
                           "read32", "write32", "exit"};

/* UINT8 register data read */
STATUS uint8Read(UINT32 addr, UINT8 *retData) 
{
    *retData = *(UINT8 *)(regBuffer + addr);
    return OK;
}

/* UINT8 register data write */
STATUS uint8Write(UINT32 addr, UINT8 data) 
{
    *(UINT8 *)(regBuffer + addr) = data;
    return OK;
}

/* UINT16 register data read */
STATUS uint16Read(UINT32 addr, UINT16 *retData) 
{
    *retData = *(UINT16 *)(regBuffer + addr);
    return OK;
}

/* UINT16 register data write */
STATUS uint16Write(UINT32 addr, UINT16 data) 
{
    *(UINT16 *)(regBuffer + addr) = data;
    return OK;
}

/* UINT32 register data read */
STATUS uint32Read(UINT32 addr, UINT32 *retData) 
{
    *retData = *(UINT32 *)(regBuffer + addr);
    return OK;
}

/* UINT32 register data write */
STATUS uint32Write(UINT32 addr, UINT32 data) 
{
    *(UINT32 *)(regBuffer + addr) = data;
    return OK;
}


int main(int argc, char* argv[])
{
    int i;
    char strInput[100];
    char *cmdString, *arg1, *arg2;
    int cmdIndex;
    char* stopstring;
    
    UINT32 addr, data, count;
    
    UINT8 retData8;
    UINT16 retData16;
    UINT32 retData32;
    UINT32 retMultipleData[10000];
    
    UINT32 testData[9] = {0x11111111, 0x22222222, 0x33333333, 0x44444444, 0x55555555, 0x66666666, 0x77777777, 0x88888888, 0x99999999};
    
    printf("#####  Welcome to the shell utility for hardware registers access  #####\n");
    printf("#####     Please press \"help\" to list the supported commands     #####\n");
  
    printf("->");
    fflush(stdout);
  
    /* Infinite loop for shell command parsing */
    while(fgets(strInput, sizeof(strInput), stdin) !=0)
    {
		/* Replace the ENTER with \0 */
		for(i=0; i<sizeof(strInput); i++) {
		    if(strInput[i] == 10) {
		        strInput[i] = 0;
		    }
		}

		if(strInput[0] == 0)
		{
		    printf("->");
		    fflush(stdout);
		    continue;
		}
		 
		/* Split command and parameters */
		strtok(strInput," ");
		cmdString = strInput;
			
		/* Find the corresponding command */
		for(int i=0; i<CMD_NUM; i++)
		{
		    if(!strcmp(cmdList[i], cmdString))
		    {
		        cmdIndex = i;
		        break;
		    }
		    else if(i == CMD_NUM - 1)
		    {
		        cmdIndex = -1;
		    }
		}
			
		switch (cmdIndex)
		{
		    case CMD_HELP:
		        printf("Valid commands:\n");
		        printf("help                            - show valid commands\n");
		        printf("mread    addr count             - read multiple registers of FPGA\n");
		        printf("mwrite                          - write multiple registers of FPGA\n");
		        printf("read     addr                   - read uint32 registers of FPGA\n");
		        printf("write    addr data              - write uint32 registers of FPGA\n");
		        printf("read8    addr                   - read uint8 registers of FPGA\n");
		        printf("write8   addr data              - write uint8 registers of FPGA\n");
		        printf("read16   addr                   - read uint16 registers of FPGA\n");
		        printf("write16  addr data              - write uint16 registers of FPGA\n");
		        printf("read32   addr                   - read uint32 registers of FPGA\n");
		        printf("write32  addr data              - write uint32 registers of FPGA\n");
		        printf("exit                            - quit");
		        break;
		        
		    case CMD_MULTI_REG_READ:
				arg1 = strtok(NULL, " ");
				arg2 = strtok(NULL, " ");
				if(arg1 == NULL || arg2 == NULL)
				{
					printf("Command syntax error!");
					break;
				}
				addr = (UINT32)strtoul(arg1, &stopstring, 0);
				count = (UINT32)strtoul(arg2, &stopstring, 0);
				for(i=0; i<count; i++) {
					uint32Read(addr + i * 4, &retMultipleData[i]);
				}
				for(i=0; i<count; i++) {
					printf("addr: 0x%08X", addr + i * 4);
					printf("\t");
					printf("data: 0x%08X", retMultipleData[i]);
					printf("\n");
				}
				break;
				
		    case CMD_MULTI_REG_WRITE:
				for(i=0; i<128; i++) {
					uint32Write(i * 4, testData[i % 9]);
				}
				break;
			
			case CMD_REG_READ:
				arg1 = strtok(NULL, " ");
				if(arg1 == NULL)
				{
					printf("Command syntax error!");
					break;
				}
				addr = (UINT32)strtoul(arg1, &stopstring, 0);
				if(uint32Read(addr, &retData32) != OK)
				{
					printf("\n");
					printf("main(): uint32Read() returns ERROR!\n");
					break;
				}
				printf("\n");
				printf("FPGA uint32 register read:\n");
				printf("addr = 0x%08X, data = 0x%08X\n", addr, retData32);
				break;
			 
			case CMD_REG_WRITE:
				arg1 = strtok(NULL, " ");
				arg2 = strtok(NULL, " ");
				if(arg1 == NULL || arg2 == NULL)
				{
					printf("Command syntax error!");
					break;
				}
				addr = (UINT32)strtoul(arg1, &stopstring, 0);
				data = (UINT32)strtoul(arg2, &stopstring, 0);
				if(uint32Write(addr, data) != OK)
				{
					printf("\n");
					printf("main(): uint32Write() returns ERROR!\n");
				}
				printf("FPGA uint32 register write:\n");
				printf("addr = 0x%08X, data = 0x%08X\n", addr, data);
				break;

		    case CMD_UINT8_REG_READ:
		        arg1 = strtok(NULL, " ");
		        if(arg1 == NULL)
		        {
		            printf("Command syntax error!");
		            break;
		        }
		        addr = (UINT32)strtoul(arg1, &stopstring, 0);
		        if(uint8Read(addr, &retData8) != OK)
		        {
		            printf("\n");
		            printf("main(): uint8Read() returns ERROR!\n");
		            break;
		        }
		        printf("\n");
		        printf("FPGA uint8 register read:\n");
		        printf("addr = 0x%08X, data = 0x%02X\n", addr, retData8);
		        break;
			 
		    case CMD_UINT8_REG_WRITE:
		        arg1 = strtok(NULL, " ");
		        arg2 = strtok(NULL, " ");
		        if(arg1 == NULL || arg2 == NULL)
		        {
		            printf("Command syntax error!");
		            break;
		        }
		        addr = (UINT32)strtoul(arg1, &stopstring, 0);
		        data = (UINT32)strtoul(arg2, &stopstring, 0);
		        if(uint8Write(addr, data) != OK)
		        {
		            printf("\n");
		            printf("main(): uint8Write() returns ERROR!\n");
		        }
		        printf("FPGA uint8 register write:\n");
		        printf("addr = 0x%08X, data = 0x%02X\n", addr, data);
		        break;
			 
		    case CMD_UINT16_REG_READ:
		        arg1 = strtok(NULL, " ");
		        if(arg1 == NULL)
		        {
		            printf("Command syntax error!");
		            break;
		        }
		        addr = (UINT32)strtoul(arg1, &stopstring, 0);
		        if(uint16Read(addr, &retData16) != OK)
		        {
		            printf("\n");
		            printf("main(): uint16Read() returns ERROR!\n");
		            break;
		        }
		        printf("\n");
		        printf("FPGA uint16 register read:\n");
		        printf("addr = 0x%08X, data = 0x%04X\n", addr, retData16);
		        break;
			 
		    case CMD_UINT16_REG_WRITE:
		        arg1 = strtok(NULL, " ");
		        arg2 = strtok(NULL, " ");
		        if(arg1 == NULL || arg2 == NULL)
		        {
		            printf("Command syntax error!");
		            break;
		        }
		        addr = (UINT32)strtoul(arg1, &stopstring, 0);
		        data = (UINT32)strtoul(arg2, &stopstring, 0);
				if(uint16Write(addr, data) != OK)
				{
					printf("\n");
					printf("main(): uint16Write() returns ERROR!\n");
				}
				printf("FPGA uint16 register write:\n");
				printf("addr = 0x%08X, data = 0x%04X\n", addr, data);
				break;
		 
			case CMD_UINT32_REG_READ:
				arg1 = strtok(NULL, " ");
				if(arg1 == NULL)
				{
					printf("Command syntax error!");
					break;
				}
				addr = (UINT32)strtoul(arg1, &stopstring, 0);
				if(uint32Read(addr, &retData32) != OK)
				{
					printf("\n");
					printf("main(): uint32Read() returns ERROR!\n");
					break;
				}
				printf("\n");
				printf("FPGA uint32 register read:\n");
				printf("addr = 0x%08X, data = 0x%08X\n", addr, retData32);
				break;
			 
			case CMD_UINT32_REG_WRITE:
				arg1 = strtok(NULL, " ");
				arg2 = strtok(NULL, " ");
				if(arg1 == NULL || arg2 == NULL)
				{
					printf("Command syntax error!");
					break;
				}
				addr = (UINT32)strtoul(arg1, &stopstring, 0);
				data = (UINT32)strtoul(arg2, &stopstring, 0);
				if(uint32Write(addr, data) != OK)
				{
					printf("\n");
					printf("main(): uint32Write() returns ERROR!\n");
				}
				printf("FPGA uint32 register write:\n");
				printf("addr = 0x%08X, data = 0x%08X\n", addr, data);
				break;

			case CMD_EXIT:
				printf("Exiting...\n");
				return OK;
				break;
			 
			default:
				printf("Invalid command!\n");
				break;
		}
		
		printf("\n->");
		fflush(stdout);
	}

    return OK;
}
