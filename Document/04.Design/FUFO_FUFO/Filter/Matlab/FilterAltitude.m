load E:\FUFO_firmware\statusAltitude.txt;         %  read data into status
baro = statusAltitude(:,1);    %  first column into baro values
acc = statusAltitude(:,2);
final = statusAltitude(:,3);

numOfSample = length(baro); 
step = zeros(1,numOfSample); % create the steps array
step(1) = 1;
for i = 2:numOfSample
    step(i) = step(i-1) + 1;
end
k = 0.98;
kH = 0.02;
%high pass filter
HighpassEuler = zeros(1,numOfSample); % Create the array
HighpassEuler(1) = kH*(0 + acc(1));
for i = 2:numOfSample
    % ? * y[i-1] + ? * (x[i] - x[i-1]) = ? * (y[i-1] + (x[i] - x[i-1]))
    HighpassEuler(i) = kH*HighpassEuler(i-1) + kH*(acc(i)-acc(i-1)); 
end

%complementary filter
ComplementaryEuler = zeros(1,numOfSample); % create the array
ComplementaryEuler(1) = k*(0 + HighpassEuler(1)) + (1-k)*baro(1);
for i = 2:numOfSample
    ComplementaryEuler(i) = k*(ComplementaryEuler(i-1) + HighpassEuler(i)-HighpassEuler(i-1)) + (1-k)*baro(i);  % complementary filter
end
% Plot          
plot(step,baro,'r-', step, final,'g-',step, ComplementaryEuler,'b-', step, 0.8, 'k-', step, step*0, 'k-');     %  plot 
xlabel('time');              %  add axis labels and plot title
ylabel('meter');
title('Test Altitude');
h = legend('Baro','final',' ComplementaryEuler', 3);
set(h,'Interpreter','none');