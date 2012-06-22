load D:\status4.txt;         %  read data into status
step = status4(:,1);     % Steps
gyrosDOT = status4(:,2);    %  first column into gyrosDOT value
accel = status4(:,3);    %  second column into accel value (Already in Euler Angle)
% the angles calculated by gyrosDOT 
gyrosAngle = gyrosDOT*0.01;  % 0.01 is the delta t
gyros = cumsum(gyrosAngle);   
% Complementary Filter
k = 0.98;  % Time Coefficient
numOfSample = length(gyrosDOT); 
ComplementedEuler = zeros(1,numOfSample); % create the array
ComplementedEuler(1) = k*(0 + gyrosDOT(1)*0.01) + (1-k)*accel(1); % calculate the first Euler value
for i = 2:numOfSample
    ComplementedEuler(i) = k*(ComplementedEuler(i-1) + gyrosDOT(i)*0.01) + (1-k)*accel(i);  % complementary filter
end
plot(step,accel,'r-',step,gyros,'g-', step, ComplementedEuler,'b-');     %  plot 
xlabel('sensor');              %  add axis labels and plot title
ylabel('angles');
title('Test');
