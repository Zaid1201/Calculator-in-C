clear device
%%Matlab code to send a ‘1’ on the serial line to the Arduino when the user presses    % ENTER. Author TB 11.08.2021
%Clear ports

% if ~isempty(instrfind)    
% fclose(instrfind);
% delete(instrfind);
% end
disp('BURGLAR ALARM SYSTEM');
disp('Default PIN: 1234');
PIN="1234"; % default PIN
STATE = 2; % starts in idle state
electricity = 1;

if exist('device','var') == 0   % so that if its already there we don't declare it twice
    device = serialport("COM4",9600,"Timeout",60);  %changed timeout val so no error orange
    flush(device);
    pause(10);% for arduino to "load"
end
% main while loop
while electricity % would be while 1 in final application     
    while STATE == 1 % Active state
        disp('ACTIVE STATE');
        door = read(device,1,"char");
        if door == 'D'   % door opened (can have an or case and add window)
            disp("Door has been opened...");
            while input("PIN: ",'s') ~= PIN     % asking for PIN
                disp("WRONG PIN, PLEASE TRY AGAIN");
%                     door = read(device,1,"char");
%                 if door == 'A'
%                     disp("ALARM ACTIVATED");
%                 elseif door == 'P'
%                     disp("Buzzer off")
%                 end
            end
            write(device,1,"uint8"); % correct pin inputted
            clc
            disp('SYSTEM DEACTIVATED... going into idle state...');
            pause(3);
            clc
            STATE = 2;
        end
    end
    while STATE == 2 % Idle State (Starting Point)
        % Functions to add here: Change PIN, Change timer, Change mode
        option = input("\nMAIN MENU (idle state)\n(1) Active \n(2) Add Faces \n(3) Reset & Add Faces\n(4) Change Timer\n(5) Change PIN \n(6) Exit\nOption: ");       
        switch option
            case 1  % Activate System
                STATE = 1;
                write(device,1,"uint8");
            case 2  % Add Faces
                % streamingFaceRecognition(8,0.5,2);
            case 3  % Reset & Add Faces
                % streamingFaceRecognition(8,0.5,1);
            case 4 % change timer 
             
            case 5 % change PIN
                PIN = changePin(PIN);
            case 6 % exit function
                electricity = 0;
                disp('Exiting program...');
                break
        end
        clc
    end
end

function [NEW_PIN] = changePin(PIN) % changing PIN function
    disp('This is change pin function: ');
    xx=0;
    x1=0;
    while (xx==0)
        temp_PIN = input('enter the OLD pin: ','s');
        if isequal(temp_PIN,PIN)
            disp('The PIN is correct');
            % checking is the new PIN 4 character long
            while(x1==0)
                temp_PIN = input('enter the new pin: ','s');
                
                if isequal(size(temp_PIN),[1 4]) % the size requiremtns has been satisfy
                    temp_PIN2=input('re-enter the new pin: ','s');
                    if isequal(temp_PIN2,temp_PIN) % checking are new PINS the same
                        
                        x1=1; % ending while loop
                        xx=1; % ending while loop
                        
                        NEW_PIN=temp_PIN;
                        
                        clc;
                    else % pin are not equal
                        disp('Your new pins doesn;t match ');      
                    end
                else % the size of new pin is not 4
                    disp('The PIN is not size 4, try again');
                end
            end
        else
            disp('the PIN is incorret please try again'); 
        end
    end
end