device = serialport('COM3',9600);
while 1
    mode = read(device,6,"char");
    disp(mode);
    if mode == "Opened"
        streamingFaceRecognition(8,0.5,3);
    end
end