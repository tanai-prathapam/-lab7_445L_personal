C = 1200e-6;
R_C = 11e-3;
L = 10e-6;
R_L = 30e-3;
s = 1j * sqrt(L*C);
R_s = 0.25; % found through binary search
filter_tf = tf([(R_C + R_s) * C, 1], [L * C, C * (R_L + R_C + R_s), 1]);
bode(filter_tf)