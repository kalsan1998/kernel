import os
import serial
import subprocess
import sys
import time


def checksum(stream):
    s = 0
    for b in stream:
        s = s + b
    return s


if os.geteuid() != 0:
    os.execvp('sudo', ['sudo', 'python3'] + sys.argv)


BAUDRATE = 115200
img_path = sys.argv[1]
serial_path = sys.argv[2]
print('img_path: ', img_path)
print('serial_path: ', serial_path)

serial = serial.Serial(serial_path, BAUDRATE)
kernel_stream = open(img_path, 'rb')
kernel_size = os.path.getsize(img_path)

data = kernel_stream.read()
size = len(data)
checksum = checksum(data)
if checksum >= 2 ** 32:
    print('Checksum exceeded max int')
    exit(1)
print('Kernel size: ', size)
print('Kernel checksum: ', checksum)

serial.write(size.to_bytes(4, byteorder='big'))
serial.flush()
time.sleep(1)
size_confirmation = int.from_bytes(serial.read(4), byteorder='big')

if size_confirmation != size:
    print('Expected size ', size, ' but got ', size_confirmation)
    exit(1)

print('Size confirmed. Sending kernel.')

kernel_stream.close()
kernel_stream = open(img_path, 'rb')
i = 0
print('Progress: 0%')
while True:
    data = kernel_stream.read(1)
    sys.stdout.write("\033[F")
    sys.stdout.write("\033[K") #clear line
    print('Progress: ', i*100.0/size, '%')
    if not data:
        break
    serial.write(data)
    confirmation = serial.read()
    if data != confirmation:
        print('Sent ', data, ' but received ', confirmation)
        print('')
        exit(1)
    i += 1

time.sleep(1)

print('Kernel sent. Validating checksum.')
sum_confirmation = int.from_bytes(serial.read(4), byteorder='big')
if sum_confirmation != checksum:
    print('Expected checksum ', checksum, ' but got ', sum_confirmation)
    exit(1)
print('Sending ready.')
ready = 0
serial.write(ready.to_bytes(1, byteorder='big'))
print('SUCCESS')
exit(0)
