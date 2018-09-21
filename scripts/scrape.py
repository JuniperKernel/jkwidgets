import os
import sys
import re

def stage1():
  d = "../inst/include/xwidgets"
  headers = os.listdir(d)
  for h in headers:
    p = os.path.join(d, h)
    with open(p, 'rb') as hf:
      print("file {}".format(h))
      for line in hf:
        ls = line.strip()
        if len(ls) > 5:
          if (ls[0]=='c') and (ls[1]=='l') and (ls[2]=='a') and (ls[3]=='s') and (ls[4]=='s'):
            print ls
        if "XPROPERTY" in ls:
          print ls

def process_xprop(l):
  if "XPROPERTY" not in l:
    raise ValueError("not an XPROPERTY: {}".format(l))

  l = l[len("XPROPERTY("):]
  choices = None

  if "XEITHER" in l:
    m = re.search("XEITHER.*\(", l)
    substr = l[m.end():]
    p = "[{}]".format(substr).translate(None, '();')
    choices = p
    l = l[:m.start()]

  info =  prop_info(l)
  info.update({'choices': choices if choices else "None"})  
  return info
  
def prop_info(xprop):
  info = xprop.split(',')
  info = [i.strip().translate(None, '();') for i in info]
  return {
    'type': info[0],
    'name': info[2],
    'default': "None" if len(info) < 4 else info[3],
  }
 
def stage2(stage1_result):
  with open(stage1_result, 'rb') as f:
    # read a class
    # for each class read N XPROPERTY instances
    # for each XPROPERTY do some extra work
    # if no XPROPERTY instances found, skip...
    l = f.readline()
    fname = ""
    clazz = ""
    while l!='':
      if "file" in l:
        fname = l.split()[1]
        l = f.readline()
      if "class" in l:
        clazz = l.split()[1]
        # read until we hit next "class" isntance
        l = f.readline().strip()
        while (l!='') and ("class" not in l) and ("file" not in l):
          l = process_xprop(l)
          print("{}:{} -> {}".format(fname, clazz, l))
          l = f.readline().strip()
        continue
      l = f.readline()

if __name__ == "__main__":
  args = sys.argv
  if len(args) == 1:
    stage1()

  if len(args) == 2:
    stage2(args[1])
