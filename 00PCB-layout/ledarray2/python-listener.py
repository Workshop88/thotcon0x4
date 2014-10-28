import select
import socket
import serial
import time

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('', 6667))

serial = serial.Serial("/dev/ttyUSB0", 115200)
scrollMode = True
lastTime = ''
sendOverride = False

while True:
  s.listen(1)
  conn, addr = s.accept()
  print 'Connected by', addr
  
  while True:
    # check if there's stuff to read
    try:
      ready_to_read, ready_to_write, in_error = select.select([conn],[],[],0.1)
    except:
      break
    
    # is there new stuff to read?
    if ready_to_read:
      if not scrollMode:
        scrollMode = True
        serial.write('b')
 
      try:
        data = conn.recv(1)
      except:
        break
        
      if not data:
        break
      # actually do something with it
      if not data == '\n':
        serial.write(data)
        response = serial.read()
        if not response == 'n':
          break
    else:
    #send time
      if scrollMode:
        scrollMode = False
	sendOverride = True
        serial.write('a')
        #serial.write('z')
        time.sleep(.5)

      #print str(sendOverride) + " asdf"
      currTime = time.strftime("%H:%M")
      if sendOverride or not lastTime == currTime:
        #print str(sendOverride) + " fooos"
        serial.write('z')      
        serial.write(currTime + "\n")
        lastTime = currTime
        sendOverride = False
     
    
    # do background task
    #print "background task"
    
  print 'Closing connection...'
  conn.close()
