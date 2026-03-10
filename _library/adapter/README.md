# Adapter

This directory provides a `init.c`, it has the following behavior:

- Read the FLAG from the environment variable `FLAG` and unset it from the environment.
- Write the FLAG to a file. Set the permission of the file if options specified.
- Run the specified command (if any). If options specified, run with the specified user and HOME environment variable.

## Usage

Build command:

```bash
gcc init.c -o init -static -no-pie
```

> [!NOTE]
> If you use `-u <user>` option instead of `-u <uid:gid>`, it requires at runtime the shared libraries from the glibc version used for linking.

Use `init --help` to see the usage of the command line options.

```bash
Usage: ./init [OPTIONS] [--] <command...>
Options:
  -i:e, --from:env <env_var>     Get flag from specified environment variable (default: FLAG)
  -o:e, --to:env <env_var>       Set environment variable to flag value (default: none)
  -o:f, --to:file <path>         Set file path for flag output (default: none)
  -p, --file:perm <permissions>  Set file permissions for flag file (default: 444, octal)
  -u, --user <user|uid:gid>      Set user by name or UID:GID (e.g., nobody or 1000:1000)
  -H, --home <path>              Set HOME environment variable
  -h, --help                     Show this help message
```

Example usage:

```bash
# write FLAG to /flag
init -o:f /flag node server.js
# write FLAG to GZCTF_FLAG environment, run as `ctf`
init -o:e GZCTF_FLAG -u ctf -- /pwn
# write GZCTF_FLAG to /flag with permission 444, run as `nobody`
init -i:e GZCTF_FLAG -o:f /flag.txt -p 444 -u nobody -- python3 main.py
```

Example of using in Dockerfile:

```Dockerfile
FROM ghcr.io/pj-newstar/ctf-template/library/adapter:latest AS init

FROM alpine:latest

COPY --from=init /init /init

# ...

ENTRYPOINT ["/init", "-p", "444", "-u", "ctf", "--"]
CMD ["python3", "main.py"]
```