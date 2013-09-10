function plotSlipPlane (filename)
%% plotDislocations (filename)
%  This function simply plots the positions (on the y-axis) of various
%  defects present on a slip plane as a function of time (on the x-axis).
%  The data is provided by the file whose name is given in the variable
%  filename.
%  The data in the file is presented in a row for each instant in time. The
%  first column gives us the time and the remaining columns give us the
%  positions.
%  Since the function simply plots as crosses the entities present at a
%  given time and does not try to connect the crosses across time, the
%  order in which the entities appear is irrelevant.

    %% Open the file
    fid = fopen (filename(:));
    
    %% Read and parse line
    oneline = fgetl(fid);
    while ischar(oneline)
        %
    end
    
end
