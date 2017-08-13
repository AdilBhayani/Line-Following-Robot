%A star implementation which should work when called from the README.m
%file.
%Implemented after reading
%"https://www.raywenderlich.com/4946/introduction-to-a-pathfinding".

function [retMap,retVisited,retSteps] = aStar( mapFile,startLocation,target)
    retMap = map_convert(mapFile); %Call given map_convert function to get map
    retVisited = ones(size(retMap)); %Initially assume all blocks are unvisited
    openList = [startLocation(1),startLocation(2)]; %Open list keeps track of blocks which need to be discovered
    closedList = []; %No blocks have been explored yet
    retSteps = []; %No steps have been taken yet
    fValues = zeros(size(retMap)); %An array of values of f which is how far the block is estimated to be from end
    gValues = zeros(size(retMap)); %Will be used for movement costs from start point to all index locations
    hValues = zeros(size(retMap)); %Will be used for estimated movement costs
    parents = zeros([size(retMap),2]); %Will be used to keep track of parents of each block to traverse path back once completed
    
    %Calculating h and f values for the start location
    hValues(startLocation(1),startLocation(2)) = abs(target(1)-startLocation(1)) * 10 + abs(target(2)-startLocation(2)) * 10;
    fValues(startLocation(1),startLocation(2)) = abs(target(1)-startLocation(1)) * 10 + abs(target(2)-startLocation(2)) * 10;

    while (size(openList,1) > 0) %Keep going while there is still a block to be discovered
        lowestFSquareIndex = findLowestFSquare(fValues,openList); %Call helper function to get the block with lowest f value. (Assumed to be most likely to lead to finish)
        closedList(end+1,:) = openList(lowestFSquareIndex,:); %Close off the current block
        squareToCheck = closedList(end,:); %Keep a copy to use for checking
        retVisited(openList(lowestFSquareIndex,1),openList(lowestFSquareIndex,2)) = 0; %Mark the block as visited
        openList(lowestFSquareIndex,:) = []; %Removing block from openList
        
        %For block to the top of current block being checked
        [inClosedList,~] = inList(squareToCheck(1)-1,squareToCheck(2), closedList); %Call helper function to check if the block to the top of current block is already closed
        if squareToCheck(1) > 1 && retMap(squareToCheck(1)-1,squareToCheck(2)) == 0 && ~inClosedList; %If the block isnt out of bounds and not a wall and it is not already closed
            [inOpenList, index] = inList(squareToCheck(1) - 1,squareToCheck(2),openList); %Call helper function to see if it is an open block
            if ~inOpenList %If it isnt open then add it to the open list using helper function
            [openList,fValues,gValues,hValues, parents] = addSquare(squareToCheck(1), squareToCheck(2), squareToCheck(1)-1,squareToCheck(2),openList, fValues, gValues, hValues, parents, target);
            else %If it is already in the open list
                if gValues(squareToCheck(1)-1,squareToCheck(2)) > 10 + gValues(squareToCheck(1),squareToCheck(2)) %Check if we have found a shorter path to the block, if so, update values by calling helper function
                    [openList,fValues,gValues,hValues, parents] = updateSquare(index, squareToCheck(1), squareToCheck(2), squareToCheck(1)-1,squareToCheck(2),openList, fValues, gValues, hValues, parents, target);
                end
            end
        end
        
        %Repeat for block to the right
        [inClosedList,~] = inList(squareToCheck(1),squareToCheck(2)+1, closedList);
        if squareToCheck(2) < size(retMap,2) && retMap(squareToCheck(1),squareToCheck(2)+1) == 0 && ~inClosedList
            [inOpenList,index] = inList(squareToCheck(1),squareToCheck(2)+1,openList);
            if ~inOpenList
                [openList,fValues,gValues,hValues, parents] = addSquare(squareToCheck(1), squareToCheck(2), squareToCheck(1),squareToCheck(2)+1,openList, fValues, gValues, hValues, parents, target);
            else
                if gValues(squareToCheck(1),squareToCheck(2)+1) > 10 + gValues(squareToCheck(1),squareToCheck(2))
                    [openList,fValues,gValues,hValues, parents] = updateSquare(index, squareToCheck(1), squareToCheck(2), squareToCheck(1),squareToCheck(2)+1,openList, fValues, gValues, hValues, parents, target);
                end
            end
        end
        
        %Repeat for block to the bottom
        [inClosedList,~] = inList(squareToCheck(1)+1,squareToCheck(2), closedList);
        if squareToCheck(1) < size(retMap,1) && retMap(squareToCheck(1)+1,squareToCheck(2)) == 0 && ~inClosedList
            [inOpenList,index] = inList(squareToCheck(1)+1,squareToCheck(2),openList);
            if ~inOpenList
                [openList,fValues,gValues,hValues, parents] = addSquare(squareToCheck(1), squareToCheck(2), squareToCheck(1)+1,squareToCheck(2),openList, fValues, gValues, hValues, parents, target);
            else
                if gValues(squareToCheck(1)+1,squareToCheck(2)) > 10 + gValues(squareToCheck(1),squareToCheck(2))
                    [openList,fValues,gValues,hValues, parents] = updateSquare(index, squareToCheck(1), squareToCheck(2), squareToCheck(1)+1,squareToCheck(2),openList, fValues, gValues, hValues, parents, target);
                end
            end
        end
        
        %Repeat for block to the left
        [inClosedList,~] = inList(squareToCheck(1),squareToCheck(2)-1, closedList);
        if squareToCheck(2) > 1 && retMap(squareToCheck(1),squareToCheck(2)-1) == 0 && ~inClosedList
            [inOpenList,index] = inList(squareToCheck(1),squareToCheck(2)-1,openList);
            if ~inOpenList
                [openList,fValues,gValues,hValues, parents] = addSquare(squareToCheck(1), squareToCheck(2), squareToCheck(1),squareToCheck(2)-1,openList, fValues, gValues, hValues, parents, target);
            else
                if gValues(squareToCheck(1),squareToCheck(2)-1) > 10 + gValues(squareToCheck(1),squareToCheck(2))
                    [openList,fValues,gValues,hValues, parents] = updateSquare(index, squareToCheck(1), squareToCheck(2), squareToCheck(1),squareToCheck(2)-1,openList, fValues, gValues, hValues, parents, target);
                end
            end
        end
        
        if size(closedList,1) > 1 %Start graphing the map once we have more than one value in closedList
            plotmap(retMap,closedList);
            set(gcf,'numbertitle','off','name','Current Search Path')
            pause(0.1); %Wait 0.1 seconds before continuing to allow time to visualise
        end
        
        if closedList(end,1) == target(1) && closedList(end,2) == target(2) %If we have just closed off a block which has coordinates of target block
            currentSquare = target;
            while currentSquare(1) ~= startLocation(1) || currentSquare(2) ~= startLocation(2) %Loop back over the linked list till we get to the start to get shortest path
                retSteps(end+1,:) = currentSquare;
                %Traversing back linked list from finish
                tempX = parents(currentSquare(1),currentSquare(2),1);
                tempY = parents(currentSquare(1),currentSquare(2),2);
                currentSquare(1) = tempX;
                currentSquare(2) = tempY;
            end
            retSteps(end+1,:) = startLocation; %Add the start location to the steps
            retSteps = flipud(retSteps); %Reverse the path so it appears as if we started from start and traversed to finish
            break
        end
    end

