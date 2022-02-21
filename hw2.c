#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ldirect(const char *name, int tab, int Sflag, int sflag, int svalue)
{

DIR *dir;
struct dirent *parentDir;
struct stat file_stats;

if (!(dir = opendir(name)))
	return;

while ((parentDir = readdir(dir)) != NULL) 
{


	if (parentDir->d_type == DT_REG)
	{

		if(sflag == 1)
		{
			stat(parentDir->d_name,&file_stats);
			int x = (unsigned int)file_stats.st_size;
			if ((x >= svalue) == 1)
				printf("%s",parentDir->d_name);
				printf("%u bytes:", (unsigned int) file_stats.st_size);	
				printf("\n");
			continue;
		}
		if(Sflag == 1)
		{
			stat(parentDir->d_name,&file_stats);
			printf("%u bytes:", (unsigned int) file_stats.st_size);
		}
	}


		if (parentDir->d_type == DT_DIR) 
		{
			char path[1024];
			if (strcmp(parentDir->d_name, ".") == 						0 || strcmp(parentDir->d_name, "..") == 0)
				continue;
				snprintf(path, sizeof(path), "%s/%s", name, parentDir->d_name);
				printf("%*s[%s]\n", tab,"", parentDir->d_name);
ldirect(path, tab + 2, Sflag, sflag, svalue);
		} 
		else 
		{
			printf("%*s- %s\n", tab, "", parentDir->d_name);
		}
	}
//https://stackoverflow.com/questions/8436841/how-to-recursively-list-directories-in-c-on-linux
closedir(dir);
}

int main(int argc, char **argv) {

	int Sflag = 0;
	int sflag = 0;
	int svalue = 0;
	char *fvalue = NULL;
	int index;
	int c;

	opterr = 0;

	while ((c = getopt (argc, argv, "Ss:f:")) != -1)
	{
		switch (c)
		{
			case 'S':
				Sflag = 1;
				break;
			case 's':
				svalue = atoi (optarg);
				sflag = 1;
				break;
			case 'f':
				fvalue = optarg;
				break;
		}
	}
	
	printf ("Sflag = %d, svalue = %d, fvalue = %s\n", Sflag, svalue, fvalue);

	char *ret = argv[(argc-1)];
	
	if (ret[0] != '/')
		ldirect(".", 0,Sflag, sflag, svalue);
	else
		ldirect(ret,0,Sflag, sflag, svalue);

	return 0;
}

