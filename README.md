#README

This is my own shell, called rshell. This is an assignment for cs100 at UCR and is an attempt of creating a simple version of bash.

The project aims to work in a similar way as bash, but simpler. For example, the cd commad cannot be used.

The program ends when "exit" is entered.

##Download and use

To download project, use:


```
$ git clone  https://github.com/ecarr007/rshell.git
$ cd rshell
$ git checkout hw0
$ make
$ bin/rshell
```

Following these steps will allow you to download and use the project.

##known bugs

This project cannot run the cd command, as it cannot be called by execvp or other functions in the exec family.

This program can only run one command at a time. It is not able to use connectors.

When the word "test" is typed in, no error is output.
