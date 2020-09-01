# CPU-Schedular-Simulator

In this programming exercise, i'll design a CPU scheduler simulator. This simulator would use a list data structure. Here is how it
should work: The scheduler should take in processes from a file named readylist.txt and add them to a list. The format of the file
would be:
<process_name, execution_time>

This file could have processes in any order. After reading in, your program should empty the file readylist.txt

 Once all the processes are read from the readylist.txt file into a list, your program would execute each of the processes in
highest-execution-time-first (the process having a highest execution time will be run first) order.

 But before executing any process, the program should print the sorted contents of the list, and example could be,
The contents of the ready queue are:
sms.exe, 23
mms.exe, 13
explorer.exe, 9
devmgmt.exe, 4
…..
…..

 Now it should start executing the processes in the list. For each process, execution just means that process stays at the head of
the list until time equal to its execution time has passed. The process is deleted from the list after that. At this moment 
program should print that such and such process has finished execution.
For Example
sms.exe, <Execution Time>, <Waiting Time>, <Turnaround Time>
e.g. if a process arrives at time 0, has an execution time of 4 and terminates at time 12 the output should be:
sms.exe, 4, 8, 12
  
 You must remember that this is a simulator. This means that you’ll have to define your own timer, one which increments in unit
steps (hint: use loop).

 After the passage of every 15 time units, your program should pause until the user presses <enter> and then check the contents
of the readylist.txt file to check if any new processes are added to it. It should continue the same way after reading the new
processes in, and print the contents of the list and so on.
  
 At the end , program should output the average waiting time and the average turnaround time for all the jobs.

Waiting Time for one Job = Execution Start Time – Arrival Time
Turnaround Time for one Job = Execution Ending Time – Arrival Time

Note: Jobs that are in the file at the start of the program are assumed to have arrival time 0. Jobs that appear in the file at time 10
have arrival time 10 and so on.
The program 'll terminate when there are no more processes in the queue and the readylist.txt file is empty.
