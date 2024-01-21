clear device
clc

fprintf("BURGLAR ALARM SYSTEM\nDefault PIN: 1234\nDefault timer: 10 seconds\n"); % Default info displayed before the program is run.
PIN = "1234"; % Default PIN.
STATE = 1; % Program starts in idle state (Menu options).
electricity = 1; % Variable used as a condition in a while loop for exiting the program. 
Timer = 10; % Default timer.
key = 0;

if exist('device','var') == 0   % Checking if the usb port is connected to the arduino.
    device = serialport("COM6",9600,"Timeout",120);  
    flush(device);
    pause(10); % Adding a delay to allow the ardino program to load.
end

% Main while loop
        flush(device);
        fprintf('ACTIVE STATE\n');
        sensor = read(device,1,"char"); % reading from arduino
        if sensor == 'M' % If movement has been detected
            fprintf('\nMotion detected outside the door');
            detection = streamingFaceRecognition(8,0.5,3); % Running Facial Recognition.
            if detection == 1 % Person identified
                write(device,1,"uint8");
            else % Person not identified
                write(device,0,"uint8");
                fprintf('\nPerson not identified.\nNotifying user of unidentified person.\n');
            end
        end
        sensor = read(device,1,"char"); % reading from arduino
           
        if sensor == 'D'   % Door opened when unlocked
            disp("DOOR has been opened...");
            key = checkPINalarm(PIN,device);  % Asking for PIN
            if key == 1 %Correct PIN has been entered
                clc
                disp('SYSTEM DEACTIVATED... going into IDLE state...');
                pause(2);
                clc
                STATE = 2;
            end
        end

function key = checkPINalarm(PIN,device) %% checking PIN to de-activate the system
    TimePassed = 'N';
    attempts = 0;
    correctPIN = false;
    disp('Enter PIN to deactivate alarm.');
    while attempts < 3 && ~correctPIN
        flush(device);
        alarm = read(device,1,"char");
        if  alarm == 'A' % Timer has ended
            fprintf('\nALARM IS SOUNDING\nCALLING EMERGENCY SERVICES\n\n');
        end
        inputPIN = input("PIN: ","s");
        if isequal(inputPIN,PIN) % Correct PIN entered
            key = 1;
            correctPIN = true;
            write(device,1,"uint8");
        else
            msg = ['WRONG PIN: ',num2str(2-attempts),' attempts left.'];
            disp(msg);
            attempts = attempts + 1;
        end
    end
    if attempts == 3 % Exceeded number of attempts
        clc
        disp('Exceded number of attempts.');
        runonce = 1;
        while ~isequal(TimePassed,'Y')
            TimePassed = read(device,1,"char"); % wait for arduino input
            if TimePassed == 'A'&& runonce
                fprintf('\nALARM IS SOUNDING\nCALLING EMERGENCY SERVICES\n\n');
                runonce = 0;
            end 
        end
        write(device,1,"uint8");
        key = 1;
        clc 
   end
end

function key = checkPIN(PIN) %% Checking PIN function returning "1" if PIN is correct and "0" if incorrect (Used in the menu options)
    attempts = 0;
    correctPIN = false;
    disp('Please enter your PIN to confirm procedure.');
    while attempts < 3 && ~correctPIN
        inputPIN = input("PIN: ","s");
        clc
        if isequal(inputPIN,PIN)
            key = 1;
            correctPIN = true;
        else
            msg = ['WRONG PIN: ',num2str(2-attempts),' attempts left.'];
            disp(msg);
            attempts = attempts + 1;
        end
    end
    if attempts == 3
        key = 0;
        clc
        disp('Exceded number of attempts.');
        pause(1);
        clc 
   end
end

function [Timer] = changeTimer(device) % Changing Timer function
    clc
    Timer = 0;
    fprintf("\nChanging timer\nTimer must be between 10-60 seconds.\n");
    write(device,4,"uint8");
    while Timer < 10 || Timer > 60 % Outside limits                    
        Timer = input("New timer: "); % Asking for new timer
        if Timer < 10 || Timer > 60
            disp("Timer outside limits.\n");
        end
    end
    Timer = uint32(Timer);
    clc
    write(device,Timer,"uint32");  
end
