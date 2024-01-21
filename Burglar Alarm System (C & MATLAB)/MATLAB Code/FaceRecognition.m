mode = input("1. Reset\n2. Add Faces\n3. Use as is\n");
if mode == 3
    detection = streamingFaceRecognition(8,0.5,3);
    disp(detection);
else
    detection = streamingFaceRecognition(8,0.5,mode);
end