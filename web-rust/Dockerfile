FROM rust:1-alpine AS builder

RUN apk add --no-cache build-base

WORKDIR /app

COPY Cargo.toml ./
COPY src ./src
COPY static ./static

RUN cargo build --release --bin web_server

FROM alpine:latest

ENV FLAG=flag{test_flag}
RUN mkdir -p /var/www/html

WORKDIR /var/www/html

COPY --from=builder /app/static/ /var/www/html/
COPY --from=builder /app/target/release/web_server /usr/local/bin/web_server

CMD ["/usr/local/bin/web_server"]

EXPOSE 80