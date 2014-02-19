//
//  main.c
//  GeneProcess
//
//  Created by Songli on 14-2-17.
//  Copyright (c) 2014年 Songli. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINE 200

int fileFilter(char *dataFileLoc, char *resultFileLoc);
char *itoa(int num, char *str, int radix);
char *newFileName(int num);
char *newFileLoc(int num, char *resultFileLoc);


int main(int argc, const char * argv[])
{

    fileFilter("/Users/Song/workspace/xcode/GeneProcess/data/test.fasta", "/Users/Song/workspace/xcode/GeneProcess/resultdata");
    
    return 0;
}

int fileFilter(char *dataFileLoc, char *resultFileLoc) {
    int i = 0;
    FILE *dataFile;
    FILE *newFile;
    char *line;
    char *firstCh;
    char *stripLine;
    
    char *resultFileName = newFileLoc(i, resultFileLoc);
    printf("%s\n", resultFileName);

    newFile = fopen(resultFileName, "w");
    
    if ((dataFile = fopen(dataFileLoc, "r")) != NULL) {
        printf("file open!\n");
  
        line = (char *)malloc(100);
        
        
        while (fgets(line, MAXLINE, dataFile) != NULL) {
            printf("%s", line);
            
            firstCh = (char *)malloc(10);
            memset(firstCh, 0, sizeof(firstCh));
            strncpy(firstCh, line, 1);
            
            if ((strcmp(firstCh, ">") == 0) && (i == 0)) {
                printf("this is first > line\n");
                i++;
            }
            else if ((strcmp(firstCh, ">") == 0) && (i > 0)) {
                printf("this is > line\n");
                
				fclose(newFile);
                
                resultFileName = newFileLoc(i, resultFileLoc);
                printf("%s\n", resultFileName);
                
                newFile = fopen(resultFileName, "w");
				
				i++;

            }
            else {
                printf("this is gene line\n");
                
                stripLine = (char *)malloc(strlen(line));
                memset(stripLine, 0, sizeof(stripLine));
				strcpy(stripLine, line);
                
                if (stripLine[strlen(stripLine) - 1] == '\n') {
                    stripLine[strlen(stripLine) - 1] = '\0';
                }
                
                printf("%s", stripLine);
                
                fputs(stripLine, newFile);
                
                free(stripLine);
            }
            free(firstCh);
            
        }
  
        
        free(line);
    }
    else {
        printf("file open wrong!\n");
    }
    
    fclose(dataFile);
    return  i;
}


char *itoa(int num, char *str, int radix) {
    char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned unum; /* 中间变量 */
    int i=0,j,k;
    /* 确定unum的值 */
    if(radix==10&&num<0) /* 十进制负数 */
    {
        unum=(unsigned)-num;
        str[i++]='-';
    }
    else unum=(unsigned)num; /* 其他情况 */
    /* 转换 */
    do{
        str[i++]=index[unum%(unsigned)radix];
        unum/=radix;
    }while(unum);
    str[i]='\0';
    /* 逆序 */
    if(str[0]=='-') k=1; /* 十进制负数 */
    else k=0;
    char temp;
    for(j=k;j<=(i-1)/2;j++)
    {
        temp=str[j];
        str[j] = str[i-1+k-j];
        str[i-1+k-j] = temp;
    }
    return str;
}

char *newFileName(int num) {
    char *prefix = (char *)malloc(50);
    char tmpNum[10];
    
    itoa(num, tmpNum, 10);
    strcpy(prefix, "/seg_");
    strcat(prefix, tmpNum);
    strcat(prefix, ".txt");
    
    return prefix;
}

char *newFileLoc(int num, char *resultFileLoc) {
    char *prefix = (char *)malloc(50);
    
    strcpy(prefix, resultFileLoc);
    strcat(prefix, newFileName(num));
    
    return prefix;
}


