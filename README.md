Concurrent programming
=================================
This contains the lab assignment 1 for concurrent programming module.
# How to run the programme
### Serial linked list
- **gcc -g linkedListSerial.c -o linkedListSerial.o -lm** to compile.
- **./linkedListSerial.o** to run the executable file.
### Linked list with one mutex for the entire linked list
- **gcc -g linkedListMutex.c -o linkedListMutex.o -lm -lpthread** to compile.
- **./linkedListMutex.o ** to run the executable file.
### Linked list with read-write locks for the entire linked list
- **gcc -g linkedListReadWriteLock.c -o linkedListReadWriteLock.o -lm -lpthread** to compile.
- **./linkedListReadWriteLock.o ** to run the executable file.
