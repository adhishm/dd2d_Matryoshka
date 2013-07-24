function [dislocationPositions, dislocationDistances] = findDislocationPositions (filename)
%% [dislocationPositions, dislocationDistances] = findDislocationPositions
%  (filename)
%  This function reads the dislocation positions from a file and returns
%  them in a matrix (nx3). It also returns the distances with respect to
%  the first dislocation in the list

    %% Read the data
    data = dlmread (filename);
    
    %% Extract positions
    dislocationPositions = data (:,1:3);
    
    %% Extract distances
    d0 = dislocationPositions(1,1:3);
    nDisl = size(dislocationPositions,1);
    dislocationDistances = zeros(nDisl,1);
    for i=1:nDisl
        dislocationDistances(i) = norm (dislocationPositions(i,:) - d0);
    end
    
end
