#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myString.h"

int main (int argc, char *argv[])
{	
	//clear screen
	system("cls");
	
	printf("\n*=============================================================================*\n"
	       "*-Caesar Cipher Program                                                       *\n"
	       "*-Created by: Andrew Acosta                                                   *\n"
	       "*-----------------------------------------------------------------------------*\n"
	       "*-This program will Encrypt your message and output it as a .txt file so you  *\n"
	       "*-can send it to your friends and they can Decrypt it using this program also.*\n"
	       "*-Part of this program uses Harvad's CS50 GetString function.                 *\n"		   
		   "*-Below is Harvad's CS50 copyright and usage statement:                       *\n"
		   "*-----------------------------------------------------------------------------*\n"
		   "*-CS50 Library 5                                                              *\n"
           "*-https://manual.cs50.net/library/ * Based on Eric Roberts' genlib.c and      *\n"
           "*-simpio.c Copyright (c) 2013,                                                *\n"
           "*-Glenn Holloway <holloway@eecs.harvard.edu>                                  *\n"
           "*-David J. Malan <malan@harvard.edu>                                          *\n"
           "*-All rights reserved.                                                        *\n"
           "*-----------------------------------------------------------------------------*\n"
           "*-BSD 3-Clause License                                                        *\n"
           "*-http://www.opensource.org/licenses/BSD-3-Clause                             *\n"
		   "*-----------------------------------------------------------------------------*\n"
           "*-Redistribution and use in source and binary forms, with or without          *\n"
           "*-modification, are permitted provided that the following conditions are met: *\n"
           "*-----------------------------------------------------------------------------*\n"
           "*-Redistributions of source code must retain the above copyright notice,      *\n"
           "* this list of conditions and the following disclaimer.                       *\n"
           "*-Redistributions in binary form must reproduce the above copyright           *\n"
           "* notice, this list of conditions and the following disclaimer in the         *\n"
           "* documentation and/or other materials provided with the distribution.        *\n"
           "*-Neither the name of CS50 nor the names of its contributors may be used      *\n"
           "* to endorse or promote products derived from this software without           *\n"
           "* specific prior written permission.                                          *\n"
	       "*                                                                             *\n"
	       "*=============================================================================*\n");
		   
	FILE *fp;
	int Ckey;
	char CMode;
		
	if (argc == 3)
	{
		char *key = argv[1];
		int keyL = strlen(key);
		char *mode = argv[2];
		int modeL = strlen(mode);
		
		if (keyL < 3)
		{
			int i;
			
			for (i = 0; i < 2; i++)
			{
				if (isalpha(key[i]))
				{
					printf("\nKey can't have letters.\n");
					return 1;
				}
				else
				{
					Ckey = atoi(key);
				}
			}
			
			if (Ckey < 1 || Ckey > 25)
			{
				printf("\nKey must be between 1 and 25.\n");
				return 1;
			}
			else
			{
				//key is between 1 and 25
			}
		}
		else
		{
			printf("\nKey needs to be between 1 and 25.\n");
			return 1;
		}
		
		if (modeL < 2)
		{
			if(isdigit(mode[0]))
			{
				printf("\nMode must be an E or D.\n");
				return 1;
			}
			else
			{
				if (mode[0] == 'E' || mode[0] == 'e')
				{
					CMode = 'E';
				}
				else if (mode[0] == 'D' || mode[0] == 'd')
				{
					CMode = 'D';
				}
				else
				{
					printf("\nMode must be an E or D.\n");
					return 1;
				}				
			}
		}
		else
		{
			printf("\nMode should only be an E or D.\n");
			return 1;
		}
	}	
	else
	{
		printf("\nYou must enter Key and Mode.\n");
		return 1;
	}
		
	if (CMode == 'E' || CMode == 'e')
	{
		printf("\n*-Type your message to be Encrypted-------------------------------------------*\n");
		printf("*-----------------------------------------------------------------------------*\n\n");
		
		char *myMsg = myString();		
		int myMsgL = strlen(myMsg);
		char *myMsgE = (char *) malloc((myMsgL + 1) *sizeof(char));
		int i;
		
		for (i = 0; i < (myMsgL + 1); i++)
		{
			if (isalpha(myMsg[i]))
			{
				if (islower(myMsg[i]))
				{
					myMsgE[i] = (((myMsg[i] - 97) + Ckey) % 26) + 97;
				}
				else if (isupper(myMsg[i]))
				{
					myMsgE[i] = (((myMsg[i] - 65) + Ckey) % 26) + 65;
				}
			}			
			else
			{
				myMsgE[i] = myMsg[i];
			}
		}
		
		fp = fopen ("Message.txt", "w+");
		fprintf(fp, "%s", myMsgE);
		
		free (myMsgE);
		for (i = 0; i < (myMsgL - 1); i++ )
		{
			myMsg[i] = 0;
		}
		printf("\033[2J\033[1;1H");
		
		printf("\n*-----------------------------------------------------------------------------*\n"
		       "Your message has been Encrypted and saved as\n\"Message.txt\" file.              \n"
			   "*-----------------------------------------------------------------------------*\n");
			   
		fclose(fp);
		
	}
	else
	{
		char c;
		int m;
		
		printf("\n*-------Your message is Decrypted below---------------------------------------*\n");
		printf("*-----------------------------------------------------------------------------*\n\n");
		
		fp = fopen("Message.txt","r");
		
		if (fp == NULL)
		{
			printf("I could not find Message.txt in the folder.\n");
			return 1;
		}
		else
		{
			//continue
		}
		
		while(1)
		{		
			c = fgetc(fp);
			
			if (isalpha(c))
			{
				if (islower(c))
				{
					m = (((c - 97) + (26 - Ckey)) % 26) + 97;
				}
				else if (isupper(c))
				{
					m = (((c - 65) + (26 - Ckey)) % 26) + 65;
				}				
			}
			else
			{
				m = c;
			}
			
			if (feof(fp))
			{
				break;
			}
			
			printf("%c", m);
			
			
		}
	}
	printf("\n");
	fclose(fp);

	return 0;
}
