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
#define MAXLINE 655630

int fileFilter(char *dataFileLoc, char *resultFileLoc);
char *itoa(int num, char *str, int radix);
char *newFileName(int num);
char *newFileLoc(int num, char *resultFileLoc);


int main(int argc, const char * argv[])
{

    fileFilter("/Users/Song/workspace/xcode/GeneProcess/data/NCBI37.fasta", "/Users/Song/workspace/xcode/GeneProcess/resultdata");
    
    return 0;
}

int fileFilter(char *dataFileLoc, char *resultFileLoc) {
    int i = 0;
    
    char *resultFileName = newFileLoc(i, resultFileLoc);
    printf("%s", resultFileName);
    printf("\n");

    FILE *dataFile;
    
    FILE *newFile = fopen(resultFileName, "w");
    
    if ((dataFile = fopen(dataFileLoc, "r")) != NULL) {
        printf("file open!\n");
  
        char line[MAXLINE];
        
        while (fgets(line, MAXLINE, dataFile) != NULL) {
            printf("%s", line);
            
            char *firstCh = (char *)malloc(10);
            strncpy(firstCh, line, 1);
            
            if (strcmp(firstCh, ">") == 0) {
                printf("this is > line\n");
                //fputs(line, newFile);
                
            }
            else if (*firstCh == 13) {
                printf("this is enter line\n");
                
                fclose(newFile);
                i = i + 1;
                
                resultFileName = newFileLoc(i, resultFileLoc);
                printf("%s", resultFileName);
                printf("\n");
            
                newFile = fopen(resultFileName, "w");
            }
            else {
                printf("this is gene line\n");
                
                char *stripLine = (char *)malloc(10);
                strncpy(stripLine, line, strlen(line) - 1);

                printf("%s", stripLine);
                
                fputs(stripLine, newFile);
                
            }
            
        }
        
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
    char *prefix = (char *)malloc(100);
    char tmpNum[10];
    
    itoa(num, tmpNum, 10);
    strcpy(prefix, "/seg_");
    strcat(prefix, tmpNum);
    strcat(prefix, ".txt");
    
    return prefix;
}

char *newFileLoc(int num, char *resultFileLoc) {
    char *prefix = (char *)malloc(100);
    
    strcpy(prefix, resultFileLoc);
    strcat(prefix, newFileName(num));
    
    return prefix;
}


