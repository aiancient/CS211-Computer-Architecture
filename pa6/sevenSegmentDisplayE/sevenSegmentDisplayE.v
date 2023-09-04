input [3:0] numeral_bit;

output e;

wire not_numeral_bit_3;
wire not_numeral_bit_2;
wire not_numeral_bit_1;
wire not_numeral_bit_0;

wire minterm_00;
wire minterm_02;
wire minterm_06;
wire minterm_08;

wire minterm_00_or_minterm_02;
wire minterm_06_or_minterm_08; 

wire not_numeral_bit_3_and_not_numeral_bit_2; 
wire not_numeral_bit_1_and_not_numeral_bit_0; 

wire not_numeral_bit_0_and_numeral_bit_1; 

wire not_numeral_bit_3_and_not_numeral_bit_0; 
wire numeral_bit_2_and_numeral_bit_1; 

wire not_numeral_bit_1_0_and_not_numeral_bit_2; 

assign not_numeral_bit_3 = ~ numeral_bit[3];
assign not_numeral_bit_2 = ~ numeral_bit[2];
assign not_numeral_bit_1 = ~ numeral_bit[1];
assign not_numeral_bit_0 = ~ numeral_bit[0];

assign not_numeral_bit_3_and_not_numeral_bit_2 = not_numeral_bit_3 & not_numeral_bit_2; 
assign not_numeral_bit_1_and_not_numeral_bit_0 = not_numeral_bit_1 & not_numeral_bit_0; 
assign minterm_00 = not_numeral_bit_3_and_not_numeral_bit_2 & not_numeral_bit_1_and_not_numeral_bit_0; 

assign not_numeral_bit_0_and_numeral_bit_1 = not_numeral_bit_0 & numeral_bit[1]; 
assign minterm_02 = not_numeral_bit_3_and_not_numeral_bit_2 & not_numeral_bit_0_and_numeral_bit_1; 

assign not_numeral_bit_3_and_not_numeral_bit_0 = not_numeral_bit_3 & not_numeral_bit_0; 
assign numeral_bit_2_and_numeral_bit_1 = numeral_bit[2] & numeral_bit[1]; 
assign minterm_06 = not_numeral_bit_3_and_not_numeral_bit_0 & numeral_bit_2_and_numeral_bit_1; 

assign not_numeral_bit_1_0_and_not_numeral_bit_2 = not_numeral_bit_1_and_not_numeral_bit_0 & not_numeral_bit_2; 
assign minterm_08 = not_numeral_bit_1_0_and_not_numeral_bit_2 & numeral_bit[3]; 

assign minterm_00_or_minterm_02 = minterm_00 | minterm_02; 
assign minterm_06_or_minterm_08 = minterm_06 | minterm_08; 
assign e = minterm_00_or_minterm_02 | minterm_06_or_minterm_08;
