# nc-file

Basic netcat challenge template.

## Features

- Netcat the port to interact with the challenge.
- Enter `admin` to get the flag.

## Description

The [Dockerfile](Dockerfile) has 2 stages:

- Build: Compile the C source code and generate the binary.
- Create a minimal image: Use socat to expose the binary on port 1337.

## Configuration

FLAG represents in FLAG environment variable, which can be modified in [docker-compose.yml](docker-compose.yml).

Modify your source code in [src/](src/) to implement your challenge logic.

Modify the build stage in [Dockerfile](Dockerfile) to compile your source code into a binary.

## Usage

```bash
docker compose up -d
nc 127.0.0.1 11337
```
