import sys

lines_in = open('font.txt', 'r').readlines()
fout = open('font.c', 'w')

def nonblank(x):
  if x==" ":
    return 0
  else:
    return 1

num_chars = len(lines_in)/7

for i in xrange(num_chars):
  tlines = lines_in[7*i : 7*i + 7]
  
  # get font character  
  tchar = tlines[0][:-1] # remove NL

  sys.stderr.write(tchar)

  # get width
  twidth = int(tlines[1].strip())

  # remove newline and then pad rows
  for j in xrange(5): # j = row#
    tlines[j+2] = tlines[j+2][:-1] + "     "
    
  # construct columns
  tcols = []
  for j in xrange(5): # j = col#
    tcolval = 0
    for k in xrange(5): # k=row#
      tcolval += nonblank(tlines[k+2][j]) << k
    tcols.append(tcolval)
    
  
  # output
  esc_tchar = tchar.replace("\\", "\\\\").replace("'", "\\'")
  ts = ""
  ts += "const char font_%d[] PROGMEM = { '%s', %d" % (i, esc_tchar, twidth)
  for j in tcols: # j = col#
    ts += ", 0x%02x" % j
  ts += " };"
  print ts
  
  
# output the font count and array
print "#define FONT_SIZE %d" % num_chars
print "PGM_P font[%d] PROGMEM = {" % num_chars,
print ", ".join(map(lambda(x): "font_"+str(x), xrange(num_chars))),
print " };"
