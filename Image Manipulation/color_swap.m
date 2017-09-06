clc
clear all
close all

c=imread('../Assignment_1/sample.png');

figure
imshow(c);
title('Original Image');

new(:,:,1)=c(:,:,2);
new(:,:,2)=c(:,:,1);
new(:,:,3)=c(:,:,3);

figure
imshow(new);
title('Color Swapped Image');