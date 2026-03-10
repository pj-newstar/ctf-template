# web-rust

Web challenge template using Rust with a custom HTTP server.

## Features

- Rust-based HTTP server.
- Serves static files from `static/` directory.
- Dynamic route `/robots.txt` that contains the path to the flag.

## Configuration

FLAG represents in FLAG environment variable, which can be modified in [docker-compose.yml](docker-compose.yml).

Modify the Rust source code in this directory.

Modify build stage in [Dockerfile](Dockerfile) to compile your Rust source code into a binary.

Copy other necessary files into the final image and configure the server to serve them.

### Exposes

The following port is exposed by the container:

| Port | Protocol | Description |
| ---- | -------- | ----------- |
| 80   | TCP      | The port to the challenge HTTP server. |

## Usage

```bash
docker compose up -d
```

Access at `http://localhost:8000`
