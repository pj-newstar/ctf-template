FROM python:3.10-slim

WORKDIR /app

# install gunicorn
RUN pip install --no-cache-dir gunicorn

# cache requirements first to speed up subsequent builds
COPY src/requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

COPY src/ /app/

# CMD ["python3", "src/main.py"]
CMD ["gunicorn", "-w", "4", "-b", "0.0.0.0:80", "main:app"]

EXPOSE 80
