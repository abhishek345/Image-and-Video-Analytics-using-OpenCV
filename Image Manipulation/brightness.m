clc
close all
clear all

c=imread('../Assignment_1/sample.png');
d=c;
[m,n]=size(c);

for i=1:m 
    for j=1:n
       c(i,j)=c(i,j)+50; 
    end
end
figure
imshow(d);
title('RGB Original Image');
figure
imshow(c);
title('RGB Brightened Image');
