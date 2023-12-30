#include <stdio.h>
#include <string.h>

int main()
{
    char buffer[1000];
    char *data;

    FILE* file = fopen("zari-2020.csv", "r");

    if (file == NULL)
    {
        printf("Error: could not open file\n");
        return 1;
    }

    int day = 0;

    while(fgets(buffer, sizeof(buffer), file))
    {
        printf("%s", buffer);
    }

    rewind(file);

    while(fgets(buffer, sizeof(buffer), file))
    {
        printf("%s", buffer);
    }

    fclose(file);


}
