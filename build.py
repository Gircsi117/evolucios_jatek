import subprocess
import os

def saveComamnd(command):
  with open("build.txt", "w") as f:
    f.write(" ".join(command))

def getFiles(folder):
  a = []
  for root, subFolder, files in os.walk(folder):
    for file in files:
      fullRoot = os.path.join(root, file)
      a.append(fullRoot.replace("\\", "/"))
  return a

def generateCommand(files):
  command = ["g++", "-o", "build/app", "-Wall", "main.cpp"]

  for i in files:
    if(i[-4::] == ".cpp"):
      command.append(i[2::])

  subprocess.run(command)
  subprocess.run(["./build/app"])

  saveComamnd(command)

generateCommand(getFiles("./src"))