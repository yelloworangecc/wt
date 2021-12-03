from flask import Flask
from flask import render_template
from flask import send_file
from flask import url_for

app = Flask(__name__)

@app.route('/')
def hello_world():
    return render_template('dashboard.html')

@app.route('/album/')
@app.route('/album/<name>')
def album(name=None):
    if name is None:
        return render_template('album.html')
    else:
        return send_file('album/'+name)

if __name__ == '__main__':
    app.run(debug=True,port=8080)
