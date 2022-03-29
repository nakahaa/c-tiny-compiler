## build 
 1. docker build -t toy-c . 
 2. docker run -d --name toy-c toy-c sleep 10000000000000000000
 3. docker cp c-tinycompiler toy-c:/src/
 4. docker exec -it toy-c bash 
 5. cd /src/c-tinycompiler/
 6. make 

## run 

cat tests/test1.c | ./compiler 