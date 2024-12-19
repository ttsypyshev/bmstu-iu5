q0=1;
q1=-0.5;

[t,x]=ode45('ode_lab_sint',[0 10],[q0 q1]);

plot(t,x(:,1),'b-',t,x(:,2),'g-',t, sin(t),'LineWidth',2)

legend('x_1(t)', 'x_2(t)', 'sin(t)')
grid on
xlabel('t, c')
ylabel('x_i(t)')
title('Реакция системы на входной сигнал y=sin(t) при начальных условиях [1, 0.5, 0]')
