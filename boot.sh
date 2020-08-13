python3 ./tools/boot_send.py ./out/client_kernel.img /dev/ttyUSB0
if [ $? -eq 0 ]; then
    cd ./out
    rm  -rf ./screenlog*
	sudo screen -L -S screenlog /dev/ttyUSB0 115200
    cd ../
fi
