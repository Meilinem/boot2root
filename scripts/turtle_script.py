from turtle import *

f = open("turtle", "r")
text = f.read()
lines = text.count("\n")
i = 1
number = ""
x = 0
y = 0
setpos(x, y)
shape("turtle")
fillcolor("green")
n_color = ["red", "blue", "green", "brown", "blue"]
n_c = 0
pencolor(n_color[n_c])

with open("turtle") as fp:
   line = fp.readline()
   cnt = 1
   while line:
       if len(line) < 3:
           penup()
           setpos(x, y)
           pendown()
           n_c+=1
           if n_c < 5:
               pencolor(n_color[n_c])
           x+=100
           y+=50

       if "gauche" in line:
           #print("left : ")
           for n in line:
               if n.isdigit():
                   number += n
           #print(number)
           left(int(number))
           number=""

       if "droite" in line:
           #print("right : ")
           for n in line:
               if n.isdigit():
                   number += n
           #print(number)
           right(int(number))
           number=""

       if "Avance" in line:
           #print("forward : ")
           for n in line:
               if n.isdigit():
                   number += n
           #print(number)
           forward(int(number))
           number=""

       if "Recule" in line:
           #print("backward : ")
           for n in line:
               if n.isdigit():
                   number += n
           #print(number)
           backward(int(number))
           number=""

       #print("Line {}: {}".format(cnt, line.strip()))
       line = fp.readline()
       cnt += 1

fp.close()
f.close()

while True:
    a=1
