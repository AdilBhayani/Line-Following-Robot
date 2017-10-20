%% Function descriptions
%% To view a map, given a map file

viewmap('map_1.txt',0); % shows walls
viewmap('map_1.txt',1); % shows track

%or else

[m]=map_convert('current_map.txt');
plotmap(m);
%Here   'm' is the map file returned as a matrix


% Your simulations will use this structure
[m,v,s]=dfs('current_map.txt',[2,2],[1,1]);
%Here   'm' is the map file returned as a matrix
%       'v' is a matrix that shows which cells have been visited, '0' means
%       visited, '1' means not visited
%       's' is the vector of steps to reach the target,
%       [startloc] is a vector i.e. [2,2]
%       [targetloc] is also a vector ie [4,18]

%To view the path determined above use 
figure();
set(gcf,'numbertitle','off','name','Final path')
plotmap(m,s);

disp(s - 1);
disp(size(s,1));%Total number of steps taken
