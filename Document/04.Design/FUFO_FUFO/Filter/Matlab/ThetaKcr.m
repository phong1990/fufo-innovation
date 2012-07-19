load D:\statusKcr.txt;         %  read data into status
Theta = statusKcr(:,1);    %  first column into Theta values
Kcr = statusKcr(:,2);       %  Kcr

numOfSample = length(Theta); 
step = zeros(1,numOfSample); % create the steps array
step(1) = 1;
for i = 2:numOfSample
    step(i) = step(i-1) + 1;
end

% Plot          
plot(step,Theta*1000,'r-',step,Kcr*100,'g-',step,step*0,'b-',step,step*0+20,'b-');     %  plot 
xlabel('time');              %  add axis labels and plot title
ylabel('Theta/Kcr');
title('Test Kcr');
h = legend('Theta','Kcr','SetPoint0','setPoint20',3);
set(h,'Interpreter','none');