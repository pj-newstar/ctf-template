# nc-file

Basic netcat challenge template.

## Description

The [Dockerfile](Dockerfile) has 2 stages:

- Build: Compile the C source code and generate the binary.
- Create a minimal image: Use socat to expose the binary on port 1337.

## Configuration

Modify your source code in [src/](src/) to implement your challenge logic. The flag is stored in the `FLAG` environment variable, which can be set in `docker-compose.yml`.

Modify the build stage in [Dockerfile](Dockerfile) to compile your source code into a binary.

## Usage

```bash
docker compose up -d
nc 127.0.0.1 1337
```
