clear;clc

e_init = 1;
s_init = 10;
es_init = 0;
p_init = 0;
K1 = 100;
K2 = 600;
K3 = 150;
N = 500;
h = 0.001;

y = [e_init, s_init, es_init, p_init]';
y_plot = [];
y_plot = [y_plot, y];

for i=1:N
    k1 = h*[-K1*y(1)*y(2)+(K2+K3)*y(3); -K1*y(1)*y(2)+K2*y(3); K1*y(1)*y(2)-(K2+K3)*y(3); K1*y(1)*y(2)-K2*y(3)];
    y2 = y + 0.5*k1;
    k2 = h*[-K1*y2(1)*y2(2)+(K2+K3)*y2(3); -K1*y2(1)*y2(2)+K2*y2(3); K1*y2(1)*y2(2)-(K2+K3)*y2(3); K1*y2(1)*y2(2)-K2*y2(3)];
    y3 = y + 0.5*k2;
    k3 = h*[-K1*y3(1)*y3(2)+(K2+K3)*y3(3); -K1*y3(1)*y3(2)+K2*y3(3); K1*y3(1)*y3(2)-(K2+K3)*y3(3); K1*y3(1)*y3(2)-K2*y3(3)];
    y4 = y + k3;
    k4 = h*[-K1*y4(1)*y4(2)+(K2+K3)*y4(3); -K1*y4(1)*y4(2)+K2*y4(3); K1*y4(1)*y4(2)-(K2+K3)*y4(3); K1*y4(1)*y4(2)-K2*y4(3)];
    y = y + 1/6*(k1 + 2*k2 + 2*k3 + k4);
    y_plot = [y_plot, y];
end

plot([1:N+1]*h, y_plot);
hold on;



