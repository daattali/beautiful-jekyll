---
layout: post
title: Deploying Plotly Dash app to the cloud
subtitle: Lessons learned 
tags: [code]
comments: true
---

I love Plotly Dash and Flask, but I ran into issues while trying to deploy it in a production environment with continuous deployment, such that the latest version of my app was live as I was developing it.

For this, I found that [CapRover](https://caprover.com) was really powerful, for deployment, but the examples for Flask apps were not great (and the Plotly Dash documentaion was bad, too, because I think they want you to pay for their enterprise solution).

Here are the various errors I ran into and how I solved them.

The main issue was that you can no longer run `python app.py` on the server anymore, since Flask needs to be running below gunicorn. Also, I didn't have experience writing Docker files, so it took some time to get mine right.

When I tried running gunicorn using the boilerplate, I started getting an "App needs to be callable" error. This was caused by not exposing the right internal variables inside my `app.py`.

For instance, inside your main script:

```python
import flask

server = flask.Flask(__name__)
app = dash.Dash(__name__, server=server)
```


Here is my example captain file:

```
{
	"schemaVersion" : 2 ,
	"dockerfileLines" :[
		"FROM python:3.7.0-alpine",
    "RUN apk add --update curl gcc g++",
    "RUN ln -s /usr/include/locale.h /usr/include/xlocale.h",
    "RUN mkdir -p /usr/src/app", 
    "WORKDIR /usr/src/app",
    "COPY requirements.txt /usr/src/app",
    "RUN pip install --upgrade pip && pip install --no-cache-dir -r /usr/src/app/requirements.txt",
    "COPY ./ /usr/src/app",
		"RUN ls -la /usr/src/app",
		"EXPOSE 80 5000 27017 8050",
		"CMD [ \"gunicorn\", \"-b\", \":5000\", \"app:server\" ]"
	]
}
```
Here, the `app:server` section refers to the name of the python script (in my case, `app.py` and the exposed `server` variable).

Another big issue was that the Pandas dependencies were silently not being installed correctly. To fix this, you need to `sudo pip install --upgrade pip && sudo pip install -r /path/to/requirements.txt`. Running all the pip installs as a single line turns out to be crucial!

Finally, gunicorn did not use the default CapRover port of 80. So, in my Caprover config I had to change it to the one that is being printed out in your terminal. 


