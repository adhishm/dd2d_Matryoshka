function plotSlipSystem (filename, delimiter)
%% plotSlipSystem (filename, delimiter)
%  This function simply plots the positions (on the xy-plane) of various
%  defects present in a slip system as a function of time (on the z-axis).
%  The data is provided by the file whose name is given in the variable
%  filename.
%  The data in the file is presented in a row for each instant in time. The
%  first element of each row gives us the time and the remaining columns give us the
%  (x y) co-ordinates. The columns are separated by the character given by the
%  argument delimiter.
%  Since the function simply plots as crosses the entities present at a
%  given time and does not try to connect the crosses across time, the
%  order in which the entities appear is irrelevant.

    %% Open the file
    fid = fopen (filename(:));
    
    if (fid == -1)
        % Could not open the file
        disp ('Unable to open the file!');
        return
    end
    
    %% Initialize the figure
    figure;
    hold on;
    
    %% Read the file one line at a time
    oneline = fgetl(fid);
    while ischar(oneline)
        %% Parse line data into numbers
        data = parseLineData(oneline, delimiter);
        
        %% Separate data
        nObjects = (size(data,2)-1)/2;	% The first element is the time and there are 2 data elements for each object
        positions = zeros(nObjects, 3);
        positions(:,3) = data(1) * 1000.0; % Scale to ms
        positions(:,1:2) = (reshape(data(2:end),2,[]))';
        positions(:,1:2) = positions(:,1:2) * 1.0e06;   % Scale positions to microns
        plot3 (positions(:,1), positions(:,2), positions(:,3), 'b.');
        oneline = fgetl(fid);
    end
    
    %% Close the file
    fclose (fid);
    
    %% Release the figure
    hold off;
    zlabel('Time (ms)');
    ylabel('y (µm)');
    xlabel('x (µm)');
    view (45,45);
    
end
