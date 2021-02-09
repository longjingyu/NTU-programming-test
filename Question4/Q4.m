clear;clc

input = dlmread('input_question_4', '\t');
cc = bwconncomp(input, 4); % 4-connective or 8-connective
num_comp = cc.NumObjects;
for i=1:num_comp
    input(cc.PixelIdxList{i}) = i;
end

fid = fopen('output_question_4.txt', 'w');
[c, r] = size(input);
for i=1:c
    for j=1:r
        fprintf(fid, '%d', input(i, j));
        if(j < r)
            fprintf(fid, ' ');
        end
    end
    fprintf(fid, '\r\n');
end