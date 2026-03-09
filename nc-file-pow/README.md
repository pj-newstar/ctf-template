# nc-file

Basic netcat challenge template with Proof of Work (PoW) protection, compared to [nc-file](../nc-file/).

## Comparison

If you want to add Proof of Work protection to your existing challenge, follow the steps below to modify your Dockerfile:

1. Pull [ghcr.io/pj-newstar/proof-of-work](https://github.com/pj-newstar/proof-of-work/pkgs/container/proof-of-work) and copy its binary into the image.

2. Wrap the challenge execution command with `pow run <difficulty> -- <original_command>`. The difficulty can be adjusted based on the expected time to solve the PoW.

For more details about the `pow` binary, please refer to [pj-newstar/proof-of-work](https://github.com/pj-newstar/proof-of-work).

### Dockerfile Diff

```diff
+ FROM ghcr.io/pj-newstar/proof-of-work:latest AS pow

  FROM alpine:latest AS builder

  RUN apk update && apk add --no-cache gcc musl-dev

  ENV FLAG=flag{test_flag}

+ # copy the pow binary
+ COPY --from=pow /usr/local/bin/pow /usr/local/bin/pow

  # install socat
  RUN apk update && apk add --no-cache coreutils socat

  WORKDIR /var/chal

- CMD ["socat", "TCP4-LISTEN:1337,reuseaddr,fork", "EXEC:/var/chal/app"]
+ CMD ["socat", "TCP4-LISTEN:1337,reuseaddr,fork", "EXEC:/usr/local/bin/pow run 15360 -- /var/chal/asappk"]

 EXPOSE 1337
```

## Usage

```bash
docker compose up -d
nc 127.0.0.1 1337
```
