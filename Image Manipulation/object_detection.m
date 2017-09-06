clc
clear all
close all

c=(imread('../Assignment_1/sample.png'));
[x,y] = size(c);
[m,n,o] = size(c);
d = uint8(zeros(m,n,o));
f=d;
x_min=n;
y_min=m;
x_max=0;
y_max=0;

x_min1=n;
y_min1=m;
x_max1=0;
y_max1=0;


e=c;
for i=1:x 
    for j=1:y
       e(i,j)=e(i,j)+50;  
    end
end

for i=1:m
    for j=1:n
        Red = double(c(i,j,1));
        Green = double(c(i,j,2));
        Blue = double(c(i,j,3));
        if ((Red > 100) && (Green < 52) && (Blue < 60))
            d(i,j,1) = 255;
            d(i,j,2) = 255;
            d(i,j,3) = 255;
            if(i < x_min)
                x_min = i;
            end
            if(i > x_max)
                x_max = i;
            end
            if(j < y_min)
                y_min = j;
            end
            if(j > y_max)
                y_max = j;
            end
        else
            d(i,j,1) = 0;
            d(i,j,2) = 0;
            d(i,j,3) = 0;
        end
    end
end

for i=1:m
    for j=1:n
        Red1 = double(e(i,j,1));
        Green1 = double(e(i,j,2));
        Blue1 = double(e(i,j,3));
        if ((Red1 > 150) && (Green1 < 102) && (Blue1 < 110))
            f(i,j,1) = 255;
            f(i,j,2) = 255;
            f(i,j,3) = 255;
            if(i < x_min1)
                x_min1 = i;
            end
            if(i > x_max1)
                x_max1 = i;
            end
            if(j < y_min1)
                y_min1 = j;
            end
            if(j > y_max1)
                y_max1 = j;
            end
        else
            f(i,j,1) = 0;
            f(i,j,2) = 0;
            f(i,j,3) = 0;
        end
    end
end



x_temp = x_max - x_min;
y_temp = y_max - y_min;
figure;
imshow(c);
title('Original RGB Image');
figure;
imshow(d);
hold on
rectangle('Position',[y_min x_min y_temp x_temp],'EdgeColor','r')
hold off
title('Object detection based on color in RGB domain');

x_temp1 = x_max1 - x_min1;
y_temp1 = y_max1 - y_min1;
figure;
imshow(e);
title('Original RGB brightened Image');
figure;
imshow(f);
hold on
rectangle('Position',[y_min1 x_min1 y_temp1 x_temp1],'EdgeColor','r')
hold off
title('Object detection based on color in RGB brightened domain');
