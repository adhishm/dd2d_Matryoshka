function plotStresses (stressFileName, dislPosFileName)
%% plotStresses (stressFileName, dislPosFileName)
%  Plots the stresses along a slip plane. These stresses are stored in the 
%  file whose name is provided as the argument.

    %% Read stress data
    data = dlmread (stressFileName);
    % Number of points
    nPoints = size (data, 1);
    % Points
    points = data(:,1:3);
    % Local and global stresses
    sLocal  = data(:,4:9);
    sGlobal = data(:,10:15);
    
    %% Calculate distances
    d = zeros(nPoints,1);
    p0 = points(1,:);
    for i=1:nPoints
      d(i) = norm(points(i,:)-p0);
    end
    
    %% Get dislocation data
    [~, dists] = findDislocationPositions (dislPosFileName);
    nDisl = size(dists,1);
    zeroPoints = zeros(nDisl,1);
        

    %% Local stresses
    figure
    hold on
    plot (d, sLocal(:,1), '.-r'); % s_xx
    plot (d, sLocal(:,2), '.-g'); % s_yy
    plot (d, sLocal(:,3), '.-b'); % s_zz
    plot (d, sLocal(:,4), '.-k'); % s_xy
    plot (d, sLocal(:,5), '.-c'); % s_xz
    plot (d, sLocal(:,6), '.-m'); % s_yz
    plot (dists, zeroPoints, 'xk'); % Dislocations
    legend ('s_{xx}', 's_{yy}', 's_{zz}', 's_{xy}', 's_{xz}', 's_{yz}');
    xlabel ('Distance (m)');
    ylabel ('Local stresses s_{ij}');
    title ('Stresses in local co-ordinate system');
    hold off
    
    %% Global stresses
    figure
    hold on
    plot (d, sGlobal(:,1), '.-r'); % s_xx
    plot (d, sGlobal(:,2), '.-g'); % s_yy
    plot (d, sGlobal(:,3), '.-b'); % s_zz
    plot (d, sGlobal(:,4), '.-k'); % s_xy
    plot (d, sGlobal(:,5), '.-c'); % s_xz
    plot (d, sGlobal(:,6), '.-m'); % s_yz
    plot (dists, zeroPoints, 'xk'); % Dislocations
    legend ('s_{xx}', 's_{yy}', 's_{zz}', 's_{xy}', 's_{xz}', 's_{yz}');
    xlabel ('Distance (m)');
    ylabel ('Global stresses s_{ij}');
    title ('Stresses in global co-ordinate system');
    hold off

    %% Clear data
    clear data;
    clear sLocal;
    clear sGlobal;

end
