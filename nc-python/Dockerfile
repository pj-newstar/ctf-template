FROM python:3.10-alpine

ENV FLAG=flag{test_flag}

# install socat
RUN apk update && apk add --no-cache coreutils socat

# copy the challenge files
COPY src/ /var/chal/
RUN chmod +x /var/chal/main.py

WORKDIR /var/chal

# install python dependencies
# RUN pip install --no-cache-dir -r requirements.txt

# CMD ["tcpserver", "-v", "-D", "-c", "50", "0", "1337", "python3", "/var/chal/main.py"]
CMD ["socat", "TCP4-LISTEN:1337,reuseaddr,fork", "EXEC:python3 /var/chal/main.py"]

EXPOSE 1337
