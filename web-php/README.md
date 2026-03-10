# web-php

Basic web challenge template using PHP and Apache.

## Features

- PHP with Apache server.
- Directly outputs the flag.

## Configuration

FLAG represents in FLAG environment variable, which can be modified in [docker-compose.yml](docker-compose.yml).

Modify files in `src/` to implement your challenge.

### Exposes

The following port is exposed by the container:

| Port | Protocol | Description |
| ---- | -------- | ----------- |
| 80   | TCP      | The port to the challenge web server. |

## Usage

```bash
docker compose up -d
```

Access at `http://localhost:18080`
