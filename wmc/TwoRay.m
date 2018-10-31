    clear all;
    close all;
    lambda = 0.3; 
    %f=c/lambda;
    ht100=100;
    ht30=30;
    ht2=2;

    clear al;
    close all;

    hr=10;

    p100=[];
    p30=[];
    p2=[];
    pfsDB=[];
    x=[];
    dist=10;
    twoRay100PLdB=[];
    twoRay30PLdB=[];
    twoRay2PLdB=[];
    freeSpacePLdB=[];
    %for i=1:5
     %   for j=10:0.02:50
     %       dist=j^i;
      %      x=[x dist];
       %     freeSpacePL=(lambda/(4*3.1415*dist))^2 ;
        %    twoRay100PL = freeSpacePL* 4 *(sin(2*3.1415*hr*ht100/(lambda*dist)))^2;
         %   twoRay30PL  = freeSpacePL* 4 *(sin(2*3.1415*hr*ht30/(lambda*dist)))^2;
          %  twoRay2PL   = freeSpacePL* 4 *(sin(2*3.1415*hr*ht2/(lambda*dist)))^2;

    %        twoRay100PLdB = [twoRay100PLdB 10*log10(twoRay100PL)];
     %       twoRay30PLdB = [twoRay30PLdB 10*log10(twoRay30PL)];
      %      twoRay2PLdB = [twoRay2PLdB 10*log10(twoRay2PL)];
       %     freeSpacePLdB = [freeSpacePLdB 10*log10(freeSpacePL)];

        %end    
    %end

    %for i=1:5000
     %   dist=(10)^(i/1000);
     for i=50:1:8000
        dist=10^(i/1000);
        x=[x dist];
        freeSpacePL=(lambda/(4*3.1415*dist))^2 ;
        twoRay100PL = freeSpacePL* 4 *(sin(2*3.1415*hr*ht100/(lambda*dist)))^2;
        twoRay30PL  = freeSpacePL* 4 *(sin(2*3.1415*hr*ht30/(lambda*dist)))^2;
        twoRay2PL   = freeSpacePL* 4 *(sin(2*3.1415*hr*ht2/(lambda*dist)))^2;

        twoRay100PLdB = [twoRay100PLdB 10*log10(twoRay100PL)];
        twoRay30PLdB = [twoRay30PLdB 10*log10(twoRay30PL)];
        twoRay2PLdB = [twoRay2PLdB 10*log10(twoRay2PL)];
        freeSpacePLdB = [freeSpacePLdB 10*log10(freeSpacePL)];

    end




    figure(1);
    semilogx(x,twoRay100PLdB,'g-');%green
    hold on;
    semilogx(x,twoRay30PLdB, 'b-');%blue
    semilogx(x,twoRay2PLdB, 'r-');%red
    semilogx(x,freeSpacePLdB,'k-');%black


    xlabel('distance in m');
    ylabel('pathloss');
