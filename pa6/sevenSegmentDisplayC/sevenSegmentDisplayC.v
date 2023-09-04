input [3:0] numeral_bit;

output c;

wire not_numeral_bit_3;
wire not_numeral_bit_2;
wire not_numeral_bit_1;
wire not_numeral_bit_0;

wire not_numeral_bit_3_and_not_numeral_bit_2; 
wire not_numeral_bit_0_and_numeral_bit_1; 
wire minterm_02; 

assign not_numeral_bit_3 = ~ numeral_bit[3];
assign not_numeral_bit_2 = ~ numeral_bit[2];
assign not_numeral_bit_1 = ~ numeral_bit[1];
assign not_numeral_bit_0 = ~ numeral_bit[0];

assign not_numeral_bit_3_and_not_numeral_bit_2 = not_numeral_bit_3 & not_numeral_bit_2; 
assign not_numeral_bit_0_and_numeral_bit_1 = not_numeral_bit_0 & numeral_bit[1]; 
assign minterm_02 = not_numeral_bit_3_and_not_numeral_bit_2 & not_numeral_bit_0_and_numeral_bit_1; 

assign c = ~ minterm_02;
