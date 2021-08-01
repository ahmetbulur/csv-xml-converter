#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct record {
    
    char name[64];
    char surname[32];
    char gender[2];
    char email[32];
    char phone_number[16];
    char address[32];
    char level_of_education[8];
    unsigned int income_level;
    unsigned int expenditure;
    char currency_unit[16];
    char currentMood[32];
    float height;
    unsigned int weight;
    
};
typedef struct record r;

int main() {
    
    char inputfile[20];
    char outputfile[20];
    
    FILE* read;
    FILE* writed;
    
    strcpy(inputfile, "records.csv");

    // open inputfile to read
    read= fopen(inputfile, "r");

    int bufferLength = 1024;
    char buffer[bufferLength];
    char tagHolder[bufferLength];

    // determine how many records exist
    int recordLength = -1;
    while(fgets(buffer, bufferLength, read)){

        ++recordLength;

    }

    r rec[recordLength];

    int recId = 0;
    int tagId = 0;
    int firstLine = 0;

    // array to keep tags
    char tags[13][20];
    
    // open inputfile to read
    read = fopen(inputfile, "r");

    while(fgets(buffer, bufferLength, read)) {
          
        // checks whether first line or not
        if(firstLine == 0){

            firstLine++;

            strcpy(tagHolder, buffer);
            
            // split tags in first line and store them in tags array
            char * tag = strtok(tagHolder, ",");
            while( tag != NULL ) {

                strcpy(tags[tagId], tag);
                
                tagId++;
                if(tagId != 12){
                    
                    tag= strtok(NULL, ",");   
                }
                else{
                    
                    tag= strtok(NULL, "\n");
                }
                
            }

        }
        else{
            
            // split and assign values to proper structure(rec[recordLength]) variables
            char * token = strtok(buffer, ",");
            
            strcpy(rec[recId].name, token);
            token = strtok(NULL, ","); 
            strcpy(rec[recId].surname, token);
            token = strtok(NULL, ","); 
            strcpy(rec[recId].gender, token);
            token = strtok(NULL, ","); 
            strcpy(rec[recId].email, token);
            token = strtok(NULL, ","); 
            strcpy(rec[recId].phone_number, token);    
            token = strtok(NULL, ","); 
            strcpy(rec[recId].address, token);
            token = strtok(NULL, ","); 
            strcpy(rec[recId].level_of_education, token);
            token = strtok(NULL, ","); 
            rec[recId].income_level = atoi(token);
            token = strtok(NULL, ","); 
            rec[recId].expenditure = atoi(token);
            token = strtok(NULL, ","); 
            strcpy(rec[recId].currency_unit, token);
            token = strtok(NULL, ","); 
            strcpy(rec[recId].currentMood, token);
            token = strtok(NULL, ","); 
            rec[recId].height = atof(token);
            token = strtok(NULL, "\n");
            rec[recId].weight = atoi(token);

            recId++;
            
        }

    }
    
    // split inputfile to get root tag name
    char temp[20];
    strcpy(temp, inputfile);
    char * rootTag = strtok(temp, ".");
    
    snprintf(outputfile, 20, "%s%s", rootTag, ".xml");
    
	// open outputfile to write
    writed = fopen(outputfile, "w");

    // write tags and variables using tags array (tags[tagId]) and structure (rec[recordLength]) variables to outputfile
    fprintf(writed, "<?xml version=%c1.0%c encoding=%cUTF-8%c?>\n", '"', '"', '"', '"');
    fprintf(writed, "<%s>\n", rootTag);
    int i;
    for (i = 0; i < recordLength; ++i){

        tagId = 0;

        fprintf(writed, "\t<row id=%d>\n", (i+1));

        fprintf(writed, "\t\t<%s>%s</%s>\n", tags[tagId++], rec[i].name, tags[tagId]);
        fprintf(writed, "\t\t<%s>%s</%s>\n", tags[tagId++], rec[i].surname, tags[tagId]);
        fprintf(writed, "\t\t<%s>%s</%s>\n", tags[tagId++], rec[i].gender, tags[tagId]);
        fprintf(writed, "\t\t<%s>%s</%s>\n", tags[tagId++], rec[i].email, tags[tagId]);
        fprintf(writed, "\t\t<%s>%s</%s>\n", tags[tagId++], rec[i].phone_number, tags[tagId]);
        fprintf(writed, "\t\t<%s>%s</%s>\n", tags[tagId++], rec[i].address, tags[tagId]);
        fprintf(writed, "\t\t<%s>%s</%s>\n", tags[tagId++], rec[i].level_of_education, tags[tagId]);
        fprintf(writed, "\t\t<%s>%d</%s>\n", tags[tagId++], rec[i].income_level, tags[tagId]);
        fprintf(writed, "\t\t<%s>%d</%s>\n", tags[tagId++], rec[i].expenditure, tags[tagId]);
        fprintf(writed, "\t\t<%s>%s</%s>\n", tags[tagId++], rec[i].currency_unit, tags[tagId]);
        fprintf(writed, "\t\t<%s>%s</%s>\n", tags[tagId++], rec[i].currentMood, tags[tagId]);
        fprintf(writed, "\t\t<%s>%.2f</%s>\n", tags[tagId++], rec[i].height, tags[tagId]);
        fprintf(writed, "\t\t<%s>%d</%s>\n", tags[tagId], rec[i].weight, tags[tagId]);

        fprintf(writed, "\t</row>\n");

    }
    fprintf(writed, "</%s>\n", rootTag);

    fclose(read);
    fclose(writed);

    printf("\n%s was converted to %s!\n", inputfile, outputfile);
    printf("%s file was created!\n\n", outputfile);

    return(0);

}
