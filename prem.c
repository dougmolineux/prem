#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include "cJSON.h"

char *loadlfile(const char *path);

int main() {
	char *out, *team, *text, *pts;
	cJSON *json, *results, *col1;
	int i;

	system("wget -O scores.json http://www.kimonolabs.com/api/8mshjilc?apikey=72a30f4b0c702968f39731877bd38ebb 2> /dev/null");	
	text = loadlfile("scores.json");
        json = cJSON_Parse(text);
        if (!json) {
		printf("Error before: [%s]\n",cJSON_GetErrorPtr());
	}
        else {
		results = cJSON_GetObjectItem(json, "results");
		col1 = cJSON_GetObjectItem(results, "collection1");
		printf("    Team Name         Points\n");
		for(i = 0; i < 20; i++) {
			cJSON *item = cJSON_GetArrayItem(col1, i);
			out = cJSON_Print(item);
			pts = cJSON_Print(cJSON_GetObjectItem(item, "Points"));
			team = cJSON_Print(cJSON_GetObjectItem(cJSON_GetObjectItem(item, "property1"), "text"));
			memmove(team, team+1, strlen(team));
			memmove(pts, pts+1, strlen(pts));
			team[strlen(team)-1] = 0;
			pts[strlen(pts)-1] = 0;
			printf("%-3d %-17s %s\n", i+1, team, pts);
		}
                cJSON_Delete(json);
                free(out);
        }
	return 0;
}

char *loadlfile(const char *path) {
    int file_descr;
    FILE *fp;
    struct stat buf;
    char *p, *buffer;
    fstat((file_descr = open(path, O_RDONLY)), &buf);
    if(NULL == (buffer = malloc(buf.st_size + 1)))
        return NULL;
    fp = fdopen(file_descr, "rb");
    p = buffer;
    while((*p++ = fgetc(fp)) != EOF)
        ;
    *p = '\0';
    fclose(fp);
    close(file_descr);
    return buffer;
}
