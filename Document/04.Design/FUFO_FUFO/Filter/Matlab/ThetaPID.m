load D:\statusPIDtheta.txt;         %  read data into status
Phi = statusPIDtheta(:,1);       %  
Theta = statusPIDtheta(:,2);       %  
PWM2 = statusPIDtheta(:,3);       %  

numOfSample = length(Theta); 
step = zeros(1,numOfSample); % create the steps array
step(1) = 1;
for i = 2:numOfSample
    step(i) = step(i-1) + 1;
end

% Plot          
plot(step,Phi*1000,'r-',step,PWM2,'g-');     %  plot 
xlabel('time');              %  add axis labels and plot title
ylabel('Phi');
title('Test PID');
h = legend('Phi','PWM',3);
set(h,'Interpreter','none');