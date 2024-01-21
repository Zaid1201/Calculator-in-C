time = 0;
tic
while time < 3
    tic;
    time = time + toc;
    %disp(time);
end
toc
disp("3 seconds have passed");