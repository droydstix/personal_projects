clc; clear all; close all
%a=input('input the length of link 2, a = '); % or input it manually  
a=sqrt((7.914)^2+(11.991)^2); 
%b=input('input the length of link 3, b = '); % or input it manually  
b=sqrt((22.899-7.914)^2+(26.236-11.991)^2);
%c=input('input the length of link 4, c = '); % or input it manually  
c=sqrt((40-22.899)^2+(-26.236)^2);
%d=input('input the length ground, d = '); % or input it manually  
d=40;
ternlinkx=22.899+0.981;
ternlinky=26.597-11.991;
%%
for theta=0:1:360         
    %a_X(theta+1)=a*cos(deg2rad(theta));     
    %or     
    a_X(theta+1)=a*cosd(theta);         
    %a_Y(theta+1)=a*sin(deg2rad(theta));     
    %or     
    a_Y(theta+1)=a*sind(theta);             
    S=(a^2-b^2+c^2-d^2)/(2*(a_X(theta+1)-d));
    R=((d-S)^2)-c^2;

    P=1+(a_Y(theta+1))^2/((a_X(theta+1)-d)^2);     
    Q=(2*a_Y(theta+1)*(d-S))/(a_X(theta+1)-d);    
    if(Q^2-4*P*R)>=0        
        b_Y_1(theta+1)=(-Q+sqrt(Q^2-4*P*R))/(2*P);        
        b_Y_2(theta+1)=(-Q-sqrt(Q^2-4*P*R))/(2*P);
        b_Y_3(theta+1)=ternlinky+(-Q-sqrt(Q^2-4*P*R))/(2*P);
        a_X_2(theta+1)=ternlinkx+a*cosd(theta);
        b_X_1(theta+1)=S-(2*a_Y(theta+1)*b_Y_1(theta+1))/...
            (2*(a_X(theta+1)-d));        
        b_X_2(theta+1)=S-(2*a_Y(theta+1)*b_Y_2(theta+1))/...            
            (2*(a_X(theta+1)-d));  

        
         
    end
end


figure; 
subplot(1,2,1)
plot(a_X,a_Y,'*')
title('The position of tip of the link AB')
axis equal 
subplot(1,2,2)
plot(b_X_1,b_Y_1,'ko')
hold on 
subplot(1,2,2)
plot(b_X_2,b_Y_2,'ko')
title('The position of tip of the link BD')
axis equal
figure;
subplot(1,2,1)
plot(a_X_2,b_Y_3,'*')
title('The position of tip of the link C')
axis equal
filename= 'output2.xlsx';
% write dta to excell % xlswrite(filename,a_X,a_Y,b_X_1,b_Y_1,b_X_2,b_Y_2,'a_X','a_Y','b_X,1',... %     'b_Y,1','b_X,2','b_Y,2');
name = {'a_X';'a_Y';'b_X,1';'b_Y,1';'b_X,2';'b_Y,2';'a_X,2';'b_Y,3'}; 
xlswrite(filename,name',1,'A1');
out_table=[a_X' a_Y' b_X_1' b_Y_1' b_X_2' b_Y_2' a_X_2' b_Y_3']; 
xlswrite(filename,out_table,1,'A2');
out_table=table(a_X',a_Y',b_X_1',b_Y_1',b_X_2',b_Y_2',a_X_2',b_Y_3'); 
writetable(out_table,filename,'FileType','spreadsheet','WriteRowNames',1)
%plot(a_X,a_Y) %- this is to plot the initial input link

%plot(b_X_1,b_Y_1) - this is to plot one set of valid position of B %plot(b_X_2,b_Y_2) - this is to plot another set of valid position of B %the choice between the two valid positions of B depends on the initial %position of B, if the initial position of B is closer to the original %position