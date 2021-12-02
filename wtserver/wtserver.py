from flask import Flask
# from flask import render_template
from flask import send_file
# from flask import url_for

app = Flask(__name__)

@app.route("/")
def hello_world():
    return send_file('dashboard.html')

if __name__ == '__main__':
    app.run(debug=True,port=8080)
