#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/stat.h>

#define DEFAULT_FROM_ENV "FLAG"
#define DEFAULT_FILE_PERM 0444

typedef struct {
    char *from_env;     // environment variable to read flag from
    char *to_env;       // environment variable to write flag to
    char *to_file;    // flag file path
    mode_t file_perm;   // flag file permissions
    char *user_or_uid;  // username or uid:gid format
    char *home;         // custom home directory
    int cmd_index;      // index of command in argv
} options_t;

// simple atoi implementation that doesn't rely on full libc
static int str_to_int(const char *str) {
    int result = 0;
    int sign = 1;

    if (*str == '-') {
        sign = -1;
        str++;
    }

    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }

    return sign * result;
}

// parse octal string to mode_t
static mode_t str_to_octal(const char *str) {
    mode_t result = 0;

    // skip leading 0 if present
    if (*str == '0') {
        str++;
    }

    while (*str >= '0' && *str <= '7') {
        result = result * 8 + (*str - '0');
        str++;
    }

    return result;
}

void print_usage(const char *prog_name) {
    fprintf(stderr, "Usage: %s [OPTIONS] [--] <command...>\n", prog_name);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -i:e, --from:env <env_var>     Get flag from specified environment variable (default: FLAG)\n");
    fprintf(stderr, "  -o:e, --to:env <env_var>       Set environment variable to flag value (default: none)\n");
    fprintf(stderr, "  -o:f, --to:file <path>         Set file path for flag output (default: none)\n");
    fprintf(stderr, "  -p, --file:perm <permissions>  Set file permissions for flag file (default: 444, octal)\n");
    fprintf(stderr, "  -u, --user <user|uid:gid>      Set user by name or UID:GID (e.g., nobody or 1000:1000)\n");
    fprintf(stderr, "  -H, --home <path>              Set HOME environment variable\n");
    fprintf(stderr, "  -h, --help                     Show this help message\n");
}

int parse_args(int argc, char *argv[], options_t *opts) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    // initialize options
    opts->from_env = DEFAULT_FROM_ENV;
    opts->to_env = NULL;
    opts->to_file = NULL;
    opts->file_perm = DEFAULT_FILE_PERM;
    opts->user_or_uid = NULL;
    opts->home = NULL;
    opts->cmd_index = 1;

    int i = 1;
    while (i < argc) {
        const char *arg = argv[i];

        #define ARG_IS(short_opt, long_opt) (strcmp(arg, short_opt) == 0 || strcmp(arg, long_opt) == 0)
        #define MISSING_ARG_ERROR() do { \
            fprintf(stderr, "Error: Missing argument for %s\n", arg); \
            print_usage(argv[0]); \
            return -1; \
        } while(0)

        if (ARG_IS("-h", "--help")) {
            print_usage(argv[0]);
            return -1;
        } else if (ARG_IS("-i:e", "--from:env")) {
            if (i + 1 >= argc) MISSING_ARG_ERROR();
            opts->from_env = argv[i + 1];
            i += 2;
        } else if (ARG_IS("-o:e", "--to:env")) {
            if (i + 1 >= argc) MISSING_ARG_ERROR();
            opts->to_env = argv[i + 1];
            i += 2;
        } else if (ARG_IS("-o:f", "--to:file")) {
            if (i + 1 >= argc) MISSING_ARG_ERROR();
            opts->to_file = argv[i + 1];
            i += 2;
        } else if (ARG_IS("-p", "--file:perm")) {
            if (i + 1 >= argc) MISSING_ARG_ERROR();
            opts->file_perm = str_to_octal(argv[i + 1]);
            i += 2;
        } else if (ARG_IS("-u", "--user")) {
            if (i + 1 >= argc) MISSING_ARG_ERROR();
            opts->user_or_uid = argv[i + 1];
            i += 2;
        } else if (ARG_IS("-H", "--home")) {
            if (i + 1 >= argc) MISSING_ARG_ERROR();
            opts->home = argv[i + 1];
            i += 2;
        } else if (strcmp(arg, "--") == 0) {
            // end of options, next argument is command
            if (i + 1 >= argc) {
                opts->cmd_index = 0; // no command specified
                return 0;
            }
            opts->cmd_index = i + 1;
            return 0;
        } else {
            // found the command
            opts->cmd_index = i;
            return 0;
        }
    }

    #undef ARG_IS
    #undef MISSING_ARG_ERROR

    // no command found
    opts->cmd_index = 0;
    return 0;
}

int main(int argc, char *argv[]) {
    // parse command line arguments
    options_t opts;
    if (parse_args(argc, argv, &opts) != 0) {
        return 1;
    }

    // get flag from environment variable
    char *flag = getenv(opts.from_env);
    if (flag == NULL) {
        flag = "flag{test}";
    }
    unsetenv(opts.from_env);

    // write to file if path is specified
    if (opts.to_file != NULL) {
        FILE *fp = fopen(opts.to_file, "w");
        if (fp == NULL) {
            perror("Failed to open flag file");
            return 1;
        }

        fprintf(fp, "%s\n", flag);
        fclose(fp);

        // set file permissions
        if (chmod(opts.to_file, opts.file_perm) != 0) {
            perror("Failed to set file permissions");
            return 1;
        }
    }

    // write to environment variable if specified
    if (opts.to_env != NULL) {
        if (setenv(opts.to_env, flag, 1) != 0) {
            perror("Failed to set environment variable");
            return 1;
        }
    }

    // set user if specified
    if (opts.user_or_uid != NULL) {
        // check if it's uid:gid format (contains colon)
        char *colon = strchr(opts.user_or_uid, ':');

        if (colon != NULL) {
            // uid:gid format - minimal dependency version
            char *uid_str = opts.user_or_uid;
            *colon = '\0';
            uid_t uid = str_to_int(uid_str);
            gid_t gid = str_to_int(colon + 1);

            if (setgid(gid) != 0) {
                perror("Failed to set GID");
                return 1;
            }
            if (setuid(uid) != 0) {
                perror("Failed to set UID");
                return 1;
            }
        } else {
            // username format
            struct passwd *pwd = getpwnam(opts.user_or_uid);
            if (pwd == NULL) {
                fprintf(stderr, "User %s not found\n", opts.user_or_uid);
                return 1;
            }
            if (setgid(pwd->pw_gid) != 0) {
                perror("Failed to set GID");
                return 1;
            }
            if (setuid(pwd->pw_uid) != 0) {
                perror("Failed to set UID");
                return 1;
            }
            if (setenv("USER", opts.user_or_uid, 1) != 0) {
                perror("Failed to set USER environment variable");
                return 1;
            }
            // set HOME from passwd if not explicitly specified
            if (opts.home == NULL) {
                if (setenv("HOME", pwd->pw_dir, 1) != 0) {
                    // fallback to /tmp if user's home doesn't exist
                    setenv("HOME", "/tmp", 1);
                }
            }
        }
    }

    // set custom HOME if specified
    if (opts.home != NULL) {
        if (setenv("HOME", opts.home, 1) != 0) {
            perror("Failed to set HOME environment variable");
            return 1;
        }
    }

    // run command
    if (opts.cmd_index == 0) {
        return 0; // no command to run, just exit
    } else {
      execvp(argv[opts.cmd_index], &argv[opts.cmd_index]);
      // if execvp returns, it failed
      perror("Failed to execute command");
      return 1;
    }
}