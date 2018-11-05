    clc;
    close all;
    clear all;
    N = 3;%mT
    M = 2;%mR
    ITER = 10;
    SNRdB = [0:30];
    SNR = 10.^(SNRdB/10);
    CC_SISO = zeros(1,length(SNR))
    CC_SIMO = zeros(1,length(SNR));
    CC_MISO = zeros(1,length(SNR));
    CC_MIMO2x2 = zeros(1,length(SNR));
    CC_MIMO3x3 = zeros(1,length(SNR));
    CC_MIMO4x4 = zeros(1,length(SNR));
    CC_MIMO5x5 = zeros(1,length(SNR));
    for ite = 1:ITER
    h_SISO = (randn +j*randn)/sqrt(2);
    h_SIMO = (randn(M,1)+j*randn(M,1))/sqrt(2);
    h_MISO = (randn(1,N)+j*randn(1,N))/sqrt(2);
    h_MIMO2x2 = (randn(2,2)+j*randn(2,2))/sqrt(2);
    h_MIMO3x3 = (randn(3,3)+j*randn(3,3))/sqrt(2);
    h_MIMO4x4 = (randn(4,4)+j*randn(4,4))/sqrt(2);
    h_MIMO5x5 = (randn(5,5)+j*randn(5,5))/sqrt(2);
    for k=1:length(SNR)
        %CC_SISO(k) = log2(1+SNR(k))+ log2(1+ SNR(k)*norm(h_SISO)^2);
        %CC_SIMO(k) = log2(1+2*SNR(k)) + log2(1+ SNR(k)*norm(h_SIMO)^2);
        %CC_SIMO(k) = log2(1+3*SNR(k)) + log2(1+ SNR(k)*norm(h_MISO)^2);
        %CC_MIMO2x2(k) = log2(1+2*2*SNR(k)) + log2(1+ SNR(k)*norm(h_MIMO2x2)^2);
        %CC_MIMO3x3(k) = log2(1+3*3*SNR(k)) + log2(1+ SNR(k)*norm(h_MIMOx3)^2);
        %CC_MIMO4x4(k) = log2(1+4*4*SNR(k)) + log2(1+ SNR(k)*norm(h_MIMO4x4)^2);
        %CC_MIMO5x5(k) = log2(1+5*5*SNR(k)) + log2(1+ SNR(k)*norm(h_MIMO5x5)^2);

        CC_SISO(k) = CC_SISO(k)+log2(1+ SNR(k)*norm(h_SISO)^2);
        CC_SIMO(k) = CC_SIMO(k)+log2(1+ SNR(k)*norm(h_SIMO)^2);
        CC_MISO(k) = CC_MISO(k)+log2(1+ SNR(k)*norm(h_MISO)^2/3);
        CC_MIMO2x2(k) = log2(abs(det(eye(2)+SNR(k)*h_MIMO2x2*h_MIMO2x2'/2)));    
        CC_MIMO3x3(k) = log2(abs(det(eye(3)+SNR(k)*h_MIMO3x3*h_MIMO3x3'/3)));
        CC_MIMO4x4(k) = log2(abs(det(eye(4)+SNR(k)*h_MIMO4x4*h_MIMO4x4'/4)));
        CC_MIMO5x5(k) = log2(abs(det(eye(5)+SNR(k)*h_MIMO5x5*h_MIMO5x5'/5)));

    end
    end

    CC_SISO = CC_SISO/ITER;
    CC_SIMO = CC_SIMO/ITER;
    CC_MISO = CC_MISO/ITER;
    %CC_MIMO2x2 = CC_MIMO2x2/ITER;
    %CC_MIMO3x3 = CC_MIMO3x3/ITER;
    %CC_MIMO4x4 = CC_MIMO4x4/ITER;
    %CC_MIMO5x5 = CC_MIMO5x5/ITER;
    figure(1);

    plot(SNRdB,CC_SISO,'r');
    %axis([0 30 0 45]);
    hold on;
    plot(SNRdB,CC_SIMO,'b');
    plot(SNRdB,CC_MISO,'m');
    plot(SNRdB,CC_MIMO2x2,'k');
    legend('SISO','SIMO(1x2)','MISO(3x1)','MIMO(2x2)');
    xlabel('SNR in dB')
    ylabel('Capacity (b/s/Hz)')
    title('Channel Capacity vs SNR')
    figure(2);
    plot(SNRdB,CC_MIMO2x2,'k');
    hold on;
    plot(SNRdB,CC_MIMO3x3,'m');
    plot(SNRdB,CC_MIMO4x4,'b');
    plot(SNRdB,CC_MIMO5x5,'r');
    legend('MIMO(2x2)','MIMO(3x3)','MIMO(4x4)','MIMO(5x5)');
    xlabel('SNR in dB')
    ylabel('Capacity (b/s/Hz)')
    title('Channel Capacity vs SNR')
