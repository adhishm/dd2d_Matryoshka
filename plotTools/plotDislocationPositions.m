function plotDislocationPositions (dataFiles)
%% plotDislocationPositions (dataFiles)
%  This function plots dislocation positions that are stored in files the
%  names of which are given in the vector dataFiles. The data in the files
%  are in 2 columns: the first one gives the time in seconds and the second
%  one the position in metres.

    %% Get number of files
    nFiles = size(dataFiles,1);
    
    %% Symbols and colours
    symbols = [ '.'; '-'; '+'; 'x'; 'o'];
    nSymbols = length(symbols);
    
    colours = [ 'r'; 'g'; 'b'; 'y'; 'c'; 'm'; 'k' ];
    nColours = length(colours);
    
    
    %% Colour index
    colourIndex = 0;
    
    %% Read each file, scale the axes, and plot its data
    for i=1:nFiles
        figure;
        title(dataFiles(i,:));
        hold on;
        % Each file has its own colour
        colourIndex = returnIndex(colourIndex, nColours);
        % Symbol index
        symbolIndex = 0;
        % Read data
        data = dlmread (dataFiles(i,:));
        % Number of defects = (number of columns - 1)
        nDefects = size(data,2)-1;
        % Scale time to milliseconds
        data(:,1) = 1.0e3 * data(:,1);
        % Scale positions to microns and plot
        for j=2:(nDefects+1)
            data(:,j) = 1.0e6 * data(:,j);
            symbolIndex = returnIndex(symbolIndex, nSymbols);
            %plot (data(:,1), data(:,j), [symbols(symbolIndex) colours(colourIndex)]);
            plot (data(:,1), data(:,j), ['-' colours(colourIndex)]);
        end
        clear data;
    end
    
    hold off;
    
    xlabel ('Time (ms)');
    ylabel ('Distance (10^{-6}m)');
    
end

function index = returnIndex (currentIndex, indexMax)
    
    index = currentIndex + 1;
    
    if (index > indexMax)
        index = 1;
    end
end
