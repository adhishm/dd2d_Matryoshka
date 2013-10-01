function numbers = parseLineData (lineData, delimiter)
%% numbers = parseLineData (lineData, delimiter)
%  This function takes line of characters that contains numbers (as text)
%  separated by a delimiter. The function separates out these numbers and
%  returns them in the vector numbers.

    %% Find number of characters
    nChar = size(lineData,2);   % Number of columns
    
    %% Pre-allocate numbers for speed
    numbers = zeros(1,nChar);   % There cannot be more numbers than there are characters
    
    %% Browse through characters till the end of the line is reached
    charCount = 1;
    dataCount = 0;
    while (charCount <= nChar)
        %% Find the start and end point of each data
        startPosition = charCount;
        while (lineData(charCount) ~= delimiter)
            charCount = charCount + 1;
        end
        endPosition = charCount - 1;    % The position before the delimiter
        
        %% Separate the data, convert to number, insert into vector
        data = lineData(startPosition:endPosition);
        dataCount = dataCount + 1;
        numbers(1,dataCount) = str2double(data);
        clear data;
        
        charCount = charCount + 1;  % Increment charCount to move beyond the delimiter
    end
    
    %% Remove padding zeros
    numbers = numbers(1,1:dataCount);

end
