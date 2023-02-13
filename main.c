#include <stdio.h>
#include <stdlib.h>

int main()
{
    char source_file[100], target_file[100];
    FILE *source, *target;
    int size;

    printf("Enter name of source file: ");
    scanf("%s", source_file);

    source = fopen(source_file, "rb");
    if (source == NULL) {
        printf("Unable to open source file\n");
        return 1;
    }

    printf("Enter name of target file: ");
    scanf("%s", target_file);

    target = fopen(target_file, "wb");
    if (target == NULL) {
        printf("Unable to open target file\n");
        fclose(source);
        return 1;
    }

    // Determine the size of the source file
    fseek(source, 0, SEEK_END);
    size = ftell(source);
    fseek(source, 0, SEEK_SET);

    // Allocate a buffer to hold the data
    char *buffer = (char*)malloc(sizeof(char) * size);

    // Read the data into the buffer
    int bytes_read = fread(buffer, 1, size, source);

    // Write the data to the target file
    int bytes_written = fwrite(buffer, 1, bytes_read, target);

    // Clean up
    fclose(source);
    fclose(target);
    free(buffer);

    if (bytes_read != bytes_written) {
        printf("Error copying file\n");
        return 1;
    } else {
        printf("File copied successfully\n");
        return 0;
    }
}
