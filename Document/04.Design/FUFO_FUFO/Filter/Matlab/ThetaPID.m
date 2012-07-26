load D:\statusPIDtheta.txt;         %  read data into status
Theta = statusPIDtheta(:,2);       %  Kcr
kd = statusPIDtheta(:,3);       %  Kcr

numOfSample = length(Theta); 
step = zeros(1,numOfSample); % create the steps array
step(1) = 1;
for i = 2:numOfSample
    step(i) = step(i-1) + 1;
end

% Plot          
plot(step,Theta*1000,'r-',step,kd*100,'g-');     %  plot 
xlabel('time');              %  add axis labels and plot title
ylabel('Theta');
title('Test PID');
h = legend('Theta','Setpoint',3);
set(h,'Interpreter','none');