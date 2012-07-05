load D:\statusPI.txt;         %  read data into status
step = statusPI(:,1);      % Steps
Theta = statusPI(:,2);    %  first column into Theta values
Pwm1 = statusPI(:,3);     %  second column into PWM of motor 1 value
Pwm3 = statusPI(:,4);     %  Third column into PWM of motor 2 value
                            %  in case of Harmonic Oscillator, the plot of
                            %  PWM1 will be a sine/cosine type plot and PWM
                            %  will be an inverse image of PWM3
                            %  PWM1 and PWM3 will have an equal in
                            %  frequency.
% Plot          
plot(step,Theta,'r-',step,Pwm1,'g-', step, Pwm3,'b-');     %  plot 
xlabel('time');              %  add axis labels and plot title
ylabel('Theta/PWM');
title('Test PI');
h = legend('Theta','PWM1','PWM3',3);
set(h,'Interpreter','none');