# nc-python

Basic netcat challenge template using Python.

## Features

- Netcat the port to interact with the challenge.
- Hex decoding the output to get the flag.

## Configuration

FLAG represents in FLAG environment variable, which can be modified in [docker-compose.yml](docker-compose.yml).

Modify your source code in [src/](src/) to implement your challenge logic.

Modify [Dockerfile](Dockerfile) if you need to install additional dependencies, change entry script, or change python version.

### Exposes

The following port is exposed by the container:

| Port | Protocol | Description |
| ---- | -------- | ----------- |
| 1337 | TCP      | The port to interact with the challenge. |

## Usage

```bash
docker compose up -d
nc 127.0.0.1 11337
```
