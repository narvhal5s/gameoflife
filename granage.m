%%Le Gran¿ 
clear;
n = 11;
start = -1;
stop = 1;
range = abs(start - stop);
interval = range /( n - 1);
y = zeros(n , 1);
x = zeros(n , 1);
k = 1;
for i = start:interval:stop
    y(k , 1) = 1/(1 + i^10);
    x(k , 1) = i ;
    k=k+1;
end

    xwartosci = start:0.002:stop;
    ywartosci = start:0.002:stop;
    zwartosci = start:0.002:stop;
    licznik = 1;
    for xwartosc = start:0.002:stop
        zwartosci(licznik) = 1/(1+xwartosc^10);
        suma = 0;
        for i = 1:n
            mnozenie = 1;
            for j = 1:n
                if  i == j 
                    continue
                end
                mnozenie = mnozenie * ( ( xwartosc - x(j,1)) / (x(i,1)- x(j,1)));
            end
            suma = suma + (y( i , 1) * mnozenie);
        end
        ywartosci(licznik) = suma; 
        licznik = licznik + 1;
    end
    plot(xwartosci , ywartosci , 'b'); 
    hold on;
   xlim([ start , stop]); 
    ylim([ -5 , 5]);  
    grid on;
    plot(xwartosci , zwartosci ,'r');
    plot(x , y , 'o');
    legend('inter','chuj')
    
    roznica = abs(ywartosci - zwartosci);
    maks = max(roznica)
    chgw = mean(roznica)
    
    a = zeros( n , 1) ;
    
    