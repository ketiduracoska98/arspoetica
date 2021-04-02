#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#include "util/task_helper.h"
void uppercase(char **poem)
{
	int i;
    for(i = 1; (*poem)[i] != '\0'; i ++)
    {
    	 // Ascii code for  uppercase letters
    	if(65 <= (*poem)[i] && (*poem)[i] <= 90)
    	{	
    		(*poem)[i] += 32;  // set it to lowercase 

    	}
    }
    for(i = 1; (*poem)[i] != '\0'; i ++)
    {
    	if((*poem)[i]=='\n' && (*poem)[i+1]=='\n')
    	{
    		continue;
    	}
    	else if((*poem)[i]=='\n')  // set lettter to uppercase after every newline 
    	{
    		(*poem)[i+1] -= 32;
    	}
    }
    if((*poem)[0] >= 97 && (*poem)[0] <= 122)
    {
    	(*poem)[0] -= 32;
    }
}

void trimming(char **poem)
{
	int i,j=0;
	char *poem_trim=(char *) malloc(1 * sizeof(char));
	for(i=0;(*poem)[i]!='\0';i++)
	{
		if(!( ((*poem)[i]==32 && (*poem)[i+1]==32) || (*poem)[i]==33 || (*poem)[i]==44 || (*poem)[i]==46 || (*poem)[i]==58 ||(*poem)[i]==59 || (*poem)[i]==63))
		{
			// for every char in a poem if it is not space or some nonalphabetic char copy it to new poem
		    poem_trim[j]=(*poem)[i]; 
		    j++;
		    poem_trim=(char*)realloc(poem_trim,(j+1)*sizeof(char));
		    // reallocate memory for a next char
	    }
	}
	poem_trim[strlen(poem_trim)]='\0';
	*poem=poem_trim;

}

void rhimy()
{
	return;
}

void friendly(char *token,char *friendly_word,char**poem)
{
	char* poem1=(char *) malloc(5000 * sizeof(char));
	if(poem1==NULL)
	{
		return;
	}
	char* poem2=(char *) malloc(5000 * sizeof(char));
	if(poem2==NULL)
	{
		return;
	}
	// find first occurence of a word in a poem
	char *p=strstr(*poem,token);
	// copy the words before that occurence
	strncpy(poem1,*poem,p-*poem);

	poem1[p-*poem+1]='\0';
	// append the new word 
	strcat(poem1,friendly_word);
	// get the rest of the poem
	p += strlen(token);
	

	strcpy(poem2,poem1);
	strcat(poem2,p);
	poem2[strlen(poem2)]='\0';
	*poem=poem2;
}

void make_it_silly(char **poem,double prob)
{
	int i;
	for(i = 0; (*poem)[i] != '\0'; i ++)
    {
    	// check if a char is letter
    	if(65 <= (*poem)[i] && (*poem)[i] <= 122)
    	{
    		// generate a random number
    		float sample = rand() % 100 / 99.0;
    		if(sample < prob)
    		{
    			if((65 <= (*poem)[i] && (*poem)[i] <= 90))
    			{
    				// set it to uppercase
    				(*poem)[i]=(*poem)[i]+32;
    			}
    			else if((*poem)[i] >= 97 && (*poem)[i] <= 122)
    			{
    				// set it to lowercase
    				(*poem)[i]=(*poem)[i]-32;
    			}
    		}
    		else
    		{
    			// do not change it if random is bigger than probability 
    			(*poem)[i]=(*poem)[i];
    		}
    	}
    	else
    	{
    		// copy every non alphabetic char
    		(*poem)[i]=(*poem)[i];
    	}	  			
    }
}

void print(char **poem)
{
	printf("%s\n",*poem);
}

int main(void)
{
	srand(42);
	int i;
	char *poem=(char *) malloc(6000 * sizeof(char));
	if(poem==NULL)
	{
		return -1;
	}
	char *file=(char *) malloc(41 * sizeof(char));
	if((file)==NULL)
	{
		return -1;
	}
	char *command=(char *) malloc(51 * sizeof(char));
	if(command==NULL)
	{
		return -1;
	}
	char *friendly_word=(char *) malloc(500 * sizeof(char));
	if(friendly_word==NULL)
	{
		return -1;
	}
    char *poem1=(char *) malloc(6000 * sizeof(char));
    if(poem==NULL)
    {
    	return -1;
    }
    char *token=(char *) malloc(300 * sizeof(char));
    if(token==NULL)
    {
    	return -1;
    }
	char *newline="\n";
   	char *space=" ";
   	char *dot=".";
   	char *vir=",";
	while(strcmp(command,"quit")!=0)
	{
		scanf("%s",command);
		if(strcmp(command,"load")==0)
		{
			    scanf("%s",file);
	 		 	load_file(file,poem);
	 	}
		else if(strcmp(command,"uppercase")==0)
		{
			uppercase(&poem);
		}
		else if(strcmp(command,"trimming")==0)
		{
			 trimming(&poem);
		}
		else if(strcmp(command,"make_it_silly")==0)
		{
			char *prob=(char*)malloc(sizeof(char)*10);
			scanf("%s",prob);
			make_it_silly(&poem,atof(prob));
		}
		else if(strcmp(command,"make_it_friendlier")==0)
		{
			strncpy(poem1,poem,strlen(poem)); 

   			for(i = 0; i < strlen(poem); i ++)
  			{
    			if((poem[i]==*newline) || (poem[i]==*dot) || (poem[i]==*vir))
    			{
    				poem1[i]=*space;
    				// change every newline or nonalphabetic char with space
    			}
   			}
   			poem1[strlen(poem)+1]='\0';
   			// separate every word
   			token=strtok(poem1,space);
			while(token!=NULL)
    		{
    			get_friendly_word(token,&friendly_word);
      		    if(friendly_word==NULL)
     	   		{
     	   			// continue separating while function returns a friendly_word
        			token=strtok(NULL,space);
    				continue;
    			}
    			else
    			{
    	    		friendly(token,friendly_word,&poem);
    				token=strtok(NULL,space);
    			}
    		}
		}
		else if(strcmp(command,"make_it_rhyme")==0)
		{
		}

		else if(strcmp(command,"print")==0)
		{
			print(&poem);
			printf("\n");
		}
}
	return 0;
}
