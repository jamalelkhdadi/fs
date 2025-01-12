#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

#define VERSION "1.1.0" // Updated version

void print_usage(const char *program_name) {
    printf("Usage: %s <file_name>\n", program_name);
    printf("       %s -v or --version       Display the version\n", program_name);
    printf("       %s -h or --help          Display this help message\n", program_name);
    printf("       %s -d <dir_name> or --dir <dir_name> Calculate the size of a directory\n", program_name);
}

void print_version() {
    printf("File Size Checker Version: %s\n", VERSION);
}

long long calculate_directory_size(const char *dir_name) {
    DIR *dir = opendir(dir_name);
    if (!dir) {
        perror("Error opening directory");
        return -1;
    }

    struct dirent *entry;
    struct stat file_stat;
    long long total_size = 0;

    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Build the full path
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);

        if (stat(path, &file_stat) == -1) {
            perror("Error getting file stats");
            continue;
        }

        if (S_ISREG(file_stat.st_mode)) {
            total_size += file_stat.st_size; // Regular file
        } else if (S_ISDIR(file_stat.st_mode)) {
            long long subdir_size = calculate_directory_size(path); // Recursively calculate subdirectory size
            if (subdir_size != -1) {
                total_size += subdir_size;
            }
        }
    }

    closedir(dir);
    return total_size;
}

void display_size(long long size_bytes) {
    if (size_bytes >= (1024LL * 1024 * 1024)) {
        printf("Total size: %.2f GB\n", (double)size_bytes / (1024 * 1024 * 1024));
    } else if (size_bytes >= (1024LL * 1024)) {
        printf("Total size: %.2f MB\n", (double)size_bytes / (1024 * 1024));
    } else if (size_bytes >= 1024LL) {
        printf("Total size: %.2f KB\n", (double)size_bytes / 1024);
    } else {
        printf("Total size: %lld bytes\n", size_bytes);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
        print_version();
        return 0;
    }

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        print_usage(argv[0]);
        return 0;
    }

    if ((strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--dir") == 0) && argc == 3) {
        const char *dir_name = argv[2];
        long long dir_size = calculate_directory_size(dir_name);
        if (dir_size != -1) {
            display_size(dir_size);
        }
        return 0;
    }

    // For file size calculation
    const char *file_name = argv[1];
    struct stat file_stat;
    if (stat(file_name, &file_stat) == -1) {
        perror("Error getting file stats");
        return 1;
    }

    if (S_ISDIR(file_stat.st_mode)) {
        printf("Error: %s is a directory. Use -d or --dir to calculate directory size.\n", file_name);
        return 1;
    }

    long long file_size_bytes = file_stat.st_size;
    display_size(file_size_bytes);

    return 0;
}
