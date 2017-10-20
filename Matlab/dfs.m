%% This is a shell that you will have to follow strictly. 
% You will use the plotmap() and viewmap() to display the outcome of your algorithm.

% Load sample_data_map_8, three variables will be created in your workspace. These were created as a 
% result of [m,v,s]=dfs('map_8.txt',[14,1],[1,18]);
% The solution can be viewed using 
% plotmap(m,s) 

% write your own function for the DFS algorithm.
function [retmap,retvisited,retsteps] = dfs( mapfile,startlocation,targetlocation)
retmap = map_convert(mapfile);
retvisited = ones(size(retmap));
retsteps = [startlocation(1),startlocation(2)];

poppingArray = [startlocation(1),startlocation(2)];
currentLocation = startlocation;
retvisited(currentLocation(1), currentLocation(2)) = 0;

while size(poppingArray,1) > 0 && (currentLocation(1) ~= targetlocation(1) || currentLocation(2) ~= targetlocation(2))
   if checkIntersection(retmap, retvisited, currentLocation) > 1
       poppingArray(end+1,:) = currentLocation;
   end
   if currentLocation(1) > 1 && retmap(currentLocation(1)-1,currentLocation(2)) == 0 && retvisited(currentLocation(1)-1, currentLocation(2)) == 1
       currentLocation(1) = currentLocation(1) - 1;
   elseif currentLocation(2) < size(retmap,2) && retmap(currentLocation(1), currentLocation(2)+1) == 0 && retvisited(currentLocation(1), currentLocation(2)+1) == 1
       currentLocation(2) = currentLocation(2) + 1;
   elseif currentLocation(1) < size(retmap,1) && retmap(currentLocation(1)+1, currentLocation(2)) == 0 && retvisited(currentLocation(1)+1, currentLocation(2)) == 1
       currentLocation(1) = currentLocation(1) + 1;
   elseif currentLocation(2) > 1 && retmap(currentLocation(1), currentLocation(2)-1) == 0 && retvisited(currentLocation(1), currentLocation(2)-1) == 1
       currentLocation(2) = currentLocation(2) - 1;
   else
        i = 1;
        while i <= size(poppingArray,1)
            if size(poppingArray,1) >= i
                currentLocation = poppingArray(i,:);
                if  checkIntersection(retmap, retvisited, currentLocation) < 1
                    poppingArray(i,:) = [];
                    if i > 1
                       i = i - 1; 
                    end
                end
            end
            i = i + 1;
        end
       if size(poppingArray,1) > 0
          currentLocation = poppingArray(size(poppingArray,1),:);
       end
       stepsIndex = size(retsteps,1);
       while size(poppingArray,1) > 0 && (currentLocation(1) ~= poppingArray(size(poppingArray,1),1) || currentLocation(2) ~= poppingArray(size(poppingArray,1),2))
           currentLocation = retsteps(stepsIndex,:);
           if stepsIndex > 0
              stepsIndex = stepsIndex - 1;
           else
               break
           end
       end
   end
   if retsteps(end,1) ~= currentLocation(1) || retsteps(end,2) ~= currentLocation(2)
       retsteps(end+1,:) = currentLocation;
   end
   retvisited(currentLocation(1), currentLocation(2)) = 0;
   if size(retsteps,1) > 1
        plotmap(retmap,retsteps);
        set(gcf,'numbertitle','off','name','Current Search Path')
        pause(0.1); %Wait 0.1 seconds before continuing to allow time to visualise
   end
end

end


function count = checkIntersection(retmap,retvisited, currentLocation)
count = 0;
if currentLocation(1) > 1 && retmap(currentLocation(1)-1,currentLocation(2)) == 0 && retvisited(currentLocation(1)-1, currentLocation(2)) == 1
    count = count + 1;
end
if currentLocation(2) < size(retmap,2) && retmap(currentLocation(1), currentLocation(2)+1) == 0 && retvisited(currentLocation(1), currentLocation(2)+1) == 1
    count = count + 1;
end
if currentLocation(1) < size(retmap,1) && retmap(currentLocation(1)+1, currentLocation(2)) == 0 && retvisited(currentLocation(1)+1, currentLocation(2)) == 1
    count = count + 1;
end
if currentLocation(2) > 1 && retmap(currentLocation(1), currentLocation(2)-1) == 0 && retvisited(currentLocation(1), currentLocation(2)-1) == 1
    count = count + 1;
end
end

function placestep(position,i)
% This function will plot a insert yellow rectangle and also print a number in this rectangle. Use with plotmap/viewmap. 
position = [16-position(1) position(2)];
position=[position(2)+0.1 position(1)+0.1];
rectangle('Position',[position,0.8,0.8],'FaceColor','y');
c=sprintf('%d',i);
text(position(1)+0.2,position(2)+0.2,c,'FontSize',10);
end
