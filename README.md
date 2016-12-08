Concurrent programming
=================================
This contains the lab assignment 1 for concurrent programming module.
# How to run the programme
### Serial linked list
- `gcc -Wall -g src/linkedListSerial.c -o linkedListSerial.o -lm` to compile.
- `./linkedListSerial.o` to run the executable file.

### Linked list with one mutex for the entire linked list
- `gcc -Wall -g src/linkedListMutex.c -o linkedListMutex.o -lm -lpthread` to compile.
- `./linkedListMutex.o` to run the executable file.

### Linked list with read-write locks for the entire linked list
- `gcc -Wall -g src/linkedListReadWriteLock.c -o linkedListReadWriteLock.o -lm -lpthread` to compile.
- `./linkedListReadWriteLock.o` to run the executable file.

### All the above cases in a single file
- `gcc -Wall -g src/allInOne.c -o allInOne.o -lm -lpthread` to compile.
- `./allInOne.o` to run the executable file.

### sample inputs
- No of samples: 25
- Enter n: 1000
- Enter m: 10000
- Enter member_fraction: 0.99
- Enter insert_fraction: 0.005
- Enter delete_fraction: 0.005
- Enter thread count: 2

