FROM alpine:latest AS builder

RUN apk update && apk add --no-cache gcc musl-dev

COPY ./src /var/chal
WORKDIR /var/chal

RUN gcc -o ask ask.c \
    -fstack-protector-strong \
    -fstack-clash-protection \
    -D_FORTIFY_SOURCE=2 \
    -O2 \
    -pie \
    -fPIE \
    -Wl,-z,relro \
    -Wl,-z,now \
    -Wl,-z,noexecstack \
    -fcf-protection

FROM alpine:latest

ENV FLAG=flag{test_flag}

# install socat
RUN apk update && apk add --no-cache coreutils socat

# copy the compiled binary
COPY --from=builder /var/chal/ask /var/chal/ask
RUN chmod +x /var/chal/ask

# CMD ["tcpserver", "-v", "-D", "-c", "50", "0", "1337", "/var/chal/ask"]
CMD ["socat", "TCP4-LISTEN:1337,reuseaddr,fork", "EXEC:/var/chal/ask"]

EXPOSE 1337
