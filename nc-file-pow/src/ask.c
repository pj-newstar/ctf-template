#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char name[64+3];
    char *flag;

    // Get the flag from environment variable
    flag = getenv("FLAG");
    if (flag == NULL) {
        flag = "flag{test_flag}";  // Default flag if not set
    }

    // Disable buffering for stdout
    setbuf(stdout, NULL);
    while (1) {
        memset(name, 0, sizeof(name));
        fflush(stdin);
        printf("Please tell your name: ");

        // Read the name input
        if (fgets(name, sizeof(name), stdin) == NULL) {
            break;  // Exit on EOF or error
        }
        name[sizeof(name) - 1] = '\0';  // Ensure null termination

        // Remove newline character if present
        name[strcspn(name, "\r\n")] = '\0';
        name[strcspn(name, "\n")] = '\0';

        // Check if the name is "admin"
        if (strcmp(name, "admin") == 0) {
            printf("Here is your flag: %s\n", flag);
            break;  // Exit the loop after giving the flag
        } else {
            printf("Only admin can get flag\n");
            // Continue the loop to ask again
        }
    }

    return 0;
}