import os
from flask import Flask

app = Flask(__name__)

FLAG = os.getenv("flag", "flag{test_flag}")

@app.route("/")
def index():
    return f"<strong>Your flag is</strong> {FLAG}"

if __name__ == "__main__":
    app.run(host="0.0.0.0", debug=False, port=5000)
