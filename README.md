# consumerProducer
This project is the solution for the second task ```The producer-consumer problem revisited ```. For making this solution I used phtread.h and semaphore.h libraries

### Environment
This project was made on Kali-Linux-2021.1-vbox-amd64

### Running the project
Locate in the root directory of the repo and then
```make``` and ```./main``` First you specify the number of maximum items that can be produced by producer and consumed by consumer, then the number of consumers and lastly the number of producers. In some cases this program could run infinnitely, so if the number of consumers and producers are not valid the program will not run.

### Quick overview of the project
Firstly the global variables are declared or initialized. Below it there are two method - `consumerMethod` and `producerMethod`, which are the heart of the solution. In main there are some scanfs, quick input validation and calls of the mentioned above methods.