end


%Helper function returns the index of the lowest square in openList
function [lowestFSquareIndex] = findLowestFSquare(fValues, openList)
    lowestFSquareValue = fValues(openList(1,1),openList(1,2));
    lowestFSquareIndex = 1;
    for i = 1:size(openList,1)
        if fValues(openList(i,1),openList(i,2)) <= lowestFSquareValue
            lowestFSquareValue = fValues(openList(i,1),openList(i,2));
            lowestFSquareIndex = i;
        end
    end

end


%Returns a boolean indicating whether the square given is in the provided
%list
function [present,i] = inList(xPos,yPos,list)
    present = false;
    for i = 1:size(list,1)
        if list(i,1) == xPos && list(i,2) == yPos
            present = true;
            break;
        end
    end
end

%Adds a newly discovered square
function [openList,fValues,gValues,hValues, parents] = addSquare(parentX, parentY, x, y, openList, fValues, gValues, hValues, parents, target)
    openList(end+1,:) = [x,y];
    parents(x,y,1) = parentX;
    parents(x,y,2) = parentY;
    gValues(x,y) = gValues(parentX, parentY) + 10;
    hValues(x,y) = abs(target(1)-x) * 10 + abs(target(2)-y) * 10;
    fValues(x,y) = gValues(x,y) + hValues(x,y);
end

%Updates a existing square in the openList
function [openList,fValues,gValues,hValues, parents] = updateSquare(index, parentX, parentY, x, y, openList, fValues, gValues, hValues, parents, target)
    openList(index,:) = [x,y];
    parents(x,y,1) = parentX;
    parents(x,y,2) = parentY;
    gValues(x,y) = gValues(parentX, parentY) + 10;
    hValues(x,y) = abs(target(1)-x) * 10 + abs(target(2)-y) * 10;
    fValues(x,y) = gValues(x,y) + hValues(x,y);
end
