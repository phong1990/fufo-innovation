load D:\statusKcr.txt;         %  read data into status
step = statusKcr(:,1);      % Steps
Theta = statusKcr(:,2);    %  first column into Theta values
Pwm1 = statusKcr(:,3);     %  second column into PWM of motor 1 value
Pwm3 = statusKcr(:,4);     %  Third column into PWM of motor 2 value
                            %  in case of Harmonic Oscillator, the plot of
                            %  PWM1 will be a sine/cosine type plot and PWM
                            %  will be an inverse image of PWM3
                            %  PWM1 and PWM3 will have an equal in
                            %  frequency.
Kcr = statusKcr(:,5);       %  Kcr value
% Plot          
plot(step,Theta,'r-',step,Pwm1,'g-', step, Pwm3,'b-',step,Kcr,'m+');     %  plot 
xlabel('time');              %  add axis labels and plot title
ylabel('Theta/PWM/Kcr');
title('Test Kcr');
h = legend('Theta','PWM1','PWM3','Kcr',3);
set(h,'Interpreter','none');