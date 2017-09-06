clc
clear all
close all

c=(imread('../Assignment_1/sample.png'));
[x,y]=size(c);
[m,n,o] = size(c);
d = uint8(zeros(m,n,o));
temp = zeros(m,n,o);
f=d;
g=temp;

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
        float_red = Red/255;
        Green = double(c(i,j,2));
        float_green = Green/255;
        Blue = double(c(i,j,3));
        float_blue = Blue/255;
        
        Red1 = double(e(i,j,1));
        float_red1 = Red1/255;
        Green1 = double(e(i,j,2));
        float_green1 = Green1/255;
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
        
        V_max1 = 255*V_max1;
        S1 = 255*S1;
        H1 = H1/2;
        
        g(i,j,1) = H1;
        g(i,j,2) = S1;
        g(i,j,3) = V_max1;
        
        temp(i,j,1) = H;
        temp(i,j,2) = S;
        temp(i,j,3) = V_max;
    end
end


for i=1:m
    for j=1:n
        Red2 = double(temp(i,j,1));
        Green2 = double(temp(i,j,2));
        Blue2 = double(temp(i,j,3));
        
        Red3 = double(g(i,j,1));
        Green3 = double(g(i,j,2));
        Blue3 = double(g(i,j,3));
        
        if ((Red2 < 9.25) && (Green2 > 115) && (Blue2 > 70))
            f(i,j,1) = 255;
            f(i,j,2) = 255;
            f(i,j,3) = 255;
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
            f(i,j,1) = 0;
            f(i,j,2) = 0;
            f(i,j,3) = 0;
        end
        
        if ((Red3 < 10.3) && (Green3 > 115) && (Blue3 > 70))
            d(i,j,1) = 255;
            d(i,j,2) = 255;
            d(i,j,3) = 255;
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
            d(i,j,1) = 0;
            d(i,j,2) = 0;
            d(i,j,3) = 0;
        end
        
    end
end



x_temp = x_max - x_min;
y_temp = y_max - y_min;
figure;
imshow(c);
title('Original RGB Image');
figure;
imshow(f);
hold on
rectangle('Position',[y_min x_min y_temp x_temp],'EdgeColor','r')
hold off
title('Object detection based on color in HSV domain');

x_temp1 = x_max1 - x_min1;
y_temp1 = y_max1 - y_min1;
figure;
imshow(e);
title('Original RGB brightened Image');
figure;
imshow(d);
hold on
rectangle('Position',[y_min1 x_min1 y_temp1 x_temp1],'EdgeColor','r')
hold off
title('Object detection based on color in HSV Brightened domain');
