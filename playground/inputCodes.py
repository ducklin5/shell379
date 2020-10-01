# https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html#writing-a-command-line
import sys, tty
tty.setraw(sys.stdin)
while True:
    char = sys.stdin.read(1)
    if ord(char) == 3: # CTRL-C
        break;
    print(ord(char))
    sys.stdout.write(u"\u001b[1000D") # Move all the way left
