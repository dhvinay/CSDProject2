%% ReadEnums.m
%{  
    This file pareces through files in the source, finds enums, and creates
    then in the workspace for use in model.
%}
%% Setup
cd(projectPath);
cd('Data');

enumFile = horzcat(ProjectName,'_emuns.m');

ouputFileStream = fopen(enumFile, 'w');
%% Parse
for x = 1:size(EnumFileNames,2)
    filePath = strcat('..\..\Src\', char(EnumFileNames(x)));

    fileStream = fopen(filePath);
    
    if ( fileStream == -1 )
        
        filePath = strcat('..\', char(EnumFileNames(x)));

        fileStream = fopen(filePath);
         
    end

    currentLine = fgetl(fileStream);

    %Initialization
    enumValue = 0;
    enumArray = [];
    definesArray = [];
    array = [];
    arrayOfEnumArrays = {};
    arrayOfDefines = {};

    %Loop through every line of the file
    while ischar(currentLine)

        %current line of the file
        currentLine = fgetl(fileStream);

        %Look for the string "enum" to determine where an enum declaration starts
        %This next block will parse the entire enum
        if ( strfind(currentLine, 'enum') )

            %Get the next line and check that it's an "{" bracket to
            %indicate the enum is being declared
            currentLine = fgetl(fileStream);
            if( strfind(currentLine, '{') )

                %Get the next line and loop through the lines of the file
                %until "}" is found
                currentLine = fgetl(fileStream);
                while(isempty(strfind(currentLine, '}') ) )

                    %Store each line of the enum into enumArray so that it
                    %can be parsed later
                    currentLine = strtrim(currentLine);
                    enumArray{end + 1} = currentLine;

                    currentLine = fgetl(fileStream);
                end

                %Since each enumArray contains all the data of a single
                %enum block, we need an array of enumArrays when multiple
                %enums are defined in a single file
                arrayOfEnumArrays{ end + 1} = enumArray;
                enumArray = [];
            end
        end
        
        
       if ( ~isempty(strfind(currentLine, '#define')) && isempty((strfind(currentLine, '_H_'))))
            arrayOfDefines{end + 1} = strtrim(currentLine);
       end
    end


    %Here we parse the array
    for i = 1:numel(arrayOfEnumArrays)

        currentEnum = arrayOfEnumArrays(1, i);
        currentEnum = char(currentEnum{1});

        %Loop through the number of enums found
        for n = 1:size(currentEnum,1)

            thisEnum = char(currentEnum(n,:));

            %Here we determine if the values of the enum are implied or are
            %literally assigned
            if( isempty(strfind(thisEnum, '=') ) )

                splitString = char(strsplit(thisEnum, ','));
                array = [array; cellstr(splitString(1,:)) cellstr(int2str(enumValue))];

            else
                splitString = char(strsplit(thisEnum));

                if( ~isempty(strfind(thisEnum, 'x') ))   
                    out = sscanf(splitString(3,:),'%x');
                else
                    out = sscanf(splitString(3,:),'%u');
                end

                enumValue = out;

                array = [array; cellstr(splitString(1,:)) cellstr(int2str(out))] ;
            end

                enumValue = enumValue + 1;
        end

        enumValue = 0;
    end


    for i = 1:numel(arrayOfDefines)
        
        stringSplitBySpaces = strsplit(arrayOfDefines{i});
        
        if (size(stringSplitBySpaces,2) == 3) && (~contains(char(stringSplitBySpaces(:,3)),'//'))
            
            defineName = stringSplitBySpaces(:,2);
            defineValue = char(stringSplitBySpaces(:,3));

            if( ~isempty(strfind(defineValue, 'x') ))   
                out = sscanf(char(defineValue),'%x');
            else
                out = sscanf(defineValue,'%u');
            end


            if( round(out) ~= out)

                type = 'single';

            elseif( out < 0)

                if( abs(out) < 127)
                    type = 'uint8';
                elseif( abs(out) < 32767)
                    type = 'uint16';
                else
                    type = 'uint32';
                end

            elseif( out >= 0 )

                if( out < 255)
                    type = 'uint8';
                elseif( out < 65535)
                    type = 'uint16';
                else
                    type = 'uint32';
                end  
            end

            definesArray = [definesArray; defineName out type];
        end
    
    end
    
    
    for i = 1:size(array,1)

        enumStringName = array{i,1};
        enumValue = str2double(array{i,2});

        if( round(enumValue) ~= enumValue)
            
            type = 'single';
            
        elseif( enumValue < 0)
            
            if( abs(enumValue) < 127)
                type = 'uint8';
            elseif( abs(enumValue) < 32767)
                type = 'uint16';
            else
                type = 'uint32';
            end
            
        elseif( enumValue >= 0 )
            
            if( enumValue < 255)
                type = 'uint8';
            elseif( enumValue < 65535)
                type = 'uint16';
            else
                type = 'uint32';
            end  
        end
        
        formatSpec = '%s = Simulink.Parameter;\n';
        fprintf(ouputFileStream, formatSpec, enumStringName);

        formatSpec = '%s.Value = %u;\n';
        fprintf(ouputFileStream, formatSpec, enumStringName, enumValue);

        formatSpec = '%s.DataType = ''%s'';\n';
        fprintf(ouputFileStream, formatSpec, enumStringName, type);

        formatSpec = '%s.Min = [];\n';
        fprintf(ouputFileStream, formatSpec, enumStringName);

        formatSpec = '%s.Max = [];\n';
        fprintf(ouputFileStream, formatSpec, enumStringName);

        formatSpec = '%s.DocUnits = '''';\n';
        fprintf(ouputFileStream, formatSpec, enumStringName);

        formatSpec = '%s.CoderInfo.StorageClass = ''Custom'';\n';
        fprintf(ouputFileStream, formatSpec, enumStringName);

        formatSpec = '%s.CoderInfo.CustomStorageClass = ''ImportFromFile'';\n';
        fprintf(ouputFileStream, formatSpec, enumStringName);

        formatSpec = '%s.CoderInfo.CustomAttributes.HeaderFile = ''%s'';\n';
        fprintf(ouputFileStream, formatSpec, enumStringName, char(EnumFileNames(x)));

        fprintf(ouputFileStream, '\n');

    end
end

%% Load
run(enumFile);

%% Clean up
fclose(ouputFileStream);
delete(enumFile);
cd(projectPath);
clear enumFile EnumFileNames ouputFileStream filePath fileStream currentLine enumValue ...
    enumStringName currentEnum enumArray array arrayOfEnumArrays thisEnum splitString i ...
    ans arrayOfDefines stringSplitBySpaces formatSpec type out definesArray n x

