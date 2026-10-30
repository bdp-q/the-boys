# 🦸The Boys: The Discrete super hero simulator!🦸
The Boys is a discrete-event simulation of a world of superheroes, bases and missions, written in C for the *Programming 1* course at UFPR led by Prof. [Marcos Castilho.](https://www.inf.ufpr.br/marcos/index-en.html)

Heroes wander between bases, queue up to get in, form teams, and get called to missions that require specific sets of skills. The simulation runs for one simulated year (525,600 minutes) and prints every event as it happens, followed by a final report with statistics for heroes, bases and missions.

Every run is randomized, so who lives and who dies always change!

> If you haven't noticed, the project is loosely inspired by the TV series *The Boys* ;) 

## Build and run for yourself

```bash
make            # builds ./theboys
make run        # builds and runs
make valgrind   # runs under Valgrind with full leak checking
make clean
```

It compiles with `-Wall -Werror -Wextra -std=c99 -g` and needs `-lm`.


## How it works

The simulator follows the classic discrete-event loop. A global clock jumps from event to event, and a **Future Event List (FEL)**, implemented as a priority queue ordered by time, holds everything that is going to happen.

```
create world and initial events
while there are events:
    ev = pop earliest event from the FEL
    clock = ev.time
    handle ev // updates state, may schedule new events
print results
```

> Note: To better understand the different events, the entities, and what the output means, I recommend reading the assignment prompt located in enunciado.pdf. The document and the output are in Portuguese, since the course was taken in Brazil.


## Project structure

```
theboys/
├── theboys.c        # main and the simulation loop
├── entidades.h      # structs for heroes, bases, missions and the world
├── universo.c/.h    # world constants, creation, destruction, initial events
├── eventos.c/.h     # one handler function per event
├── funcExtras.c/.h  # helpers (random numbers, distance)
├── fprio.c/.h       # priority queue ADT (the FEL)
├── fila.c/.h        # queue ADT (waiting queues)
├── conjunto.h/.o    # set ADT (provided by the course)
└── makefile
```

The data structures are built as abstract data types (ADTs):

- **Priority queue**: a sorted linked list. Insertion keeps items ordered by time, and items with the same priority come out in FIFO order.
- **Queue**: a linked list with a pointer to the last node for constant-time insertion.
- **Set**: used for each base's present heroes, each hero's skills and each mission's requirements. Provided as an object file by the course.

## Output
The interesting of the simulation is seeing the results. Every event is printed, so the output is basically all the story lines of what all the 50 heroes were doing for a year!

At the end, a report shows each hero's status and experience, each base's maximum queue length and missions handled, and global statistics such as missions completed, attempts per mission and mortality rate.

Since a full run produces millions of lines, the shell helps a lot:

```bash
./theboys | grep "HEROI 37" | more      # follow one hero story!
./theboys | tail -n 80                  # final report
```

## What I learned
This was my first big project in University, being an interesting beginner experience with C.
I learned:
- Building data structures, designing and using ADTs without breaking their abstraction
- Managing dynamic memory in a long-running program (every event is allocated and freed), and checking it with Valgrind
- Splitting a large C program into modules with a makefile
- Debugging a big program with a huge output by shrinking the scenario and filtering logs with `grep`
