# Running the Server under Linux
When you SSH into your server and want to run `./shizu-server` then
follow these instructions:

Run Shizu server in detached state by entering
```
shizu-server &
```
To terminate the running server, find its process id by
```
ps -eo pid,command | grep shizu-server
```
and send it a sigint
```
kill -SIGINT 6699
```
assuming the process it was determined to be `6699`.
