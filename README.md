# holbertonschool-simple_shell
This is a project for replicating the sh command. What this program does is prompt the user for some input. Depending on the input there will be a program associated with it. This program will be executed by a seperate call by the sh program. Once the command has been executed, it will then prompt the user for another command. This repeats until the user inputs the command to exit.
## Programs Used
- **execve.c** : forks a child process to execute command line input
- **findpath.c** : identifies the path variable and returns a string of that path
- **free_array.c** : frees memory allocated for token array and path array
- **main.c** : entry point for program - displays prompt, receives input, and exits on command
- **maketoken.c** : receives a string and tokenizes based on specified delimiter
- **shell.h** : header file containing used functions

## Flow Chart
![Ugly Flow Chart](https://github.com/Jimwall0/holbertonschool-simple_shell/assets/127359266/00e7f1e8-fab0-4d47-ad91-d67ac6d52b27)
## Credits
- Ryan Donaldson
- Tsim Muaj Yang
