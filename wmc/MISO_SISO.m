    % This program will give the comparison between two scheme: SISO and MIMO,
    % in which, with SISO scheme, the capacity will follow the equation of
    % Shannon. It shows that the capacity receiving from MIMO scheme will be 
    % larger than in SISO
    % 
    % Input: 
    %   +) Signal Noise Rate: SNR
    %   +) The number of receiving antennas Nr and transmiting antennas Nt
    %   +) The channel co-efficient will follow Rayleigh distribution in which
    %   the dimension of H depends on the number of receiving and transmiting
    %   antennas
    %   +) Bandwidth of channel: B = 1

    clc;
    clear all;
    SNR_DB = [0:0.01:50];
    SNR = 10.^(SNR_DB/10);

    % The capacity of SISO model
    C_SISO = log2(1+SNR);
    figure
    plot(SNR_DB,C_SISO,'-','LineWidth',1.5,'Color','g');
    hold on

    % The capacity of MIMO model
    Nr = 3;
    Nt = 3;

    N = min(Nr,Nt);
    H = zeros(Nr,Nt);
    for k=1:Nr
        for l=1:Nt
            H(k,l) = randn(1) + j* randn(1);
        end
    end

    [S V D] = svd(H*H');

    C_MIMO = 0;
    % When CSI is not available at the transmitter side
    for k=1:N
        lamda(k) = V(k,k);
        C_MIMO = C_MIMO + log2(1+SNR*lamda(k)/Nt);
    end

    plot(SNR_DB,C_MIMO, 'LineWidth', 1.5);
    legend('SISO','MIMO');
    xlabel('SNR');
    ylabel('Capacity');



