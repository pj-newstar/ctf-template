FROM alpine:latest AS builder

COPY init.c /init.c

RUN apk add --no-cache --virtual .build-deps gcc musl-dev

RUN gcc /init.c -o /init -static -no-pie

# ensure only root can execute the init binary
RUN chmod 100 /init

FROM scratch

COPY --from=builder /init /init

