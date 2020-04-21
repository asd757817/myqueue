# myqueue

This project will demo simple queue operations and implementations.

There will be 3 different queue in this project.
- main.c
    This only supports simple operations like insert and pop.
    This isn't a thread-safe queue. It's not realiable that applying this in multithread program

@TODO
- thread-safe_main.c
    Support multithread program by mutex.

- lock-free_main.c
    Implement a lock-free queue which can be uesd in multithread program.
    Use CAS instruction.


