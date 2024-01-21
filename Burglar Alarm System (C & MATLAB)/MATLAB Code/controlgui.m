clear device;
device = serialport("COM4",9600,"Timeout",120);
flush(device);
run intro.mlapp;
pause(10); % Adding a delay to allow the ardino program to load.

currentPIN = '1234';
currentTimer = 10;