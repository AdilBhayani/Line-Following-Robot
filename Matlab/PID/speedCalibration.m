%PID calibration program
%First Attempt:
fileID = fopen('Attempt1.txt','r');
[values,count] = fscanf(fileID, ['M1: ' '%d' ',M2: ' '%d' '\n']);
A = values(1:2:end);
B = values (2:2:end);
x = 1:count/2;
fclose(fileID);
disp(values);
figure();
plot(x,A, x, B);

Speed = A-B;
theSum = sum(Speed);

%{
fileID = fopen('Attempt2.txt','r');
[values,count] = fscanf(fileID, ['M1: ' '%d' ',M2: ' '%d' '\n']);
A = values(1:2:end);
B = values (2:2:end);
x = 1:count/2;
fclose(fileID);
disp(values);
figure();
plot(x,A, x, B);

fileID = fopen('Attempt3.txt','r');
[values,count] = fscanf(fileID, ['M1: ' '%d' ',M2: ' '%d' '\n']);
A = values(1:2:end);
B = values (2:2:end);
x = 1:count/2;
fclose(fileID);
disp(values);
figure();
plot(x,A, x, B);
%}
