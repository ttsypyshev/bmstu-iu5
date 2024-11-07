	function [dx]=ode_lab_1(t,x)
	a0=1;
	a1=0.5;
	a2=0.5;
	b=2;
	y=1;
    
	dx=zeros(2,1);
	dx(1)=x(2);
	dx(2)=(b*y-a0*x(1)-a1*x(2))/a2;
	end
