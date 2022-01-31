#include <stdio.h>
#include <stdlib.h>
#include <string.h>





// struct
typedef struct Keyword
{
	char k[50];
	int count;
}key;



int main(int argc, char **argv)
{
	int i,x;
	char *line=NULL;
	size_t maxlen = 0;
	ssize_t n;
	key *keys= (key *) malloc(argc*sizeof(key)); 
	for(i = 0; i < argc-1; i++)
		strcpy(keys[i].k, argv[i+1]);

	while ((n = getline(&line, &maxlen, stdin)) > 0)
	{
		char* token = strtok(line, " ");
		while (token != NULL)
		{
			int idx;
			for(idx = 0; idx < argc-1; idx++)
			{
				// compare token with each key by using loop
				if(strcmp(token, keys[idx].k) == 0)	
					keys[idx].count++;
			}
				token = strtok(NULL, " ");
		}
	}
	// freeing memory
	free(line);
	printf("%s", "result:\n");
	for(x = 0; x< argc-1; x++)
		printf("%s:%d\n",keys[x].k,keys[x].count);
}

