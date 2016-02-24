//
//  test_assign1_2.c
//
//  Created by Young on 2/5/16.
//  Copyright © 2016 Young. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "storage_mgr.h"
#include "dberror.h"
#include "test_helper.h"

// test name
char *testName;

/* test output files */
#define TESTPF "test_pagefile.bin"
//#define TESTPF "/Users/young/Desktop/test3.txt"

static void newTest(void);

/* main function running all tests */
int
main (void)
{
    newTest();
    return 0;
}



void newTest(void)
{
    SM_FileHandle fh;
    SM_PageHandle ph;
    char str1[PAGE_SIZE],str2[PAGE_SIZE],str3[PAGE_SIZE],str4[PAGE_SIZE];
    
    //initialization
    for (int i=0;i<PAGE_SIZE;i++)
    {
        str1[i]='1';
        str2[i]='2';
        str3[i]='3';
        str4[i]='4';
        
    }
    createPageFile (TESTPF);
    openPageFile (TESTPF, &fh);
    
    //test on WriteBlock functions
    writeBlock(0,&fh,str1);
    appendEmptyBlock(&fh);
    writeCurrentBlock(&fh,str2);
    ensureCapacity(3, &fh);
    writeCurrentBlock(&fh, str3);
    appendEmptyBlock(&fh);
    writeBlock(3, &fh, str4);
    
    //test on ReadBlock functions
    char temp1[PAGE_SIZE],temp2[PAGE_SIZE],temp3[PAGE_SIZE],temp4[PAGE_SIZE];
    char temp[PAGE_SIZE];
    fh.curPagePos=0;
    printf("\nReadBlock 0:\n");
    readBlock(0, &fh, temp);
    memset(temp,'\0',PAGE_SIZE);
    
    printf("\nReadNextBlock:\n");
    readNextBlock(&fh, temp);
    memset(temp,'\0',PAGE_SIZE);
    
    printf("\nReadCurrentBlock 3:\n");
    fh.curPagePos=3;
    readCurrentBlock(&fh,temp);
    memset(temp,'\0',PAGE_SIZE);
    
    printf("\nReadPreviousBlock:\n");
    readPreviousBlock(&fh, temp);
    memset(temp,'\0',PAGE_SIZE);
    
}
