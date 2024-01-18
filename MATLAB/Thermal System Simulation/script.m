%Title: Task 1
%Name: Zaid Daghash
%Date written: 03/04/2022
%Purpose of code: This code assigns parameters for a given thermal system and then proceeds to simulate the thermal system through a simulink model.
                  %The output of the simulation is then extracted and plotted. The steady-state value and the settling time (2%) for both temperatures in the system is displayed in
                  %the command window.

%Creating variables for use in the model.

    C1=100; %First capacitance (J/K).
    C2=60; %Second capacitance (J/K).
    R1=10; %First resistance (Ks/J).
    R2=10; %Second resistance (Ks/J).
    R3=10; %Third resistance (Ks/J)
    R12=((R1*R2)/(R1+R2)); %Sum of first and second resistances in parallel (Ks/J).
    R23=((R2*R3)/(R2+R3)); %Sum of second and third resistances in parallel (Ks/J).
    Theta_A=293.15; %Ambient temperature (Kelvin).

out=sim('Model'); %Simulating the model.

figure(1) %Creating the figure.
    
    set(gcf,'units','normalized','outerposition',[0 0 1 1]) %Setting the figure to occupy the entire screen.

    subplot(1,2,1) %First graph
    plot((out.ScopeData{1}.Values.Time)/60,out.ScopeData{1}.Values.Data(:,1)) %Plotting the output of 'theta_2'.
    hold on
    plot((out.ScopeData{2}.Values.Time)/60,out.ScopeData{2}.Values.Data(:,1)) %Plotting the output of 'theta_1' on the same plot as 'theta_2'.
    grid on %Displaying grid lines.
    hold off
    title('"\theta_1 & \theta_2" Model') %Giving the graph a title.
    xlabel("Time (Minutes)"); %Labelling the x-axis.
    ylabel("Temperature (Kelvin)"); %Labelling the y-axis.
    legend('\theta_2','\theta_1','Location','northeastoutside'); %Providing a legend since there are two plots on the same graph.

    subplot(1,2,2) %Second Graph
    plot((out.ScopeData1{1}.Values.Time)/60,out.ScopeData1{1}.Values.Data(:,1)) %Plotting the input heat flow on a different graph.
    title('"Heat Flow into the System" Model') %Giving the graph a title.
    xlabel("Time (Minutes)") %Labelling the x-axis.
    ylabel("Q1 (Amplitude)") %Labelling the y-axis.


t = (out.ScopeData{1}.Values.Time); %Assigning the output time of 'theta_2' to the variable 't'.
t2 = (out.ScopeData{2}.Values.Time); %Assigning the output time of 'theta_1' to the variable 't2'.

y=out.ScopeData{2}.Values.Data(:,1); %Assigning the output data of 'theta_1' to the variable 'y'.
y2=out.ScopeData{1}.Values.Data(:,1); %Assigning the output data of 'theta_2' to the variable 'y2'.

T1initial = y(1); %The initial value of 'Theta_1'
T2initial = y2(1); %The initial value of 'Theta_2'

SST1=y(end); %Finding the steady-state value of 'theta_1'.
SST2=y2(end); %Finding the steady-state value of 'theta_2'.

%Finding the settling time of 'theta_1'

    J=stepinfo(y,t2/60,SST1,T1initial);
    S=J.SettlingTime;
    Settling_Time_Theta1 = S-10; %Subtracting the dead-time
  

%Finding the settling time of 'theta_2'

    K=stepinfo(y2,t/60,SST2,T2initial);
    L=K.SettlingTime;
    Settling_Time_Theta2 = L-10; %Subtracting the dead-time
 

fprintf(['\nThe steady-state value of \x3B8(1) is: ',num2str(SST1),' Kelvin']); %Printing the steady-state value of 'theta_1' to the command window.
fprintf(['\nThe steady-state value of \x3B8(2) is: ',num2str(SST2),' Kelvin\n']); %Printing the steady-state value of 'theta_2' to the command window.
fprintf(['\nThe settling time for \x3B8(1) is: ',num2str(Settling_Time_Theta1),' minutes']); %Printing the settling time of 'theta_1' to the command window.
fprintf(['\nThe settling time for \x3B8(2) is: ',num2str(Settling_Time_Theta2),' minutes\n']); %Printing the settling time of 'theta_2' to the command window.