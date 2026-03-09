# nc-python

Basic netcat challenge template using Python.

## Configuration

Modify your source code in [src/](src/) to implement your challenge logic. The flag is stored in the `FLAG` environment variable, which can be set in `docker-compose.yml`.

Modify [Dockerfile](Dockerfile) if you need to install additional dependencies, change entry script, or change python version.

## Usage

```bash
docker compose up -d
nc 127.0.0.1 1337
```
