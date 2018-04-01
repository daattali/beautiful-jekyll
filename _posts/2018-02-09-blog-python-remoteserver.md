---
layout: post
title: Run Jupyter notebook on a remote server
show-avatar: true
tags:
  - blogs
  - python
  - remote server
published: true
---

### Run Jupyter notebook on a remote server

- On the remote machine, start the jupyter notebooks server:

```
remote_user@remote_host$ jupyter notebook --no-browser --port=8889
```


- On the local machine, start an SSH tunnel:

```
local_user@local_host$ ssh -N -f -L localhost:8888:localhost:8889 remote_user@remote_host
```
The first option -N tells SSH that no remote commands will be executed, and is useful for port forwarding. 
The second option -f has the effect that SSH will go to background, so the local tunnel-enabling terminal remains usable. 
The last option -L lists the port forwarding configuration (remote port 8889 to local port 8888). Alternatively, you can start the tunnel without the -f option. 
The process will then remain in the foreground and can be killed with ctrl-c.


- Now open your browser on the local machine and type in the address line:

```
localhost:8888
```


- To close the SSH tunnel on the local machine, look for the process and kill it manually:

```
local_user@local_host$ ps aux | grep localhost:8889
local_user 18418  0.0  0.0  41488   684 ?        Ss   17:27   0:00 ssh -N -f -L localhost:8888:localhost:8889 remote_user@remote_host
local_user 18424  0.0  0.0  11572   932 pts/6    S+   17:27   0:00 grep localhost:8889
```

```
local_user@local_host$ kill -15 18418
```
