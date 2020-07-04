python3 ./tools/boot_send.py ./out/client_kernel.img /dev/ttyUSB0
if [ $? -eq 0 ]; then
	sudo screen /dev/ttyUSB0 115200
fi