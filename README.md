# simple_shell
A simple UNIX command interpreter. An immitation of the fantastic Bourne-again SHell a.k.a <code>bash</code>. I can't find a suitable name for my shell. Every Unix shell out there is an acronym of some words ending with the word "shell", like <code>bash</code> or <code>zsh</code> which stands for Z shell.

This shell is named <code>hsh</code>.

ALX Africa gave me the opportunity to work on this project during studying in their sorfware engineering program. 

#DoHardThings 

# Installation

To use this project, first clone the repo on your device using the command below:<br>
<code>git clone https://github.com/Abdorithm/simple_shell.git</code><br>
Then, the repo will be downloaded on your machine. <br>
<em>You can also download it as a zip file or fork it to your account.</em>

# Usage

After installation, fire up your terminal and navigate to the <code>simple_shell</code> directory.

To run the new shell, run this command:
<pre>
user@os:~/simple_shell$ ./hsh
</pre>

Now you can execute commands using our <code>hsh</code> instead of <code>bash</code> or <em>whatever the shell</em> in your system.
<pre>
abdo@pop:~/simple_shell$ ./hsh 
^-^$ ls
builtin_exit.c	hsh  main.c
^-^$ echo "hello, shell!"
"hello, shell!"
^-^$ exit
abdo@pop:~/simple_shell$ 
</pre>

# Commands
There are a numerous number of command a UNIX shell can intrepeter. To keep it short, following is a list of the commands that are not implemented yet. When these are implemented, I will delete the word "simple" from the repo name.

- Most built-ins, like the <code>cd</code> command and <code>alias</code>.
- Logical operators and command separators.
- File as input, and comments.

Otherwise, <code>hsh</code> works as expected, for more info about the development of this shell, I will write a <code>DEV.md</code>.
