clear;
clc;

in_polygon = dlmread('input_question_6_polygon', ' ');
in_points = dlmread('input_question_6_points', ' ');
pgon = polyshape(in_polygon(:, 1), in_polygon(:, 2));
res = is_in_polygon(in_polygon, in_points);
% res=1,inside:res=0,outside
plot(pgon)
hold on;
scatter(in_points(:, 1), in_points(:, 2));
a = [1:length(in_points)]';
b = num2str(a);
dx = 0.5; dy = 0.5;
text(in_points(:, 1)+dx, in_points(:, 2)+dy, b);

test_polygon = [[1, 1, 10, 10]; [1, 5, 5, 1]]';
test_points = [[3, 7, 5]; [3, 5, 6]]';
res2 = is_in_polygon(test_polygon, test_points);

function res = is_in_polygon(polygon, points)
    res = zeros(length(points), 1);
    for i=1:length(points)
        wn = 0;
        for j=1:length(polygon)
            if(j < length(polygon))
                v1 = polygon(j, :)-points(i, :);
                v2 = polygon(j+1, :)-points(i, :);
            else
                v1 = polygon(j, :)-points(i, :);
                v2 = polygon(1, :)-points(i, :);
            end
            [t1, ~] = cart2pol(v1(1), v1(2));
            [t2, ~] = cart2pol(v2(1), v2(2));
            if(t1 - t2 < -pi)
                delta = t1 - t2 + 2*pi;
            else
                if(t1 - t2 > pi)
                    delta = 2*pi - (t1 - t2);
                else
                    delta = t1 - t2;
                end
            end
            wn = wn + delta;
        end
        res(i) = abs(wn / (2*pi)) >= 1-1e-10;
    end
end


