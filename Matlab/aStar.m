%A star implementation which should work when called from the README.m
%file.

function [retMap,retVisited,retSteps] = aStar( mapFile,startLocation,target)
    retMap = map_convert(mapFile);
    retVisited = ones(size(retMap));
    openList = [startLocation(1),startLocation(2)];
    closedList = [];
    retSteps = [];
    fValues = zeros(size(retMap));
    gValues = zeros(size(retMap));
    hValues = zeros(size(retMap));
    parents = zeros([size(retMap),2]);
    
    hValues(startLocation(1),startLocation(2)) = abs(target(1)-startLocation(1)) * 10 + abs(target(2)-startLocation(2)) * 10;
    fValues(startLocation(1),startLocation(2)) = abs(target(1)-startLocation(1)) * 10 + abs(target(2)-startLocation(2)) * 10;
    currentPosition = startLocation;
    while (size(openList,1) > 0)
        lowestFSquareIndex = findLowestFSquare(fValues,openList, currentPosition);
        closedList(end+1,:) = openList(lowestFSquareIndex,:);
        currentPosition = openList(lowestFSquareIndex,:);
        squareToCheck = closedList(end,:);
        retVisited(openList(lowestFSquareIndex,1),openList(lowestFSquareIndex,2)) = 0;
        openList(lowestFSquareIndex,:) = [];
             
        [inClosedList,~] = inList(squareToCheck(1)-1,squareToCheck(2), closedList);
        if squareToCheck(1) > 1 && retMap(squareToCheck(1)-1,squareToCheck(2)) == 0 && ~inClosedList;
            [inOpenList, index] = inList(squareToCheck(1) - 1,squareToCheck(2),openList);
            if ~inOpenList
            [openList,fValues,gValues,hValues, parents] = addSquare(squareToCheck(1), squareToCheck(2), squareToCheck(1)-1,squareToCheck(2),openList, fValues, gValues, hValues, parents, target);
            else
                if gValues(squareToCheck(1)-1,squareToCheck(2)) > 10 + gValues(squareToCheck(1),squareToCheck(2))
                    [openList,fValues,gValues,hValues, parents] = updateSquare(index, squareToCheck(1), squareToCheck(2), squareToCheck(1)-1,squareToCheck(2),openList, fValues, gValues, hValues, parents, target);
                end
            end
        end
        
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
        
        if size(closedList,1) > 1
            plotmap(retMap,closedList);
            set(gcf,'numbertitle','off','name','Current Search Path')
            pause(0.1);
        end
        
        if closedList(end,1) == target(1) && closedList(end,2) == target(2)
            currentSquare = target;
            while currentSquare(1) ~= startLocation(1) || currentSquare(2) ~= startLocation(2)
                retSteps(end+1,:) = currentSquare;
                tempX = parents(currentSquare(1),currentSquare(2),1);
                tempY = parents(currentSquare(1),currentSquare(2),2);
                currentSquare(1) = tempX;
                currentSquare(2) = tempY;
            end
            retSteps(end+1,:) = startLocation;
            retSteps = flipud(retSteps);
            break
        end
    end

end


%Helper function returns the index of the lowest square in openList
function [lowestFSquareIndex] = findLowestFSquare(fValues, openList,currentPosition)
    lowestFSquareValue = fValues(openList(1,1),openList(1,2));
    lowestFSquareIndex = 1;
    for i = 1:size(openList,1)
        if fValues(openList(i,1),openList(i,2)) <= (lowestFSquareValue + 5 * abs(currentPosition(1) - openList(i,1)) + 5 * abs(currentPosition(2) - openList(i,2)))
            lowestFSquareValue = fValues(openList(i,1),openList(i,2));
            lowestFSquareIndex = i;
        end
    end

end


%Returns a boolean indicating whether the square given is in the provided
%list.
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
    gValues(x,y) = gValues(parentX, parentY) + 5;
    hValues(x,y) = abs(target(1)-x) * 10 + abs(target(2)-y) * 10;
    fValues(x,y) = gValues(x,y) + hValues(x,y);
end

function [openList,fValues,gValues,hValues, parents] = updateSquare(index, parentX, parentY, x, y, openList, fValues, gValues, hValues, parents, target)
    openList(index,:) = [x,y];
    parents(x,y,1) = parentX;
    parents(x,y,2) = parentY;
    gValues(x,y) = gValues(parentX, parentY) + 5;
    hValues(x,y) = abs(target(1)-x) * 10 + abs(target(2)-y) * 10;
    fValues(x,y) = gValues(x,y) + hValues(x,y);
end
