from turtle import *

f = open("turtle", "r")
text = f.read()
lines = text.count("\n")
i = 0
number = ""
x = 1
y = 1

with open("turtle") as fp:
   line = fp.readline()
   cnt = 1
   while line:
       if len(line) < 3:
           penup()
           goto(x, y)
           pendown()
           x += 1
           y += 1

       if "gauche" in line:
           print("left : ")
           for n in line:
               if n.isdigit():
                   number += n
           print(number)
           left(int(number))
           number=""

       if "droite" in line:
           print("right : ")
           for n in line:
               if n.isdigit():
                   number += n
           print(number)
           right(int(number))
           number=""

       if "Avance" in line:
           print("forward : ")
           for n in line:
               if n.isdigit():
                   number += n
           print(number)
           forward(int(number))
           number=""

       if "Recule" in line:
           print("backward : ")
           for n in line:
               if n.isdigit():
                   number += n
           print(number)
           backward(int(number))
           number=""

       #print("Line {}: {}".format(cnt, line.strip()))
       line = fp.readline()
       cnt += 1

fp.close()
f.close()

while True:
    a=1
