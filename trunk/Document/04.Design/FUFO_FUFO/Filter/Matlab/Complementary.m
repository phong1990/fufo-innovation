load D:\statusyphi.txt;         %  read data into status
step = statusyphi(:,1);     % Steps
gyrosDOT = statusyphi(:,3);    %  first column into gyrosDOT value
accel = statusyphi(:,2);    %  second column into accel value (Already in Euler Angle)

% the angles calculated by gyrosDOT 
gyrosAngle = gyrosDOT*0.01;  % 0.01 is the delta t
gyros = cumsum(gyrosAngle);   

% Complementary Filter
k = 0.99;  % Time Coefficient
numOfSample = length(gyrosDOT); 
ComplementaryEuler = zeros(1,numOfSample); % create the array
ComplementaryEuler(1) = k*(0 + gyrosDOT(1)*0.01) + (1-k)*accel(1); % calculate the first Euler value
for i = 2:numOfSample
    ComplementaryEuler(i) = k*(ComplementaryEuler(i-1) + gyrosDOT(i)*0.01) + (1-k)*accel(i);  % complementary filter
end

%low pass filter
LowpassEuler = zeros(1,numOfSample); % Create the array
LowpassEuler(1) = k*0 + (1-k)*accel(1); % calculate the first Euler value
for i = 2:numOfSample
    LowpassEuler(i) = k*LowpassEuler(i-1) + (1-k)*accel(i);
end

%high pass filter
HighpassEuler = zeros(1,numOfSample); % Create the array
HighpassEuler(1) = k*(0 + gyros(i)*0.01); % calculate the first Euler value
for i = 2:numOfSample
    % ? * y[i-1] + ? * (x[i] - x[i-1]) = ? * (y[i-1] + (x[i] - x[i-1]))
    HighpassEuler(i) = k*HighpassEuler(i-1) + k*(gyros(i)-gyros(i-1)); 
end



plot(step,accel,'r-',step,gyros,'g-', step, ComplementaryEuler,'b-',step, LowpassEuler,'c-',step, HighpassEuler,'m-');     %  plot 
xlabel('sensor');              %  add axis labels and plot title
ylabel('angles');
title('Test');
h = legend('accel','gyros','Complementary','Lowpass','Highpass',3);
set(h,'Interpreter','none');