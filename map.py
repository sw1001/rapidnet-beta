
def replace(file_name):
  s = open('./data/prov/'+file_name, 'r').readline().strip()
  print s
  with open('./data/map/'+file_name, 'r') as f:
    for line in f.readlines():
      line = line.strip()
      l = line.split(' ')
      s = s.replace(l[0], l[1])
  return s

if __name__ == '__main__':
  s = replace('trustPath4-5.txt')
  print s
