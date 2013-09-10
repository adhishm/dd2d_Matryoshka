function plotSlipPlane (filename, delimiter)
%% plotDislocations (filename, delimiter)
%  This function simply plots the positions (on the y-axis) of various
%  defects present on a slip plane as a function of time (on the x-axis).
%  The data is provided by the file whose name is given in the variable
%  filename.
%  The data in the file is presented in a row for each instant in time. The
%  first column gives us the time and the remaining columns give us the
%  positions. The columns are separated by the character given by the
%  argument delimiter.
%  Since the function simply plots as crosses the entities present at a
%  given time and does not try to connect the crosses across time, the
%  order in which the entities appear is irrelevant.

    %% Initialize the figure
    figure;
    hold on;

    %% Open the file
    fid = fopen (filename(:));
    
    %% Read the file one line at a time
    oneline = fgetl(fid);
    while ischar(oneline)
        %% Parse line data into numbers
        data = parseLineData(oneline, delimiter);
        
        %% Separate data
        timeInstant = data(1,1);        % The first data is the time
        nObjects = size(data,2) - 1;    % All the others are object positions
        positions = data(1,2:end);
        for i=1:nObjects
            plot (timeInstant, positions(1,i), 'bx');
        end
    end
    
    %% Close the file
    fclose (fid);
    
    %% Release the figure
    hold off;
    xlabel('Time (s)');
    ylabel('Positions (m)');
    
end
