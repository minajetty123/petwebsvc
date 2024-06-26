# Pet web Service
A C++ http service to handle with CRUD pet
### Prerequisites
* C++ 17 or above
### Preliminary Install
* sudo apt install libboost-all-dev
## Build && Running
Go to root folder of the project
```
mkdir build
cd build
cmake ..
make
then run executable ./petwebsvc
```
## Test
```
. Add Pet (Post): curl -X POST -d '{"name": "Fluffy"}' -H "Content-Type: application/json" http://localhost:8080/pets
. Delete Pet (Post): curl -X DELETE http://localhost:8080/pets/1
. Get Pets (Get): curl http://localhost:8080/pets
. Get Pet (Get): curl http://localhost:8080/pets/1
```
## Following up:
```
To running under high availability, scalability and observability
. Dockerization (for container registry) and running under orchestrator based on statefulset 
. Add Up Observability for monitoring perf and its business logic metrics
. Running LoadTest to test its scalability, stability responsiveness
```

