# web-python-flask

Basic web challenge template using Python web framework Flask.

## Features

- Python Flask-based web server.
- Uses **Gunicorn** as production WSGI server.
- Directly outputs the flag.

## Configuration

FLAG represents in FLAG environment variable, which can be modified in [docker-compose.yml](docker-compose.yml).

Modify files in `src/` to implement your challenge.

If you want to start the development server instead of using Gunicorn, or use other WSGI server, you can change the `CMD` in [Dockerfile](Dockerfile).

### Exposes

The following port is exposed by the container:

| Port | Protocol | Description |
| ---- | -------- | ----------- |
| 80   | TCP      | The port to the challenge WSGI server. |

## Usage

```bash
docker compose up -d
```

Access at `http://localhost:8080`
