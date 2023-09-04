input [3:0] numeral_bit;

output a;
output b;
output c;
output d;
output e;
output f;
output g;

wire not_numeral_bit_3;
wire not_numeral_bit_2;
wire not_numeral_bit_1;
wire not_numeral_bit_0;

wire minterm_00;
wire minterm_01;
wire minterm_02;
wire minterm_03;
wire minterm_04;
wire minterm_05;
wire minterm_06;
wire minterm_07;
wire minterm_08;
wire minterm_09;

wire not_numeral_bit_3_and_not_numeral_bit_2; 
wire not_numeral_bit_1_and_numeral_bit_0; 
wire not_numeral_bit_1_and_not_numeral_bit_0; 
wire not_numeral_bit_3_and_numeral_bit_2; 
wire minterm_01_or_minterm_04;

wire numeral_bit_1_and_not_numeral_bit_0; 
wire minterm_05_or_minterm_06;

wire numeral_bit_1_and_numeral_bit_0; 

wire minterm_07_or_minterm_09;
wire m1479;  

wire numeral_bit_3_and_not_numeral_bit_2; 
wire minterm_00_or_minterm_02;
wire minterm_06_or_minterm_08;  

wire minterm_01_or_minterm_02; 
wire minterm_03_or_minterm_07; 
wire m1_or_m2_or_m3_or_m7; 

wire minterm_00_or_minterm_01; 
wire m0_or_m1_or_m7; 

assign not_numeral_bit_3 = ~ numeral_bit[3];
assign not_numeral_bit_2 = ~ numeral_bit[2];
assign not_numeral_bit_1 = ~ numeral_bit[1];
assign not_numeral_bit_0 = ~ numeral_bit[0];





assign not_numeral_bit_3_and_not_numeral_bit_2 = not_numeral_bit_3 & not_numeral_bit_2; 
assign not_numeral_bit_1_and_numeral_bit_0 = not_numeral_bit_1 & numeral_bit[0]; 
assign minterm_01 = not_numeral_bit_3_and_not_numeral_bit_2 & not_numeral_bit_1_and_numeral_bit_0; 

assign not_numeral_bit_1_and_not_numeral_bit_0 = not_numeral_bit_1 & not_numeral_bit_0; 
assign not_numeral_bit_3_and_numeral_bit_2 = not_numeral_bit_3 & numeral_bit[2]; 
assign minterm_04 = not_numeral_bit_1_and_not_numeral_bit_0 & not_numeral_bit_3_and_numeral_bit_2; 

assign minterm_01_or_minterm_04 = minterm_01 | minterm_04; 
assign a = ~ minterm_01_or_minterm_04; 








assign minterm_05 = not_numeral_bit_3_and_numeral_bit_2 & not_numeral_bit_1_and_numeral_bit_0; 

assign numeral_bit_1_and_not_numeral_bit_0 = numeral_bit[1] & not_numeral_bit_0; 
assign minterm_06 = not_numeral_bit_3_and_numeral_bit_2 & numeral_bit_1_and_not_numeral_bit_0;

assign minterm_05_or_minterm_06 = minterm_05 | minterm_06; 
assign b =  ~ minterm_05_or_minterm_06; 











assign minterm_02 = not_numeral_bit_3_and_not_numeral_bit_2 & numeral_bit_1_and_not_numeral_bit_0; 
assign c = ~ minterm_02;








assign numeral_bit_1_and_numeral_bit_0 = numeral_bit[1] & numeral_bit[0]; 
assign minterm_07 = not_numeral_bit_3_and_numeral_bit_2 & numeral_bit_1_and_numeral_bit_0; 


assign numeral_bit_3_and_not_numeral_bit_2 = numeral_bit[3] & not_numeral_bit_2; 
assign minterm_09 = numeral_bit_3_and_not_numeral_bit_2 & not_numeral_bit_1_and_numeral_bit_0; 

assign minterm_07_or_minterm_09 = minterm_07 | minterm_09; 

assign m1479 = minterm_01_or_minterm_04 | minterm_07_or_minterm_09; 
assign d = ~ m1479; 








assign minterm_00 = not_numeral_bit_3_and_not_numeral_bit_2 & not_numeral_bit_1_and_not_numeral_bit_0; 

assign minterm_08 = numeral_bit_3_and_not_numeral_bit_2 & not_numeral_bit_1_and_not_numeral_bit_0; 

assign minterm_00_or_minterm_02 = minterm_00 | minterm_02; 
assign minterm_06_or_minterm_08 = minterm_06 | minterm_08; 
assign e = minterm_00_or_minterm_02 | minterm_06_or_minterm_08;











assign minterm_03 = not_numeral_bit_3_and_not_numeral_bit_2 & numeral_bit_1_and_numeral_bit_0; 

assign minterm_01_or_minterm_02 = minterm_01 | minterm_02; 
assign minterm_03_or_minterm_07 = minterm_03 | minterm_07; 
assign m1_or_m2_or_m3_or_m7 = minterm_01_or_minterm_02 | minterm_03_or_minterm_07;
assign f = ~ m1_or_m2_or_m3_or_m7; 












assign minterm_00_or_minterm_01 = minterm_00 | minterm_01; 
assign m0_or_m1_or_m7 = minterm_00_or_minterm_01 | minterm_07; 
assign g = ~ m0_or_m1_or_m7; 
