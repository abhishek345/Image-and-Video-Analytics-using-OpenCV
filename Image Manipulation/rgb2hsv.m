clc
clear all
close all

c=(imread('../Assignment_1/sample.png'));

[x,y] = size(c);
[m,n,o] = size(c);
d = uint8(zeros(m,n,o));
f = d;
e = c;

for i=1:x 
    for j=1:y
       e(i,j)=e(i,j)+50;  
    end
end
figure;
imshow(c);
title('RGB Original image');


for i=1:m
    for j=1:n
        Red = double(c(i,j,1));
        Red1 = double(e(i,j,1));
        float_red = Red/255;
        float_red1 = Red1/255;
        Green = double(c(i,j,2));
        float_green = Green/255;
        Green1 = double(e(i,j,2));
        float_green1 = Green1/255;
        Blue = double(c(i,j,3));
        float_blue = Blue/255;
        Blue1 = double(e(i,j,3));
        float_blue1 = Blue1/255;
        
        
        if ((float_red > float_green) && (float_red > float_blue))
            V_max=float_red;
        else
            if ((float_green > float_red) && (float_green > float_blue))
                V_max=float_green;
            else
                V_max=float_blue;
            end
        end
        
        if ((float_red1 > float_green1) && (float_red1 > float_blue1))
            V_max1=float_red1;
        else
            if ((float_green1 > float_red1) && (float_green1 > float_blue1))
                V_max1=float_green1;
            else
                V_max1=float_blue1;
            end
        end
        
        
        if ((float_red < float_green) && (float_red < float_blue))
            V_min=float_red;
        else
            if ((float_green < float_red) && (float_green < float_blue))
                V_min=float_green;
            else
                V_min=float_blue;
            end
        end
        
        if ((float_red1 < float_green1) && (float_red1 < float_blue1))
            V_min1=float_red1;
        else
            if ((float_green1 < float_red1) && (float_green1 < float_blue1))
                V_min1=float_green1;
            else
                V_min1=float_blue1;
            end
        end
        
        
        if (V_max == 0)
            S = 0;
        else
            S = (V_max - V_min)/V_max;
        end
        
        if (V_max1 == 0)
            S1 = 0;
        else
            S1 = (V_max1 - V_min1)/V_max1;
        end
      
        if (V_max == float_red)
            H = 60*(float_green - float_blue)/(V_max - V_min);
        elseif (V_max == float_green)
            H = 120 + (60*(float_blue - float_red)/(V_max - V_min));
        else
            H = 240 + (60*(float_red - float_green)/(V_max - V_min));
        end

        if (V_max1 == float_red1)
            H1 = 60*(float_green1 - float_blue1)/(V_max1 - V_min1);
        elseif (V_max1 == float_green1)
            H1 = 120 + (60*(float_blue1 - float_red1)/(V_max1 - V_min1));
        else
            H1 = 240 + (60*(float_red1 - float_green1)/(V_max1 - V_min1));
        end

        
        if (H < 0)
            H = H + 360;
        end
 
        if (H1 < 0)
            H1 = H1 + 360;
        end
        
        V_max = 255*V_max;
        S = 255*S;
        H = H/2;
        
        d(i,j,1) = H;
        d(i,j,2) = S;
        d(i,j,3) = V_max;
        
        V_max1 = 255*V_max1;
        S1 = 255*S1;
        H1 = H1/2;
        
        f(i,j,1) = H1;
        f(i,j,2) = S1;
        f(i,j,3) = V_max1;
        
    end
end


figure;
imshow(d);
title('RGB to HSV converted Image');

figure
imshow(e);
title('RGB Brightened Image');

figure
imshow(f);
title('RGB Brightened Image to HSV Image');

